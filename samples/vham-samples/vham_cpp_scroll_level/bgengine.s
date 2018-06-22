	.file	"bgengine.cpp"
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
	.global	_ZN9CBGEngine14InitBackGroundEh11TBackGround
	.type	_ZN9CBGEngine14InitBackGroundEh11TBackGround,function
_ZN9CBGEngine14InitBackGroundEh11TBackGround:
	@ Function supports interworking.
	@ args = 32, pretend = 8, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	mov	ip, sp
	sub	sp, sp, #8
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, ip, lr, pc}
	sub	fp, ip, #12
	add	lr, fp, #4
	sub	sp, sp, #16
	mov	r5, r0	@  this
	stmia	lr, {r2, r3}
	mov	r8, r1	@  bgno
	ldmia	lr!, {r0, r1, r2, r3}
	mov	r7, #0	@  bgno
	add	ip, r5, #12	@  this
	strh	r7, [r5, #8]	@ movhi 	@  bgno,  <variable>.m_StartTileX
	stmia	ip!, {r0, r1, r2, r3}
	ldmia	lr, {r0, r1, r2, r3}
	ldr	r4, [fp, #20]	@  this,  bg.pPalette
	ldrh	r6, [fp, #24]	@  bgno,  bg.PaletteSize
	stmia	ip, {r0, r1, r2, r3}
	mov	r3, #8	@  value
	mov	sl, #1	@  ScrollDelay
	and	r8, r8, #255	@  bgno,  bgno
	strb	r3, [r5, #48]	@  value,  <variable>.m_AnimateDelay
	mov	r2, #30
	add	r3, r3, #92	@  value,  value
	str	r2, [r5, #4]	@  <variable>.m_ScrollPosXInTiles
	strb	r3, [r5, #50]	@  value,  <variable>.m_ActScrollDelay
	mov	r0, r4	@  this
	mov	r1, r6	@  bgno
	strb	r8, [r5, #10]	@  bgno,  <variable>.m_BGNo
	str	r7, [r5, #0]	@  bgno,  <variable>.m_ScrollPosX
	strb	sl, [r5, #49]	@  ScrollDelay,  <variable>.m_ChoosenScrollDelay
	ldr	r3, .L5
	mov	lr, pc
	bx	r3
	ldrh	r1, [fp, #16]	@  bgno,  bg.TilesSize
	mov	r2, sl	@  ScrollDelay
	mov	r3, sl	@  ScrollDelay
	ldr	ip, .L5+4
	ldr	r0, [fp, #12]	@  bg.pTiles
	mov	lr, pc
	bx	ip
	ldr	r9, .L5+8
	add	r4, r8, r8, asl #2	@  bgno,  bgno
	mov	r4, r4, asl #2
	add	r2, r4, r9
	mov	r6, r0	@  this
	mov	r1, r7	@  bgno
	str	r6, [r2, #4]	@  this,  <variable>.ti
	mov	r0, sl	@  ScrollDelay
	ldr	r3, .L5+12
	mov	lr, pc
	bx	r3
	mov	lr, #20
	mov	r6, r0	@  this
	mov	ip, #32
	str	lr, [sp, #8]
	ldrh	r1, [fp, #6]	@  bgno,  bg.MapWidth
	ldrh	r2, [fp, #8]	@  ScrollDelay,  bg.MapHeight
	mov	r3, r7	@  bgno
	str	ip, [sp, #4]
	ldr	r0, [fp, #28]	@  bg.pMap
	str	r6, [r4, r9]	@  this,  <variable>.mi
	str	r7, [sp, #0]	@  bgno
	str	r7, [sp, #12]	@  bgno
	ldr	ip, .L5+16
	mov	lr, pc
	bx	ip
	mov	r1, r8	@  bgno
	mov	r2, r7	@  bgno
	ldr	ip, .L5+20
	str	r0, [r5, #44]	@  this,  <variable>.m_MapFragment
	mov	r3, r7	@  bgno
	mov	lr, pc
	bx	ip
	mov	r0, r5	@  this
	ldr	r3, .L5+24
	mov	lr, pc
	bx	r3
	mov	r0, r5	@  this
	ldr	r3, .L5+28
	mov	lr, pc
	bx	r3
	add	r2, r8, sl	@  ScrollDelay,  bgno
	mov	r0, r8	@  bgno
	mov	r1, sl	@  ScrollDelay
	mov	r3, r7	@  bgno
	ldr	ip, .L5+32
	mov	lr, pc
	bx	ip
	ldmea	fp, {r4, r5, r6, r7, r8, r9, sl, fp, sp, lr}
	bx	lr
.L6:
	.align	2
.L5:
	.word	ham_LoadBGPal
	.word	ham_InitTileSet
	.word	ham_bg
	.word	ham_InitMapEmptySet
	.word	ham_InitMapFragment
	.word	ham_InsertMapFragment
	.word	_ZN9CBGEngine11ScrollRightEv
	.word	_ZN9CBGEngine10ScrollLeftEv
	.word	ham_InitBg
.Lfe1:
	.size	_ZN9CBGEngine14InitBackGroundEh11TBackGround,.Lfe1-_ZN9CBGEngine14InitBackGroundEh11TBackGround
	.align	2
	.global	_ZN9CBGEngine6DeInitEv
	.type	_ZN9CBGEngine6DeInitEv,function
_ZN9CBGEngine6DeInitEv:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	ldr	r3, .L9
	sub	fp, ip, #4
	ldrb	r0, [r0, #10]	@ zero_extendqisi2	@  <anonymous>,  <variable>.m_BGNo
	mov	lr, pc
	bx	r3
	ldmea	fp, {fp, sp, lr}
	bx	lr
.L10:
	.align	2
.L9:
	.word	ham_DeInitBg
.Lfe2:
	.size	_ZN9CBGEngine6DeInitEv,.Lfe2-_ZN9CBGEngine6DeInitEv
	.data
	.type	_ZZN9CBGEngine7AnimateEvE8actTiles,object
	.size	_ZZN9CBGEngine7AnimateEvE8actTiles,1
_ZZN9CBGEngine7AnimateEvE8actTiles:
	.byte	0
	.type	_ZZN9CBGEngine7AnimateEvE14s_AnimateDelay,object
	.size	_ZZN9CBGEngine7AnimateEvE14s_AnimateDelay,1
_ZZN9CBGEngine7AnimateEvE14s_AnimateDelay:
	.byte	0
	.text
	.align	2
	.global	_ZN9CBGEngine7AnimateEv
	.type	_ZN9CBGEngine7AnimateEv,function
_ZN9CBGEngine7AnimateEv:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	ldr	r6, .L16
	ldrb	r3, [r6, #0]	@  s_AnimateDelay
	add	r3, r3, #1
	strb	r3, [r6, #0]	@  s_AnimateDelay
	ldrb	r2, [r0, #48]	@ zero_extendqisi2	@  <variable>.m_AnimateDelay
	and	r3, r3, #255
	cmp	r3, r2
	sub	fp, ip, #4
	ldr	r7, .L16+4
	ldr	r5, .L16+8
	mov	r4, r0	@  this
	bls	.L11
	ldrb	r3, [r5, #0]	@  actTiles
	add	r3, r3, #1
	and	r2, r3, #255
	cmp	r2, #3
	strb	r3, [r5, #0]	@  actTiles
	movhi	r3, #0
	strhib	r3, [r5, #0]	@  actTiles
	ldrb	r3, [r4, #10]	@ zero_extendqisi2	@  <anonymous>,  <variable>.m_BGNo
	add	r3, r3, r3, asl #2	@  <anonymous>,  <anonymous>
	add	r3, r7, r3, asl #2
	ldr	r0, [r3, #4]	@  this,  <variable>.ti
	ldr	r2, .L16+12
	mov	lr, pc
	bx	r2
	ldrb	r3, [r5, #0]	@ zero_extendqisi2	@  actTiles
	mov	r2, #1
	add	r3, r4, r3, asl #2	@  this
	ldr	r0, [r3, #20]	@  this,  <variable>.m_BackGround.pTiles
	ldrh	r1, [r4, #24]	@  <variable>.m_BackGround.TilesSize
	mov	r3, r2
	ldr	ip, .L16+16
	ldrb	r4, [r4, #10]	@ zero_extendqisi2	@  <anonymous>,  <variable>.m_BGNo
	mov	lr, pc
	bx	ip
	add	r4, r4, r4, asl #2	@  <anonymous>,  <anonymous>
	add	r4, r7, r4, asl #2
	mov	r3, #0
	str	r0, [r4, #4]	@  this,  <variable>.ti
	strb	r3, [r6, #0]	@  s_AnimateDelay
.L11:
	ldmea	fp, {r4, r5, r6, r7, fp, sp, lr}
	bx	lr
.L17:
	.align	2
.L16:
	.word	_ZZN9CBGEngine7AnimateEvE14s_AnimateDelay
	.word	ham_bg
	.word	_ZZN9CBGEngine7AnimateEvE8actTiles
	.word	ham_DeInitTileSet
	.word	ham_InitTileSet
.Lfe3:
	.size	_ZN9CBGEngine7AnimateEv,.Lfe3-_ZN9CBGEngine7AnimateEv
	.data
	.align	1
	.type	_ZZN9CBGEngine11ScrollRightEvE16s_ScrollPosCount,object
	.size	_ZZN9CBGEngine11ScrollRightEvE16s_ScrollPosCount,2
_ZZN9CBGEngine11ScrollRightEvE16s_ScrollPosCount:
	.short	0
	.text
	.align	2
	.global	_ZN9CBGEngine11ScrollRightEv
	.type	_ZN9CBGEngine11ScrollRightEv,function
_ZN9CBGEngine11ScrollRightEv:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	sub	fp, ip, #4
	sub	sp, sp, #16
	mov	r4, r0	@  this
	ldrb	r3, [r0, #50]	@  <variable>.m_ActScrollDelay
	ldrb	r1, [r0, #49]	@ zero_extendqisi2	@  <variable>.m_ChoosenScrollDelay
	add	r3, r3, #1
	and	r2, r3, #255
	cmp	r2, r1
	mov	r5, #0
	strb	r3, [r0, #50]	@  <variable>.m_ActScrollDelay
	bcc	.L28
	ldr	r3, [r0, #4]	@  <variable>.m_ScrollPosXInTiles
	ldrh	r1, [r0, #14]	@  <anonymous>,  <variable>.m_BackGround.MapWidth
	cmp	r3, r1	@  <anonymous>
	ldr	ip, .L30
	strb	r5, [r0, #50]	@  <variable>.m_ActScrollDelay
	bcs	.L21
	ldrb	r2, [r0, #12]	@ zero_extendqisi2	@  <variable>.m_BackGround.TileWidth
	add	lr, r3, #1
	ldrh	r3, [ip, #0]	@ movhi	@  s_ScrollPosCount
	add	r0, r3, #1
	cmp	r2, r3
	strh	r0, [ip, #0]	@ movhi 	@  s_ScrollPosCount
	bls	.L29
	ldr	r3, [r4, #0]	@  <variable>.m_ScrollPosX
	add	r3, r3, #1
	str	r3, [r4, #0]	@  <variable>.m_ScrollPosX
.L21:
	ldrb	r0, [r4, #10]	@ zero_extendqisi2	@  <anonymous>,  <variable>.m_BGNo
	ldrh	r1, [r4, #0]	@  <anonymous>,  <variable>.m_ScrollPosX
	mov	r2, #0
	ldr	r3, .L30+4
	mov	lr, pc
	bx	r3
.L28:
	ldr	r0, [r4, #4]	@  <anonymous>,  <variable>.m_ScrollPosXInTiles
	ldmea	fp, {r4, r5, fp, sp, lr}
	bx	lr
.L29:
	strh	r5, [ip, #0]	@ movhi 	@  s_ScrollPosCount
	mov	r3, #1
	mov	ip, #20
	ldrh	r2, [r4, #16]	@  <variable>.m_BackGround.MapHeight
	ldr	r0, [r4, #36]	@  this,  <variable>.m_BackGround.pMap
	stmib	sp, {r3, ip}	@ phole stm
	str	r5, [sp, #0]
	str	r5, [sp, #12]
	str	lr, [r4, #4]	@  <variable>.m_ScrollPosXInTiles
	ldr	ip, .L30+8
	ldrh	r3, [r4, #4]	@  <variable>.m_ScrollPosXInTiles
	mov	lr, pc
	bx	ip
	ldrb	r2, [r4, #4]	@  <variable>.m_ScrollPosXInTiles
	ldrb	r1, [r4, #10]	@ zero_extendqisi2	@  <anonymous>,  <variable>.m_BGNo
	and	r2, r2, #63
	str	r0, [r4, #44]	@  this,  <variable>.m_MapFragment
	mov	r3, r5
	ldr	ip, .L30+12
	mov	lr, pc
	bx	ip
	b	.L21
.L31:
	.align	2
.L30:
	.word	_ZZN9CBGEngine11ScrollRightEvE16s_ScrollPosCount
	.word	ham_SetBgXY
	.word	ham_InitMapFragment
	.word	ham_InsertMapFragment
.Lfe4:
	.size	_ZN9CBGEngine11ScrollRightEv,.Lfe4-_ZN9CBGEngine11ScrollRightEv
	.data
	.align	1
	.type	_ZZN9CBGEngine10ScrollLeftEvE16s_ScrollPosCount,object
	.size	_ZZN9CBGEngine10ScrollLeftEvE16s_ScrollPosCount,2
_ZZN9CBGEngine10ScrollLeftEvE16s_ScrollPosCount:
	.short	0
	.text
	.align	2
	.global	_ZN9CBGEngine10ScrollLeftEv
	.type	_ZN9CBGEngine10ScrollLeftEv,function
_ZN9CBGEngine10ScrollLeftEv:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	sub	fp, ip, #4
	sub	sp, sp, #16
	mov	r4, r0	@  this
	ldrb	r3, [r0, #50]	@  <variable>.m_ActScrollDelay
	ldrb	r1, [r0, #49]	@ zero_extendqisi2	@  <variable>.m_ChoosenScrollDelay
	add	r3, r3, #1
	and	r2, r3, #255
	cmp	r2, r1
	mov	r5, #0
	strb	r3, [r0, #50]	@  <variable>.m_ActScrollDelay
	bcc	.L42
	ldr	r3, [r4, #4]	@  <variable>.m_ScrollPosXInTiles
	cmp	r3, #30
	ldr	r0, .L44
	strb	r5, [r4, #50]	@  <variable>.m_ActScrollDelay
	bls	.L35
	ldrb	r2, [r4, #12]	@ zero_extendqisi2	@  <variable>.m_BackGround.TileWidth
	sub	lr, r3, #1
	ldrh	r3, [r0, #0]	@ movhi	@  s_ScrollPosCount
	add	r1, r3, #1
	cmp	r2, r3
	strh	r1, [r0, #0]	@ movhi 	@  s_ScrollPosCount
	bls	.L43
	ldr	r3, [r4, #0]	@  <variable>.m_ScrollPosX
	sub	r3, r3, #1
	str	r3, [r4, #0]	@  <variable>.m_ScrollPosX
.L35:
	ldrb	r0, [r4, #10]	@ zero_extendqisi2	@  <anonymous>,  <variable>.m_BGNo
	ldrh	r1, [r4, #0]	@  <anonymous>,  <variable>.m_ScrollPosX
	mov	r2, #0
	ldr	r3, .L44+4
	mov	lr, pc
	bx	r3
.L42:
	ldr	r0, [r4, #4]	@  <anonymous>,  <variable>.m_ScrollPosXInTiles
	ldmea	fp, {r4, r5, fp, sp, lr}
	bx	lr
.L43:
	strh	r5, [r0, #0]	@ movhi 	@  s_ScrollPosCount
	mov	r3, #1
	mov	ip, #20
	ldrh	r1, [r4, #14]	@  <anonymous>,  <variable>.m_BackGround.MapWidth
	ldrh	r2, [r4, #16]	@  <variable>.m_BackGround.MapHeight
	ldr	r0, [r4, #36]	@  this,  <variable>.m_BackGround.pMap
	stmib	sp, {r3, ip}	@ phole stm
	str	lr, [r4, #4]	@  <variable>.m_ScrollPosXInTiles
	ldrh	r3, [r4, #4]	@ movhi	@  <variable>.m_ScrollPosXInTiles
	sub	r3, r3, #32
	mov	r3, r3, asl #16
	mov	r3, r3, lsr #16
	str	r5, [sp, #0]
	str	r5, [sp, #12]
	ldr	ip, .L44+8
	mov	lr, pc
	bx	ip
	ldrb	r2, [r4, #4]	@  <variable>.m_ScrollPosXInTiles
	add	r2, r2, #32
	ldrb	r1, [r4, #10]	@ zero_extendqisi2	@  <anonymous>,  <variable>.m_BGNo
	and	r2, r2, #63
	str	r0, [r4, #44]	@  this,  <variable>.m_MapFragment
	mov	r3, r5
	ldr	ip, .L44+12
	mov	lr, pc
	bx	ip
	b	.L35
.L45:
	.align	2
.L44:
	.word	_ZZN9CBGEngine10ScrollLeftEvE16s_ScrollPosCount
	.word	ham_SetBgXY
	.word	ham_InitMapFragment
	.word	ham_InsertMapFragment
.Lfe5:
	.size	_ZN9CBGEngine10ScrollLeftEv,.Lfe5-_ZN9CBGEngine10ScrollLeftEv
	.ident	"GCC: (GNU) 3.2.2"
