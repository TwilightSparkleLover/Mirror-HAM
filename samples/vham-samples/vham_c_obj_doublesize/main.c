/*
 * Created by using HAM 2.6
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
u8  g_SprObj;   // Global Sprite (index)
u8  g_NewFrame=1;
u16 g_Angle=0;


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

   // Sets the GBAs BGMode to the value specified
   ham_SetBgMode(0);
   
    // Init the Text display system on the bg of your choice
    // This function must be called if you want to use HAMlibs text display system.
   ham_InitText(0);
   
    // Will set the color indices of the font to the BG colors specified
    ham_SetTextCol(1,    // Set texts front color to the BG palette index specified
                   0);   // Set texts back color to the BG palette index specified
   
   // Will set the background color palette entries
   TOOL_SET_BG_PAL_256(0, 0x80, 0x00, 0x00);
   TOOL_SET_BG_PAL_256(1, 0xFF, 0xFF, 0xFF);

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
                             0,                       // x position of sprite on screen
                             0);                      // y position of sprite on screen


   // Will enable Rotation and Scaling for a Sprite.
   // You need to specify one of the 32 available (0..31)
   // Rotation Sets this sprite will use (also together with other Sprites using the same set)
   // using ham_SetObjRotSetSelect() in order to assign the sprite.
   // After that, you can use ham_RotObjDefineSet() to modify the angle and zooming of
   // the sprites assigned to the Rotation Set.
   ham_SetObjRotEnable(g_SprObj,    // OBJ number of which you want to modify
                       1);          // 0 = object is not in rotation mode
                                    // 1 = object will be in rotation mode using the
                                    // rotation set specified by the ham_SetObjRotSetSelect() function
                                    
   // This will assign the Rotation Set the Sprite specified should use from now on
   ham_SetObjRotSetSelect(g_SprObj, // OBJ number of which you want to modify
                          1);       // number of the Rotation Set (0..31)
   
   // Will, once activated, trigger the specified interrupt,
   // and then call the function specified
   ham_StartIntHandler(INT_TYPE_VBL,         // The Interrupts ID you want to start.
                       (void *)&vblFunc);    // The adress of a function that should be called when the interrupt is fired

   // Draws Text. Be aware that this function is SLOW.
   // It should only be used for debug purposes.
   ham_DrawText(4, 2, "   hold -a- button");
   ham_DrawText(4, 3, "to enable double size");
   
   // Loop forever
   while(1)
   {
       // New Frame?
       if(g_NewFrame)
       {
           // Set the Values for a Rotation Set for Sprite
           ham_RotObjDefineSet(1,               // RotationRotation Set you want to modify (0..31)
                              (g_Angle++)%360,  // Angle to rotate the BG in degrees (0..359)
                              0x100,            // Zoom level for the X axis (default is 0x100 which is 256, means no zoom)
                              0x100);           // Zoom level for the Y axis (default is 0x100 which is 256, means no zoom)

           // Get joypad input
           if(F_CTRLINPUT_A_PRESSED)
           {
               // Enable object double size
               ham_SetObjDblSize(g_SprObj, 1);
                
               // Update Object X,Y position in order to have it centred
               ham_SetObjXY(g_SprObj, 240/2-64, 160/2-64);
           }
           else
           {
               // Disable object double size
               ham_SetObjDblSize(g_SprObj, 0);
                
               // Update Object X,Y position in order to have it centred
               ham_SetObjXY(g_SprObj, 240/2-32, 160/2-32);
           }
           
           // not a new frame anymore
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
   // Call this (preferably during a VBL interrupt) to commit your
   // ham_obj information to the hardware. Only after you did this your
   // sprite changes will appear on screen.
    ham_CopyObjToOAM();
    
    g_NewFrame=1;
}

/* END OF FILE */
