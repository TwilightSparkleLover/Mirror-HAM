/*
 * Author: Peter Schraut (www.console-dev.de)
 *
 * Created for HAM 2.6+
*/
/*********************************************************************************
 * Includes
 ********************************************************************************/
// Basically, first, as on top of all HAM files, the most
// important include is the mygba.h, which contains all the
// macro definitions, and the HAMlib function prototypes.
#include "mygba.h"
// Sinetables
#include "sinetables.h"
// Sprite GFX
#include "gfx/balls.raw.c"
#include "gfx/master.pal.c"
// Background GFX
#include "gfx/bg.raw.c"
#include "gfx/bg.pal.c"

/*********************************************************************************
 * Structures
 ********************************************************************************/
typedef struct TSprite
{
    u8 ObjNo;
    u8 X, Y;
}TSprite;

/*********************************************************************************
 * Defines and Constants
 ********************************************************************************/
#define SPRITES_COUNT  36
const u16 SPRITES_COUNT_HALF = SPRITES_COUNT/2;

/*********************************************************************************
 * Globals
 ********************************************************************************/
u8 g_NewFrame=0;
TSprite g_Spr[SPRITES_COUNT];

/*********************************************************************************
 * Prototypes
 ********************************************************************************/
void vblFunc        (void);
void CreateSprites  (void);
void MoveSprites    (void);

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
    
    // Load bitmap to vram
    ham_LoadBitmap((void*)bg_Bitmap);
    
    // Load Background Palette
    ham_LoadBGPal256((void*)bg_Palette);
    
    // Flip buffer once
    ham_FlipBGBuffer();

    // Create sprites
    CreateSprites();
    
    // Load the Palette for the Sprite
    ham_LoadObjPal256((void*)master_Palette); // a pointer to the palette data that is to be loaded
    
    // Set up the alpha blend FX
    // first parameter is selecting the source layer as follows:
    //
    // BG0 BG1 BG2 BG3 OBJ Backdrop
    //   0   0   0   0   1   0       (1=use)
    //
    // then, set up which layer should be the target layer:
    // BG0 BG1 BG2 BG3 OBJ Backdrop
    //   0   0   1   0   0   0       (1=use)
    //
    // Set the affected layers for alpha blending and tranparency.
    ham_SetFxMode(FX_LAYER_SELECT(0,0,0,0,1,0),     // Source layer
                  FX_LAYER_SELECT(0,0,1,0,0,0),     // Target layer
                  FX_MODE_ALPHABLEND);              // Effect mode
                  
    // Set the intensity of the source and target layer
    ham_SetFxAlphaLevel(10,             // Source intensity
                         9);            // Target intensity

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
            // Move our sprites
            MoveSprites();
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
    CreateSprites(void)

    Creates the objects (sprites)

*****************************************************************************************/
void CreateSprites(void)
{
    u16 i=0;

    g_Spr[0].X = 120 + rand()%120-16;
    g_Spr[0].Y =  80 + rand()%80-16;

    // Returns the ham_obj entry which is now associated with the sprite created.
    // Memory for the graphics are automatically allocated and the sprite data is
    //copied. Remember that this does not mean the sprite is comitted to Hardware yet,
    // you need to run ham_CopyObjToOAM for that
    g_Spr[0].ObjNo = ham_CreateObj((void*)balls_Bitmap,             // A pointer to the tile data for this object
                                    OBJ_SIZE_32X32,                 // obj_shape & obj_size
                                    OBJ_MODE_SEMITRANSPARENT,       // obj_mode
                                    1,                              // col_mode (1=256 colors)
                                    0,                              // pal_no
                                    0,                              // mosaic
                                    0,                              // hflip
                                    0,                              // vflip
                                    0,                              // dbl_size
                                    0,                              // prio
                                    g_Spr[0].X,                     // x position of sprite on screen
                                    g_Spr[0].Y);                    // y position of sprite on screen

    
    
    for(i=1; i<SPRITES_COUNT_HALF; i++)
    {
        g_Spr[i].X = 120 + rand()%120-16;
        g_Spr[i].Y =  80 + rand()%80-16;
        
        // Clone an existing Sprite
        g_Spr[i].ObjNo = ham_CloneObj(g_Spr[0].ObjNo,   // OBJ number of which you want to clone
                                      g_Spr[i].X,       // X position of the cloned sprite (0..511)
                                      g_Spr[i].Y);      // Y position of the cloned sprite (0..255)
    }


    // Returns the ham_obj entry which is now associated with the sprite created.
    // Memory for the graphics are automatically allocated and the sprite data is
    //copied. Remember that this does not mean the sprite is comitted to Hardware yet,
    // you need to run ham_CopyObjToOAM for that
    g_Spr[i].ObjNo = ham_CreateObj((void*)&balls_Bitmap[32*32],     // A pointer to the tile data for this object
                                    OBJ_SIZE_32X32,                 // obj_shape & obj_size
                                    OBJ_MODE_SEMITRANSPARENT,       // obj_mode
                                    1,                              // col_mode (1=256 colors)
                                    0,                              // pal_no
                                    0,                              // mosaic
                                    0,                              // hflip
                                    0,                              // vflip
                                    0,                              // dbl_size
                                    0,                              // prio
                                    g_Spr[0].X-1,                   // x position of sprite on screen
                                    g_Spr[0].Y-1);                  // y position of sprite on screen

    
    
    for(i=SPRITES_COUNT_HALF+1; i<(SPRITES_COUNT); i++)
    {
        g_Spr[i].X = g_Spr[i-SPRITES_COUNT_HALF].X;
        g_Spr[i].Y = g_Spr[i-SPRITES_COUNT_HALF].Y;
        
        // Clone an existing Sprite
        g_Spr[i].ObjNo = ham_CloneObj(g_Spr[SPRITES_COUNT_HALF].ObjNo,  // OBJ number of which you want to clone
                                      g_Spr[i].X,                       // X position of the cloned sprite (0..511)
                                      g_Spr[i].Y);                      // Y position of the cloned sprite (0..255)
    }
}

/*****************************************************************************************
    MoveSprites(void)
    
    Moves the objects (sprites) around.
    
*****************************************************************************************/
void MoveSprites(void)
{
    u16 i;
    static u16 s_Count1=0;
    
    if(++s_Count1 > 128) s_Count1=0;
    
    for(i=0; i<SPRITES_COUNT_HALF; i++)
    {
        s16 x =  70 + ((g_Spr[i].X + g_SinTab2[(SPRITES_COUNT_HALF+s_Count1+(i<<2))] + g_SinTab1[SPRITES_COUNT_HALF+s_Count1+(i<<2)])>>1);
        s16 y =  30 + ((g_Spr[i].Y + g_SinTab2[s_Count1+(i<<2)] - g_SinTab1[SPRITES_COUNT_HALF+(s_Count1+(i<<1))])>>1);

        // Set a Sprites X and Y Position on the screen
        ham_SetObjXY(g_Spr[i].ObjNo,                    // OBJ number of which you want to position
                     x,                                 // The desired X value (0..511)
                     y);                                // The desired Y value (0..255)

        // Set a Sprites X and Y Position on the screen
        ham_SetObjXY(g_Spr[i+SPRITES_COUNT_HALF].ObjNo, // OBJ number of which you want to position
                     x,                                 // The desired X value (0..511)
                     y);                                // The desired Y value (0..255)
    }
}

/* END OF FILE */
