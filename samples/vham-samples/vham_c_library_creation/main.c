/*
 * Author: Peter Schraut / www.console-dev.de
 *
 * Created for HAM 2.52+
 *
 * To update/compile the library call "make lib"
 * And you really should take a look at the makefile!
 *
*/
/*********************************************************************************
 * Includes
 ********************************************************************************/
// Basically, first, as on top of all HAM files, the most
// important include is the mygba.h, which contains all the
// macro definitions, and the HAMlib function prototypes.
#include "mygba.h"
// include our own header
#include "mylib.h"

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
    ham_SetBgMode(1);
    
    // Init the Text display system on the bg of your choice
    // This function must be called if you want to use HAMlibs text display system.
    // After calling this, you can use ham_DrawText and ham_SetTextCol.
    ham_InitText(0);
    
    // Call the function from our linked library
    mylib_PrintHelloWorld();
    
    // Loop for ever
    while(1);

    return 0;
}


/* END OF FILE */
