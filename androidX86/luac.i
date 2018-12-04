# 1 "jni/luac/luac.c"
# 1 "C:\\cygwin64\\home\\kwang\\C\\androidX86//"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "jni/luac/luac.c"






# 1 "d:\\android-ndk-r12b\\platforms\\android-9\\arch-x86\\usr\\include\\errno.h" 1 3 4
# 31 "d:\\android-ndk-r12b\\platforms\\android-9\\arch-x86\\usr\\include\\errno.h" 3 4
# 1 "d:\\android-ndk-r12b\\platforms\\android-9\\arch-x86\\usr\\include\\sys\\cdefs.h" 1 3 4
# 77 "d:\\android-ndk-r12b\\platforms\\android-9\\arch-x86\\usr\\include\\sys\\cdefs.h" 3 4
# 1 "d:\\android-ndk-r12b\\platforms\\android-9\\arch-x86\\usr\\include\\sys\\cdefs_elf.h" 1 3 4
# 78 "d:\\android-ndk-r12b\\platforms\\android-9\\arch-x86\\usr\\include\\sys\\cdefs.h" 2 3 4
# 547 "d:\\android-ndk-r12b\\platforms\\android-9\\arch-x86\\usr\\include\\sys\\cdefs.h" 3 4
# 1 "d:\\android-ndk-r12b\\platforms\\android-9\\arch-x86\\usr\\include\\android\\api-level.h" 1 3 4
# 548 "d:\\android-ndk-r12b\\platforms\\android-9\\arch-x86\\usr\\include\\sys\\cdefs.h" 2 3 4
# 32 "d:\\android-ndk-r12b\\platforms\\android-9\\arch-x86\\usr\\include\\errno.h" 2 3 4
# 1 "d:\\android-ndk-r12b\\platforms\\android-9\\arch-x86\\usr\\include\\linux\\errno.h" 1 3 4
# 15 "d:\\android-ndk-r12b\\platforms\\android-9\\arch-x86\\usr\\include\\linux\\errno.h" 3 4
# 1 "d:\\android-ndk-r12b\\platforms\\android-9\\arch-x86\\usr\\include\\asm\\errno.h" 1 3 4
# 19 "d:\\android-ndk-r12b\\platforms\\android-9\\arch-x86\\usr\\include\\asm\\errno.h" 3 4
# 1 "d:\\android-ndk-r12b\\platforms\\android-9\\arch-x86\\usr\\include\\asm-generic\\errno.h" 1 3 4
# 15 "d:\\android-ndk-r12b\\platforms\\android-9\\arch-x86\\usr\\include\\asm-generic\\errno.h" 3 4
# 1 "d:\\android-ndk-r12b\\platforms\\android-9\\arch-x86\\usr\\include\\asm-generic\\errno-base.h" 1 3 4
# 16 "d:\\android-ndk-r12b\\platforms\\android-9\\arch-x86\\usr\\include\\asm-generic\\errno.h" 2 3 4
# 19 "d:\\android-ndk-r12b\\platforms\\android-9\\arch-x86\\usr\\include\\asm\\errno.h" 2 3 4
# 16 "d:\\android-ndk-r12b\\platforms\\android-9\\arch-x86\\usr\\include\\linux\\errno.h" 2 3 4
# 33 "d:\\android-ndk-r12b\\platforms\\android-9\\arch-x86\\usr\\include\\errno.h" 2 3 4


# 44 "d:\\android-ndk-r12b\\platforms\\android-9\\arch-x86\\usr\\include\\errno.h" 3 4
extern volatile int* __errno(void);






static __inline__ int __attribute__((deprecated))
__set_errno(int n) {
  (*__errno()) = n;
  return -1;
}


# 8 "jni/luac/luac.c" 2
# 1 "d:\\android-ndk-r12b\\platforms\\android-9\\arch-x86\\usr\\include\\stdio.h" 1 3 4
# 50 "d:\\android-ndk-r12b\\platforms\\android-9\\arch-x86\\usr\\include\\stdio.h" 3 4
# 1 "d:\\android-ndk-r12b\\platforms\\android-9\\arch-x86\\usr\\include\\sys\\types.h" 1 3 4
# 33 "d:\\android-ndk-r12b\\platforms\\android-9\\arch-x86\\usr\\include\\sys\\types.h" 3 4
# 1 "d:\\android-ndk-r12b\\toolchains\\x86-4.9\\prebuilt\\windows-x86_64\\lib\\gcc\\i686-linux-android\\4.9.x\\include\\stddef.h" 1 3 4
# 147 "d:\\android-ndk-r12b\\toolchains\\x86-4.9\\prebuilt\\windows-x86_64\\lib\\gcc\\i686-linux-android\\4.9.x\\include\\stddef.h" 3 4
typedef int ptrdiff_t;
# 212 "d:\\android-ndk-r12b\\toolchains\\x86-4.9\\prebuilt\\windows-x86_64\\lib\\gcc\\i686-linux-android\\4.9.x\\include\\stddef.h" 3 4
typedef unsigned int size_t;
# 34 "d:\\android-ndk-r12b\\platforms\\android-9\\arch-x86\\usr\\include\\sys\\types.h" 2 3 4
# 1 "d:\\android-ndk-r12b\\platforms\\android-9\\arch-x86\\usr\\include\\stdint.h" 1 3 4
# 31 "d:\\android-ndk-r12b\\platforms\\android-9\\arch-x86\\usr\\include\\stdint.h" 3 4
# 1 "d:\\android-ndk-r12b\\toolchains\\x86-4.9\\prebuilt\\windows-x86_64\\lib\\gcc\\i686-linux-android\\4.9.x\\include\\stddef.h" 1 3 4
# 324 "d:\\android-ndk-r12b\\toolchains\\x86-4.9\\prebuilt\\windows-x86_64\\lib\\gcc\\i686-linux-android\\4.9.x\\include\\stddef.h" 3 4
typedef long int wchar_t;
# 32 "d:\\android-ndk-r12b\\platforms\\android-9\\arch-x86\\usr\\include\\stdint.h" 2 3 4
# 1 "d:\\android-ndk-r12b\\platforms\\android-9\\arch-x86\\usr\\include\\sys\\_types.h" 1 3 4
# 40 "d:\\android-ndk-r12b\\platforms\\android-9\\arch-x86\\usr\\include\\sys\\_types.h" 3 4
# 1 "d:\\android-ndk-r12b\\platforms\\android-9\\arch-x86\\usr\\include\\machine\\_types.h" 1 3 4
# 39 "d:\\android-ndk-r12b\\platforms\\android-9\\arch-x86\\usr\\include\\machine\\_types.h" 3 4
typedef signed char __int8_t;
typedef unsigned char __uint8_t;
typedef short __int16_t;
typedef unsigned short __uint16_t;
typedef int __int32_t;
typedef unsigned int __uint32_t;

typedef long long __int64_t;

typedef unsigned long long __uint64_t;


typedef __int8_t __int_least8_t;
typedef __uint8_t __uint_least8_t;
typedef __int16_t __int_least16_t;
typedef __uint16_t __uint_least16_t;
typedef __int32_t __int_least32_t;
typedef __uint32_t __uint_least32_t;
typedef __int64_t __int_least64_t;
typedef __uint64_t __uint_least64_t;


typedef __int32_t __int_fast8_t;
typedef __uint32_t __uint_fast8_t;
typedef __int32_t __int_fast16_t;
typedef __uint32_t __uint_fast16_t;
typedef __int32_t __int_fast32_t;
typedef __uint32_t __uint_fast32_t;
typedef __int64_t __int_fast64_t;
typedef __uint64_t __uint_fast64_t;


typedef int __intptr_t;
typedef unsigned int __uintptr_t;


typedef __int64_t __intmax_t;
typedef __uint64_t __uintmax_t;


typedef __int32_t __register_t;


typedef unsigned long __vaddr_t;
typedef unsigned long __paddr_t;
typedef unsigned long __vsize_t;
typedef unsigned long __psize_t;


typedef int __clock_t;
typedef int __clockid_t;
typedef long __ptrdiff_t;
typedef int __time_t;
typedef int __timer_t;

typedef __builtin_va_list __va_list;






typedef int __wchar_t;

typedef int __wint_t;
typedef int __rune_t;
typedef void * __wctrans_t;
typedef void * __wctype_t;
# 41 "d:\\android-ndk-r12b\\platforms\\android-9\\arch-x86\\usr\\include\\sys\\_types.h" 2 3 4

typedef unsigned long __cpuid_t;
typedef __int32_t __dev_t;
typedef __uint32_t __fixpt_t;
typedef __uint32_t __gid_t;
typedef __uint32_t __id_t;
typedef __uint32_t __in_addr_t;
typedef __uint16_t __in_port_t;
typedef __uint32_t __ino_t;
typedef long __key_t;
typedef __uint32_t __mode_t;
typedef __uint32_t __nlink_t;
typedef __int32_t __pid_t;
typedef __uint64_t __rlim_t;
typedef __uint16_t __sa_family_t;
typedef __int32_t __segsz_t;
typedef __uint32_t __socklen_t;
typedef __int32_t __swblk_t;
typedef __uint32_t __uid_t;
typedef __uint32_t __useconds_t;
typedef __int32_t __suseconds_t;





typedef union {
 char __mbstate8[128];
 __int64_t __mbstateL;
} __mbstate_t;
# 33 "d:\\android-ndk-r12b\\platforms\\android-9\\arch-x86\\usr\\include\\stdint.h" 2 3 4
# 42 "d:\\android-ndk-r12b\\platforms\\android-9\\arch-x86\\usr\\include\\stdint.h" 3 4
typedef __int8_t int8_t;
typedef __uint8_t uint8_t;
typedef __int16_t int16_t;
typedef __uint16_t uint16_t;
typedef __int32_t int32_t;
typedef __uint32_t uint32_t;
typedef __int64_t int64_t;
typedef __uint64_t uint64_t;





typedef int8_t int_least8_t;
typedef int8_t int_fast8_t;

typedef uint8_t uint_least8_t;
typedef uint8_t uint_fast8_t;
# 88 "d:\\android-ndk-r12b\\platforms\\android-9\\arch-x86\\usr\\include\\stdint.h" 3 4
typedef int16_t int_least16_t;
typedef int32_t int_fast16_t;

typedef uint16_t uint_least16_t;
typedef uint32_t uint_fast16_t;
# 121 "d:\\android-ndk-r12b\\platforms\\android-9\\arch-x86\\usr\\include\\stdint.h" 3 4
typedef int32_t int_least32_t;
typedef int32_t int_fast32_t;

typedef uint32_t uint_least32_t;
typedef uint32_t uint_fast32_t;
# 154 "d:\\android-ndk-r12b\\platforms\\android-9\\arch-x86\\usr\\include\\stdint.h" 3 4
typedef int64_t int_least64_t;
typedef int64_t int_fast64_t;

typedef uint64_t uint_least64_t;
typedef uint64_t uint_fast64_t;
# 198 "d:\\android-ndk-r12b\\platforms\\android-9\\arch-x86\\usr\\include\\stdint.h" 3 4
typedef int intptr_t;
typedef unsigned int uintptr_t;
# 220 "d:\\android-ndk-r12b\\platforms\\android-9\\arch-x86\\usr\\include\\stdint.h" 3 4
typedef uint64_t uintmax_t;
typedef int64_t intmax_t;
# 242 "d:\\android-ndk-r12b\\platforms\\android-9\\arch-x86\\usr\\include\\stdint.h" 3 4
# 1 "d:\\android-ndk-r12b\\platforms\\android-9\\arch-x86\\usr\\include\\sys\\_wchar_limits.h" 1 3 4
# 243 "d:\\android-ndk-r12b\\platforms\\android-9\\arch-x86\\usr\\include\\stdint.h" 2 3 4
# 254 "d:\\android-ndk-r12b\\platforms\\android-9\\arch-x86\\usr\\include\\stdint.h" 3 4
typedef int ssize_t;
# 35 "d:\\android-ndk-r12b\\platforms\\android-9\\arch-x86\\usr\\include\\sys\\types.h" 2 3 4


# 1 "d:\\android-ndk-r12b\\platforms\\android-9\\arch-x86\\usr\\include\\linux\\posix_types.h" 1 3 4
# 15 "d:\\android-ndk-r12b\\platforms\\android-9\\arch-x86\\usr\\include\\linux\\posix_types.h" 3 4
# 1 "d:\\android-ndk-r12b\\platforms\\android-9\\arch-x86\\usr\\include\\linux\\stddef.h" 1 3 4
# 21 "d:\\android-ndk-r12b\\platforms\\android-9\\arch-x86\\usr\\include\\linux\\stddef.h" 3 4
# 1 "d:\\android-ndk-r12b\\platforms\\android-9\\arch-x86\\usr\\include\\linux\\compiler.h" 1 3 4
# 22 "d:\\android-ndk-r12b\\platforms\\android-9\\arch-x86\\usr\\include\\linux\\stddef.h" 2 3 4
# 16 "d:\\android-ndk-r12b\\platforms\\android-9\\arch-x86\\usr\\include\\linux\\posix_types.h" 2 3 4
# 32 "d:\\android-ndk-r12b\\platforms\\android-9\\arch-x86\\usr\\include\\linux\\posix_types.h" 3 4
typedef struct {
 unsigned long fds_bits [(1024/(8 * sizeof(unsigned long)))];
} __kernel_fd_set;

typedef void (*__kernel_sighandler_t)(int);

typedef int __kernel_key_t;
typedef int __kernel_mqd_t;

# 1 "d:\\android-ndk-r12b\\platforms\\android-9\\arch-x86\\usr\\include\\asm\\posix_types.h" 1 3 4
# 19 "d:\\android-ndk-r12b\\platforms\\android-9\\arch-x86\\usr\\include\\asm\\posix_types.h" 3 4
# 1 "d:\\android-ndk-r12b\\platforms\\android-9\\arch-x86\\usr\\include\\asm\\posix_types_32.h" 1 3 4
# 21 "d:\\android-ndk-r12b\\platforms\\android-9\\arch-x86\\usr\\include\\asm\\posix_types_32.h" 3 4
typedef unsigned long __kernel_ino_t;
typedef unsigned short __kernel_mode_t;

typedef unsigned short __kernel_nlink_t;
typedef long __kernel_off_t;
typedef int __kernel_pid_t;
typedef unsigned short __kernel_ipc_pid_t;

typedef unsigned short __kernel_uid_t;
typedef unsigned short __kernel_gid_t;
typedef unsigned int __kernel_size_t;
typedef int __kernel_ssize_t;

typedef int __kernel_ptrdiff_t;
typedef long __kernel_time_t;
typedef long __kernel_suseconds_t;
typedef long __kernel_clock_t;

typedef int __kernel_timer_t;
typedef int __kernel_clockid_t;
typedef int __kernel_daddr_t;
typedef char * __kernel_caddr_t;

typedef unsigned short __kernel_uid16_t;
typedef unsigned short __kernel_gid16_t;
typedef unsigned int __kernel_uid32_t;
typedef unsigned int __kernel_gid32_t;

typedef unsigned short __kernel_old_uid_t;
typedef unsigned short __kernel_old_gid_t;
typedef unsigned short __kernel_old_dev_t;


typedef long long __kernel_loff_t;

typedef struct {




 int __val[2];


} __kernel_fsid_t;
# 19 "d:\\android-ndk-r12b\\platforms\\android-9\\arch-x86\\usr\\include\\asm\\posix_types.h" 2 3 4
# 42 "d:\\android-ndk-r12b\\platforms\\android-9\\arch-x86\\usr\\include\\linux\\posix_types.h" 2 3 4
# 38 "d:\\android-ndk-r12b\\platforms\\android-9\\arch-x86\\usr\\include\\sys\\types.h" 2 3 4
# 1 "d:\\android-ndk-r12b\\platforms\\android-9\\arch-x86\\usr\\include\\asm\\types.h" 1 3 4
# 22 "d:\\android-ndk-r12b\\platforms\\android-9\\arch-x86\\usr\\include\\asm\\types.h" 3 4
typedef unsigned short umode_t;

typedef __signed__ char __s8;
typedef unsigned char __u8;
typedef __signed__ short __s16;
typedef unsigned short __u16;

typedef __signed__ int __s32;
typedef unsigned int __u32;

__extension__ typedef __signed__ long long __s64;

__extension__ typedef unsigned long long __u64;
# 39 "d:\\android-ndk-r12b\\platforms\\android-9\\arch-x86\\usr\\include\\sys\\types.h" 2 3 4
# 1 "d:\\android-ndk-r12b\\platforms\\android-9\\arch-x86\\usr\\include\\linux\\types.h" 1 3 4
# 21 "d:\\android-ndk-r12b\\platforms\\android-9\\arch-x86\\usr\\include\\linux\\types.h" 3 4
typedef __u16 __le16;
typedef __u16 __be16;
typedef __u32 __le32;
typedef __u32 __be32;

typedef __u64 __le64;
typedef __u64 __be64;


struct ustat {
 __kernel_daddr_t f_tfree;
 __kernel_ino_t f_tinode;
 char f_fname[6];
 char f_fpack[6];
};
# 40 "d:\\android-ndk-r12b\\platforms\\android-9\\arch-x86\\usr\\include\\sys\\types.h" 2 3 4
# 1 "d:\\android-ndk-r12b\\platforms\\android-9\\arch-x86\\usr\\include\\machine\\kernel.h" 1 3 4
# 33 "d:\\android-ndk-r12b\\platforms\\android-9\\arch-x86\\usr\\include\\machine\\kernel.h" 3 4
typedef unsigned long __kernel_blkcnt_t;
typedef unsigned long __kernel_blksize_t;


typedef unsigned long __kernel_fsblkcnt_t;
typedef unsigned long __kernel_fsfilcnt_t;
typedef unsigned int __kernel_id_t;
# 41 "d:\\android-ndk-r12b\\platforms\\android-9\\arch-x86\\usr\\include\\sys\\types.h" 2 3 4

typedef __u32 __kernel_dev_t;
# 52 "d:\\android-ndk-r12b\\platforms\\android-9\\arch-x86\\usr\\include\\sys\\types.h" 3 4
typedef __kernel_blkcnt_t blkcnt_t;
typedef __kernel_blksize_t blksize_t;
typedef __kernel_clock_t clock_t;
typedef __kernel_clockid_t clockid_t;
typedef __kernel_dev_t dev_t;
typedef __kernel_fsblkcnt_t fsblkcnt_t;
typedef __kernel_fsfilcnt_t fsfilcnt_t;
typedef __kernel_gid32_t gid_t;
typedef __kernel_id_t id_t;
typedef __kernel_ino_t ino_t;
typedef __kernel_key_t key_t;
typedef __kernel_mode_t mode_t;
typedef __kernel_nlink_t nlink_t;


typedef __kernel_off_t off_t;

typedef __kernel_loff_t loff_t;
typedef loff_t off64_t;

typedef __kernel_pid_t pid_t;
# 93 "d:\\android-ndk-r12b\\platforms\\android-9\\arch-x86\\usr\\include\\sys\\types.h" 3 4
typedef __kernel_suseconds_t suseconds_t;
typedef __kernel_time_t time_t;
typedef __kernel_uid32_t uid_t;
typedef signed long useconds_t;

typedef __kernel_daddr_t daddr_t;
typedef __kernel_timer_t timer_t;
typedef __kernel_mqd_t mqd_t;

typedef __kernel_caddr_t caddr_t;
typedef unsigned int uint_t;
typedef unsigned int uint;


# 1 "d:\\android-ndk-r12b\\platforms\\android-9\\arch-x86\\usr\\include\\sys\\sysmacros.h" 1 3 4
# 36 "d:\\android-ndk-r12b\\platforms\\android-9\\arch-x86\\usr\\include\\sys\\sysmacros.h" 3 4
static __inline__ int major(dev_t _dev)
{
  return (_dev >> 8) & 0xfff;
}

static __inline__ int minor(dev_t _dev)
{
  return (_dev & 0xff) | ((_dev >> 12) & 0xfff00);
}

static __inline__ dev_t makedev(int __ma, int __mi)
{
  return ((__ma & 0xfff) << 8) | (__mi & 0xff) | ((__mi & 0xfff00) << 12);
}
# 108 "d:\\android-ndk-r12b\\platforms\\android-9\\arch-x86\\usr\\include\\sys\\types.h" 2 3 4


typedef unsigned char u_char;
typedef unsigned short u_short;
typedef unsigned int u_int;
typedef unsigned long u_long;

typedef uint32_t u_int32_t;
typedef uint16_t u_int16_t;
typedef uint8_t u_int8_t;
typedef uint64_t u_int64_t;
# 51 "d:\\android-ndk-r12b\\platforms\\android-9\\arch-x86\\usr\\include\\stdio.h" 2 3 4



# 1 "d:\\android-ndk-r12b\\toolchains\\x86-4.9\\prebuilt\\windows-x86_64\\lib\\gcc\\i686-linux-android\\4.9.x\\include\\stdarg.h" 1 3 4
# 40 "d:\\android-ndk-r12b\\toolchains\\x86-4.9\\prebuilt\\windows-x86_64\\lib\\gcc\\i686-linux-android\\4.9.x\\include\\stdarg.h" 3 4
typedef __builtin_va_list __gnuc_va_list;
# 55 "d:\\android-ndk-r12b\\platforms\\android-9\\arch-x86\\usr\\include\\stdio.h" 2 3 4



# 1 "d:\\android-ndk-r12b\\toolchains\\x86-4.9\\prebuilt\\windows-x86_64\\lib\\gcc\\i686-linux-android\\4.9.x\\include\\stddef.h" 1 3 4
# 59 "d:\\android-ndk-r12b\\platforms\\android-9\\arch-x86\\usr\\include\\stdio.h" 2 3 4


# 1 "d:\\android-ndk-r12b\\toolchains\\x86-4.9\\prebuilt\\windows-x86_64\\lib\\gcc\\i686-linux-android\\4.9.x\\include\\stddef.h" 1 3 4
# 62 "d:\\android-ndk-r12b\\platforms\\android-9\\arch-x86\\usr\\include\\stdio.h" 2 3 4



typedef off_t fpos_t;
# 74 "d:\\android-ndk-r12b\\platforms\\android-9\\arch-x86\\usr\\include\\stdio.h" 3 4
struct __sbuf {
 unsigned char *_base;
 int _size;
};
# 106 "d:\\android-ndk-r12b\\platforms\\android-9\\arch-x86\\usr\\include\\stdio.h" 3 4
typedef struct __sFILE {
 unsigned char *_p;
 int _r;
 int _w;
 short _flags;
 short _file;
 struct __sbuf _bf;
 int _lbfsize;


 void *_cookie;
 int (*_close)(void *);
 int (*_read)(void *, char *, int);
 fpos_t (*_seek)(void *, fpos_t, int);
 int (*_write)(void *, const char *, int);


 struct __sbuf _ext;

 unsigned char *_up;
 int _ur;


 unsigned char _ubuf[3];
 unsigned char _nbuf[1];


 struct __sbuf _lb;


 int _blksize;
 fpos_t _offset;
} FILE;


extern FILE __sF[];

# 210 "d:\\android-ndk-r12b\\platforms\\android-9\\arch-x86\\usr\\include\\stdio.h" 3 4

void clearerr(FILE *);
int fclose(FILE *);
int feof(FILE *);
int ferror(FILE *);
int fflush(FILE *);
int fgetc(FILE *);
int fgetpos(FILE *, fpos_t *);
char *fgets(char *, int, FILE *);
FILE *fopen(const char *, const char *);
int fprintf(FILE *, const char *, ...);
int fputc(int, FILE *);
int fputs(const char *, FILE *);
size_t fread(void *, size_t, size_t, FILE *);
FILE *freopen(const char *, const char *, FILE *);
int fscanf(FILE *, const char *, ...);
int fseek(FILE *, long, int);
int fseeko(FILE *, off_t, int);
int fsetpos(FILE *, const fpos_t *);
long ftell(FILE *);
off_t ftello(FILE *);
size_t fwrite(const void *, size_t, size_t, FILE *);
int getc(FILE *);
int getchar(void);
char *gets(char *);



extern int sys_nerr;
extern char *sys_errlist[];

void perror(const char *);
int printf(const char *, ...);
int putc(int, FILE *);
int putchar(int);
int puts(const char *);
int remove(const char *);
int rename(const char *, const char *);
void rewind(FILE *);
int scanf(const char *, ...);
void setbuf(FILE *, char *);
int setvbuf(FILE *, char *, int, size_t);
int sprintf(char *, const char *, ...);
int sscanf(const char *, const char *, ...);
FILE *tmpfile(void);
char *tmpnam(char *);
int ungetc(int, FILE *);
int vfprintf(FILE *, const char *, __va_list);
int vprintf(const char *, __va_list);
int vsprintf(char *, const char *, __va_list);


int snprintf(char *, size_t, const char *, ...)
  __attribute__((__format__ (printf, 3, 4)))
  __attribute__((__nonnull__ (3)));
int vfscanf(FILE *, const char *, __va_list)
  __attribute__((__format__ (scanf, 2, 0)))
  __attribute__((__nonnull__ (2)));
int vscanf(const char *, __va_list)
  __attribute__((__format__ (scanf, 1, 0)))
  __attribute__((__nonnull__ (1)));
int vsnprintf(char *, size_t, const char *, __va_list)
  __attribute__((__format__ (printf, 3, 0)))
  __attribute__((__nonnull__ (3)));
int vsscanf(const char *, const char *, __va_list)
  __attribute__((__format__ (scanf, 2, 0)))
  __attribute__((__nonnull__ (2)));



# 289 "d:\\android-ndk-r12b\\platforms\\android-9\\arch-x86\\usr\\include\\stdio.h" 3 4





FILE *fdopen(int, const char *);
int fileno(FILE *);


int pclose(FILE *);
FILE *popen(const char *, const char *);



void flockfile(FILE *);
int ftrylockfile(FILE *);
void funlockfile(FILE *);





int getc_unlocked(FILE *);
int getchar_unlocked(void);
int putc_unlocked(int, FILE *);
int putchar_unlocked(int);



char *tempnam(const char *, const char *);










int asprintf(char **, const char *, ...)
  __attribute__((__format__ (printf, 2, 3)))
  __attribute__((__nonnull__ (2)));
char *fgetln(FILE *, size_t *);
int fpurge(FILE *);
int getw(FILE *);
int putw(int, FILE *);
void setbuffer(FILE *, char *, int);
int setlinebuf(FILE *);
int vasprintf(char **, const char *, __va_list)
  __attribute__((__format__ (printf, 2, 0)))
  __attribute__((__nonnull__ (2)));






FILE *funopen(const void *,
  int (*)(void *, char *, int),
  int (*)(void *, const char *, int),
  fpos_t (*)(void *, fpos_t, int),
  int (*)(void *));

# 9 "jni/luac/luac.c" 2
# 1 "d:\\android-ndk-r12b\\platforms\\android-9\\arch-x86\\usr\\include\\stdlib.h" 1 3 4
# 37 "d:\\android-ndk-r12b\\platforms\\android-9\\arch-x86\\usr\\include\\stdlib.h" 3 4
# 1 "d:\\android-ndk-r12b\\toolchains\\x86-4.9\\prebuilt\\windows-x86_64\\lib\\gcc\\i686-linux-android\\4.9.x\\include\\stddef.h" 1 3 4
# 38 "d:\\android-ndk-r12b\\platforms\\android-9\\arch-x86\\usr\\include\\stdlib.h" 2 3 4

# 1 "d:\\android-ndk-r12b\\toolchains\\x86-4.9\\prebuilt\\windows-x86_64\\lib\\gcc\\i686-linux-android\\4.9.x\\include\\stddef.h" 1 3 4
# 40 "d:\\android-ndk-r12b\\platforms\\android-9\\arch-x86\\usr\\include\\stdlib.h" 2 3 4
# 1 "d:\\android-ndk-r12b\\platforms\\android-9\\arch-x86\\usr\\include\\string.h" 1 3 4
# 32 "d:\\android-ndk-r12b\\platforms\\android-9\\arch-x86\\usr\\include\\string.h" 3 4
# 1 "d:\\android-ndk-r12b\\toolchains\\x86-4.9\\prebuilt\\windows-x86_64\\lib\\gcc\\i686-linux-android\\4.9.x\\include\\stddef.h" 1 3 4
# 33 "d:\\android-ndk-r12b\\platforms\\android-9\\arch-x86\\usr\\include\\string.h" 2 3 4
# 1 "d:\\android-ndk-r12b\\platforms\\android-9\\arch-x86\\usr\\include\\malloc.h" 1 3 4
# 26 "d:\\android-ndk-r12b\\platforms\\android-9\\arch-x86\\usr\\include\\malloc.h" 3 4
# 1 "d:\\android-ndk-r12b\\toolchains\\x86-4.9\\prebuilt\\windows-x86_64\\lib\\gcc\\i686-linux-android\\4.9.x\\include\\stddef.h" 1 3 4
# 27 "d:\\android-ndk-r12b\\platforms\\android-9\\arch-x86\\usr\\include\\malloc.h" 2 3 4



extern __attribute__((malloc)) void* malloc(size_t);
extern __attribute__((malloc)) void* calloc(size_t, size_t);
extern void* realloc(void *, size_t);
extern void free(void *);

extern void* memalign(size_t alignment, size_t bytesize);
extern size_t malloc_usable_size(const void*);

extern void* valloc(size_t bytesize);
extern void* pvalloc(size_t bytesize);



struct mallinfo {
  size_t arena;
  size_t ordblks;
  size_t smblks;
  size_t hblks;
  size_t hblkhd;
  size_t usmblks;
  size_t fsmblks;
  size_t uordblks;
  size_t fordblks;
  size_t keepcost;
};


extern struct mallinfo mallinfo(void);


# 34 "d:\\android-ndk-r12b\\platforms\\android-9\\arch-x86\\usr\\include\\string.h" 2 3 4



extern void* memccpy(void *, const void *, int, size_t);
extern void* memchr(const void *, int, size_t);
extern void* memrchr(const void *, int, size_t);
extern int memcmp(const void *, const void *, size_t);
extern void* memcpy(void *, const void *, size_t);
extern void* memmove(void *, const void *, size_t);
extern void* memset(void *, int, size_t);
extern void* memmem(const void *, size_t, const void *, size_t);
extern void memswap(void *, void *, size_t);

extern char* index(const char *, int);
extern char* rindex(const char *, int);
extern char* strchr(const char *, int);
extern char* strrchr(const char *, int);

extern size_t strlen(const char *);
extern int strcmp(const char *, const char *);
extern char* strcpy(char *, const char *);
extern char* strcat(char *, const char *);

extern int strcasecmp(const char *, const char *);
extern int strncasecmp(const char *, const char *, size_t);
extern char* strdup(const char *);

extern char* strstr(const char *, const char *);
extern char* strcasestr(const char *haystack, const char *needle);
extern char* strtok(char *, const char *);
extern char* strtok_r(char *, const char *, char**);

extern char* strerror(int);
extern int strerror_r(int errnum, char *buf, size_t n);

extern size_t strnlen(const char *, size_t);
extern char* strncat(char *, const char *, size_t);
extern char* strndup(const char *, size_t);
extern int strncmp(const char *, const char *, size_t);
extern char* strncpy(char *, const char *, size_t);

extern size_t strlcat(char *, const char *, size_t);
extern size_t strlcpy(char *, const char *, size_t);

extern size_t strcspn(const char *, const char *);
extern char* strpbrk(const char *, const char *);
extern char* strsep(char **, const char *);
extern size_t strspn(const char *, const char *);

extern char* strsignal(int sig);

extern int strcoll(const char *, const char *);
extern size_t strxfrm(char *, const char *, size_t);


# 41 "d:\\android-ndk-r12b\\platforms\\android-9\\arch-x86\\usr\\include\\stdlib.h" 2 3 4
# 1 "d:\\android-ndk-r12b\\platforms\\android-9\\arch-x86\\usr\\include\\alloca.h" 1 3 4
# 42 "d:\\android-ndk-r12b\\platforms\\android-9\\arch-x86\\usr\\include\\stdlib.h" 2 3 4
# 1 "d:\\android-ndk-r12b\\platforms\\android-9\\arch-x86\\usr\\include\\strings.h" 1 3 4
# 45 "d:\\android-ndk-r12b\\platforms\\android-9\\arch-x86\\usr\\include\\strings.h" 3 4




int bcmp(const void *, const void *, size_t);
int ffs(int);
int strcasecmp(const char *, const char *);
int strncasecmp(const char *, const char *, size_t);

# 43 "d:\\android-ndk-r12b\\platforms\\android-9\\arch-x86\\usr\\include\\stdlib.h" 2 3 4
# 1 "d:\\android-ndk-r12b\\platforms\\android-9\\arch-x86\\usr\\include\\memory.h" 1 3 4
# 44 "d:\\android-ndk-r12b\\platforms\\android-9\\arch-x86\\usr\\include\\stdlib.h" 2 3 4






extern __attribute__((__noreturn__)) void exit(int);
extern __attribute__((__noreturn__)) void abort(void);
extern int atexit(void (*)(void));

extern char *getenv(const char *);
extern int putenv(const char *);
extern int setenv(const char *, const char *, int);
extern int unsetenv(const char *);
extern int clearenv(void);

extern char *mkdtemp(char *);
extern char *mktemp (char *);
extern int mkstemp (char *);

extern long strtol(const char *, char **, int);
extern long long strtoll(const char *, char **, int);
extern unsigned long strtoul(const char *, char **, int);
extern unsigned long long strtoull(const char *, char **, int);
extern double strtod(const char *nptr, char **endptr) ;


static __inline__ float strtof(const char *nptr, char **endptr)
{
    return (float)strtod(nptr, endptr);
}

extern int atoi(const char *);
extern long atol(const char *);
extern long long atoll(const char *);


static __inline__ double atof(const char *nptr)
{
    return (strtod(nptr, ((void *)0)));
}

static __inline__ int abs(int __n) {
    return (__n < 0) ? -__n : __n;
}

static __inline__ long labs(long __n) {
    return (__n < 0L) ? -__n : __n;
}

static __inline__ long long llabs(long long __n) {
    return (__n < 0LL) ? -__n : __n;
}

extern char * realpath(const char *path, char *resolved);
extern int system(const char * string);

extern void * bsearch(const void *key, const void *base0,
 size_t nmemb, size_t size,
 int (*compar)(const void *, const void *));

extern void qsort(void *, size_t, size_t, int (*)(const void *, const void *));

extern long jrand48(unsigned short *);
extern long mrand48(void);
extern long nrand48(unsigned short *);
extern long lrand48(void);
extern unsigned short *seed48(unsigned short*);
extern double erand48(unsigned short xsubi[3]) ;
extern double drand48(void) ;
extern void srand48(long);
extern unsigned int arc4random(void);
extern void arc4random_stir(void);
extern void arc4random_addrandom(unsigned char *, int);


static __inline__ int rand(void) {
    return (int)lrand48();
}
static __inline__ void srand(unsigned int __s) {
    srand48(__s);
}
static __inline__ long random(void)
{
    return lrand48();
}
static __inline__ void srandom(unsigned int __s)
{
    srand48(__s);
}



extern int unlockpt(int);
extern char* ptsname(int);
extern int ptsname_r(int, char*, size_t);
extern int getpt(void);

static __inline__ int grantpt(int __fd __attribute((unused)))
{
  (void)__fd;
  return 0;
}

typedef struct {
    int quot;
    int rem;
} div_t;

extern div_t div(int, int);

typedef struct {
    long int quot;
    long int rem;
} ldiv_t;

extern ldiv_t ldiv(long, long);

typedef struct {
    long long int quot;
    long long int rem;
} lldiv_t;

extern lldiv_t lldiv(long long, long long);



extern int mblen(const char *, size_t);
extern size_t mbstowcs(wchar_t *, const char *, size_t);
extern int mbtowc(wchar_t *, const char *, size_t);


extern int wctomb(char *, wchar_t);
extern size_t wcstombs(char *, const wchar_t *, size_t);
# 186 "d:\\android-ndk-r12b\\platforms\\android-9\\arch-x86\\usr\\include\\stdlib.h" 3 4

# 10 "jni/luac/luac.c" 2





# 1 "jni/luac/lua.h" 1
# 12 "jni/luac/lua.h"
# 1 "d:\\android-ndk-r12b\\toolchains\\x86-4.9\\prebuilt\\windows-x86_64\\lib\\gcc\\i686-linux-android\\4.9.x\\include\\stdarg.h" 1 3 4
# 98 "d:\\android-ndk-r12b\\toolchains\\x86-4.9\\prebuilt\\windows-x86_64\\lib\\gcc\\i686-linux-android\\4.9.x\\include\\stdarg.h" 3 4
typedef __gnuc_va_list va_list;
# 13 "jni/luac/lua.h" 2
# 1 "d:\\android-ndk-r12b\\toolchains\\x86-4.9\\prebuilt\\windows-x86_64\\lib\\gcc\\i686-linux-android\\4.9.x\\include\\stddef.h" 1 3 4
# 14 "jni/luac/lua.h" 2


# 1 "jni/luac/luaconf.h" 1
# 11 "jni/luac/luaconf.h"
# 1 "d:\\android-ndk-r12b\\platforms\\android-9\\arch-x86\\usr\\include\\limits.h" 1 3 4
# 86 "d:\\android-ndk-r12b\\platforms\\android-9\\arch-x86\\usr\\include\\limits.h" 3 4
# 1 "d:\\android-ndk-r12b\\platforms\\android-9\\arch-x86\\usr\\include\\sys\\limits.h" 1 3 4
# 30 "d:\\android-ndk-r12b\\platforms\\android-9\\arch-x86\\usr\\include\\sys\\limits.h" 3 4
# 1 "d:\\android-ndk-r12b\\platforms\\android-9\\arch-x86\\usr\\include\\linux\\limits.h" 1 3 4
# 31 "d:\\android-ndk-r12b\\platforms\\android-9\\arch-x86\\usr\\include\\sys\\limits.h" 2 3 4
# 44 "d:\\android-ndk-r12b\\platforms\\android-9\\arch-x86\\usr\\include\\sys\\limits.h" 3 4
# 1 "d:\\android-ndk-r12b\\platforms\\android-9\\arch-x86\\usr\\include\\machine\\internal_types.h" 1 3 4
# 45 "d:\\android-ndk-r12b\\platforms\\android-9\\arch-x86\\usr\\include\\sys\\limits.h" 2 3 4


# 1 "d:\\android-ndk-r12b\\platforms\\android-9\\arch-x86\\usr\\include\\machine\\limits.h" 1 3 4
# 48 "d:\\android-ndk-r12b\\platforms\\android-9\\arch-x86\\usr\\include\\sys\\limits.h" 2 3 4
# 87 "d:\\android-ndk-r12b\\platforms\\android-9\\arch-x86\\usr\\include\\limits.h" 2 3 4


# 1 "d:\\android-ndk-r12b\\platforms\\android-9\\arch-x86\\usr\\include\\sys\\syslimits.h" 1 3 4
# 90 "d:\\android-ndk-r12b\\platforms\\android-9\\arch-x86\\usr\\include\\limits.h" 2 3 4
# 109 "d:\\android-ndk-r12b\\platforms\\android-9\\arch-x86\\usr\\include\\limits.h" 3 4
# 1 "d:\\android-ndk-r12b\\platforms\\android-9\\arch-x86\\usr\\include\\asm\\page.h" 1 3 4
# 19 "d:\\android-ndk-r12b\\platforms\\android-9\\arch-x86\\usr\\include\\asm\\page.h" 3 4
# 1 "d:\\android-ndk-r12b\\platforms\\android-9\\arch-x86\\usr\\include\\asm\\page_32.h" 1 3 4
# 19 "d:\\android-ndk-r12b\\platforms\\android-9\\arch-x86\\usr\\include\\asm\\page.h" 2 3 4
# 110 "d:\\android-ndk-r12b\\platforms\\android-9\\arch-x86\\usr\\include\\limits.h" 2 3 4
# 12 "jni/luac/luaconf.h" 2
# 1 "d:\\android-ndk-r12b\\toolchains\\x86-4.9\\prebuilt\\windows-x86_64\\lib\\gcc\\i686-linux-android\\4.9.x\\include\\stddef.h" 1 3 4
# 13 "jni/luac/luaconf.h" 2
# 17 "jni/luac/lua.h" 2
# 54 "jni/luac/lua.h"
typedef struct lua_State lua_State;

typedef int (*lua_CFunction) (lua_State *L);





typedef const char * (*lua_Reader) (lua_State *L, void *ud, size_t *sz);

typedef int (*lua_Writer) (lua_State *L, const void* p, size_t sz, void* ud);





typedef void * (*lua_Alloc) (void *ud, void *ptr, size_t osize, size_t nsize);
# 103 "jni/luac/lua.h"
typedef double lua_Number;



typedef ptrdiff_t lua_Integer;


typedef unsigned int lua_Unsigned;
# 125 "jni/luac/lua.h"
extern const char lua_ident[];





extern lua_State *(lua_newstate) (lua_Alloc f, void *ud);
extern void (lua_close) (lua_State *L);
extern lua_State *(lua_newthread) (lua_State *L);

extern lua_CFunction (lua_atpanic) (lua_State *L, lua_CFunction panicf);


extern const lua_Number *(lua_version) (lua_State *L);





extern int (lua_absindex) (lua_State *L, int idx);
extern int (lua_gettop) (lua_State *L);
extern void (lua_settop) (lua_State *L, int idx);
extern void (lua_pushvalue) (lua_State *L, int idx);
extern void (lua_remove) (lua_State *L, int idx);
extern void (lua_insert) (lua_State *L, int idx);
extern void (lua_replace) (lua_State *L, int idx);
extern void (lua_copy) (lua_State *L, int fromidx, int toidx);
extern int (lua_checkstack) (lua_State *L, int sz);

extern void (lua_xmove) (lua_State *from, lua_State *to, int n);






extern int (lua_isnumber) (lua_State *L, int idx);
extern int (lua_isstring) (lua_State *L, int idx);
extern int (lua_iscfunction) (lua_State *L, int idx);
extern int (lua_isuserdata) (lua_State *L, int idx);
extern int (lua_type) (lua_State *L, int idx);
extern const char *(lua_typename) (lua_State *L, int tp);

extern lua_Number (lua_tonumberx) (lua_State *L, int idx, int *isnum);
extern lua_Integer (lua_tointegerx) (lua_State *L, int idx, int *isnum);
extern lua_Unsigned (lua_tounsignedx) (lua_State *L, int idx, int *isnum);
extern int (lua_toboolean) (lua_State *L, int idx);
extern const char *(lua_tolstring) (lua_State *L, int idx, size_t *len);
extern size_t (lua_rawlen) (lua_State *L, int idx);
extern lua_CFunction (lua_tocfunction) (lua_State *L, int idx);
extern void *(lua_touserdata) (lua_State *L, int idx);
extern lua_State *(lua_tothread) (lua_State *L, int idx);
extern const void *(lua_topointer) (lua_State *L, int idx);
# 192 "jni/luac/lua.h"
extern void (lua_arith) (lua_State *L, int op);





extern int (lua_rawequal) (lua_State *L, int idx1, int idx2);
extern int (lua_compare) (lua_State *L, int idx1, int idx2, int op);





extern void (lua_pushnil) (lua_State *L);
extern void (lua_pushnumber) (lua_State *L, lua_Number n);
extern void (lua_pushinteger) (lua_State *L, lua_Integer n);
extern void (lua_pushunsigned) (lua_State *L, lua_Unsigned n);
extern const char *(lua_pushlstring) (lua_State *L, const char *s, size_t l);
extern const char *(lua_pushstring) (lua_State *L, const char *s);
extern const char *(lua_pushvfstring) (lua_State *L, const char *fmt,
                                                      va_list argp);
extern const char *(lua_pushfstring) (lua_State *L, const char *fmt, ...);
extern void (lua_pushcclosure) (lua_State *L, lua_CFunction fn, int n);
extern void (lua_pushboolean) (lua_State *L, int b);
extern void (lua_pushlightuserdata) (lua_State *L, void *p);
extern int (lua_pushthread) (lua_State *L);





extern void (lua_getglobal) (lua_State *L, const char *var);
extern void (lua_gettable) (lua_State *L, int idx);
extern void (lua_getfield) (lua_State *L, int idx, const char *k);
extern void (lua_rawget) (lua_State *L, int idx);
extern void (lua_rawgeti) (lua_State *L, int idx, int n);
extern void (lua_rawgetp) (lua_State *L, int idx, const void *p);
extern void (lua_createtable) (lua_State *L, int narr, int nrec);
extern void *(lua_newuserdata) (lua_State *L, size_t sz);
extern int (lua_getmetatable) (lua_State *L, int objindex);
extern void (lua_getuservalue) (lua_State *L, int idx);





extern void (lua_setglobal) (lua_State *L, const char *var);
extern void (lua_settable) (lua_State *L, int idx);
extern void (lua_setfield) (lua_State *L, int idx, const char *k);
extern void (lua_rawset) (lua_State *L, int idx);
extern void (lua_rawseti) (lua_State *L, int idx, int n);
extern void (lua_rawsetp) (lua_State *L, int idx, const void *p);
extern int (lua_setmetatable) (lua_State *L, int objindex);
extern void (lua_setuservalue) (lua_State *L, int idx);





extern void (lua_callk) (lua_State *L, int nargs, int nresults, int ctx,
                           lua_CFunction k);


extern int (lua_getctx) (lua_State *L, int *ctx);

extern int (lua_pcallk) (lua_State *L, int nargs, int nresults, int errfunc,
                            int ctx, lua_CFunction k);


extern int (lua_load) (lua_State *L, lua_Reader reader, void *dt,
                                        const char *chunkname,
                                        const char *mode);

extern int (lua_dump) (lua_State *L, lua_Writer writer, void *data);





extern int (lua_yieldk) (lua_State *L, int nresults, int ctx,
                           lua_CFunction k);

extern int (lua_resume) (lua_State *L, lua_State *from, int narg);
extern int (lua_status) (lua_State *L);
# 294 "jni/luac/lua.h"
extern int (lua_gc) (lua_State *L, int what, int data);






extern int (lua_error) (lua_State *L);

extern int (lua_next) (lua_State *L, int idx);

extern void (lua_concat) (lua_State *L, int n);
extern void (lua_len) (lua_State *L, int idx);

extern lua_Alloc (lua_getallocf) (lua_State *L, void **ud);
extern void (lua_setallocf) (lua_State *L, lua_Alloc f, void *ud);
# 375 "jni/luac/lua.h"
typedef struct lua_Debug lua_Debug;



typedef void (*lua_Hook) (lua_State *L, lua_Debug *ar);


extern int (lua_getstack) (lua_State *L, int level, lua_Debug *ar);
extern int (lua_getinfo) (lua_State *L, const char *what, lua_Debug *ar);
extern const char *(lua_getlocal) (lua_State *L, const lua_Debug *ar, int n);
extern const char *(lua_setlocal) (lua_State *L, const lua_Debug *ar, int n);
extern const char *(lua_getupvalue) (lua_State *L, int funcindex, int n);
extern const char *(lua_setupvalue) (lua_State *L, int funcindex, int n);

extern void *(lua_upvalueid) (lua_State *L, int fidx, int n);
extern void (lua_upvaluejoin) (lua_State *L, int fidx1, int n1,
                                               int fidx2, int n2);

extern int (lua_sethook) (lua_State *L, lua_Hook func, int mask, int count);
extern lua_Hook (lua_gethook) (lua_State *L);
extern int (lua_gethookmask) (lua_State *L);
extern int (lua_gethookcount) (lua_State *L);


struct lua_Debug {
  int event;
  const char *name;
  const char *namewhat;
  const char *what;
  const char *source;
  int currentline;
  int linedefined;
  int lastlinedefined;
  unsigned char nups;
  unsigned char nparams;
  char isvararg;
  char istailcall;
  char short_src[60];

  struct CallInfo *i_ci;
};
# 16 "jni/luac/luac.c" 2
# 1 "jni/luac/lauxlib.h" 1
# 12 "jni/luac/lauxlib.h"
# 1 "d:\\android-ndk-r12b\\toolchains\\x86-4.9\\prebuilt\\windows-x86_64\\lib\\gcc\\i686-linux-android\\4.9.x\\include\\stddef.h" 1 3 4
# 13 "jni/luac/lauxlib.h" 2
# 23 "jni/luac/lauxlib.h"
typedef struct luaL_Reg {
  const char *name;
  lua_CFunction func;
} luaL_Reg;


extern void (luaL_checkversion_) (lua_State *L, lua_Number ver);


extern int (luaL_getmetafield) (lua_State *L, int obj, const char *e);
extern int (luaL_callmeta) (lua_State *L, int obj, const char *e);
extern const char *(luaL_tolstring) (lua_State *L, int idx, size_t *len);
extern int (luaL_argerror) (lua_State *L, int numarg, const char *extramsg);
extern const char *(luaL_checklstring) (lua_State *L, int numArg,
                                                          size_t *l);
extern const char *(luaL_optlstring) (lua_State *L, int numArg,
                                          const char *def, size_t *l);
extern lua_Number (luaL_checknumber) (lua_State *L, int numArg);
extern lua_Number (luaL_optnumber) (lua_State *L, int nArg, lua_Number def);

extern lua_Integer (luaL_checkinteger) (lua_State *L, int numArg);
extern lua_Integer (luaL_optinteger) (lua_State *L, int nArg,
                                          lua_Integer def);
extern lua_Unsigned (luaL_checkunsigned) (lua_State *L, int numArg);
extern lua_Unsigned (luaL_optunsigned) (lua_State *L, int numArg,
                                            lua_Unsigned def);

extern void (luaL_checkstack) (lua_State *L, int sz, const char *msg);
extern void (luaL_checktype) (lua_State *L, int narg, int t);
extern void (luaL_checkany) (lua_State *L, int narg);

extern int (luaL_newmetatable) (lua_State *L, const char *tname);
extern void (luaL_setmetatable) (lua_State *L, const char *tname);
extern void *(luaL_testudata) (lua_State *L, int ud, const char *tname);
extern void *(luaL_checkudata) (lua_State *L, int ud, const char *tname);

extern void (luaL_where) (lua_State *L, int lvl);
extern int (luaL_error) (lua_State *L, const char *fmt, ...);

extern int (luaL_checkoption) (lua_State *L, int narg, const char *def,
                                   const char *const lst[]);

extern int (luaL_fileresult) (lua_State *L, int stat, const char *fname);
extern int (luaL_execresult) (lua_State *L, int stat);





extern int (luaL_ref) (lua_State *L, int t);
extern void (luaL_unref) (lua_State *L, int t, int ref);

extern int (luaL_loadfilex) (lua_State *L, const char *filename,
                                               const char *mode);



extern int (luaL_loadbufferx) (lua_State *L, const char *buff, size_t sz,
                                   const char *name, const char *mode);
extern int (luaL_loadstring) (lua_State *L, const char *s);

extern lua_State *(luaL_newstate) (void);

extern int (luaL_len) (lua_State *L, int idx);

extern const char *(luaL_gsub) (lua_State *L, const char *s, const char *p,
                                                  const char *r);

extern void (luaL_setfuncs) (lua_State *L, const luaL_Reg *l, int nup);

extern int (luaL_getsubtable) (lua_State *L, int idx, const char *fname);

extern void (luaL_traceback) (lua_State *L, lua_State *L1,
                                  const char *msg, int level);

extern void (luaL_requiref) (lua_State *L, const char *modname,
                                 lua_CFunction openf, int glb);
# 143 "jni/luac/lauxlib.h"
typedef struct luaL_Buffer {
  char *b;
  size_t size;
  size_t n;
  lua_State *L;
  char initb[1024];
} luaL_Buffer;
# 158 "jni/luac/lauxlib.h"
extern void (luaL_buffinit) (lua_State *L, luaL_Buffer *B);
extern char *(luaL_prepbuffsize) (luaL_Buffer *B, size_t sz);
extern void (luaL_addlstring) (luaL_Buffer *B, const char *s, size_t l);
extern void (luaL_addstring) (luaL_Buffer *B, const char *s);
extern void (luaL_addvalue) (luaL_Buffer *B);
extern void (luaL_pushresult) (luaL_Buffer *B);
extern void (luaL_pushresultsize) (luaL_Buffer *B, size_t sz);
extern char *(luaL_buffinitsize) (lua_State *L, luaL_Buffer *B, size_t sz);
# 188 "jni/luac/lauxlib.h"
typedef struct luaL_Stream {
  FILE *f;
  lua_CFunction closef;
} luaL_Stream;
# 17 "jni/luac/luac.c" 2

# 1 "jni/luac/lobject.h" 1
# 15 "jni/luac/lobject.h"
# 1 "jni/luac/llimits.h" 1
# 12 "jni/luac/llimits.h"
# 1 "d:\\android-ndk-r12b\\toolchains\\x86-4.9\\prebuilt\\windows-x86_64\\lib\\gcc\\i686-linux-android\\4.9.x\\include\\stddef.h" 1 3 4
# 13 "jni/luac/llimits.h" 2





typedef unsigned int lu_int32;

typedef size_t lu_mem;

typedef ptrdiff_t l_mem;




typedef unsigned char lu_byte;
# 53 "jni/luac/llimits.h"
typedef union { double u; void *s; long l; } L_Umaxalign;



typedef double l_uacNumber;
# 133 "jni/luac/llimits.h"
typedef lu_int32 Instruction;
# 216 "jni/luac/llimits.h"
union luai_Cast { double l_d; int l_p[2]; };
# 16 "jni/luac/lobject.h" 2
# 70 "jni/luac/lobject.h"
typedef union GCObject GCObject;
# 83 "jni/luac/lobject.h"
typedef struct GCheader {
  GCObject *next; lu_byte tt; lu_byte marked;
} GCheader;






typedef union Value Value;
# 106 "jni/luac/lobject.h"
typedef struct lua_TValue TValue;
# 388 "jni/luac/lobject.h"
union Value {
  GCObject *gc;
  void *p;
  int b;
  lua_CFunction f;
 
};


struct lua_TValue {
  union { struct { Value v__; int tt__; } i; double d__; } u;
};


typedef TValue *StkId;







typedef union TString {
  L_Umaxalign dummy;
  struct {
    GCObject *next; lu_byte tt; lu_byte marked;
    lu_byte extra;
    unsigned int hash;
    size_t len;
  } tsv;
} TString;
# 431 "jni/luac/lobject.h"
typedef union Udata {
  L_Umaxalign dummy;
  struct {
    GCObject *next; lu_byte tt; lu_byte marked;
    struct Table *metatable;
    struct Table *env;
    size_t len;
  } uv;
} Udata;






typedef struct Upvaldesc {
  TString *name;
  lu_byte instack;
  lu_byte idx;
} Upvaldesc;






typedef struct LocVar {
  TString *varname;
  int startpc;
  int endpc;
} LocVar;





typedef struct Proto {
  GCObject *next; lu_byte tt; lu_byte marked;
  TValue *k;
  Instruction *code;
  struct Proto **p;
  int *lineinfo;
  LocVar *locvars;
  Upvaldesc *upvalues;
  union Closure *cache;
  TString *source;
  int sizeupvalues;
  int sizek;
  int sizecode;
  int sizelineinfo;
  int sizep;
  int sizelocvars;
  int linedefined;
  int lastlinedefined;
  GCObject *gclist;
  lu_byte numparams;
  lu_byte is_vararg;
  lu_byte maxstacksize;
} Proto;






typedef struct UpVal {
  GCObject *next; lu_byte tt; lu_byte marked;
  TValue *v;
  union {
    TValue value;
    struct {
      struct UpVal *prev;
      struct UpVal *next;
    } l;
  } u;
} UpVal;
# 516 "jni/luac/lobject.h"
typedef struct CClosure {
  GCObject *next; lu_byte tt; lu_byte marked; lu_byte nupvalues; GCObject *gclist;
  lua_CFunction f;
  TValue upvalue[1];
} CClosure;


typedef struct LClosure {
  GCObject *next; lu_byte tt; lu_byte marked; lu_byte nupvalues; GCObject *gclist;
  struct Proto *p;
  UpVal *upvals[1];
} LClosure;


typedef union Closure {
  CClosure c;
  LClosure l;
} Closure;
# 545 "jni/luac/lobject.h"
typedef union TKey {
  struct {
    union { struct { Value v__; int tt__; } i; double d__; } u;
    struct Node *next;
  } nk;
  TValue tvk;
} TKey;


typedef struct Node {
  TValue i_val;
  TKey i_key;
} Node;


typedef struct Table {
  GCObject *next; lu_byte tt; lu_byte marked;
  lu_byte flags;
  lu_byte lsizenode;
  int sizearray;
  TValue *array;
  Node *node;
  Node *lastfree;
  struct Table *metatable;
  GCObject *gclist;
} Table;
# 591 "jni/luac/lobject.h"
__attribute__((visibility("hidden"))) extern const TValue luaO_nilobject_;


__attribute__((visibility("hidden"))) extern int luaO_int2fb (unsigned int x);
__attribute__((visibility("hidden"))) extern int luaO_fb2int (int x);
__attribute__((visibility("hidden"))) extern int luaO_ceillog2 (unsigned int x);
__attribute__((visibility("hidden"))) extern lua_Number luaO_arith (int op, lua_Number v1, lua_Number v2);
__attribute__((visibility("hidden"))) extern int luaO_str2d (const char *s, size_t len, lua_Number *result);
__attribute__((visibility("hidden"))) extern int luaO_hexavalue (int c);
__attribute__((visibility("hidden"))) extern const char *luaO_pushvfstring (lua_State *L, const char *fmt,
                                                       va_list argp);
__attribute__((visibility("hidden"))) extern const char *luaO_pushfstring (lua_State *L, const char *fmt, ...);
__attribute__((visibility("hidden"))) extern void luaO_chunkid (char *out, const char *source, size_t len);
# 19 "jni/luac/luac.c" 2
# 1 "jni/luac/lstate.h" 1
# 13 "jni/luac/lstate.h"
# 1 "jni/luac/ltm.h" 1
# 18 "jni/luac/ltm.h"
typedef enum {
  TM_INDEX,
  TM_NEWINDEX,
  TM_GC,
  TM_MODE,
  TM_LEN,
  TM_EQ,
  TM_ADD,
  TM_SUB,
  TM_MUL,
  TM_DIV,
  TM_MOD,
  TM_POW,
  TM_UNM,
  TM_LT,
  TM_LE,
  TM_CONCAT,
  TM_CALL,
  TM_N
} TMS;
# 49 "jni/luac/ltm.h"
__attribute__((visibility("hidden"))) extern const char *const luaT_typenames_[((9 +1)+2)];


__attribute__((visibility("hidden"))) extern const TValue *luaT_gettm (Table *events, TMS event, TString *ename);
__attribute__((visibility("hidden"))) extern const TValue *luaT_gettmbyobj (lua_State *L, const TValue *o,
                                                       TMS event);
__attribute__((visibility("hidden"))) extern void luaT_init (lua_State *L);
# 14 "jni/luac/lstate.h" 2
# 1 "jni/luac/lzio.h" 1
# 13 "jni/luac/lzio.h"
# 1 "jni/luac/lmem.h" 1
# 11 "jni/luac/lmem.h"
# 1 "d:\\android-ndk-r12b\\toolchains\\x86-4.9\\prebuilt\\windows-x86_64\\lib\\gcc\\i686-linux-android\\4.9.x\\include\\stddef.h" 1 3 4
# 12 "jni/luac/lmem.h" 2
# 47 "jni/luac/lmem.h"
__attribute__((visibility("hidden"))) extern void __attribute__((noreturn)) luaM_toobig (lua_State *L);


__attribute__((visibility("hidden"))) extern void *luaM_realloc_ (lua_State *L, void *block, size_t oldsize,
                                                          size_t size);
__attribute__((visibility("hidden"))) extern void *luaM_growaux_ (lua_State *L, void *block, int *size,
                               size_t size_elem, int limit,
                               const char *what);
# 14 "jni/luac/lzio.h" 2




typedef struct Zio ZIO;




typedef struct Mbuffer {
  char *buffer;
  size_t n;
  size_t buffsize;
} Mbuffer;
# 45 "jni/luac/lzio.h"
__attribute__((visibility("hidden"))) extern char *luaZ_openspace (lua_State *L, Mbuffer *buff, size_t n);
__attribute__((visibility("hidden"))) extern void luaZ_init (lua_State *L, ZIO *z, lua_Reader reader,
                                        void *data);
__attribute__((visibility("hidden"))) extern size_t luaZ_read (ZIO* z, void* b, size_t n);





struct Zio {
  size_t n;
  const char *p;
  lua_Reader reader;
  void* data;
  lua_State *L;
};


__attribute__((visibility("hidden"))) extern int luaZ_fill (ZIO *z);
# 15 "jni/luac/lstate.h" 2
# 42 "jni/luac/lstate.h"
struct lua_longjmp;
# 59 "jni/luac/lstate.h"
typedef struct stringtable {
  GCObject **hash;
  lu_int32 nuse;
  int size;
} stringtable;





typedef struct CallInfo {
  StkId func;
  StkId top;
  struct CallInfo *previous, *next;
  short nresults;
  lu_byte callstatus;
  ptrdiff_t extra;
  union {
    struct {
      StkId base;
      const Instruction *savedpc;
    } l;
    struct {
      int ctx;
      lua_CFunction k;
      ptrdiff_t old_errfunc;
      lu_byte old_allowhook;
      lu_byte status;
    } c;
  } u;
} CallInfo;
# 112 "jni/luac/lstate.h"
typedef struct global_State {
  lua_Alloc frealloc;
  void *ud;
  lu_mem totalbytes;
  l_mem GCdebt;
  lu_mem GCmemtrav;
  lu_mem GCestimate;
  stringtable strt;
  TValue l_registry;
  unsigned int seed;
  lu_byte currentwhite;
  lu_byte gcstate;
  lu_byte gckind;
  lu_byte gcrunning;
  int sweepstrgc;
  GCObject *allgc;
  GCObject *finobj;
  GCObject **sweepgc;
  GCObject **sweepfin;
  GCObject *gray;
  GCObject *grayagain;
  GCObject *weak;
  GCObject *ephemeron;
  GCObject *allweak;
  GCObject *tobefnz;
  UpVal uvhead;
  Mbuffer buff;
  int gcpause;
  int gcmajorinc;
  int gcstepmul;
  lua_CFunction panic;
  struct lua_State *mainthread;
  const lua_Number *version;
  TString *memerrmsg;
  TString *tmname[TM_N];
  struct Table *mt[9];
} global_State;





struct lua_State {
  GCObject *next; lu_byte tt; lu_byte marked;
  lu_byte status;
  StkId top;
  global_State *l_G;
  CallInfo *ci;
  const Instruction *oldpc;
  StkId stack_last;
  StkId stack;
  int stacksize;
  unsigned short nny;
  unsigned short nCcalls;
  lu_byte hookmask;
  lu_byte allowhook;
  int basehookcount;
  int hookcount;
  lua_Hook hook;
  GCObject *openupval;
  GCObject *gclist;
  struct lua_longjmp *errorJmp;
  ptrdiff_t errfunc;
  CallInfo base_ci;
};
# 185 "jni/luac/lstate.h"
union GCObject {
  GCheader gch;
  union TString ts;
  union Udata u;
  union Closure cl;
  struct Table h;
  struct Proto p;
  struct UpVal uv;
  struct lua_State th;
};
# 221 "jni/luac/lstate.h"
__attribute__((visibility("hidden"))) extern void luaE_setdebt (global_State *g, l_mem debt);
__attribute__((visibility("hidden"))) extern void luaE_freethread (lua_State *L, lua_State *L1);
__attribute__((visibility("hidden"))) extern CallInfo *luaE_extendCI (lua_State *L);
__attribute__((visibility("hidden"))) extern void luaE_freeCI (lua_State *L);
# 20 "jni/luac/luac.c" 2
# 1 "jni/luac/lundump.h" 1
# 14 "jni/luac/lundump.h"
__attribute__((visibility("hidden"))) extern Closure* luaU_undump (lua_State* L, ZIO* Z, Mbuffer* buff, const char* name);


__attribute__((visibility("hidden"))) extern void luaU_header (lu_byte* h);


__attribute__((visibility("hidden"))) extern int luaU_dump (lua_State* L, const Proto* f, lua_Writer w, void* data, int strip);
# 21 "jni/luac/luac.c" 2

static void PrintFunction(const Proto* f, int full);





static int listing=0;
static int dumping=1;
static int stripping=0;
static char Output[]={ "luac" ".out" };
static const char* output=Output;
static const char* progname="luac";

static void fatal(const char* message)
{
 fprintf((&__sF[2]),"%s: %s\n",progname,message);
 exit(1);
}

static void cannot(const char* what)
{
 fprintf((&__sF[2]),"%s: cannot %s %s: %s\n",progname,what,output,strerror((*__errno())));
 exit(1);
}

static void usage(const char* message)
{
 if (*message=='-')
  fprintf((&__sF[2]),"%s: unrecognized option " "'" "%s" "'" "\n",progname,message);
 else
  fprintf((&__sF[2]),"%s: %s\n",progname,message);
 fprintf((&__sF[2]),
  "usage: %s [options] [filenames]\n"
  "Available options are:\n"
  "  -l       list (use -l -l for full listing)\n"
  "  -o name  output to file " "'" "name" "'" " (default is \"%s\")\n"
  "  -p       parse only\n"
  "  -s       strip debug information\n"
  "  -v       show version information\n"
  "  --       stop handling options\n"
  "  -        stop handling options and process stdin\n"
  ,progname,Output);
 exit(1);
}



static int doargs(int argc, char* argv[])
{
 int i;
 int version=0;
 if (argv[0]!=((void *)0) && *argv[0]!=0) progname=argv[0];
 for (i=1; i<argc; i++)
 {
  if (*argv[i]!='-')
   break;
  else if ((strcmp(argv[i],"--")==0))
  {
   ++i;
   if (version) ++version;
   break;
  }
  else if ((strcmp(argv[i],"-")==0))
   break;
  else if ((strcmp(argv[i],"-l")==0))
   ++listing;
  else if ((strcmp(argv[i],"-o")==0))
  {
   output=argv[++i];
   if (output==((void *)0) || *output==0 || (*output=='-' && output[1]!=0))
    usage("'" "-o" "'" " needs argument");
   if ((strcmp(argv[i],"-")==0)) output=((void *)0);
  }
  else if ((strcmp(argv[i],"-p")==0))
   dumping=0;
  else if ((strcmp(argv[i],"-s")==0))
   stripping=1;
  else if ((strcmp(argv[i],"-v")==0))
   ++version;
  else
   usage(argv[i]);
 }
 if (i==argc && (listing || !dumping))
 {
  dumping=0;
  argv[--i]=Output;
 }
 if (version)
 {
  printf("%s\n","Lua " "5" "." "2" "." "4" "  Copyright (C) 1994-2015 Lua.org, PUC-Rio");
  if (version==argc-1) exit(0);
 }
 return i;
}



static const char* reader(lua_State *L, void *ud, size_t *size)
{
 ((void)(L));
 if ((*(int*)ud)--)
 {
  *size=sizeof("(function()end)();")-1;
  return "(function()end)();";
 }
 else
 {
  *size=0;
  return ((void *)0);
 }
}



static const Proto* combine(lua_State* L, int n)
{
 if (n==1)
  return ((&((L->top+(-1))->u.i.v__).gc->cl.l)->p);
 else
 {
  Proto* f;
  int i=n;
  if (lua_load(L,reader,&i,"=(" "luac" ")",((void *)0))!=0) fatal(lua_tolstring(L, (-1), ((void *)0)));
  f=((&((L->top+(-1))->u.i.v__).gc->cl.l)->p);
  for (i=0; i<n; i++)
  {
   f->p[i]=((&((L->top+(i-n-1))->u.i.v__).gc->cl.l)->p);
   if (f->p[i]->sizeupvalues>0) f->p[i]->upvalues[0].instack=0;
  }
  f->sizelineinfo=0;
  return f;
 }
}

static int writer(lua_State* L, const void* p, size_t size, void* u)
{
 ((void)(L));
 return (fwrite(p,size,1,(FILE*)u)!=1) && (size!=0);
}

static int pmain(lua_State* L)
{
 int argc=(int)lua_tointegerx(L,1,((void *)0));
 char** argv=(char**)lua_touserdata(L,2);
 const Proto* f;
 int i;
 if (!lua_checkstack(L,argc)) fatal("too many input files");
 for (i=0; i<argc; i++)
 {
  const char* filename=(strcmp(argv[i],"-")==0) ? ((void *)0) : argv[i];
  if (luaL_loadfilex(L,filename,((void *)0))!=0) fatal(lua_tolstring(L, (-1), ((void *)0)));
 }
 f=combine(L,argc);
 if (listing) PrintFunction(f,listing>1);
 if (dumping)
 {
  FILE* D= (output==((void *)0)) ? (&__sF[1]) : fopen(output,"wb");
  if (D==((void *)0)) cannot("open");
  ((void) 0);
  luaU_dump(L,f,writer,D,stripping);
  ((void) 0);
  if ((((D)->_flags & 0x0040) != 0)) cannot("write");
  if (fclose(D)) cannot("close");
 }
 return 0;
}

int main(int argc, char* argv[])
{
 lua_State* L;
 int i=doargs(argc,argv);
 argc-=i; argv+=i;
 if (argc<=0) usage("no input files given");
 L=luaL_newstate();
 if (L==((void *)0)) fatal("cannot create state: not enough memory");
 lua_pushcclosure(L, (&pmain), 0);
 lua_pushinteger(L,argc);
 lua_pushlightuserdata(L,argv);
 if (lua_pcallk(L, (2), (0), (0), 0, ((void *)0))!=0) fatal(lua_tolstring(L, (-1), ((void *)0)));
 lua_close(L);
 return 0;
}







# 1 "d:\\android-ndk-r12b\\platforms\\android-9\\arch-x86\\usr\\include\\ctype.h" 1 3 4
# 54 "d:\\android-ndk-r12b\\platforms\\android-9\\arch-x86\\usr\\include\\ctype.h" 3 4


extern const char *_ctype_;
extern const short *_tolower_tab_;
extern const short *_toupper_tab_;
# 72 "d:\\android-ndk-r12b\\platforms\\android-9\\arch-x86\\usr\\include\\ctype.h" 3 4
int isalnum(int);
int isalpha(int);
int iscntrl(int);
int isdigit(int);
int isgraph(int);
int islower(int);
int isprint(int);
int ispunct(int);
int isspace(int);
int isupper(int);
int isxdigit(int);
int tolower(int);
int toupper(int);



int isblank(int);



int isascii(int);
int toascii(int);
int _tolower(int);
int _toupper(int);






extern __inline int isalnum(int c)
{
 return (c == -1 ? 0 : ((_ctype_ + 1)[(unsigned char)c] & (0x01|0x02|0x04)));
}

extern __inline int isalpha(int c)
{
 return (c == -1 ? 0 : ((_ctype_ + 1)[(unsigned char)c] & (0x01|0x02)));
}

extern __inline int iscntrl(int c)
{
 return (c == -1 ? 0 : ((_ctype_ + 1)[(unsigned char)c] & 0x20));
}

extern __inline int isdigit(int c)
{
 return (c == -1 ? 0 : ((_ctype_ + 1)[(unsigned char)c] & 0x04));
}

extern __inline int isgraph(int c)
{
 return (c == -1 ? 0 : ((_ctype_ + 1)[(unsigned char)c] & (0x10|0x01|0x02|0x04)));
}

extern __inline int islower(int c)
{
 return (c == -1 ? 0 : ((_ctype_ + 1)[(unsigned char)c] & 0x02));
}

extern __inline int isprint(int c)
{
 return (c == -1 ? 0 : ((_ctype_ + 1)[(unsigned char)c] & (0x10|0x01|0x02|0x04|0x80)));
}

extern __inline int ispunct(int c)
{
 return (c == -1 ? 0 : ((_ctype_ + 1)[(unsigned char)c] & 0x10));
}

extern __inline int isspace(int c)
{
 return (c == -1 ? 0 : ((_ctype_ + 1)[(unsigned char)c] & 0x08));
}

extern __inline int isupper(int c)
{
 return (c == -1 ? 0 : ((_ctype_ + 1)[(unsigned char)c] & 0x01));
}

extern __inline int isxdigit(int c)
{
 return (c == -1 ? 0 : ((_ctype_ + 1)[(unsigned char)c] & (0x04|0x40)));
}

extern __inline int tolower(int c)
{
 if ((unsigned int)c > 255)
  return (c);
 return ((_tolower_tab_ + 1)[c]);
}

extern __inline int toupper(int c)
{
 if ((unsigned int)c > 255)
  return (c);
 return ((_toupper_tab_ + 1)[c]);
}



extern __inline int isblank(int c)
{
 return (c == ' ' || c == '\t');
}



extern __inline int isascii(int c)
{
 return ((unsigned int)c <= 0177);
}

extern __inline int toascii(int c)
{
 return (c & 0177);
}

extern __inline int _tolower(int c)
{
 return (c - 'A' + 'a');
}

extern __inline int _toupper(int c)
{
 return (c - 'a' + 'A');
}





# 212 "jni/luac/luac.c" 2





# 1 "jni/luac/ldebug.h" 1
# 24 "jni/luac/ldebug.h"
__attribute__((visibility("hidden"))) extern void __attribute__((noreturn)) luaG_typeerror (lua_State *L, const TValue *o,
                                                const char *opname);
__attribute__((visibility("hidden"))) extern void __attribute__((noreturn)) luaG_concaterror (lua_State *L, StkId p1, StkId p2);
__attribute__((visibility("hidden"))) extern void __attribute__((noreturn)) luaG_aritherror (lua_State *L, const TValue *p1,
                                                 const TValue *p2);
__attribute__((visibility("hidden"))) extern void __attribute__((noreturn)) luaG_ordererror (lua_State *L, const TValue *p1,
                                                 const TValue *p2);
__attribute__((visibility("hidden"))) extern void __attribute__((noreturn)) luaG_runerror (lua_State *L, const char *fmt, ...);
__attribute__((visibility("hidden"))) extern void __attribute__((noreturn)) luaG_errormsg (lua_State *L);
# 218 "jni/luac/luac.c" 2

# 1 "jni/luac/lopcodes.h" 1
# 32 "jni/luac/lopcodes.h"
enum OpMode {iABC, iABx, iAsBx, iAx};
# 165 "jni/luac/lopcodes.h"
typedef enum {



OP_MOVE,
OP_LOADK,
OP_LOADKX,
OP_LOADBOOL,
OP_LOADNIL,
OP_GETUPVAL,

OP_GETTABUP,
OP_GETTABLE,

OP_SETTABUP,
OP_SETUPVAL,
OP_SETTABLE,

OP_NEWTABLE,

OP_SELF,

OP_ADD,
OP_SUB,
OP_MUL,
OP_DIV,
OP_MOD,
OP_POW,
OP_UNM,
OP_NOT,
OP_LEN,

OP_CONCAT,

OP_JMP,
OP_EQ,
OP_LT,
OP_LE,

OP_TEST,
OP_TESTSET,

OP_CALL,
OP_TAILCALL,
OP_RETURN,

OP_FORLOOP,

OP_FORPREP,

OP_TFORCALL,
OP_TFORLOOP,

OP_SETLIST,

OP_CLOSURE,

OP_VARARG,

OP_EXTRAARG
} OpCode;
# 265 "jni/luac/lopcodes.h"
enum OpArgMask {
  OpArgN,
  OpArgU,
  OpArgR,
  OpArgK
};

__attribute__((visibility("hidden"))) extern const lu_byte luaP_opmodes[(((int)(OP_EXTRAARG)) + 1)];
# 281 "jni/luac/lopcodes.h"
__attribute__((visibility("hidden"))) extern const char *const luaP_opnames[(((int)(OP_EXTRAARG)) + 1)+1];
# 220 "jni/luac/luac.c" 2



static void PrintString(const TString* ts)
{
 const char* s=((const char *)((ts) + 1));
 size_t i,n=ts->tsv.len;
 printf("%c",'"');
 for (i=0; i<n; i++)
 {
  int c=(int)(unsigned char)s[i];
  switch (c)
  {
   case '"': printf("\\\""); break;
   case '\\': printf("\\\\"); break;
   case '\a': printf("\\a"); break;
   case '\b': printf("\\b"); break;
   case '\f': printf("\\f"); break;
   case '\n': printf("\\n"); break;
   case '\r': printf("\\r"); break;
   case '\t': printf("\\t"); break;
   case '\v': printf("\\v"); break;
   default: if (isprint(c))
      printf("%c",c);
  else
   printf("\\%03d",c);
  }
 }
 printf("%c",'"');
}

static void PrintConstant(const Proto* f, int i)
{
 const TValue* o=&f->k[i];
 switch (((((((((o)->u.i.tt__) & 0x7FFFFF00) != 0x7FF7A500) ? 3 : ((o)->u.i.tt__) & 0xff)) & 0x0F)))
 {
  case 0:
 printf("nil");
 break;
  case 1:
 printf((((o)->u.i.v__).b) ? "true" : "false");
 break;
  case 3:
 printf("%.14g",(((o)->u.d__)));
 break;
  case 4:
 PrintString((&((o)->u.i.v__).gc->ts));
 break;
  default:
 printf("? type=%d",((((((o)->u.i.tt__) & 0x7FFFFF00) != 0x7FF7A500) ? 3 : ((o)->u.i.tt__) & 0xff) & 0x3F));
 break;
 }
}




static void PrintCode(const Proto* f)
{
 const Instruction* code=f->code;
 int pc,n=f->sizecode;
 for (pc=0; pc<n; pc++)
 {
  Instruction i=code[pc];
  OpCode o=(((OpCode)(((i)>>0) & ((~((~(Instruction)0)<<(6)))<<(0)))));
  int a=(((int)(((i)>>(0 + 6)) & ((~((~(Instruction)0)<<(8)))<<(0)))));
  int b=(((int)(((i)>>(((0 + 6) + 8) + 9)) & ((~((~(Instruction)0)<<(9)))<<(0)))));
  int c=(((int)(((i)>>((0 + 6) + 8)) & ((~((~(Instruction)0)<<(9)))<<(0)))));
  int ax=(((int)(((i)>>(0 + 6)) & ((~((~(Instruction)0)<<((9 + 9 + 8))))<<(0)))));
  int bx=(((int)(((i)>>((0 + 6) + 8)) & ((~((~(Instruction)0)<<((9 + 9))))<<(0)))));
  int sbx=((((int)(((i)>>((0 + 6) + 8)) & ((~((~(Instruction)0)<<((9 + 9))))<<(0)))))-(((1<<(9 + 9))-1)>>1));
  int line=(((f)->lineinfo) ? (f)->lineinfo[pc] : 0);
  printf("\t%d\t",pc+1);
  if (line>0) printf("[%d]\t",line); else printf("[-]\t");
  printf("%-9s\t",luaP_opnames[o]);
  switch ((((enum OpMode)(luaP_opmodes[o] & 3))))
  {
   case iABC:
    printf("%d",a);
    if ((((enum OpArgMask)((luaP_opmodes[o] >> 4) & 3)))!=OpArgN) printf(" %d",((b) & (1 << (9 - 1))) ? ((-1-(((int)(b) & ~(1 << (9 - 1)))))) : b);
    if ((((enum OpArgMask)((luaP_opmodes[o] >> 2) & 3)))!=OpArgN) printf(" %d",((c) & (1 << (9 - 1))) ? ((-1-(((int)(c) & ~(1 << (9 - 1)))))) : c);
    break;
   case iABx:
    printf("%d",a);
    if ((((enum OpArgMask)((luaP_opmodes[o] >> 4) & 3)))==OpArgK) printf(" %d",(-1-(bx)));
    if ((((enum OpArgMask)((luaP_opmodes[o] >> 4) & 3)))==OpArgU) printf(" %d",bx);
    break;
   case iAsBx:
    printf("%d %d",a,sbx);
    break;
   case iAx:
    printf("%d",(-1-(ax)));
    break;
  }
  switch (o)
  {
   case OP_LOADK:
    printf("\t; "); PrintConstant(f,bx);
    break;
   case OP_GETUPVAL:
   case OP_SETUPVAL:
    printf("\t; %s",((f->upvalues[b].name) ? ((const char *)((f->upvalues[b].name) + 1)) : "-"));
    break;
   case OP_GETTABUP:
    printf("\t; %s",((f->upvalues[b].name) ? ((const char *)((f->upvalues[b].name) + 1)) : "-"));
    if (((c) & (1 << (9 - 1)))) { printf(" "); PrintConstant(f,((int)(c) & ~(1 << (9 - 1)))); }
    break;
   case OP_SETTABUP:
    printf("\t; %s",((f->upvalues[a].name) ? ((const char *)((f->upvalues[a].name) + 1)) : "-"));
    if (((b) & (1 << (9 - 1)))) { printf(" "); PrintConstant(f,((int)(b) & ~(1 << (9 - 1)))); }
    if (((c) & (1 << (9 - 1)))) { printf(" "); PrintConstant(f,((int)(c) & ~(1 << (9 - 1)))); }
    break;
   case OP_GETTABLE:
   case OP_SELF:
    if (((c) & (1 << (9 - 1)))) { printf("\t; "); PrintConstant(f,((int)(c) & ~(1 << (9 - 1)))); }
    break;
   case OP_SETTABLE:
   case OP_ADD:
   case OP_SUB:
   case OP_MUL:
   case OP_DIV:
   case OP_POW:
   case OP_EQ:
   case OP_LT:
   case OP_LE:
    if (((b) & (1 << (9 - 1))) || ((c) & (1 << (9 - 1))))
    {
     printf("\t; ");
     if (((b) & (1 << (9 - 1)))) PrintConstant(f,((int)(b) & ~(1 << (9 - 1)))); else printf("-");
     printf(" ");
     if (((c) & (1 << (9 - 1)))) PrintConstant(f,((int)(c) & ~(1 << (9 - 1)))); else printf("-");
    }
    break;
   case OP_JMP:
   case OP_FORLOOP:
   case OP_FORPREP:
   case OP_TFORLOOP:
    printf("\t; to %d",sbx+pc+2);
    break;
   case OP_CLOSURE:
    printf("\t; %p",((const void*)(f->p[bx])));
    break;
   case OP_SETLIST:
    if (c==0) printf("\t; %d",(int)code[++pc]); else printf("\t; %d",c);
    break;
   case OP_EXTRAARG:
    printf("\t; "); PrintConstant(f,ax);
    break;
   default:
    break;
  }
  printf("\n");
 }
}




static void PrintHeader(const Proto* f)
{
 const char* s=f->source ? ((const char *)((f->source) + 1)) : "=?";
 if (*s=='@' || *s=='=')
  s++;
 else if (*s=="\033Lua"[0])
  s="(bstring)";
 else
  s="(string)";
 printf("\n%s <%s:%d,%d> (%d instruction%s at %p)\n",
  (f->linedefined==0)?"main":"function",s,
 f->linedefined,f->lastlinedefined,
 (int)(f->sizecode),((f->sizecode==1)?"":"s"),((const void*)(f)));
 printf("%d%s param%s, %d slot%s, %d upvalue%s, ",
 (int)(f->numparams),f->is_vararg?"+":"",((f->numparams==1)?"":"s"),
 (int)(f->maxstacksize),((f->maxstacksize==1)?"":"s"),(int)(f->sizeupvalues),((f->sizeupvalues==1)?"":"s"));
 printf("%d local%s, %d constant%s, %d function%s\n",
 (int)(f->sizelocvars),((f->sizelocvars==1)?"":"s"),(int)(f->sizek),((f->sizek==1)?"":"s"),(int)(f->sizep),((f->sizep==1)?"":"s"));
}

static void PrintDebug(const Proto* f)
{
 int i,n;
 n=f->sizek;
 printf("constants (%d) for %p:\n",n,((const void*)(f)));
 for (i=0; i<n; i++)
 {
  printf("\t%d\t",i+1);
  PrintConstant(f,i);
  printf("\n");
 }
 n=f->sizelocvars;
 printf("locals (%d) for %p:\n",n,((const void*)(f)));
 for (i=0; i<n; i++)
 {
  printf("\t%d\t%s\t%d\t%d\n",
  i,((const char *)((f->locvars[i].varname) + 1)),f->locvars[i].startpc+1,f->locvars[i].endpc+1);
 }
 n=f->sizeupvalues;
 printf("upvalues (%d) for %p:\n",n,((const void*)(f)));
 for (i=0; i<n; i++)
 {
  printf("\t%d\t%s\t%d\t%d\n",
  i,((f->upvalues[i].name) ? ((const char *)((f->upvalues[i].name) + 1)) : "-"),f->upvalues[i].instack,f->upvalues[i].idx);
 }
}

static void PrintFunction(const Proto* f, int full)
{
 int i,n=f->sizep;
 PrintHeader(f);
 PrintCode(f);
 if (full) PrintDebug(f);
 for (i=0; i<n; i++) PrintFunction(f->p[i],full);
}
