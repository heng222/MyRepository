// BSD.h

#if !defined _BSD_h_
#define _BSD_h_
/*
(0-�ǽ�·���� 1-�����ղ� 2-�����ӽ� 3-������ʾ 4-����� 5-�շ���� 
6-�շ帴ʾ 7-���Զ������ӳ� 8-���Զ��������� 9-�Զ������ӷ��� 
10-�Զ������ල���� 11-�Զ��������� 13-ƽ����� 20��21-�����ʾ 
100-CTC��ʾ 103-������CTCͨѶ�ı�ʾ
)
(����0/5/10/11/12/13/20/100Ϊ����ʽ����1/4/7/8/9/21Ϊ��ͷʽ 
	����3/6Ϊ�źŻ�ʽ ����2Ϊֱ��ʽ)

*/

/* BiaoShiDeng Type */
#define BSD_TYPE_FJD     0   /* �ǽ�·���� */
#define BSD_TYPE_CLZC    1   /* �����ղ� */
#define BSD_TYPE_CLJJ    2   /* �����ӽ� */
#define BSD_TYPE_CLFS    3   /* ������ʾ */
#define BSD_TYPE_JWD     4   /* ����� */
#define BSD_TYPE_TFKZ    5   /* �շ����*/
#define BSD_TYPE_TFFS    6   /* �շ帴ʾ */
#define BSD_TYPE_BZDJC   7   /* ���Զ������ӳ� */
#define BSD_TYPE_BZDFC   8   /* ���Զ���������*/
#define BSD_TYPE_ZDJFC   9   /* �Զ������ӷ���*/
#define BSD_TYPE_ZDJDQD 10   /* �Զ������ල����zi dong bi sai jian du qu duan */
#define BSD_TYPE_ZDFZ   11   /* �Զ���������zi dong bi sai fu zhu */
#define BSD_TYPE_TS     20   /* �����ʶte shu biao shi (single light mode)*/
#define BSD_TYPE_TSARR  21   /* �����ʶte shu biao shi (arrow mode)*/
#define BSD_TYPE_KZMS   100  /* ����ģʽ(single light mode)*/

#include "BaseElement.h"

// Draw BiaoShiDeng
class CBSD : public CBaseElement
{
	DECLARE_SERIAL(CBSD)
public:
	CBSD();
	~CBSD();


// Attibutes
public:
	int			m_iType;
	CString		m_strName;

	int m_iDir;
	int m_iIndex;

	CPoint m_T_pt;
	BOOL m_bHidAble;

	int m_iStatus;
	WORD m_wBSDNo;
	
	int	m_iTemp;

// Operations
public:
	
	
private:	
	void MapLgtColor(BOOL bFlash,COLORREF& iClr);
	void DrawArraw(CDC *pDC,BOOL bFlash);
	void DrawLight(CDC *pDC,BOOL bLightOnly,BOOL bFlash);

//Temp funtion
private:
	void FreshLight(CDC *pDC,BOOL bLightOnly,BOOL bFlash );
	void FreshArraw(CDC *pDC,BOOL bFlash );
	void FreshBSD(CDC *pDC,BOOL bFlash);


// Implematation
public:
	BOOL	GetFlashState();
	void	DrawSlf(CDC *pDC,int iDevicSta);
	void	ShowName(CDC* pDC,int iNameSta);
	int		GetType() { return m_iType;	}
};

typedef CTypedPtrList<CObList,CBSD*> CBSDList;
#endif

