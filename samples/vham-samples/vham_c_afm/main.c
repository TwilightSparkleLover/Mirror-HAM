/*********************************************************************************
 * Includes
 ********************************************************************************/
// Basically, first, as on top of all HAM files, the most
// important include is the mygba.h, which contains all the
// macro definitions, and the HAMlib function prototypes.
#include "mygba.h"
// Include AFM header
#include "afm.h"

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
   
   // Draws Text. Be aware that this function is SLOW.
   // It should only be used for debug purposes.
   ham_DrawText(2,2,"AFM Module Player Example");
   ham_DrawText(2,5,"Listen!");
   ham_DrawText(2,6,"Its already playing...");
   ham_DrawText(2,8,"Song made by TDK");

   // Install player/mixer
   // you must call this function before calling any other of the
   // players routines.
   afm_install();
   
   // init modfile + soundsystem
   // modfile must be a pointer to a standard 4-Channel Protracker Module
   afm_init((unsigned char*)&_binary_module_mod_start);

   // Will, once activated, trigger the specified interrupt,
   // and then call the function specified
   ham_StartIntHandler(INT_TYPE_VBL,         // The Interrupts ID you want to start.
                       (void *)&vblFunc);    // The adress of a function that should be called when the interrupt is fired

   // Loop
   while(1)
   {
       if(g_NewFrame)
       {
           // update player+mixing buffers
           // you must call this once each frame (timing doesnt matter)
           afm_update();
           
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
    // Sync sound DMA
    // you must call this right at the start of vblank (precise timing required)
    afm_sync();
    
    g_NewFrame=1;
}

/* END OF FILE */
