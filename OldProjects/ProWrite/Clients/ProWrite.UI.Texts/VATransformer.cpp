#include "StdAfx.h"
#include "VATransformer.h"


INT CVATransformer::m_iRatio = 1;

CVATransformer::CVATransformer(void)
{
}

CVATransformer::~CVATransformer(void)
{
}



BOOL CVATransformer::V2A(const LONG& lVValue, LONG& lAValue)
{
    if (m_iRatio==0)
    {
        return FALSE;
    }
    else if (m_iRatio>0)
    {
        lAValue = lVValue / m_iRatio;
    }
    else
    {
        lAValue = lVValue*abs(m_iRatio);
    }

    return TRUE;
}
BOOL CVATransformer::A2V(const LONG& lAValue, LONG& lVValue) 
{
    if (m_iRatio==0)
    {
        return FALSE;
    }
    else if (m_iRatio>0)
    {
        lVValue = lAValue * m_iRatio;
    }
    else
    {
        lVValue = lAValue / abs(m_iRatio);
    }

    return TRUE;

}

BOOL CVATransformer::V2A(const INT& iVValue, INT& iAValue)
{
    if (m_iRatio==0)
    {
        return FALSE;
    }
    else if (m_iRatio>0)
    {
        iAValue = iVValue / m_iRatio;
    }
    else
    {
        iAValue = iVValue*abs(m_iRatio);
    }

    return TRUE;
}

BOOL CVATransformer::A2V(const INT& iAValue, INT& iVValue)
{
    if (m_iRatio==0)
    {
        return FALSE;
    }
    else if (m_iRatio>0)
    {
        iVValue = iAValue * m_iRatio;
    }
    else
    {
        iVValue = iAValue / abs(m_iRatio);
    }

    return TRUE;
}

BOOL CVATransformer::V2A(const SIZE& sVValue, SIZE& sAValue)
{
    if (m_iRatio==0)
    {
        return FALSE;
    }

    V2A(sVValue.cx,sAValue.cx);
    V2A(sVValue.cy,sAValue.cy);

    return TRUE;

}
BOOL CVATransformer::A2V(const SIZE& sAValue, SIZE& sVValue)
{
    if (m_iRatio==0)
    {
        return FALSE;
    }

    A2V(sAValue.cx,sVValue.cx);
    A2V(sAValue.cy,sVValue.cy);

    return TRUE;

}