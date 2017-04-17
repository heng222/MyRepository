// FrameTrainNoList.cpp: implementation of the CFrameTrainNoList class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "FrameTrainNoList.h"
#include "CommFunction.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFrameTrainNoList::CFrameTrainNoList()
{
	
}

CFrameTrainNoList::~CFrameTrainNoList()
{
	ClearList();
}

void CFrameTrainNoList::ClearList()
{
	while( GetHeadPosition() )
	{
		delete RemoveHead();
	}
}

BOOL CFrameTrainNoList::ReadFrameInf(CString strFileName,
				CSize sizeShrink/*=CSize(1,1)*/, CSize sizeExcursion/*=CSize(0,0)*/)
{
	//If the file is exist?
	CStdioFile stdFile;
	if (!stdFile.Open(strFileName,CFile::modeRead | CFile::shareDenyNone)) {
		TRACE("Can not open %s!\n",strFileName);
		return FALSE;
	}
	//
	ClearList();
	//读取车次框数目
	int m_nFrameNumber = GetPrivateProfileInt( "FRAMENUM","NUM", 0,strFileName );
	

	CString strLine,strKey;
	int i=1;
	while (stdFile.ReadString(strLine)) {
		strKey.Format("[FRAME%d]",i);
		
		if (strLine == strKey) {
			
			CFrameTrainNo* pFrame = new CFrameTrainNo;

			//frame ID
			stdFile.ReadString(strLine);
			pFrame->m_iFrameID = GetNFStr(strLine,0);

//
#ifdef _DEBUG
/*
if (pFrame->m_iFrameID%2 == 0) {
	pFrame->m_strContent.Format("%d",pFrame->m_iFrameID);
	if (pFrame->m_iFrameID%4==0) {
		pFrame->m_iDirection = CFrameTrainNo::FD_DOWN;
	}
	else{
		pFrame->m_iDirection = CFrameTrainNo::FD_UP;
		pFrame->m_iTimeExcur = -pFrame->m_iTimeExcur;
	}
	if (pFrame->m_iFrameID > 100) {
		pFrame->m_iTimeExcur = 0;
	}
}
//*/	
#endif

			//frame coordinates
			stdFile.ReadString(strLine);
			pFrame->m_pointPos.x = GetNFStr(strLine,0);
			pFrame->m_pointPos.y = GetNFStr(strLine,1);

			//frame size
			stdFile.ReadString(strLine);
			pFrame->m_size.cx = GetNFStr(strLine,0);
			pFrame->m_size.cy = GetNFStr(strLine,1);

			//Relative section
			stdFile.ReadString(strLine);
			pFrame->m_iSectRelNum = GetNFStr(strLine,0);
			ASSERT(pFrame->m_iSectRelNum < RELSECTMAXNUM);
			for(int n=0; n<pFrame->m_iSectRelNum; n++){
				pFrame->m_iSectRelID[n] = GetNFStr(strLine,n+1);
			}
			
			//
			i++;

			//
			pFrame->m_pointPos.x = pFrame->m_pointPos.x/sizeShrink.cx + sizeExcursion.cx;
			pFrame->m_pointPos.y = pFrame->m_pointPos.y/sizeShrink.cy + sizeExcursion.cy;
			AddTail(pFrame);
		}
	}

/*	
	//读取车次框数目
	int m_nFrameNumber = GetPrivateProfileInt( "FRAME","MAX_NUMBER", 0,strFileName );

	//Read the frame data
	char cTmp[200];
	CString strKey;
	for( int i=0; i<m_nFrameNumber; i++ ) 
	{
		CFrameTrainNo* pFrame = new CFrameTrainNo;
		//
		strKey.Format( "%d", i+1 );
		GetPrivateProfileString( "FRAME", strKey, "", cTmp, 200, strFileName );
		sscanf( cTmp, "%d %d %d %d %d %d %s",
			&(pFrame->m_pointPos.x), &(pFrame->m_pointPos.y),
			&(pFrame->m_size.cx),	&(pFrame->m_size.cy),
			&(pFrame->m_iFrameID),
			&(pFrame->m_iSectionRelID), (pFrame->m_strSectionName.GetBuffer(20))
			);
		pFrame->m_strSectionName.ReleaseBuffer();
		
		pFrame->m_pointPos.x = pFrame->m_pointPos.x/sizeShrink.cx + sizeExcursion.cx;
		pFrame->m_pointPos.y = pFrame->m_pointPos.y/sizeShrink.cy + sizeExcursion.cy;
		//
		AddTail(pFrame);
	}
*/
	//////////////////////////////////////////////////////////////////////////
/*	CStdioFile stdFile;
	CString strLine;
	stdFile.Open(strFileName+"a",CFile::modeCreate|CFile::modeWrite);
	stdFile.WriteString("[FRAMENUM]\n");
	strLine.Format("NUM=%d\n",GetCount());
	stdFile.WriteString(strLine);
	POSITION pos = GetHeadPosition();
	int j=0;
	while (pos) {
		CFrameTrainNo* pFrame = (CFrameTrainNo*)GetNext(pos);
		j++;
		strLine.Format("\n[FRAME%d]\n",j);
		stdFile.WriteString(strLine);

		strLine.Format("ID=%d\n",pFrame->m_iFrameID);
		stdFile.WriteString(strLine);

		strLine.Format("coordinates= %d %d\n",pFrame->m_pointPos.x,pFrame->m_pointPos.y);
		stdFile.WriteString(strLine);

		strLine.Format("size= %d %d\n",pFrame->m_size.cx,pFrame->m_size.cy);
		stdFile.WriteString(strLine);

		if (pFrame->m_iSectionRelID) {
			strLine.Format("SectionID= 1; %d \n",pFrame->m_iSectionRelID);
		}
		else
		{
			strLine.Format("SectionID= 0;\n");
		}
		
		stdFile.WriteString(strLine);
	}
	stdFile.Close();
*/
	//////////////////////////////////////////////////////////////////////////
	stdFile.Close();
	
	return TRUE;
}

BOOL CFrameTrainNoList::CreateFrames(CWnd* pParentWnd)
{
	ASSERT_VALID(pParentWnd);
	//
	POSITION	pos = GetHeadPosition();
	while ( pos )
	{
		CFrameTrainNo* pFrame = (CFrameTrainNo* )GetNext(pos);
		if (!pFrame->CreateFrame(pParentWnd)) {
			return FALSE;
		}
	}
	return TRUE;
}

void CFrameTrainNoList::ShowFrames(CDC* pDC,int nCmdShow)
{
	POSITION pos = GetHeadPosition();
	while ( pos )
	{
		CFrameTrainNo* pFrame = (CFrameTrainNo* )GetNext(pos);
		if (nCmdShow == SW_SHOW) {
			pFrame->RecalcLayout(pDC);
		}
		else
		{
			pFrame->ShowWindow(SW_HIDE);
		}
	}
}

void CFrameTrainNoList::UpdateFrameInf(int iFrameID, CString strInf,int iDirection)
{
	POSITION pos = GetHeadPosition();
	while (pos){
		CFrameTrainNo* pFrame = (CFrameTrainNo*)GetNext(pos);
		if( pFrame->m_iFrameID == iFrameID ){
			pFrame->UpdateContent(strInf,FALSE);
			pFrame->SetDirection(iDirection);
			break;
		}
	}
}

void CFrameTrainNoList::UpadateTimeExcur(int iFrameID, int iDirection, int iTimeExcur)
{
	POSITION pos = GetHeadPosition();
	while (pos){
		CFrameTrainNo* pFrame = (CFrameTrainNo*)GetNext(pos);
		if( pFrame->m_iFrameID == iFrameID ){
			pFrame->SetTimeExcur(iTimeExcur,FALSE);
			pFrame->SetDirection(iDirection);
			break;
		}
	}
}

void CFrameTrainNoList::ClearFrameContent()
{
	POSITION pos = GetHeadPosition();
	while (pos)	{
		CFrameTrainNo* pFrame = (CFrameTrainNo*)GetNext(pos);
		pFrame->UpdateContent("");
	}
}

CString CFrameTrainNoList::GetContBySectRel(int iSectRelID)
{
	POSITION pos = GetHeadPosition();
	while (pos)	{
		CFrameTrainNo* pFrame = (CFrameTrainNo*)GetNext(pos);
		for(int i=0; i<pFrame->m_iSectRelNum; i++)
		{
			if (pFrame->m_iSectRelID[i] == iSectRelID) {
				return pFrame->m_strContent;
			}
		}
	}
	return "";
}

CString CFrameTrainNoList::GetContByID(int iFrameID)
{
	POSITION pos = GetHeadPosition();
	while (pos)	{
		CFrameTrainNo* pFrame = (CFrameTrainNo*)GetNext(pos);
		if (pFrame->m_iFrameID == iFrameID) {
			return pFrame->m_strContent;
		}
	}
	return "";
}
int CFrameTrainNoList::GetFrameIDBySectRel(int iSectRelID)
{
	POSITION pos = GetHeadPosition();
	while (pos)	{
		CFrameTrainNo* pFrame = (CFrameTrainNo*)GetNext(pos);
		for(int i=0; i<pFrame->m_iSectRelNum; i++)
		{
			if (pFrame->m_iSectRelID[i] == iSectRelID) {
				return pFrame->m_iFrameID;
			}
		}
	}
	return 0;
}

void CFrameTrainNoList::InvalidateInf(BOOL bInfInvalid)
{
	POSITION pos = GetHeadPosition();
	while (pos)	{
		CFrameTrainNo* pFrame = (CFrameTrainNo*)GetNext(pos);
		pFrame->InvalidInf(bInfInvalid);
	}
}

