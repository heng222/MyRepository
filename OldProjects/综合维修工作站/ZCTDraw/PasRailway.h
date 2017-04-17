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
	 	����������ť����Ƿ������Ӧ�Ľ�·
		[in]	  pWBtn: ������ť
		[in]	iBtnNum: ��ť����
		[out]	 iFound: �����������Ľ�·��������ṹ,����Ϊ��

		Return Value: ���ڷ���TRUE
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


	//�������
	void ClearList();
	//�����½��
	void AddNode(PRNode* item);
	//���ļ�
	BOOL ReadFile(LPCSTR lpcsFileName);
	CPasRailway();
	virtual ~CPasRailway();
	WORD PWNumber;

private:
	void InitNode(PRNode* item);
	
	PRNode* Head;
};

#endif // !defined(AFX_PASRAILWAY_H__0872C916_6A63_44A4_91EB_E22E149695F3__INCLUDED_)
