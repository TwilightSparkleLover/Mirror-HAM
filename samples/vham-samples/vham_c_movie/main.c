/*
 * Created by using HAM 2.6
 * Author: Peter Schraut / www.console-dev.de
 *
 * Graphic downloaded from www.world-in-motion.de
*/

/*********************************************************************************
 * Includes
 ********************************************************************************/
// Basically, first, as on top of all HAM files, the most
// important include is the mygba.h, which contains all the
// macro definitions, and the HAMlib function prototypes.
#include "mygba.h"

// gfx includes
#include "gfxincludes.h"


/*********************************************************************************
 * Structures
 ********************************************************************************/
/*
 * Holds bitmap and palette data
*/
typedef struct TFrame
{
    u8  *pBitmap;
    u16 *pPalette;
}TFrame;
/*
 * Holds count of frames and each bitmap and palette data
*/
typedef struct TMovie
{
    u16    Delay;
    u32    nFrames;
    TFrame Frames[];
}TMovie;


/*********************************************************************************
 * Global Variables and Constants
 ********************************************************************************/
const TMovie g_Movie = {
    8,
    20,
    {{(u8*)&Frame001_Bitmap, (u16*)&master_Palette},
     {(u8*)&Frame002_Bitmap, (u16*)&master_Palette},
     {(u8*)&Frame003_Bitmap, (u16*)&master_Palette},
     {(u8*)&Frame004_Bitmap, (u16*)&master_Palette},
     {(u8*)&Frame005_Bitmap, (u16*)&master_Palette},
     {(u8*)&Frame006_Bitmap, (u16*)&master_Palette},
     {(u8*)&Frame007_Bitmap, (u16*)&master_Palette},
     {(u8*)&Frame006_Bitmap, (u16*)&master_Palette},
     {(u8*)&Frame005_Bitmap, (u16*)&master_Palette},
     {(u8*)&Frame005_Bitmap, (u16*)&master_Palette},
     {(u8*)&Frame005_Bitmap, (u16*)&master_Palette},
     {(u8*)&Frame005_Bitmap, (u16*)&master_Palette},
     {(u8*)&Frame004_Bitmap, (u16*)&master_Palette},
     {(u8*)&Frame003_Bitmap, (u16*)&master_Palette},
     {(u8*)&Frame002_Bitmap, (u16*)&master_Palette},
     {(u8*)&Frame001_Bitmap, (u16*)&master_Palette},
     {(u8*)&Frame001_Bitmap, (u16*)&master_Palette},
     {(u8*)&Frame001_Bitmap, (u16*)&master_Palette},
     {(u8*)&Frame001_Bitmap, (u16*)&master_Palette},
     {(u8*)&Frame001_Bitmap, (u16*)&master_Palette},
     }
};

u8 g_NewFrame=0;



/*********************************************************************************
 * Prototypes
 ********************************************************************************/
u8   PlayMovie(TMovie *pMovie);
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
    
    // Sets the GBAs BGMode to the value specified in bgno
    ham_SetBgMode(4);

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
            // Play "Movie"
            if(PlayMovie((TMovie*)&g_Movie))
            {
                // FLip background buffer
                ham_FlipBGBuffer();
            }
            
            g_NewFrame=0;
        }
    }

    return 0;
}

/*********************************************************************************
 * PlayMovie(TMovie *pMovie)
 *
 * Stores the next "frame" into vram
 * and the palette too
 ********************************************************************************/
u8 PlayMovie(TMovie *pMovie)
{
    static u16 s_Delay=0;
    static u32 s_ActFrame=0;

    if(++s_Delay < pMovie->Delay) return 0;

    s_Delay=0;

    // All frames done?
    if(++s_ActFrame >= pMovie->nFrames)
    {
        s_ActFrame=0;   // Back to beginning
    }

    // Get act frame
    TFrame Frame = pMovie->Frames[s_ActFrame];

    // Store next picture
    ham_LoadBitmap((void*)Frame.pBitmap);

    // Store next palette
    ham_LoadBGPal256((void*)Frame.pPalette);

    return 1;
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

/* END OF FILE */
