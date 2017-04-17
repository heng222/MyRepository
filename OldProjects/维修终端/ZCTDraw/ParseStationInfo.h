// ParseStationInfo.h: interface for the CParseStationInfo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PARSESTATIONINFO_H__D62D5C96_529B_4565_9309_E791A36AA2DA__INCLUDED_)
#define AFX_PARSESTATIONINFO_H__D62D5C96_529B_4565_9309_E791A36AA2DA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#define DATABUFFER_SIZE  1024
#define BIT_SIZE  3

#define SSDI		0x02	//
#define SSDCI		0x03	//

// Bit mask tables struct define
typedef struct
{
	WORD LDevNo,DDevNo;        // Lx Dev No,Dx Dev No

	// Green,GreenYellow,DoubleYellow,Red,White
	int GBit,YBit,GYBit,DYBit,DGBit,YSYBit,RWBit,RBit,YSBit,RSBit,GSBit,DSBit,WBit,WSBit;  
	WORD LLtBit,DLtBit;        // Lx Btn Light,Dx Btn Light
	char Name[11];
} XHTABLE;

typedef struct
{
	WORD DevNo;
	WORD ZBit,SBit;            // Zhanyong,Suobi
	char Name[11];
} QDTABLE;

typedef struct
{
	WORD DevNo;             // Qu Duan device number
	WORD DBit,FBit,JCBit,DSBit,DFBit;            // DingWei,FanWei,JiCha,DanSuo,DanFeng
	char Name[11];
} DCTABLE;

typedef struct 
{
	WORD type;
	WORD index;
	int  GBit,RBit,WBit,YBit,FBit;
	char Name[11];
	
}BSDTABLE;

typedef struct 
{
	WORD type;
	WORD offest;
	int SBit;
	char Name[11];
}GNDTABLE;

typedef struct
{
	// Mask define tables
	WORD nBitmapLen;
	WORD nXhTblSum;
	WORD nDcTblSum;
	WORD nQdTblSum;
	WORD nBsdTblSum;
	WORD nGndTblSum;
	//WORD nBjTblSum;
	//WORD nAndTblSum;
	//WORD nAnTblSum;
	XHTABLE* pXhTbl;
	QDTABLE* pQdTbl;
	DCTABLE* pDcTbl;
	BSDTABLE* pBsdTbl;
	GNDTABLE* pGndTbl;
	//BJDTABLE* pBjTbl;
	//ANDTABLE* pAndTbl;
	//ANTABLE* pAnTbl;
	
	BYTE LieXinTbl[DATABUFFER_SIZE];
	BYTE DiaoXinTbl[DATABUFFER_SIZE];
	BYTE DaoChaTbl[DATABUFFER_SIZE];
	BYTE QuDuanTbl[DATABUFFER_SIZE];
	int BiaoShiDengTbl[DATABUFFER_SIZE][BIT_SIZE];
	BYTE GongNengDengTbl[DATABUFFER_SIZE];
	BYTE InfoTabOutBuf[DATABUFFER_SIZE];
} MASKTABLE;

class CZCTWnd;

class CParseStationInfo
{
public:
	CParseStationInfo();
	virtual ~CParseStationInfo();
	BOOL ReadMask(CString strMaskFile);
	LPBYTE GetInfoTabOutBuf();
	WORD GetBsdTblSum();
	void TransactData(CZCTWnd* pParent,BYTE* pBuf, WORD wLen, BYTE byFrame);
	void ReleaseTables();

private:	
	CZCTWnd* m_pParent;
	MASKTABLE *m_pMskTab;
	BOOL m_bNewMsktabed;
	
	BOOL ReadMaskTbl(LPCTSTR szIniFile);	
	void ParseMaskTable(int nBit, BYTE bValue,BOOL bAll);
	void SetInfoTab(BYTE bFrame);


};

#endif // !defined(AFX_PARSESTATIONINFO_H__D62D5C96_529B_4565_9309_E791A36AA2DA__INCLUDED_)
