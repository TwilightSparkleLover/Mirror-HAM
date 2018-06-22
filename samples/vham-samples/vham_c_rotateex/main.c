/*********************************************************************************
 * Includes
 ********************************************************************************/
// Basically, first, as on top of all HAM files, the most
// important include is the mygba.h, which contains all the
// macro definitions, and the HAMlib function prototypes.
#include "mygba.h"
// Graphics
#include "gfx/logo.raw.c"
#include "gfx/storm.raw.c"
#include "gfx/storm.map.c"
#include "gfx/arrow.raw.c"
#include "gfx/arrow2.raw.c"
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
u32 g_Frames=0;
u16 g_ZoomX=0x100;
u16 g_ZoomY=0x100;
u8  g_NewFrame=0;
u8  g_LogoSpr;
u8  g_CenterSpr;
u8  g_ScrSpr;
u8  g_PosX=120;
u8  g_PosY=80;
u8  g_ScrX=0;
u8  g_ScrY=0;


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
    
    // Init the Text display system on the bg of your choice
    // This function must be called if you want to use HAMlibs text display system.
    // After calling this, you can use ham_DrawText and ham_SetTextCol.
    ham_InitText(0);
    
    // Will set the color indices of the font to the BG colors specified
    ham_SetTextCol(0x07,    // Set texts front color to the BG palette index specified
                   0xff);   // Set texts back color to the BG palette index specified
                   
    // Sets the GBAs BGMode to the value specified in bgno
	ham_SetBgMode(1);


    // Load Background Palette
    ham_LoadBGPal((void *)&master_Palette,         // a pointer to the palette data that is to be loaded
                  SIZEOF_16BIT(master_Palette));   // the size of the data in u16 chunks (usually 256)
                  
    // Load Background Palette
    ham_LoadObjPal((void *)&master_Palette,        // a pointer to the palette data that is to be loaded
                  SIZEOF_16BIT(master_Palette));   // the size of the data in u16 chunks (usually 256)


    // This function will load a tileset (usually from ROM)
    // from the src pointer and copy it into an appropiate spot
    // in the GBAs BG VRAM. The spot is decided by the memory manager,
    // and passed back in the structure.
    ham_bg[2].ti = ham_InitTileSet((void*)&storm_Tiles,             // A pointer to the source data
                                    SIZEOF_16BIT(storm_Tiles),      // The size of the tiles to be copied into Tile RAM, in number of 16bit chunks
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


    // This function will load a map (usually from ROM) from the src pointer and copy
    // it into an appropiate spot in the GBAs BG VRAM.
    // The spot is decided by the memory manager, and passed back in the structure.
	ham_bg[2].mi = ham_InitMapSet((void*)&storm_Map,       // A pointer to the source data
                                  256,                     // Size of the tiles to be copied into BG RAM, in number of 16bit chunks
                                  0,                       // Size of the map (0-3). This depends on the map_rot parameter!
                                  1);                      // Determines if this is a map for a rotation screen.
                                                           // Please make sure that the map data you will load corresponds to
                                                           // the map type you set. (0 = no rotation map, 1 = rotation map)


    // You can call this function to actually commit this BG to the hardware.
    // This command will throw an error if the BG that you want to init has not yet
    // been assigned a ti and mi. For more information on how to assign these to a bg,
    //see the links below.
    ham_InitBg(2,   // The BGs number that you want to Initialize (0-3)
               1,   // 1 = show this BG, 0 = hide this BG
               1,   // Priority of this BG to other BGs (0 = highest prio, 3 = lowest)
               0);  // Enable / Disable Mosaic for this BG (0=off 1=on)
               
               
   // Returns the ham_obj entry which is now associated with the sprite created.
   // Memory for the graphics are automatically allocated and the sprite data is
   //copied. Remember that this does not mean the sprite is comitted to Hardware yet,
   // you need to run ham_CopyObjToOAM for that
   g_LogoSpr = ham_CreateObj((void *)&logo_Tiles,  // A pointer to the tile data for this object
                             1,                       // obj_shape
                             3,                       // obj_size
                             OBJ_MODE_NORMAL,         // obj_mode
                             1,                       // col_mode
                             0,                       // pal_no
                             0,                       // mosaic
                             0,                       // hflip
                             0,                       // vflip
                             0,                       // dbl_size
                             0,                       // prio
                             176,                     // x position of sprite on screen
                             5);                      // y position of sprite on screen
                             
                             
   // Returns the ham_obj entry which is now associated with the sprite created.
   // Memory for the graphics are automatically allocated and the sprite data is
   //copied. Remember that this does not mean the sprite is comitted to Hardware yet,
   // you need to run ham_CopyObjToOAM for that
   g_CenterSpr = ham_CreateObj((void *)&arrow_Tiles,    // A pointer to the tile data for this object
                               1,                       // obj_shape
                               3,                       // obj_size
                               OBJ_MODE_NORMAL,         // obj_mode
                               1,                       // col_mode
                               0,                       // pal_no
                               0,                       // mosaic
                               0,                       // hflip
                               0,                       // vflip
                               0,                       // dbl_size
                               0,                       // prio
                               g_ScrX,                  // x position of sprite on screen
                               g_ScrY);                 // y position of sprite on screen
                             
                             
   // Returns the ham_obj entry which is now associated with the sprite created.
   // Memory for the graphics are automatically allocated and the sprite data is
   //copied. Remember that this does not mean the sprite is comitted to Hardware yet,
   // you need to run ham_CopyObjToOAM for that
   g_ScrSpr = ham_CreateObj((void *)&arrow2_Tiles,    // A pointer to the tile data for this object
                            1,                       // obj_shape
                            3,                       // obj_size
                            OBJ_MODE_NORMAL,         // obj_mode
                            1,                       // col_mode
                            0,                       // pal_no
                            0,                       // mosaic
                            0,                       // hflip
                            0,                       // vflip
                            0,                       // dbl_size
                            0,                       // prio
                            g_PosX,                  // x position of sprite on screen
                            g_PosY);                 // y position of sprite on screen
                               

    // Draws Text. Be aware that this function is SLOW.
    // It should only be used for debug purposes.
    ham_DrawText(1,12,"ham extended rotation example");
    ham_DrawText(1,14,"Pad:   Set Scroll");
    ham_DrawText(1,15,"Pad+A: Set Rot Center");
    ham_DrawText(1,16,"Pad+B: Set Zoom");
    ham_DrawText(1,17,"Start: Reset all");


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
   	        // Increase frame counter
            g_Frames++;
	        
        	// update the arrow positions
        	// Sets the X and Y Position of the Sprite number specified
        	ham_SetObjXY(g_CenterSpr, g_PosX,  g_PosY);
        	ham_SetObjXY(g_ScrSpr,    g_ScrX,  g_ScrY);

            // Draws Text. Be aware that this function is SLOW.
            // It should only be used for debug purposes.
        	ham_DrawText(1, 1, "ZoomX: %4x", g_ZoomX);
        	ham_DrawText(1, 2, "ZoomY: %4x", g_ZoomY);
        	ham_DrawText(1, 3, "PosX : %4x", g_PosX);
        	ham_DrawText(1, 4, "PosY : %4x", g_PosY);
        	ham_DrawText(1, 5, "ScrlX: %4x", g_ScrX);
        	ham_DrawText(1, 6, "ScrlY: %4x", g_ScrY);

            // check the controller and update coordinates
            if(F_CTRLINPUT_A_PRESSED)
            {
                if(F_CTRLINPUT_LEFT_PRESSED ) g_PosX--;
                if(F_CTRLINPUT_RIGHT_PRESSED) g_PosX++;
                if(F_CTRLINPUT_UP_PRESSED   ) g_PosY--;
                if(F_CTRLINPUT_DOWN_PRESSED ) g_PosY++;
            }
            else if(F_CTRLINPUT_B_PRESSED)
            {
                if(F_CTRLINPUT_LEFT_PRESSED ) g_ZoomX--;
                if(F_CTRLINPUT_RIGHT_PRESSED) g_ZoomX++;
                if(F_CTRLINPUT_UP_PRESSED   ) g_ZoomY--;
                if(F_CTRLINPUT_DOWN_PRESSED ) g_ZoomY++;
            }
            else
            {
                if(F_CTRLINPUT_LEFT_PRESSED ) g_ScrX--;
                if(F_CTRLINPUT_RIGHT_PRESSED) g_ScrX++;
                if(F_CTRLINPUT_UP_PRESSED   ) g_ScrY--;
                if(F_CTRLINPUT_DOWN_PRESSED ) g_ScrY++;
            }
            
            // Check if start pressed and reset all values if so
            if(F_CTRLINPUT_START_PRESSED)
            {
                g_ZoomX=0x100;
                g_ZoomY=0x100;
                g_PosX=120;
                g_PosY=80;
                g_ScrX=0;
                g_ScrY=0;
            }
            
            // This is the enhanced version of ham_RotBg.
            // Use this to get finer control over how your BG zooms / rotates.
            // This was added to allow for MarioKart style effects.
            // See the new example source code on this.
            ham_RotBgEx(2,              // The bg number that is to be rotated (2-3 only since BG1 and 2 can never rotate in the GBA)
                        g_Frames%360,   // Angle of rotation
                        g_PosX,         // Rotation center x
                        g_PosY,         // Rotation center y
                        g_ScrX,         // BG scrolling offset x
                        g_ScrY,         // BG scrolling offset y
                        g_ZoomX,        // Fixed point value for zoom in x direction. Default (no zoom) is 0x100.
                        g_ZoomY);       // Fixed point value for zoom in y direction. Default (no zoom) is 0x100.


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
   // Call this (preferably during a VBL interrupt) to commit your
   // ham_obj information to the hardware. Only after you did this your
   // sprite changes will appear on screen.
   ham_CopyObjToOAM();
	
   g_NewFrame=1;
}

/* END OF FILE */
