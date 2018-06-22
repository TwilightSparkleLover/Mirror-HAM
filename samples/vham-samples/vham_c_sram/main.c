/*
 * This document has been created by using Visual HAM
 * http://www.console-dev.de
 *
 * Author: Peter Schraut
 *
 * Created for HAM 2.7
 *
 * Note that thes SRAM functions will not work in MULTIBOOT mode, 
 * as there is no cartridge in this case. 
*/
/*********************************************************************************
 * Includes
 ********************************************************************************/
// Basically, first, as on top of all HAM files, the most
// important include is the mygba.h, which contains all the
// macro definitions, and the HAMlib function prototypes.
#include "mygba.h"

// identifier string used for the SRAM load/save functions
#define IDENTIFIER_STRING   "Our Block"

// little custom structure we will
// save later into SRAM
typedef struct TSRAMDataBlock
{
    u32  nStarts;
    char Text[32];
}TSRAMDataBlock;

/*********************************************************************************
 * Program entry point
 ********************************************************************************/
int main(void)
{
    TSRAMDataBlock SRAMBlock;
    
    // Initialize HAMlib
    // Then we call the single most important function of ham, ham_Init .
    // This function must be called first thing when working with HAMlib,
    // because all ham_* functions will only work correctly after this has been called.
    // Behaviour of HAMlib is undefined if you comment this out.
    ham_Init();
    
    // Sets the GBAs BGMode to the value specified in bgno
    ham_SetBgMode(0);
    
    // Init the Text display system on the bg of your choice
    // This function must be called if you want to use HAMlibs text display system.
    // After calling this, you can use ham_DrawText and ham_SetTextCol.
    ham_InitText(0);
    
    //   Set a specific BG palette color to a 15 bit BGR value
    ham_SetBgPalCol(0, COLOR_BLACK);
    ham_SetBgPalCol(1,              // color you want to modify
                    COLOR_LIME);    // BGR color value in GBA color format
    
    // Set the foreground and background color numbers 
    // for the DrawText system
    ham_SetTextCol(1,   // BG color palette entry number of the color 
                        // that should be used for rendering the text itself 
                   0);  // BG color palette entry number of the color that should 
                        // be used for rendering the 8*8 pixel area around the text
    
    
    // Initialize the HAMlib Save RAM Load/Save system.
    // RAM_TYPE_SRAM_256K Will provide 32 kBytes (256 kBit) of 
    // SRAM data storage if available in the ROM
    // As of HAM 2.7 , only SRAM is supported! Choosing EEPROM types will result in malfunction.
    //
    // This function will return
    //      1 if the RAM was loaded correctly, and HAM detected a correct HAM data block
    //      0 if the RAM was left in a previously undefined state. 
    //      HAM created a new data block and deleted all previous allocation assignments
    switch(ham_InitRAM(RAM_TYPE_SRAM_256K))
    {
        // RAM was loaded correctly, and HAM detected a correct HAM data block
        case 1: 
                // Load raw block into custom structure
                ham_LoadRawFromRAM(IDENTIFIER_STRING, // Specify an identifier string for the integer 
                                                      // to be retrieved.
                                   (void*)&SRAMBlock);// pointer to the structure you want to load 
                                                      // the retrieved data into

                                                
                // Draws Text. Be aware that this function is SLOW.
                // It should only be used for debug purposes.
                ham_DrawText(1, 1, "SRAM inited ok");
                ham_DrawText(1, 2, "Started ROM already %d times", SRAMBlock.nStarts++);
                ham_DrawText(1, 4, "Text: %s", SRAMBlock.Text);
                
                // Save custom structure into SRAM
                ham_SaveRawToRAM(IDENTIFIER_STRING,       // Specify an identifier string for the integer 
                                                          // to be retrieved.
                                 (void*)&SRAMBlock,       // pointer to the structure you want to load 
                                                          // the retrieved data into
                                 sizeof(TSRAMDataBlock)); // Length in bytes of the structure to store
        
                break;
        
        // RAM was left in a previously undefined state. 
        // HAM created a new data block and deleted all previous allocation assignments
        case 0: 
                // Draws Text. Be aware that this function is SLOW.
                // It should only be used for debug purposes.        
                ham_DrawText(1, 1, "Created new DATA block");
                
                // Init structure
                SRAMBlock.nStarts = 1;
                memcpy(&SRAMBlock.Text, "Hello SRAM", strlen("Hello SRAM"));
                
                // Save custom structure into SRAM
                ham_SaveRawToRAM(IDENTIFIER_STRING,       // Specify an identifier string for the integer 
                                                          // to be retrieved.
                                 (void*)&SRAMBlock,       // pointer to the structure you want to load 
                                                          // the retrieved data into
                                 sizeof(TSRAMDataBlock)); // Length in bytes of the structure to store
            
                break;
    }

    // Loop forever
    while(1)
    {
        // ...
    }
    
    return 0;
}


/* END OF FILE */
