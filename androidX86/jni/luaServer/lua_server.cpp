/*
** Lua binding: lua_server
*/

#include "tolua.h"

#ifndef __cplusplus
#include <stdlib.h>
#endif
#ifdef __cplusplus
 extern "C" int tolua_bnd_takeownership (lua_State* L); // from tolua_map.c
#else
 int tolua_bnd_takeownership (lua_State* L); /* from tolua_map.c */
#endif
#include <string.h>

/* Exported function */
TOLUA_API int tolua_lua_server_open (lua_State* tolua_S);
LUALIB_API int luaopen_lua_server (lua_State* tolua_S);

#include <unistd.h>
//#include "../util/logger.h"
#include "../util/AndroidLogger.h"
#include "MonoHooker.hpp"
#include "MonoEval.hpp"
extern Logger *serverLogger;
MonoEval *monoEval;
bool flgLogMonoRuntimeInvoke;
bool flgLoadAssemblySuccess;

/* function to release collected object via destructor */
#ifdef __cplusplus

static int tolua_collect_RunTimeInvokeData (lua_State* tolua_S)
{
 RunTimeInvokeData* self = (RunTimeInvokeData*) tolua_tousertype(tolua_S,1,0);
 tolua_release(tolua_S,self);
 delete self;
 return 0;
}
#endif


/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"MonoProperty");
 tolua_usertype(tolua_S,"RunTimeInvokeQueue");
 tolua_usertype(tolua_S,"MonoMethod");
 tolua_usertype(tolua_S,"Logger");
 tolua_usertype(tolua_S,"MonoDomain");
 tolua_usertype(tolua_S,"MonoImage");
 tolua_usertype(tolua_S,"uint32_t");
 tolua_usertype(tolua_S,"MonoAssemblyName");
 tolua_usertype(tolua_S,"MonoVTable");
 tolua_usertype(tolua_S,"MonoAssembly");
 tolua_usertype(tolua_S,"MonoClassField");
 tolua_usertype(tolua_S,"Mutex");
 tolua_usertype(tolua_S,"MonoObject");
 tolua_usertype(tolua_S,"MonoString");
 tolua_usertype(tolua_S,"MonoThreadsSync");
 tolua_usertype(tolua_S,"MonoEval");
 tolua_usertype(tolua_S,"MonoClass");
 tolua_usertype(tolua_S,"RunTimeInvokeData");
}

/* get function: vtable of class  MonoObject */
static int tolua_get_MonoObject_MonoObject_vtable_ptr(lua_State* tolua_S)
{
  MonoObject* self = (MonoObject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'vtable'",NULL);
#endif
 tolua_pushusertype(tolua_S,(void*)self->vtable,"MonoVTable");
 return 1;
}

/* set function: vtable of class  MonoObject */
static int tolua_set_MonoObject_MonoObject_vtable_ptr(lua_State* tolua_S)
{
  MonoObject* self = (MonoObject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'vtable'",NULL);
 if (!tolua_isusertype(tolua_S,2,"MonoVTable",0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->vtable = ((MonoVTable*)  tolua_tousertype(tolua_S,2,0));
 return 0;
}

/* get function: synchronisation of class  MonoObject */
static int tolua_get_MonoObject_MonoObject_synchronisation_ptr(lua_State* tolua_S)
{
  MonoObject* self = (MonoObject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'synchronisation'",NULL);
#endif
 tolua_pushusertype(tolua_S,(void*)self->synchronisation,"MonoThreadsSync");
 return 1;
}

/* set function: synchronisation of class  MonoObject */
static int tolua_set_MonoObject_MonoObject_synchronisation_ptr(lua_State* tolua_S)
{
  MonoObject* self = (MonoObject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'synchronisation'",NULL);
 if (!tolua_isusertype(tolua_S,2,"MonoThreadsSync",0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->synchronisation = ((MonoThreadsSync*)  tolua_tousertype(tolua_S,2,0));
 return 0;
}

/* get function: object of class  MonoString */
static int tolua_get_MonoString_MonoString_object(lua_State* tolua_S)
{
  MonoString* self = (MonoString*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'object'",NULL);
#endif
 tolua_pushusertype(tolua_S,(void*)&self->object,"MonoObject");
 return 1;
}

/* set function: object of class  MonoString */
static int tolua_set_MonoString_MonoString_object(lua_State* tolua_S)
{
  MonoString* self = (MonoString*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'object'",NULL);
 if (!tolua_isusertype(tolua_S,2,"MonoObject",0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->object = *((MonoObject*)  tolua_tousertype(tolua_S,2,0));
 return 0;
}

/* get function: length of class  MonoString */
static int tolua_get_MonoString_MonoString_length(lua_State* tolua_S)
{
  MonoString* self = (MonoString*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'length'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->length);
 return 1;
}

/* set function: length of class  MonoString */
static int tolua_set_MonoString_MonoString_length(lua_State* tolua_S)
{
  MonoString* self = (MonoString*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'length'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->length = ((long)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: chars of class  MonoString */
static int tolua_get_lua_server_MonoString_chars(lua_State* tolua_S)
{
 int tolua_index;
  MonoString* self;
 lua_pushstring(tolua_S,".self");
 lua_rawget(tolua_S,1);
 self = (MonoString*)  lua_touserdata(tolua_S,-1);
#ifndef TOLUA_RELEASE
 {
 tolua_Error tolua_err;
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in array indexing.",&tolua_err);
 }
#endif
 tolua_index = (int)tolua_tonumber(tolua_S,2,0)-1;
#ifndef TOLUA_RELEASE
 if (tolua_index<0 || tolua_index>=0)
 tolua_error(tolua_S,"array indexing out of range.",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->chars[tolua_index]);
 return 1;
}

/* set function: chars of class  MonoString */
static int tolua_set_lua_server_MonoString_chars(lua_State* tolua_S)
{
 int tolua_index;
  MonoString* self;
 lua_pushstring(tolua_S,".self");
 lua_rawget(tolua_S,1);
 self = (MonoString*)  lua_touserdata(tolua_S,-1);
#ifndef TOLUA_RELEASE
 {
 tolua_Error tolua_err;
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in array indexing.",&tolua_err);
 }
#endif
 tolua_index = (int)tolua_tonumber(tolua_S,2,0)-1;
#ifndef TOLUA_RELEASE
 if (tolua_index<0 || tolua_index>=0)
 tolua_error(tolua_S,"array indexing out of range.",NULL);
#endif
  self->chars[tolua_index] = ((short)  tolua_tonumber(tolua_S,3,0));
 return 0;
}

/* function: mono_class_get_name */
static int tolua_lua_server_mono_class_get_name00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isnumber(tolua_S,1,0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  unsigned int monoClass = ((unsigned int)  tolua_tonumber(tolua_S,1,0));
 {
  char* tolua_ret = (char*)  mono_class_get_name(monoClass);
 tolua_pushstring(tolua_S,(const char*)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'mono_class_get_name'.",&tolua_err);
 return 0;
#endif
}

/* function: mono_class_get_namespace */
static int tolua_lua_server_mono_class_get_namespace00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isnumber(tolua_S,1,0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  unsigned int monoClass = ((unsigned int)  tolua_tonumber(tolua_S,1,0));
 {
  char* tolua_ret = (char*)  mono_class_get_namespace(monoClass);
 tolua_pushstring(tolua_S,(const char*)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'mono_class_get_namespace'.",&tolua_err);
 return 0;
#endif
}

/* function: mono_method_get_name */
static int tolua_lua_server_mono_method_get_name00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isnumber(tolua_S,1,0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  unsigned int monoMethod = ((unsigned int)  tolua_tonumber(tolua_S,1,0));
 {
  char* tolua_ret = (char*)  mono_method_get_name(monoMethod);
 tolua_pushstring(tolua_S,(const char*)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'mono_method_get_name'.",&tolua_err);
 return 0;
#endif
}

/* function: mono_method_get_class */
static int tolua_lua_server_mono_method_get_class00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isnumber(tolua_S,1,0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  unsigned int monoMethod = ((unsigned int)  tolua_tonumber(tolua_S,1,0));
 {
  unsigned int tolua_ret = (unsigned int)  mono_method_get_class(monoMethod);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'mono_method_get_class'.",&tolua_err);
 return 0;
#endif
}

/* function: mono_domain_get */
static int tolua_lua_server_mono_domain_get00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isnoobj(tolua_S,1,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
 {
  MonoDomain* tolua_ret = (MonoDomain*)  mono_domain_get();
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"MonoDomain");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'mono_domain_get'.",&tolua_err);
 return 0;
#endif
}

/* function: mono_image_open_from_data */
static int tolua_lua_server_mono_image_open_from_data00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isstring(tolua_S,1,0,&tolua_err) || 
 !tolua_isnumber(tolua_S,2,0,&tolua_err) || 
 !tolua_isnumber(tolua_S,3,0,&tolua_err) || 
 !tolua_isnumber(tolua_S,4,0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  unsigned char* data = ((unsigned char*)  tolua_tostring(tolua_S,1,0));
  int size = ((int)  tolua_tonumber(tolua_S,2,0));
  int num = ((int)  tolua_tonumber(tolua_S,3,0));
  int status = ((int)  tolua_tonumber(tolua_S,4,0));
 {
  MonoImage* tolua_ret = (MonoImage*)  mono_image_open_from_data(data,size,num,&status);
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"MonoImage");
 tolua_pushnumber(tolua_S,(lua_Number)status);
 }
 }
 return 2;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'mono_image_open_from_data'.",&tolua_err);
 return 0;
#endif
}

/* function: mono_domain_assembly_open */
static int tolua_lua_server_mono_domain_assembly_open00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"MonoDomain",0,&tolua_err) || 
 !tolua_isstring(tolua_S,2,0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  MonoDomain* domain = ((MonoDomain*)  tolua_tousertype(tolua_S,1,0));
  const char* assemblyName = ((const char*)  tolua_tostring(tolua_S,2,0));
 {
  MonoAssembly* tolua_ret = (MonoAssembly*)  mono_domain_assembly_open(domain,assemblyName);
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"MonoAssembly");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'mono_domain_assembly_open'.",&tolua_err);
 return 0;
#endif
}

/* function: mono_get_root_domain */
static int tolua_lua_server_mono_get_root_domain00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isnoobj(tolua_S,1,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
 {
  MonoDomain* tolua_ret = (MonoDomain*)  mono_get_root_domain();
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"MonoDomain");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'mono_get_root_domain'.",&tolua_err);
 return 0;
#endif
}

/* function: mono_thread_attach */
static int tolua_lua_server_mono_thread_attach00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"MonoDomain",0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  MonoDomain* domain = ((MonoDomain*)  tolua_tousertype(tolua_S,1,0));
 {
  mono_thread_attach(domain);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'mono_thread_attach'.",&tolua_err);
 return 0;
#endif
}

/* function: mono_assembly_load_from_full */
static int tolua_lua_server_mono_assembly_load_from_full00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"MonoImage",0,&tolua_err) || 
 !tolua_isstring(tolua_S,2,0,&tolua_err) || 
 !tolua_isnumber(tolua_S,3,0,&tolua_err) || 
 !tolua_isnumber(tolua_S,4,0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  MonoImage* image = ((MonoImage*)  tolua_tousertype(tolua_S,1,0));
  const char* fname = ((const char*)  tolua_tostring(tolua_S,2,0));
  int status = ((int)  tolua_tonumber(tolua_S,3,0));
  int readonly = ((int)  tolua_tonumber(tolua_S,4,0));
 {
  MonoAssembly* tolua_ret = (MonoAssembly*)  mono_assembly_load_from_full(image,fname,&status,readonly);
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"MonoAssembly");
 tolua_pushnumber(tolua_S,(lua_Number)status);
 }
 }
 return 2;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'mono_assembly_load_from_full'.",&tolua_err);
 return 0;
#endif
}

/* function: mono_assembly_get_image */
static int tolua_lua_server_mono_assembly_get_image00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"MonoAssembly",0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  MonoAssembly* assembly = ((MonoAssembly*)  tolua_tousertype(tolua_S,1,0));
 {
  MonoImage* tolua_ret = (MonoImage*)  mono_assembly_get_image(assembly);
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"MonoImage");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'mono_assembly_get_image'.",&tolua_err);
 return 0;
#endif
}

/* function: mono_class_from_name */
static int tolua_lua_server_mono_class_from_name00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"MonoImage",0,&tolua_err) || 
 !tolua_isstring(tolua_S,2,0,&tolua_err) || 
 !tolua_isstring(tolua_S,3,0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  MonoImage* image = ((MonoImage*)  tolua_tousertype(tolua_S,1,0));
  const char* name_space = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* name = ((const char*)  tolua_tostring(tolua_S,3,0));
 {
  MonoClass* tolua_ret = (MonoClass*)  mono_class_from_name(image,name_space,name);
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"MonoClass");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'mono_class_from_name'.",&tolua_err);
 return 0;
#endif
}

/* function: mono_class_get_method_from_name */
static int tolua_lua_server_mono_class_get_method_from_name00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"MonoClass",0,&tolua_err) || 
 !tolua_isstring(tolua_S,2,0,&tolua_err) || 
 !tolua_isnumber(tolua_S,3,0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  MonoClass* klass = ((MonoClass*)  tolua_tousertype(tolua_S,1,0));
  const char* name = ((const char*)  tolua_tostring(tolua_S,2,0));
  int param_count = ((int)  tolua_tonumber(tolua_S,3,0));
 {
  MonoMethod* tolua_ret = (MonoMethod*)  mono_class_get_method_from_name(klass,name,param_count);
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"MonoMethod");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'mono_class_get_method_from_name'.",&tolua_err);
 return 0;
#endif
}

/* function: mono_runtime_invoke */
static int tolua_lua_server_mono_runtime_invoke00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"MonoMethod",0,&tolua_err) || 
 !tolua_isusertype(tolua_S,2,"MonoObject",0,&tolua_err) || 
 !tolua_isnumber(tolua_S,3,0,&tolua_err) || 
 !tolua_isnumber(tolua_S,4,0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  MonoMethod* method = ((MonoMethod*)  tolua_tousertype(tolua_S,1,0));
  MonoObject* obj = ((MonoObject*)  tolua_tousertype(tolua_S,2,0));
  unsigned int params = ((unsigned int)  tolua_tonumber(tolua_S,3,0));
  unsigned int exc = ((unsigned int)  tolua_tonumber(tolua_S,4,0));
 {
  void* tolua_ret = (void*)  mono_runtime_invoke(method,obj,params,exc);
 tolua_pushuserdata(tolua_S,(void*)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'mono_runtime_invoke'.",&tolua_err);
 return 0;
#endif
}

/* function: mono_assembly_foreach */
static int tolua_lua_server_mono_assembly_foreach00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isnumber(tolua_S,1,0,&tolua_err) || 
 !tolua_isuserdata(tolua_S,2,0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  unsigned int func = ((unsigned int)  tolua_tonumber(tolua_S,1,0));
  void* user_data = ((void*)  tolua_touserdata(tolua_S,2,0));
 {
  mono_assembly_foreach(func,user_data);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'mono_assembly_foreach'.",&tolua_err);
 return 0;
#endif
}

/* function: mono_assembly_get_name */
static int tolua_lua_server_mono_assembly_get_name00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isnumber(tolua_S,1,0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  unsigned int assembly = ((unsigned int)  tolua_tonumber(tolua_S,1,0));
 {
  MonoAssemblyName* tolua_ret = (MonoAssemblyName*)  mono_assembly_get_name(assembly);
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"MonoAssemblyName");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'mono_assembly_get_name'.",&tolua_err);
 return 0;
#endif
}

/* function: mono_stringify_assembly_name */
static int tolua_lua_server_mono_stringify_assembly_name00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"MonoAssemblyName",0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  MonoAssemblyName* aname = ((MonoAssemblyName*)  tolua_tousertype(tolua_S,1,0));
 {
  char* tolua_ret = (char*)  mono_stringify_assembly_name(aname);
 tolua_pushstring(tolua_S,(const char*)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'mono_stringify_assembly_name'.",&tolua_err);
 return 0;
#endif
}

/* function: mono_image_get_table_rows */
static int tolua_lua_server_mono_image_get_table_rows00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"MonoImage",0,&tolua_err) || 
 !tolua_isnumber(tolua_S,2,0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  MonoImage* image = ((MonoImage*)  tolua_tousertype(tolua_S,1,0));
  int table_id = ((int)  tolua_tonumber(tolua_S,2,0));
 {
  int tolua_ret = (int)  mono_image_get_table_rows(image,table_id);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'mono_image_get_table_rows'.",&tolua_err);
 return 0;
#endif
}

/* function: mono_class_get */
static int tolua_lua_server_mono_class_get00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"MonoImage",0,&tolua_err) || 
 !tolua_isusertype(tolua_S,2,"uint32_t",0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  MonoImage* image = ((MonoImage*)  tolua_tousertype(tolua_S,1,0));
  uint32_t type_token = *((uint32_t*)  tolua_tousertype(tolua_S,2,0));
 {
  MonoClass* tolua_ret = (MonoClass*)  mono_class_get(image,type_token);
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"MonoClass");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'mono_class_get'.",&tolua_err);
 return 0;
#endif
}

/* function: mono_class_get_fields */
static int tolua_lua_server_mono_class_get_fields00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"MonoClass",0,&tolua_err) || 
 !tolua_isnumber(tolua_S,2,0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  MonoClass* klass = ((MonoClass*)  tolua_tousertype(tolua_S,1,0));
  unsigned int iter = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
 {
  MonoClassField* tolua_ret = (MonoClassField*)  mono_class_get_fields(klass,&iter);
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"MonoClassField");
 tolua_pushnumber(tolua_S,(lua_Number)iter);
 }
 }
 return 2;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'mono_class_get_fields'.",&tolua_err);
 return 0;
#endif
}

/* function: mono_field_get_name */
static int tolua_lua_server_mono_field_get_name00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"MonoClassField",0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  MonoClassField* field = ((MonoClassField*)  tolua_tousertype(tolua_S,1,0));
 {
  char* tolua_ret = (char*)  mono_field_get_name(field);
 tolua_pushstring(tolua_S,(const char*)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'mono_field_get_name'.",&tolua_err);
 return 0;
#endif
}

/* function: mono_field_static_set_value */
static int tolua_lua_server_mono_field_static_set_value00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"MonoVTable",0,&tolua_err) || 
 !tolua_isusertype(tolua_S,2,"MonoClassField",0,&tolua_err) || 
 !tolua_isuserdata(tolua_S,3,0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  MonoVTable* vt = ((MonoVTable*)  tolua_tousertype(tolua_S,1,0));
  MonoClassField* field = ((MonoClassField*)  tolua_tousertype(tolua_S,2,0));
  void* value = ((void*)  tolua_touserdata(tolua_S,3,0));
 {
  mono_field_static_set_value(vt,field,value);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'mono_field_static_set_value'.",&tolua_err);
 return 0;
#endif
}

/* function: mono_field_static_get_value */
static int tolua_lua_server_mono_field_static_get_value00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"MonoVTable",0,&tolua_err) || 
 !tolua_isusertype(tolua_S,2,"MonoClassField",0,&tolua_err) || 
 !tolua_isuserdata(tolua_S,3,0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  MonoVTable* vt = ((MonoVTable*)  tolua_tousertype(tolua_S,1,0));
  MonoClassField* field = ((MonoClassField*)  tolua_tousertype(tolua_S,2,0));
  void* value = ((void*)  tolua_touserdata(tolua_S,3,0));
 {
  mono_field_static_get_value(vt,field,value);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'mono_field_static_get_value'.",&tolua_err);
 return 0;
#endif
}

/* function: mono_class_vtable */
static int tolua_lua_server_mono_class_vtable00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"MonoDomain",0,&tolua_err) || 
 !tolua_isusertype(tolua_S,2,"MonoClass",0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  MonoDomain* domain = ((MonoDomain*)  tolua_tousertype(tolua_S,1,0));
  MonoClass* klass = ((MonoClass*)  tolua_tousertype(tolua_S,2,0));
 {
  MonoVTable* tolua_ret = (MonoVTable*)  mono_class_vtable(domain,klass);
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"MonoVTable");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'mono_class_vtable'.",&tolua_err);
 return 0;
#endif
}

/* function: mono_string_new */
static int tolua_lua_server_mono_string_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"MonoDomain",0,&tolua_err) || 
 !tolua_isstring(tolua_S,2,0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  MonoDomain* domain = ((MonoDomain*)  tolua_tousertype(tolua_S,1,0));
  char* str = ((char*)  tolua_tostring(tolua_S,2,0));
 {
  MonoString* tolua_ret = (MonoString*)  mono_string_new(domain,str);
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"MonoString");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'mono_string_new'.",&tolua_err);
 return 0;
#endif
}

/* function: mono_runtime_class_init */
static int tolua_lua_server_mono_runtime_class_init00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"MonoVTable",0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  MonoVTable* vtable = ((MonoVTable*)  tolua_tousertype(tolua_S,1,0));
 {
  mono_runtime_class_init(vtable);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'mono_runtime_class_init'.",&tolua_err);
 return 0;
#endif
}

/* function: mono_string_to_utf8 */
static int tolua_lua_server_mono_string_to_utf800(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"MonoString",0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  MonoString* s = ((MonoString*)  tolua_tousertype(tolua_S,1,0));
 {
  char* tolua_ret = (char*)  mono_string_to_utf8(s);
 tolua_pushstring(tolua_S,(const char*)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'mono_string_to_utf8'.",&tolua_err);
 return 0;
#endif
}

/* function: mono_class_get_field_from_name */
static int tolua_lua_server_mono_class_get_field_from_name00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"MonoClass",0,&tolua_err) || 
 !tolua_isstring(tolua_S,2,0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  MonoClass* klass = ((MonoClass*)  tolua_tousertype(tolua_S,1,0));
  char* name = ((char*)  tolua_tostring(tolua_S,2,0));
 {
  MonoClassField* tolua_ret = (MonoClassField*)  mono_class_get_field_from_name(klass,name);
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"MonoClassField");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'mono_class_get_field_from_name'.",&tolua_err);
 return 0;
#endif
}

/* function: mono_property_get_value */
static int tolua_lua_server_mono_property_get_value00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"MonoProperty",0,&tolua_err) || 
 !tolua_isuserdata(tolua_S,2,0,&tolua_err) || 
 !tolua_isuserdata(tolua_S,3,0,&tolua_err) || 
 !tolua_isusertype(tolua_S,4,"MonoObject",0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  MonoProperty* prop = ((MonoProperty*)  tolua_tousertype(tolua_S,1,0));
  void* obj = ((void*)  tolua_touserdata(tolua_S,2,0));
  void* params = ((void*)  tolua_touserdata(tolua_S,3,0));
  MonoObject* exc = ((MonoObject*)  tolua_tousertype(tolua_S,4,0));
 {
  MonoObject* tolua_ret = (MonoObject*)  mono_property_get_value(prop,obj,&params,&exc);
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"MonoObject");
 tolua_pushuserdata(tolua_S,(void*)params);
 tolua_pushusertype(tolua_S,(void*)exc,"MonoObject");
 }
 }
 return 3;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'mono_property_get_value'.",&tolua_err);
 return 0;
#endif
}

/* function: mono_property_set_value */
static int tolua_lua_server_mono_property_set_value00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"MonoProperty",0,&tolua_err) || 
 !tolua_isuserdata(tolua_S,2,0,&tolua_err) || 
 !tolua_isuserdata(tolua_S,3,0,&tolua_err) || 
 !tolua_isusertype(tolua_S,4,"MonoObject",0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  MonoProperty* prop = ((MonoProperty*)  tolua_tousertype(tolua_S,1,0));
  void* obj = ((void*)  tolua_touserdata(tolua_S,2,0));
  void* params = ((void*)  tolua_touserdata(tolua_S,3,0));
  MonoObject* exc = ((MonoObject*)  tolua_tousertype(tolua_S,4,0));
 {
  mono_property_set_value(prop,obj,&params,&exc);
 tolua_pushuserdata(tolua_S,(void*)params);
 tolua_pushusertype(tolua_S,(void*)exc,"MonoObject");
 }
 }
 return 2;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'mono_property_set_value'.",&tolua_err);
 return 0;
#endif
}

/* function: mono_class_get_property_from_name */
static int tolua_lua_server_mono_class_get_property_from_name00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"MonoClass",0,&tolua_err) || 
 !tolua_isstring(tolua_S,2,0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  MonoClass* klass = ((MonoClass*)  tolua_tousertype(tolua_S,1,0));
  const char* name = ((const char*)  tolua_tostring(tolua_S,2,0));
 {
  MonoProperty* tolua_ret = (MonoProperty*)  mono_class_get_property_from_name(klass,name);
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"MonoProperty");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'mono_class_get_property_from_name'.",&tolua_err);
 return 0;
#endif
}

/* function: mono_class_get_parent */
static int tolua_lua_server_mono_class_get_parent00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"MonoClass",0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  MonoClass* klass = ((MonoClass*)  tolua_tousertype(tolua_S,1,0));
 {
  MonoClass* tolua_ret = (MonoClass*)  mono_class_get_parent(klass);
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"MonoClass");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'mono_class_get_parent'.",&tolua_err);
 return 0;
#endif
}

/* function: mono_field_get_value */
static int tolua_lua_server_mono_field_get_value00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"MonoObject",0,&tolua_err) || 
 !tolua_isusertype(tolua_S,2,"MonoClassField",0,&tolua_err) || 
 !tolua_isuserdata(tolua_S,3,0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  MonoObject* obj = ((MonoObject*)  tolua_tousertype(tolua_S,1,0));
  MonoClassField* field = ((MonoClassField*)  tolua_tousertype(tolua_S,2,0));
  void* value = ((void*)  tolua_touserdata(tolua_S,3,0));
 {
  mono_field_get_value(obj,field,value);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'mono_field_get_value'.",&tolua_err);
 return 0;
#endif
}

/* function: mono_field_set_value */
static int tolua_lua_server_mono_field_set_value00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"MonoObject",0,&tolua_err) || 
 !tolua_isusertype(tolua_S,2,"MonoClassField",0,&tolua_err) || 
 !tolua_isuserdata(tolua_S,3,0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  MonoObject* obj = ((MonoObject*)  tolua_tousertype(tolua_S,1,0));
  MonoClassField* field = ((MonoClassField*)  tolua_tousertype(tolua_S,2,0));
  void* value = ((void*)  tolua_touserdata(tolua_S,3,0));
 {
  mono_field_set_value(obj,field,value);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'mono_field_set_value'.",&tolua_err);
 return 0;
#endif
}

/* function: MonoLoad */
static int tolua_lua_server_MonoLoad00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isnoobj(tolua_S,1,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
 {
  unsigned int tolua_ret = (unsigned int)  MonoLoad();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'MonoLoad'.",&tolua_err);
 return 0;
#endif
}

/* function: BackupTargetAddress */
static int tolua_lua_server_BackupTargetAddress00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isnumber(tolua_S,1,0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  unsigned int targetAddr = ((unsigned int)  tolua_tonumber(tolua_S,1,0));
 {
  unsigned char* tolua_ret = (unsigned char*)  BackupTargetAddress(targetAddr);
 tolua_pushstring(tolua_S,(const char*)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'BackupTargetAddress'.",&tolua_err);
 return 0;
#endif
}

/* function: InjectJumpCode */
static int tolua_lua_server_InjectJumpCode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isnumber(tolua_S,1,0,&tolua_err) || 
 !tolua_isnumber(tolua_S,2,0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  unsigned int targetAddr = ((unsigned int)  tolua_tonumber(tolua_S,1,0));
  int jumpToAddr = ((int)  tolua_tonumber(tolua_S,2,0));
 {
  InjectJumpCode(targetAddr,jumpToAddr);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'InjectJumpCode'.",&tolua_err);
 return 0;
#endif
}

/* function: MonoHook */
static int tolua_lua_server_MonoHook00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isstring(tolua_S,1,0,&tolua_err) || 
 !tolua_isnumber(tolua_S,2,0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  char* monoFunctionName = ((char*)  tolua_tostring(tolua_S,1,0));
  unsigned int monoHookFuncAddr = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
 {
  unsigned int tolua_ret = (unsigned int)  MonoHook(monoFunctionName,monoHookFuncAddr);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'MonoHook'.",&tolua_err);
 return 0;
#endif
}

/* function: MonoLoadAssembly */
static int tolua_lua_server_MonoLoadAssembly00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isstring(tolua_S,1,0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const char* fileName = ((const char*)  tolua_tostring(tolua_S,1,0));
 {
  MonoAssembly* tolua_ret = (MonoAssembly*)  MonoLoadAssembly(fileName);
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"MonoAssembly");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'MonoLoadAssembly'.",&tolua_err);
 return 0;
#endif
}

/* function: MonoDumpImage */
static int tolua_lua_server_MonoDumpImage00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"MonoImage",0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  MonoImage* image = ((MonoImage*)  tolua_tousertype(tolua_S,1,0));
 {
  MonoDumpImage(image);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'MonoDumpImage'.",&tolua_err);
 return 0;
#endif
}

/* function: MonoLoadAndInvokeAssembly */
static int tolua_lua_server_MonoLoadAndInvokeAssembly00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isstring(tolua_S,1,0,&tolua_err) || 
 !tolua_isstring(tolua_S,2,0,&tolua_err) || 
 !tolua_isstring(tolua_S,3,0,&tolua_err) || 
 !tolua_isstring(tolua_S,4,0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const char* fileName = ((const char*)  tolua_tostring(tolua_S,1,0));
  const char* name_space = ((const char*)  tolua_tostring(tolua_S,2,0));
  char* className = ((char*)  tolua_tostring(tolua_S,3,0));
  const char* methodName = ((const char*)  tolua_tostring(tolua_S,4,0));
 {
  MonoLoadAndInvokeAssembly(fileName,name_space,className,methodName);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'MonoLoadAndInvokeAssembly'.",&tolua_err);
 return 0;
#endif
}

/* get function: libmonoHandle */
static int tolua_get_unsigned_libmonoHandle(lua_State* tolua_S)
{
 tolua_pushnumber(tolua_S,(lua_Number)libmonoHandle);
 return 1;
}

/* set function: libmonoHandle */
static int tolua_set_unsigned_libmonoHandle(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  libmonoHandle = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: monoTextSize */
static int tolua_get_unsigned_monoTextSize(lua_State* tolua_S)
{
 tolua_pushnumber(tolua_S,(lua_Number)monoTextSize);
 return 1;
}

/* set function: monoTextSize */
static int tolua_set_unsigned_monoTextSize(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  monoTextSize = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: monoBaseAddr */
static int tolua_get_unsigned_monoBaseAddr(lua_State* tolua_S)
{
 tolua_pushnumber(tolua_S,(lua_Number)monoBaseAddr);
 return 1;
}

/* set function: monoBaseAddr */
static int tolua_set_unsigned_monoBaseAddr(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  monoBaseAddr = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* method: new of class  MonoEval */
static int tolua_lua_server_MonoEval_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertable(tolua_S,1,"MonoEval",0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
 {
  MonoEval* tolua_ret = (MonoEval*)  new MonoEval();
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"MonoEval");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}

/* method: eval of class  MonoEval */
static int tolua_lua_server_MonoEval_eval00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"MonoEval",0,&tolua_err) || 
 !tolua_isstring(tolua_S,2,0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  MonoEval* self = (MonoEval*)  tolua_tousertype(tolua_S,1,0);
  char* str = ((char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'eval'",NULL);
#endif
 {
  self->eval(str);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'eval'.",&tolua_err);
 return 0;
#endif
}

/* method: GetAllAssembly of class  MonoEval */
static int tolua_lua_server_MonoEval_GetAllAssembly00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"MonoEval",0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  MonoEval* self = (MonoEval*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetAllAssembly'",NULL);
#endif
 {
  self->GetAllAssembly();
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetAllAssembly'.",&tolua_err);
 return 0;
#endif
}

/* method: GetClassFromName of class  MonoEval */
static int tolua_lua_server_MonoEval_GetClassFromName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"MonoEval",0,&tolua_err) || 
 !tolua_isstring(tolua_S,2,0,&tolua_err) || 
 !tolua_isstring(tolua_S,3,0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  MonoEval* self = (MonoEval*)  tolua_tousertype(tolua_S,1,0);
  char* klassNameSpace = ((char*)  tolua_tostring(tolua_S,2,0));
  char* klassName = ((char*)  tolua_tostring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetClassFromName'",NULL);
#endif
 {
  MonoClass* tolua_ret = (MonoClass*)  self->GetClassFromName(klassNameSpace,klassName);
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"MonoClass");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetClassFromName'.",&tolua_err);
 return 0;
#endif
}

/* method: GetFieldFromName of class  MonoEval */
static int tolua_lua_server_MonoEval_GetFieldFromName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"MonoEval",0,&tolua_err) || 
 !tolua_isusertype(tolua_S,2,"MonoClass",0,&tolua_err) || 
 !tolua_isstring(tolua_S,3,0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  MonoEval* self = (MonoEval*)  tolua_tousertype(tolua_S,1,0);
  MonoClass* klass = ((MonoClass*)  tolua_tousertype(tolua_S,2,0));
  char* name = ((char*)  tolua_tostring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetFieldFromName'",NULL);
#endif
 {
  MonoClassField* tolua_ret = (MonoClassField*)  self->GetFieldFromName(klass,name);
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"MonoClassField");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetFieldFromName'.",&tolua_err);
 return 0;
#endif
}

/* method: SetFieldBool of class  MonoEval */
static int tolua_lua_server_MonoEval_SetFieldBool00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"MonoEval",0,&tolua_err) || 
 !tolua_isusertype(tolua_S,2,"MonoClass",0,&tolua_err) || 
 !tolua_isusertype(tolua_S,3,"MonoObject",0,&tolua_err) || 
 !tolua_isstring(tolua_S,4,0,&tolua_err) || 
 !tolua_isboolean(tolua_S,5,0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  MonoEval* self = (MonoEval*)  tolua_tousertype(tolua_S,1,0);
  MonoClass* klass = ((MonoClass*)  tolua_tousertype(tolua_S,2,0));
  MonoObject* obj = ((MonoObject*)  tolua_tousertype(tolua_S,3,0));
  char* fieldName = ((char*)  tolua_tostring(tolua_S,4,0));
  bool value = ((bool)  tolua_toboolean(tolua_S,5,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetFieldBool'",NULL);
#endif
 {
  self->SetFieldBool(klass,obj,fieldName,value);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetFieldBool'.",&tolua_err);
 return 0;
#endif
}

/* method: GetFieldAsBool of class  MonoEval */
static int tolua_lua_server_MonoEval_GetFieldAsBool00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"MonoEval",0,&tolua_err) || 
 !tolua_isusertype(tolua_S,2,"MonoClass",0,&tolua_err) || 
 !tolua_isusertype(tolua_S,3,"MonoObject",0,&tolua_err) || 
 !tolua_isstring(tolua_S,4,0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  MonoEval* self = (MonoEval*)  tolua_tousertype(tolua_S,1,0);
  MonoClass* klass = ((MonoClass*)  tolua_tousertype(tolua_S,2,0));
  MonoObject* obj = ((MonoObject*)  tolua_tousertype(tolua_S,3,0));
  char* fieldName = ((char*)  tolua_tostring(tolua_S,4,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetFieldAsBool'",NULL);
#endif
 {
  bool tolua_ret = (bool)  self->GetFieldAsBool(klass,obj,fieldName);
 tolua_pushboolean(tolua_S,(bool)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetFieldAsBool'.",&tolua_err);
 return 0;
#endif
}

/* method: SetFieldInt of class  MonoEval */
static int tolua_lua_server_MonoEval_SetFieldInt00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"MonoEval",0,&tolua_err) || 
 !tolua_isusertype(tolua_S,2,"MonoClass",0,&tolua_err) || 
 !tolua_isusertype(tolua_S,3,"MonoObject",0,&tolua_err) || 
 !tolua_isstring(tolua_S,4,0,&tolua_err) || 
 !tolua_isnumber(tolua_S,5,0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  MonoEval* self = (MonoEval*)  tolua_tousertype(tolua_S,1,0);
  MonoClass* klass = ((MonoClass*)  tolua_tousertype(tolua_S,2,0));
  MonoObject* obj = ((MonoObject*)  tolua_tousertype(tolua_S,3,0));
  char* fieldName = ((char*)  tolua_tostring(tolua_S,4,0));
  int value = ((int)  tolua_tonumber(tolua_S,5,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetFieldInt'",NULL);
#endif
 {
  self->SetFieldInt(klass,obj,fieldName,value);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetFieldInt'.",&tolua_err);
 return 0;
#endif
}

/* method: GetFieldAsInt of class  MonoEval */
static int tolua_lua_server_MonoEval_GetFieldAsInt00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"MonoEval",0,&tolua_err) || 
 !tolua_isusertype(tolua_S,2,"MonoClass",0,&tolua_err) || 
 !tolua_isusertype(tolua_S,3,"MonoObject",0,&tolua_err) || 
 !tolua_isstring(tolua_S,4,0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  MonoEval* self = (MonoEval*)  tolua_tousertype(tolua_S,1,0);
  MonoClass* klass = ((MonoClass*)  tolua_tousertype(tolua_S,2,0));
  MonoObject* obj = ((MonoObject*)  tolua_tousertype(tolua_S,3,0));
  char* fieldName = ((char*)  tolua_tostring(tolua_S,4,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetFieldAsInt'",NULL);
#endif
 {
  int tolua_ret = (int)  self->GetFieldAsInt(klass,obj,fieldName);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetFieldAsInt'.",&tolua_err);
 return 0;
#endif
}

/* method: SetFieldString of class  MonoEval */
static int tolua_lua_server_MonoEval_SetFieldString00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"MonoEval",0,&tolua_err) || 
 !tolua_isusertype(tolua_S,2,"MonoClass",0,&tolua_err) || 
 !tolua_isusertype(tolua_S,3,"MonoObject",0,&tolua_err) || 
 !tolua_isstring(tolua_S,4,0,&tolua_err) || 
 !tolua_isstring(tolua_S,5,0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  MonoEval* self = (MonoEval*)  tolua_tousertype(tolua_S,1,0);
  MonoClass* klass = ((MonoClass*)  tolua_tousertype(tolua_S,2,0));
  MonoObject* obj = ((MonoObject*)  tolua_tousertype(tolua_S,3,0));
  char* fieldName = ((char*)  tolua_tostring(tolua_S,4,0));
  char* str = ((char*)  tolua_tostring(tolua_S,5,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetFieldString'",NULL);
#endif
 {
  self->SetFieldString(klass,obj,fieldName,str);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetFieldString'.",&tolua_err);
 return 0;
#endif
}

/* method: GetFieldAsString of class  MonoEval */
static int tolua_lua_server_MonoEval_GetFieldAsString00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"MonoEval",0,&tolua_err) || 
 !tolua_isusertype(tolua_S,2,"MonoClass",0,&tolua_err) || 
 !tolua_isusertype(tolua_S,3,"MonoObject",0,&tolua_err) || 
 !tolua_isstring(tolua_S,4,0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  MonoEval* self = (MonoEval*)  tolua_tousertype(tolua_S,1,0);
  MonoClass* klass = ((MonoClass*)  tolua_tousertype(tolua_S,2,0));
  MonoObject* obj = ((MonoObject*)  tolua_tousertype(tolua_S,3,0));
  char* fieldName = ((char*)  tolua_tostring(tolua_S,4,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetFieldAsString'",NULL);
#endif
 {
  char* tolua_ret = (char*)  self->GetFieldAsString(klass,obj,fieldName);
 tolua_pushstring(tolua_S,(const char*)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetFieldAsString'.",&tolua_err);
 return 0;
#endif
}

/* method: GetPropertyAsInt of class  MonoEval */
static int tolua_lua_server_MonoEval_GetPropertyAsInt00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"MonoEval",0,&tolua_err) || 
 !tolua_isusertype(tolua_S,2,"MonoClass",0,&tolua_err) || 
 !tolua_isusertype(tolua_S,3,"MonoObject",0,&tolua_err) || 
 !tolua_isstring(tolua_S,4,0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  MonoEval* self = (MonoEval*)  tolua_tousertype(tolua_S,1,0);
  MonoClass* klass = ((MonoClass*)  tolua_tousertype(tolua_S,2,0));
  MonoObject* obj = ((MonoObject*)  tolua_tousertype(tolua_S,3,0));
  char* fieldName = ((char*)  tolua_tostring(tolua_S,4,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetPropertyAsInt'",NULL);
#endif
 {
  int tolua_ret = (int)  self->GetPropertyAsInt(klass,obj,fieldName);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetPropertyAsInt'.",&tolua_err);
 return 0;
#endif
}

/* method: GetPropertyAsString of class  MonoEval */
static int tolua_lua_server_MonoEval_GetPropertyAsString00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"MonoEval",0,&tolua_err) || 
 !tolua_isusertype(tolua_S,2,"MonoClass",0,&tolua_err) || 
 !tolua_isusertype(tolua_S,3,"MonoObject",0,&tolua_err) || 
 !tolua_isstring(tolua_S,4,0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  MonoEval* self = (MonoEval*)  tolua_tousertype(tolua_S,1,0);
  MonoClass* klass = ((MonoClass*)  tolua_tousertype(tolua_S,2,0));
  MonoObject* obj = ((MonoObject*)  tolua_tousertype(tolua_S,3,0));
  char* fieldName = ((char*)  tolua_tostring(tolua_S,4,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetPropertyAsString'",NULL);
#endif
 {
  char* tolua_ret = (char*)  self->GetPropertyAsString(klass,obj,fieldName);
 tolua_pushstring(tolua_S,(const char*)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetPropertyAsString'.",&tolua_err);
 return 0;
#endif
}

/* method: GetPropertyAsBool of class  MonoEval */
static int tolua_lua_server_MonoEval_GetPropertyAsBool00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"MonoEval",0,&tolua_err) || 
 !tolua_isusertype(tolua_S,2,"MonoClass",0,&tolua_err) || 
 !tolua_isusertype(tolua_S,3,"MonoObject",0,&tolua_err) || 
 !tolua_isstring(tolua_S,4,0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  MonoEval* self = (MonoEval*)  tolua_tousertype(tolua_S,1,0);
  MonoClass* klass = ((MonoClass*)  tolua_tousertype(tolua_S,2,0));
  MonoObject* obj = ((MonoObject*)  tolua_tousertype(tolua_S,3,0));
  char* fieldName = ((char*)  tolua_tostring(tolua_S,4,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetPropertyAsBool'",NULL);
#endif
 {
  bool tolua_ret = (bool)  self->GetPropertyAsBool(klass,obj,fieldName);
 tolua_pushboolean(tolua_S,(bool)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetPropertyAsBool'.",&tolua_err);
 return 0;
#endif
}

/* method: SetProperty of class  MonoEval */
static int tolua_lua_server_MonoEval_SetProperty00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"MonoEval",0,&tolua_err) || 
 !tolua_isusertype(tolua_S,2,"MonoClass",0,&tolua_err) || 
 !tolua_isusertype(tolua_S,3,"MonoObject",0,&tolua_err) || 
 !tolua_isstring(tolua_S,4,0,&tolua_err) || 
 !tolua_isnumber(tolua_S,5,0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  MonoEval* self = (MonoEval*)  tolua_tousertype(tolua_S,1,0);
  MonoClass* klass = ((MonoClass*)  tolua_tousertype(tolua_S,2,0));
  MonoObject* obj = ((MonoObject*)  tolua_tousertype(tolua_S,3,0));
  char* fieldName = ((char*)  tolua_tostring(tolua_S,4,0));
  int value = ((int)  tolua_tonumber(tolua_S,5,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetProperty'",NULL);
#endif
 {
  self->SetProperty(klass,obj,fieldName,value);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetProperty'.",&tolua_err);
 return 0;
#endif
}

/* method: SetPropertyString of class  MonoEval */
static int tolua_lua_server_MonoEval_SetPropertyString00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"MonoEval",0,&tolua_err) || 
 !tolua_isusertype(tolua_S,2,"MonoClass",0,&tolua_err) || 
 !tolua_isusertype(tolua_S,3,"MonoObject",0,&tolua_err) || 
 !tolua_isstring(tolua_S,4,0,&tolua_err) || 
 !tolua_isstring(tolua_S,5,0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  MonoEval* self = (MonoEval*)  tolua_tousertype(tolua_S,1,0);
  MonoClass* klass = ((MonoClass*)  tolua_tousertype(tolua_S,2,0));
  MonoObject* obj = ((MonoObject*)  tolua_tousertype(tolua_S,3,0));
  char* fieldName = ((char*)  tolua_tostring(tolua_S,4,0));
  char* str = ((char*)  tolua_tostring(tolua_S,5,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetPropertyString'",NULL);
#endif
 {
  self->SetPropertyString(klass,obj,fieldName,str);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetPropertyString'.",&tolua_err);
 return 0;
#endif
}

/* method: IntToMonoObject of class  MonoEval */
static int tolua_lua_server_MonoEval_IntToMonoObject00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"MonoEval",0,&tolua_err) || 
 !tolua_isnumber(tolua_S,2,0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  MonoEval* self = (MonoEval*)  tolua_tousertype(tolua_S,1,0);
  int x = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IntToMonoObject'",NULL);
#endif
 {
  MonoObject* tolua_ret = (MonoObject*)  self->IntToMonoObject(x);
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"MonoObject");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IntToMonoObject'.",&tolua_err);
 return 0;
#endif
}

/* method: InvokeStatic of class  MonoEval */
static int tolua_lua_server_MonoEval_InvokeStatic00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"MonoEval",0,&tolua_err) || 
 !tolua_isstring(tolua_S,2,0,&tolua_err) || 
 !tolua_isstring(tolua_S,3,0,&tolua_err) || 
 !tolua_isstring(tolua_S,4,0,&tolua_err) || 
 !tolua_isstring(tolua_S,5,0,&tolua_err) || 
 !tolua_isboolean(tolua_S,6,0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,7,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  MonoEval* self = (MonoEval*)  tolua_tousertype(tolua_S,1,0);
  char* klassNameSpace = ((char*)  tolua_tostring(tolua_S,2,0));
  char* klassName = ((char*)  tolua_tostring(tolua_S,3,0));
  const char* methodName = ((const char*)  tolua_tostring(tolua_S,4,0));
  char* param = ((char*)  tolua_tostring(tolua_S,5,0));
  bool flgQueue = ((bool)  tolua_toboolean(tolua_S,6,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'InvokeStatic'",NULL);
#endif
 {
  self->InvokeStatic(klassNameSpace,klassName,methodName,param,flgQueue);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'InvokeStatic'.",&tolua_err);
 return 0;
#endif
}

/* method: attatch of class  MonoEval */
static int tolua_lua_server_MonoEval_attatch00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"MonoEval",0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  MonoEval* self = (MonoEval*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'attatch'",NULL);
#endif
 {
  self->attatch();
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'attatch'.",&tolua_err);
 return 0;
#endif
}

/* get function: method of class  RunTimeInvokeData */
static int tolua_get_RunTimeInvokeData_RunTimeInvokeData_method_ptr(lua_State* tolua_S)
{
  RunTimeInvokeData* self = (RunTimeInvokeData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'method'",NULL);
#endif
 tolua_pushusertype(tolua_S,(void*)self->method,"MonoMethod");
 return 1;
}

/* set function: method of class  RunTimeInvokeData */
static int tolua_set_RunTimeInvokeData_RunTimeInvokeData_method_ptr(lua_State* tolua_S)
{
  RunTimeInvokeData* self = (RunTimeInvokeData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'method'",NULL);
 if (!tolua_isusertype(tolua_S,2,"MonoMethod",0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->method = ((MonoMethod*)  tolua_tousertype(tolua_S,2,0));
 return 0;
}

/* get function: obj of class  RunTimeInvokeData */
static int tolua_get_RunTimeInvokeData_RunTimeInvokeData_obj_ptr(lua_State* tolua_S)
{
  RunTimeInvokeData* self = (RunTimeInvokeData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'obj'",NULL);
#endif
 tolua_pushusertype(tolua_S,(void*)self->obj,"MonoObject");
 return 1;
}

/* set function: obj of class  RunTimeInvokeData */
static int tolua_set_RunTimeInvokeData_RunTimeInvokeData_obj_ptr(lua_State* tolua_S)
{
  RunTimeInvokeData* self = (RunTimeInvokeData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'obj'",NULL);
 if (!tolua_isusertype(tolua_S,2,"MonoObject",0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->obj = ((MonoObject*)  tolua_tousertype(tolua_S,2,0));
 return 0;
}

/* get function: params of class  RunTimeInvokeData */
static int tolua_get_RunTimeInvokeData_RunTimeInvokeData_unsigned_params(lua_State* tolua_S)
{
  RunTimeInvokeData* self = (RunTimeInvokeData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'params'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->params);
 return 1;
}

/* set function: params of class  RunTimeInvokeData */
static int tolua_set_RunTimeInvokeData_RunTimeInvokeData_unsigned_params(lua_State* tolua_S)
{
  RunTimeInvokeData* self = (RunTimeInvokeData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'params'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->params = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: exec of class  RunTimeInvokeData */
static int tolua_get_RunTimeInvokeData_RunTimeInvokeData_unsigned_exec(lua_State* tolua_S)
{
  RunTimeInvokeData* self = (RunTimeInvokeData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'exec'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->exec);
 return 1;
}

/* set function: exec of class  RunTimeInvokeData */
static int tolua_set_RunTimeInvokeData_RunTimeInvokeData_unsigned_exec(lua_State* tolua_S)
{
  RunTimeInvokeData* self = (RunTimeInvokeData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'exec'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->exec = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* method: new of class  RunTimeInvokeData */
static int tolua_lua_server_RunTimeInvokeData_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertable(tolua_S,1,"RunTimeInvokeData",0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
 {
  RunTimeInvokeData* tolua_ret = (RunTimeInvokeData*)  new RunTimeInvokeData();
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"RunTimeInvokeData");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}

/* get function: mutex of class  RunTimeInvokeQueue */
static int tolua_get_RunTimeInvokeQueue_RunTimeInvokeQueue_mutex(lua_State* tolua_S)
{
  RunTimeInvokeQueue* self = (RunTimeInvokeQueue*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'mutex'",NULL);
#endif
 tolua_pushusertype(tolua_S,(void*)&self->mutex,"Mutex");
 return 1;
}

/* set function: mutex of class  RunTimeInvokeQueue */
static int tolua_set_RunTimeInvokeQueue_RunTimeInvokeQueue_mutex(lua_State* tolua_S)
{
  RunTimeInvokeQueue* self = (RunTimeInvokeQueue*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'mutex'",NULL);
 if (!tolua_isusertype(tolua_S,2,"Mutex",0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->mutex = *((Mutex*)  tolua_tousertype(tolua_S,2,0));
 return 0;
}

/* method: new of class  RunTimeInvokeQueue */
static int tolua_lua_server_RunTimeInvokeQueue_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertable(tolua_S,1,"RunTimeInvokeQueue",0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
 {
  RunTimeInvokeQueue* tolua_ret = (RunTimeInvokeQueue*)  new RunTimeInvokeQueue();
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"RunTimeInvokeQueue");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}

/* method: add of class  RunTimeInvokeQueue */
static int tolua_lua_server_RunTimeInvokeQueue_add00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"RunTimeInvokeQueue",0,&tolua_err) || 
 !tolua_isusertype(tolua_S,2,"RunTimeInvokeData",0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  RunTimeInvokeQueue* self = (RunTimeInvokeQueue*)  tolua_tousertype(tolua_S,1,0);
  RunTimeInvokeData data = *((RunTimeInvokeData*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'add'",NULL);
#endif
 {
  self->add(data);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'add'.",&tolua_err);
 return 0;
#endif
}

/* method: size of class  RunTimeInvokeQueue */
static int tolua_lua_server_RunTimeInvokeQueue_size00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"RunTimeInvokeQueue",0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  RunTimeInvokeQueue* self = (RunTimeInvokeQueue*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'size'",NULL);
#endif
 {
  int tolua_ret = (int)  self->size();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'size'.",&tolua_err);
 return 0;
#endif
}

/* method: pop of class  RunTimeInvokeQueue */
static int tolua_lua_server_RunTimeInvokeQueue_pop00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"RunTimeInvokeQueue",0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  RunTimeInvokeQueue* self = (RunTimeInvokeQueue*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'pop'",NULL);
#endif
 {
  RunTimeInvokeData tolua_ret =  self->pop();
 {
#ifdef __cplusplus
 void* tolua_obj = new RunTimeInvokeData(tolua_ret);
 tolua_pushusertype(tolua_S,tolua_clone(tolua_S,tolua_obj,tolua_collect_RunTimeInvokeData),"RunTimeInvokeData");
#else
 void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(RunTimeInvokeData));
 tolua_pushusertype(tolua_S,tolua_clone(tolua_S,tolua_obj,NULL),"RunTimeInvokeData");
#endif
 }
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'pop'.",&tolua_err);
 return 0;
#endif
}

/* get function: runTimeInvokeQueue */
static int tolua_get_runTimeInvokeQueue_ptr(lua_State* tolua_S)
{
 tolua_pushusertype(tolua_S,(void*)runTimeInvokeQueue,"RunTimeInvokeQueue");
 return 1;
}

/* set function: runTimeInvokeQueue */
static int tolua_set_runTimeInvokeQueue_ptr(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!tolua_isusertype(tolua_S,2,"RunTimeInvokeQueue",0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  runTimeInvokeQueue = ((RunTimeInvokeQueue*)  tolua_tousertype(tolua_S,2,0));
 return 0;
}

/* method: logStr of class  Logger */
static int tolua_lua_server_Logger_logStr00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"Logger",0,&tolua_err) || 
 !tolua_isstring(tolua_S,2,0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  Logger* self = (Logger*)  tolua_tousertype(tolua_S,1,0);
  char* p = ((char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'logStr'",NULL);
#endif
 {
  self->logStr(p);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'logStr'.",&tolua_err);
 return 0;
#endif
}

/* method: logHex of class  Logger */
static int tolua_lua_server_Logger_logHex00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"Logger",0,&tolua_err) || 
 !tolua_isnumber(tolua_S,2,0,&tolua_err) || 
 !tolua_isnumber(tolua_S,3,0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  Logger* self = (Logger*)  tolua_tousertype(tolua_S,1,0);
  unsigned int tolua_var_1 = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
  int len = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'logHex'",NULL);
#endif
 {
  self->logHex(tolua_var_1,len);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'logHex'.",&tolua_err);
 return 0;
#endif
}

/* method: toHex of class  Logger */
static int tolua_lua_server_Logger_toHex00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"Logger",0,&tolua_err) || 
 !tolua_isnumber(tolua_S,2,0,&tolua_err) || 
 !tolua_isnumber(tolua_S,3,0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  Logger* self = (Logger*)  tolua_tousertype(tolua_S,1,0);
  unsigned int tolua_var_2 = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
  int len = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'toHex'",NULL);
#endif
 {
  char* tolua_ret = (char*)  self->toHex(tolua_var_2,len);
 tolua_pushstring(tolua_S,(const char*)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'toHex'.",&tolua_err);
 return 0;
#endif
}

/* get function: monoEval */
static int tolua_get_monoEval_ptr(lua_State* tolua_S)
{
 tolua_pushusertype(tolua_S,(void*)monoEval,"MonoEval");
 return 1;
}

/* set function: monoEval */
static int tolua_set_monoEval_ptr(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!tolua_isusertype(tolua_S,2,"MonoEval",0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  monoEval = ((MonoEval*)  tolua_tousertype(tolua_S,2,0));
 return 0;
}

/* get function: flgLogMonoRuntimeInvoke */
static int tolua_get_flgLogMonoRuntimeInvoke(lua_State* tolua_S)
{
 tolua_pushboolean(tolua_S,(bool)flgLogMonoRuntimeInvoke);
 return 1;
}

/* set function: flgLogMonoRuntimeInvoke */
static int tolua_set_flgLogMonoRuntimeInvoke(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  flgLogMonoRuntimeInvoke = ((bool)  tolua_toboolean(tolua_S,2,0));
 return 0;
}

/* get function: flgLoadAssemblySuccess */
static int tolua_get_flgLoadAssemblySuccess(lua_State* tolua_S)
{
 tolua_pushboolean(tolua_S,(bool)flgLoadAssemblySuccess);
 return 1;
}

/* set function: flgLoadAssemblySuccess */
static int tolua_set_flgLoadAssemblySuccess(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  flgLoadAssemblySuccess = ((bool)  tolua_toboolean(tolua_S,2,0));
 return 0;
}

/* function: sleep */
static int tolua_lua_server_sleep00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isnumber(tolua_S,1,0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  int tolua_var_3 = ((int)  tolua_tonumber(tolua_S,1,0));
 {
  sleep(tolua_var_3);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'sleep'.",&tolua_err);
 return 0;
#endif
}

/* get function: serverLogger */
static int tolua_get_serverLogger_ptr(lua_State* tolua_S)
{
 tolua_pushusertype(tolua_S,(void*)serverLogger,"Logger");
 return 1;
}

/* set function: serverLogger */
static int tolua_set_serverLogger_ptr(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!tolua_isusertype(tolua_S,2,"Logger",0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  serverLogger = ((Logger*)  tolua_tousertype(tolua_S,2,0));
 return 0;
}

/* Open lib function */
LUALIB_API int luaopen_lua_server (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,1);
 tolua_beginmodule(tolua_S,NULL);
 tolua_cclass(tolua_S,"MonoAssembly","MonoAssembly","",NULL);
 tolua_beginmodule(tolua_S,"MonoAssembly");
 tolua_endmodule(tolua_S);
 tolua_cclass(tolua_S,"MonoDomain","MonoDomain","",NULL);
 tolua_beginmodule(tolua_S,"MonoDomain");
 tolua_endmodule(tolua_S);
 tolua_cclass(tolua_S,"MonoImage","MonoImage","",NULL);
 tolua_beginmodule(tolua_S,"MonoImage");
 tolua_endmodule(tolua_S);
 tolua_cclass(tolua_S,"MonoAssemblyName","MonoAssemblyName","",NULL);
 tolua_beginmodule(tolua_S,"MonoAssemblyName");
 tolua_endmodule(tolua_S);
 tolua_cclass(tolua_S,"MonoClass","MonoClass","",NULL);
 tolua_beginmodule(tolua_S,"MonoClass");
 tolua_endmodule(tolua_S);
 tolua_cclass(tolua_S,"MonoClassField","MonoClassField","",NULL);
 tolua_beginmodule(tolua_S,"MonoClassField");
 tolua_endmodule(tolua_S);
 tolua_cclass(tolua_S,"MonoVTable","MonoVTable","",NULL);
 tolua_beginmodule(tolua_S,"MonoVTable");
 tolua_endmodule(tolua_S);
 tolua_cclass(tolua_S,"MonoThreadsSync","MonoThreadsSync","",NULL);
 tolua_beginmodule(tolua_S,"MonoThreadsSync");
 tolua_endmodule(tolua_S);
 tolua_cclass(tolua_S,"MonoProperty","MonoProperty","",NULL);
 tolua_beginmodule(tolua_S,"MonoProperty");
 tolua_endmodule(tolua_S);
 tolua_cclass(tolua_S,"MonoMethod","MonoMethod","",NULL);
 tolua_beginmodule(tolua_S,"MonoMethod");
 tolua_endmodule(tolua_S);
 tolua_cclass(tolua_S,"MonoObject","MonoObject","",NULL);
 tolua_beginmodule(tolua_S,"MonoObject");
 tolua_variable(tolua_S,"vtable",tolua_get_MonoObject_MonoObject_vtable_ptr,tolua_set_MonoObject_MonoObject_vtable_ptr);
 tolua_variable(tolua_S,"synchronisation",tolua_get_MonoObject_MonoObject_synchronisation_ptr,tolua_set_MonoObject_MonoObject_synchronisation_ptr);
 tolua_endmodule(tolua_S);
 tolua_cclass(tolua_S,"MonoString","MonoString","",NULL);
 tolua_beginmodule(tolua_S,"MonoString");
 tolua_variable(tolua_S,"object",tolua_get_MonoString_MonoString_object,tolua_set_MonoString_MonoString_object);
 tolua_variable(tolua_S,"length",tolua_get_MonoString_MonoString_length,tolua_set_MonoString_MonoString_length);
 tolua_array(tolua_S,"chars",tolua_get_lua_server_MonoString_chars,tolua_set_lua_server_MonoString_chars);
 tolua_endmodule(tolua_S);
 tolua_function(tolua_S,"mono_class_get_name",tolua_lua_server_mono_class_get_name00);
 tolua_function(tolua_S,"mono_class_get_namespace",tolua_lua_server_mono_class_get_namespace00);
 tolua_function(tolua_S,"mono_method_get_name",tolua_lua_server_mono_method_get_name00);
 tolua_function(tolua_S,"mono_method_get_class",tolua_lua_server_mono_method_get_class00);
 tolua_function(tolua_S,"mono_domain_get",tolua_lua_server_mono_domain_get00);
 tolua_function(tolua_S,"mono_image_open_from_data",tolua_lua_server_mono_image_open_from_data00);
 tolua_function(tolua_S,"mono_domain_assembly_open",tolua_lua_server_mono_domain_assembly_open00);
 tolua_function(tolua_S,"mono_get_root_domain",tolua_lua_server_mono_get_root_domain00);
 tolua_function(tolua_S,"mono_thread_attach",tolua_lua_server_mono_thread_attach00);
 tolua_function(tolua_S,"mono_assembly_load_from_full",tolua_lua_server_mono_assembly_load_from_full00);
 tolua_function(tolua_S,"mono_assembly_get_image",tolua_lua_server_mono_assembly_get_image00);
 tolua_function(tolua_S,"mono_class_from_name",tolua_lua_server_mono_class_from_name00);
 tolua_function(tolua_S,"mono_class_get_method_from_name",tolua_lua_server_mono_class_get_method_from_name00);
 tolua_function(tolua_S,"mono_runtime_invoke",tolua_lua_server_mono_runtime_invoke00);
 tolua_function(tolua_S,"mono_assembly_foreach",tolua_lua_server_mono_assembly_foreach00);
 tolua_function(tolua_S,"mono_assembly_get_name",tolua_lua_server_mono_assembly_get_name00);
 tolua_function(tolua_S,"mono_stringify_assembly_name",tolua_lua_server_mono_stringify_assembly_name00);
 tolua_function(tolua_S,"mono_image_get_table_rows",tolua_lua_server_mono_image_get_table_rows00);
 tolua_function(tolua_S,"mono_class_get",tolua_lua_server_mono_class_get00);
 tolua_function(tolua_S,"mono_class_get_fields",tolua_lua_server_mono_class_get_fields00);
 tolua_function(tolua_S,"mono_field_get_name",tolua_lua_server_mono_field_get_name00);
 tolua_function(tolua_S,"mono_field_static_set_value",tolua_lua_server_mono_field_static_set_value00);
 tolua_function(tolua_S,"mono_field_static_get_value",tolua_lua_server_mono_field_static_get_value00);
 tolua_function(tolua_S,"mono_class_vtable",tolua_lua_server_mono_class_vtable00);
 tolua_function(tolua_S,"mono_string_new",tolua_lua_server_mono_string_new00);
 tolua_function(tolua_S,"mono_runtime_class_init",tolua_lua_server_mono_runtime_class_init00);
 tolua_function(tolua_S,"mono_string_to_utf8",tolua_lua_server_mono_string_to_utf800);
 tolua_function(tolua_S,"mono_class_get_field_from_name",tolua_lua_server_mono_class_get_field_from_name00);
 tolua_function(tolua_S,"mono_property_get_value",tolua_lua_server_mono_property_get_value00);
 tolua_function(tolua_S,"mono_property_set_value",tolua_lua_server_mono_property_set_value00);
 tolua_function(tolua_S,"mono_class_get_property_from_name",tolua_lua_server_mono_class_get_property_from_name00);
 tolua_function(tolua_S,"mono_class_get_parent",tolua_lua_server_mono_class_get_parent00);
 tolua_function(tolua_S,"mono_field_get_value",tolua_lua_server_mono_field_get_value00);
 tolua_function(tolua_S,"mono_field_set_value",tolua_lua_server_mono_field_set_value00);
 tolua_function(tolua_S,"MonoLoad",tolua_lua_server_MonoLoad00);
 tolua_function(tolua_S,"BackupTargetAddress",tolua_lua_server_BackupTargetAddress00);
 tolua_function(tolua_S,"InjectJumpCode",tolua_lua_server_InjectJumpCode00);
 tolua_function(tolua_S,"MonoHook",tolua_lua_server_MonoHook00);
 tolua_function(tolua_S,"MonoLoadAssembly",tolua_lua_server_MonoLoadAssembly00);
 tolua_function(tolua_S,"MonoDumpImage",tolua_lua_server_MonoDumpImage00);
 tolua_function(tolua_S,"MonoLoadAndInvokeAssembly",tolua_lua_server_MonoLoadAndInvokeAssembly00);
 tolua_variable(tolua_S,"libmonoHandle",tolua_get_unsigned_libmonoHandle,tolua_set_unsigned_libmonoHandle);
 tolua_variable(tolua_S,"monoTextSize",tolua_get_unsigned_monoTextSize,tolua_set_unsigned_monoTextSize);
 tolua_variable(tolua_S,"monoBaseAddr",tolua_get_unsigned_monoBaseAddr,tolua_set_unsigned_monoBaseAddr);
 tolua_cclass(tolua_S,"MonoEval","MonoEval","",NULL);
 tolua_beginmodule(tolua_S,"MonoEval");
 tolua_function(tolua_S,"new",tolua_lua_server_MonoEval_new00);
 tolua_function(tolua_S,"eval",tolua_lua_server_MonoEval_eval00);
 tolua_function(tolua_S,"GetAllAssembly",tolua_lua_server_MonoEval_GetAllAssembly00);
 tolua_function(tolua_S,"GetClassFromName",tolua_lua_server_MonoEval_GetClassFromName00);
 tolua_function(tolua_S,"GetFieldFromName",tolua_lua_server_MonoEval_GetFieldFromName00);
 tolua_function(tolua_S,"SetFieldBool",tolua_lua_server_MonoEval_SetFieldBool00);
 tolua_function(tolua_S,"GetFieldAsBool",tolua_lua_server_MonoEval_GetFieldAsBool00);
 tolua_function(tolua_S,"SetFieldInt",tolua_lua_server_MonoEval_SetFieldInt00);
 tolua_function(tolua_S,"GetFieldAsInt",tolua_lua_server_MonoEval_GetFieldAsInt00);
 tolua_function(tolua_S,"SetFieldString",tolua_lua_server_MonoEval_SetFieldString00);
 tolua_function(tolua_S,"GetFieldAsString",tolua_lua_server_MonoEval_GetFieldAsString00);
 tolua_function(tolua_S,"GetPropertyAsInt",tolua_lua_server_MonoEval_GetPropertyAsInt00);
 tolua_function(tolua_S,"GetPropertyAsString",tolua_lua_server_MonoEval_GetPropertyAsString00);
 tolua_function(tolua_S,"GetPropertyAsBool",tolua_lua_server_MonoEval_GetPropertyAsBool00);
 tolua_function(tolua_S,"SetProperty",tolua_lua_server_MonoEval_SetProperty00);
 tolua_function(tolua_S,"SetPropertyString",tolua_lua_server_MonoEval_SetPropertyString00);
 tolua_function(tolua_S,"IntToMonoObject",tolua_lua_server_MonoEval_IntToMonoObject00);
 tolua_function(tolua_S,"InvokeStatic",tolua_lua_server_MonoEval_InvokeStatic00);
 tolua_function(tolua_S,"attatch",tolua_lua_server_MonoEval_attatch00);
 tolua_endmodule(tolua_S);
#ifdef __cplusplus
 tolua_cclass(tolua_S,"RunTimeInvokeData","RunTimeInvokeData","",tolua_collect_RunTimeInvokeData);
#else
 tolua_cclass(tolua_S,"RunTimeInvokeData","RunTimeInvokeData","",NULL);
#endif
 tolua_beginmodule(tolua_S,"RunTimeInvokeData");
 tolua_variable(tolua_S,"method",tolua_get_RunTimeInvokeData_RunTimeInvokeData_method_ptr,tolua_set_RunTimeInvokeData_RunTimeInvokeData_method_ptr);
 tolua_variable(tolua_S,"obj",tolua_get_RunTimeInvokeData_RunTimeInvokeData_obj_ptr,tolua_set_RunTimeInvokeData_RunTimeInvokeData_obj_ptr);
 tolua_variable(tolua_S,"params",tolua_get_RunTimeInvokeData_RunTimeInvokeData_unsigned_params,tolua_set_RunTimeInvokeData_RunTimeInvokeData_unsigned_params);
 tolua_variable(tolua_S,"exec",tolua_get_RunTimeInvokeData_RunTimeInvokeData_unsigned_exec,tolua_set_RunTimeInvokeData_RunTimeInvokeData_unsigned_exec);
 tolua_function(tolua_S,"new",tolua_lua_server_RunTimeInvokeData_new00);
 tolua_endmodule(tolua_S);
 tolua_cclass(tolua_S,"RunTimeInvokeQueue","RunTimeInvokeQueue","",NULL);
 tolua_beginmodule(tolua_S,"RunTimeInvokeQueue");
 tolua_variable(tolua_S,"mutex",tolua_get_RunTimeInvokeQueue_RunTimeInvokeQueue_mutex,tolua_set_RunTimeInvokeQueue_RunTimeInvokeQueue_mutex);
 tolua_function(tolua_S,"new",tolua_lua_server_RunTimeInvokeQueue_new00);
 tolua_function(tolua_S,"add",tolua_lua_server_RunTimeInvokeQueue_add00);
 tolua_function(tolua_S,"size",tolua_lua_server_RunTimeInvokeQueue_size00);
 tolua_function(tolua_S,"pop",tolua_lua_server_RunTimeInvokeQueue_pop00);
 tolua_endmodule(tolua_S);
 tolua_variable(tolua_S,"runTimeInvokeQueue",tolua_get_runTimeInvokeQueue_ptr,tolua_set_runTimeInvokeQueue_ptr);
 tolua_cclass(tolua_S,"Logger","Logger","",NULL);
 tolua_beginmodule(tolua_S,"Logger");
 tolua_function(tolua_S,"logStr",tolua_lua_server_Logger_logStr00);
 tolua_function(tolua_S,"logHex",tolua_lua_server_Logger_logHex00);
 tolua_function(tolua_S,"toHex",tolua_lua_server_Logger_toHex00);
 tolua_endmodule(tolua_S);
 tolua_variable(tolua_S,"monoEval",tolua_get_monoEval_ptr,tolua_set_monoEval_ptr);
 tolua_variable(tolua_S,"flgLogMonoRuntimeInvoke",tolua_get_flgLogMonoRuntimeInvoke,tolua_set_flgLogMonoRuntimeInvoke);
 tolua_variable(tolua_S,"flgLoadAssemblySuccess",tolua_get_flgLoadAssemblySuccess,tolua_set_flgLoadAssemblySuccess);
 tolua_function(tolua_S,"sleep",tolua_lua_server_sleep00);
 tolua_variable(tolua_S,"serverLogger",tolua_get_serverLogger_ptr,tolua_set_serverLogger_ptr);
 tolua_endmodule(tolua_S);
 return 1;
}
/* Open tolua function */
TOLUA_API int tolua_lua_server_open (lua_State* tolua_S)
{
 lua_pushcfunction(tolua_S, luaopen_lua_server);
 lua_pushstring(tolua_S, "lua_server");
 lua_call(tolua_S, 1, 0);
 return 1;
}
