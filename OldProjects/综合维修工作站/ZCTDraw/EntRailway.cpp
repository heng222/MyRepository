 // EntRailway.cpp: implementation of the CEntRailway class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "EntRailway.h"
#include "CommFunction.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CEntRailway::CEntRailway()
{
	m_wLength = 0;
	m_pHead = NULL;
}
CEntRailway::CEntRailway(const CEntRailway& cEntR)
{
	*this = cEntR;
}
CEntRailway::~CEntRailway()
{
	ClearList();
}

//////////////////////////////////////////////////////////////////////////
#if _DEBUG
void CEntRailway::TraverseList(int nCondition) const
{
	ERNode *p = m_pHead;
	int i = 0;
	//-----------------------------------------
	while( p != NULL )
	{
		if( nCondition >= DIS_TRAIN ){
			TRACE("\n[DRoad%d]",p->iOrder);
		}
		else{
			TRACE("\n[LRoad%d]",p->iOrder);
		}

		TRACE("\nThroat= %d",p->byThroat);

		TRACE("\nButton=");
		for(i=0; i<BTNMAXNUM; i++)
			TRACE("  %d",p->wButton[i]);

		TRACE("\nType= %d",p->byType);

		TRACE("\nProp= %d",p->byProp);

		if( nCondition >= DIS_TRAIN ){
			TRACE("\nStartLight= %d %d",p->byStartLight[0],p->byStartLight[1]);
		}
		else{
			TRACE("\nStartLight= %d",p->byStartLight[0]);
		}
		

		TRACE("\nSwitch=");
		if(p->pSwitch != NULL)
		{
			TRACE(" %d;",p->wSwitchNum);
			for(i=0; i<p->wSwitchNum; i++){
				TRACE("  %d %d",p->pSwitch[i].wSwitch,p->pSwitch[i].byFlag);
			}
		}

		TRACE("\nSection=");
		if(p->pwSection != NULL)
		{
			for(i=0; i<=p->pwSection[0]; i++)
			{
				TRACE("  %d",p->pwSection[i]);
				if(i == 0){
					TRACE(";");
				}
			}
		}

		TRACE("\nNearSection= %d;",p->wNearSectionNum);
		for ( i = 0; i<p->wNearSectionNum; i++ ){
			TRACE(" %d",p->pwNearSection[i]);
		}

		TRACE("\nFarSection= %d;",p->wFarSectionNum);
		for ( i = 0; i<p->wFarSectionNum; i++ ){
			TRACE(" %d",p->pwFarSection[i]);
		}

		TRACE("\nLEnemyLight=");
		if(p->pwLEnemyLight != NULL)
		{
			TRACE(" %d;",p->wLEnemyLightNum);
			for(i=0; i<p->wLEnemyLightNum; i++){
				TRACE(" %d",p->pwLEnemyLight[i]);
			}
		}
		
		TRACE("\nDEnemyLight=");
		if(p->pwDEnemyLight != NULL)
		{
			TRACE(" %d;",p->wDEnemyLightNum);
			for(i=0; i<p->wDEnemyLightNum; i++){
				TRACE(" %d",p->pwDEnemyLight[i]);
			}
		}

		if( nCondition >= DIS_TRAIN )
		{
			TRACE("\nConsumeTime= %d",p->byConsumeTime);
			
			TRACE("\nSubRoadButton = %d;",p->bySubRoadButtonNum );
			for (i=0; i<p->bySubRoadButtonNum; i++){
				TRACE(" %d",p->pbySubRoadButton[i]);
			}

			TRACE("\nReturnSection = %d;",p->byReturnSectionNum);
			for (i=0; i<p->byReturnSectionNum; i++){
				TRACE(" %d",p->pbyReturnSection[i]);
			}

		}
		
		TRACE("\njlenable= %d;",p->wJlEnableNum);
		for ( i = 0; i<p->wJlEnableNum; i++ ){
			TRACE(" %d",p->pwJlEnable[i]);
		}
		
		TRACE("\njlnoable= %d;",p->wJlDisableNum);
		for ( i = 0 ; i<p->wJlDisableNum; i++){
			TRACE(" %d",p->pwJlDisable[i]);
		}
		////-----
		TRACE("\n");
		p=p->Next;
	}
}
#endif

//////////////////////////////////////////////////////////////////////////
BOOL CEntRailway::ReadERFile(LPCSTR lpcFileName)
{
	if( !ReadERFile(lpcFileName, TRAIN) )
	{
		ClearList();
		return false;
	}
	if( !ReadERFile(lpcFileName, DIS_TRAIN) )
	{
		ClearList();
		return false;
	}
	return true;
}
BOOL CEntRailway::ReadERFile(LPCSTR lpcFileName,int nReadCondition, WORD wSection /*=0*/ )
{
	CString strKeyName;	//�г�������Ĺؼ��ֶ�

	if( nReadCondition >= DIS_TRAIN )//ָ��Ҫ�����Ľ�·��Ϣ
	{
		strKeyName = "[DRoad";
	}
	else //ָ��Ҫ�г��Ľ�·��Ϣ
	{
		strKeyName = "[LRoad";
	}

	//------------------------------------------------------
	CStdioFile fp;
	CString strLine;
	if( !fp.Open(lpcFileName,CFile::modeRead | CFile::shareDenyNone) )
	{
		TRACE("Can not open %s! \n",lpcFileName);
		return false;
	}

	//--------------------------------------------------------
	LENGTHTYPE	iOrder		= 1;		
	BOOL		bStarted	= false;	//ָ��һ����·��Ϣ�Ƿ�ʼ
	BOOL		bEnded		= true;		//ָ��һ����·��Ϣ�Ƿ����
	ERNode		cNewNode;

	//���ļ�����ÿһ����·��Ϣ���뵥������
	while( fp.ReadString(strLine) )
	{
		strLine.TrimLeft(" ");
		//-----------------------------------------------
		//��һ���·��Ϣ���뵽�����
		if( !strLine.Left(6).CompareNoCase(strKeyName) )
		{
			cNewNode.iOrder = iOrder;
			iOrder++;
			bStarted = true;	//�ҵ���·�Ŀ�ʼ��־
			bEnded = false;
			continue;
		}
		//���Ѿ��ҵ���·�Ŀ�ʼ��־
		if( bStarted )
		{
			WORD wCount = 0;
			BYTE i = 0 ;

			/*
			LPBYTE		pByPointer = NULL;
			LPWORD		pWPointer = NULL;
			Switch*		pSwitch = NULL;
			*/
			//ERType
			if (nReadCondition >= DIS_TRAIN) {
				cNewNode.byERType = ERNode::ET_DIAOCHE;
			}
			else
			{
				cNewNode.byERType = ERNode::ET_LIECHE;
			}

			//Throat
			if( !strLine.Left(6).CompareNoCase("Throat") )
			{
				cNewNode.byThroat =	(BYTE)GetNFStr(strLine,0);
			}
			//Button
			else if( !strLine.Left(6).CompareNoCase("Button") )
			{
				for(i = 0; i<BTNMAXNUM; i++)
				{
					cNewNode.wButton[i] = (BYTE)GetNFStr(strLine,i);
				}
			}
			//Type
			else if( !strLine.Left(4).CompareNoCase("Type") )
			{
				cNewNode.byType = (BYTE)GetNFStr(strLine,0);
			}
			//Prop
			else if( !strLine.Left(4).CompareNoCase("Prop") )
			{
				cNewNode.byProp = (BYTE)GetNFStr(strLine,0);
			}
			//StartLight
			else if( !strLine.Left(10).CompareNoCase("StartLight") )
			{
				cNewNode.byStartLight[0] = (BYTE)GetNFStr(strLine,0);
				if( nReadCondition >= DIS_TRAIN )
					//ָ��Ҫ�����Ľ�·��Ϣʱ���Ž��źŵƵķ���ȡ��
				{
					cNewNode.byStartLight[1] = (BYTE)GetNFStr(strLine,1);
				}
			}
			//Switch
			else if( !strLine.Left(6).CompareNoCase("Switch") )
			{
				cNewNode.wSwitchNum = GetNFStr(strLine,0);
				cNewNode.pSwitch = new Switch[cNewNode.wSwitchNum];
				for(i = 0; i<cNewNode.wSwitchNum; i++)
				{
					cNewNode.pSwitch[i].wSwitch = GetNFStr(strLine,i*2+1);
					cNewNode.pSwitch[i].byFlag = (BYTE)GetNFStr(strLine,i*2+2);	
				}
				//cNewNode.pSwitch = pSwitch;
			}
			//Section
			else if( !strLine.Left(7).CompareNoCase("Section") )
			{
				wCount = GetNFStr(strLine,0);
				cNewNode.pwSection = new WORD[wCount + 1];
				cNewNode.pwSection[0] = wCount;
				for(i = 1; i<wCount+1; i++)
				{
					cNewNode.pwSection[i] = GetNFStr(strLine,i);
				}
				//cNewNode.pwSection = pWPointer;
			}
			//NearSection
			else if( !strLine.Left(11).CompareNoCase("NearSection") )
			{
				wCount = GetNFStr(strLine,0);
				cNewNode.wNearSectionNum = wCount;
				cNewNode.pwNearSection = new WORD[wCount];
				for ( i = 0; i< wCount; i++)
				{
					cNewNode.pwNearSection[i] = GetNFStr(strLine,i+1);
				}
			}
			//FarSection
			else if( !strLine.Left(10).CompareNoCase("FarSection") )
			{
				wCount = GetNFStr(strLine,0);
				cNewNode.wFarSectionNum = wCount;
				cNewNode.pwFarSection = new WORD[wCount];
				for ( i = 0; i< wCount; i++)
				{
					cNewNode.pwFarSection[i] = GetNFStr(strLine,i+1);
				}
			}
			//LEnemyLight
			else if( !strLine.Left(11).CompareNoCase("LEnemyLight") )
			{
				cNewNode.wLEnemyLightNum = GetNFStr(strLine,0);
				wCount = GetNFStr(strLine,0);
				cNewNode.pwLEnemyLight = new WORD[wCount];
	
				for(i = 1; i<wCount+1; i++)
				{
					cNewNode.pwLEnemyLight[i-1] = GetNFStr(strLine,i);
				}
				//cNewNode.pwLEnemyLight = pWPointer;				
			}
			//DEnemyLight
			else if( !strLine.Left(11).CompareNoCase("DEnemyLight") )
			{
				cNewNode.wDEnemyLightNum = GetNFStr(strLine,0);
				wCount = GetNFStr(strLine,0);
				cNewNode.pwDEnemyLight = new WORD[wCount];

				for(i = 1; i<wCount+1; i++)
				{
					cNewNode.pwDEnemyLight[i-1] = GetNFStr(strLine,i);
				}
				//cNewNode.pwDEnemyLight = pWPointer;
			}
			//ConsumeTime
			else if( !strLine.Left(11).CompareNoCase("ConsumeTime") )
			{
				cNewNode.byConsumeTime = (BYTE)GetNFStr(strLine,0);
			}
			//SubRoadButton
			else if( !strLine.Left(13).CompareNoCase("SubRoadButton"))
			{
				cNewNode.bySubRoadButtonNum = (BYTE)GetNFStr(strLine,0);
				cNewNode.pbySubRoadButton = new BYTE[cNewNode.bySubRoadButtonNum];
				for(i = 1; i<=cNewNode.bySubRoadButtonNum; i++)
				{
					cNewNode.pbySubRoadButton[i-1] = (BYTE)GetNFStr(strLine,i);
				}
				//cNewNode.pbySubRoadButton = pByPointer;
			}
			//ReturnSection
			else if( !strLine.Left(13).CompareNoCase("ReturnSection"))
			{
				cNewNode.byReturnSectionNum = (BYTE)GetNFStr(strLine,0);
				cNewNode.pbyReturnSection = new BYTE[cNewNode.byReturnSectionNum];
				for(i = 1; i<=cNewNode.byReturnSectionNum; i++)
				{
					cNewNode.pbyReturnSection[i-1] = (BYTE)GetNFStr(strLine,i);
				}
				//cNewNode.pbyReturnSection = pByPointer;
				
			}
			//jlEnable
			else if ( !strLine.Left(8).CompareNoCase("jlenable") )
			{
				cNewNode.wJlEnableNum = (WORD)GetNFStr(strLine,0);
				cNewNode.pwJlEnable = new WORD[cNewNode.wJlEnableNum];
				for(i = 1; i<=cNewNode.wJlEnableNum; i++)
				{
					cNewNode.pwJlEnable[i-1] = (WORD)GetNFStr(strLine,i);
				}
				//cNewNode.pwJlEnable = pWPointer;
			}
			//jlNoable
			else if ( !strLine.Left(8).CompareNoCase("jlnoable") )
			{
				cNewNode.wJlDisableNum = (WORD)GetNFStr(strLine,0);
				cNewNode.pwJlDisable = new WORD[cNewNode.wJlDisableNum];
				for(i = 1; i<=cNewNode.wJlDisableNum; i++)
				{
					cNewNode.pwJlDisable[i-1] = (WORD)GetNFStr(strLine,i);
				}
				//cNewNode.pwJlDisable = pWPointer;
			}
			//end
			else if ( !strLine.Left(3).CompareNoCase("end") )
			{
				bEnded = true;//һ�������ĵ�����·��ȡ���
			}



			//-------------------------------------------------------
			//���ݸ����������ж��Ƿ񱣴��½��
			if( bStarted && bEnded )
			{
				switch(nReadCondition)
				{
					//Train
				case TRAIN:
					AddTail(cNewNode);
					break;
				/*case TRAIN_NEARSECTION:
					if(cNewNode.pwNearSection[0] == wSection)//���ӽ����ε��ڸ�����ֵʱ
					{
						AddTail(cNewNode);
					}
					break;
				case TRAIN_FARSECTION:
					if(cNewNode.pwFarSection[0] == wSection)//���뿪���ε��ڸ�����ֵʱ
					{
						AddTail(cNewNode);
					}
					break;*/


					//Dispatch train
				case DIS_TRAIN:
					AddTail(cNewNode);
					break;
				case DIS_TRAIN_NEARSECTION:
					if(cNewNode.pwNearSection[0] == wSection)//���ӽ����ε��ڸ�����ֵʱ
					{
						AddTail(cNewNode);
					}
					break;
				case DIS_TRAIN_FARSECTION:
					if(cNewNode.pwFarSection[0] == wSection)//���뿪���ε��ڸ�����ֵʱ
					{
						AddTail(cNewNode);
					}
					break;
				};//End of "Switch"

				//�ͷ��ڴ�
				cNewNode.Free();

				//��ʼһ���µĽ�·��Ϣ
				bStarted = false;

			}//End of "if( bStarted && bEnded )"

		}//End of "if( bStarted )"

	}//End of "while(fp.ReadString(strLine))"
	
	fp.Close();
	return true;
}

void CEntRailway::AddTail(const ERNode &item)
{
	ERNode *newPtr = new ERNode;

	//�������¿��ٵĿռ���
	*newPtr = item;

	//���½���Nextָ�븳ΪNULL���������û�н��
	newPtr->Next = NULL;

	//--------------------------------------------------------------
	//��ͷָ��Ϊ�գ���ͷָ��ָ��ǰ���
	if( m_pHead==NULL )
	{
		m_pHead = newPtr;
	}
	else//ͷָ�벻Ϊ�գ����ҵ��������ĩβ��������ǰ�����뵽ĩβ.
	{
		ERNode *p = m_pHead;
		while(p->Next!=NULL)
		{
			p = p->Next;
		}
		p->Next = newPtr;
	}
	//----------------------------------------------------------
	m_wLength ++;
}



BOOL CEntRailway::IsExistNearFarSection(const WORD &wNearSection, const WORD &wFarSection)
{
	ERNode *cp;
	//
	cp=m_pHead;
	while(cp!=NULL)
	{
		if ( cp->pwNearSection[0] == wNearSection && cp->pwFarSection[0] == wFarSection )
		{
			return TRUE;
		}
		cp=cp->Next;
	}
	return FALSE;
}
BOOL CEntRailway::FindItemByOrder(const LENGTHTYPE &wOrder)
{
	ERNode *cp;
	//
	cp=m_pHead;
	while(cp!=NULL)
	{
		if ( cp->iOrder == wOrder )
		{
			return TRUE;
		}
		cp=cp->Next;
	}
	return FALSE;
}
/*
	FUN:	�ӵ�������ɾ���ʺ�ŵ���/������byThroat�ĵ�һ�����
*/
BOOL CEntRailway::DeleteItem(const BYTE &byThroat, BOOL bIsEqual/* = FASLE */)
{
	ERNode*		p = m_pHead;	//ָ���̽��
	ERNode*		fp = m_pHead;	//ǰ������ָ��


	while ( p != NULL )
	{
		BOOL bIsDelete;
		if ( bIsEqual )
		{
			bIsDelete = (p->byThroat == byThroat);
		}
		else
		{
			bIsDelete = (p->byThroat != byThroat);
		}

		//�Ƿ�Ҫɾ��ָ���Ľ�㣿
		if ( bIsDelete )//Ҫɾ���Ľ��
		{

			if ( p == m_pHead )//����Ҫɾ���Ľ���Ƿ�Ϊ��ͷ�����в�ͬ�Ĵ���
			{
				m_pHead = p->Next;
				//fp = m_pHead;
			}
			else
			{
				fp->Next = p->Next;
			}
			delete p;
			//��¼����һ
			m_wLength -- ;
			return TRUE;
		}

		//-------------------
		fp = p;
		p = p->Next;
		
	}
	return FALSE;
}



BOOL CEntRailway::DelItemByNearFarSection(const WORD &wNearSection, const WORD &wFarSection)
{
	ERNode*		p = m_pHead;	//ָ���̽��
	ERNode*		fp = m_pHead;	//ǰ������ָ��


	while ( p != NULL )
	{


		//�Ƿ�Ҫɾ��ָ���Ľ�㣿
		if ( p->pwNearSection[0] != wNearSection || p->pwFarSection[0] != wFarSection )//Ҫɾ���Ľ��
		{

			if ( p == m_pHead )//����Ҫɾ���Ľ���Ƿ�Ϊ��ͷ�����в�ͬ�Ĵ���
			{
				m_pHead = p->Next;
				//fp = m_pHead;
			}
			else
			{
				fp->Next = p->Next;
			}
			delete p;
			//��¼����һ
			m_wLength -- ;
			return TRUE;
		}

		//-------------------
		fp = p;
		p = p->Next;
		
	}
	return FALSE;
}

ERNode* CEntRailway::GetHead() const
{
	return m_pHead;
}

ERNode* CEntRailway::GetTail() const
{
	ERNode* cp = m_pHead;
	if(cp != NULL)
	{
		while(cp->Next != NULL)
		{
			cp = cp->Next;
		}
	}
	return cp;
}

void CEntRailway::ClearList()
{
	ERNode *cp,*np;
	//
	cp=m_pHead;
	while(cp!=NULL)
	{
		np=cp->Next;
		//���ͷŽṹ����ռ�õ��ڴ�
		delete cp;
		cp=np;
	}
	//
	m_wLength	=	0;
	m_pHead		=	NULL;
}

CEntRailway& CEntRailway::operator =(const CEntRailway &cER)
{
	if(&cER != this)
	{
		this->ClearList();
		ERNode *cp = cER.GetHead();
		while( cp != NULL )
		{
			this->AddTail(*cp);
			cp = cp->Next;
		}
	}
	return *this;
}

ERNode* CEntRailway::GetAt(const LENGTHTYPE &index) const
{
	if ( index>= m_wLength )
	{
		throw "��ͼ���ò����ڵĽ�㣡";
		return NULL;
	}
	//
	ERNode *cp = m_pHead;
	for(WORD i = 0; i<index; i++)
	{
		if(cp == NULL)
		{
			return NULL;
		}
		cp = cp->Next;
	}
	return cp;
}

ERNode& CEntRailway::operator [](const LENGTHTYPE& i)
{
	return *GetAt(i);
}

LENGTHTYPE CEntRailway::GetLengh() const
{
	/*ERNode* cp = m_pHead;
	WORD i = 0;
	while (cp!=NULL)
	{
		i++;
		cp = cp->Next;
	}
	return i;*/
	return m_wLength;
}

//##############################################################################
//Struct ERNode member function
void ERNode::Free()
{
	if ( pSwitch ){
		delete[] pSwitch;
	}

	if ( pwSection ){
		delete[] pwSection;
	}

	if ( pwNearSection ){
		delete[] pwNearSection;
	}

	if ( pwFarSection ){
		delete[] pwFarSection;
	}

	if ( pwLEnemyLight ){
		delete[] pwLEnemyLight;
	}

	if ( pwDEnemyLight ){
		delete[] pwDEnemyLight;
	}

	if ( pbySubRoadButton ){
		delete[] pbySubRoadButton;
	}

	if ( pbyReturnSection ){
		delete[] pbyReturnSection;
	}

	if ( pwJlEnable ){
		delete[] pwJlEnable;
	}

	if ( pwJlDisable ){
		delete[] pwJlDisable;
	}
	//
	WORD _size = sizeof(*this);
	ZeroMemory(this,_size);
}

ERNode& ERNode::operator =(const ERNode &item)
{
	WORD wLen;

	//Order
	iOrder = item.iOrder;
	
	//Throat
	byThroat = item.byThroat;
	
	//Button
	memcpy(wButton,item.wButton,sizeof(wButton));

	//Type
	byType = item.byType;

	//Prop
	byProp = item.byProp;

	//StartLight
	memcpy(byStartLight,item.byStartLight,sizeof(byStartLight));
	
	//Switch
	wLen = item.wSwitchNum;
	wSwitchNum = item.wSwitchNum;
	pSwitch = new Switch[wLen];
	memcpy( pSwitch, item.pSwitch, wLen*sizeof(Switch) );
	
	//Section
	wLen = item.pwSection[0];
	pwSection = new WORD[wLen+1];
	memcpy( pwSection, item.pwSection, (wLen+1)*sizeof(WORD) );

	//NearSection
	wLen = wNearSectionNum = item.wNearSectionNum;
	pwNearSection = new WORD[wLen];
	memcpy( pwNearSection, item.pwNearSection, (wLen)*sizeof(WORD) );

	//FarSection
	wLen = wFarSectionNum = item.wFarSectionNum;
	pwFarSection = new WORD[wLen];
	memcpy( pwFarSection, item.pwFarSection, (wLen)*sizeof(WORD) );

	//LEnemyLight
	wLen = item.wLEnemyLightNum;
	wLEnemyLightNum = wLen;
	pwLEnemyLight = new WORD[wLen];
	memcpy( pwLEnemyLight, item.pwLEnemyLight, wLen*sizeof(WORD) );

	//DEnemyLight
	wLen = item.wDEnemyLightNum;
	wDEnemyLightNum = wLen;
	pwDEnemyLight = new WORD[wLen];
	memcpy( pwDEnemyLight, item.pwDEnemyLight, wLen*sizeof(WORD) );

	//ConsumeTime
	byConsumeTime = item.byConsumeTime;

	//SubRoadButton
	wLen = item.bySubRoadButtonNum;
	bySubRoadButtonNum = (BYTE)wLen;
	pbySubRoadButton = new BYTE[wLen];
	memcpy( pbySubRoadButton, item.pbySubRoadButton, wLen );

	//ReturnSection
	wLen = item.byReturnSectionNum;
	byReturnSectionNum = (BYTE)wLen;
	pbyReturnSection = new BYTE[wLen];
	memcpy( pbyReturnSection, item.pbyReturnSection, wLen );

	//JLEnable
	wLen = item.wJlEnableNum;
	wJlEnableNum = wLen;
	pwJlEnable = new WORD[wLen];
	memcpy( pwJlEnable, item.pwJlEnable, wLen*sizeof(WORD) );

	//JLDisable
	wLen = item.wJlDisableNum;
	wJlDisableNum = wLen;
	pwJlDisable = new WORD[wLen];
	memcpy( pwJlDisable, item.pwJlDisable, wLen*sizeof(WORD) );
	
	//
	return *this;
}


BOOL CEntRailway::IsExistER(const WORD *pwBtn, int iBtnNum, ERNode *pItem/*=NULL*/)
{
	for(int i = 0; i<GetLengh(); i++)
	{	
		BOOL bResult = TRUE;
		for(int j=0; j<iBtnNum; j++)
		{
			bResult &= (GetAt(i)->wButton[j] == pwBtn[j]);
		}
		//
		if (bResult) {
			if(pItem)
			{
				*pItem = *GetAt(i);
			}
			return TRUE;
		}		
	}

	//
	return FALSE;
}

int CEntRailway::GetProAccordByBtn(const WORD *pBtnList, const int &iBtnNum)
{
	if (iBtnNum<=0) {
		return -1;
	}

	//
	ERNode erNode;
	BOOL bValue = IsExistER(pBtnList,iBtnNum,&erNode);
	if (bValue = FALSE) {
		return -1;
	}
	else{
		return erNode.byProp;
	}
}
