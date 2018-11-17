	.file	"Mutex.cpp"
	.text
.Ltext0:
	.section	.text.unlikely.MutexCreate,"ax",@progbits
.LCOLDB0:
	.section	.text.MutexCreate,"ax",@progbits
.LHOTB0:
	.p2align 4,,15
	.section	.text.unlikely.MutexCreate
.Ltext_cold0:
	.section	.text.MutexCreate
	.globl	MutexCreate
	.type	MutexCreate, @function
MutexCreate:
.LFB22:
	.file 1 "jni/tracer/../util/Mutex.cpp"
	.loc 1 20 0
	.cfi_startproc
.LVL0:
	pushl	%ebx
	.cfi_def_cfa_offset 8
	.cfi_offset 3, -8
	call	__x86.get_pc_thunk.bx
	addl	$_GLOBAL_OFFSET_TABLE_, %ebx
	leal	-24(%esp), %esp
	.cfi_def_cfa_offset 32
	.loc 1 24 0
	movl	32(%esp), %eax
	movl	$0, 4(%esp)
	movl	%eax, (%esp)
	call	pthread_mutex_init@PLT
.LVL1:
	.loc 1 26 0
	leal	24(%esp), %esp
	.cfi_def_cfa_offset 8
	popl	%ebx
	.cfi_restore 3
	.cfi_def_cfa_offset 4
	ret
	.cfi_endproc
.LFE22:
	.size	MutexCreate, .-MutexCreate
	.section	.text.unlikely.MutexCreate
.LCOLDE0:
	.section	.text.MutexCreate
.LHOTE0:
	.section	.text.unlikely.MutexDestroy,"ax",@progbits
.LCOLDB1:
	.section	.text.MutexDestroy,"ax",@progbits
.LHOTB1:
	.p2align 4,,15
	.globl	MutexDestroy
	.type	MutexDestroy, @function
MutexDestroy:
.LFB23:
	.loc 1 30 0
	.cfi_startproc
.LVL2:
	pushl	%ebx
	.cfi_def_cfa_offset 8
	.cfi_offset 3, -8
	call	__x86.get_pc_thunk.bx
	addl	$_GLOBAL_OFFSET_TABLE_, %ebx
	leal	-24(%esp), %esp
	.cfi_def_cfa_offset 32
	.loc 1 34 0
	movl	32(%esp), %eax
	movl	%eax, (%esp)
	call	pthread_mutex_destroy@PLT
.LVL3:
	.loc 1 36 0
	leal	24(%esp), %esp
	.cfi_def_cfa_offset 8
	popl	%ebx
	.cfi_restore 3
	.cfi_def_cfa_offset 4
	ret
	.cfi_endproc
.LFE23:
	.size	MutexDestroy, .-MutexDestroy
	.section	.text.unlikely.MutexDestroy
.LCOLDE1:
	.section	.text.MutexDestroy
.LHOTE1:
	.section	.text.unlikely.MutexLock,"ax",@progbits
.LCOLDB2:
	.section	.text.MutexLock,"ax",@progbits
.LHOTB2:
	.p2align 4,,15
	.globl	MutexLock
	.type	MutexLock, @function
MutexLock:
.LFB24:
	.loc 1 39 0
	.cfi_startproc
.LVL4:
	pushl	%ebx
	.cfi_def_cfa_offset 8
	.cfi_offset 3, -8
	call	__x86.get_pc_thunk.bx
	addl	$_GLOBAL_OFFSET_TABLE_, %ebx
	leal	-24(%esp), %esp
	.cfi_def_cfa_offset 32
	.loc 1 43 0
	movl	32(%esp), %eax
	movl	%eax, (%esp)
	call	pthread_mutex_lock@PLT
.LVL5:
	.loc 1 45 0
	leal	24(%esp), %esp
	.cfi_def_cfa_offset 8
	popl	%ebx
	.cfi_restore 3
	.cfi_def_cfa_offset 4
	ret
	.cfi_endproc
.LFE24:
	.size	MutexLock, .-MutexLock
	.section	.text.unlikely.MutexLock
.LCOLDE2:
	.section	.text.MutexLock
.LHOTE2:
	.section	.text.unlikely.MutexUnlock,"ax",@progbits
.LCOLDB3:
	.section	.text.MutexUnlock,"ax",@progbits
.LHOTB3:
	.p2align 4,,15
	.globl	MutexUnlock
	.type	MutexUnlock, @function
MutexUnlock:
.LFB25:
	.loc 1 48 0
	.cfi_startproc
.LVL6:
	pushl	%ebx
	.cfi_def_cfa_offset 8
	.cfi_offset 3, -8
	call	__x86.get_pc_thunk.bx
	addl	$_GLOBAL_OFFSET_TABLE_, %ebx
	leal	-24(%esp), %esp
	.cfi_def_cfa_offset 32
	.loc 1 52 0
	movl	32(%esp), %eax
	movl	%eax, (%esp)
	call	pthread_mutex_unlock@PLT
.LVL7:
	.loc 1 54 0
	leal	24(%esp), %esp
	.cfi_def_cfa_offset 8
	popl	%ebx
	.cfi_restore 3
	.cfi_def_cfa_offset 4
	ret
	.cfi_endproc
.LFE25:
	.size	MutexUnlock, .-MutexUnlock
	.section	.text.unlikely.MutexUnlock
.LCOLDE3:
	.section	.text.MutexUnlock
.LHOTE3:
	.section	.text.__x86.get_pc_thunk.bx,"axG",@progbits,__x86.get_pc_thunk.bx,comdat
	.globl	__x86.get_pc_thunk.bx
	.hidden	__x86.get_pc_thunk.bx
	.type	__x86.get_pc_thunk.bx, @function
__x86.get_pc_thunk.bx:
.LFB26:
	.cfi_startproc
	movl	(%esp), %ebx
	ret
	.cfi_endproc
.LFE26:
	.text
.Letext0:
	.section	.text.unlikely.MutexCreate
.Letext_cold0:
	.file 2 "D:/android-ndk-r12b/build//../sources/cxx-stl/stlport/stlport/stl/config/features.h"
	.file 3 "d:\\android-ndk-r12b\\platforms\\android-9\\arch-x86\\usr\\include\\pthread.h"
	.file 4 "jni/tracer/../util/Mutex.hpp"
	.file 5 "<built-in>"
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.long	0x22e
	.value	0x4
	.long	.Ldebug_abbrev0
	.byte	0x4
	.uleb128 0x1
	.long	.LASF25
	.byte	0x4
	.long	.LASF26
	.long	.LASF27
	.long	.Ldebug_ranges0+0
	.long	0
	.long	.Ldebug_line0
	.uleb128 0x2
	.string	"std"
	.byte	0x5
	.byte	0
	.uleb128 0x3
	.long	.LASF0
	.byte	0x2
	.value	0x1a0
	.long	0x25
	.uleb128 0x3
	.long	.LASF1
	.byte	0x2
	.value	0x218
	.long	0x25
	.uleb128 0x3
	.long	.LASF2
	.byte	0x2
	.value	0x21c
	.long	0x25
	.uleb128 0x4
	.byte	0x4
	.byte	0x5
	.string	"int"
	.uleb128 0x5
	.byte	0x4
	.byte	0x7
	.long	.LASF3
	.uleb128 0x5
	.byte	0x8
	.byte	0x5
	.long	.LASF4
	.uleb128 0x5
	.byte	0x8
	.byte	0x4
	.long	.LASF5
	.uleb128 0x6
	.long	.LASF28
	.uleb128 0x5
	.byte	0x1
	.byte	0x6
	.long	.LASF6
	.uleb128 0x5
	.byte	0x1
	.byte	0x8
	.long	.LASF7
	.uleb128 0x5
	.byte	0x2
	.byte	0x5
	.long	.LASF8
	.uleb128 0x5
	.byte	0x2
	.byte	0x7
	.long	.LASF9
	.uleb128 0x5
	.byte	0x8
	.byte	0x7
	.long	.LASF10
	.uleb128 0x5
	.byte	0x4
	.byte	0x7
	.long	.LASF11
	.uleb128 0x5
	.byte	0x4
	.byte	0x5
	.long	.LASF12
	.uleb128 0x5
	.byte	0x1
	.byte	0x6
	.long	.LASF13
	.uleb128 0x5
	.byte	0x4
	.byte	0x7
	.long	.LASF14
	.uleb128 0x7
	.byte	0x4
	.byte	0x3
	.byte	0x29
	.long	.LASF29
	.long	0xc9
	.uleb128 0x8
	.long	.LASF30
	.byte	0x3
	.byte	0x2a
	.long	0xc9
	.byte	0
	.byte	0
	.uleb128 0x9
	.long	0x50
	.uleb128 0xa
	.long	.LASF15
	.byte	0x3
	.byte	0x2b
	.long	0xb0
	.uleb128 0xa
	.long	.LASF16
	.byte	0x3
	.byte	0x51
	.long	0x9b
	.uleb128 0xa
	.long	.LASF17
	.byte	0x4
	.byte	0x16
	.long	0xce
	.uleb128 0xb
	.long	.LASF18
	.byte	0x1
	.byte	0x13
	.long	.LFB22
	.long	.LFE22-.LFB22
	.uleb128 0x1
	.byte	0x9c
	.long	0x129
	.uleb128 0xc
	.string	"m"
	.byte	0x1
	.byte	0x13
	.long	0x129
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0xd
	.long	.LVL1
	.long	0x1cb
	.uleb128 0xe
	.uleb128 0x2
	.byte	0x74
	.sleb128 0
	.uleb128 0x3
	.byte	0x91
	.sleb128 0
	.byte	0x6
	.uleb128 0xe
	.uleb128 0x2
	.byte	0x74
	.sleb128 4
	.uleb128 0x1
	.byte	0x30
	.byte	0
	.byte	0
	.uleb128 0xf
	.byte	0x4
	.long	0xe4
	.uleb128 0xb
	.long	.LASF19
	.byte	0x1
	.byte	0x1d
	.long	.LFB23
	.long	.LFE23-.LFB23
	.uleb128 0x1
	.byte	0x9c
	.long	0x163
	.uleb128 0xc
	.string	"m"
	.byte	0x1
	.byte	0x1d
	.long	0x129
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0xd
	.long	.LVL3
	.long	0x1f6
	.uleb128 0xe
	.uleb128 0x2
	.byte	0x74
	.sleb128 0
	.uleb128 0x3
	.byte	0x91
	.sleb128 0
	.byte	0x6
	.byte	0
	.byte	0
	.uleb128 0xb
	.long	.LASF20
	.byte	0x1
	.byte	0x26
	.long	.LFB24
	.long	.LFE24-.LFB24
	.uleb128 0x1
	.byte	0x9c
	.long	0x197
	.uleb128 0xc
	.string	"m"
	.byte	0x1
	.byte	0x26
	.long	0x129
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0xd
	.long	.LVL5
	.long	0x20b
	.uleb128 0xe
	.uleb128 0x2
	.byte	0x74
	.sleb128 0
	.uleb128 0x3
	.byte	0x91
	.sleb128 0
	.byte	0x6
	.byte	0
	.byte	0
	.uleb128 0xb
	.long	.LASF21
	.byte	0x1
	.byte	0x2f
	.long	.LFB25
	.long	.LFE25-.LFB25
	.uleb128 0x1
	.byte	0x9c
	.long	0x1cb
	.uleb128 0xc
	.string	"m"
	.byte	0x1
	.byte	0x2f
	.long	0x129
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0xd
	.long	.LVL7
	.long	0x220
	.uleb128 0xe
	.uleb128 0x2
	.byte	0x74
	.sleb128 0
	.uleb128 0x3
	.byte	0x91
	.sleb128 0
	.byte	0x6
	.byte	0
	.byte	0
	.uleb128 0x10
	.long	.LASF22
	.byte	0x3
	.byte	0xa6
	.long	0x50
	.long	0x1e5
	.uleb128 0x11
	.long	0x1e5
	.uleb128 0x11
	.long	0x1eb
	.byte	0
	.uleb128 0xf
	.byte	0x4
	.long	0xce
	.uleb128 0xf
	.byte	0x4
	.long	0x1f1
	.uleb128 0x12
	.long	0xd9
	.uleb128 0x10
	.long	.LASF23
	.byte	0x3
	.byte	0xa8
	.long	0x50
	.long	0x20b
	.uleb128 0x11
	.long	0x1e5
	.byte	0
	.uleb128 0x10
	.long	.LASF24
	.byte	0x3
	.byte	0xa9
	.long	0x50
	.long	0x220
	.uleb128 0x11
	.long	0x1e5
	.byte	0
	.uleb128 0x13
	.long	.LASF31
	.byte	0x3
	.byte	0xaa
	.long	0x50
	.uleb128 0x11
	.long	0x1e5
	.byte	0
	.byte	0
	.section	.debug_abbrev,"",@progbits
.Ldebug_abbrev0:
	.uleb128 0x1
	.uleb128 0x11
	.byte	0x1
	.uleb128 0x25
	.uleb128 0xe
	.uleb128 0x13
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1b
	.uleb128 0xe
	.uleb128 0x55
	.uleb128 0x17
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x10
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x2
	.uleb128 0x39
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x18
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x4
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0x8
	.byte	0
	.byte	0
	.uleb128 0x5
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.byte	0
	.byte	0
	.uleb128 0x6
	.uleb128 0x3b
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.byte	0
	.byte	0
	.uleb128 0x7
	.uleb128 0x13
	.byte	0x1
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x6e
	.uleb128 0xe
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x8
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x9
	.uleb128 0x35
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xa
	.uleb128 0x16
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xb
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x2117
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xc
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0xd
	.uleb128 0x4109
	.byte	0x1
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x31
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xe
	.uleb128 0x410a
	.byte	0
	.uleb128 0x2
	.uleb128 0x18
	.uleb128 0x2111
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0xf
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x10
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3c
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x11
	.uleb128 0x5
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x12
	.uleb128 0x26
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x13
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3c
	.uleb128 0x19
	.byte	0
	.byte	0
	.byte	0
	.section	.debug_aranges,"",@progbits
	.long	0x34
	.value	0x2
	.long	.Ldebug_info0
	.byte	0x4
	.byte	0
	.value	0
	.value	0
	.long	.LFB22
	.long	.LFE22-.LFB22
	.long	.LFB23
	.long	.LFE23-.LFB23
	.long	.LFB24
	.long	.LFE24-.LFB24
	.long	.LFB25
	.long	.LFE25-.LFB25
	.long	0
	.long	0
	.section	.debug_ranges,"",@progbits
.Ldebug_ranges0:
	.long	.LFB22
	.long	.LFE22
	.long	.LFB23
	.long	.LFE23
	.long	.LFB24
	.long	.LFE24
	.long	.LFB25
	.long	.LFE25
	.long	0
	.long	0
	.section	.debug_line,"",@progbits
.Ldebug_line0:
	.section	.debug_str,"MS",@progbits,1
.LASF23:
	.string	"pthread_mutex_destroy"
.LASF30:
	.string	"value"
.LASF24:
	.string	"pthread_mutex_lock"
.LASF28:
	.string	"decltype(nullptr)"
.LASF31:
	.string	"pthread_mutex_unlock"
.LASF15:
	.string	"pthread_mutex_t"
.LASF7:
	.string	"unsigned char"
.LASF2:
	.string	"_STL"
.LASF19:
	.string	"MutexDestroy"
.LASF11:
	.string	"long unsigned int"
.LASF9:
	.string	"short unsigned int"
.LASF0:
	.string	"__std_alias"
.LASF25:
	.string	"GNU C++ 4.9.x 20150123 (prerelease) -fpreprocessed -mssse3 -fno-short-enums -mbionic -fPIC -mtune=intel -march=i686 -g -g -O2 -std=c++11 -ffunction-sections -funwind-tables -fstack-protector-strong -fno-exceptions -frtti"
.LASF1:
	.string	"stlport"
.LASF3:
	.string	"unsigned int"
.LASF10:
	.string	"long long unsigned int"
.LASF20:
	.string	"MutexLock"
.LASF18:
	.string	"MutexCreate"
.LASF14:
	.string	"sizetype"
.LASF4:
	.string	"long long int"
.LASF13:
	.string	"char"
.LASF16:
	.string	"pthread_mutexattr_t"
.LASF8:
	.string	"short int"
.LASF26:
	.string	"jni/tracer/../util/Mutex.cpp"
.LASF29:
	.string	"15pthread_mutex_t"
.LASF21:
	.string	"MutexUnlock"
.LASF12:
	.string	"long int"
.LASF22:
	.string	"pthread_mutex_init"
.LASF5:
	.string	"long double"
.LASF6:
	.string	"signed char"
.LASF27:
	.string	"C:\\\\cygwin64\\\\home\\\\Administrator\\\\C\\\\androidX86"
.LASF17:
	.string	"Mutex"
	.ident	"GCC: (GNU) 4.9.x 20150123 (prerelease)"
	.section	.note.GNU-stack,"",@progbits
