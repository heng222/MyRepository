/*******************************************
* �ļ���	��  DmuZcDataHandle.c
* ��  ��	��  ZC��
* ����ʱ��	��  2015-5-25
* ��������	��	ZC��ѯ����
* ��  ע	��  ��
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
* ������	�� ZcBnfDataInit
* ��������: ��ʼ��ZC�����ļ�
* ����˵����UINT8* bnfFileAddr   �������ļ��ĵ�ַ
* ����ֵ��1:�ɹ���	0:ʧ��
*/
INT8_S ZcBnfDataInit(CHAR_S* bnfFileAddr)
{
    INT8_S retVal = 0; /*��������ֵ*/

    /*��ȡBNF�ļ�*/
    ReadManage();

    if (NULL != bnfFileAddr)
    {
        retVal = ReadData(bnfFileAddr);

        if (0 == retVal)
        {
            /*���������ļ�*/
            /*������·����*/
            LoadLineDataManage();
            /*������������*/
            LoadRunDataManage();
            /*����ϵͳ��������*/
            LoadSystemDataManage();
            /*���طֽ������*/
            LoadDividPointDataManage();
            /*����ZC�������*/
            LoadZcManage();

            /*���ع�������*/
            retVal =  LoadData();

            /*���������еĶ�̬��*/
            if (0 == retVal)
            {
                retVal= (INT8_S)CalcCommAddInfo();
            }
            else
            {
                retVal = 0;
            }

            /*����ZC����*/
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
* ������	�� GetLineOverlapOfSwitchNum
* ���������� ��ȡ�������ΰ����ĵ�������
* ����˵���� const UINT16 overlapId,��������ID
* ����ֵ  �� 0xffff: ��ȡ����ʧ��
*			>0:��������
*/
UINT16_S GetLineOverlapOfSwitchNum(const UINT16_S overlapId)
{
    UINT16_S retVal = UINT16_NULL;
    UINT16_S axleSecId[PROTECTZONE_AXLESGM_MAX_NUM] = {0U};/*��������*/
    UINT16_S axleNum = 0U;/*�������θ���*/
    UINT16_S segIdBuff[AXLESECTION_SEG_MAX_NUM] = {0U};/*SEGID*/
    UINT16_S segIdNum = 0U;/*SegID����*/
    UINT16_S i = 0U;/*ѭ��ʹ��*/
    UINT16_S j = 0U;/*ѭ��ʹ��*/
    UINT16_S index = 0U;/*����ƫ��*/
    UINT16_S tempSegIdBuff[AXLESECTION_SEG_MAX_NUM*PROTECTZONE_AXLESGM_MAX_NUM] = {0U};
    UINT16_S switchIdNum = 0U;/*�������*/

    /*��ȡ��·�������������ļ�������*/
    axleNum = GetLineOverlapOfAcInfo(overlapId,axleSecId);

    for (i = 0U;i < axleNum; i++)
    {
        /*��ȡ�������α�Ŷ�Ӧ��SEGID*/
        segIdNum = GetAxleSectionOfSegInfo(axleSecId[i],segIdBuff);

        for (j = 0U;j < segIdNum; j++)
        {
            tempSegIdBuff[index] = segIdBuff[j];
            index = index + 1U;
        }
    }

    /*��ѯ���������SEGID��ȡ����ĸ���*/
    switchIdNum = GetSegIdOfSwitchIdNum(tempSegIdBuff,index);

    if (switchIdNum != 0U)
    {
        retVal = switchIdNum;
    }
    return retVal;
}

/*******************************************
* ������	�� GetLineRouteOfObsInfo
* ���������� ��ȡ��·��Ӧ�źŻ�ID
* ����˵���� const UINT16 routeId,��·ID
*            UINT16_S obsInfoBuf[]���ϰ�����Ϣ���飨id,���ͣ�
* ����ֵ  �� 0xffff: ��ȡ����ʧ��
*			>=0:�ϰ�������(����PSD,ESB)
*/
UINT16_S GetLineRouteOfObsInfo(const UINT16_S routeId,UINT16_S obsInfoBuf[])
{
    UINT8_S tmpRetVal = 0U;/*�ֲ���������ֵ*/
    UINT16_S stationIdBuff[ROUTE_INCLUDE_PLATFORM_MAX_NUM] = {0U};/*վ̨ID*/
    UINT8_S stationIdNum = 0U;/*վ̨ID����*/
    UINT16_S index = 0U;/*����ƫ��*/
    BnfRouteStruct* tmpRouteStru = NULL;/*��·�ṹ��*/
    BnfSignStruct* startSignStru = NULL;/*����źŻ��ṹ��*/
    BnfSignStruct* endSignStru = NULL;/*����źŻ��ṹ��*/
    UINT16_S segIdBuff[BOTHSEG_INCLUDE_MAX_SEG]= {0U};/*����SEG֮�������SEGID*/
    UINT8_S segIdNum = 0U;/*����SEG֮�������SEGID����*/
    UINT8_S indexSeg = 0U;/*����ƫ��*/
    UINT16_S obsNum = UINT16_NULL;

    /*��ȡ��·�����Ľ�·�ṹ����Ϣ*/
    tmpRouteStru = GetIndexIdRouteDataStru(routeId);

    if (tmpRouteStru != NULL)
    {
        /*��ȡʼ���źŻ�ID��Ӧ����Ϣ*/
        startSignStru = GetIndexIdSignDataStru(tmpRouteStru->startSignalId);

        /*��ȡ�ն��źŻ�ID��Ӧ��SEGID*/
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

            /*��ȡ�źŻ���Χ�ڵ�SEG��Ϣ*/
            tmpRetVal = GetNoDirNoSwitchStutasSegArray(startSignStru->signProtectSegId,endSignStru->signProtectSegId,0U,&segIdNum,&segIdBuff[indexSeg]);

            /*����վ̨���ȡ��SEGID��Ӧ��վ̨ID*/
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

                /*��ѯ��վ̨��Ӧ��PSD����*/
                if(NULL != obsInfoBuf)
                {
                    obsNum = GetStationIdBelongofPsdInfo(stationIdBuff,stationIdNum,(UINT16_S)(obsNum*2U),obsInfoBuf);
                    /*��ѯ�˽�·��Ӧ�ĵ������*/
                    obsNum += GetSegIdBelongofSwitchInfo(segIdBuff,indexSeg,(UINT16_S)(obsNum*2U),&obsInfoBuf[index]);
                    /*��ѯ��վ̨��Ӧ��ESB����*/
                    obsNum += GetStationIdBelongofEsbInfo(stationIdBuff,stationIdNum,(UINT16_S)(obsNum*2U),&obsInfoBuf[index]);
                }
            }
        }
    }

    return obsNum;
}

/*******************************************
* ������	�� GetLineSignalDefaultStatus
* ���������� ��ȡ��·�źŻ�Ĭ��״̬
* ����˵���� const UINT16 signalId,�źŻ�ID
* ����ֵ  �� 0: ��ȡ����ʧ��
*			0x55/0xaa:Ĭ��״̬
*/
UINT16_S GetLineSignalDefaultStatus(const UINT16_S signalId)
{
    UINT16_S retVal = 0U;/*��������ֵ*/

    retVal = GetZcSignInfoDataStrulightFlag(signalId);

    return retVal;
}


/*******************************************
* ������	�� GetLineCbtcLightOffType
* ���������� ��ȡ��·�źŻ�CBTC�г���������(Ԥ��)
* ����˵���� const UINT16 signalId,�źŻ�ID
* ����ֵ  �� 0: ��ȡ����ʧ��
*			0x55/0xaa:CBTC�г���������
*/
UINT8_S GetLineCbtcLightOffType(const UINT16_S signalId)
{
    UINT8_S retVal = 0U;/*��������ֵ*/

    return retVal;
}

/*******************************************
* ������	�� GetLineCrossType
* ���������� ��ȡ��·�źŻ���ѹ����(Ԥ��)
* ����˵���� const UINT16 signalId,�źŻ�ID
* ����ֵ  �� 0: ��ȡ����ʧ��
*			0x55/0xaa:��ѹ����
*/
UINT8_S GetLineCrossType(const UINT16_S signalId)
{
    UINT8_S retVal = 0U;/*��������ֵ*/



    return retVal;
}

/*******************************************
* ������	�� GetLineCrashType
* ���������� ��ȡ��·�źŻ����ź�����
* ����˵���� const UINT16 signalId,�źŻ�ID
* ����ֵ  �� 0: ��ȡ����ʧ��
*			0x55/0xaa:���ź�����
*/
UINT16_S GetLineCrashType(const UINT16_S signalId)
{
    UINT16_S retVal = 0U;/*��������ֵ*/

    retVal = GetZcSignInfoDataStruthroughSignFlag(signalId);

    return retVal;
}

/*******************************************
* ������	�� GetLineSwitchPosition
* ���������� ��ȡ��·����λ����Ϣ��������/���ߣ�
* ����˵���� const UINT16 switchId,����ID
* ����ֵ  �� 0: ��ȡ����ʧ��
*			0xaa/0x55:������/����
*/
UINT8_S GetLineSwitchPosition(const UINT16_S switchId)
{
    UINT8_S retVal = 0U;/*��������ֵ*/
    UINT16_S ciId = 0U; /*����ID*/

    /*��ȡ����CI��ID*/
    ciId = GetLineSwitchBelongCiId(switchId);

    /*��������ID��ȡ��������*/
    if (ciId > 0U)
    {
        retVal = GetSecPropertyAccordName(DEV_CI_TYPE,ciId);
    }

    return retVal;
}

/*******************************************
* ������	�� GetLineAcType
* ���������� ��ȡ������������
* ����˵���� const UINT16 acId����������ID
* ����ֵ  �� 0: ��ȡʧ��
*			0x55-������������;0xaa-��������������
*/
UINT8_S GetLineAcType(const UINT16_S acId)
{
    UINT8_S retVal = 0U;/*��������ֵ*/
    UINT16_S ciId = 0U; /*����ID*/

    /*��ȡ����CI��ID*/
    ciId = GetLineAcBelongCiId(acId);

    /*��������ID��ȡ��������*/
    if (ciId > 0U)
    {
        retVal = GetSecPropertyAccordName(DEV_CI_TYPE,ciId);
    }

    return retVal;
}

/*******************************************
* ������	�� GetLineAcIncludeSwitchInfo
* ���������� ��ȡ�������ΰ���������Ϣ
* ����˵���� const UINT16 acId����������ID
*            UINT8_S *switchNum,��������
*            UINT16_S switchIdBuf[]������ID����
* ����ֵ  �� 0: ��ȡʧ��
*		    1: ��ȡ�ɹ�
*/
UINT8_S GetLineAcIncludeSwitchInfo(const UINT16_S acId,UINT8_S *switchNum,UINT16_S switchIdBuf[])
{
    UINT8_S retVal = 0U;/*��������ֵ*/
    UINT16_S pSegId[AXLESECTION_SEG_MAX_NUM] = {0U};/*SEGָ��*/
    UINT16_S includeSegNum = 0U;/*������SEG����*/

    /*��ȡ�˼������ζ�Ӧ��SEG��Ϣ*/
    includeSegNum = GetAxleSectionDataStruSegInfo(acId,pSegId);

    /*����SEG��ȡ����ID�Լ�����*/
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
* ������	�� CheckPositionBelongAc
* ���������� ��ѯλ��������������
* ����˵���� const UINT16 segId,SEG��ID
* ����ֵ  �� 0: ��ȡʧ��
*		    >0: �������ε�ID
*/
UINT16_S CheckPositionBelongAc(const UINT16_S segId)
{
    UINT16_S axleSecId = 0U;/*��������*/
    UINT16_S tmpSegBuff[3] = {0U};
    UINT8_S tmpSegNum = 0U;/*SEG����*/
    UINT8_S needFindNum = 0U;/*��Ҫ���ҵ��ĸ���*/

    /*��ѯ��SEGǰ���Ƿ��е������е���,��ǰ���SEGд��*/
    tmpSegNum = GetSegBuffAccordSedIdAndSwitch(segId,tmpSegBuff,&needFindNum);
    if (tmpSegNum > 0U)
    {
        axleSecId = GetSegIdBelongofAxleSecId(tmpSegBuff,tmpSegNum,needFindNum);
    }

    return axleSecId;
}

/*******************************************
* ������	�� CheckAcTopPosition
* ���������� ��ѯ��������ʼ��λ��
* ����˵���� const UINT16 acId,��������ID
*            const UINT16_S dir,�г������seg���������з���
*			 UINT16_S *segId,seg��ID
*			 UINT32_S *offset,�����seg��ƫ����
* ����ֵ  �� 0: ��ȡʧ��
*		    1: ��ȡ�ɹ�
*/
UINT8_S CheckAcTopPosition(const UINT16_S acId,const UINT16_S dir,UINT16_S *segId,UINT32_S *offset)
{
    UINT8_S retVal = 0U;/*��������ֵ*/
    UINT8_S isErrorFlag = 1U;/*1��ȷ  0 ����*/
    BnfAxleSectionStruct *pAxleSgmtStruct = NULL;/*ָ�����������Ϣ�Ľṹ��ָ��*/

    /*�ж������������Ч��*/
    if(UINT16_NULL == GetAxleSectionDataStruIndex(acId))
    {
        /*������Ч�����ش���*/
        isErrorFlag = 0U;
    }

    /*�ж����з������Ч��*/
    if ((0U == isErrorFlag)&&(LINESEG_SAME_DIR != dir) && (LINESEG_CONVER_DIR != dir))
    {
        /*������Ч�����ش���*/
        isErrorFlag = 0U;
    }

    pAxleSgmtStruct = GetIndexIdAxleSectionDataStru(acId);

    if((NULL != pAxleSgmtStruct) && (NULL != segId) && (NULL != offset))
    {
        /*�������: 
        �г������seg���������з�����ͬʱ;�����������Ϊ�����ʼ��	*/
        if ((1U == isErrorFlag)&&(LINESEG_SAME_DIR == dir))
        {
            *segId = pAxleSgmtStruct->orgnSegId;
            *offset = pAxleSgmtStruct->orgnSegOfst;
            retVal = 0x01U;

        }
        else if((1U == isErrorFlag)&&(LINESEG_CONVER_DIR == dir))
        {
            /*�������: 
            �г������seg���������з����෴ʱ;���������Ҷ�Ϊ����ʼ��	*/
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
* ������	�� CheckAcTerminalPosition
* ���������� ��ѯ���������ն�λ��
* ����˵���� const UINT16 acId,��������ID
*            const UINT16_S dir,�г������seg���������з���
*			 UINT16_S *segId,seg��ID
*			 UINT32_S *offset,�����seg��ƫ����
* ����ֵ  �� 0: ��ȡʧ��
*		    1: ��ȡ�ɹ�
*/
UINT8_S CheckAcTerminalPosition(const UINT16_S acId,const UINT16_S dir,UINT16_S *seg,UINT32_S *offset)
{
    UINT8_S retVal = 0U;/*��������ֵ*/
    UINT8_S isErrorFlag = 1U;/*1��ȷ  0 ����*/
    BnfAxleSectionStruct *pAxleSgmtStruct = NULL;/*ָ�����������Ϣ�Ľṹ��ָ��*/

    /*�ж������������Ч��*/
    if(UINT16_NULL == GetAxleSectionDataStruIndex(acId))
    {
        /*������Ч�����ش���*/
        isErrorFlag = 0U;
    }

    /*�ж����з������Ч��*/
    if ((0U == isErrorFlag)&&(LINESEG_SAME_DIR != dir) && (LINESEG_CONVER_DIR != dir))
    {
        /*������Ч�����ش���*/
        isErrorFlag = 0U;
    }

    pAxleSgmtStruct = GetIndexIdAxleSectionDataStru(acId);

    if((NULL != pAxleSgmtStruct) && (NULL != seg) && (NULL != offset))
    {
        /*�������: 
        �г������seg���������з�����ͬʱ;�����������Ϊ�����ʼ��	*/
        if ((1U == isErrorFlag)&&(LINESEG_SAME_DIR == dir))
        {
            *seg = pAxleSgmtStruct->tmnlSegId;
            *offset = pAxleSgmtStruct->tmnlSegOfst;
            retVal = 0x01U;

        }
        else if((1U == isErrorFlag)&&(LINESEG_CONVER_DIR == dir))
        {
            /*�������: 
            �г������seg���������з����෴ʱ;���������Ҷ�Ϊ����ʼ��	*/
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
* ������	�� CheckSwitchBelongAc
* ���������� ��ѯ�����Ӧ�ļ�������
* ����˵���� const UINT16 switchId,����ID
*            UINT8_S *acNum,������������
*            UINT16_S acIdBuf[],��������ID����
* ����ֵ  �� 0: ��ȡʧ��
*		    1: ��ȡ�ɹ�
*/
UINT8_S CheckSwitchBelongAc(const UINT16_S switchId,UINT8_S *acNum,UINT16_S acIdBuf[])
{
    UINT8_S retVal = 0U;/*��������ֵ*/
    UINT8_S axleSecNum = 0U;/*����������Ŀ*/
    UINT16_S i = 0U;/*ѭ���ñ���*/
    UINT16_S j = 0U;/*ѭ���ñ���*/
    UINT16_S axleSecIdBuff[MAX_ACOFSWITCH_NUM] = {0U};/*������������*/	
    BnfAxleSectionStruct *pAxleSecStru =NULL;/*����������Ϣ�ṹ��ָ��*/
    UINT16_S axleSecLineNum = 0U;/*�����������ݳ���*/
    UINT8_S errorRetVal = 1U;/*1 ��������  0 �����˳�*/

    /*�����ʼ��*/
    MemorySet(acIdBuf, ((UINT32_S)(MAX_ACOFSWITCH_NUM*sizeof(UINT16_S))), 
        0U, ((UINT32_S)(MAX_ACOFSWITCH_NUM*sizeof(UINT16_S))));
    MemorySet(axleSecIdBuff,((UINT32_S)(MAX_ACOFSWITCH_NUM*sizeof(UINT16_S))),
        0U, ((UINT32_S)(MAX_ACOFSWITCH_NUM*sizeof(UINT16_S))));

    /*���ù������õ��������ε������Ϣ*/
    pAxleSecStru = GetAxleSectionDataInfo(&axleSecLineNum);

    if((NULL != pAxleSecStru) && (NULL != acNum) && (NULL != acIdBuf))
    {
        /*��������������Ϣ���õ�����ָ������ļ�������*/
        for (i=0U; i<axleSecLineNum; i++)
        {
            for (j=0U; j<pAxleSecStru[i].relatPointNum; j++)
            {
                if (pAxleSecStru[i].relatPointId[j] == switchId)
                {
                    if (axleSecNum == MAX_ACOFSWITCH_NUM)
                    {
                        /*����Խ�磬���ز�ѯʧ��*/
                        retVal = 0U;
                        errorRetVal = 0U;
                        break;
                    }
                    else
                    {
                        /*�������������Ϣ*/
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

        /*������ɣ�������*/
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
* ������	�� CheckFrontACStatus
* ���������� ��ѯǰ����������(�����ڶ�λ��λ)
* ����˵���� const UINT16 acId,��������ID
*            const UINT8_S dir,�г����з���
*            UINT16_S *frontAcId,ǰ����������ID
* ����ֵ  ��0: ��ȡʧ��
*		    1: ��ȡ�ɹ�
*           2: ��·�յ�ʧ��
*           3: ����ԭ��ʧ��
*/
UINT8_S CheckFrontACStatus(const UINT16_S acId,const UINT8_S dir,UINT16_S *frontAcId)
{
    UINT8_S retVal = 0U;/*��������ֵ*/
    UINT16_S adjacentAxleSegID = 0U;/*��ѯ�������ڼ�������*/
    UINT8_S errorFlag = 0U;/*������  1��ȷ   0����*/
    UINT8_S axleSecNum = 0U;/*�������θ���*/

    /*�ж��������뷽�����ȷ��*/
    if ((LINESEG_SAME_DIR == dir) || (LINESEG_CONVER_DIR == dir)) 
    {
        /*�����������*/
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
* ������	�� CheckRearACStatus
* ���������� ��ѯ�󷽼�������(�����ڶ�λ��λ)
* ����˵����  const UINT16 acId,��������ID
*            const UINT8_S dir,�г����з���
*            UINT16_S *rearAcId,�󷽼�������ID
* ����ֵ  �� 0: ��ȡʧ��
*		     1: ��ȡ�ɹ�
*            2: ��·�յ�ʧ��
*            3: ����ԭ��ʧ��
*/
UINT8_S CheckRearACStatus(const UINT16_S acId,const UINT8_S dir,UINT16_S *rearAcId)
{
    UINT8_S retVal = 0U;/*��������ֵ*/
    UINT16_S adjacentAxleSegID = 0U;/*��ѯ�������ڼ�������*/
    UINT8_S errorFlag = 1U;/*������  1��ȷ   0����*/
    UINT8_S axleSecNum = 0U;/*�������θ���*/

    /*�ж��������뷽�����ȷ��*/
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
* ������	�� CheckFrontACCanStatus
* ���������� ��ѯǰ���������ο��ܵ�����(�����п���Ϊ�Ŀ�)
* ����˵���� const UINT16 acId,��������ID
*            const UINT8_S dir,�г����з���
*            UINT16_S *frontAcId,ǰ����������ID
* ����ֵ  �� 0��ʧ��
*			1���ɹ�
*			2����·��ͷ����ʧ��
*			3������ԭ����ʧ��
*/
UINT8_S CheckFrontACCanStatus(const UINT16_S acId,const UINT8_S dir,UINT8_S* frontAcNum, UINT16_S *frontAcIdBuff)
{
    UINT8_S retVal = 0U;/*��������ֵ*/
    UINT8_S errorFlag = 0U;/*������  1��ȷ   0����*/

    /*�ж��������뷽�����ȷ��*/
    if ((LINESEG_SAME_DIR == dir) || (LINESEG_CONVER_DIR == dir)) 
    {
        /*�����������*/
        errorFlag = 1U;
    }

    if ((1U == errorFlag) && (NULL != frontAcNum) && (NULL != frontAcIdBuff))
    {
        retVal = FindAdjacentACID(acId,dir,END_POINT,frontAcNum,frontAcIdBuff);
    }

    return retVal;
}

/*******************************************
* ������	�� CheckRearACCanStatus
* ���������� ��ѯ�󷽼�������(�����п���Ϊ�Ŀ�)
* ����˵����  const UINT16 acId,��������ID
*            const UINT8_S dir,�г����з���
*            UINT16_S *rearAcId,�󷽼�������ID
* ����ֵ  ��0��ʧ��
*			1���ɹ�
*			2����·��ͷ����ʧ��
*			3������ԭ����ʧ��
*/
UINT8_S CheckRearACCanStatus(const UINT16_S acId,const UINT8_S dir,UINT8_S* rearAcNum, UINT16_S *rearAcIdBuff)
{
    UINT8_S retVal = 0U;/*��������ֵ*/
    UINT8_S errorFlag = 1U;/*������  1��ȷ   0����*/

    /*�ж��������뷽�����ȷ��*/
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
* ������	�� CheckDistanceBetweenTwoPoints
* ���������� ��ѯ����֮��ľ�������
* ����˵���� const UINT16 seg1,seg��ID
*            const UINT32_S offset1,seg��ƫ����
*            const UINT16_S seg2,seg��ID
*            const UINT32_S offset2,seg��ƫ����
*            UINT8_S dir,���з���
* ����ֵ  �� UINT32_NULL: ��ȡʧ��
*		    ����: ��ȡ�ɹ�
*/
UINT32_S CheckDistanceBetweenTwoPoints(const UINT16_S seg1,const UINT32_S offset1,const UINT16_S seg2,const UINT32_S offset2,UINT8_S dir)
{
    UINT8_S retVal = 0U;/*��������ֵ*/
    UINT32_S distance = 0U;/*Ŀ�����*/

    retVal = GetDirBothSegPointDisPlus(seg1,offset1,seg2,offset2,dir,&distance);

    if (0U == retVal)
    {
        distance = UINT32_NULL;
    }

    return distance;
}

/*******************************************
* ������	�� CheckPointNearestSignalBaseDir
* ���������� ��ѯ���ڷ����������������ͬ�����źŻ�
* ����˵���� const UINT8 dir,���з���
*            const UINT16_S seg, seg��ID
*            const UINT32_S offset,seg��ƫ����
*            UINT16_S *outSignalId,�źŻ���ID
* ����ֵ  �� 0: ��ȡʧ��
*		     1: ��ȡ�ɹ�
*/
UINT8_S CheckPointNearestSignalBaseDir(const UINT8_S dir,const UINT16_S seg,const UINT32_S offset,UINT16_S *outSignalId)
{
    UINT16_S neighborSignalID[4] = {0U};/*��������ֵ���г�ǰ��ͬ���źŻ�ID,2*/
    UINT16_S currentSegID = 0U;/*��ǰSEG��ID��Ϣ*/
    UINT16_S nextSegID = 0U;/*��ǰSEG������seg��Ϣ*/
    UINT8_S retVal = 0U;/*���ú�������ֵ*/
    BnfSignStruct * signalStru = NULL;/*�źŻ���Ϣ�ṹ��ָ��*/
    UINT16_S signalSegID = 0U;/*�źŻ�����seg���*/
    UINT32_S signalSegOffset = 0U;/*�źŻ�����segƫ����*/
    UINT8_S bFlag = 0U;/*�ҵ��źŻ��ı�־λ��0��δ�ҵ��źŻ���1���ҵ��źŻ�*/
    UINT8_S  signalNum = DEFAULT_ZERO;
    UINT8_S  signalCycle = DEFAULT_ZERO;
    UINT32_S  destDis = DEFAULT_ZERO;
    UINT32_S  dwMaxDisOfTrainAndSignal = UINT32_NULL;
    UINT16_S searchSignalID = 0U; /*���ݺ�������ֵ���з���*/
    UINT8_S flag = 1U;/*1 ��ȷ  0 ����*/

    /*��ʼ���ֲ�����*/
    MemorySet(&neighborSignalID[0],((UINT32_S)(sizeof(UINT16_S) * 4U)),
        DEFAULT_ZERO,((UINT32_S)(sizeof(UINT16_S) * 4U)));

    /*�ж�������ݳ�ͷ����segƫ��������Ч��*/
    if (offset > GetSegDataStrulength(seg))
    {
        flag = 0U;
    }

    /*�ж�������ݷ������Ч��*/
    if ((1U == flag)&&((LINESEG_SAME_DIR == dir) || (LINESEG_CONVER_DIR == dir)))
    {
        flag = 1U;
    }
    else
    {
        flag = 0U;
    }

    /*����ͷSEG��Ϊ��ǰSEG*/
    currentSegID = seg;

    /*���ù��ܺ�������ѯ��ǰSEG��ָ������������źŻ���Ϣ*/
    if (1U == flag)
    {
        retVal = FindCurrentSegSignal(currentSegID, dir, neighborSignalID, &signalNum);
    }

    /*�ڵ�ǰSEG���ҵ�ͬ���źŻ�*/
    if (1U == retVal)
    {
        for (signalCycle = (UINT8_S)DEFAULT_ZERO;signalCycle < signalNum;signalCycle++)
        {
            /*���ù�����ֱ���ҵ��źŻ���Ϣ*/
            signalStru = GetIndexIdSignDataStru(neighborSignalID[signalCycle]);
            if(NULL != signalStru)
            {
                signalSegID = signalStru->signProtectSegId;
                signalSegOffset = signalStru->signProtectSegOffset;

                /*���ú������ж�����ǰ��λ�á����жϳ�ͷλ�����źŻ�λ�õ�ǰ���ϵ*/
                retVal = CheckLocRelationBetweenTwoPoints(seg, offset, signalSegID, signalSegOffset, dir);

                /*�ҵ����źŻ�λ�����г���ȫ��ͷǰ������Ϊ����*/
                if (2U == retVal)
                {
                    /*�źŻ�λ�����г�ǰ��,��ѯ�źŻ�������г��ľ���*/
                    retVal = GetNoDirBothSegPointDis(seg, offset, signalSegID, signalSegOffset,&destDis);

                    if (1U == retVal)
                    {
                        searchSignalID = signalStru->signId;
                        dwMaxDisOfTrainAndSignal = destDis;
                    } 
                    else
                    {
                        /*��������*/
                    }	
                }
            }
        }

        if (searchSignalID != DEFAULT_ZERO)
        {
            /*�����ҵ����źŻ���ţ���ѯ�ɹ�*/
            bFlag = 1U;		
        }
        else
        {
            /*����*/
        }
    }
    else
    {
        /*�ڵ�ǰSEGû���ҵ��źŻ�*/
    }

    /*��ʼ������*/
    dwMaxDisOfTrainAndSignal = (UINT32_S)UINT32_NULL;

    /*�ڵ�ǰseg��û���ҵ��źŻ������ҵ����źŻ�λ�ڳ�ͷ�󷽣���Ҫ�ڳ�ͷ����seg���߼�ǰ��seg�ϲ����źŻ�*/
    while ((1U == flag)&&(0U == bFlag)) 
    {
        /*���ù��ܺ�������ѯ��ǰseg������seg���ҵ���ͷ����seg��ǰ������seg*/
        retVal = GetNextSegId(currentSegID, dir,&nextSegID);

        /*���ú�������ֵ�����жϣ���������ʧ��*/
        if (0U == retVal)
        {
            /*��ѯʧ��*/
            searchSignalID = 0U;
            break;
        }

        /*���ҵ�������seg��Ϊ�µĵ�ǰseg*/
        currentSegID = nextSegID;

        /*���ù��ܺ�������ѯ��ǰseg��ָ������������źŻ���Ϣ*/
        retVal = FindCurrentSegSignal(currentSegID, dir, neighborSignalID, &signalNum);

        /*�ڵ�ǰseg���ҵ�ͬ���źŻ�*/
        if (1U == retVal) 
        {
            for (signalCycle = (UINT8_S)DEFAULT_ZERO;signalCycle < signalNum;signalCycle++)
            {
                /*���ù�����ֱ���ҵ��źŻ���Ϣ*/
                signalStru = GetIndexIdSignDataStru(neighborSignalID[signalCycle]);

                /*��¼�źŻ���λ����Ϣ��2010.9.6���޸��źŻ�λ��Ϊ�߼�λ��*/
                signalSegID = signalStru->signProtectSegId;
                signalSegOffset = signalStru->signProtectSegOffset;

                /*���ú������ж�����ǰ��λ�á����жϳ�ͷλ�����źŻ�λ�õ�ǰ���ϵ*/
                retVal = CheckLocRelationBetweenTwoPoints(seg, offset, signalSegID, signalSegOffset, dir);

                /*�ҵ����źŻ�λ�����г���ȫ��ͷǰ������Ϊ����*/
                if (2U == retVal)
                {
                    /*�źŻ�λ�����г�ǰ��,��ѯ�źŻ�������г��ľ���*/
                    retVal = GetNoDirBothSegPointDis(seg, offset, signalSegID, signalSegOffset,&destDis);

                    if ((1U == retVal)&&(destDis < dwMaxDisOfTrainAndSignal))
                    {
                        searchSignalID = signalStru->signId;
                        dwMaxDisOfTrainAndSignal = destDis;
                    } 
                    else
                    {
                        /*��������*/
                    }	
                }
            }

            if (searchSignalID != DEFAULT_ZERO)
            {
                /*�����ҵ����źŻ���ţ���ѯ�ɹ�*/
                bFlag = 1U;
                break;		
            }
            else
            {
                /*����*/
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
* ������	�� CheckLocRelationBetweenTwoPoints
* ���������� ��ѯ�����Ӹ��������ǰ���ϵ
* ����˵���� const UINT16 seg1,seg��ID
*            const UINT32_S offset1,seg��ƫ����
*            const UINT16_S seg2,seg��ID
*            const UINT32_S offset2,seg��ƫ����
*            UINT8_S dir,���з���
* ����ֵ  �� 
*    0x01:seg1��Զ;
*    0x02:seg2��Զ;
*    0x03:�غ�
*    0x00:�Ƚ�ʧ��
*/
UINT8_S CheckLocRelationBetweenTwoPoints(const UINT16_S seg1,const UINT32_S offset1,const UINT16_S seg2,const UINT32_S offset2,UINT8_S dir)
{
#if 0
    UINT8_S tmpRetVal=0U;/*���õĺ����ķ���ֵ*/
    UINT8_S retVal = 0U;/*��������ֵ*/
    UINT16_S currentSeg1ID = 0U;/*��¼��seg1�ҵ��ĵ�ǰsegID*/
    UINT16_S currentSeg2ID = 0U;/*��¼��seg2�ҵ��ĵ�ǰsegID*/
    UINT16_S adjecttSeg1ID = 0U;/*��¼��seg1�ҵ�������segID*/
    UINT16_S adjecttSeg2ID = 0U;/*��¼��seg2�ҵ�������segID*/
    UINT8_S flagA = 0U;/*λ��A��ʼ����ִ�в�ѯ�ı�־λ*/
    UINT8_S flagB = 0U;/*λ��B��ʼ����ִ�в�ѯ�ı�־λ*/
    UINT16_S tmpSegId=0U; /*��ʱ����*/
    UINT32_S tmpSegLen=0U;/*��ʱ����*/
    UINT8_S flag = 1U;/*1 ��ȷ  0 ����*/
    UINT8_S isFind = 0U;/*�Ƿ��Ѿ���ѯ�� 1 ��ѯ�� 0 δ��ѯ��*/
    UINT32_S tmpSeg1Len = 0U;
    UINT32_S tmpSeg2Len = 0U;

    /*�ж�λ��1ƫ���������������Ч��*/
    tmpSeg1Len =  GetSegDataStrulength(seg1);
    if (offset1 > tmpSeg1Len) 
    {
        /*��ڲ���ʧ������ѯʧ�ܣ�����Ĭ��ֵ*/
        flag = 0U;
    }

    /*�ж�λ��2ƫ���������������Ч��*/
    tmpSeg2Len =  GetSegDataStrulength(seg2);
    if ((0U == flag)||(offset2 > tmpSeg2Len)) 
    {
        /*��ڲ���ʧ������ѯʧ�ܣ�����Ĭ��ֵ*/
        flag = 0U;
    }

    /*�ж�����������з������ȷ��*/
    if ((0U == flag)||((LINESEG_SAME_DIR != dir) && (LINESEG_CONVER_DIR != dir)))
    {
        /*��ڲ���ʧ������ѯʧ�ܣ�����Ĭ��ֵ*/
        flag = 0U;
    }

    if (1U == flag)
    {
        /*���ų���seg�߽���غϵ����*/
        /*��seg1����seg2*/
        tmpSegLen= tmpSeg1Len;
        if(offset1 == tmpSegLen)
        {
            tmpRetVal = GetNextSegId(seg1, LINESEG_SAME_DIR,&tmpSegId);
            if(1U == tmpRetVal)
            {
                /*�ɹ��ҵ�����seg*/
                if ((tmpSegId == seg2) &&(offset2 == 0U))
                {
                    /*�����غ�*/
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
                    /*�����غ�*/
                    retVal = 0x03U;
                    isFind = 1U;
                }
            }
        }
        else
        {
            /* ������ */
        }

        /*����������ͬһ��segʱ*/
        if((0U == isFind)&&(seg1 == seg2))
        {
            /*������seg���߼�������ͬ�ҵ�һ���ƫ�������ڵڶ��㣬
            ���߷�����seg���߼������෴�ҵ�һ���ƫ����С�ڵڶ���ʱ����һ����ǰ���ڶ����ں�*/
            if (((LINESEG_SAME_DIR == dir) && (offset1 > offset2)) 
                || ((LINESEG_CONVER_DIR == dir) && (offset1 < offset2)))
            {
                /*��ѯ�ɹ�������*/
                retVal = 0x01U;
                isFind = 1U;
            }
            else
            {
                if (offset1 == offset2)
                {
                    /*��ѯ�ɹ�������*/
                    retVal = 0x03U;
                    isFind = 1U;
                }
                else
                {
                    /*������seg���߼������෴�ҵ�һ���ƫ�������ڵ��ڵڶ��㣬
                    ���߷�����seg���߼�������ͬ�ҵ�һ���ƫ����С�ڵڶ���ʱ���ڶ�����ǰ����һ���ں󣬷���*/
                    retVal = 0x02U;
                    isFind = 1U;
                }
            }
        }

        /*�������㲻��ͬһ��SEG��*/
        /*����seg1�ҵ��ĵ�ǰSegID��ʼ��Ϊseg1����seg2�ҵ��ĵ�ǰSegID��ʼ��Ϊseg2*/
        currentSeg1ID = seg1;
        currentSeg2ID = seg2;

        /*��seg1��seg2��ͬһ���������һ��seg�������ҵ���segID�ֱ���seg2��seg1���бȽϣ�
        ���ڱȶԷ�����ͬʱ������whileѭ��*/
        while ((0U == isFind)&&(currentSeg1ID != seg2) && (currentSeg2ID != seg1))
        {

            /*�����ѯ��־λ��Ϊ��ֹ��ѯ�����ز�ѯʧ��*/
            if ((1U == flagA) && (1U == flagB))
            {
                retVal = 0x00U;	
                isFind = 1U;
                break;
            }

            /*�жϱ�־λ״̬��������Seg1����*/
            if ((0U == isFind)&&(0U == flagA))
            {
                /*���ù��ܺ��������ҵ�ǰseg������seg��������seg1�����ĵ�ǰseg������seg*/
                tmpRetVal = GetNextSegId(currentSeg1ID, dir,&adjecttSeg1ID);

                /*��ѯʧ�ܣ��������ѯ�ı�־λ��Ϊ��ֹ��ѯ*/
                if (0U == tmpRetVal)
                {
                    flagA = 1U;				
                }

                /*����seg1ִ�в�ѯ�ı�־λΪ���Լ�����ѯ*/
                if (0U == flagA)
                {
                    /*������seg��Ϊ�µĵ�ǰsegID*/
                    currentSeg1ID = adjecttSeg1ID;				
                }

            }

            /*�жϱ�־λ״̬��������Seg2����*/
            if ((0U == isFind)&&(0U == flagB))
            {
                /*���ù��ܺ��������ҵ�ǰsegID������segID��������seg1�����ĵ�ǰsegID������segID*/
                tmpRetVal = GetNextSegId(currentSeg2ID, dir, &adjecttSeg2ID);

                /*��ѯʧ�ܣ��������ѯ�ı�־λ��Ϊ��ֹ��ѯ*/
                if (0U == tmpRetVal)
                {
                    flagB = 1U;				
                }	

                /*����seg1ִ�в�ѯ�ı�־λΪ���Լ�����ѯ*/
                if (0U == flagB)
                {
                    /*������seg��Ϊ�µĵ�ǰseg*/
                    currentSeg2ID = adjecttSeg2ID;				
                }
            }		
        }

        /*����������Ϊͨ��seg1�ҵ�seg2����seg2��ǰ����ѯ�ɹ�������*/
        /*isFind�����ų�ǰ���Ѿ����ҵ�ȴ�ٴθ�����ֵ��ֵ*/
        if((0U==isFind)&&(0U == retVal))
        {
            if (currentSeg1ID == seg2)
            {
                retVal = 0x02U;	
            }
            else if (currentSeg2ID == seg1)
            {
                /*��������Ϊͨ��seg2�ҵ�seg1����seg1��ǰ����ѯ�ɹ�������*/
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
    UINT8_S tmpRetVal=0U;/*���õĺ����ķ���ֵ*/
    UINT8_S retVal = 0U;/*��������ֵ*/
    UINT16_S currentSeg1ID = 0U;/*��¼��seg1�ҵ��ĵ�ǰsegID*/
    UINT16_S currentSeg2ID = 0U;/*��¼��seg2�ҵ��ĵ�ǰsegID*/
    UINT16_S adjecttSeg1ID = 0U;/*��¼��seg1�ҵ�������segID*/
    UINT16_S adjecttSeg2ID = 0U;/*��¼��seg2�ҵ�������segID*/
    UINT16_S tmpSegId=0U; /*��ʱ����*/
    UINT32_S tmpSegLen=0U;/*��ʱ����*/
    UINT8_S findFlag = 0U;/*�Ƿ��Ѿ���ѯ�� 1 ��ѯ�� 0 δ��ѯ��*/
    UINT32_S tmpSeg1Len = 0U;
    UINT32_S tmpSeg2Len = 0U;

    /*�ж�λ��1ƫ���������������Ч��*/
    tmpSeg1Len =  GetSegDataStrulength(seg1);
    tmpSeg2Len =  GetSegDataStrulength(seg2);

    /* �ж��������ݵĺϷ��� */
    if ((tmpSeg1Len >= offset1) && (tmpSeg2Len >= offset2) && ((LINESEG_SAME_DIR == dir) || (LINESEG_CONVER_DIR == dir)))
    {       
        if (seg1 == seg2)
        {
            /* ���ų�ͬ��һ��seg����� */
            if (offset1 == offset2)
            {
                /* ƫ������ͬ,ͬ1�� */
                retVal = 0x03u;
            }  
            else if(offset1 < offset2)
            {
                /*1��ƫ����С */
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
                /*1��ƫ������ */
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
            /* ���ų���seg�߽���غϵ���� */
            tmpSegLen= tmpSeg1Len;

            if(offset1 == tmpSegLen)
            {
                tmpRetVal = GetNextSegId(seg1, LINESEG_SAME_DIR,&tmpSegId);

                if(1U == tmpRetVal)
                {
                    /*�ɹ��ҵ�����seg*/
                    if ((tmpSegId == seg2) &&(offset2 == 0u))
                    {
                        /*�����غ�*/
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
                        /*�����غ�*/
                        retVal = 0x03u;
                        findFlag = 1u;
                    }
                }
            }
            else
            {
                /* ������ */
            }

            if (0u == findFlag)
            {
                /* ������ͬһ��seg�ұ߽�㲻�غ� */ 
                currentSeg1ID = seg1;
                currentSeg2ID = seg2;

                /* ��seg1�ط�����seg2��ѯ */
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

                /* ��seg2�ط�����seg1��ѯ */
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
        /* ����������Ϸ�,����0 */
        retVal = 0u;
    }

    return retVal;
}

/*******************************************
* ������	�� CheckPointBelongToOutCbtcArea
* ���������� ��ѯĳ�����Ƿ������˳�CBTC����
* ����˵���� UINT16_S wTrainHeadSeg, 
*          UINT32_S dwTrainHeadOffset
* ����ֵ  �� 0: ��ȡʧ��
*		    1: ����
*            2: ������
*/
UINT8_S CheckPointBelongToOutCbtcArea(UINT16_S wTrainHeadSeg, UINT32_S dwTrainHeadOffset)
{
    UINT8_S retVal = 0U;
    UINT32_S segLength = 0U;/*SEG����*/

    /*��SEGID���з���*/
    segLength = GetSegDataStrulength(wTrainHeadSeg);
    if (segLength > 0U)
    {
        /*�жϴ˵��Ƿ������˳�CBTC����*/
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
* ������	�� CheckAcOrderBetweenTwoPoints
* ���������� ��ѯ�����Ӹ�������ļ�������(���֧��TWO_POINT_AC_NUM_MAX��20��������)����seg1��seg2������
* ����˵���� const UINT16 seg1,SEG��ID
*            const UINT16_S seg2,SEG��ID
*            const UINT8_S dir,���з���
*            UINT8_S *acNum,���������
*            UINT16_S acIdBuff[],�����ID 
* ����ֵ  �� 
*    00,��ѯʧ��
*    1,��ѯ�ɹ�
*    2,���ֳɹ�
*/
UINT8_S CheckAcOrderBetweenTwoPoints(const UINT16_S seg1,const UINT16_S seg2,const UINT8_S dir,UINT8_S *acNum,UINT16_S acIdBuff[])
{
    UINT8_S retVal = 0U;/*��������ֵ*/
    UINT16_S pSegId[BOTHSEG_INCLUDE_MAX_SEG] = {0U};/*���SEGID*/
    UINT8_S includeSegId = 0U;/*������SEGID*/

    /*��ȡ����SEG֮�������SEGID*/
    retVal = GetDirSegArray(seg1,seg2,dir,1U,&includeSegId,pSegId);

    /*��ȡSEGID��Ӧ�ļ�������*/
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
* ������	�� GetLineSegBelongZcId
* ���������� ��ѯSeg����ZC
* ����˵���� const UINT16_S segId,
* ����ֵ  �� 0: ��ȡʧ��
*		    >0: ����ZC
*/
UINT16_S GetLineSegBelongZcId(const UINT16_S segId)
{
    UINT16_S retVal = 0U;/*��������ֵ*/

    retVal = GetSegDataStrusegManageZCId(segId);

    return retVal;
}

/*******************************************
* ������	��
* ���������� ��ѯ���Ƿ�λ���л�������ƽ�������
* ����˵���� const UINT16 condominiumLineId �ƽ�����SEGID
*			 const UINT16_S seg ��������SEGID
*            const UINT32_S offset,����Link��ƫ����
* ����ֵ  �� 0: ��ȡʧ��
*		    1: ����
*            2: ������
*/
UINT8_S CheckPointBelongTocondominiumLineOfHand(const UINT16_S condominiumLineId,const UINT16_S seg,const UINT32_S offset)
{
    UINT8_S retVal = 0U;/*��������ֵ*/
    BnfLineSwitchInfoStruct* lineSwitchStru = NULL;/*�л���·��Ϣ�ṹ��ָ��*/
    UINT16_S segIdBuff[BOTHSEG_INCLUDE_MAX_SEG] = {0U};/*�������SEG֮���SEG*/
    UINT8_S includeSegNum = 0U;/*������SEG����*/
    UINT8_S i = 0U;/*ѭ��ʹ��*/
    UINT16_S zcId = 0U;/*��ǰSEG������ZCID*/
    UINT32_S segLength = 0U;/* SEG���ܳ� */
    UINT8_S retGetSeg = 0U;

    /*�����л���ID��ȡ�л���·��Ϣ*/
    lineSwitchStru = GetIndexIdLineSwitchInfoDataStru(condominiumLineId);

    if (lineSwitchStru != NULL)
    {
        /*��ȡ�л������SegID*/
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
                    /*��ѯ������Լ���Χ��*/
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
                    /*��ѯ�յ����Լ���Χ��*/
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
* ������	��CheckAcBelongToStation
* ������������ѯĳ�����������Ƿ�����վ̨����
* ����˵���� const UINT16_S acId
* ����ֵ  �� 0: ��ȡʧ��
*		    1: ����
*            2: ������
*/
UINT8_S CheckAcBelongToStation(const UINT16_S acId)
{
    UINT8_S retVal = 0U;/*��������ֵ*/
    UINT16_S pSegId[AXLESECTION_SEG_MAX_NUM] = {0U};
    UINT16_S includeSegNum = 0U;/*������SEGID����*/

    /*��ȡ�������ζ��ڵ�SEGID*/
    includeSegNum = GetAxleSectionDataStruSegInfo(acId,pSegId);
    if (0U < includeSegNum)
    {
        /*���Ҵ�SEG�Ƿ�����վ̨����,����ֵΪ1 ���� 2 ������*/
        retVal = SearchStationBelongAxleSec(pSegId,includeSegNum);
    }

    return retVal;
}

/*******************************************
* ������	�� CheckSwitchOrderBetweenTwoPoints
* ���������� ��ѯ�����Ӹ�������ĵ�������(���֧��TWO_POINT_SWITCH_NUM_MAX��30����)����seg1��seg2������
* ����˵���� const UINT16_S seg1,
*          const UINT16_S seg2,
*          UINT8_S dir,
*          UINT8_S *switchNum,
*          UINT16_S swtichIdBuff[],
* ����ֵ  �� 
*    00,��ѯʧ��
*    1,��ѯ�ɹ�
*    2,���ֳɹ�
*/
UINT8_S CheckSwitchOrderBetweenTwoPoints(const UINT16_S seg1,const UINT16_S seg2,UINT8_S dir,UINT8_S *switchNum,UINT16_S swtichIdBuff[])
{
    UINT8_S retVal = 0U;/*��������ֵ*/
    UINT16_S pSegId[BOTHSEG_INCLUDE_MAX_SEG] = {0U};/*���SEGID*/
    UINT8_S includeSegId = 0U;/*������SEGID*/

    /*��ȡ����SEG֮�������SEGID*/
    retVal = GetDirSegArray(seg1,seg2,dir,1U,&includeSegId,pSegId);

    /*��ȡSEGID��Ӧ�ĵ���*/
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
* ������	�� CheckPsdOrderBetweenTwoPoints
* ���������� ��ѯ�����Ӹ������������������(���֧��TWO_POINT_PSD_NUM_MAX��10����)����seg1��seg2������
* ����˵���� const UINT16_S seg1,
*          const UINT16_S seg2,
*          UINT8_S dir,
*          UINT8_S *psdNum,
*          UINT16_S psdIdBuff[],
* ����ֵ  �� 
*    00,��ѯʧ��
*    1,��ѯ�ɹ�
*    2,���ֳɹ�
*/
UINT8_S CheckPsdOrderBetweenTwoPoints(const UINT16_S seg1,const UINT16_S seg2,UINT8_S dir,UINT8_S *psdNum,UINT16_S psdIdBuff[])
{
    UINT8_S retVal = 0U;/*��������ֵ*/
    UINT16_S pSegId[BOTHSEG_INCLUDE_MAX_SEG] = {0U};/*���SEGID*/
    UINT8_S includeSegId = 0U;/*������SEGID*/
    UINT8_S platPormNum = 0U;/*վ̨����*/
    UINT16_S platPormBuff[TWO_POINT_STATION_NUM_MAX] = {0U};/*����SEG֮���վ̨iD*/

    if ((NULL != psdNum) && (NULL != psdIdBuff))
    {
        *psdNum = 0U;

        /*��ȡ����SEG֮�������SEGID*/
        retVal = GetDirSegArray(seg1,seg2,dir,1U,&includeSegId,pSegId);

        /*��ȡSEGID��Ӧ��վ̨ID*/
        if (1U == retVal)
        {
            platPormNum = GetPlatformIdAccordSegBuff(pSegId,includeSegId,platPormBuff);
            if (platPormNum > 0U)
            {
                /*����վ̨ID��ȡ��Ӧ��������ID*/
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
* ������	��  CheckEsbOrderBetweenTwoPoints
* ���������� ��ѯ�����Ӹ�������Ľ���ͣ����ť����(���֧��TWO_POINT_ESB_NUM_MAX��10����)����seg1��seg2������
* ����˵���� const UINT16_S seg1,
*          const UINT16_S seg2,
*          UINT8_S dir,
*          UINT8_S *esbNum,
*          UINT16_S esbIdBuff[],
* ����ֵ  �� 
*    00,��ѯʧ��
*    1,��ѯ�ɹ�
*    2,���ֳɹ�
*/
UINT8_S CheckEsbOrderBetweenTwoPoints(const UINT16_S seg1,const UINT16_S seg2,UINT8_S dir,UINT8_S *esbNum,UINT16_S esbIdBuff[])
{
    UINT8_S retVal = 0U;/*��������ֵ*/
    UINT16_S pSegId[BOTHSEG_INCLUDE_MAX_SEG] = {0U};/*���SEGID*/
    UINT8_S includeSegId = 0U;/*������SEGID*/
    UINT8_S platPormNum = 0U;/*վ̨����*/
    UINT16_S platPormBuff[TWO_POINT_STATION_NUM_MAX] = {0U};/*����SEG֮���վ̨iD*/

    if ((NULL != esbNum) && (NULL != esbIdBuff))
    {
        *esbNum = 0U;

        /*��ȡ����SEG֮�������SEGID*/
        retVal = GetDirSegArray(seg1,seg2,dir,1U,&includeSegId,pSegId);

        /*��ȡSEGID��Ӧ��վ̨ID*/
        if (1U == retVal)
        {
            platPormNum = GetPlatformIdAccordSegBuff(pSegId,includeSegId,platPormBuff);
            if (platPormNum > 0U)
            {
                /*����վ̨ID��ȡ��Ӧ�Ľ���ͣ����ťID*/
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
* ������	�� CheckSuperpositionBetweenTwoArea
* ���������� ��ѯ����������غ�����
* ����˵���� const UINT8 logicSectionNum,�߼���������
*            const UINT16_S logicSectionId[],�߼�����ID����(����߼���������50��)
*            const AreaInfoStruct maArea,�ƶ���Ȩ����
*            const UINT8_S dir,�г����з���
*            UINT8_S *superAreaNum,�غ���������
*            AreaInfoStruct superArea[],�غ�����(����غ�����5��)
* ����ֵ  �� 
*    0,��ѯʧ��
*    1,��ѯ�ɹ�
*/
UINT8_S CheckSuperpositionBetweenTwoArea(const UINT8_S logicSectionNum, const UINT16_S logicSectionId[],const AreaInfoStruct maArea,const UINT8_S dir,UINT8_S *superAreaNum,AreaInfoStruct superArea[])
{
    UINT8_S retVal = 0U;/*��������ֵ*/
    UINT8_S tmpRetVal = 0U;/*��������ֵ*/
    UINT8_S errorFlag = 1U;/*1��ȷ 0 ����*/
    BnfSegStruct* maStartSegStru = NULL;/*MA�����Ϣ��SEG��Ϣ�ṹ��ָ��*/
    BnfSegStruct* maEndSegStru = NULL;/*MA�յ���Ϣ��SEG��Ϣ�ṹ��ָ��*/
    BnfLogicSectionStruct* tmpLogStru = NULL;
    UINT8_S i = 0U;/*ѭ��ʹ��*/
    UINT8_S j = 0U;/*ѭ��ʹ��*/
    UINT8_S k = 0U;/*ѭ��ʹ��*/
    UINT8_S firstFind = 0U;
    UINT8_S findIndex = 0U;
    UINT8_S tmpFingFlag = 0U;

    UINT16_S tmpLogicId[TWO_POINT_LOGICSEC_NUM_MAX] = {0U};
    UINT8_S tmpRelateLogicNum[TWO_POINT_LOGICSEC_NUM_MAX] = {0U};
    BnfRelateLogicSecInfoStruct relateLogicInfo[TWO_POINT_LOGICSEC_NUM_MAX][2];
    UINT8_S tmpLogicNum = 0U;

    /*��ڷ���*/
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
        /*�ж������ڰ������߼�����ID*/
        tmpRetVal = GetDirSegArrayAndLogicSec(maArea.startSegId,maArea.startSegOffSet,maArea.endSegId,maArea.endSegOffSet,dir,&tmpLogicNum,tmpLogicId,tmpRelateLogicNum,relateLogicInfo);

        if (1U == tmpRetVal)
        {
            /*�ж�������߼������Ƿ�������������غ�����,����غ�����*/

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
                                    /*DNW,2016.3.13,��Ӳ�����1�����������1��seg�ж���߼����ε����*/
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
* ������	�� CheckPointReclosingAtQuitCbtc
* ���������� ��ѯĳ�����Ƿ���˳�CBTC�����յ��غ�
* ����˵���� const UINT16_S seg,
*          const UINT32_S offset,
* ����ֵ  �� 
*    0,��ѯʧ��
*    1,�غ�
*    2,���غ�
*/
UINT8_S CheckPointReclosingAtQuitCbtc(const UINT16_S seg,const UINT32_S offset)
{
    UINT8_S retVal = 0U;/*��������ֵ*/
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
* ������	��  CheckPointBelongToArea
* ���������� ��ѯĳ�����Ƿ�����ĳ������
* ����˵���� const UINT16_S startSeg,
*          const UINT32_S startOffset,
*          const UINT16_S endSeg,
*          const UINT32_S endOffset,
*          const UINT16_S checkSeg,
*          const UINT32_S checkOffset,
*          const UINT8_S dir,
* ����ֵ  �� 
*    0,������
*    1,����
*/
UINT8_S CheckPointBelongToArea(const UINT16_S startSeg,const UINT32_S startOffset,const UINT16_S endSeg,const UINT32_S endOffset,const UINT16_S checkSeg,const UINT32_S checkOffset,const UINT8_S dir)
{
#if 0
    UINT8_S retVal = 0U;/*��������ֵ*/
    UINT8_S i = 0U;/*ѭ���ñ���*/
    UINT8_S bFlag = 0U;/*��־λ*/
    UINT16_S* pSegId = NULL;
    UINT8_S segBothPointNum = 0U;/*����SEG���SEG��Ŀ*/
    UINT32_S disStartToTrain = UINT32_NULL;/*��㵽�г������*/
    UINT32_S disStartToEnd = UINT32_NULL;/*��㵽�յ����*/
    UINT32_S disEndToTrain = UINT32_NULL;/*�յ㵽�г������*/
    UINT8_S errorFlag = 1U;/*1��ȷ 0 ����*/
    UINT16_S segTableNum = 0U;/*��ȡSEG�������*/
    UINT8_S disRtnValue1 = 0U;  /* ��ȡ2��֮����뷵��ֵ */
    UINT8_S disRtnValue2 = 0U;  /* ��ȡ2��֮����뷵��ֵ */
    UINT8_S disRtnValue3 = 0U;  /* ��ȡ2��֮����뷵��ֵ */

    /*�жϷ������Ч��*/
    if ((dir != LINESEG_SAME_DIR) && (dir != LINESEG_CONVER_DIR))
    {
        errorFlag = 0U;
    }

    segTableNum = GetSegIdNum();
    pSegId = (UINT16_S*)MemoryMalloc(sizeof(UINT16_S)*segTableNum);

    printf("cc %d-%d-%d-%d-0x%x\n",startSeg,endSeg,segTableNum,sizeof(UINT16_S),pSegId);
    if (NULL != pSegId)
    {    
        /*������յ���ͬһsegʱ*/
        if ((1U == errorFlag)&&(startSeg ==  endSeg))
        {
            /*�������ڸ�seg��ʱ������ƫ���������ж�*/
            if (startSeg == checkSeg)
            {
                /*ƫ�����ж�*/
                if (((startOffset >= checkOffset) && (endOffset <= checkOffset)) || ((endOffset >= checkOffset) && (startOffset <= checkOffset)))
                {
                    /*����������*/
                    retVal = 1U;
                }
                else
                {
                    /*�㲻��������*/
                    retVal = 0U;
                }
            }
            else
            {
                /*seg�Ų�ͬ���ز���������*/
                retVal = 0U;
            }
        }
        else if ((1U == errorFlag))
        {
            /*��㣬�յ��ڲ�ͬ��seg*/
            /*���ú�������ѯ������seg���У��õ����յ���seg����*/
            retVal = GetDirSegArray(startSeg, endSeg, dir,1U,&segBothPointNum, pSegId);

            /*��ѯʧ��*/
            if (1U == retVal)
            {
                /*�жϵ��Ƿ���seg������*/
                for (i=0U; i<segBothPointNum; i++)
                {
                    if (pSegId[i] == checkSeg)
                    {
                        /*�ñ�־λ*/
                        bFlag = 1U;
                        break;
                    }
                }

                if (0U == bFlag)
                {
                    /*�㲻�������ڣ�����*/
                    retVal = 0U;
                }
                else
                {
                    /*���þ�������ж�,�����������ľ���*/
                    disRtnValue1 = GetDirBothSegPointDisPlus(startSeg, startOffset, checkSeg, checkOffset,dir,&disStartToTrain);
                    disRtnValue2 = GetDirBothSegPointDisPlus(startSeg, startOffset, endSeg, endOffset, dir,&disStartToEnd);
                    disRtnValue3 = GetDirBothSegPointDisPlus(checkSeg, checkOffset, endSeg, endOffset, dir, &disEndToTrain);

                    if ((UINT32_NULL == disStartToTrain) || (UINT32_NULL == disStartToEnd) || (UINT32_NULL == disEndToTrain))
                    {
                        /*��������ʧ�ܣ������ϲ���ʧ��*/
                        retVal = 0U;
                    }

                    if ((1U == disRtnValue1) && (1U == disRtnValue2) && (1U == disRtnValue3))
                    {
                        if ((disStartToTrain + disEndToTrain) == disStartToEnd)
                        {
                            /*����������*/
                            retVal = 1U;
                        }
                        else
                        {
                            /*�㲻��������*/
                            retVal = 0U;
                        }
                    }
                    else
                    {
                        /* GetDirBothSegPointDisPlus�����ط������ƫ��С���յ�ƫ��,����0 */
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
    /*���ز�ѯ���*/
    return retVal;
#endif

    UINT8_S retVal = 0U;           /*��������ֵ*/
    UINT8_S rtn1 = DEFAULT_ZERO;   /* ����ȷ�ϵ��߼���ϵ����ֵ */
    UINT8_S rtn2 = DEFAULT_ZERO;   /* ȷ�ϵ���յ��߼���ϵ����ֵ */

    rtn1 = CheckLocRelationBetweenTwoPoints(startSeg,startOffset,checkSeg,checkOffset,dir);

    rtn2 = CheckLocRelationBetweenTwoPoints(checkSeg,checkOffset,endSeg,endOffset,dir);

    if ((3u == rtn1) || (3u == rtn2))
    {
        /* ��1���˵��غ� */
        retVal = 1u;
    } 
    else if((2u == rtn1) && (2u == rtn2))
    {
        /* �������յ�֮�� */
        retVal = 1u;
    }
    else
    {
        retVal = 0u;
    }

    return retVal;
}

/*******************************************
* ������	�� GetLineAcLength
* ���������� ��ѯ�������γ���
* ����˵���� const UINT16_S acId,
*          UINT32_S *acLength
* ����ֵ  �� 
*    0,��ѯʧ��
*    1,��ѯ�ɹ�
*/
UINT8_S GetLineAcLength(const UINT16_S acId,UINT32_S *acLength)
{
    UINT8_S retVal = 0U;/*��������ֵ*/
    UINT16_S pSegId[AXLESECTION_SEG_MAX_NUM] = {0U}; /*SEGIDָ��*/
    UINT16_S segNum = 0U;/*SEG����*/
    UINT16_S i = 0U;/*ѭ��ʹ��*/
    UINT32_S tempAxleLen = 0U;/*�������γ���*/

    /*��ȡSEG����*/
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
* ������	�� CheckPointBelongDrButtonId
* ���������� ��ѯĳ���������������۷���ťID
* ����˵���� const UINT16_S seg,
*          const UINT32_S offset,
*          UINT16_S *drButtonId
* ����ֵ  �� 
*    0,��ѯʧ��
*    1,��ѯ�ɹ�
*/
UINT8_S CheckPointBelongDrButtonId(const UINT16_S seg,const UINT32_S offset,UINT16_S *drButtonId)
{
    UINT8_S retVal = 0U;/*��������ֵ*/
    UINT8_S breakFlag = 0U;
    BnfArStruct *bnfArStru = NULL;
    BnfStopPointStruct *bnfStopPointStru = NULL;
    UINT16_S lineNum = DEFAULT_ZERO;
    UINT16_S cycle = DEFAULT_ZERO;
    UINT16_S arInStopPointId = DEFAULT_ZERO;

    /*��ȡ�����۷���Ϣ*/
    bnfArStru = GetArDataInfo(&lineNum);

    if ((NULL != bnfArStru) && (NULL != drButtonId))
    {
        for (cycle = DEFAULT_ZERO;cycle < lineNum;cycle++)
        {
            /*��ȡ�����۷���Ӧ�Ľ���ͣ������Ϣ*/
            arInStopPointId = bnfArStru[cycle].arInStopPointId;

            /*��ȡͣ��������Seg*/
            bnfStopPointStru = GetIndexIdStopPointDataStru(arInStopPointId);

            if (NULL != bnfStopPointStru)
            {
                /*��ȡͣ��������SEG*/
                if (bnfStopPointStru->segId == seg)
                {
                    if ((offset >= (bnfStopPointStru->segOfst - bnfStopPointStru->aTPParkArea))
                        && (offset <= (bnfStopPointStru->segOfst + bnfStopPointStru->aTPParkArea)))
                    {
                        /*����seg�������۷������������ID*/
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
* ������	��  CheckSignalPostion
* ���������� ��ѯ�źŻ�λ��ID
* ����˵���� const UINT16_S signalId,
*          UINT16_S *seg,
*          UINT32_S *offset
* ����ֵ  �� 
*    0,��ѯʧ��
*    1,��ѯ�ɹ�
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
* ������	��  CheckFirstAcOfSignal
* ���������� ��ѯ�źŻ��ڷ���һ����������
* ����˵���� const UINT16_S signalId,
*          UINT16_S * acId
* ����ֵ  �� 
*    0,��ѯʧ��
*    1,��ѯ�ɹ�
*/
UINT8_S CheckFirstAcOfSignal(const UINT16_S signalId,UINT16_S * acId)
{
    UINT8_S retVal = 0U;/*��������ֵ*/
    UINT16_S signalSegId = DEFAULT_ZERO;
    UINT16_S tmpSegIdBuff[3] = {0U};
    UINT8_S tmpSegIdNum = 0U;/*SEGID����*/
    UINT8_S findNum = 0U;/*���ҵ�SEG�ĸ��������ڵ���2��Ϊ2*/
    BnfSignStruct* signStru = NULL;/*�źŻ��ṹ��*/

    /*��ȡ�źŻ���Ϣ*/
    signStru = GetIndexIdSignDataStru(signalId);

    /*��ȡ�źŻ��ķ�������*/
    if ((signStru != NULL)  && (NULL != acId))
    {
        if (LINESEG_SAME_DIR == signStru->protectiveDir)
        {
            /*�����źŻ���λ���ж�*/
            if (DEFAULT_ZERO == signStru->signProtectSegOffset)
            {
                /*˵��������seg��Ϊ�ڷ�����������Seg*/
                signalSegId = signStru->signProtectSegId;
                retVal = 1U;
            } 
            else
            {
                /*������·�����ȡ��SEG���յ�SEGID*/
                retVal = GetNextSegId(signStru->signProtectSegId,LINESEG_SAME_DIR,&signalSegId);
            }
        } 
        else if (LINESEG_CONVER_DIR == signStru->protectiveDir)
        {
            /*�����źŻ���λ���ж�*/
            if (DEFAULT_ZERO == signStru->signProtectSegOffset)
            {
                /*������·�����ȡ��SEG���������SEGID*/
                retVal = GetNextSegId(signStru->signProtectSegId,LINESEG_CONVER_DIR,&signalSegId);
            } 
            else
            {
                /*˵��������seg��Ϊ�ڷ�����������Seg*/
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
            /*��ȡ��SEG�������а�������ʱ,�����е������Ӧ��SEGID*/
            tmpSegIdNum = GetSegBuffAccordSedIdAndSwitch(signalSegId,tmpSegIdBuff,&findNum);
            *acId = GetSegIdBelongofAxleSecId(tmpSegIdBuff,tmpSegIdNum,findNum);
        }
    }

    return retVal;
}

/*******************************************
* ������	��  CheckOutsideAcOfSignal
* ���������� ��ѯ�źŻ��ⷽ��һ����������
* ����˵���� const UINT16 signalId, �źŻ�ID
*            UINT16_S * acId,�źŻ��ⷽ��һ����������ID
* ����ֵ  �� 
*    0,��ѯʧ��
*    1,��ѯ�ɹ�
*/
UINT8_S CheckOutsideAcOfSignal(const UINT16_S signalId,UINT16_S * acId)
{
    UINT8_S retVal = 0U;/*��������ֵ*/
    UINT16_S signalSegId = DEFAULT_ZERO;
    UINT16_S tmpSegIdBuff[3] = {0U};
    UINT8_S tmpSegIdNum = 0U;/*SEGID����*/
    UINT8_S findNum = 0U;/*���ҵ�SEG�ĸ��������ڵ���2��Ϊ2*/
    BnfSignStruct* signStru = NULL;/*�źŻ��ṹ��*/

    /*��ȡ�źŻ���Ϣ*/
    signStru = GetIndexIdSignDataStru(signalId);

    /*��ȡ�źŻ��ķ�������*/
    if ((signStru != NULL) && (NULL != acId))
    {
        if (LINESEG_SAME_DIR == signStru->protectiveDir)
        {
            /*�����źŻ���λ���ж�*/
            if (DEFAULT_ZERO == signStru->signProtectSegOffset)
            {
                /*������·�����ȡ��SEG���������SEGID*/
                retVal = GetNextSegId(signStru->signProtectSegId,LINESEG_CONVER_DIR,&signalSegId);
            } 
            else
            {
                /*˵��������seg��Ϊ�ڷ�����������Seg*/
                signalSegId = signStru->signProtectSegId;
                retVal = 1U;
            }
        } 
        else if (LINESEG_CONVER_DIR == signStru->protectiveDir)
        {
            /*�����źŻ���λ���ж�*/
            if (DEFAULT_ZERO == signStru->signProtectSegOffset)
            {
                /*˵��������seg��Ϊ�ⷽ����������Seg*/
                signalSegId = signStru->signProtectSegId;
                retVal = 1U;
            } 
            else
            {
                /*������·�����ȡ��SEG���յ�����SEGID*/
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
* ������	�� CheckAcLength
* ���������� ��ѯ�������γ���
* ����˵���� const UINT16_S acId �������α��
*          UINT32_S *length �������γ���
* ����ֵ  �� 
*    0,��ѯʧ��
*    1,��ѯ�ɹ�
*/
UINT8_S CheckAcLength(const UINT16_S acId,UINT32_S *length)
{
    BnfAxleSectionStruct* bnfAxleSectionStru = NULL;
    UINT8_S rtnValue = DEFAULT_ZERO;
    UINT16_S cycle = DEFAULT_ZERO;
    UINT32_S segLength = DEFAULT_ZERO;
    UINT32_S tempLength = DEFAULT_ZERO;
    UINT8_S breakFlag = DEFAULT_ZERO;

    /*��ȡ����������Ϣ*/
    bnfAxleSectionStru = GetIndexIdAxleSectionDataStru(acId);

    if (NULL != bnfAxleSectionStru)
    {
        /*�ɼ������ΰ�����seg�����ܳ���*/
        for (cycle = DEFAULT_ZERO;cycle < bnfAxleSectionStru->includeSegNum;cycle++)
        {
            /*��ȡseg����*/
            segLength = GetSegDataStrulength(bnfAxleSectionStru->segIdBuff[cycle]);

            if (DEFAULT_ZERO != segLength)
            {
                /*�ۼӳ���*/
                tempLength = tempLength + segLength;
            } 
            else
            {
                /*��ȡʧ��*/
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
        /*�������*/
        (*length) = tempLength;
    }

    return rtnValue;
}

/*******************************************
* ������	�� GetLineRouteAreaType
* ���������� ��ѯ��·��������
* ����˵���� 
* ����ֵ  �� 
*    0,��ѯʧ��
*   >0,��������
*/
UINT8_S GetLineRouteAreaType(const UINT16_S routeId)
{
    UINT8_S retVal = 0U;/*��������ֵ*/
    UINT16_S ciId = 0U;/*CIID*/

    /*��ȡ��·������CIID*/
    ciId = GetRouteDataStrumanageCI(routeId);

    /*��������ID��ȡ��������*/
    retVal = GetSecPropertyAccordName(DEV_CI_TYPE,ciId);

    return retVal;
}


/*******************************************
* ������	�� CheckLogicIdBetweenPoints
* ���������� ��ѯ����֮����߼���������
* ����˵���� 
*const UINT8_S  selfFlag
*	selfFlag˵����1��������㲻�����յ��߼����Σ�2�������յ㲻��������߼����Σ�3�����������յ��߼����Σ�0�������������յ��߼�����
* const UINT16_S headSeg  ���seg
* const UINT32_S headOffset ���offset
* const UINT16_S tailSeg  �յ�seg
* const UINT32_S tailOffset �յ�offset
* const UINT8_S direction  ��ѯ����
UINT16_S logicSectionId[SIZE_MAX_SECTION_AC] �߼��������У�������㵽�յ�ķ�����
* ����ֵ  ��0XFF ʧ��
>=0   �߼����θ���(��selfFlagΪ0x55ʱ������ֵ������Ϊ0)	  
*/
UINT8_S CheckLogicIdBetweenPoints(const UINT8_S selfFlag,const UINT16_S headSeg,const UINT32_S headOffset,const UINT16_S TailSeg,const UINT32_S TailOffset,const UINT8_S direction,UINT16_S logicSectionId[])
{
    UINT8_S retVal = UINT8_NULL;/*��������ֵ*/
    UINT16_S segBuff[BOTHSEG_INCLUDE_MAX_SEG + 2U] = {0U};
    UINT8_S segIdNum = 0U;/*����SEG֮���SEG����*/
    UINT8_S index = 0U;/*�����±�*/
    BnfLogicSectionStruct* logicSecStru = NULL;/*�߼����νṹ��*/
    UINT16_S lineLogicSecNum = 0U;/*�߼����α�����*/
    UINT16_S i = 0U,j = 0U,jj = 0U;/*ѭ��ʹ��*/
    UINT8_S isFind = 0U;/*1�ҵ� 0 δ�ҵ�*/
    UINT8_S indexLog = 0U;/*�����±�*/
    UINT8_S isErrorLogId = 0U;/*�Ƿ�Ϊ��Ч���߼�����ID*/
    UINT32_S tmpHeadOffset = 0U;/*��ʱ������ƫ����*/
    UINT32_S tmpTailOffset = 0U;/*��ʱ����յ�ƫ����*/
    UINT16_S tmpStartSeg = headSeg;
    UINT16_S tmpEndSeg = TailSeg;
    UINT8_S isFindNum = 0U;/*���ҵ��ĸ���*/
    UINT32_S tmpStartSegLength = 0U;/*���SEG����*/
    BnfSegStruct* startSegInfoStru = NULL;/*���SEG��Ϣ�ṹ��*/
    BnfSegStruct* endSegInfoStru = NULL;/*�յ�SEG��Ϣ�ṹ��*/
    UINT8_S tmpSwitchStatus = 0U;/*��ʱ�����״̬*/
    UINT16_S tmpNextSegId = 0U;/*��ʱ�����һ��SEGID*/
    UINT8_S tmpSelfFlag = 0U;/*��ʼ��ֵ*/

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
            /*���������յ�֮�������SEGID,�����������յ����ڵ�SEGID*/
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
                            /*���߼����β�д��*/
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
                        /*���߼����β�д��*/
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
                        /*���߼����β�д��*/
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
                        /*���߼����β�д��*/
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
                                /*���߼����β�д��*/
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
                                /*���߼����β�д��*/
                                isErrorLogId = 1U;
                                break;
                            }
                        }
                        else
                        {
                            /*���߼�����ֱ��д��*/
                        }

                        if((tmpSelfFlag != 3U)&&(tmpSelfFlag != 1U))
                        {
                            /*���߼����β�д��*/
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
                                /*���߼����β�д��*/
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
                                /*���߼����β�д��*/
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
                            /*���߼�����ֱ��д��*/
                        }

                        if((tmpSelfFlag != 3U)&&(tmpSelfFlag != 2U))
                        {
                            /*���߼����β�д��*/
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
                        /*������ҵ����߼��ε����SEG���յ�SEG*/
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
            /* ����ѯ������� */
            for (i=DEFAULT_ZERO;i < (indexLog / 2u);i++)
            {
                /* ����1��������� tmpLogicId*/
                /*
                tmpLogicId = logicSectionId[indexLog-i-1u];
                logicSectionId[indexLog-i-1u] = logicSectionId[i];
                logicSectionId[i] = tmpLogicId;
                */

                /*����2���ڳ������ֵ���*/
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
* ������	�� CheckPointBelongReverseArea
* ���������� ��ѯĳ�����Ƿ������۷���
* ����˵���� const UINT16 segId,Seg���
* ����ֵ  �� 
*    0,�������۷���
*    1,�����۷���
*/
UINT8_S CheckPointBelongReverseArea(const UINT16_S segId)
{
    UINT16_S stopSecType = 0U;
    UINT8_S rtnValue = 0U;

    stopSecType = GetCurSegOfStopSecType(segId);

    if ((UINT16_S)(RUN_REVERT_AREA) == (UINT16_S)(stopSecType & ((UINT16_S)RUN_REVERT_AREA)))
    {
        /*�����۷���*/
        rtnValue = 1U;
    } 
    else
    {
        /*�������۷���*/
        rtnValue = 0U;
    }

    return rtnValue;
}

/*******************************************
* ������	�� CheckAcOrderAccordLineSwitchId
* ���������� ��ѯ�л���ID��ȡ���л���������ļ������θ�����ID
* ����˵����const UINT16 lineSwitchId
*           UINT8_S *acNum,���������
*           UINT16_S acIdBuff[],�����ID 
* ����ֵ  �� 
*    00,��ѯʧ��
*    1,��ѯ�ɹ�
*    2,���ֳɹ�
*/

UINT8_S CheckAcOrderAccordLineSwitchId(const UINT16_S lineSwitchId,UINT8_S *acNum,UINT16_S acIdBuff[])
{
    UINT8_S retVal = 0U;/*��������ֵ*/
    BnfLineSwitchInfoStruct* lineSwitchStru = NULL;/*�л�����Ϣ�ṹ��*/

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
* ������	�� CalculatePointOfInsideLink
* ���������� ����ĳ������ڷ�link(��Ҫ�������ڵ�����ֱ�ʾ����(a+max=b+0),��ȡ�ط�����ڷ�link)
* ����˵���� const UINT8 dir,����
*            const UINT16_S segId,����segId
*            const UINT32_S offset,����ƫ����
*            UINT16_S *outSegId,���seg
* ����ֵ  �� 0:��ȡʧ��
*            1:��ȡ�ɹ�
*/
UINT8_S CalculatePointOfInsideLink(const UINT8_S dir,const UINT16_S segId,const UINT32_S offset,UINT16_S *outSegId)
{
    UINT8_S rtnValue = 0U;
    UINT32_S tmpSegLen = 0U;
    UINT8_S flag = 1U;
    UINT8_S tmpRetVal = 0U;
    UINT16_S nextSegId = 0U;
    UINT16_S frontAcId = 0U;

    /*�ж�λ��ƫ���������������Ч��*/
    tmpSegLen =  GetSegDataStrulength(segId);
    if (offset > tmpSegLen) 
    {
        /*��ڲ���ʧ������ѯʧ�ܣ�����Ĭ��ֵ*/
        flag = 0x00U;
    }

    /*�ж�����������з������ȷ��*/
    if ((LINESEG_SAME_DIR != dir) && (LINESEG_CONVER_DIR != dir))
    {
        /*��ڲ���ʧ������ѯʧ�ܣ�����Ĭ��ֵ*/
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
* ������	�� CheckFrontLink
* ���������� ���㵱ǰSegǰ��Seg
* ����˵���� const UINT8 dir,����
*            const UINT16_S segId,��ǰsegId
*            UINT16_S *outSegId,���seg
* ����ֵ  �� 0:��ȡʧ��
*            1:��ȡ�ɹ�
*/
UINT8_S CheckFrontLink(const UINT8_S dir,const UINT16_S segId,UINT16_S *outSegId)
{
    UINT8_S errorFlag = 0U;
    UINT8_S retVal = 0U;
    UINT16_S nextSeg = 0U;

    /*�ж��������뷽�����ȷ��*/
    if ((LINESEG_SAME_DIR == dir) || (LINESEG_CONVER_DIR == dir)) 
    {
        /*�����������*/
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
* ������	�� CheckPointQuitCbtcIsFindPoint
* ���������� ��ѯĳ�����Ƿ������˳�CBTC������
* ����˵���� 
* ����ֵ  �� 
*    1,����
*    2,������
*	 0,��ѯʧ��
*/
UINT8_S CheckPointQuitCbtcIsFindPoint(const UINT16_S seg,const UINT32_S offset,const UINT8_S dir)
{

#if 0
    UINT8_S retVal = 0u;/*��������ֵ*/
    UINT8_S checkRtn = 0u;
    UINT16_S i = 0u;/*ѭ��ʹ��*/
    UINT16_S j =0u;/*ѭ��ʹ��*/
    BnfExitCbtcSectionStruct* exitCbtcSectionDataStru = NULL;
    UINT16_S exitCbtcNum = 0u;
    UINT16_S tmpheadSegId = 0u;
    UINT32_S tmpheadSegOffset = 0u;
    UINT16_S tmptailSegId = 0u;
    UINT32_S tmptailSegOffset = 0u;
    UINT8_S isFindSameDir = 0u;/*1 ���� 0 δ����*/


    /*��ȡ�˳�CBTC������Ϣ*/
    exitCbtcSectionDataStru = GetExitCbtcSectionDataInfo(&exitCbtcNum);

    if (NULL != exitCbtcSectionDataStru)
    {
        /*������Ϊ������*/
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
                {/*1��ͷ�㣬β�㡢���ҵ���ͬһLink�ϣ�ֻ��Ҫ�Ƚ�offset*/
                    if((offset >= exitCbtcSectionDataStru[i].startOffset)&&(offset <= exitCbtcSectionDataStru[i].endOffSet))
                    {
                        retVal = 1u;
                    }
                }
                else if((exitCbtcSectionDataStru[i].startSegId == exitCbtcSectionDataStru[i].endSegId)&&(exitCbtcSectionDataStru[i].endSegId != seg))
                {/*2��ͷ�㡢β����ͬһLink�ϣ����ҵ㲻�ڣ�ֱ�Ӳ���ʧ��*/
                    retVal = 2u;
                }
                else if(seg == exitCbtcSectionDataStru[i].startSegId == seg)
                {/*3��ͷ�㡢���ҵ���ͬһLink�ϣ�ͷ�㲻�ڣ�ֻ��Ҫ�Ƚ�offset*/
                    if(offset >= exitCbtcSectionDataStru[i].startOffset)
                    {
                        retVal = 1u;
                    }
                }
                else if(seg == exitCbtcSectionDataStru[i].endSegId)
                {/*4��β�㡢���ҵ���ͬһLink�ϣ�β�㲻�ڣ�ֻ��Ҫ�Ƚ�offset*/ 
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

    UINT8_S retVal = 0u;         /*��������ֵ*/
    UINT16_S i = 0u;/*ѭ��ʹ��*/
    BnfExitCbtcSectionStruct* exitCbtcSectionDataStru = NULL;
    UINT16_S exitCbtcNum = 0u;
    UINT16_S tmpHeadSegId = 0u;
    UINT32_S tmpHeadSegOffset = 0u;
    UINT16_S tmpTailSegId = 0u;
    UINT32_S tmpTailSegOffset = 0u;
    UINT8_S rtnRelation = 0u;

    /*��ȡ�˳�CBTC������Ϣ*/
    exitCbtcSectionDataStru = GetExitCbtcSectionDataInfo(&exitCbtcNum);

    if (NULL != exitCbtcSectionDataStru)
    {
        /*������Ϊ������*/
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
                        /* �����������������������������CBTC�˳�����,�������� */
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
