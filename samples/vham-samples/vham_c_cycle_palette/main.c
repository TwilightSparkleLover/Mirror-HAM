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
// Images
#include "bg.raw.c"
#include "master.pal.c"

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
u8 g_NewFrame=0;
u8 g_Mode=0;

/*********************************************************************************
 * Prototypes
 ********************************************************************************/
void vblFunc(void);
void CycleBGPalette(void);


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

   ham_LoadBGPal((void *)&master_Palette,         // a pointer to the palette data that is to be loaded
                  SIZEOF_16BIT(master_Palette));  // the size of the data in u16 chunks (usually 256)

   // DMA the background picture
   TOOL_DMA1_SET((void *)&bg_Bitmap,
                  MEM_BG_PTR,
                  SIZEOF_32BIT(bg_Bitmap),
                  DMA_TRANSFER_32BIT,
                  DMA_STARTAT_NOW)

   // Will, once activated, trigger the specified interrupt,
   // and then call the function specified
   ham_StartIntHandler(INT_TYPE_VBL, (void*)&vblFunc);
   
   while(1)
   {
       if(g_NewFrame)
       {
           CycleBGPalette();
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
    g_NewFrame=1;
}

/*********************************************************************************
 * CycleBGPalette(void)
 *
 * This will do the palette cycle-stuff
 *
 ********************************************************************************/
void CycleBGPalette(void)
{
    u16 i;
/*
    Output from gfx2gba:

    Saving masterpalette to..: master.pal.c ... ok

    Total files read & converted.:   1
    Colors used before converting: 240
    Colors used after converting.: 187
    Colors saved.................:  53
*/
    #define COLORS_AFTER_CONVERTING 187
    
    
    // Save the last colorvalue
    ACCESS_16(MEM_PAL_COL_PTR(COLORS_AFTER_CONVERTING))=ACCESS_16(MEM_PAL_COL_PTR(1));
    
    // go trough all indices
    for(i=1; i<COLORS_AFTER_CONVERTING; i++)
    {
        // Swap color of index
        ACCESS_16(MEM_PAL_COL_PTR(i))=ACCESS_16(MEM_PAL_COL_PTR((i+1)));
    }

    return;
}
/* END OF FILE */
