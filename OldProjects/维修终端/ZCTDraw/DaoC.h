// DaoC.h

#ifndef _DaoC_H
#define _DaoC_h

#include "BaseElement.h"


#define CX_RADIUS      14 /* radius of the heart of DaoCha */
#define DC_POINT       12
#define DefaultSlope   1

typedef struct {         /* Qu Duan Map */
	short QD_INDEX;
	short iPrDC;
} DCQDMAP;

typedef struct {         /* Dao Cha Jiao Cha Huan Wei */
	short dc1;
	BOOL  DWZG1;
	short dc2;
	BOOL  DWZG2;
} JCHW;

//����״̬����
enum _DaoChaStatus		
{
	DCST_SK = 0x00,	//�Ŀ�
	DCST_FW = 0x01,	//��λ
	DCST_DW = 0x02,	//��λ
	DCST_JC = 0x03,	//����
	DCST_DF = 0x08,	//����
	DCST_DS = 0x24	//����
};

//����״̬�жϺ궨��
#define DAOCHA_ISSK(iStatus)	((iStatus)==DCST_SK)	// �Ƿ��Ŀ� 
#define DAOCHA_ISFW(iStatus)	((iStatus)&DCST_FW)		// �Ƿ�λ
#define DAOCHA_ISDW(iStatus)	((iStatus)&DCST_DW)		// �Ƿ�λ 
#define DAOCHA_ISJC(iStatus)	((iStatus)==DCST_JC)	// �Ƿ񼷲� 
#define DAOCHA_ISLOCK(iStatus)	((iStatus)&DCST_DS)		// �Ƿ��� 
#define DAOCHA_ISOFF(iStatus)	((iStatus)&DCST_DF)		// �Ƿ񵥷�
	

class CDaoC: public CBaseElement
{
	DECLARE_SERIAL(CDaoC)
//Construtor
public:
	CDaoC();
	~CDaoC();

	//��������
	enum _DaoChaType		
	{
		DT_GENERAL = 0,		//��ͨ����
		DT_TUOGUIQI= 1		//�ѹ���
	};



// Attributes
public:
	//static data, from file "yard.dat"
	CPoint m_deltaA;
	CPoint m_deltaB;
	CPoint m_deltaC;

	int	m_iIndex;

	int m_iALink;
	int m_iBLink;
	int m_iCLink;

	int	m_iType;
	CString	m_strName;

	//
	float CosAlpha;
    float SinAlpha; 
	float fSlope;



	int m_iRWCBand;
	
	//int m_iPrevRWCBand;
	//int m_iDir,m_iPrevDir;
	
	int m_iStatus;	//����״̬
	
	BOOL bZoom;

	
// Operations
public:

	/* �Ƿ��Ŀ� */
	BOOL IsSK() { return DAOCHA_ISSK(m_iStatus); }
	
	/* �Ƿ�λ */
	BOOL IsFW() { return DAOCHA_ISFW(m_iStatus);}
	
	/* �Ƿ�λ */
	BOOL IsDW() { return DAOCHA_ISDW(m_iStatus); }

	/* �Ƿ񼷲� */
	BOOL IsJC() { return DAOCHA_ISJC(m_iStatus); }

	/* �Ƿ��� */
	BOOL IsLocked() { return DAOCHA_ISLOCK(m_iStatus); }

	/* �Ƿ񵥷� */
	BOOL IsOffed() { return DAOCHA_ISOFF(m_iStatus); }

// Overrides
public:
	void DrawSlf(CDC* pDC, int mDvcSta);
	int GetType() { return m_iType; }

public:
	void DrawDcc(CDC *pDC,/*int x,int y,*/int deltaX,int deltaY,int iClr,int iClr0,
		BOOL bIsCJ,BOOL bCXOnly);

private:
	/*
	 *	����ͨ����( _/_ )
	 */
	void DrawGeneralDC(CDC *pDC,BOOL bInfInvalid);
	
	/*
	 *	���ѹ���( �� )
	 */
	void DrawTGQ(CDC *pDC,BOOL bInfInvalid);
};

typedef CTypedPtrList<CObList,CDaoC*> CDaoCList;
#endif







