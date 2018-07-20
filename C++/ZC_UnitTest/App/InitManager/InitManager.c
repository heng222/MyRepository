/********************************************************                                                                                                            
 �� �� ���� InitManager.c 
 ��    �ߣ� ZC��
 ����ʱ�䣺 2015-06-04
 ������ ��ʼ��ʹ������
 ��ע�� ��  
********************************************************/

#include "../SysDataManager/SysDefine.h"
#include "InitManager.h"
#include "../SysDataManager/SysConfigInitManager.h"
#include "../LineDataManager/AC/ACInitManager.h"
#include "../LineDataManager/Change/ChangeInitManager.h"
#include "../LineDataManager/DR/DRInitManager.h"
#include "../LineDataManager/ESB/ESBInitManager.h"
#include "../LineDataManager/LogicSection/LogicSectionInitManager.h"
#include "../LineDataManager/Mask/MaskInitManager.h"
#include "../LineDataManager/Overlap/OverlapInitManager.h"
#include "../LineDataManager/PSD/PSDInitManager.h"
#include "../LineDataManager/Route/RouteInitManager.h"
#include "../LineDataManager/Signal/SignalInitManager.h"
#include "../LineDataManager/Switch/SwitchInitManager.h"
#include "../LineDataManager/DataVersion/DataVersionInitManage.h"
#include "../IOManager/CommTarget/CommTargetInitManager.h"
#include "../DmuZc/DataHandle/DmuZcDataHandle.h"
#include "../TrainManager/Train/TrainInitManager.h"
#include "../TrainManager/MA/MAInitManager.h"
#include "../SysDataManager/SysStatusData.h"
#include "../LineDataManager/Tsr/TsrInitManager.h"
#include "../MaintainManager/MaintainManager.h"
#include "../../Common/Malloc.h"
#include "../../Common/MemSet.h"
#include "../LineDataManager/Change/ChangeConfigData.h"
#include "../TsrManager/TsrInterface.h"/*-bye-*/

/*#include "..\..\Rssp1\CCS_RSSP1_Task.h"*/
extern ChangeAreaConfigStruct* gpChangeAreaConfigStruBuff;     /* */

/*************************************************
*  ������:      InitAllLocalInfo
*  ��������:    ��ʼ������������Ϣ
*  ����:        ��
*  ���:        ��
*  ����ֵ:      0: ��ʼ��ʧ��
*               1: ��ʼ���ɹ�
*************************************************/
INT8_S InitAllLocalInfo(void)
{
	UINT16_S initErrorFlag = DEFAULT_ZERO;
	INT8_S  rtnValue = 0;

    /* ���䲢��ʼ��ȫ�ֵ��л������������ݽṹ������,Vxworks��������ʱ���������������̫���ܳɹ��������ϵ�������ɹ� */
    gpChangeAreaConfigStruBuff = (ChangeAreaConfigStruct*)MemoryMalloc(sizeof(ChangeAreaConfigStruct)*CHANGE_AREA_LOCAL_SUM_MAX);
    MemorySet(gpChangeAreaConfigStruBuff,((UINT32_S)(sizeof(ChangeAreaConfigStruct)*CHANGE_AREA_LOCAL_SUM_MAX)),0u,((UINT32_S)(sizeof(ChangeAreaConfigStruct)*CHANGE_AREA_LOCAL_SUM_MAX)));

	/*��ʼ�����ӵ�ͼ����*/
	if (1 == ZcBnfDataInit(ZC_DATA_INFO))
	{
        /*������*/
	} 
	else
	{
		initErrorFlag = (UINT16_S)(initErrorFlag | ZC_ERROR_CODE_1);
		printf(" BNF FAILED \n");
	}

	/*��ʼ����������������Ϣ*/
	if (RETURN_SUCCESS == InitAllConfigData())
	{
        /*������*/
	} 
	else
	{
		initErrorFlag = (UINT16_S)(initErrorFlag | ZC_ERROR_CODE_2);
		printf(" InitAllConfigData() FAILED \n");
	}

	/*��ʼ��������·������Ϣ*/
	if (RETURN_SUCCESS == InitAllLocalLineData())
	{
        /*������*/
	} 
	else
	{
		initErrorFlag = (UINT16_S)(initErrorFlag | ZC_ERROR_CODE_3);
		printf(" InitAllLocalLineData() FAILED \n");
	}

	/*��ʼ��TSR*/
	if(RETURN_SUCCESS == TsrInit())/*-bye-*/
	{
		/*������*/
	}
	else
	{
		initErrorFlag = (UINT16_S)(initErrorFlag | ZC_ERROR_CODE_4);
		printf(" TsrInit() FAILED \n");
	}

    /*��ʼ��ȫ������*/
    InitAllStaticData();

	if (DEFAULT_ZERO == initErrorFlag)
	{
		rtnValue = 1;
	} 
	else
	{
		rtnValue = 0;

	}

    /* ��ʼ��Rssp1Э�� */
#if 0
    TB_RSSP1_Init();
#endif

	LogPrintf(1U,"InitAllLocalInfo Error=%d\n",initErrorFlag);
	return rtnValue;
}

/*************************************************
  ������:      InitAllConfigData
  ��������:    ��ʼ����������������Ϣ
  ����:        ��
  ���:        ��
  ����ֵ:      RETURN_ERROR:   ��ʼ��ʧ��
               RETURN_SUCCESS: ��ʼ���ɹ�
*************************************************/
UINT8_S InitAllConfigData(void)
{
	UINT16_S initErrorFlag = DEFAULT_ZERO;
	UINT8_S  rtnValue = DEFAULT_ZERO;
	 

	/*��ʼ������ZCid*/
	if (RETURN_SUCCESS == InitLocalZcIdConfigData())
	{
        /*������*/
	} 
	else
	{
		initErrorFlag = (UINT16_S)(initErrorFlag | ZC_ERROR_CODE_1);
	}

	/*��ʼ������ZCͨ�Ŷ���*/
	if (RETURN_SUCCESS == InitCommTargetInfo())
	{
        /*������*/
	} 
	else
	{
		initErrorFlag = (UINT16_S)(initErrorFlag | ZC_ERROR_CODE_2);
	}

	/*��ʼ��ϵͳ��������*/
	if (RETURN_SUCCESS == InitSystemConfigData())
	{
        /*������*/
	} 
	else
	{
		initErrorFlag = (UINT16_S)(initErrorFlag | ZC_ERROR_CODE_3);
	}

	/*��ʼ��ZC��ϵͳ��������*/
	if (RETURN_SUCCESS == InitZcSubSystemConfigData())
	{
        /*������*/
	} 
	else
	{
		initErrorFlag = (UINT16_S)(initErrorFlag | ZC_ERROR_CODE_4);
	}

	/*��ʼ�����ݰ汾��Ϣ*/
	if (RETURN_SUCCESS == InitLocalDataVersion())
	{
        /*������*/
	} 
	else
	{
		initErrorFlag = (UINT16_S)(initErrorFlag | ZC_ERROR_CODE_5);
	}

	/*��ʼ��NTP������Ϣ*/
	InitLocalNtpConfigData();

	if (DEFAULT_ZERO == initErrorFlag)
	{
		rtnValue = RETURN_SUCCESS;
	} 
	else
	{
		rtnValue = RETURN_ERROR;
	}

	LogPrintf(1U,"InitAllConfigData Error=%d\n",initErrorFlag);
	return rtnValue;
}

/*************************************************
  ������:      InitAllLocalLineData
  ��������:    ��ʼ������������·��Ϣ
  ����:        ��
  ���:        ��
  ����ֵ:      RETURN_ERROR:   ��ʼ��ʧ��
               RETURN_SUCCESS: ��ʼ���ɹ�
*************************************************/
UINT8_S InitAllLocalLineData(void)
{
	UINT16_S initErrorFlag = DEFAULT_ZERO;
	UINT8_S  rtnValue = DEFAULT_ZERO;
    UINT8_S  initDrButtonFlag = DEFAULT_ZERO;
	UINT8_S  initDrLampFlag = DEFAULT_ZERO;
	
	/*��ʼ���л���������*/
	if (RETURN_SUCCESS == InitChangeInfo())
	{
		/*������*/
	} 
	else
	{
		initErrorFlag = (UINT16_S)(initErrorFlag | ZC_ERROR_CODE_1);
	}

	/*��ʼ��������������*/
	if (RETURN_SUCCESS == InitACLocalInfo())
	{
        /*������*/
	} 
	else
	{
		initErrorFlag = (UINT16_S)(initErrorFlag | ZC_ERROR_CODE_2);
	}

	/*��ʼ�������۷�����*/
	initDrButtonFlag = InitDrButtonLocalInfo();
	initDrLampFlag = InitDrLampLocalInfo();
	if ((RETURN_SUCCESS == initDrButtonFlag)
		&& (RETURN_SUCCESS == initDrLampFlag))
	{
        /*������*/
	} 
	else
	{
		initErrorFlag = (UINT16_S)(initErrorFlag | ZC_ERROR_CODE_3);
	}

	/*��ʼ������ͣ����ť����*/
	if (RETURN_SUCCESS == InitESBLocalInfo())
	{
        /*������*/
	} 
	else
	{
		initErrorFlag = (UINT16_S)(initErrorFlag | ZC_ERROR_CODE_4);
	}

	/*��ʼ���߼���������*/
	if (RETURN_SUCCESS == InitLogicSectionLocalInfo())
	{
        /*������*/
	} 
	else
	{
		initErrorFlag = (UINT16_S)(initErrorFlag | ZC_ERROR_CODE_5);
	}

	/*��ʼ��ZC��Ci��λ����*/
	if (RETURN_SUCCESS == InitZcCiMaskLocalInfo())
	{
        /*������*/
	} 
	else
	{
		initErrorFlag = (UINT16_S)(initErrorFlag | ZC_ERROR_CODE_6);
	}

	/*��ʼ��������������*/
	if (RETURN_SUCCESS == InitOverlapLocalInfo())
	{
        /*������*/
	} 
	else
	{
		initErrorFlag = (UINT16_S)(initErrorFlag | ZC_ERROR_CODE_7);
	}

	/*��ʼ������������*/
	if (RETURN_SUCCESS == InitPSDLocalInfo())
	{
        /*������*/
	} 
	else
	{
		initErrorFlag = (UINT16_S)(initErrorFlag | ZC_ERROR_CODE_8);
	}

	/*��ʼ����·����*/
	if (RETURN_SUCCESS == InitRouteLocalInfo())
	{
        /*������*/
	} 
	else
	{
		initErrorFlag = (initErrorFlag | ZC_ERROR_CODE_9);
	}

	/*��ʼ���źŻ�����*/
	if (RETURN_SUCCESS == InitSignalLocalInfo())
	{
        /*������*/
	} 
	else
	{
		initErrorFlag = (UINT16_S)(initErrorFlag | ZC_ERROR_CODE_10);
	}

	/*��ʼ����������*/
	if (RETURN_SUCCESS == InitSwitchLocalInfo())
	{
        /*������*/
	} 
	else
	{
		initErrorFlag = (UINT16_S)(initErrorFlag | ZC_ERROR_CODE_11);
	}

	if (DEFAULT_ZERO == initErrorFlag)
	{
		rtnValue = RETURN_SUCCESS;
	} 
	else
	{
		rtnValue = RETURN_ERROR;
	}
	
	LogPrintf(1U,"InitAllLocalLineData Error=%d\n",initErrorFlag);
	return rtnValue;
}

/*************************************************
  ������:      InitAllStaticData
  ��������:    ��ʼ����������ȫ�����ݲ�����Ϣ
  ����:        ��
  ���:        ��
  ����ֵ:      ��
*************************************************/
void InitAllStaticData(void)
{
	/*��ʼ���ƶ���Ȩ������Ϣ*/
	InitMaLocalInfo();

	/*��ʼ���г�������Ϣ*/
	InitTrainLocalInfo();

	/*��ʼ��ZC��ϵͳ״̬��Ϣ*/
	InitZcSysStatusData();

	/*��ʼ����ʱ���ٲ�����Ϣ*/
	InitTsrLocalInfo();
}
