

#ifndef _AUTOLOCK_8D7B38222502_D464C06B_5710_4ea9_9E09
#define _AUTOLOCK_8D7B38222502_D464C06B_5710_4ea9_9E09

//////////////////////////////////////////////////////////////////////////
#include "MuType.h"
#include "CritSec.h"

// 
class AFX_EXT_CLASS CAutoLock
{
public:
    CAutoLock(CCritSec *plock);
    ~CAutoLock(void);

private:
    CCritSec*   m_pCriSec;
};


//////////////////////////////////////////////////////////////////////////
#endif
