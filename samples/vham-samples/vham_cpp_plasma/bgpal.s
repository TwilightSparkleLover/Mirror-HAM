	.file	"bgpal.cpp"
@ GNU C++ version 3.2.2 (arm-thumb-elf)
@	compiled by GNU C version 2.95.3-5 (cygwin special).
@ options passed:  -fpreprocessed -mthumb-interwork -mlong-calls -O2 -Wall
@ -fverbose-asm
@ options enabled:  -fdefer-pop -fomit-frame-pointer
@ -foptimize-sibling-calls -fcse-follow-jumps -fcse-skip-blocks
@ -fexpensive-optimizations -fthread-jumps -fstrength-reduce -fpeephole
@ -fforce-mem -ffunction-cse -fkeep-static-consts -fcaller-saves
@ -freg-struct-return -fgcse -fgcse-lm -fgcse-sm -frerun-cse-after-loop
@ -frerun-loop-opt -fdelete-null-pointer-checks -fschedule-insns
@ -fschedule-insns2 -fsched-interblock -fsched-spec -fbranch-count-reg
@ -fexceptions -freorder-blocks -fcprop-registers -fcommon -fverbose-asm
@ -fgnu-linker -fregmove -foptimize-register-move -fargument-alias
@ -fstrict-aliasing -fmerge-constants -fident -fpeephole2
@ -fguess-branch-probability -fmath-errno -ftrapping-math -mapcs
@ -mapcs-frame -mapcs-32 -msoft-float -mthumb-interwork -mlong-calls

	.text
	.align	2
	.global	_ZN6CBGPalC2Ev
	.type	_ZN6CBGPalC2Ev,function
_ZN6CBGPalC2Ev:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	mov	r3, #0
	strb	r3, [r0, #1]	@  <variable>.m_Mode
	strb	r3, [r0, #0]	@  <variable>.m_Value
	mov	r3, #8	@ movhi
	@ lr needed for prologue
	strh	r3, [r0, #2]	@ movhi 	@  <variable>.m_ColorValCount
	bx	lr
.Lfe1:
	.size	_ZN6CBGPalC2Ev,.Lfe1-_ZN6CBGPalC2Ev
	.align	2
	.global	_ZN6CBGPalC1Ev
	.type	_ZN6CBGPalC1Ev,function
_ZN6CBGPalC1Ev:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	mov	r3, #0
	strb	r3, [r0, #1]	@  <variable>.m_Mode
	strb	r3, [r0, #0]	@  <variable>.m_Value
	mov	r3, #8	@ movhi
	@ lr needed for prologue
	strh	r3, [r0, #2]	@ movhi 	@  <variable>.m_ColorValCount
	bx	lr
.Lfe2:
	.size	_ZN6CBGPalC1Ev,.Lfe2-_ZN6CBGPalC1Ev
	.data
	.type	_ZZN6CBGPal6SplashEPttaE6s_Mode,object
	.size	_ZZN6CBGPal6SplashEPttaE6s_Mode,1
_ZZN6CBGPal6SplashEPttaE6s_Mode:
	.byte	0
	.text
	.align	2
	.global	_ZN6CBGPal6SplashEPtta
	.type	_ZN6CBGPal6SplashEPtta,function
_ZN6CBGPal6SplashEPtta:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	mov	ip, sp
	stmfd	sp!, {r4, fp, ip, lr, pc}
	mov	r2, r2, asl #16
	ldr	r4, .L10
	mov	r2, r2, asr #16	@  palette_size
	mov	lr, r3
	sub	fp, ip, #4
	mov	r3, r2, asl #16	@  palette_size
	ldrb	ip, [r4, #0]	@ zero_extendqisi2	@  s_Mode
	mov	r2, r2, asl #16	@  palette_size
	mov	r3, r3, lsr #16
	and	lr, lr, #255	@  delta_per_call
	cmp	ip, #0
	mov	ip, r2, lsr #16
	mov	r2, r3
	mov	r3, lr, asl #24	@  delta_per_call
	mov	lr, lr, asl #24	@  delta_per_call
	mov	r3, r3, asr #24
	mov	lr, lr, asr #24
	bne	.L6
	ldr	ip, .L10+4
	mov	lr, pc
	bx	ip
	and	r0, r0, #255	@  this
	cmp	r0, #1
	streqb	r0, [r4, #0]	@  s_Mode
.L8:
	mov	r0, #0	@  this
.L5:
	ldmea	fp, {r4, fp, sp, lr}
	bx	lr
.L6:
	mov	r3, lr
	mov	r2, ip
	ldr	ip, .L10+8
	mov	lr, pc
	bx	ip
	and	r0, r0, #255	@  this,  this
	cmp	r0, #1	@  this
	moveq	r3, #0
	streqb	r3, [r4, #0]	@  s_Mode
	bne	.L8
	b	.L5
.L11:
	.align	2
.L10:
	.word	_ZZN6CBGPal6SplashEPttaE6s_Mode
	.word	_ZN6CBGPal2InEPtta
	.word	_ZN6CBGPal3OutEPtta
.Lfe3:
	.size	_ZN6CBGPal6SplashEPtta,.Lfe3-_ZN6CBGPal6SplashEPtta
	.data
	.type	_ZZN6CBGPal10SplashWaitEPttatE6s_Mode,object
	.size	_ZZN6CBGPal10SplashWaitEPttatE6s_Mode,1
_ZZN6CBGPal10SplashWaitEPttatE6s_Mode:
	.byte	0
	.align	1
	.type	_ZZN6CBGPal10SplashWaitEPttatE6s_Wait,object
	.size	_ZZN6CBGPal10SplashWaitEPttatE6s_Wait,2
_ZZN6CBGPal10SplashWaitEPttatE6s_Wait:
	.short	0
	.text
	.align	2
	.global	_ZN6CBGPal10SplashWaitEPttat
	.type	_ZN6CBGPal10SplashWaitEPttat,function
_ZN6CBGPal10SplashWaitEPttat:
	@ Function supports interworking.
	@ args = 4, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	ldr	r7, .L20
	sub	fp, ip, #4
	ldrb	ip, [r7, #0]	@ zero_extendqisi2	@  s_Mode
	mov	r2, r2, asl #16
	cmp	ip, #0
	ldrsh	ip, [fp, #4]	@  wait_value,  wait_value
	mov	r4, r2, asr #16	@  palette_size
	and	lr, r3, #255	@  delta_per_call
	mov	r2, r4, asl #16	@  palette_size
	mov	r3, lr, asl #24	@  delta_per_call
	mov	ip, ip, asl #16	@  wait_value
	ldr	r6, .L20+4
	mov	r2, r2, lsr #16
	mov	r3, r3, asr #24
	mov	r5, ip, lsr #16
	beq	.L18
	ldrh	ip, [r6, #0]	@ movhi	@  s_Wait
	mov	r2, r4, asl #16	@  palette_size
	mov	r3, lr, asl #24	@  delta_per_call
	cmp	r5, ip
	add	lr, ip, #1
	mov	r2, r2, lsr #16
	mov	r3, r3, asr #24
	mov	r4, #0	@  this
	strh	lr, [r6, #0]	@ movhi 	@  s_Wait
	bls	.L19
.L12:
	mov	r0, r4	@  this
	ldmea	fp, {r4, r5, r6, r7, fp, sp, lr}
	bx	lr
.L19:
	ldr	ip, .L20+8
	mov	lr, pc
	bx	ip
	and	r0, r0, #255	@  this,  this
	mov	r3, #0
	cmp	r0, #1	@  this
	mov	r4, r0	@  this,  this
	streqh	r3, [r6, #0]	@ movhi 	@  s_Wait
	streqb	r3, [r7, #0]	@  s_Mode
	beq	.L12
.L15:
	mov	r4, #0	@  this
	b	.L12
.L18:
	ldr	ip, .L20+12
	mov	lr, pc
	bx	ip
	and	r0, r0, #255	@  this
	cmp	r0, #1
	streqb	r0, [r7, #0]	@  s_Mode
	b	.L15
.L21:
	.align	2
.L20:
	.word	_ZZN6CBGPal10SplashWaitEPttatE6s_Mode
	.word	_ZZN6CBGPal10SplashWaitEPttatE6s_Wait
	.word	_ZN6CBGPal3OutEPtta
	.word	_ZN6CBGPal2InEPtta
.Lfe4:
	.size	_ZN6CBGPal10SplashWaitEPttat,.Lfe4-_ZN6CBGPal10SplashWaitEPttat
	.align	2
	.global	_ZN6CBGPal2InEPtta
	.type	_ZN6CBGPal2InEPtta,function
_ZN6CBGPal2InEPtta:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, fp, ip, lr, pc}
	sub	fp, ip, #4
	and	ip, r3, #255	@  delta_per_call
	mov	r3, ip, asl #24	@  delta_per_call
	mov	r2, r2, asl #16
	movs	lr, r3, asr #24
	mov	r4, r2, asr #16	@  palette_size
	mov	r5, r0	@  this
	mov	r7, r1	@  palette
	bmi	.L35
	ldrb	r3, [r0, #0]	@  <variable>.m_Value
	add	r3, r3, ip	@  delta_per_call
	and	r1, r3, #255
	rsb	r2, lr, #255
	cmp	r1, r2
	strb	r3, [r0, #0]	@  <variable>.m_Value
	movge	r0, #1	@  this
	bge	.L22
	mov	r6, r4, asl #16	@  palette_size
	mov	r4, #0	@  Idx
	cmp	r4, r6, lsr #16	@  Idx
	bcs	.L34
	mov	r0, r4	@  Idx,  Idx
	mov	r8, #83886080
.L32:
	mov	lr, r0, lsr #15	@  Idx
	ldrsh	r1, [lr, r7]	@  Color, * palette
	mov	r2, r1, asl #16	@  Color
	ldrb	ip, [r5, #0]	@ zero_extendqisi2	@  r,  <variable>.m_Value
	mov	r3, r2, lsr #18
	and	r3, r3, #248	@  g
	mov	r2, r2, lsr #23
	add	r0, r4, #1	@  Idx
	cmp	r3, ip	@  g,  r
	movcs	r3, ip	@  g,  r
	and	r2, r2, #248	@  b
	mov	r0, r0, asl #16
	cmp	r2, ip	@  b,  r
	movcs	r2, ip	@  b,  r
	mov	r3, r3, lsr #3	@  g
	and	r1, r1, #31	@  Color
	mov	r4, r0, asr #16	@  Idx
	mov	r1, r1, asl #3	@  r
	mov	r2, r2, lsr #3	@  b
	mov	r3, r3, asl #5
	cmp	r1, ip	@  r,  r
	movcs	r1, ip	@  r,  r
	mov	r0, r4, asl #16	@  Idx,  Idx
	add	r3, r3, r2, asl #10
	add	r3, r3, r1, lsr #3	@  r
	cmp	r0, r6	@  Idx
	strh	r3, [lr, r8]	@ movhi 
	bcc	.L32
.L34:
	mov	r0, #0	@  this
.L22:
	ldmea	fp, {r4, r5, r6, r7, r8, fp, sp, lr}
	bx	lr
.L35:
	rsb	r3, lr, #0
	mov	r2, r4, asl #16	@  palette_size
	mov	r3, r3, asl #24
	mov	r2, r2, lsr #16
	mov	r3, r3, asr #24
	ldr	ip, .L36
	mov	lr, pc
	bx	ip
	and	r0, r0, #255	@  this,  this
	b	.L22
.L37:
	.align	2
.L36:
	.word	_ZN6CBGPal3OutEPtta
.Lfe5:
	.size	_ZN6CBGPal2InEPtta,.Lfe5-_ZN6CBGPal2InEPtta
	.align	2
	.global	_ZN6CBGPal3OutEPtta
	.type	_ZN6CBGPal3OutEPtta,function
_ZN6CBGPal3OutEPtta:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, fp, ip, lr, pc}
	sub	fp, ip, #4
	and	ip, r3, #255	@  delta_per_call
	mov	r3, ip, asl #24	@  delta_per_call
	mov	r2, r2, asl #16
	movs	lr, r3, asr #24
	mov	r4, r2, asr #16	@  palette_size
	mov	r5, r0	@  this
	mov	r7, r1	@  palette
	bmi	.L51
	ldrb	r3, [r0, #0]	@  <variable>.m_Value
	rsb	r3, ip, r3	@  delta_per_call
	and	r2, r3, #255
	cmp	r2, lr
	strb	r3, [r0, #0]	@  <variable>.m_Value
	movlt	r0, #1	@  this
	blt	.L38
	mov	r6, r4, asl #16	@  palette_size
	mov	r4, #0	@  Idx
	cmp	r4, r6, lsr #16	@  Idx
	bcs	.L50
	mov	r0, r4	@  Idx,  Idx
	mov	r8, #83886080
.L48:
	mov	lr, r0, lsr #15	@  Idx
	ldrsh	r1, [lr, r7]	@  Color, * palette
	mov	r2, r1, asl #16	@  Color
	ldrb	ip, [r5, #0]	@ zero_extendqisi2	@  r,  <variable>.m_Value
	mov	r3, r2, lsr #18
	and	r3, r3, #248	@  g
	mov	r2, r2, lsr #23
	add	r0, r4, #1	@  Idx
	cmp	r3, ip	@  g,  r
	movcs	r3, ip	@  g,  r
	and	r2, r2, #248	@  b
	mov	r0, r0, asl #16
	cmp	r2, ip	@  b,  r
	movcs	r2, ip	@  b,  r
	mov	r3, r3, lsr #3	@  g
	and	r1, r1, #31	@  Color
	mov	r4, r0, asr #16	@  Idx
	mov	r1, r1, asl #3	@  r
	mov	r2, r2, lsr #3	@  b
	mov	r3, r3, asl #5
	cmp	r1, ip	@  r,  r
	movcs	r1, ip	@  r,  r
	mov	r0, r4, asl #16	@  Idx,  Idx
	add	r3, r3, r2, asl #10
	add	r3, r3, r1, lsr #3	@  r
	cmp	r0, r6	@  Idx
	strh	r3, [lr, r8]	@ movhi 
	bcc	.L48
.L50:
	mov	r0, #0	@  this
.L38:
	ldmea	fp, {r4, r5, r6, r7, r8, fp, sp, lr}
	bx	lr
.L51:
	rsb	r3, lr, #0
	mov	r2, r4, asl #16	@  palette_size
	mov	r3, r3, asl #24
	mov	r2, r2, lsr #16
	mov	r3, r3, asr #24
	bl	_ZN6CBGPal2InEPtta
	and	r0, r0, #255	@  this,  this
	b	.L38
.Lfe6:
	.size	_ZN6CBGPal3OutEPtta,.Lfe6-_ZN6CBGPal3OutEPtta
	.align	2
	.global	_ZN6CBGPal6InvertEv
	.type	_ZN6CBGPal6InvertEv,function
_ZN6CBGPal6InvertEv:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	stmfd	sp!, {r4, lr}
	mov	lr, #0	@  Idx
	mov	r0, lr	@  Idx,  Idx
	mov	r4, #83886080
.L57:
	mov	ip, r0, lsr #15	@  Idx
	ldrh	r1, [ip, r4]	@ movhi
	mov	r2, r1, asl #16
	mov	r3, r2, lsr #21
	add	r0, lr, #1	@  Idx
	and	r3, r3, #31	@  g
	mov	r2, r2, lsr #26
	mov	r0, r0, asl #16
	and	r2, r2, #31	@  b
	eor	r3, r3, #31	@  g
	mov	lr, r0, asr #16	@  Idx
	eor	r2, r2, #31	@  b
	mov	r3, r3, asl #5
	and	r1, r1, #31	@  r
	mov	r0, lr, asl #16	@  Idx,  Idx
	add	r3, r3, r2, asl #10
	eor	r1, r1, #31	@  r
	add	r1, r1, r3
	cmp	r0, #16711680	@  Idx
	strh	r1, [ip, r4]	@ movhi 
	bls	.L57
	ldmfd	sp!, {r4, lr}
	bx	lr
.Lfe7:
	.size	_ZN6CBGPal6InvertEv,.Lfe7-_ZN6CBGPal6InvertEv
	.align	2
	.global	_ZN6CBGPal12CyclePaletteEtt
	.type	_ZN6CBGPal12CyclePaletteEtt,function
_ZN6CBGPal12CyclePaletteEtt:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	stmfd	sp!, {r4, lr}
	mov	r1, r1, asl #16
	mov	r3, r1, lsr #15
	mov	r2, r2, asl #16
	mov	r0, #83886080
	mov	lr, r2, lsr #16
	mov	ip, r1, lsr #16
	ldrh	r2, [r3, r0]	@ movhi
	cmp	ip, lr
	mov	r3, lr, asl #1
	strh	r2, [r3, r0]	@ movhi 
	mov	r1, r1, asr #16	@  i
	bcs	.L67
	mov	r4, r0
.L65:
	add	r3, ip, #1
	add	r2, r1, #1	@  i
	mov	r2, r2, asl #16
	mov	r3, r3, asl #1
	mov	r1, ip, asl #1
	ldrh	r0, [r3, r4]	@ movhi
	mov	ip, r2, lsr #16
	cmp	ip, lr
	strh	r0, [r1, r4]	@ movhi 
	mov	r1, r2, asr #16	@  i
	bcc	.L65
.L67:
	ldmfd	sp!, {r4, lr}
	bx	lr
.Lfe8:
	.size	_ZN6CBGPal12CyclePaletteEtt,.Lfe8-_ZN6CBGPal12CyclePaletteEtt
	.data
	.type	_ZZN6CBGPal18CyclePaletteColorsEttE6s_AddR,object
	.size	_ZZN6CBGPal18CyclePaletteColorsEttE6s_AddR,1
_ZZN6CBGPal18CyclePaletteColorsEttE6s_AddR:
	.byte	1
	.type	_ZZN6CBGPal18CyclePaletteColorsEttE6s_AddG,object
	.size	_ZZN6CBGPal18CyclePaletteColorsEttE6s_AddG,1
_ZZN6CBGPal18CyclePaletteColorsEttE6s_AddG:
	.byte	0
	.type	_ZZN6CBGPal18CyclePaletteColorsEttE6s_AddB,object
	.size	_ZZN6CBGPal18CyclePaletteColorsEttE6s_AddB,1
_ZZN6CBGPal18CyclePaletteColorsEttE6s_AddB:
	.byte	0
	.text
	.align	2
	.global	_ZN6CBGPal18CyclePaletteColorsEtt
	.type	_ZN6CBGPal18CyclePaletteColorsEtt,function
_ZN6CBGPal18CyclePaletteColorsEtt:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	mov	r1, r1, asl #16
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, sl, lr}
	mov	r6, r1, asr #16	@  i
	mov	ip, r6, asl #16	@  i
	mov	r8, r2, asl #16
	mov	r1, ip, lsr #16
	cmp	r1, r8, lsr #16
	mov	r7, ip
	mov	r5, r0	@  this
	bcs	.L89
	mov	r9, #0	@  b
	mov	sl, #83886080
.L87:
	mov	r1, r1, asl #1
	mov	r3, #83886080
	ldrh	r2, [r1, r3]	@ movhi
	ldrb	ip, [r5, #1]	@ zero_extendqisi2	@  r,  <variable>.m_Mode
	mov	r2, r2, asl #16
	mov	r3, r2
	mov	r1, r2, lsr #23
	mov	r3, r3, lsr #18
	and	r2, r2, #2031616
	cmp	ip, #0	@  r
	mov	r4, r2, lsr #13	@  r
	and	lr, r3, #248	@  g
	and	r0, r1, #248	@  b
	beq	.L73
	ldr	r2, .L91
	ldrb	r3, [r2, #0]	@ zero_extendqisi2	@  s_AddR
	cmp	r3, #0
	beq	.L74
	ldrh	r3, [r5, #2]	@ movhi	@  <variable>.m_ColorValCount
	add	r3, r4, r3	@  r
	mov	r3, r3, asl #16
	mov	r4, r3, asr #16	@  r
	cmp	r4, #255	@  r
	ble	.L74
	mov	r3, #0
	strb	r3, [r2, #0]	@  s_AddR
	ldr	r3, .L91+4
	mov	r2, #1
	strb	r2, [r3, #0]	@  s_AddG
	mov	r4, #255	@  r
.L74:
	ldr	r2, .L91+4
	ldrb	r3, [r2, #0]	@ zero_extendqisi2	@  s_AddG
	cmp	r3, #0
	beq	.L76
	ldrh	r3, [r5, #2]	@ movhi	@  <variable>.m_ColorValCount
	add	r3, lr, r3	@  g
	mov	r3, r3, asl #16
	mov	lr, r3, asr #16	@  g
	cmp	lr, #255	@  g
	ble	.L76
	mov	r3, #0
	strb	r3, [r2, #0]	@  s_AddG
	ldr	r3, .L91+8
	mov	r2, #1
	strb	r2, [r3, #0]	@  s_AddB
	mov	lr, #255	@  g
.L76:
	ldr	ip, .L91+8
	ldrb	r3, [ip, #0]	@ zero_extendqisi2	@  s_AddB
	cmp	r3, #0
	beq	.L80
	ldrh	r3, [r5, #2]	@ movhi	@  <variable>.m_ColorValCount
	add	r3, r0, r3	@  b
	mov	r3, r3, asl #16
	mov	r0, r3, asr #16	@  b
	cmp	r0, #255	@  b
	ble	.L80
	ldr	r3, .L91+4
	mov	r1, #0
	mov	r2, #1
	mov	r0, #255	@  b
	strb	r2, [r3, #0]	@  s_AddG
	strb	r1, [ip, #0]	@  s_AddB
	strb	r1, [r5, #1]	@  <variable>.m_Mode
.L80:
	add	r3, r6, #1	@  i
	mov	r3, r3, asl #16
	mov	r2, lr, asl #13	@  g
	mov	r6, r3, asr #16	@  i
	mov	r1, r0, asl #13	@  b
	mov	r2, r2, asr #16
	mov	ip, r6, asl #16	@  i
	mov	r1, r1, asr #16
	mov	r2, r2, asl #5
	add	r2, r2, r1, asl #10
	mov	r1, ip, lsr #16
	mov	r3, r7, lsr #15
	add	r2, r2, r4, asr #3	@  r
	cmp	r1, r8, lsr #16
	mov	r7, ip
	strh	r2, [r3, sl]	@ movhi 
	bcc	.L87
.L89:
	ldmfd	sp!, {r4, r5, r6, r7, r8, r9, sl, lr}
	bx	lr
.L73:
	ldr	r1, .L91
	ldrb	r3, [r1, #0]	@ zero_extendqisi2	@  s_AddR
	cmp	r3, #0
	beq	.L81
	ldrh	r3, [r5, #2]	@ movhi	@  <variable>.m_ColorValCount
	rsb	r3, r3, r4	@  r
	mov	r3, r3, asl #16
	mov	r4, r3, asr #16	@  r
	cmp	r4, #0	@  r
	ldrle	r3, .L91+8
	movle	r2, #1
	strleb	r2, [r3, #0]	@  s_AddB
	strleb	ip, [r1, #0]	@  r,  s_AddR
	movle	r4, ip	@  r,  r
.L81:
	ldr	ip, .L91+4
	ldrb	r3, [ip, #0]	@ zero_extendqisi2	@  s_AddG
	cmp	r3, #0
	beq	.L83
	ldrh	r3, [r5, #2]	@ movhi	@  <variable>.m_ColorValCount
	rsb	r3, r3, lr	@  g
	mov	r3, r3, asl #16
	mov	lr, r3, asr #16	@  g
	cmp	lr, #0	@  g
	ble	.L90
.L83:
	ldr	r1, .L91+8
	ldrb	r3, [r1, #0]	@ zero_extendqisi2	@  s_AddB
	cmp	r3, #0
	beq	.L80
	ldrh	r3, [r5, #2]	@ movhi	@  <variable>.m_ColorValCount
	rsb	r3, r3, r0	@  b
	mov	r3, r3, asl #16
	mov	r0, r3, asr #16	@  b
	cmp	r0, #0	@  b
	bgt	.L80
	ldr	r3, .L91
	mov	r2, #1
	strb	r9, [r1, #0]	@  b,  s_AddB
	strb	r2, [r3, #0]	@  s_AddR
	strb	r2, [r5, #1]	@  <variable>.m_Mode
	mov	r0, r9	@  b,  b
	b	.L80
.L90:
	ldr	r3, .L91
	mov	r1, #0	@  g
	mov	r2, #1
	strb	r2, [r3, #0]	@  s_AddR
	strb	r1, [ip, #0]	@  g,  s_AddG
	mov	lr, r1	@  g,  g
	b	.L83
.L92:
	.align	2
.L91:
	.word	_ZZN6CBGPal18CyclePaletteColorsEttE6s_AddR
	.word	_ZZN6CBGPal18CyclePaletteColorsEttE6s_AddG
	.word	_ZZN6CBGPal18CyclePaletteColorsEttE6s_AddB
.Lfe9:
	.size	_ZN6CBGPal18CyclePaletteColorsEtt,.Lfe9-_ZN6CBGPal18CyclePaletteColorsEtt
	.ident	"GCC: (GNU) 3.2.2"
