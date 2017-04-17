
/*
* ============================================================================
*  Name     : Internal module communication
*  Part of  : Auxiliary module
*  Created  : 19.11.2006 by Henry
*  Description: Free
*     
*  Version  : 1.2
*  Copyright: Copyright (c) 2007-2010. DCL-CHARY Network Corporation Ltd.
* ============================================================================
*/


//#pragma message("\n")

#ifndef __INTERMODULE_MESSAGE_COMM__
#define __INTERMODULE_MESSAGE_COMM__

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

#ifndef _NBASE_MODULE_PROJECT_

#ifdef _DEBUG
    #ifdef _UNICODE
    #define _NBASE_DLL "NBase20UD"   
    #else
    #define _NBASE_DLL "NBase20D"   
    #endif     
#else    
    #ifdef _UNICODE
    #define _NBASE_DLL "NBase20U"
    #else
    #define _NBASE_DLL "NBase20"   
    #endif      
#endif

#endif

//////////////////////////////////////////////////////////////////////////
#ifdef _NBASE_MODULE_PROJECT_
#define NBASE_EXT_API __declspec(dllexport)
#else
#define NBASE_EXT_API __declspec(dllimport)
#endif


//////////////////////////////////////////////////////////////////////////

#include <afxtempl.h>
#include "MuSys.h"
              


//////////////////////////////////////////////////////////////////////////


// Message used for communicating during inter-modules.

class NBASE_EXT_API CImcMessage  : public CObject
{
public:

    // Reserved ID
    const static int ReservedID;

    // Restart application
    const static int RestartApp;

    // close all the modules
    const static int CloseAllModule;

    // log type define
    const static int AppLogMsg;

    // General error code.
    enum TErrorCode 
    {
        ERR_ALREADYEXIST,
        ERR_OVERFLOW,
    };

    // message priority.
    enum TMsgPriority
    {
        EMP_HIGHEST,
        EMP_NORMAL,
        EMP_IDLE,
    };
    
    WPARAM          m_wParam;
    LPARAM          m_lParam;


protected:
    
    // type of message
    unsigned short	    m_wMsgType;			

    // the type when dispatching
    enum TDispType
    {
        // Synchronous message(Default)
        EDT_SYNCHRONOUS,    
        // Asynchronous message
        EDT_ASYNCHRONOUS,   
    };
    TDispType m_iDispatchType; // the type of msg when it's dispatched(synchronous or asynchronous)
    
    BOOL      m_bAutoDel; // TRUE: call delete this when the msg is asynchronous .



private:

    enum { EMaxNumDestMod= 10};
    BYTE      m_byNumDestModule; // Number of iDestModule

    int m_DestModule[EMaxNumDestMod];  // Destination module list

    int m_SourceModID; // Source module


	// Constructor && Destructor
public:

    CImcMessage();

    CImcMessage( WORD wMsgType, // message type
		int iSourceMod = 0, // source module ID
		int iDestMod = 0 // dest module ID
		);
	
	// virtual destructors are necessary
    virtual ~CImcMessage();

    DECLARE_DYNCREATE(CImcMessage)


	// virtual functions
public:

	// must be overridden if you wanna the message can be handled asynchronously.
    virtual CImcMessage* Duplicate() const; 

	// must be overridden if your wanna the subclass be saved correctly!
    virtual void Serialize(CArchive& ar); 


    // New public functions
public:    

    CImcMessage& operator= (const CImcMessage& other);
    void    Copy(const CImcMessage& other);

    unsigned short    GetMsgType() const;

    BOOL    IsSynchronous() const;
    void    SetSynchronous(BOOL bEnable=FALSE);

    void    SetAutoDel(BOOL bFlag);
    void    AutoDelete();

    int   GetDestMod(int aIndex) const;

    int   GetSourceModul() const;

    void        SetSourceModule(int aSourceID);

    BYTE        GetNumDestMod() const;

    void        SetDestModule(int aDest);

    int         AddDestModule(int aDest);

    void        DelDestModule(int aDest);

    BOOL        IsExistDestModule(int aID) const;

protected:


};
typedef  CImcMessage* PTImcMsg;
typedef CList<PTImcMsg,PTImcMsg> TImcMsgList;

//////////////////////////////////////////////////////////////////////////

#ifndef _NBASE_MODULE_PROJECT_
#pragma comment( lib, _NBASE_DLL )
#endif

//////////////////////////////////////////////////////////////////////////

extern NBASE_EXT_API int nWDLL;

//////////////////////////////////////////////////////////////////////////
#endif