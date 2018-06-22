#include "mygba.h"

#include "balls.raw.c"
#include "balls.map.c"
#include "engine.raw.c"
#include "engine.map.c"
#include "bg.pal.c"




/*
----------------------------------
 Program entry point
----------------------------------
*/

u32 frames=0,newframe=1;
u32 num_effect=0;
u8 bg2x=0,bg2y=0;

void vbl()
{
    ham_CopyObjToOAM();
    frames++;
    newframe=1;
    ham_SetBgXY(2,bg2x++,bg2y++);

}

int main(void)
{
    
    // initialize HAMlib
    ham_Init();
    ham_InitText(0);
    //switch to simple tile mode
    ham_SetBgMode(0);

    //load the BG palette
    ham_LoadBGPal256(bg_Palette);

    //set up BG 2 with the Balls picture
    ham_bg[2].ti = ham_InitTileSet(balls_Tiles,1088/2,1,1);
    ham_bg[2].mi = ham_InitMapSet(balls_Map,1024,0,0);
    ham_InitBg(2,1,2,0);
    
    //set up BG 3 with the Engine picture
    ham_bg[3].ti = ham_InitTileSet(engine_Tiles,15872/2,1,1);
    ham_bg[3].mi = ham_InitMapSet(engine_Map,1024,0,0);
    ham_InitBg(3,1,1,0);

    //scroll the Engine picture 50 pixels across and down
    ham_SetBgXY(3,10,50);

    //start vbl function every new frame
    ham_StartIntHandler(INT_TYPE_VBL,&vbl);
    
    while(1)
    {
        if(newframe)
        {
           
            switch(num_effect)
            {
                case 0:
                    ham_SetFxMode(  FX_LAYER_SELECT(0,0,0,0,0,0),
                                    FX_LAYER_SELECT(0,0,0,0,0,0),
                                    FX_MODE_OFF);
                    ham_DrawText(1,18,"Original Image             ");
                break;

                case 1:
                    ham_SetFxMode(  FX_LAYER_SELECT(0,0,0,1,0,0),
                                    FX_LAYER_SELECT(0,0,1,0,1,0),
                                    FX_MODE_DARKEN);
                    ham_SetFxBrightnessLevel(8);
                    ham_DrawText(1,18,"Effect: Darken Layers     ");
                break;

                case 2:
                    ham_SetFxMode(  FX_LAYER_SELECT(0,0,0,1,0,0),
                                    FX_LAYER_SELECT(0,0,1,0,1,0),
                                    FX_MODE_LIGHTEN);
                    ham_SetFxBrightnessLevel(8);
                    ham_DrawText(1,18,"Effect: Brighten Layers    ");
                break;

                case 3:
                    ham_SetFxMode(  FX_LAYER_SELECT(0,0,0,1,0,0),
                                    FX_LAYER_SELECT(0,0,1,0,1,0),
                                    FX_MODE_ALPHABLEND);
                    ham_SetFxAlphaLevel(8,8);
                    ham_DrawText(1,18,"Effect: Soft Alpha Blending  ");
                break;
                case 4:
                    ham_SetFxMode(  FX_LAYER_SELECT(0,0,0,1,0,0),
                                    FX_LAYER_SELECT(0,0,1,0,1,0),
                                    FX_MODE_ALPHABLEND);
                    ham_SetFxAlphaLevel(16,16);
                    ham_DrawText(1,18,"Effect: Hard Alpha Blending  ");
                break;

                default:
                break;
            }
            
            //if 150 frames passed
            if(frames%150==0)
            {
                //switch to next effect
                num_effect++;
                if(num_effect>4)
                    num_effect=0;

            }
            //declare frame as done
            newframe=0;
        }
    }    
}


