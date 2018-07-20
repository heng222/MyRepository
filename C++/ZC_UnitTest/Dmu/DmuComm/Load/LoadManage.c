/********************************************************
* 
* �� �� ���� LoadManage.c 
* ��    �ߣ� ���� 
* ����ʱ�䣺 2016-09-03  
* ���������� ������� 
*         ���ֽܷ�����: 
*          1��������·����ע����� 
*          2��������Ӫ����ע����� 
*          3������ϵͳ��������ע����� 
*          4������ֽ������ע����� 
*          5���������봦�� 
* ��    ע�� �� 
* 
********************************************************/ 

#include "LoadManage.h"
#include "LoadAxle.h"
#include "LoadAxleSection.h"
#include "LoadAr.h"
#include "LoadBalise.h"
#include "LoadBlocApptchSection.h"
#include "LoadBlocTrgZone.h"
#include "LoadCbtcApptchSection.h"
#include "LoadCbtcTrgZone.h"
#include "LoadCommFailTime.h"
#include "LoadDefaultRoute.h"
#include "LoadEmergStopButton.h"
#include "LoadExitCbtcSection.h"
#include "LoadGrade.h"
#include "LoadLogicSection.h"
#include "LoadPhysicalSection.h"
#include "LoadPlatForm.h"
#include "LoadPoint.h"
#include "LoadProtectZone.h"
#include "LoadRoute.h"
#include "LoadShieldDoor.h"
#include "LoadSign.h"
#include "LoadStaRunLevel.h"
#include "LoadStaticResSpeed.h"
#include "LoadStopPoint.h"
#include "LoadStopSection.h"
#include "LoadSwitch.h"
#include "LoadSystemAccTable.h"
#include "LoadSystemConfig.h"
#include "LoadSystemRailInfo.h"
#include "LoadTempLimitSpeed.h"
#include "LoadTrainControlLevel.h"
#include "LoadTrainInfo.h"
#include "LoadTrainStation.h"
#include "LoadTrainTypeConfig.h"
#include "LoadLineSwitchInfo.h"
#include "LoadSeg.h"
#include "LoadSystemDevComm.h"
#include "LoadConGrade.h"
#include "LoadConResSpeed.h"
#include "LoadSectionType.h"

static LoadObjectStruct LoadObjStru[LOAD_OBJECT_MAX]; /*�������*/
static UINT8_S LoadObjCount = 0u; /*����������*/

/*
* ���������� ������·���ݹ���
* ����˵���� void
* ����ֵ  �� void       
*/
void LoadLineDataManage(void)
{
    LoadObjStru[LoadObjCount].LoadData = &LoadAxleData;
    LoadObjCount=LoadObjCount+1;

    LoadObjStru[LoadObjCount].LoadData = &LoadAxleSectionData;
    LoadObjCount=LoadObjCount+1;

    LoadObjStru[LoadObjCount].LoadData = &LoadBaliseData;
    LoadObjCount=LoadObjCount+1;

    LoadObjStru[LoadObjCount].LoadData = &LoadBlocApptchSectionData;
    LoadObjCount=LoadObjCount+1;

    LoadObjStru[LoadObjCount].LoadData = &LoadBlocTrgZoneData;
    LoadObjCount=LoadObjCount+1;

    LoadObjStru[LoadObjCount].LoadData = &LoadCbtcApptchSectionData;
    LoadObjCount=LoadObjCount+1;

    LoadObjStru[LoadObjCount].LoadData = &LoadCbtcTrgZoneData;
    LoadObjCount=LoadObjCount+1;

    LoadObjStru[LoadObjCount].LoadData = &LoadEmergStopButtonData;
    LoadObjCount=LoadObjCount+1;
    
    LoadObjStru[LoadObjCount].LoadData = &LoadGradeData;
    LoadObjCount=LoadObjCount+1;
    
    LoadObjStru[LoadObjCount].LoadData = &LoadLogicSectionData;
    LoadObjCount=LoadObjCount+1;

    LoadObjStru[LoadObjCount].LoadData = &LoadPhysicalSectionData;
    LoadObjCount=LoadObjCount+1;

    LoadObjStru[LoadObjCount].LoadData = &LoadPlatFormData;
    LoadObjCount=LoadObjCount+1;

    LoadObjStru[LoadObjCount].LoadData = &LoadPointData;
    LoadObjCount=LoadObjCount+1;

    LoadObjStru[LoadObjCount].LoadData = &LoadProtectZoneData;
    LoadObjCount=LoadObjCount+1;

    LoadObjStru[LoadObjCount].LoadData = &LoadRouteData;
    LoadObjCount=LoadObjCount+1;

    LoadObjStru[LoadObjCount].LoadData = &LoadSegData;
    LoadObjCount=LoadObjCount+1;

    LoadObjStru[LoadObjCount].LoadData = &LoadShieldDoorData;
    LoadObjCount=LoadObjCount+1;

    LoadObjStru[LoadObjCount].LoadData = &LoadSignData;
    LoadObjCount=LoadObjCount+1;

    LoadObjStru[LoadObjCount].LoadData = &LoadStaticResSpeedData;
    LoadObjCount=LoadObjCount+1;

    LoadObjStru[LoadObjCount].LoadData = &LoadSwitchData;
    LoadObjCount=LoadObjCount+1;

    LoadObjStru[LoadObjCount].LoadData = &LoadTrainStationData;
    LoadObjCount=LoadObjCount+1;

    LoadObjStru[LoadObjCount].LoadData = &LoadConResSpeedData;
    LoadObjCount=LoadObjCount+1;

    LoadObjStru[LoadObjCount].LoadData = &LoadConGradeData;
    LoadObjCount=LoadObjCount+1;
    
    LoadObjStru[LoadObjCount].LoadData = &LoadSectionTypeData;
    LoadObjCount=LoadObjCount+1;    
}

/*
* ���������� ������Ӫ���ݹ���
* ����˵���� void
* ����ֵ  �� void       
*/
void LoadRunDataManage(void)
{
    LoadObjStru[LoadObjCount].LoadData = &LoadArData;
    LoadObjCount=LoadObjCount+1;

    LoadObjStru[LoadObjCount].LoadData = &LoadDefaultRouteData;
    LoadObjCount=LoadObjCount+1;
    
    LoadObjStru[LoadObjCount].LoadData = &LoadExitCbtcSectionData;
    LoadObjCount=LoadObjCount+1;

    LoadObjStru[LoadObjCount].LoadData = &LoadTrainControlLevelData;
    LoadObjCount=LoadObjCount+1;

    LoadObjStru[LoadObjCount].LoadData = &LoadStopPointData;
    LoadObjCount=LoadObjCount+1;

    LoadObjStru[LoadObjCount].LoadData = &LoadStopSectionData;
    LoadObjCount=LoadObjCount+1;
    
    LoadObjStru[LoadObjCount].LoadData = &LoadStaRunLevelData;
    LoadObjCount=LoadObjCount+1;
}

/*
* ���������� ����ϵͳ�������ݹ���
* ����˵���� void
* ����ֵ  �� void       
*/
void LoadSystemDataManage(void)
{
    LoadObjStru[LoadObjCount].LoadData = &LoadSystemAccTableData;
    LoadObjCount=LoadObjCount+1;

    LoadObjStru[LoadObjCount].LoadData = &LoadSystemConfigData;
    LoadObjCount=LoadObjCount+1;

    LoadObjStru[LoadObjCount].LoadData = &LoadSystemRailInfoData;
    LoadObjCount=LoadObjCount+1;

    LoadObjStru[LoadObjCount].LoadData = &LoadTempLimitSpeedData;
    LoadObjCount=LoadObjCount+1;

    LoadObjStru[LoadObjCount].LoadData = &LoadTrainInfoData;
    LoadObjCount=LoadObjCount+1;

    LoadObjStru[LoadObjCount].LoadData = &LoadTrainTypeConfigData;
    LoadObjCount=LoadObjCount+1;

    LoadObjStru[LoadObjCount].LoadData = &LoadCommFailTimeData;
    LoadObjCount=LoadObjCount+1;

    LoadObjStru[LoadObjCount].LoadData = &LoadSystemDevCommData;
    LoadObjCount=LoadObjCount+1;
}

/*
* ���������� ����ֽ�����ݹ���
* ����˵���� void
* ����ֵ  �� void       
*/
void LoadDividPointDataManage(void)
{
    LoadObjStru[LoadObjCount].LoadData = &LoadLineSwitchInfoData;
    LoadObjCount=LoadObjCount+1;
}

/*
* ���������� ��������
* ����˵���� void
* ����ֵ  �� 0:�ɹ�����
*           -1:���󷵻�
*/
INT8_S LoadData(void)
{
    INT8_S retVal = 0;/*��������ֵ*/
    UINT8_S ii = 0u;
    for (ii = 0u; ii < LoadObjCount; ii++)
    {
        if (LoadObjStru[ii].LoadData != NULL)
        {
            retVal = LoadObjStru[ii].LoadData();
            if (retVal != 0)
            {
                break;
            }
        }
        else
        {
            retVal = -1;
            break;
        }
    }
    return retVal;
}
