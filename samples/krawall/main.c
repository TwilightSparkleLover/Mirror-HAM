#include "mygba.h"
#include "modules.h"

u32 gframes=0;
u32 gnewframe=0;

void vbl()
{
	kramWorker();
	gnewframe=1;
}

int main(void)
{
  u32 now_playing=0xff;

  // initialize HAMlib
  ham_Init();
  ham_InitText(0);
  
  // lets draw some text
  ham_DrawText(7,2 ,"ham krawall demo");
  ham_DrawText(7,4 ,"  press a key");
  ham_DrawText(1,9, "UP      aqua.s3m");
  ham_DrawText(1,10,"DOWN    autonomus.s3m");
  ham_DrawText(1,11,"LEFT    ctgoblin.s3m");
  ham_DrawText(1,12,"RIGHT   explorat.s3m");
  ham_DrawText(1,13,"A       gmotion.s3m");
  ham_DrawText(1,14,"B       inspiration.s3m");
  
  kragInit(KRAG_INIT_STEREO);
  
  ham_StartIntHandler(INT_TYPE_TIM1,&kradInterrupt);
  ham_StartIntHandler(INT_TYPE_VBL,&vbl);
  
  while(1)
    {
      if(gnewframe)
	{
	  if(F_CTRLINPUT_UP_PRESSED && (now_playing!=0))
	    {
	      now_playing=0;
	      krapPlay(&mod_aqua,KRAP_MODE_LOOP,now_playing);
	    }
	  if(F_CTRLINPUT_DOWN_PRESSED && (now_playing!=1))
	    {
	      now_playing=1;
	      krapPlay(&mod_autonomus,KRAP_MODE_LOOP,now_playing);
	    }
	  if(F_CTRLINPUT_LEFT_PRESSED && (now_playing!=2))
	    {
	      now_playing=2;
	      krapPlay(&mod_ctgoblin,KRAP_MODE_LOOP,now_playing);
	    }
	  if(F_CTRLINPUT_RIGHT_PRESSED && (now_playing!=3))
	    {
	      now_playing=3;
	      krapPlay(&mod_explorat,KRAP_MODE_LOOP,now_playing);
	    }
	  if(F_CTRLINPUT_A_PRESSED && (now_playing!=4))
	    {
	      now_playing=4;
	      krapPlay(&mod_gmotion,KRAP_MODE_LOOP,now_playing);
	    }
	  if(F_CTRLINPUT_B_PRESSED && (now_playing!=5))
	    {
	      now_playing=5;
	      krapPlay(&mod_inspiration,KRAP_MODE_LOOP,now_playing);
	    }

	  gnewframe=0;
	}
    }    
}


