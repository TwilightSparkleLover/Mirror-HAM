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

/*********************************************************************************
 * MULTIBOOT is interesting.
 * If you write this on the top of your main file,
 * the GBA ROM you build will automatically be capable of running both
 * from FLA carts and, in addition directly over the MBV2 cable.
 * If you do not need this, simply comment it out.
 ********************************************************************************/
MULTIBOOT

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
   // Mode4 = 240 x 160 Pixels (doublebuffered)
   ham_SetBgMode(4);

   // Background color
   TOOL_SET_BG_PAL_256(0,  // Palette index
                       0,  // Red value
                       0,  // Green value
                       0)  // Blue value

   // Color of line we will display
   TOOL_SET_BG_PAL_256(1, 100, 100, 255)


   // loop 4ever
   while(1)
   {
      // Clears the backbuffer by using colorindex 0
      ham_ClearBackBuffer(0);

      // Plott line
      ham_PutLine(10,    // x coordinate of the line start point
                  10,    // y coordinate of the line start point
                  230,   // x coordinate of the line end point
                  150,   // y coordinate of the line end point
                  1);    // The color value you want to set.
                         // Depending on the BG Mode you are in, this
                         // should either be a color palette index
                         // (for 256 color mode) or a 16bit RGB value
                         // (for high color modes)

      // Flip buffers
      ham_FlipBGBuffer();
   }
}


/* www.console-dev.de */

/* END OF FILE */
