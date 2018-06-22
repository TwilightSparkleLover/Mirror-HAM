#include "mygba.h"
#include "afm.h"

#include "gfx/facerot.raw.c"
#include "gfx/facerot.map.c"
#include "gfx/master.pal.c"

MULTIBOOT


/*
----------------------------------
 Program entry point
----------------------------------
*/

u32 frames=0;
u8 newframe=0;
u32 rotangle=0;

// extern holding the mod file
extern const _binary_module_mod_start;


void hblFunc()
{
	// sync the modplayer
	afm_sync();

	// rotate and zoom the face
	ham_RotBg(2,rotangle%360,120,80,0x100+(SIN_SFP32[frames%360]));

	//signify new frame
	newframe=1;
	frames++;
	rotangle+=2;
}
int main(void)
{

	map_fragment_info_ptr theface;

    // initialize HAMlib
    ham_Init();
    // set the new BGMode
    ham_SetBgMode(1);
    // init the Text display system on bg of choice
    ham_InitText(0);

    // load new masterpal for our picture
    ham_LoadBGPal(&Master_Palette,sizeof(Master_Palette));

	// set the font to bright color in the new palette
	ham_SetTextCol(0x54,0x53);

    // set up the tiles for the face
	ham_bg[2].ti = ham_InitTileSet( &facerot_Tiles,                // adress of tile data
                                    SIZEOF_16BIT(facerot_Tiles),   // size of tile data in u16s
                                    1,                           // color mode (0=16col 1=256col)
									1);
	// create an empty map for BG2
	ham_bg[2].mi = ham_InitMapEmptySet(1,1);

	// set up the small map (13*13 tiles)
	theface = ham_InitMapFragment(&facerot_Map,13,13,0,0,13,13,1);

	// copy the map fragment to BG2 at x=5 y=5
	ham_InsertMapFragment(theface,2,5,5);
	

	// get this BG onto screen (BGno,active,priority,mosaic)
    ham_InitBg( 2,1,2,1);

	// set the scrolling values for rotation
	ham_bg[2].x_scroll=100;
	ham_bg[2].y_scroll=100;

	// start the mod player
	afm_install();
	afm_init((u8*)&_binary_module_mod_start);

    // start hblFunc every frame
    ham_StartIntHandler(INT_TYPE_VBL,&hblFunc);

    while(1)
    {
		if(newframe)
		{
			if(F_VCNT_CURRENT_SCANLINE>50)
			{
				//update the modplayer once per frame.
				afm_update();
				//draw some info text
				ham_DrawText(1,1,"frame:%3d",frames);
				ham_DrawText(1,2,"angle:%3d",frames%360);
				ham_DrawText(2,15,"HAMlib bg rotation example");
				newframe=0;
			}
		}

    }    
}


