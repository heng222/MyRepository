
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
    #define _NBASE_DLL "NBaseUD"   
    #else
    #define _NBASE_DLL "NBaseD"   
    #endif     
#else    
    #ifdef _UNICODE
    #define _NBASE_DLL "NBaseU"   
    #else
    #define _NBASE_DLL "NBase"   
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
#include "NB_Type.h"

//////////////////////////////////////////////////////////////////////////
// Module Identifiers Definition

#define     ID_MODULE_NONE       0x0000			// None
#define     ID_MODULE_SYS        0x0001         // system ID

#define     ID_MODULE_RESERVED   0x0010         // Reserved!

#define     ID_MODULE_ALL        0xFFFF		 	// All modules



// Identification of modules that has defined already for you.£¨must be greater than ID_MODULE_RESERVED.£©

#define     ID_MODULE_USERIF     ID_MODULE_RESERVED+1		// UI Module
#define     ID_MODULE_DATABASE   ID_MODULE_RESERVED+2       // DataBase Module
#define     ID_MODULE_NETWORK    ID_MODULE_RESERVED+3       // SCK Module


//////////////////////////////////////////////////////////////////////////
// System message ID ( 0x0001 ~ 0x0100 )

#define     ESYS_RESTART_APP         0x0001                 // Restart application
#define     ESYS_CLOSE_ALLMODULS     0x0002                 // close all the modules

#define     ESYS_RESERVED            0x0100                 // Reserved ID




// Message identification of user-defined ( must be greater than ESYS_RESERVED. )

#define     ESYS_NEW_LOG        ESYS_RESERVED+1	                // new logs



//////////////////////////////////////////////////////////////////////////

typedef NB_WORD     NB_MSGID;
typedef NB_INT      TModuleID;

// Message used for communicating during inter-modules.

class NBASE_EXT_API TImcMsg  : public CObject
{
public:

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

    NB_MSGID	    m_wMsgType;			// type of message

    // the type when dispatching
    enum TDispType
    {
        EDT_SYNCHRONOUS,    // Synchronous message(Default)
        EDT_ASYNCHRONOUS,   // Asynchronous message
    };
    TDispType m_iDispatchType; // the type of msg when it's dispatched(synchronous or asynchronous)
    
    BOOL      m_bAutoDel; // TRUE: call delete this when the msg is asynchronous .



private:

    enum { EMaxNumDestMod= 10};
    BYTE      m_byNumDestModule; // Number of iDestModule

    TModuleID m_DestModule[EMaxNumDestMod];  // Destination module list

    TModuleID m_SourceModID; // Source module


	// Constructor && Destructor
public:

    TImcMsg();

    TImcMsg( WORD wMsgType, // message type
		TModuleID iSourceMod=ID_MODULE_NONE, // source module ID
		TModuleID iDestMod=ID_MODULE_NONE // dest module ID
		);
	
	// virtual destructors are necessary
    virtual ~TImcMsg();

    DECLARE_DYNCREATE(TImcMsg)


	// virtual functions
public:

	// must be overridden if you wanna the message can be handled asynchronously.
    virtual TImcMsg* Duplicate() const; 

	// must be overridden if your wanna the subclass be saved correctly!
    virtual void Serialize(CArchive& ar); 


    // New public functions
public:    

    TImcMsg& operator= (const TImcMsg& other);
    void    Copy(const TImcMsg& other);

    NB_MSGID    GetMsgType() const;

    BOOL    IsSynchronous() const;
    void    SetSynchronous(BOOL bEnable=FALSE);

    void    SetAutoDel(BOOL bFlag);
    void    AutoDelete();

    TModuleID   GetDestMod(int aIndex) const;

    TModuleID   GetSourceModul() const;

    void        SetSourceModule(TModuleID aSourceID);

    BYTE        GetNumDestMod() const;

    void        SetDestModule(TModuleID aDest);

    int         AddDestModule(TModuleID aDest);

    void        DelDestModule(TModuleID aDest);

    BOOL        IsExistDestModule(TModuleID aID) const;

protected:


};
typedef  TImcMsg* PTImcMsg;
typedef CList<PTImcMsg,PTImcMsg> TImcMsgList;

//////////////////////////////////////////////////////////////////////////

#ifndef _NBASE_MODULE_PROJECT_
#pragma comment( lib, _NBASE_DLL )
#endif

//////////////////////////////////////////////////////////////////////////

extern NBASE_EXT_API int nWDLL;

//////////////////////////////////////////////////////////////////////////
#endif