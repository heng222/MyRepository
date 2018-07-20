/************************************************************************
*
* 文件名   ：  FFFE.c
* 版权说明 ：  
* 版本号   ：  1.0  
* 创建时间 ：  2009.08.17
* 作者     ： 
* 功能描述 ：  FFFE协议转义及接收文件 
* 使用注意 ：  所能处理的长度为65535，因为受长度的类型UINT16限制。
* 修改记录 ：  20120706,增加了FFFEPack函数
*
************************************************************************/

#include "FFFE.h"
#include "stdlib.h"

/*FFFE解转义状态*/
#define WAIT_FF_C1 0x00
#define WAIT_FF_C2 0x01
#define WAIT_NO_FF 0x02
#define WAIT_FF_POS 0x03
#define ABNORMAL_STATE 0x04

/*FFFE数据接收状态*/
#define COM_WAIT_START_FF 0x00
#define COM_WAIT_START_FE 0x01
#define COM_WAIT_STOP_FF 0x02
#define COM_WAIT_STOP_FD 0x03

/*
* 功能描述： 将数据进行FFFE转义处理（不加头FFFE及尾FFFD）。
* 输入参数： const UINT8_S *pSrc    数据(无FFFE转义)
*            UINT16_S SrcLen        数据(无FFFE转义)的长度
* 输出参数： UINT8_S *pTgt          数据(经过FFFE转义)
* 返回值：   转义后的长度   
*/
UINT16_S TranslateToFFFE(const UINT8_S *pSrc, UINT8_S *pTgt,UINT16_S SrcLen)
{
    UINT16_S SrcPos = 0;
    UINT16_S TgtPos = 0;
    UINT16_S Pos1 = 0;/*前一个FF的位置*/
    UINT16_S Pos2 = 0;/*后一个FF的位置*/
    UINT16_S iii = 0;/*临时计数变量*/
    UINT16_S Gap = 0;/*两个FF之间的字节数*/
    UINT8_S Got1stFF = 0;/*1-获得前一个FF；0-未获得前一个FF*/

    if((NULL != pSrc) && (NULL != pTgt))
    {
        for(SrcPos=0;SrcPos<SrcLen;SrcPos++)
        {
            if(1 == Got1stFF)
            {
                if(0xFF == pSrc[SrcPos])
                {
                    /*已遇到前一个FF，且当前又遇到FF*/
                    Pos2 = SrcPos;
                    pTgt[TgtPos]=Pos2-Pos1;
                    TgtPos++;

                    for(iii=Pos1+1;iii<Pos2;iii++)
                    {
                        pTgt[TgtPos]=pSrc[iii];
                        TgtPos++;
                    }

                    Got1stFF=0;
                    Pos1=0;
                    Pos2=0;
                    Gap=0;
                }
                else
                {
                    /*已遇到前一个FF，且当前遇到非FF*/
                    Gap++;
                    if(252 == Gap)
                    {
                        Got1stFF=0;
                        Gap=0;
                        pTgt[TgtPos]=0;
                        TgtPos++;
                        for(iii=Pos1+1;iii<=SrcPos;iii++)
                        {
                            pTgt[TgtPos]=pSrc[iii];
                            TgtPos++;
                        }
                    }
                    else
                    {
                        /*Do nothing currently !*/
                    }
                }
            }
            else
            {
                /*尚未遇到前一个FF*/
                pTgt[TgtPos]=pSrc[SrcPos];
                TgtPos++;
                if(0xFF == pSrc[SrcPos])   
                {
                    /*遇到前一个FF*/
                    Got1stFF=1;
                    Pos1=SrcPos;
                    Gap=0;
                }
                else
                {
                    /*Do nothing currently !*/
                }
            }
        }
        /*已经遇到了前一个FF, 且源数据已到了末尾仍未遇到后一个FF*/
        if(1 == Got1stFF)
        {
            pTgt[TgtPos] = 0;
            TgtPos++;

            for(iii=Pos1+1;iii<SrcLen;iii++)
            {
                pTgt[TgtPos]=pSrc[iii];
                TgtPos++;
            }
        }
        else
        {
            /*Do nothing currently !*/
        }
    
    }


    return TgtPos;
}


/*
* 功能描述：  将经过FFFE转义处理后的数据（已经去掉了头FFFE及尾FFFD）还原为原始数据
* 输入参数：  const UINT8_S *pSrc,    数据(FFFE转义)
*             UINT16_S SrcLen,        数据(FFFE转义)的长度
* 输出参数：  UINT8_S *pTgt,          数据(去掉FFFE转义)
* 返回值：    大于0,  转义成功,返回转义后的数据长度
*             0,   有不能转义的字符，转义失败。或者转义后的数据长度为0   
*/
UINT16_S TranslateFromFFFE(const UINT8_S *pSrc,UINT8_S *pTgt,UINT16_S SrcLen)
{
    UINT16_S SrcPos=0;
    UINT16_S TgtPos=0;
    UINT16_S NonFFCount=0;/*进入WAIT_NO_FF状态的次数*/
    UINT16_S NextFFPos=0;/*下一个FF字符的位置*/
    UINT8_S Char=0;/*当前字符值*/
    UINT8_S State=WAIT_FF_C1;/*状态*/

    if((NULL != pSrc) && (NULL != pTgt))
    {
        for(SrcPos=0;SrcPos<SrcLen;SrcPos++)
        {
            Char=pSrc[SrcPos];
            switch(State)
            {
            case WAIT_FF_C1:
                /*等待FF序列第一FF字符*/

                if(0xFF == Char)  
                {
                    /*收到FF字符*/
                    pTgt[TgtPos]=Char;
                    TgtPos++;
                    State = WAIT_FF_C2;
                }
                else
                {
                    /*当前非FF字符*/
                    pTgt[TgtPos]=Char;
                    TgtPos++;
                }

                break;
            case WAIT_FF_C2:
                /*等待FF序列第二FF字符*/

                if( (0xFD==Char) || (0xFE==Char) || (0xFF==Char) )
                {
                    State = ABNORMAL_STATE;
                }
                else
                {
                    if(0 == Char)
                    {
                        State = WAIT_NO_FF;
                    }
                    else
                    {
                        if(1 == Char)
                        {
                            pTgt[TgtPos]=0xff;
                            TgtPos++;
                            State = WAIT_FF_C1;
                        }
                        else
                        {
                            NextFFPos=SrcPos+Char-1;
                            State = WAIT_FF_POS;
                        }
                    }
                }
                break;
            case WAIT_NO_FF:
                /*消息中不再有FF字符需要处理，*/

                NonFFCount++;
                if( (0xFF==Char) && (NonFFCount<=252) )
                {
                    /*如果在252个字符之内存在FF，解码失败*/
                    State = ABNORMAL_STATE;
                }
                else
                {
                    /*接受非FF字符*/
                    pTgt[TgtPos]=Char;
                    TgtPos++;

                    if(252 == NonFFCount)
                    {
                        NonFFCount=0;
                        State = WAIT_FF_C1;
                    }
                    else
                    {
                        /*Do nothing currently !*/
                    }
                }
                break;
            case WAIT_FF_POS:
                /*等待插入FF字符的位置*/

                if(0xFF == Char)
                {
                    /*当前字符是FF字符*/

                    State = ABNORMAL_STATE;
                }
                else
                {
                    /*当前字符非FF字符*/

                    pTgt[TgtPos]=Char;
                    TgtPos++;
                    if(SrcPos == NextFFPos)
                    {
                        pTgt[TgtPos]=0xff;
                        TgtPos++;
                        State = WAIT_FF_C1;
                    }
                    else
                    {
                        /*Do nothing currently !*/
                    }
                }
                break;
            default:
                State = ABNORMAL_STATE;
                break;
            }
            if(State==ABNORMAL_STATE)
            {
                /*非法状态*/
                TgtPos=0;
                break;
            }
            else
            {
                /*Do nothing currently !*/
            }
        }
    
    }

    /*退出时的状态判断*/
    if((State == WAIT_FF_C2)||(State ==WAIT_FF_POS))
    {
        TgtPos = 0;
    }
    else
    {
        /*Do nothing currently!*/
    }
    return TgtPos;
}

/*
* 功能描述：  FFFE结构体初始化函数
* 输入参数：  UINT16_S FFFEBufferSize, 用于接收一帧数据的缓冲区长度   
*             FFFE_STATE_STRU *pFFFEStatStru, FFFE状态结构体
* 返回值：    0,函数执行失败
*             1,函数执行成功
*/
UINT8_S FFFEInit(FFFE_STATE_STRU *pFFFEStatStru,UINT16_S FFFEBufferSize)
{
    UINT8_S ret = 0u;
    
    /*FFFE状态清零复位*/
	if(NULL != pFFFEStatStru)
    {
        pFFFEStatStru->RawDataRcvBufferSize=FFFEBufferSize;
        pFFFEStatStru->pRawDataRcvBuf=(UINT8_S*)malloc(pFFFEStatStru->RawDataRcvBufferSize*sizeof(UINT8_S));
        if (pFFFEStatStru->pRawDataRcvBuf==NULL)
        {
            ret = 0u;
        }
        else
        {
            pFFFEStatStru->RcvState=COM_WAIT_START_FF;
            pFFFEStatStru->GotFrame=0;
            pFFFEStatStru->DataCount=0;

            ret = 1u;
        }
    
    }
    return ret;
}

/*
* 功能描述：   按字符接收待解转义的数据，获得整帧FFFE报文（不含FFFE和FFFD）。
* 输入参数：   UINT8_S RcvChar,      当前接收的字符
*              PORT_STATE_STRU *pFFFEStatStru,
* 输出参数：   UINT8_S *pRawDataRcv,  数据接收缓冲区指针
* 返回值：     大于0,  表示收到完整帧的数据长度，并将收到的完整帧拷贝到接收缓冲区；
*              0,   未收到整帧数据； 
*/

UINT16_S FFFERcv(FFFE_STATE_STRU *pFFFEStatStru,UINT8_S RcvChar, UINT8_S *pRawDataRcv)
{

    UINT16_S ReturnVal = 0;
    UINT16_S iii = 0;
    
	if((NULL != pFFFEStatStru) && (NULL != pRawDataRcv) && (NULL != pFFFEStatStru->pRawDataRcvBuf))
    {
        /*运行接收状态机*/
        switch(pFFFEStatStru->RcvState)
        {
        case COM_WAIT_START_FF:

            /*等待接收开始FF状态*/
            if(0xFF != RcvChar)
            {
                /*Do nothing currently!*/
            }
            else
            {
                pFFFEStatStru->RcvState = COM_WAIT_START_FE;
            }
            break;
        case COM_WAIT_START_FE:

            /*等待接收开始FE状态*/
            if(0xFE != RcvChar)
            {
                pFFFEStatStru->RcvState = COM_WAIT_START_FF;
            }
            else
            {
                pFFFEStatStru->DataCount = 0;
                pFFFEStatStru->GotFrame = 0;
                pFFFEStatStru->RcvState = COM_WAIT_STOP_FF;
            }            
            break;
        case COM_WAIT_STOP_FF:

            /*等待接收停止FF状态*/
            if(0xFF == RcvChar)
            {
                pFFFEStatStru->RcvState = COM_WAIT_STOP_FD;
            }
            else
            {

                if(pFFFEStatStru->DataCount >= pFFFEStatStru->RawDataRcvBufferSize)
                {
                    pFFFEStatStru->DataCount = 0;
                    pFFFEStatStru->GotFrame = 0;
                    pFFFEStatStru->RcvState = COM_WAIT_START_FF;
                }
                else
                {     
                      pFFFEStatStru->pRawDataRcvBuf[pFFFEStatStru->DataCount] = RcvChar; 
                    pFFFEStatStru->DataCount++;

                }
            }
            break;
        case COM_WAIT_STOP_FD:

            /*等待接收停止FD状态*/
            switch(RcvChar)
            {
            case 0xFF:
                pFFFEStatStru->DataCount = 0;
                pFFFEStatStru->GotFrame = 0;
                pFFFEStatStru->RcvState = COM_WAIT_START_FF; 
                break;
            case 0xFE:
                pFFFEStatStru->DataCount = 0;
                pFFFEStatStru->GotFrame = 0;
                pFFFEStatStru->RcvState = COM_WAIT_STOP_FF; 
                break;
            case 0xFD:
                pFFFEStatStru->GotFrame = 1;
                pFFFEStatStru->RcvState = COM_WAIT_START_FF;
                break;
            default:

                if(pFFFEStatStru->DataCount >= (pFFFEStatStru->RawDataRcvBufferSize-1))
                {
                    pFFFEStatStru->DataCount = 0;
                    pFFFEStatStru->GotFrame = 0;
                    pFFFEStatStru->RcvState = COM_WAIT_START_FF;
                }
                else
                {  
                      pFFFEStatStru->pRawDataRcvBuf[pFFFEStatStru->DataCount] = 0xFF; 
                    pFFFEStatStru->DataCount++;
                    pFFFEStatStru->pRawDataRcvBuf[pFFFEStatStru->DataCount] = RcvChar; 
                    pFFFEStatStru->DataCount++;
                    pFFFEStatStru->RcvState = COM_WAIT_STOP_FF; 
                }
                break;
            }
            break;
        default:
            break;
        }
        
        /*收到完整帧*/
        if(1 == pFFFEStatStru->GotFrame)
        {
            for(iii=0; iii<pFFFEStatStru->DataCount; iii++)
            {
                pRawDataRcv[iii] = pFFFEStatStru->pRawDataRcvBuf[iii];
            }

            ReturnVal = pFFFEStatStru->DataCount;
            pFFFEStatStru->DataCount = 0;
            pFFFEStatStru->GotFrame = 0;
        }
        else
        {
            /*Do nothing currently !*/
        }    
    }

    return ReturnVal;
}

/*
* 功能描述：  FFFE状态清理函数
* 输入参数：  PORT_STATE_STRU *pFFFEStatStru, FFFE状态结构体
* 返回值：     
*/
void FFFEFree(FFFE_STATE_STRU *pFFFEStatStru)
{
    /*FFFE清理*/
    #ifdef SYS_TYPE_WINDOWS
	if(NULL != pFFFEStatStru)
    {
        free (pFFFEStatStru->pRawDataRcvBuf);
    }    
    #endif
	if(NULL != pFFFEStatStru)
    {
            pFFFEStatStru->pRawDataRcvBuf = NULL;    
    }

}


/*
* 功能描述： 将数据进行FFFE转义处理,加头FFFE及尾FFFD
* 输入参数： const UINT8_S *pSrc    数据(无FFFE转义)
*            UINT16_S SrcLen        数据(无FFFE转义)的长度
* 输出参数： UINT8_S *pTgt          数据(经过FFFE转义),并添加FFFE头及FFFD尾
* 返回值：   转义后的长度   
*/
UINT16_S FFFEPack(const UINT8_S *pSrc, UINT8_S *pTgt,UINT16_S SrcLen)
{
    UINT16_S PackDataLen=0;
    if((NULL != pSrc) && (NULL != pTgt))
    {
        /*添加FFFE头*/
        pTgt[PackDataLen]=0xFF;
        PackDataLen++;
        pTgt[PackDataLen]=0xFE;
        PackDataLen++;

        /*数据转义*/
        PackDataLen= TranslateToFFFE(pSrc, pTgt+PackDataLen,SrcLen);

        /*添加FFFD尾*/
        pTgt[PackDataLen]=0xFF;
        PackDataLen++;
        pTgt[PackDataLen]=0xFD;
        PackDataLen++;    
    }

    return PackDataLen;


}

