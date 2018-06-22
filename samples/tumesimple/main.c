/*********************************************************************************
 * Includes
 ********************************************************************************/
// Basically, first, as on top of all HAM files, the most
// important include is the mygba.h, which contains all the
// macro definitions, and the HAMlib function prototypes.
#include <mygba.h>

// TUME specific -- your converted Level must be included here. the HAM build logic
//                  uses tUMERIC to convert the level specified in the makefile into
//                  a header file. This header file must be included so we can then 
//                  reference it, as shown below.
#include "tumemap/LVL1.h"

/*********************************************************************************
 * Globals
 ********************************************************************************/
u8  g_NewFrame=TRUE;
int worldx=0;
int worldy=0;

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
    // start the Pad Monitoring System
    ham_InitPad();
    
    // Initialize the tUME Map support in HAM, specifying the tUME Map to use
    ham_InitTume((TUMERIC_ROOT*)&LVL1_ROOT);
    // Initialize a Room of your choice (which loads the tiles for the room)
    ham_InitTumeRoom(0);
    // Initialize a Layer in that Room (which created the BG and displays it)
    ham_InitTumeLayer(0,0,0,0,worldx,worldy);

    // start a Vertical Blank Interrupt
    ham_StartIntHandler(INT_TYPE_VBL,         // The Interrupts ID you want to start.
                        (void *)&vblFunc);    // The adress of a function that should be called when the interrupt is fired

    // Loop
    while(TRUE)
    {
        // It's a new frame?
        if(g_NewFrame)
        {
            if(Pad.Held.Right)
                worldx+=8;
            if(Pad.Held.Left)
                worldx-=8;
            if(Pad.Held.Up)
                worldy-=8;
            if(Pad.Held.Down)
                worldy+=8;

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
    //check for button presses
    ham_UpdatePad();
    //move the tUME layer
    ham_MoveTumeLayer(0,worldx,worldy);
    //signify a new frame
    g_NewFrame=TRUE;
}
/* END OF FILE */
