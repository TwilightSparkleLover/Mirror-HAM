#ifndef MYLIB_H
#define MYLIB_H

#include "mygba.h"

/*
 * If you add a new function or change/update anything,
 * you must call "make lib" to build a new library!!!
 * Check the makefile to see what's there ...
*/

#ifdef __cplusplus
extern "C" {
#endif

extern void mylib_PrintHelloWorld(void);

#ifdef __cplusplus
}
#endif

#endif /* MYLIB_H */

/* END OF FILE */
