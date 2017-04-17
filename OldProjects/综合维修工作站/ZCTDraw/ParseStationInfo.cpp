// ParseStationInfo.cpp: implementation of the CParseStationInfo class.
//
//////////////////////////////////////////////////////////////////////
//#include "io.h"
#include "stdafx.h"
#include "ParseStationInfo.h"
#include "ZCTWnd.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CParseStationInfo::CParseStationInfo()
{
	m_pParent = NULL;
	m_bNewMsktabed = FALSE;
}

CParseStationInfo::~CParseStationInfo()
{
	//ReleaseTables();
}

//Release buffer of mask tables; 
void CParseStationInfo::ReleaseTables()
{
	if(!m_bNewMsktabed) return;
	
	if(m_pMskTab->pXhTbl != NULL) 
	{
		delete m_pMskTab->pXhTbl;
		m_pMskTab->pXhTbl = NULL;
	}
	if(m_pMskTab->pQdTbl != NULL) 
	{
		delete m_pMskTab->pQdTbl;
		m_pMskTab->pQdTbl = NULL;
	}
	if(m_pMskTab->pDcTbl != NULL) 
	{
		delete m_pMskTab->pDcTbl;
		m_pMskTab->pDcTbl = NULL;
	}
	if(m_pMskTab->pBsdTbl != NULL)
	{
		delete m_pMskTab->pBsdTbl;
		m_pMskTab->pBsdTbl = NULL;
	}
	if(m_pMskTab->pGndTbl != NULL)
	{
		delete m_pMskTab->pGndTbl;
		m_pMskTab->pGndTbl = NULL;
	}
	if(m_pMskTab!= NULL) 
	{
		delete m_pMskTab;
		m_pMskTab = NULL;
	}

}

LPBYTE CParseStationInfo::GetInfoTabOutBuf()
{
	return m_pMskTab->InfoTabOutBuf;
}

WORD CParseStationInfo::GetBsdTblSum()
{
	return m_pMskTab->nBsdTblSum;
}

BOOL CParseStationInfo::ReadMask(CString strMaskFile)
{
	m_pMskTab = new MASKTABLE;
	ZeroMemory(m_pMskTab, sizeof(MASKTABLE));
	ZeroMemory(m_pMskTab->LieXinTbl,DATABUFFER_SIZE);
	ZeroMemory(m_pMskTab->DiaoXinTbl,DATABUFFER_SIZE);
	ZeroMemory(m_pMskTab->DaoChaTbl,DATABUFFER_SIZE);
	ZeroMemory(m_pMskTab->QuDuanTbl,DATABUFFER_SIZE);
	ZeroMemory(m_pMskTab->BiaoShiDengTbl,DATABUFFER_SIZE*BIT_SIZE*2);
	ZeroMemory(m_pMskTab->GongNengDengTbl,DATABUFFER_SIZE);
	ZeroMemory(m_pMskTab->InfoTabOutBuf,DATABUFFER_SIZE);

	m_bNewMsktabed = TRUE;

	if( !ReadMaskTbl(strMaskFile) )
	{
		ReleaseTables();
		AfxMessageBox( _T("无法完成码位表文件的读取!\r\n") + strMaskFile);
		return FALSE;
	}
	
	return TRUE;
}

//Read mask table 
BOOL CParseStationInfo::ReadMaskTbl(LPCTSTR szIniFile)
{
	int i;
	char buf[256];
	CString strSequence;

	m_pMskTab->nBitmapLen = 0;
	// 确定码位最大长度的宏函数
	#define GetMaxBmpLen(a) m_pMskTab->nBitmapLen = max( ((a)+7)/8, m_pMskTab->nBitmapLen );

	// read [Xin Hao Table]
	#define XHSECTION "Xin Hao Table"
	m_pMskTab->nXhTblSum = ::GetPrivateProfileInt( XHSECTION, "Sum", 0, szIniFile );
	if( m_pMskTab->nXhTblSum > 0 )
	{
		m_pMskTab->pXhTbl =  new XHTABLE[m_pMskTab->nXhTblSum];
		if( m_pMskTab->pXhTbl == NULL ) return FALSE;
		ZeroMemory( m_pMskTab->pXhTbl, m_pMskTab->nXhTblSum );

		for( i=0; i<m_pMskTab->nXhTblSum; i++ )
		{
			strSequence.Format( "%u", i+1 );
			if( ::GetPrivateProfileString( XHSECTION, strSequence, "", buf, sizeof(buf), szIniFile ) == 0 )
				return FALSE;
			sscanf( buf, "%d %d	%d %d %d %d	%d %d %d %d	%d %d %d %d	%d %d %d %d	%s", 
				&m_pMskTab->pXhTbl[i].LDevNo, &m_pMskTab->pXhTbl[i].DDevNo, 
				&m_pMskTab->pXhTbl[i].GBit,&m_pMskTab->pXhTbl[i].RBit,&m_pMskTab->pXhTbl[i].WBit,
				&m_pMskTab->pXhTbl[i].YBit,&m_pMskTab->pXhTbl[i].DGBit,&m_pMskTab->pXhTbl[i].GYBit,
				&m_pMskTab->pXhTbl[i].DYBit,&m_pMskTab->pXhTbl[i].YSYBit,&m_pMskTab->pXhTbl[i].RWBit,
				&m_pMskTab->pXhTbl[i].WSBit,&m_pMskTab->pXhTbl[i].RSBit,&m_pMskTab->pXhTbl[i].YSBit,
				&m_pMskTab->pXhTbl[i].GSBit,&m_pMskTab->pXhTbl[i].DSBit,&m_pMskTab->pXhTbl[i].LLtBit,
				&m_pMskTab->pXhTbl[i].DLtBit,buf );
			memmove( m_pMskTab->pXhTbl[i].Name, buf, sizeof(m_pMskTab->pXhTbl[i].Name)-1 );
			m_pMskTab->pXhTbl[i].Name[sizeof(m_pMskTab->pXhTbl[i].Name)-1] = 0;
			GetMaxBmpLen( m_pMskTab->pXhTbl[i].GBit );
			GetMaxBmpLen( m_pMskTab->pXhTbl[i].YBit );
			GetMaxBmpLen( m_pMskTab->pXhTbl[i].GYBit );
			GetMaxBmpLen( m_pMskTab->pXhTbl[i].DYBit );
			GetMaxBmpLen( m_pMskTab->pXhTbl[i].DGBit );
			GetMaxBmpLen( m_pMskTab->pXhTbl[i].YSYBit );
			GetMaxBmpLen( m_pMskTab->pXhTbl[i].RWBit );
			GetMaxBmpLen( m_pMskTab->pXhTbl[i].RBit );
			GetMaxBmpLen( m_pMskTab->pXhTbl[i].YSBit );
			GetMaxBmpLen( m_pMskTab->pXhTbl[i].RSBit );
			GetMaxBmpLen( m_pMskTab->pXhTbl[i].GSBit );
			GetMaxBmpLen( m_pMskTab->pXhTbl[i].DSBit );
			GetMaxBmpLen( m_pMskTab->pXhTbl[i].WBit );
			GetMaxBmpLen( m_pMskTab->pXhTbl[i].WSBit );
			GetMaxBmpLen( m_pMskTab->pXhTbl[i].LLtBit );
			GetMaxBmpLen( m_pMskTab->pXhTbl[i].DLtBit );
		}
	}
	// read [Qu Duan Table]
	#define QDSECTION "Qu Duan Table"
	m_pMskTab->nQdTblSum = ::GetPrivateProfileInt( QDSECTION, "Sum", 0, szIniFile );
	if( m_pMskTab->nQdTblSum > 0 )
	{
		m_pMskTab->pQdTbl = new QDTABLE[m_pMskTab->nQdTblSum];
		if( m_pMskTab->pQdTbl == NULL ) return FALSE;
		ZeroMemory( m_pMskTab->pQdTbl, m_pMskTab->nQdTblSum );

		for( i=0; i<m_pMskTab->nQdTblSum; i++ )
		{
			strSequence.Format( "%u", i+1 );
			if( ::GetPrivateProfileString( QDSECTION, strSequence, "", buf, sizeof(buf), szIniFile ) == 0 )
				return FALSE;
			sscanf( buf, "%u %u %u %s", &m_pMskTab->pQdTbl[i].DevNo, &m_pMskTab->pQdTbl[i].ZBit,
				&m_pMskTab->pQdTbl[i].SBit,buf ) ;
			memmove( m_pMskTab->pQdTbl[i].Name, buf, sizeof(m_pMskTab->pQdTbl[i].Name)-1 );
			m_pMskTab->pQdTbl[i].Name[sizeof(m_pMskTab->pQdTbl[i].Name)-1] = 0;

			GetMaxBmpLen( m_pMskTab->pQdTbl[i].ZBit );
			GetMaxBmpLen( m_pMskTab->pQdTbl[i].SBit );			
		}
	}
	// read [Dao Cha Table]
	#define DCSECTION "Dao Cha Table"
	m_pMskTab->nDcTblSum = ::GetPrivateProfileInt( DCSECTION, "Sum", 0, szIniFile );
	if( m_pMskTab->nDcTblSum > 0 )
	{
		m_pMskTab->pDcTbl = new DCTABLE[m_pMskTab->nDcTblSum];
		if( m_pMskTab->pDcTbl == NULL ) return FALSE;
		ZeroMemory( m_pMskTab->pDcTbl, m_pMskTab->nDcTblSum );

		for( i=0; i<m_pMskTab->nDcTblSum; i++ )
		{
			strSequence.Format( "%u", i+1 );
			if( ::GetPrivateProfileString( DCSECTION, strSequence, "", buf, sizeof(buf), szIniFile ) == 0 )
				return FALSE;
			sscanf( buf, "%u %u %u %u %u %s", &m_pMskTab->pDcTbl[i].DevNo,&m_pMskTab->pDcTbl[i].DBit,
				&m_pMskTab->pDcTbl[i].FBit,&m_pMskTab->pDcTbl[i].DSBit,
				&m_pMskTab->pDcTbl[i].DFBit,buf ) ;
			memmove( m_pMskTab->pDcTbl[i].Name, buf, sizeof(m_pMskTab->pDcTbl[i].Name)-1 );
			m_pMskTab->pDcTbl[i].Name[sizeof(m_pMskTab->pDcTbl[i].Name)-1] = 0;

			GetMaxBmpLen( m_pMskTab->pDcTbl[i].DBit );
			GetMaxBmpLen( m_pMskTab->pDcTbl[i].FBit );
			GetMaxBmpLen( m_pMskTab->pDcTbl[i].DSBit );
			GetMaxBmpLen( m_pMskTab->pDcTbl[i].DFBit );
		}
	}
	// read [Biao Shi Deng Table]
	#define BSDSECTION "Biao Shi Deng Table"
	m_pMskTab->nBsdTblSum = ::GetPrivateProfileInt( BSDSECTION, "Sum", 0, szIniFile );
	if( m_pMskTab->nBsdTblSum > 0 )
	{
		m_pMskTab->pBsdTbl = new BSDTABLE[m_pMskTab->nBsdTblSum];
		if( m_pMskTab->pBsdTbl == NULL ) return FALSE;
		ZeroMemory( m_pMskTab->pBsdTbl, m_pMskTab->nBsdTblSum );

		for( i=0; i<m_pMskTab->nBsdTblSum; i++ )
		{
			strSequence.Format( "%u", i+1 );
			if( ::GetPrivateProfileString( BSDSECTION, strSequence, "", buf, sizeof(buf), szIniFile ) == 0 )
				return FALSE;
			sscanf( buf, "%d %d	%d %d %d %d	%d %s", 
				&m_pMskTab->pBsdTbl[i].type, &m_pMskTab->pBsdTbl[i].index, 
				&m_pMskTab->pBsdTbl[i].GBit,&m_pMskTab->pBsdTbl[i].RBit,&m_pMskTab->pBsdTbl[i].WBit,
				&m_pMskTab->pBsdTbl[i].YBit,&m_pMskTab->pBsdTbl[i].FBit,buf );
			memmove( m_pMskTab->pBsdTbl[i].Name, buf, sizeof(m_pMskTab->pBsdTbl[i].Name)-1 );
			m_pMskTab->pBsdTbl[i].Name[sizeof(m_pMskTab->pBsdTbl[i].Name)-1] = 0;
			GetMaxBmpLen( m_pMskTab->pBsdTbl[i].GBit );
			GetMaxBmpLen( m_pMskTab->pBsdTbl[i].RBit );	
			GetMaxBmpLen( m_pMskTab->pBsdTbl[i].WBit );		
			GetMaxBmpLen( m_pMskTab->pBsdTbl[i].YBit );
			GetMaxBmpLen( m_pMskTab->pBsdTbl[i].FBit );
			
		}
	}

	// read [Gong Neng Deng Table]
	#define GNDSECTION "Gong Neng Deng Table"
	m_pMskTab->nGndTblSum = ::GetPrivateProfileInt( GNDSECTION, "Sum", 0, szIniFile );
	if( m_pMskTab->nGndTblSum > 0 )
	{
		m_pMskTab->pGndTbl = new GNDTABLE[m_pMskTab->nGndTblSum];
		if( m_pMskTab->pGndTbl == NULL ) return FALSE;
		ZeroMemory( m_pMskTab->pGndTbl, m_pMskTab->nGndTblSum );

		for( i=0; i<m_pMskTab->nGndTblSum; i++ )
		{
			strSequence.Format( "%u", i+1 );
			if( ::GetPrivateProfileString( GNDSECTION, strSequence, "", buf, sizeof(buf), szIniFile ) == 0 )
				return FALSE;
			sscanf( buf, "%d %d	%d %s", 
				&m_pMskTab->pGndTbl[i].type, &m_pMskTab->pGndTbl[i].offest, 
				&m_pMskTab->pGndTbl[i].SBit,buf );
			memmove( m_pMskTab->pGndTbl[i].Name, buf, sizeof(m_pMskTab->pGndTbl[i].Name)-1 );
			m_pMskTab->pGndTbl[i].Name[sizeof(m_pMskTab->pGndTbl[i].Name)-1] = 0;
			GetMaxBmpLen( m_pMskTab->pGndTbl[i].SBit );
		}
	}
	
	#undef GetMaxBmpLen

	if( m_pMskTab->nBitmapLen > DATABUFFER_SIZE ) return FALSE;

	return TRUE;
}

/*
**函数：TransactData(CZCTWnd* pParent,BYTE* pBuf,WORD wLen, BYTE byFrame)
**功能：处理站场表示数据
**参数：UINT nNo  端口控制结构下标 
**      BYTE* pBuf 站场表示数据
**      WORD wLen  站场表示数据长度
**		BYTE byFrame 帧类型（站场帧和站场变化帧）
*/
void CParseStationInfo::TransactData(CZCTWnd* pParent,BYTE* pBuf,WORD wLen, BYTE byFrame)
{
	WORD wBit;
	BYTE bValue = 0;
	int i,j,k,n;

	if(NULL == pParent) return;
	m_pParent = pParent;

	if (byFrame == SSDI)
	{
		for (j=0; j<wLen; j++)
		{
			for(i=1; i<=8; i++)
			{
				bValue = 0;
				n = 1;
				for(k=1; k<i; k++) n *= 2;
				//从低位到高位处理
				if ((pBuf[j] & n) > 0) bValue = 1;
				ParseMaskTable(j*8+i, bValue,TRUE);
			}
		}
	}
	else if (byFrame == SSDCI)
	{
		for (i = 0; i < wLen; )
		{		
			wBit = *(WORD*)(pBuf + i);	
			bValue = (wBit & 0x8000) >> 15;
			wBit &= 0x7FFF; 		
			if ( wBit == 0 ) 
			{			
				i += 2;
				continue;
			}
			ParseMaskTable(wBit,bValue,FALSE);
			i += 2;
		}		
	}

	SetInfoTab(byFrame);	
}

/*
**函数：SetInfoTab(BYTE bFrame)
**功能：将解析后的数据放到一缓冲区中(InfoTabOutBuf),待调用.
**参数：BYTE bFrame 帧类型
*/  
void CParseStationInfo::SetInfoTab(BYTE bFrame)
{
	int i,nPos;
	WORD wLNo,wDNo,wQdDevNo,wDcDevNo,wBSDIndex,wBsdType;

	BYTE* pBuf = m_pMskTab->InfoTabOutBuf;

//	pBuf[0] = bFrame;//帧类型
//	*(WORD*)(pBuf+1) = nStationNo;//站码
	pBuf[3] = 0xc0;//列信状态域起始标志
	nPos = 4;
	for(i = 0; i < m_pMskTab->nXhTblSum; i++)
	{
		wLNo = m_pMskTab->pXhTbl[i].LDevNo;
		if (wLNo > 0)
		{
			pBuf[nPos] = m_pMskTab->LieXinTbl[wLNo];
			nPos++;
		}
	}
	pBuf[nPos] = 0xc1;//调信状态域起始标志
	nPos++;
	for(i = 0; i < m_pMskTab->nXhTblSum; i++)
	{
		wDNo = m_pMskTab->pXhTbl[i].DDevNo;	
		if (wDNo > 0) 
		{
			pBuf[nPos] = m_pMskTab->DiaoXinTbl[wDNo];
			nPos++;
		}
	}
	pBuf[nPos] = 0xc2;//区段状态域起始标志
	nPos++;
	for(i = 0; i < m_pMskTab->nQdTblSum; i++)
	{
		wQdDevNo = m_pMskTab->pQdTbl[i].DevNo;
		if (wQdDevNo == 0) continue;
		pBuf[nPos] = m_pMskTab->QuDuanTbl[wQdDevNo];
		nPos++;
	}
	pBuf[nPos] = 0xc3;//道岔状态域起始标志
	nPos++;
	for(i = 0; i < m_pMskTab->nDcTblSum; i++)
	{
		wDcDevNo = m_pMskTab->pDcTbl[i].DevNo;
		if (wDcDevNo == 0) continue;
		pBuf[nPos] = m_pMskTab->DaoChaTbl[wDcDevNo];
		nPos++;
	}
	pBuf[nPos] = 0xc4;//表示灯状态域起始标志
	nPos++;
	for(i = 0; i < m_pMskTab->nBsdTblSum; i++)
	{
		wBsdType = m_pMskTab->pBsdTbl[i].type;
		wBSDIndex = m_pMskTab->pBsdTbl[i].index;
		if (wBsdType == 0&&wBSDIndex == 0) continue;
		pBuf[nPos] = m_pMskTab->BiaoShiDengTbl[i+1][0];
		nPos++;
	}
	pBuf[nPos] = 0xC5; //功能灯状态起始标志
	nPos++;
	for(i = 0; i<m_pMskTab->nGndTblSum; i++)
	{
		pBuf[nPos] = m_pMskTab->GongNengDengTbl[i+1];
		nPos++;
	}	
}

/*
** 函数：ParseMaskTable(int nBit,BYTE bValue)
** 功能：解析码位(对于给定的码位,对照码位信息表,获得相应值).
** 参数：int nBit  码位信息表位置
**       BYTE bValue  位值(0,1)
*/
void CParseStationInfo::ParseMaskTable(int nBit,BYTE bValue,BOOL bAll)
{
	WORD wLNo,wDNo,wQdDevNo,wDcDevNo,wBsdType,wBsdIndex,wBsdNo,wGndType,wGndOffset,wGndNo;

	//列信、调信
	for (UINT i = 0; i<m_pMskTab->nXhTblSum; i++)
	{
		wLNo = m_pMskTab->pXhTbl[i].LDevNo;
		wDNo = m_pMskTab->pXhTbl[i].DDevNo; 
		if (nBit == m_pMskTab->pXhTbl[i].GBit && bValue == 1) 
		{
			if (wLNo > 0) m_pMskTab->LieXinTbl[wLNo] = COL_GREEN;
			if (wDNo > 0) m_pMskTab->DiaoXinTbl[wDNo] = COL_GREEN;
			return;
		}
		if (nBit == m_pMskTab->pXhTbl[i].YBit && bValue == 1)
		{
			if (wLNo > 0) m_pMskTab->LieXinTbl[wLNo] = COL_YELLOW;
			if (wDNo > 0) m_pMskTab->DiaoXinTbl[wDNo] = COL_YELLOW;
			return;
		}
		if (nBit == m_pMskTab->pXhTbl[i].GYBit && bValue == 1) 
		{
			if (wLNo > 0) m_pMskTab->LieXinTbl[wLNo] = COL_GY;
			if (wDNo > 0) m_pMskTab->DiaoXinTbl[wDNo] = COL_GY;
			return;
		}
		if (nBit == m_pMskTab->pXhTbl[i].DYBit && bValue == 1)
		{
			if (wLNo > 0) m_pMskTab->LieXinTbl[wLNo] = COL_DY;
			if (wDNo > 0) m_pMskTab->DiaoXinTbl[wDNo] = COL_DY;
			return;
		}
		if (nBit == m_pMskTab->pXhTbl[i].DGBit && bValue == 1) 
		{
			if (wLNo > 0) m_pMskTab->LieXinTbl[wLNo] = COL_DG;
			if (wDNo > 0) m_pMskTab->DiaoXinTbl[wDNo] = COL_DG;
			return;
		}
		if (nBit == m_pMskTab->pXhTbl[i].YSYBit && bValue == 1)
		{
			if (wLNo > 0) m_pMskTab->LieXinTbl[wLNo] = COL_YFY;
			if (wDNo > 0) m_pMskTab->DiaoXinTbl[wDNo] = COL_YFY;
			return;
		}
		if (nBit == m_pMskTab->pXhTbl[i].RWBit && bValue == 1)
		{
			if (wLNo > 0) m_pMskTab->LieXinTbl[wLNo] = COL_RW;
			if (wDNo > 0) m_pMskTab->DiaoXinTbl[wDNo] = COL_RW;
			return;
		}
		if (nBit == m_pMskTab->pXhTbl[i].RBit && bValue == 1)
		{
			if (wLNo > 0) m_pMskTab->LieXinTbl[wLNo] = COL_RED;
			if (wDNo > 0) m_pMskTab->DiaoXinTbl[wDNo] = COL_RED;
			return;
		}
		if (nBit == m_pMskTab->pXhTbl[i].YSBit && bValue == 1)
		{
			if (wLNo > 0) m_pMskTab->LieXinTbl[wLNo] = COL_YF;
			if (wDNo > 0) m_pMskTab->DiaoXinTbl[wDNo] = COL_YF;
			return;
		}
		if (nBit == m_pMskTab->pXhTbl[i].GSBit && bValue == 1)
		{
			if (wLNo > 0) m_pMskTab->LieXinTbl[wLNo] = COL_GF;
			if (wDNo > 0) m_pMskTab->DiaoXinTbl[wDNo] = COL_GF;
			return;
		}
		if (nBit == m_pMskTab->pXhTbl[i].WBit && bValue == 1)
		{
			if (wLNo > 0) m_pMskTab->LieXinTbl[wLNo] = COL_WITHE;
			if (wDNo > 0) m_pMskTab->DiaoXinTbl[wDNo] = COL_WITHE;
			return;
		}
		if (nBit == m_pMskTab->pXhTbl[i].WSBit && bValue == 1)
		{
			if (wLNo > 0) m_pMskTab->LieXinTbl[wLNo] = COL_WF;
			if (wDNo > 0) m_pMskTab->DiaoXinTbl[wDNo] = COL_WF;
			return;
		}
		if (nBit == m_pMskTab->pXhTbl[i].RSBit && bValue == 1)
		{
			if (wLNo > 0) m_pMskTab->LieXinTbl[wLNo] = COL_RF;
			if (wDNo > 0) m_pMskTab->DiaoXinTbl[wDNo] = COL_RF;
			return;
		}
		if (nBit == m_pMskTab->pXhTbl[i].DSBit && bValue == 1)
		{
			if (wLNo > 0) m_pMskTab->LieXinTbl[wLNo] = COL_FB;
			if (wDNo > 0) m_pMskTab->DiaoXinTbl[wDNo] = COL_FB;
			return;
		}
	}
	//区段
	for (int i = 0; i<m_pMskTab->nQdTblSum; i++)
	{
		wQdDevNo = m_pMskTab->pQdTbl[i].DevNo;
		if (wQdDevNo == 0) continue;
		if (nBit == m_pMskTab->pQdTbl[i].ZBit && bValue == 1)//有车占用
		{
			m_pMskTab->QuDuanTbl[wQdDevNo] &= 0xF3;//置3、4位为零
			m_pMskTab->QuDuanTbl[wQdDevNo] |= 0x04;
			return;
		}
		if (nBit == m_pMskTab->pQdTbl[i].ZBit && bValue == 0)//无车占用
		{
			m_pMskTab->QuDuanTbl[wQdDevNo] &= 0xF3;//置3、4位为零
			m_pMskTab->QuDuanTbl[wQdDevNo] |= 0x08;
			return;
		}
		if (nBit == m_pMskTab->pQdTbl[i].SBit && bValue == 1)//锁闭
		{
			m_pMskTab->QuDuanTbl[wQdDevNo] &= 0xFC;//置1、2位为零
			m_pMskTab->QuDuanTbl[wQdDevNo] |= 0x01;
			return;
		}
		if(nBit == m_pMskTab->pQdTbl[i].SBit && bValue == 0)//未锁闭
		{
			m_pMskTab->QuDuanTbl[wQdDevNo] &= 0xFC;//置1、2位为零
			m_pMskTab->QuDuanTbl[wQdDevNo] |= 0x02;
			return;
		}
	}
	//道岔
	for (int i = 0; i<m_pMskTab->nDcTblSum; i++)
	{
		wDcDevNo = m_pMskTab->pDcTbl[i].DevNo;
		if (wDcDevNo == 0) continue;
		if (nBit == m_pMskTab->pDcTbl[i].DBit && bValue == 1)//定表
		{
			m_pMskTab->DaoChaTbl[wDcDevNo] &= 0xFD;//置2位为零
			m_pMskTab->DaoChaTbl[wDcDevNo] |= 0x02;
			return;
		}else if (nBit == m_pMskTab->pDcTbl[i].DBit && bValue == 0)
		{
			m_pMskTab->DaoChaTbl[wDcDevNo] &= 0xFD;//置2位为零
			return;
		}
		if (nBit == m_pMskTab->pDcTbl[i].FBit && bValue == 1)//反表
		{
			m_pMskTab->DaoChaTbl[wDcDevNo] &= 0xFE;//置1位为零
			m_pMskTab->DaoChaTbl[wDcDevNo] |= 0x01;
			return;
		}else if (nBit == m_pMskTab->pDcTbl[i].FBit && bValue == 0)
		{
			m_pMskTab->DaoChaTbl[wDcDevNo] &= 0xFE;//置1位为零
			return;
		}
		if (nBit == m_pMskTab->pDcTbl[i].DSBit && bValue == 1)//单锁
		{
			m_pMskTab->DaoChaTbl[wDcDevNo] &= 0xFB;//置3位为零
			m_pMskTab->DaoChaTbl[wDcDevNo] |= 0x04;
			return;
		}else if (nBit == m_pMskTab->pDcTbl[i].DSBit && bValue == 0)
		{
			m_pMskTab->DaoChaTbl[wDcDevNo] &= 0xFB;//置3位为零
			return;
		}
		if (nBit == m_pMskTab->pDcTbl[i].DFBit && bValue == 1)//单封
		{
			m_pMskTab->DaoChaTbl[wDcDevNo] &= 0xF7;//置4位为零
			m_pMskTab->DaoChaTbl[wDcDevNo] |= 0x08;
			return;
		}else if (nBit == m_pMskTab->pDcTbl[i].DFBit && bValue == 0) 
		{
			m_pMskTab->DaoChaTbl[wDcDevNo] &= 0xF7;//置4位为零
			return;
		}
	}
	//表示灯
	for (int i = 0; i<m_pMskTab->nBsdTblSum; i++)
	{
		wBsdType = m_pMskTab->pBsdTbl[i].type;
		wBsdIndex = m_pMskTab->pBsdTbl[i].index;
		if (nBit == m_pMskTab->pBsdTbl[i].GBit) 
		{
			POSITION pos = m_pParent->m_BSDList.GetHeadPosition();
			while(pos!=NULL)
			{
				CBSD *pBSD=(CBSD *)m_pParent->m_BSDList.GetNext(pos);
				if((pBSD->m_iType == wBsdType)&&pBSD->m_iIndex == wBsdIndex)
				{
					wBsdNo = pBSD->m_wBSDNo;
					if(bValue == 0)
					{
						if(m_pMskTab->BiaoShiDengTbl[wBsdNo][1]==nBit)
						{
							m_pMskTab->BiaoShiDengTbl[wBsdNo][0] = COL_BLACK;							
							return;
						}
					}
					if(bValue == 1)
					{
						if(m_pMskTab->BiaoShiDengTbl[wBsdNo][2]==1)
						{
							m_pMskTab->BiaoShiDengTbl[wBsdNo][0] = COL_GF;
						//	m_pMskTab->BiaoShiDengTbl[wBsdNo][1] = nBit;
						}
						else
						{
							m_pMskTab->BiaoShiDengTbl[wBsdNo][0] = COL_GREEN;
							m_pMskTab->BiaoShiDengTbl[wBsdNo][1] = nBit;
						}
						
						return;
					}
				}
				if(pBSD->m_iType==BSD_TYPE_ZDJFC && pBSD->m_iIndex==wBsdIndex
					                             && (wBsdType == 101 || wBsdType == 102))
				{
					wBsdNo = pBSD->m_wBSDNo;
					if(bValue == 0)
					{
						if(m_pMskTab->BiaoShiDengTbl[wBsdNo][1]==nBit)
						{
							m_pMskTab->BiaoShiDengTbl[wBsdNo][0] = COL_BLACK;
							
							return;
						}
					}
					if(bValue==1)
					{
					//	bGBit = true;
						m_pMskTab->BiaoShiDengTbl[wBsdNo][0] = COL_GREEN;
						pBSD->m_iTemp = wBsdType;
						m_pMskTab->BiaoShiDengTbl[wBsdNo][1] = nBit;
						
						
						return;
					}
				}				
			}
		}
		if (nBit == m_pMskTab->pBsdTbl[i].RBit) 
		{
			POSITION pos = m_pParent->m_BSDList.GetHeadPosition();
			while(pos!=NULL)
			{
				CBSD *pBSD=(CBSD *)m_pParent->m_BSDList.GetNext(pos);
				if((pBSD->m_iType == wBsdType)&&pBSD->m_iIndex == wBsdIndex)
				{
					wBsdNo = pBSD->m_wBSDNo;
					
					if(bValue == 0)
					{
						if(m_pMskTab->BiaoShiDengTbl[wBsdNo][1]==nBit)
						{
							m_pMskTab->BiaoShiDengTbl[wBsdNo][0] = COL_BLACK;
							
							return;
						}
					}
					if(bValue==1)
					{
						if(m_pMskTab->BiaoShiDengTbl[wBsdNo][2]==1)
						{
							m_pMskTab->BiaoShiDengTbl[wBsdNo][0] = COL_RF;
						//	m_pMskTab->BiaoShiDengTbl[wBsdNo][1] = nBit;
						}
						else
						{
							m_pMskTab->BiaoShiDengTbl[wBsdNo][0] = COL_RED;
							m_pMskTab->BiaoShiDengTbl[wBsdNo][1] = nBit;
						}
						
						return;
					}
					
				}
				if(pBSD->m_iType==BSD_TYPE_ZDJFC && pBSD->m_iIndex==wBsdIndex
												 && (wBsdType == 101 || wBsdType == 102))
				{
					wBsdNo = pBSD->m_wBSDNo;
					if(bValue == 0)
					{
						if(m_pMskTab->BiaoShiDengTbl[wBsdNo][1]==nBit)
						{
							m_pMskTab->BiaoShiDengTbl[wBsdNo][0] = COL_BLACK;
							
							return;
						}
					}
					if(bValue==1)
					{
					//	bGBit = true;
						m_pMskTab->BiaoShiDengTbl[wBsdNo][0] = COL_RED;
						pBSD->m_iTemp = wBsdType;
						m_pMskTab->BiaoShiDengTbl[wBsdNo][1] = nBit;	
						return;
					}
				}		
			}
		}

		if (nBit == m_pMskTab->pBsdTbl[i].WBit) 
		{
			POSITION pos = m_pParent->m_BSDList.GetHeadPosition();
			while(pos!=NULL)
			{
				CBSD *pBSD=(CBSD *)m_pParent->m_BSDList.GetNext(pos);
				if((pBSD->m_iType == wBsdType)&&pBSD->m_iIndex == wBsdIndex)
				{
					wBsdNo = pBSD->m_wBSDNo;
					
					if(bValue == 0)
					{
						if(m_pMskTab->BiaoShiDengTbl[wBsdNo][1]==nBit)
						{
							m_pMskTab->BiaoShiDengTbl[wBsdNo][0] = COL_BLACK;
							
							return;
						}
					}
					if(bValue==1)
					{
						if(m_pMskTab->BiaoShiDengTbl[wBsdNo][2]==1)
						{
							m_pMskTab->BiaoShiDengTbl[wBsdNo][0] = COL_WF;
						//	m_pMskTab->BiaoShiDengTbl[wBsdNo][1] = nBit;
						}
						else
						{
							m_pMskTab->BiaoShiDengTbl[wBsdNo][0] = COL_WITHE;
							m_pMskTab->BiaoShiDengTbl[wBsdNo][1] = nBit;
						}
						
						return;
					}
					
				}
				if(pBSD->m_iType==BSD_TYPE_ZDJFC && pBSD->m_iIndex == wBsdIndex
												 && (wBsdType == 101 || wBsdType == 102))
				{
					wBsdNo = pBSD->m_wBSDNo;
					if(bValue == 0)
					{
						if(m_pMskTab->BiaoShiDengTbl[wBsdNo][1]==nBit)
						{
							m_pMskTab->BiaoShiDengTbl[wBsdNo][0] = COL_BLACK;
							
							return;
						}
					}
					if(bValue==1)
					{
					//	bGBit = true;
						m_pMskTab->BiaoShiDengTbl[wBsdNo][0] = COL_WITHE;
						pBSD->m_iTemp = wBsdType;
						m_pMskTab->BiaoShiDengTbl[wBsdNo][1] = nBit;
						
						
						return;
					}
				}		
			}
		}

		if (nBit == m_pMskTab->pBsdTbl[i].YBit) 
		{
			POSITION pos = m_pParent->m_BSDList.GetHeadPosition();
			while(pos!=NULL)
			{
				CBSD *pBSD=(CBSD *)m_pParent->m_BSDList.GetNext(pos);
				if((pBSD->m_iType == wBsdType)&&pBSD->m_iIndex == wBsdIndex)
				{
					wBsdNo = pBSD->m_wBSDNo;
					
					if(bValue == 0)
					{
						if(m_pMskTab->BiaoShiDengTbl[wBsdNo][1]==nBit)
						{
							m_pMskTab->BiaoShiDengTbl[wBsdNo][0] = COL_BLACK;
							
							return;
						}
					}
					if(bValue==1)
					{
						if(m_pMskTab->BiaoShiDengTbl[wBsdNo][2]==1)
						{
							m_pMskTab->BiaoShiDengTbl[wBsdNo][0] = COL_YF;
						//	m_pMskTab->BiaoShiDengTbl[wBsdNo][1] = nBit;
						}
						else
						{
							m_pMskTab->BiaoShiDengTbl[wBsdNo][0] = COL_YELLOW;
							m_pMskTab->BiaoShiDengTbl[wBsdNo][1] = nBit;
						}
						
						return;
					}
					
				}
				if(pBSD->m_iType==BSD_TYPE_ZDJFC && pBSD->m_iIndex==wBsdIndex
												 && (wBsdType == 101 || wBsdType == 102))
				{
					wBsdNo = pBSD->m_wBSDNo;
					if(bValue == 0)
					{
						if(m_pMskTab->BiaoShiDengTbl[wBsdNo][1]==nBit)
						{
							m_pMskTab->BiaoShiDengTbl[wBsdNo][0] = COL_BLACK;
							
							return;
						}
					}
					if(bValue==1)
					{
					//	bGBit = true;
						m_pMskTab->BiaoShiDengTbl[wBsdNo][0] = COL_YELLOW;
						pBSD->m_iTemp = wBsdType;
						m_pMskTab->BiaoShiDengTbl[wBsdNo][1] = nBit;
						
						
						return;
					}
				}		
			}
		}

		if (nBit == m_pMskTab->pBsdTbl[i].FBit) 
		{
			POSITION pos = m_pParent->m_BSDList.GetHeadPosition();
			while(pos!=NULL)
			{
				CBSD *pBSD=(CBSD *)m_pParent->m_BSDList .GetNext(pos);
				if((pBSD->m_iType == wBsdType)&&pBSD->m_iIndex == wBsdIndex)
				{
					wBsdNo = pBSD->m_wBSDNo;
					
					if(bValue == 0)
					{
					//	if(m_pMskTab->BiaoShiDengTbl[wBsdNo][1]==nBit)
					//	{
							if(m_pMskTab->BiaoShiDengTbl[wBsdNo][0] == COL_GF||m_pMskTab->BiaoShiDengTbl[wBsdNo][0] == COL_GREEN)
								m_pMskTab->BiaoShiDengTbl[wBsdNo][0] = COL_GREEN;
							else if(m_pMskTab->BiaoShiDengTbl[wBsdNo][0] == COL_RF||m_pMskTab->BiaoShiDengTbl[wBsdNo][0] == COL_RED)
								m_pMskTab->BiaoShiDengTbl[wBsdNo][0] = COL_RED;
							else if(m_pMskTab->BiaoShiDengTbl[wBsdNo][0] == COL_WF||m_pMskTab->BiaoShiDengTbl[wBsdNo][0] == COL_WITHE)
								m_pMskTab->BiaoShiDengTbl[wBsdNo][0] = COL_WITHE;
							else if(m_pMskTab->BiaoShiDengTbl[wBsdNo][0] == COL_YF||m_pMskTab->BiaoShiDengTbl[wBsdNo][0] == COL_YELLOW)
								m_pMskTab->BiaoShiDengTbl[wBsdNo][0] = COL_YELLOW;
							else
								m_pMskTab->BiaoShiDengTbl[wBsdNo][0] = COL_BLACK;
							m_pMskTab->BiaoShiDengTbl[wBsdNo][2]=0;
							return;
					//	}
					}
					if(bValue==1)
					{
//						if(m_pMskTab->BiaoShiDengTbl[wBsdNo][1]==nBit)
//						{
							if(m_pMskTab->BiaoShiDengTbl[wBsdNo][0] == COL_GREEN)
								m_pMskTab->BiaoShiDengTbl[wBsdNo][0] = COL_GF;
							else if(m_pMskTab->BiaoShiDengTbl[wBsdNo][0] == COL_RED)
								m_pMskTab->BiaoShiDengTbl[wBsdNo][0] = COL_RF;
							else if(m_pMskTab->BiaoShiDengTbl[wBsdNo][0] == COL_WITHE)
								m_pMskTab->BiaoShiDengTbl[wBsdNo][0] = COL_WF;
							else if(m_pMskTab->BiaoShiDengTbl[wBsdNo][0] == COL_YELLOW)
								m_pMskTab->BiaoShiDengTbl[wBsdNo][0] = COL_YF;
							m_pMskTab->BiaoShiDengTbl[wBsdNo][2]=1;
							return;
//						}
					}
				}
			}
		}		
	}
	//功能灯
	for (int i = 0; i<m_pMskTab->nGndTblSum; i++)
	{
		wGndType = m_pMskTab->pGndTbl[i].type-1;
		wGndOffset = ((wGndType&0x0f)<<4)+m_pMskTab->pGndTbl[i].offest;
		if (nBit == m_pMskTab->pGndTbl[i].SBit) 
		{
			POSITION pos = m_pParent->m_FuncBtnList.GetHeadPosition();
			while(pos!=NULL)
			{
				CFuncBtn *pFuncBtn=(CFuncBtn *)m_pParent->m_FuncBtnList.GetNext(pos);
				if(pFuncBtn->m_iOffset == wGndOffset)
				{
					wGndNo = pFuncBtn->m_Index;
					if(bValue == 1)
					{
						m_pMskTab->GongNengDengTbl[wGndNo] = 1;
						return;
					}
					else
					{	
						m_pMskTab->GongNengDengTbl[wGndNo] = 0;
						return;
					}
				}
			}
		}
	}
					
}