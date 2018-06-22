#include "mygba.h"


#include "gfx/master.pal.c"
#include "gfx/isle.raw.c"
#include "gfx/isle.map.c"

MULTIBOOT

/*
----------------------------------
 Program entry point
----------------------------------
*/

u8 newframe=0;
u8 frames=0;
u16 my_x=0;
u16 my_y=0;

void hblFunc()
{
	//signify new frame
	newframe=1;
	frames++;
}

int main(void)
{

	map_fragment_info_ptr mymap;

    // initialize HAMlib
    ham_Init();
    // set the new BGMode
    ham_SetBgMode(0);
    // init the Text display system on bg of choice
    ham_InitText(0);
	// init the Palettes for Sprite and BG Text
	ham_LoadBGPal(&Master_Palette,sizeof(Master_Palette));

	// set the Text Color
	ham_SetTextCol(0x2,0x5);

	// load the tileset
	ham_bg[1].ti = ham_InitTileSet(&isle_Tiles,SIZEOF_16BIT(isle_Tiles),1,1);
	// init an empty map
	ham_bg[1].mi = ham_InitMapEmptySet(3,0);

	// make a reference to Map data in the ROM
	mymap = ham_InitMapFragment(&isle_Map,64,64,0,0,64,64,0);

	// copy (in this case the whole) map to BG1 at x=0 y=0
	ham_InsertMapFragment(mymap,1,0,0);
	
	// and get it on screen
	ham_InitBg(1,1,2,0);

    // start hblFunc every frame
    ham_StartIntHandler(INT_TYPE_VBL,&hblFunc);

    while(1)
    {
		if(newframe)
		{
			// write some stuff
			ham_DrawText(1,1,"HAM 512 by 512 Map example");
			ham_DrawText(1,2,"  use pad to scroll around");

			ham_DrawText(1,17,"scroll-x: %5d",my_x);
			ham_DrawText(1,18,"scroll-y: %5d",my_y);

			// and make people move the map around
			if(F_CTRLINPUT_DOWN_PRESSED)
			{
				if(my_y<(512-160))
					M_BG1SCRLY_SET(my_y++)
			}
			if(F_CTRLINPUT_UP_PRESSED)
			{
				if(my_y>0)
				M_BG1SCRLY_SET(my_y--)
			}
			if(F_CTRLINPUT_LEFT_PRESSED)
			{
				if(my_x>0)
				M_BG1SCRLX_SET(my_x--)
			}
			if(F_CTRLINPUT_RIGHT_PRESSED)
			{
				if(my_x<(512-240))
				M_BG1SCRLX_SET(my_x++)
			}
			newframe=0;
		}

    }    
}


