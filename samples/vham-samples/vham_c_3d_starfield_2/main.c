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

/*********************************************************************************
 * Structures
 ********************************************************************************/
typedef struct TVector3
{
   s32 x, y, z;
}TVector3, *PVector3;

/*********************************************************************************
 * Defines
 ********************************************************************************/
#define  STAR_MAX    (512)    // How many stars we want to display
#define  STAR_AREA   (4000)   // Specifies the stars area
#define  STAR_MAXZ   (90)     // Max z position of a star
#define  STAR_SPEED  (1)      // Specifies the speed of a star

/*********************************************************************************
 * Global Variables
 ********************************************************************************/
TVector3 g_Star[STAR_MAX];
PVector3 g_pStar=&g_Star[0];
u8 g_NewFrame=1;

/*********************************************************************************
 * Prototypes
 ********************************************************************************/
void ClearScreen(void);
void init3dStarfield(void);
void draw3dStarfield(void);
void vblFunc(void);




/*********************************************************************************
 * Program entry point
 ********************************************************************************/
int main(void)
{
   u16 i=0;

   // Initialize HAMlib
   // Then we call the single most important function of ham, ham_Init .
   // This function must be called first thing when working with HAMlib,
   // because all ham_* functions will only work correctly after this has been called.
   // Behaviour of HAMlib is undefined if you comment this out.
   ham_Init();

   // Sets the GBAs BGMode to the value specified
   // Mode4 = 240 x 160 Pixels (doublebuffered)
   ham_SetBgMode(4);

   // Setup the background platte
   for(i=0; i<256; i++)
   {
      TOOL_SET_BG_PAL_256(i,  // Palette index
                          i,  // Red value
                          i,  // Green value
                          i)  // Blue value
   }

   // Inits the "3d" starfield
   init3dStarfield();

   // Will, once activated, trigger the specified interrupt,
   // and then call the function specified
   ham_StartIntHandler(INT_TYPE_VBL,         // The Interrupts ID you want to start.
                       (void *)&vblFunc);    // The adress of a function that should be called when the interrupt is fired


   // loop 4ever
   while(1)
   {
       // New Frame?
       if(g_NewFrame)
       {
            // Clears the backbuffer
            //ham_ClearBackBuffer(0);
            ClearScreen();
            // Run the starfield
            draw3dStarfield();
            // Flip buffers
            ham_FlipBGBuffer();
            
            g_NewFrame=0;
       }
   }
}

/*********************************************************************************
 * ClearScreen(void)
 *
 * Clears the backbuffer
 * Much faster than the original "ham_ClearBackBuffer" function in HAM 2.52
 ********************************************************************************/
void ClearScreen(void)
{
    u8 i;
    u64 *Addr;

    // Get current buffer
	if(F_DISCNT_BUFSEL_GET)
        Addr = (u64*)MEM_VRAM;
	else
        Addr = (u64*)(MEM_VRAM+0xA000);

    // Clear each scanline
    for(i=0; i < 160; ++i)
    {
        *Addr++ = 0; *Addr++ = 0; *Addr++ = 0; *Addr++ = 0;
        *Addr++ = 0; *Addr++ = 0; *Addr++ = 0; *Addr++ = 0;
        *Addr++ = 0; *Addr++ = 0; *Addr++ = 0; *Addr++ = 0;
        *Addr++ = 0; *Addr++ = 0; *Addr++ = 0; *Addr++ = 0;
        *Addr++ = 0; *Addr++ = 0; *Addr++ = 0; *Addr++ = 0;
        *Addr++ = 0; *Addr++ = 0; *Addr++ = 0; *Addr++ = 0;
        *Addr++ = 0; *Addr++ = 0; *Addr++ = 0; *Addr++ = 0;
        *Addr++ = 0; *Addr++ = 0;
    }
};

/*********************************************************************************
 * init3dStarfield
 *
 ********************************************************************************/
void init3dStarfield(void)
{
   u16 i;

   // Init randomizer
   srand(0x8764321);

   // Init stars
   for(i=0; i<STAR_MAX; i++)
   {
      g_pStar->x  = STAR_AREA - (rand()%STAR_AREA << 1);
      g_pStar->y  = STAR_AREA - (rand()%STAR_AREA << 1);
      g_pStar->z  = 1 + rand()%STAR_MAXZ-1;

      g_pStar++;
   }
}

/*********************************************************************************
 * draw3dStarfield
 *
 ********************************************************************************/
void draw3dStarfield(void)
{
   u16 i;
   s32 x, y;
   u8  col;

   // Pointer to the first star in our array
   g_pStar = &g_Star[0];

   for(i=0; i<STAR_MAX; i++)
   {
      // Star "reached" us?
      if(g_pStar->z < 2)
         g_pStar->z = STAR_MAXZ; // Move back into the screen

      // Calculate x, y coordinates and increase the colorindex
      // depending on z position
      // 120 = Width/2, 80 = Height/2
      x   = (g_pStar->x / g_pStar->z) + (120);  // Calc x position
      y   = (g_pStar->y / g_pStar->z) + (80);   // Calc y position
      col = (g_pStar->z << 1) * -1;             // Calc new color index

      // Move star toward us
      g_pStar->z -= STAR_SPEED;

      // Next star
      g_pStar++;

      // Star is still in visible area?
      if(((x > 0) && (x < GFX_MODE4_WIDTH)) &&
         ((y > 0) && (y < GFX_MODE4_HEIGHT)))
         ham_PutPixel(x, y, col);   // Plott pixel onto screen
                                    // ham_PutPixels writes into the backbuffer
                                    // if you use mode4, as we do!

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
/* www.console-dev.de */

/* END OF FILE */
