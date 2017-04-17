#pragma once

#include "InterfaceEx.h"

//** 道路编号映射表
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

    // 读取道路ID的映射文件
    BOOL    ReadMapFile();

    // 清空
    void    Clear();

private:

};
