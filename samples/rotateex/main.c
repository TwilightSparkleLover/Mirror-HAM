/*
This source demonstrates the use of the ham_RotBgEx 
function in a way that people hopefully will understand ;)

This will compile with HAMlib 2.18 and newer.

*/

//one include to rule them all
#include "mygba.h"

// multiboot. comment this line to run from ROM
MULTIBOOT

// the graphics
#include "gfx/logo.raw.c"
#include "gfx/storm.raw.c"
#include "gfx/storm.map.c"
#include "gfx/arrow.raw.c"
#include "gfx/arrow2.raw.c"
#include "gfx/master.pal.c"

// global variables
u32 frames=0;
u8 logospr,centerspr,scrspr;

u16 zoomx=0x100;
u16 zoomy=0x100;
u8 posx=120;
u8 posy=80;
u8 scrx=0;
u8 scry=0;


void vbl()
{
	// update the arrow positions
	ham_SetObjX(centerspr,posx);
	ham_SetObjY(centerspr,posy);
	ham_SetObjX(scrspr,scrx);
	ham_SetObjY(scrspr,scry);

	//copy the sprites into hardware
	ham_CopyObjToOAM();

	// update the descriptive coordinates
	ham_DrawText(1,1,"zoomx: %4x",zoomx);
	ham_DrawText(1,2,"zoomy: %4x",zoomy);
	ham_DrawText(1,3,"posx:  %4x",posx);
	ham_DrawText(1,4,"posy:  %4x",posy);
	ham_DrawText(1,5,"scrlx: %4x",scrx);
	ham_DrawText(1,6,"scrly: %4x",scry);

	// check the controller and update coordinates
	if(F_CTRLINPUT_A_PRESSED)
	{
		if(F_CTRLINPUT_LEFT_PRESSED)
			posx--;
		if(F_CTRLINPUT_RIGHT_PRESSED)
			posx++;
		if(F_CTRLINPUT_UP_PRESSED)
			posy--;
		if(F_CTRLINPUT_DOWN_PRESSED)
			posy++;
	}
	else if(F_CTRLINPUT_B_PRESSED)
	{
		if(F_CTRLINPUT_LEFT_PRESSED)
			zoomx--;
		if(F_CTRLINPUT_RIGHT_PRESSED)
			zoomx++;
		if(F_CTRLINPUT_UP_PRESSED)
			zoomy--;
		if(F_CTRLINPUT_DOWN_PRESSED)
			zoomy++;
	}
	else
	{
		if(F_CTRLINPUT_LEFT_PRESSED)
			scrx--;
		if(F_CTRLINPUT_RIGHT_PRESSED)
			scrx++;
		if(F_CTRLINPUT_UP_PRESSED)
			scry--;
		if(F_CTRLINPUT_DOWN_PRESSED)
			scry++;
	}
	// check if start pressed and reset all values if so
	if(F_CTRLINPUT_START_PRESSED)
	{
		zoomx=0x100;
		zoomy=0x100;
		posx=120;
		posy=80;
		scrx=0;
		scry=0;
	}
	//rotate the background with the new values.
	ham_RotBgEx(2,frames%360,posx,posy,scrx,scry,zoomx,zoomy);

	//increase frame counter
	frames++;

}

int main(void)
{
	

    // initialize HAMlib
    ham_Init();
	ham_InitText(0);
	ham_SetTextCol(7,0xFF);
	ham_SetBgMode(1);

	// load the color palettes
	ham_LoadBGPal(&master_Palette,256);
	ham_LoadObjPal(&master_Palette,256);

	// initialize the rotating BG
	ham_bg[2].ti = ham_InitTileSet(&storm_Tiles,SIZEOF_16BIT(storm_Tiles),1,1);
	ham_bg[2].mi = ham_InitMapSet(&storm_Map,256,0,1);

	// get the BG onto the screen
	ham_InitBg(2,1,1,0);

	// initialize the sprites (logo and the two arrows)
	logospr		= ham_CreateObj((void*)&logo_Tiles[0],1,3,OBJ_MODE_NORMAL,1,0,0,0,0,0,0,176,5);
	centerspr	= ham_CreateObj((void*)&arrow_Tiles[0],1,3,OBJ_MODE_NORMAL,1,0,0,0,0,0,0,scrx,scry);
	scrspr		= ham_CreateObj((void*)&arrow2_Tiles[0],1,3,OBJ_MODE_NORMAL,1,0,0,0,0,0,0,posx,posy);

	// draw instructions
	ham_DrawText(1,12,"ham extended rotation example");
	ham_DrawText(1,14,"Pad:   Set Scroll");
	ham_DrawText(1,15,"Pad+A: Set Rot Center");
	ham_DrawText(1,16,"Pad+B: Set Zoom");
	ham_DrawText(1,17,"Start: Reset all");


	// start the interrupt handler
	ham_StartIntHandler(INT_TYPE_VBL,&vbl);

    while(1)
    {
		//wait for vbl to happen.
    }    
}


