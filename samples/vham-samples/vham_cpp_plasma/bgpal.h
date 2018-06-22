/*
 * Author: Peter Schraut / www.console-dev.de
 *
*/
#ifndef BGPAL_H
#define BGPAL_H

#include "mygba.h"

/*********************************************************************************
 * Macros
 ********************************************************************************/
#ifndef RGB_GET_R_VALUE
 #define RGB_GET_R_VALUE(rgb)    ((rgb & 0x001f) << 3)
#endif
#ifndef RGB_GET_G_VALUE
 #define RGB_GET_G_VALUE(rgb)    (((rgb >> 5) & 0x001f) << 3)
#endif
#ifndef RGB_GET_B_VALUE
 #define RGB_GET_B_VALUE(rgb)    (((rgb >> 10) & 0x001f) << 3)
#endif


/*********************************************************************************
 * CBGPal
 *
 * Class to handle some fading for the background palette
 *
 ********************************************************************************/
class CBGPal
{
    private:
        u8  m_Value;
        u8  m_Mode;
        u16 m_ColorValCount;
        
    public:
        CBGPal            ();
        void Reset        (void) { m_Value=0; m_Mode=0; m_ColorValCount=8; }
        u8   Splash       (u16 *palette, u16 palette_size, s8 delta_per_call);
        u8   SplashWait   (u16 *palette, u16 palette_size, s8 delta_per_call, u16 wait_value);
        u8   In           (u16 *palette, u16 palette_size, s8 delta_per_call);
        u8   Out          (u16 *palette, u16 palette_size, s8 delta_per_call);
        
        // Special Effects
        void Invert       (void);
        void CyclePalette (u16 from_value, u16 to_value);
        void CyclePaletteColors(u16 from_value, u16 to_value);
};

#endif /* BGPAL_H */


/* END OF FILE */
