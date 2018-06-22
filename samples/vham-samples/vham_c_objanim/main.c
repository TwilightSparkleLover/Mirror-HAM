/*********************************************************************************
 * Includes
 ********************************************************************************/
// Basically, first, as on top of all HAM files, the most
// important include is the mygba.h, which contains all the
// macro definitions, and the HAMlib function prototypes.
#include "mygba.h"
// Graphics include
#include "gfx/monster.raw.c"
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
 * Defines
 ********************************************************************************/
#define ANIM_UP     0
#define ANIM_RIGHT  256*3
#define ANIM_DOWN   256*6
#define ANIM_LEFT   256*9


/*********************************************************************************
 * Global Variables
 ********************************************************************************/
u16 g_DirectionAnim=0;  // Direction the monster faces
u8  g_AnimCnt=0;        // Counter for the animation frames (0-2)
u8  g_Monster;          // Monster sprite index
u8  g_MonsterX=110;     // x pos of the g_Monster
u8  g_MonsterY=50;      // y pos of the g_Monster
u8  g_InMotion=0;       // When Monster moves, this is 1
u32 g_Frames=0;         // Global frame counter
u8  g_NewFrame=0;


/*********************************************************************************
 * Prototypes
 ********************************************************************************/
void vblFunc      (void);
void queryKeys    (void);
void redrawMonster(void);


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
    ham_SetBgMode(1);

    // Init the Text display system on the bg of your choice
    // This function must be called if you want to use HAMlibs text display system.
    // After calling this, you can use ham_DrawText and ham_SetTextCol.
    ham_InitText(0);

    // Inits the Palette for the Sprite
    ham_LoadObjPal((void *)&master_Palette,        // a pointer to the palette data that is to be loaded
                   SIZEOF_16BIT(master_Palette));  // the number of the 16 color OBJ (sprite) palette you
                                                   // want to load with the 16 color values at address src.


   // Returns the ham_obj entry which is now associated with the sprite created.
   // Memory for the graphics are automatically allocated and the sprite data is
   //copied. Remember that this does not mean the sprite is comitted to Hardware yet,
   // you need to run ham_CopyObjToOAM for that
   g_Monster = ham_CreateObj((void *)&monster_Bitmap[16*16],  // A pointer to the tile data for this object
                              0,                       // obj_shape
                              1,                       // obj_size
                              OBJ_MODE_NORMAL,      // obj_mode
                              1,                       // col_mode
                              0,                       // pal_no
                              0,                       // mosaic
                              0,                       // hflip
                              0,                       // vflip
                              0,                       // dbl_size
                              0,                       // prio
                              g_MonsterX,              // x position of sprite on screen
                              g_MonsterY);             // y position of sprite on screen

                              
    // Draws Text. Be aware that this function is SLOW.
    // It should only be used for debug purposes.
	ham_DrawText(5, 14, "ham animated sprites");
	ham_DrawText(3, 16, "move around with the pad");

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
            // Only update animation every 5th frame,
            // and only if the Monster is "in motion"
            if(!(g_Frames%5) && g_InMotion)
            {
                // load new graphics for this sprite
                ham_UpdateObjGfx(g_Monster,(void*)&monster_Bitmap[g_DirectionAnim+256*(g_AnimCnt%3)]);
                g_AnimCnt++;
                g_InMotion=0;
            }

            queryKeys    ();    // query the joypad
            redrawMonster();    // update the g_Monster position
            
            g_Frames++;         // Increase the frame counter
            g_NewFrame=0;       // Set new frame to zero again
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

/*********************************************************************************
 * redrawMonster(void)
 *
 * Sets the X and Y position of the Monster
 ********************************************************************************/
void redrawMonster(void)
{
	ham_SetObjXY(g_Monster,     // The sprite number we want to move
                 g_MonsterX,    // x position of the
                 g_MonsterY);   // y position of the sprite
}

/*********************************************************************************
 * queryKeys(void)
 *
 * Get joypad input and set new positions
 ********************************************************************************/
void queryKeys(void)
{
	if(F_CTRLINPUT_UP_PRESSED)
	{
		g_DirectionAnim = ANIM_UP;
		g_MonsterY--;
		g_InMotion=1;
		return;
	}

	if(F_CTRLINPUT_DOWN_PRESSED)
	{
		g_DirectionAnim = ANIM_DOWN;
		g_MonsterY++;
		g_InMotion=1;
		return;
	}

	if(F_CTRLINPUT_LEFT_PRESSED)
	{
		g_DirectionAnim = ANIM_LEFT;
		g_MonsterX--;
		g_InMotion=1;
		return;
	}

	if(F_CTRLINPUT_RIGHT_PRESSED)
	{
		g_DirectionAnim = ANIM_RIGHT;
		g_MonsterX++;
		g_InMotion=1;
		return;
	}
}
