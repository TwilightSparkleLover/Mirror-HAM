/*
 * This document has been created by using Visual HAM
 * http://www.console-dev.de
 *
 * Author: Peter Schraut
*/
#ifndef PAD_H
#define PAD_H

#include "mygba.h"

class CPad
{
   private:
      bool    m_bIdle;
      
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

      void  ReadState      () { if(bIdle())m_bIdle=true;     }
      bool  bAPressed      () { if((m_bIdle) && (F_CTRLINPUT_A_PRESSED))     { m_bIdle=false; return true; } else return false; }
      bool  bBPressed      () { if((m_bIdle) && (F_CTRLINPUT_B_PRESSED))     { m_bIdle=false; return true; } else return false; }
      bool  bSelectPressed () { if((m_bIdle) && (F_CTRLINPUT_SELECT_PRESSED)){ m_bIdle=false; return true; } else return false; }
      bool  bStartPressed  () { if((m_bIdle) && (F_CTRLINPUT_START_PRESSED)) { m_bIdle=false; return true; } else return false; }
      bool  bRPressed      () { if((m_bIdle) && (F_CTRLINPUT_R_PRESSED))     { m_bIdle=false; return true; } else return false; }
      bool  bLPressed      () { if((m_bIdle) && (F_CTRLINPUT_L_PRESSED))     { m_bIdle=false; return true; } else return false; }
      bool  bLeftPressed   () { if((m_bIdle) && (F_CTRLINPUT_LEFT_PRESSED))  { m_bIdle=false; return true; } else return false; }
      bool  bRightPressed  () { if((m_bIdle) && (F_CTRLINPUT_RIGHT_PRESSED)) { m_bIdle=false; return true; } else return false; }
      bool  bUpPressed     () { if((m_bIdle) && (F_CTRLINPUT_UP_PRESSED))    { m_bIdle=false; return true; } else return false; }
      bool  bDownPressed   () { if((m_bIdle) && (F_CTRLINPUT_DOWN_PRESSED))  { m_bIdle=false; return true; } else return false; }

      bool  bIdle  () { if( (!F_CTRLINPUT_A_PRESSED) &&
                            (!F_CTRLINPUT_B_PRESSED) )
                         return true;
                         else return false; }
/*
      bool  bIdle  () { if( (!F_CTRLINPUT_A_PRESSED) &&
                            (!F_CTRLINPUT_B_PRESSED) &&
                            (!F_CTRLINPUT_SELECT_PRESSED) &&
                            (!F_CTRLINPUT_START_PRESSED) &&
                            (!F_CTRLINPUT_R_PRESSED) &&
                            (!F_CTRLINPUT_L_PRESSED) &&
                            (!F_CTRLINPUT_LEFT_PRESSED) &&
                            (!F_CTRLINPUT_RIGHT_PRESSED) &&
                            (!F_CTRLINPUT_UP_PRESSED) &&
                            (!F_CTRLINPUT_DOWN_PRESSED) )
                         return true;
                         else return false; }
*/

};

#endif /* PAD_H */
 
