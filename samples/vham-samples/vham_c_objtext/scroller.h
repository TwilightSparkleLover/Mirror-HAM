/****************************************************************************
 *
 *
 *  Little Class to make a Text-Scroller
 *
 *
 *  Version    Date          Author             Log
 *  -------------------------------------------------------------------------
 *  Initial   29th Nov 02    Peter Schraut      www.console-dev.de
 *
 ***************************************************************************/
#ifndef SCROLLER_H
#define SCROLLER_H

#include "mygba.h"


/*
 * TCharDesc
 *
 * Description of a char (letter)
*/
typedef struct TCharDesc
{
    u8  Width;      // Describes the width of one letter
    u8  Height;     // Describes the height of one letter
    u8  Space;      // Describes the spaces between two letters
}TCharDesc;


/*
 * TScrollDesc
 *
 * Description of our scroller stuff
*/
typedef struct TScrollDesc
{
    void        *pRawSource;        // Picture (Bitmap) Data
    u8          BasePositionX;
    u8          BasePositionY;
    TCharDesc   CharDesc;
    char        *pCharOrder;
    char        *pText;
}TScrollDesc;


/*
 * TScrollSprite
 *
 * It's used for our sprites
*/
typedef struct TScrollSprite
{
    u8          ObjNo;
    s16         X, Y;
}TScrollSprite;



/*
 * CBaseScroller
 *
 * Simple Class to scroll sprites
 *
 * Sprites are using a 256 color palette!
*/
class CBaseScroller
{
    private:
        u8             *m_pRawSource;
        u8              m_BasePositionX;
        u8              m_BasePositionY;
        TCharDesc       m_CharDesc;
        char            *m_pCharOrder;          // Will hold the char order on the texture
        char            *m_pText;
        TScrollSprite   m_Sprites[(240/8)+2];   // Since 8 pixels is the smallest size (holds 32 objects)
        u16             m_ActCharPos;
        u16             m_CharWidthHeight;

        inline u32      CalcCharAddress         (char Char);
        
    public:
        void            SetCharDesc             (TCharDesc CharDesc);
        void            SetBasePositionXY       (u8 BasePosX, u8 BasePosY);
        void            SetBasePositionX        (u8 BasePosX);
        void            SetBasePositionY        (u8 BasePosY);
        void            SetCharOrder            (char *pCharOrder);
        void            SetText                 (char *pText);
        void            SetRawSource            (u8 *pRawSource);
        
        void            InitCharSet             (TScrollDesc ScrollDesc);
        void            CreateSprites           (u8 ObjShape, u8 ObjSize);
        void            DeleteSprites           (void);
        void            ScrollRightToLeft       (s16 Y);
        void            ScrollRightToLeftSine   (s16 *pSineTable, u16 CountWrap, u8 MulFactor, s16 Y);
};


#endif /* SCROLLER_H */

/* END OF FILE */
