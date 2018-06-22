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

// Include the graphic, a 64x64 4bit texture (3 colors)
// Convertet by using gfx2gba
#include "gfx/texture.raw.c"
#include "gfx/master.pal.c"

/*********************************************************************************
 * MULTIBOOT is interesting. 
 * If you write this on the top of your main file, 
 * the GBA ROM you build will automatically be capable of running both 
 * from FLA carts and, in addition directly over the MBV2 cable. 
 * If you do not need this, simply comment it out.
 ********************************************************************************/
MULTIBOOT

/*********************************************************************************
 * Global Variables
 ********************************************************************************/
u8 g_SprObj;   // Global Sprite (index)

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
   ham_SetBgMode(4);

   // Inits the Palette for the Sprite
   ham_LoadObjPal((void *)&master_Palette,        // a pointer to the palette data that is to be loaded
                   SIZEOF_16BIT(master_Palette)); // the number of the 16 color OBJ (sprite) palette you
                                                  // want to load with the 16 color values at address src.
                                             
   // Returns the ham_obj entry which is now associated with the sprite created. 
   // Memory for the graphics are automatically allocated and the sprite data is 
   //copied. Remember that this does not mean the sprite is comitted to Hardware yet, 
   // you need to run ham_CopyObjToOAM for that
   g_SprObj = ham_CreateObj((void *)&texture_Bitmap,  // A pointer to the tile data for this object
                             0,                       // obj_shape
                             3,                       // obj_size
                             OBJ_MODE_NORMAL,         // obj_mode
                             1,                       // col_mode
                             0,                       // pal_no
                             0,                       // mosaic
                             0,                       // hflip
                             0,                       // vflip
                             0,                       // dbl_size
                             0,                       // prio
                             240/2-32,                // x position of sprite on screen
                             160/2-32);               // y position of sprite on screen


   // Call this (preferably during a VBL interrupt) to commit your 
   // ham_obj information to the hardware. Only after you did this your 
   // sprite changes will appear on screen.          
   ham_CopyObjToOAM();
   
   
   while(1)
   {
   }    
}


/* END OF FILE */
