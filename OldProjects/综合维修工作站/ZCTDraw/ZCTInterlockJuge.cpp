// ZCTInterlockJuge.cpp: implementation of the CZCTInterlockJuge class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZCTInterlockJuge.h"
#include "ZCTWnd.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CZCTInterlockJuge::CZCTInterlockJuge()
{
}
CZCTInterlockJuge::~CZCTInterlockJuge()
{
}

void CZCTInterlockJuge::SetInf(CZCTWnd *pParentObt)
{
	m_pParentObject = pParentObt;
}

/*========================================================================
	Name:		����������ť֮���Ƿ���ڽ�·
    ----------------------------------------------------------
	Params:
				strCause        ����·������ʱ����ԭ��
    ----------------------------------------------------------
	Remarks:	
==========================================================================*/
BOOL CZCTInterlockJuge::IsExistER(CString& strCause,CString& strFrameContent,int iBtnType)
{
	//���µİ�ťID�����������
	WORD wBtnCommandID[BTNMAXNUM] = {0}, wBtnNum = 0;

	//
	POSITION pos = m_pParentObject->m_AnNActiveList.GetHeadPosition();
	while (pos) {
		CAnN* pAnN = m_pParentObject->m_AnNActiveList.GetNext(pos);
		//
		wBtnCommandID[wBtnNum] = pAnN->m_iCommandID;
		wBtnNum ++;
	}

	//if none of buttons has been pressed down, return fasle;
	if (wBtnNum < 2) {
		strCause.Format("��ť����ѡ������\n");
		return FALSE;
	}


	//û�н�·��Ϣ
	if(m_EntRailWay.GetLengh()==0)
	{
		strCause="��·�ļ������ڻ��޷���!";
		return FALSE;
	}

	//
	ERNode erItemNode[2];
	PRNode prItemNode;
	BOOL bIsExistPasRoad,bIsExistEntRoad;
	int iCycleNum = 0;

	//�ȼ��ͨ����·���Ƿ����
	bIsExistPasRoad = m_PasRailWay.IsExistER(wBtnCommandID,wBtnNum,&prItemNode);
	if (!bIsExistPasRoad) {//ͨ����·�в�����ʱ���ڵ��г���·�в���
		bIsExistEntRoad = m_EntRailWay.IsExistER(wBtnCommandID,wBtnNum,&erItemNode[0]);
		bIsExistEntRoad ? iCycleNum = 1 : iCycleNum = 0;
	}
	else{//ͨ����·�д��ڴ˽�·�����ڵ��г���·������ص�������·
		if (!m_EntRailWay.IsExistER(prItemNode.abySubRoad1,2,&erItemNode[0])) {
			strCause = "ͨ����·��������";
			return FALSE;
		}
		if (!m_EntRailWay.IsExistER(prItemNode.abySubRoad2,2,&erItemNode[1])) {
			return FALSE;
			strCause = "ͨ����·��������";
		}
		iCycleNum = 2;
	}
	

	//-----------------------------------------------------//
	//------------------ ���������ж� ---------------------//
	if (bIsExistPasRoad || bIsExistEntRoad) 
	{
		//������·�����ҵ�һ����ťΪ������ť��������Ž�·ʱ������Ҫ����һ�����
		if (m_pParentObject->m_AnNActiveList.GetHead()->m_iType == CAnN::BTN_TYPE_YA ||
			iBtnType == CFuncBtn::JLSP) {
			return TRUE;
		}

		//�������豸��״̬�Ƿ�������·����
		for( int iIndex = 0; iIndex<iCycleNum; iIndex++){

			//��������·���ڣ���鿴����״̬�Ƿ���������·����
			for(int j=0;j<erItemNode[iIndex].wSwitchNum;j++){
				Switch* pS = erItemNode[iIndex].pSwitch+j;
				if(!DaoCIsUsableness(pS->wSwitch,pS->byFlag,strCause)){
					return FALSE;
				}
			}
			
			//�޲�����״̬�Ƿ���������·����
			WORD wNum=erItemNode[iIndex].pwSection[0];//������������
			for(int j=1;j<=wNum;j++){
				WORD wS = erItemNode[iIndex].pwSection[j];
				if(!WcQDIsUsableness(wS,strCause)){
					return FALSE;
				}
			}
			
			//�����г���·ʱ��������ɵ�������״̬
			if (erItemNode[iIndex].byERType == ERNode::ET_LIECHE) {
				//
				TRACE("�����г���·\n");
				//�Ƿ��еж��źŴ���
				for(int j=0;j<erItemNode[iIndex].wLEnemyLightNum;j++){
					WORD wLE = erItemNode[iIndex].pwLEnemyLight[j];
					if(!EnemySignalIsUsableness(strCause,wLE,TRUE))	{
						return FALSE;
					}
				}
				for(int j=0;j<erItemNode[iIndex].wDEnemyLightNum;j++){
					WORD wDE = erItemNode[iIndex].pwDEnemyLight[j];
					if(!EnemySignalIsUsableness(strCause,wDE,FALSE)){
						return FALSE;
					}
				}
				//�Ƿ�ɵ�����
				WORD wQDNum=erItemNode[iIndex].pwSection[0];//������������
				for(int j=1;j<=wQDNum;j++){
					WORD wS = erItemNode[iIndex].pwSection[j];					
					if(!GuDaoCloseoffIsUsableness(strCause,wS)){
						return FALSE;
					}
				}
				//�Ƿ��������
				if(!QuJianCloseoffIsUsableness(strCause,wBtnCommandID[wBtnNum-1])){
					return FALSE;
				}
			}
		}

		//�����г���·ʱ,Ӧ�ҵ���Ӧ�ĳ��κ�
		if (erItemNode[0].byERType == ERNode::ET_LIECHE) {
			for(int n=0; n<erItemNode[0].wNearSectionNum; n++){
				strFrameContent = m_pParentObject->m_FrameTrainNoList.GetContBySectRel(erItemNode[0].pwNearSection[n]);
				if (!strFrameContent.IsEmpty()) {
					TRACE("�ӽ�����ID��%d\n",erItemNode[0].pwNearSection[n]);
					break;
				}
			}
			//��û���ҵ���Ӧ�ĳ��Σ����ڳ��ζ����м�������
			if (strFrameContent.IsEmpty()) {
				int iFrameID = erItemNode[0].byStartLight[0]*100+1;
				TRACE("����ID��%d\n",iFrameID);
				strFrameContent = m_pParentObject->m_FrameTrainNoList.GetContByID(iFrameID);
			}
		
		}
		return TRUE;
	}
	else//��·���в����ڻ�����·
	{
		strCause = "�ڰ�ť";
		for(int n=0; n<wBtnNum; n++){
			CString strInf;
			if (n==wBtnNum-1) {
				strInf.Format("%s(%d)֮�䲻���ڻ�����·!",
					m_pParentObject->GetBtnNameByID(wBtnCommandID[n]),wBtnCommandID[n]);
			}
			else{
				strInf.Format("%s(%d)��",
					m_pParentObject->GetBtnNameByID(wBtnCommandID[n]),wBtnCommandID[n]);
			}
			strCause += strInf;
		}
		return FALSE;
	}
}

/*========================================================================
	Name:		����״̬�Ƿ���������·����
    ----------------------------------------------------------
	Params:		wDaoCId		��������
				bState		�����״̬(1��λ,0��λ)
				&strCause	����·������ʱ����ԭ��
    ----------------------------------------------------------
	Remarks:	
==========================================================================*/
BOOL CZCTInterlockJuge::DaoCIsUsableness(WORD wDaoCId, BOOL bState ,CString& strCause ,BOOL bQud)
{
	POSITION pos = m_pParentObject->m_DCList.GetHeadPosition();
	int nS;
	CString strName;
 	while(pos)
 	{
 		WORD wTemp = m_pParentObject->m_DCList.GetAt(pos)->m_iIndex;
 		if(wTemp == wDaoCId)
 		{
			nS=m_pParentObject->m_DCList.GetAt(pos)->m_iRWCBand;
			strName=m_pParentObject->m_DCList.GetAt(pos)->m_strName;
			//���������Ƿ����
			if( nS & CYAN_BAND || nS & WHITE_BAND || nS & RED_BAND){
				strCause.Format("����%s �������β�����!",strName);
				return FALSE;
			}
			if(bQud)
				return TRUE;
			//�����Ƿ�����
 			if(m_pParentObject->m_DCList.GetAt(pos)->IsLocked())
			{
				if(bState)//��λ
				{
					if(!m_pParentObject->m_DCList.GetAt(pos)->IsDW())
					{
						strCause="����"+strName+"�������ڷ�λ!";
						return FALSE;
					}
				}
				else//��λ
				{
					if(!m_pParentObject->m_DCList.GetAt(pos)->IsFW())
					{
						strCause="����"+strName+"����������λ!";
						return FALSE;
					}
				}
			}
 			return TRUE;
		}
		m_pParentObject->m_DCList.GetNext(pos);//ԭ m_ANList.GetNext(pos);
 	}

	strCause.Format("δ�ҵ�����,���=%d,��鿴վ���ļ�!",wDaoCId);
	return FALSE;
}

/*========================================================================
	Name:		�޲�����״̬�Ƿ���������·����
    ----------------------------------------------------------
	Params:		wWcQDId		�޲����ε����
				&strCause	����·������ʱ����ԭ��
	----------------------------------------------------------
	Remarks:	
==========================================================================*/
BOOL CZCTInterlockJuge::WcQDIsUsableness(WORD wQDId,CString& strCause)
{
	int i,nS;
	CString strName;
	POSITION pos = m_pParentObject->m_WcQDList.GetHeadPosition();

 	while(pos)
 	{
 		WORD wTemp = m_pParentObject->m_WcQDList.GetAt(pos)->m_iIndex;
		strName=m_pParentObject->m_WcQDList.GetAt(pos)->m_strName;
 		if(wTemp == wQDId)
 		{
			nS=m_pParentObject->m_WcQDList.GetAt(pos)->m_iStatus;
			if( nS & CYAN_BAND || nS & WHITE_BAND || nS & RED_BAND)
			{
				strCause="�޲�����"+strName+"������!";
				return FALSE;
			}
			else
				return TRUE;
		}
		m_pParentObject->m_WcQDList.GetNext(pos);
 	}

	for(i=0;i<m_pParentObject->iDCQDMaps;i++)
	{
		if(m_pParentObject->DCQDMap[i].QD_INDEX == wQDId)
		{
			if(DaoCIsUsableness(m_pParentObject->DCQDMap[i].iPrDC+1,FALSE,strCause,TRUE))
				return TRUE;
			else
				return FALSE;
		}
	}

	strCause.Format("δ�ҵ�����,���=%d,��鿴վ���ļ�!",wQDId);
	return FALSE;
}

BOOL CZCTInterlockJuge::EnemySignalIsUsableness(CString&strCause,WORD wLE,BOOL bLE)
{
	POSITION pos=m_pParentObject->m_XHJList.GetHeadPosition();
	while(pos)
	{
		int iTemp;
		if(bLE)
			iTemp = m_pParentObject->m_XHJList.GetAt(pos)->m_iLXIndex;
		else
			iTemp = m_pParentObject->m_XHJList.GetAt(pos)->m_iDXIndex;
		CString strName=m_pParentObject->m_XHJList.GetAt(pos)->m_strName;
		
		if(iTemp ==wLE)
		{
			int iStatus = m_pParentObject->m_XHJList.GetAt(pos)->m_iStatus;
			if(iStatus &0x04)
				return TRUE;
			else 
			{
				strCause="�ж��ź�"+strName+"����!";
				return FALSE;
			}
		}
		m_pParentObject->m_XHJList.GetNext(pos);
	}
	strCause.Format("δ�ҵ��ź�,���=%d,��鿴վ���ļ�!",wLE);
	return FALSE;
}
BOOL CZCTInterlockJuge::GuDaoCloseoffIsUsableness(CString&strCause,WORD wGdID)
{
	POSITION pos = m_pParentObject->m_GdStatusList.GetHeadPosition();
	while(pos)
	{
		CGdStatus* pGdSta = m_pParentObject->m_GdStatusList.GetNext(pos);
		int iTemp = pGdSta->m_iCommandID;
		CString strName = pGdSta->m_strName;

		if(iTemp == wGdID){
			if(pGdSta->GetLockSta()){
				strCause ="�ɵ�"+strName+"����!";
				return FALSE;
			}
			else
				return TRUE;
		}

	}
	return TRUE;
}
BOOL CZCTInterlockJuge::QuJianCloseoffIsUsableness(CString&strCause,WORD wBtnID)
{
	POSITION pos = m_pParentObject->m_QjStatusList.GetHeadPosition();
	while (pos)
	{
		CQjStatus *pQjSta = m_pParentObject->m_QjStatusList.GetNext(pos);
		int iTemp = pQjSta->m_iXHNo1;

		if(iTemp == wBtnID)	{
			if(pQjSta->GetLockSta()){
				strCause = "�������!";
				return FALSE;
			}
			else
				return TRUE;
		}
	}
	return TRUE;
}