/*
 * Created for HAM 2.6
 * Author: Peter Schraut / www.console-dev.de
*/

/*********************************************************************************
 * Includes
 ********************************************************************************/
// Basically, first, as on top of all HAM files, the most
// important include is the mygba.h, which contains all the
// macro definitions, and the HAMlib function prototypes.
#include "mygba.h"

// Include the graphic, a 64x64 4bit texture (3 colors)
// Convertet by using gfx2gba
#include "gfx/texture.raw.c"
#include "gfx/master.pal.c"

/*********************************************************************************
 * Structures
 ********************************************************************************/
typedef struct TSprite
{
    u8 ObjNo;
    s16 X, Y;
    s8  SpeedX, SpeedY;
}TSprite;

/*********************************************************************************
 * Defines
 ********************************************************************************/
#define SPRITES_MAX  128

/*********************************************************************************
 * Global Variables
 ********************************************************************************/
TSprite g_SprObj[SPRITES_MAX];
u8 g_NewFrame=0;
u8 g_nObjects=SPRITES_MAX;

/*********************************************************************************
 * Prototypes
 ********************************************************************************/
void vblFunc(void);
void doSprites(void);
void initSprites(void);

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
   ham_SetBgMode(0);

   ham_InitText(0);
   ham_SetTextCol(1, 2);

   // Inits the Palette for the Sprite
   ham_LoadObjPal((void *)&master_Palette,        // a pointer to the palette data that is to be loaded
                   SIZEOF_16BIT(master_Palette)); // the number of the 16 color OBJ (sprite) palette you
                                                  // want to load with the 16 color values at address src.
   initSprites();

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
           ham_DrawText(1,1,"Available objects: %d", ham_GetObjAvailable());
           ham_DrawText(1,2,"-A- to delete an object");
           
           if(F_CTRLINPUT_A_PRESSED)
           {
               if(ham_GetObjAvailable() < 128)
               {
                   ham_DeleteObj(g_SprObj[g_nObjects--].ObjNo);
               }
           }
           
           doSprites();
           g_NewFrame=0;
       }
   }    
}

/*********************************************************************************
 * initSprites(void)
 *
 * Creates some sprites
 ********************************************************************************/
void initSprites(void)
{
   u16 i;
    
   // Init randomizer
   srand(556677);
    
   g_SprObj[0].X = 120-16;
   g_SprObj[0].Y = 80-16;
   g_SprObj[0].SpeedX = 1;
   g_SprObj[0].SpeedY = 2;
   
   // Returns the ham_obj entry which is now associated with the sprite created.
   // Memory for the graphics are automatically allocated and the sprite data is
   //copied. Remember that this does not mean the sprite is comitted to Hardware yet,
   // you need to run ham_CopyObjToOAM for that
   g_SprObj[0].ObjNo = ham_CreateObj((void *)&texture_Bitmap,  // A pointer to the tile data for this object
                             OBJ_SIZE_32X32,          // obj_shape & obj_size
                             OBJ_MODE_NORMAL,         // obj_mode
                             1,                       // col_mode
                             0,                       // pal_no
                             0,                       // mosaic
                             0,                       // hflip
                             0,                       // vflip
                             0,                       // dbl_size
                             0,                       // prio
                             g_SprObj[0].X,                // x position of sprite on screen
                             g_SprObj[0].Y);               // y position of sprite on screen
    
    for(i=1;i < SPRITES_MAX; i++)
    {
        g_SprObj[i].X = 1+rand()%(240-32);
        g_SprObj[i].Y = 32+rand()%(160-32);
        g_SprObj[i].SpeedX = 1+rand()%3;
        g_SprObj[i].SpeedY = 1+rand()%3;
        g_SprObj[i].ObjNo = ham_CloneObj(g_SprObj[0].ObjNo, g_SprObj[i].X, g_SprObj[i].Y);
    }
}

/*********************************************************************************
 * doSprites(void)
 *
 * This function updates the X,Y positions of our sprites
 ********************************************************************************/
void doSprites(void)
{
    u16 i;
    
    for(i=0;i < SPRITES_MAX; i++)
    {
       // Clip sprite
       if ((g_SprObj[i].X > 240-32) || (g_SprObj[i].X < 1)) g_SprObj[i].SpeedX*=-1;
       if ((g_SprObj[i].Y > 160-32) || (g_SprObj[i].Y < 32)) g_SprObj[i].SpeedY*=-1;

       // Calculate new x and y position
       g_SprObj[i].X+=g_SprObj[i].SpeedX;
       g_SprObj[i].Y+=g_SprObj[i].SpeedY;

       // Sets the X and Y Position of the Sprite number specified
       ham_SetObjXY(g_SprObj[i].ObjNo,  // The sprite number we want to move
                    g_SprObj[i].X,  // The x position of the sprite
                    g_SprObj[i].Y); // The y position of the sprite
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

   // Call this (preferably during a VBL interrupt) to commit your 
   // ham_obj information to the hardware. Only after you did this your 
   // sprite changes will appear on screen.          
   ham_CopyObjToOAM();
}

/* END OF FILE */
