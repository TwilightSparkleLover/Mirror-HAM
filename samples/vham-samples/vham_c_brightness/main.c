/*
 * Special FX supported since HAM 2.6 !
*/
/*********************************************************************************
 * Includes
 ********************************************************************************/
// Basically, first, as on top of all HAM files, the most
// important include is the mygba.h, which contains all the
// macro definitions, and the HAMlib function prototypes.
#include "mygba.h"

#include "buster.map.c"
#include "buster.raw.c"
#include "obj.pal.c"

#include "balls.raw.c"
#include "balls.map.c"
#include "engine.raw.c"
#include "engine.map.c"
#include "bg.pal.c"


/*********************************************************************************
 * Global Variables
 ********************************************************************************/
u32 g_Frames=0;
u8  g_NewFrame=1;
u8  g_BrightIntensity=0;
u8  g_BG2X=0;
u8  g_BG2Y=0;


/*********************************************************************************
 * Prototypes
 ********************************************************************************/
void vblFunc(void);


/*********************************************************************************
 * Program entry point
 ********************************************************************************/
int main(void)
{
    // Sprite-Index of the bunny on the lower right
    u8 SprBunny;
    
    
    // Initialize HAMlib
    // Then we call the single most important function of ham, ham_Init .
    // This function must be called first thing when working with HAMlib,
    // because all ham_* functions will only work correctly after this has been called.
    // Behaviour of HAMlib is undefined if you comment this out.
    ham_Init();


    // Sets the GBAs BGMode to the value specified
    ham_SetBgMode(0);


    // Load Background Palette
    // 256 colors/entries
    ham_LoadBGPal256((void*)bg_Palette);


    // This function will load a tileset (usually from ROM)
    // from the src pointer and copy it into an appropiate spot
    // in the GBAs BG VRAM. The spot is decided by the memory manager,
    // and passed back in the structure.
    ham_bg[2].ti = ham_InitTileSet( &balls_Tiles,                   // A pointer to the source data
                                    SIZEOF_16BIT(balls_Tiles),      // The size of the tiles to be copied into Tile RAM, in number of 16bit chunks
                                    1,                              // The Color mode of the tile set (0=16col 1=256col)
                                    1);                             // Setting this one requires a bit of understanding of the GBA hardware.
                                                                    // Basically, if you put tiles into the GBA memory, you will have to put
                                                                    // them at the start of a Character Base block in order to be able to
                                                                    // access tile #0 with a map entry of 0. If the allocated block is not
                                                                    // directly at the start of a CBB, you will have to offset your map entries.
                                                                    // This is automatically done for you when you use ham_SetMapTile.
                                                                    // However, when you load your map from ROM, you might want to align your
                                                                    // tileset to a CBB boundary. If in doubt, and you have some VRAM left, set
                                                                    // this to 1 always.
                                                                    // 0=allocate at the earliest possible spot, unsafe if you do not know / do not
                                                                    // want to offset your map entries!
                                                                    // 1=allocate only on a CBB start to ensure tile 0 is map index no 0.
                                                                    // Again, if you have no idea what this is, set it to 1.


    // Initializes a Map Set and loads it into GBA VRAM
    ham_bg[2].mi = ham_InitMapSet((void*)balls_Map,     // A pointer to the source data, usually in ROM
                                  1024,                 // Size of the map to be copied into BG RAM, in number of 16bit chunks
                                  0,                    // Size of the map (0-3). This depends on the map_rot parameter
                                  0);                   // Determines if this is a map for a rotation screen (0 = no rotation map)


    // You can call this function to actually commit this BG to the hardware.
    // This command will throw an error if the BG that you want to init has not yet
    // been assigned a ti and mi. For more information on how to assign these to a bg,
    //see the links below.
    ham_InitBg(2,   // The BGs number that you want to Initialize (0-3)
               1,   // 1 = show this BG, 0 = hide this BG
               2,   // Priority of this BG to other BGs (0 = highest prio, 3 = lowest)
               0);  // Enable / Disable Mosaic for this BG (0=off 1=on)
               
               
    // This function will load a tileset (usually from ROM)
    // from the src pointer and copy it into an appropiate spot
    // in the GBAs BG VRAM. The spot is decided by the memory manager,
    // and passed back in the structure.
    ham_bg[3].ti = ham_InitTileSet( &engine_Tiles,                  // A pointer to the source data
                                    SIZEOF_16BIT(engine_Tiles),     // The size of the tiles to be copied into Tile RAM, in number of 16bit chunks
                                    1,                              // The Color mode of the tile set (0=16col 1=256col)
                                    1);                             // Setting this one requires a bit of understanding of the GBA hardware.
                                                                    // Basically, if you put tiles into the GBA memory, you will have to put
                                                                    // them at the start of a Character Base block in order to be able to
                                                                    // access tile #0 with a map entry of 0. If the allocated block is not
                                                                    // directly at the start of a CBB, you will have to offset your map entries.
                                                                    // This is automatically done for you when you use ham_SetMapTile.
                                                                    // However, when you load your map from ROM, you might want to align your
                                                                    // tileset to a CBB boundary. If in doubt, and you have some VRAM left, set
                                                                    // this to 1 always.
                                                                    // 0=allocate at the earliest possible spot, unsafe if you do not know / do not
                                                                    // want to offset your map entries!
                                                                    // 1=allocate only on a CBB start to ensure tile 0 is map index no 0.
                                                                    // Again, if you have no idea what this is, set it to 1.


    // Initializes a Map Set and loads it into GBA VRAM
    ham_bg[3].mi = ham_InitMapSet((void*)engine_Map,    // A pointer to the source data, usually in ROM
                                  1024,                 // Size of the map to be copied into BG RAM, in number of 16bit chunks
                                  0,                    // Size of the map (0-3). This depends on the map_rot parameter
                                  0);                   // Determines if this is a map for a rotation screen (0 = no rotation map)


    // You can call this function to actually commit this BG to the hardware.
    // This command will throw an error if the BG that you want to init has not yet
    // been assigned a ti and mi. For more information on how to assign these to a bg,
    //see the links below.
    ham_InitBg(3,   // The BGs number that you want to Initialize (0-3)
               1,   // 1 = show this BG, 0 = hide this BG
               0,   // Priority of this BG to other BGs (0 = highest prio, 3 = lowest)
               0);  // Enable / Disable Mosaic for this BG (0=off 1=on)
               
               
    // Set the Scroll offset of a BG Layer.
    ham_SetBgXY(3,        // The BG number we want to scroll
                30,       // The new X offset value
                50);      // The new Y offset value
                        
                        
    // Load the Palette for the Sprite
    ham_LoadObjPal256((void*)obj_Palette); // a pointer to the palette data that is to be loaded


    // Returns the ham_obj entry which is now associated with the sprite created.
    // Memory for the graphics are automatically allocated and the sprite data is
    //copied. Remember that this does not mean the sprite is comitted to Hardware yet,
    // you need to run ham_CopyObjToOAM for that
    SprBunny = ham_CreateObj((void*)buster_Tiles,           // A pointer to the tile data for this object
                            OBJ_SIZE_32X64,                 // obj_shape & obj_size
                            OBJ_MODE_SEMITRANSPARENT,       // obj_mode
                            1,                              // col_mode (1=256 colors)
                            0,                              // pal_no
                            0,                              // mosaic
                            0,                              // hflip
                            0,                              // vflip
                            0,                              // dbl_size
                            0,                              // prio
                            200,                            // x position of sprite on screen
                            90);                            // y position of sprite on screen


   // Will, once activated, trigger the specified interrupt,
   // and then call the function specified
   ham_StartIntHandler(INT_TYPE_VBL,         // The Interrupts ID you want to start.
                       (void *)&vblFunc);    // The adress of a function that should be called when the interrupt is fired

    // Loop
    while(1)
    {
        // Its a new frame?
        if(g_NewFrame)
        {
            // Just to skip some frames
            if(!(g_Frames&7))
            {
                // Fade screen from normal to white
                if(g_BrightIntensity < 16)
                {
                    ham_SetFxMode(FX_LAYER_SELECT(1,1,1,1,1,0),         // Source layer
                                  FX_LAYER_SELECT(0,0,0,0,0,0),         // Target layer
                                  FX_MODE_LIGHTEN);                     // Effect mode
                                  
                    // Set the intensity of the source and target layer
                    ham_SetFxBrightnessLevel(g_BrightIntensity&15);     // intensity
                }
                else
                // Fade screen from white to normal
                if((g_BrightIntensity >= 16) && (g_BrightIntensity < 32))
                {
                    ham_SetFxMode(FX_LAYER_SELECT(1,1,1,1,1,0),         // Source layer
                                  FX_LAYER_SELECT(0,0,0,0,0,0),         // Target layer
                                  FX_MODE_LIGHTEN);                     // Effect mode
                                  
                    // Set the intensity of the source and target layer
                    ham_SetFxBrightnessLevel(32-g_BrightIntensity);     // intensity
                }
                else
                // Fade screen from normal to black
                if((g_BrightIntensity >= 32) && (g_BrightIntensity < 48))
                {
                    ham_SetFxMode(FX_LAYER_SELECT(1,1,1,1,1,0),         // Source layer
                                  FX_LAYER_SELECT(0,0,0,0,0,0),         // Target layer
                                  FX_MODE_DARKEN);                      // Effect mode
                                  
                    // Set the intensity of the source and target layer
                    ham_SetFxBrightnessLevel(g_BrightIntensity&15);     // intensity
                }
                else
                // Fade screen from black to normal
                if((g_BrightIntensity >= 48) && (g_BrightIntensity < 64))
                {
                    ham_SetFxMode(FX_LAYER_SELECT(1,1,1,1,1,0),         // Source layer
                                  FX_LAYER_SELECT(0,0,0,0,0,0),         // Target layer
                                  FX_MODE_DARKEN);                      // Effect mode
                                  
                    // Set the intensity of the source and target layer
                    ham_SetFxBrightnessLevel(64-g_BrightIntensity);     // intensity
                }
                else
                    g_BrightIntensity=0;

                // Increase bright helper variable
                g_BrightIntensity++;
            }
            
            // Set the Scroll offset of a BG Layer.
            ham_SetBgXY(2,              // The BG number we want to scroll
                        g_BG2X++,       // The new X offset value
                        g_BG2Y++);      // The new Y offset value
            
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
void vblFunc()
{
   // Call this (preferably during a VBL interrupt) to commit your
   // ham_obj information to the hardware. Only after you did this your
   // sprite changes will appear on screen.
   ham_CopyObjToOAM();
   // increase total frames
   g_Frames++;
   // Its a new frame
   g_NewFrame=1;
}
