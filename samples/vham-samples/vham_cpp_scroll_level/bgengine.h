/****************************************************************************
 *
 *  Background Scroll Class
 *
 *  This class will only correct work, if you use 8x8 tiles (!)
 *
 *
 *  Version    Date          Author             Log
 *  -------------------------------------------------------------------------
 *  0.0       8.12.02        Peter Schraut      Initial build
 *  0.1      11.12.02        Peter Schraut      Added the routine to be able
 *                                              to scroll to the left.
 *
 ***************************************************************************/
#ifndef BGENGINE_H
#define BGENGINE_H

#include "mygba.h"

/*
 * This describes the count of tiles on the screen
 * "30" because this "engine" is made for 8x8 tiles
 * and 240/8 is 30 :)
*/
#define BGE_START_TILE_COUNT_X   (30)

/*
 * Structure to store several information
 * about the background etc
*/
typedef struct TBackGround
{
    u8 TileWidth;       // Width of one tile
    u8 TileHeight;      // Height of one tile
    
    u16 MapWidth;       // In tiles
    u16 MapHeight;      // In tiles
    
    u8 *pTiles[1];      // Pointer to BG picture
    u16 TilesSize;      // Size of Tiles Bitmap (sizeof(bla))
    u16 *pPalette;      // Pointer to palette
    u16 PaletteSize;    // Size of Palette (sizeof(bla))
    u16 *pMap;          // Pointer to BG Map
    u16 *pColMap;       // Pointer to collision map
    
}TBackGround;
    
    
    
class CBGEngine
{
    private:
        u32                     m_ScrollPosX;           // Current X position in pixel
        u32                     m_ScrollPosXInTiles;    // Current X position in tiles
        u16                     m_StartTileX;           // At which tile we want to start.
        u8                      m_BGNo;                 // What BG layer we use
        TBackGround             m_BackGround;           // Struct that contains several infos about the bg etc
        map_fragment_info_ptr   m_MapFragment;
        u8                      m_AnimateDelay;         // Used to specify how often the bg should be updated/animated
        u8                      m_ChoosenScrollDelay;   // The scrolldelay the programmer choosed
        u8                      m_ActScrollDelay;       // The current reached scroll delay.
                                                        // We have to specify it here, since ScrollLeft/Right using this
                                                        // member variable to be more precise!
        
        /*
         * These functions are for internal purposes only.
         * They increase/descrease every left/right call
        */
        u8  GetActScrollDelay   (void)        { return m_ActScrollDelay; }
        u8  SetActScrollDelay   (u8 value)    { m_ActScrollDelay=value;  }
        
    public:
        /*
         * Returns the current scroll position in pixels
        */
        u32 GetScrollPositionX          (void){ return m_ScrollPosX; }
        /*
         * Returns the current scroll position in tiles
        */
        u32 GetScrollPositionInTiles    (void){ return m_ScrollPosXInTiles; }
        /*
         * Returns the current scroll position in pixels between 0..63
        */
        u8  GetLimitedScrollPositionX   (void){ return m_ScrollPosX&63; }
        /*
         * Returns the background number which this class is assigned to
        */
        u8  GetBgNo                     (void){ return m_BGNo; }
        /*
         * Returns the scroll delay
        */
        u8  GetScrollDelay              (void){ return m_ChoosenScrollDelay; }
        /*
         * Sets the scroll delay
        */
        void SetScrollDelay              (u8 ScrollDelay){ m_ChoosenScrollDelay=ScrollDelay; }
        
        void InitBackGround(u8 bgno, TBackGround bg);
        /*
         * DeInits the background.
         * Free's Tile Information and Map Information from BG
        */
        void DeInit(void);
        /*
         * Scrolls the map to the right and returns the current position in tiles
         * It will stop at the end of the map
        */
        u32 ScrollRight(void);
        /*
         * Scrolls the map to the left and returns the current position in tiles
         * It will stop if it is at the start tiles
        */
        u32 ScrollLeft(void);
        /*
         * "Animates" the map.
         * It only assigned a new tileset. To be more exactly, it will assign
         * the next tileset you specified into the "TBackGround" structure
         * for the tiles.
         * Please keep in mind, that the tiles must in the same order as
         * the other tilesets you specified!!!! Otherwise it will look
         * very weird :)
        */
        void Animate(void);
        /*
         * Set how often, normally in frames, the tileset should become
         * updated (animated).
        */
        void SetAnimateDelay(u8 value) { m_AnimateDelay=value; }
        /*
         * Get the animation delay
        */
        u8   GetAnimateDelay(void) { return m_AnimateDelay; }
};

#endif /* BGENGINE_H */

/* END OF FILE */
