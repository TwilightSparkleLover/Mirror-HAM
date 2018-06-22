#include "bgpal.h"

/*
 ***************************************************************************************************
 ***************************************************************************************************
 * Class: CBGPal
 ***************************************************************************************************
 ***************************************************************************************************
*/
/***************************************************************************************************
 *
 * Constructor
 *
 ***************************************************************************************************
 *
*/
CBGPal::CBGPal()
{
    this->Reset();
    
    return;
}
/*
 ***************************************************************************************************
 *
 * Arg:
 *      palette          :   Palette to fade in/out
 *      palette_size     :   Size of palette
 *      delta_per_call   :   Amount to increase of the palette each call
 *
 * Ret:
 *      1   :   Maximal amount reached (255)
 *      0   :   Can still fading
 *
 * Note:
 *      This fades the palette in and out
 *
 ***************************************************************************************************
*/
u8 CBGPal::Splash(u16 *palette, u16 palette_size, s8 delta_per_call)
{
    static u8 s_Mode=0;

    if(0 == s_Mode){
      if(1 == this->In(palette, palette_size, delta_per_call)) s_Mode=1;
    }
    else {
      if(1 == this->Out(palette, palette_size, delta_per_call)){
         s_Mode=0;
         return 1;
      }
    }

    return 0;
}
/*
 ***************************************************************************************************
 *
 * Arg:
 *      palette          :   Palette to fade in/out
 *      palette_size     :   Size of palette
 *      delta_per_call   :   Amount to increase of the palette each call
 *      wait_value       :   Steps to wait before continue with fading out
 *
 * Ret:
 *      1   :   Maximal amount reached (255)
 *      0   :   Can still fading
 *
 * Note:
 *      This function fades the palette in, waits "wait_value" times and fades the palette out
 *
 ***************************************************************************************************
*/
u8 CBGPal::SplashWait(u16 *palette, u16 palette_size, s8 delta_per_call, u16 wait_value)
{
    static u8 s_Mode=0;
    static u16 s_Wait=0;

    if(0 == s_Mode){
      if(1 == this->In(palette, palette_size, delta_per_call)) s_Mode=1;
    }
    else {
      /* Just return when still waiting */
      if(s_Wait++ < wait_value) return 0;
      
      if(1 == this->Out(palette, palette_size, delta_per_call)){
         s_Mode=0;
         s_Wait=0;
         return 1;
      }
    }

    return 0;
}
/*
 ***************************************************************************************************
 *
 * Arg:
 *      palette          :   Palette to fade in
 *      palette_size     :   Size of palette
 *      delta_per_call   :   Amount to increase of the palette each call
 *
 * Ret:
 *      1   :   Maximal amount reached (255)
 *      0   :   Can still fading
 *
 * Note:
 *      If delta_per_call becomes negative (<0) the function will call CBGPal::Out,
 *      since a negative value would mean to invert the fading progress ...
 *
 ***************************************************************************************************
*/
u8 CBGPal::In(u16 *palette, u16 palette_size, s8 delta_per_call)
{
    u16 Idx;
	
	/* Negative delta_per_call means fade out */
	if(delta_per_call < 0)
	 return this->Out(palette, palette_size, delta_per_call*-1);
	 
	/* Maximal value reached? */
	if((m_Value+=delta_per_call) >= 255-delta_per_call)
    {
        return 1;
    }
        	        	
	for(Idx=0; Idx < palette_size; Idx++)
	{
	    u16 Color = palette[Idx];
	
		u8 r = RGB_GET_R_VALUE(Color);
		u8 g = RGB_GET_G_VALUE(Color);
		u8 b = RGB_GET_B_VALUE(Color);
	
        if(m_Value < r){ r = m_Value; }
		if(m_Value < g){ g = m_Value; }
		if(m_Value < b){ b = m_Value; }
			
		ACCESS_16(MEM_PAL_COL_PTR(Idx)) = RGB(r, g, b);
	}
	
	return 0;
}
/*
 ***************************************************************************************************
 *
 * Arg:
 *      palette          :   Palette to fade in
 *      palette_size     :   Size of palette
 *      delta_per_call   :   Amount to decrease of the palette each call
 *
 * Ret:
 *      1   :   Minimal amount reached (255)
 *      0   :   Can still fading
 *
 * Note:
 *      If delta_per_call becomes negative (<0) the function will call CBGPal::In,
 *      since a negative value would mean to invert the fading progress ...
 *
 ***************************************************************************************************
*/
u8 CBGPal::Out(u16 *palette, u16 palette_size, s8 delta_per_call)
{
    u16 Idx;
	
	/* Negative delta_per_call means fade in */
	if(delta_per_call < 0)
	 return this->In(palette, palette_size, delta_per_call*-1);
     	
 	/* Maximal value reached? */
	if((m_Value+=-delta_per_call) < delta_per_call)
    {
        return 1;
    }
        	
	for(Idx=0; Idx < palette_size; Idx++)
	{
	    u16 Color = palette[Idx];
	
		u8 r = RGB_GET_R_VALUE(Color);
		u8 g = RGB_GET_G_VALUE(Color);
		u8 b = RGB_GET_B_VALUE(Color);
	
        if(m_Value < r){ r = m_Value; }
		if(m_Value < g){ g = m_Value; }
		if(m_Value < b){ b = m_Value; }
			
		ACCESS_16(MEM_PAL_COL_PTR(Idx)) = RGB(r, g, b);
	}
	
	return 0;
}
/*
 ***************************************************************************************************
 *
 * Arg:
 *      n/a
 *
 * Ret:
 *      n/a
 *
 * Note:
 *      Inverts the colors of the background palette (256 colors)
 *
 ***************************************************************************************************
*/
void CBGPal::Invert(void)
{
    u16 Idx;
    
	for(Idx=0; Idx < 256; Idx++)
	{
	    u16 Color = ACCESS_16(MEM_PAL_COL_PTR(Idx));

		u8 r = 255-RGB_GET_R_VALUE(Color);
		u8 g = 255-RGB_GET_G_VALUE(Color);
		u8 b = 255-RGB_GET_B_VALUE(Color);
        			
		ACCESS_16(MEM_PAL_COL_PTR(Idx)) = RGB(r, g, b);
	}
	
	return;
}

/*
 ***************************************************************************************************
 *
 * Arg:
 *      from_value  :   Value to start cycling from
 *      to_value    :   Value to cycle to
 *
 * Ret:
 *      n/a
 *
 * Note:
 *      Cycles the palette indices around
 *
 ***************************************************************************************************
*/
void CBGPal::CyclePalette(u16 from_value, u16 to_value)
{
    u16 i;

    // Save the last colorvalue
    ACCESS_16(MEM_PAL_COL_PTR(to_value))=ACCESS_16(MEM_PAL_COL_PTR(from_value));

    // go trough all indices
    for(i=from_value; i<to_value; i++)
    {
        // Swap color of index
        ACCESS_16(MEM_PAL_COL_PTR(i))=ACCESS_16(MEM_PAL_COL_PTR((i+1)));
    }

    return;
}

/*
 ***************************************************************************************************
 *
 * Arg:
 *      n/a
 *
 * Ret:
 *      n/a
 *
 * Note:
 *      Cycles the colors of the background palette
 *
 ***************************************************************************************************
*/
void CBGPal::CyclePaletteColors(u16 from_value, u16 to_value)
{
    u16 Color;
    static u8 s_AddR=1, s_AddG=0, s_AddB=0;
    s16 r, g, b;
    u16 i;

    for(i=from_value; i<to_value; i++)
    {
        // Get the color from the background palette
        Color = ACCESS_16(MEM_PAL_COL_PTR(i));

        // Get Red, Green and Blue values
        r = RGB_GET_R_VALUE(Color);
        g = RGB_GET_G_VALUE(Color);
        b = RGB_GET_B_VALUE(Color);

        // Increasing color-values
        if(m_Mode)
        {
            if(s_AddR){
                if((r+=m_ColorValCount) > 255){
                    s_AddR=0;
                    s_AddG=1;
                    r=255;
                }
            }

            if(s_AddG){
                if((g+=m_ColorValCount) > 255){
                    s_AddG=0;
                    s_AddB=1;
                    g=255;
                }
            }

            if(s_AddB){
                if((b+=m_ColorValCount) > 255){
                    s_AddB=0;
                    s_AddG=1;
                    m_Mode=0;
                    b=255;
                }
            }
        }
        // Decreasing color-values
        else {
            if(s_AddR){
                if((r-=m_ColorValCount) < 1){
                    s_AddR=0;
                    s_AddB=1;
                    r=0;
                }
            }
            if(s_AddG){
                if((g-=m_ColorValCount) < 1){
                    s_AddG=0;
                    s_AddR=1;
                    g=0;
                }
            }
            if(s_AddB){
                if((b-=m_ColorValCount) < 1){
                    s_AddB=0;
                    s_AddR=1;
                    m_Mode=1;
                    b=0;
                }
            }
        }

        // Store new color value in background palette
        ACCESS_16(MEM_PAL_COL_PTR(i)) = RGB(r, g, b);
    }

    return;
}
/* END OF FILE */


