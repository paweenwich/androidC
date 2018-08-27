/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MonoMockUp.hpp
 * Author: kwang
 *
 * Created on September 6, 2016, 7:48 AM
 */

#ifndef MONOMOCKUP_HPP
#define MONOMOCKUP_HPP

#ifdef __cplusplus
extern "C" {
#endif

typedef int            gboolean;
typedef int            gint;
typedef unsigned int   guint;
typedef short          gshort;
typedef unsigned short gushort;
typedef long           glong;
typedef unsigned long  gulong;
typedef void *         gpointer;
typedef const void *   gconstpointer;
typedef char           gchar;
typedef unsigned char  guchar;

typedef char              gint8;
typedef unsigned char     guint8;
typedef short             gint16;
typedef unsigned short    guint16;
typedef long             gint32;
typedef unsigned long    guint32;
typedef long long        gint64;
typedef unsigned long long    guint64;
typedef float               gfloat;
typedef double              gdouble;
typedef unsigned short    gunichar2;

typedef guint32 mono_array_size_t;
typedef gint32 mono_array_lower_bound_t;
typedef pthread_mutex_t mono_mutex_t;

#define MONO_ZERO_LEN_ARRAY 1
#if defined(_MSC_VER) && defined(PLATFORM_IPHONE_XCOMP)
#   define USE_UINT8_BIT_FIELD(type, field) guint8 field 
#else
#   define USE_UINT8_BIT_FIELD(type, field) type field
#endif

struct MonoDomain;
struct MonoAssembly;
struct MonoImage;

struct MonoMethodSignature;
struct MonoMethodDesc;
struct MonoClassField;
struct MonoProperty;
struct MonoEvent;
struct MonoThreadsSync;
struct MonoRuntimeGenericContext;
struct MonoMarshalType;
struct MonoGenericClass;
struct MonoGenericContainer;
struct MonoClassRuntimeInfo;
struct MonoClassExt;
struct MonoClass;
struct MonoImageSet;
struct MonoArrayType {
	MonoClass *eklass;
	// Number of dimensions of the array
	uint8_t rank;

	// Arrays recording known upper and lower index bounds for each dimension
	uint8_t numsizes;
	uint8_t numlobounds;
	int *sizes;
	int *lobounds;
};
struct MonoGenericParam;
//enum MonoTypeEnum;
typedef enum {
	MONO_TYPE_END        = 0x00,       /* End of List */
	MONO_TYPE_VOID       = 0x01,
	MONO_TYPE_BOOLEAN    = 0x02,
	MONO_TYPE_CHAR       = 0x03,
	MONO_TYPE_I1         = 0x04,
	MONO_TYPE_U1         = 0x05,
	MONO_TYPE_I2         = 0x06,
	MONO_TYPE_U2         = 0x07,
	MONO_TYPE_I4         = 0x08,
	MONO_TYPE_U4         = 0x09,
	MONO_TYPE_I8         = 0x0a,
	MONO_TYPE_U8         = 0x0b,
	MONO_TYPE_R4         = 0x0c,
	MONO_TYPE_R8         = 0x0d,
	MONO_TYPE_STRING     = 0x0e,
	MONO_TYPE_PTR        = 0x0f,       /* arg: <type> token */
	MONO_TYPE_BYREF      = 0x10,       /* arg: <type> token */
	MONO_TYPE_VALUETYPE  = 0x11,       /* arg: <type> token */
	MONO_TYPE_CLASS      = 0x12,       /* arg: <type> token */
	MONO_TYPE_VAR	     = 0x13,	   /* number */
	MONO_TYPE_ARRAY      = 0x14,       /* type, rank, boundsCount, bound1, loCount, lo1 */
	MONO_TYPE_GENERICINST= 0x15,	   /* <type> <type-arg-count> <type-1> \x{2026} <type-n> */
	MONO_TYPE_TYPEDBYREF = 0x16,
	MONO_TYPE_I          = 0x18,
	MONO_TYPE_U          = 0x19,
	MONO_TYPE_FNPTR      = 0x1b,	      /* arg: full method signature */
	MONO_TYPE_OBJECT     = 0x1c,
	MONO_TYPE_SZARRAY    = 0x1d,       /* 0-based one-dim-array */
	MONO_TYPE_MVAR	     = 0x1e,       /* number */
	MONO_TYPE_CMOD_REQD  = 0x1f,       /* arg: typedef or typeref token */
	MONO_TYPE_CMOD_OPT   = 0x20,       /* optional arg: typedef or typref token */
	MONO_TYPE_INTERNAL   = 0x21,       /* CLR internal type */

	MONO_TYPE_MODIFIER   = 0x40,       /* Or with the following types */
	MONO_TYPE_SENTINEL   = 0x41,       /* Sentinel for varargs method signature */
	MONO_TYPE_PINNED     = 0x45,       /* Local var that points to pinned object */

	MONO_TYPE_ENUM       = 0x55        /* an enumeration */
} MonoTypeEnum;


struct MonoCustomMod;
struct MonoClass;
struct MonoType;
struct MonoMethod;
struct MonoVTable;

struct MonoMemPool;

typedef struct {
	const char* data;
	guint32  size;
} MonoStreamHeader;


struct MonoTableInfo {
	const char *base;
	guint       rows     : 24;
	guint       row_size : 8;

	/*
	 * Tables contain up to 9 columns and the possible sizes of the
	 * fields in the documentation are 1, 2 and 4 bytes.  So we
	 * can encode in 2 bits the size.
	 *
	 * A 32 bit value can encode the resulting size
	 *
	 * The top eight bits encode the number of columns in the table.
	 * we only need 4, but 8 is aligned no shift required. 
	 */
	guint32   size_bitfield;
};
struct GHashTable;
struct MonoConcurrentHashTable;
//struct mono_mutex_t;
struct MonoPropertyHash;
struct MonoDllMap;
struct MonoBitSet;
struct GSList;
struct MonoWrapperCaches;
struct MonoImageLoader;

struct MonoCustomMod {
    unsigned int required : 1;
    unsigned int token : 31;
} ;

#define FIELD_ATTRIBUTE_FIELD_ACCESS_MASK     0x0007
#define FIELD_ATTRIBUTE_COMPILER_CONTROLLED   0x0000
#define FIELD_ATTRIBUTE_PRIVATE               0x0001
#define FIELD_ATTRIBUTE_FAM_AND_ASSEM         0x0002
#define FIELD_ATTRIBUTE_ASSEMBLY              0x0003
#define FIELD_ATTRIBUTE_FAMILY                0x0004
#define FIELD_ATTRIBUTE_FAM_OR_ASSEM          0x0005
#define FIELD_ATTRIBUTE_PUBLIC                0x0006

#define FIELD_ATTRIBUTE_STATIC                0x0010
#define FIELD_ATTRIBUTE_INIT_ONLY             0x0020
#define FIELD_ATTRIBUTE_LITERAL               0x0040
#define FIELD_ATTRIBUTE_NOT_SERIALIZED        0x0080
#define FIELD_ATTRIBUTE_SPECIAL_NAME          0x0200
#define FIELD_ATTRIBUTE_PINVOKE_IMPL          0x2000


struct MonoType {
    union {
        MonoClass *klass; /* for VALUETYPE and CLASS */
        MonoType *type;   /* for PTR */
        MonoArrayType *array; /* for ARRAY */
        MonoMethodSignature *method;
        MonoGenericParam *generic_param; /* for VAR and MVAR */
        MonoGenericClass *generic_class; /* for GENERICINST */
    } data;
    unsigned int attrs : 16; /* param attributes or field flags */
    MonoTypeEnum type : 8;
    unsigned int num_mods : 6;  /* max 64 modifiers follow at the end */
    unsigned int byref : 1;
    unsigned int pinned : 1;  /* valid when included in a local var signature */
    MonoCustomMod modifiers[MONO_ZERO_LEN_ARRAY]; /* this may grow */
};



struct MonoClass {
    /* element class for arrays and enum basetype for enums */
    MonoClass *element_class;
    /* used for subtype checks */
    MonoClass *cast_class;

    /* for fast subtype checks */
    MonoClass **supertypes;
    guint16     idepth;

    /* array dimension */
    guint8     rank;

    int        instance_size; /* object instance size */

    USE_UINT8_BIT_FIELD(guint, inited          : 1);
    /* We use init_pending to detect cyclic calls to mono_class_init */
    USE_UINT8_BIT_FIELD(guint, init_pending    : 1);

    /* A class contains static and non static data. Static data can be
    * of the same type as the class itselfs, but it does not influence
    * the instance size of the class. To avoid cyclic calls to
    * mono_class_init (from mono_class_instance_size ()) we first
    * initialise all non static fields. After that we set size_inited
    * to 1, because we know the instance size now. After that we
    * initialise all static fields.
    */
    USE_UINT8_BIT_FIELD(guint, size_inited     : 1);
    USE_UINT8_BIT_FIELD(guint, valuetype       : 1); /* derives from System.ValueType */
    USE_UINT8_BIT_FIELD(guint, enumtype        : 1); /* derives from System.Enum */
    USE_UINT8_BIT_FIELD(guint, blittable       : 1); /* class is blittable */
    USE_UINT8_BIT_FIELD(guint, unicode         : 1); /* class uses unicode char when marshalled */
    USE_UINT8_BIT_FIELD(guint, wastypebuilder  : 1); /* class was created at runtime from a TypeBuilder */
    /* next byte */
    guint8 min_align;
    /* next byte */
    USE_UINT8_BIT_FIELD(guint, packing_size    : 4);
    USE_UINT8_BIT_FIELD(guint, has_unity_native_intptr : 1); // This class has a IntPtr that points to a native class with an asset reference
    /* still 3 bits free */
    /* next byte */
    USE_UINT8_BIT_FIELD(guint, ghcimpl         : 1); /* class has its own GetHashCode impl */
    USE_UINT8_BIT_FIELD(guint, has_finalize    : 1); /* class has its own Finalize impl */
    USE_UINT8_BIT_FIELD(guint, marshalbyref    : 1); /* class is a MarshalByRefObject */
    USE_UINT8_BIT_FIELD(guint, contextbound    : 1); /* class is a ContextBoundObject */
    USE_UINT8_BIT_FIELD(guint, delegate        : 1); /* class is a Delegate */
    USE_UINT8_BIT_FIELD(guint, gc_descr_inited : 1); /* gc_descr is initialized */
    USE_UINT8_BIT_FIELD(guint, has_cctor       : 1); /* class has a cctor */
    USE_UINT8_BIT_FIELD(guint, has_references  : 1); /* it has GC-tracked references in the instance */
    /* next byte */
    USE_UINT8_BIT_FIELD(guint, has_static_refs : 1); /* it has static fields that are GC-tracked */
    USE_UINT8_BIT_FIELD(guint, no_special_static_fields : 1); /* has no thread/context static fields */
    /* directly or indirectly derives from ComImport attributed class.
    * this means we need to create a proxy for instances of this class
    * for COM Interop. set this flag on loading so all we need is a quick check
    * during object creation rather than having to traverse supertypes
    */
    USE_UINT8_BIT_FIELD(guint, is_com_object   : 1);
    USE_UINT8_BIT_FIELD(guint, nested_classes_inited : 1); /* Whenever nested_class is initialized */
    USE_UINT8_BIT_FIELD(guint, interfaces_inited : 1); /* interfaces is initialized */
    USE_UINT8_BIT_FIELD(guint, simd_type       : 1); /* class is a simd intrinsic type */
    USE_UINT8_BIT_FIELD(guint, is_generic      : 1); /* class is a generic type definition */
    USE_UINT8_BIT_FIELD(guint, is_inflated     : 1); /* class is a generic instance */

    guint8     exception_type;	/* MONO_EXCEPTION_* */

    /* Additional information about the exception */
    /* Stored as property MONO_CLASS_PROP_EXCEPTION_DATA */
    //void       *exception_data;

    MonoClass  *parent;
    MonoClass  *nested_in;

    MonoImage *image;
    const char *name;
    const char *name_space;

    guint32    type_token;
    int        vtable_size; /* number of slots */

    guint16     interface_count;
    guint16     interface_id;        /* unique inderface id (for interfaces) */
    guint16     max_interface_id;

    guint16     interface_offsets_count;
    MonoClass **interfaces_packed;
    guint16    *interface_offsets_packed;
    guint8     *interface_bitmap;

    MonoClass **interfaces;

    union {
        int class_size; /* size of area for static fields */
        int element_size; /* for array types */
        int generic_param_token; /* for generic param types, both var and mvar */
    } sizes;

    /*
    * From the TypeDef table
    */
    guint32    flags;
    struct {
        guint32 first, count;
    } field, method;

    /* loaded on demand */
    MonoMarshalType *marshal_info;

    /*
    * Field information: Type and location from object base
    */
    MonoClassField *fields;

    MonoMethod **methods;

    /* used as the type of the this argument and when passing the arg by value */
    MonoType this_arg;
    MonoType byval_arg;

    MonoGenericClass *generic_class;
    MonoGenericContainer *generic_container;

    void *reflection_info;

    void *gc_descr;

    MonoClassRuntimeInfo *runtime_info;

    /* next element in the class_cache hash list (in MonoImage) */
    //MonoClass *next_class_cache;
    unsigned int next_class_cache;

    /* Generic vtable. Initialized by a call to mono_class_setup_vtable () */
    MonoMethod **vtable;

    /* Rarely used fields of classes */
    MonoClassExt *ext;
};



struct MonoVTable {
    MonoClass  *klass;
    /*
    * According to comments in gc_gcj.h, this should be the second word in
    * the vtable.
    */
    void *gc_descr;
    MonoDomain *domain;  /* each object/vtable belongs to exactly one domain */
    gpointer    data; /* to store static class data */
    gpointer    type; /* System.Type type for klass */
    guint8     *interface_bitmap;
    guint16     max_interface_id;
    guint8      rank;
    USE_UINT8_BIT_FIELD(guint, remote      : 1); /* class is remotely activated */
    USE_UINT8_BIT_FIELD(guint, initialized : 1); /* cctor has been run */
    USE_UINT8_BIT_FIELD(guint, init_failed : 1); /* cctor execution failed */
    guint32     imt_collisions_bitmap;
    MonoRuntimeGenericContext *runtime_generic_context;
    /* do not add any fields after vtable, the structure is dynamically extended */
    gpointer    vtable[MONO_ZERO_LEN_ARRAY];
};


struct MonoObject {
    MonoVTable *vtable;
    MonoThreadsSync *synchronisation;
};
struct MonoString {
    MonoObject object;
    gint32 length;
    gunichar2 chars[MONO_ZERO_LEN_ARRAY];
};

struct MonoArrayBounds {
    mono_array_size_t length;
    mono_array_lower_bound_t lower_bound;
};

struct MonoArray{
    MonoObject obj;
    /* bounds is NULL for szarrays */
    MonoArrayBounds *bounds;
    /* total number of elements of the array */
    mono_array_size_t max_length;
    unsigned int vector[MONO_ZERO_LEN_ARRAY];
};

struct MonoMethod {
    guint16 flags;  /* method flags */
    guint16 iflags; /* method implementation flags */
    guint32 token;
    MonoClass *klass;
    MonoMethodSignature *signature;
    /* name is useful mostly for debugging */
    const char *name;
    /* this is used by the inlining algorithm */
    unsigned int inline_info : 1;
    unsigned int inline_failure : 1;
    unsigned int wrapper_type : 5;
    unsigned int string_ctor : 1;
    unsigned int save_lmf : 1;
    unsigned int dynamic : 1; /* created & destroyed during runtime */
    unsigned int is_generic : 1; /* whenever this is a generic method definition */
    unsigned int is_inflated : 1; /* whether we're a MonoMethodInflated */
    unsigned int skip_visibility : 1; /* whenever to skip JIT visibility checks */
    unsigned int verification_success : 1; /* whether this method has been verified successfully.*/
    /* TODO we MUST get rid of this field, it's an ugly hack nobody is proud of. */
    unsigned int is_mb_open : 1;		/* This is the fully open instantiation of a generic method_builder. Worse than is_tb_open, but it's temporary */
    signed int slot : 17;

    /*
    * If is_generic is TRUE, the generic_container is stored in image->property_hash,
    * using the key MONO_METHOD_PROP_GENERIC_CONTAINER.
    */
};

typedef void MonoMethodHeader;

struct MonoMethodNormal {
    MonoMethod method;
    MonoMethodHeader *header;
};

struct MonoMethodPInvoke {
    MonoMethod method;
    gpointer addr;
    /* add marshal info */
    guint16 piflags;  /* pinvoke flags */
    guint16 implmap_idx;  /* index into IMPLMAP */
};


struct MonoGenericInst {
    guint id;			/* unique ID for debugging */
    guint type_argc : 22;	/* number of type arguments */
    guint is_open : 1;	/* if this is an open type */
    MonoType *type_argv[MONO_ZERO_LEN_ARRAY];
};

struct MonoGenericContext {
    MonoGenericInst *class_inst;
    MonoGenericInst *method_inst;
};

struct MonoMethodInflated {
    union {
        MonoMethod method;
        MonoMethodNormal normal;
        MonoMethodPInvoke pinvoke;
    } method;
    MonoMethod *declaring;		/* the generic method definition. */
    MonoGenericContext context;	/* The current instantiation */
};

struct MonoImage {
	/*
	 * The number of assemblies which reference this MonoImage though their 'image'
	 * field plus the number of images which reference this MonoImage through their 
	 * 'modules' field, plus the number of threads holding temporary references to
	 * this image between calls of mono_image_open () and mono_image_close ().
	 */
	int   ref_count;

	/* If the raw data was allocated from a source such as mmap, the allocator may store resource tracking information here. */
	void *raw_data_handle;
	char *raw_data;
	guint32 raw_data_len;
	guint8 raw_buffer_used    : 1;
	guint8 raw_data_allocated : 1;
	guint8 fileio_used : 1;

#ifdef HOST_WIN32
	/* Module was loaded using LoadLibrary. */
	guint8 is_module_handle : 1;

	/* Module entry point is _CorDllMain. */
	guint8 has_entry_point : 1;
#endif

	/* Whenever this is a dynamically emitted module */
	guint8 dynamic : 1;

	/* Whenever this is a reflection only image */
	guint8 ref_only : 1;

	/* Whenever this image contains uncompressed metadata */
	guint8 uncompressed_metadata : 1;

	/* Whenever this image contains metadata only without PE data */
	guint8 metadata_only : 1;

	guint8 checked_module_cctor : 1;
	guint8 has_module_cctor : 1;

	guint8 idx_string_wide : 1;
	guint8 idx_guid_wide : 1;
	guint8 idx_blob_wide : 1;

	/* Whenever this image is considered as platform code for the CoreCLR security model */
	guint8 core_clr_platform_code : 1;

	/* The path to the file for this image. */
	char *name;

	/* The assembly name reported in the file for this image (expected to be NULL for a netmodule) */
	const char *assembly_name;

	/* The module name reported in the file for this image (could be NULL for a malformed file) */
	const char *module_name;

	char *version;
	gint16 md_version_major, md_version_minor;
	char *guid;
	void *image_info;
	MonoMemPool         *mempool; /*protected by the image lock*/

	char                *raw_metadata;
			    
	MonoStreamHeader     heap_strings;
	MonoStreamHeader     heap_us;
	MonoStreamHeader     heap_blob;
	MonoStreamHeader     heap_guid;
	MonoStreamHeader     heap_tables;
	MonoStreamHeader     heap_pdb;
			    
	const char          *tables_base;

	/**/
	MonoTableInfo        tables [0x38];

	/*
	 * references is initialized only by using the mono_assembly_open
	 * function, and not by using the lowlevel mono_image_open.
	 *
	 * It is NULL terminated.
	 */
	MonoAssembly **references;
	int nreferences;

	/* Code files in the assembly. */
	MonoImage **modules;
	guint32 module_count;
	gboolean *modules_loaded;

	/*
	 * Files in the assembly. Items are either NULL or alias items in modules, so this does not impact ref_count.
	 * Protected by the image lock.
	 */
	MonoImage **files;

	gpointer aot_module;

	guint8 aotid[16];

	/*
	 * The Assembly this image was loaded from.
	 */
	MonoAssembly *assembly;

	/*
	 * Indexed by method tokens and typedef tokens.
	 */
	GHashTable *method_cache; /*protected by the image lock*/
};

struct MonoClassField {
	/* Type of the field */
	MonoType        *type;

	const char      *name;

	/* Type where the field was defined */
	MonoClass       *parent;

	/*
	 * Offset where this field is stored; if it is an instance
	 * field, it's the offset from the start of the object, if
	 * it's static, it's from the start of the memory chunk
	 * allocated for statics for the class.
	 * For special static fields, this is set to -1 during vtable construction.
	 */
	int              offset;
};
struct MonoGHashTable;
struct GPtrArray;
struct MonoJitInfoTable;
struct MonoThunkFreeList;
struct MonoMemPool;
struct MonoCodeManager;
struct MonoAppDomain;
struct MonoException;
struct MonoAppContext;
struct MonoAppDomainSetup;
struct LockFreeMempool;
typedef void* HANDLE;
typedef void* GHashFunc;
typedef struct _MonoCoopMutex MonoCoopMutex;

struct _MonoCoopMutex {
	mono_mutex_t m;
};
typedef gpointer (*MonoInternalHashKeyExtractFunc) (gpointer value);
typedef gpointer* (*MonoInternalHashNextValueFunc) (gpointer value);
struct MonoInternalHashTable
{
	GHashFunc hash_func;
	MonoInternalHashKeyExtractFunc key_extract;
	MonoInternalHashNextValueFunc next_value;
	gint size;
	gint num_entries;
	gpointer *table;
};

struct MonoDomain {
	/*
	 * This lock must never be taken before the loader lock,
	 * i.e. if both are taken by the same thread, the loader lock
	 * must taken first.
	 */
	MonoCoopMutex    lock;
	MonoMemPool        *mp;
	MonoCodeManager    *code_mp;
	/*
	 * keep all the managed objects close to each other for the precise GC
	 * For the Boehm GC we additionally keep close also other GC-tracked pointers.
	 */
#define MONO_DOMAIN_FIRST_OBJECT setup
	MonoAppDomainSetup *setup;
	MonoAppDomain      *domain;
	MonoAppContext     *default_context;
	MonoException      *out_of_memory_ex;
	MonoException      *null_reference_ex;
	MonoException      *stack_overflow_ex;
	/* typeof (void) */
	MonoObject         *typeof_void;
	/* Ephemeron Tombstone*/
	MonoObject         *ephemeron_tombstone;
	/* new MonoType [0] */
	MonoArray          *empty_types;
	/* 
	 * The fields between FIRST_GC_TRACKED and LAST_GC_TRACKED are roots, but
	 * not object references.
	 */
#define MONO_DOMAIN_FIRST_GC_TRACKED env
	MonoGHashTable     *env;
	MonoGHashTable     *ldstr_table;
	/* hashtables for Reflection handles */
	MonoGHashTable     *type_hash;
	MonoGHashTable     *refobject_hash;
	/*
	 * A GC-tracked array to keep references to the static fields of types.
	 * See note [Domain Static Data Array].
	 */
	gpointer           *static_data_array;
	/* maps class -> type initialization exception object */
	MonoGHashTable    *type_init_exception_hash;
	/* maps delegate trampoline addr -> delegate object */
	MonoGHashTable     *delegate_hash_table;
#define MONO_DOMAIN_LAST_GC_TRACKED delegate_hash_table
	guint32            state;
	/* Needed by Thread:GetDomainID() */
	gint32             domain_id;
	gint32             shadow_serial;
	unsigned char      inet_family_hint; // used in socket-io.c as a cache
	GSList             *domain_assemblies;
	MonoAssembly       *entry_assembly;
	char               *friendly_name;
	GPtrArray          *class_vtable_array;
	/* maps remote class key -> MonoRemoteClass */
	GHashTable         *proxy_vtable_hash;
	/* Protected by 'jit_code_hash_lock' */
	MonoInternalHashTable jit_code_hash;
	mono_mutex_t    jit_code_hash_lock;
	int		    num_jit_info_tables;
	MonoJitInfoTable * 
	  volatile          jit_info_table;
	/*
	 * Contains information about AOT loaded code.
	 * Only used in the root domain.
	 */
	MonoJitInfoTable *
	  volatile          aot_modules;
	GSList		   *jit_info_free_queue;
	/* Used when loading assemblies */
	gchar **search_path;
	gchar *private_bin_path;
	LockFreeMempool *lock_free_mp;
	
	/* Used by remoting proxies */
	MonoMethod         *create_proxy_for_type_method;
	MonoMethod         *private_invoke_method;
	/* Used to store offsets of thread and context static fields */
	GHashTable         *special_static_fields;
	/* 
	 * This must be a GHashTable, since these objects can't be finalized
	 * if the hashtable contains a GC visible reference to them.
	 */
	GHashTable         *finalizable_objects_hash;

	/* Protects the three hashes above */
	mono_mutex_t   finalizable_objects_hash_lock;
	/* Used when accessing 'domain_assemblies' */
	mono_mutex_t    assemblies_lock;

	GHashTable	   *method_rgctx_hash;

	GHashTable	   *generic_virtual_cases;
	MonoThunkFreeList **thunk_free_lists;

	GHashTable     *generic_virtual_thunks;

	/* Information maintained by the JIT engine */
	gpointer runtime_info;

	/*thread pool jobs, used to coordinate shutdown.*/
	volatile int			threadpool_jobs;
	HANDLE				cleanup_semaphore;
	
	/* Contains the compiled runtime invoke wrapper used by finalizers */
	gpointer            finalize_runtime_invoke;

	/* Contains the compiled runtime invoke wrapper used by async resylt creation to capture thread context*/
	gpointer            capture_context_runtime_invoke;

	/* Contains the compiled method used by async resylt creation to capture thread context*/
	gpointer            capture_context_method;

	/* Assembly bindings, the per-domain part */
	GSList *assembly_bindings;
	gboolean assembly_bindings_parsed;

	/* Used by socket-io.c */
	/* These are domain specific, since the assembly can be unloaded */
	MonoImage *socket_assembly;
	MonoClass *sockaddr_class;
	MonoClassField *sockaddr_data_field;
	MonoClassField *sockaddr_data_length_field;

	/* Cache function pointers for architectures  */
	/* that require wrappers */
	GHashTable *ftnptrs_hash;

	/* Maps MonoMethod* to weak links to DynamicMethod objects */
	GHashTable *method_to_dyn_method;

	/* <ThrowUnobservedTaskExceptions /> support */
	gboolean throw_unobserved_task_exceptions;

	guint32 execution_context_field_offset;
};

struct MonoGenericClass {
	MonoClass *container_class;	/* the generic type definition */
	MonoGenericContext context;	/* a context that contains the type instantiation doesn't contain any method instantiation */ /* FIXME: Only the class_inst member of "context" is ever used, so this field could be replaced with just a monogenericinst */
	guint is_dynamic  : 1;		/* Contains dynamic types */
	guint is_tb_open  : 1;		/* This is the fully open instantiation for a type_builder. Quite ugly, but it's temporary.*/
	guint need_sync   : 1;      /* Only if dynamic. Need to be synchronized with its container class after its finished. */
	MonoClass *cached_class;	/* if present, the MonoClass corresponding to the instantiation.  */

	/* 
	 * The image set which owns this generic class. Memory owned by the generic class
	 * including cached_class should be allocated from the mempool of the image set,
	 * so it is easy to free.
	 */
	MonoImageSet *owner;
};

#ifdef __cplusplus
}
#endif

#endif /* MONOMOCKUP_HPP */

