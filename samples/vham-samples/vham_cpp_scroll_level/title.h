/*
 * This document has been created by using Visual HAM
 * http://www.console-dev.de
 *
 * Author: Peter Schraut
 *
*/
#ifndef TITLE_H
#define TITLE_H
/*****************************************************************************************
    S Y S T E M    I N C L U D E S
 ****************************************************************************************/
#include "mygba.h"
#include "bgengine.h"

/*****************************************************************************************
    G R A P H I C    I N C L U D E S
 ****************************************************************************************/
 // The Level has been created with the mapeditor located into the
 // "bin" folder of your Visual HAM installation
#include "gfx\GfxLevel1A.raw.c" // Graphics pixeled by TB himself!
#include "gfx\GfxLevel1A.pal.c"
#include "gfx\GfxLevel1A.map.c" // The map has been created with the MapEditor located in the "bin" folder of Visual HAM

/*****************************************************************************************
    C O N S T A N T E S   &   V A R I A B L E S
 ****************************************************************************************/
const TBackGround g_TitleBg =
{
    8,                                  // Width of one tile
    8,                                  // Height of one tile
    150,                                // Map width In tiles
    20,                                 // Map height In tiles
    {
        (u8*)GfxLevel1A_Tiles,          // Pointer to BG picture/tiles
    },
    sizeof(GfxLevel1A_Tiles),           // Size of Tiles Bitmap (sizeof(bla))
    (u16*)GfxLevel1A_Palette,           // Pointer to palette
    SIZEOF_16BIT(GfxLevel1A_Palette),   // Size of Palette (sizeof(bla))
    (u16*)GfxLevel1A_Map,               // Pointer to BG Map
    NULL                                // Pointer to collision map
};

/*****************************************************************************************
    P R O T O T Y P E S
 ****************************************************************************************/
void ShowTitleLevel(void);

#endif /* TITLE_H */


/* END OF FILE */
