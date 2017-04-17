// EntRailway.h: interface for the CEntRailway class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ENTRAILWAY_H__47F3190A_8960_41DA_BCC5_3E30439BB9F7__INCLUDED_)
#define AFX_ENTRAILWAY_H__47F3190A_8960_41DA_BCC5_3E30439BB9F7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//����ṹ
struct Switch
{
	WORD	wSwitch;	//�����
	BYTE	byFlag;		//��λ��λ
};

//�洢ÿ����·����ϸ��Ϣ(ER means Entry Railway)
#define		BTNMAXNUM		10		//��ť�����Ŀ

//

struct AFX_EXT_CLASS ERNode
{
	friend class CEntRailway;
public:
	enum ERType{	//��·����
		ET_LIECHE	/*�г���·*/,
		ET_DIAOCHE	/*������·*/,
		ET_TONGGUO	/*ͨ����·*/
	};
public:
	BYTE		byERType;				//��·����(ET_LIECHEΪ�г���·(default),ET_DIAOCHEΪ������·)
	
	/*--------- ����Ϊ��·�ļ�����Ϣ ---------*/
	WORD		iOrder;					//���

	BYTE		byThroat;				//�ʺ��

	WORD		wButton[BTNMAXNUM];		//��ť��

	BYTE		byType;					//��·����1�� ������·����ͨ��·����Ч��·��
	
	BYTE		byProp;					//��·����2�� �ӳ�0������1������2��ͨ��3������4
	
	//�г���·��Ϣ�����źŵƷ���
	BYTE		byStartLight[2];		//�źŵ�ID���䷽��(0Ϊ��1Ϊ��)
	
	WORD		wSwitchNum;				//������
	Switch*		pSwitch;				//��������ָ��
	
	WORD*		pwSection;				//����������

	WORD		wNearSectionNum;		//�ӽ����θ���
	WORD*		pwNearSection;			//

	WORD		wFarSectionNum;			//Զ�����θ���
	WORD*		pwFarSection;			//
	
	
	WORD		wLEnemyLightNum;		//LEnemyLight����Ŀ
	WORD*		pwLEnemyLight;			//LEnemyLight�ж��ź�
	
	WORD		wDEnemyLightNum;		//DEnemyLight����Ŀ
	WORD*		pwDEnemyLight;			//DEnemyLight�ж��ź�

	//�г���·��Ϣ���޴�����
	BYTE		byConsumeTime;			//����ʱ��(����)

	//�г���·��Ϣ���޴�����
	BYTE		bySubRoadButtonNum;		//�ӽ�·��ť����Ŀ
	BYTE*		pbySubRoadButton;		//�ӽ�·��ť�����

	//�г���·��Ϣ���޴�����
	BYTE		byReturnSectionNum;		//�۷����ε���Ŀ
	BYTE*		pbyReturnSection;		//�۷����ε�ID

	
	WORD		wJlEnableNum;			//jlenable����Ŀ
	WORD*		pwJlEnable;				//jleable������ָ��
	

	WORD		wJlDisableNum;			//jlnoable����Ŀ
	WORD*		pwJlDisable;			//jlnoable������ָ��


	ERNode*		Next;					//ָ����һ��ERNode���

public:
	ERNode()
	{
		WORD _size = sizeof(*this);
		ZeroMemory(this,_size);
	}
	~ERNode()
	{
		Free();
	}

private:
	void Free();
	ERNode& operator =(const ERNode &item);
};
typedef ERNode*  lpERNode;

//���ļ�ʱָ��������
enum {

	/* ����ֵָ���Ƕ����г���ص���Ϣ */
	TRAIN,					// --- ���г���·ȫ����Ϣ
	//TRAIN_NEARSECTION,	// --- ���г���·��NearSection���ڸ���ֵ����Ϣ
	//TRAIN_FARSECTION,		// --- ���г���·��FarSection���ڸ���ֵ����Ϣ
	//-------------------------

	
	/* ����ֵָ���Ƕ���������ص���Ϣ */

	DIS_TRAIN,				// --- ��������·ȫ����Ϣ
	DIS_TRAIN_NEARSECTION,	// --- ��������·��NearSection���ڸ���ֵ����Ϣ
	DIS_TRAIN_FARSECTION	// --- ��������·��FarSection���ڸ���ֵ����Ϣ
	//-------------------------
 } ;

//----------------------------------------
//Class CEntRailway Declaration
typedef WORD LENGTHTYPE;

class AFX_EXT_CLASS CEntRailway : public CObject  
{
//operation
public:	
	/*
		FUNTION:�õ�������ĳ���(����0��ʾ������Ϊ��)
	*/
	LENGTHTYPE GetLengh() const;
	
	/*
		FUNTION:��յ��������ͷ��ڴ�(��ʱ������ظ���ʼ״̬)
	*/
	void ClearList();
	
	/*
		FUNTION:�õ�����Ϊindex�Ľ��ָ��(������Ϊ�ջ�Խ��,�򷵻�NULL)
	*/
	ERNode* GetAt(const LENGTHTYPE& index) const;
	
	/*
		FUNTION:�õ�ָ������ĩβ����ָ��(������Ϊ�շ���NULL)
	*/
	ERNode* GetTail() const;
	
	/*
		FUNTION:�õ�ָ�������ͷ����ָ��(������Ϊ�շ���NULL)
	*/
	ERNode* GetHead() const;
	
public:
	//##############################################################################
		/*
		FUNTION:��ȡ��·�е�ȫ����Ϣ
	*/
	BOOL ReadERFile(LPCSTR lpcFileName);

	/*FUNTION: ����ָ����������ȡINI�ļ�
				PAR1:	lpcFileName ------ INI�ļ��ľ���·��
				PAR2:	nReadCondition ------ ���ļ�ʱָ��������(��ReadCondition ˵��)
				PAR3:	wSection ------------ ����ֵ

	����ֵ����ȡ�ɹ�����TRUE
	        ���ɹ�����FALSE
	*/
	BOOL ReadERFile( LPCSTR lpcFileName, int nReadCondition,  WORD wSection = 0 );
	
	//###############################################################################

//overide
public:
	
#ifdef _DEBUG
	/*
		FUNTION: ����������
		PAR:	 nCondition ------ �Ƿ�Ϊ����������
	*/
	void TraverseList(int nCondition) const;
#endif
	
	/*
		�� =�� ����
	*/
	CEntRailway& operator =(const CEntRailway &cER);
	
	/*
		�� []�� ����
	*/
	ERNode& operator [](const LENGTHTYPE& i);
	

	// Construction
	CEntRailway();
	CEntRailway(const CEntRailway& cEntR);
	virtual ~CEntRailway();

public:
	
	/*
	 *	ͨ����ť���ؽ�·����
	 [in] pBtnList: ��ť����
	 [in] iBtnNum:����ť����
	 */
	int GetProAccordByBtn(const WORD* pBtnList,const int& iBtnNum);
	
	/*
	 	����������ť����Ƿ������Ӧ�Ľ�·
		[in] pWBtn: ������ť
		[in] iBtnNum: ��ť����
		[out] iFound: �����������Ľ�·��������ṹ,����Ϊ��

		Return Value: ���ڷ���TRUE
	 */
	BOOL IsExistER(const WORD* pwBtn,int iBtnNum,ERNode *pItem = NULL);

	/*
	 *	�Ƿ���ڽӽ����ε���wNearSection���뿪���ε���wFarSection�Ľ�·
	 */
	BOOL IsExistNearFarSection(const WORD& wNearSection,const WORD& wFarSection);
	
	/*
	 *	
	 */
	BOOL DelItemByNearFarSection(const WORD& wNearSection,const WORD& wFarSection);
	/*
	 *	
	 */
	BOOL FindItemByOrder(const LENGTHTYPE& wOrder);
	
	/*
	 *	
	 */
	BOOL DeleteItem(const BYTE& byThroat, BOOL bIsEqual = FALSE);

	/*FUNTION: ��������ĩβ����һ�����
				PAR1:	item ----- �½��
	*/
	void AddTail(const ERNode& item);
	
private:
	
	LENGTHTYPE		m_wLength;		//������ĳ���

	ERNode*			m_pHead;		//������ͷָ��
};

#endif // !defined(AFX_ENTRAILWAY_H__47F3190A_8960_41DA_BCC5_3E30439BB9F7__INCLUDED_)























