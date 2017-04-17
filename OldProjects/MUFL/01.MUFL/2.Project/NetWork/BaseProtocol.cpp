#include "stdafx.h"
#include "BaseProtocol.h"

//////////////////////////////////////////////////////////////////////////
TBaseProtocol::TBaseProtocol()
{
    m_bAutoDel = FALSE;
}
TBaseProtocol::~TBaseProtocol()
{

}

//////////////////////////////////////////////////////////////////////////
void TBaseProtocol::SetAutoDel(BOOL bFlag)
{
    m_bAutoDel = bFlag;
}

void TBaseProtocol::AutoDel()
{
    if (m_bAutoDel)
    {
        delete this;
    }
}