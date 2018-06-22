/*
 * Created by using HAM 2.52
 * Author: Peter Schraut / www.console-dev.de
*/

/*********************************************************************************
 * Includes
 ********************************************************************************/
// Basically, first, as on top of all HAM files, the most
// important include is the mygba.h, which contains all the
// macro definitions, and the HAMlib function prototypes.
#include "mygba.h"
// Graphics
#include "gfx/facerot.raw.c"
#include "gfx/facerot.map.c"
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
 * Macros and other defines
 ********************************************************************************/
#ifndef RGB_GET_R_VALUE
 #define RGB_GET_R_VALUE(rgb)    ((rgb & 0x001f) << 3)
#endif
#ifndef RGB_GET_G_VALUE
 #define RGB_GET_G_VALUE(rgb)    (((rgb >> 5) & 0x001f) << 3)
#endif
#ifndef RGB_GET_B_VALUE
 #define RGB_GET_B_VALUE(rgb)    (((rgb >> 10) & 0x001f) << 3)
#endif


/*********************************************************************************
 * Global Variables
 ********************************************************************************/
u8  g_NewFrame=0;
u16 g_Frames=0;
u32 g_Rotangle=0;
u8  g_Delay=0;

/*********************************************************************************
 * Prototypes
 ********************************************************************************/
void vblFunc(void);
void InvertBGPalette(void);

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

    // Will set the color indices of the font to the BG colors specified
    ham_SetTextCol(0x01,    // Set texts front color to the BG palette index specified
                   0x00);   // Set texts back color to the BG palette index specified

    // This function will load a tileset (usually from ROM)
    // from the src pointer and copy it into an appropiate spot
    // in the GBAs BG VRAM. The spot is decided by the memory manager,
    // and passed back in the structure.
    ham_bg[2].ti = ham_InitTileSet( &facerot_Tiles,                 // A pointer to the source data
                                    SIZEOF_16BIT(facerot_Tiles),    // The size of the tiles to be copied into Tile RAM, in number of 16bit chunks
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
    ham_bg[2].mi = ham_InitMapEmptySet(1,   // the size of the map (0-3). This depends on the map_rot parameter!
                                       1);  // determines if this is a map for a rotation screen. (0 = no rotation map, 1 = rotation map)


    // This function will allocate a new structure that can be used
    // to reference the map data (usually in ROM) for rectangle
    // copies onto a map currently on screen.
    BackGroundMap = ham_InitMapFragment((void*)&facerot_Map,        // A pointer to the source data
                                        13,                         // The total width of the map you are pointing to in tiles.
                                        13,                         // The total height of the map you are pointing to in tiles.
                                        0,                          // The horizontal offset, in tiles, on the map you want to start copying from
                                        0,                          // The vertical offset, in tiles, on the map you want to start copying from
                                        13,                         // The number of tiles (from the offset on) you want to specify horizontally
                                        13,                         // The number of tiles (from the offset on) you want to specify vertically
                                        1);                         // 0 = no rotation map, 1 = rotation map


    // This will copy the map from the Map Fragment onto the
    // BG Map currently used by the BG specified at a location
    // the user chooses with the x and y parameters.
    ham_InsertMapFragment(BackGroundMap,    // A map fragment info pointer previously created by ham_InitMapFragment
                          2,                // The BG number you want to Insert the map fragment on (0-3)
                          5,                // The X position (in tiles) in the BG map where you want the Fragment to be placed
                          5);               // The Y position (in tiles) in the BG map where you want the Fragment to be placed


    // You can call this function to actually commit this BG to the hardware.
    // This command will throw an error if the BG that you want to init has not yet
    // been assigned a ti and mi. For more information on how to assign these to a bg,
    //see the links below.
    ham_InitBg(2,   // The BGs number that you want to Initialize (0-3)
               1,   // 1 = show this BG, 0 = hide this BG
               2,   // Priority of this BG to other BGs (0 = highest prio, 3 = lowest)
               1);  // Enable / Disable Mosaic for this BG (0=off 1=on)


    // Set the scrolling values for rotation
    ham_bg[2].x_scroll=90;
    ham_bg[2].y_scroll=100;

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
            // Current Scanline is greater than 50?
            if(F_VCNT_CURRENT_SCANLINE>50)
            {
                // Get joypad input
                if((F_CTRLINPUT_A_PRESSED) && (g_Delay++ > 5))
                {
                    // Invert Palette
                    InvertBGPalette();
                    g_Delay=0;
                }
                
                // Draws Text. Be aware that this function is SLOW.
                // It should only be used for debug purposes.
                ham_DrawText(1, 17, "Press A to invert BG palette");
                ham_DrawText(1, 18, "Graphic by TB himself");

                g_NewFrame=0;
            }
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
    // Rotate and zoom the Background-Map
    ham_RotBg(2,                                // The bg number that is to be rotated (2-3 only since BG1 and 2 can never rotate in the GBA)
              g_Rotangle%360,                   // Angle of rotation
              120,                              // Rotation center x
              80,                               // Rotation center y
              0x100+(SIN_SFP32[g_Frames%360])); // Fixed point number. Normal (no zoom) is 0x100.

    // Signify new frame
    g_NewFrame=1;
    g_Frames++;
    g_Rotangle+=2;
}

/*********************************************************************************
 * InvertBGPalette(void)
 *
 * This will invert each color of the background palette
 ********************************************************************************/
void InvertBGPalette(void)
{
    u16 i;

    // go trough all 256 colors
    for(i=0; i<256; i++)
    {
        // Invert color of index i
        u16 Color = ACCESS_16(MEM_PAL_COL_PTR(i));

        // Calc new R,G,B Values
        u8 R = 255-RGB_GET_R_VALUE(Color);
        u8 G = 255-RGB_GET_G_VALUE(Color);
        u8 B = 255-RGB_GET_B_VALUE(Color);

        // Set new color
        ACCESS_16(MEM_PAL_COL_PTR(i)) = RGB(R, G, B);
    }

    return;
}

/* END OF FILE */
