#include "scroller.h"

/*
 * SetCharDesc(const TCharDesc CharDesc)
 *
 * Desc: Sets up a CharDescription
 *
 * Note: This needs to be called before you use the Scroll function
*/
void CBaseScroller::SetCharDesc(TCharDesc CharDesc)
{
    m_CharDesc.Width = CharDesc.Width;
    m_CharDesc.Height= CharDesc.Height;
    m_CharDesc.Space = CharDesc.Space;
    m_CharWidthHeight= m_CharDesc.Width*m_CharDesc.Height;
}

/*
 * SetBasePositionXY(u8 BasePosX, u8 BasePosY)
 *
 * Desc: Sets up the x, y Base position of the scroller
 *
 * Note: This is where the scroller will Bases at the first time
         and where a letter will moved to, when it's out of the screen
*/
void CBaseScroller::SetBasePositionXY(u8 BasePosX, u8 BasePosY)
{
    SetBasePositionX(BasePosX);
    SetBasePositionY(BasePosY);
}

void CBaseScroller::SetBasePositionX(u8 BasePosX)
{
    m_BasePositionX = BasePosX;
}

void CBaseScroller::SetBasePositionY(u8 BasePosY)
{
    m_BasePositionY = BasePosY;
}
/*
 * SetCharOrder(char *pCharOrder)
 *
 * Desc: Tells the class where which char is located onto the texture
 *
 * Note: Must be called before you call init !
 *
 *       If you texture looks like this:
 *       A
 *       B
 *       C
 *
 *       You have to set the char order to "ABC", so it knows what char offset is to use
 *
 *******************
 *
 *       If you texture looks like this:
 *       A
 *       C
 *       B
 *
 *       You have to set the char order to "ACB" !
 *
*/
void CBaseScroller::SetCharOrder(char *pCharOrder)
{
    m_pCharOrder = pCharOrder;
}

/*
 * CalcCharAddress(char Char)
 *
 * Desc: Calculates the offset of a char within the texture
 *
 * Note: This means how many pixels are before the beginning of this char
*/
inline u32 CBaseScroller::CalcCharAddress(char Char)
{
    u16 i=0;
    char *pC = &m_pCharOrder[0];
    
    //for(i=0; i<strlen(pC); i++)
    while(*pC)
    {
      if(Char == *pC++) break;
      i++;
    }

     //return (m_CharDesc.Width * m_CharDesc.Height) * i;
     return m_CharWidthHeight * i;
}

/*
 * SetText(char *pText)
 *
 * Desc: Sets the text you specified and will then show it as scroller later on
 *
 * Note: n/a
*/
void CBaseScroller::SetText(char *pText)
{
    m_pText = pText;
}


/*
 * SetRawSource(u8 *pRawSource)
 *
 * Desc: Sets the bitmap font texture address
 *
 * Note: n/a
*/
void CBaseScroller::SetRawSource(u8 *pRawSource)
{
    m_pRawSource = pRawSource;
}

void CBaseScroller::InitCharSet(TScrollDesc ScrollDesc)
{
    m_ActCharPos = 0;
    
    this->SetBasePositionXY    (ScrollDesc.BasePositionX, ScrollDesc.BasePositionY);
    this->SetCharOrder          ((char*)ScrollDesc.pCharOrder);
    this->SetCharDesc           ((TCharDesc)ScrollDesc.CharDesc);
    this->SetText               ((char*)ScrollDesc.pText);
    this->SetRawSource          ((u8*)ScrollDesc.pRawSource);
}

/*
 * CreateSprites(u8 ObjShape, u8 ObjSize)
 *
 * Desc: Creates sprites for the scroller!
 *
*/
void CBaseScroller::CreateSprites(u8 ObjShape, u8 ObjSize)
{
    u16 i;
    
    for(i=0; i<(240/m_CharDesc.Width)+2; i++)
    {
        m_Sprites[i].X     = m_BasePositionX + (i * m_CharDesc.Width);
        m_Sprites[i].Y     = m_BasePositionY;
        
        m_Sprites[i].ObjNo = ham_CreateObj((void*)&m_pRawSource[CalcCharAddress(m_pText[i])], ObjShape, ObjSize, OBJ_MODE_NORMAL, 1, 0, 1, 0, 0, 0, 0, m_Sprites[i].X, m_Sprites[i].Y);
    }
    
    m_ActCharPos+=i;
}

/*
 * DeleteSprites(void)
 *
 * Desc: Deletes previously created sprites again
 *
*/
void CBaseScroller::DeleteSprites(void)
{
    u16 i;

    for(i=0; i<(240/m_CharDesc.Width)+2; i++)
    {
        ham_DeleteObj(m_Sprites[i].ObjNo);
    }
}

/*
 * ScrollRightToLeft(s16 Y)
 *
 * Args: Y is the Y screen position of the scroller
 *
 * Desc: Scrolls the text from right to left
 *
*/
void CBaseScroller::ScrollRightToLeft(s16 Y)
{
    u16 i;

    for(i=0; i<(240/m_CharDesc.Width)+2; i++)
    {
        if(m_Sprites[i].X-- < 0-m_CharDesc.Width)
        {
            ham_UpdateObjGfx(m_Sprites[i].ObjNo, (void*)&m_pRawSource[CalcCharAddress(m_pText[m_ActCharPos])]);
            if(m_ActCharPos++ > strlen(m_pText)) m_ActCharPos=0;
            m_Sprites[i].X = m_BasePositionX + m_CharDesc.Width;
        }

        ham_SetObjXY(m_Sprites[i].ObjNo, m_Sprites[i].X, Y);
    }
}

/*
 * ScrollRightToLeftSine(s16 *pSineTable, u16 CountWrap, u8 MulFactor, s16 Y)
 *
 * Args:
 *       pSineTable     :       Pointer to a sinewave-table
 *       CountWrap      :       The sinetable position where we want to start again
 *       MulFactor      :       Factor for multiplication. play with it :p
 *       Y              :       Base Y position
 *
 * Desc: Scrolls the text from right to left
 *
*/
void CBaseScroller::ScrollRightToLeftSine(s16 *pSineTable, u16 CountWrap, u8 MulFactor, s16 Y)
{
    u16 i;
    static u16 s_Counter=0;
    
    if (++s_Counter > CountWrap) s_Counter=0;
    
    for(i=0; i<(240/m_CharDesc.Width)+2; i++)
    {
        if(m_Sprites[i].X-- < 0-m_CharDesc.Width)
        {
            ham_UpdateObjGfx(m_Sprites[i].ObjNo, (void*)&m_pRawSource[CalcCharAddress(m_pText[m_ActCharPos])]);
            if(m_ActCharPos++ > strlen(m_pText)) m_ActCharPos=0;
            m_Sprites[i].X = m_BasePositionX + m_CharDesc.Width;
        }

        m_Sprites[i].Y = Y + pSineTable[s_Counter+(i*MulFactor)];
        ham_SetObjXY(m_Sprites[i].ObjNo, m_Sprites[i].X, m_Sprites[i].Y);
    }
}

/* END OF FILE */
