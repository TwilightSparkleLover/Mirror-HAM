/*
 * Created by using HAM 2.5
 * Author: Peter Schraut / www.console-dev.de
*/

#ifndef MYPAD_H
#define MYPAD_H

#include "mygba.h"

class CPad
{
   public:
      bool  bA     () { return F_CTRLINPUT_A_PRESSED;        }
      bool  bB     () { return F_CTRLINPUT_B_PRESSED;        }
      bool  bSelect() { return F_CTRLINPUT_SELECT_PRESSED;   }
      bool  bStart () { return F_CTRLINPUT_START_PRESSED;    }
      bool  bR     () { return F_CTRLINPUT_R_PRESSED;        }
      bool  bL     () { return F_CTRLINPUT_L_PRESSED;        }
      bool  bLeft  () { return F_CTRLINPUT_LEFT_PRESSED;     }
      bool  bRight () { return F_CTRLINPUT_RIGHT_PRESSED;    }
      bool  bUp    () { return F_CTRLINPUT_UP_PRESSED;       }
      bool  bDown  () { return F_CTRLINPUT_DOWN_PRESSED;     }   
};

#endif /* MYPAD_H */
