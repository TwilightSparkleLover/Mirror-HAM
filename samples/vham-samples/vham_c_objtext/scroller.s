	.file	"scroller.cpp"
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
	.global	_ZN13CBaseScroller11SetCharDescE9TCharDesc
	.type	_ZN13CBaseScroller11SetCharDescE9TCharDesc,function
_ZN13CBaseScroller11SetCharDescE9TCharDesc:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	stmfd	sp!, {r4, lr}
	mov	r4, r1, lsr #8	@  CharDesc
	and	r3, r4, #255
	and	ip, r1, #255	@  CharDesc
	mul	lr, r3, ip
	mov	r2, #276
	mov	r3, r1, lsr #16	@  CharDesc
	add	r2, r2, #2
	strh	lr, [r0, r2]	@ movhi 	@  <variable>.m_CharWidthHeight
	strb	r3, [r0, #10]	@  <variable>.m_CharDesc.Space
	strb	r1, [r0, #8]	@  CharDesc,  <variable>.m_CharDesc.Width
	strb	r4, [r0, #9]	@  <variable>.m_CharDesc.Height
	ldmfd	sp!, {r4, lr}
	bx	lr
.Lfe1:
	.size	_ZN13CBaseScroller11SetCharDescE9TCharDesc,.Lfe1-_ZN13CBaseScroller11SetCharDescE9TCharDesc
	.align	2
	.global	_ZN13CBaseScroller17SetBasePositionXYEhh
	.type	_ZN13CBaseScroller17SetBasePositionXYEhh,function
_ZN13CBaseScroller17SetBasePositionXYEhh:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	and	r1, r1, #255	@  BasePosX,  BasePosX
	and	r4, r2, #255	@  BasePosY
	mov	r5, r0	@  this
	sub	fp, ip, #4
	ldr	r3, .L3
	mov	lr, pc
	bx	r3
	mov	r0, r5	@  this
	mov	r1, r4	@  BasePosY
	ldr	r3, .L3+4
	mov	lr, pc
	bx	r3
	ldmea	fp, {r4, r5, fp, sp, lr}
	bx	lr
.L4:
	.align	2
.L3:
	.word	_ZN13CBaseScroller16SetBasePositionXEh
	.word	_ZN13CBaseScroller16SetBasePositionYEh
.Lfe2:
	.size	_ZN13CBaseScroller17SetBasePositionXYEhh,.Lfe2-_ZN13CBaseScroller17SetBasePositionXYEhh
	.align	2
	.global	_ZN13CBaseScroller16SetBasePositionXEh
	.type	_ZN13CBaseScroller16SetBasePositionXEh,function
_ZN13CBaseScroller16SetBasePositionXEh:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	@ lr needed for prologue
	strb	r1, [r0, #4]	@  <variable>.m_BasePositionX
	bx	lr
.Lfe3:
	.size	_ZN13CBaseScroller16SetBasePositionXEh,.Lfe3-_ZN13CBaseScroller16SetBasePositionXEh
	.align	2
	.global	_ZN13CBaseScroller16SetBasePositionYEh
	.type	_ZN13CBaseScroller16SetBasePositionYEh,function
_ZN13CBaseScroller16SetBasePositionYEh:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	@ lr needed for prologue
	strb	r1, [r0, #5]	@  <variable>.m_BasePositionY
	bx	lr
.Lfe4:
	.size	_ZN13CBaseScroller16SetBasePositionYEh,.Lfe4-_ZN13CBaseScroller16SetBasePositionYEh
	.align	2
	.global	_ZN13CBaseScroller12SetCharOrderEPc
	.type	_ZN13CBaseScroller12SetCharOrderEPc,function
_ZN13CBaseScroller12SetCharOrderEPc:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	@ lr needed for prologue
	str	r1, [r0, #12]	@  pCharOrder,  <variable>.m_pCharOrder
	bx	lr
.Lfe5:
	.size	_ZN13CBaseScroller12SetCharOrderEPc,.Lfe5-_ZN13CBaseScroller12SetCharOrderEPc
	.align	2
	.global	_ZN13CBaseScroller7SetTextEPc
	.type	_ZN13CBaseScroller7SetTextEPc,function
_ZN13CBaseScroller7SetTextEPc:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	@ lr needed for prologue
	str	r1, [r0, #16]	@  pText,  <variable>.m_pText
	bx	lr
.Lfe6:
	.size	_ZN13CBaseScroller7SetTextEPc,.Lfe6-_ZN13CBaseScroller7SetTextEPc
	.align	2
	.global	_ZN13CBaseScroller12SetRawSourceEPh
	.type	_ZN13CBaseScroller12SetRawSourceEPh,function
_ZN13CBaseScroller12SetRawSourceEPh:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	@ lr needed for prologue
	str	r1, [r0, #0]	@  pRawSource,  <variable>.m_pRawSource
	bx	lr
.Lfe7:
	.size	_ZN13CBaseScroller12SetRawSourceEPh,.Lfe7-_ZN13CBaseScroller12SetRawSourceEPh
	.align	2
	.global	_ZN13CBaseScroller11InitCharSetE11TScrollDesc
	.type	_ZN13CBaseScroller11InitCharSetE11TScrollDesc,function
_ZN13CBaseScroller11InitCharSetE11TScrollDesc:
	@ Function supports interworking.
	@ args = 20, pretend = 12, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	mov	ip, sp
	sub	sp, sp, #12
	stmfd	sp!, {r4, fp, ip, lr, pc}
	sub	fp, ip, #16
	add	ip, fp, #4
	stmia	ip, {r1, r2, r3}
	mov	r3, #276
	mov	ip, #0	@ movhi
	ldrb	r2, [fp, #9]	@ zero_extendqisi2	@  ScrollDesc.BasePositionY
	mov	r4, r0	@  this
	ldrb	r1, [fp, #8]	@ zero_extendqisi2	@  ScrollDesc.BasePositionX
	strh	ip, [r0, r3]	@ movhi 	@  <variable>.m_ActCharPos
	bl	_ZN13CBaseScroller17SetBasePositionXYEhh
	ldr	r1, [fp, #16]	@  ScrollDesc.pCharOrder
	mov	r0, r4	@  this
	bl	_ZN13CBaseScroller12SetCharOrderEPc
	ldr	r1, [fp, #12]
	mov	r0, r4	@  this
	bl	_ZN13CBaseScroller11SetCharDescE9TCharDesc
	ldr	r1, [fp, #20]	@  ScrollDesc.pText
	mov	r0, r4	@  this
	bl	_ZN13CBaseScroller7SetTextEPc
	ldr	r1, [fp, #4]	@  ScrollDesc.pRawSource
	mov	r0, r4	@  this
	@ Sibcall epilogue
	ldmea	fp, {r4, fp, sp, lr}
	b	_ZN13CBaseScroller12SetRawSourceEPh
.Lfe8:
	.size	_ZN13CBaseScroller11InitCharSetE11TScrollDesc,.Lfe8-_ZN13CBaseScroller11InitCharSetE11TScrollDesc
	.global	__divsi3
	.align	2
	.global	_ZN13CBaseScroller13CreateSpritesEhh
	.type	_ZN13CBaseScroller13CreateSpritesEhh,function
_ZN13CBaseScroller13CreateSpritesEhh:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, ip, lr, pc}
	mov	r8, #0	@  i
	sub	fp, ip, #4
	sub	sp, sp, #36
	mov	r4, r0	@  this
	and	r9, r1, #255	@  ObjShape,  ObjShape
	and	sl, r2, #255	@  ObjSize,  ObjSize
	mov	r6, r8	@  i
.L12:
	ldrb	r5, [r4, #8]	@ zero_extendqisi2	@  ObjShape,  <variable>.m_CharDesc.Width
	mov	r0, #240
	mov	r1, r5	@  ObjShape
	ldr	r3, .L25
	mov	lr, pc
	bx	r3
	mov	r7, r8, asl #16	@  i
	add	r0, r0, #2	@  this
	mov	ip, r7, lsr #16
	cmp	ip, r0
	bge	.L24
	ldrb	r3, [r4, #4]	@ zero_extendqisi2	@  <variable>.m_BasePositionX
	mla	r1, r8, r5, r3	@  i,  ObjShape
	add	r2, r4, ip, asl #3	@  this
	add	r5, r2, #20
	strh	r1, [r5, #2]	@ movhi 	@  <variable>.X
	ldrb	r3, [r4, #5]	@ zero_extendqisi2	@  <variable>.m_BasePositionY
	strh	r3, [r2, #24]	@ movhi 	@  <variable>.Y
	ldr	r0, [r4, #12]	@  pC,  <variable>.m_pCharOrder
	ldrb	r1, [r0, #0]	@ * pC
	ldr	r3, [r4, #16]	@  <variable>.m_pText
	cmp	r1, #0
	ldrb	ip, [r3, ip]	@ zero_extendqisi2	@  Char
	mov	lr, #0	@  i
	beq	.L17
.L20:
	and	r3, r1, #255
	add	r2, lr, #1	@  i
	cmp	r3, ip	@  Char
	mov	r2, r2, asl #16
	add	r0, r0, #1	@  pC,  pC
	beq	.L17
	ldrb	r1, [r0, #0]	@ * pC
	cmp	r1, #0
	mov	lr, r2, asr #16	@  i
	bne	.L20
.L17:
	mov	r3, #276
	add	r3, r3, #2
	ldrh	ip, [r4, r3]	@  <variable>.m_CharWidthHeight
	ldr	r1, [r4, #0]	@  <variable>.m_pRawSource
	mov	r3, #1
	mov	r2, lr, asl #16	@  i
	str	r3, [sp, #8]
	stmia	sp, {r3, r6}	@ phole stm
	str	r6, [sp, #12]
	str	r6, [sp, #16]
	str	r6, [sp, #20]
	str	r6, [sp, #24]
	mov	r2, r2, lsr #16
	mla	r0, r2, ip, r1	@  this
	add	r2, r4, r7, lsr #13	@  this
	ldrh	r3, [r2, #22]	@  <variable>.X
	str	r3, [sp, #28]
	ldrh	lr, [r2, #24]	@  <variable>.Y
	mov	r3, r6
	mov	r1, r9	@  ObjShape
	mov	r2, sl	@  ObjSize
	str	lr, [sp, #32]
	ldr	ip, .L25+4
	mov	lr, pc
	bx	ip
	add	r3, r8, #1	@  i
	mov	r3, r3, asl #16
	strb	r0, [r5, #0]	@  this,  <variable>.ObjNo
	mov	r8, r3, asr #16	@  i
	b	.L12
.L24:
	mov	r2, #276
	ldrh	r3, [r4, r2]	@ movhi	@  <variable>.m_ActCharPos
	add	r3, r3, r8	@  i
	strh	r3, [r4, r2]	@ movhi 	@  <variable>.m_ActCharPos
	ldmea	fp, {r4, r5, r6, r7, r8, r9, sl, fp, sp, lr}
	bx	lr
.L26:
	.align	2
.L25:
	.word	__divsi3
	.word	ham_CreateObj
.Lfe9:
	.size	_ZN13CBaseScroller13CreateSpritesEhh,.Lfe9-_ZN13CBaseScroller13CreateSpritesEhh
	.align	2
	.global	_ZN13CBaseScroller13DeleteSpritesEv
	.type	_ZN13CBaseScroller13DeleteSpritesEv,function
_ZN13CBaseScroller13DeleteSpritesEv:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	ldr	r7, .L34
	sub	fp, ip, #4
	mov	r6, r0	@  this
	mov	r5, #0	@  i
.L28:
	ldrb	r1, [r6, #8]	@ zero_extendqisi2	@  <variable>.m_CharDesc.Width
	mov	r0, #240
	mov	lr, pc
	bx	r7
	mov	r4, r5, asl #16	@  i
	mov	r4, r4, lsr #16
	add	r0, r0, #2	@  this
	cmp	r4, r0
	add	r3, r6, r4, asl #3	@  this
	bge	.L33
	ldrb	r0, [r3, #20]	@ zero_extendqisi2	@  this,  <variable>.ObjNo
	ldr	r2, .L34+4
	mov	lr, pc
	bx	r2
	add	r3, r5, #1	@  i
	mov	r3, r3, asl #16
	mov	r5, r3, asr #16	@  i
	b	.L28
.L33:
	ldmea	fp, {r4, r5, r6, r7, fp, sp, lr}
	bx	lr
.L35:
	.align	2
.L34:
	.word	__divsi3
	.word	ham_DeleteObj
.Lfe10:
	.size	_ZN13CBaseScroller13DeleteSpritesEv,.Lfe10-_ZN13CBaseScroller13DeleteSpritesEv
	.align	2
	.global	_ZN13CBaseScroller17ScrollRightToLeftEs
	.type	_ZN13CBaseScroller17ScrollRightToLeftEs,function
_ZN13CBaseScroller17ScrollRightToLeftEs:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, ip, lr, pc}
	mov	r1, r1, asl #16
	sub	fp, ip, #4
	mov	r5, r0	@  this
	mov	r9, r1, asr #16	@  Y
	mov	sl, #0	@  i
.L37:
	ldr	r3, .L52
	ldrb	r1, [r5, #8]	@ zero_extendqisi2	@  <variable>.m_CharDesc.Width
	mov	r0, #240
	mov	lr, pc
	bx	r3
	mov	r6, sl, asl #16	@  i
	add	r0, r0, #2	@  this
	mov	r3, r6, lsr #16
	cmp	r3, r0
	bge	.L51
	add	r2, r5, r3, asl #3	@  this
	add	r2, r2, #20
	ldrh	r0, [r2, #2]	@ movhi	@  <variable>.X
	sub	r1, r0, #1
	strh	r1, [r2, #2]	@ movhi 	@  <variable>.X
	ldrb	r3, [r5, #8]	@ zero_extendqisi2	@  <variable>.m_CharDesc.Width
	mov	r0, r0, asl #16
	rsb	r3, r3, #0
	cmp	r3, r0, asr #16
	ble	.L41
	ldr	ip, [r5, #12]	@  pC,  <variable>.m_pCharOrder
	mov	r3, #276
	ldrb	r0, [ip, #0]	@ * pC
	ldrh	r1, [r5, r3]	@  <variable>.m_ActCharPos
	ldr	r2, [r5, #16]	@  <variable>.m_pText
	cmp	r0, #0
	ldrb	lr, [r2, r1]	@ zero_extendqisi2	@  Char
	mov	r1, #0	@  i
	beq	.L43
.L46:
	and	r3, r0, #255
	add	r2, r1, #1	@  i
	cmp	r3, lr	@  Char
	mov	r2, r2, asl #16
	add	ip, ip, #1	@  pC,  pC
	beq	.L43
	ldrb	r0, [ip, #0]	@ * pC
	cmp	r0, #0
	mov	r1, r2, asr #16	@  i
	bne	.L46
.L43:
	mov	r7, #276
	add	r2, r7, #2
	ldrh	r0, [r5, r2]	@  <variable>.m_CharWidthHeight
	mov	r3, r1, asl #16	@  i
	ldr	r2, [r5, #0]	@  <variable>.m_pRawSource
	add	ip, r5, r6, lsr #13	@  this
	mov	r3, r3, lsr #16
	mla	r1, r3, r0, r2
	ldrb	r0, [ip, #20]	@ zero_extendqisi2	@  this,  <variable>.ObjNo
	ldr	r3, .L52+4
	add	r8, ip, #20
	mov	lr, pc
	bx	r3
	ldrh	r4, [r5, r7]	@ movhi	@  <variable>.m_ActCharPos
	add	r3, r4, #1
	strh	r3, [r5, r7]	@ movhi 	@  <variable>.m_ActCharPos
	ldr	r0, [r5, #16]	@  this,  <variable>.m_pText
	ldr	r3, .L52+8
	mov	lr, pc
	bx	r3
	cmp	r4, r0	@  this
	movhi	r3, #0	@ movhi
	strhih	r3, [r5, r7]	@ movhi 	@  <variable>.m_ActCharPos
	ldrb	r2, [r5, #8]	@ zero_extendqisi2	@  <variable>.m_CharDesc.Width
	ldrb	r3, [r5, #4]	@ zero_extendqisi2	@  <variable>.m_BasePositionX
	add	r3, r3, r2
	strh	r3, [r8, #2]	@ movhi 	@  <variable>.X
.L41:
	add	r3, r5, r6, lsr #13	@  this
	mov	r2, r9, asl #16	@  Y
	ldrh	r1, [r3, #22]	@  <variable>.X
	ldrb	r0, [r3, #20]	@ zero_extendqisi2	@  this,  <variable>.ObjNo
	mov	r2, r2, lsr #16
	ldr	ip, .L52+12
	mov	lr, pc
	bx	ip
	add	r3, sl, #1	@  i
	mov	r3, r3, asl #16
	mov	sl, r3, asr #16	@  i
	b	.L37
.L51:
	ldmea	fp, {r4, r5, r6, r7, r8, r9, sl, fp, sp, lr}
	bx	lr
.L53:
	.align	2
.L52:
	.word	__divsi3
	.word	ham_UpdateObjGfx
	.word	strlen
	.word	ham_SetObjXY
.Lfe11:
	.size	_ZN13CBaseScroller17ScrollRightToLeftEs,.Lfe11-_ZN13CBaseScroller17ScrollRightToLeftEs
	.data
	.align	1
	.type	_ZZN13CBaseScroller21ScrollRightToLeftSineEPsthsE9s_Counter,object
	.size	_ZZN13CBaseScroller21ScrollRightToLeftSineEPsthsE9s_Counter,2
_ZZN13CBaseScroller21ScrollRightToLeftSineEPsthsE9s_Counter:
	.short	0
	.text
	.align	2
	.global	_ZN13CBaseScroller21ScrollRightToLeftSineEPsths
	.type	_ZN13CBaseScroller21ScrollRightToLeftSineEPsths,function
_ZN13CBaseScroller21ScrollRightToLeftSineEPsths:
	@ Function supports interworking.
	@ args = 4, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, ip, lr, pc}
	ldr	r4, .L71
	sub	fp, ip, #4
	sub	sp, sp, #8
	and	r3, r3, #255
	ldrh	lr, [r4, #0]	@ movhi	@  s_Counter
	add	lr, lr, #1
	mov	ip, lr, asl #16
	cmp	ip, r2, asl #16
	ldrsh	r9, [fp, #4]	@  Y,  Y
	movhi	r2, #0	@ movhi
	mov	r5, r0	@  this
	mov	sl, #0	@  i
	strh	lr, [r4, #0]	@ movhi 	@  s_Counter
	str	r1, [fp, #-44]	@  pSineTable
	str	r3, [fp, #-48]	@  MulFactor
	strhih	r2, [r4, #0]	@ movhi 	@  s_Counter
.L56:
	ldr	r3, .L71+4
	ldrb	r1, [r5, #8]	@ zero_extendqisi2	@  pSineTable,  <variable>.m_CharDesc.Width
	mov	r0, #240
	mov	lr, pc
	bx	r3
	mov	r6, sl, asl #16	@  i
	add	r0, r0, #2	@  this
	mov	r3, r6, lsr #16
	cmp	r3, r0
	bge	.L70
	add	r2, r5, r3, asl #3	@  this
	add	r2, r2, #20
	ldrh	r0, [r2, #2]	@ movhi	@  <variable>.X
	sub	r1, r0, #1
	strh	r1, [r2, #2]	@ movhi 	@  <variable>.X
	ldrb	r3, [r5, #8]	@ zero_extendqisi2	@  <variable>.m_CharDesc.Width
	mov	r0, r0, asl #16
	rsb	r3, r3, #0
	cmp	r3, r0, asr #16
	ble	.L60
	ldr	ip, [r5, #12]	@  pC,  <variable>.m_pCharOrder
	mov	r3, #276
	ldrb	r0, [ip, #0]	@ * pC
	ldrh	r1, [r5, r3]	@  <variable>.m_ActCharPos
	ldr	r2, [r5, #16]	@  <variable>.m_pText
	cmp	r0, #0
	ldrb	lr, [r2, r1]	@ zero_extendqisi2	@  Char
	mov	r1, #0	@  i
	beq	.L62
.L65:
	and	r3, r0, #255
	add	r2, r1, #1	@  i
	cmp	r3, lr	@  Char
	mov	r2, r2, asl #16
	add	ip, ip, #1	@  pC,  pC
	beq	.L62
	ldrb	r0, [ip, #0]	@ * pC
	cmp	r0, #0
	mov	r1, r2, asr #16	@  i
	bne	.L65
.L62:
	mov	r7, #276
	add	r2, r7, #2
	ldrh	r0, [r5, r2]	@  <variable>.m_CharWidthHeight
	mov	r3, r1, asl #16	@  i
	ldr	r2, [r5, #0]	@  <variable>.m_pRawSource
	add	ip, r5, r6, lsr #13	@  this
	mov	r3, r3, lsr #16
	mla	r1, r3, r0, r2	@  pSineTable
	ldrb	r0, [ip, #20]	@ zero_extendqisi2	@  this,  <variable>.ObjNo
	ldr	r3, .L71+8
	add	r8, ip, #20
	mov	lr, pc
	bx	r3
	ldrh	r4, [r5, r7]	@ movhi	@  <variable>.m_ActCharPos
	add	r3, r4, #1
	strh	r3, [r5, r7]	@ movhi 	@  <variable>.m_ActCharPos
	ldr	r0, [r5, #16]	@  this,  <variable>.m_pText
	ldr	r3, .L71+12
	mov	lr, pc
	bx	r3
	cmp	r4, r0	@  this
	movhi	r3, #0	@ movhi
	strhih	r3, [r5, r7]	@ movhi 	@  <variable>.m_ActCharPos
	ldrb	r2, [r5, #8]	@ zero_extendqisi2	@  <variable>.m_CharDesc.Width
	ldrb	r3, [r5, #4]	@ zero_extendqisi2	@  <variable>.m_BasePositionX
	add	r3, r3, r2
	strh	r3, [r8, #2]	@ movhi 	@  <variable>.X
.L60:
	ldr	r3, .L71
	ldrh	r2, [r3, #0]	@  s_Counter
	ldr	r3, [fp, #-48]	@  MulFactor
	mov	lr, r6, lsr #16
	mla	r3, lr, r3, r2
	ldr	r2, [fp, #-44]	@  pSineTable
	mov	r3, r3, asl #1
	ldrh	ip, [r3, r2]	@ movhi
	add	ip, r9, ip	@  Y
	add	lr, r5, lr, asl #3	@  this
	mov	r2, ip, asl #16
	strh	ip, [lr, #24]	@ movhi 	@  <variable>.Y
	ldrh	r1, [lr, #22]	@  pSineTable,  <variable>.X
	ldrb	r0, [lr, #20]	@ zero_extendqisi2	@  this,  <variable>.ObjNo
	mov	r2, r2, lsr #16
	ldr	ip, .L71+16
	mov	lr, pc
	bx	ip
	add	r3, sl, #1	@  i
	mov	r3, r3, asl #16
	mov	sl, r3, asr #16	@  i
	b	.L56
.L70:
	ldmea	fp, {r4, r5, r6, r7, r8, r9, sl, fp, sp, lr}
	bx	lr
.L72:
	.align	2
.L71:
	.word	_ZZN13CBaseScroller21ScrollRightToLeftSineEPsthsE9s_Counter
	.word	__divsi3
	.word	ham_UpdateObjGfx
	.word	strlen
	.word	ham_SetObjXY
.Lfe12:
	.size	_ZN13CBaseScroller21ScrollRightToLeftSineEPsths,.Lfe12-_ZN13CBaseScroller21ScrollRightToLeftSineEPsths
	.ident	"GCC: (GNU) 3.2.2"
