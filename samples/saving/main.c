// include the header of headers
#include "mygba.h"

int main(void)
{

    //set our values to later be loaded from RAM to intial values
    u32 highscore=0;
    u8 my_Name[22]="";
    u8 my_Street[256]="";
    u8 my_City[64]="";
 
    //Initialize Lib and Text output system
   ham_Init();
   ham_InitText(0);

   //bla
   ham_DrawText(8,2,"Saving Example");
   ham_DrawText(1,4,"Looking for HAM SRAM...");

    //If the RAM is already organized in HAM format...
    if(ham_InitRAM(RAM_TYPE_SRAM_256K))
    {
        //print a success message
        ham_DrawText(3,5,"Found initialized SRAM");
        //and load a previously stored integer
        ham_LoadIntFromRAM("groovy highscore",&highscore);
        //as well as a Raw piece of data, like a string
        ham_LoadRawFromRAM("saved name",my_Name);
        ham_LoadRawFromRAM("saved street",my_Street);
        ham_LoadRawFromRAM("saved city",my_City);
    }
    else
    {
        //RAM was not in HAM format, so it was initialized now.
        //Save the values we want to load later in the next try
        ham_DrawText(3,5,"Re - initialized SRAM");
        ham_SaveIntToRAM("groovy highscore",125644);
        strcpy(my_Name,"Emanuel Schleussinger");
        ham_SaveRawToRAM("saved name",my_Name,22);
        strcpy(my_Street,"a little street...");
        ham_SaveRawToRAM("saved street",my_Street,22);
        strcpy(my_City,"near Munich");
        ham_SaveRawToRAM("saved city",my_City,22);
        strcpy(my_Name,  "                     ");
        strcpy(my_Street,"                     ");
        strcpy(my_City,  "                     ");
    }
   
    ham_DrawText(1,7,"Saved highscore: %d",highscore);
    
    ham_DrawText(1,9,"Saved Name:");
    ham_DrawText(3,10,"%s",my_Name);
    ham_DrawText(1,11,"Saved Street:");
    ham_DrawText(3,12,"%s",my_Street);
    ham_DrawText(1,13,"Saved City:");
    ham_DrawText(3,14,"%s",my_City);

   while(1)
   {
   }
}


/* END OF FILE */
