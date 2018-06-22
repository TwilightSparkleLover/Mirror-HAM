/*
 * This document has been created by using Visual HAM
 * http://www.console-dev.de
 *
 * Author: Peter Schraut
 *
 * Made with HAM 2.7
 *
 * This file was made as an example for a question at the HAM mailinglist
*/
/*********************************************************************************
 * Includes
 ********************************************************************************/
// Basically, first, as on top of all HAM files, the most
// important include is the mygba.h, which contains all the
// macro definitions, and the HAMlib function prototypes.
#include "mygba.h"
// Our graphics
#include "gfx/GfxBeer.raw.c"
#include "gfx/master.pal.c"

/*********************************************************************************
 * Globals
 ********************************************************************************/
u8 g_NewFrame=1;
u8 g_Obj[2];

/*********************************************************************************
 * Prototypes
 ********************************************************************************/
void vblFunc         (void);
void CreateObjects   (void);
void MoveObjects     (void);

/* Tables by GPZ's SinLab V1 (c)98 by Hitmen */
// download it at www.hitmen-console.org
/* 2 Period(s) from -32 to 32 */
const s8 g_SinTab1[128*2]=
{ 2 , 3 , 5 , 6 , 8 , 9 , 11 , 12 ,
 14 , 15 , 16 , 18 , 19 , 20 , 21 , 23 ,
 24 , 25 , 26 , 27 , 27 , 28 , 29 , 30 ,
 30 , 31 , 31 , 31 , 32 , 32 , 32 , 32 ,
 32 , 32 , 32 , 31 , 31 , 31 , 30 , 30 ,
 29 , 28 , 27 , 27 , 26 , 25 , 24 , 23 ,
 21 , 20 , 19 , 18 , 16 , 15 , 14 , 12 ,
 11 , 9 , 8 , 6 , 5 , 3 , 2 , 0 ,
-2 ,-3 ,-5 ,-6 ,-8 ,-9 ,-11 ,-12 ,
-14 ,-15 ,-16 ,-18 ,-19 ,-20 ,-21 ,-23 ,
-24 ,-25 ,-26 ,-27 ,-27 ,-28 ,-29 ,-30 ,
-30 ,-31 ,-31 ,-31 ,-32 ,-32 ,-32 ,-32 ,
-32 ,-32 ,-32 ,-31 ,-31 ,-31 ,-30 ,-30 ,
-29 ,-28 ,-27 ,-27 ,-26 ,-25 ,-24 ,-23 ,
-21 ,-20 ,-19 ,-18 ,-16 ,-15 ,-14 ,-12 ,
-11 ,-9 ,-8 ,-6 ,-5 ,-3 ,-2 , 0,
 2 , 3 , 5 , 6 , 8 , 9 , 11 , 12 ,
 14 , 15 , 16 , 18 , 19 , 20 , 21 , 23 ,
 24 , 25 , 26 , 27 , 27 , 28 , 29 , 30 ,
 30 , 31 , 31 , 31 , 32 , 32 , 32 , 32 ,
 32 , 32 , 32 , 31 , 31 , 31 , 30 , 30 ,
 29 , 28 , 27 , 27 , 26 , 25 , 24 , 23 ,
 21 , 20 , 19 , 18 , 16 , 15 , 14 , 12 ,
 11 , 9 , 8 , 6 , 5 , 3 , 2 , 0 ,
-2 ,-3 ,-5 ,-6 ,-8 ,-9 ,-11 ,-12 ,
-14 ,-15 ,-16 ,-18 ,-19 ,-20 ,-21 ,-23 ,
-24 ,-25 ,-26 ,-27 ,-27 ,-28 ,-29 ,-30 ,
-30 ,-31 ,-31 ,-31 ,-32 ,-32 ,-32 ,-32 ,
-32 ,-32 ,-32 ,-31 ,-31 ,-31 ,-30 ,-30 ,
-29 ,-28 ,-27 ,-27 ,-26 ,-25 ,-24 ,-23 ,
-21 ,-20 ,-19 ,-18 ,-16 ,-15 ,-14 ,-12 ,
-11 ,-9 ,-8 ,-6 ,-5 ,-3 ,-2 , 0 };

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

    // Creates the objects (sprites)
    CreateObjects();

    // Will, once activated, trigger the specified interrupt,
    // and then call the function specified
    ham_StartIntHandler(INT_TYPE_VBL,         // The Interrupts ID you want to start.
                        (void *)&vblFunc);    // The adress of a function that should be called when the interrupt is fired

    // Loop
    while(1)
    {
        // It's a new frame?
        if(g_NewFrame)
        {
            // Move the objects (sprites)
            MoveObjects();
            
            // Frames isn't new anymore
            g_NewFrame=0;
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
    g_NewFrame=1;
}

/*****************************************************************************************
 *
 * MoveObjects(void)
 *
 * Moves an object on the y axis using the sintable above
 *
 ****************************************************************************************/
void MoveObjects(void)
{
   static u16 s_Counter=0;
   
   // increase counter
   if(++s_Counter > 128) s_Counter=0;
   
   // Sets the X and Y position of an object (sprite)
   ham_SetObjXY(g_Obj[0],                 // Object number
                116,                      // Set X position
                80+g_SinTab1[s_Counter]); // Set Y position
}

/*****************************************************************************************
 *
 * CreateObjects(void)
 *
 * Just creates one object (sprite)
 *
 ****************************************************************************************/
void CreateObjects(void)
{
   // Load the object palette
   ham_LoadObjPal256((void*)&master_Palette);
   
   // Create an object
   g_Obj[0] = ham_CreateObj((void*)&GfxBeer_Bitmap,  // A pointer to the tile data for this object
                     OBJ_SIZE_16X32,      // obj_shape & obj_size
                     OBJ_MODE_NORMAL,     // obj_mode
                     1,                   // col_mode (1=256 colors)
                     0,                   // pal_no
                     0,                   // mosaic
                     0,                   // hflip
                     0,                   // vflip
                     0,                   // prio
                     0,                   // dbl_size
                     120,                 // x position of sprite on screen
                     0);                  // y position of sprite on screen
}
/* END OF FILE */
