// ReadStationInf.h: interface for the CReadStationInf class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_READSTATIONINF_H__F0523364_9A30_469C_A795_8FFBE5EF36F9__INCLUDED_)
#define AFX_READSTATIONINF_H__F0523364_9A30_469C_A795_8FFBE5EF36F9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CommFunction.h"

/*#####################################################################
			存放所有车站的站码、名字以及所在路径等信息
######################################################################*/

struct AFX_EXT_CLASS StationNode
{
	friend class CReadStationInf;
public:
	int			iIndex;				//序号

	/*  ---- 车站自身信息 ---------*/
	int			iStationID;			//车站的站码
	CString		strName;			//车站的名字
	CString		strDirectory;		//车站站场图信息所在的相对路径

	/* ------上下相邻两站的站码----*/
	int			iUpStationID[2];		//上行相邻站站码
	int			iDownStationID[2];		//下行相邻站站码

private:
	StationNode* Next;				//下一结点的指针
};
//----------------------------------
class AFX_EXT_CLASS CReadStationInf : public CObject  
{
protected:
		CReadStationInf();
		virtual ~CReadStationInf();
		
public:
	static void ReleaseInstance();
	static CReadStationInf* GetInstance() ;
	static void SetActiveStation(int iActStaID) { _iActiveStationID = iActStaID;}
	static int  GetActiveStation() { return _iActiveStationID;}

	//得到第iIndex个元素的指针
	StationNode* GetAt(int iIndex) const;

	//通过站码得到此站的结构信息
	StationNode* GetItem(int iStationID) const;
	
	//返回链表的长度
	int GetLength() const;
	

	//将站码列表转换为名字列表或是将名字列表转换为站码列表
	//SComPart 指定strName或strNum中源串的分隔符
	//DComPart 指定strNum或strName中目标字符串的分隔符
	CString CovNameToNum(CString strName, char SComPart = ',', char DComPart = '/' ) const;
	CString CovNumToName(CString strNum,  char SComPart = '/', char DComPart = ',' ) const;

	//清空单链表
	void	ClearList();


	//根据车站的名字得到车站的站码
	WORD	GetStationID(LPCSTR strName) const;
	/*
	 *	根据序号得到车站的站码
	 */
	WORD	GetStationID(int iOrder) const;

	//根据车站的站码或索引号得到车站的名字
	/*
		Par: bFlag为TRUE时，根据站码得到站名，为FALSE时根据序号得到站名
	*/
	CString GetName(const WORD& wStationNo,BOOL byStationID = TRUE) const;


	/*根据车站的站码或名称得到车站信息所在的文件夹位置
		bAbsolute :
			TRUE: 返回绝对路径
			FALSE:返回相对路径
	*/
	CString GetDirectory(const WORD& wStationNo,BOOL bAbsolute = TRUE) const;
	CString GetDirectory(const CString& strStationName,BOOL bAbsolute = TRUE) const;



private:
	//从文件中读取车站的信息
	BOOL	ReadFile(LPCSTR lpFileName = '\0');

	/*
	 *	
	 */
	void	Add(const StationNode& item);

private:
	//CString	m_strPath;		//站场信息文件所在路径

	StationNode*	m_pHead;
	WORD			m_wStationNum;	//链表中车站的数目

private:
	static CReadStationInf*	_pInstance;
	static int		_iActiveStationID;//当前处于显示状态的站场图ID

};

#endif // !defined(AFX_READSTATIONINF_H__F0523364_9A30_469C_A795_8FFBE5EF36F9__INCLUDED_)
