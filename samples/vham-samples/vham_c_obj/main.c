/*********************************************************************************
 * Includes
 ********************************************************************************/
// Basically, first, as on top of all HAM files, the most
// important include is the mygba.h, which contains all the
// macro definitions, and the HAMlib function prototypes.
#include "mygba.h"
// Include AFM header
#include "afm.h"
// Graphics
#include "gfx/master.pal.c"
#include "gfx/balls.raw.c"
#include "gfx/bg.raw.c"
#include "gfx/bg.pal.c"
// Lookup tables for the sprite wobbling
#include "lookups.h"


/*********************************************************************************
 * MULTIBOOT is interesting.
 * If you write this on the top of your main file,
 * the GBA ROM you build will automatically be capable of running both
 * from FLA carts and, in addition directly over the MBV2 cable.
 * If you do not need this, simply comment it out.
 ********************************************************************************/
MULTIBOOT

/*********************************************************************************
 * Defines
 ********************************************************************************/
#define NUM_SPRITES 80  // You can set this to max 127


/*********************************************************************************
 * Global Variables
 ********************************************************************************/
u8 g_NewFrame=0;
u32 g_Frames=0;
// extern holding the mod file
extern const unsigned char _binary_module_mod_start;

/*********************************************************************************
 * Prototypes
 ********************************************************************************/
void vblFunc(void);


/*********************************************************************************
 * Program entry point
 ********************************************************************************/
int main(void)
{

    u8 i;
    u8 arSprite[NUM_SPRITES];

    // Initialize HAMlib
    // Then we call the single most important function of ham, ham_Init .
    // This function must be called first thing when working with HAMlib,
    // because all ham_* functions will only work correctly after this has been called.
    // Behaviour of HAMlib is undefined if you comment this out.
    ham_Init();

    // Sets the GBAs BGMode to the value specified
    // Mode4 = 240 x 160 Pixels (doublebuffered)
    ham_SetBgMode(4);

    // DMA the background pic
    TOOL_DMA1_SET(&bg_Bitmap,MEM_BG_PTR,SIZEOF_32BIT(bg_Bitmap),DMA_TRANSFER_32BIT,DMA_STARTAT_NOW)


    // Load Background Palette
    ham_LoadBGPal((void *)&bg_Palette,         // a pointer to the palette data that is to be loaded
                  SIZEOF_16BIT(bg_Palette));   // the size of the data in u16 chunks (usually 256)
    
    // Inits the Palette for the Sprite
    ham_LoadObjPal((void *)&master_Palette,        // a pointer to the palette data that is to be loaded
                   SIZEOF_16BIT(master_Palette));  // the number of the 16 color OBJ (sprite) palette you
                                                   // want to load with the 16 color values at address src.

   // Returns the ham_obj entry which is now associated with the sprite created.
   // Memory for the graphics are automatically allocated and the sprite data is
   //copied. Remember that this does not mean the sprite is comitted to Hardware yet,
   // you need to run ham_CopyObjToOAM for that
   arSprite[0] = ham_CreateObj((void *)&balls_Bitmap[0],  // A pointer to the tile data for this object
                              0,                       // obj_shape
                              2,                       // obj_size
                              OBJ_MODE_NORMAL,         // obj_mode
                              1,                       // col_mode
                              0,                       // pal_no
                              0,                       // mosaic
                              0,                       // hflip
                              0,                       // vflip
                              0,                       // dbl_size
                              0,                       // prio
                              30,                      // x position of sprite on screen
                              30);                     // y position of sprite on screen
                             
   // Returns the ham_obj entry which is now associated with the sprite created.
   // Memory for the graphics are automatically allocated and the sprite data is
   //copied. Remember that this does not mean the sprite is comitted to Hardware yet,
   // you need to run ham_CopyObjToOAM for that
   arSprite[1] = ham_CreateObj((void *)&balls_Bitmap[32*32],  // A pointer to the tile data for this object
                              0,                       // obj_shape
                              2,                       // obj_size
                              OBJ_MODE_NORMAL,         // obj_mode
                              1,                       // col_mode
                              0,                       // pal_no
                              0,                       // mosaic
                              0,                       // hflip
                              0,                       // vflip
                              0,                       // dbl_size
                              0,                       // prio
                              30,                      // x position of sprite on screen
                              30);                     // y position of sprite on screen
                              
    // Clone the others
    for(i=2; i<NUM_SPRITES; i++)
    {
        // Cloning a sprite means having another ham_obj entry that you can play
        // with that uses a copy of the data set up for the sprite specified in objno.
    	arSprite[i] = ham_CloneObj(arSprite[i%2],  // The sprite number we want to clone
                                   1,              // X position of the cloned sprite
                                   1);             // Y position of the cloned sprite
    }

   // Install player/mixer
   // you must call this function before calling any other of the
   // players routines.
   afm_install();

   // init modfile + soundsystem
   // modfile must be a pointer to a standard 4-Channel Protracker Module
   afm_init((unsigned char*)&_binary_module_mod_start);
   
   // Set sound parameters
   afm_sound_param(0x30,    // vol: 0x00...0x3f    master volume
                   1);      // chn: 1: mono replay (somewhat louder) any other: stereo replay


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
           // update player+mixing buffers
           // you must call this once each frame (timing doesnt matter)
           afm_update();

           // Rotate and zoom the Background-Map
           ham_RotBg(2,                                    // The bg number that is to be rotated (2-3 only since BG1 and 2 can never rotate in the GBA)
                     g_Frames%360,                         // Angle of rotation
                     120,                                  // Rotation center x
                     80,                                   // Rotation center y
                     0x100+(SIN_SFP32[180+g_Frames%180])); // Fixed point number. Normal (no zoom) is 0x100.

            // update the sprite positions.
            for(i=0;i<NUM_SPRITES/2;i++)
            {
                // Sets the X and Y Position of the Sprite number specified
                ham_SetObjXY(arSprite[i],wobble_x[(g_Frames+(i*2))%120],
                             wobble_y[(g_Frames+(i*3))%300]);
            }
            
            for(i=NUM_SPRITES/2;i<NUM_SPRITES;i++)
            {
                // Sets the X and Y Position of the Sprite number specified
                ham_SetObjXY(arSprite[i],wobble_x[(g_Frames+1400+(i*2))%120],
                             wobble_y[(g_Frames+1400+(i*2))%300]);
            }
            
            // show this frame as processed (will be set to 1 in
            // VBLhandler again)
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
void vblFunc()
{
    // Sync sound DMA
    // you must call this right at the start of vblank (precise timing required)
    afm_sync();
	             	
   // Call this (preferably during a VBL interrupt) to commit your
   // ham_obj information to the hardware. Only after you did this your
   // sprite changes will appear on screen.
   ham_CopyObjToOAM();
                 	
   //signify new frame
   g_NewFrame=1;
   g_Frames++;
}

/* END OF FILE */
