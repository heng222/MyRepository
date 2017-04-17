#pragma once

#include "InterfaceEx.h"

//** ��·���ӳ���
struct TRoadIDMap 
{
    CString     strRoadID;
    DWORD       dwRoadID;
};
typedef TRoadIDMap* PTRoadIDMap;


//////////////////////////////////////////////////////////////////////////
class CRoadIDMgr : public CTypedPtrMap<CMapStringToPtr,CString,PTRoadIDMap>
{
public:

    CRoadIDMgr(void);
    ~CRoadIDMgr(void);

    // ��ȡ��·ID��ӳ���ļ�
    BOOL    ReadMapFile();

    // ���
    void    Clear();

private:

};
