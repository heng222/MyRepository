#include "stdafx.h"
#include "MobileFrameMgr_bin.h"

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
CMobileFrameMgrBin::CMobileFrameMgrBin()
{
    Init();
}

CMobileFrameMgrBin::~CMobileFrameMgrBin()
{
}


void CMobileFrameMgrBin::Init()
{
    memset(m_byFrame,0,sizeof(m_byFrame));
    m_iFrameLen = 0;
    m_bHasRcvHead = FALSE;
    m_bRecvNextDLE = TRUE;
}
//////////////////////////////////////////////////////////////////////////
//########################################################################
// Parse Frame...
WORD CMobileFrameMgrBin::GetMaxLenFrame() const
{
    return TMobileFrameBin::EMaxLenFrame;
}

void CMobileFrameMgrBin::ParseRawData(LPBYTE pByData, WORD wDataLen,CBaseProtocolList& aFrameList)
{

	// 解析出一个完整的帧...
	for (WORD i = 0; i<wDataLen; i++)
	{

		switch(pByData[i])
		{
            // 转义字符
        case TMobileFrameBin::EEscapeChar: 
			if(m_iFrameLen==0)
			{
				m_byFrame[m_iFrameLen++] = TMobileFrameBin::EEscapeChar;
				m_bRecvNextDLE = FALSE;
			}
			else if(m_byFrame[m_iFrameLen-1] != TMobileFrameBin::EEscapeChar)
			{
                m_byFrame[m_iFrameLen++] = TMobileFrameBin::EEscapeChar;
				m_bRecvNextDLE = FALSE;
			}
			else
			{
				if(m_bRecvNextDLE)
				{
                    m_byFrame[m_iFrameLen++] = TMobileFrameBin::EEscapeChar;
					m_bRecvNextDLE = FALSE;
				}
				else
				{
					m_bRecvNextDLE = TRUE;
				}
			}
			break;

            // 帧头标识
        case TMobileFrameBin::EStartFlag: 
            if (m_bHasRcvHead)
            {
                m_byFrame[m_iFrameLen++] = pByData[i];
            }
            else if( m_iFrameLen>0 && m_byFrame[m_iFrameLen-1]==TMobileFrameBin::EEscapeChar)
            {
                // 已收到帧头
                m_bHasRcvHead = TRUE;
                m_iFrameLen = 0;
                m_byFrame[m_iFrameLen++] = TMobileFrameBin::EEscapeChar;
                m_byFrame[m_iFrameLen++] = TMobileFrameBin::EStartFlag;
            }
			break;

            // 帧尾标识
        case TMobileFrameBin::EEndFlag:
			if (m_bHasRcvHead)
			{				
				if(!m_bRecvNextDLE && m_byFrame[m_iFrameLen-1]==TMobileFrameBin::EEscapeChar)
				{
                    m_byFrame[m_iFrameLen++] = TMobileFrameBin::EEndFlag;

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
            if (m_bHasRcvHead && m_iFrameLen<TMobileFrameBin::EMaxLenFrame)
            {
                m_byFrame[m_iFrameLen++] = pByData[i];
            }
            else if (m_iFrameLen>TMobileFrameBin::EMaxLenFrame)
            {
                ASSERT(0);
            }
		} // end of switch
	}
    
}

TBaseProtocol* CMobileFrameMgrBin::ParsePacket()
{
    // Divest the header and tail from the frame.
    LPBYTE lpFrame = m_byFrame;
    DivestFrame(lpFrame,m_iFrameLen);

    // ATTENTION: aBuffer已经去除帧头与帧尾
    int iIndex = 0;

    // Get the CommandID of the frame.
    TMobileFrameBin frameHead;
    int tempIdx = iIndex;
    frameHead.ParseBuffer(lpFrame,tempIdx);

    // 
    PTMobileFrameBin pFrame = TMobileFrameBin::GetInstance(frameHead.wCmdID);

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
void CMobileFrameMgrBin::BuildPacket(TBaseProtocol* pProtocol, LPBYTE lpBuffer,int& iBufLen)
{
    ASSERT(pProtocol->GetProType()==TMobileFrameBin::E_PRO_FLAG);

    if (pProtocol->GetProType()==TMobileFrameBin::E_PRO_FLAG)
    {
        iBufLen = 0;
        TMobileFrameBin* pFrame = (TMobileFrameBin*)(pProtocol);

        LPBYTE lpStartAddr = lpBuffer+TMobileFrameBin::ELenFrmHead/*给帧头预留位置*/;
        pFrame->GetBuffer(lpStartAddr,iBufLen);

        // Check DLE
        CheckDLE(lpStartAddr,iBufLen);

        // Encapsulate frame
        EncapsFrame(lpStartAddr,iBufLen);
    }
}

//////////////////////////////////////////////////////////////////////////
// Private functions
void CMobileFrameMgrBin::CheckDLE( LPBYTE lpbyFrame,int& iLen)
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
    int i=0;
    int j = 0;
    for (i=0,j=0; i<iLen; i++,j++)
    {
        lpbyFrame[j] = lpNewFrame[i];
        if (lpNewFrame[i]==TMobileFrameBin::EEscapeChar)
        {
            j++;
            lpbyFrame[j] = TMobileFrameBin::EEscapeChar;
        }
    }

    // 
    iLen = j;

    delete lpNewFrame;

}

void CMobileFrameMgrBin::EncapsFrame(LPBYTE lpbyDest,int& iLen)
{
    LPBYTE pFrmHead = lpbyDest - TMobileFrameBin::ELenFrmHead;
    pFrmHead[0] = TMobileFrameBin::EEscapeChar;
    pFrmHead[1] = TMobileFrameBin::EStartFlag;

    LPBYTE pFrmTail = lpbyDest + iLen;
    pFrmTail[0] = TMobileFrameBin::EEscapeChar;
    pFrmTail[1] = TMobileFrameBin::EEndFlag;

    iLen += (TMobileFrameBin::ELenFrmHead+TMobileFrameBin::ELenFrmTail);
}

void CMobileFrameMgrBin::DivestFrame(LPBYTE& lpbyDest,int& iLen)
{
    if (iLen>(TMobileFrameBin::ELenFrmHead + TMobileFrameBin::ELenFrmTail))
    {
        lpbyDest += TMobileFrameBin::ELenFrmHead;
        iLen -= (TMobileFrameBin::ELenFrmHead + TMobileFrameBin::ELenFrmTail);
    }
}

