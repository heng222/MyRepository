// EntRailway.h: interface for the CEntRailway class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ENTRAILWAY_H__47F3190A_8960_41DA_BCC5_3E30439BB9F7__INCLUDED_)
#define AFX_ENTRAILWAY_H__47F3190A_8960_41DA_BCC5_3E30439BB9F7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//道岔结构
struct Switch
{
	WORD	wSwitch;	//道岔号
	BYTE	byFlag;		//正位或反位
};

//存储每个进路的详细信息(ER means Entry Railway)
#define		BTNMAXNUM		10		//按钮最大数目

//

struct AFX_EXT_CLASS ERNode
{
	friend class CEntRailway;
public:
	enum ERType{	//进路类型
		ET_LIECHE	/*列车进路*/,
		ET_DIAOCHE	/*调车进路*/,
		ET_TONGGUO	/*通过进路*/
	};
public:
	BYTE		byERType;				//进路类型(ET_LIECHE为列车进路(default),ET_DIAOCHE为调车进路)
	
	/*--------- 以下为进路文件中信息 ---------*/
	WORD		iOrder;					//序号

	BYTE		byThroat;				//咽喉号

	WORD		wButton[BTNMAXNUM];		//按钮号

	BYTE		byType;					//进路性质1： 基本进路、变通进路、无效进路。
	
	BYTE		byProp;					//进路性质2： 接车0、发车1、延续2、通过3、调车4
	
	//列车进路信息中无信号灯方向
	BYTE		byStartLight[2];		//信号灯ID与其方向(0为左，1为右)
	
	WORD		wSwitchNum;				//道岔数
	Switch*		pSwitch;				//道岔数组指针
	
	WORD*		pwSection;				//经过的区段

	WORD		wNearSectionNum;		//接近区段个数
	WORD*		pwNearSection;			//

	WORD		wFarSectionNum;			//远离区段个数
	WORD*		pwFarSection;			//
	
	
	WORD		wLEnemyLightNum;		//LEnemyLight的数目
	WORD*		pwLEnemyLight;			//LEnemyLight敌对信号
	
	WORD		wDEnemyLightNum;		//DEnemyLight的数目
	WORD*		pwDEnemyLight;			//DEnemyLight敌对信号

	//列车进路信息中无此内容
	BYTE		byConsumeTime;			//所需时间(钩分)

	//列车进路信息中无此内容
	BYTE		bySubRoadButtonNum;		//子进路按钮的数目
	BYTE*		pbySubRoadButton;		//子进路按钮的序号

	//列车进路信息中无此内容
	BYTE		byReturnSectionNum;		//折返区段的数目
	BYTE*		pbyReturnSection;		//折返区段的ID

	
	WORD		wJlEnableNum;			//jlenable的数目
	WORD*		pwJlEnable;				//jleable的数组指针
	

	WORD		wJlDisableNum;			//jlnoable的数目
	WORD*		pwJlDisable;			//jlnoable的数组指针


	ERNode*		Next;					//指向下一个ERNode结点

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

//读文件时指定的条件
enum {

	/* 以下值指定是读跟列车相关的信息 */
	TRAIN,					// --- 读列车进路全部信息
	//TRAIN_NEARSECTION,	// --- 读列车进路中NearSection等于给定值的信息
	//TRAIN_FARSECTION,		// --- 读列车进路中FarSection等于给定值的信息
	//-------------------------

	
	/* 以下值指定是读跟调车相关的信息 */

	DIS_TRAIN,				// --- 读调车进路全部信息
	DIS_TRAIN_NEARSECTION,	// --- 读调车进路中NearSection等于给定值的信息
	DIS_TRAIN_FARSECTION	// --- 读调车进路中FarSection等于给定值的信息
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
		FUNTION:得到单链表的长度(返回0表示单链表为空)
	*/
	LENGTHTYPE GetLengh() const;
	
	/*
		FUNTION:清空单链表以释放内存(此时单链表回复初始状态)
	*/
	void ClearList();
	
	/*
		FUNTION:得到索引为index的结点指针(若链表为空或越界,则返回NULL)
	*/
	ERNode* GetAt(const LENGTHTYPE& index) const;
	
	/*
		FUNTION:得到指向单链表末尾结点的指针(若链表为空返回NULL)
	*/
	ERNode* GetTail() const;
	
	/*
		FUNTION:得到指向单链表表头结点的指针(若链表为空返回NULL)
	*/
	ERNode* GetHead() const;
	
public:
	//##############################################################################
		/*
		FUNTION:读取进路中的全部信息
	*/
	BOOL ReadERFile(LPCSTR lpcFileName);

	/*FUNTION: 根据指定的条件读取INI文件
				PAR1:	lpcFileName ------ INI文件的绝对路径
				PAR2:	nReadCondition ------ 读文件时指定的条件(见ReadCondition 说明)
				PAR3:	wSection ------------ 区段值

	返回值：读取成功返回TRUE
	        不成功返回FALSE
	*/
	BOOL ReadERFile( LPCSTR lpcFileName, int nReadCondition,  WORD wSection = 0 );
	
	//###############################################################################

//overide
public:
	
#ifdef _DEBUG
	/*
		FUNTION: 遍历单链表
		PAR:	 nCondition ------ 是否为调车单链表
	*/
	void TraverseList(int nCondition) const;
#endif
	
	/*
		对 =号 重载
	*/
	CEntRailway& operator =(const CEntRailway &cER);
	
	/*
		对 []号 重载
	*/
	ERNode& operator [](const LENGTHTYPE& i);
	

	// Construction
	CEntRailway();
	CEntRailway(const CEntRailway& cEntR);
	virtual ~CEntRailway();

public:
	
	/*
	 *	通过按钮返回进路性质
	 [in] pBtnList: 按钮链表
	 [in] iBtnNum:　按钮个数
	 */
	int GetProAccordByBtn(const WORD* pBtnList,const int& iBtnNum);
	
	/*
	 	根据所击按钮检查是否存在相应的进路
		[in] pWBtn: 所击按钮
		[in] iBtnNum: 按钮个数
		[out] iFound: 若存在这样的进路，返回其结构,可以为空

		Return Value: 存在返回TRUE
	 */
	BOOL IsExistER(const WORD* pwBtn,int iBtnNum,ERNode *pItem = NULL);

	/*
	 *	是否存在接近区段等于wNearSection，离开区段等于wFarSection的进路
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

	/*FUNTION: 往单链表末尾加入一个结点
				PAR1:	item ----- 新结点
	*/
	void AddTail(const ERNode& item);
	
private:
	
	LENGTHTYPE		m_wLength;		//单链表的长度

	ERNode*			m_pHead;		//单链表头指针
};

#endif // !defined(AFX_ENTRAILWAY_H__47F3190A_8960_41DA_BCC5_3E30439BB9F7__INCLUDED_)























