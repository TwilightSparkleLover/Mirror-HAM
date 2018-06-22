/*
 * Created for HAM 2.7
 * Author: Peter Sch. / www.console-dev.de
 *
 * 23/1/2003 - Changed TOOL_SET_BG_PAL_256 macro to ham function ham_SetBgPalCol
 *
*/

/*********************************************************************************
 * Includes
 ********************************************************************************/
// Basically, first, as on top of all HAM files, the most
// important include is the mygba.h, which contains all the
// macro definitions, and the HAMlib function prototypes.
#include "mygba.h"


/*********************************************************************************
 * MULTIBOOT is interesting.
 * If you write this on the top of your main file,
 * the GBA ROM you build will automatically be capable of running both
 * from FLA carts and, in addition directly over the MBV2 cable.
 * If you do not need this, simply comment it out.
 ********************************************************************************/
MULTIBOOT


/*********************************************************************************
 * Prototypes
 ********************************************************************************/
extern void ASM_PutPixelM4(u32 x, u32 y, u32 color);


/*********************************************************************************
 * Program entry point
 ********************************************************************************/
int main(void)
{
   u16 i=0;
   
   // Initialize HAMlib
   // Then we call the single most important function of ham, ham_Init .
   // This function must be called first thing when working with HAMlib,
   // because all ham_* functions will only work correctly after this has been called.
   // Behaviour of HAMlib is undefined if you comment this out.
   ham_Init();

   // Sets the GBAs BGMode to the value specified
   // Mode4 = 240 x 160 Pixels (doublebuffered)
   ham_SetBgMode(4);

   // Set a specific OBJ Palette color to a 15 bit BGR value
   ham_SetBgPalCol(0,               // The color you want to modify
                   COLOR_BLACK);    // BGR color value in GBA color format ( 5 bit blue, 5 bit green, 5 bit red)

   // Set a specific OBJ Palette color to a 15 bit BGR value
   ham_SetBgPalCol(1,               // The color you want to modify
                   COLOR_FUCHSIA);  // BGR color value in GBA color format ( 5 bit blue, 5 bit green, 5 bit red)

   // loop 4ever
   while(1)
   {
      // Clears the backbuffer
      ham_ClearBackBuffer(0);

      for(i=10; i<220; i++)
      {
          // Calling the assembler routine
          ASM_PutPixelM4(i, 80, 1);
      }

      // Flip buffers
      ham_FlipBGBuffer();
   }
}


/* www.console-dev.de */

/* END OF FILE */
