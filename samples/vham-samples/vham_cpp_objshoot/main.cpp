/*********************************************************************************
 * Includes
 ********************************************************************************/
#include "main.h"


/*********************************************************************************
 * Program entry point
 ********************************************************************************/
int main(void)
{
    // Initialize HAMlib
    // Then we call the single most important function of ham, ham_Init .
    // This function must be called first thing when working with HAMlib,
    // because all ham_* functions will only work correctly after this has been called.
    // Behaviour of HAMlib is undefined if you comment this out.
    ham_Init();

    // Sets the GBAs BGMode to the value specified in bgno
    ham_SetBgMode(0);
    
    // Init the Text display system on the bg of your choice
    // This function must be called if you want to use HAMlibs text display system.
    // After calling this, you can use ham_DrawText and ham_SetTextCol.
    ham_InitText(0);
    
    // Will set the color indices of the font to the BG colors specified
    ham_SetTextCol(1,    // Set texts front color to the BG palette index specified
                   0);   // Set texts back color to the BG palette index specified

    // Create GFX for the HeroStarship and bullets
    // Well, the sharship is the white rect ;-)
    CreateHeroGfx();

    // Will, once activated, trigger the specified interrupt,
    // and then call the function specified
    ham_StartIntHandler(INT_TYPE_VBL,         // The Interrupts ID you want to start.
                        (void*) &vblFunc);    // The adress of a function that should be called when the interrupt is fired

    // Loop
    while(true)
    {
        // It's a new frame?
        if(g_NewFrame)
        {
            // Display how many bullets left
            ham_DrawText(3, 1, "Shooting example?");
            ham_DrawText(3, 2, "Bullets left: %d ", HERO_BULLET_MAX-g_HeroShip.nFired);
           
            // Get user input
            QueryKeys();
            
            // Scroll bullets to the right
            MoveHeroBullets();
            
            // Set starship position
            ham_SetObjXY(g_HeroShip.ObjNo, g_HeroShip.X, g_HeroShip.Y);
            
            // Frames isn't new anymore
            g_NewFrame=false;
        }
    }

    return 0;
}

/*****************************************************************************************
 *
 * CreateHeroGfx(void)
 *
 * Whats it do:
 *
 *    Loads Object Palette
 *    Setups the Hero Starship
 *    Creates the HeroStarship sprite
 *    Creates bullet sprites and set them to invsible
 *
 ****************************************************************************************/
void CreateHeroGfx(void)
{
   u8 i;

   ham_LoadObjPal256((void*)&master_Palette);

   g_HeroShip.X = 20;
   g_HeroShip.Y = 80;
   g_HeroShip.Speed  = 1;
   g_HeroShip.nFired = 0;

   // Create the "hero starship", it's just a 32x16 sprite
   g_HeroShip.ObjNo = ham_CreateObj((void*)&GfxHeroShip_Bitmap,  // A pointer to the tile data for this object
                           OBJ_SIZE_32X16,      // obj_shape & obj_size
                           OBJ_MODE_NORMAL,     // obj_mode
                           1,                   // col_mode (1=256 colors)
                           0,                   // pal_no
                           0,                   // mosaic
                           0,                   // hflip
                           0,                   // vflip
                           0,                   // prio
                           0,                   // dbl_size
                           g_HeroShip.X,        // x position of sprite on screen
                           g_HeroShip.Y);       // y position of sprite on screen


   // Create the "hero bullet", it's just a 8X8 sprite
   g_HeroShip.Bullets[0].ObjNo = ham_CreateObj((void*)&GfxHeroBullet_Bitmap,  // A pointer to the tile data for this object
                           OBJ_SIZE_8X8,        // obj_shape & obj_size
                           OBJ_MODE_NORMAL,     // obj_mode
                           1,                   // col_mode (1=256 colors)
                           0,                   // pal_no
                           0,                   // mosaic
                           0,                   // hflip
                           0,                   // vflip
                           0,                   // prio
                           0,                   // dbl_size
                           240,                 // x position of sprite on screen
                           0);                  // y position of sprite on screen

   // Get the object number of the "master" bullet we will clone
   u8 CloneFromNo = g_HeroShip.Bullets[0].ObjNo;
   ham_SetObjVisible(CloneFromNo, FALSE);

   // Loop to clone the bullets
   for(i=1; i<HERO_BULLET_MAX; i++)
   {
      g_HeroShip.Bullets[i].ObjNo = ham_CloneObj(CloneFromNo, 240, 0);
      ham_SetObjVisible(g_HeroShip.Bullets[i].ObjNo, FALSE);
   }
}
/*****************************************************************************************
 *
 * SetupHeroBullet(THeroBullet *pBullet, s16 X, s16 Y, u8 Speed, u8 Active)
 *
 * Args:
 *          pBullet  :  Pointer to THeroBullet structure
 *                      Thats the bullet to "setup"
 *          X        :  X Position of bullet
 *          Y        :  Y Position of bullet
 *          Speed    :  Speed of a the bullet
 *          Active   :  Is the bullet active?
 *
 ****************************************************************************************/
void SetupHeroBullet(THeroBullet *pBullet, s16 X, s16 Y, u8 Speed, u8 Active)
{
   pBullet->X = X;
   pBullet->Y = Y;
   pBullet->Speed = Speed;
   pBullet->Active = Active;

   if(Active)
      ham_SetObjVisible(pBullet->ObjNo, TRUE);
   else
      ham_SetObjVisible(pBullet->ObjNo, FALSE);
}
/*****************************************************************************************
 *
 * QueryKeys(void)
 *
 * Reads pad state. This just means, it checks if button A or B is still pressed
 *
 *
 *
 *
 ****************************************************************************************/
void QueryKeys(void)
{
   u8 i;

   g_Pad.ReadState();

   // FIREEEE ! ;-)
   if(g_Pad.bAPressed())
   {
      // Maximum amount of bullets still to reached?
      if(g_HeroShip.nFired < HERO_BULLET_MAX)
      {
         // Loop through all bullets
         for(i=0; i<HERO_BULLET_MAX; i++)
         {
            // Make sure the bullet is NOT active
            if(!g_HeroShip.Bullets[i].Active)
            {
               // So we can setup it again
               SetupHeroBullet((THeroBullet*)&g_HeroShip.Bullets[i], g_HeroShip.X+24, g_HeroShip.Y+4, 2, TRUE);
               // Increase amount of bullets
               g_HeroShip.nFired++;
               break;
            }
         }
      }
   }

   // Move starship up
   if(g_Pad.bUp())
   {
      if(g_HeroShip.Y > 0) g_HeroShip.Y--;
   }

   // Move starship down
   if(g_Pad.bDown())
   {
      if(g_HeroShip.Y < 160-16) g_HeroShip.Y++;
   }
}

/*****************************************************************************************
 *
 * MoveHeroBullets(void)
 *
 *
 ****************************************************************************************/
void MoveHeroBullets(void)
{
   u8 i;
   THeroBullet *Ptr=NULL;

   // Loop through all bullets
   for(i=0; i<HERO_BULLET_MAX; i++)
   {
      Ptr = (THeroBullet*)&g_HeroShip.Bullets[i];

      // Make sure this one is active
      if(Ptr->Active)
      {
         // Does it "hit" the end?
         if((Ptr->X+=Ptr->Speed) > 240)
         {
            // Setup bullet (make invisible)
            SetupHeroBullet(Ptr, 240, 0, 1, FALSE);
            // Decrease amount of fired bullets
            g_HeroShip.nFired--;
         }
         else
            // Bullet is active, so move it to the right
            ham_SetObjXY(Ptr->ObjNo, Ptr->X, Ptr->Y);
      }
   }
}

/*********************************************************************************
 * vblFunc(void)
 *
 * This function is called whenever the GBA is about
 * to draw a new picture onto the screen.
 ********************************************************************************/
void vblFunc(void)
{
    // Call this (preferably during a VBL interrupt) to commit your
    // ham_obj information to the hardware. Only after you did this your
    // sprite changes will appear on screen.
    ham_CopyObjToOAM();

    // It's a new frame yet
    g_NewFrame=true;
}
/* END OF FILE */
