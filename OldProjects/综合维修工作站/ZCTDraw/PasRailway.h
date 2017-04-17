// PasRailway.h: interface for the CPasRailway class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PASRAILWAY_H__0872C916_6A63_44A4_91EB_E22E149695F3__INCLUDED_)
#define AFX_PASRAILWAY_H__0872C916_6A63_44A4_91EB_E22E149695F3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
//########################################
struct PRNode
{
	WORD	abyButton[2];
	WORD	abySubRoad1[2];
	WORD	abySubRoad2[2];

	PRNode*	Next;
};
class CPasRailway : public CObject  
{
public:
	/*
	 	根据所击按钮检查是否存在相应的进路
		[in]	  pWBtn: 所击按钮
		[in]	iBtnNum: 按钮个数
		[out]	 iFound: 若存在这样的进路，返回其结构,可以为空

		Return Value: 存在返回TRUE
	 */
	BOOL IsExistER(const WORD* pwBtn,int iBtnNum=2,PRNode *pItem = NULL);
	/*
	 *	
	 */
	int GetLength();
	/*
	 *	
	 */
	PRNode* GetAt(const int& iIndex);


	//清空链表
	void ClearList();
	//加入新结点
	void AddNode(PRNode* item);
	//读文件
	BOOL ReadFile(LPCSTR lpcsFileName);
	CPasRailway();
	virtual ~CPasRailway();
	WORD PWNumber;

private:
	void InitNode(PRNode* item);
	
	PRNode* Head;
};

#endif // !defined(AFX_PASRAILWAY_H__0872C916_6A63_44A4_91EB_E22E149695F3__INCLUDED_)
