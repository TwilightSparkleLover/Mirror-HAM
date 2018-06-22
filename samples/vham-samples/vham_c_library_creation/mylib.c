#include "mylib.h"

/*
 * It doesnt matter if this makes no sense yet, it's only an example ;-)
*/
void mylib_PrintHelloWorld(void)
{
    // Draws Text. Be aware that this function is SLOW.
    // It should only be used for debug purposes.
    ham_DrawText(1, 1, "hello world");
    ham_DrawText(1, 2, "i am the library");
}
