/*
 * This document has been created by using Visual HAM
 * http://www.console-dev.de
 *
 * Author: Peter Schraut
 *
 * Created for HAM 2.7
 *
*/
/*********************************************************************************
 * Includes
 ********************************************************************************/
// Basically, first, as on top of all HAM files, the most
// important include is the mygba.h, which contains all the
// macro definitions, and the HAMlib function prototypes.
#include "mygba.h"
// Include stdio.h for the sprintf stuff
#include "stdio.h"


/*********************************************************************************
 * Program entry point
 ********************************************************************************/
int main(void)
{
   u32 iLib;
   char strLib[32];
   
   // Initialize HAMlib
   // Then we call the single most important function of ham, ham_Init .
   // This function must be called first thing when working with HAMlib,
   // because all ham_* functions will only work correctly after this has been called.
   // Behaviour of HAMlib is undefined if you comment this out.
   ham_Init();

   // Sets the GBAs BGMode to the value specified in bgno
   ham_SetBgMode(0);
   
    // Init the Text display system on the bg of your choice
    // This function must be called if you want to use HAMlibs text display system.
    // After calling this, you can use ham_DrawText and ham_SetTextCol.
   ham_InitText(0);
   
   // Will set the color indices of the font to the BG colors specified
   ham_SetTextCol(1,    // Set texts front color to the BG palette index specified
                  0);   // Set texts back color to the BG palette index specified

   // Set a specific BG palette color to a 15 bit BGR value
   ham_SetBgPalCol(0, COLOR_MEDGRAY);
   ham_SetBgPalCol(1, COLOR_BLACK);

   // Get current HAMlib version
   iLib = ham_GetHAMlibVersion();
   sprintf(strLib, "HAMlib Version %.2f", (float)((iLib>>16)+((iLib&0x0000FFFF)*0.1f)));
   
   // Draws Text. Be aware that this function is SLOW.
   // It should only be used for debug purposes.
   ham_DrawText(1, 2, "Compiled with:");
   ham_DrawText(1, 3, strLib);

   // Infinite loop
   while(1)
   {
      // ...
   }

   return 0;
}


/* END OF FILE */
