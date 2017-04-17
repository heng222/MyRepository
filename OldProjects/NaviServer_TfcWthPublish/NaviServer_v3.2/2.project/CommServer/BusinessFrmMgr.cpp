#include "stdafx.h"
#include "BusinessFrmMgr.h"

//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
/* 
打包规则：
	1、打包内容体(Content body)
	2、打包内容头部(Content header)
	3、打包协议头部(Frame header)

解包规则：
	1、解包协议头部(Frame header)
	2、解包内容头部(Content header)
	3、解包内容体(Content body)
*/
//////////////////////////////////////////////////////////////////////////
CBusinessFrameMgr::CBusinessFrameMgr()
{
    Init();
}

CBusinessFrameMgr::~CBusinessFrameMgr()
{
}


void CBusinessFrameMgr::Init()
{
    memset(m_byFrame,0,sizeof(m_byFrame));
    m_iFrameLen = 0;
    m_bHasRcvHead = FALSE;
    m_bRecvNextDLE = TRUE;
}
//////////////////////////////////////////////////////////////////////////
//########################################################################
// Parse Frame...
WORD CBusinessFrameMgr::GetMaxLenFrame() const
{
    return TBusinessFrm::EMaxLenFrame;
}

void CBusinessFrameMgr::ParseRawData(LPBYTE pByData, WORD wDataLen,CBaseProtocolList& aFrameList)
{

	// 解析出一个完整的帧...
	for (WORD i = 0; i<wDataLen; i++)
	{

		switch(pByData[i])
		{
            // 转义字符
        case TBusinessFrm::EEscapeChar: 
			if(m_iFrameLen==0)
			{
				m_byFrame[m_iFrameLen++] = TBusinessFrm::EEscapeChar;
				m_bRecvNextDLE = FALSE;
			}
			else if(m_byFrame[m_iFrameLen-1] != TBusinessFrm::EEscapeChar)
			{
                m_byFrame[m_iFrameLen++] = TBusinessFrm::EEscapeChar;
				m_bRecvNextDLE = FALSE;
			}
			else
			{
				if(m_bRecvNextDLE)
				{
                    m_byFrame[m_iFrameLen++] = TBusinessFrm::EEscapeChar;
					m_bRecvNextDLE = FALSE;
				}
				else
				{
					m_bRecvNextDLE = TRUE;
				}
			}
			break;

            // 帧头标识
        case TBusinessFrm::EStartFlag: 
            if (m_bHasRcvHead)
            {
                m_byFrame[m_iFrameLen++] = pByData[i];
            }
            else if( m_iFrameLen>0 && m_byFrame[m_iFrameLen-1]==TBusinessFrm::EEscapeChar)
            {
                // 已收到帧头
                m_bHasRcvHead = TRUE;
                m_iFrameLen = 0;
                m_byFrame[m_iFrameLen++] = TBusinessFrm::EEscapeChar;
                m_byFrame[m_iFrameLen++] = TBusinessFrm::EStartFlag;
            }
			break;

            // 帧尾标识
        case TBusinessFrm::EEndFlag:
			if (m_bHasRcvHead)
			{				
				if(!m_bRecvNextDLE && m_byFrame[m_iFrameLen-1]==TBusinessFrm::EEscapeChar)
				{
                    m_byFrame[m_iFrameLen++] = TBusinessFrm::EEndFlag;

					// 将RecDLESTX置0
					m_bHasRcvHead = FALSE;

					// Start parsing frame
					TBaseProtocol* pFrame = ParsePacket();

                    // Save
                    if (pFrame!=NULL)
                    {
                        aFrameList.AddTail(pFrame);
                    }

                    // 初始化
                    Init();
				}
				else
				{
                    m_byFrame[m_iFrameLen++] = pByData[i];
				}
			}
			break;

		default:
            if (m_bHasRcvHead && m_iFrameLen<TBusinessFrm::EMaxLenFrame)
            {
                m_byFrame[m_iFrameLen++] = pByData[i];
            }
            else if (m_iFrameLen>TBusinessFrm::EMaxLenFrame)
            {
                ASSERT(0);
            }
		} // end of switch
	}
    
}

TBaseProtocol* CBusinessFrameMgr::ParsePacket()
{
    // Divest the header and tail from the frame.
    LPBYTE lpFrame = m_byFrame;
    DivestFrame(lpFrame,m_iFrameLen);

    // ATTENTION: aBuffer已经去除帧头与帧尾
    int iIndex = 0;

    // Get the CommandID of the frame.
    TBusinessFrm frameHead;
    int tempIdx = iIndex;
    frameHead.ParseBuffer(lpFrame,tempIdx);

    // 
    PTBusinessFrm pFrame = TBusinessFrm::GetInstance(frameHead.wCmdID);

    if (pFrame!=NULL)
    {
        if (!pFrame->ParseBuffer(lpFrame,iIndex))
        {
            pFrame->AutoDel();
            pFrame = NULL;
        }
    }

    return pFrame;
}


//////////////////////////////////////////////////////////////////////////
// ######################################################################
// Build Frame ...
void CBusinessFrameMgr::BuildPacket(TBaseProtocol* pProtocol, LPBYTE lpBuffer,int& iBufLen)
{
    ASSERT(pProtocol->GetProType()==TBusinessFrm::E_PRO_FLAG);

    if (pProtocol->GetProType()==TBusinessFrm::E_PRO_FLAG)
    {
        iBufLen = 0;
        TBusinessFrm* pFrame = (TBusinessFrm*)(pProtocol);

        LPBYTE lpStartAddr = lpBuffer+TBusinessFrm::ELenFrmHead/*给帧头预留位置*/;
        pFrame->GetBuffer(lpStartAddr,iBufLen);

        // Check DLE
        CheckDLE(lpStartAddr,iBufLen);

        // Encapsulate frame
        EncapsFrame(lpStartAddr,iBufLen);
    }
}

//////////////////////////////////////////////////////////////////////////
// Private functions
void CBusinessFrameMgr::CheckDLE( LPBYTE lpbyFrame,int& iLen)
{
    LPBYTE lpNewFrame = new BYTE[iLen];
    if (lpNewFrame==NULL)
    {
        TRACE(_T("Out of memory!\n"));
        ASSERT(NULL);
        return;
    }

    // make a copy
    memcpy(lpNewFrame,lpbyFrame,iLen);
    memset(lpbyFrame,0,iLen);

    // 
    int i=0,j=0;
    for (; i<iLen; i++,j++)
    {
        lpbyFrame[j] = lpNewFrame[i];
        if (lpNewFrame[i]==TBusinessFrm::EEscapeChar)
        {
            j++;
            lpbyFrame[j] = TBusinessFrm::EEscapeChar;
        }
    }

    // 
    iLen = j;

    delete lpNewFrame;

}

void CBusinessFrameMgr::EncapsFrame(LPBYTE lpbyDest,int& iLen)
{
    LPBYTE pFrmHead = lpbyDest - TBusinessFrm::ELenFrmHead;
    pFrmHead[0] = TBusinessFrm::EEscapeChar;
    pFrmHead[1] = TBusinessFrm::EStartFlag;

    LPBYTE pFrmTail = lpbyDest + iLen;
    pFrmTail[0] = TBusinessFrm::EEscapeChar;
    pFrmTail[1] = TBusinessFrm::EEndFlag;

    iLen += (TBusinessFrm::ELenFrmHead+TBusinessFrm::ELenFrmTail);
}

void CBusinessFrameMgr::DivestFrame(LPBYTE& lpbyDest,int& iLen)
{
    if (iLen>(TBusinessFrm::ELenFrmHead + TBusinessFrm::ELenFrmTail))
    {
        lpbyDest += TBusinessFrm::ELenFrmHead;
        iLen -= (TBusinessFrm::ELenFrmHead + TBusinessFrm::ELenFrmTail);
    }
}

