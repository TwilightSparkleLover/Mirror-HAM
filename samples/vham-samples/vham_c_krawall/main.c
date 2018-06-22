/*
 * Created by using HAM 2.52
 * Author: Peter Sch. / www.console-dev.de
*/

/*********************************************************************************
 * Includes
 ********************************************************************************/
// Basically, first, as on top of all HAM files, the most
// important include is the mygba.h, which contains all the
// macro definitions, and the HAMlib function prototypes.
#include "mygba.h"
#include "modules.h"

/*********************************************************************************
 * Global Variables
 ********************************************************************************/
u32 g_Frames=0;
u32 g_NewFrame=0;

/*********************************************************************************
 * Prototpyes
 ********************************************************************************/
void vblFunc(void);


/*********************************************************************************
 * Program entry point
 ********************************************************************************/
int main(void)
{
  u16 Now_Playing=0xff;

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
   ham_DrawText(7,2 ,"HAM Krawall Demo");
   ham_DrawText(7,4 ,"  Press a key");
   ham_DrawText(1,9, "UP      aqua.s3m");
   ham_DrawText(1,10,"DOWN    autonomus.s3m");
   ham_DrawText(1,11,"LEFT    ctgoblin.s3m");
   ham_DrawText(1,12,"RIGHT   explorat.s3m");
   ham_DrawText(1,13,"A       gmotion.s3m");
   ham_DrawText(1,14,"B       inspiration.s3m");

   // Call this function once at startup
   kragInit(KRAG_INIT_STEREO);

   // Will, once activated, trigger the specified interrupt,
   // and then call the function specified
   ham_StartIntHandler(INT_TYPE_TIM1,&kradInterrupt);
   ham_StartIntHandler(INT_TYPE_VBL,&vblFunc);

  // Loop
  while(1)
  {
      if(g_NewFrame)
      {
   	  if(F_CTRLINPUT_UP_PRESSED   && (0!=Now_Playing))
   	  {
   	      Now_Playing=0;
   	      krapPlay(&mod_aqua,KRAP_MODE_LOOP,Now_Playing);
   	  }

   	  if(F_CTRLINPUT_DOWN_PRESSED && (1!=Now_Playing))
   	  {
   	      Now_Playing=1;
   	      krapPlay(&mod_autonomus,KRAP_MODE_LOOP,Now_Playing);
   	  }

   	  if(F_CTRLINPUT_LEFT_PRESSED && (2!=Now_Playing))
   	  {
   	      Now_Playing=2;
   	      krapPlay(&mod_ctgoblin,KRAP_MODE_LOOP,Now_Playing);
   	  }

   	  if(F_CTRLINPUT_RIGHT_PRESSED && (3!=Now_Playing))
   	  {
   	      Now_Playing=3;
   	      krapPlay(&mod_explorat,KRAP_MODE_LOOP,Now_Playing);
   	  }

   	  if(F_CTRLINPUT_A_PRESSED && (4!=Now_Playing))
   	  {
   	      Now_Playing=4;
   	      krapPlay(&mod_gmotion,KRAP_MODE_LOOP,Now_Playing);
   	  }

   	  if(F_CTRLINPUT_B_PRESSED && (5!=Now_Playing))
        {
            Now_Playing=5;
            krapPlay(&mod_inspiration,KRAP_MODE_LOOP,Now_Playing);
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
    kramWorker();

	g_NewFrame=1;
}

/* END OF FILE */
