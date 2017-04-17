#pragma once

#include "afx.h"
#include <afxtempl.h>
#include "NBMapEngine.h"
#include "UserColors.h"
#include "DataModulInterface.h"

//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
class CMapTRawTfcList : public CMapStringToPtr
{
private:
    CRITICAL_SECTION    m_CriticalSection;

public:
    CMapTRawTfcList()
    {
        InitializeCriticalSection(&m_CriticalSection);
        InitHashTable(100);
    }
    ~CMapTRawTfcList()
    {
        ClearList();
        DeleteCriticalSection(&m_CriticalSection);
    }

    //
    void DrawRoad(CDC* pDC,MCoorTransProvider& ctProvider)
    {
        EnterCriticalSection(&m_CriticalSection);

        POSITION pos;
        CString key;
        PIMsgRawTrafInf pTRoadInf;

        for( pos = GetStartPosition(); pos != NULL; )
        {
            GetNextAssoc( pos, key, (void*&)pTRoadInf );
            pTRoadInf->m_tfcRawRoadInf.DrawRoad(pDC,ctProvider);
        }

        LeaveCriticalSection(&m_CriticalSection);
    }

    // 
    void DrawNodeName(CDC* pDC,MCoorTransProvider& ctProvider)
    {
        EnterCriticalSection(&m_CriticalSection);

        POSITION pos;
        CString key;
        PIMsgRawTrafInf pTRoadInf;

        for( pos = GetStartPosition(); pos != NULL; )
        {
            GetNextAssoc( pos, key, (void*&)pTRoadInf );
            pTRoadInf->m_tfcRawRoadInf.DrawRoadName(pDC,ctProvider);
        }

        LeaveCriticalSection(&m_CriticalSection);
    }

    //
    void AddItem(LPCTSTR key,PIMsgRawTrafInf newValue)
    {
        EnterCriticalSection(&m_CriticalSection);

        PIMsgRawTrafInf pOldElement=NULL;
        BOOL bFlag = CMapStringToPtr::Lookup( key, (void *&)pOldElement );
        if( !bFlag )
        {
            PIMsgRawTrafInf pRoadTfcInf = new IMsgRawTrafInf;
            pRoadTfcInf->Copy(*newValue);
            CMapStringToPtr::SetAt(key,pRoadTfcInf);
        }
        else
        {
            pOldElement->Copy(*newValue);
        }

        LeaveCriticalSection(&m_CriticalSection);
    }

    // 
    void ClearList()
    {
        EnterCriticalSection(&m_CriticalSection);

        POSITION pos;
        CString key;
        PIMsgRawTrafInf pa;

        for( pos = GetStartPosition(); pos != NULL; )
        {
            GetNextAssoc( pos, key, (void*&)pa );
            delete pa;
        }

        RemoveAll();

        LeaveCriticalSection(&m_CriticalSection);
    }
};



//////////////////////////////////////////////////////////////////////////
class CTfcInfMgr : public CNBMapEngine
{
public:

    CTfcInfMgr(void);
    ~CTfcInfMgr(void);


    // From CNBMapEngine
private:

    BOOL OnInitialize(TEgAttri& aAttri,TMRect& mapRect,CSize& sizeGrid);

public:

    BOOL Open();

    void SetAt(LPCTSTR key,PIMsgRawTrafInf newValue);
    INT_PTR GetRoadCount() const;
	
    COleDateTime GetUpdateTime() const;
    COleDateTime GetFlashTime() const;
    
    void UpdateFlashTime();
    void DrawTfcStream(CDC* pDC,BOOL bDrawName);

    void Close();

    CTfcEventList&  RetrieveTfcEvents() ;
    void DrawTfcEvent(CDC* pDC);
    PTTfcEventAttri GetTfcEvent(CPoint ptPos) const;

public:

    CMapTRawTfcList  m_RawTfcList;
    CTfcEventList    m_TfcEvtList;
    TMRect  m_rectMap;

private:

    COleDateTime  m_timeFlash;
};
