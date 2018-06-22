/*********************************************************************************
 * Includes
 ********************************************************************************/
// Basically, first, as on top of all HAM files, the most
// important include is the mygba.h, which contains all the
// macro definitions, and the HAMlib function prototypes.
#include <mygba.h>

/*********************************************************************************
 * MULTIBOOT is interesting.
 * If you write this on the top of your main file,
 * the GBA ROM you build will automatically be capable of running both
 * from FLA carts and, in addition directly over the MBV2 cable.
 * If you do not need this, simply comment it out.
 ********************************************************************************/
MULTIBOOT


/*********************************************************************************
 * Globals
 ********************************************************************************/
u8 g_NewFrame=TRUE;


/*********************************************************************************
 * Prototypes
 ********************************************************************************/
void vblFunc(void);


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

    // Will, once activated, trigger the specified interrupt,
    // and then call the function specified
    ham_StartIntHandler(INT_TYPE_VBL,         // The Interrupts ID you want to start.
                        (void *)&vblFunc);    // The adress of a function that should be called when the interrupt is fired

    // Loop
    while(TRUE)
    {
        // It's a new frame?
        if(g_NewFrame)
        {

            // Frames isn't new anymore
            g_NewFrame=FALSE;
        }
    }

    return 0;
}

/*********************************************************************************
 * vblFunc(void)
 *
 * This function is called whenever the GBA is about
 * to draw a new picture onto the screen.
 ********************************************************************************/
void vblFunc(void)
{
    // Call this (preferably during a VBL interrupt) to commit your
    // ham_obj information to the hardware. Only after you did this your
    // sprite changes will appear on screen.
    ham_CopyObjToOAM();

    // It's a new frame yet
    g_NewFrame=TRUE;
}
/* END OF FILE */
