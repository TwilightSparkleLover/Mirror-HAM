/*
 * Author: Peter Schraut (www.console-dev.de)
 *
 * Created for HAM 2.52+
 *
 * Fake "plasma" effect :P
*/
/*********************************************************************************
 * Includes
 ********************************************************************************/
// Basically, first, as on top of all HAM files, the most
// important include is the mygba.h, which contains all the
// macro definitions, and the HAMlib function prototypes.
#include "mygba.h"
#include "bgpal.h"
#include "sinetable.h"
#include "gfx/bg1.map.c"
#include "gfx/bg1.raw.c"
#include "gfx/part1.pal.c"

/*********************************************************************************
 * Defines
 ********************************************************************************/
#define CYCLE_PALETTE   // undef this line if you dont want to cycle the palette

/*********************************************************************************
 * Global Variables
 ********************************************************************************/
u8      g_CycleDelay=0;
bool    g_NewFrame=false;
u16     g_AngleBG2=0;
CBGPal  g_BGPal;

/*********************************************************************************
 * Prototypes
 ********************************************************************************/
void vblFunc(void);
void hblFunc(void);


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

    // Sets the GBAs BGMode to the value specified in bgno
    ham_SetBgMode(2);

    // Load Background Palette
    ham_LoadBGPal((void *)&part1_Palette,         // a pointer to the palette data that is to be loaded
                  SIZEOF_16BIT(part1_Palette));   // the size of the data in u16 chunks (usually 256)

    // This function will load a tileset (usually from ROM)
    // from the src pointer and copy it into an appropiate spot
    // in the GBAs BG VRAM. The spot is decided by the memory manager,
    // and passed back in the structure.
    ham_bg[2].ti = ham_InitTileSet((void*)&bg1_Tiles,               // A pointer to the source data
                                    SIZEOF_16BIT(bg1_Tiles),        // The size of the tiles to be copied into Tile RAM, in number of 16bit chunks
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
    ham_bg[2].mi = ham_InitMapSet((void*)&bg1_Map,                  // A pointer to the source data, usually in ROM
                                  1024,                             // Size of the map to be copied into BG RAM, in number of 16bit chunks
                                  1,                                // Size of the map (0-3). This depends on the map_rot parameter!
                                  1);                               // Determines if this is a map for a rotation screen, 0 = no rotation map, 1 = rotation map

    // Wrap around display
	M_BG2CNT_WRAP_SET_ON

    // You can call this function to actually commit this BG to the hardware.
    // This command will throw an error if the BG that you want to init has not yet
    // been assigned a ti and mi. For more information on how to assign these to a bg,
    //see the links below.
    ham_InitBg(2,   // The BGs number that you want to Initialize (0-3)
               1,   // 1 = show this BG, 0 = hide this BG
               2,   // Priority of this BG to other BGs (0 = highest prio, 3 = lowest)
               1);  // Enable / Disable Mosaic for this BG (0=off 1=on)
               
               
   // Will, once activated, trigger the specified interrupt,
   // and then call the function specified
   ham_StartIntHandler(INT_TYPE_VBL,         // The Interrupts ID you want to start.
                       (void*) &vblFunc);    // The adress of a function that should be called when the interrupt is fired


   // Will, once activated, trigger the specified interrupt,
   // and then call the function specified
   ham_StartIntHandler(INT_TYPE_HBL,         // The Interrupts ID you want to start.
                       (void*) &hblFunc);    // The adress of a function that should be called when the interrupt is fired
	
	// Loop forever
    while(true)
    {
       // New frame?
       if(g_NewFrame)
       {
           // Increase angle
           g_AngleBG2++;
           
#ifdef CYCLE_PALETTE
           if(++g_CycleDelay > 1)
           {
               // Cycle palette indices
               g_BGPal.CyclePalette(1, 121);
               // Cycle palette colors
               g_BGPal.CyclePaletteColors(12, 32);
               g_CycleDelay=0;
           }
#endif /* CYCLE_PALETTE */

           g_NewFrame=false;
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
    // Signify new frame
    g_NewFrame=true;
}

/*********************************************************************************
 * hblFunc(void)
 *
 * This function is called whenever the GBA has
 * finished to draw a horizontal line onto the screen.
 ********************************************************************************/
void hblFunc(void)
{
    // Rotate / Zoom a BG
    ham_RotBg(2,                                                        // BG number to rotate. Make sure the BG is rotation capable
              (g_AngleBG2+g_Wobble[F_VCNT_CURRENT_SCANLINE])%360,       // Angle to rotate the BG in degrees (0..359)
              120,                                                      // X center of the rotation
               80,                                                      // Y center of the rotation
              256-(g_Wobble[(F_VCNT_CURRENT_SCANLINE+g_AngleBG2)&255])  // Zoom level (default is 0x100 which is 256, means no zoom)
              );
}
/* END OF FILE */
