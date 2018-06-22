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
#include "math.h"



/*********************************************************************************
 * Prototypes
 ********************************************************************************/
// Notice the "C", otherwise you get linker errors!
extern "C" void ASM_PutPixelM4(u32 x, u32 y, u32 color);


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

   // Background color
   TOOL_SET_BG_PAL_256(0,  // Palette index
                       0,  // Red value
                       0,  // Green value
                       0)  // Blue value

   // Color of pixel we will put
   TOOL_SET_BG_PAL_256(1, 255, 100, 255)


   // loop 4ever
   while(1)
   {
      // Clears the backbuffer
      ham_ClearBackBuffer(0);

      for(i=0; i<100; i++)
      {
          // Calling the assembler routine
          ASM_PutPixelM4(10+i, 80, 1);
      }
      
      // Flip buffers
      ham_FlipBGBuffer();
   }
}


/* www.console-dev.de */

/* END OF FILE */
