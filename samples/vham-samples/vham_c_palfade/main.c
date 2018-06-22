/*
 * Created by using HAM 2.5
 * Author: Peter Schraut / www.console-dev.de
*/

/*********************************************************************************
 * Includes
 ********************************************************************************/
// Basically, first, as on top of all HAM files, the most
// important include is the mygba.h, which contains all the
// macro definitions, and the HAMlib function prototypes.
#include "mygba.h"

// Include the graphic, a 240x160 texture
// Convertet by using gfx2gba
#include "bg.raw.c"
#include "bg.pal.c"

/*********************************************************************************
 * MULTIBOOT is interesting.
 * If you write this on the top of your main file,
 * the GBA ROM you build will automatically be capable of running both
 * from FLA carts and, in addition directly over the MBV2 cable.
 * If you do not need this, simply comment it out.
 ********************************************************************************/
MULTIBOOT

/*********************************************************************************
 * Global Variables
 ********************************************************************************/
u8 g_NewFrame=0;


/*********************************************************************************
 * Prototypes
 ********************************************************************************/
void vblFunc(void);


/*********************************************************************************
 * Program entry point
 ********************************************************************************/
int main(void)
{
   u8 delay=0;

   // Initialize HAMlib
   // Then we call the single most important function of ham, ham_Init .
   // This function must be called first thing when working with HAMlib,
   // because all ham_* functions will only work correctly after this has been called.
   // Behaviour of HAMlib is undefined if you comment this out.
   ham_Init();

   // Sets the GBAs BGMode to the value specified
   ham_SetBgMode(4);

   // Use these to schedule your DMA transfers easily.
   //dma the background pic
   TOOL_DMA1_SET(bg_Bitmap,               // start address to read data from
                 MEM_BG_PTR,              // address to write the data to
                 SIZEOF_32BIT(bg_Bitmap), // how many elements to copy
                 DMA_TRANSFER_32BIT,      // if this is DMA_TRANSFER_32BIT, one element is 32bits
                                          // if this is DMA_TRANSFER_16BIT, one element is 16bits
                 DMA_STARTAT_NOW)         // specifies when the DMA will start

   // init the Palette for background
   ham_LoadBGPal((void*)bg_Palette,
                  sizeof(bg_Palette));

   // Will, once activated, trigger the specified interrupt,
   // and then call the function specified
   ham_StartIntHandler(INT_TYPE_VBL,         // The Interrupts ID you want to start.
                       (void *)&vblFunc);    // The adress of a function that should be called when the interrupt is fired

   while(1)
   {
      if(g_NewFrame)
      {
         // Get input control, check if "A" button has been pressed
         if(F_CTRLINPUT_A_PRESSED)
            // init the Palette for background
            ham_LoadBGPal((void*)bg_Palette,
                           sizeof(bg_Palette));

            if(++delay > 8)
            {
               // Fades the palatte to black
               ham_FadePal(0,    // The palette number to fade, 0 for BG palette, 1 for Sprite palette
                           1);   // the amount that is subtracted from the palette each call
               delay=0;
            }

          g_NewFrame=0;
      }
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
   g_NewFrame=1;
}

/* END OF FILE */
