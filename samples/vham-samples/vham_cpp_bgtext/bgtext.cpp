#include "bgtext.h"

/*
 * Init(TBgTextInfo BgInfo)
 *
 * Inits the Background Text System
*/
void CBgText::Init(TBgTextInfo BgInfo)
{
    this->SetTextInfo   (BgInfo);
    this->ApplyTextInfo ();
}

/*
 * SetTextInfo(TBgTextInfo BgInfo)
 *
 * Copies the Background Text Information in our member variable
 * so we can access every info later on
*/
void CBgText::SetTextInfo(TBgTextInfo BgInfo)
{
    memcpy(&m_BgInfo, &BgInfo, sizeof(TBgTextInfo));
}

/*
 * ApplyTextInfo(void)
 *
 * Inits the entire stuff
 *  - DeInit Tileset, in order to not flood the memory
 *  - Load palette, depending if 16 or 256 colors
 *  - Init a tileset
 *  - Paste an empty mapset
 *  - Get the index of the letter "SPACE"
 *  - Clear the background with "SPACE"
 *  - Activate the background
*/
void CBgText::ApplyTextInfo(void)
{
    u8 ColMode;
    
    /* DeInit Background first, otherwise it could cause
     * that we flood the bg memory
    */
     if(NULL != ham_bg[m_BgInfo.BgNo].ti)
      ham_DeInitTileSet(ham_bg[m_BgInfo.BgNo].ti);
      
    /* Check if this is a 256 color palette.
     * -1 = 256 color, any other value specifies the 16 color palette index
    */
    if(-1 == m_BgInfo.PaletteIndex)
    {
        ham_LoadBGPal256((void*)m_BgInfo.pPalette);
        ColMode = 1;
    }
    /* If its not -1, store it as 16 color palette */
    else {
        ham_LoadBGPal16((void*)m_BgInfo.pPalette, m_BgInfo.PaletteIndex);
        ColMode = 0;
    }
    
    // This function will load a tileset (usually from ROM)
    // from the src pointer and copy it into an appropiate spot
    // in the GBAs BG VRAM. The spot is decided by the memory manager,
    // and passed back in the structure.
    ham_bg[m_BgInfo.BgNo].ti = ham_InitTileSet(m_BgInfo.pTileData,  // A pointer to the source data
                                      m_BgInfo.TileSize,            // The size of the tiles to be copied into Tile RAM, in number of 16bit chunks
                                      ColMode,                      // The Color mode of the tile set (0=16col 1=256col)
                                      1);                           // Setting this one requires a bit of understanding of the GBA hardware.
                                                                    // Basically, if you put tiles into the GBA memory, you will have to put
                                                                    // them at the start of a Character Base block in order to be able to
                                                                    // access tile #0 with a map entry of 0. If the allocated block is not
                                                                    // directly at the start of a CBB, you will have to offset your map entries.
                                                                    // This is automatically done for you when you use ham_SetMapTile.
                                                                    // However, when you load your map from ROM, you might want to align your
                                                                    // tileset to a CBB boundary. If in doubt, and you have some VRAM left, set
                                                                    // this to 1 always.
                                                                    // 0=allocate at the earliest possible spot, unsafe if you do not know / do not
                                                                    // want to offset your map entries!
                                                                    // 1=allocate only on a CBB start to ensure tile 0 is map index no 0.
                                                                    // Again, if you have no idea what this is, set it to 1.

    // This function will create an Empty (all zero) map in the BG RAM,
    // and return a pointer to it via the map_info structure.
    // This empty map can be linked to a BG, or populated by functions like ham_InsertMapFragment
    ham_bg[m_BgInfo.BgNo].mi = ham_InitMapEmptySet(0,   // the size of the map (0-3). This depends on the map_rot parameter!
                                                   0);  // determines if this is a map for a rotation screen. (0 = no rotation map, 1 = rotation map)

    /* Gets the index from a SPACE */
    m_SpaceIndex = GetSpaceIndexFirstTime();
    
    /* Clear background with the SPACE.
       If we dont do this and the first char is NOT a space
       the bg will filled with a non space letter.
       Because its always the first.
    */
    this->Clear();
    
    // You can call this function to actually commit this BG to the hardware.
    // This command will throw an error if the BG that you want to init has not yet
    // been assigned a ti and mi.
    ham_InitBg(m_BgInfo.BgNo,   // The BGs number that you want to Initialize (0-3)
               1,               // 1 = show this BG, 0 = hide this BG
               0,               // Priority of this BG to other BGs (0 = highest prio, 3 = lowest)
               1);              // Enable / Disable Mosaic for this BG (0=off 1=on)
               
}

/*
 * GetSpaceIndexFirstTime()
 *
 * Searchs for the "SPACE" index. Only needed once on init process
*/
s32 CBgText::GetSpaceIndexFirstTime()
{
    u16 i;
    u16 MaxChars=m_BgInfo.nChars;
    s32 Ret=-1;

    /* Scan all chars. This could be done much faster with access
       in an array with the char as index, but needs 256 bytes memory
    */
    for(i=0; i<MaxChars; i++)
    {
        if(' ' == m_BgInfo.pCharIndices[i].Char)
        {
            Ret = m_BgInfo.pCharIndices[i].Index;
            break;
        }
    }

    return Ret;
}

/*
 * GetTileIndex(char C)
 *
 * Searchs for the char and returns the index
*/
inline s32 CBgText::GetTileIndex(char C)
{
    u16 i;
    u16 MaxChars=m_BgInfo.nChars;
    s32 Ret=-1;

    /* If its a space, just return the index :) */
    if(' ' == C) return m_SpaceIndex;

    /* Scan all chars. This could be done much faster with access
       in an array with the char as index, but needs 256 bytes memory
    */
    for(i=0; i<MaxChars; i++)
    {
        if(C == m_BgInfo.pCharIndices[i].Char)
        {
            Ret = m_BgInfo.pCharIndices[i].Index;
            break;
        }
    }

    return Ret;
}

/*
 * PrintEx(u8 X, u8 Y, char *pText, ...)
 *
 * Prints text on the background
 * This function also supports more arguments
*/
void CBgText::PrintEx(u8 X, u8 Y, char *pText, ...)
{
    u8 i, Cnt;
    char Buffer[64];
    va_list Args;

    va_start(Args, pText);
    Cnt = vsprintf(Buffer,  pText, Args);
    
    for(i=0; i<Cnt; i++)
    {
        ham_SetMapTile(m_BgInfo.BgNo, X++, Y, GetTileIndex(Buffer[i]));
    }
}

/*
 * Print(u8 X, u8 Y, char *pText)
 *
 * Simply prints text on the background
*/
void CBgText::Print(u8 X, u8 Y, char *pText)
{
    while(NULL != *pText)
    {
        ham_SetMapTile(m_BgInfo.BgNo, X++, Y, GetTileIndex(*(pText++)));
    }
}

/*
 * ClearRow(u8 Row)
 *
 * Clears row using the "SPACE" letter
*/
void CBgText::ClearRow(u8 Row)
{
    u8  X=0,BgNo=m_BgInfo.BgNo;
    s32 Index=m_SpaceIndex;
    
    ham_SetMapTile(BgNo, X++, Row, Index);
    ham_SetMapTile(BgNo, X++, Row, Index);
    ham_SetMapTile(BgNo, X++, Row, Index);
    ham_SetMapTile(BgNo, X++, Row, Index);
    ham_SetMapTile(BgNo, X++, Row, Index);
    ham_SetMapTile(BgNo, X++, Row, Index);
    ham_SetMapTile(BgNo, X++, Row, Index);
    ham_SetMapTile(BgNo, X++, Row, Index);
    ham_SetMapTile(BgNo, X++, Row, Index);
    ham_SetMapTile(BgNo, X++, Row, Index);
    ham_SetMapTile(BgNo, X++, Row, Index);
    ham_SetMapTile(BgNo, X++, Row, Index);
    ham_SetMapTile(BgNo, X++, Row, Index);
    ham_SetMapTile(BgNo, X++, Row, Index);
    ham_SetMapTile(BgNo, X++, Row, Index);
    ham_SetMapTile(BgNo, X++, Row, Index);
    ham_SetMapTile(BgNo, X++, Row, Index);
    ham_SetMapTile(BgNo, X++, Row, Index);
    ham_SetMapTile(BgNo, X++, Row, Index);
    ham_SetMapTile(BgNo, X++, Row, Index);
    ham_SetMapTile(BgNo, X++, Row, Index);
    ham_SetMapTile(BgNo, X++, Row, Index);
    ham_SetMapTile(BgNo, X++, Row, Index);
    ham_SetMapTile(BgNo, X++, Row, Index);
    ham_SetMapTile(BgNo, X++, Row, Index);
    ham_SetMapTile(BgNo, X++, Row, Index);
    ham_SetMapTile(BgNo, X++, Row, Index);
    ham_SetMapTile(BgNo, X++, Row, Index);
    ham_SetMapTile(BgNo, X++, Row, Index);
    ham_SetMapTile(BgNo, X++, Row, Index);
}

/*
 * Clear(void)
 *
 * Clears the background with the "SPACE" key
*/
void CBgText::Clear(void)
{
    u8 Y;

    for(Y=0; Y<20; Y++)
    {
        ClearRow(Y);
    }
}

/* END OF FILE */
