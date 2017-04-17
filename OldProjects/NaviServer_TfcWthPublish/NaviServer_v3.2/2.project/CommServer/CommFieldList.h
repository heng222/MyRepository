// CommFieldList.h: interface for the CCommFieldList class.
//

#pragma once
#include "CommField.h"

class CCommFieldList : public CObList  
{
public:
	CCommFieldList();
	virtual ~CCommFieldList();


public:	

    BOOL Delete(const DWORD& dwFieldID);
	CCommField* GetCommField(DWORD dwFieldID);
    void AddHead(CCommField* newElement);
	BOOL SendAll(LPBYTE lpData,int iDataLen);
	//BOOL SendExcept(LPBYTE lpData,int iDataLen,SOCKET sExcept);
    WORD GetAuthCount(void);
    void ClearList();

    // 清除无效的连接
    void CleanUp(int iType);

private:
	
    CRITICAL_SECTION  m_CriSection;


};

