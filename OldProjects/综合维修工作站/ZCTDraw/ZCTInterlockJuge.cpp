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
	Name:		查找两个按钮之间是否存在进路
    ----------------------------------------------------------
	Params:
				strCause        若进路不存在时返回原因
    ----------------------------------------------------------
	Remarks:	
==========================================================================*/
BOOL CZCTInterlockJuge::IsExistER(CString& strCause,CString& strFrameContent,int iBtnType)
{
	//按下的按钮ID数组与其个数
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
		strCause.Format("按钮个数选择有误！\n");
		return FALSE;
	}


	//没有进路信息
	if(m_EntRailWay.GetLengh()==0)
	{
		strCause="进路文件不存在或无法打开!";
		return FALSE;
	}

	//
	ERNode erItemNode[2];
	PRNode prItemNode;
	BOOL bIsExistPasRoad,bIsExistEntRoad;
	int iCycleNum = 0;

	//先检查通过进路中是否存在
	bIsExistPasRoad = m_PasRailWay.IsExistER(wBtnCommandID,wBtnNum,&prItemNode);
	if (!bIsExistPasRoad) {//通过进路中不存在时，在调列车进路中查找
		bIsExistEntRoad = m_EntRailWay.IsExistER(wBtnCommandID,wBtnNum,&erItemNode[0]);
		bIsExistEntRoad ? iCycleNum = 1 : iCycleNum = 0;
	}
	else{//通过进路中存在此进路，则在调列车进路中找相关的两条进路
		if (!m_EntRailWay.IsExistER(prItemNode.abySubRoad1,2,&erItemNode[0])) {
			strCause = "通过进路数据有误！";
			return FALSE;
		}
		if (!m_EntRailWay.IsExistER(prItemNode.abySubRoad2,2,&erItemNode[1])) {
			return FALSE;
			strCause = "通过进路数据有误！";
		}
		iCycleNum = 2;
	}
	

	//-----------------------------------------------------//
	//------------------ 进行联锁判断 ---------------------//
	if (bIsExistPasRoad || bIsExistEntRoad) 
	{
		//基本进路存在且第一个按钮为引导按钮或进行试排进路时，不需要做进一步检查
		if (m_pParentObject->m_AnNActiveList.GetHead()->m_iType == CAnN::BTN_TYPE_YA ||
			iBtnType == CFuncBtn::JLSP) {
			return TRUE;
		}

		//检测相关设备的状态是否满足排路需求
		for( int iIndex = 0; iIndex<iCycleNum; iIndex++){

			//若基本进路存在，则查看道岔状态是否可以满足进路成立
			for(int j=0;j<erItemNode[iIndex].wSwitchNum;j++){
				Switch* pS = erItemNode[iIndex].pSwitch+j;
				if(!DaoCIsUsableness(pS->wSwitch,pS->byFlag,strCause)){
					return FALSE;
				}
			}
			
			//无岔区段状态是否可以满足进路成立
			WORD wNum=erItemNode[iIndex].pwSection[0];//经过的区段数
			for(int j=1;j<=wNum;j++){
				WORD wS = erItemNode[iIndex].pwSection[j];
				if(!WcQDIsUsableness(wS,strCause)){
					return FALSE;
				}
			}
			
			//排列列车进路时，还需检查股道与区间状态
			if (erItemNode[iIndex].byERType == ERNode::ET_LIECHE) {
				//
				TRACE("排列列车进路\n");
				//是否有敌对信号存在
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
				//是否股道封锁
				WORD wQDNum=erItemNode[iIndex].pwSection[0];//经过的区段数
				for(int j=1;j<=wQDNum;j++){
					WORD wS = erItemNode[iIndex].pwSection[j];					
					if(!GuDaoCloseoffIsUsableness(strCause,wS)){
						return FALSE;
					}
				}
				//是否区间封锁
				if(!QuJianCloseoffIsUsableness(strCause,wBtnCommandID[wBtnNum-1])){
					return FALSE;
				}
			}
		}

		//排列列车进路时,应找到相应的车次号
		if (erItemNode[0].byERType == ERNode::ET_LIECHE) {
			for(int n=0; n<erItemNode[0].wNearSectionNum; n++){
				strFrameContent = m_pParentObject->m_FrameTrainNoList.GetContBySectRel(erItemNode[0].pwNearSection[n]);
				if (!strFrameContent.IsEmpty()) {
					TRACE("接近区段ID＝%d\n",erItemNode[0].pwNearSection[n]);
					break;
				}
			}
			//若没有找到相应的车次，则在车次队列中继续查找
			if (strFrameContent.IsEmpty()) {
				int iFrameID = erItemNode[0].byStartLight[0]*100+1;
				TRACE("队列ID＝%d\n",iFrameID);
				strFrameContent = m_pParentObject->m_FrameTrainNoList.GetContByID(iFrameID);
			}
		
		}
		return TRUE;
	}
	else//进路表中不存在基本进路
	{
		strCause = "在按钮";
		for(int n=0; n<wBtnNum; n++){
			CString strInf;
			if (n==wBtnNum-1) {
				strInf.Format("%s(%d)之间不存在基本进路!",
					m_pParentObject->GetBtnNameByID(wBtnCommandID[n]),wBtnCommandID[n]);
			}
			else{
				strInf.Format("%s(%d)、",
					m_pParentObject->GetBtnNameByID(wBtnCommandID[n]),wBtnCommandID[n]);
			}
			strCause += strInf;
		}
		return FALSE;
	}
}

/*========================================================================
	Name:		道岔状态是否可以满足进路成立
    ----------------------------------------------------------
	Params:		wDaoCId		道岔的序号
				bState		道岔的状态(1正位,0反位)
				&strCause	若进路不存在时返回原因
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
			//道岔区段是否空闲
			if( nS & CYAN_BAND || nS & WHITE_BAND || nS & RED_BAND){
				strCause.Format("道岔%s 所在区段不空闲!",strName);
				return FALSE;
			}
			if(bQud)
				return TRUE;
			//道岔是否锁定
 			if(m_pParentObject->m_DCList.GetAt(pos)->IsLocked())
			{
				if(bState)//正位
				{
					if(!m_pParentObject->m_DCList.GetAt(pos)->IsDW())
					{
						strCause="道岔"+strName+"被锁定在反位!";
						return FALSE;
					}
				}
				else//反位
				{
					if(!m_pParentObject->m_DCList.GetAt(pos)->IsFW())
					{
						strCause="道岔"+strName+"被锁定在正位!";
						return FALSE;
					}
				}
			}
 			return TRUE;
		}
		m_pParentObject->m_DCList.GetNext(pos);//原 m_ANList.GetNext(pos);
 	}

	strCause.Format("未找到道岔,序号=%d,请查看站场文件!",wDaoCId);
	return FALSE;
}

/*========================================================================
	Name:		无岔区段状态是否可以满足进路成立
    ----------------------------------------------------------
	Params:		wWcQDId		无岔区段的序号
				&strCause	若进路不存在时返回原因
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
				strCause="无岔区段"+strName+"不空闲!";
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

	strCause.Format("未找到区段,序号=%d,请查看站场文件!",wQDId);
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
				strCause="敌对信号"+strName+"开放!";
				return FALSE;
			}
		}
		m_pParentObject->m_XHJList.GetNext(pos);
	}
	strCause.Format("未找到信号,序号=%d,请查看站场文件!",wLE);
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
				strCause ="股道"+strName+"封锁!";
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
				strCause = "区间封锁!";
				return FALSE;
			}
			else
				return TRUE;
		}
	}
	return TRUE;
}