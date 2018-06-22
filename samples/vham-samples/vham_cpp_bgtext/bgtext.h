/****************************************************************************
 *
 *
 *
 *
 *  Version    Date          Author             Log
 *  -------------------------------------------------------------------------
 *  0.0        12.12.2002    Peter Schraut      Inital Version
 *
 ***************************************************************************/
#ifndef BGTEXT_H
#define BGTEXT_H

#include "mygba.h"
#include "string.h"
#include "stdarg.h"

/*
 * Structure to hold the tile index of a char
*/
typedef struct TCharIndex
{
    char Char;
    u8   Index;
}TCharIndex, *PCharIndex;

/*
 * Structure to hold the entire information we need
 * to control our class
*/
typedef struct TBgTextInfo
{
    u8          BgNo;           // BG we want to use for text output
    u8          TileWidth;      // Width of one tile
    u8          TileHeight;     // Height of one tile
    u8          *pTileData;     // Pointer to tiles data
    u16         TileSize;       // Size of tiles data
    u16         *pPalette;      // Pointer to colorpalette
    s16         PaletteIndex;   // If it's a 16 color palette, -1 = 256 color palette
    u16         PaletteSize;    // Size of palette
    u16         nChars;         // How many entries "pCharIndices" contains
    PCharIndex  pCharIndices;   // Pointer to CharIndex information
    
}TBgTextInfo, *PBgTextInfo;
    
/*
 * Class to display text on a tile-based background.
 *
*/
class CBgText
{
    private:
        TBgTextInfo     m_BgInfo;       // Holds entire bg text information
        u16             m_SpaceIndex;   // Hold the "SPACE" index after initing
        
        /*
         * Scans for the char specified and returns the index
        */
        inline s32      GetTileIndex(char C);
        /*
         * Scans for "SPACE" and returns the index
        */
        s32             GetSpaceIndexFirstTime();
        /*
         * Sets the Background Text Information.
         * Without this, the class can't work
        */
        void            SetTextInfo(TBgTextInfo BgInfo);
        /*
         * Returns the assigned Background Text Infomation
         * what this class is currently using
        */
        TBgTextInfo     GetTextInfo(void){ return m_BgInfo; }
        /*
         * Applies the BgInfo what has become stored by
         * SetTextInfo previously
         * Means this will load the tiles, palette etc
        */
        void            ApplyTextInfo(void);
        
    public:
        /*
         * Prints text
        */
        void            Print(u8 X, u8 Y, char *pText);
        /*
         * Prints text, also parameter list supported
        */
        void            PrintEx(u8 X, u8 Y, char *pText, ...);
        /*
         * Clears prevousily printed text, using the "SPACE" char
        */
        void            Clear(void);
        /*
         * Clears one row, using the "SPACE" char
        */
        void            ClearRow(u8 Row);
        /*
         * Inits the entire textsystem
        */
        void            Init(TBgTextInfo BgInfo);
};


#endif /* BGTEXT_H */


/* END OF FILE */
