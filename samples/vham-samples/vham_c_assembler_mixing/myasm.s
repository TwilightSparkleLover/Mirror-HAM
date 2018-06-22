.GLOBL  ASM_PutPixelM4

.ARM
@.SECTION .iwram
.ALIGN
.TEXT

@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@
@   ASM_PutPixelM4 - Stores a Pixel into VRAM (MODE 4 ONLY!!!)
@
@   Not sure if this is OK anyway *cought*
@
@   c/c++ : extern void ASM_PutPixelM4(u32 x, u32 y, u32 color);
@
@   r0 = x, r1 = y, r2 = color
@
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ 20 January 2003, Peter Schraut , added MakeValue1 and MakeValue2
@ 23 January 2003, Markus Glanzer, some optimizions
ASM_PutPixelM4:

        STMFD   sp!, {r3-r7}                        @ Save registers

        @ START - F_DISCNT_BUFSEL_GET
        MOV     r3,     #0x04000000                 @ r3 = 0x04000000
        LDR     r4,     [r3]                        @ r4 = val from addr 0x04000000
        AND     r4,     r4,     #0x10               @ r4 = r4 & 0x10
        MOV     r4,     r4,     LSR #4              @ r4 = r4 >> 4
        @ End - F_DISCNT_BUFSEL_GET
        
        CMP     r4,     #1                          @ r4 == 1
        BNE     .CalcVRamAddr2						    @ != 1

   .CalcVRamAddr1:
        MOV     r3,     r1,     LSL #8
        SUB     r3,     r3,     r1,      LSL #4
        ADD     r3,     r3,     r0                  @ r3 = r3 + x
        ADD     r3,     r3,     #0x6000000          @ r3 = r3 + VRAM_ADDR
        B       .PrepareColor

   .CalcVRamAddr2:
        MOV     r3,     r1,     LSL #8
        SUB     r3,     r3,     r1,      LSL #4
        ADD     r3,     r3,     r0                  @ r3 = r3 + x
        ADD     r3,     r3,     #0x6000000          @ r3 = r3 + VRAM_ADDR
        ADD     r3,     r3,     #0xA000             @ r3 = r3 + 0xA000 (Backbuffer Addr)

   .PrepareColor:
        LDRH    r5,     [r3]                        @ r5 = VideoBuffer[Offset]
        MOV     r6,     r5,      LSR   #8           @ r6 = r5>>8 (hi)
        MOV     r7,     r5                          @ r7 = r5
        AND     r5,     r0,      #1                 @ r5 = X & 1
        TST     r5,     #0                          @ if(X&1) ..
        BNE       .MakeValue2                       @ != 0
        
   .MakeValue1:
        MOV     r4,     r2,      LSL   #8           @ hi = Color << 8
        ORR     r2,     r7,      r4                 @ color = low | r4
        B       .StoreColor
        
   .MakeValue2:
        MOV     r6,     r6,      LSL   #8           @ hi = hi << 8
        ORR     r2,     r6,      r2                 @ color = hi | color

   .StoreColor:
        STRH    r2,     [r3]                        @ Store colorvalue in VRAM
        LDMFD   sp!, {r3-r7}                        @ Restore registers
        BX      lr

