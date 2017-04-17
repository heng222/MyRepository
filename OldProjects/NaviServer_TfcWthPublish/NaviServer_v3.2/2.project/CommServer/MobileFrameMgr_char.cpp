#include "stdafx.h"
#include "MobileFrameMgr_char.h"
#include "CommonFunc.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////////
CMobileFrameMgrChar::CMobileFrameMgrChar(void)
{
	Init();
}

CMobileFrameMgrChar::~CMobileFrameMgrChar(void)
{
}
void CMobileFrameMgrChar::Init(void)
{
	memset(m_byFrame,0,sizeof(m_byFrame));
	m_wFrameLen = 0;
	m_bHasRcvHead = FALSE;
	m_wBlockSize = 0;
}

WORD CMobileFrameMgrChar::GetMaxLenFrame() const
{
    return TMobileFrame_Char::EMaxLenFrame;
}
// 解析给定的数据
void CMobileFrameMgrChar::ParseRawData(LPBYTE pByData, WORD wDataLen,CBaseProtocolList& aFrameList)
{

	//解析出一个完整的帧...
	for (WORD i = 0; i<wDataLen && i<GetMaxLenFrame(); i++)
	{
		switch(pByData[i])
		{

        case TMobileFrame_Char::EHeaderFrame:
			m_byFrame[m_wFrameLen++] = pByData[i];
            if (m_wFrameLen!=1 && m_byFrame[m_wFrameLen-2]==TMobileFrame_Char::EHeaderFrame)
			{
				//初始化
				memset(m_byFrame,0,sizeof(m_byFrame));
				m_wFrameLen = 0;
				m_wBlockSize = 0;
				m_byFrame[m_wFrameLen++] = pByData[i];
				m_byFrame[m_wFrameLen++] = pByData[i];

				//连续收到两个帧头标记
				m_bHasRcvHead = TRUE;
			}
			break;

		default:
            if (m_bHasRcvHead) 
            {
                //
                if(m_wFrameLen == TMobileFrame_Char::EOffBlockSize+TMobileFrame_Char::ESizeBlock)
                {
                    //得到协议体的大小
                    char tmp[5] = {0};
                    memcpy(tmp,m_byFrame+TMobileFrame_Char::EOffBlockSize,TMobileFrame_Char::ESizeBlock);
                    m_wBlockSize = (WORD)StrHextoDeci(tmp);
                }

                // 将收到的数据放入缓冲
                m_byFrame[m_wFrameLen] = pByData[i];
                m_wFrameLen++;

                // 接收到一条完整的帧
                if ( ((m_wBlockSize+TMobileFrame_Char::ESizeOfHeader)==m_wFrameLen)
                    /*&& (m_wBlockSize!=0)*/ )
                {

                    // 解析数据帧为对应的数据结构
                    TBaseProtocol* pFrame = ParsePacket();


                    if (pFrame!=NULL)
                    {
                        aFrameList.AddTail(pFrame);
                    }

                    Init();
                }
            }
		}
	}
}

TBaseProtocol* CMobileFrameMgrChar::ParsePacket()
{
    ASSERT(m_wFrameLen>=TMobileFrame_Char::ESizeOfHeader);

    int iIndex = 0;
    
    // Parse the header of the frame.

    // Get the CommandID of the frame.
    TMobileFrame_Char contentHead;
    int tempIdx = iIndex;
    contentHead.ParseBuffer(m_byFrame,tempIdx);

    // 
    PTMobileFrame_Char pFrame = TMobileFrame_Char::GetInstance(contentHead.wCmdID);

    if (pFrame!=NULL)
    {
        if (!pFrame->ParseBuffer(m_byFrame,iIndex))
        {
            pFrame->AutoDel();
            pFrame = NULL;
        }
    }

    return pFrame;    
}


void CMobileFrameMgrChar::BuildPacket(TBaseProtocol* pBasePro,LPBYTE lpBuffer,int& iBufLen)
{
    ASSERT(pBasePro->GetProType()==TMobileFrame_Char::E_PRO_FLAG);
    if (pBasePro->GetProType()==TMobileFrame_Char::E_PRO_FLAG)
    {
        iBufLen = 0;
        PTMobileFrame_Char pContent = (PTMobileFrame_Char)(pBasePro);
        pContent->CalculateBlockSize();
        pContent->GetBuffer(lpBuffer,iBufLen);
    }
}
