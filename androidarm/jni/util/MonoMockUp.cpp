#include <stdio.h>
#include <sys/ptrace.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/uio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <assert.h>
#include <string.h>
#include <dlfcn.h>
#include <stdarg.h>
#include <signal.h>
#include <set>
#include <string>
#include <vector>
#include <algorithm>
#include <dirent.h>
#include "logger.h"
#include "util.hpp"
#include "ProcessScanner.hpp"

unsigned int MonoArrayData::get(int index){
    return vAddr[index];
}

bool MonoClassData::isValid(ProcessScanner &pscan)
{
    if(!pscan.isDataAddress((unsigned int)this->element_class)){
	return false;
    }
    if(!pscan.isDataAddress((unsigned int)this->cast_class)){
	return false;
    }
    if(!pscan.isDataAddress((unsigned int)this->supertypes)){
	return false;
    }
    unsigned int superTypesAddr = pscan.ReadInt((unsigned int)this->supertypes);
    if(!pscan.isDataAddress(superTypesAddr)){
	return false;
    }
    return true;
}
void MonoClassData::show(ProcessScanner &pscan)
{
    printf(" -- Class ---\n");
    printf("thisAddr: 0x%08X\n",this->thisAddr);
    char *name = pscan.readMonoClassName(this->thisAddr);
    if(strlen(name)==0){
	printf("Not a MonoClass\n");
	return;
    }
    printf("name: [%s]\n",name);
    printf("element_class: 0x%08X [%s]\n",(unsigned int)this->element_class,pscan.readMonoClassName((unsigned int)this->element_class));
    printf("cast_class: 0x%08X [%s]\n",(unsigned int)this->cast_class,pscan.readMonoClassName((unsigned int)this->cast_class));
    unsigned int superTypesAddr = pscan.ReadInt((unsigned int)this->supertypes);
    printf("supertypes: 0x%08X -> 0x%08X [%s]\n",(unsigned int)this->supertypes,superTypesAddr,pscan.readMonoClassName(superTypesAddr));
    printf("parent 0x%08X  [%s]\n",(unsigned int)this->parent,pscan.readMonoClassName((unsigned int)this->parent));
    printf("nested_in 0x%08X [%s]\n",(unsigned int)this->nested_in,pscan.readMonoClassName((unsigned int)this->nested_in));
    printf("image 0x%08X\n",(unsigned int)this->image);
    
    printf("idepth: %d\n",this->idepth);
    printf("rank: %d\n",this->rank);
    printf("instance_size: %d\n",this->instance_size);
    printf("init: %d\n",this->inited);
    printf("init_pending: %d\n",this->init_pending);
    printf("size_inited: %d\n",this->size_inited);
    printf("valuetype: %d\n",this->valuetype);
    printf("enumtype: %d\n",this->enumtype);
    printf("blittable: %d\n",this->blittable);
    printf("unicode: %d\n",this->unicode);
    printf("wastypebuilder: %d\n",this->wastypebuilder);
    printf("packing_size: %d\n",this->packing_size);
    printf("has_unity_native_intptr: %d\n",this->has_unity_native_intptr);
    printf("ghcimpl: %d\n",this->ghcimpl);
    printf("has_finalize: %d\n",this->has_finalize);
    printf("marshalbyref: %d\n",this->marshalbyref);
    printf("contextbound: %d\n",this->contextbound);
    printf("delegate: %d\n",this->delegate);
    printf("gc_descr_inited: %d\n",this->gc_descr_inited);
    printf("has_cctor: %d\n",this->has_cctor);
    printf("has_references: %d\n",this->has_references);
    
    printf("exception_type: %d\n",this->exception_type);
    printf("type_token: %ld\n",this->type_token);
    printf("vtable_size: %d\n",this->vtable_size);
    printf("sizes: %d\n",this->sizes.class_size);
    printf("field count=%ld first=%ld\n",this->field.count,this->field.first);
    
    printf("fields: 0x%08X\n",(unsigned int)this->fields);
    if(pscan.isDataAddress((unsigned int)this->fields)){
	//MonoClassField fields[this->field.count];	    
	//pscan.read((unsigned int)this->fields,sizeof(fields),(unsigned int)&fields[0]);
	for(int i=0;i<this->field.count;i++){
	    MonoClassFieldData field = pscan.readMonoClassField((unsigned int)this->fields + (i*sizeof(MonoClassField)));
	    field.show(pscan);
	}
    }
    printf("method count=%ld first=%ld\n",this->method.count,this->method.first);
    
    printf("methods: 0x%08X\n",(unsigned int)this->methods);
    if(pscan.isDataAddress((unsigned int)this->methods)){
	unsigned int methodAddrs[this->method.count];	    
	pscan.read((unsigned int)this->methods,sizeof(methodAddrs),(unsigned int)&methodAddrs[0]);
	for(int i=0;i<this->method.count;i++){
	    MonoMethodData method = pscan.readMonoMethod(methodAddrs[i]);
	    method.show(pscan);
	}
    }
    printf("next_class_cache: 0x%08X\n",(unsigned int)this->next_class_cache);
    printf("generic_class: 0x%08X\n",(unsigned int)this->generic_class);
    printf("vtable: 0x%08X\n",(unsigned int)this->vtable);
    printf("runtime_info: 0x%08X\n",(unsigned int)this->runtime_info);
    
}

MonoClassFieldData MonoClassData::GetField(ProcessScanner& pscan,char *name)
{
    
    if((this->field.count >0) &&(pscan.isDataAddress((unsigned int)this->fields))){
	for(int i=0;i<this->field.count;i++){
	    MonoClassFieldData field = pscan.readMonoClassField((unsigned int)this->fields + (i*sizeof(MonoClassField)));
	    char *strName = pscan.readCString((unsigned int)field.name);
	    if(strcmp(strName,name)==0){
		return field;
	    }
	    //field.show(pscan);
	}
    }
    MonoClassFieldData ret;
    return ret;
}

struct MonoClassFieldData_less_by_offset
{
    inline bool operator() (const MonoClassFieldData& struct1, const MonoClassFieldData& struct2)
    {
        return (struct1.offset < struct2.offset);
    }
};

std::vector<MonoClassFieldData>  MonoClassData::GetFields(ProcessScanner& pscan)
{
    std::vector<MonoClassFieldData> vParentFields;
    // check parent
    char *parentClassName = pscan.readMonoClassName((unsigned int)this->parent);
    if((strlen(parentClassName)>0)&&(strcmp(parentClassName,"System.Object")!=0)){
	// has valid parent
	printf("GetFields: Parent = [%s]\n",parentClassName);
	MonoClassData parentClassData = pscan.readMonoClass((unsigned int)this->parent);
	vParentFields = parentClassData.GetFields(pscan);
    }
    std::vector<MonoClassFieldData> vFields;
    if((this->field.count >0) &&(pscan.isDataAddress((unsigned int)this->fields))){
	for(int i=0;i<this->field.count;i++){
	    MonoClassFieldData field = pscan.readMonoClassField((unsigned int)this->fields + (i*sizeof(MonoClassField)));
	    vFields.push_back(field);
	}
        //std::sort(vFields.begin(), vFields.end(), MonoClassFieldData_less_by_offset());
    }   
    if(vParentFields.size()>0){
	vFields.insert(vFields.end(),vParentFields.begin(),vParentFields.end());
    }
    return vFields;
}

std::vector<MonoClassFieldData> MonoClassData::GetInstanceFields(ProcessScanner& pscan)
{
    std::vector<MonoClassFieldData> vParentFields;
    // check parent
    char *parentClassName = pscan.readMonoClassName((unsigned int)this->parent);
    if((strlen(parentClassName)>0)&&(strcmp(parentClassName,"System.Object")!=0)){
	// has valid parent
	printf("GetInstanceFields: Parent = [%s]\n",parentClassName);
	MonoClassData parentClassData = pscan.readMonoClass((unsigned int)this->parent);
	vParentFields = parentClassData.GetInstanceFields(pscan);
    }
    std::vector<MonoClassFieldData> vFields;
    if((this->field.count >0) &&(pscan.isDataAddress((unsigned int)this->fields))){
	for(int i=0;i<this->field.count;i++){
	    MonoClassFieldData field = pscan.readMonoClassField((unsigned int)this->fields + (i*sizeof(MonoClassField)));
            if((field.typeData.attrs & FIELD_ATTRIBUTE_STATIC)==0){
                //field.show(pscan);
                vFields.push_back(field);
            }
	}
        //std::sort(vFields.begin(), vFields.end(), MonoClassFieldData_less_by_offset());
    }   
    if(vParentFields.size()>0){
	vFields.insert(vFields.end(),vParentFields.begin(),vParentFields.end());
    }
    std::sort(vFields.begin(), vFields.end(), MonoClassFieldData_less_by_offset());
    return vFields;
}

std::string MonoClassData::ToCClass(ProcessScanner& pscan)
{
    char tmp[512];
    std::string toCStringStr;
    std::string showStr;
    std::string ret;
    std::vector<MonoClassFieldData> vFields = GetInstanceFields(pscan);
    std::string thisClassname(pscan.readMonoClassName(thisAddr));
    while(StringReplace(thisClassname,".","_"));
    
    sprintf(tmp,"class %s: MonoObject{\n",thisClassname.c_str());ret += tmp;
    ret += "public:\n";

    sprintf(tmp,"\tstd::string ToString(ProcessScanner& pscan){\n");toCStringStr += tmp;
    toCStringStr += "\t\tchar tmp[1024];\n";
    toCStringStr += "\t\tstd::vector<std::string> vStringList;\n";
    
    sprintf(tmp,"\tvoid Show(ProcessScanner& pscan){\n");showStr += tmp;
    showStr += "\t\tprintf(\"------ Show [%s] ------\\n\",pscan.GetVTableClassName((unsigned int)this->vtable));\n";
    
    //showStr += "\t\tchar tmp[1024];\n";
    
    int fillerCount = 0;
    if(vFields.size()>0){
        int expectOffset = 8;
        for(int i=0;i<vFields.size();i++){
            MonoClassFieldData *f = &vFields[i];
            if(f->offset<expectOffset){
                printf("currect offset is %d <> expect %d\n",f->offset,expectOffset);
                break;
            }
            if(f->offset> expectOffset){
                sprintf(tmp,"\tunsigned char unk%d[%d];\n",fillerCount,f->offset - expectOffset);
                ret += tmp;
                fillerCount++;
		expectOffset = f->offset;
            }
	    char rawName[128];
	    strcpy(rawName,pscan.readCString((unsigned int)f->name));
            // clean fieldname like <isAlwaysCritical>k__BackingField 
	    char *ptr = &rawName[0];
	    while(*ptr){
		if(*ptr == '<') *ptr = '_';
		if(*ptr == '>') *ptr = '_';
		ptr++;
	    }
	    char *name = &rawName[0];
            char *typeName = MonoTypeData::GetTypeName(f->typeData.type);
            if((f->typeData.type == MONO_TYPE_VOID)
                    ||(f->typeData.type == MONO_TYPE_I4)||(f->typeData.type == MONO_TYPE_U4)
                    ||(f->typeData.type == MONO_TYPE_R4)||(f->typeData.type == MONO_TYPE_STRING)
                    ||(f->typeData.type == MONO_TYPE_PTR)||(f->typeData.type == MONO_TYPE_BYREF)
                    ||(f->typeData.type == MONO_TYPE_CLASS)||(f->typeData.type == MONO_TYPE_ARRAY)
                    ||(f->typeData.type == MONO_TYPE_GENERICINST)||(f->typeData.type == MONO_TYPE_SZARRAY)
            ){
		
		if(f->typeData.type == MONO_TYPE_STRING){
		    sprintf(tmp,"\tunsigned int %s; //%d %s\n",name,f->offset,typeName);
		    ret += tmp;
		    
		    sprintf(tmp,"\t\tsprintf(tmp,\"\\\"%%s\\\"\",SaveCString(pscan.readMonoString(this->%s)).c_str());vStringList.push_back(tmp);\n",name);
		    //sprintf(tmp,"\t\tstd::string %s = pscan.readMonoString(this->%s);\n",name,name);
		    toCStringStr += tmp;
		    sprintf(tmp,"\t\tprintf(\"%s=[%%s]\\n\",SaveCString(pscan.readMonoString(this->%s)).c_str());\n",name,name);
		    showStr += tmp;
		}else if(f->typeData.type == MONO_TYPE_R4){
		    sprintf(tmp,"\tfloat %s; //%d %s\n",name,f->offset,typeName);
		    ret += tmp;
		    
		    sprintf(tmp,"\t\tsprintf(tmp,\"%%f\",this->%s);vStringList.push_back(tmp);\n",name);
		    toCStringStr += tmp;
		    
		    sprintf(tmp,"\t\tprintf(\"%s=%%f\\n\",this->%s);\n",name,name);
		    showStr += tmp;
		    
		}else {
		    if((f->typeData.type == MONO_TYPE_CLASS)){
			char *className = pscan.readMonoClassName((unsigned int)f->typeData.data.klass);
			sprintf(tmp,"\tunsigned int %s; //%d %s %s\n",name,f->offset,typeName,className);
		    }else if((f->typeData.type == MONO_TYPE_ARRAY)||(f->typeData.type == MONO_TYPE_SZARRAY)){
			MonoArrayType atype;
			pscan.read((unsigned int)f->typeData.data.array,sizeof(atype),(unsigned int)&atype);
			char *className = pscan.readMonoClassName((unsigned int)atype.eklass);
			sprintf(tmp,"\tunsigned int %s; //%d %s %s\n",name,f->offset,typeName,className);
		    }else if(f->typeData.type == MONO_TYPE_GENERICINST){
			MonoGenericClass gClass;
			pscan.read((unsigned int)f->typeData.data.generic_class,sizeof(gClass),(unsigned int)&gClass);
			char containerClass[128];
			char cacheClass[128];
			strcpy(containerClass,pscan.readMonoClassName((unsigned int)gClass.container_class));
			strcpy(cacheClass,pscan.readMonoClassName((unsigned int)gClass.cached_class));
			sprintf(tmp,"\tunsigned int %s; //%d %s %s \n",name,f->offset,typeName,containerClass);
		    }else{
			sprintf(tmp,"\tunsigned int %s; //%d %s\n",name,f->offset,typeName);
		    }
		    ret += tmp;
		    
		    sprintf(tmp,"\t\tsprintf(tmp,\"%%d\",this->%s);vStringList.push_back(tmp);\n",name);
		    toCStringStr += tmp;
		    
		    if((f->typeData.type == MONO_TYPE_CLASS)||(f->typeData.type == MONO_TYPE_ARRAY)
			    ||(f->typeData.type == MONO_TYPE_SZARRAY)||(f->typeData.type == MONO_TYPE_GENERICINST)
		    ){
			sprintf(tmp,"\t\tprintf(\"%s=%%08X\\n\",this->%s);\n",name,name);
			showStr += tmp;		    
		    }else{
			sprintf(tmp,"\t\tprintf(\"%s=%%d\\n\",this->%s);\n",name,name);
			showStr += tmp;		    
		    }
		}
                expectOffset+=4;
	    }else if((f->typeData.type == MONO_TYPE_VALUETYPE)){
		char *className = pscan.readMonoClassName((unsigned int)f->typeData.data.klass);
		MonoClassData monoClassData = pscan.readMonoClass((unsigned int)f->typeData.data.klass);
		int size = monoClassData.instance_size;
		if(size == 0){
		    // native type assume byte
		    size = 1;
		}else{
		    size -= 8;
		}
		if(size == 1){
		    sprintf(tmp,"\tunsigned char %s; //%d %s size=%d %s\n",name,f->offset,typeName,size,className);
		    ret += tmp;
		    
		    sprintf(tmp,"\t\tsprintf(tmp,\"%%d\",this->%s);vStringList.push_back(tmp);\n",name);
		    toCStringStr += tmp;

		    sprintf(tmp,"\t\tprintf(\"%s=%%d\\n\",this->%s);\n",name,name);
		    showStr += tmp;			    
		}else{
		    if(strcmp("UnityEngine.ReferenceData",className)==0){
			strcpy(className,"long long int");
		    }
		    sprintf(tmp,"\t%s %s; //%d %s size=%d\n",className,name,f->offset,typeName,size);
		    ret += tmp;
		}
		expectOffset+=size;
            }else if((f->typeData.type == MONO_TYPE_CHAR)
                    ||(f->typeData.type == MONO_TYPE_I1)||(f->typeData.type == MONO_TYPE_U1)
                    ||(f->typeData.type == MONO_TYPE_BOOLEAN)
                    
            ){
                sprintf(tmp,"\tunsigned char %s; //%d %s\n",name,f->offset,typeName);
                ret += tmp;
		sprintf(tmp,"\t\tsprintf(tmp,\"%%d\",this->%s);vStringList.push_back(tmp);\n",name);
		toCStringStr += tmp;

		sprintf(tmp,"\t\tprintf(\"%s=%%d\\n\",this->%s);\n",name,name);
		showStr += tmp;		    
		
                expectOffset+=1;
            }else if(
                    (f->typeData.type == MONO_TYPE_I2)||(f->typeData.type == MONO_TYPE_U2)
		    
            ){
                sprintf(tmp,"\tunsigned short %s; //%d %s\n",name,f->offset,typeName);
                ret += tmp;
		sprintf(tmp,"\t\tsprintf(tmp,\"%%d\",this->%s);vStringList.push_back(tmp);\n",name);
		toCStringStr += tmp;
		
		sprintf(tmp,"\t\tprintf(\"%s=%%d\\n\",this->%s);\n",name,name);
		showStr += tmp;		    
		
                expectOffset+=2;
	    }else if((f->typeData.type == MONO_TYPE_I8)||(f->typeData.type == MONO_TYPE_U8)||(f->typeData.type == MONO_TYPE_R8)){
		if((f->typeData.type == MONO_TYPE_R8)){
		    sprintf(tmp,"\tdouble %s; //%d %s\n",name,f->offset,typeName);
		    ret += tmp;
		    sprintf(tmp,"\t\tsprintf(tmp,\"%%f\",this->%s);vStringList.push_back(tmp);\n",name);
		    toCStringStr += tmp;

		    sprintf(tmp,"\t\tprintf(\"%s=%%f\\n\",this->%s);\n",name,name);
		    showStr += tmp;		    
		    
		}else{
		    sprintf(tmp,"\tlong long int %s; //%d %s\n",name,f->offset,typeName);
		    ret += tmp;

		    sprintf(tmp,"\t\tsprintf(tmp,\"%%lld\",this->%s);vStringList.push_back(tmp);\n",name);
		    toCStringStr += tmp;

		    sprintf(tmp,"\t\tprintf(\"%s=%%lld\\n\",this->%s);\n",name,name);
		    showStr += tmp;		    
		    
		}
		
                expectOffset+=8;
		
            }else {
                sprintf(tmp,"//unknown %s %s %02X; //%d\n",name,typeName,f->typeData.type,f->offset);
                ret += tmp;
                break;
            }
            //vFields[i].show(pscan);
            
        }
    }
    sprintf(tmp,"\t\tstd::string ret;\n");toCStringStr += tmp;
    sprintf(tmp,"\t\tret += \"{\";\n");toCStringStr += tmp;
    sprintf(tmp,"\t\tret += ConcatStrings(vStringList,\",\");\n");toCStringStr += tmp;
    sprintf(tmp,"\t\tret += \"},\";\n");toCStringStr += tmp;
    sprintf(tmp,"\t\treturn ret;\n");toCStringStr += tmp;
    toCStringStr += "\t}\n";
    
    showStr += "\t}\n";

    ret += toCStringStr;
    ret += showStr;    
    ret += "};\n";
    
    printf("%s\n",ret.c_str());
    return ret;
}



void MonoClassFieldData::init(ProcessScanner& pscan)
{
    typeData = pscan.readMonoType((unsigned int)this->type);
}

void MonoClassFieldData::show(ProcessScanner& pscan)
{
    char attrName[64];
    attrName[0] = 0;
    if(typeData.attrs & FIELD_ATTRIBUTE_STATIC){
	strcat(attrName,"Static ");
    }
    if(typeData.attrs & FIELD_ATTRIBUTE_LITERAL){
	strcat(attrName,"Literal ");
    }
    printf("%sField: 0x%08X [%s] offset=%d [%s] %04X\n",
	    attrName,
	    this->thisAddr,
	    pscan.readCString((unsigned int)this->name),
	    this->offset,
	    MonoTypeData::GetTypeName(typeData.type),
	    typeData.attrs
    );
}

char *MonoTypeData::GetTypeName(int typeEnum)
{
    static char *names[] = {
	"End","Void","Bool","Char","Byte","UByte","Short","UShort","Int","UInt","Int64","UIn64",
	"float","doube","String","PTR","REF","VALUE","Class","Var","Array","List","TypeByRef",
	"","I","U","","FNPTR","Object","SZARRAY","MVAR"
    };
    if(typeEnum < 0x1E) return names[typeEnum];
    static char out[64];
    sprintf(out,"Type%2X",typeEnum);
    return(&out[0]);
}

void MonoTypeData::show(ProcessScanner& pscan)
{
    printf("Type: %s\n",GetTypeName(this->type));
}


unsigned int MonoVTableData::GetStaticInt(ProcessScanner &pscan,char *varName)
{
    if(!classData.isInit()){
	classData = pscan.readMonoClass((unsigned int)this->klass);
    }
    if(classData.isInit()){
	MonoClassFieldData field = classData.GetField(pscan,varName);
	if(field.isInit()){
	    int offset = field.offset;
	    printf("GetStaticInt %s offset=%d\n",varName,offset);
	    if(field.typeData.attrs & FIELD_ATTRIBUTE_STATIC){
		// static
		unsigned int dataAddr = (unsigned int)this->data + offset;
		printf("GetStaticInt %s addr=0x%08X\n",varName,dataAddr);
		unsigned int ret;
		pscan.read(dataAddr,sizeof(ret),(unsigned int)&ret);
		printf("GetStaticInt %s value=%d\n",varName,ret);
		return ret;
	    }
	}else{
	    printf("ERROR: GetStaticInt fields [%s] not found\n",varName);
	}
    }else{
	printf("ERROR: GetStaticInt classData %08X not found\n",(unsigned int)this->klass);
    }
    return 0;
}

void MonoVTableData::show(ProcessScanner& pscan)
{
    printf("---VTable----\n");
    printf("thisAddr: 0x%08X\n",this->thisAddr);
    printf("class: 0x%08X [%s]\n",(unsigned int)this->klass,pscan.readMonoClassName((unsigned int)this->klass));
    printf("gc_descr: 0x%08X\n",(unsigned int)this->gc_descr);
    printf("domain: 0x%08X\n",(unsigned int)this->domain);
    printf("data: 0x%08X\n",(unsigned int)this->data);
    printf("type: 0x%08X\n",(unsigned int)this->type);
    printf("interface_bitmap: 0x%02X\n",(unsigned int)this->interface_bitmap);
    printf("max_interface_id: 0x%04X\n",(unsigned int)this->max_interface_id);
    printf("rank: 0x%02X\n",(unsigned int)this->rank);	
    printf("remote: %d\n",this->remote);	
    printf("initialized: %d\n",this->initialized);	
    printf("init_failed: %d\n",this->init_failed);	
    printf("runtime_generic_context: 0x%08X\n",(unsigned int)this->runtime_generic_context);
    if(!classData.isInit()){
	classData = pscan.readMonoClass((unsigned int)this->klass);
    }
    std::vector<MonoClassFieldData> vFields =  classData.GetFields(pscan);
    for(int i=0;i<vFields.size();i++){
	MonoClassFieldData *f = &vFields[i];
	//f->show(pscan);
	std::string fieldName(pscan.readCString((unsigned int)f->name));
	if(f->typeData.attrs & FIELD_ATTRIBUTE_STATIC){
	    unsigned int dataAddr = (unsigned int)this->data +f->offset;
	    if(f->typeData.type == MONO_TYPE_STRING){
		unsigned int dataValue = pscan.ReadInt(dataAddr);
		printf("Static: %s=0x%08X [%s] \n",fieldName.c_str(),dataValue,pscan.readMonoString(dataValue));
	    }else if((f->typeData.type == MONO_TYPE_I1)||(f->typeData.type == MONO_TYPE_U1)){
		printf("Static: %s=%d\n",fieldName.c_str(),pscan.GetStaticClassField<unsigned char>(*this,(char *)fieldName.c_str()));
	    }else if((f->typeData.type == MONO_TYPE_I2)||(f->typeData.type == MONO_TYPE_U2)){
		printf("Static: %s=%d\n",fieldName.c_str(),pscan.GetStaticClassField<unsigned short>(*this,(char *)fieldName.c_str()));
	    }else if((f->typeData.type == MONO_TYPE_I8)||(f->typeData.type == MONO_TYPE_U8)){
		printf("Static: %s=%lld\n",fieldName.c_str(),pscan.GetStaticClassField<long long int>(*this,(char *)fieldName.c_str()));
	    }else if(f->typeData.type == MONO_TYPE_R4){
		printf("Static: %s=%f\n",fieldName.c_str(),pscan.GetStaticClassField<float>(*this,(char *)fieldName.c_str()));
	    }else if(f->typeData.type == MONO_TYPE_R8){
		printf("Static: %s=%f\n",fieldName.c_str(),pscan.GetStaticClassField<double>(*this,(char *)fieldName.c_str()));
	    }else{
		printf("Static: %s=0x%08X\n",fieldName.c_str(),pscan.GetStaticClassField<unsigned int>(*this,(char *)fieldName.c_str()));
	    }
	}
    }

}

void MonoMethodData::show(ProcessScanner& pscan)
{
    printf("Method: 0x%08X [%s] slot=%d\n",this->thisAddr,pscan.readCString((unsigned int)this->name),this->slot);
}

char *MonoObjectData::GetName(ProcessScanner& pscan)
{
    static char out[128];
    unsigned int classAddr = pscan.ReadInt((unsigned int)this->vtable);
    char *str = pscan.readMonoClassName(classAddr);
    out[0]=0;
    strcpy(out,str);
    return(&out[0]);
}

void MonoObjectData::show(ProcessScanner& pscan)
{
    printf("Object: 0x%08X [%s]\n",this->thisAddr,GetName(pscan));
}

MonoVTableData MonoObjectData::GetVTable(ProcessScanner& pscan)
{
    unsigned int vTableAddr = (unsigned int)this->vtable;
    MonoVTableData ret = pscan.readMonoVTable(vTableAddr);
    return ret;
}