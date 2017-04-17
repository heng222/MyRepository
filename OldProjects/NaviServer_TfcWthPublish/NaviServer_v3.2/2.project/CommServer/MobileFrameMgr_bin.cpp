#include "stdafx.h"
#include "MobileFrameMgr_bin.h"

//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
/* 
�������
	1�����������(Content body)
	2���������ͷ��(Content header)
	3�����Э��ͷ��(Frame header)

�������
	1�����Э��ͷ��(Frame header)
	2���������ͷ��(Content header)
	3�����������(Content body)
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

	// ������һ��������֡...
	for (WORD i = 0; i<wDataLen; i++)
	{

		switch(pByData[i])
		{
            // ת���ַ�
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

            // ֡ͷ��ʶ
        case TMobileFrameBin::EStartFlag: 
            if (m_bHasRcvHead)
            {
                m_byFrame[m_iFrameLen++] = pByData[i];
            }
            else if( m_iFrameLen>0 && m_byFrame[m_iFrameLen-1]==TMobileFrameBin::EEscapeChar)
            {
                // ���յ�֡ͷ
                m_bHasRcvHead = TRUE;
                m_iFrameLen = 0;
                m_byFrame[m_iFrameLen++] = TMobileFrameBin::EEscapeChar;
                m_byFrame[m_iFrameLen++] = TMobileFrameBin::EStartFlag;
            }
			break;

            // ֡β��ʶ
        case TMobileFrameBin::EEndFlag:
			if (m_bHasRcvHead)
			{				
				if(!m_bRecvNextDLE && m_byFrame[m_iFrameLen-1]==TMobileFrameBin::EEscapeChar)
				{
                    m_byFrame[m_iFrameLen++] = TMobileFrameBin::EEndFlag;

					// ��RecDLESTX��0
					m_bHasRcvHead = FALSE;

					// Start parsing frame
					TBaseProtocol* pFrame = ParsePacket();

                    // Save
                    if (pFrame!=NULL)
                    {
                        aFrameList.AddTail(pFrame);
                    }

                    // ��ʼ��
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

    // ATTENTION: aBuffer�Ѿ�ȥ��֡ͷ��֡β
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

        LPBYTE lpStartAddr = lpBuffer+TMobileFrameBin::ELenFrmHead/*��֡ͷԤ��λ��*/;
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

