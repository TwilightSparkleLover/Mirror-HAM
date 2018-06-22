/*
 * Author: Peter Schraut (www.console-dev.de)
 *
 * Made for HAM 2.52+
 *
*/
/*********************************************************************************
 * Includes
 ********************************************************************************/
// Basically, first, as on top of all HAM files, the most
// important include is the mygba.h, which contains all the
// macro definitions, and the HAMlib function prototypes.
#include "mygba.h"
#include "sinetable.h"


/*********************************************************************************
 * Defines
 ********************************************************************************/
#ifndef R_DMA3CNT32
#define R_DMA3CNT32  *(volatile u32 *)(MEM_IO + 0x0DC)
#endif


/*********************************************************************************
 * Globals
 ********************************************************************************/
u8  g_NewFrame=0;
u16 *g_pScreen=NULL;


/*********************************************************************************
 * Prototypes
 ********************************************************************************/
void vblFunc(void);
void DrawLines(void);
void ClearScreen(void);
inline u16 *GetBackBufferAddrOf(u8 X, u8 Y);
inline void DrawScanline(u16 *pActScreen, s16 wX1, s16 wX2, s16 wY, u8 ubColor);


/*********************************************************************************
 * Program entry point
 ********************************************************************************/
int main(void)
{
    // Initialize HAMlib
    // Then we call the single most important function of ham, ham_Init .
    // This function must be called first thing when working with HAMlib,
    // because all ham_* functions will only work correctly after this has been called.
    // Behaviour of HAMlib is undefined if you comment this out.
    ham_Init();

    // Sets the GBAs BGMode to the value specified
    ham_SetBgMode(4);
    
    // Store colors into background palette
    TOOL_SET_BG_PAL_256(0,0x00,0x40,0x80);
    TOOL_SET_BG_PAL_256(1,0x00,0x80,0xC0);


    // Will, once activated, trigger the specified interrupt,
    // and then call the function specified
    ham_StartIntHandler(INT_TYPE_VBL,         // The Interrupts ID you want to start.
                        (void *)&vblFunc);    // The adress of a function that should be called when the interrupt is fired


    // Loop
    while(1)
    {
        // It's a new frame?
        if(g_NewFrame)
        {
            // Get backbuffer address
            g_pScreen = GetBackBufferAddrOf(0, 0);
            
            // Clears the backbuffer
            ClearScreen();
            
            // Displays our sinewaves
            DrawLines();
            
            // Flip buffer
            ham_FlipBGBuffer();
            
            // Frames isn't new anymore
            g_NewFrame=0;
        }
    }

    return 0;
}
/*********************************************************************************
 * DrawLines(void)
 *
 * Draws the sinewave lines
 ********************************************************************************/
void DrawLines(void)
{
    u16 i=0;
    static u16 s_Counter=0;

    if((s_Counter+=2) > 256) s_Counter=0;

    // Loop
    while(i < 160)
    {
        DrawScanline(g_pScreen, 0, 40+((g_SinTab[s_Counter+i]+g_SinTab[s_Counter+(i<<2)])>>1), i, 1);
        i++;
    }
}
/*********************************************************************************
 * DrawScanline(u16 *pActScreen, s16 X1, s16 X2, s16 Y, u8 Color)
 *
 * Draws a horizontal line onto the screen, using DMA3 transfer (pretty fast)
 *
 * Routine is originaly made by Arnaud STORQ a.k.a.
 * No Recess/CONDENSE (norecess@planet-d.net)
 *
 * Slighty modified to fit more into HAM.
 ********************************************************************************/
inline void DrawScanline(u16 *pActScreen, s16 X1, s16 X2, s16 Y, u8 Color)
{
#ifndef R_DMA3CNT32
#define R_DMA3CNT32  *(volatile u32 *)(MEM_IO + 0x0DC)
#endif

	u16 Pixel;
	u16 Value;
	u16 Count;
	s16 Offset;
	
	if ((Y<0) || (Y>160)) return;
	if ((X1<0) && (X2<0)) return;
	if ((X1>240) && (X2>240)) return;
	if (X2 < X1) return;
	
	if (X1<0) X1 = 0;
	if (X2>240) X2 = 240;

	Offset = (Y*240+X1)>>1;

	if ((X1 & 1) != 0)
	{
		Pixel = pActScreen[Offset];
		pActScreen[Offset] = (Color<<8) + (Pixel & 0x00FF);
		X1++;
		Offset++;
	}

	Value = (Color<<8) + Color;
	Count = (X2-X1)>>1;

	if (Count > 1)
	{		
		R_DMA3SRC   = (u32)(&Value);
		R_DMA3DST   = (u32)(&pActScreen[Offset]);
		R_DMA3CNT32 = ((u32)1<<31) | ((u32)1<<24) | Count;
	}

	Offset += Count;

	if (X2 < 240)
	{
		if ((X2 & 1) != 0)
		{
			Pixel = pActScreen[Offset];
			pActScreen[Offset] =  (Pixel & 0xFF00) + Color;
		}
	}
}
/*********************************************************************************
 * GetBackBufferAddrOf(u8 X, u8 Y)
 *
 * Returns the BackBuffer address specified in X and Y
 ********************************************************************************/
inline u16 *GetBackBufferAddrOf(u8 X, u8 Y)
{
    u32 Addr;

    // Get current buffer
	if(F_DISCNT_BUFSEL_GET)
		Addr = MEM_VRAM;
	else
		Addr = (MEM_VRAM + 0xA000);
		
	// Return adress
    return (u16*)(Addr + (Y*240) + X);
}
/*********************************************************************************
 * ClearScreen(void)
 *
 * Clears the backbuffer
 * Much faster than the original "ham_ClearBackBuffer" function in HAM 2.52
 ********************************************************************************/
void ClearScreen(void)
{
    u8 i;
    u64 *Addr;

    // Get current buffer
	if(F_DISCNT_BUFSEL_GET)
        Addr = (u64*)MEM_VRAM;
	else
        Addr = (u64*)(MEM_VRAM+0xA000);

    // Clear each scanline
    for(i=0; i < 160; ++i)
    {
        *Addr++ = 0; *Addr++ = 0; *Addr++ = 0; *Addr++ = 0;
        *Addr++ = 0; *Addr++ = 0; *Addr++ = 0; *Addr++ = 0;
        *Addr++ = 0; *Addr++ = 0; *Addr++ = 0; *Addr++ = 0;
        *Addr++ = 0; *Addr++ = 0; *Addr++ = 0; *Addr++ = 0;
        *Addr++ = 0; *Addr++ = 0; *Addr++ = 0; *Addr++ = 0;
        *Addr++ = 0; *Addr++ = 0; *Addr++ = 0; *Addr++ = 0;
        *Addr++ = 0; *Addr++ = 0; *Addr++ = 0; *Addr++ = 0;
        *Addr++ = 0; *Addr++ = 0;
    }
}
/*********************************************************************************
 * vblFunc(void)
 *
 * This function is called whenever the GBA is about
 * to draw a new picture onto the screen.
 ********************************************************************************/
void vblFunc(void)
{
    // Call this (preferably during a VBL interrupt) to commit your
    // ham_obj information to the hardware. Only after you did this your
    // sprite changes will appear on screen.
    ham_CopyObjToOAM();

    // It's a new frame yet
    g_NewFrame=1;
}
/* END OF FILE */
