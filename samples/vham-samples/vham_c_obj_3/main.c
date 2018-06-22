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
 * Structures
 ********************************************************************************/
typedef struct
{
   s16 x, y;
}TVector2, *PVector2;

/*********************************************************************************
 * Global Variables
 ********************************************************************************/
u8 g_SprObj;   // Global Sprite (index)
u8 g_NewFrame=0;

/*********************************************************************************
 * Prototypes
 ********************************************************************************/
void vblFunc(void);
void doSprites(void);

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


   // Will, once activated, trigger the specified interrupt, 
   // and then call the function specified
   ham_StartIntHandler(INT_TYPE_VBL,         // The Interrupts ID you want to start.
                       (void *)&vblFunc);    // The adress of a function that should be called when the interrupt is fired
   
   // Loop
   while(1)
   {
       // New Frame?
       if(g_NewFrame)
       {
           doSprites();
           g_NewFrame=0;
       }
   }    
}

/*********************************************************************************
 * doSprites(void)
 *
 * This function updates the X,Y positions of our sprites
 ********************************************************************************/
void doSprites(void)
{
   static TVector2 vSprXY = {240/2-32, 160/2-32};
   static s8 xSpeed=1, ySpeed=2;

   // Clip sprite
   if ((vSprXY.x > 240-64) || (vSprXY.x < 1)) xSpeed*=-1;
   if ((vSprXY.y > 160-64) || (vSprXY.y < 1)) ySpeed*=-1;

   // Calculate new x and y position
   vSprXY.x+=xSpeed;
   vSprXY.y+=ySpeed;

   // Sets the X and Y Position of the Sprite number specified
   ham_SetObjXY(g_SprObj,  // The sprite number we want to move
                vSprXY.x,  // The x position of the sprite
                vSprXY.y); // The y position of the sprite
}

/*********************************************************************************
 * vblFunc(void)
 * 
 * This function is called whenever the GBA is about 
 * to draw a new picture onto the screen.
 ********************************************************************************/
void vblFunc(void)
{
   g_NewFrame=1;

   // Call this (preferably during a VBL interrupt) to commit your 
   // ham_obj information to the hardware. Only after you did this your 
   // sprite changes will appear on screen.          
   ham_CopyObjToOAM();
}

/* END OF FILE */
