// BSD.h

#if !defined _BSD_h_
#define _BSD_h_
/*
(0-非进路调车 1-场联照查 2-场联接近 3-场联复示 4-机务段 5-驼峰控制 
6-驼峰复示 7-半自动闭塞接车 8-半自动闭塞发车 9-自动闭塞接发车 
10-自动闭塞监督区段 11-自动闭塞辅助 13-平面溜放 20、21-特殊表示 
100-CTC表示 103-仅用于CTC通讯的表示
)
(类型0/5/10/11/12/13/20/100为单灯式类型1/4/7/8/9/21为箭头式 
	类型3/6为信号机式 类型2为直线式)

*/

/* BiaoShiDeng Type */
#define BSD_TYPE_FJD     0   /* 非进路调车 */
#define BSD_TYPE_CLZC    1   /* 场联照查 */
#define BSD_TYPE_CLJJ    2   /* 场联接近 */
#define BSD_TYPE_CLFS    3   /* 场联复示 */
#define BSD_TYPE_JWD     4   /* 机务段 */
#define BSD_TYPE_TFKZ    5   /* 驼峰控制*/
#define BSD_TYPE_TFFS    6   /* 驼峰复示 */
#define BSD_TYPE_BZDJC   7   /* 半自动闭塞接车 */
#define BSD_TYPE_BZDFC   8   /* 半自动闭塞发车*/
#define BSD_TYPE_ZDJFC   9   /* 自动闭塞接发车*/
#define BSD_TYPE_ZDJDQD 10   /* 自动闭塞监督区段zi dong bi sai jian du qu duan */
#define BSD_TYPE_ZDFZ   11   /* 自动闭塞辅助zi dong bi sai fu zhu */
#define BSD_TYPE_TS     20   /* 特殊标识te shu biao shi (single light mode)*/
#define BSD_TYPE_TSARR  21   /* 特殊标识te shu biao shi (arrow mode)*/
#define BSD_TYPE_KZMS   100  /* 控制模式(single light mode)*/

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

