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

   // Init the Text display system on the bg of your choice
   // This function must be called if you want to use HAMlibs text display system.
   // After calling this, you can use ham_DrawText and ham_SetTextCol.
   ham_InitText(0);

   // Draws Text. Be aware that this function is SLOW.
   // It should only be used for debug purposes.
   ham_DrawText(2,2,"C PAD Demo");

   while(1)
   {
           if(F_CTRLINPUT_A_PRESSED     ) ham_DrawText(2,4,"-A- Pressed     ");
      else if(F_CTRLINPUT_B_PRESSED     ) ham_DrawText(2,4,"-B- Pressed     ");
      else if(F_CTRLINPUT_R_PRESSED     ) ham_DrawText(2,4,"-R- Pressed     ");
      else if(F_CTRLINPUT_L_PRESSED     ) ham_DrawText(2,4,"-L- Pressed     ");
      else if(F_CTRLINPUT_START_PRESSED ) ham_DrawText(2,4,"-Start- Pressed ");
      else if(F_CTRLINPUT_SELECT_PRESSED) ham_DrawText(2,4,"-Select- Pressed");
      else if(F_CTRLINPUT_UP_PRESSED    ) ham_DrawText(2,4,"-Up- Pressed    ");
      else if(F_CTRLINPUT_DOWN_PRESSED  ) ham_DrawText(2,4,"-Down- Pressed  ");
      else if(F_CTRLINPUT_LEFT_PRESSED  ) ham_DrawText(2,4,"-Left- Pressed  ");
      else if(F_CTRLINPUT_RIGHT_PRESSED ) ham_DrawText(2,4,"-Right- Pressed ");
   }
}


/* END OF FILE */
