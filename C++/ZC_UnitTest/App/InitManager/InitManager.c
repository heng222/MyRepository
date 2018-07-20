/********************************************************                                                                                                            
 文 件 名： InitManager.c 
 作    者： ZC组
 创建时间： 2015-06-04
 描述： 初始化使用数据
 备注： 无  
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
*  函数名:      InitAllLocalInfo
*  功能描述:    初始化本地所有信息
*  输入:        无
*  输出:        无
*  返回值:      0: 初始化失败
*               1: 初始化成功
*************************************************/
INT8_S InitAllLocalInfo(void)
{
	UINT16_S initErrorFlag = DEFAULT_ZERO;
	INT8_S  rtnValue = 0;

    /* 分配并初始化全局的切换区域配置数据结构体数组,Vxworks程序运行时候申请这个数组因太大不能成功，仅在上电能申请成功 */
    gpChangeAreaConfigStruBuff = (ChangeAreaConfigStruct*)MemoryMalloc(sizeof(ChangeAreaConfigStruct)*CHANGE_AREA_LOCAL_SUM_MAX);
    MemorySet(gpChangeAreaConfigStruBuff,((UINT32_S)(sizeof(ChangeAreaConfigStruct)*CHANGE_AREA_LOCAL_SUM_MAX)),0u,((UINT32_S)(sizeof(ChangeAreaConfigStruct)*CHANGE_AREA_LOCAL_SUM_MAX)));

	/*初始化电子地图数据*/
	if (1 == ZcBnfDataInit(ZC_DATA_INFO))
	{
        /*不处理*/
	} 
	else
	{
		initErrorFlag = (UINT16_S)(initErrorFlag | ZC_ERROR_CODE_1);
		printf(" BNF FAILED \n");
	}

	/*初始化本地配置数据信息*/
	if (RETURN_SUCCESS == InitAllConfigData())
	{
        /*不处理*/
	} 
	else
	{
		initErrorFlag = (UINT16_S)(initErrorFlag | ZC_ERROR_CODE_2);
		printf(" InitAllConfigData() FAILED \n");
	}

	/*初始化本地线路数据信息*/
	if (RETURN_SUCCESS == InitAllLocalLineData())
	{
        /*不处理*/
	} 
	else
	{
		initErrorFlag = (UINT16_S)(initErrorFlag | ZC_ERROR_CODE_3);
		printf(" InitAllLocalLineData() FAILED \n");
	}

	/*初始化TSR*/
	if(RETURN_SUCCESS == TsrInit())/*-bye-*/
	{
		/*不处理*/
	}
	else
	{
		initErrorFlag = (UINT16_S)(initErrorFlag | ZC_ERROR_CODE_4);
		printf(" TsrInit() FAILED \n");
	}

    /*初始化全局数据*/
    InitAllStaticData();

	if (DEFAULT_ZERO == initErrorFlag)
	{
		rtnValue = 1;
	} 
	else
	{
		rtnValue = 0;

	}

    /* 初始化Rssp1协议 */
#if 0
    TB_RSSP1_Init();
#endif

	LogPrintf(1U,"InitAllLocalInfo Error=%d\n",initErrorFlag);
	return rtnValue;
}

/*************************************************
  函数名:      InitAllConfigData
  功能描述:    初始化本地所有配置信息
  输入:        无
  输出:        无
  返回值:      RETURN_ERROR:   初始化失败
               RETURN_SUCCESS: 初始化成功
*************************************************/
UINT8_S InitAllConfigData(void)
{
	UINT16_S initErrorFlag = DEFAULT_ZERO;
	UINT8_S  rtnValue = DEFAULT_ZERO;
	 

	/*初始化本地ZCid*/
	if (RETURN_SUCCESS == InitLocalZcIdConfigData())
	{
        /*不处理*/
	} 
	else
	{
		initErrorFlag = (UINT16_S)(initErrorFlag | ZC_ERROR_CODE_1);
	}

	/*初始化本地ZC通信对象*/
	if (RETURN_SUCCESS == InitCommTargetInfo())
	{
        /*不处理*/
	} 
	else
	{
		initErrorFlag = (UINT16_S)(initErrorFlag | ZC_ERROR_CODE_2);
	}

	/*初始化系统配置数据*/
	if (RETURN_SUCCESS == InitSystemConfigData())
	{
        /*不处理*/
	} 
	else
	{
		initErrorFlag = (UINT16_S)(initErrorFlag | ZC_ERROR_CODE_3);
	}

	/*初始化ZC子系统配置数据*/
	if (RETURN_SUCCESS == InitZcSubSystemConfigData())
	{
        /*不处理*/
	} 
	else
	{
		initErrorFlag = (UINT16_S)(initErrorFlag | ZC_ERROR_CODE_4);
	}

	/*初始化数据版本信息*/
	if (RETURN_SUCCESS == InitLocalDataVersion())
	{
        /*不处理*/
	} 
	else
	{
		initErrorFlag = (UINT16_S)(initErrorFlag | ZC_ERROR_CODE_5);
	}

	/*初始化NTP配置信息*/
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
  函数名:      InitAllLocalLineData
  功能描述:    初始化本地所有线路信息
  输入:        无
  输出:        无
  返回值:      RETURN_ERROR:   初始化失败
               RETURN_SUCCESS: 初始化成功
*************************************************/
UINT8_S InitAllLocalLineData(void)
{
	UINT16_S initErrorFlag = DEFAULT_ZERO;
	UINT8_S  rtnValue = DEFAULT_ZERO;
    UINT8_S  initDrButtonFlag = DEFAULT_ZERO;
	UINT8_S  initDrLampFlag = DEFAULT_ZERO;
	
	/*初始化切换区域数据*/
	if (RETURN_SUCCESS == InitChangeInfo())
	{
		/*不处理*/
	} 
	else
	{
		initErrorFlag = (UINT16_S)(initErrorFlag | ZC_ERROR_CODE_1);
	}

	/*初始化计轴区段数据*/
	if (RETURN_SUCCESS == InitACLocalInfo())
	{
        /*不处理*/
	} 
	else
	{
		initErrorFlag = (UINT16_S)(initErrorFlag | ZC_ERROR_CODE_2);
	}

	/*初始化无人折返数据*/
	initDrButtonFlag = InitDrButtonLocalInfo();
	initDrLampFlag = InitDrLampLocalInfo();
	if ((RETURN_SUCCESS == initDrButtonFlag)
		&& (RETURN_SUCCESS == initDrLampFlag))
	{
        /*不处理*/
	} 
	else
	{
		initErrorFlag = (UINT16_S)(initErrorFlag | ZC_ERROR_CODE_3);
	}

	/*初始化紧急停车按钮数据*/
	if (RETURN_SUCCESS == InitESBLocalInfo())
	{
        /*不处理*/
	} 
	else
	{
		initErrorFlag = (UINT16_S)(initErrorFlag | ZC_ERROR_CODE_4);
	}

	/*初始化逻辑区段数据*/
	if (RETURN_SUCCESS == InitLogicSectionLocalInfo())
	{
        /*不处理*/
	} 
	else
	{
		initErrorFlag = (UINT16_S)(initErrorFlag | ZC_ERROR_CODE_5);
	}

	/*初始化ZC和Ci码位数据*/
	if (RETURN_SUCCESS == InitZcCiMaskLocalInfo())
	{
        /*不处理*/
	} 
	else
	{
		initErrorFlag = (UINT16_S)(initErrorFlag | ZC_ERROR_CODE_6);
	}

	/*初始化保护区段数据*/
	if (RETURN_SUCCESS == InitOverlapLocalInfo())
	{
        /*不处理*/
	} 
	else
	{
		initErrorFlag = (UINT16_S)(initErrorFlag | ZC_ERROR_CODE_7);
	}

	/*初始化屏蔽门数据*/
	if (RETURN_SUCCESS == InitPSDLocalInfo())
	{
        /*不处理*/
	} 
	else
	{
		initErrorFlag = (UINT16_S)(initErrorFlag | ZC_ERROR_CODE_8);
	}

	/*初始化进路数据*/
	if (RETURN_SUCCESS == InitRouteLocalInfo())
	{
        /*不处理*/
	} 
	else
	{
		initErrorFlag = (initErrorFlag | ZC_ERROR_CODE_9);
	}

	/*初始化信号机数据*/
	if (RETURN_SUCCESS == InitSignalLocalInfo())
	{
        /*不处理*/
	} 
	else
	{
		initErrorFlag = (UINT16_S)(initErrorFlag | ZC_ERROR_CODE_10);
	}

	/*初始化道岔数据*/
	if (RETURN_SUCCESS == InitSwitchLocalInfo())
	{
        /*不处理*/
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
  函数名:      InitAllStaticData
  功能描述:    初始化本地所有全局数据部分信息
  输入:        无
  输出:        无
  返回值:      无
*************************************************/
void InitAllStaticData(void)
{
	/*初始化移动授权部分信息*/
	InitMaLocalInfo();

	/*初始化列车部分信息*/
	InitTrainLocalInfo();

	/*初始化ZC子系统状态信息*/
	InitZcSysStatusData();

	/*初始化临时限速部分信息*/
	InitTsrLocalInfo();
}
