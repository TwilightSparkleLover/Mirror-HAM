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
 * TOOL_PROFILER_INIT, available since HAM version 2.52 !!!
 *
 * WARNING: If you want to use this, make sure that your code does NOT use Timer3.
 * This is needed by the profiler.
 *
 * The HAM Profiler defines can help you to find out how fast a certain piece of your
 * program executes.
 ********************************************************************************/
TOOL_PROFILER_INIT


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

   // Start profiler
   TOOL_PROFILER_START
   
   // Draws Text. Be aware that this function is SLOW.
   // It should only be used for debug purposes.
   ham_DrawText(2,2,"PROFILER EXAMPLE:");
   ham_DrawText(2,4,"HAM will VBAText out the");
   ham_DrawText(2,5,"time elapsed between the");
   ham_DrawText(2,6,"start and end of the code");
   ham_DrawText(2,7,"in question.");

   // End profiler
   // When the end is encountered, HAM will VBAText out the time elapsed
   // between the start and end of the code in question.
   TOOL_PROFILER_END
   
   
   while(1)
   {
   }
}


/* END OF FILE */
