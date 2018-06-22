/*
OBJ anim example
*/

// one include to rule them all
#include "mygba.h"

MULTIBOOT

// sprite palette and graphics include
#include "gfx/monster.raw.c"
#include "gfx/master.pal.c"


/*
----------------------------------
 Program entry point
----------------------------------
*/

// these are the offsets for the different animations in the gfx
#define ANIM_UP 0
#define ANIM_RIGHT 256*3
#define ANIM_DOWN 256*6
#define ANIM_LEFT 256*9

// direction the monster faces
u16 dir_anim=0;

// the counter for the animation frames (0-2)
u8 animcnt=0;
// monster sprite index
u8 monster;

// x pos of the monster
u8  monster_x=110;
// y pos of the monster
u8  monster_y=50;
// when monster moves, this is 1
u8 in_motion=0;

// global frame counter
u32 frames=0;


void queryKeys()
{
	if(F_CTRLINPUT_UP_PRESSED)
	{
		dir_anim= ANIM_UP;
		monster_y--;
		in_motion=1;
		return;
	}

	if(F_CTRLINPUT_DOWN_PRESSED)
	{
		dir_anim= ANIM_DOWN;
		monster_y++;
		in_motion=1;
		return;
	}

	if(F_CTRLINPUT_LEFT_PRESSED)
	{
		dir_anim= ANIM_LEFT;
		monster_x--;
		in_motion=1;
		return;
	}

	if(F_CTRLINPUT_RIGHT_PRESSED)
	{
		dir_anim= ANIM_RIGHT;
		monster_x++;
		in_motion=1;
		return;
	}
}

void redrawMonster()
{
	// update the position
	ham_SetObjX(monster,monster_x);
	ham_SetObjY(monster,monster_y);
}

void vblFunc()
{   
	// only update animation every 5th frame, 
	// and only if the monster is "in motion"
    if(!(frames%5) && in_motion)
    {
		// load new graphics for this sprite
        ham_UpdateObjGfx(monster,(void*)&monster_Bitmap[dir_anim+256*(animcnt%3)]);
        animcnt++;
		in_motion=0;
    }

	// create the monster sprite in hardware
    ham_CopyObjToOAM();
	// query the joypad
	queryKeys();
	// update the monster position
	redrawMonster();
	// and increase the frame counter
	frames++;
}

int main(void)
{

    // initialize HAMlib
    ham_Init();
    ham_InitText(0);
    ham_SetBgMode(1);

	// load the sprite palette
    ham_LoadObjPal(&master_Palette,256);

	// create the sprite
 
    monster = ham_CreateObj((void*)&monster_Bitmap[16*16*0],0,1,OBJ_MODE_NORMAL,1,0,0,0,0,0,0,monster_x,monster_y);

	// draw some stuff
	ham_DrawText(5,10,"ham animated sprites");
	ham_DrawText(4,12,"move around with d pad");

	// start VBL interrupt handler
    ham_StartIntHandler(INT_TYPE_VBL,&vblFunc);

    while(1)
    {
		// loop endless. Interrupted every VBL by the vblFunc function
    }
}


