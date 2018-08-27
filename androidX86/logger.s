	.file	"logger.cpp"
	.text
.Ltext0:
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"a+"
	.section	.text.unlikely._ZN6LoggerC2EPcb,"ax",@progbits
	.align 2
.LCOLDB1:
	.section	.text._ZN6LoggerC2EPcb,"ax",@progbits
.LHOTB1:
	.align 2
	.p2align 4,,15
	.section	.text.unlikely._ZN6LoggerC2EPcb
.Ltext_cold0:
	.section	.text._ZN6LoggerC2EPcb
	.globl	_ZN6LoggerC2EPcb
	.type	_ZN6LoggerC2EPcb, @function
_ZN6LoggerC2EPcb:
.LFB30:
	.file 1 "jni/scrcap/../util/logger.cpp"
	.loc 1 11 0
	.cfi_startproc
.LVL0:
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	pushl	%edi
	.cfi_def_cfa_offset 12
	.cfi_offset 7, -12
	pushl	%esi
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	pushl	%ebx
	.cfi_def_cfa_offset 20
	.cfi_offset 3, -20
	call	__x86.get_pc_thunk.bx
	addl	$_GLOBAL_OFFSET_TABLE_, %ebx
	leal	-28(%esp), %esp
	.cfi_def_cfa_offset 48
	.loc 1 11 0
	movl	48(%esp), %esi
	movl	52(%esp), %edi
	movl	56(%esp), %ebp
.LBB17:
	.loc 1 13 0
	movl	%esi, (%esp)
	call	MutexCreate@PLT
.LVL1:
	.loc 1 14 0
	testl	%edi, %edi
	je	.L9
	.loc 1 17 0
	movl	%ebp, %eax
	movb	%al, 8(%esi)
	.loc 1 18 0
	leal	.LC0@GOTOFF(%ebx), %eax
	movl	%eax, 4(%esp)
	movl	%edi, (%esp)
	call	fopen@PLT
.LVL2:
	movl	%eax, 4(%esi)
	testl	%eax, %eax
	je	.L1
	.loc 1 19 0
	movl	$511, 4(%esp)
	movl	%edi, (%esp)
	call	chmod@PLT
.LVL3:
.L1:
.LBE17:
	.loc 1 22 0
	leal	28(%esp), %esp
	.cfi_remember_state
	.cfi_def_cfa_offset 20
	popl	%ebx
	.cfi_restore 3
	.cfi_def_cfa_offset 16
	popl	%esi
	.cfi_restore 6
	.cfi_def_cfa_offset 12
	popl	%edi
	.cfi_restore 7
	.cfi_def_cfa_offset 8
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa_offset 4
	ret
	.p2align 4,,7
	.p2align 3
.L9:
	.cfi_restore_state
.LBB18:
	.loc 1 15 0
	movl	__sF@GOT(%ebx), %eax
	leal	84(%eax), %eax
	movl	%eax, 4(%esi)
.LBE18:
	.loc 1 22 0
	leal	28(%esp), %esp
	.cfi_def_cfa_offset 20
	popl	%ebx
	.cfi_restore 3
	.cfi_def_cfa_offset 16
	popl	%esi
	.cfi_restore 6
	.cfi_def_cfa_offset 12
	popl	%edi
	.cfi_restore 7
	.cfi_def_cfa_offset 8
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa_offset 4
	ret
	.cfi_endproc
.LFE30:
	.size	_ZN6LoggerC2EPcb, .-_ZN6LoggerC2EPcb
	.section	.text.unlikely._ZN6LoggerC2EPcb
.LCOLDE1:
	.section	.text._ZN6LoggerC2EPcb
.LHOTE1:
	.globl	_ZN6LoggerC1EPcb
	.set	_ZN6LoggerC1EPcb,_ZN6LoggerC2EPcb
	.section	.text.unlikely._ZN6LoggerC2Ev,"ax",@progbits
	.align 2
.LCOLDB2:
	.section	.text._ZN6LoggerC2Ev,"ax",@progbits
.LHOTB2:
	.align 2
	.p2align 4,,15
	.globl	_ZN6LoggerC2Ev
	.type	_ZN6LoggerC2Ev, @function
_ZN6LoggerC2Ev:
.LFB33:
	.loc 1 24 0
	.cfi_startproc
.LVL4:
	pushl	%esi
	.cfi_def_cfa_offset 8
	.cfi_offset 6, -8
	pushl	%ebx
	.cfi_def_cfa_offset 12
	.cfi_offset 3, -12
	call	__x86.get_pc_thunk.bx
	addl	$_GLOBAL_OFFSET_TABLE_, %ebx
	leal	-20(%esp), %esp
	.cfi_def_cfa_offset 32
	.loc 1 24 0
	movl	32(%esp), %esi
.LBB19:
	.loc 1 26 0
	movl	%esi, (%esp)
	call	MutexCreate@PLT
.LVL5:
	.loc 1 27 0
	movl	__sF@GOT(%ebx), %eax
	.loc 1 28 0
	movb	$1, 8(%esi)
	.loc 1 27 0
	leal	84(%eax), %eax
	movl	%eax, 4(%esi)
.LBE19:
	.loc 1 30 0
	leal	20(%esp), %esp
	.cfi_def_cfa_offset 12
	popl	%ebx
	.cfi_restore 3
	.cfi_def_cfa_offset 8
	popl	%esi
	.cfi_restore 6
	.cfi_def_cfa_offset 4
	ret
	.cfi_endproc
.LFE33:
	.size	_ZN6LoggerC2Ev, .-_ZN6LoggerC2Ev
	.section	.text.unlikely._ZN6LoggerC2Ev
.LCOLDE2:
	.section	.text._ZN6LoggerC2Ev
.LHOTE2:
	.globl	_ZN6LoggerC1Ev
	.set	_ZN6LoggerC1Ev,_ZN6LoggerC2Ev
	.section	.text.unlikely._ZN6LoggerD2Ev,"ax",@progbits
	.align 2
.LCOLDB3:
	.section	.text._ZN6LoggerD2Ev,"ax",@progbits
.LHOTB3:
	.align 2
	.p2align 4,,15
	.globl	_ZN6LoggerD2Ev
	.type	_ZN6LoggerD2Ev, @function
_ZN6LoggerD2Ev:
.LFB36:
	.loc 1 32 0
	.cfi_startproc
.LVL6:
	pushl	%ebx
	.cfi_def_cfa_offset 8
	.cfi_offset 3, -8
	call	__x86.get_pc_thunk.bx
	addl	$_GLOBAL_OFFSET_TABLE_, %ebx
	leal	-24(%esp), %esp
	.cfi_def_cfa_offset 32
.LBB20:
	.loc 1 34 0
	movl	32(%esp), %eax
	movl	4(%eax), %eax
	.loc 1 35 0
	testl	%eax, %eax
	je	.L12
	movl	__sF@GOT(%ebx), %edx
	leal	84(%edx), %edx
	cmpl	%edx, %eax
	je	.L12
	.loc 1 36 0
	movl	%eax, (%esp)
	call	fclose@PLT
.LVL7:
.L12:
.LBE20:
	.loc 1 39 0
	leal	24(%esp), %esp
	.cfi_def_cfa_offset 8
	popl	%ebx
	.cfi_restore 3
	.cfi_def_cfa_offset 4
	ret
	.cfi_endproc
.LFE36:
	.size	_ZN6LoggerD2Ev, .-_ZN6LoggerD2Ev
	.section	.text.unlikely._ZN6LoggerD2Ev
.LCOLDE3:
	.section	.text._ZN6LoggerD2Ev
.LHOTE3:
	.globl	_ZN6LoggerD1Ev
	.set	_ZN6LoggerD1Ev,_ZN6LoggerD2Ev
	.section	.rodata.str1.1
.LC4:
	.string	"%02X "
	.section	.text.unlikely._ZN6Logger5toHexEPhi,"ax",@progbits
	.align 2
.LCOLDB5:
	.section	.text._ZN6Logger5toHexEPhi,"ax",@progbits
.LHOTB5:
	.align 2
	.p2align 4,,15
	.globl	_ZN6Logger5toHexEPhi
	.type	_ZN6Logger5toHexEPhi, @function
_ZN6Logger5toHexEPhi:
.LFB38:
	.loc 1 42 0
	.cfi_startproc
.LVL8:
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	pushl	%edi
	.cfi_def_cfa_offset 12
	.cfi_offset 7, -12
	pushl	%esi
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	pushl	%ebx
	.cfi_def_cfa_offset 20
	.cfi_offset 3, -20
	call	__x86.get_pc_thunk.bx
	addl	$_GLOBAL_OFFSET_TABLE_, %ebx
	leal	-92(%esp), %esp
	.cfi_def_cfa_offset 112
	leal	_ZZN6Logger5toHexEPhiE3tmp@GOTOFF(%ebx), %edi
	.loc 1 42 0
	movl	112(%esp), %eax
	movl	116(%esp), %ecx
	movl	%gs:20, %edx
	movl	%edx, 76(%esp)
	xorl	%edx, %edx
.LBB21:
	.loc 1 46 0
	movl	%eax, (%esp)
.LBE21:
	.loc 1 42 0
	movl	%eax, 28(%esp)
.LBB23:
	.loc 1 45 0
	movb	$0, _ZZN6Logger5toHexEPhiE3tmp@GOTOFF(%ebx)
.LBE23:
	.loc 1 42 0
	movl	%ecx, 20(%esp)
.LBB24:
	.loc 1 46 0
	call	MutexLock@PLT
.LVL9:
.LBB22:
	.loc 1 47 0 discriminator 1
	movl	120(%esp), %eax
	testl	%eax, %eax
	jle	.L23
	leal	.LC4@GOTOFF(%ebx), %eax
	xorl	%ebp, %ebp
	leal	44(%esp), %esi
	leal	_ZZN6Logger5toHexEPhiE3tmp@GOTOFF(%ebx), %edi
	movl	%eax, 24(%esp)
	jmp	.L22
.LVL10:
	.p2align 4,,7
	.p2align 3
.L41:
	cmpl	%ebp, 120(%esp)
	jle	.L26
.LVL11:
.L22:
	.loc 1 48 0
	movl	20(%esp), %eax
	movzbl	(%eax,%ebp), %eax
	.loc 1 47 0 discriminator 3
	addl	$1, %ebp
.LVL12:
	.loc 1 48 0
	movl	%esi, (%esp)
	movl	%eax, 8(%esp)
	movl	24(%esp), %eax
	movl	%eax, 4(%esp)
	call	sprintf@PLT
.LVL13:
	.loc 1 49 0
	movl	%esi, 4(%esp)
	movl	%edi, (%esp)
	call	strcat@PLT
.LVL14:
	.loc 1 47 0 discriminator 1
	cmpl	$15, %ebp
	jle	.L41
.L26:
.LBE22:
	.loc 1 51 0
	cmpl	$16, 120(%esp)
	jg	.L42
.LVL15:
.L23:
	.loc 1 54 0
	movl	28(%esp), %eax
	movl	%eax, (%esp)
	call	MutexUnlock@PLT
.LVL16:
.LBE24:
	.loc 1 56 0
	movl	76(%esp), %edx
	xorl	%gs:20, %edx
	movl	%edi, %eax
	jne	.L43
	leal	92(%esp), %esp
	.cfi_remember_state
	.cfi_def_cfa_offset 20
	popl	%ebx
	.cfi_restore 3
	.cfi_def_cfa_offset 16
	popl	%esi
	.cfi_restore 6
	.cfi_def_cfa_offset 12
	popl	%edi
	.cfi_restore 7
	.cfi_def_cfa_offset 8
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa_offset 4
	ret
.LVL17:
	.p2align 4,,7
	.p2align 3
.L42:
	.cfi_restore_state
.LBB25:
	.loc 1 52 0
	movl	%edi, %edx
.L27:
	movl	(%edx), %ecx
	addl	$4, %edx
	leal	-16843009(%ecx), %eax
	notl	%ecx
	andl	%ecx, %eax
	andl	$-2139062144, %eax
	je	.L27
	movl	%eax, %ecx
	shrl	$16, %ecx
	testl	$32896, %eax
	cmove	%ecx, %eax
	leal	2(%edx), %ecx
	cmove	%ecx, %edx
	addb	%al, %al
	sbbl	$3, %edx
	.loc 1 52 0 is_stmt 0 discriminator 1
	movl	$3026478, (%edx)
	jmp	.L23
.LVL18:
.L43:
.LBE25:
	.loc 1 56 0 is_stmt 1
	call	__stack_chk_fail_local
.LVL19:
	.cfi_endproc
.LFE38:
	.size	_ZN6Logger5toHexEPhi, .-_ZN6Logger5toHexEPhi
	.section	.text.unlikely._ZN6Logger5toHexEPhi
.LCOLDE5:
	.section	.text._ZN6Logger5toHexEPhi
.LHOTE5:
	.section	.rodata.str1.1
.LC6:
	.string	"[%5d] %s\n"
.LC7:
	.string	"%s [%5d] %s\n"
	.section	.text.unlikely._ZN6Logger6logStrEPc,"ax",@progbits
	.align 2
.LCOLDB8:
	.section	.text._ZN6Logger6logStrEPc,"ax",@progbits
.LHOTB8:
	.align 2
	.p2align 4,,15
	.globl	_ZN6Logger6logStrEPc
	.type	_ZN6Logger6logStrEPc, @function
_ZN6Logger6logStrEPc:
.LFB40:
	.loc 1 68 0
	.cfi_startproc
.LVL20:
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	pushl	%edi
	.cfi_def_cfa_offset 12
	.cfi_offset 7, -12
	pushl	%esi
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	pushl	%ebx
	.cfi_def_cfa_offset 20
	.cfi_offset 3, -20
	call	__x86.get_pc_thunk.bx
	addl	$_GLOBAL_OFFSET_TABLE_, %ebx
	leal	-60(%esp), %esp
	.cfi_def_cfa_offset 80
	.loc 1 68 0
	movl	80(%esp), %esi
	movl	%gs:20, %eax
	movl	%eax, 44(%esp)
	xorl	%eax, %eax
.LBB26:
	.loc 1 70 0
	movl	4(%esi), %eax
.LBE26:
	.loc 1 68 0
	movl	84(%esp), %ebp
.LBB29:
	.loc 1 70 0
	testl	%eax, %eax
	je	.L44
.LBB27:
	.loc 1 71 0
	movl	%esi, (%esp)
	.loc 1 73 0
	leal	40(%esp), %edi
	.loc 1 71 0
	call	MutexLock@PLT
.LVL21:
	.loc 1 73 0
	movl	%edi, (%esp)
	call	time@PLT
.LVL22:
	.loc 1 74 0
	movl	%edi, (%esp)
	call	ctime@PLT
.LVL23:
	.loc 1 75 0
	movl	%eax, (%esp)
	.loc 1 74 0
	movl	%eax, %edi
.LVL24:
	.loc 1 75 0
	call	strlen@PLT
.LVL25:
	movb	$0, -1(%edi,%eax)
	.loc 1 76 0
	cmpb	$0, 8(%esi)
	jne	.L50
	.loc 1 79 0
	call	gettid@PLT
.LVL26:
	.loc 1 79 0 is_stmt 0 discriminator 1
	movl	%eax, 12(%esp)
	leal	.LC7@GOTOFF(%ebx), %eax
	movl	%ebp, 16(%esp)
	movl	%edi, 8(%esp)
	movl	%eax, 4(%esp)
	movl	4(%esi), %eax
	movl	%eax, (%esp)
	call	fprintf@PLT
.LVL27:
.L47:
	.loc 1 81 0 is_stmt 1
	movl	4(%esi), %eax
	movl	%eax, (%esp)
	call	fflush@PLT
.LVL28:
	.loc 1 82 0
	movl	%esi, (%esp)
	call	MutexUnlock@PLT
.LVL29:
.L44:
.LBE27:
.LBE29:
	.loc 1 84 0
	movl	44(%esp), %eax
	xorl	%gs:20, %eax
	jne	.L51
	leal	60(%esp), %esp
	.cfi_remember_state
	.cfi_def_cfa_offset 20
	popl	%ebx
	.cfi_restore 3
	.cfi_def_cfa_offset 16
	popl	%esi
	.cfi_restore 6
	.cfi_def_cfa_offset 12
	popl	%edi
	.cfi_restore 7
	.cfi_def_cfa_offset 8
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa_offset 4
	ret
.LVL30:
	.p2align 4,,7
	.p2align 3
.L50:
	.cfi_restore_state
.LBB30:
.LBB28:
	.loc 1 77 0
	call	gettid@PLT
.LVL31:
	.loc 1 77 0 is_stmt 0 discriminator 1
	movl	%eax, 8(%esp)
	leal	.LC6@GOTOFF(%ebx), %eax
	movl	%ebp, 12(%esp)
	movl	%eax, 4(%esp)
	movl	4(%esi), %eax
	movl	%eax, (%esp)
	call	fprintf@PLT
.LVL32:
	jmp	.L47
.LVL33:
.L51:
.LBE28:
.LBE30:
	.loc 1 84 0 is_stmt 1
	call	__stack_chk_fail_local
.LVL34:
	.cfi_endproc
.LFE40:
	.size	_ZN6Logger6logStrEPc, .-_ZN6Logger6logStrEPc
	.section	.text.unlikely._ZN6Logger6logStrEPc
.LCOLDE8:
	.section	.text._ZN6Logger6logStrEPc
.LHOTE8:
	.section	.text.unlikely._ZN6Logger6printfEPcz,"ax",@progbits
	.align 2
.LCOLDB9:
	.section	.text._ZN6Logger6printfEPcz,"ax",@progbits
.LHOTB9:
	.align 2
	.p2align 4,,15
	.globl	_ZN6Logger6printfEPcz
	.type	_ZN6Logger6printfEPcz, @function
_ZN6Logger6printfEPcz:
.LFB39:
	.loc 1 59 0
	.cfi_startproc
.LVL35:
	pushl	%edi
	.cfi_def_cfa_offset 8
	.cfi_offset 7, -8
	pushl	%esi
	.cfi_def_cfa_offset 12
	.cfi_offset 6, -12
	pushl	%ebx
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
	call	__x86.get_pc_thunk.bx
	addl	$_GLOBAL_OFFSET_TABLE_, %ebx
	leal	-2080(%esp), %esp
	.cfi_def_cfa_offset 2096
	.loc 1 59 0
	movl	%gs:20, %eax
	movl	%eax, 2076(%esp)
	xorl	%eax, %eax
.LBB31:
	.loc 1 62 0
	leal	2104(%esp), %eax
.LVL36:
	.loc 1 63 0
	leal	28(%esp), %esi
	movl	%eax, 8(%esp)
	movl	2100(%esp), %eax
.LVL37:
.LBE31:
	.loc 1 59 0
	movl	2096(%esp), %edi
.LBB32:
	.loc 1 63 0
	movl	%esi, (%esp)
	movl	%eax, 4(%esp)
	call	vsprintf@PLT
.LVL38:
	.loc 1 65 0
	movl	%esi, 4(%esp)
	movl	%edi, (%esp)
	call	_ZN6Logger6logStrEPc@PLT
.LVL39:
.LBE32:
	.loc 1 66 0
	movl	2076(%esp), %eax
	xorl	%gs:20, %eax
	jne	.L55
	leal	2080(%esp), %esp
	.cfi_remember_state
	.cfi_def_cfa_offset 16
	popl	%ebx
	.cfi_restore 3
	.cfi_def_cfa_offset 12
	popl	%esi
	.cfi_restore 6
	.cfi_def_cfa_offset 8
	popl	%edi
	.cfi_restore 7
	.cfi_def_cfa_offset 4
	ret
.L55:
	.cfi_restore_state
	call	__stack_chk_fail_local
.LVL40:
	.cfi_endproc
.LFE39:
	.size	_ZN6Logger6printfEPcz, .-_ZN6Logger6printfEPcz
	.section	.text.unlikely._ZN6Logger6printfEPcz
.LCOLDE9:
	.section	.text._ZN6Logger6printfEPcz
.LHOTE9:
	.section	.rodata.str1.1
.LC10:
	.string	"   "
	.section	.text.unlikely._ZN6Logger6logHexEPhi,"ax",@progbits
	.align 2
.LCOLDB11:
	.section	.text._ZN6Logger6logHexEPhi,"ax",@progbits
.LHOTB11:
	.align 2
	.p2align 4,,15
	.globl	_ZN6Logger6logHexEPhi
	.type	_ZN6Logger6logHexEPhi, @function
_ZN6Logger6logHexEPhi:
.LFB41:
	.loc 1 90 0
	.cfi_startproc
.LVL41:
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	pushl	%edi
	.cfi_def_cfa_offset 12
	.cfi_offset 7, -12
	pushl	%esi
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	pushl	%ebx
	.cfi_def_cfa_offset 20
	.cfi_offset 3, -20
	call	__x86.get_pc_thunk.bx
	addl	$_GLOBAL_OFFSET_TABLE_, %ebx
	leal	-44(%esp), %esp
	.cfi_def_cfa_offset 64
	.loc 1 90 0
	movl	64(%esp), %edi
.LBB33:
.LBB34:
	.loc 1 92 0
	movl	4(%edi), %ecx
	testl	%ecx, %ecx
	je	.L56
.LBB35:
	.loc 1 93 0
	movl	%edi, (%esp)
	call	MutexLock@PLT
.LVL42:
.LBB36:
	.loc 1 94 0 discriminator 1
	movl	72(%esp), %edx
	testl	%edx, %edx
	jle	.L76
.LBB37:
	.loc 1 95 0
	movl	68(%esp), %eax
	movzbl	(%eax), %eax
	movl	%eax, 8(%esp)
	leal	.LC4@GOTOFF(%ebx), %eax
	movl	%eax, 4(%esp)
	movl	%eax, 28(%esp)
	movl	4(%edi), %eax
	movl	%eax, (%esp)
	call	fprintf@PLT
.LVL43:
	movl	68(%esp), %eax
.LBB38:
	.loc 1 96 0
	movl	$1, 24(%esp)
	movl	_ctype_@GOT(%ebx), %ebp
.LVL44:
	addl	$2, %eax
	movl	%eax, 20(%esp)
.LBE38:
.LBE37:
	.loc 1 94 0 discriminator 1
	movl	24(%esp), %eax
	cmpl	72(%esp), %eax
	je	.L77
.LVL45:
	.p2align 5,,30
	.p2align 3
.L64:
.LBB46:
	.loc 1 95 0
	movl	20(%esp), %esi
	movzbl	-1(%esi), %eax
	movl	%eax, 8(%esp)
	movl	28(%esp), %eax
	movl	%eax, 4(%esp)
	movl	4(%edi), %eax
	movl	%eax, (%esp)
	call	fprintf@PLT
.LVL46:
.LBB45:
	.loc 1 96 0
	addl	$1, 24(%esp)
.LVL47:
	movl	24(%esp), %eax
	testb	$15, %al
	jne	.L60
	leal	-16(%esi), %esi
	jmp	.L63
.LVL48:
	.p2align 4,,7
	.p2align 3
.L79:
.LBB39:
.LBB40:
.LBB41:
	.loc 1 100 0
	movl	4(%edi), %ecx
	addl	$1, %esi
.LVL49:
	.loc 1 99 0
	movl	%eax, (%esp)
.LVL50:
	.loc 1 100 0
	movl	%ecx, 4(%esp)
	call	fputc@PLT
.LVL51:
.LBE41:
	.loc 1 97 0 discriminator 1
	cmpl	20(%esp), %esi
	je	.L78
.L63:
.LVL52:
.LBB44:
.LBB42:
.LBB43:
	.file 2 "d:\\android-ndk-r12b\\platforms\\android-9\\arch-x86\\usr\\include\\ctype.h"
	.loc 2 104 0 discriminator 1
	movzbl	(%esi), %eax
.LVL53:
	movl	0(%ebp), %ecx
.LBE43:
.LBE42:
	.loc 1 99 0
	testb	$7, 1(%ecx,%eax)
	jne	.L79
	.loc 1 102 0
	movl	4(%edi), %eax
.LVL54:
	addl	$1, %esi
.LVL55:
	movl	$46, (%esp)
.LVL56:
	movl	%eax, 4(%esp)
	call	fputc@PLT
.LVL57:
.LBE44:
	.loc 1 97 0 discriminator 1
	cmpl	20(%esp), %esi
	jne	.L63
.L78:
.LBE40:
	.loc 1 105 0
	movl	4(%edi), %eax
	movl	$10, (%esp)
	movl	%eax, 4(%esp)
	call	fputc@PLT
.LVL58:
.L60:
.LBE39:
.LBE45:
.LBE46:
	.loc 1 94 0 discriminator 1
	movl	24(%esp), %eax
	addl	$1, 20(%esp)
	cmpl	72(%esp), %eax
	jne	.L64
.LVL59:
.L77:
.LBE36:
	.loc 1 108 0
	movl	72(%esp), %esi
	movl	72(%esp), %ebp
	sarl	$31, %esi
	shrl	$28, %esi
	addl	%esi, %ebp
	andl	$15, %ebp
	subl	%esi, %ebp
	.loc 1 110 0 discriminator 1
	movl	$16, %esi
	.loc 1 108 0
	movl	%ebp, 24(%esp)
.LVL60:
	.loc 1 110 0 discriminator 1
	subl	%ebp, %esi
	movl	%esi, 20(%esp)
.LVL61:
.L59:
	leal	.LC10@GOTOFF(%ebx), %ebp
	xorl	%esi, %esi
	movl	%ebp, %eax
	movl	%edi, %ebp
	movl	%eax, %edi
.LVL62:
	.p2align 5,,30
	.p2align 3
.L65:
	.loc 1 111 0
	movl	4(%ebp), %eax
	.loc 1 110 0 discriminator 3
	addl	$1, %esi
.LVL63:
	.loc 1 111 0
	movl	$3, 8(%esp)
	movl	$1, 4(%esp)
	movl	%eax, 12(%esp)
	movl	%edi, (%esp)
	call	fwrite@PLT
.LVL64:
	.loc 1 110 0 discriminator 1
	cmpl	20(%esp), %esi
	jne	.L65
.LBB47:
	.loc 1 114 0 discriminator 1
	movl	24(%esp), %eax
	movl	%ebp, %edi
.LVL65:
	testl	%eax, %eax
	jle	.L70
	movl	72(%esp), %ebp
	movl	68(%esp), %eax
.LVL66:
	movl	_ctype_@GOT(%ebx), %esi
	subl	24(%esp), %ebp
	addl	72(%esp), %eax
	addl	68(%esp), %ebp
	movl	%eax, 20(%esp)
	jmp	.L69
.LVL67:
	.p2align 4,,7
	.p2align 3
.L80:
.LBB48:
	.loc 1 117 0
	movl	4(%edi), %ecx
	addl	$1, %ebp
.LVL68:
	.loc 1 116 0
	movl	%eax, (%esp)
.LVL69:
	.loc 1 117 0
	movl	%ecx, 4(%esp)
	call	fputc@PLT
.LVL70:
.LBE48:
	.loc 1 114 0 discriminator 1
	cmpl	20(%esp), %ebp
	je	.L70
.L69:
.LVL71:
.LBB51:
.LBB49:
.LBB50:
	.loc 2 104 0 discriminator 1
	movzbl	0(%ebp), %eax
.LVL72:
.LBE50:
.LBE49:
	.loc 1 116 0
	movl	(%esi), %ecx
	testb	$7, 1(%ecx,%eax)
	jne	.L80
	.loc 1 119 0
	movl	4(%edi), %eax
.LVL73:
	addl	$1, %ebp
.LVL74:
	movl	$46, (%esp)
.LVL75:
	movl	%eax, 4(%esp)
	call	fputc@PLT
.LVL76:
.LBE51:
	.loc 1 114 0 discriminator 1
	cmpl	20(%esp), %ebp
	jne	.L69
.L70:
.LBE47:
	.loc 1 122 0
	movl	4(%edi), %eax
	movl	$10, (%esp)
	movl	%eax, 4(%esp)
	call	fputc@PLT
.LVL77:
	.loc 1 123 0
	movl	4(%edi), %eax
	movl	%eax, (%esp)
	call	fflush@PLT
.LVL78:
	.loc 1 124 0
	movl	%edi, (%esp)
	call	MutexUnlock@PLT
.LVL79:
.L56:
.LBE35:
.LBE34:
.LBE33:
	.loc 1 126 0
	leal	44(%esp), %esp
	.cfi_remember_state
	.cfi_def_cfa_offset 20
	popl	%ebx
	.cfi_restore 3
	.cfi_def_cfa_offset 16
	popl	%esi
	.cfi_restore 6
	.cfi_def_cfa_offset 12
	popl	%edi
	.cfi_restore 7
	.cfi_def_cfa_offset 8
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa_offset 4
	ret
.LVL80:
.L76:
	.cfi_restore_state
.LBB55:
.LBB54:
.LBB53:
.LBB52:
	.loc 1 94 0
	movl	$0, 72(%esp)
.LBE52:
	.loc 1 108 0
	movl	$0, 24(%esp)
	.loc 1 110 0 discriminator 1
	movl	$16, 20(%esp)
	jmp	.L59
.LBE53:
.LBE54:
.LBE55:
	.cfi_endproc
.LFE41:
	.size	_ZN6Logger6logHexEPhi, .-_ZN6Logger6logHexEPhi
	.section	.text.unlikely._ZN6Logger6logHexEPhi
.LCOLDE11:
	.section	.text._ZN6Logger6logHexEPhi
.LHOTE11:
	.local	_ZZN6Logger5toHexEPhiE3tmp
	.comm	_ZZN6Logger5toHexEPhiE3tmp,1024000,64
	.section	.text.__x86.get_pc_thunk.bx,"axG",@progbits,__x86.get_pc_thunk.bx,comdat
	.globl	__x86.get_pc_thunk.bx
	.hidden	__x86.get_pc_thunk.bx
	.type	__x86.get_pc_thunk.bx, @function
__x86.get_pc_thunk.bx:
.LFB42:
	.cfi_startproc
	movl	(%esp), %ebx
	ret
	.cfi_endproc
.LFE42:
	.text
.Letext0:
	.section	.text.unlikely._ZN6LoggerC2EPcb
.Letext_cold0:
	.file 3 "D:/android-ndk-r12b/build//../sources/cxx-stl/stlport/stlport/stl/config/features.h"
	.file 4 "d:\\android-ndk-r12b\\toolchains\\x86-4.9\\prebuilt\\windows-x86_64\\lib\\gcc\\i686-linux-android\\4.9.x\\include\\stddef.h"
	.file 5 "d:\\android-ndk-r12b\\platforms\\android-9\\arch-x86\\usr\\include\\machine\\_types.h"
	.file 6 "d:\\android-ndk-r12b\\platforms\\android-9\\arch-x86\\usr\\include\\asm\\posix_types_32.h"
	.file 7 "d:\\android-ndk-r12b\\platforms\\android-9\\arch-x86\\usr\\include\\sys\\types.h"
	.file 8 "d:\\android-ndk-r12b\\toolchains\\x86-4.9\\prebuilt\\windows-x86_64\\lib\\gcc\\i686-linux-android\\4.9.x\\include\\stdarg.h"
	.file 9 "d:\\android-ndk-r12b\\platforms\\android-9\\arch-x86\\usr\\include\\stdio.h"
	.file 10 "d:\\android-ndk-r12b\\platforms\\android-9\\arch-x86\\usr\\include\\pthread.h"
	.file 11 "jni/scrcap/../util/Mutex.hpp"
	.file 12 "jni/scrcap/../util/logger.h"
	.file 13 "d:\\android-ndk-r12b\\platforms\\android-9\\arch-x86\\usr\\include\\sys\\stat.h"
	.file 14 "d:\\android-ndk-r12b\\platforms\\android-9\\arch-x86\\usr\\include\\string.h"
	.file 15 "d:\\android-ndk-r12b\\platforms\\android-9\\arch-x86\\usr\\include\\time.h"
	.file 16 "<built-in>"
	.file 17 "d:\\android-ndk-r12b\\platforms\\android-9\\arch-x86\\usr\\include\\unistd.h"
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.long	0xc7c
	.value	0x4
	.long	.Ldebug_abbrev0
	.byte	0x4
	.uleb128 0x1
	.long	.LASF96
	.byte	0x4
	.long	.LASF97
	.long	.LASF98
	.long	.Ldebug_ranges0+0xb8
	.long	0
	.long	.Ldebug_line0
	.uleb128 0x2
	.string	"std"
	.byte	0x10
	.byte	0
	.uleb128 0x3
	.long	.LASF0
	.byte	0x3
	.value	0x1a0
	.long	0x25
	.uleb128 0x3
	.long	.LASF1
	.byte	0x3
	.value	0x218
	.long	0x25
	.uleb128 0x3
	.long	.LASF2
	.byte	0x3
	.value	0x21c
	.long	0x25
	.uleb128 0x4
	.byte	0x4
	.byte	0x5
	.string	"int"
	.uleb128 0x5
	.long	.LASF13
	.byte	0x4
	.byte	0xd4
	.long	0x62
	.uleb128 0x6
	.byte	0x4
	.byte	0x7
	.long	.LASF3
	.uleb128 0x6
	.byte	0x8
	.byte	0x5
	.long	.LASF4
	.uleb128 0x6
	.byte	0x8
	.byte	0x4
	.long	.LASF5
	.uleb128 0x7
	.long	.LASF99
	.uleb128 0x6
	.byte	0x1
	.byte	0x6
	.long	.LASF6
	.uleb128 0x6
	.byte	0x1
	.byte	0x8
	.long	.LASF7
	.uleb128 0x6
	.byte	0x2
	.byte	0x5
	.long	.LASF8
	.uleb128 0x6
	.byte	0x2
	.byte	0x7
	.long	.LASF9
	.uleb128 0x6
	.byte	0x8
	.byte	0x7
	.long	.LASF10
	.uleb128 0x6
	.byte	0x4
	.byte	0x7
	.long	.LASF11
	.uleb128 0x6
	.byte	0x4
	.byte	0x5
	.long	.LASF12
	.uleb128 0x5
	.long	.LASF14
	.byte	0x5
	.byte	0x5e
	.long	0xb8
	.uleb128 0x8
	.byte	0x4
	.long	.LASF100
	.long	0xc2
	.uleb128 0x6
	.byte	0x1
	.byte	0x6
	.long	.LASF15
	.uleb128 0x9
	.byte	0x4
	.uleb128 0x6
	.byte	0x4
	.byte	0x7
	.long	.LASF16
	.uleb128 0x5
	.long	.LASF17
	.byte	0x6
	.byte	0x16
	.long	0x91
	.uleb128 0x5
	.long	.LASF18
	.byte	0x6
	.byte	0x19
	.long	0xa6
	.uleb128 0x5
	.long	.LASF19
	.byte	0x6
	.byte	0x1a
	.long	0x50
	.uleb128 0x5
	.long	.LASF20
	.byte	0x6
	.byte	0x23
	.long	0xa6
	.uleb128 0xa
	.byte	0x4
	.long	0xc2
	.uleb128 0x5
	.long	.LASF21
	.byte	0x7
	.byte	0x3f
	.long	0xd2
	.uleb128 0x5
	.long	.LASF22
	.byte	0x7
	.byte	0x43
	.long	0xdd
	.uleb128 0x5
	.long	.LASF23
	.byte	0x7
	.byte	0x48
	.long	0xe8
	.uleb128 0x5
	.long	.LASF24
	.byte	0x7
	.byte	0x5e
	.long	0xf3
	.uleb128 0x5
	.long	.LASF25
	.byte	0x8
	.byte	0x28
	.long	0xb8
	.uleb128 0x5
	.long	.LASF26
	.byte	0x9
	.byte	0x41
	.long	0x10f
	.uleb128 0xb
	.long	.LASF29
	.byte	0x8
	.byte	0x9
	.byte	0x4a
	.long	0x16b
	.uleb128 0xc
	.long	.LASF27
	.byte	0x9
	.byte	0x4b
	.long	0x16b
	.byte	0
	.uleb128 0xc
	.long	.LASF28
	.byte	0x9
	.byte	0x4c
	.long	0x50
	.byte	0x4
	.byte	0
	.uleb128 0xa
	.byte	0x4
	.long	0x83
	.uleb128 0xb
	.long	.LASF30
	.byte	0x54
	.byte	0x9
	.byte	0x6a
	.long	0x26b
	.uleb128 0xd
	.string	"_p"
	.byte	0x9
	.byte	0x6b
	.long	0x16b
	.byte	0
	.uleb128 0xd
	.string	"_r"
	.byte	0x9
	.byte	0x6c
	.long	0x50
	.byte	0x4
	.uleb128 0xd
	.string	"_w"
	.byte	0x9
	.byte	0x6d
	.long	0x50
	.byte	0x8
	.uleb128 0xc
	.long	.LASF31
	.byte	0x9
	.byte	0x6e
	.long	0x8a
	.byte	0xc
	.uleb128 0xc
	.long	.LASF32
	.byte	0x9
	.byte	0x6f
	.long	0x8a
	.byte	0xe
	.uleb128 0xd
	.string	"_bf"
	.byte	0x9
	.byte	0x70
	.long	0x146
	.byte	0x10
	.uleb128 0xc
	.long	.LASF33
	.byte	0x9
	.byte	0x71
	.long	0x50
	.byte	0x18
	.uleb128 0xc
	.long	.LASF34
	.byte	0x9
	.byte	0x74
	.long	0xc9
	.byte	0x1c
	.uleb128 0xc
	.long	.LASF35
	.byte	0x9
	.byte	0x75
	.long	0x27a
	.byte	0x20
	.uleb128 0xc
	.long	.LASF36
	.byte	0x9
	.byte	0x76
	.long	0x299
	.byte	0x24
	.uleb128 0xc
	.long	.LASF37
	.byte	0x9
	.byte	0x77
	.long	0x2b8
	.byte	0x28
	.uleb128 0xc
	.long	.LASF38
	.byte	0x9
	.byte	0x78
	.long	0x2e2
	.byte	0x2c
	.uleb128 0xc
	.long	.LASF39
	.byte	0x9
	.byte	0x7b
	.long	0x146
	.byte	0x30
	.uleb128 0xd
	.string	"_up"
	.byte	0x9
	.byte	0x7d
	.long	0x16b
	.byte	0x38
	.uleb128 0xd
	.string	"_ur"
	.byte	0x9
	.byte	0x7e
	.long	0x50
	.byte	0x3c
	.uleb128 0xc
	.long	.LASF40
	.byte	0x9
	.byte	0x81
	.long	0x2e8
	.byte	0x40
	.uleb128 0xc
	.long	.LASF41
	.byte	0x9
	.byte	0x82
	.long	0x2f8
	.byte	0x43
	.uleb128 0xd
	.string	"_lb"
	.byte	0x9
	.byte	0x85
	.long	0x146
	.byte	0x44
	.uleb128 0xc
	.long	.LASF42
	.byte	0x9
	.byte	0x88
	.long	0x50
	.byte	0x4c
	.uleb128 0xc
	.long	.LASF43
	.byte	0x9
	.byte	0x89
	.long	0x13b
	.byte	0x50
	.byte	0
	.uleb128 0xe
	.long	0x50
	.long	0x27a
	.uleb128 0xf
	.long	0xc9
	.byte	0
	.uleb128 0xa
	.byte	0x4
	.long	0x26b
	.uleb128 0xe
	.long	0x50
	.long	0x299
	.uleb128 0xf
	.long	0xc9
	.uleb128 0xf
	.long	0xfe
	.uleb128 0xf
	.long	0x50
	.byte	0
	.uleb128 0xa
	.byte	0x4
	.long	0x280
	.uleb128 0xe
	.long	0x13b
	.long	0x2b8
	.uleb128 0xf
	.long	0xc9
	.uleb128 0xf
	.long	0x13b
	.uleb128 0xf
	.long	0x50
	.byte	0
	.uleb128 0xa
	.byte	0x4
	.long	0x29f
	.uleb128 0xe
	.long	0x50
	.long	0x2d7
	.uleb128 0xf
	.long	0xc9
	.uleb128 0xf
	.long	0x2d7
	.uleb128 0xf
	.long	0x50
	.byte	0
	.uleb128 0xa
	.byte	0x4
	.long	0x2dd
	.uleb128 0x10
	.long	0xc2
	.uleb128 0xa
	.byte	0x4
	.long	0x2be
	.uleb128 0x11
	.long	0x83
	.long	0x2f8
	.uleb128 0x12
	.long	0xcb
	.byte	0x2
	.byte	0
	.uleb128 0x11
	.long	0x83
	.long	0x308
	.uleb128 0x12
	.long	0xcb
	.byte	0
	.byte	0
	.uleb128 0x5
	.long	.LASF44
	.byte	0x9
	.byte	0x8a
	.long	0x171
	.uleb128 0x11
	.long	0xc2
	.long	0x323
	.uleb128 0x12
	.long	0xcb
	.byte	0x1f
	.byte	0
	.uleb128 0x5
	.long	.LASF45
	.byte	0x8
	.byte	0x62
	.long	0x130
	.uleb128 0x13
	.byte	0x4
	.byte	0xa
	.byte	0x29
	.long	.LASF101
	.long	0x347
	.uleb128 0xc
	.long	.LASF46
	.byte	0xa
	.byte	0x2a
	.long	0x347
	.byte	0
	.byte	0
	.uleb128 0x14
	.long	0x50
	.uleb128 0x5
	.long	.LASF47
	.byte	0xa
	.byte	0x2b
	.long	0x32e
	.uleb128 0x5
	.long	.LASF48
	.byte	0xb
	.byte	0x16
	.long	0x34c
	.uleb128 0x15
	.long	.LASF51
	.byte	0xc
	.byte	0xc
	.byte	0x5
	.long	0x479
	.uleb128 0x16
	.long	.LASF49
	.byte	0xc
	.byte	0x7
	.long	0x357
	.byte	0
	.byte	0x1
	.uleb128 0x17
	.string	"fp"
	.byte	0xc
	.byte	0x8
	.long	0x479
	.byte	0x4
	.byte	0x1
	.uleb128 0x16
	.long	.LASF50
	.byte	0xc
	.byte	0x9
	.long	0x47f
	.byte	0x8
	.byte	0x1
	.uleb128 0x18
	.long	.LASF51
	.byte	0xc
	.byte	0xa
	.long	.LASF52
	.byte	0x1
	.long	0x3a8
	.long	0x3b8
	.uleb128 0x19
	.long	0x486
	.uleb128 0xf
	.long	0xfe
	.uleb128 0xf
	.long	0x47f
	.byte	0
	.uleb128 0x18
	.long	.LASF51
	.byte	0xc
	.byte	0xb
	.long	.LASF53
	.byte	0x1
	.long	0x3cc
	.long	0x3d2
	.uleb128 0x19
	.long	0x486
	.byte	0
	.uleb128 0x18
	.long	.LASF54
	.byte	0xc
	.byte	0xc
	.long	.LASF55
	.byte	0x1
	.long	0x3e6
	.long	0x3f1
	.uleb128 0x19
	.long	0x486
	.uleb128 0x19
	.long	0x50
	.byte	0
	.uleb128 0x18
	.long	.LASF56
	.byte	0xc
	.byte	0xd
	.long	.LASF57
	.byte	0x1
	.long	0x405
	.long	0x410
	.uleb128 0x19
	.long	0x486
	.uleb128 0xf
	.long	0xfe
	.byte	0
	.uleb128 0x18
	.long	.LASF58
	.byte	0xc
	.byte	0xe
	.long	.LASF59
	.byte	0x1
	.long	0x424
	.long	0x434
	.uleb128 0x19
	.long	0x486
	.uleb128 0xf
	.long	0x16b
	.uleb128 0xf
	.long	0x50
	.byte	0
	.uleb128 0x1a
	.long	.LASF102
	.byte	0xc
	.byte	0xf
	.long	.LASF103
	.long	0xfe
	.byte	0x1
	.long	0x44c
	.long	0x45c
	.uleb128 0x19
	.long	0x486
	.uleb128 0xf
	.long	0x16b
	.uleb128 0xf
	.long	0x50
	.byte	0
	.uleb128 0x1b
	.long	.LASF104
	.byte	0xc
	.byte	0x10
	.long	.LASF105
	.byte	0x1
	.long	0x46c
	.uleb128 0x19
	.long	0x486
	.uleb128 0xf
	.long	0xfe
	.uleb128 0x1c
	.byte	0
	.byte	0
	.uleb128 0xa
	.byte	0x4
	.long	0x308
	.uleb128 0x6
	.byte	0x1
	.byte	0x2
	.long	.LASF60
	.uleb128 0xa
	.byte	0x4
	.long	0x362
	.uleb128 0x1d
	.long	.LASF77
	.byte	0x2
	.byte	0x66
	.long	0x50
	.byte	0x3
	.long	0x4a6
	.uleb128 0x1e
	.string	"c"
	.byte	0x2
	.byte	0x66
	.long	0x50
	.byte	0
	.uleb128 0x1f
	.long	0x394
	.byte	0x1
	.byte	0xb
	.byte	0
	.long	0x4b6
	.long	0x4d6
	.uleb128 0x20
	.long	.LASF63
	.long	0x4d6
	.uleb128 0x21
	.long	.LASF61
	.byte	0x1
	.byte	0xb
	.long	0xfe
	.uleb128 0x21
	.long	.LASF62
	.byte	0x1
	.byte	0xb
	.long	0x47f
	.byte	0
	.uleb128 0x10
	.long	0x486
	.uleb128 0x22
	.long	0x4a6
	.long	.LASF64
	.long	.LFB30
	.long	.LFE30-.LFB30
	.uleb128 0x1
	.byte	0x9c
	.long	0x4f6
	.long	0x55c
	.uleb128 0x23
	.long	0x4b6
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x23
	.long	0x4bf
	.uleb128 0x2
	.byte	0x91
	.sleb128 4
	.uleb128 0x23
	.long	0x4ca
	.uleb128 0x2
	.byte	0x91
	.sleb128 8
	.uleb128 0x24
	.long	.LVL1
	.long	0xacf
	.long	0x523
	.uleb128 0x25
	.uleb128 0x2
	.byte	0x74
	.sleb128 0
	.uleb128 0x2
	.byte	0x76
	.sleb128 0
	.byte	0
	.uleb128 0x24
	.long	.LVL2
	.long	0xae6
	.long	0x542
	.uleb128 0x25
	.uleb128 0x2
	.byte	0x74
	.sleb128 0
	.uleb128 0x2
	.byte	0x77
	.sleb128 0
	.uleb128 0x25
	.uleb128 0x2
	.byte	0x74
	.sleb128 4
	.uleb128 0x5
	.byte	0x3
	.long	.LC0
	.byte	0
	.uleb128 0x26
	.long	.LVL3
	.long	0xb00
	.uleb128 0x25
	.uleb128 0x2
	.byte	0x74
	.sleb128 0
	.uleb128 0x2
	.byte	0x77
	.sleb128 0
	.uleb128 0x25
	.uleb128 0x2
	.byte	0x74
	.sleb128 4
	.uleb128 0x3
	.byte	0xa
	.value	0x1ff
	.byte	0
	.byte	0
	.uleb128 0x1f
	.long	0x3b8
	.byte	0x1
	.byte	0x18
	.byte	0
	.long	0x56c
	.long	0x576
	.uleb128 0x20
	.long	.LASF63
	.long	0x4d6
	.byte	0
	.uleb128 0x22
	.long	0x55c
	.long	.LASF65
	.long	.LFB33
	.long	.LFE33-.LFB33
	.uleb128 0x1
	.byte	0x9c
	.long	0x591
	.long	0x5ab
	.uleb128 0x23
	.long	0x56c
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x26
	.long	.LVL5
	.long	0xacf
	.uleb128 0x25
	.uleb128 0x2
	.byte	0x74
	.sleb128 0
	.uleb128 0x2
	.byte	0x76
	.sleb128 0
	.byte	0
	.byte	0
	.uleb128 0x1f
	.long	0x3d2
	.byte	0x1
	.byte	0x20
	.byte	0
	.long	0x5bb
	.long	0x5ce
	.uleb128 0x20
	.long	.LASF63
	.long	0x4d6
	.uleb128 0x20
	.long	.LASF66
	.long	0x5ce
	.byte	0
	.uleb128 0x10
	.long	0x50
	.uleb128 0x22
	.long	0x5ab
	.long	.LASF67
	.long	.LFB36
	.long	.LFE36-.LFB36
	.uleb128 0x1
	.byte	0x9c
	.long	0x5ee
	.long	0x600
	.uleb128 0x23
	.long	0x5bb
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x27
	.long	.LVL7
	.long	0xb1a
	.byte	0
	.uleb128 0x28
	.long	0x434
	.byte	0x1
	.byte	0x29
	.long	.LFB38
	.long	.LFE38-.LFB38
	.uleb128 0x1
	.byte	0x9c
	.long	0x619
	.long	0x6eb
	.uleb128 0x29
	.long	.LASF63
	.long	0x4d6
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x2a
	.string	"p"
	.byte	0x1
	.byte	0x29
	.long	0x16b
	.uleb128 0x2
	.byte	0x91
	.sleb128 4
	.uleb128 0x2a
	.string	"len"
	.byte	0x1
	.byte	0x29
	.long	0x50
	.uleb128 0x2
	.byte	0x91
	.sleb128 8
	.uleb128 0x2b
	.long	.Ldebug_ranges0+0
	.long	0x6e1
	.uleb128 0x2c
	.string	"tmp"
	.byte	0x1
	.byte	0x2b
	.long	0x6eb
	.uleb128 0x5
	.byte	0x3
	.long	_ZZN6Logger5toHexEPhiE3tmp
	.uleb128 0x2c
	.string	"t"
	.byte	0x1
	.byte	0x2c
	.long	0x313
	.uleb128 0x3
	.byte	0x91
	.sleb128 -68
	.uleb128 0x2d
	.long	.LBB22
	.long	.LBE22-.LBB22
	.long	0x6b7
	.uleb128 0x2e
	.string	"i"
	.byte	0x1
	.byte	0x2f
	.long	0x50
	.long	.LLST0
	.uleb128 0x24
	.long	.LVL13
	.long	0xb2f
	.long	0x69e
	.uleb128 0x25
	.uleb128 0x2
	.byte	0x74
	.sleb128 0
	.uleb128 0x2
	.byte	0x76
	.sleb128 0
	.uleb128 0x25
	.uleb128 0x2
	.byte	0x74
	.sleb128 4
	.uleb128 0x4
	.byte	0x91
	.sleb128 -88
	.byte	0x6
	.byte	0
	.uleb128 0x26
	.long	.LVL14
	.long	0xb4a
	.uleb128 0x25
	.uleb128 0x2
	.byte	0x74
	.sleb128 0
	.uleb128 0x2
	.byte	0x77
	.sleb128 0
	.uleb128 0x25
	.uleb128 0x2
	.byte	0x74
	.sleb128 4
	.uleb128 0x2
	.byte	0x76
	.sleb128 0
	.byte	0
	.byte	0
	.uleb128 0x24
	.long	.LVL9
	.long	0xb64
	.long	0x6cd
	.uleb128 0x25
	.uleb128 0x2
	.byte	0x74
	.sleb128 0
	.uleb128 0x3
	.byte	0x91
	.sleb128 0
	.byte	0x6
	.byte	0
	.uleb128 0x26
	.long	.LVL16
	.long	0xb75
	.uleb128 0x25
	.uleb128 0x2
	.byte	0x74
	.sleb128 0
	.uleb128 0x4
	.byte	0x91
	.sleb128 -84
	.byte	0x6
	.byte	0
	.byte	0
	.uleb128 0x27
	.long	.LVL19
	.long	0xb86
	.byte	0
	.uleb128 0x11
	.long	0xc2
	.long	0x6fe
	.uleb128 0x2f
	.long	0xcb
	.long	0xf9fff
	.byte	0
	.uleb128 0x28
	.long	0x3f1
	.byte	0x1
	.byte	0x44
	.long	.LFB40
	.long	.LFE40-.LFB40
	.uleb128 0x1
	.byte	0x9c
	.long	0x717
	.long	0x823
	.uleb128 0x29
	.long	.LASF63
	.long	0x4d6
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x2a
	.string	"p"
	.byte	0x1
	.byte	0x44
	.long	0xfe
	.uleb128 0x2
	.byte	0x91
	.sleb128 4
	.uleb128 0x2b
	.long	.Ldebug_ranges0+0x28
	.long	0x819
	.uleb128 0x2c
	.string	"t"
	.byte	0x1
	.byte	0x48
	.long	0x125
	.uleb128 0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0x30
	.long	.LASF68
	.byte	0x1
	.byte	0x4a
	.long	0xfe
	.long	.LLST1
	.uleb128 0x24
	.long	.LVL21
	.long	0xb64
	.long	0x768
	.uleb128 0x25
	.uleb128 0x2
	.byte	0x74
	.sleb128 0
	.uleb128 0x2
	.byte	0x76
	.sleb128 0
	.byte	0
	.uleb128 0x24
	.long	.LVL22
	.long	0xb8b
	.long	0x77d
	.uleb128 0x25
	.uleb128 0x2
	.byte	0x74
	.sleb128 0
	.uleb128 0x2
	.byte	0x77
	.sleb128 0
	.byte	0
	.uleb128 0x24
	.long	.LVL23
	.long	0xba6
	.long	0x792
	.uleb128 0x25
	.uleb128 0x2
	.byte	0x74
	.sleb128 0
	.uleb128 0x2
	.byte	0x77
	.sleb128 0
	.byte	0
	.uleb128 0x24
	.long	.LVL25
	.long	0xbc6
	.long	0x7a7
	.uleb128 0x25
	.uleb128 0x2
	.byte	0x74
	.sleb128 0
	.uleb128 0x2
	.byte	0x77
	.sleb128 0
	.byte	0
	.uleb128 0x27
	.long	.LVL26
	.long	0xbdb
	.uleb128 0x24
	.long	.LVL27
	.long	0xbe6
	.long	0x7d6
	.uleb128 0x25
	.uleb128 0x2
	.byte	0x74
	.sleb128 4
	.uleb128 0x5
	.byte	0x3
	.long	.LC7
	.uleb128 0x25
	.uleb128 0x2
	.byte	0x74
	.sleb128 8
	.uleb128 0x2
	.byte	0x77
	.sleb128 0
	.uleb128 0x25
	.uleb128 0x2
	.byte	0x74
	.sleb128 16
	.uleb128 0x2
	.byte	0x75
	.sleb128 0
	.byte	0
	.uleb128 0x27
	.long	.LVL28
	.long	0xc01
	.uleb128 0x24
	.long	.LVL29
	.long	0xb75
	.long	0x7f4
	.uleb128 0x25
	.uleb128 0x2
	.byte	0x74
	.sleb128 0
	.uleb128 0x2
	.byte	0x76
	.sleb128 0
	.byte	0
	.uleb128 0x27
	.long	.LVL31
	.long	0xbdb
	.uleb128 0x26
	.long	.LVL32
	.long	0xbe6
	.uleb128 0x25
	.uleb128 0x2
	.byte	0x74
	.sleb128 4
	.uleb128 0x5
	.byte	0x3
	.long	.LC6
	.uleb128 0x25
	.uleb128 0x2
	.byte	0x74
	.sleb128 12
	.uleb128 0x2
	.byte	0x75
	.sleb128 0
	.byte	0
	.byte	0
	.uleb128 0x27
	.long	.LVL34
	.long	0xb86
	.byte	0
	.uleb128 0x28
	.long	0x45c
	.byte	0x1
	.byte	0x3a
	.long	.LFB39
	.long	.LFE39-.LFB39
	.uleb128 0x1
	.byte	0x9c
	.long	0x83c
	.long	0x8c5
	.uleb128 0x29
	.long	.LASF63
	.long	0x4d6
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x31
	.long	.LASF69
	.byte	0x1
	.byte	0x3a
	.long	0xfe
	.uleb128 0x2
	.byte	0x91
	.sleb128 4
	.uleb128 0x1c
	.uleb128 0x2b
	.long	.Ldebug_ranges0+0x40
	.long	0x8bb
	.uleb128 0x32
	.long	.LASF70
	.byte	0x1
	.byte	0x3c
	.long	0x8c5
	.uleb128 0x3
	.byte	0x91
	.sleb128 -2068
	.uleb128 0x30
	.long	.LASF71
	.byte	0x1
	.byte	0x3d
	.long	0x323
	.long	.LLST2
	.uleb128 0x24
	.long	.LVL38
	.long	0xc16
	.long	0x8a2
	.uleb128 0x25
	.uleb128 0x2
	.byte	0x74
	.sleb128 0
	.uleb128 0x2
	.byte	0x76
	.sleb128 0
	.uleb128 0x25
	.uleb128 0x2
	.byte	0x74
	.sleb128 4
	.uleb128 0x3
	.byte	0x91
	.sleb128 4
	.byte	0x6
	.uleb128 0x25
	.uleb128 0x2
	.byte	0x74
	.sleb128 8
	.uleb128 0x2
	.byte	0x91
	.sleb128 8
	.byte	0
	.uleb128 0x26
	.long	.LVL39
	.long	0x6fe
	.uleb128 0x25
	.uleb128 0x2
	.byte	0x74
	.sleb128 0
	.uleb128 0x2
	.byte	0x77
	.sleb128 0
	.uleb128 0x25
	.uleb128 0x2
	.byte	0x74
	.sleb128 4
	.uleb128 0x2
	.byte	0x76
	.sleb128 0
	.byte	0
	.byte	0
	.uleb128 0x27
	.long	.LVL40
	.long	0xb86
	.byte	0
	.uleb128 0x11
	.long	0xc2
	.long	0x8d6
	.uleb128 0x33
	.long	0xcb
	.value	0x7ff
	.byte	0
	.uleb128 0x28
	.long	0x410
	.byte	0x1
	.byte	0x59
	.long	.LFB41
	.long	.LFE41-.LFB41
	.uleb128 0x1
	.byte	0x9c
	.long	0x8ef
	.long	0xa8d
	.uleb128 0x29
	.long	.LASF63
	.long	0x4d6
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x2a
	.string	"p"
	.byte	0x1
	.byte	0x59
	.long	0x16b
	.uleb128 0x2
	.byte	0x91
	.sleb128 4
	.uleb128 0x2a
	.string	"len"
	.byte	0x1
	.byte	0x59
	.long	0x50
	.uleb128 0x2
	.byte	0x91
	.sleb128 8
	.uleb128 0x34
	.long	.Ldebug_ranges0+0x58
	.uleb128 0x2e
	.string	"i"
	.byte	0x1
	.byte	0x5b
	.long	0x50
	.long	.LLST3
	.uleb128 0x2e
	.string	"j"
	.byte	0x1
	.byte	0x5b
	.long	0x50
	.long	.LLST4
	.uleb128 0x34
	.long	.Ldebug_ranges0+0x70
	.uleb128 0x30
	.long	.LASF72
	.byte	0x1
	.byte	0x6c
	.long	0x50
	.long	.LLST5
	.uleb128 0x2b
	.long	.Ldebug_ranges0+0x88
	.long	0x997
	.uleb128 0x2e
	.string	"ch"
	.byte	0x1
	.byte	0x62
	.long	0x83
	.long	.LLST6
	.uleb128 0x35
	.long	0x48c
	.long	.LBB42
	.long	.LBE42-.LBB42
	.byte	0x1
	.byte	0x63
	.long	0x97c
	.uleb128 0x36
	.long	0x49c
	.long	.LLST7
	.byte	0
	.uleb128 0x27
	.long	.LVL51
	.long	0xc36
	.uleb128 0x26
	.long	.LVL57
	.long	0xc36
	.uleb128 0x25
	.uleb128 0x2
	.byte	0x74
	.sleb128 0
	.uleb128 0x2
	.byte	0x8
	.byte	0x2e
	.byte	0
	.byte	0
	.uleb128 0x2b
	.long	.Ldebug_ranges0+0xa0
	.long	0x9e6
	.uleb128 0x2e
	.string	"ch"
	.byte	0x1
	.byte	0x73
	.long	0x83
	.long	.LLST8
	.uleb128 0x35
	.long	0x48c
	.long	.LBB49
	.long	.LBE49-.LBB49
	.byte	0x1
	.byte	0x74
	.long	0x9cb
	.uleb128 0x36
	.long	0x49c
	.long	.LLST9
	.byte	0
	.uleb128 0x27
	.long	.LVL70
	.long	0xc36
	.uleb128 0x26
	.long	.LVL76
	.long	0xc36
	.uleb128 0x25
	.uleb128 0x2
	.byte	0x74
	.sleb128 0
	.uleb128 0x2
	.byte	0x8
	.byte	0x2e
	.byte	0
	.byte	0
	.uleb128 0x24
	.long	.LVL42
	.long	0xb64
	.long	0x9fb
	.uleb128 0x25
	.uleb128 0x2
	.byte	0x74
	.sleb128 0
	.uleb128 0x2
	.byte	0x77
	.sleb128 0
	.byte	0
	.uleb128 0x24
	.long	.LVL43
	.long	0xbe6
	.long	0xa11
	.uleb128 0x25
	.uleb128 0x2
	.byte	0x74
	.sleb128 4
	.uleb128 0x3
	.byte	0x91
	.sleb128 -36
	.byte	0x6
	.byte	0
	.uleb128 0x24
	.long	.LVL46
	.long	0xbe6
	.long	0xa27
	.uleb128 0x25
	.uleb128 0x2
	.byte	0x74
	.sleb128 4
	.uleb128 0x3
	.byte	0x91
	.sleb128 -36
	.byte	0x6
	.byte	0
	.uleb128 0x24
	.long	.LVL58
	.long	0xc36
	.long	0xa3b
	.uleb128 0x25
	.uleb128 0x2
	.byte	0x74
	.sleb128 0
	.uleb128 0x1
	.byte	0x3a
	.byte	0
	.uleb128 0x24
	.long	.LVL64
	.long	0xc52
	.long	0xa5c
	.uleb128 0x25
	.uleb128 0x2
	.byte	0x74
	.sleb128 0
	.uleb128 0x2
	.byte	0x77
	.sleb128 0
	.uleb128 0x25
	.uleb128 0x2
	.byte	0x74
	.sleb128 4
	.uleb128 0x1
	.byte	0x31
	.uleb128 0x25
	.uleb128 0x2
	.byte	0x74
	.sleb128 8
	.uleb128 0x1
	.byte	0x33
	.byte	0
	.uleb128 0x24
	.long	.LVL77
	.long	0xc36
	.long	0xa70
	.uleb128 0x25
	.uleb128 0x2
	.byte	0x74
	.sleb128 0
	.uleb128 0x1
	.byte	0x3a
	.byte	0
	.uleb128 0x27
	.long	.LVL78
	.long	0xc01
	.uleb128 0x26
	.long	.LVL79
	.long	0xb75
	.uleb128 0x25
	.uleb128 0x2
	.byte	0x74
	.sleb128 0
	.uleb128 0x2
	.byte	0x77
	.sleb128 0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x11
	.long	0x171
	.long	0xa98
	.uleb128 0x37
	.byte	0
	.uleb128 0x38
	.long	.LASF73
	.byte	0x9
	.byte	0x8d
	.long	0xa8d
	.uleb128 0x38
	.long	.LASF74
	.byte	0x2
	.byte	0x38
	.long	0x2d7
	.uleb128 0x38
	.long	.LASF75
	.byte	0x2
	.byte	0x39
	.long	0xab9
	.uleb128 0xa
	.byte	0x4
	.long	0xabf
	.uleb128 0x10
	.long	0x8a
	.uleb128 0x38
	.long	.LASF76
	.byte	0x2
	.byte	0x3a
	.long	0xab9
	.uleb128 0x39
	.long	.LASF83
	.byte	0xb
	.byte	0x17
	.long	0xae0
	.uleb128 0xf
	.long	0xae0
	.byte	0
	.uleb128 0xa
	.byte	0x4
	.long	0x357
	.uleb128 0x3a
	.long	.LASF78
	.byte	0x9
	.byte	0xdb
	.long	0x479
	.long	0xb00
	.uleb128 0xf
	.long	0x2d7
	.uleb128 0xf
	.long	0x2d7
	.byte	0
	.uleb128 0x3a
	.long	.LASF79
	.byte	0xd
	.byte	0x73
	.long	0x50
	.long	0xb1a
	.uleb128 0xf
	.long	0x2d7
	.uleb128 0xf
	.long	0x104
	.byte	0
	.uleb128 0x3a
	.long	.LASF80
	.byte	0x9
	.byte	0xd4
	.long	0x50
	.long	0xb2f
	.uleb128 0xf
	.long	0x479
	.byte	0
	.uleb128 0x3a
	.long	.LASF81
	.byte	0x9
	.byte	0xfc
	.long	0x50
	.long	0xb4a
	.uleb128 0xf
	.long	0xfe
	.uleb128 0xf
	.long	0x2d7
	.uleb128 0x1c
	.byte	0
	.uleb128 0x3a
	.long	.LASF82
	.byte	0xe
	.byte	0x37
	.long	0xfe
	.long	0xb64
	.uleb128 0xf
	.long	0xfe
	.uleb128 0xf
	.long	0x2d7
	.byte	0
	.uleb128 0x39
	.long	.LASF84
	.byte	0xb
	.byte	0x19
	.long	0xb75
	.uleb128 0xf
	.long	0xae0
	.byte	0
	.uleb128 0x39
	.long	.LASF85
	.byte	0xb
	.byte	0x1a
	.long	0xb86
	.uleb128 0xf
	.long	0xae0
	.byte	0
	.uleb128 0x3b
	.long	.LASF106
	.uleb128 0x3a
	.long	.LASF86
	.byte	0xf
	.byte	0x28
	.long	0x125
	.long	0xba0
	.uleb128 0xf
	.long	0xba0
	.byte	0
	.uleb128 0xa
	.byte	0x4
	.long	0x125
	.uleb128 0x3a
	.long	.LASF87
	.byte	0xf
	.byte	0x52
	.long	0xfe
	.long	0xbbb
	.uleb128 0xf
	.long	0xbbb
	.byte	0
	.uleb128 0xa
	.byte	0x4
	.long	0xbc1
	.uleb128 0x10
	.long	0x125
	.uleb128 0x3a
	.long	.LASF88
	.byte	0xe
	.byte	0x34
	.long	0x57
	.long	0xbdb
	.uleb128 0xf
	.long	0x2d7
	.byte	0
	.uleb128 0x3c
	.long	.LASF107
	.byte	0x11
	.byte	0x39
	.long	0x11a
	.uleb128 0x3a
	.long	.LASF89
	.byte	0x9
	.byte	0xdc
	.long	0x50
	.long	0xc01
	.uleb128 0xf
	.long	0x479
	.uleb128 0xf
	.long	0x2d7
	.uleb128 0x1c
	.byte	0
	.uleb128 0x3a
	.long	.LASF90
	.byte	0x9
	.byte	0xd7
	.long	0x50
	.long	0xc16
	.uleb128 0xf
	.long	0x479
	.byte	0
	.uleb128 0x3d
	.long	.LASF91
	.byte	0x9
	.value	0x103
	.long	0x50
	.long	0xc36
	.uleb128 0xf
	.long	0xfe
	.uleb128 0xf
	.long	0x2d7
	.uleb128 0xf
	.long	0xad
	.byte	0
	.uleb128 0x3e
	.long	.LASF92
	.long	.LASF94
	.long	0x50
	.long	0xc52
	.uleb128 0xf
	.long	0x50
	.uleb128 0xf
	.long	0x479
	.byte	0
	.uleb128 0x3e
	.long	.LASF93
	.long	.LASF95
	.long	0x62
	.long	0xc78
	.uleb128 0xf
	.long	0xc78
	.uleb128 0xf
	.long	0x57
	.uleb128 0xf
	.long	0x57
	.uleb128 0xf
	.long	0x479
	.byte	0
	.uleb128 0xa
	.byte	0x4
	.long	0xc7e
	.uleb128 0x3f
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
	.uleb128 0x6
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
	.uleb128 0x7
	.uleb128 0x3b
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.byte	0
	.byte	0
	.uleb128 0x8
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x9
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0xa
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xb
	.uleb128 0x13
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xc
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
	.uleb128 0xd
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
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
	.uleb128 0xe
	.uleb128 0x15
	.byte	0x1
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xf
	.uleb128 0x5
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x10
	.uleb128 0x26
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x11
	.uleb128 0x1
	.byte	0x1
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x12
	.uleb128 0x21
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x13
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
	.uleb128 0x14
	.uleb128 0x35
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x15
	.uleb128 0x2
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x16
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
	.uleb128 0x32
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x17
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xb
	.uleb128 0x32
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x18
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
	.uleb128 0x6e
	.uleb128 0xe
	.uleb128 0x32
	.uleb128 0xb
	.uleb128 0x3c
	.uleb128 0x19
	.uleb128 0x64
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x19
	.uleb128 0x5
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x34
	.uleb128 0x19
	.byte	0
	.byte	0
	.uleb128 0x1a
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
	.uleb128 0x6e
	.uleb128 0xe
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x32
	.uleb128 0xb
	.uleb128 0x3c
	.uleb128 0x19
	.uleb128 0x64
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1b
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
	.uleb128 0x6e
	.uleb128 0xe
	.uleb128 0x32
	.uleb128 0xb
	.uleb128 0x3c
	.uleb128 0x19
	.uleb128 0x64
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1c
	.uleb128 0x18
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x1d
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
	.uleb128 0x20
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1e
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
	.byte	0
	.byte	0
	.uleb128 0x1f
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x47
	.uleb128 0x13
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x20
	.uleb128 0xb
	.uleb128 0x64
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x20
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x34
	.uleb128 0x19
	.byte	0
	.byte	0
	.uleb128 0x21
	.uleb128 0x5
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
	.uleb128 0x22
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x6e
	.uleb128 0xe
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x64
	.uleb128 0x13
	.uleb128 0x2117
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x23
	.uleb128 0x5
	.byte	0
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x24
	.uleb128 0x4109
	.byte	0x1
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x25
	.uleb128 0x410a
	.byte	0
	.uleb128 0x2
	.uleb128 0x18
	.uleb128 0x2111
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x26
	.uleb128 0x4109
	.byte	0x1
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x31
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x27
	.uleb128 0x4109
	.byte	0
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x31
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x28
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x47
	.uleb128 0x13
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
	.uleb128 0x64
	.uleb128 0x13
	.uleb128 0x2117
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x29
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x34
	.uleb128 0x19
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x2a
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
	.uleb128 0x2b
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x55
	.uleb128 0x17
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x2c
	.uleb128 0x34
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
	.uleb128 0x2d
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x2e
	.uleb128 0x34
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
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x2f
	.uleb128 0x21
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x30
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x31
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
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
	.uleb128 0x32
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
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
	.uleb128 0x33
	.uleb128 0x21
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0x5
	.byte	0
	.byte	0
	.uleb128 0x34
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x55
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x35
	.uleb128 0x1d
	.byte	0x1
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.uleb128 0x58
	.uleb128 0xb
	.uleb128 0x59
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x36
	.uleb128 0x5
	.byte	0
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x37
	.uleb128 0x21
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x38
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3c
	.uleb128 0x19
	.byte	0
	.byte	0
	.uleb128 0x39
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
	.uleb128 0x3c
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x3a
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
	.uleb128 0x3b
	.uleb128 0x2e
	.byte	0
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x34
	.uleb128 0x19
	.uleb128 0x3c
	.uleb128 0x19
	.byte	0
	.byte	0
	.uleb128 0x3c
	.uleb128 0x2e
	.byte	0
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
	.uleb128 0x3d
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3c
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x3e
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x6e
	.uleb128 0xe
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x34
	.uleb128 0x19
	.uleb128 0x3c
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x3f
	.uleb128 0x26
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.section	.debug_loc,"",@progbits
.Ldebug_loc0:
.LLST0:
	.long	.LVL9
	.long	.LVL10
	.value	0x2
	.byte	0x30
	.byte	0x9f
	.long	.LVL10
	.long	.LVL12
	.value	0x1
	.byte	0x55
	.long	.LVL12
	.long	.LVL14
	.value	0x3
	.byte	0x75
	.sleb128 -1
	.byte	0x9f
	.long	.LVL14
	.long	.LVL15
	.value	0x1
	.byte	0x55
	.long	.LVL17
	.long	.LVL18
	.value	0x1
	.byte	0x55
	.long	0
	.long	0
.LLST1:
	.long	.LVL24
	.long	.LVL25-1
	.value	0x1
	.byte	0x50
	.long	.LVL25-1
	.long	.LVL29
	.value	0x1
	.byte	0x57
	.long	.LVL30
	.long	.LVL33
	.value	0x1
	.byte	0x57
	.long	0
	.long	0
.LLST2:
	.long	.LVL36
	.long	.LVL37
	.value	0x1
	.byte	0x50
	.long	.LVL37
	.long	.LVL38-1
	.value	0x3
	.byte	0x91
	.sleb128 -2088
	.long	.LVL38-1
	.long	.LFE39
	.value	0x3
	.byte	0x91
	.sleb128 8
	.byte	0x9f
	.long	0
	.long	0
.LLST3:
	.long	.LVL42
	.long	.LVL44
	.value	0x2
	.byte	0x30
	.byte	0x9f
	.long	.LVL44
	.long	.LVL47
	.value	0x2
	.byte	0x91
	.sleb128 -40
	.long	.LVL58
	.long	.LVL59
	.value	0x2
	.byte	0x91
	.sleb128 -40
	.long	.LVL59
	.long	.LVL61
	.value	0x1
	.byte	0x50
	.long	.LVL80
	.long	.LFE41
	.value	0x2
	.byte	0x30
	.byte	0x9f
	.long	0
	.long	0
.LLST4:
	.long	.LVL48
	.long	.LVL49
	.value	0xd
	.byte	0x91
	.sleb128 4
	.byte	0x6
	.byte	0x91
	.sleb128 -40
	.byte	0x6
	.byte	0x22
	.byte	0x76
	.sleb128 0
	.byte	0x1c
	.byte	0x23
	.uleb128 0x1
	.byte	0x9f
	.long	.LVL49
	.long	.LVL51
	.value	0xd
	.byte	0x91
	.sleb128 4
	.byte	0x6
	.byte	0x76
	.sleb128 0
	.byte	0x1c
	.byte	0x91
	.sleb128 -40
	.byte	0x6
	.byte	0x22
	.byte	0x23
	.uleb128 0x2
	.byte	0x9f
	.long	.LVL52
	.long	.LVL55
	.value	0xd
	.byte	0x91
	.sleb128 4
	.byte	0x6
	.byte	0x91
	.sleb128 -40
	.byte	0x6
	.byte	0x22
	.byte	0x76
	.sleb128 0
	.byte	0x1c
	.byte	0x23
	.uleb128 0x1
	.byte	0x9f
	.long	.LVL55
	.long	.LVL57
	.value	0xd
	.byte	0x91
	.sleb128 4
	.byte	0x6
	.byte	0x76
	.sleb128 0
	.byte	0x1c
	.byte	0x91
	.sleb128 -40
	.byte	0x6
	.byte	0x22
	.byte	0x23
	.uleb128 0x2
	.byte	0x9f
	.long	.LVL60
	.long	.LVL62
	.value	0x2
	.byte	0x30
	.byte	0x9f
	.long	.LVL62
	.long	.LVL63
	.value	0x1
	.byte	0x56
	.long	.LVL63
	.long	.LVL64
	.value	0x3
	.byte	0x76
	.sleb128 -1
	.byte	0x9f
	.long	.LVL64
	.long	.LVL65
	.value	0x1
	.byte	0x56
	.long	.LVL65
	.long	.LVL66
	.value	0x1
	.byte	0x50
	.long	.LVL66
	.long	.LVL67
	.value	0x2
	.byte	0x91
	.sleb128 -40
	.long	0
	.long	0
.LLST5:
	.long	.LVL60
	.long	.LVL61
	.value	0x1
	.byte	0x55
	.long	.LVL61
	.long	.LVL79
	.value	0x2
	.byte	0x91
	.sleb128 -40
	.long	0
	.long	0
.LLST6:
	.long	.LVL48
	.long	.LVL49
	.value	0x2
	.byte	0x76
	.sleb128 0
	.long	.LVL49
	.long	.LVL50
	.value	0x2
	.byte	0x76
	.sleb128 -1
	.long	.LVL50
	.long	.LVL51-1
	.value	0x1
	.byte	0x50
	.long	.LVL52
	.long	.LVL55
	.value	0x2
	.byte	0x76
	.sleb128 0
	.long	.LVL55
	.long	.LVL56
	.value	0x2
	.byte	0x76
	.sleb128 -1
	.long	0
	.long	0
.LLST7:
	.long	.LVL48
	.long	.LVL51-1
	.value	0x1
	.byte	0x50
	.long	.LVL52
	.long	.LVL53
	.value	0x8
	.byte	0x76
	.sleb128 0
	.byte	0x94
	.byte	0x1
	.byte	0x8
	.byte	0xff
	.byte	0x1a
	.byte	0x9f
	.long	.LVL53
	.long	.LVL54
	.value	0x1
	.byte	0x50
	.long	.LVL54
	.long	.LVL55
	.value	0x8
	.byte	0x76
	.sleb128 0
	.byte	0x94
	.byte	0x1
	.byte	0x8
	.byte	0xff
	.byte	0x1a
	.byte	0x9f
	.long	.LVL55
	.long	.LVL56
	.value	0x8
	.byte	0x76
	.sleb128 -1
	.byte	0x94
	.byte	0x1
	.byte	0x8
	.byte	0xff
	.byte	0x1a
	.byte	0x9f
	.long	0
	.long	0
.LLST8:
	.long	.LVL67
	.long	.LVL68
	.value	0x2
	.byte	0x75
	.sleb128 0
	.long	.LVL68
	.long	.LVL69
	.value	0x2
	.byte	0x75
	.sleb128 -1
	.long	.LVL69
	.long	.LVL70-1
	.value	0x1
	.byte	0x50
	.long	.LVL71
	.long	.LVL74
	.value	0x2
	.byte	0x75
	.sleb128 0
	.long	.LVL74
	.long	.LVL75
	.value	0x2
	.byte	0x75
	.sleb128 -1
	.long	0
	.long	0
.LLST9:
	.long	.LVL67
	.long	.LVL70-1
	.value	0x1
	.byte	0x50
	.long	.LVL71
	.long	.LVL72
	.value	0x8
	.byte	0x75
	.sleb128 0
	.byte	0x94
	.byte	0x1
	.byte	0x8
	.byte	0xff
	.byte	0x1a
	.byte	0x9f
	.long	.LVL72
	.long	.LVL73
	.value	0x1
	.byte	0x50
	.long	.LVL73
	.long	.LVL74
	.value	0x8
	.byte	0x75
	.sleb128 0
	.byte	0x94
	.byte	0x1
	.byte	0x8
	.byte	0xff
	.byte	0x1a
	.byte	0x9f
	.long	.LVL74
	.long	.LVL75
	.value	0x8
	.byte	0x75
	.sleb128 -1
	.byte	0x94
	.byte	0x1
	.byte	0x8
	.byte	0xff
	.byte	0x1a
	.byte	0x9f
	.long	0
	.long	0
	.section	.debug_aranges,"",@progbits
	.long	0x4c
	.value	0x2
	.long	.Ldebug_info0
	.byte	0x4
	.byte	0
	.value	0
	.value	0
	.long	.LFB30
	.long	.LFE30-.LFB30
	.long	.LFB33
	.long	.LFE33-.LFB33
	.long	.LFB36
	.long	.LFE36-.LFB36
	.long	.LFB38
	.long	.LFE38-.LFB38
	.long	.LFB40
	.long	.LFE40-.LFB40
	.long	.LFB39
	.long	.LFE39-.LFB39
	.long	.LFB41
	.long	.LFE41-.LFB41
	.long	0
	.long	0
	.section	.debug_ranges,"",@progbits
.Ldebug_ranges0:
	.long	.LBB21
	.long	.LBE21
	.long	.LBB23
	.long	.LBE23
	.long	.LBB24
	.long	.LBE24
	.long	.LBB25
	.long	.LBE25
	.long	0
	.long	0
	.long	.LBB27
	.long	.LBE27
	.long	.LBB28
	.long	.LBE28
	.long	0
	.long	0
	.long	.LBB31
	.long	.LBE31
	.long	.LBB32
	.long	.LBE32
	.long	0
	.long	0
	.long	.LBB33
	.long	.LBE33
	.long	.LBB55
	.long	.LBE55
	.long	0
	.long	0
	.long	.LBB35
	.long	.LBE35
	.long	.LBB53
	.long	.LBE53
	.long	0
	.long	0
	.long	.LBB41
	.long	.LBE41
	.long	.LBB44
	.long	.LBE44
	.long	0
	.long	0
	.long	.LBB48
	.long	.LBE48
	.long	.LBB51
	.long	.LBE51
	.long	0
	.long	0
	.long	.LFB30
	.long	.LFE30
	.long	.LFB33
	.long	.LFE33
	.long	.LFB36
	.long	.LFE36
	.long	.LFB38
	.long	.LFE38
	.long	.LFB40
	.long	.LFE40
	.long	.LFB39
	.long	.LFE39
	.long	.LFB41
	.long	.LFE41
	.long	0
	.long	0
	.section	.debug_line,"",@progbits
.Ldebug_line0:
	.section	.debug_str,"MS",@progbits,1
.LASF104:
	.string	"printf"
.LASF53:
	.string	"_ZN6LoggerC4Ev"
.LASF83:
	.string	"MutexCreate"
.LASF66:
	.string	"__in_chrg"
.LASF13:
	.string	"size_t"
.LASF57:
	.string	"_ZN6Logger6logStrEPc"
.LASF45:
	.string	"va_list"
.LASF107:
	.string	"gettid"
.LASF10:
	.string	"long long unsigned int"
.LASF33:
	.string	"_lbfsize"
.LASF73:
	.string	"__sF"
.LASF35:
	.string	"_close"
.LASF6:
	.string	"signed char"
.LASF93:
	.string	"__builtin_fwrite"
.LASF70:
	.string	"buff"
.LASF40:
	.string	"_ubuf"
.LASF1:
	.string	"stlport"
.LASF63:
	.string	"this"
.LASF92:
	.string	"__builtin_fputc"
.LASF34:
	.string	"_cookie"
.LASF12:
	.string	"long int"
.LASF20:
	.string	"__kernel_time_t"
.LASF31:
	.string	"_flags"
.LASF2:
	.string	"_STL"
.LASF14:
	.string	"__va_list"
.LASF42:
	.string	"_blksize"
.LASF4:
	.string	"long long int"
.LASF81:
	.string	"sprintf"
.LASF43:
	.string	"_offset"
.LASF67:
	.string	"_ZN6LoggerD2Ev"
.LASF84:
	.string	"MutexLock"
.LASF22:
	.string	"off_t"
.LASF36:
	.string	"_read"
.LASF46:
	.string	"value"
.LASF26:
	.string	"fpos_t"
.LASF79:
	.string	"chmod"
.LASF3:
	.string	"unsigned int"
.LASF88:
	.string	"strlen"
.LASF103:
	.string	"_ZN6Logger5toHexEPhi"
.LASF11:
	.string	"long unsigned int"
.LASF32:
	.string	"_file"
.LASF106:
	.string	"__stack_chk_fail_local"
.LASF62:
	.string	"FLGNOTIME"
.LASF65:
	.string	"_ZN6LoggerC2Ev"
.LASF76:
	.string	"_toupper_tab_"
.LASF9:
	.string	"short unsigned int"
.LASF80:
	.string	"fclose"
.LASF60:
	.string	"bool"
.LASF56:
	.string	"logStr"
.LASF82:
	.string	"strcat"
.LASF99:
	.string	"decltype(nullptr)"
.LASF19:
	.string	"__kernel_pid_t"
.LASF87:
	.string	"ctime"
.LASF38:
	.string	"_write"
.LASF58:
	.string	"logHex"
.LASF59:
	.string	"_ZN6Logger6logHexEPhi"
.LASF16:
	.string	"sizetype"
.LASF17:
	.string	"__kernel_mode_t"
.LASF48:
	.string	"Mutex"
.LASF51:
	.string	"Logger"
.LASF101:
	.string	"15pthread_mutex_t"
.LASF25:
	.string	"__gnuc_va_list"
.LASF94:
	.string	"fputc"
.LASF97:
	.string	"jni/scrcap/../util/logger.cpp"
.LASF86:
	.string	"time"
.LASF61:
	.string	"logfile"
.LASF98:
	.string	"C:\\\\cygwin64\\\\home\\\\kwang\\\\C\\\\androidX86"
.LASF24:
	.string	"time_t"
.LASF78:
	.string	"fopen"
.LASF90:
	.string	"fflush"
.LASF49:
	.string	"mutex"
.LASF7:
	.string	"unsigned char"
.LASF64:
	.string	"_ZN6LoggerC2EPcb"
.LASF8:
	.string	"short int"
.LASF29:
	.string	"__sbuf"
.LASF75:
	.string	"_tolower_tab_"
.LASF85:
	.string	"MutexUnlock"
.LASF77:
	.string	"isalnum"
.LASF30:
	.string	"__sFILE"
.LASF44:
	.string	"FILE"
.LASF69:
	.string	"format"
.LASF37:
	.string	"_seek"
.LASF89:
	.string	"fprintf"
.LASF5:
	.string	"long double"
.LASF15:
	.string	"char"
.LASF28:
	.string	"_size"
.LASF39:
	.string	"_ext"
.LASF72:
	.string	"index"
.LASF74:
	.string	"_ctype_"
.LASF18:
	.string	"__kernel_off_t"
.LASF100:
	.string	"__builtin_va_list"
.LASF50:
	.string	"flgNoTime"
.LASF91:
	.string	"vsprintf"
.LASF52:
	.string	"_ZN6LoggerC4EPcb"
.LASF68:
	.string	"stime"
.LASF47:
	.string	"pthread_mutex_t"
.LASF96:
	.string	"GNU C++ 4.9.x 20150123 (prerelease) -fpreprocessed -mssse3 -fno-short-enums -mbionic -fPIC -mtune=intel -march=i686 -g -g -O2 -std=c++11 -ffunction-sections -funwind-tables -fstack-protector-strong -fno-exceptions -frtti"
.LASF95:
	.string	"fwrite"
.LASF0:
	.string	"__std_alias"
.LASF21:
	.string	"mode_t"
.LASF55:
	.string	"_ZN6LoggerD4Ev"
.LASF27:
	.string	"_base"
.LASF105:
	.string	"_ZN6Logger6printfEPcz"
.LASF41:
	.string	"_nbuf"
.LASF54:
	.string	"~Logger"
.LASF23:
	.string	"pid_t"
.LASF102:
	.string	"toHex"
.LASF71:
	.string	"args"
	.hidden	__stack_chk_fail_local
	.ident	"GCC: (GNU) 4.9.x 20150123 (prerelease)"
	.section	.note.GNU-stack,"",@progbits
