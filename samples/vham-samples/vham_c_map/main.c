/*********************************************************************************
 * Includes
 ********************************************************************************/
// Basically, first, as on top of all HAM files, the most
// important include is the mygba.h, which contains all the
// macro definitions, and the HAMlib function prototypes.
#include "mygba.h"
// Graphic includes
#include "gfx/master.pal.c"
#include "gfx/isle.raw.c"
#include "gfx/isle.map.c"


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
u8  g_NewFrame=0;
u8  g_Frames=0;
u16 g_X=0;
u16 g_Y=0;


/*********************************************************************************
 * Prototypes
 ********************************************************************************/
void vblFunc(void);


/*********************************************************************************
 * Program entry point
 ********************************************************************************/
int main(void)
{

	map_fragment_info_ptr BackGroundMap;

    // Initialize HAMlib
    // Then we call the single most important function of ham, ham_Init .
    // This function must be called first thing when working with HAMlib,
    // because all ham_* functions will only work correctly after this has been called.
    // Behaviour of HAMlib is undefined if you comment this out.
    ham_Init();
    
    // Sets the GBAs BGMode to the value specified in bgno
    ham_SetBgMode(1);

    // Init the Text display system on the bg of your choice
    // This function must be called if you want to use HAMlibs text display system.
    // After calling this, you can use ham_DrawText and ham_SetTextCol.
    ham_InitText(0);
    
    // Load Background Palette
    ham_LoadBGPal((void *)&master_Palette,         // a pointer to the palette data that is to be loaded
                  SIZEOF_16BIT(master_Palette));   // the size of the data in u16 chunks (usually 256)

    // Sets a RGB color value to the background palette
    TOOL_SET_BG_PAL_256(3,      // Index
                        255,    // R Value
                        255,    // G Value
                        255)    // B Value
    
    // Will set the color indices of the font to the BG colors specified
    ham_SetTextCol(0x03,    // Set texts front color to the BG palette index specified
                   0x00);   // Set texts back color to the BG palette index specified

    // This function will load a tileset (usually from ROM)
    // from the src pointer and copy it into an appropiate spot
    // in the GBAs BG VRAM. The spot is decided by the memory manager,
    // and passed back in the structure.
    ham_bg[1].ti = ham_InitTileSet((void*)&isle_Tiles,              // A pointer to the source data
                                    SIZEOF_16BIT(isle_Tiles),       // The size of the tiles to be copied into Tile RAM, in number of 16bit chunks
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


    // This function will create an Empty (all zero) map in the BG RAM,
    // and return a pointer to it via the map_info structure.
    // This empty map can be linked to a BG, or populated by functions like ham_InsertMapFragment
    ham_bg[1].mi = ham_InitMapEmptySet(3,   // the size of the map (0-3). This depends on the map_rot parameter!
                                       0);  // determines if this is a map for a rotation screen. (0 = no rotation map, 1 = rotation map)

    // This function will allocate a new structure that can be used
    // to reference the map data (usually in ROM) for rectangle
    // copies onto a map currently on screen.
    BackGroundMap = ham_InitMapFragment((void*)&isle_Map,           // A pointer to the source data
                                        64,                         // The total width of the map you are pointing to in tiles.
                                        64,                         // The total height of the map you are pointing to in tiles.
                                        0,                          // The horizontal offset, in tiles, on the map you want to start copying from
                                        0,                          // The vertical offset, in tiles, on the map you want to start copying from
                                        64,                         // The number of tiles (from the offset on) you want to specify horizontally
                                        64,                         // The number of tiles (from the offset on) you want to specify vertically
                                        0);                         // 0 = no rotation map, 1 = rotation map


    // This will copy the map from the Map Fragment onto the
    // BG Map currently used by the BG specified at a location
    // the user chooses with the x and y parameters.
    ham_InsertMapFragment(BackGroundMap,    // A map fragment info pointer previously created by ham_InitMapFragment
                          1,                // The BG number you want to Insert the map fragment on (0-3)
                          0,                // The X position (in tiles) in the BG map where you want the Fragment to be placed
                          0);               // The Y position (in tiles) in the BG map where you want the Fragment to be placed


    // You can call this function to actually commit this BG to the hardware.
    // This command will throw an error if the BG that you want to init has not yet
    // been assigned a ti and mi. For more information on how to assign these to a bg,
    //see the links below.
    ham_InitBg(1,   // The BGs number that you want to Initialize (0-3)
               1,   // 1 = show this BG, 0 = hide this BG
               2,   // Priority of this BG to other BGs (0 = highest prio, 3 = lowest)
               1);  // Enable / Disable Mosaic for this BG (0=off 1=on)
               
               
   // Will, once activated, trigger the specified interrupt,
   // and then call the function specified
   ham_StartIntHandler(INT_TYPE_VBL,         // The Interrupts ID you want to start.
                       (void *)&vblFunc);    // The adress of a function that should be called when the interrupt is fired


   // Draws Text. Be aware that this function is SLOW.
   // It should only be used for debug purposes.
   ham_DrawText(1, 1, "HAM 512 by 512 Map example");
   ham_DrawText(1, 2, "  use pad to scroll around");
            
    // Loop
    while(1)
    {
        // New Frame?
        if(g_NewFrame)
        {
            // Draws Text. Be aware that this function is SLOW.
            // It should only be used for debug purposes.
            ham_DrawText(1,17, "scroll-x: %5d", g_X);
            ham_DrawText(1,18, "scroll-y: %5d", g_Y);

            // Get joypad info and scroll around
            if(F_CTRLINPUT_DOWN_PRESSED ) if(g_Y < (512-160)) g_Y++;
            if(F_CTRLINPUT_UP_PRESSED   ) if(g_Y > 0) g_Y--;
            if(F_CTRLINPUT_LEFT_PRESSED ) if(g_X > 0) g_X--;
            if(F_CTRLINPUT_RIGHT_PRESSED) if(g_X < (512-240)) g_X++;
            
            // Set the Scroll offset of a BG Layer.
            ham_SetBgXY(1,      // The BG number we want to scroll
                        g_X,    // The new X offset value
                        g_Y);   // The new Y offset value
            
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
	// Signify new frame
	g_NewFrame=1;
	g_Frames++;
}

/* END OF FILE */
