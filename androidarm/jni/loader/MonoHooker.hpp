/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MonoHooker.hpp
 * Author: kwang
 *
 * Created on August 9, 2016, 9:45 AM
 */

#include <vector>
#ifndef MONOHOOKER_HPP
#define MONOHOOKER_HPP

 
typedef enum {
	MONO_TOKEN_MODULE            = 0x00000000,
	MONO_TOKEN_TYPE_REF          = 0x01000000,
	MONO_TOKEN_TYPE_DEF          = 0x02000000,
	MONO_TOKEN_FIELD_DEF         = 0x04000000,
	MONO_TOKEN_METHOD_DEF        = 0x06000000, 
	MONO_TOKEN_PARAM_DEF         = 0x08000000,
	MONO_TOKEN_INTERFACE_IMPL    = 0x09000000,
	MONO_TOKEN_MEMBER_REF        = 0x0a000000,
	MONO_TOKEN_CUSTOM_ATTRIBUTE  = 0x0c000000,
	MONO_TOKEN_PERMISSION        = 0x0e000000,
	MONO_TOKEN_SIGNATURE         = 0x11000000,
	MONO_TOKEN_EVENT             = 0x14000000,
	MONO_TOKEN_PROPERTY          = 0x17000000,
	MONO_TOKEN_MODULE_REF        = 0x1a000000,
	MONO_TOKEN_TYPE_SPEC         = 0x1b000000,
	MONO_TOKEN_ASSEMBLY          = 0x20000000,
	MONO_TOKEN_ASSEMBLY_REF      = 0x23000000,
	MONO_TOKEN_FILE              = 0x26000000,
	MONO_TOKEN_EXPORTED_TYPE     = 0x27000000,
	MONO_TOKEN_MANIFEST_RESOURCE = 0x28000000,
	MONO_TOKEN_GENERIC_PARAM     = 0x2a000000,
	MONO_TOKEN_METHOD_SPEC       = 0x2b000000,

	/*
	 * These do not match metadata tables directly
	 */
	MONO_TOKEN_STRING            = 0x70000000,
	MONO_TOKEN_NAME              = 0x71000000,
	MONO_TOKEN_BASE_TYPE         = 0x72000000
} MonoTokenType;


#define MONO_TABLE_TYPEDEF  2

class MonoAssembly {};
class MonoDomain {};
class MonoImage {};
class MonoAssemblyName {};
class MonoClass {};
class MonoClassField {};
class MonoVTable {};
class MonoThreadsSync {};
class MonoProperty {};
class MonoMethod {};

typedef struct _MonoObject {
	MonoVTable *vtable;
	MonoThreadsSync *synchronisation;
} MonoObject;
typedef struct _MonoString {
	MonoObject object;
	int32_t length;
	uint16_t chars [0];
} MonoString;


typedef char* (*mono_class_get_name_t)(unsigned int monoClass);
extern mono_class_get_name_t mono_class_get_name;

typedef char* (*mono_class_get_namespace_t)(unsigned int monoClass);
extern mono_class_get_namespace_t mono_class_get_namespace;

typedef char* (*mono_method_get_name_t)(unsigned int monoMethod);
extern mono_method_get_name_t mono_method_get_name;

typedef unsigned int (*mono_method_get_class_t)(unsigned int monoMethod);
extern mono_method_get_class_t mono_method_get_class;

typedef MonoDomain * (*mono_domain_get_t)();
extern mono_domain_get_t mono_domain_get;

typedef MonoImage* (*mono_image_open_from_data_t)(unsigned char *data,int size,int num,int *status);
extern mono_image_open_from_data_t mono_image_open_from_data;

typedef MonoAssembly* (*mono_domain_assembly_open_t)(MonoDomain *domain, const char *assemblyName);
extern mono_domain_assembly_open_t mono_domain_assembly_open;

typedef MonoDomain * (*mono_get_root_domain_t)();
extern mono_get_root_domain_t mono_get_root_domain;

typedef void (*mono_thread_attach_t)(MonoDomain *domain);
extern mono_thread_attach_t mono_thread_attach;

typedef MonoAssembly* (*mono_assembly_load_from_full_t)(MonoImage *image, const char *fname,int *status,int readonly);
extern mono_assembly_load_from_full_t mono_assembly_load_from_full;

typedef MonoImage* (*mono_assembly_get_image_t)(MonoAssembly *assembly);
extern mono_assembly_get_image_t mono_assembly_get_image;

typedef MonoClass* (*mono_class_from_name_t)(MonoImage *image, const char* name_space, const char *name);
extern mono_class_from_name_t mono_class_from_name;

typedef MonoMethod* (*mono_class_get_method_from_name_t)(MonoClass *klass, const char *name, int param_count);
extern mono_class_get_method_from_name_t mono_class_get_method_from_name;

typedef void* (*mono_runtime_invoke_t)(MonoMethod *method, MonoObject *obj, unsigned int params, unsigned int exc);
extern mono_runtime_invoke_t mono_runtime_invoke;

typedef void  (*mono_assembly_foreach_t)(unsigned int func, void* user_data);
extern mono_assembly_foreach_t mono_assembly_foreach;

typedef MonoAssemblyName* (*mono_assembly_get_name_t)(unsigned int assembly);
extern mono_assembly_get_name_t mono_assembly_get_name;

typedef char* (*mono_stringify_assembly_name_t)(MonoAssemblyName *aname);
extern mono_stringify_assembly_name_t mono_stringify_assembly_name;

typedef int (*mono_image_get_table_rows_t)(MonoImage *image, int table_id);
extern mono_image_get_table_rows_t mono_image_get_table_rows;

typedef MonoClass* (*mono_class_get_t)(MonoImage *image, uint32_t type_token);
extern mono_class_get_t mono_class_get;

typedef MonoClassField* (*mono_class_get_fields_t) (MonoClass* klass, unsigned int *iter);
extern mono_class_get_fields_t mono_class_get_fields;

typedef char * (*mono_field_get_name_t)(MonoClassField *field);
extern mono_field_get_name_t mono_field_get_name;

typedef void (*mono_field_static_set_value_t)(MonoVTable *vt, MonoClassField *field, void *value);
extern mono_field_static_set_value_t mono_field_static_set_value;

typedef void (*mono_field_static_get_value_t)(MonoVTable *vt, MonoClassField *field, void *value);
extern mono_field_static_get_value_t mono_field_static_get_value;

typedef MonoVTable * (*mono_class_vtable_t)(MonoDomain *domain, MonoClass *klass);
extern mono_class_vtable_t mono_class_vtable;

typedef MonoString* (*mono_string_new_t)(MonoDomain* domain,char* str);
extern mono_string_new_t mono_string_new;

typedef void (*mono_runtime_class_init_t)(MonoVTable *vtable);
extern mono_runtime_class_init_t mono_runtime_class_init;

typedef char * (*mono_string_to_utf8_t)(MonoString *s);
extern mono_string_to_utf8_t mono_string_to_utf8;

typedef MonoClassField * (*mono_class_get_field_from_name_t)(MonoClass *klass,char *name);
extern mono_class_get_field_from_name_t mono_class_get_field_from_name;

typedef MonoObject* (*mono_property_get_value_t)(MonoProperty *prop, void *obj, void **params, MonoObject **exc);
extern mono_property_get_value_t mono_property_get_value;

typedef void (*mono_property_set_value_t)(MonoProperty *prop, void *obj, void **params, MonoObject **exc);
extern mono_property_set_value_t mono_property_set_value;

typedef MonoProperty* (*mono_class_get_property_from_name_t)(MonoClass *klass, const char *name);
extern mono_class_get_property_from_name_t mono_class_get_property_from_name;

typedef MonoClass* (*mono_class_get_parent_t)(MonoClass *klass);
extern mono_class_get_parent_t mono_class_get_parent;

typedef void (*mono_field_get_value_t)(MonoObject *obj, MonoClassField *field, void *value);
extern mono_field_get_value_t mono_field_get_value;

typedef void (*mono_field_set_value_t)(MonoObject *obj, MonoClassField *field, void *value);
extern mono_field_set_value_t mono_field_set_value;

unsigned int MonoLoad();
unsigned char* BackupTargetAddress(unsigned int targetAddr);
void InjectJumpCode(unsigned int targetAddr,int jumpToAddr);
unsigned int MonoHook(char *monoFunctionName,unsigned int monoHookFuncAddr);
MonoAssembly * MonoLoadAssembly(const char* fileName);
void MonoDumpImage(MonoImage *image);
void MonoLoadAndInvokeAssembly(const char* fileName,const char* name_space,char *className,const char* methodName);
void *LoadManagedLibrary(void *);
void ThreadLoadManageLibrary();

extern unsigned int libmonoHandle;
extern unsigned int monoTextSize;
extern unsigned int monoBaseAddr;

#endif /* MONOHOOKER_HPP */

