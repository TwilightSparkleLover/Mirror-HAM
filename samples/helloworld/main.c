#include "mygba.h"

MULTIBOOT


/*
----------------------------------
 Program entry point
----------------------------------
*/

int main(void)
{
    // initialize HAMlib
    ham_Init();

    // init the Text display system on the bg of your choice
    ham_InitText(0);

	// lets draw some text
	ham_DrawText(2,10,"HAMlib text display example");

    while(1)
    {
    }    
}


