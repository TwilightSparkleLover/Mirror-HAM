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

/*********************************************************************************
 * Prototypes
 ********************************************************************************/
void Timer3Function(void);


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
   
   // Sets the GBAs BGMode to the value specified in bgno
   ham_SetBgMode(0);

   // Init the Text display system on the bg of your choice
   // This function must be called if you want to use HAMlibs text display system.
   // After calling this, you can use ham_DrawText and ham_SetTextCol.
   ham_InitText(0);
   
   // Set a specific BG palette color to a 15 bit BGR value
   ham_SetBgPalCol(0, COLOR_BLACK);
   ham_SetBgPalCol(1, COLOR_LIME);


   // Will set the color indices of the font to the BG colors specified
   ham_SetTextCol(1,    // Set texts front color to the BG palette index specified
                  0);   // Set texts back color to the BG palette index specified

   // Will, once activated, trigger the specified interrupt,
   // and then call the function specified
   ham_StartIntHandler(INT_TYPE_TIM3,               // The Interrupts ID you want to start.
                       (void *)&Timer3Function);   // The adress of a function that should be called when the interrupt is fired

   
   // Selects the speed of timer3
   M_TIM3CNT_SPEED_SELECT_SET(10)

   // Enable IRQ for timer3
   M_TIM3CNT_IRQ_ENABLE

   // Start timer3
   M_TIM3CNT_TIMER_START

   // Draws Text. Be aware that this function is SLOW.
   // It should only be used for debug purposes.
   ham_DrawText(6, 2, "ham timer example");

   // Infinite loop
   while(1)
   {
      // ...
   }

   return 0;
}

/*****************************************************************************************
 *
 * Timer3Function(void)
 *
 * Displays the elapsed hours, minutes and seconds *twink twink*
 *
 ****************************************************************************************/
void Timer3Function(void)
{
   static u8 s_H=0, s_M=0, s_S=0;

   if(++s_S > 59)
   {
      if(++s_M > 59)
      {
         if(++s_H > 11)
         {
            s_H=0;
         }
         s_M=0;
      }
      s_S = 0;
   }

   // Draws Text. Be aware that this function is SLOW.
   // It should only be used for debug purposes.
   ham_DrawText(6, 6, "HH:MM:SS %.2d:%.2d:%.2d ", s_H, s_M, s_S);
}

/* END OF FILE */
