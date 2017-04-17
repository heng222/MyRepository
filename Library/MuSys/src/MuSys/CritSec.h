


#ifndef _MANUALLOCK_E42A205F_854E_4091_912A_7D5E33878B4B
#define _MANUALLOCK_E42A205F_854E_4091_912A_7D5E33878B4B

//////////////////////////////////////////////////////////////////////////
#include "MuType.h"

class AFX_EXT_CLASS CCritSec
{
public:

    CCritSec(void);
    ~CCritSec(void);

    void Lock();
    void Unlock();

private:

    CRITICAL_SECTION  m_CriticalSection;
};

//////////////////////////////////////////////////////////////////////////
#endif