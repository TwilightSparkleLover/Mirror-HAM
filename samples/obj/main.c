// one include to rule them all
#include "mygba.h"

//the krawall modules
#include "modules.h"

// gfx includes
#include "gfx/master.pal.c"
#include "gfx/balls.raw.c"
#include "gfx/bg.raw.c"
#include "gfx/bg.pal.c"

// some lookup tables for the sprite wobbling
#include "lookups.h"

// you can set this to max 128
//careful with processor time when also playing a mod!
#define NUM_SPRITES 128

/*
----------------------------------
Program entry point
----------------------------------
*/

// this variable will be set to 1 when a new frame is reached
u8 newframe=0;
// this one will count the frames that have elapsed
u32 frames=0;
// this will count up the rotation angle of the background picture
u32 anglecnt=0;
// this will count up the zoom level of the backgournd picture
u32 bgzoomcnt=180;



// this function gets called by the Interrupt handler

void vblFunc()
{
  // rotate and zoom the face
  ham_RotBg(2,anglecnt,120,80,0x100+(SIN_SFP32[bgzoomcnt]));
  // Copy the objs into OAM once per frame
  ham_CopyObjToOAM();
  // Call the Krawall Update function
  kramWorker();
  //signify new frame
  newframe=1;
  frames++;
}

int main(void)
{
	
  u8 i;
  // the array of sprite handles
  u8 mysprite[NUM_SPRITES];
	
	
  // initialize HAMlib
  ham_Init();
  // set the new BGMode
  ham_SetBgMode(4);
  
  //dma the background pic
  TOOL_DMA3_SET(&bg_Bitmap,MEM_BG_PTR,SIZEOF_32BIT(bg_Bitmap),DMA_TRANSFER_32BIT,DMA_STARTAT_NOW)
    
    
  // init the Palettes for Sprite and BG Text
  ham_LoadBGPal(&bg_Palette,SIZEOF_16BIT(bg_Palette));
  ham_LoadObjPal(&master_Palette,SIZEOF_16BIT(master_Palette));
  
  //init sprite 0 with all attributes into handle 0
  mysprite[0] = ham_CreateObj((void*)&balls_Bitmap[0],0,2,OBJ_MODE_NORMAL,1,0,0,0,0,0,0,30,30);
  //init sprite 1 (different colored sprite) into handle 1
  mysprite[1] = ham_CreateObj((void*)&balls_Bitmap[32*32],0,2,OBJ_MODE_NORMAL,1,0,0,0,0,0,0,30,30);
  
  // and clone the others into the sprite handles
  for(i=2;i<NUM_SPRITES;i++)
    {
      mysprite[i]=ham_CloneObj(mysprite[i%2],1,1);
    }
  
  // initialize Krawall
  kragInit(KRAG_INIT_STEREO);

  // initialize Module play
  krapPlay(&mod_dq,KRAP_MODE_LOOP,0);

  // start Krawall interrupt (see Krawall docs for details)
  ham_StartIntHandler(INT_TYPE_TIM1,&kradInterrupt);
  
  // start hblFunc every frame
  ham_StartIntHandler(INT_TYPE_VBL,&vblFunc);
  
  while(1)
    {
      if(newframe)
	{	  
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

	  //update rotation angle
	  if(anglecnt==359)
	      anglecnt=0;
	  else
	      anglecnt++;

	  //update zoom amount
	  if(bgzoomcnt==359)
	      bgzoomcnt=180;
	  else
	      bgzoomcnt++;

	  // show this frame as processed (will be set to 1 in 
	  // vblFunc again)
	  newframe=0;
	}   
    }    
}


