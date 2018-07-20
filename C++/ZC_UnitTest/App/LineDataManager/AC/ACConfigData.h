/********************************************************
*                                                                                                            
* 文 件 名： ACConfigData.h  
* 创建时间： 2015-05-01
* 作    者： 
* 功能描述： 计轴配置数据管理  
* 备  注  ：  无
*
********************************************************/ 

#ifndef AC_CONFIG_DATA_H_
#define AC_CONFIG_DATA_H_
#include "../../../Common/CommonTypes.h"
#include "ACDefine.h"
#include "../../SysDataManager/SysDefine.h"

#ifdef __cplusplus
extern "C" 
{
#endif

	typedef struct SwitchInAcStruct
	{
		UINT16_S SwitchId;
		UINT8_S  SwitchPostion;
	}SwitchInAcStruct;

	/*计轴区段配置数据结构体*/
	typedef struct SAcConfigDataStruct
	{
		UINT16_S AcId;      		/*计轴区段ID*/
		UINT16_S BelongCiId;    	/*所属联锁ID*/
		UINT16_S BelongZcId;      /*所属ZCID*/
		UINT8_S  AcType;			/*计轴类型：0x55-正线联锁计轴;0xaa-车辆段联锁计轴*/
		UINT8_S  ChangeAttribute;  /*计轴共管区域属性：1：属于共管区域，且属于本ZC;2：属于共管区域，且属于相邻ZC;3：不属于共管区域C*/
		UINT8_S  SwitchNum;       /*计轴区段包含的道岔数量*/
		SwitchInAcStruct SwitchInAcStru[AC_SWITCH_SUM_MAX]; /*计轴区段包含的道岔信息*/
		UINT8_S  LogicSectionNum;                             /*计轴区段包含的逻辑区段数量*/
		UINT16_S LogicSectionIdBuff[SIZE_MAX_SECTIONNUM];      /*计轴区段包含的逻辑区段Id数组*/
	} AcConfigDataStruct;

	/*函数声明*/
    /*
    * 功能描述： 获取指定ID计轴索引号
    * 参数说明： const UINT16 acId, 计轴ID
    * 返回值  ： LOCAL_AC_SUM_MAX 或 AC_SUM_MAX: 获取数据失败
    *			<LOCAL_AC_SUM_MAX: 查找成功
    */
	UINT16_S GetAcConfigBufIndex(const UINT16_S acId);

	/*
	* 功能描述： 获取计轴当前总数
	* 参数说明： void    
	* 返回值  ： 0: 获取计轴数量失败
	*			>0: 计轴当前总数
	*/
	UINT16_S GetAcCurSum(void);

	/*
	* 功能描述： 获取指定数组下标对应的计轴区段ID
	* 参数说明： const UINT16 bufIndex, 数组下标    
	* 返回值  ： 0: 获取数据失败
	*			>0: ACID      
	*/
	UINT16_S GetAcId(const UINT16_S bufIndex);

	/*
	* 功能描述： 获取指定ID计轴所属联锁ID
	* 参数说明： const UINT16 acId, 计轴ID    
	* 返回值  ： 0: 获取数据失败
	*			>0: 所属联锁ID      
	*/
	UINT16_S GetAcBelongCiId(const UINT16_S acId);

	/*
	* 功能描述： 获取指定ID计轴所属Zc ID
	* 参数说明： const UINT16 acId, 计轴ID    
	* 返回值  ： 0: 获取数据失败
	*			>0: 所属ZC ID      
	*/
	UINT16_S GetAcBelongZcId(const UINT16_S acId);

	/*
	* 功能描述： 获取指定ID计轴所属类型
	* 参数说明： const UINT16 acId, 计轴ID    
	* 返回值  ： 0: 获取数据失败
	*			 0x55-正线联锁计轴
	0xaa-车辆段联锁计轴   
	*/
	UINT8_S GetAcType(const UINT16_S acId);

    /*
    * 功能描述： 获取指定ID计轴边界点属性
    * 参数说明： const UINT16 acId, 计轴ID    
    * 返回值  ： 0:不属于
    *            FLAG_SET:属于
    */
	UINT8_S GetAcBoundaryType(const UINT16_S acId);

	/*
	* 功能描述： 获取指定ID计轴包含的道岔数量
	* 参数说明： const UINT16 acId, 计轴ID    
	* 返回值  ： 0xff: 获取数据失败
	*			>=0: 道岔数量 
	*/
	UINT8_S GetAcSwitchNum(const UINT16_S acId);

	/*
	* 功能描述： 获取指定ID计轴包含的道岔信息
	* 参数说明： const UINT16 acId, 计轴ID 
	*            const UINT8_S bufSize,大小
	*            SwitchInAcStruct switchInAcStruBuff[],道岔信息
	* 返回值  ： 0: 获取数据失败
	*			 1: 获取数据成功   
	*/
	UINT8_S GetAcSwitchInfo(const UINT16_S acId,const UINT8_S bufSize,SwitchInAcStruct switchInAcStruBuff[]);

	/*
	* 功能描述： 获取指定计轴区段包含的逻辑区段数量
	* 参数说明： const UINT16 acId, 计轴区段Id    
	* 返回值  ： 0: 获取数据失败
	*			>0: 数量      
	*/
	UINT16_S GetAcLogicSectionNum(const UINT16_S acId);

	/*
	* 功能描述： 获取指定计轴区段包含的逻辑区段Id数组
	* 参数说明： const UINT16 bufIndex, 数组下标    
	*            const UINT16_S bufSize,输出数组大小
	*            UINT16_S logicSectionIdBuff[],输出数组
	* 返回值  ： 0: 获取数据失败
	*			 1: 获取成功      
	*/
	UINT8_S GetAcLogicSectionIdBuf(const UINT16_S acId,const UINT16_S bufSize,UINT16_S logicSectionIdBuff[]);
	
#ifdef __cplusplus
}
#endif

#endif
