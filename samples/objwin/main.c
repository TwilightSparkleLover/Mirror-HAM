// one include to rule them all
#include "mygba.h"
// modplayer include
#include "afm.h"

// gfx includes
#include "gfx/master.pal.c"
#include "gfx/balls.raw.c"
#include "gfx/bg.raw.c"
#include "gfx/bg.pal.c"

// some lookup tables for the sprite wobbling
#include "lookups.h"

// you can set this to max 126
#define NUM_SPRITES 80


/*
----------------------------------
 Program entry point
----------------------------------
*/

u8 newframe=0;
u32 frames=0;

// extern holding the mod file
extern const u8* _binary_module_mod_start;


// this function gets called by the Interrupt handler

void vblFunc()
{
	// sync the modplayer
	afm_sync();
	// Copy the objs into OAM once per frame
	ham_CopyObjToOAM();
    // rotate and zoom the face
	ham_RotBg(2,frames%360,120,80,0x100+(SIN_SFP32[180+frames%180]));
	//signify new frame
	newframe=1;
	frames++;
}

int main(void)
{

	u8 i;
	u8 mysprite[NUM_SPRITES];


    // initialize HAMlib
    ham_Init();
    // set the new BGMode
    ham_SetBgMode(4);

	//dma the background pic
	TOOL_DMA1_SET(&bg_Bitmap,MEM_BG_PTR,SIZEOF_32BIT(bg_Bitmap),DMA_TRANSFER_32BIT,DMA_STARTAT_NOW)


	// init the Palettes for Sprite and BG Text
	ham_LoadBGPal(&bg_Palette,SIZEOF_16BIT(bg_Palette));
	ham_LoadObjPal(&master_Palette,SIZEOF_16BIT(master_Palette));

	//init sprite 0 with all attributes
	mysprite[0] = ham_CreateObj((void*)&balls_Bitmap[0],0,2,OBJ_MODE_OBJWINDOW,1,0,0,0,0,0,0,30,30);
	//init sprite 1
	mysprite[1] = ham_CreateObj((void*)&balls_Bitmap[32*32],0,2,OBJ_MODE_OBJWINDOW,1,0,0,0,0,0,0,30,30);

	// and clone the others
	for(i=2;i<NUM_SPRITES;i++)
	{
		mysprite[i]=ham_CloneObj(mysprite[i%2],1,1);
	}

    // this is the ONLY difference to the OBJ example.
    ham_CreateWin(2,30,30,100,100,0x1f,0x1f,0);


	// start the mod player
	afm_install();
	afm_init((u8*)&_binary_module_mod_start);
    afm_sound_param(0x30,1);

	// start hblFunc every frame
    ham_StartIntHandler(INT_TYPE_VBL,&vblFunc);

    while(1)
    {
		if(newframe)
		{
		// update the modplayer once per frame.
		afm_update();
			// when we are in the middle of the screen the time is right
				// for all our updates...
				
				// update the sprite positions.
				for(i=0;i<NUM_SPRITES/2;i++)
				{
					ham_SetObjX(mysprite[i],wobble_x[(frames+(i*2))%120]);
					ham_SetObjY(mysprite[i],wobble_y[(frames+(i*3))%300]);
				}
				for(i=NUM_SPRITES/2;i<NUM_SPRITES;i++)
				{
					ham_SetObjX(mysprite[i],wobble_x[(frames+1400+(i*2))%120]);
					ham_SetObjY(mysprite[i],wobble_y[(frames+1400+(i*2))%300]);
				}
				// show this frame as processed (will be set to 1 in 
				// VBLhandler again)
				newframe=0;
		}

    }    
}


