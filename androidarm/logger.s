	.arch armv5te
	.fpu softvfp
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 2
	.eabi_attribute 30, 4
	.eabi_attribute 34, 0
	.eabi_attribute 18, 4
	.code	16
	.file	"logger.cpp"
	.text
.Ltext0:
	.cfi_sections	.debug_frame
	.section	.text._ZN6LoggerC2EPcb,"ax",%progbits
	.align	1
	.global	_ZN6LoggerC2EPcb
	.code	16
	.thumb_func
	.type	_ZN6LoggerC2EPcb, %function
_ZN6LoggerC2EPcb:
	.fnstart
.LFB30:
	.file 1 "jni/tracer/../util/logger.cpp"
	.loc 1 11 0
	.cfi_startproc
.LVL0:
	ldr	r3, .L8
	push	{r4, r5, r6, lr}
	.save {r4, r5, r6, lr}
	.cfi_def_cfa_offset 16
	.cfi_offset 4, -16
	.cfi_offset 5, -12
	.cfi_offset 6, -8
	.cfi_offset 14, -4
.LPIC3:
	add	r3, pc
.LBB17:
	.loc 1 11 0
	ldr	r3, [r3]
.LBE17:
	mov	r4, r0
.LBB18:
	add	r3, r3, #8
	stmia	r0!, {r3}
.LVL1:
.LBE18:
	mov	r5, r1
	mov	r6, r2
.LBB19:
	.loc 1 13 0
	bl	MutexCreate
.LVL2:
	.loc 1 14 0
	cmp	r5, #0
	bne	.L2
	ldr	r3, .L8+4
.LPIC2:
	add	r3, pc
	.loc 1 15 0
	ldr	r3, [r3]
	add	r3, r3, #84
	str	r3, [r4, #8]
	b	.L3
.L2:
	.loc 1 18 0
	ldr	r1, .L8+8
	.loc 1 17 0
	strb	r6, [r4, #12]
	.loc 1 18 0
	mov	r0, r5
.LPIC1:
	add	r1, pc
	bl	fopen
.LVL3:
	str	r0, [r4, #8]
	cmp	r0, #0
	beq	.L3
	.loc 1 19 0
	mov	r0, r5
	ldr	r1, .L8+12
	bl	chmod
.LVL4:
.L3:
.LBE19:
	.loc 1 22 0
	mov	r0, r4
	@ sp needed
.LVL5:
.LVL6:
	pop	{r4, r5, r6, pc}
.L9:
	.align	2
.L8:
	.word	_ZTV6Logger(GOT_PREL)+(.-(.LPIC3+4))
	.word	__sF(GOT_PREL)+(.-(.LPIC2+4))
	.word	.LC0-(.LPIC1+4)
	.word	511
	.cfi_endproc
.LFE30:
	.fnend
	.size	_ZN6LoggerC2EPcb, .-_ZN6LoggerC2EPcb
	.global	_ZN6LoggerC1EPcb
	.thumb_set _ZN6LoggerC1EPcb,_ZN6LoggerC2EPcb
	.section	.text._ZN6LoggerC2Ev,"ax",%progbits
	.align	1
	.global	_ZN6LoggerC2Ev
	.code	16
	.thumb_func
	.type	_ZN6LoggerC2Ev, %function
_ZN6LoggerC2Ev:
	.fnstart
.LFB33:
	.loc 1 24 0
	.cfi_startproc
.LVL7:
	push	{r4, lr}
	.save {r4, lr}
	.cfi_def_cfa_offset 8
	.cfi_offset 4, -8
	.cfi_offset 14, -4
	.loc 1 24 0
	mov	r4, r0
	ldr	r3, .L11
	.loc 1 30 0
	@ sp needed
.LPIC6:
	add	r3, pc
.LBB20:
	.loc 1 24 0
	ldr	r3, [r3]
	add	r3, r3, #8
	stmia	r0!, {r3}
.LVL8:
	.loc 1 26 0
	bl	MutexCreate
.LVL9:
	ldr	r3, .L11+4
.LBE20:
	.loc 1 30 0
	mov	r0, r4
.LBB21:
	.loc 1 26 0
.LPIC5:
	add	r3, pc
	.loc 1 27 0
	ldr	r3, [r3]
	add	r3, r3, #84
	str	r3, [r4, #8]
	.loc 1 28 0
	mov	r3, #1
	strb	r3, [r4, #12]
.LVL10:
.LBE21:
	.loc 1 30 0
	pop	{r4, pc}
.L12:
	.align	2
.L11:
	.word	_ZTV6Logger(GOT_PREL)+(.-(.LPIC6+4))
	.word	__sF(GOT_PREL)+(.-(.LPIC5+4))
	.cfi_endproc
.LFE33:
	.fnend
	.size	_ZN6LoggerC2Ev, .-_ZN6LoggerC2Ev
	.global	_ZN6LoggerC1Ev
	.thumb_set _ZN6LoggerC1Ev,_ZN6LoggerC2Ev
	.section	.text._ZN6LoggerD2Ev,"ax",%progbits
	.align	1
	.global	_ZN6LoggerD2Ev
	.code	16
	.thumb_func
	.type	_ZN6LoggerD2Ev, %function
_ZN6LoggerD2Ev:
	.fnstart
.LFB36:
	.loc 1 32 0
	.cfi_startproc
.LVL11:
	ldr	r3, .L18
	push	{r4, lr}
	.save {r4, lr}
	.cfi_def_cfa_offset 8
	.cfi_offset 4, -8
	.cfi_offset 14, -4
.LPIC9:
	add	r3, pc
.LBB22:
	.loc 1 32 0
	ldr	r3, [r3]
.LBE22:
	mov	r4, r0
.LBB23:
	add	r3, r3, #8
	str	r3, [r0]
	.loc 1 34 0
	ldr	r0, [r0, #8]
.LVL12:
	cmp	r0, #0
	beq	.L14
	ldr	r3, .L18+4
.LPIC8:
	add	r3, pc
	.loc 1 35 0
	ldr	r3, [r3]
	add	r3, r3, #84
	cmp	r0, r3
	beq	.L14
	.loc 1 36 0
	bl	fclose
.LVL13:
.L14:
.LBE23:
	.loc 1 39 0
	mov	r0, r4
	@ sp needed
.LVL14:
	pop	{r4, pc}
.L19:
	.align	2
.L18:
	.word	_ZTV6Logger(GOT_PREL)+(.-(.LPIC9+4))
	.word	__sF(GOT_PREL)+(.-(.LPIC8+4))
	.cfi_endproc
.LFE36:
	.fnend
	.size	_ZN6LoggerD2Ev, .-_ZN6LoggerD2Ev
	.global	_ZN6LoggerD1Ev
	.thumb_set _ZN6LoggerD1Ev,_ZN6LoggerD2Ev
	.section	.text._ZN6Logger5toHexEPhi,"ax",%progbits
	.align	1
	.global	_ZN6Logger5toHexEPhi
	.code	16
	.thumb_func
	.type	_ZN6Logger5toHexEPhi, %function
_ZN6Logger5toHexEPhi:
	.fnstart
.LFB38:
	.loc 1 42 0
	.cfi_startproc
.LVL15:
	push	{r4, r5, r6, r7, lr}
	.save {r4, r5, r6, r7, lr}
	.cfi_def_cfa_offset 20
	.cfi_offset 4, -20
	.cfi_offset 5, -16
	.cfi_offset 6, -12
	.cfi_offset 7, -8
	.cfi_offset 14, -4
.LBB24:
	.loc 1 45 0
	mov	r4, #0
	ldr	r5, .L26
.LBE24:
	.loc 1 42 0
	.pad #52
	sub	sp, sp, #52
	.cfi_def_cfa_offset 72
.LBB26:
	.loc 1 46 0
	add	r6, r0, #4
.LPIC25:
	add	r5, pc
.LBE26:
	.loc 1 42 0
	ldr	r5, [r5]
.LBB27:
	.loc 1 46 0
	mov	r0, r6
.LVL16:
.LBE27:
	.loc 1 42 0
	ldr	r3, [r5]
	str	r1, [sp]
	mov	r7, r2
	str	r3, [sp, #44]
.LBB28:
	.loc 1 45 0
	ldr	r3, .L26+4
.LPIC19:
	add	r3, pc
	strb	r4, [r3]
	.loc 1 46 0
	bl	MutexLock
.LVL17:
	str	r5, [sp, #4]
.LVL18:
.L21:
.LBB25:
	.loc 1 47 0 discriminator 1
	cmp	r4, r7
	bge	.L22
	.loc 1 47 0 is_stmt 0 discriminator 3
	cmp	r4, #16
	beq	.L25
	.loc 1 48 0 is_stmt 1
	ldr	r3, [sp]
	ldr	r1, .L26+8
	add	r5, sp, #12
	ldrb	r2, [r3, r4]
.LPIC20:
	add	r1, pc
	mov	r0, r5
	bl	sprintf
.LVL19:
	.loc 1 49 0
	ldr	r0, .L26+12
	mov	r1, r5
.LPIC21:
	add	r0, pc
	bl	strcat
.LVL20:
	.loc 1 47 0 discriminator 4
	add	r4, r4, #1
.LVL21:
	b	.L21
.L25:
.LBE25:
	.loc 1 51 0
	cmp	r7, #16
	ble	.L22
	.loc 1 52 0
	ldr	r0, .L26+16
	ldr	r1, .L26+20
.LPIC22:
	add	r0, pc
.LPIC23:
	add	r1, pc
	bl	strcat
.LVL22:
.L22:
	.loc 1 54 0
	mov	r0, r6
	bl	MutexUnlock
.LVL23:
.LBE28:
	.loc 1 56 0
	ldr	r3, [sp, #4]
	ldr	r0, .L26+24
	ldr	r2, [sp, #44]
	ldr	r3, [r3]
.LPIC24:
	add	r0, pc
	cmp	r2, r3
	beq	.L24
	bl	__stack_chk_fail
.LVL24:
.L24:
	add	sp, sp, #52
.LVL25:
	@ sp needed
.LVL26:
.LVL27:
.LVL28:
	pop	{r4, r5, r6, r7, pc}
.L27:
	.align	2
.L26:
	.word	__stack_chk_guard(GOT_PREL)+(.-(.LPIC25+4))
	.word	.LANCHOR0-(.LPIC19+4)
	.word	.LC1-(.LPIC20+4)
	.word	.LANCHOR0-(.LPIC21+4)
	.word	.LANCHOR0-(.LPIC22+4)
	.word	.LC2-(.LPIC23+4)
	.word	.LANCHOR0-(.LPIC24+4)
	.cfi_endproc
.LFE38:
	.fnend
	.size	_ZN6Logger5toHexEPhi, .-_ZN6Logger5toHexEPhi
	.section	.text._ZN6Logger6printfEPcz,"ax",%progbits
	.align	1
	.global	_ZN6Logger6printfEPcz
	.code	16
	.thumb_func
	.type	_ZN6Logger6printfEPcz, %function
_ZN6Logger6printfEPcz:
	.fnstart
.LFB39:
	.loc 1 59 0
	.cfi_startproc
.LVL29:
	push	{r1, r2, r3}
	.pad #12
	.cfi_def_cfa_offset 12
	push	{r4, r5, r6, lr}
	.save {r4, r5, r6, lr}
	.cfi_def_cfa_offset 28
	.cfi_offset 4, -28
	.cfi_offset 5, -24
	.cfi_offset 6, -20
	.cfi_offset 14, -16
	mov	r6, r0
	ldr	r4, .L30
	ldr	r2, .L30+4
	ldr	r0, .L30+8
.LVL30:
	.pad #2060
	add	sp, sp, r4
	.cfi_def_cfa_offset 2088
	ldr	r4, .L30+12
	.loc 1 59 0
	add	r2, r2, sp
	ldmia	r2!, {r1}
.LPIC27:
	add	r4, pc
	ldr	r4, [r4]
	add	r0, r0, sp
.LBB29:
	.loc 1 63 0
	add	r5, sp, #4
.LBE29:
	.loc 1 59 0
	ldr	r3, [r4]
.LBB30:
	.loc 1 62 0
	str	r2, [sp]
.LBE30:
	.loc 1 59 0
	str	r3, [r0]
.LBB31:
	.loc 1 63 0
	mov	r0, r5
	bl	vsprintf
.LVL31:
	.loc 1 65 0
	ldr	r3, [r6]
	mov	r0, r6
	ldr	r3, [r3]
	mov	r1, r5
	blx	r3
.LVL32:
.LBE31:
	.loc 1 66 0
	ldr	r3, .L30+8
	add	r3, r3, sp
	ldr	r2, [r3]
	ldr	r3, [r4]
	cmp	r2, r3
	beq	.L29
	bl	__stack_chk_fail
.LVL33:
.L29:
	ldr	r3, .L30+16
	add	sp, sp, r3
	@ sp needed
.LVL34:
	pop	{r4, r5, r6}
	pop	{r3}
	add	sp, sp, #12
	bx	r3
.L31:
	.align	2
.L30:
	.word	-2060
	.word	2076
	.word	2052
	.word	__stack_chk_guard(GOT_PREL)+(.-(.LPIC27+4))
	.word	2060
	.cfi_endproc
.LFE39:
	.fnend
	.size	_ZN6Logger6printfEPcz, .-_ZN6Logger6printfEPcz
	.section	.text._ZN6Logger6logStrEP7__sFILEPcb,"ax",%progbits
	.align	1
	.global	_ZN6Logger6logStrEP7__sFILEPcb
	.code	16
	.thumb_func
	.type	_ZN6Logger6logStrEP7__sFILEPcb, %function
_ZN6Logger6logStrEP7__sFILEPcb:
	.fnstart
.LFB40:
	.loc 1 69 0
	.cfi_startproc
.LVL35:
	push	{r4, r5, r6, r7, lr}
	.save {r4, r5, r6, r7, lr}
	.cfi_def_cfa_offset 20
	.cfi_offset 4, -20
	.cfi_offset 5, -16
	.cfi_offset 6, -12
	.cfi_offset 7, -8
	.cfi_offset 14, -4
	.pad #36
	sub	sp, sp, #36
	.cfi_def_cfa_offset 56
	.loc 1 69 0
	str	r3, [sp, #16]
	ldr	r3, .L41
.LVL36:
	mov	r6, r2
.LPIC32:
	add	r3, pc
	ldr	r3, [r3]
	str	r0, [sp, #12]
	sub	r4, r1, #0
	ldr	r2, [r3]
.LVL37:
	str	r3, [sp, #20]
	str	r2, [sp, #28]
.LBB32:
	.loc 1 71 0
	beq	.L32
.LBB33:
	.loc 1 72 0
	add	r7, r0, #4
	.loc 1 74 0
	add	r5, sp, #24
	.loc 1 72 0
	mov	r0, r7
.LVL38:
	bl	MutexLock
.LVL39:
	.loc 1 74 0
	mov	r0, r5
	bl	time
.LVL40:
	.loc 1 75 0
	mov	r0, r5
	bl	ctime
.LVL41:
	mov	r5, r0
.LVL42:
	.loc 1 76 0
	bl	strlen
.LVL43:
	mov	r3, #0
	add	r0, r5, r0
	sub	r0, r0, #1
	strb	r3, [r0]
	.loc 1 77 0
	ldr	r3, [sp, #16]
	cmp	r3, #0
	beq	.L34
	.loc 1 78 0
	ldr	r1, .L41+4
	mov	r0, r4
.LPIC29:
	add	r1, pc
	mov	r2, r6
	bl	fprintf
.LVL44:
	b	.L35
.L34:
	.loc 1 80 0
	ldr	r3, [sp, #12]
	ldrb	r3, [r3, #12]
	cmp	r3, #0
	beq	.L36
	.loc 1 81 0
	bl	gettid
.LVL45:
	.loc 1 81 0 is_stmt 0 discriminator 1
	ldr	r1, .L41+8
	.loc 1 81 0
	mov	r2, r0
	.loc 1 81 0 discriminator 1
.LPIC30:
	add	r1, pc
	mov	r0, r4
	mov	r3, r6
	bl	fprintf
.LVL46:
	b	.L35
.L36:
	.loc 1 83 0 is_stmt 1
	bl	gettid
.LVL47:
	.loc 1 83 0 is_stmt 0 discriminator 1
	ldr	r1, .L41+12
	.loc 1 83 0
	mov	r3, r0
	.loc 1 83 0 discriminator 1
	str	r6, [sp]
	mov	r0, r4
.LPIC31:
	add	r1, pc
	mov	r2, r5
	bl	fprintf
.LVL48:
.L35:
	.loc 1 86 0 is_stmt 1
	mov	r0, r4
	bl	fflush
.LVL49:
	.loc 1 87 0
	mov	r0, r7
	bl	MutexUnlock
.LVL50:
.L32:
.LBE33:
.LBE32:
	.loc 1 89 0
	ldr	r3, [sp, #20]
	ldr	r2, [sp, #28]
	ldr	r3, [r3]
	cmp	r2, r3
	beq	.L37
	bl	__stack_chk_fail
.LVL51:
.L37:
	add	sp, sp, #36
	@ sp needed
.LVL52:
.LVL53:
	pop	{r4, r5, r6, r7, pc}
.L42:
	.align	2
.L41:
	.word	__stack_chk_guard(GOT_PREL)+(.-(.LPIC32+4))
	.word	.LC3-(.LPIC29+4)
	.word	.LC4-(.LPIC30+4)
	.word	.LC5-(.LPIC31+4)
	.cfi_endproc
.LFE40:
	.fnend
	.size	_ZN6Logger6logStrEP7__sFILEPcb, .-_ZN6Logger6logStrEP7__sFILEPcb
	.section	.text._ZN6Logger6logStrEPc,"ax",%progbits
	.align	1
	.global	_ZN6Logger6logStrEPc
	.code	16
	.thumb_func
	.type	_ZN6Logger6logStrEPc, %function
_ZN6Logger6logStrEPc:
	.fnstart
.LFB41:
	.loc 1 91 0
	.cfi_startproc
.LVL54:
	push	{r3, lr}
	.save {r3, lr}
	.cfi_def_cfa_offset 8
	.cfi_offset 3, -8
	.cfi_offset 14, -4
	.loc 1 91 0
	mov	r2, r1
	.loc 1 92 0
	mov	r3, #0
	ldr	r1, [r0, #8]
.LVL55:
	bl	_ZN6Logger6logStrEP7__sFILEPcb
.LVL56:
	.loc 1 93 0
	@ sp needed
	pop	{r3, pc}
	.cfi_endproc
.LFE41:
	.fnend
	.size	_ZN6Logger6logStrEPc, .-_ZN6Logger6logStrEPc
	.section	.text._ZN6Logger6logRawEPc,"ax",%progbits
	.align	1
	.global	_ZN6Logger6logRawEPc
	.code	16
	.thumb_func
	.type	_ZN6Logger6logRawEPc, %function
_ZN6Logger6logRawEPc:
	.fnstart
.LFB42:
	.loc 1 96 0
	.cfi_startproc
.LVL57:
	push	{r3, lr}
	.save {r3, lr}
	.cfi_def_cfa_offset 8
	.cfi_offset 3, -8
	.cfi_offset 14, -4
	.loc 1 96 0
	mov	r2, r1
	.loc 1 97 0
	mov	r3, #1
	ldr	r1, [r0, #8]
.LVL58:
	bl	_ZN6Logger6logStrEP7__sFILEPcb
.LVL59:
	.loc 1 98 0
	@ sp needed
	pop	{r3, pc}
	.cfi_endproc
.LFE42:
	.fnend
	.size	_ZN6Logger6logRawEPc, .-_ZN6Logger6logRawEPc
	.section	.text._ZN6Logger6logHexEPhi,"ax",%progbits
	.align	1
	.global	_ZN6Logger6logHexEPhi
	.code	16
	.thumb_func
	.type	_ZN6Logger6logHexEPhi, %function
_ZN6Logger6logHexEPhi:
	.fnstart
.LFB43:
	.loc 1 104 0
	.cfi_startproc
.LVL60:
	push	{r4, r5, r6, r7, lr}
	.save {r4, r5, r6, r7, lr}
	.cfi_def_cfa_offset 20
	.cfi_offset 4, -20
	.cfi_offset 5, -16
	.cfi_offset 6, -12
	.cfi_offset 7, -8
	.cfi_offset 14, -4
.LBB34:
.LBB35:
	.loc 1 106 0
	ldr	r3, [r0, #8]
.LBE35:
.LBE34:
	.loc 1 104 0
	.pad #20
	sub	sp, sp, #20
	.cfi_def_cfa_offset 40
.LBB55:
.LBB54:
	.loc 1 106 0
	cmp	r3, #0
	beq	.L45
.LBB36:
.LBB37:
	.loc 1 108 0
	mov	r7, #0
.LBE37:
	.loc 1 107 0
	add	r3, r0, #4
	mov	r6, r0
	mov	r0, r3
.LVL61:
	str	r3, [sp, #8]
	str	r2, [sp, #4]
	str	r1, [sp, #12]
	bl	MutexLock
.LVL62:
	ldr	r3, [sp, #12]
	str	r3, [sp]
.LVL63:
.L47:
.LBB49:
	.loc 1 108 0 discriminator 1
	ldr	r3, [sp, #4]
	cmp	r7, r3
	bge	.L66
.LBB38:
.LBB39:
	.loc 1 110 0
	mov	r4, #15
.LBE39:
	.loc 1 109 0
	ldr	r3, [sp]
	ldr	r1, .L67
	ldr	r0, [r6, #8]
	ldrb	r2, [r3]
.LPIC33:
	add	r1, pc
.LBB47:
	.loc 1 110 0
	add	r7, r7, #1
.LVL64:
.LBE47:
	.loc 1 109 0
	bl	fprintf
.LVL65:
.LBB48:
	.loc 1 110 0
	and	r4, r7
	bne	.L48
	ldr	r5, .L67+4
.LPIC36:
	add	r5, pc
.LBB40:
.LBB41:
.LBB42:
.LBB43:
.LBB44:
	.file 2 "d:\\android-ndk-r12b\\platforms\\android-9\\arch-arm\\usr\\include\\ctype.h"
	.loc 2 104 0 discriminator 1
	ldr	r5, [r5]
.L51:
.LVL66:
	mov	r3, r4
.LBE44:
.LBE43:
	.loc 1 112 0
	ldr	r2, [sp]
	sub	r3, r3, #15
	ldr	r1, [r6, #8]
	ldrb	r0, [r2, r3]
.LVL67:
.LBB46:
.LBB45:
	.loc 2 104 0 discriminator 1
	ldr	r3, [r5]
	add	r3, r3, r0
	ldrb	r3, [r3, #1]
.LBE45:
.LBE46:
	.loc 1 113 0
	lsl	r3, r3, #29
	bne	.L64
	.loc 1 116 0
	mov	r0, #46
.LVL68:
.L64:
	add	r4, r4, #1
.LVL69:
	bl	fputc
.LVL70:
.LBE42:
	.loc 1 111 0 discriminator 1
	cmp	r4, #16
	bne	.L51
.LBE41:
	.loc 1 119 0
	mov	r0, #10
	ldr	r1, [r6, #8]
	bl	fputc
.LVL71:
.L48:
	ldr	r3, [sp]
	add	r3, r3, #1
	str	r3, [sp]
	b	.L47
.LVL72:
.L66:
	mvn	r5, r3
.LBE40:
.LBE48:
.LBE38:
.LBE49:
	.loc 1 122 0
	mov	r4, #15
	asr	r5, r5, #31
	and	r5, r3
	.loc 1 124 0 discriminator 1
	mov	r3, #16
	.loc 1 124 0 is_stmt 0
	mov	r7, #0
.LVL73:
	.loc 1 122 0 is_stmt 1
	and	r4, r5
.LVL74:
	.loc 1 124 0 discriminator 1
	sub	r3, r3, r4
	str	r3, [sp]
.LVL75:
.L54:
	ldr	r3, [sp]
	cmp	r7, r3
	bge	.L56
	.loc 1 125 0
	ldr	r0, .L67+8
	ldr	r1, [r6, #8]
	.loc 1 124 0 discriminator 3
	add	r7, r7, #1
.LVL76:
	.loc 1 125 0
.LPIC35:
	add	r0, pc
	bl	fputs
.LVL77:
	b	.L54
.LVL78:
.L59:
	ldr	r3, [sp, #12]
	neg	r2, r4
	add	r3, r3, r5
.LBB50:
.LBB51:
	.loc 1 129 0
	ldrb	r0, [r3, r2]
.LVL79:
	ldr	r3, .L67+12
.LPIC37:
	add	r3, pc
.LBB52:
.LBB53:
	.loc 2 104 0 discriminator 1
	ldr	r3, [r3]
	ldr	r3, [r3]
	add	r3, r3, r0
	ldrb	r3, [r3, #1]
.LBE53:
.LBE52:
	.loc 1 130 0
	lsl	r3, r3, #29
	bne	.L65
	.loc 1 133 0
	mov	r0, #46
.LVL80:
.L65:
	bl	fputc
.LVL81:
.LBE51:
	.loc 1 128 0 discriminator 2
	sub	r4, r4, #1
.LVL82:
.L56:
	ldr	r1, [r6, #8]
	.loc 1 128 0 is_stmt 0 discriminator 1
	cmp	r4, #0
	bne	.L59
.LBE50:
	.loc 1 136 0 is_stmt 1
	mov	r0, #10
	bl	fputc
.LVL83:
	.loc 1 137 0
	ldr	r0, [r6, #8]
	bl	fflush
.LVL84:
	.loc 1 138 0
	ldr	r0, [sp, #8]
	bl	MutexUnlock
.LVL85:
.L45:
.LBE36:
.LBE54:
.LBE55:
	.loc 1 140 0
	add	sp, sp, #20
	@ sp needed
	pop	{r4, r5, r6, r7, pc}
.L68:
	.align	2
.L67:
	.word	.LC1-(.LPIC33+4)
	.word	_ctype_(GOT_PREL)+(.-(.LPIC36+4))
	.word	.LC6-(.LPIC35+4)
	.word	_ctype_(GOT_PREL)+(.-(.LPIC37+4))
	.cfi_endproc
.LFE43:
	.fnend
	.size	_ZN6Logger6logHexEPhi, .-_ZN6Logger6logHexEPhi
	.global	_ZTS6Logger
	.global	_ZTI6Logger
	.global	_ZTV6Logger
	.section	.rodata
	.align	2
	.type	_ZTS6Logger, %object
	.size	_ZTS6Logger, 8
_ZTS6Logger:
	.ascii	"6Logger\000"
	.section	.data.rel.ro,"aw",%progbits
	.align	3
	.type	_ZTI6Logger, %object
	.size	_ZTI6Logger, 8
_ZTI6Logger:
	.word	_ZTVN10__cxxabiv117__class_type_infoE+8
	.word	_ZTS6Logger
	.type	_ZTV6Logger, %object
	.size	_ZTV6Logger, 16
_ZTV6Logger:
	.word	0
	.word	_ZTI6Logger
	.word	_ZN6Logger6logStrEPc
	.word	_ZN6Logger6logRawEPc
	.section	.rodata.str1.1,"aMS",%progbits,1
.LC0:
	.ascii	"a+\000"
.LC1:
	.ascii	"%02X \000"
.LC2:
	.ascii	"...\000"
.LC3:
	.ascii	"%s\012\000"
.LC4:
	.ascii	"[%5d] %s\012\000"
.LC5:
	.ascii	"%s [%5d] %s\012\000"
.LC6:
	.ascii	"   \000"
	.bss
	.align	2
.LANCHOR0 = . + 0
	.type	_ZZN6Logger5toHexEPhiE3tmp, %object
	.size	_ZZN6Logger5toHexEPhiE3tmp, 1024000
_ZZN6Logger5toHexEPhiE3tmp:
	.space	1024000
	.text
.Letext0:
	.file 3 "D:/android-ndk-r12b/build//../sources/cxx-stl/stlport/stlport/stl/config/features.h"
	.file 4 "d:\\android-ndk-r12b\\toolchains\\arm-linux-androideabi-4.9\\prebuilt\\windows-x86_64\\lib\\gcc\\arm-linux-androideabi\\4.9.x\\include\\stddef.h"
	.file 5 "d:\\android-ndk-r12b\\platforms\\android-9\\arch-arm\\usr\\include\\machine\\_types.h"
	.file 6 "d:\\android-ndk-r12b\\platforms\\android-9\\arch-arm\\usr\\include\\asm\\posix_types.h"
	.file 7 "d:\\android-ndk-r12b\\platforms\\android-9\\arch-arm\\usr\\include\\sys\\types.h"
	.file 8 "d:\\android-ndk-r12b\\toolchains\\arm-linux-androideabi-4.9\\prebuilt\\windows-x86_64\\lib\\gcc\\arm-linux-androideabi\\4.9.x\\include\\stdarg.h"
	.file 9 "d:\\android-ndk-r12b\\platforms\\android-9\\arch-arm\\usr\\include\\stdio.h"
	.file 10 "<built-in>"
	.file 11 "d:\\android-ndk-r12b\\platforms\\android-9\\arch-arm\\usr\\include\\pthread.h"
	.file 12 "jni/tracer/../util/Mutex.hpp"
	.file 13 "jni/tracer/../util/logger.h"
	.file 14 "d:\\android-ndk-r12b\\platforms\\android-9\\arch-arm\\usr\\include\\sys\\stat.h"
	.file 15 "d:\\android-ndk-r12b\\platforms\\android-9\\arch-arm\\usr\\include\\string.h"
	.file 16 "d:\\android-ndk-r12b\\platforms\\android-9\\arch-arm\\usr\\include\\time.h"
	.file 17 "d:\\android-ndk-r12b\\platforms\\android-9\\arch-arm\\usr\\include\\unistd.h"
	.section	.debug_info,"",%progbits
.Ldebug_info0:
	.4byte	0xdb7
	.2byte	0x4
	.4byte	.Ldebug_abbrev0
	.byte	0x4
	.uleb128 0x1
	.4byte	.LASF108
	.byte	0x4
	.4byte	.LASF109
	.4byte	.LASF110
	.4byte	.Ldebug_ranges0+0x78
	.4byte	0
	.4byte	.Ldebug_line0
	.uleb128 0x2
	.ascii	"std\000"
	.byte	0xa
	.byte	0
	.uleb128 0x3
	.4byte	.LASF0
	.byte	0x3
	.2byte	0x1a0
	.4byte	0x25
	.uleb128 0x3
	.4byte	.LASF1
	.byte	0x3
	.2byte	0x218
	.4byte	0x25
	.uleb128 0x3
	.4byte	.LASF2
	.byte	0x3
	.2byte	0x21c
	.4byte	0x25
	.uleb128 0x4
	.byte	0x4
	.byte	0x5
	.ascii	"int\000"
	.uleb128 0x5
	.4byte	.LASF13
	.byte	0x4
	.byte	0xd4
	.4byte	0x62
	.uleb128 0x6
	.byte	0x4
	.byte	0x7
	.4byte	.LASF3
	.uleb128 0x6
	.byte	0x8
	.byte	0x5
	.4byte	.LASF4
	.uleb128 0x6
	.byte	0x8
	.byte	0x4
	.4byte	.LASF5
	.uleb128 0x7
	.4byte	.LASF111
	.uleb128 0x6
	.byte	0x1
	.byte	0x6
	.4byte	.LASF6
	.uleb128 0x6
	.byte	0x1
	.byte	0x8
	.4byte	.LASF7
	.uleb128 0x6
	.byte	0x2
	.byte	0x5
	.4byte	.LASF8
	.uleb128 0x6
	.byte	0x2
	.byte	0x7
	.4byte	.LASF9
	.uleb128 0x6
	.byte	0x8
	.byte	0x7
	.4byte	.LASF10
	.uleb128 0x6
	.byte	0x4
	.byte	0x7
	.4byte	.LASF11
	.uleb128 0x6
	.byte	0x4
	.byte	0x5
	.4byte	.LASF12
	.uleb128 0x5
	.4byte	.LASF14
	.byte	0x5
	.byte	0x5e
	.4byte	0xb8
	.uleb128 0x8
	.4byte	.LASF14
	.byte	0x4
	.byte	0xa
	.byte	0
	.4byte	0xcf
	.uleb128 0x9
	.4byte	.LASF112
	.4byte	0xcf
	.byte	0
	.byte	0
	.uleb128 0xa
	.byte	0x4
	.uleb128 0x6
	.byte	0x4
	.byte	0x7
	.4byte	.LASF15
	.uleb128 0x6
	.byte	0x1
	.byte	0x8
	.4byte	.LASF16
	.uleb128 0x5
	.4byte	.LASF17
	.byte	0x6
	.byte	0x10
	.4byte	0x91
	.uleb128 0x5
	.4byte	.LASF18
	.byte	0x6
	.byte	0x12
	.4byte	0xa6
	.uleb128 0x5
	.4byte	.LASF19
	.byte	0x6
	.byte	0x13
	.4byte	0x50
	.uleb128 0x5
	.4byte	.LASF20
	.byte	0x6
	.byte	0x1a
	.4byte	0xa6
	.uleb128 0xb
	.byte	0x4
	.4byte	0xd8
	.uleb128 0x5
	.4byte	.LASF21
	.byte	0x7
	.byte	0x3f
	.4byte	0xdf
	.uleb128 0x5
	.4byte	.LASF22
	.byte	0x7
	.byte	0x43
	.4byte	0xea
	.uleb128 0x5
	.4byte	.LASF23
	.byte	0x7
	.byte	0x48
	.4byte	0xf5
	.uleb128 0x5
	.4byte	.LASF24
	.byte	0x7
	.byte	0x5e
	.4byte	0x100
	.uleb128 0x5
	.4byte	.LASF25
	.byte	0x8
	.byte	0x28
	.4byte	0xb8
	.uleb128 0x5
	.4byte	.LASF26
	.byte	0x9
	.byte	0x41
	.4byte	0x11c
	.uleb128 0x8
	.4byte	.LASF27
	.byte	0x8
	.byte	0x9
	.byte	0x4a
	.4byte	0x178
	.uleb128 0xc
	.4byte	.LASF28
	.byte	0x9
	.byte	0x4b
	.4byte	0x178
	.byte	0
	.uleb128 0xc
	.4byte	.LASF29
	.byte	0x9
	.byte	0x4c
	.4byte	0x50
	.byte	0x4
	.byte	0
	.uleb128 0xb
	.byte	0x4
	.4byte	0x83
	.uleb128 0x8
	.4byte	.LASF30
	.byte	0x54
	.byte	0x9
	.byte	0x6a
	.4byte	0x278
	.uleb128 0xd
	.ascii	"_p\000"
	.byte	0x9
	.byte	0x6b
	.4byte	0x178
	.byte	0
	.uleb128 0xd
	.ascii	"_r\000"
	.byte	0x9
	.byte	0x6c
	.4byte	0x50
	.byte	0x4
	.uleb128 0xd
	.ascii	"_w\000"
	.byte	0x9
	.byte	0x6d
	.4byte	0x50
	.byte	0x8
	.uleb128 0xc
	.4byte	.LASF31
	.byte	0x9
	.byte	0x6e
	.4byte	0x8a
	.byte	0xc
	.uleb128 0xc
	.4byte	.LASF32
	.byte	0x9
	.byte	0x6f
	.4byte	0x8a
	.byte	0xe
	.uleb128 0xd
	.ascii	"_bf\000"
	.byte	0x9
	.byte	0x70
	.4byte	0x153
	.byte	0x10
	.uleb128 0xc
	.4byte	.LASF33
	.byte	0x9
	.byte	0x71
	.4byte	0x50
	.byte	0x18
	.uleb128 0xc
	.4byte	.LASF34
	.byte	0x9
	.byte	0x74
	.4byte	0xcf
	.byte	0x1c
	.uleb128 0xc
	.4byte	.LASF35
	.byte	0x9
	.byte	0x75
	.4byte	0x287
	.byte	0x20
	.uleb128 0xc
	.4byte	.LASF36
	.byte	0x9
	.byte	0x76
	.4byte	0x2a6
	.byte	0x24
	.uleb128 0xc
	.4byte	.LASF37
	.byte	0x9
	.byte	0x77
	.4byte	0x2c5
	.byte	0x28
	.uleb128 0xc
	.4byte	.LASF38
	.byte	0x9
	.byte	0x78
	.4byte	0x2ef
	.byte	0x2c
	.uleb128 0xc
	.4byte	.LASF39
	.byte	0x9
	.byte	0x7b
	.4byte	0x153
	.byte	0x30
	.uleb128 0xd
	.ascii	"_up\000"
	.byte	0x9
	.byte	0x7d
	.4byte	0x178
	.byte	0x38
	.uleb128 0xd
	.ascii	"_ur\000"
	.byte	0x9
	.byte	0x7e
	.4byte	0x50
	.byte	0x3c
	.uleb128 0xc
	.4byte	.LASF40
	.byte	0x9
	.byte	0x81
	.4byte	0x2f5
	.byte	0x40
	.uleb128 0xc
	.4byte	.LASF41
	.byte	0x9
	.byte	0x82
	.4byte	0x305
	.byte	0x43
	.uleb128 0xd
	.ascii	"_lb\000"
	.byte	0x9
	.byte	0x85
	.4byte	0x153
	.byte	0x44
	.uleb128 0xc
	.4byte	.LASF42
	.byte	0x9
	.byte	0x88
	.4byte	0x50
	.byte	0x4c
	.uleb128 0xc
	.4byte	.LASF43
	.byte	0x9
	.byte	0x89
	.4byte	0x148
	.byte	0x50
	.byte	0
	.uleb128 0xe
	.4byte	0x50
	.4byte	0x287
	.uleb128 0xf
	.4byte	0xcf
	.byte	0
	.uleb128 0xb
	.byte	0x4
	.4byte	0x278
	.uleb128 0xe
	.4byte	0x50
	.4byte	0x2a6
	.uleb128 0xf
	.4byte	0xcf
	.uleb128 0xf
	.4byte	0x10b
	.uleb128 0xf
	.4byte	0x50
	.byte	0
	.uleb128 0xb
	.byte	0x4
	.4byte	0x28d
	.uleb128 0xe
	.4byte	0x148
	.4byte	0x2c5
	.uleb128 0xf
	.4byte	0xcf
	.uleb128 0xf
	.4byte	0x148
	.uleb128 0xf
	.4byte	0x50
	.byte	0
	.uleb128 0xb
	.byte	0x4
	.4byte	0x2ac
	.uleb128 0xe
	.4byte	0x50
	.4byte	0x2e4
	.uleb128 0xf
	.4byte	0xcf
	.uleb128 0xf
	.4byte	0x2e4
	.uleb128 0xf
	.4byte	0x50
	.byte	0
	.uleb128 0xb
	.byte	0x4
	.4byte	0x2ea
	.uleb128 0x10
	.4byte	0xd8
	.uleb128 0xb
	.byte	0x4
	.4byte	0x2cb
	.uleb128 0x11
	.4byte	0x83
	.4byte	0x305
	.uleb128 0x12
	.4byte	0xd1
	.byte	0x2
	.byte	0
	.uleb128 0x11
	.4byte	0x83
	.4byte	0x315
	.uleb128 0x12
	.4byte	0xd1
	.byte	0
	.byte	0
	.uleb128 0x5
	.4byte	.LASF44
	.byte	0x9
	.byte	0x8a
	.4byte	0x17e
	.uleb128 0x11
	.4byte	0xd8
	.4byte	0x330
	.uleb128 0x12
	.4byte	0xd1
	.byte	0x1f
	.byte	0
	.uleb128 0x5
	.4byte	.LASF45
	.byte	0x8
	.byte	0x62
	.4byte	0x13d
	.uleb128 0x13
	.byte	0x4
	.byte	0xb
	.byte	0x29
	.4byte	.LASF113
	.4byte	0x354
	.uleb128 0xc
	.4byte	.LASF46
	.byte	0xb
	.byte	0x2a
	.4byte	0x354
	.byte	0
	.byte	0
	.uleb128 0x14
	.4byte	0x50
	.uleb128 0x5
	.4byte	.LASF47
	.byte	0xb
	.byte	0x2b
	.4byte	0x33b
	.uleb128 0x15
	.byte	0x4
	.byte	0xb
	.byte	0x35
	.4byte	0x391
	.uleb128 0x16
	.4byte	.LASF48
	.sleb128 0
	.uleb128 0x16
	.4byte	.LASF49
	.sleb128 1
	.uleb128 0x16
	.4byte	.LASF50
	.sleb128 2
	.uleb128 0x16
	.4byte	.LASF51
	.sleb128 2
	.uleb128 0x16
	.4byte	.LASF52
	.sleb128 1
	.uleb128 0x16
	.4byte	.LASF53
	.sleb128 0
	.byte	0
	.uleb128 0x5
	.4byte	.LASF54
	.byte	0xc
	.byte	0x16
	.4byte	0x359
	.uleb128 0x17
	.4byte	.LASF58
	.byte	0x10
	.byte	0xd
	.byte	0x5
	.4byte	0x39c
	.4byte	0x547
	.uleb128 0x18
	.4byte	.LASF55
	.4byte	0x552
	.byte	0
	.byte	0x1
	.uleb128 0x19
	.4byte	.LASF56
	.byte	0xd
	.byte	0x7
	.4byte	0x391
	.byte	0x4
	.byte	0x1
	.uleb128 0x1a
	.ascii	"fp\000"
	.byte	0xd
	.byte	0x8
	.4byte	0x562
	.byte	0x8
	.byte	0x1
	.uleb128 0x19
	.4byte	.LASF57
	.byte	0xd
	.byte	0x9
	.4byte	0x568
	.byte	0xc
	.byte	0x1
	.uleb128 0x1b
	.4byte	.LASF58
	.4byte	.LASF114
	.4byte	0x56f
	.byte	0x1
	.4byte	0x3f3
	.4byte	0x3fe
	.uleb128 0x1c
	.4byte	0x56f
	.uleb128 0xf
	.4byte	0x575
	.byte	0
	.uleb128 0x1d
	.4byte	.LASF58
	.byte	0x1
	.byte	0xb
	.4byte	.LASF59
	.4byte	0x56f
	.byte	0x1
	.4byte	0x416
	.4byte	0x426
	.uleb128 0x1c
	.4byte	0x56f
	.uleb128 0xf
	.4byte	0x10b
	.uleb128 0xf
	.4byte	0x568
	.byte	0
	.uleb128 0x1d
	.4byte	.LASF58
	.byte	0x1
	.byte	0x18
	.4byte	.LASF60
	.4byte	0x56f
	.byte	0x1
	.4byte	0x43e
	.4byte	0x444
	.uleb128 0x1c
	.4byte	0x56f
	.byte	0
	.uleb128 0x1d
	.4byte	.LASF61
	.byte	0x1
	.byte	0x20
	.4byte	.LASF62
	.4byte	0xcf
	.byte	0x1
	.4byte	0x45c
	.4byte	0x467
	.uleb128 0x1c
	.4byte	0x56f
	.uleb128 0x1c
	.4byte	0x50
	.byte	0
	.uleb128 0x1e
	.4byte	.LASF63
	.byte	0x1
	.byte	0x44
	.4byte	.LASF68
	.byte	0x1
	.4byte	0x47b
	.4byte	0x490
	.uleb128 0x1c
	.4byte	0x56f
	.uleb128 0xf
	.4byte	0x562
	.uleb128 0xf
	.4byte	0x10b
	.uleb128 0xf
	.4byte	0x568
	.byte	0
	.uleb128 0x1f
	.4byte	.LASF63
	.byte	0x1
	.byte	0x5b
	.4byte	.LASF65
	.byte	0x1
	.uleb128 0x2
	.byte	0x10
	.uleb128 0
	.4byte	0x39c
	.byte	0x1
	.4byte	0x4ac
	.4byte	0x4b7
	.uleb128 0x1c
	.4byte	0x56f
	.uleb128 0xf
	.4byte	0x10b
	.byte	0
	.uleb128 0x1f
	.4byte	.LASF64
	.byte	0x1
	.byte	0x5f
	.4byte	.LASF66
	.byte	0x1
	.uleb128 0x2
	.byte	0x10
	.uleb128 0x1
	.4byte	0x39c
	.byte	0x1
	.4byte	0x4d3
	.4byte	0x4de
	.uleb128 0x1c
	.4byte	0x56f
	.uleb128 0xf
	.4byte	0x10b
	.byte	0
	.uleb128 0x1e
	.4byte	.LASF67
	.byte	0x1
	.byte	0x67
	.4byte	.LASF69
	.byte	0x1
	.4byte	0x4f2
	.4byte	0x502
	.uleb128 0x1c
	.4byte	0x56f
	.uleb128 0xf
	.4byte	0x178
	.uleb128 0xf
	.4byte	0x50
	.byte	0
	.uleb128 0x1d
	.4byte	.LASF70
	.byte	0x1
	.byte	0x29
	.4byte	.LASF71
	.4byte	0x10b
	.byte	0x1
	.4byte	0x51a
	.4byte	0x52a
	.uleb128 0x1c
	.4byte	0x56f
	.uleb128 0xf
	.4byte	0x178
	.uleb128 0xf
	.4byte	0x50
	.byte	0
	.uleb128 0x20
	.4byte	.LASF115
	.byte	0x1
	.byte	0x3a
	.4byte	.LASF116
	.byte	0x1
	.4byte	0x53a
	.uleb128 0x1c
	.4byte	0x56f
	.uleb128 0xf
	.4byte	0x10b
	.uleb128 0x21
	.byte	0
	.byte	0
	.uleb128 0xe
	.4byte	0x50
	.4byte	0x552
	.uleb128 0x21
	.byte	0
	.uleb128 0xb
	.byte	0x4
	.4byte	0x558
	.uleb128 0x22
	.byte	0x4
	.4byte	.LASF117
	.4byte	0x547
	.uleb128 0xb
	.byte	0x4
	.4byte	0x315
	.uleb128 0x6
	.byte	0x1
	.byte	0x2
	.4byte	.LASF72
	.uleb128 0xb
	.byte	0x4
	.4byte	0x39c
	.uleb128 0x23
	.byte	0x4
	.4byte	0x57b
	.uleb128 0x10
	.4byte	0x39c
	.uleb128 0x24
	.4byte	.LASF91
	.byte	0x2
	.byte	0x66
	.4byte	0x50
	.byte	0x3
	.4byte	0x59a
	.uleb128 0x25
	.ascii	"c\000"
	.byte	0x2
	.byte	0x66
	.4byte	0x50
	.byte	0
	.uleb128 0x26
	.4byte	0x3fe
	.byte	0
	.4byte	0x5a8
	.4byte	0x5c8
	.uleb128 0x27
	.4byte	.LASF75
	.4byte	0x5c8
	.uleb128 0x28
	.4byte	.LASF73
	.byte	0x1
	.byte	0xb
	.4byte	0x10b
	.uleb128 0x28
	.4byte	.LASF74
	.byte	0x1
	.byte	0xb
	.4byte	0x568
	.byte	0
	.uleb128 0x10
	.4byte	0x56f
	.uleb128 0x29
	.4byte	0x59a
	.4byte	.LASF76
	.4byte	.LFB30
	.4byte	.LFE30-.LFB30
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x5e8
	.4byte	0x643
	.uleb128 0x2a
	.4byte	0x5a8
	.4byte	.LLST0
	.uleb128 0x2a
	.4byte	0x5b1
	.4byte	.LLST1
	.uleb128 0x2a
	.4byte	0x5bc
	.4byte	.LLST2
	.uleb128 0x2b
	.4byte	.LVL2
	.4byte	0xc1f
	.4byte	0x617
	.uleb128 0x2c
	.uleb128 0x1
	.byte	0x50
	.uleb128 0x2
	.byte	0x74
	.sleb128 4
	.byte	0
	.uleb128 0x2b
	.4byte	.LVL3
	.4byte	0xc36
	.4byte	0x62b
	.uleb128 0x2c
	.uleb128 0x1
	.byte	0x50
	.uleb128 0x2
	.byte	0x75
	.sleb128 0
	.byte	0
	.uleb128 0x2d
	.4byte	.LVL4
	.4byte	0xc50
	.uleb128 0x2c
	.uleb128 0x1
	.byte	0x51
	.uleb128 0x3
	.byte	0xa
	.2byte	0x1ff
	.uleb128 0x2c
	.uleb128 0x1
	.byte	0x50
	.uleb128 0x2
	.byte	0x75
	.sleb128 0
	.byte	0
	.byte	0
	.uleb128 0x26
	.4byte	0x426
	.byte	0
	.4byte	0x651
	.4byte	0x65b
	.uleb128 0x27
	.4byte	.LASF75
	.4byte	0x5c8
	.byte	0
	.uleb128 0x29
	.4byte	0x643
	.4byte	.LASF77
	.4byte	.LFB33
	.4byte	.LFE33-.LFB33
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x676
	.4byte	0x690
	.uleb128 0x2a
	.4byte	0x651
	.4byte	.LLST3
	.uleb128 0x2d
	.4byte	.LVL9
	.4byte	0xc1f
	.uleb128 0x2c
	.uleb128 0x1
	.byte	0x50
	.uleb128 0x2
	.byte	0x74
	.sleb128 4
	.byte	0
	.byte	0
	.uleb128 0x26
	.4byte	0x444
	.byte	0
	.4byte	0x69e
	.4byte	0x6b1
	.uleb128 0x27
	.4byte	.LASF75
	.4byte	0x5c8
	.uleb128 0x27
	.4byte	.LASF78
	.4byte	0x6b1
	.byte	0
	.uleb128 0x10
	.4byte	0x50
	.uleb128 0x29
	.4byte	0x690
	.4byte	.LASF79
	.4byte	.LFB36
	.4byte	.LFE36-.LFB36
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x6d1
	.4byte	0x6e4
	.uleb128 0x2a
	.4byte	0x69e
	.4byte	.LLST4
	.uleb128 0x2e
	.4byte	.LVL13
	.4byte	0xc6a
	.byte	0
	.uleb128 0x2f
	.4byte	0x502
	.4byte	.LFB38
	.4byte	.LFE38-.LFB38
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x6fb
	.4byte	0x7c1
	.uleb128 0x30
	.4byte	.LASF75
	.4byte	0x5c8
	.4byte	.LLST5
	.uleb128 0x31
	.ascii	"p\000"
	.byte	0x1
	.byte	0x29
	.4byte	0x178
	.4byte	.LLST6
	.uleb128 0x31
	.ascii	"len\000"
	.byte	0x1
	.byte	0x29
	.4byte	0x50
	.4byte	.LLST7
	.uleb128 0x32
	.4byte	.Ldebug_ranges0+0
	.4byte	0x7b7
	.uleb128 0x33
	.ascii	"tmp\000"
	.byte	0x1
	.byte	0x2b
	.4byte	0x7c1
	.uleb128 0x5
	.byte	0x3
	.4byte	_ZZN6Logger5toHexEPhiE3tmp
	.uleb128 0x33
	.ascii	"t\000"
	.byte	0x1
	.byte	0x2c
	.4byte	0x320
	.uleb128 0x2
	.byte	0x91
	.sleb128 -60
	.uleb128 0x34
	.4byte	.LBB25
	.4byte	.LBE25-.LBB25
	.4byte	0x789
	.uleb128 0x35
	.ascii	"i\000"
	.byte	0x1
	.byte	0x2f
	.4byte	0x50
	.4byte	.LLST8
	.uleb128 0x2b
	.4byte	.LVL19
	.4byte	0xc7f
	.4byte	0x778
	.uleb128 0x2c
	.uleb128 0x1
	.byte	0x50
	.uleb128 0x2
	.byte	0x75
	.sleb128 0
	.byte	0
	.uleb128 0x2d
	.4byte	.LVL20
	.4byte	0xc9a
	.uleb128 0x2c
	.uleb128 0x1
	.byte	0x51
	.uleb128 0x2
	.byte	0x75
	.sleb128 0
	.byte	0
	.byte	0
	.uleb128 0x2b
	.4byte	.LVL17
	.4byte	0xcb4
	.4byte	0x79d
	.uleb128 0x2c
	.uleb128 0x1
	.byte	0x50
	.uleb128 0x2
	.byte	0x76
	.sleb128 0
	.byte	0
	.uleb128 0x2e
	.4byte	.LVL22
	.4byte	0xc9a
	.uleb128 0x2d
	.4byte	.LVL23
	.4byte	0xcc5
	.uleb128 0x2c
	.uleb128 0x1
	.byte	0x50
	.uleb128 0x2
	.byte	0x76
	.sleb128 0
	.byte	0
	.byte	0
	.uleb128 0x2e
	.4byte	.LVL24
	.4byte	0xcd6
	.byte	0
	.uleb128 0x11
	.4byte	0xd8
	.4byte	0x7d4
	.uleb128 0x36
	.4byte	0xd1
	.4byte	0xf9fff
	.byte	0
	.uleb128 0x2f
	.4byte	0x52a
	.4byte	.LFB39
	.4byte	.LFE39-.LFB39
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x7eb
	.4byte	0x86c
	.uleb128 0x30
	.4byte	.LASF75
	.4byte	0x5c8
	.4byte	.LLST9
	.uleb128 0x37
	.4byte	.LASF80
	.byte	0x1
	.byte	0x3a
	.4byte	0x10b
	.uleb128 0x2
	.byte	0x91
	.sleb128 -12
	.uleb128 0x21
	.uleb128 0x32
	.4byte	.Ldebug_ranges0+0x28
	.4byte	0x862
	.uleb128 0x38
	.4byte	.LASF81
	.byte	0x1
	.byte	0x3c
	.4byte	0x86c
	.uleb128 0x3
	.byte	0x91
	.sleb128 -2084
	.uleb128 0x38
	.4byte	.LASF82
	.byte	0x1
	.byte	0x3d
	.4byte	0x330
	.uleb128 0x3
	.byte	0x91
	.sleb128 -2088
	.uleb128 0x2b
	.4byte	.LVL31
	.4byte	0xcdb
	.4byte	0x84f
	.uleb128 0x2c
	.uleb128 0x1
	.byte	0x52
	.uleb128 0x2
	.byte	0x91
	.sleb128 -32
	.uleb128 0x2c
	.uleb128 0x1
	.byte	0x51
	.uleb128 0x3
	.byte	0x91
	.sleb128 -36
	.byte	0x6
	.uleb128 0x2c
	.uleb128 0x1
	.byte	0x50
	.uleb128 0x2
	.byte	0x75
	.sleb128 0
	.byte	0
	.uleb128 0x39
	.4byte	.LVL32
	.uleb128 0x2c
	.uleb128 0x1
	.byte	0x51
	.uleb128 0x2
	.byte	0x75
	.sleb128 0
	.uleb128 0x2c
	.uleb128 0x1
	.byte	0x50
	.uleb128 0x2
	.byte	0x76
	.sleb128 0
	.byte	0
	.byte	0
	.uleb128 0x2e
	.4byte	.LVL33
	.4byte	0xcd6
	.byte	0
	.uleb128 0x11
	.4byte	0xd8
	.4byte	0x87d
	.uleb128 0x3a
	.4byte	0xd1
	.2byte	0x7ff
	.byte	0
	.uleb128 0x2f
	.4byte	0x467
	.4byte	.LFB40
	.4byte	.LFE40-.LFB40
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x894
	.4byte	0x9da
	.uleb128 0x30
	.4byte	.LASF75
	.4byte	0x5c8
	.4byte	.LLST10
	.uleb128 0x3b
	.4byte	.LASF83
	.byte	0x1
	.byte	0x44
	.4byte	0x562
	.4byte	.LLST11
	.uleb128 0x31
	.ascii	"p\000"
	.byte	0x1
	.byte	0x44
	.4byte	0x10b
	.4byte	.LLST12
	.uleb128 0x3b
	.4byte	.LASF84
	.byte	0x1
	.byte	0x44
	.4byte	0x568
	.4byte	.LLST13
	.uleb128 0x34
	.4byte	.LBB33
	.4byte	.LBE33-.LBB33
	.4byte	0x9d0
	.uleb128 0x33
	.ascii	"t\000"
	.byte	0x1
	.byte	0x49
	.4byte	0x132
	.uleb128 0x2
	.byte	0x91
	.sleb128 -32
	.uleb128 0x3c
	.4byte	.LASF85
	.byte	0x1
	.byte	0x4b
	.4byte	0x10b
	.4byte	.LLST14
	.uleb128 0x2b
	.4byte	.LVL39
	.4byte	0xcb4
	.4byte	0x908
	.uleb128 0x2c
	.uleb128 0x1
	.byte	0x50
	.uleb128 0x2
	.byte	0x77
	.sleb128 0
	.byte	0
	.uleb128 0x2b
	.4byte	.LVL40
	.4byte	0xcfb
	.4byte	0x91c
	.uleb128 0x2c
	.uleb128 0x1
	.byte	0x50
	.uleb128 0x2
	.byte	0x75
	.sleb128 0
	.byte	0
	.uleb128 0x2b
	.4byte	.LVL41
	.4byte	0xd16
	.4byte	0x930
	.uleb128 0x2c
	.uleb128 0x1
	.byte	0x50
	.uleb128 0x2
	.byte	0x75
	.sleb128 0
	.byte	0
	.uleb128 0x2b
	.4byte	.LVL43
	.4byte	0xd36
	.4byte	0x944
	.uleb128 0x2c
	.uleb128 0x1
	.byte	0x50
	.uleb128 0x2
	.byte	0x75
	.sleb128 0
	.byte	0
	.uleb128 0x2b
	.4byte	.LVL44
	.4byte	0xd4b
	.4byte	0x95e
	.uleb128 0x2c
	.uleb128 0x1
	.byte	0x52
	.uleb128 0x2
	.byte	0x76
	.sleb128 0
	.uleb128 0x2c
	.uleb128 0x1
	.byte	0x50
	.uleb128 0x2
	.byte	0x74
	.sleb128 0
	.byte	0
	.uleb128 0x2e
	.4byte	.LVL45
	.4byte	0xd66
	.uleb128 0x2b
	.4byte	.LVL46
	.4byte	0xd4b
	.4byte	0x981
	.uleb128 0x2c
	.uleb128 0x1
	.byte	0x53
	.uleb128 0x2
	.byte	0x76
	.sleb128 0
	.uleb128 0x2c
	.uleb128 0x1
	.byte	0x50
	.uleb128 0x2
	.byte	0x74
	.sleb128 0
	.byte	0
	.uleb128 0x2e
	.4byte	.LVL47
	.4byte	0xd66
	.uleb128 0x2b
	.4byte	.LVL48
	.4byte	0xd4b
	.4byte	0x9ab
	.uleb128 0x2c
	.uleb128 0x1
	.byte	0x52
	.uleb128 0x2
	.byte	0x75
	.sleb128 0
	.uleb128 0x2c
	.uleb128 0x1
	.byte	0x50
	.uleb128 0x2
	.byte	0x74
	.sleb128 0
	.uleb128 0x2c
	.uleb128 0x2
	.byte	0x7d
	.sleb128 0
	.uleb128 0x2
	.byte	0x76
	.sleb128 0
	.byte	0
	.uleb128 0x2b
	.4byte	.LVL49
	.4byte	0xd71
	.4byte	0x9bf
	.uleb128 0x2c
	.uleb128 0x1
	.byte	0x50
	.uleb128 0x2
	.byte	0x74
	.sleb128 0
	.byte	0
	.uleb128 0x2d
	.4byte	.LVL50
	.4byte	0xcc5
	.uleb128 0x2c
	.uleb128 0x1
	.byte	0x50
	.uleb128 0x2
	.byte	0x77
	.sleb128 0
	.byte	0
	.byte	0
	.uleb128 0x2e
	.4byte	.LVL51
	.4byte	0xcd6
	.byte	0
	.uleb128 0x2f
	.4byte	0x490
	.4byte	.LFB41
	.4byte	.LFE41-.LFB41
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x9f1
	.4byte	0xa29
	.uleb128 0x30
	.4byte	.LASF75
	.4byte	0x5c8
	.4byte	.LLST15
	.uleb128 0x31
	.ascii	"p\000"
	.byte	0x1
	.byte	0x5b
	.4byte	0x10b
	.4byte	.LLST16
	.uleb128 0x2d
	.4byte	.LVL56
	.4byte	0x87d
	.uleb128 0x2c
	.uleb128 0x1
	.byte	0x53
	.uleb128 0x1
	.byte	0x30
	.uleb128 0x2c
	.uleb128 0x1
	.byte	0x52
	.uleb128 0x3
	.byte	0xf3
	.uleb128 0x1
	.byte	0x51
	.uleb128 0x2c
	.uleb128 0x1
	.byte	0x50
	.uleb128 0x3
	.byte	0xf3
	.uleb128 0x1
	.byte	0x50
	.byte	0
	.byte	0
	.uleb128 0x2f
	.4byte	0x4b7
	.4byte	.LFB42
	.4byte	.LFE42-.LFB42
	.uleb128 0x1
	.byte	0x9c
	.4byte	0xa40
	.4byte	0xa78
	.uleb128 0x30
	.4byte	.LASF75
	.4byte	0x5c8
	.4byte	.LLST17
	.uleb128 0x31
	.ascii	"p\000"
	.byte	0x1
	.byte	0x5f
	.4byte	0x10b
	.4byte	.LLST18
	.uleb128 0x2d
	.4byte	.LVL59
	.4byte	0x87d
	.uleb128 0x2c
	.uleb128 0x1
	.byte	0x53
	.uleb128 0x1
	.byte	0x31
	.uleb128 0x2c
	.uleb128 0x1
	.byte	0x52
	.uleb128 0x3
	.byte	0xf3
	.uleb128 0x1
	.byte	0x51
	.uleb128 0x2c
	.uleb128 0x1
	.byte	0x50
	.uleb128 0x3
	.byte	0xf3
	.uleb128 0x1
	.byte	0x50
	.byte	0
	.byte	0
	.uleb128 0x2f
	.4byte	0x4de
	.4byte	.LFB43
	.4byte	.LFE43-.LFB43
	.uleb128 0x1
	.byte	0x9c
	.4byte	0xa8f
	.4byte	0xbdd
	.uleb128 0x30
	.4byte	.LASF75
	.4byte	0x5c8
	.4byte	.LLST19
	.uleb128 0x31
	.ascii	"p\000"
	.byte	0x1
	.byte	0x67
	.4byte	0x178
	.4byte	.LLST20
	.uleb128 0x31
	.ascii	"len\000"
	.byte	0x1
	.byte	0x67
	.4byte	0x50
	.4byte	.LLST21
	.uleb128 0x3d
	.4byte	.Ldebug_ranges0+0x48
	.uleb128 0x35
	.ascii	"i\000"
	.byte	0x1
	.byte	0x69
	.4byte	0x50
	.4byte	.LLST22
	.uleb128 0x35
	.ascii	"j\000"
	.byte	0x1
	.byte	0x69
	.4byte	0x50
	.4byte	.LLST23
	.uleb128 0x3e
	.4byte	.LBB36
	.4byte	.LBE36-.LBB36
	.uleb128 0x3c
	.4byte	.LASF86
	.byte	0x1
	.byte	0x7a
	.4byte	0x50
	.4byte	.LLST24
	.uleb128 0x34
	.4byte	.LBB42
	.4byte	.LBE42-.LBB42
	.4byte	0xb31
	.uleb128 0x35
	.ascii	"ch\000"
	.byte	0x1
	.byte	0x70
	.4byte	0x83
	.4byte	.LLST25
	.uleb128 0x3f
	.4byte	0x580
	.4byte	.LBB43
	.4byte	.Ldebug_ranges0+0x60
	.byte	0x1
	.byte	0x71
	.4byte	0xb27
	.uleb128 0x2a
	.4byte	0x590
	.4byte	.LLST26
	.byte	0
	.uleb128 0x2e
	.4byte	.LVL70
	.4byte	0xd86
	.byte	0
	.uleb128 0x34
	.4byte	.LBB51
	.4byte	.LBE51-.LBB51
	.4byte	0xb73
	.uleb128 0x35
	.ascii	"ch\000"
	.byte	0x1
	.byte	0x81
	.4byte	0x83
	.4byte	.LLST27
	.uleb128 0x40
	.4byte	0x580
	.4byte	.LBB52
	.4byte	.LBE52-.LBB52
	.byte	0x1
	.byte	0x82
	.4byte	0xb69
	.uleb128 0x2a
	.4byte	0x590
	.4byte	.LLST28
	.byte	0
	.uleb128 0x2e
	.4byte	.LVL81
	.4byte	0xd86
	.byte	0
	.uleb128 0x2b
	.4byte	.LVL62
	.4byte	0xcb4
	.4byte	0xb88
	.uleb128 0x2c
	.uleb128 0x1
	.byte	0x50
	.uleb128 0x3
	.byte	0x91
	.sleb128 -32
	.byte	0x6
	.byte	0
	.uleb128 0x2e
	.4byte	.LVL65
	.4byte	0xd4b
	.uleb128 0x2b
	.4byte	.LVL71
	.4byte	0xd86
	.4byte	0xba4
	.uleb128 0x2c
	.uleb128 0x1
	.byte	0x50
	.uleb128 0x1
	.byte	0x3a
	.byte	0
	.uleb128 0x2e
	.4byte	.LVL77
	.4byte	0xda2
	.uleb128 0x2b
	.4byte	.LVL83
	.4byte	0xd86
	.4byte	0xbc0
	.uleb128 0x2c
	.uleb128 0x1
	.byte	0x50
	.uleb128 0x1
	.byte	0x3a
	.byte	0
	.uleb128 0x2e
	.4byte	.LVL84
	.4byte	0xd71
	.uleb128 0x2d
	.4byte	.LVL85
	.4byte	0xcc5
	.uleb128 0x2c
	.uleb128 0x1
	.byte	0x50
	.uleb128 0x3
	.byte	0x91
	.sleb128 -32
	.byte	0x6
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x11
	.4byte	0x17e
	.4byte	0xbe8
	.uleb128 0x41
	.byte	0
	.uleb128 0x42
	.4byte	.LASF87
	.byte	0x9
	.byte	0x8d
	.4byte	0xbdd
	.uleb128 0x42
	.4byte	.LASF88
	.byte	0x2
	.byte	0x38
	.4byte	0x2e4
	.uleb128 0x42
	.4byte	.LASF89
	.byte	0x2
	.byte	0x39
	.4byte	0xc09
	.uleb128 0xb
	.byte	0x4
	.4byte	0xc0f
	.uleb128 0x10
	.4byte	0x8a
	.uleb128 0x42
	.4byte	.LASF90
	.byte	0x2
	.byte	0x3a
	.4byte	0xc09
	.uleb128 0x43
	.4byte	.LASF97
	.byte	0xc
	.byte	0x17
	.4byte	0xc30
	.uleb128 0xf
	.4byte	0xc30
	.byte	0
	.uleb128 0xb
	.byte	0x4
	.4byte	0x391
	.uleb128 0x44
	.4byte	.LASF92
	.byte	0x9
	.byte	0xdb
	.4byte	0x562
	.4byte	0xc50
	.uleb128 0xf
	.4byte	0x2e4
	.uleb128 0xf
	.4byte	0x2e4
	.byte	0
	.uleb128 0x44
	.4byte	.LASF93
	.byte	0xe
	.byte	0x73
	.4byte	0x50
	.4byte	0xc6a
	.uleb128 0xf
	.4byte	0x2e4
	.uleb128 0xf
	.4byte	0x111
	.byte	0
	.uleb128 0x44
	.4byte	.LASF94
	.byte	0x9
	.byte	0xd4
	.4byte	0x50
	.4byte	0xc7f
	.uleb128 0xf
	.4byte	0x562
	.byte	0
	.uleb128 0x44
	.4byte	.LASF95
	.byte	0x9
	.byte	0xfc
	.4byte	0x50
	.4byte	0xc9a
	.uleb128 0xf
	.4byte	0x10b
	.uleb128 0xf
	.4byte	0x2e4
	.uleb128 0x21
	.byte	0
	.uleb128 0x44
	.4byte	.LASF96
	.byte	0xf
	.byte	0x37
	.4byte	0x10b
	.4byte	0xcb4
	.uleb128 0xf
	.4byte	0x10b
	.uleb128 0xf
	.4byte	0x2e4
	.byte	0
	.uleb128 0x43
	.4byte	.LASF98
	.byte	0xc
	.byte	0x19
	.4byte	0xcc5
	.uleb128 0xf
	.4byte	0xc30
	.byte	0
	.uleb128 0x43
	.4byte	.LASF99
	.byte	0xc
	.byte	0x1a
	.4byte	0xcd6
	.uleb128 0xf
	.4byte	0xc30
	.byte	0
	.uleb128 0x45
	.4byte	.LASF118
	.uleb128 0x46
	.4byte	.LASF100
	.byte	0x9
	.2byte	0x103
	.4byte	0x50
	.4byte	0xcfb
	.uleb128 0xf
	.4byte	0x10b
	.uleb128 0xf
	.4byte	0x2e4
	.uleb128 0xf
	.4byte	0xad
	.byte	0
	.uleb128 0x44
	.4byte	.LASF101
	.byte	0x10
	.byte	0x28
	.4byte	0x132
	.4byte	0xd10
	.uleb128 0xf
	.4byte	0xd10
	.byte	0
	.uleb128 0xb
	.byte	0x4
	.4byte	0x132
	.uleb128 0x44
	.4byte	.LASF102
	.byte	0x10
	.byte	0x52
	.4byte	0x10b
	.4byte	0xd2b
	.uleb128 0xf
	.4byte	0xd2b
	.byte	0
	.uleb128 0xb
	.byte	0x4
	.4byte	0xd31
	.uleb128 0x10
	.4byte	0x132
	.uleb128 0x44
	.4byte	.LASF103
	.byte	0xf
	.byte	0x34
	.4byte	0x57
	.4byte	0xd4b
	.uleb128 0xf
	.4byte	0x2e4
	.byte	0
	.uleb128 0x44
	.4byte	.LASF104
	.byte	0x9
	.byte	0xdc
	.4byte	0x50
	.4byte	0xd66
	.uleb128 0xf
	.4byte	0x562
	.uleb128 0xf
	.4byte	0x2e4
	.uleb128 0x21
	.byte	0
	.uleb128 0x47
	.4byte	.LASF119
	.byte	0x11
	.byte	0x39
	.4byte	0x127
	.uleb128 0x44
	.4byte	.LASF105
	.byte	0x9
	.byte	0xd7
	.4byte	0x50
	.4byte	0xd86
	.uleb128 0xf
	.4byte	0x562
	.byte	0
	.uleb128 0x48
	.4byte	.LASF106
	.4byte	.LASF120
	.4byte	0x50
	.4byte	0xda2
	.uleb128 0xf
	.4byte	0x50
	.uleb128 0xf
	.4byte	0x562
	.byte	0
	.uleb128 0x49
	.4byte	.LASF107
	.4byte	.LASF121
	.4byte	0x50
	.uleb128 0xf
	.4byte	0x2e4
	.uleb128 0xf
	.4byte	0x562
	.byte	0
	.byte	0
	.section	.debug_abbrev,"",%progbits
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
	.uleb128 0x9
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xb
	.uleb128 0x34
	.uleb128 0x19
	.byte	0
	.byte	0
	.uleb128 0xa
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0xb
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x49
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
	.uleb128 0x4
	.byte	0x1
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
	.uleb128 0x28
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1c
	.uleb128 0xd
	.byte	0
	.byte	0
	.uleb128 0x17
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
	.uleb128 0x1d
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x18
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xb
	.uleb128 0x34
	.uleb128 0x19
	.uleb128 0x32
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x19
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
	.uleb128 0x1a
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
	.uleb128 0x1b
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
	.uleb128 0x1c
	.uleb128 0x5
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x34
	.uleb128 0x19
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
	.uleb128 0x1e
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
	.uleb128 0x1f
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
	.uleb128 0x4c
	.uleb128 0xb
	.uleb128 0x4d
	.uleb128 0x18
	.uleb128 0x1d
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
	.uleb128 0x20
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
	.uleb128 0x21
	.uleb128 0x18
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x22
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
	.uleb128 0x23
	.uleb128 0x10
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x24
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
	.uleb128 0x25
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
	.uleb128 0x26
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x47
	.uleb128 0x13
	.uleb128 0x20
	.uleb128 0xb
	.uleb128 0x64
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x27
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
	.uleb128 0x28
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
	.uleb128 0x29
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
	.uleb128 0x2a
	.uleb128 0x5
	.byte	0
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x2b
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
	.uleb128 0x2c
	.uleb128 0x410a
	.byte	0
	.uleb128 0x2
	.uleb128 0x18
	.uleb128 0x2111
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x2d
	.uleb128 0x4109
	.byte	0x1
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x31
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x2e
	.uleb128 0x4109
	.byte	0
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x31
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x2f
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x47
	.uleb128 0x13
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
	.uleb128 0x30
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x34
	.uleb128 0x19
	.uleb128 0x2
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x31
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
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x32
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x55
	.uleb128 0x17
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x33
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
	.uleb128 0x34
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
	.uleb128 0x35
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
	.uleb128 0x36
	.uleb128 0x21
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x37
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
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x39
	.uleb128 0x4109
	.byte	0x1
	.uleb128 0x11
	.uleb128 0x1
	.byte	0
	.byte	0
	.uleb128 0x3a
	.uleb128 0x21
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0x5
	.byte	0
	.byte	0
	.uleb128 0x3b
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
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x3c
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
	.uleb128 0x3d
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x55
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x3e
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x3f
	.uleb128 0x1d
	.byte	0x1
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x52
	.uleb128 0x1
	.uleb128 0x55
	.uleb128 0x17
	.uleb128 0x58
	.uleb128 0xb
	.uleb128 0x59
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x40
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
	.uleb128 0x41
	.uleb128 0x21
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x42
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
	.uleb128 0x43
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
	.uleb128 0x44
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
	.uleb128 0x45
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
	.uleb128 0x46
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
	.uleb128 0x47
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
	.uleb128 0x48
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
	.uleb128 0x49
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
	.byte	0
	.byte	0
	.byte	0
	.section	.debug_loc,"",%progbits
.Ldebug_loc0:
.LLST0:
	.4byte	.LVL0
	.4byte	.LVL1
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL1
	.4byte	.LVL5
	.2byte	0x1
	.byte	0x54
	.4byte	.LVL5
	.4byte	.LFE30
	.2byte	0x1
	.byte	0x50
	.4byte	0
	.4byte	0
.LLST1:
	.4byte	.LVL0
	.4byte	.LVL2-1
	.2byte	0x1
	.byte	0x51
	.4byte	.LVL2-1
	.4byte	.LVL6
	.2byte	0x1
	.byte	0x55
	.4byte	.LVL6
	.4byte	.LFE30
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x51
	.byte	0x9f
	.4byte	0
	.4byte	0
.LLST2:
	.4byte	.LVL0
	.4byte	.LVL2-1
	.2byte	0x1
	.byte	0x52
	.4byte	.LVL2-1
	.4byte	.LFE30
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x52
	.byte	0x9f
	.4byte	0
	.4byte	0
.LLST3:
	.4byte	.LVL7
	.4byte	.LVL8
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL8
	.4byte	.LVL10
	.2byte	0x1
	.byte	0x54
	.4byte	.LVL10
	.4byte	.LFE33
	.2byte	0x1
	.byte	0x50
	.4byte	0
	.4byte	0
.LLST4:
	.4byte	.LVL11
	.4byte	.LVL12
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL12
	.4byte	.LVL14
	.2byte	0x1
	.byte	0x54
	.4byte	.LVL14
	.4byte	.LFE36
	.2byte	0x1
	.byte	0x50
	.4byte	0
	.4byte	0
.LLST5:
	.4byte	.LVL15
	.4byte	.LVL16
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL16
	.4byte	.LVL17-1
	.2byte	0x3
	.byte	0x70
	.sleb128 -4
	.byte	0x9f
	.4byte	.LVL17-1
	.4byte	.LVL27
	.2byte	0x3
	.byte	0x76
	.sleb128 -4
	.byte	0x9f
	.4byte	.LVL27
	.4byte	.LFE38
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x50
	.byte	0x9f
	.4byte	0
	.4byte	0
.LLST6:
	.4byte	.LVL15
	.4byte	.LVL17-1
	.2byte	0x1
	.byte	0x51
	.4byte	.LVL17-1
	.4byte	.LVL25
	.2byte	0x2
	.byte	0x7d
	.sleb128 0
	.4byte	.LVL25
	.4byte	.LFE38
	.2byte	0x3
	.byte	0x91
	.sleb128 -72
	.4byte	0
	.4byte	0
.LLST7:
	.4byte	.LVL15
	.4byte	.LVL17-1
	.2byte	0x1
	.byte	0x52
	.4byte	.LVL17-1
	.4byte	.LVL28
	.2byte	0x1
	.byte	0x57
	.4byte	.LVL28
	.4byte	.LFE38
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x52
	.byte	0x9f
	.4byte	0
	.4byte	0
.LLST8:
	.4byte	.LVL17
	.4byte	.LVL18
	.2byte	0x2
	.byte	0x30
	.byte	0x9f
	.4byte	.LVL18
	.4byte	.LVL26
	.2byte	0x1
	.byte	0x54
	.4byte	0
	.4byte	0
.LLST9:
	.4byte	.LVL29
	.4byte	.LVL30
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL30
	.4byte	.LVL34
	.2byte	0x1
	.byte	0x56
	.4byte	.LVL34
	.4byte	.LFE39
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x50
	.byte	0x9f
	.4byte	0
	.4byte	0
.LLST10:
	.4byte	.LVL35
	.4byte	.LVL38
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL38
	.4byte	.LFE40
	.2byte	0x2
	.byte	0x91
	.sleb128 -44
	.4byte	0
	.4byte	0
.LLST11:
	.4byte	.LVL35
	.4byte	.LVL39-1
	.2byte	0x1
	.byte	0x51
	.4byte	.LVL39-1
	.4byte	.LVL52
	.2byte	0x1
	.byte	0x54
	.4byte	.LVL52
	.4byte	.LFE40
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x51
	.byte	0x9f
	.4byte	0
	.4byte	0
.LLST12:
	.4byte	.LVL35
	.4byte	.LVL37
	.2byte	0x1
	.byte	0x52
	.4byte	.LVL37
	.4byte	.LVL53
	.2byte	0x1
	.byte	0x56
	.4byte	.LVL53
	.4byte	.LFE40
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x52
	.byte	0x9f
	.4byte	0
	.4byte	0
.LLST13:
	.4byte	.LVL35
	.4byte	.LVL36
	.2byte	0x1
	.byte	0x53
	.4byte	.LVL36
	.4byte	.LFE40
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x53
	.byte	0x9f
	.4byte	0
	.4byte	0
.LLST14:
	.4byte	.LVL42
	.4byte	.LVL43-1
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL43-1
	.4byte	.LVL50
	.2byte	0x1
	.byte	0x55
	.4byte	0
	.4byte	0
.LLST15:
	.4byte	.LVL54
	.4byte	.LVL56-1
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL56-1
	.4byte	.LFE41
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x50
	.byte	0x9f
	.4byte	0
	.4byte	0
.LLST16:
	.4byte	.LVL54
	.4byte	.LVL55
	.2byte	0x1
	.byte	0x51
	.4byte	.LVL55
	.4byte	.LVL56-1
	.2byte	0x1
	.byte	0x52
	.4byte	.LVL56-1
	.4byte	.LFE41
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x51
	.byte	0x9f
	.4byte	0
	.4byte	0
.LLST17:
	.4byte	.LVL57
	.4byte	.LVL59-1
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL59-1
	.4byte	.LFE42
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x50
	.byte	0x9f
	.4byte	0
	.4byte	0
.LLST18:
	.4byte	.LVL57
	.4byte	.LVL58
	.2byte	0x1
	.byte	0x51
	.4byte	.LVL58
	.4byte	.LVL59-1
	.2byte	0x1
	.byte	0x52
	.4byte	.LVL59-1
	.4byte	.LFE42
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x51
	.byte	0x9f
	.4byte	0
	.4byte	0
.LLST19:
	.4byte	.LVL60
	.4byte	.LVL61
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL61
	.4byte	.LVL85
	.2byte	0x1
	.byte	0x56
	.4byte	.LVL85
	.4byte	.LFE43
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x50
	.byte	0x9f
	.4byte	0
	.4byte	0
.LLST20:
	.4byte	.LVL60
	.4byte	.LVL62-1
	.2byte	0x1
	.byte	0x51
	.4byte	.LVL62-1
	.4byte	.LVL85
	.2byte	0x2
	.byte	0x91
	.sleb128 -28
	.4byte	.LVL85
	.4byte	.LFE43
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x51
	.byte	0x9f
	.4byte	0
	.4byte	0
.LLST21:
	.4byte	.LVL60
	.4byte	.LVL62-1
	.2byte	0x1
	.byte	0x52
	.4byte	.LVL62-1
	.4byte	.LVL85
	.2byte	0x2
	.byte	0x91
	.sleb128 -36
	.4byte	.LVL85
	.4byte	.LFE43
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x52
	.byte	0x9f
	.4byte	0
	.4byte	0
.LLST22:
	.4byte	.LVL62
	.4byte	.LVL63
	.2byte	0x2
	.byte	0x30
	.byte	0x9f
	.4byte	.LVL63
	.4byte	.LVL64
	.2byte	0x1
	.byte	0x57
	.4byte	.LVL64
	.4byte	.LVL72
	.2byte	0x3
	.byte	0x77
	.sleb128 -1
	.byte	0x9f
	.4byte	.LVL72
	.4byte	.LVL73
	.2byte	0x1
	.byte	0x57
	.4byte	0
	.4byte	0
.LLST23:
	.4byte	.LVL66
	.4byte	.LVL69
	.2byte	0x5
	.byte	0x40
	.byte	0x74
	.sleb128 0
	.byte	0x1c
	.byte	0x9f
	.4byte	.LVL69
	.4byte	.LVL70
	.2byte	0x5
	.byte	0x41
	.byte	0x74
	.sleb128 0
	.byte	0x1c
	.byte	0x9f
	.4byte	.LVL74
	.4byte	.LVL75
	.2byte	0x2
	.byte	0x30
	.byte	0x9f
	.4byte	.LVL75
	.4byte	.LVL76
	.2byte	0x1
	.byte	0x57
	.4byte	.LVL76
	.4byte	.LVL77
	.2byte	0x3
	.byte	0x77
	.sleb128 -1
	.byte	0x9f
	.4byte	.LVL77
	.4byte	.LVL78
	.2byte	0x1
	.byte	0x57
	.4byte	.LVL78
	.4byte	.LVL85
	.2byte	0x1
	.byte	0x54
	.4byte	0
	.4byte	0
.LLST24:
	.4byte	.LVL74
	.4byte	.LVL78
	.2byte	0x1
	.byte	0x54
	.4byte	.LVL78
	.4byte	.LVL85
	.2byte	0x5
	.byte	0x75
	.sleb128 0
	.byte	0x3f
	.byte	0x1a
	.byte	0x9f
	.4byte	0
	.4byte	0
.LLST25:
	.4byte	.LVL67
	.4byte	.LVL68
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL68
	.4byte	.LVL69
	.2byte	0x7
	.byte	0x72
	.sleb128 0
	.byte	0x74
	.sleb128 0
	.byte	0x22
	.byte	0x3f
	.byte	0x1c
	.4byte	.LVL69
	.4byte	.LVL70-1
	.2byte	0x7
	.byte	0x72
	.sleb128 0
	.byte	0x74
	.sleb128 0
	.byte	0x22
	.byte	0x40
	.byte	0x1c
	.4byte	0
	.4byte	0
.LLST26:
	.4byte	.LVL67
	.4byte	.LVL68
	.2byte	0x6
	.byte	0x70
	.sleb128 0
	.byte	0x8
	.byte	0xff
	.byte	0x1a
	.byte	0x9f
	.4byte	.LVL68
	.4byte	.LVL69
	.2byte	0xd
	.byte	0x72
	.sleb128 0
	.byte	0x74
	.sleb128 0
	.byte	0x22
	.byte	0x3f
	.byte	0x1c
	.byte	0x94
	.byte	0x1
	.byte	0x8
	.byte	0xff
	.byte	0x1a
	.byte	0x9f
	.4byte	.LVL69
	.4byte	.LVL70-1
	.2byte	0xd
	.byte	0x72
	.sleb128 0
	.byte	0x74
	.sleb128 0
	.byte	0x22
	.byte	0x40
	.byte	0x1c
	.byte	0x94
	.byte	0x1
	.byte	0x8
	.byte	0xff
	.byte	0x1a
	.byte	0x9f
	.4byte	0
	.4byte	0
.LLST27:
	.4byte	.LVL79
	.4byte	.LVL80
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL80
	.4byte	.LVL81-1
	.2byte	0x9
	.byte	0x91
	.sleb128 -28
	.byte	0x6
	.byte	0x75
	.sleb128 0
	.byte	0x22
	.byte	0x72
	.sleb128 0
	.byte	0x22
	.4byte	0
	.4byte	0
.LLST28:
	.4byte	.LVL79
	.4byte	.LVL80
	.2byte	0x6
	.byte	0x70
	.sleb128 0
	.byte	0x8
	.byte	0xff
	.byte	0x1a
	.byte	0x9f
	.4byte	.LVL80
	.4byte	.LVL81-1
	.2byte	0xf
	.byte	0x91
	.sleb128 -28
	.byte	0x6
	.byte	0x75
	.sleb128 0
	.byte	0x22
	.byte	0x72
	.sleb128 0
	.byte	0x22
	.byte	0x94
	.byte	0x1
	.byte	0x8
	.byte	0xff
	.byte	0x1a
	.byte	0x9f
	.4byte	0
	.4byte	0
	.section	.debug_aranges,"",%progbits
	.4byte	0x5c
	.2byte	0x2
	.4byte	.Ldebug_info0
	.byte	0x4
	.byte	0
	.2byte	0
	.2byte	0
	.4byte	.LFB30
	.4byte	.LFE30-.LFB30
	.4byte	.LFB33
	.4byte	.LFE33-.LFB33
	.4byte	.LFB36
	.4byte	.LFE36-.LFB36
	.4byte	.LFB38
	.4byte	.LFE38-.LFB38
	.4byte	.LFB39
	.4byte	.LFE39-.LFB39
	.4byte	.LFB40
	.4byte	.LFE40-.LFB40
	.4byte	.LFB41
	.4byte	.LFE41-.LFB41
	.4byte	.LFB42
	.4byte	.LFE42-.LFB42
	.4byte	.LFB43
	.4byte	.LFE43-.LFB43
	.4byte	0
	.4byte	0
	.section	.debug_ranges,"",%progbits
.Ldebug_ranges0:
	.4byte	.LBB24
	.4byte	.LBE24
	.4byte	.LBB26
	.4byte	.LBE26
	.4byte	.LBB27
	.4byte	.LBE27
	.4byte	.LBB28
	.4byte	.LBE28
	.4byte	0
	.4byte	0
	.4byte	.LBB29
	.4byte	.LBE29
	.4byte	.LBB30
	.4byte	.LBE30
	.4byte	.LBB31
	.4byte	.LBE31
	.4byte	0
	.4byte	0
	.4byte	.LBB34
	.4byte	.LBE34
	.4byte	.LBB55
	.4byte	.LBE55
	.4byte	0
	.4byte	0
	.4byte	.LBB43
	.4byte	.LBE43
	.4byte	.LBB46
	.4byte	.LBE46
	.4byte	0
	.4byte	0
	.4byte	.LFB30
	.4byte	.LFE30
	.4byte	.LFB33
	.4byte	.LFE33
	.4byte	.LFB36
	.4byte	.LFE36
	.4byte	.LFB38
	.4byte	.LFE38
	.4byte	.LFB39
	.4byte	.LFE39
	.4byte	.LFB40
	.4byte	.LFE40
	.4byte	.LFB41
	.4byte	.LFE41
	.4byte	.LFB42
	.4byte	.LFE42
	.4byte	.LFB43
	.4byte	.LFE43
	.4byte	0
	.4byte	0
	.section	.debug_line,"",%progbits
.Ldebug_line0:
	.section	.debug_str,"MS",%progbits,1
.LASF84:
	.ascii	"flgRaw\000"
.LASF103:
	.ascii	"strlen\000"
.LASF80:
	.ascii	"format\000"
.LASF68:
	.ascii	"_ZN6Logger6logStrEP7__sFILEPcb\000"
.LASF61:
	.ascii	"~Logger\000"
.LASF51:
	.ascii	"PTHREAD_MUTEX_ERRORCHECK_NP\000"
.LASF105:
	.ascii	"fflush\000"
.LASF93:
	.ascii	"chmod\000"
.LASF60:
	.ascii	"_ZN6LoggerC4Ev\000"
.LASF3:
	.ascii	"unsigned int\000"
.LASF79:
	.ascii	"_ZN6LoggerD2Ev\000"
.LASF33:
	.ascii	"_lbfsize\000"
.LASF31:
	.ascii	"_flags\000"
.LASF109:
	.ascii	"jni/tracer/../util/logger.cpp\000"
.LASF66:
	.ascii	"_ZN6Logger6logRawEPc\000"
.LASF114:
	.ascii	"_ZN6LoggerC4ERKS_\000"
.LASF98:
	.ascii	"MutexLock\000"
.LASF65:
	.ascii	"_ZN6Logger6logStrEPc\000"
.LASF120:
	.ascii	"fputc\000"
.LASF36:
	.ascii	"_read\000"
.LASF117:
	.ascii	"__vtbl_ptr_type\000"
.LASF121:
	.ascii	"fputs\000"
.LASF34:
	.ascii	"_cookie\000"
.LASF19:
	.ascii	"__kernel_pid_t\000"
.LASF99:
	.ascii	"MutexUnlock\000"
.LASF113:
	.ascii	"15pthread_mutex_t\000"
.LASF96:
	.ascii	"strcat\000"
.LASF26:
	.ascii	"fpos_t\000"
.LASF56:
	.ascii	"mutex\000"
.LASF10:
	.ascii	"long long unsigned int\000"
.LASF63:
	.ascii	"logStr\000"
.LASF83:
	.ascii	"file\000"
.LASF30:
	.ascii	"__sFILE\000"
.LASF49:
	.ascii	"PTHREAD_MUTEX_RECURSIVE\000"
.LASF116:
	.ascii	"_ZN6Logger6printfEPcz\000"
.LASF102:
	.ascii	"ctime\000"
.LASF43:
	.ascii	"_offset\000"
.LASF101:
	.ascii	"time\000"
.LASF55:
	.ascii	"_vptr.Logger\000"
.LASF46:
	.ascii	"value\000"
.LASF81:
	.ascii	"buff\000"
.LASF25:
	.ascii	"__gnuc_va_list\000"
.LASF13:
	.ascii	"size_t\000"
.LASF110:
	.ascii	"C:\\\\cygwin64\\\\home\\\\kwang\\\\C\\\\androidarm\000"
.LASF97:
	.ascii	"MutexCreate\000"
.LASF20:
	.ascii	"__kernel_time_t\000"
.LASF71:
	.ascii	"_ZN6Logger5toHexEPhi\000"
.LASF54:
	.ascii	"Mutex\000"
.LASF1:
	.ascii	"stlport\000"
.LASF100:
	.ascii	"vsprintf\000"
.LASF16:
	.ascii	"char\000"
.LASF39:
	.ascii	"_ext\000"
.LASF108:
	.ascii	"GNU C++ 4.9.x 20150123 (prerelease) -fpreprocessed "
	.ascii	"-mbionic -march=armv5te -mtune=xscale -mfloat-abi=s"
	.ascii	"oft -mthumb -mfpu=vfp -mtls-dialect=gnu -g -g -Os -"
	.ascii	"std=c++11 -fpic -ffunction-sections -funwind-tables"
	.ascii	" -fstack-protector-strong -fno-exceptions -frtti\000"
.LASF50:
	.ascii	"PTHREAD_MUTEX_ERRORCHECK\000"
.LASF90:
	.ascii	"_toupper_tab_\000"
.LASF24:
	.ascii	"time_t\000"
.LASF35:
	.ascii	"_close\000"
.LASF45:
	.ascii	"va_list\000"
.LASF4:
	.ascii	"long long int\000"
.LASF115:
	.ascii	"printf\000"
.LASF77:
	.ascii	"_ZN6LoggerC2Ev\000"
.LASF28:
	.ascii	"_base\000"
.LASF23:
	.ascii	"pid_t\000"
.LASF69:
	.ascii	"_ZN6Logger6logHexEPhi\000"
.LASF89:
	.ascii	"_tolower_tab_\000"
.LASF32:
	.ascii	"_file\000"
.LASF91:
	.ascii	"isalnum\000"
.LASF112:
	.ascii	"__ap\000"
.LASF76:
	.ascii	"_ZN6LoggerC2EPcb\000"
.LASF106:
	.ascii	"__builtin_fputc\000"
.LASF18:
	.ascii	"__kernel_off_t\000"
.LASF85:
	.ascii	"stime\000"
.LASF74:
	.ascii	"FLGNOTIME\000"
.LASF92:
	.ascii	"fopen\000"
.LASF119:
	.ascii	"gettid\000"
.LASF64:
	.ascii	"logRaw\000"
.LASF82:
	.ascii	"args\000"
.LASF5:
	.ascii	"long double\000"
.LASF95:
	.ascii	"sprintf\000"
.LASF73:
	.ascii	"logfile\000"
.LASF38:
	.ascii	"_write\000"
.LASF75:
	.ascii	"this\000"
.LASF48:
	.ascii	"PTHREAD_MUTEX_NORMAL\000"
.LASF87:
	.ascii	"__sF\000"
.LASF8:
	.ascii	"short int\000"
.LASF12:
	.ascii	"long int\000"
.LASF118:
	.ascii	"__stack_chk_fail\000"
.LASF94:
	.ascii	"fclose\000"
.LASF104:
	.ascii	"fprintf\000"
.LASF72:
	.ascii	"bool\000"
.LASF70:
	.ascii	"toHex\000"
.LASF78:
	.ascii	"__in_chrg\000"
.LASF42:
	.ascii	"_blksize\000"
.LASF14:
	.ascii	"__va_list\000"
.LASF15:
	.ascii	"sizetype\000"
.LASF11:
	.ascii	"long unsigned int\000"
.LASF62:
	.ascii	"_ZN6LoggerD4Ev\000"
.LASF47:
	.ascii	"pthread_mutex_t\000"
.LASF17:
	.ascii	"__kernel_mode_t\000"
.LASF58:
	.ascii	"Logger\000"
.LASF7:
	.ascii	"unsigned char\000"
.LASF59:
	.ascii	"_ZN6LoggerC4EPcb\000"
.LASF52:
	.ascii	"PTHREAD_MUTEX_RECURSIVE_NP\000"
.LASF111:
	.ascii	"decltype(nullptr)\000"
.LASF57:
	.ascii	"flgNoTime\000"
.LASF27:
	.ascii	"__sbuf\000"
.LASF2:
	.ascii	"_STL\000"
.LASF67:
	.ascii	"logHex\000"
.LASF88:
	.ascii	"_ctype_\000"
.LASF6:
	.ascii	"signed char\000"
.LASF21:
	.ascii	"mode_t\000"
.LASF22:
	.ascii	"off_t\000"
.LASF9:
	.ascii	"short unsigned int\000"
.LASF29:
	.ascii	"_size\000"
.LASF41:
	.ascii	"_nbuf\000"
.LASF0:
	.ascii	"__std_alias\000"
.LASF86:
	.ascii	"index\000"
.LASF44:
	.ascii	"FILE\000"
.LASF37:
	.ascii	"_seek\000"
.LASF107:
	.ascii	"__builtin_fputs\000"
.LASF53:
	.ascii	"PTHREAD_MUTEX_DEFAULT\000"
.LASF40:
	.ascii	"_ubuf\000"
	.ident	"GCC: (GNU) 4.9.x 20150123 (prerelease)"
	.section	.note.GNU-stack,"",%progbits
