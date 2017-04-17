#include "stdafx.h"
#include ".\spframemgr.h"
#include "CommonFunc.h"

CSPFrameMgr::CSPFrameMgr(void)
{
    memset(m_byFrame,0,sizeof(m_byFrame));
    m_wFrameLen = 0;
    m_bHasRcvHead = FALSE;
    m_wBlockSize = 0;
}

CSPFrameMgr::~CSPFrameMgr(void)
{
}
//////////////////////////////////////////////////////////////////////////
WORD CSPFrameMgr::GetMaxLenFrame() const
{
    return TSpFrame::EMaxLenFrame;
}
void CSPFrameMgr::ParseRawData(LPBYTE pByData, WORD wDataLen,CBaseProtocolList& aFrameList)
{
    // 解析出一个完整的帧...
    for (WORD i = 0; i<wDataLen && i<GetMaxLenFrame(); i++)
    {
        switch(pByData[i])
        {
        case TSpFrame::EFrameHeader:
            {
                m_byFrame[m_wFrameLen++] = pByData[i];
                if (m_wFrameLen!=1 && m_byFrame[m_wFrameLen-2]==TSpFrame::EFrameHeader)
                {
                    // 初始化
                    memset(m_byFrame,0,sizeof(m_byFrame));
                    m_wFrameLen = 0;
                    m_wBlockSize = 0;
                    m_byFrame[m_wFrameLen++] = pByData[i];
                    m_byFrame[m_wFrameLen++] = pByData[i];

                    // 连续收到两个帧头标记
                    m_bHasRcvHead = TRUE;
                }
            }
            break;

        case TSpFrame::EFrameTail:
            {
                if (m_bHasRcvHead)
                {
                    m_byFrame[m_wFrameLen++] = pByData[i];
                    if ( (m_wFrameLen>4) && (m_byFrame[m_wFrameLen-2]==TSpFrame::EFrameTail) )
                    {
                        // 解析数据帧为对应的数据结构
                        TBaseProtocol* pFrame = ParsePacket();
                        if (pFrame!=NULL)
                        {
                            aFrameList.AddTail(pFrame);
                        }

                        // 回收缓冲
                        memset(m_byFrame,0,sizeof(m_byFrame));
                        m_wFrameLen = 0;
                        m_wBlockSize = 0;
                        m_bHasRcvHead = FALSE;
                    }
                }
            }
            break;

        default:
            if (m_bHasRcvHead) 
            {
                // 将收到的数据放入缓冲
                m_byFrame[m_wFrameLen] = pByData[i];
                m_wFrameLen++;
            }
            
        }
    }
}

TBaseProtocol* CSPFrameMgr::ParsePacket()
{
    // Get the CStringList Object.
    CString strDelimiter;
    _service_provider_frame::GetDelimiter(strDelimiter);

    CStringList strList;
    CString strFrame = CString(m_byFrame);
    _service_provider_frame::PellShell(strFrame);
    ParseFormattedString(strFrame,strDelimiter,strList);

    // Get the type of the frame.
    TSpFrame frameHead;
    POSITION pos = strList.GetHeadPosition();
    frameHead.ParseBuffer(strList,pos);

    //
    PTSpFrame pFrame = TSpFrame::GetInstance(frameHead.strFrameType);

    if (pFrame!=NULL)
    {
        pFrame->SetAutoDel(TRUE);
        pos = strList.GetHeadPosition();
        if (pFrame->ParseBuffer(strList,pos))
        {
            return pFrame;
        }
        else
        {
            pFrame->AutoDel();
            return NULL;
        }
    }

    return NULL;
}

void CSPFrameMgr::BuildPacket(TBaseProtocol* pBasePro,LPBYTE lpBuffer,int& iBufLen)
{
    if (pBasePro->GetProType()==TSpFrame::E_PRO_FLAG)
    {
        PTSpFrame pContent = (PTSpFrame)(pBasePro);

        CString strFrame;
        pContent->GetBuffer(strFrame);

        iBufLen = strFrame.GetLength();
        memcpy(lpBuffer,strFrame.GetBuffer(0),iBufLen);
    }
}