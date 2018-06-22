	.file	"bgtext.cpp"
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
	.global	_ZN7CBgText4InitE11TBgTextInfo
	.type	_ZN7CBgText4InitE11TBgTextInfo,function
_ZN7CBgText4InitE11TBgTextInfo:
	@ Function supports interworking.
	@ args = 28, pretend = 12, frame = 28
	@ frame_needed = 1, uses_anonymous_args = 0
	mov	ip, sp
	sub	sp, sp, #12
	stmfd	sp!, {r4, fp, ip, lr, pc}
	sub	fp, ip, #16
	add	ip, fp, #4
	sub	sp, sp, #44
	mov	r4, r0	@  this
	stmia	ip, {r1, r2, r3}
	ldmia	ip!, {r0, r1, r2, r3}
	sub	lr, fp, #44
	stmia	lr!, {r0, r1, r2, r3}
	ldmia	ip, {r0, r1, r2}
	stmia	lr, {r0, r1, r2}
	sub	ip, fp, #32
	ldmia	ip, {r0, r1, r2, r3}
	stmia	sp, {r0, r1, r2, r3}
	sub	lr, fp, #44
	ldmia	lr, {r1, r2, r3}
	mov	r0, r4	@  this
	ldr	ip, .L2
	mov	lr, pc
	bx	ip
	mov	r0, r4	@  this
	ldr	r3, .L2+4
	mov	lr, pc
	bx	r3
	ldmea	fp, {r4, fp, sp, lr}
	bx	lr
.L3:
	.align	2
.L2:
	.word	_ZN7CBgText11SetTextInfoE11TBgTextInfo
	.word	_ZN7CBgText13ApplyTextInfoEv
.Lfe1:
	.size	_ZN7CBgText4InitE11TBgTextInfo,.Lfe1-_ZN7CBgText4InitE11TBgTextInfo
	.align	2
	.global	_ZN7CBgText11SetTextInfoE11TBgTextInfo
	.type	_ZN7CBgText11SetTextInfoE11TBgTextInfo,function
_ZN7CBgText11SetTextInfoE11TBgTextInfo:
	@ Function supports interworking.
	@ args = 28, pretend = 12, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	sub	sp, sp, #12
	str	lr, [sp, #-4]!
	add	lr, sp, #4
	stmia	lr, {r1, r2, r3}
	mov	ip, r0	@  this
	ldmia	lr!, {r0, r1, r2, r3}
	stmia	ip!, {r0, r1, r2, r3}	@  this
	ldmia	lr, {r0, r1, r2}
	stmia	ip, {r0, r1, r2}	@  this
	ldr	lr, [sp], #4
	add	sp, sp, #12
	bx	lr
.Lfe2:
	.size	_ZN7CBgText11SetTextInfoE11TBgTextInfo,.Lfe2-_ZN7CBgText11SetTextInfoE11TBgTextInfo
	.align	2
	.global	_ZN7CBgText13ApplyTextInfoEv
	.type	_ZN7CBgText13ApplyTextInfoEv,function
_ZN7CBgText13ApplyTextInfoEv:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	ldrb	r2, [r0, #0]	@ zero_extendqisi2	@  <variable>.m_BgInfo.BgNo
	ldr	r3, .L9
	add	r2, r2, r2, asl #2
	add	r3, r3, r2, asl #2
	mov	r7, r0	@  this
	sub	fp, ip, #4
	ldr	r0, [r3, #4]	@  this,  <variable>.ti
	ldr	r3, .L9+4
	mov	lr, pc
	bx	r3
	ldrsh	r2, [r7, #16]	@  <variable>.m_BgInfo.PaletteIndex
	cmn	r2, #1
	beq	.L8
	ldr	r0, [r7, #12]	@  this,  <variable>.m_BgInfo.pPalette
	ldrb	r1, [r7, #16]	@ zero_extendqisi2	@  this,  <variable>.m_BgInfo.PaletteIndex
	ldr	r3, .L9+8
	mov	lr, pc
	bx	r3
	mov	r2, #0	@  ColMode
.L7:
	ldr	ip, .L9+12
	ldrh	r1, [r7, #8]	@  this,  <variable>.m_BgInfo.TileSize
	ldr	r0, [r7, #4]	@  this,  <variable>.m_BgInfo.pTileData
	mov	r3, #1
	ldrb	r5, [r7, #0]	@ zero_extendqisi2	@  <variable>.m_BgInfo.BgNo
	mov	lr, pc
	bx	ip
	ldr	r6, .L9
	add	r5, r5, r5, asl #2
	add	r5, r6, r5, asl #2
	str	r0, [r5, #4]	@  this,  <variable>.ti
	mov	r0, #0
	mov	r1, r0
	ldr	r3, .L9+16
	ldrb	r4, [r7, #0]	@ zero_extendqisi2	@  <variable>.m_BgInfo.BgNo
	mov	lr, pc
	bx	r3
	add	r4, r4, r4, asl #2
	mov	r2, r0	@  this
	mov	r4, r4, asl #2
	str	r2, [r4, r6]	@  this,  <variable>.mi
	mov	r0, r7	@  this
	ldr	r3, .L9+20
	mov	lr, pc
	bx	r3
	ldr	r3, .L9+24
	strh	r0, [r7, #28]	@ movhi 	@  this,  <variable>.m_SpaceIndex
	mov	r0, r7	@  this
	mov	lr, pc
	bx	r3
	mov	r1, #1
	ldrb	r0, [r7, #0]	@ zero_extendqisi2	@  this,  <variable>.m_BgInfo.BgNo
	mov	r2, #0
	mov	r3, r1
	ldr	ip, .L9+28
	mov	lr, pc
	bx	ip
	ldmea	fp, {r4, r5, r6, r7, fp, sp, lr}
	bx	lr
.L8:
	ldr	r0, [r7, #12]	@  this,  <variable>.m_BgInfo.pPalette
	ldr	r3, .L9+32
	mov	lr, pc
	bx	r3
	mov	r2, #1	@  ColMode
	b	.L7
.L10:
	.align	2
.L9:
	.word	ham_bg
	.word	ham_DeInitTileSet
	.word	ham_LoadBGPal16
	.word	ham_InitTileSet
	.word	ham_InitMapEmptySet
	.word	_ZN7CBgText22GetSpaceIndexFirstTimeEv
	.word	_ZN7CBgText5ClearEv
	.word	ham_InitBg
	.word	ham_LoadBGPal256
.Lfe3:
	.size	_ZN7CBgText13ApplyTextInfoEv,.Lfe3-_ZN7CBgText13ApplyTextInfoEv
	.align	2
	.global	_ZN7CBgText22GetSpaceIndexFirstTimeEv
	.type	_ZN7CBgText22GetSpaceIndexFirstTimeEv,function
_ZN7CBgText22GetSpaceIndexFirstTimeEv:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	stmfd	sp!, {r4, r5, lr}
	ldrh	r3, [r0, #20]	@  <variable>.m_BgInfo.nChars
	mov	lr, #0	@  i
	cmp	lr, r3	@  i
	mvn	r5, #0	@  Ret
	bcs	.L13
	ldr	r4, [r0, #24]	@  <variable>.m_BgInfo.pCharIndices
	mov	ip, lr	@  i,  i
	mov	r0, r3
.L17:
	mov	r1, ip, lsr #16	@  i
	add	r3, lr, #1	@  i
	mov	r3, r3, asl #16
	ldrb	r2, [r4, r1, asl #2]	@ zero_extendqisi2	@  <variable>.Char
	mov	lr, r3, asr #16	@  i
	mov	r3, lr, asl #16	@  i,  i
	cmp	r2, #32
	mov	ip, r3	@  i,  i
	addeq	r3, r4, r1, asl #2
	ldreqb	r5, [r3, #1]	@ zero_extendqisi2	@  Ret,  <variable>.Index
	beq	.L13
	cmp	r0, r3, lsr #16	@  i
	bhi	.L17
.L13:
	mov	r0, r5	@  Ret
	ldmfd	sp!, {r4, r5, lr}
	bx	lr
.Lfe4:
	.size	_ZN7CBgText22GetSpaceIndexFirstTimeEv,.Lfe4-_ZN7CBgText22GetSpaceIndexFirstTimeEv
	.align	2
	.global	_ZN7CBgText7PrintExEhhPcz
	.type	_ZN7CBgText7PrintExEhhPcz,function
_ZN7CBgText7PrintExEhhPcz:
	@ Function supports interworking.
	@ args = 4, pretend = 4, frame = 64
	@ frame_needed = 1, uses_anonymous_args = 1
	mov	ip, sp
	str	r3, [sp, #-4]!
	stmfd	sp!, {r4, r5, r6, r7, r8, fp, ip, lr, pc}
	mov	r3, r1	@  pText
	sub	fp, ip, #8
	sub	sp, sp, #64
	mov	ip, r2	@  Y
	mov	r6, r0	@  this
	ldr	r1, [fp, #4]	@  pText
	sub	r0, fp, #96
	add	r2, fp, #8
	and	r5, r3, #255	@  X,  pText
	ldr	r3, .L27
	and	r8, ip, #255	@  Y,  Y
	mov	lr, pc
	bx	r3
	mov	r4, #0	@  i
	and	r7, r0, #255	@  Cnt,  this
	cmp	r4, r7	@  i,  Cnt
	bcc	.L24
.L26:
	ldmea	fp, {r4, r5, r6, r7, r8, fp, sp, lr}
	bx	lr
.L24:
	sub	r2, fp, #32
	add	r3, r2, r4	@  i
	ldrb	r1, [r3, #-64]	@ zero_extendqisi2	@  pText,  Buffer
	mov	r0, r6	@  this
	ldr	r3, .L27+4
	mov	lr, pc
	bx	r3
	mov	r1, r5	@  X
	mov	r3, r0	@  this
	add	lr, r5, #1	@  X
	ldrb	r0, [r6, #0]	@ zero_extendqisi2	@  this,  <variable>.m_BgInfo.BgNo
	mov	r2, r8	@  Y
	ldr	ip, .L27+8
	and	r5, lr, #255	@  X
	mov	lr, pc
	bx	ip
	add	r3, r4, #1	@  i
	and	r4, r3, #255	@  i
	cmp	r4, r7	@  i,  Cnt
	bcc	.L24
	b	.L26
.L28:
	.align	2
.L27:
	.word	vsprintf
	.word	_ZN7CBgText12GetTileIndexEc
	.word	ham_SetMapTile
.Lfe5:
	.size	_ZN7CBgText7PrintExEhhPcz,.Lfe5-_ZN7CBgText7PrintExEhhPcz
	.align	2
	.global	_ZN7CBgText5PrintEhhPc
	.type	_ZN7CBgText5PrintEhhPc,function
_ZN7CBgText5PrintEhhPc:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	mov	r5, r3	@  pText
	ldrb	r3, [r3, #0]	@ * pText
	cmp	r3, #0
	sub	fp, ip, #4
	mov	r6, r0	@  this
	and	r4, r1, #255	@  X,  X
	and	r7, r2, #255	@  Y,  Y
	bne	.L33
.L35:
	ldmea	fp, {r4, r5, r6, r7, fp, sp, lr}
	bx	lr
.L33:
	and	r1, r3, #255	@  X
	mov	r0, r6	@  this
	ldr	r3, .L36
	mov	lr, pc
	bx	r3
	mov	r1, r4	@  X
	mov	r3, r0	@  this
	add	lr, r4, #1	@  X
	ldrb	r0, [r6, #0]	@ zero_extendqisi2	@  this,  <variable>.m_BgInfo.BgNo
	mov	r2, r7	@  Y
	ldr	ip, .L36+4
	and	r4, lr, #255	@  X
	mov	lr, pc
	bx	ip
	ldrb	r3, [r5, #1]!
	cmp	r3, #0
	bne	.L33
	b	.L35
.L37:
	.align	2
.L36:
	.word	_ZN7CBgText12GetTileIndexEc
	.word	ham_SetMapTile
.Lfe6:
	.size	_ZN7CBgText5PrintEhhPc,.Lfe6-_ZN7CBgText5PrintEhhPc
	.align	2
	.global	_ZN7CBgText8ClearRowEh
	.type	_ZN7CBgText8ClearRowEh,function
_ZN7CBgText8ClearRowEh:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, fp, ip, lr, pc}
	ldrh	r8, [r0, #28]	@  Index,  <variable>.m_SpaceIndex
	ldrb	r6, [r0, #0]	@ zero_extendqisi2	@  BgNo,  <variable>.m_BgInfo.BgNo
	and	r5, r1, #255	@  Row,  X
	mov	r4, #0	@  X
	sub	fp, ip, #4
	ldr	r7, .L39
	mov	r1, r4	@  X
	mov	r0, r6	@  BgNo
	mov	r2, r5	@  Row
	mov	r3, r8	@  Index
	add	r4, r4, #1	@  X,  X
	mov	lr, pc
	bx	r7
	mov	r1, r4	@  X
	mov	r0, r6	@  BgNo
	mov	r2, r5	@  Row
	mov	r3, r8	@  Index
	add	r4, r4, #1	@  X,  X
	mov	lr, pc
	bx	r7
	mov	r1, r4	@  X
	mov	r0, r6	@  BgNo
	mov	r2, r5	@  Row
	mov	r3, r8	@  Index
	add	r4, r4, #1	@  X,  X
	mov	lr, pc
	bx	r7
	mov	r1, r4	@  X
	mov	r0, r6	@  BgNo
	mov	r2, r5	@  Row
	mov	r3, r8	@  Index
	add	r4, r4, #1	@  X,  X
	mov	lr, pc
	bx	r7
	mov	r1, r4	@  X
	mov	r0, r6	@  BgNo
	mov	r2, r5	@  Row
	mov	r3, r8	@  Index
	add	r4, r4, #1	@  X,  X
	mov	lr, pc
	bx	r7
	mov	r1, r4	@  X
	mov	r0, r6	@  BgNo
	mov	r2, r5	@  Row
	mov	r3, r8	@  Index
	add	r4, r4, #1	@  X,  X
	mov	lr, pc
	bx	r7
	mov	r1, r4	@  X
	mov	r0, r6	@  BgNo
	mov	r2, r5	@  Row
	mov	r3, r8	@  Index
	add	r4, r4, #1	@  X,  X
	mov	lr, pc
	bx	r7
	mov	r1, r4	@  X
	mov	r0, r6	@  BgNo
	mov	r2, r5	@  Row
	mov	r3, r8	@  Index
	add	r4, r4, #1	@  X,  X
	mov	lr, pc
	bx	r7
	mov	r1, r4	@  X
	mov	r0, r6	@  BgNo
	mov	r2, r5	@  Row
	mov	r3, r8	@  Index
	add	r4, r4, #1	@  X,  X
	mov	lr, pc
	bx	r7
	mov	r1, r4	@  X
	mov	r0, r6	@  BgNo
	mov	r2, r5	@  Row
	mov	r3, r8	@  Index
	add	r4, r4, #1	@  X,  X
	mov	lr, pc
	bx	r7
	mov	r1, r4	@  X
	mov	r0, r6	@  BgNo
	mov	r2, r5	@  Row
	mov	r3, r8	@  Index
	add	r4, r4, #1	@  X,  X
	mov	lr, pc
	bx	r7
	mov	r1, r4	@  X
	mov	r0, r6	@  BgNo
	mov	r2, r5	@  Row
	mov	r3, r8	@  Index
	add	r4, r4, #1	@  X,  X
	mov	lr, pc
	bx	r7
	mov	r1, r4	@  X
	mov	r0, r6	@  BgNo
	mov	r2, r5	@  Row
	mov	r3, r8	@  Index
	add	r4, r4, #1	@  X,  X
	mov	lr, pc
	bx	r7
	mov	r1, r4	@  X
	mov	r0, r6	@  BgNo
	mov	r2, r5	@  Row
	mov	r3, r8	@  Index
	add	r4, r4, #1	@  X,  X
	mov	lr, pc
	bx	r7
	mov	r1, r4	@  X
	mov	r0, r6	@  BgNo
	mov	r2, r5	@  Row
	mov	r3, r8	@  Index
	add	r4, r4, #1	@  X,  X
	mov	lr, pc
	bx	r7
	mov	r1, r4	@  X
	mov	r0, r6	@  BgNo
	mov	r2, r5	@  Row
	mov	r3, r8	@  Index
	add	r4, r4, #1	@  X,  X
	mov	lr, pc
	bx	r7
	mov	r1, r4	@  X
	mov	r0, r6	@  BgNo
	mov	r2, r5	@  Row
	mov	r3, r8	@  Index
	add	r4, r4, #1	@  X,  X
	mov	lr, pc
	bx	r7
	mov	r1, r4	@  X
	mov	r0, r6	@  BgNo
	mov	r2, r5	@  Row
	mov	r3, r8	@  Index
	add	r4, r4, #1	@  X,  X
	mov	lr, pc
	bx	r7
	mov	r1, r4	@  X
	mov	r0, r6	@  BgNo
	mov	r2, r5	@  Row
	mov	r3, r8	@  Index
	add	r4, r4, #1	@  X,  X
	mov	lr, pc
	bx	r7
	mov	r1, r4	@  X
	mov	r0, r6	@  BgNo
	mov	r2, r5	@  Row
	mov	r3, r8	@  Index
	add	r4, r4, #1	@  X,  X
	mov	lr, pc
	bx	r7
	mov	r1, r4	@  X
	mov	r0, r6	@  BgNo
	mov	r2, r5	@  Row
	mov	r3, r8	@  Index
	add	r4, r4, #1	@  X,  X
	mov	lr, pc
	bx	r7
	mov	r1, r4	@  X
	mov	r0, r6	@  BgNo
	mov	r2, r5	@  Row
	mov	r3, r8	@  Index
	add	r4, r4, #1	@  X,  X
	mov	lr, pc
	bx	r7
	mov	r1, r4	@  X
	mov	r0, r6	@  BgNo
	mov	r2, r5	@  Row
	mov	r3, r8	@  Index
	add	r4, r4, #1	@  X,  X
	mov	lr, pc
	bx	r7
	mov	r1, r4	@  X
	mov	r0, r6	@  BgNo
	mov	r2, r5	@  Row
	mov	r3, r8	@  Index
	add	r4, r4, #1	@  X,  X
	mov	lr, pc
	bx	r7
	mov	r1, r4	@  X
	mov	r0, r6	@  BgNo
	mov	r2, r5	@  Row
	mov	r3, r8	@  Index
	add	r4, r4, #1	@  X,  X
	mov	lr, pc
	bx	r7
	mov	r1, r4	@  X
	mov	r0, r6	@  BgNo
	mov	r2, r5	@  Row
	mov	r3, r8	@  Index
	add	r4, r4, #1	@  X,  X
	mov	lr, pc
	bx	r7
	mov	r1, r4	@  X
	mov	r0, r6	@  BgNo
	mov	r2, r5	@  Row
	mov	r3, r8	@  Index
	add	r4, r4, #1	@  X,  X
	mov	lr, pc
	bx	r7
	mov	r1, r4	@  X
	mov	r0, r6	@  BgNo
	mov	r2, r5	@  Row
	mov	r3, r8	@  Index
	add	r4, r4, #1	@  X,  X
	mov	lr, pc
	bx	r7
	mov	r1, r4	@  X
	mov	r0, r6	@  BgNo
	mov	r2, r5	@  Row
	mov	r3, r8	@  Index
	add	r4, r4, #1	@  X,  X
	mov	lr, pc
	bx	r7
	mov	r0, r6	@  BgNo
	mov	r1, r4	@  X
	mov	r2, r5	@  Row
	mov	r3, r8	@  Index
	mov	lr, pc
	bx	r7
	ldmea	fp, {r4, r5, r6, r7, r8, fp, sp, lr}
	bx	lr
.L40:
	.align	2
.L39:
	.word	ham_SetMapTile
.Lfe7:
	.size	_ZN7CBgText8ClearRowEh,.Lfe7-_ZN7CBgText8ClearRowEh
	.align	2
	.global	_ZN7CBgText5ClearEv
	.type	_ZN7CBgText5ClearEv,function
_ZN7CBgText5ClearEv:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	sub	fp, ip, #4
	mov	r5, r0	@  this
	mov	r4, #0	@  Y
.L46:
	mov	r1, r4	@  Y
	mov	r0, r5	@  this
	bl	_ZN7CBgText8ClearRowEh
	add	r3, r4, #1	@  Y
	and	r4, r3, #255	@  Y
	cmp	r4, #19	@  Y
	bls	.L46
	ldmea	fp, {r4, r5, fp, sp, lr}
	bx	lr
.Lfe8:
	.size	_ZN7CBgText5ClearEv,.Lfe8-_ZN7CBgText5ClearEv
	.section	.gnu.linkonce.t._ZN7CBgText12GetTileIndexEc,"ax",%progbits
	.align	2
	.weak	_ZN7CBgText12GetTileIndexEc
	.type	_ZN7CBgText12GetTileIndexEc,function
_ZN7CBgText12GetTileIndexEc:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	stmfd	sp!, {r4, r5, r6, lr}
	and	r5, r1, #255	@  C
	cmp	r5, #32	@  C
	ldrsh	r3, [r0, #20]	@  MaxChars,  <variable>.m_BgInfo.nChars
	mvn	r6, #0	@  Ret
	ldreqh	r0, [r0, #28]	@  Ret,  <variable>.m_SpaceIndex
	beq	.L49
	mov	r3, r3, asl #16	@  MaxChars
	mov	r3, r3, lsr #16
	mov	r1, #0	@  i
	cmp	r1, r3	@  i
	bcs	.L52
	ldr	r4, [r0, #24]	@  <variable>.m_BgInfo.pCharIndices
	mov	lr, r1	@  i,  i
	mov	r0, r3
.L56:
	mov	ip, lr, lsr #16	@  i
	add	r3, r1, #1	@  i
	mov	r3, r3, asl #16
	ldrb	r2, [r4, ip, asl #2]	@ zero_extendqisi2	@  <variable>.Char
	mov	r1, r3, asr #16	@  i
	mov	r3, r1, asl #16	@  i,  i
	cmp	r2, r5	@  C
	mov	lr, r3	@  i,  i
	addeq	r3, r4, ip, asl #2
	ldreqb	r6, [r3, #1]	@ zero_extendqisi2	@  Ret,  <variable>.Index
	beq	.L52
	cmp	r0, r3, lsr #16	@  i
	bhi	.L56
.L52:
	mov	r0, r6	@  Ret,  Ret
.L49:
	ldmfd	sp!, {r4, r5, r6, lr}
	bx	lr
.Lfe9:
	.size	_ZN7CBgText12GetTileIndexEc,.Lfe9-_ZN7CBgText12GetTileIndexEc
	.ident	"GCC: (GNU) 3.2.2"
