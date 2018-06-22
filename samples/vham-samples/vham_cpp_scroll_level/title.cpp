#include "title.h"

bool g_bTitleNewFrame=true;

/*****************************************************************************************
    vblTitelFunc(void)
    
 ****************************************************************************************/
void vblTitelFunc(void)
{
    g_bTitleNewFrame=true;
}

/*****************************************************************************************
    ShowTitleLevel(void)
    
*****************************************************************************************/
void ShowTitleLevel(void)
{
    #define LEFT        (0)
    #define RIGHT       (1)
    
    CBGEngine BgEngine;
    
    bool bQuit=false;
    u8   Direction=RIGHT;
    
    /* Init background 1 and init the text system.
       This is actually needed, cause we ran mode 4 before.
    */
    ham_SetBgMode(0);

    /* Init the Background "Engine" */
    BgEngine.InitBackGround(1, g_TitleBg);
 
    /* Start VBL Interrupt */
    ham_StartIntHandler(INT_TYPE_VBL, (void*) &vblTitelFunc);
    
    // Loop
    while(!bQuit)
    {
        if(g_bTitleNewFrame)
        {
            /*
             * This switchs between the direction,
             * in order to scroll the map to the left or to the right
            */
            switch(Direction)
            {
                /* Scroll map to the right */
                case RIGHT:
                            /* Map width reached? Then scroll to the left again */
                            if(g_TitleBg.MapWidth == BgEngine.ScrollRight())
                                Direction = LEFT;
                            break;

                /* Scroll map to the left */
                case LEFT:
                            /* Map start reached? Then scroll to the right */
                            if(BGE_START_TILE_COUNT_X == BgEngine.ScrollLeft())
                                Direction = RIGHT;
                            break;
            }

            g_bTitleNewFrame=false;
        }
    }
    
    /* Stop VBL Interrupt again */
    ham_StopIntHandler(INT_TYPE_VBL);
}
