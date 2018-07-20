/*******************************************
* 文件名	：  DmuZcDataHandle.c
* 作  者	：  ZC组
* 创建时间	：  2015-5-25
* 功能描述	：	ZC查询函数
* 备  注	：  无
*******************************************/
#include "DmuZcDataHandle.h"
#include "../../../Dmu/DmuComm/DataHandle/DmuCommDataHandle.h"
#include "../../../Common/Copy.h"
#include "../../../Common/Convert.h"
#include "../../../Common/Malloc.h"
#include "../../../Common/MemSet.h"
#include "../../../Dmu/DmuComm/DataHandle/DmuCommDataTypeDefine.h"
#include "../../../Dmu/DmuComm/Data/ArData.h"
#include "../../../Dmu/DmuComm/Data/StopPointData.h"
#include "../../../Dmu/DmuComm/Data/SegData.h"
#include "../../../Dmu/DmuComm/Data/EmergStopButtonData.h"
#include "../../../Dmu/DmuComm/Data/PlatFormData.h"
#include "../../../Dmu/DmuComm/Data/ProtectZoneData.h"
#include "../../../Dmu/DmuComm/Data/AxleSectionData.h"
#include "../../../Dmu/DmuComm/Data/SwitchData.h"
#include "../../../Dmu/DmuComm/Data/ShieldDoorData.h"
#include "../../../Dmu/DmuComm/Data/RouteData.h"
#include "../../../Dmu/DmuComm/Data/SignData.h"
#include "../../../Dmu/DmuComm/Data/PlatFormData.h"
#include "../../../Dmu/DmuComm/Data/LogicSectionData.h"
#include "../../../Dmu/DmuComm/Data/PointData.h"
#include "../../../Dmu/DmuComm/Load/LoadManage.h"
#include "../Load/LoadZcManage.h"
#include "../../../Dmu/Read/ReadManage.h"
#include "../../../Dmu/DmuComm/DataHandle/DmuCommDataTypeDefine.h"
#include "../../../Dmu/DmuComm/Data/ExitCbtcSectionData.h"
#include "../Data/ZcSignInfoData.h"
#include "../../../Dmu/DmuComm/Data/LineSwitchInfoData.h"
#include "../../../Dmu/DmuComm/Data/SectionTypeData.h"
#include "../../../Dmu/DmuComm/Data/StopSectionData.h"

/*******************************************
* 函数名	： ZcBnfDataInit
* 功能描述: 初始化ZC数据文件
* 参数说明：UINT8* bnfFileAddr   二进制文件的地址
* 返回值：1:成功，	0:失败
*/
INT8_S ZcBnfDataInit(CHAR_S* bnfFileAddr)
{
    INT8_S retVal = 0; /*函数返回值*/

    /*读取BNF文件*/
    ReadManage();

    if (NULL != bnfFileAddr)
    {
        retVal = ReadData(bnfFileAddr);

        if (0 == retVal)
        {
            /*加载数据文件*/
            /*加载线路数据*/
            LoadLineDataManage();
            /*加载运行数据*/
            LoadRunDataManage();
            /*加载系统配置数据*/
            LoadSystemDataManage();
            /*加载分界点数据*/
            LoadDividPointDataManage();
            /*加载ZC相关数据*/
            LoadZcManage();

            /*加载公共数据*/
            retVal =  LoadData();

            /*计算数据中的动态项*/
            if (0 == retVal)
            {
                retVal= (INT8_S)CalcCommAddInfo();
            }
            else
            {
                retVal = 0;
            }

            /*加载ZC数据*/
            if (1 == retVal)
            {
                retVal = LoadZcData();

                if (0 == retVal)
                {
                    retVal = 1;
                }
                else
                {
                    retVal = 0;
                }
            }
        }
        else
        {
            retVal = 0;
        }
    } 
    else
    {
        retVal = 0;
    }

    return retVal;
}

/*******************************************
* 函数名	： GetLineOverlapOfSwitchNum
* 功能描述： 获取保护区段包含的道岔数量
* 参数说明： const UINT16 overlapId,保护区段ID
* 返回值  ： 0xffff: 获取数据失败
*			>0:道岔数量
*/
UINT16_S GetLineOverlapOfSwitchNum(const UINT16_S overlapId)
{
    UINT16_S retVal = UINT16_NULL;
    UINT16_S axleSecId[PROTECTZONE_AXLESGM_MAX_NUM] = {0U};/*计轴区段*/
    UINT16_S axleNum = 0U;/*计轴区段个数*/
    UINT16_S segIdBuff[AXLESECTION_SEG_MAX_NUM] = {0U};/*SEGID*/
    UINT16_S segIdNum = 0U;/*SegID个数*/
    UINT16_S i = 0U;/*循环使用*/
    UINT16_S j = 0U;/*循环使用*/
    UINT16_S index = 0U;/*数组偏移*/
    UINT16_S tempSegIdBuff[AXLESECTION_SEG_MAX_NUM*PROTECTZONE_AXLESGM_MAX_NUM] = {0U};
    UINT16_S switchIdNum = 0U;/*道岔个数*/

    /*获取线路保护区段所属的计轴区段*/
    axleNum = GetLineOverlapOfAcInfo(overlapId,axleSecId);

    for (i = 0U;i < axleNum; i++)
    {
        /*获取计轴区段编号对应的SEGID*/
        segIdNum = GetAxleSectionOfSegInfo(axleSecId[i],segIdBuff);

        for (j = 0U;j < segIdNum; j++)
        {
            tempSegIdBuff[index] = segIdBuff[j];
            index = index + 1U;
        }
    }

    /*查询道岔表，根据SEGID获取道岔的个数*/
    switchIdNum = GetSegIdOfSwitchIdNum(tempSegIdBuff,index);

    if (switchIdNum != 0U)
    {
        retVal = switchIdNum;
    }
    return retVal;
}

/*******************************************
* 函数名	： GetLineRouteOfObsInfo
* 功能描述： 获取进路对应信号机ID
* 参数说明： const UINT16 routeId,进路ID
*            UINT16_S obsInfoBuf[]，障碍物信息数组（id,类型）
* 返回值  ： 0xffff: 获取数据失败
*			>=0:障碍物数量(道岔，PSD,ESB)
*/
UINT16_S GetLineRouteOfObsInfo(const UINT16_S routeId,UINT16_S obsInfoBuf[])
{
    UINT8_S tmpRetVal = 0U;/*局部函数返回值*/
    UINT16_S stationIdBuff[ROUTE_INCLUDE_PLATFORM_MAX_NUM] = {0U};/*站台ID*/
    UINT8_S stationIdNum = 0U;/*站台ID个数*/
    UINT16_S index = 0U;/*数组偏移*/
    BnfRouteStruct* tmpRouteStru = NULL;/*进路结构体*/
    BnfSignStruct* startSignStru = NULL;/*起点信号机结构体*/
    BnfSignStruct* endSignStru = NULL;/*起点信号机结构体*/
    UINT16_S segIdBuff[BOTHSEG_INCLUDE_MAX_SEG]= {0U};/*两个SEG之间包含的SEGID*/
    UINT8_S segIdNum = 0U;/*两个SEG之间包含的SEGID个数*/
    UINT8_S indexSeg = 0U;/*数组偏移*/
    UINT16_S obsNum = UINT16_NULL;

    /*获取进路所属的进路结构体信息*/
    tmpRouteStru = GetIndexIdRouteDataStru(routeId);

    if (tmpRouteStru != NULL)
    {
        /*获取始端信号机ID对应的信息*/
        startSignStru = GetIndexIdSignDataStru(tmpRouteStru->startSignalId);

        /*获取终端信号机ID对应的SEGID*/
        endSignStru = GetIndexIdSignDataStru(tmpRouteStru->endSignalId);

        if((NULL != startSignStru) && (NULL != endSignStru))
        {
            if (startSignStru->protectiveDir == SIGNPRO_DIR_SAME)
            {
                if (startSignStru->signProtectSegOffset == 0U)
                {
                    segIdBuff[indexSeg] = startSignStru->signProtectSegId;
                    indexSeg = indexSeg + 1U;
                }
            }
            else if (startSignStru->protectiveDir == SIGNPRO_DIR_CONTRA)
            {
                if (startSignStru->signProtectSegOffset == GetSegDataStrulength(startSignStru->signProtectSegId))
                { 
                    segIdBuff[indexSeg] = startSignStru->signProtectSegId;
                    indexSeg = indexSeg + 1U;
                }
            }
            else
            {
                /*Do nothing currently !*/
            }

            /*获取信号机范围内的SEG信息*/
            tmpRetVal = GetNoDirNoSwitchStutasSegArray(startSignStru->signProtectSegId,endSignStru->signProtectSegId,0U,&segIdNum,&segIdBuff[indexSeg]);

            /*查找站台表获取此SEGID对应的站台ID*/
            if (1U  == tmpRetVal)
            {
                indexSeg += segIdNum;
                if (endSignStru->protectiveDir == SIGNPRO_DIR_SAME)
                {
                    if (endSignStru->signProtectSegOffset == GetSegDataStrulength(endSignStru->signProtectSegId))
                    {
                        segIdBuff[indexSeg] = endSignStru->signProtectSegId;
                        indexSeg = indexSeg + 1U;
                    }
                }
                else if (endSignStru->protectiveDir == SIGNPRO_DIR_CONTRA)
                {
                    if (endSignStru->signProtectSegOffset == 0U)
                    {
                        segIdBuff[indexSeg] = endSignStru->signProtectSegId;
                        indexSeg = indexSeg + 1U;
                    }
                }
                else
                {
                    /*Do nothing currently !*/
                }

                obsNum = 0U;
                stationIdNum = GetSegIdBelongOfStationId(segIdBuff,indexSeg,stationIdBuff);

                /*查询此站台对应的PSD个数*/
                if(NULL != obsInfoBuf)
                {
                    obsNum = GetStationIdBelongofPsdInfo(stationIdBuff,stationIdNum,(UINT16_S)(obsNum*2U),obsInfoBuf);
                    /*查询此进路对应的道岔个数*/
                    obsNum += GetSegIdBelongofSwitchInfo(segIdBuff,indexSeg,(UINT16_S)(obsNum*2U),&obsInfoBuf[index]);
                    /*查询此站台对应的ESB个数*/
                    obsNum += GetStationIdBelongofEsbInfo(stationIdBuff,stationIdNum,(UINT16_S)(obsNum*2U),&obsInfoBuf[index]);
                }
            }
        }
    }

    return obsNum;
}

/*******************************************
* 函数名	： GetLineSignalDefaultStatus
* 功能描述： 获取线路信号机默认状态
* 参数说明： const UINT16 signalId,信号机ID
* 返回值  ： 0: 获取数据失败
*			0x55/0xaa:默认状态
*/
UINT16_S GetLineSignalDefaultStatus(const UINT16_S signalId)
{
    UINT16_S retVal = 0U;/*函数返回值*/

    retVal = GetZcSignInfoDataStrulightFlag(signalId);

    return retVal;
}


/*******************************************
* 函数名	： GetLineCbtcLightOffType
* 功能描述： 获取线路信号机CBTC列车亮灭类型(预留)
* 参数说明： const UINT16 signalId,信号机ID
* 返回值  ： 0: 获取数据失败
*			0x55/0xaa:CBTC列车亮灭类型
*/
UINT8_S GetLineCbtcLightOffType(const UINT16_S signalId)
{
    UINT8_S retVal = 0U;/*函数返回值*/

    return retVal;
}

/*******************************************
* 函数名	： GetLineCrossType
* 功能描述： 获取线路信号机跨压类型(预留)
* 参数说明： const UINT16 signalId,信号机ID
* 返回值  ： 0: 获取数据失败
*			0x55/0xaa:跨压类型
*/
UINT8_S GetLineCrossType(const UINT16_S signalId)
{
    UINT8_S retVal = 0U;/*函数返回值*/



    return retVal;
}

/*******************************************
* 函数名	： GetLineCrashType
* 功能描述： 获取线路信号机闯信号类型
* 参数说明： const UINT16 signalId,信号机ID
* 返回值  ： 0: 获取数据失败
*			0x55/0xaa:闯信号类型
*/
UINT16_S GetLineCrashType(const UINT16_S signalId)
{
    UINT16_S retVal = 0U;/*函数返回值*/

    retVal = GetZcSignInfoDataStruthroughSignFlag(signalId);

    return retVal;
}

/*******************************************
* 函数名	： GetLineSwitchPosition
* 功能描述： 获取线路道岔位置信息（车辆段/正线）
* 参数说明： const UINT16 switchId,道岔ID
* 返回值  ： 0: 获取数据失败
*			0xaa/0x55:车辆段/正线
*/
UINT8_S GetLineSwitchPosition(const UINT16_S switchId)
{
    UINT8_S retVal = 0U;/*函数返回值*/
    UINT16_S ciId = 0U; /*联锁ID*/

    /*获取所属CI的ID*/
    ciId = GetLineSwitchBelongCiId(switchId);

    /*根据联锁ID获取区域属性*/
    if (ciId > 0U)
    {
        retVal = GetSecPropertyAccordName(DEV_CI_TYPE,ciId);
    }

    return retVal;
}

/*******************************************
* 函数名	： GetLineAcType
* 功能描述： 获取计轴区段类型
* 参数说明： const UINT16 acId，计轴区段ID
* 返回值  ： 0: 获取失败
*			0x55-正线联锁计轴;0xaa-车辆段联锁计轴
*/
UINT8_S GetLineAcType(const UINT16_S acId)
{
    UINT8_S retVal = 0U;/*函数返回值*/
    UINT16_S ciId = 0U; /*联锁ID*/

    /*获取所属CI的ID*/
    ciId = GetLineAcBelongCiId(acId);

    /*根据联锁ID获取区域属性*/
    if (ciId > 0U)
    {
        retVal = GetSecPropertyAccordName(DEV_CI_TYPE,ciId);
    }

    return retVal;
}

/*******************************************
* 函数名	： GetLineAcIncludeSwitchInfo
* 功能描述： 获取计轴区段包含道岔信息
* 参数说明： const UINT16 acId，计轴区段ID
*            UINT8_S *switchNum,道岔数量
*            UINT16_S switchIdBuf[]，道岔ID数组
* 返回值  ： 0: 获取失败
*		    1: 获取成功
*/
UINT8_S GetLineAcIncludeSwitchInfo(const UINT16_S acId,UINT8_S *switchNum,UINT16_S switchIdBuf[])
{
    UINT8_S retVal = 0U;/*函数返回值*/
    UINT16_S pSegId[AXLESECTION_SEG_MAX_NUM] = {0U};/*SEG指针*/
    UINT16_S includeSegNum = 0U;/*包含的SEG个数*/

    /*获取此计轴区段对应的SEG信息*/
    includeSegNum = GetAxleSectionDataStruSegInfo(acId,pSegId);

    /*根据SEG获取道岔ID以及数量*/
    if((NULL != switchNum) && (NULL != switchIdBuf))
    {
        *switchNum = GetSegIdBuffOfSwitchInfo(pSegId,includeSegNum,switchIdBuf);

        if (UINT8_NULL != (*switchNum))
        {
            retVal = 1U;
        }
    }

    return retVal;
}

/*******************************************
* 函数名	： CheckPositionBelongAc
* 功能描述： 查询位置所属计轴区段
* 参数说明： const UINT16 segId,SEG的ID
* 返回值  ： 0: 获取失败
*		    >0: 计轴区段的ID
*/
UINT16_S CheckPositionBelongAc(const UINT16_S segId)
{
    UINT16_S axleSecId = 0U;/*计轴区段*/
    UINT16_S tmpSegBuff[3] = {0U};
    UINT8_S tmpSegNum = 0U;/*SEG个数*/
    UINT8_S needFindNum = 0U;/*需要查找到的个数*/

    /*查询此SEG前后是否有道岔，若有道岔,将前后的SEG写入*/
    tmpSegNum = GetSegBuffAccordSedIdAndSwitch(segId,tmpSegBuff,&needFindNum);
    if (tmpSegNum > 0U)
    {
        axleSecId = GetSegIdBelongofAxleSecId(tmpSegBuff,tmpSegNum,needFindNum);
    }

    return axleSecId;
}

/*******************************************
* 函数名	： CheckAcTopPosition
* 功能描述： 查询计轴区段始端位置
* 参数说明： const UINT16 acId,计轴区段ID
*            const UINT16_S dir,列车相对于seg的期望运行方向
*			 UINT16_S *segId,seg的ID
*			 UINT32_S *offset,相对于seg的偏移量
* 返回值  ： 0: 获取失败
*		    1: 获取成功
*/
UINT8_S CheckAcTopPosition(const UINT16_S acId,const UINT16_S dir,UINT16_S *segId,UINT32_S *offset)
{
    UINT8_S retVal = 0U;/*函数返回值*/
    UINT8_S isErrorFlag = 1U;/*1正确  0 错误*/
    BnfAxleSectionStruct *pAxleSgmtStruct = NULL;/*指向计轴区段信息的结构体指针*/

    /*判断数据输入的有效性*/
    if(UINT16_NULL == GetAxleSectionDataStruIndex(acId))
    {
        /*数据无效，返回错误*/
        isErrorFlag = 0U;
    }

    /*判断运行方向的有效性*/
    if ((0U == isErrorFlag)&&(LINESEG_SAME_DIR != dir) && (LINESEG_CONVER_DIR != dir))
    {
        /*数据无效，返回错误*/
        isErrorFlag = 0U;
    }

    pAxleSgmtStruct = GetIndexIdAxleSectionDataStru(acId);

    if((NULL != pAxleSgmtStruct) && (NULL != segId) && (NULL != offset))
    {
        /*以下情况: 
        列车相对于seg的期望运行方向相同时;计轴区段左端为所需的始端	*/
        if ((1U == isErrorFlag)&&(LINESEG_SAME_DIR == dir))
        {
            *segId = pAxleSgmtStruct->orgnSegId;
            *offset = pAxleSgmtStruct->orgnSegOfst;
            retVal = 0x01U;

        }
        else if((1U == isErrorFlag)&&(LINESEG_CONVER_DIR == dir))
        {
            /*以下情况: 
            列车相对于seg的期望运行方向相反时;计轴区段右端为所需始端	*/
            *segId = pAxleSgmtStruct->tmnlSegId;
            *offset = pAxleSgmtStruct->tmnlSegOfst;
            retVal = 0x01U;
        }
        else
        {
            /*Do nothing currently !*/
        }
    }

    return retVal;
}

/*******************************************
* 函数名	： CheckAcTerminalPosition
* 功能描述： 查询计轴区段终端位置
* 参数说明： const UINT16 acId,计轴区段ID
*            const UINT16_S dir,列车相对于seg的期望运行方向
*			 UINT16_S *segId,seg的ID
*			 UINT32_S *offset,相对于seg的偏移量
* 返回值  ： 0: 获取失败
*		    1: 获取成功
*/
UINT8_S CheckAcTerminalPosition(const UINT16_S acId,const UINT16_S dir,UINT16_S *seg,UINT32_S *offset)
{
    UINT8_S retVal = 0U;/*函数返回值*/
    UINT8_S isErrorFlag = 1U;/*1正确  0 错误*/
    BnfAxleSectionStruct *pAxleSgmtStruct = NULL;/*指向计轴区段信息的结构体指针*/

    /*判断数据输入的有效性*/
    if(UINT16_NULL == GetAxleSectionDataStruIndex(acId))
    {
        /*数据无效，返回错误*/
        isErrorFlag = 0U;
    }

    /*判断运行方向的有效性*/
    if ((0U == isErrorFlag)&&(LINESEG_SAME_DIR != dir) && (LINESEG_CONVER_DIR != dir))
    {
        /*数据无效，返回错误*/
        isErrorFlag = 0U;
    }

    pAxleSgmtStruct = GetIndexIdAxleSectionDataStru(acId);

    if((NULL != pAxleSgmtStruct) && (NULL != seg) && (NULL != offset))
    {
        /*以下情况: 
        列车相对于seg的期望运行方向相同时;计轴区段左端为所需的始端	*/
        if ((1U == isErrorFlag)&&(LINESEG_SAME_DIR == dir))
        {
            *seg = pAxleSgmtStruct->tmnlSegId;
            *offset = pAxleSgmtStruct->tmnlSegOfst;
            retVal = 0x01U;

        }
        else if((1U == isErrorFlag)&&(LINESEG_CONVER_DIR == dir))
        {
            /*以下情况: 
            列车相对于seg的期望运行方向相反时;计轴区段右端为所需始端	*/
            *seg = pAxleSgmtStruct->orgnSegId;
            *offset = pAxleSgmtStruct->orgnSegOfst;
            retVal = 0x01U;
        }
        else
        {
            /*Do nothing currently !*/
        }
    }

    return retVal;
}

/*******************************************
* 函数名	： CheckSwitchBelongAc
* 功能描述： 查询道岔对应的计轴区段
* 参数说明： const UINT16 switchId,道岔ID
*            UINT8_S *acNum,计轴区段数量
*            UINT16_S acIdBuf[],计轴区段ID数组
* 返回值  ： 0: 获取失败
*		    1: 获取成功
*/
UINT8_S CheckSwitchBelongAc(const UINT16_S switchId,UINT8_S *acNum,UINT16_S acIdBuf[])
{
    UINT8_S retVal = 0U;/*函数返回值*/
    UINT8_S axleSecNum = 0U;/*计轴区段树目*/
    UINT16_S i = 0U;/*循环用变量*/
    UINT16_S j = 0U;/*循环用变量*/
    UINT16_S axleSecIdBuff[MAX_ACOFSWITCH_NUM] = {0U};/*计轴区段数组*/	
    BnfAxleSectionStruct *pAxleSecStru =NULL;/*计轴区段信息结构体指针*/
    UINT16_S axleSecLineNum = 0U;/*计轴区段数据长度*/
    UINT8_S errorRetVal = 1U;/*1 正常流程  0 错误退出*/

    /*数组初始化*/
    MemorySet(acIdBuf, ((UINT32_S)(MAX_ACOFSWITCH_NUM*sizeof(UINT16_S))), 
        0U, ((UINT32_S)(MAX_ACOFSWITCH_NUM*sizeof(UINT16_S))));
    MemorySet(axleSecIdBuff,((UINT32_S)(MAX_ACOFSWITCH_NUM*sizeof(UINT16_S))),
        0U, ((UINT32_S)(MAX_ACOFSWITCH_NUM*sizeof(UINT16_S))));

    /*利用管理函数得到计轴区段的相关信息*/
    pAxleSecStru = GetAxleSectionDataInfo(&axleSecLineNum);

    if((NULL != pAxleSecStru) && (NULL != acNum) && (NULL != acIdBuf))
    {
        /*遍历计轴区段信息，得到包含指定道岔的计轴区段*/
        for (i=0U; i<axleSecLineNum; i++)
        {
            for (j=0U; j<pAxleSecStru[i].relatPointNum; j++)
            {
                if (pAxleSecStru[i].relatPointId[j] == switchId)
                {
                    if (axleSecNum == MAX_ACOFSWITCH_NUM)
                    {
                        /*数组越界，返回查询失败*/
                        retVal = 0U;
                        errorRetVal = 0U;
                        break;
                    }
                    else
                    {
                        /*保存计轴区段信息*/
                        axleSecIdBuff[axleSecNum] = pAxleSecStru[i].indexId;
                        axleSecNum++;
                    }
                }
            }

            if (0U == errorRetVal)
            {
                break;
            }
        }

        /*计算完成，输出结果*/
        for (i=0U; (i<axleSecNum)&&(1U == errorRetVal); i++)
        {
            acIdBuf[i] = axleSecIdBuff[i];
            *acNum = axleSecNum;
        }

        if (1U == errorRetVal)
        {
            retVal = 1U;
        }
    }

    return retVal;
}

/*******************************************
* 函数名	： CheckFrontACStatus
* 功能描述： 查询前方计轴区段(道岔在定位或反位)
* 参数说明： const UINT16 acId,计轴区段ID
*            const UINT8_S dir,列车运行方向
*            UINT16_S *frontAcId,前方计轴区段ID
* 返回值  ：0: 获取失败
*		    1: 获取成功
*           2: 线路终点失败
*           3: 道岔原因失败
*/
UINT8_S CheckFrontACStatus(const UINT16_S acId,const UINT8_S dir,UINT16_S *frontAcId)
{
    UINT8_S retVal = 0U;/*函数返回值*/
    UINT16_S adjacentAxleSegID = 0U;/*查询到的相邻计轴区段*/
    UINT8_S errorFlag = 0U;/*错误标记  1正确   0错误*/
    UINT8_S axleSecNum = 0U;/*计轴区段个数*/

    /*判断数据输入方向的正确性*/
    if ((LINESEG_SAME_DIR == dir) || (LINESEG_CONVER_DIR == dir)) 
    {
        /*入口数据正常*/
        errorFlag = 1U;
    }

    if ((1U == errorFlag) && (NULL != frontAcId))
    {
        retVal = FindAdjacentACID(acId,dir,END_POINT,&axleSecNum,&adjacentAxleSegID);

        switch (retVal)
        {
        case 0U:
            *frontAcId = 0U;
            retVal = 0U;
            break;
        case 3U:
            *frontAcId = 0U;
            retVal = 3U;
            break;
        case 1U:
            *frontAcId = adjacentAxleSegID;
            retVal = 1U;
            break;
        case 2U:
            *frontAcId = 0U;
            retVal = 2U;
            break;
        default:
            *frontAcId = 0U;
            retVal = 0U;
            break;
        }
    }

    return retVal;
}

/*******************************************
* 函数名	： CheckRearACStatus
* 功能描述： 查询后方计轴区段(道岔在定位或反位)
* 参数说明：  const UINT16 acId,计轴区段ID
*            const UINT8_S dir,列车运行方向
*            UINT16_S *rearAcId,后方计轴区段ID
* 返回值  ： 0: 获取失败
*		     1: 获取成功
*            2: 线路终点失败
*            3: 道岔原因失败
*/
UINT8_S CheckRearACStatus(const UINT16_S acId,const UINT8_S dir,UINT16_S *rearAcId)
{
    UINT8_S retVal = 0U;/*函数返回值*/
    UINT16_S adjacentAxleSegID = 0U;/*查询到的相邻计轴区段*/
    UINT8_S errorFlag = 1U;/*错误标记  1正确   0错误*/
    UINT8_S axleSecNum = 0U;/*计轴区段个数*/

    /*判断数据输入方向的正确性*/
    if (( dir != LINESEG_SAME_DIR) && (dir != LINESEG_CONVER_DIR)) 
    {
        errorFlag = 0U;
    }

    if((1U == errorFlag) && (NULL != rearAcId))
    {

        retVal = FindAdjacentACID(acId,dir,START_POINT,&axleSecNum,&adjacentAxleSegID);

        switch (retVal)
        {
        case 0U:
            *rearAcId = 0U;
            retVal = 0U;
            break;
        case 3U:
            *rearAcId = 0U;
            retVal = 3U;
            break;
        case 1U:
            *rearAcId = adjacentAxleSegID;
            retVal = 1U;
            break;
        case 2U:
            *rearAcId = 0U;
            retVal = 2U;
            break;
        default:
            *rearAcId = 0U;
            retVal = 0U;
            break;
        }
    }

    return retVal;
}

/*******************************************
* 函数名	： CheckFrontACCanStatus
* 功能描述： 查询前方计轴区段可能的序列(道岔有可能为四开)
* 参数说明： const UINT16 acId,计轴区段ID
*            const UINT8_S dir,列车运行方向
*            UINT16_S *frontAcId,前方计轴区段ID
* 返回值  ： 0，失败
*			1，成功
*			2，线路尽头导致失败
*			3，道岔原因导致失败
*/
UINT8_S CheckFrontACCanStatus(const UINT16_S acId,const UINT8_S dir,UINT8_S* frontAcNum, UINT16_S *frontAcIdBuff)
{
    UINT8_S retVal = 0U;/*函数返回值*/
    UINT8_S errorFlag = 0U;/*错误标记  1正确   0错误*/

    /*判断数据输入方向的正确性*/
    if ((LINESEG_SAME_DIR == dir) || (LINESEG_CONVER_DIR == dir)) 
    {
        /*入口数据正常*/
        errorFlag = 1U;
    }

    if ((1U == errorFlag) && (NULL != frontAcNum) && (NULL != frontAcIdBuff))
    {
        retVal = FindAdjacentACID(acId,dir,END_POINT,frontAcNum,frontAcIdBuff);
    }

    return retVal;
}

/*******************************************
* 函数名	： CheckRearACCanStatus
* 功能描述： 查询后方计轴区段(道岔有可能为四开)
* 参数说明：  const UINT16 acId,计轴区段ID
*            const UINT8_S dir,列车运行方向
*            UINT16_S *rearAcId,后方计轴区段ID
* 返回值  ：0，失败
*			1，成功
*			2，线路尽头导致失败
*			3，道岔原因导致失败
*/
UINT8_S CheckRearACCanStatus(const UINT16_S acId,const UINT8_S dir,UINT8_S* rearAcNum, UINT16_S *rearAcIdBuff)
{
    UINT8_S retVal = 0U;/*函数返回值*/
    UINT8_S errorFlag = 1U;/*错误标记  1正确   0错误*/

    /*判断数据输入方向的正确性*/
    if (( dir != LINESEG_SAME_DIR) && (dir != LINESEG_CONVER_DIR)) 
    {
        errorFlag = 0U;
    }

    if((1U == errorFlag) && (NULL != rearAcNum) && (NULL != rearAcIdBuff))
    {
        retVal = FindAdjacentACID(acId,dir,START_POINT,rearAcNum,rearAcIdBuff);
    }

    return retVal;
}

/*******************************************
* 函数名	： CheckDistanceBetweenTwoPoints
* 功能描述： 查询两点之间的距离区段
* 参数说明： const UINT16 seg1,seg的ID
*            const UINT32_S offset1,seg的偏移量
*            const UINT16_S seg2,seg的ID
*            const UINT32_S offset2,seg的偏移量
*            UINT8_S dir,运行方向
* 返回值  ： UINT32_NULL: 获取失败
*		    其他: 获取成功
*/
UINT32_S CheckDistanceBetweenTwoPoints(const UINT16_S seg1,const UINT32_S offset1,const UINT16_S seg2,const UINT32_S offset2,UINT8_S dir)
{
    UINT8_S retVal = 0U;/*函数返回值*/
    UINT32_S distance = 0U;/*目标距离*/

    retVal = GetDirBothSegPointDisPlus(seg1,offset1,seg2,offset2,dir,&distance);

    if (0U == retVal)
    {
        distance = UINT32_NULL;
    }

    return distance;
}

/*******************************************
* 函数名	： CheckPointNearestSignalBaseDir
* 功能描述： 查询基于方向的离给定点最近的同方向信号机
* 参数说明： const UINT8 dir,运行方向
*            const UINT16_S seg, seg的ID
*            const UINT32_S offset,seg的偏移量
*            UINT16_S *outSignalId,信号机的ID
* 返回值  ： 0: 获取失败
*		     1: 获取成功
*/
UINT8_S CheckPointNearestSignalBaseDir(const UINT8_S dir,const UINT16_S seg,const UINT32_S offset,UINT16_S *outSignalId)
{
    UINT16_S neighborSignalID[4] = {0U};/*函数返回值，列车前方同向信号机ID,2*/
    UINT16_S currentSegID = 0U;/*当前SEG的ID信息*/
    UINT16_S nextSegID = 0U;/*当前SEG的相邻seg信息*/
    UINT8_S retVal = 0U;/*调用函数返回值*/
    BnfSignStruct * signalStru = NULL;/*信号机信息结构体指针*/
    UINT16_S signalSegID = 0U;/*信号机所处seg编号*/
    UINT32_S signalSegOffset = 0U;/*信号机所处seg偏移量*/
    UINT8_S bFlag = 0U;/*找到信号机的标志位，0，未找到信号机；1，找到信号机*/
    UINT8_S  signalNum = DEFAULT_ZERO;
    UINT8_S  signalCycle = DEFAULT_ZERO;
    UINT32_S  destDis = DEFAULT_ZERO;
    UINT32_S  dwMaxDisOfTrainAndSignal = UINT32_NULL;
    UINT16_S searchSignalID = 0U; /*根据函数返回值进行分类*/
    UINT8_S flag = 1U;/*1 正确  0 错误*/

    /*初始化局部变量*/
    MemorySet(&neighborSignalID[0],((UINT32_S)(sizeof(UINT16_S) * 4U)),
        DEFAULT_ZERO,((UINT32_S)(sizeof(UINT16_S) * 4U)));

    /*判断入口数据车头所处seg偏移量的有效性*/
    if (offset > GetSegDataStrulength(seg))
    {
        flag = 0U;
    }

    /*判断入口数据方向的有效性*/
    if ((1U == flag)&&((LINESEG_SAME_DIR == dir) || (LINESEG_CONVER_DIR == dir)))
    {
        flag = 1U;
    }
    else
    {
        flag = 0U;
    }

    /*将车头SEG作为当前SEG*/
    currentSegID = seg;

    /*调用功能函数，查询当前SEG上指定防护方向的信号机信息*/
    if (1U == flag)
    {
        retVal = FindCurrentSegSignal(currentSegID, dir, neighborSignalID, &signalNum);
    }

    /*在当前SEG上找到同向信号机*/
    if (1U == retVal)
    {
        for (signalCycle = (UINT8_S)DEFAULT_ZERO;signalCycle < signalNum;signalCycle++)
        {
            /*利用管理函数直接找到信号机信息*/
            signalStru = GetIndexIdSignDataStru(neighborSignalID[signalCycle]);
            if(NULL != signalStru)
            {
                signalSegID = signalStru->signProtectSegId;
                signalSegOffset = signalStru->signProtectSegOffset;

                /*调用函数“判断两点前后位置”，判断车头位置与信号机位置的前后关系*/
                retVal = CheckLocRelationBetweenTwoPoints(seg, offset, signalSegID, signalSegOffset, dir);

                /*找到的信号机位置在列车安全车头前方，即为所求，*/
                if (2U == retVal)
                {
                    /*信号机位置在列车前方,查询信号机相对于列车的距离*/
                    retVal = GetNoDirBothSegPointDis(seg, offset, signalSegID, signalSegOffset,&destDis);

                    if (1U == retVal)
                    {
                        searchSignalID = signalStru->signId;
                        dwMaxDisOfTrainAndSignal = destDis;
                    } 
                    else
                    {
                        /*继续查找*/
                    }	
                }
            }
        }

        if (searchSignalID != DEFAULT_ZERO)
        {
            /*返回找到的信号机编号，查询成功*/
            bFlag = 1U;		
        }
        else
        {
            /*继续*/
        }
    }
    else
    {
        /*在当前SEG没有找到信号机*/
    }

    /*初始化距离*/
    dwMaxDisOfTrainAndSignal = (UINT32_S)UINT32_NULL;

    /*在当前seg上没有找到信号机，或找到的信号机位于车头后方，需要在车头所处seg的逻辑前方seg上查找信号机*/
    while ((1U == flag)&&(0U == bFlag)) 
    {
        /*调用功能函数，查询当前seg的相邻seg，找到车头所处seg的前方相邻seg*/
        retVal = GetNextSegId(currentSegID, dir,&nextSegID);

        /*利用函数返回值进行判断，函数调用失败*/
        if (0U == retVal)
        {
            /*查询失败*/
            searchSignalID = 0U;
            break;
        }

        /*将找到的相邻seg作为新的当前seg*/
        currentSegID = nextSegID;

        /*调用功能函数，查询当前seg上指定防护方向的信号机信息*/
        retVal = FindCurrentSegSignal(currentSegID, dir, neighborSignalID, &signalNum);

        /*在当前seg上找到同向信号机*/
        if (1U == retVal) 
        {
            for (signalCycle = (UINT8_S)DEFAULT_ZERO;signalCycle < signalNum;signalCycle++)
            {
                /*利用管理函数直接找到信号机信息*/
                signalStru = GetIndexIdSignDataStru(neighborSignalID[signalCycle]);

                /*记录信号机的位置信息。2010.9.6，修改信号机位置为逻辑位置*/
                signalSegID = signalStru->signProtectSegId;
                signalSegOffset = signalStru->signProtectSegOffset;

                /*调用函数“判断两点前后位置”，判断车头位置与信号机位置的前后关系*/
                retVal = CheckLocRelationBetweenTwoPoints(seg, offset, signalSegID, signalSegOffset, dir);

                /*找到的信号机位置在列车安全车头前方，即为所求，*/
                if (2U == retVal)
                {
                    /*信号机位置在列车前方,查询信号机相对于列车的距离*/
                    retVal = GetNoDirBothSegPointDis(seg, offset, signalSegID, signalSegOffset,&destDis);

                    if ((1U == retVal)&&(destDis < dwMaxDisOfTrainAndSignal))
                    {
                        searchSignalID = signalStru->signId;
                        dwMaxDisOfTrainAndSignal = destDis;
                    } 
                    else
                    {
                        /*继续查找*/
                    }	
                }
            }

            if (searchSignalID != DEFAULT_ZERO)
            {
                /*返回找到的信号机编号，查询成功*/
                bFlag = 1U;
                break;		
            }
            else
            {
                /*继续*/
            }
        }
    }

    if ((1U == bFlag) && (NULL != outSignalId))
    {
        *outSignalId = searchSignalID;
        retVal = 1U;
    }

    return retVal;
}

/*******************************************
* 函数名	： CheckLocRelationBetweenTwoPoints
* 功能描述： 查询两点延给定方向的前后关系
* 参数说明： const UINT16 seg1,seg的ID
*            const UINT32_S offset1,seg的偏移量
*            const UINT16_S seg2,seg的ID
*            const UINT32_S offset2,seg的偏移量
*            UINT8_S dir,运行方向
* 返回值  ： 
*    0x01:seg1更远;
*    0x02:seg2更远;
*    0x03:重合
*    0x00:比较失败
*/
UINT8_S CheckLocRelationBetweenTwoPoints(const UINT16_S seg1,const UINT32_S offset1,const UINT16_S seg2,const UINT32_S offset2,UINT8_S dir)
{
#if 0
    UINT8_S tmpRetVal=0U;/*调用的函数的返回值*/
    UINT8_S retVal = 0U;/*函数返回值*/
    UINT16_S currentSeg1ID = 0U;/*记录由seg1找到的当前segID*/
    UINT16_S currentSeg2ID = 0U;/*记录由seg2找到的当前segID*/
    UINT16_S adjecttSeg1ID = 0U;/*记录由seg1找到的相邻segID*/
    UINT16_S adjecttSeg2ID = 0U;/*记录由seg2找到的相邻segID*/
    UINT8_S flagA = 0U;/*位置A开始可以执行查询的标志位*/
    UINT8_S flagB = 0U;/*位置B开始可以执行查询的标志位*/
    UINT16_S tmpSegId=0U; /*临时变量*/
    UINT32_S tmpSegLen=0U;/*临时变量*/
    UINT8_S flag = 1U;/*1 正确  0 错误*/
    UINT8_S isFind = 0U;/*是否已经查询到 1 查询到 0 未查询到*/
    UINT32_S tmpSeg1Len = 0U;
    UINT32_S tmpSeg2Len = 0U;

    /*判断位置1偏移量数据输入的有效性*/
    tmpSeg1Len =  GetSegDataStrulength(seg1);
    if (offset1 > tmpSeg1Len) 
    {
        /*入口参数失常，查询失败，返回默认值*/
        flag = 0U;
    }

    /*判断位置2偏移量数据输入的有效性*/
    tmpSeg2Len =  GetSegDataStrulength(seg2);
    if ((0U == flag)||(offset2 > tmpSeg2Len)) 
    {
        /*入口参数失常，查询失败，返回默认值*/
        flag = 0U;
    }

    /*判断入口数据运行方向的正确性*/
    if ((0U == flag)||((LINESEG_SAME_DIR != dir) && (LINESEG_CONVER_DIR != dir)))
    {
        /*入口参数失常，查询失败，返回默认值*/
        flag = 0U;
    }

    if (1U == flag)
    {
        /*先排除在seg边界点重合的情况*/
        /*从seg1查找seg2*/
        tmpSegLen= tmpSeg1Len;
        if(offset1 == tmpSegLen)
        {
            tmpRetVal = GetNextSegId(seg1, LINESEG_SAME_DIR,&tmpSegId);
            if(1U == tmpRetVal)
            {
                /*成功找到相邻seg*/
                if ((tmpSegId == seg2) &&(offset2 == 0U))
                {
                    /*两点重合*/
                    retVal = 0x03U;
                    isFind = 1U;
                }
            }

        }
        else if (offset1 == 0U)
        {
            tmpRetVal = GetNextSegId(seg1, LINESEG_CONVER_DIR,&tmpSegId);
            if(1U == tmpRetVal)
            {
                tmpSegLen= GetSegDataStrulength(tmpSegId);
                if ((tmpSegId == seg2) &&(offset2 == tmpSegLen))
                {
                    /*两点重合*/
                    retVal = 0x03U;
                    isFind = 1U;
                }
            }
        }
        else
        {
            /* 不处理 */
        }

        /*当两个点在同一个seg时*/
        if((0U == isFind)&&(seg1 == seg2))
        {
            /*方向与seg的逻辑方向相同且第一点的偏移量大于第二点，
            或者方向与seg的逻辑方向相反且第一点的偏移量小于第二点时，第一点在前，第二点在后*/
            if (((LINESEG_SAME_DIR == dir) && (offset1 > offset2)) 
                || ((LINESEG_CONVER_DIR == dir) && (offset1 < offset2)))
            {
                /*查询成功，返回*/
                retVal = 0x01U;
                isFind = 1U;
            }
            else
            {
                if (offset1 == offset2)
                {
                    /*查询成功，返回*/
                    retVal = 0x03U;
                    isFind = 1U;
                }
                else
                {
                    /*方向与seg的逻辑方向相反且第一点的偏移量大于等于第二点，
                    或者方向与seg的逻辑方向相同且第一点的偏移量小于第二点时，第二点在前，第一点在后，返回*/
                    retVal = 0x02U;
                    isFind = 1U;
                }
            }
        }

        /*在两个点不在同一个SEG上*/
        /*将由seg1找到的当前SegID初始化为seg1；由seg2找到的当前SegID初始化为seg2*/
        currentSeg1ID = seg1;
        currentSeg2ID = seg2;

        /*由seg1和seg2按同一方向查找下一条seg，并将找到的segID分别与seg2，seg1进行比较，
        ，在比对发现相同时，跳出while循环*/
        while ((0U == isFind)&&(currentSeg1ID != seg2) && (currentSeg2ID != seg1))
        {

            /*允许查询标志位均为禁止查询，返回查询失败*/
            if ((1U == flagA) && (1U == flagB))
            {
                retVal = 0x00U;	
                isFind = 1U;
                break;
            }

            /*判断标志位状态，可以沿Seg1查找*/
            if ((0U == isFind)&&(0U == flagA))
            {
                /*调用功能函数“查找当前seg的相邻seg”，查找seg1关联的当前seg的相邻seg*/
                tmpRetVal = GetNextSegId(currentSeg1ID, dir,&adjecttSeg1ID);

                /*查询失败，将允许查询的标志位置为禁止查询*/
                if (0U == tmpRetVal)
                {
                    flagA = 1U;				
                }

                /*在由seg1执行查询的标志位为可以继续查询*/
                if (0U == flagA)
                {
                    /*将相邻seg置为新的当前segID*/
                    currentSeg1ID = adjecttSeg1ID;				
                }

            }

            /*判断标志位状态，可以沿Seg2查找*/
            if ((0U == isFind)&&(0U == flagB))
            {
                /*调用功能函数“查找当前segID的相邻segID”，查找seg1关联的当前segID的相邻segID*/
                tmpRetVal = GetNextSegId(currentSeg2ID, dir, &adjecttSeg2ID);

                /*查询失败，将允许查询的标志位置为禁止查询*/
                if (0U == tmpRetVal)
                {
                    flagB = 1U;				
                }	

                /*在由seg1执行查询的标志位为可以继续查询*/
                if (0U == flagB)
                {
                    /*将相邻seg置为新的当前seg*/
                    currentSeg2ID = adjecttSeg2ID;				
                }
            }		
        }

        /*若跳出条件为通过seg1找到seg2，则seg2在前，查询成功，返回*/
        /*isFind用来排除前面已经查找到却再次给返回值赋值*/
        if((0U==isFind)&&(0U == retVal))
        {
            if (currentSeg1ID == seg2)
            {
                retVal = 0x02U;	
            }
            else if (currentSeg2ID == seg1)
            {
                /*跳出条件为通过seg2找到seg1，则seg1在前，查询成功，返回*/
                retVal = 0x01U;
            }
            else
            {
                /*Do nothing currently !*/				
            }
        }
    }

    return retVal;
#endif
    UINT8_S tmpRetVal=0U;/*调用的函数的返回值*/
    UINT8_S retVal = 0U;/*函数返回值*/
    UINT16_S currentSeg1ID = 0U;/*记录由seg1找到的当前segID*/
    UINT16_S currentSeg2ID = 0U;/*记录由seg2找到的当前segID*/
    UINT16_S adjecttSeg1ID = 0U;/*记录由seg1找到的相邻segID*/
    UINT16_S adjecttSeg2ID = 0U;/*记录由seg2找到的相邻segID*/
    UINT16_S tmpSegId=0U; /*临时变量*/
    UINT32_S tmpSegLen=0U;/*临时变量*/
    UINT8_S findFlag = 0U;/*是否已经查询到 1 查询到 0 未查询到*/
    UINT32_S tmpSeg1Len = 0U;
    UINT32_S tmpSeg2Len = 0U;

    /*判断位置1偏移量数据输入的有效性*/
    tmpSeg1Len =  GetSegDataStrulength(seg1);
    tmpSeg2Len =  GetSegDataStrulength(seg2);

    /* 判断输入数据的合法性 */
    if ((tmpSeg1Len >= offset1) && (tmpSeg2Len >= offset2) && ((LINESEG_SAME_DIR == dir) || (LINESEG_CONVER_DIR == dir)))
    {       
        if (seg1 == seg2)
        {
            /* 先排除同在一个seg的情况 */
            if (offset1 == offset2)
            {
                /* 偏移量相同,同1点 */
                retVal = 0x03u;
            }  
            else if(offset1 < offset2)
            {
                /*1点偏移量小 */
                if(LINESEG_SAME_DIR == dir)
                {
                    retVal = 0x02u;
                }
                else
                {
                    retVal = 0x01u;
                }
            }
            else
            {
                /*1点偏移量大 */
                if(LINESEG_SAME_DIR == dir)
                {
                    retVal = 0x01u;
                }
                else
                {
                    retVal = 0x02u;
                }
            }
        }
        else
        {
            /* 先排除在seg边界点重合的情况 */
            tmpSegLen= tmpSeg1Len;

            if(offset1 == tmpSegLen)
            {
                tmpRetVal = GetNextSegId(seg1, LINESEG_SAME_DIR,&tmpSegId);

                if(1U == tmpRetVal)
                {
                    /*成功找到相邻seg*/
                    if ((tmpSegId == seg2) &&(offset2 == 0u))
                    {
                        /*两点重合*/
                        retVal = 0x03u;
                        findFlag = 1u;
                    }
                }

            }
            else if ( 0u == offset1)
            {
                tmpRetVal = GetNextSegId(seg1, LINESEG_CONVER_DIR,&tmpSegId);

                if(1U == tmpRetVal)
                {
                    tmpSegLen= GetSegDataStrulength(tmpSegId);

                    if ((tmpSegId == seg2) &&(offset2 == tmpSegLen))
                    {
                        /*两点重合*/
                        retVal = 0x03u;
                        findFlag = 1u;
                    }
                }
            }
            else
            {
                /* 不处理 */
            }

            if (0u == findFlag)
            {
                /* 处理不是同一个seg且边界点不重合 */ 
                currentSeg1ID = seg1;
                currentSeg2ID = seg2;

                /* 从seg1沿方向向seg2查询 */
                tmpRetVal = GetNextSegId(currentSeg1ID, dir,&adjecttSeg1ID);

                while (0u != tmpRetVal)
                {
                    if (adjecttSeg1ID == seg2)
                    {
                        retVal = 0x02u;
                        findFlag = 1u;
                        break;
                    }

                    currentSeg1ID = adjecttSeg1ID;
                    tmpRetVal = GetNextSegId(currentSeg1ID, dir,&adjecttSeg1ID);
                }

                /* 从seg2沿方向向seg1查询 */
                if (0u == findFlag)
                {
                    tmpRetVal = GetNextSegId(currentSeg2ID, dir,&adjecttSeg2ID);

                    while (0u != tmpRetVal)
                    {
                        if (adjecttSeg2ID == seg1)
                        {
                            retVal = 0x01u;
                            break;
                        }

                        currentSeg2ID = adjecttSeg2ID;
                        tmpRetVal = GetNextSegId(currentSeg2ID, dir,&adjecttSeg2ID);
                    }
                }
            }
        }      
    } 
    else
    {  
        /* 输入参数不合法,返回0 */
        retVal = 0u;
    }

    return retVal;
}

/*******************************************
* 函数名	： CheckPointBelongToOutCbtcArea
* 功能描述： 查询某个点是否属于退出CBTC区域
* 参数说明： UINT16_S wTrainHeadSeg, 
*          UINT32_S dwTrainHeadOffset
* 返回值  ： 0: 获取失败
*		    1: 属于
*            2: 不属于
*/
UINT8_S CheckPointBelongToOutCbtcArea(UINT16_S wTrainHeadSeg, UINT32_S dwTrainHeadOffset)
{
    UINT8_S retVal = 0U;
    UINT32_S segLength = 0U;/*SEG长度*/

    /*对SEGID进行防护*/
    segLength = GetSegDataStrulength(wTrainHeadSeg);
    if (segLength > 0U)
    {
        /*判断此点是否属于退出CBTC区域*/
        retVal = ExitCbtcSecIncludePoint(wTrainHeadSeg,dwTrainHeadOffset);

        if (1U == retVal)
        {
            /*Do nothing currently !*/
        }
        else
        {
            retVal = 2U;
        }
    }

    return retVal;
}

/*******************************************
* 函数名	： CheckAcOrderBetweenTwoPoints
* 功能描述： 查询两点延给定方向的计轴序列(最大支持TWO_POINT_AC_NUM_MAX（20）个计轴)，由seg1到seg2的序列
* 参数说明： const UINT16 seg1,SEG的ID
*            const UINT16_S seg2,SEG的ID
*            const UINT8_S dir,运行方向
*            UINT8_S *acNum,计轴的数量
*            UINT16_S acIdBuff[],计轴的ID 
* 返回值  ： 
*    00,查询失败
*    1,查询成功
*    2,部分成功
*/
UINT8_S CheckAcOrderBetweenTwoPoints(const UINT16_S seg1,const UINT16_S seg2,const UINT8_S dir,UINT8_S *acNum,UINT16_S acIdBuff[])
{
    UINT8_S retVal = 0U;/*函数返回值*/
    UINT16_S pSegId[BOTHSEG_INCLUDE_MAX_SEG] = {0U};/*存放SEGID*/
    UINT8_S includeSegId = 0U;/*包含的SEGID*/

    /*获取两个SEG之间包含的SEGID*/
    retVal = GetDirSegArray(seg1,seg2,dir,1U,&includeSegId,pSegId);

    /*获取SEGID对应的计轴区段*/
    if ((1U == retVal) && (NULL != acIdBuff) && (NULL != acNum))
    {
        *acNum = GetAxleSecAccordSegIdBuff(pSegId,includeSegId,acIdBuff);

        if ((*acNum) > 0U)
        {
            retVal = 1U;
        }
        else
        {
            retVal = 2U;
        }
    }
    else
    {
        retVal = 0U;
    }

    return retVal;
}

/*******************************************
* 函数名	： GetLineSegBelongZcId
* 功能描述： 查询Seg所属ZC
* 参数说明： const UINT16_S segId,
* 返回值  ： 0: 获取失败
*		    >0: 所属ZC
*/
UINT16_S GetLineSegBelongZcId(const UINT16_S segId)
{
    UINT16_S retVal = 0U;/*函数返回值*/

    retVal = GetSegDataStrusegManageZCId(segId);

    return retVal;
}

/*******************************************
* 函数名	：
* 功能描述： 查询点是否位于切换区域的移交区域内
* 参数说明： const UINT16 condominiumLineId 移交区域SEGID
*			 const UINT16_S seg 点所处的SEGID
*            const UINT32_S offset,所在Link的偏移量
* 返回值  ： 0: 获取失败
*		    1: 属于
*            2: 不属于
*/
UINT8_S CheckPointBelongTocondominiumLineOfHand(const UINT16_S condominiumLineId,const UINT16_S seg,const UINT32_S offset)
{
    UINT8_S retVal = 0U;/*函数返回值*/
    BnfLineSwitchInfoStruct* lineSwitchStru = NULL;/*切换线路信息结构体指针*/
    UINT16_S segIdBuff[BOTHSEG_INCLUDE_MAX_SEG] = {0U};/*存放两个SEG之间的SEG*/
    UINT8_S includeSegNum = 0U;/*包含的SEG个数*/
    UINT8_S i = 0U;/*循环使用*/
    UINT16_S zcId = 0U;/*当前SEG所属的ZCID*/
    UINT32_S segLength = 0U;/* SEG的总长 */
    UINT8_S retGetSeg = 0U;

    /*根据切换点ID获取切换线路信息*/
    lineSwitchStru = GetIndexIdLineSwitchInfoDataStru(condominiumLineId);

    if (lineSwitchStru != NULL)
    {
        /*获取切换区域的SegID*/
        retGetSeg = GetDirSegArray(lineSwitchStru->startLineSwitchInfoId,lineSwitchStru->switchPointSegId,lineSwitchStru->lineSwitchDir,0U,&includeSegNum,segIdBuff);

        if (1U == retGetSeg)
        {
            for ( i = 0U; i < includeSegNum; i++)
            {
                zcId = GetSegDataStrusegManageZCId(segIdBuff[i]);
                if ((zcId != 0U)&&(zcId == lineSwitchStru->lineSwitchTraZcId)&&(seg == segIdBuff[i]))
                {
                    retVal = 1U;
                    break;
                }
            }

            if (i == includeSegNum)
            {
                segLength = GetSegDataStrulength(lineSwitchStru->startLineSwitchInfoId);
                if ((seg == (lineSwitchStru->startLineSwitchInfoId))
                    &&((offset >= (lineSwitchStru->startSegOffset))&&(offset <= segLength)))
                {
                    /*查询起点在以及范围内*/
                    zcId = GetSegDataStrusegManageZCId(lineSwitchStru->startLineSwitchInfoId);
                    if ((zcId != 0U)&&(zcId == lineSwitchStru->lineSwitchTraZcId))
                    {
                        retVal = 1U;
                    }
                    else
                    {
                        retVal = 2U;
                    }
                }
                else if ((seg ==lineSwitchStru->endLineSwitchInfoId) && ((offset <= (lineSwitchStru->segEndOffset))))
                {
                    /*查询终点在以及范围内*/
                    zcId = GetSegDataStrusegManageZCId(lineSwitchStru->endLineSwitchInfoId);
                    if ((zcId != 0U)&&(zcId == lineSwitchStru->lineSwitchTraZcId))
                    {
                        retVal = 1U;
                    }
                    else
                    {
                        retVal = 2U;
                    }
                }
                else
                {
                    retVal = 2U;
                }
            }
        }
    }

    return retVal;
}

/*******************************************
* 函数名	：CheckAcBelongToStation
* 功能描述：查询某个计轴区段是否属于站台区域
* 参数说明： const UINT16_S acId
* 返回值  ： 0: 获取失败
*		    1: 属于
*            2: 不属于
*/
UINT8_S CheckAcBelongToStation(const UINT16_S acId)
{
    UINT8_S retVal = 0U;/*函数返回值*/
    UINT16_S pSegId[AXLESECTION_SEG_MAX_NUM] = {0U};
    UINT16_S includeSegNum = 0U;/*包含的SEGID个数*/

    /*获取计轴区段对于的SEGID*/
    includeSegNum = GetAxleSectionDataStruSegInfo(acId,pSegId);
    if (0U < includeSegNum)
    {
        /*查找此SEG是否属于站台区域,返回值为1 属于 2 不属于*/
        retVal = SearchStationBelongAxleSec(pSegId,includeSegNum);
    }

    return retVal;
}

/*******************************************
* 函数名	： CheckSwitchOrderBetweenTwoPoints
* 功能描述： 查询两点延给定方向的道岔序列(最大支持TWO_POINT_SWITCH_NUM_MAX（30）个)，由seg1到seg2的序列
* 参数说明： const UINT16_S seg1,
*          const UINT16_S seg2,
*          UINT8_S dir,
*          UINT8_S *switchNum,
*          UINT16_S swtichIdBuff[],
* 返回值  ： 
*    00,查询失败
*    1,查询成功
*    2,部分成功
*/
UINT8_S CheckSwitchOrderBetweenTwoPoints(const UINT16_S seg1,const UINT16_S seg2,UINT8_S dir,UINT8_S *switchNum,UINT16_S swtichIdBuff[])
{
    UINT8_S retVal = 0U;/*函数返回值*/
    UINT16_S pSegId[BOTHSEG_INCLUDE_MAX_SEG] = {0U};/*存放SEGID*/
    UINT8_S includeSegId = 0U;/*包含的SEGID*/

    /*获取两个SEG之间包含的SEGID*/
    retVal = GetDirSegArray(seg1,seg2,dir,1U,&includeSegId,pSegId);

    /*获取SEGID对应的道岔*/
    if ((1U == retVal) && (NULL != switchNum) && (NULL != swtichIdBuff))
    {
        *switchNum = GetSegIdBuffOfSwitchInfo(pSegId,((UINT16_S)includeSegId),swtichIdBuff);

        if ((*switchNum) > 0U)
        {
            retVal = 1U;
        }
        else
        {
            retVal = 2U;
        }
    }
    else
    {
        retVal = 0U;
    }

    return retVal;
}

/*******************************************
* 函数名	： CheckPsdOrderBetweenTwoPoints
* 功能描述： 查询两点延给定方向的屏蔽门序列(最大支持TWO_POINT_PSD_NUM_MAX（10）个)，由seg1到seg2的序列
* 参数说明： const UINT16_S seg1,
*          const UINT16_S seg2,
*          UINT8_S dir,
*          UINT8_S *psdNum,
*          UINT16_S psdIdBuff[],
* 返回值  ： 
*    00,查询失败
*    1,查询成功
*    2,部分成功
*/
UINT8_S CheckPsdOrderBetweenTwoPoints(const UINT16_S seg1,const UINT16_S seg2,UINT8_S dir,UINT8_S *psdNum,UINT16_S psdIdBuff[])
{
    UINT8_S retVal = 0U;/*函数返回值*/
    UINT16_S pSegId[BOTHSEG_INCLUDE_MAX_SEG] = {0U};/*存放SEGID*/
    UINT8_S includeSegId = 0U;/*包含的SEGID*/
    UINT8_S platPormNum = 0U;/*站台个数*/
    UINT16_S platPormBuff[TWO_POINT_STATION_NUM_MAX] = {0U};/*两个SEG之间的站台iD*/

    if ((NULL != psdNum) && (NULL != psdIdBuff))
    {
        *psdNum = 0U;

        /*获取两个SEG之间包含的SEGID*/
        retVal = GetDirSegArray(seg1,seg2,dir,1U,&includeSegId,pSegId);

        /*获取SEGID对应的站台ID*/
        if (1U == retVal)
        {
            platPormNum = GetPlatformIdAccordSegBuff(pSegId,includeSegId,platPormBuff);
            if (platPormNum > 0U)
            {
                /*根据站台ID获取对应的屏蔽门ID*/
                *psdNum = GetPsdIdAccordPlatformIdBuff(platPormBuff,platPormNum,psdIdBuff);

                if ((*psdNum) > 0U)
                {
                    retVal = 1U;
                }
                else
                {
                    retVal = 2U;
                }
            }
            else
            {
                /*Do nothing currently !*/
            }
        }
    }

    return retVal;
}

/*******************************************
* 函数名	：  CheckEsbOrderBetweenTwoPoints
* 功能描述： 查询两点延给定方向的紧急停车按钮序列(最大支持TWO_POINT_ESB_NUM_MAX（10）个)，由seg1到seg2的序列
* 参数说明： const UINT16_S seg1,
*          const UINT16_S seg2,
*          UINT8_S dir,
*          UINT8_S *esbNum,
*          UINT16_S esbIdBuff[],
* 返回值  ： 
*    00,查询失败
*    1,查询成功
*    2,部分成功
*/
UINT8_S CheckEsbOrderBetweenTwoPoints(const UINT16_S seg1,const UINT16_S seg2,UINT8_S dir,UINT8_S *esbNum,UINT16_S esbIdBuff[])
{
    UINT8_S retVal = 0U;/*函数返回值*/
    UINT16_S pSegId[BOTHSEG_INCLUDE_MAX_SEG] = {0U};/*存放SEGID*/
    UINT8_S includeSegId = 0U;/*包含的SEGID*/
    UINT8_S platPormNum = 0U;/*站台个数*/
    UINT16_S platPormBuff[TWO_POINT_STATION_NUM_MAX] = {0U};/*两个SEG之间的站台iD*/

    if ((NULL != esbNum) && (NULL != esbIdBuff))
    {
        *esbNum = 0U;

        /*获取两个SEG之间包含的SEGID*/
        retVal = GetDirSegArray(seg1,seg2,dir,1U,&includeSegId,pSegId);

        /*获取SEGID对应的站台ID*/
        if (1U == retVal)
        {
            platPormNum = GetPlatformIdAccordSegBuff(pSegId,includeSegId,platPormBuff);
            if (platPormNum > 0U)
            {
                /*根据站台ID获取对应的紧急停车按钮ID*/
                *esbNum = GetEsbIdAccordPlatformIdBuff(platPormBuff,platPormNum,esbIdBuff);

                if (*esbNum > 0U)
                {
                    retVal = 1U;
                }
                else
                {
                    retVal = 2U;
                }
            }
            else
            {
                /*Do nothing currently !*/
            }
        }
    }

    return retVal;
}

/*******************************************
* 函数名	： CheckSuperpositionBetweenTwoArea
* 功能描述： 查询两个区域的重合区域
* 参数说明： const UINT8 logicSectionNum,逻辑区段数量
*            const UINT16_S logicSectionId[],逻辑区段ID数组(最大逻辑区段数量50个)
*            const AreaInfoStruct maArea,移动授权区域
*            const UINT8_S dir,列车运行方向
*            UINT8_S *superAreaNum,重合区域数量
*            AreaInfoStruct superArea[],重合区域(最大重合区域5个)
* 返回值  ： 
*    0,查询失败
*    1,查询成功
*/
UINT8_S CheckSuperpositionBetweenTwoArea(const UINT8_S logicSectionNum, const UINT16_S logicSectionId[],const AreaInfoStruct maArea,const UINT8_S dir,UINT8_S *superAreaNum,AreaInfoStruct superArea[])
{
    UINT8_S retVal = 0U;/*函数返回值*/
    UINT8_S tmpRetVal = 0U;/*函数返回值*/
    UINT8_S errorFlag = 1U;/*1正确 0 错误*/
    BnfSegStruct* maStartSegStru = NULL;/*MA起点信息的SEG信息结构体指针*/
    BnfSegStruct* maEndSegStru = NULL;/*MA终点信息的SEG信息结构体指针*/
    BnfLogicSectionStruct* tmpLogStru = NULL;
    UINT8_S i = 0U;/*循环使用*/
    UINT8_S j = 0U;/*循环使用*/
    UINT8_S k = 0U;/*循环使用*/
    UINT8_S firstFind = 0U;
    UINT8_S findIndex = 0U;
    UINT8_S tmpFingFlag = 0U;

    UINT16_S tmpLogicId[TWO_POINT_LOGICSEC_NUM_MAX] = {0U};
    UINT8_S tmpRelateLogicNum[TWO_POINT_LOGICSEC_NUM_MAX] = {0U};
    BnfRelateLogicSecInfoStruct relateLogicInfo[TWO_POINT_LOGICSEC_NUM_MAX][2];
    UINT8_S tmpLogicNum = 0U;

    /*入口防护*/
    maStartSegStru = GetIndexIdSegDataStru(maArea.startSegId);
    if ((NULL == maStartSegStru)||(maStartSegStru->length < maArea.startSegOffSet))
    {
        errorFlag = 0U;
    }

    maEndSegStru = GetIndexIdSegDataStru(maArea.endSegId);
    if ((0U == errorFlag)||(NULL == maEndSegStru)||(maEndSegStru->length < maArea.endSegOffSet))
    {
        errorFlag = 0U;
    }

    if ((0U == errorFlag)||((dir != LINESEG_SAME_DIR)&&(dir != LINESEG_CONVER_DIR)))
    {
        errorFlag = 0U;
    }

    if ((logicSectionId == NULL)||(superAreaNum == NULL) || (NULL == superArea))
    {
        errorFlag = 0U;
    }

    if (1U == errorFlag)
    {
        *superAreaNum = 0U;
        /*判断两点内包含的逻辑区段ID*/
        tmpRetVal = GetDirSegArrayAndLogicSec(maArea.startSegId,maArea.startSegOffSet,maArea.endSegId,maArea.endSegOffSet,dir,&tmpLogicNum,tmpLogicId,tmpRelateLogicNum,relateLogicInfo);

        if (1U == tmpRetVal)
        {
            /*判断输入的逻辑区段是否与此区域，若有重合区域,输出重合区域*/

            for (j = 0U; (j < tmpLogicNum)&&(1U == errorFlag); j++)
            {
                for (i = 0U;( i < logicSectionNum); i++)
                {
                    if (tmpLogicId[j] == logicSectionId[i])
                    {
                        tmpFingFlag = 0U;
                        tmpLogStru = GetIndexIdLogicSectionDataStru(logicSectionId[i]);
                        if (NULL != tmpLogStru)
                        {
                            if (firstFind == 0U)
                            {
                                firstFind = 1U;
                                for ( k = 0U; k < tmpLogStru->includeSegIdNum; k++)
                                {
                                    if (tmpLogStru->segIdBuff[k] == maArea.startSegId)
                                    {
                                        break;
                                    }
                                }

                                if (LINESEG_SAME_DIR == dir)
                                {
                                    /*DNW,2016.3.13,添加不等于1的条件，解决1个seg中多个逻辑区段的情况*/
                                    if ((k < tmpLogStru->includeSegIdNum)
                                        && (1U != tmpLogStru->includeSegIdNum))
                                    {
                                        superArea[*superAreaNum].startSegId = maArea.startSegId;
                                        superArea[*superAreaNum].startSegOffSet = maArea.startSegOffSet;
                                    }
                                    else
                                    {
                                        superArea[*superAreaNum].startSegId = tmpLogStru->startSegId;
                                        superArea[*superAreaNum].startSegOffSet = tmpLogStru->startSegOffset;
                                    }
                                    superArea[*superAreaNum].endSegId = tmpLogStru->endSegId;
                                    superArea[*superAreaNum].endSegOffSet = tmpLogStru->endSegOffset;
                                }
                                else
                                {
                                    if ((k < tmpLogStru->includeSegIdNum)
                                        && (1U != tmpLogStru->includeSegIdNum))
                                    {
                                        superArea[*superAreaNum].startSegId = maArea.startSegId;
                                        superArea[*superAreaNum].startSegOffSet = maArea.startSegOffSet;
                                    }
                                    else
                                    {
                                        superArea[*superAreaNum].startSegId = tmpLogStru->endSegId;
                                        superArea[*superAreaNum].startSegOffSet = tmpLogStru->endSegOffset;
                                    }
                                    superArea[*superAreaNum].endSegId = tmpLogStru->startSegId;
                                    superArea[*superAreaNum].endSegOffSet = tmpLogStru->startSegOffset;
                                }
                            }
                            else
                            {
                                if (dir == LINESEG_SAME_DIR)
                                {
                                    if ((j - findIndex) == 1U)
                                    {
                                        superArea[*superAreaNum].endSegId = tmpLogStru->endSegId;
                                        superArea[*superAreaNum].endSegOffSet = tmpLogStru->endSegOffset;
                                    }
                                    else
                                    {
                                        (*superAreaNum)++;
                                        superArea[*superAreaNum].startSegId = tmpLogStru->startSegId;
                                        superArea[*superAreaNum].startSegOffSet = tmpLogStru->startSegOffset;
                                        superArea[*superAreaNum].endSegId = tmpLogStru->endSegId;
                                        superArea[*superAreaNum].endSegOffSet = tmpLogStru->endSegOffset;
                                    }
                                }
                                else
                                {
                                    if ((j - findIndex) == 1U)
                                    {
                                        superArea[*superAreaNum].endSegId = tmpLogStru->startSegId;
                                        superArea[*superAreaNum].endSegOffSet = tmpLogStru->startSegOffset;
                                    }
                                    else
                                    {
                                        (*superAreaNum)++;
                                        superArea[*superAreaNum].startSegId = tmpLogStru->endSegId;
                                        superArea[*superAreaNum].startSegOffSet = tmpLogStru->endSegOffset;
                                        superArea[*superAreaNum].endSegId = tmpLogStru->startSegId;
                                        superArea[*superAreaNum].endSegOffSet = tmpLogStru->startSegOffset;
                                    }
                                }
                            }
                        }
                        else
                        {
                            errorFlag = 0U;
                        }

                        findIndex = j;

                        break;
                    }
                    else
                    {
                        if (tmpRelateLogicNum[j] > 0U)
                        {
                            for (k = 0U;k <= tmpRelateLogicNum[j];k++)
                            {
                                if (logicSectionId[i] == relateLogicInfo[j][k].relateLogicId)
                                {
                                    tmpFingFlag = 0U;
                                    if (firstFind == 0U)
                                    {
                                        firstFind = 1U;

                                        if (LINESEG_SAME_DIR == dir)
                                        {
                                            if (relateLogicInfo[j][k].relateSegId == maArea.startSegId)
                                            {
                                                superArea[*superAreaNum].startSegId = maArea.startSegId;
                                                superArea[*superAreaNum].startSegOffSet = maArea.startSegOffSet;

                                                superArea[*superAreaNum].endSegId = maArea.startSegId;
                                                superArea[*superAreaNum].endSegOffSet = GetSegDataStrulength(maArea.startSegId);

                                                if (relateLogicInfo[j][k].pointFalg == START_POINT)
                                                {
                                                    (*superAreaNum)++;
                                                    tmpFingFlag = 1U;
                                                }
                                            }
                                            else if (relateLogicInfo[j][k].relateSegId == maArea.endSegId)
                                            {
                                                superArea[*superAreaNum].startSegId = maArea.endSegId;
                                                superArea[*superAreaNum].startSegOffSet = 0U;
                                                superArea[*superAreaNum].endSegId = maArea.endSegId;
                                                superArea[*superAreaNum].endSegOffSet = maArea.startSegOffSet;
                                            }
                                            else
                                            {
                                                superArea[*superAreaNum].startSegId = relateLogicInfo[j][k].relateSegId;
                                                superArea[*superAreaNum].startSegOffSet = 0U;
                                                superArea[*superAreaNum].endSegId = relateLogicInfo[j][k].relateSegId;
                                                superArea[*superAreaNum].endSegOffSet =  GetSegDataStrulength(relateLogicInfo[j][k].relateSegId);
                                                if (relateLogicInfo[j][k].pointFalg == START_POINT)
                                                {
                                                    (*superAreaNum)++;
                                                    tmpFingFlag = 1U;
                                                }
                                            }

                                        }
                                        else
                                        {
                                            if (relateLogicInfo[j][k].relateSegId == maArea.startSegId)
                                            {
                                                superArea[*superAreaNum].startSegId = maArea.startSegId;
                                                superArea[*superAreaNum].startSegOffSet = maArea.startSegOffSet;
                                                superArea[*superAreaNum].endSegId = maArea.startSegId;
                                                superArea[*superAreaNum].endSegOffSet = 0U;
                                                if (relateLogicInfo[j][k].pointFalg == END_POINT)
                                                {
                                                    (*superAreaNum)++;
                                                    tmpFingFlag = 1U;
                                                }
                                            }
                                            else if (relateLogicInfo[j][k].relateSegId == maArea.endSegId)
                                            {
                                                superArea[*superAreaNum].startSegId = maArea.endSegId;
                                                superArea[*superAreaNum].startSegOffSet = GetSegDataStrulength(maArea.endSegId);
                                                superArea[*superAreaNum].endSegId = maArea.endSegId;
                                                superArea[*superAreaNum].endSegOffSet = maArea.endSegOffSet;
                                            }
                                            else
                                            {
                                                superArea[*superAreaNum].startSegId = relateLogicInfo[j][k].relateSegId;
                                                superArea[*superAreaNum].startSegOffSet = GetSegDataStrulength(relateLogicInfo[j][k].relateSegId);
                                                superArea[*superAreaNum].endSegId = relateLogicInfo[j][k].relateSegId;
                                                superArea[*superAreaNum].endSegOffSet = 0U;

                                                if (relateLogicInfo[j][k].pointFalg == END_POINT)
                                                {
                                                    (*superAreaNum)++;
                                                    tmpFingFlag = 1U;
                                                }
                                            }
                                        }
                                    }
                                    else
                                    {
                                        if (dir == LINESEG_SAME_DIR)
                                        {
                                            if ((j - findIndex) == 1U)
                                            {
                                                if (relateLogicInfo[j][k].pointFalg == END_POINT)
                                                {
                                                    (*superAreaNum)++;
                                                    superArea[*superAreaNum].startSegId = relateLogicInfo[j][k].relateSegId;
                                                    superArea[*superAreaNum].startSegOffSet = 0U;
                                                    superArea[*superAreaNum].endSegId = relateLogicInfo[j][k].relateSegId;
                                                    superArea[*superAreaNum].endSegOffSet = GetSegDataStrulength(relateLogicInfo[j][k].relateSegId);
                                                }
                                                else
                                                {
                                                    superArea[*superAreaNum].endSegId = relateLogicInfo[j][k].relateSegId;
                                                    superArea[*superAreaNum].endSegOffSet = GetSegDataStrulength(relateLogicInfo[j][k].relateSegId);
                                                    (*superAreaNum)++;
                                                    tmpFingFlag = 1U;
                                                }

                                            }
                                            else
                                            {
                                                (*superAreaNum)++;
                                                superArea[*superAreaNum].startSegId = relateLogicInfo[j][k].relateSegId;
                                                superArea[*superAreaNum].startSegOffSet = 0U;
                                                superArea[*superAreaNum].endSegId = relateLogicInfo[j][k].relateSegId;
                                                superArea[*superAreaNum].endSegOffSet = GetSegDataStrulength(relateLogicInfo[j][k].relateSegId);
                                                if (relateLogicInfo[j][k].pointFalg == START_POINT)
                                                {
                                                    (*superAreaNum)++;
                                                    tmpFingFlag = 1U;
                                                }
                                            }
                                        }
                                        else
                                        {
                                            if ((j - findIndex) == 1U)
                                            {
                                                if (relateLogicInfo[j][k].pointFalg == START_POINT)
                                                {
                                                    (*superAreaNum)++;
                                                    superArea[*superAreaNum].startSegId = relateLogicInfo[j][k].relateSegId;
                                                    superArea[*superAreaNum].startSegOffSet = GetSegDataStrulength(relateLogicInfo[j][k].relateSegId);
                                                    superArea[*superAreaNum].endSegId = relateLogicInfo[j][k].relateSegId;
                                                    superArea[*superAreaNum].endSegOffSet = 0U;
                                                }
                                                else
                                                {
                                                    superArea[*superAreaNum].endSegId = relateLogicInfo[j][k].relateSegId;
                                                    superArea[*superAreaNum].endSegOffSet = 0U;
                                                    (*superAreaNum)++;
                                                    tmpFingFlag = 1U;
                                                }
                                            }
                                            else
                                            {
                                                (*superAreaNum)++;
                                                superArea[*superAreaNum].startSegId = tmpLogStru->endSegId;
                                                superArea[*superAreaNum].startSegOffSet = tmpLogStru->endSegOffset;
                                                superArea[*superAreaNum].endSegId = tmpLogStru->startSegId;
                                                superArea[*superAreaNum].endSegOffSet = tmpLogStru->startSegOffset;

                                                if (relateLogicInfo[j][k].pointFalg == END_POINT)
                                                {
                                                    (*superAreaNum)++;
                                                    tmpFingFlag = 1U;
                                                }
                                            }
                                        }
                                    }

                                    findIndex = j;

                                    break;
                                }
                            }
                        }
                    }
                }
            }

            if(findIndex == (j-1U))
            {
                if (tmpFingFlag == 0U)
                {
                    if (superArea[*superAreaNum].endSegId == maArea.endSegId)
                    {
                        superArea[*superAreaNum].endSegOffSet = maArea.endSegOffSet;
                    }
                }
                else
                {
                    if (superArea[(*superAreaNum)-1U].endSegId == maArea.endSegId)
                    {
                        superArea[(*superAreaNum)-1U].endSegOffSet = maArea.endSegOffSet;
                    }
                }
            }
        }

    }

    if (firstFind > 0U)
    {
        if (tmpFingFlag == 0U)
        {
            (*superAreaNum) =(*superAreaNum) + 1U;
        }
    }

    if (1U == errorFlag)
    {
        retVal = 1U;
    }

    return retVal;
}


/*******************************************
* 函数名	： CheckPointReclosingAtQuitCbtc
* 功能描述： 查询某个点是否和退出CBTC区域终点重合
* 参数说明： const UINT16_S seg,
*          const UINT32_S offset,
* 返回值  ： 
*    0,查询失败
*    1,重合
*    2,不重合
*/
UINT8_S CheckPointReclosingAtQuitCbtc(const UINT16_S seg,const UINT32_S offset)
{
    UINT8_S retVal = 0U;/*函数返回值*/
    UINT32_S  tmpSegLen = 0U;

    tmpSegLen = GetSegDataStrulength(seg);
    if ((0U == tmpSegLen)||(offset > tmpSegLen))
    {
        retVal = 0U;
    }
    else
    {
        retVal = CheckAtQuitCbtcIsFindPoint(seg,offset);
    }

    return retVal;	
}

/*******************************************
* 函数名	：  CheckPointBelongToArea
* 功能描述： 查询某个点是否属于某个区域
* 参数说明： const UINT16_S startSeg,
*          const UINT32_S startOffset,
*          const UINT16_S endSeg,
*          const UINT32_S endOffset,
*          const UINT16_S checkSeg,
*          const UINT32_S checkOffset,
*          const UINT8_S dir,
* 返回值  ： 
*    0,不属于
*    1,属于
*/
UINT8_S CheckPointBelongToArea(const UINT16_S startSeg,const UINT32_S startOffset,const UINT16_S endSeg,const UINT32_S endOffset,const UINT16_S checkSeg,const UINT32_S checkOffset,const UINT8_S dir)
{
#if 0
    UINT8_S retVal = 0U;/*函数返回值*/
    UINT8_S i = 0U;/*循环用变量*/
    UINT8_S bFlag = 0U;/*标志位*/
    UINT16_S* pSegId = NULL;
    UINT8_S segBothPointNum = 0U;/*两个SEG间的SEG数目*/
    UINT32_S disStartToTrain = UINT32_NULL;/*起点到列车点距离*/
    UINT32_S disStartToEnd = UINT32_NULL;/*起点到终点距离*/
    UINT32_S disEndToTrain = UINT32_NULL;/*终点到列车点距离*/
    UINT8_S errorFlag = 1U;/*1正确 0 错误*/
    UINT16_S segTableNum = 0U;/*获取SEG表的行数*/
    UINT8_S disRtnValue1 = 0U;  /* 获取2点之间距离返回值 */
    UINT8_S disRtnValue2 = 0U;  /* 获取2点之间距离返回值 */
    UINT8_S disRtnValue3 = 0U;  /* 获取2点之间距离返回值 */

    /*判断方向的有效性*/
    if ((dir != LINESEG_SAME_DIR) && (dir != LINESEG_CONVER_DIR))
    {
        errorFlag = 0U;
    }

    segTableNum = GetSegIdNum();
    pSegId = (UINT16_S*)MemoryMalloc(sizeof(UINT16_S)*segTableNum);

    printf("cc %d-%d-%d-%d-0x%x\n",startSeg,endSeg,segTableNum,sizeof(UINT16_S),pSegId);
    if (NULL != pSegId)
    {    
        /*当起点终点在同一seg时*/
        if ((1U == errorFlag)&&(startSeg ==  endSeg))
        {
            /*给定点在该seg上时，利用偏移量进行判断*/
            if (startSeg == checkSeg)
            {
                /*偏移量判断*/
                if (((startOffset >= checkOffset) && (endOffset <= checkOffset)) || ((endOffset >= checkOffset) && (startOffset <= checkOffset)))
                {
                    /*点在区域内*/
                    retVal = 1U;
                }
                else
                {
                    /*点不在区域内*/
                    retVal = 0U;
                }
            }
            else
            {
                /*seg号不同，必不在区域内*/
                retVal = 0U;
            }
        }
        else if ((1U == errorFlag))
        {
            /*起点，终点在不同的seg*/
            /*调用函数，查询两点间的seg序列，得到起终点间的seg序列*/
            retVal = GetDirSegArray(startSeg, endSeg, dir,1U,&segBothPointNum, pSegId);

            /*查询失败*/
            if (1U == retVal)
            {
                /*判断点是否在seg序列内*/
                for (i=0U; i<segBothPointNum; i++)
                {
                    if (pSegId[i] == checkSeg)
                    {
                        /*置标志位*/
                        bFlag = 1U;
                        break;
                    }
                }

                if (0U == bFlag)
                {
                    /*点不在区域内，返回*/
                    retVal = 0U;
                }
                else
                {
                    /*利用距离进行判断,计算三个点间的距离*/
                    disRtnValue1 = GetDirBothSegPointDisPlus(startSeg, startOffset, checkSeg, checkOffset,dir,&disStartToTrain);
                    disRtnValue2 = GetDirBothSegPointDisPlus(startSeg, startOffset, endSeg, endOffset, dir,&disStartToEnd);
                    disRtnValue3 = GetDirBothSegPointDisPlus(checkSeg, checkOffset, endSeg, endOffset, dir, &disEndToTrain);

                    if ((UINT32_NULL == disStartToTrain) || (UINT32_NULL == disStartToEnd) || (UINT32_NULL == disEndToTrain))
                    {
                        /*函数调用失败，理论上不会失败*/
                        retVal = 0U;
                    }

                    if ((1U == disRtnValue1) && (1U == disRtnValue2) && (1U == disRtnValue3))
                    {
                        if ((disStartToTrain + disEndToTrain) == disStartToEnd)
                        {
                            /*点在区域内*/
                            retVal = 1U;
                        }
                        else
                        {
                            /*点不在区域内*/
                            retVal = 0U;
                        }
                    }
                    else
                    {
                        /* GetDirBothSegPointDisPlus函数沿方向起点偏移小于终点偏移,返回0 */
                        retVal = 0U;
                    }
                }
            }
        }
        else
        {
            /*Do nothing currently !*/
        }
    }
    /*返回查询结果*/
    return retVal;
#endif

    UINT8_S retVal = 0U;           /*函数返回值*/
    UINT8_S rtn1 = DEFAULT_ZERO;   /* 起点和确认点逻辑关系返回值 */
    UINT8_S rtn2 = DEFAULT_ZERO;   /* 确认点和终点逻辑关系返回值 */

    rtn1 = CheckLocRelationBetweenTwoPoints(startSeg,startOffset,checkSeg,checkOffset,dir);

    rtn2 = CheckLocRelationBetweenTwoPoints(checkSeg,checkOffset,endSeg,endOffset,dir);

    if ((3u == rtn1) || (3u == rtn2))
    {
        /* 有1个端点重合 */
        retVal = 1u;
    } 
    else if((2u == rtn1) && (2u == rtn2))
    {
        /* 在起点和终点之间 */
        retVal = 1u;
    }
    else
    {
        retVal = 0u;
    }

    return retVal;
}

/*******************************************
* 函数名	： GetLineAcLength
* 功能描述： 查询计轴区段长度
* 参数说明： const UINT16_S acId,
*          UINT32_S *acLength
* 返回值  ： 
*    0,查询失败
*    1,查询成功
*/
UINT8_S GetLineAcLength(const UINT16_S acId,UINT32_S *acLength)
{
    UINT8_S retVal = 0U;/*函数返回值*/
    UINT16_S pSegId[AXLESECTION_SEG_MAX_NUM] = {0U}; /*SEGID指针*/
    UINT16_S segNum = 0U;/*SEG数量*/
    UINT16_S i = 0U;/*循环使用*/
    UINT32_S tempAxleLen = 0U;/*计轴区段长度*/

    /*获取SEG数量*/
    segNum = GetAxleSectionDataStruSegInfo(acId,pSegId);

    for(i = 0U;i < segNum;i++)
    {
        tempAxleLen += GetSegDataStrulength(pSegId[i]);
    }

    if ((tempAxleLen != 0U) && (NULL != acLength))
    {
        *acLength = tempAxleLen;
        retVal = 1U;
    }
    return retVal;
}

/*******************************************
* 函数名	： CheckPointBelongDrButtonId
* 功能描述： 查询某个点所属的无人折返按钮ID
* 参数说明： const UINT16_S seg,
*          const UINT32_S offset,
*          UINT16_S *drButtonId
* 返回值  ： 
*    0,查询失败
*    1,查询成功
*/
UINT8_S CheckPointBelongDrButtonId(const UINT16_S seg,const UINT32_S offset,UINT16_S *drButtonId)
{
    UINT8_S retVal = 0U;/*函数返回值*/
    UINT8_S breakFlag = 0U;
    BnfArStruct *bnfArStru = NULL;
    BnfStopPointStruct *bnfStopPointStru = NULL;
    UINT16_S lineNum = DEFAULT_ZERO;
    UINT16_S cycle = DEFAULT_ZERO;
    UINT16_S arInStopPointId = DEFAULT_ZERO;

    /*获取无人折返信息*/
    bnfArStru = GetArDataInfo(&lineNum);

    if ((NULL != bnfArStru) && (NULL != drButtonId))
    {
        for (cycle = DEFAULT_ZERO;cycle < lineNum;cycle++)
        {
            /*获取无人折返对应的进入停车点信息*/
            arInStopPointId = bnfArStru[cycle].arInStopPointId;

            /*获取停车点所处Seg*/
            bnfStopPointStru = GetIndexIdStopPointDataStru(arInStopPointId);

            if (NULL != bnfStopPointStru)
            {
                /*获取停车点所处SEG*/
                if (bnfStopPointStru->segId == seg)
                {
                    if ((offset >= (bnfStopPointStru->segOfst - bnfStopPointStru->aTPParkArea))
                        && (offset <= (bnfStopPointStru->segOfst + bnfStopPointStru->aTPParkArea)))
                    {
                        /*输入seg在无人折返进入区，输出ID*/
                        (*drButtonId) = bnfArStru[cycle].aRButtonId;
                        breakFlag = 1U;
                        break;                      
                    } 
                    else
                    {
                        /*Do nothing currently !*/
                    }
                } 
                else
                {
                    /*Do nothing currently !*/
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
        /*Do nothing currently !*/
    }

    if (1U == breakFlag)
    {
        retVal = 1U;
    } 
    else
    {
        retVal = 0U;
    }

    return retVal;
}

/*******************************************
* 函数名	：  CheckSignalPostion
* 功能描述： 查询信号机位置ID
* 参数说明： const UINT16_S signalId,
*          UINT16_S *seg,
*          UINT32_S *offset
* 返回值  ： 
*    0,查询失败
*    1,查询成功
*/
UINT8_S CheckSignalPostion(const UINT16_S signalId,UINT16_S *seg,UINT32_S *offset)
{
    UINT16_S segId = DEFAULT_ZERO;
    UINT32_S tempOffset = DEFAULT_ZERO;
    UINT8_S rtnValue = DEFAULT_ZERO;

    segId = GetSignDataStrusignProSegId(signalId);
    tempOffset = GetSignDataStrusignProSegOffset(signalId);

    if ((DEFAULT_ZERO != segId) && (NULL != seg) &&(NULL != offset))
    {
        (*seg) = segId;
        (*offset) = tempOffset;
        rtnValue = 1U;
    } 
    else
    {
        rtnValue = 0U;
    }

    return rtnValue;
}

/*******************************************
* 函数名	：  CheckFirstAcOfSignal
* 功能描述： 查询信号机内方第一个计轴区段
* 参数说明： const UINT16_S signalId,
*          UINT16_S * acId
* 返回值  ： 
*    0,查询失败
*    1,查询成功
*/
UINT8_S CheckFirstAcOfSignal(const UINT16_S signalId,UINT16_S * acId)
{
    UINT8_S retVal = 0U;/*函数返回值*/
    UINT16_S signalSegId = DEFAULT_ZERO;
    UINT16_S tmpSegIdBuff[3] = {0U};
    UINT8_S tmpSegIdNum = 0U;/*SEGID个数*/
    UINT8_S findNum = 0U;/*查找到SEG的个数，大于等于2都为2*/
    BnfSignStruct* signStru = NULL;/*信号机结构体*/

    /*获取信号机信息*/
    signStru = GetIndexIdSignDataStru(signalId);

    /*获取信号机的防护方向*/
    if ((signStru != NULL)  && (NULL != acId))
    {
        if (LINESEG_SAME_DIR == signStru->protectiveDir)
        {
            /*根据信号机的位置判断*/
            if (DEFAULT_ZERO == signStru->signProtectSegOffset)
            {
                /*说明防护点seg即为内方方计轴所属Seg*/
                signalSegId = signStru->signProtectSegId;
                retVal = 1U;
            } 
            else
            {
                /*根据线路情况获取此SEG的终点SEGID*/
                retVal = GetNextSegId(signStru->signProtectSegId,LINESEG_SAME_DIR,&signalSegId);
            }
        } 
        else if (LINESEG_CONVER_DIR == signStru->protectiveDir)
        {
            /*根据信号机的位置判断*/
            if (DEFAULT_ZERO == signStru->signProtectSegOffset)
            {
                /*根据线路情况获取此SEG的起点相邻SEGID*/
                retVal = GetNextSegId(signStru->signProtectSegId,LINESEG_CONVER_DIR,&signalSegId);
            } 
            else
            {
                /*说明防护点seg即为内方方计轴所属Seg*/
                signalSegId = signStru->signProtectSegId;
                retVal = 1U;
            }
        }
        else
        {
            /*Do nothing currently !*/			
        }

        if (1U == retVal)
        {
            /*获取此SEG两端若有包含道岔时,增加有道岔方向对应的SEGID*/
            tmpSegIdNum = GetSegBuffAccordSedIdAndSwitch(signalSegId,tmpSegIdBuff,&findNum);
            *acId = GetSegIdBelongofAxleSecId(tmpSegIdBuff,tmpSegIdNum,findNum);
        }
    }

    return retVal;
}

/*******************************************
* 函数名	：  CheckOutsideAcOfSignal
* 功能描述： 查询信号机外方第一个计轴区段
* 参数说明： const UINT16 signalId, 信号机ID
*            UINT16_S * acId,信号机外方第一个计轴区段ID
* 返回值  ： 
*    0,查询失败
*    1,查询成功
*/
UINT8_S CheckOutsideAcOfSignal(const UINT16_S signalId,UINT16_S * acId)
{
    UINT8_S retVal = 0U;/*函数返回值*/
    UINT16_S signalSegId = DEFAULT_ZERO;
    UINT16_S tmpSegIdBuff[3] = {0U};
    UINT8_S tmpSegIdNum = 0U;/*SEGID个数*/
    UINT8_S findNum = 0U;/*查找到SEG的个数，大于等于2都为2*/
    BnfSignStruct* signStru = NULL;/*信号机结构体*/

    /*获取信号机信息*/
    signStru = GetIndexIdSignDataStru(signalId);

    /*获取信号机的防护方向*/
    if ((signStru != NULL) && (NULL != acId))
    {
        if (LINESEG_SAME_DIR == signStru->protectiveDir)
        {
            /*根据信号机的位置判断*/
            if (DEFAULT_ZERO == signStru->signProtectSegOffset)
            {
                /*根据线路情况获取此SEG的起点相邻SEGID*/
                retVal = GetNextSegId(signStru->signProtectSegId,LINESEG_CONVER_DIR,&signalSegId);
            } 
            else
            {
                /*说明防护点seg即为内方方计轴所属Seg*/
                signalSegId = signStru->signProtectSegId;
                retVal = 1U;
            }
        } 
        else if (LINESEG_CONVER_DIR == signStru->protectiveDir)
        {
            /*根据信号机的位置判断*/
            if (DEFAULT_ZERO == signStru->signProtectSegOffset)
            {
                /*说明防护点seg即为外方方计轴所属Seg*/
                signalSegId = signStru->signProtectSegId;
                retVal = 1U;
            } 
            else
            {
                /*根据线路情况获取此SEG的终点相邻SEGID*/
                retVal = GetNextSegId(signStru->signProtectSegId,LINESEG_SAME_DIR,&signalSegId);
            }
        }
        else
        {
            /*Do nothing currently !*/			
        }

        if (1U == retVal)
        {
            tmpSegIdNum = GetSegBuffAccordSedIdAndSwitch(signalSegId,tmpSegIdBuff,&findNum);
            *acId = GetSegIdBelongofAxleSecId(tmpSegIdBuff,tmpSegIdNum,findNum);
        }
    }

    return retVal;
}

/*******************************************
* 函数名	： CheckAcLength
* 功能描述： 查询计轴区段长度
* 参数说明： const UINT16_S acId 计轴区段编号
*          UINT32_S *length 计轴区段长度
* 返回值  ： 
*    0,查询失败
*    1,查询成功
*/
UINT8_S CheckAcLength(const UINT16_S acId,UINT32_S *length)
{
    BnfAxleSectionStruct* bnfAxleSectionStru = NULL;
    UINT8_S rtnValue = DEFAULT_ZERO;
    UINT16_S cycle = DEFAULT_ZERO;
    UINT32_S segLength = DEFAULT_ZERO;
    UINT32_S tempLength = DEFAULT_ZERO;
    UINT8_S breakFlag = DEFAULT_ZERO;

    /*获取计轴区段信息*/
    bnfAxleSectionStru = GetIndexIdAxleSectionDataStru(acId);

    if (NULL != bnfAxleSectionStru)
    {
        /*由计轴区段包含的seg计算总长度*/
        for (cycle = DEFAULT_ZERO;cycle < bnfAxleSectionStru->includeSegNum;cycle++)
        {
            /*获取seg长度*/
            segLength = GetSegDataStrulength(bnfAxleSectionStru->segIdBuff[cycle]);

            if (DEFAULT_ZERO != segLength)
            {
                /*累加长度*/
                tempLength = tempLength + segLength;
            } 
            else
            {
                /*获取失败*/
                rtnValue = 0U;
                tempLength = 0U;
                breakFlag = 1U;
                break;
            }
        }

        if (1U != breakFlag)
        {
            rtnValue = 1U;
        } 
        else
        {
            /*Do nothing currently !*/
        }
    } 
    else
    {
        rtnValue = 0U;
        tempLength = 0U;
    }

    if (NULL !=length )
    {
        /*输出长度*/
        (*length) = tempLength;
    }

    return rtnValue;
}

/*******************************************
* 函数名	： GetLineRouteAreaType
* 功能描述： 查询进路区域属性
* 参数说明： 
* 返回值  ： 
*    0,查询失败
*   >0,区域属性
*/
UINT8_S GetLineRouteAreaType(const UINT16_S routeId)
{
    UINT8_S retVal = 0U;/*函数返回值*/
    UINT16_S ciId = 0U;/*CIID*/

    /*获取进路所属的CIID*/
    ciId = GetRouteDataStrumanageCI(routeId);

    /*根据联锁ID获取区段属性*/
    retVal = GetSecPropertyAccordName(DEV_CI_TYPE,ciId);

    return retVal;
}


/*******************************************
* 函数名	： CheckLogicIdBetweenPoints
* 功能描述： 查询两点之间的逻辑区段序列
* 参数说明： 
*const UINT8_S  selfFlag
*	selfFlag说明：1，包含起点不包含终点逻辑区段；2，包含终点不包含起点逻辑区段；3，包含起点和终点逻辑区段；0，不包含起点和终点逻辑区段
* const UINT16_S headSeg  起点seg
* const UINT32_S headOffset 起点offset
* const UINT16_S tailSeg  终点seg
* const UINT32_S tailOffset 终点offset
* const UINT8_S direction  查询方向
UINT16_S logicSectionId[SIZE_MAX_SECTION_AC] 逻辑区段序列，按照起点到终点的方向存放
* 返回值  ：0XFF 失败
>=0   逻辑区段个数(当selfFlag为0x55时，返回值不可能为0)	  
*/
UINT8_S CheckLogicIdBetweenPoints(const UINT8_S selfFlag,const UINT16_S headSeg,const UINT32_S headOffset,const UINT16_S TailSeg,const UINT32_S TailOffset,const UINT8_S direction,UINT16_S logicSectionId[])
{
    UINT8_S retVal = UINT8_NULL;/*函数返回值*/
    UINT16_S segBuff[BOTHSEG_INCLUDE_MAX_SEG + 2U] = {0U};
    UINT8_S segIdNum = 0U;/*两个SEG之间的SEG个数*/
    UINT8_S index = 0U;/*数组下标*/
    BnfLogicSectionStruct* logicSecStru = NULL;/*逻辑区段结构体*/
    UINT16_S lineLogicSecNum = 0U;/*逻辑区段表行数*/
    UINT16_S i = 0U,j = 0U,jj = 0U;/*循环使用*/
    UINT8_S isFind = 0U;/*1找到 0 未找到*/
    UINT8_S indexLog = 0U;/*数组下标*/
    UINT8_S isErrorLogId = 0U;/*是否为无效的逻辑区段ID*/
    UINT32_S tmpHeadOffset = 0U;/*临时存放起点偏移量*/
    UINT32_S tmpTailOffset = 0U;/*临时存放终点偏移量*/
    UINT16_S tmpStartSeg = headSeg;
    UINT16_S tmpEndSeg = TailSeg;
    UINT8_S isFindNum = 0U;/*查找到的个数*/
    UINT32_S tmpStartSegLength = 0U;/*起点SEG长度*/
    BnfSegStruct* startSegInfoStru = NULL;/*起点SEG信息结构体*/
    BnfSegStruct* endSegInfoStru = NULL;/*终点SEG信息结构体*/
    UINT8_S tmpSwitchStatus = 0U;/*临时道岔的状态*/
    UINT16_S tmpNextSegId = 0U;/*临时存放下一个SEGID*/
    UINT8_S tmpSelfFlag = 0U;/*初始化值*/

    logicSecStru = GetLogicSectionDataInfo(&lineLogicSecNum);

    startSegInfoStru = GetIndexIdSegDataStru(headSeg);
    endSegInfoStru = GetIndexIdSegDataStru(TailSeg);
    if ((startSegInfoStru != NULL)&&(endSegInfoStru != NULL)&&(logicSectionId != NULL)&&(logicSecStru != NULL)&&(lineLogicSecNum >0U)
        &&(headOffset<= (startSegInfoStru->length))&&(TailOffset<= (endSegInfoStru->length))
        &&((direction == LINESEG_SAME_DIR)||(direction == LINESEG_CONVER_DIR)))
    {
        segBuff[index] = headSeg;
        index = index + 1U;

        if (direction == LINESEG_SAME_DIR)
        {
            if (startSegInfoStru->startPointType == POINTTYPE_SWITCH)
            {
                tmpSwitchStatus = GetSwitchStatus(startSegInfoStru->startPointId);
                retVal = GetNextSegId(headSeg,LINESEG_CONVER_DIR,&tmpNextSegId);
            }
        }
        else
        {
            if (startSegInfoStru->endPointType == POINTTYPE_SWITCH)
            {
                tmpSwitchStatus = GetSwitchStatus(startSegInfoStru->endPointId);
                retVal = GetNextSegId(headSeg,LINESEG_SAME_DIR,&tmpNextSegId);
            }
        }

        if(headSeg == TailSeg)
        {
            if (1U == retVal)
            {
                segBuff[index] = tmpNextSegId;
                index = index + 1U;
            }
        }
        else
        {
            /*查找起点和终点之间包含的SEGID,不包含起点和终点所在的SEGID*/
            retVal = GetDirSegArray(headSeg,TailSeg,direction,0U,&segIdNum,&segBuff[index]);
            index += segIdNum;

            segBuff[index] = TailSeg;	
            index = index + 1U;
            if (1U == retVal)
            {
                for (i = 0U;i < index;i++)
                {
                    if (tmpNextSegId == segBuff[i])
                    {
                        break;
                    }
                }

                if (i == index)
                {
                    segBuff[index] = tmpNextSegId;
                    index = index + 1U;
                }
            }

            if (direction == LINESEG_SAME_DIR)
            {
                if (endSegInfoStru->endPointType == POINTTYPE_SWITCH)
                {
                    tmpSwitchStatus = GetSwitchStatus(endSegInfoStru->endPointId);
                    retVal = GetNextSegId(TailSeg,direction,&tmpNextSegId);
                }
            }
            else
            {
                if (endSegInfoStru->startPointType == POINTTYPE_SWITCH)
                {
                    tmpSwitchStatus = GetSwitchStatus(endSegInfoStru->startPointId);
                    retVal = GetNextSegId(TailSeg,direction,&tmpNextSegId);
                }
            }

            if (1U == retVal)
            {
                for (i = 0U;i < index;i++)
                {
                    if (tmpNextSegId == segBuff[i])
                    {
                        break;
                    }
                }

                if (i == index)
                {
                    segBuff[index] = tmpNextSegId;
                    index = index + 1U;
                }
            }
        }


        if (direction == LINESEG_SAME_DIR)
        {
            tmpHeadOffset = headOffset;
            tmpTailOffset = TailOffset;
            tmpStartSeg = headSeg;
            tmpEndSeg = TailSeg;
            tmpStartSegLength = startSegInfoStru->length;
            tmpSelfFlag = selfFlag;
        }
        else
        {
            tmpHeadOffset = TailOffset;
            tmpTailOffset = headOffset;
            tmpStartSeg = TailSeg;
            tmpEndSeg = headSeg;
            tmpStartSegLength = endSegInfoStru->length;
            if (1U == selfFlag)
            {
                tmpSelfFlag = 2U;
            }
            else if (2U == selfFlag)
            {
                tmpSelfFlag = 1U;
            }
            else
            {
                tmpSelfFlag = selfFlag;
            }
        }

        for (i = 0U; i < lineLogicSecNum; i++)
        {
            isFind = 0U;
            isFindNum = 0U;
            isErrorLogId = 0U;
            for (j = 0U;j < logicSecStru[i].includeSegIdNum; j++)
            {
                if ((logicSecStru[i].segIdBuff[j] == headSeg)&&(headSeg == TailSeg)&&((logicSecStru[i].startSegId == logicSecStru[i].endSegId)))
                {
                    if ((logicSecStru[i].startSegOffset <= tmpHeadOffset)&&(logicSecStru[i].endSegOffset >= tmpTailOffset))
                    {
                        if (3U == tmpSelfFlag)
                        {
                            /*Do nothing currently !*/
                        }
                        else
                        {
                            /*此逻辑区段不写入*/
                            isErrorLogId = 1U;
                            break;
                        }
                    }
                    else if(((logicSecStru[i].startSegOffset <= tmpHeadOffset)&&(logicSecStru[i].endSegOffset >= tmpHeadOffset)&&((tmpSelfFlag == 1U)||(tmpSelfFlag == 3U)))
                        ||((logicSecStru[i].startSegOffset > tmpHeadOffset)&&(logicSecStru[i].endSegOffset < tmpTailOffset))
                        ||((logicSecStru[i].startSegOffset <= tmpTailOffset)&&(logicSecStru[i].endSegOffset >= tmpTailOffset)&&((tmpSelfFlag == 2U)||(tmpSelfFlag == 3U))))
                    {
                        /*Do nothing currently !*/
                    }
                    else
                    {
                        /*此逻辑区段不写入*/
                        isErrorLogId = 1U;
                        break;
                    }

                }
                if ((logicSecStru[i].startSegId == logicSecStru[i].endSegId)&&(logicSecStru[i].startSegId == tmpStartSeg))
                {
                    if (((logicSecStru[i].startSegOffset <= tmpHeadOffset)&&(logicSecStru[i].endSegOffset >= tmpHeadOffset)&&((1U == tmpSelfFlag)||(3U == tmpSelfFlag)))
                        ||(logicSecStru[i].startSegOffset > tmpHeadOffset))
                    {
                        /*Do nothing currently !*/
                    }
                    else
                    {
                        /*此逻辑区段不写入*/
                        isErrorLogId = 1U;
                        break;
                    }
                }
                else if ((logicSecStru[i].startSegId == logicSecStru[i].endSegId)&&(logicSecStru[i].startSegId == tmpEndSeg))
                {
                    if (((logicSecStru[i].startSegOffset <= tmpTailOffset)&&(logicSecStru[i].endSegOffset >= tmpTailOffset)&&((2U == tmpSelfFlag)||(3U == tmpSelfFlag)))
                        ||(logicSecStru[i].endSegOffset < tmpTailOffset))
                    {
                        /*Do nothing currently !*/
                    }
                    else
                    {
                        /*此逻辑区段不写入*/
                        isErrorLogId = 1U;
                        break;
                    }
                }
                else
                {
                    if (logicSecStru[i].segIdBuff[j] == tmpStartSeg)
                    {
                        if (tmpStartSeg == logicSecStru[i].startSegId)
                        {
                            if(logicSecStru[i].startSegOffset > tmpHeadOffset)
                            {
                                /*此逻辑区段不写入*/
                                isErrorLogId = 1U;
                                break;
                            }
                            else 
                            {
                                /*Do nothing currently !*/								
                            }
                        }
                        else
                        {
                            /*Do nothing currently !*/
                        }

                        if(tmpStartSeg == logicSecStru[i].endSegId)
                        {
                            if(logicSecStru[i].endSegOffset >= tmpHeadOffset)
                            {
                                /*Do nothing currently !*/								
                            }
                            else
                            {
                                /*此逻辑区段不写入*/
                                isErrorLogId = 1U;
                                break;
                            }
                        }
                        else
                        {
                            /*此逻辑区段直接写入*/
                        }

                        if((tmpSelfFlag != 3U)&&(tmpSelfFlag != 1U))
                        {
                            /*此逻辑区段不写入*/
                            isErrorLogId = 1U;
                            break;
                        }
                    }

                    if(logicSecStru[i].segIdBuff[j] == tmpEndSeg)
                    {
                        if (tmpEndSeg == logicSecStru[i].startSegId)
                        {
                            if(logicSecStru[i].startSegOffset > tmpTailOffset)
                            {
                                /*此逻辑区段不写入*/
                                isErrorLogId = 1U;
                                break;
                            }
                            else
                            {
                                /*Do nothing currently !*/								
                            }
                        }
                        else if(tmpEndSeg == logicSecStru[i].endSegId)
                        {
                            if(logicSecStru[i].endSegOffset < tmpTailOffset)
                            {
                                /*此逻辑区段不写入*/
                                isErrorLogId = 1U;
                                break;
                            }
                            else
                            {
                                /*Do nothing currently !*/								
                            }
                        }
                        else
                        {
                            /*此逻辑区段直接写入*/
                        }

                        if((tmpSelfFlag != 3U)&&(tmpSelfFlag != 2U))
                        {
                            /*此逻辑区段不写入*/
                            isErrorLogId = 1U;
                            break;
                        }
                    }
                }

            }

            for (j = 0U;(j < logicSecStru[i].includeSegIdNum)&&(0U == isErrorLogId); j++)
            {
                for (jj = 0U; jj < index; jj++)
                {
                    if (logicSecStru[i].includeSegIdNum > 1U)
                    {
                        /*必须查找到此逻辑段的起点SEG和终点SEG*/
                        if (segBuff[jj] == logicSecStru[i].segIdBuff[j])
                        {
                            isFindNum += 1U;

                            if (1U == index)
                            {
                                isFind = 1U;
                            }
                            else
                            {
                                if (isFindNum >= 2U)
                                {
                                    isFind = 1U;
                                }
                            }
                        }
                    }
                    else
                    {
                        if (logicSecStru[i].segIdBuff[j] == segBuff[jj])
                        {
                            isFind = 1U;
                        }
                    }

                    if (1U == isFind)
                    {
                        logicSectionId[indexLog] = logicSecStru[i].indexId;
                        indexLog = indexLog + 1U;
                        break;
                    }
                }
                if (1U == isFind)
                {
                    break;
                }
            }
        }

        retVal = indexLog;


        if (direction == LINESEG_CONVER_DIR)
        {
            /* 将查询结果反向 */
            for (i=DEFAULT_ZERO;i < (indexLog / 2u);i++)
            {
                /* 方法1需引入变量 tmpLogicId*/
                /*
                tmpLogicId = logicSectionId[indexLog-i-1u];
                logicSectionId[indexLog-i-1u] = logicSectionId[i];
                logicSectionId[i] = tmpLogicId;
                */

                /*方法2存在超过最大值情况*/
                /*
                logicSectionId[i] = logicSectionId[i] + logicSectionId[indexLog - i - 1u];
                logicSectionId[indexLog - i - 1u] = logicSectionId[i] - logicSectionId[indexLog - i -1u];
                logicSectionId[i] = logicSectionId[i] - logicSectionId[indexLog - i -1u];
                */

                logicSectionId[i] = logicSectionId[i] ^ logicSectionId[indexLog - i - 1u];
                logicSectionId[indexLog - i - 1u] = logicSectionId[i] ^ logicSectionId[indexLog - i -1u];
                logicSectionId[i] = logicSectionId[i] ^ logicSectionId[indexLog - i -1u];
            }
        }
    }
    return retVal;
}

/*******************************************
* 函数名	： CheckPointBelongReverseArea
* 功能描述： 查询某个点是否属于折返轨
* 参数说明： const UINT16 segId,Seg编号
* 返回值  ： 
*    0,不属于折返轨
*    1,属于折返轨
*/
UINT8_S CheckPointBelongReverseArea(const UINT16_S segId)
{
    UINT16_S stopSecType = 0U;
    UINT8_S rtnValue = 0U;

    stopSecType = GetCurSegOfStopSecType(segId);

    if ((UINT16_S)(RUN_REVERT_AREA) == (UINT16_S)(stopSecType & ((UINT16_S)RUN_REVERT_AREA)))
    {
        /*属于折返轨*/
        rtnValue = 1U;
    } 
    else
    {
        /*不属于折返轨*/
        rtnValue = 0U;
    }

    return rtnValue;
}

/*******************************************
* 函数名	： CheckAcOrderAccordLineSwitchId
* 功能描述： 查询切换点ID获取此切换区域包含的计轴区段个数和ID
* 参数说明：const UINT16 lineSwitchId
*           UINT8_S *acNum,计轴的数量
*           UINT16_S acIdBuff[],计轴的ID 
* 返回值  ： 
*    00,查询失败
*    1,查询成功
*    2,部分成功
*/

UINT8_S CheckAcOrderAccordLineSwitchId(const UINT16_S lineSwitchId,UINT8_S *acNum,UINT16_S acIdBuff[])
{
    UINT8_S retVal = 0U;/*函数返回值*/
    BnfLineSwitchInfoStruct* lineSwitchStru = NULL;/*切换点信息结构体*/

    lineSwitchStru = GetIndexIdLineSwitchInfoDataStru(lineSwitchId);

    if ((NULL != lineSwitchStru) && (NULL != acNum) && (NULL != acIdBuff))
    {
        *acNum = lineSwitchStru->acNum;

        if ((lineSwitchStru->acNum) > 0U)
        {
            if (0U == MemoryCpy(acIdBuff,((UINT32_S)(sizeof(UINT16_S)*(lineSwitchStru->acNum))),
                lineSwitchStru->acIdBuff,((UINT32_S)(sizeof(UINT16_S)*(lineSwitchStru->acNum)))))
            {
                retVal = 1U;
            }           
        }
        else
        {
            retVal = 2U;
        }
    }

    return retVal;
}


/*******************************************
* 函数名	： CalculatePointOfInsideLink
* 功能描述： 计算某个点的内方link(主要处理由于点的两种表示方法(a+max=b+0),获取沿方向的内方link)
* 参数说明： const UINT8 dir,方向
*            const UINT16_S segId,待查segId
*            const UINT32_S offset,待查偏移量
*            UINT16_S *outSegId,输出seg
* 返回值  ： 0:获取失败
*            1:获取成功
*/
UINT8_S CalculatePointOfInsideLink(const UINT8_S dir,const UINT16_S segId,const UINT32_S offset,UINT16_S *outSegId)
{
    UINT8_S rtnValue = 0U;
    UINT32_S tmpSegLen = 0U;
    UINT8_S flag = 1U;
    UINT8_S tmpRetVal = 0U;
    UINT16_S nextSegId = 0U;
    UINT16_S frontAcId = 0U;

    /*判断位置偏移量数据输入的有效性*/
    tmpSegLen =  GetSegDataStrulength(segId);
    if (offset > tmpSegLen) 
    {
        /*入口参数失常，查询失败，返回默认值*/
        flag = 0x00U;
    }

    /*判断入口数据运行方向的正确性*/
    if ((LINESEG_SAME_DIR != dir) && (LINESEG_CONVER_DIR != dir))
    {
        /*入口参数失常，查询失败，返回默认值*/
        flag = 0x00U;
    }

    if ((1U == flag) && (NULL != outSegId))
    {
        if (LINESEG_SAME_DIR == dir)
        {
            if (tmpSegLen == offset)
            {
                (*outSegId) = segId;
                rtnValue = 1U;
            } 
            else if (0U == offset)
            {
                tmpRetVal = GetNextSegId(segId, LINESEG_CONVER_DIR,&nextSegId);

                if (1U == tmpRetVal)
                {
                    (*outSegId) = nextSegId;
                    rtnValue = 1U;
                } 
                else
                {
                    (*outSegId) = 0U;
                    rtnValue = 0U;
                }
            } 
            else
            {
                (*outSegId) = segId;
                rtnValue = 1U;
            }
        } 
        else 
        {
            if (0U == offset)
            {
                (*outSegId) = segId;
                rtnValue = 1U;
            } 
            else if (tmpSegLen == offset)
            {
                tmpRetVal = GetNextSegId(segId, LINESEG_SAME_DIR,&nextSegId);

                if (1U == tmpRetVal)
                {
                    (*outSegId) = nextSegId;
                    rtnValue = 1U;
                } 
                else
                {
                    (*outSegId) = 0U;
                    rtnValue = 0U;
                }
            } 
            else
            {
                (*outSegId) = segId;
                rtnValue = 1U;
            }
        }  
    }

    return rtnValue;
}


/*******************************************
* 函数名	： CheckFrontLink
* 功能描述： 计算当前Seg前方Seg
* 参数说明： const UINT8 dir,方向
*            const UINT16_S segId,当前segId
*            UINT16_S *outSegId,输出seg
* 返回值  ： 0:获取失败
*            1:获取成功
*/
UINT8_S CheckFrontLink(const UINT8_S dir,const UINT16_S segId,UINT16_S *outSegId)
{
    UINT8_S errorFlag = 0U;
    UINT8_S retVal = 0U;
    UINT16_S nextSeg = 0U;

    /*判断数据输入方向的正确性*/
    if ((LINESEG_SAME_DIR == dir) || (LINESEG_CONVER_DIR == dir)) 
    {
        /*入口数据正常*/
        errorFlag = 1U;
    }

    if ((1U == errorFlag) && (NULL != outSegId))
    {
        retVal = GetNextSegId(segId,dir,&nextSeg);

        if (1U == retVal)
        {
            (*outSegId) = nextSeg;
        } 
        else
        {
            (*outSegId) = 0U;
        }
    }

    return retVal;
}

/*******************************************
* 函数名	： CheckPointQuitCbtcIsFindPoint
* 功能描述： 查询某个点是否属于退出CBTC区域内
* 参数说明： 
* 返回值  ： 
*    1,属于
*    2,不属于
*	 0,查询失败
*/
UINT8_S CheckPointQuitCbtcIsFindPoint(const UINT16_S seg,const UINT32_S offset,const UINT8_S dir)
{

#if 0
    UINT8_S retVal = 0u;/*函数返回值*/
    UINT8_S checkRtn = 0u;
    UINT16_S i = 0u;/*循环使用*/
    UINT16_S j =0u;/*循环使用*/
    BnfExitCbtcSectionStruct* exitCbtcSectionDataStru = NULL;
    UINT16_S exitCbtcNum = 0u;
    UINT16_S tmpheadSegId = 0u;
    UINT32_S tmpheadSegOffset = 0u;
    UINT16_S tmptailSegId = 0u;
    UINT32_S tmptailSegOffset = 0u;
    UINT8_S isFindSameDir = 0u;/*1 发现 0 未发现*/


    /*获取退出CBTC区域信息*/
    exitCbtcSectionDataStru = GetExitCbtcSectionDataInfo(&exitCbtcNum);

    if (NULL != exitCbtcSectionDataStru)
    {
        /*先设置为不属于*/
        retVal = 2u;
        isFindSameDir = 0u;
        for ( i = 0u; i < exitCbtcNum; i++)
        {
            if (dir == exitCbtcSectionDataStru[i].dir)
            {
                if ((dir == LINESEG_SAME_DIR))
                {
                    tmpheadSegId = exitCbtcSectionDataStru[i].startSegId;
                    tmpheadSegOffset = exitCbtcSectionDataStru[i].startOffset;
                    tmptailSegId = exitCbtcSectionDataStru[i].endSegId;
                    tmptailSegOffset = exitCbtcSectionDataStru[i].endOffSet;

                    isFindSameDir = 1u;
                }
                else if (dir == LINESEG_CONVER_DIR)
                {

                    tmpheadSegId = exitCbtcSectionDataStru[i].endSegId;
                    tmpheadSegOffset = exitCbtcSectionDataStru[i].endOffSet;
                    tmptailSegId = exitCbtcSectionDataStru[i].startSegId;
                    tmptailSegOffset = exitCbtcSectionDataStru[i].startOffset;



                    isFindSameDir = 1u;
                }
                else
                {

                }
            }

            if (1u == isFindSameDir)
            {
                if ((seg == exitCbtcSectionDataStru[i].startSegId)&&(exitCbtcSectionDataStru[i].startSegId == exitCbtcSectionDataStru[i].endSegId))
                {/*1、头点，尾点、所找点在同一Link上，只需要比较offset*/
                    if((offset >= exitCbtcSectionDataStru[i].startOffset)&&(offset <= exitCbtcSectionDataStru[i].endOffSet))
                    {
                        retVal = 1u;
                    }
                }
                else if((exitCbtcSectionDataStru[i].startSegId == exitCbtcSectionDataStru[i].endSegId)&&(exitCbtcSectionDataStru[i].endSegId != seg))
                {/*2、头点、尾点在同一Link上，所找点不在，直接查找失败*/
                    retVal = 2u;
                }
                else if(seg == exitCbtcSectionDataStru[i].startSegId == seg)
                {/*3、头点、所找点在同一Link上，头点不在，只需要比较offset*/
                    if(offset >= exitCbtcSectionDataStru[i].startOffset)
                    {
                        retVal = 1u;
                    }
                }
                else if(seg == exitCbtcSectionDataStru[i].endSegId)
                {/*4、尾点、所找点在同一Link上，尾点不在，只需要比较offset*/ 
                    if(offset <= exitCbtcSectionDataStru[i].endOffSet)
                    {
                        retVal = 1u;
                    }
                }
                else
                {
                    for (j = 0u; j < exitCbtcSectionDataStru[i].segNum; j++)
                    {
                        if (seg == exitCbtcSectionDataStru[i].segInfoBuff[j])
                        {
                            retVal = 1u;
                            break;
                        }
                    }
                }

                if (1u == retVal)
                {
                    if ((exitCbtcSectionDataStru[i].attribute &LINE_CBTC_EXIT_SEC) == LINE_CBTC_EXIT_SEC)
                    {

                    }
                    else
                    {
                        retVal = 2u;
                    }
                    break;
                }
            }

        }

    }
    else
    {
        retVal = 0U;
    }

    return retVal;

#endif

    UINT8_S retVal = 0u;         /*函数返回值*/
    UINT16_S i = 0u;/*循环使用*/
    BnfExitCbtcSectionStruct* exitCbtcSectionDataStru = NULL;
    UINT16_S exitCbtcNum = 0u;
    UINT16_S tmpHeadSegId = 0u;
    UINT32_S tmpHeadSegOffset = 0u;
    UINT16_S tmpTailSegId = 0u;
    UINT32_S tmpTailSegOffset = 0u;
    UINT8_S rtnRelation = 0u;

    /*获取退出CBTC区域信息*/
    exitCbtcSectionDataStru = GetExitCbtcSectionDataInfo(&exitCbtcNum);

    if (NULL != exitCbtcSectionDataStru)
    {
        /*先设置为不属于*/
        retVal = 2u;

        for ( i = 0u; i < exitCbtcNum; i++)
        {
            if (dir == exitCbtcSectionDataStru[i].dir)
            {
                tmpHeadSegId = exitCbtcSectionDataStru[i].startSegId;
                tmpHeadSegOffset = exitCbtcSectionDataStru[i].startOffset;
                tmpTailSegId = exitCbtcSectionDataStru[i].endSegId;
                tmpTailSegOffset = exitCbtcSectionDataStru[i].endOffSet;

                rtnRelation = CheckPointBelongToArea(tmpHeadSegId,tmpHeadSegOffset,tmpTailSegId,tmpTailSegOffset,seg,offset,dir);

                if (1u == rtnRelation)
                {
                    if ((exitCbtcSectionDataStru[i].attribute & LINE_CBTC_EXIT_SEC) == LINE_CBTC_EXIT_SEC)
                    {
                        /* 这个点属于这个区域且这个区域属于CBTC退出区域,返回属于 */
                        retVal = 1u;
                    }
                    else
                    {
                        retVal = 2u;
                    }

                    break;
                }
            }           
        }
    }
    else
    {
        retVal = 0u;
    }

    return retVal;
}
