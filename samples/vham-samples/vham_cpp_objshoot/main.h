#ifndef MAIN_H
#define MAIN_H

// Basically, first, as on top of all HAM files, the most
// important include is the mygba.h, which contains all the
// macro definitions, and the HAMlib function prototypes.
#include "mygba.h"
#include "pad.h"
#include "gfxincludes.h"

/*********************************************************************************
 * Structures
 ********************************************************************************/
#define  HERO_BULLET_MAX    6


/*********************************************************************************
 * Structures
 ********************************************************************************/
typedef struct THeroBullet
{
   u8  ObjNo;
   s16 X, Y;
   s8  Speed;
   u8  Active;
}THeroBullet;

typedef struct THeroShip
{
   u8  ObjNo;
   s16 X, Y;
   s8  Speed;
   u8  nFired;
   THeroBullet Bullets[HERO_BULLET_MAX];
}THeroShip;


/*********************************************************************************
 * Globals
 ********************************************************************************/
bool g_NewFrame=true;
THeroShip g_HeroShip;
CPad g_Pad;

/*********************************************************************************
 * Prototypes
 ********************************************************************************/
void vblFunc         (void);
void MoveHeroBullets (void);
void QueryKeys       (void);
void SetupHeroBullet (THeroBullet *pBullet, s16 X, s16 Y, u8 Speed, u8 Active);
void CreateHeroGfx   (void);

#endif /* MAIN_H */

/* END OF FILE */
