/*
OBJ rotation example
*/

// one include to rule them all
#include "mygba.h"

MULTIBOOT

// sprite palette and graphics include
#include "gfx/monster.raw.c"
#include "gfx/master.pal.c"

//lookup table for sinus effect
#include "lookup.h"

/*
----------------------------------
 Program entry point
----------------------------------
*/

#define NUM_CLONES 127

// the counter for the animation frames (0-2)
u8 animcnt=0;
// monster sprite index
u8 monster;
u8 clones[NUM_CLONES];

// global frame counter
u32 frames=0;



void vblFunc()
{   
    u8 i=0;

	// only update animation every 5th frame, 
	// and only if the monster is "in motion"
    if(!(frames%5))
    {
		// load new graphics for this sprite
        ham_UpdateObjGfx(monster,(void*) &monster_Bitmap[(256*3)+256*(animcnt%3)]);
        animcnt++;
    }

    // set up the 4 rotation sets
    ham_RotObjDefineSet(0, frames%360,                0x100, 0x100);
	ham_RotObjDefineSet(1, (1-(frames<<2))%360,       0x100, 0x100);
	ham_RotObjDefineSet(2, (frames+180)%360,          0x100, 0x100);
	ham_RotObjDefineSet(3, (1-((frames+180)<<3))%360, 0x100, 0x100);
	
	// create the sprites in hardware
    ham_CopyObjToOAM();

    while(i<NUM_CLONES)
    {
        // set the new y positions according to the lookup table
        ham_SetObjY(clones[i],wobble[(i+frames)%256]);

        i++;
    }

	// and increase the frame counter
	frames++;
}

int main(void)
{
    u8 i;

    // initialize HAMlib
    ham_Init();
    ham_InitText(0);
    ham_SetBgMode(1);

	// load the sprite palette
    ham_LoadObjPal(&master_Palette,256);

	// create the sprite
    monster = ham_CreateObj(&monster_Bitmap,0,1,OBJ_MODE_NORMAL,1,0,0,0,0,3,1,20,20);


    //create the clones
    for(i=0;i<NUM_CLONES;i++)
    {
        clones[i] = ham_CloneObj(monster,(i*16)%256,50+((i>>4)*16));
        // make these clones rotation enabled
        ham_SetObjRotEnable(clones[i],1);
        // and assign them to one of the rotation sets
        ham_SetObjRotSetSelect(clones[i],i%4);
        
    }
    ham_SetObjVisible(monster,0);
    
    // draw some stuff
    ham_DrawText(1,15,"HAM sprite anim example");
    ham_DrawText(1,16,"   128 anim-rot sprites");
    ham_DrawText(1,17,"           www.ngine.de");


	// start VBL interrupt handler
    ham_StartIntHandler(INT_TYPE_VBL,&vblFunc);

    while(1)
    {
		// loop endless. Interrupted every VBL by the vblFunc function
    }
}


