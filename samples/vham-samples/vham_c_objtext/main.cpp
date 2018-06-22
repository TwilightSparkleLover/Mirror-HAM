/*
 * Author: Peter Schraut / www.console-dev.de
 *
 * Needs at least HAM 2.5 to compile!
 *
*/
/*********************************************************************************
 * Includes
 ********************************************************************************/
// Basically, first, as on top of all HAM files, the most
// important include is the mygba.h, which contains all the
// macro definitions, and the HAMlib function prototypes.
#include "mygba.h"
// text scroller class
#include "scroller.h"
// Sinewave
#include "sine.h"
// texture of the font (charset)
#include "gfx/font.raw.c"
// palette
#include "gfx/master.pal.c"


/*********************************************************************************
 * Global Variables
 ********************************************************************************/
bool g_NewFrame=false;


// The scroll text
const char g_ScrollText[] = "   "\
                            "this is a simple example of how to make a text scroller in c++ "\
                            "you will now see which letters this charset supports:    "\
                            "abcdefghijklmnopqrstuvwxyz1234567890()+,!C-:      "\
                            "text restarts                           ";
// Scroll description
const TScrollDesc g_ScrollDesc = {
    (u8*)font_Bitmap,       // Pointer to the font bitmap
    240,                    // X Start position of the text
    100,                    // X Start position of the text
    { 8, 8, 1 },            // Font width, Font height, Space between letters
    "abcdefghijklmnopqrstuvwxyz1234567890()+,!C-:    ",     // Font order
    (char*)g_ScrollText     // Pointer to the scrolltext
};


/*********************************************************************************
 * Prototypes
 ********************************************************************************/
void vblFunc(void);


/*********************************************************************************
 * Program entry point
 ********************************************************************************/
int main(void)
{
    
    // Scroller class
    CBaseScroller *g_pScroll = new CBaseScroller;

   // Initialize HAMlib
   // Then we call the single most important function of ham, ham_Init .
   // This function must be called first thing when working with HAMlib,
   // because all ham_* functions will only work correctly after this has been called.
   // Behaviour of HAMlib is undefined if you comment this out.
   ham_Init();

   // Sets the GBAs BGMode to the value specified
   ham_SetBgMode(1);

   // Init the Text display system on the bg of your choice
   // This function must be called if you want to use HAMlibs text display system.
   // After calling this, you can use ham_DrawText and ham_SetTextCol.
   ham_InitText(0);
    
   // Will set the color indices of the font to the BG colors specified
   ham_SetTextCol(0x01,    // Set texts front color to the BG palette index specified
                  0x02);   // Set texts back color to the BG palette index specified

   // You can call this function to actually commit this BG to the hardware.
   // This command will throw an error if the BG that you want to init has not yet
   // been assigned a ti and mi. For more information on how to assign these to a bg,
   //see the links below.
   ham_InitBg(0,   // The BGs number that you want to Initialize (0-3)
              1,   // 1 = show this BG, 0 = hide this BG
              1,   // Priority of this BG to other BGs (0 = highest prio, 3 = lowest)
              0);  // Enable / Disable Mosaic for this BG (0=off 1=on)
               
   // Draws Text. Be aware that this function is SLOW.
   // It should only be used for debug purposes.
   ham_DrawText(6, 1, "text scroller demo");

   // Sets a RGB color value to the background palette
   TOOL_SET_BG_PAL_256(0,      // Index
                       40,     // R Value
                       0,      // G Value
                       60)     // B Value
   
   // Load the Palette for the Sprite
   ham_LoadObjPal((void*)&master_Palette, 256); // a pointer to the palette data that is to be loaded
    
   // Inits the scroller class
   g_pScroll->InitCharSet(g_ScrollDesc);
   // Creates the font sprites!
   g_pScroll->CreateSprites(OBJ_SIZE_8X8);

   // Will, once activated, trigger the specified interrupt,
   // and then call the function specified
   ham_StartIntHandler(INT_TYPE_VBL,         // The Interrupts ID you want to start.
                       (void*) &vblFunc);    // The adress of a function that should be called when the interrupt is fired

   // Loop forever
   while(true)
   {
       // Its a new frame?
       if(g_NewFrame)
       {
           // Scrolls from right to left
           //g_pScroll->ScrollRightToLeft(100);
           
           // Scrolls from right to left with a sinewave on y axis
           g_pScroll->ScrollRightToLeftSine((s16*)g_SinTabY, 128, 4, 100);
           
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
   // Call this (preferably during a VBL interrupt) to commit your
   // ham_obj information to the hardware. Only after you did this your
   // sprite changes will appear on screen.
   ham_CopyObjToOAM();
    
   g_NewFrame=true;
}
/* END OF FILE */
