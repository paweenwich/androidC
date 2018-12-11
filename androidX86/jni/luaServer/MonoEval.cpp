
/* 
 * File:   MonoEval.cpp
 * Author: kwang
 * 
 * Created on August 16, 2016, 4:26 PM
 */
#include <stdio.h>
#include <sys/ptrace.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <assert.h>
#include <string.h>
#include <dlfcn.h>
#include <stdarg.h>
#include <string>
#include <vector>
#include <fstream>
#include <pthread.h>
#include "../util/logger.h"
#include "../util/payload.hpp"
#include "MonoEval.hpp"

extern Logger *serverLogger;

RunTimeInvokeQueue *runTimeInvokeQueue=NULL;

#define  LOGD(...)  serverLogger->printf(__VA_ARGS__)
#define  LOGE(...)  serverLogger->printf(__VA_ARGS__)
#define	 LOGHEX(x,y)	serverLogger->logHex((x),(y));


MonoEval::MonoEval()
{
    // make sure we load mono
    MonoLoad();
    GetAllAssembly();
}

// Support Full name separate bye .
void MonoEval::eval(char *str)
{
    
}

void mono_assembly_foreach_GetAllAssembly(unsigned int assembly,void *userData)
{
    MonoEval *me = (MonoEval *)userData;
    me->vAssembly.push_back((MonoAssembly *)assembly);
    LOGD("GetAllAssembly: add %08X",assembly);
}

void MonoEval::GetAllAssembly()
{
    vAssembly.clear();
    mono_assembly_foreach((unsigned int)mono_assembly_foreach_GetAllAssembly,this);
    LOGD("GetAllAssembly: %d",vAssembly.size());
}

void MonoEval::attatch()
{
    mono_thread_attach(mono_get_root_domain());
}


MonoClass *  MonoEval::GetClassFromName(char *klassNameSpace,char *klassName)
{
    attatch();
    LOGD("GetClassFromName %d",vAssembly.size());
    for(int i=0;i<vAssembly.size();i++){
	MonoAssembly *assembly = vAssembly[i];
	LOGD("GetClassFromName assembly %08X",assembly);
	MonoImage *image = mono_assembly_get_image(assembly);
	if(image!=NULL){
	    LOGD("image %08X",image);
	    MonoClass *klass = mono_class_from_name(image,klassNameSpace,klassName);
	    if(klass!=NULL){
		LOGD("class %08X",klass);
		return klass;
	    }else{
		//LOGE("GetClassFromName class not found");
	    }
	}else{
	    //LOGE("GetClassFromName image not found");
	}
    }
    return NULL;
}

MonoClassField * MonoEval::GetFieldFromName(MonoClass *klass,char *name)
{
    return mono_class_get_field_from_name(klass,name);
    /*
    //LOGD("GetFieldFromName=%08X %s",(unsigned int)klass,name);
    MonoClassField *fieldInfo;
    unsigned int iter = 0;
    while((fieldInfo = mono_class_get_fields(klass,&iter))!=NULL){
	//LOGD("fieldInfo=[%08X]",(unsigned int)fieldInfo);
	char *fieldName = mono_field_get_name(fieldInfo);
	//LOGD("fieldInfo=%08X %s",(unsigned int)fieldInfo,fieldName);
	if(strcmp(fieldName,name)==0){
	    //LOGD("found");
	    return fieldInfo;
	}
    }
    return NULL;
    */
}

#define GET_VTABLE_FIELFINFO(k,f)	\
    MonoDomain *domain = mono_get_root_domain();\
    mono_thread_attach(domain);\
    MonoVTable *vtable = mono_class_vtable(domain,(k)); \
    MonoClassField *fieldInfo = GetFieldFromName((k),(f)); \
    LOGD("domain=%08X vtable=%08X fieldInfo=%08X",(unsigned int)domain,(unsigned int)vtable,(unsigned int)fieldInfo); 

#define GET_VTABLE_PROPERTY(k,f)	\
    MonoDomain *domain = mono_get_root_domain();\
    mono_thread_attach(domain);\
    MonoVTable *vtable = mono_class_vtable(domain,(k)); \
    MonoProperty *property = mono_class_get_property_from_name((k),(f)); \
    LOGD("domain=%08X vtable=%08X property=%08X",(unsigned int)domain,(unsigned int)vtable,(unsigned int)property); 



void MonoEval::SetFieldBool(MonoClass *klass,MonoObject *obj,char *fieldName,bool bValue)
{
    GET_VTABLE_FIELFINFO(klass,fieldName);
    if(fieldInfo!=NULL){
	unsigned int value = bValue;	
	if(obj==NULL){
	    mono_field_static_set_value(vtable,fieldInfo,&value);
	}else{
	    mono_field_set_value(obj,fieldInfo,&value);
	}
    }else{
	LOGD("Field %s not found",fieldName);
    }
}

void MonoEval::GetField(MonoClass *klass,MonoObject *obj,char *fieldName,bool &bValue)
{
    GET_VTABLE_FIELFINFO(klass,fieldName);
    if(fieldInfo!=NULL){
	unsigned int value;
	if(obj==NULL){
	    mono_field_static_get_value(vtable,fieldInfo,&value);
	}else{
	    mono_field_get_value(obj,fieldInfo,&value);
	}
        bValue = value;
    }else{
	LOGD("Field %s not found",fieldName);
    }

}


void MonoEval::SetFieldInt(MonoClass *klass,MonoObject *obj,char *fieldName,int iValue)
{
    LOGD("SetField %08X %08X %s %08X",(unsigned int)klass,(unsigned int)obj,fieldName,iValue);
    GET_VTABLE_FIELFINFO(klass,fieldName);
    if(fieldInfo!=NULL){
	unsigned int value = iValue;	
	if(obj==NULL){
	    LOGD("SetField static %s %08X",fieldName,value);
	    mono_field_static_set_value(vtable,fieldInfo,&value);
	}else{
	    LOGD("SetField instance %s %08X %08X",fieldName,(unsigned int)obj,value);
	    mono_field_set_value(obj,fieldInfo,&value);
	}
    }else{
	LOGD("Field %s not found",fieldName);
    }
}

void MonoEval::GetField(MonoClass *klass,MonoObject *obj,char *fieldName,int &iValue)
{
    //LOGD("GetField %08X %08X %s",(unsigned int)klass,(unsigned int)obj,fieldName);
    GET_VTABLE_FIELFINFO(klass,fieldName);
    if(fieldInfo!=NULL){
	unsigned int value;	
	if(obj==NULL){
	    //LOGD("GetField static %s",fieldName);
	    mono_field_static_get_value(vtable,fieldInfo,&value);
	}else{
	    //LOGD("GetField instance %s %08X",fieldName,(unsigned int)obj);
	    mono_field_get_value(obj,fieldInfo,&value);
	}
	iValue = value;	
    }else{
	LOGD("Field %s not found",fieldName);
    }

}

void MonoEval::SetFieldString(MonoClass *klass,MonoObject *obj,char *fieldName,char *str)
{
    GET_VTABLE_FIELFINFO(klass,fieldName);
    if(fieldInfo!=NULL){
        MonoString *mstr = mono_string_new(domain,str);	
	if(obj==NULL){
	    mono_field_static_set_value(vtable,fieldInfo,mstr);
	}else{
	    mono_field_set_value(obj,fieldInfo,mstr);
	}
    }else{
	LOGD("Field %s not found",fieldName);
    }
}

void MonoEval::GetField(MonoClass *klass,MonoObject *obj,char *fieldName,char *str)
{
    GET_VTABLE_FIELFINFO(klass,fieldName);
    if(fieldInfo!=NULL){
	unsigned int value;	
	if(obj==NULL){
	    mono_field_static_get_value(vtable,fieldInfo,&value);
	}else{
	    mono_field_get_value(obj,fieldInfo,&value);
	}
	MonoString *ms = (MonoString *)value;
	//LOGD("len=%d %s",ms->length,mono_string_to_utf8(ms));
	strcpy(str,mono_string_to_utf8(ms));
    }else{
	LOGD("Field %s not found",fieldName);
    }

}

bool MonoEval::GetFieldAsBool(MonoClass *klass,MonoObject *obj,char *fieldName)
{
    bool ret = false;;
    GetField(klass,obj,fieldName,ret);
    return ret;
}

int MonoEval::GetFieldAsInt(MonoClass *klass,MonoObject *obj,char *fieldName)
{
    int ret = 0;
    GetField(klass,obj,fieldName,ret);
    return ret;
}
char* MonoEval::GetFieldAsString(MonoClass *klass,MonoObject *obj,char *fieldName)
{
    static char ret[1024] = {0};
    ret[0] = 0;
    GetField(klass,obj,fieldName,&ret[0]);
    return &ret[0];
}

int MonoEval::GetPropertyAsInt(MonoClass *klass,MonoObject *obj,char *fieldName)
{
    int ret = 0;
    GET_VTABLE_PROPERTY(klass,fieldName);
    if(property!=NULL){
	MonoObject *obj = mono_property_get_value(property, obj,NULL,NULL);
	ret = (unsigned int)obj;
    }else{
	LOGD("Property %s not found",fieldName);
    }    
    return ret;
}

char *MonoEval::GetPropertyAsString(MonoClass *klass,MonoObject *obj,char *fieldName)
{
    static char ret[1024] = {0};
    ret[0] = 0;
    GET_VTABLE_PROPERTY(klass,fieldName);
    if(property!=NULL){
	MonoString *ms = (MonoString *)mono_property_get_value(property, obj,NULL,NULL);
	strcpy(&ret[0],mono_string_to_utf8(ms));
    }else{
	LOGD("Property %s not found",fieldName);
	
    }
    return &ret[0];
}
bool MonoEval::GetPropertyAsBool(MonoClass *klass,MonoObject *obj,char *fieldName)
{
    bool ret = false;
    GET_VTABLE_PROPERTY(klass,fieldName);
    if(property!=NULL){
	MonoObject *obj = mono_property_get_value(property, obj,NULL,NULL);
	ret = (bool)obj;
    }else{
	LOGD("Property %s not found",fieldName);
    }    
    return ret;    
}

void MonoEval::SetProperty(MonoClass *klass,MonoObject *obj,char *fieldName,int value)
{
    GET_VTABLE_PROPERTY(klass,fieldName);
    if(property!=NULL){
	mono_property_set_value(property, obj,(void **)&value,NULL);
    }else{
	LOGD("Property %s not found",fieldName);
    }    
}

void MonoEval::SetPropertyString(MonoClass *klass,MonoObject *obj,char *fieldName,char *str)
{
    GET_VTABLE_PROPERTY(klass,fieldName);
    if(property!=NULL){
	MonoString *mstr = mono_string_new(domain,str);	
	mono_property_set_value(property, obj,(void **)mstr,NULL);
    }else{
	LOGD("Property %s not found",fieldName);
    }    
}

MonoObject* MonoEval::IntToMonoObject(int x)
{
    //LOGD("IntToMonoObject %08X",x);
    return ((MonoObject*)x);
}

void MonoEval::InvokeStatic(char *klassNameSpace,char *klassName,const char* methodName,char *param,bool flgQueue)
{
    attatch();
    LOGD("InvokeStatic: %s.%s.%s %08X",klassNameSpace,klassName,methodName,param);
    MonoClass *monoclass = GetClassFromName(klassNameSpace,klassName);
    if(monoclass!=NULL){
	LOGD("InvokeStatic: monoclass %08X",(unsigned int) monoclass);
        int numParam = 0;
        if(param!=NULL){
            numParam = 1;
        }
	MonoMethod *method = mono_class_get_method_from_name(monoclass,methodName,numParam);
	if(method!=NULL){
            static void *args[1];
            //unsigned int parameter = 0;
            args[0] = NULL;
            if(param!=NULL){
                MonoString *mstr = mono_string_new(mono_get_root_domain(),param);
                args[0] = (void *)mstr;
            }
	    if(flgQueue){
		RunTimeInvokeData data;
		data.method = method;
		data.obj = NULL;
                data.exec = 0;
                if(param!=NULL){
                    data.exec = (unsigned int)args;
                }
		data.params = 0;
		runTimeInvokeQueue->add(data);
		LOGD("InvokeStatic: queue add %d",runTimeInvokeQueue->size());    
	    }else{
                unsigned int parameter = 0;
                if(param!=NULL){
                    parameter = (unsigned int)args;
                }
		LOGD("InvokeStatic: myMonoMethod %08X %08X",(unsigned int) method,parameter);
		mono_runtime_invoke(method,0,parameter,0);
		LOGD("InvokeStatic: invoke done");    
	    }
	}else{
	    LOGE("InvokeStatic: %s.%s.%s not found",klassNameSpace,klassName,methodName);    
	}
    }else{
	LOGE("InvokeStatic: %s.%s not found",klassNameSpace,klassName);    
    }
}



RunTimeInvokeQueue::RunTimeInvokeQueue(){
	MutexCreate(&mutex);
}
void RunTimeInvokeQueue::add(RunTimeInvokeData data){
    MutexLock(&mutex);
    vQueue.push_back(data);
    MutexUnlock(&mutex);
}


RunTimeInvokeData RunTimeInvokeQueue::pop()
{
    RunTimeInvokeData ret;
    MutexLock(&mutex);
    if(vQueue.size()>0){
	ret = vQueue[0];
	vQueue.erase(vQueue.begin());
    }
    MutexUnlock(&mutex);
    return ret;
}

int RunTimeInvokeQueue::size()
{
    return vQueue.size();
}

