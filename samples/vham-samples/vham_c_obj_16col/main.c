/*
 * This document has been created by using Visual HAM
 * http://www.console-dev.de
 *
 * Author: Peter Schraut
 *
 * Made for HAM 2.7
 *
*/
/*
   Do not forget to take a look at the makefile, since you need
   to specify some options that the tool knows you want to convert it
   to 16 color gfx and a special palettebank!
*/

/*********************************************************************************
 * Includes
 ********************************************************************************/
// Basically, first, as on top of all HAM files, the most
// important include is the mygba.h, which contains all the
// macro definitions, and the HAMlib function prototypes.
#include "mygba.h"

// Include the graphics
#include "gfx/GfxQuadRed.raw.c"
#include "gfx/GfxQuadRed.pal.c"
#include "gfx/GfxQuadYellow.raw.c"
#include "gfx/GfxQuadYellow.pal.c"
#include "gfx/GfxQuadGreen.raw.c"
#include "gfx/GfxQuadGreen.pal.c"

/*********************************************************************************
 * Globals
 ********************************************************************************/
u8 g_NewFrame=1;
u8 g_SprRed;
u8 g_SprYellow;
u8 g_SprGreen;

/*********************************************************************************
 * Prototypes
 ********************************************************************************/
void vblFunc(void);
void InitSprites(void);


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

    // Sets the GBAs BGMode to the value specified
    ham_SetBgMode(0);

    // Init the Text display system on the bg of your choice
    // This function must be called if you want to use HAMlibs text display system.
    // After calling this, you can use ham_DrawText and ham_SetTextCol.
    ham_InitText(0);

    // Will set the color indices of the font to the BG colors specified
    ham_SetTextCol(1,    // Set texts front color to the BG palette index specified
                   0);   // Set texts back color to the BG palette index specified

    // Set a specific OBJ Palette color to a 15 bit BGR value
    ham_SetBgPalCol(0,               // The color you want to modify
                    COLOR_BLACK);    // BGR color value in GBA color format ( 5 bit blue, 5 bit green, 5 bit red)

    // Set a specific OBJ Palette color to a 15 bit BGR value
    ham_SetBgPalCol(1,               // The color you want to modify
                    COLOR_WHITE);    // BGR color value in GBA color format ( 5 bit blue, 5 bit green, 5 bit red)

    // Initialize the sprites
    InitSprites();
    
    // Draws Text. Be aware that this function is SLOW.
    // It should only be used for debug purposes.
    ham_DrawText(1, 1, "Using multiple");
    ham_DrawText(1, 2, "16 color palettes");
    
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
            // Frames isn't new anymore
            g_NewFrame=0;
        }
    }

    return 0;
}


/*********************************************************************************
 * InitSprites(void)
 ********************************************************************************/
void InitSprites(void)
{
    // Load new colors into one 16 color OBJ (Sprite) palette
    ham_LoadObjPal16((void*)&GfxQuadRed_Palette,    // pointer to the palette color data (colors need to be defined in 15bit 5:5:5 BGR format and span 16bit each)
                     0);                            // 16 color palette number you want to modify (0..15)
    // Returns the ham_obj entry which is now associated with the sprite created.
    // Memory for the graphics are automatically allocated and the sprite data is
    //copied. Remember that this does not mean the sprite is comitted to Hardware yet,
    // you need to run ham_CopyObjToOAM for that
    g_SprRed = ham_CreateObj((void*)&GfxQuadRed_Bitmap,  // A pointer to the tile data for this object
                        OBJ_SIZE_16X16,      // obj_shape & obj_size
                        OBJ_MODE_NORMAL,     // obj_mode
                        0,                   // col_mode (1=256 colors)
                        0,                   // pal_no
                        0,                   // mosaic
                        0,                   // hflip
                        0,                   // vflip
                        0,                   // prio
                        0,                   // dbl_size
                        20,                  // x position of sprite on screen
                        50);                 // y position of sprite on screen


    // Load new colors into one 16 color OBJ (Sprite) palette
    ham_LoadObjPal16((void*)&GfxQuadYellow_Palette,    // pointer to the palette color data (colors need to be defined in 15bit 5:5:5 BGR format and span 16bit each)
                     1);                               // 16 color palette number you want to modify (0..15)

    // Returns the ham_obj entry which is now associated with the sprite created.
    // Memory for the graphics are automatically allocated and the sprite data is
    //copied. Remember that this does not mean the sprite is comitted to Hardware yet,
    // you need to run ham_CopyObjToOAM for that
    g_SprYellow = ham_CreateObj((void*)&GfxQuadYellow_Bitmap,  // A pointer to the tile data for this object
                        OBJ_SIZE_16X16,      // obj_shape & obj_size
                        OBJ_MODE_NORMAL,     // obj_mode
                        0,                   // col_mode (1=256 colors)
                        1,                   // pal_no
                        0,                   // mosaic
                        0,                   // hflip
                        0,                   // vflip
                        0,                   // prio
                        0,                   // dbl_size
                        50,                  // x position of sprite on screen
                        70);                 // y position of sprite on screen


    // Load new colors into one 16 color OBJ (Sprite) palette
    ham_LoadObjPal16((void*)&GfxQuadGreen_Palette,    // pointer to the palette color data (colors need to be defined in 15bit 5:5:5 BGR format and span 16bit each)
                     2);                              // 16 color palette number you want to modify (0..15)

    // Returns the ham_obj entry which is now associated with the sprite created.
    // Memory for the graphics are automatically allocated and the sprite data is
    //copied. Remember that this does not mean the sprite is comitted to Hardware yet,
    // you need to run ham_CopyObjToOAM for that
    g_SprGreen = ham_CreateObj((void*)&GfxQuadGreen_Bitmap,  // A pointer to the tile data for this object
                        OBJ_SIZE_16X16,      // obj_shape & obj_size
                        OBJ_MODE_NORMAL,     // obj_mode
                        0,                   // col_mode (1=256 colors)
                        2,                   // pal_no
                        0,                   // mosaic
                        0,                   // hflip
                        0,                   // vflip
                        0,                   // prio
                        0,                   // dbl_size
                        80,                  // x position of sprite on screen
                        90);                 // y position of sprite on screen
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
/* END OF FILE */
