#include "bgengine.h"


void CBGEngine::InitBackGround(u8 bgno, TBackGround bg)
{
    m_StartTileX=0;
    m_BackGround = bg;
    m_BGNo = bgno;
    m_ScrollPosX = 0;
    this->SetAnimateDelay(8);
    m_ScrollPosXInTiles=BGE_START_TILE_COUNT_X;
    this->SetScrollDelay(1);
    this->SetActScrollDelay(100);
    
    // Load Background Palette
    ham_LoadBGPal((void *)bg.pPalette,         // a pointer to the palette data that is to be loaded
                  bg.PaletteSize);             // the size of the data in u16 chunks (usually 256)


    // This function will load a tileset (usually from ROM)
    // from the src pointer and copy it into an appropiate spot
    // in the GBAs BG VRAM. The spot is decided by the memory manager,
    // and passed back in the structure.
    ham_bg[bgno].ti = ham_InitTileSet(bg.pTiles[0],                 // A pointer to the source data
                                      bg.TilesSize,                 // The size of the tiles to be copied into Tile RAM, in number of 16bit chunks
                                      1,                            // The Color mode of the tile set (0=16col 1=256col)
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
    ham_bg[bgno].mi = ham_InitMapEmptySet(1,   // the size of the map (0-3). This depends on the map_rot parameter!
                                          0);  // determines if this is a map for a rotation screen. (0 = no rotation map, 1 = rotation map)

    // This function will allocate a new structure that can be used
    // to reference the map data (usually in ROM) for rectangle
    // copies onto a map currently on screen.
    m_MapFragment = ham_InitMapFragment((void*)bg.pMap,             // A pointer to the source data
                                        bg.MapWidth,                // The total width of the map you are pointing to in tiles.
                                        bg.MapHeight,               // The total height of the map you are pointing to in tiles.
                                        0,                          // The horizontal offset, in tiles, on the map you want to start copying from
                                        0,                          // The vertical offset, in tiles, on the map you want to start copying from
                                        32,                         // The number of tiles (from the offset on) you want to specify horizontally
                                        20,                         // The number of tiles (from the offset on) you want to specify vertically
                                        0);                         // 0 = no rotation map, 1 = rotation map

    // This will copy the map from the Map Fragment onto the
    // BG Map currently used by the BG specified at a location
    // the user chooses with the x and y parameters.
    ham_InsertMapFragment(m_MapFragment,    // A map fragment info pointer previously created by ham_InitMapFragment
                          bgno,             // The BG number you want to Insert the map fragment on (0-3)
                          0,                // The X position (in tiles) in the BG map where you want the Fragment to be placed
                          0);               // The Y position (in tiles) in the BG map where you want the Fragment to be placed

    /* Run it once */
    this->ScrollRight();
    this->ScrollLeft ();
    
    // You can call this function to actually commit this BG to the hardware.
    // This command will throw an error if the BG that you want to init has not yet
    // been assigned a ti and mi. For more information on how to assign these to a bg,
    //see the links below.
    ham_InitBg(bgno,    // The BGs number that you want to Initialize (0-3)
               1,       // 1 = show this BG, 0 = hide this BG
               bgno+1,  // Priority of this BG to other BGs (0 = highest prio, 3 = lowest)
               0);      // Enable / Disable Mosaic for this BG (0=off 1=on)
}

void CBGEngine::DeInit(void)
{
    // De-Init BG
    ham_DeInitBg(this->GetBgNo());
}

void CBGEngine::Animate(void)
{
    static u8 actTiles=0;
    static u8 s_AnimateDelay=0;

    if(++s_AnimateDelay > m_AnimateDelay)
    {
        if(++actTiles > 3) actTiles=0;

        // De-Init the tileset first, otherwise the bg memory will getting full
        ham_DeInitTileSet(ham_bg[this->GetBgNo()].ti);
        // Assign new tiles
        ham_bg[this->GetBgNo()].ti = ham_InitTileSet(m_BackGround.pTiles[actTiles], // A pointer to the source data
                                                     m_BackGround.TilesSize,        // The size of the tiles to be copied into Tile RAM, in number of 16bit chunks
                                                     1,                             // The Color mode of the tile set (0=16col 1=256col)
                                                     1);                            // Setting this one requires a bit of understanding of the GBA hardware.
        s_AnimateDelay=0;
    }
}



u32 CBGEngine::ScrollRight(void)
{
    static u16 s_ScrollPosCount=0;

    if(++m_ActScrollDelay < m_ChoosenScrollDelay)
        return this->GetScrollPositionInTiles();

    m_ActScrollDelay=0;
    
    // Make sure we do not scroll more right that the map is !
    if(m_ScrollPosXInTiles < m_BackGround.MapWidth)
    // Check if we have scrolled one tile, so we can copy the next one
    if(s_ScrollPosCount++ >= m_BackGround.TileWidth)
    {
        s_ScrollPosCount=0;
        m_ScrollPosXInTiles++;

        // This function will allocate a new structure that can be used
        // to reference the map data (usually in ROM) for rectangle
        // copies onto a map currently on screen.
        //
        // It will use the current map position and copies just
        // the next column to the screen
        m_MapFragment = ham_InitMapFragment((void*)m_BackGround.pMap,   // A pointer to the source data
                                            m_BackGround.MapWidth,      // The total width of the map you are pointing to in tiles.
                                            m_BackGround.MapHeight,     // The total height of the map you are pointing to in tiles.
                                            m_ScrollPosXInTiles,        // The horizontal offset, in tiles, on the map you want to start copying from
                                            0,                          // The vertical offset, in tiles, on the map you want to start copying from
                                            1,                          // The number of tiles (from the offset on) you want to specify horizontally
                                            20,                         // The number of tiles (from the offset on) you want to specify vertically
                                            0);                         // 0 = no rotation map, 1 = rotation map


        // This will copy the map from the Map Fragment onto the
        // BG Map currently used by the BG specified at a location
        // the user chooses with the x and y parameters.
        //
        // "m_ScrollPosXInTiles&63" because every 64 tiles the background
        // wraps again!
        ham_InsertMapFragment(m_MapFragment,               // A map fragment info pointer previously created by ham_InitMapFragment
                              this->GetBgNo(),             // The BG number you want to Insert the map fragment on (0-3)
                              m_ScrollPosXInTiles&63,      // The X position (in tiles) in the BG map where you want the Fragment to be placed
                              0);                          // The Y position (in tiles) in the BG map where you want the Fragment to be placed

    }
    else m_ScrollPosX++;
    
    // Scroll the background
    // If it will wrap in larger maps, we must use
    // M_BG1SCRLX_SET instead! Or ask emanuel to use "u32" instead of u16
    ham_SetBgXY(this->GetBgNo(), this->GetScrollPositionX(), 0);
    
    // Returns the current position in the map
    return this->GetScrollPositionInTiles();
}


u32 CBGEngine::ScrollLeft(void)
{
    static u16 s_ScrollPosCount=0;

    if(++m_ActScrollDelay < m_ChoosenScrollDelay)
        return this->GetScrollPositionInTiles();

    m_ActScrollDelay=0;

    // Make sure we do not scroll more right that the map is !
    if(m_ScrollPosXInTiles > BGE_START_TILE_COUNT_X)
    // Check if we have scrolled one tile, so we can copy the next one
    if(s_ScrollPosCount++ >= m_BackGround.TileWidth)
    {
        s_ScrollPosCount=0;
        m_ScrollPosXInTiles--;

        // This function will allocate a new structure that can be used
        // to reference the map data (usually in ROM) for rectangle
        // copies onto a map currently on screen.
        //
        // It will use the current map position -32 and copies just
        // the prevous column from the left to the screen
        m_MapFragment = ham_InitMapFragment((void*)m_BackGround.pMap,   // A pointer to the source data
                                            m_BackGround.MapWidth,      // The total width of the map you are pointing to in tiles.
                                            m_BackGround.MapHeight,     // The total height of the map you are pointing to in tiles.
                                            m_ScrollPosXInTiles-32,     // The horizontal offset, in tiles, on the map you want to start copying from
                                            0,                          // The vertical offset, in tiles, on the map you want to start copying from
                                            1,                          // The number of tiles (from the offset on) you want to specify horizontally
                                            20,                         // The number of tiles (from the offset on) you want to specify vertically
                                            0);                         // 0 = no rotation map, 1 = rotation map


        // This will copy the map from the Map Fragment onto the
        // BG Map currently used by the BG specified at a location
        // the user chooses with the x and y parameters.
        //
        // "m_ScrollPosXInTiles&63" because every 64 tiles the background
        // wraps again!
        ham_InsertMapFragment(m_MapFragment,               // A map fragment info pointer previously created by ham_InitMapFragment
                              this->GetBgNo(),             // The BG number you want to Insert the map fragment on (0-3)
                              (32+m_ScrollPosXInTiles)&63,   // The X position (in tiles) in the BG map where you want the Fragment to be placed
                              0);                          // The Y position (in tiles) in the BG map where you want the Fragment to be placed

    }
    else m_ScrollPosX--;

    // Scroll the background
    // If it will wrap in larger maps, we must use
    // M_BG1SCRLX_SET instead! Or ask emanuel to use "u32" instead of u16
    ham_SetBgXY(this->GetBgNo(), this->GetScrollPositionX(), 0);

    // Returns the current position in the map
    return this->GetScrollPositionInTiles();
}

/* END OF FILE */
