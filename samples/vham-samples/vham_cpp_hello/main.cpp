/*
 * Created by using HAM 2.5
 * Author: Peter Sch. / www.console-dev.de
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
 * Classes and Global Variables
 ********************************************************************************/
class CHello
{
    private:
    
    public:
       // Draws Text. Be aware that this function is SLOW.
       // It should only be used for debug purposes.
        void DrawHelloWorld(void) { ham_DrawText(2,2,"CPP Hello World"); }
};

// Our Class
CHello *g_pHello = new CHello;


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
   
   // Call DrawHelloWorld routine
   g_pHello->DrawHelloWorld();
   
   while(true)
   {
       // Loop infinite
   }    
}


/* END OF FILE */
