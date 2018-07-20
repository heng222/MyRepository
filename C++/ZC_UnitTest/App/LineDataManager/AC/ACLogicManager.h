/************************************************************************
*
* 文件名   ：  ACLogicManager.h
* 创建时间 ：  2015.04.18
* 作者     ：  ZC组
* 功能描述 ：  计轴区段的逻辑处理
* 备  注   ：  无
*
************************************************************************/

#ifndef AC_LOGIC_MANAGER_DATA_H_
#define AC_LOGIC_MANAGER_DATA_H_


#include "ACDefine.h"
#include "../../../Common/CommonTypes.h"
#include "../Switch/SwitchDefine.h"


#ifdef __cplusplus
extern "C" {
#endif

    /*
    * 功能描述： 计算前方计轴区段内的列车运行方向（以当前计轴为参考单位）
    * 参数说明： const UINT8 dirFlag,方向标记(0x55:前方计轴,0xaa:后方计轴)
    *            const UINT16_S acId,当前计轴区段(预留)
    *            const UINT16_S otherAcId
    *            const UINT8_S dir,方向信息
    * 返回值  ： 1：远离参考计轴
    *            2：接近参考计轴
    *            3：无方向
    *            0：计算失败
    */
	UINT8_S CalculateTrainDirInOtherAc(const UINT8_S dirFlag,const UINT16_S acId,const UINT16_S otherAcId,const UINT8_S dir);

	/*
	* 功能描述： 计轴区段内列车排序
	* 参数说明：无    
	* 返回值  ：无
	*/
	void CalculateTrainOrderInAc(void);

	/*
	* 功能描述： 单个计轴区段内列车排序
	* 参数说明：const UINT16 trainId,带添加列车ID
	*           const UINT16_S acId,带添加计轴区段 
	* 返回值  ：无
	*/
	void CalculateTrainInSingleAc(const UINT16_S trainId,const UINT16_S acId);

	/*
	* 功能描述： 处理插入列车操作排序
	* 参数说明：const UINT16 trainId,带添加列车ID
	*           const UINT16_S acId,带添加计轴区段   
	*           const UINT8_S insertIndex,插入位置下标
	* 返回值  ：无
	*/
	void JudgeInsertTrainOrderInAc(const UINT16_S trainId,const UINT16_S acId,const UINT8_S insertIndex);

	/*
	* 功能描述： 计算最后一列进入计轴区段的列车信息
	* 参数说明：无    
	* 返回值  ：无
	*/
	void CalculateLastTrainToAc(void);

	/*
	* 功能描述： 判断计轴区段是否满足纯非通信列车占用状态
	* 参数说明：无    
	* 返回值  ：无
	*/
	void ProcessAcUnCommTrainOccState(void);

	/*
	* 功能描述： 根据前方计轴区段信息计算当前计轴区段
	*			 是否满足纯非通信列车占用状态
	* 参数说明：const UINT8 dirFlag,方向标记(0x55:前方计轴,0xaa:后方计轴)
	*           const UINT16_S acId,计轴区段ID   
	*           const UINT16_S otherAcId,其他计轴区段ID（前方/后方计轴）
	*           const UINT8_S dir,方向信息
	* 返回值  ：1:已满足设置非通信列车占用状态
	*           0:不满足设置非通信列车占用状态
	*/
	UINT8_S JudgeAcUnCommTrainOccStateByOtherAc(const UINT8_S dirFlag,const UINT16_S acId,const UINT16_S otherAcId,const UINT8_S dir);

	/*
	* 功能描述： 处理单个计轴区段故障信息
	* 参数说明： const UINT16 acId  
	* 返回值  ： void  
	*/
	void InitFailureSingleAc(const UINT16_S acId);

	/*
	* 功能描述： 处理通信故障Ci对应的计轴区段信息
	* 参数说明： const UINT16 ciId，通信CiId    
	* 返回值  ： void  
	*/
	void InitFailureCiAc(const UINT16_S ciId);

	/*
	* 功能描述： 处理通信故障NZc对应的计轴区段信息
	* 参数说明： const UINT16 nZcId,通信ZcId    
	* 返回值  ： void  
	*/
	void InitFailureNZcAc(const UINT16_S nZcId);

	/*
	* 功能描述： 判断计轴区段是否有列车停稳
	* 参数说明： const UINT16 acId,计轴区段ID    
	* 返回值  ： 0:没有列车停稳
	*            1:有列车停稳
	*/
	UINT8_S JudgeAcStopStatus(const UINT16_S acId);
	
	/*
	* 功能描述： 清空计轴区段包含的列车序列信息
	* 参数说明： 无   
	* 返回值  ： 无
	*/
	void ClearTrainOrderInAc(void);

	/*
	* 功能描述： 判断计轴区段内的道岔是否满足锁闭和位置状态
	* 参数说明： const UINT16 acId,计轴区段ID
	* 返回值  ： 0:不满足
	*            1:满足
	*/
	UINT8_S JudgeSwitchLockAndPostionInAc(const UINT16_S acId);

	/*
	* 功能描述： 判断计轴区段内的道岔是否满足位置状态
	* 参数说明： const UINT16 acId,计轴区段ID
	*            UINT16_S outErrorSwitchId[AC_SWITCH_SUM_MAX],不满足条件的道岔数组
	*            ,UINT8_S *outErrorSwitchNum，不满足条件的道岔数量
	* 返回值  ： 0:不满足（其他原因）
	*            1:不满足（道岔原因）
	*            2:满足
	*/
	UINT8_S JudgeSwitchPostionInAc(const UINT16_S acId,UINT16_S outErrorSwitchId[AC_SWITCH_SUM_MAX],UINT8_S *outErrorSwitchNum);

	/*
	* 功能描述： 计轴ARB判断主函数
	* 参数说明： 无
	* 返回值  ： 无
	*/
	void JudgeAxleARB(void);

	/*
	* 功能描述： 若待判计轴已经判断为UT，当列车已经清扫该计轴后，将其转换为ARB
	* 参数说明： 无
	* 返回值  ： 无
	*/
	void ConvertAxleUtToArb(void);

	/*
	* 功能描述： 若待判计轴已经判断为ARB，当计轴占用状态变为空闲后，清除其ARB标志
	* 参数说明： 无
	* 返回值  ： 无
	*/
	void ConvertAxleArbToFree(void);

	/*
	* 功能描述： 判断计轴是否属于本ZC
	* 参数说明： const UINT16 acId
	* 返回值  ： RETURN_ERROR：失败
	*			 FLAG_SET：属于本ZC
	*			 FLAG_UNSET:不属于本ZC
	*/
	UINT8_S CheckAcAttribute(const UINT16_S acId);

	/*
	* 功能描述： 判断待判计轴两侧相邻计轴是否均满足ARB判断条件
	* 参数说明： const UINT16 checkedAcId
	* 返回值  ： 1：满足ARB条件
	*			 0：不满足ARB条件			 
	*/
	UINT8_S CheckAdjacentAxleArbCondition(const UINT16_S checkedAcId);

	/*
	* 功能描述： 待判计轴相邻计轴是否满足ARB条件
	* 参数说明： const UINT16  checkedAcId, 待判计轴ID
	*			 const UINT8_S direction，查询方向
	* 返回值  ： 0: 不满足ARB条件
	*			 1：满足ARB条件
	*/
	UINT8_S CheckOneSideAxleArbCondition(const UINT16_S checkedAcId,const UINT8_S direction);

	/*
	* 功能描述： 待判计轴相邻正常计轴是否满足ARB条件
	* 参数说明： const UINT16  checkedAcId, 待判计轴ID
	*			 const UINT16_S  adjacentAcId，相邻计轴ID
	*			 const UINT8_S dir, 方向
	* 返回值  ： 0: 不满足ARB条件
	*			 1：满足ARB条件
	*/
	UINT8_S CheckOneSideNormalAxleArbCondition(const UINT16_S checkedAcId,const UINT16_S adjacentAcId,const UINT8_S dir);

	/*
	* 功能描述： 待判计轴相邻四开计轴是否满足ARB条件
	* 参数说明： const UINT16  adjacentAcId[]，相邻计轴ID
	*            const UINT8_S adjacentAcNum,相邻计轴数量
	* 返回值  ： 0: 不满足ARB条件
	*			 1：满足ARB条件
	*/
	UINT8_S CheckOneSideLoseAxleArbCondition(const UINT16_S adjacentAcId[],const UINT8_S adjacentAcNum);

	/*
	* 功能描述： 计轴由RM列车清扫状态转换
	* 参数说明： 无
	* 返回值  ： 无
	*/
	void AcCleanStatusProcess(void);

	/*
	* 功能描述： 计轴清扫默认状态处理
	* 参数说明： const UINT16 acId
	* 返回值  ： 无
	*/
	void DefaultStatusProcess(const UINT16_S acId);

	/*
	* 功能描述： 计轴清扫车头已进入状态处理
	* 参数说明： const UINT16 acId
	*		     const UINT16_S trainId
	* 返回值  ： 无
	*/
	void HeadEntryStatusProcess(const UINT16_S acId,const UINT16_S trainId);


	/*
	* 功能描述： 计轴清扫车头出清状态处理
	* 参数说明： const UINT16 acId
	*		     const UINT16_S trainId
	* 返回值  ： 无
	*/
	void HeadOutStatusProcess(const UINT16_S acId,const UINT16_S trainId);

	/*
	* 功能描述： 计轴清扫车头车尾均出清状态处理
	* 参数说明： const UINT16 acId
	*		     const UINT16_S trainId
	* 返回值  ： 无
	*/
	void AllOutStatusProcess(const UINT16_S acId);

	/*
	* 功能描述： 若待判计轴有空闲变为占用，或者列车通过后维持占用，将其设置为冗余UT
	* 参数说明： 无
	* 返回值  ： 无
	*/
	void ConvertAxleFreetoUT(void);

	/*
	* 功能描述： 若待判计轴已经判断为ARB，当非通信列车接近或者占用该计轴后，将其转换为UT
	* 参数说明： 无
	* 返回值  ： 无
	*/
	void ConvertAxleArbToUt(void);

	/*
	* 功能描述： 若待判计轴已经判断为UT，当计轴占用状态变为空闲后，清除其UT标志
	* 参数说明： 无
	* 返回值  ： 无
	*/
	void ConvertAxleUtToFree(void);

	/*
	* 功能描述： 判断待判计轴两侧相邻计轴是否可满足UT判断条件
	* 参数说明： const UINT16 checkedAcId
	* 返回值  ： 1：满足UT条件
	*			 0：不满足UT条件			 
	*/
	UINT8_S CheckAdjacentAxleUtCondition(const UINT16_S checkedAcId);
	
	/*
	* 功能描述： 计轴UT判断主函数
	* 参数说明： 无
	* 返回值  ： 无
	*/
	void JudgeAxleUT(void);

	/*
	* 功能描述： 判断单个计轴区段是否位于计轴序列内
	* 参数说明： const UINT16 acId, 待查计轴
	*            const UINT8_S acOrderNum, 计轴序列数量
	*            const UINT16_S acOrderBuff[], 计轴序列
	* 返回值  ： 1：位于
	*			 0：不位于			 
	*/
	UINT8_S JudgeSingleAcInAcOrder(const UINT16_S acId,const UINT8_S acOrderNum,const UINT16_S acOrderBuff[]);

	/*
	* 功能描述： 计算输入的计轴是否满足道岔状态（锁闭和位置）
	* 参数说明： const UINT16 acId，计轴区段ID   
	* 返回值  ： 0:不满足条件
	*            1:满足条件
	*/
	UINT8_S CalulateSwtichStateOfAcIsNeed(const UINT16_S acId);

	/*
	* 功能描述： 遍历本ZC所有的计轴区段，如果包含道岔，且某一个计轴为UT，将其关联的ARB计轴设置为UT
	* 参数说明： 无   
	* 返回值  ： 无
	*/
	void ConvertSwitchAxleArbToUt(void);

	/*
	* 功能描述： 遍历道岔计轴区段，如果道岔区段某一个计轴为UT，将其关联的ARB计轴设置为UT
	* 参数说明： const UINT16 acId，计轴区段ID   
	* 返回值  ： 0:失败
	*            1:成功
	*/
	UINT8_S ConvertSingleSwitchAxleArbToUt(const UINT16_S acId);

	/*
	* 功能描述： 遍历道岔计轴区段，如果道岔区段某一个计轴为UT，将其关联的ARB计轴设置为UT
	* 参数说明： const UINT16 acId，计轴区段ID 
	*            UINT8_S *relatedAcNum,计轴区段数量
	*            UINT16_S relatedAcId[SWITCH_BELONG_AC_SUM_MAX*5],计轴区段数组
	* 返回值  ： 0:不满足条件
	*            1:满足条件
	*/
	UINT8_S CheckRelatedAcOfInputAc(const UINT16_S acId,UINT8_S *relatedAcNum,UINT16_S relatedAcId[SWITCH_BELONG_AC_SUM_MAX * 5U]);

	/*
     * 功能描述： 判断列车车身（非车头车尾）是否位于指定计轴上
     * 参数说明： const UINT16 trainId
			 const UINT16_S acId，计轴区段ID   
     * 返回值  ： 0:是被
     *            1:位于指定计轴
	 *		      2：不位于指定计轴
     */
	UINT8_S JudgeTrainBodyInAc(const UINT16_S trainId,const UINT16_S acId);

	/*
	* 功能描述： 判断当前计轴区段是否满足要求的道岔位置状态
	* 参数说明： const UINT16 acId 计轴Id
	* 返回值  ： 0: 不满足道岔状态
	*			 1: 满足道岔状态    
	*/
	UINT8_S JudgeAcOfSwitchPosInNeed(const UINT16_S acId);

	/*
	* 功能描述： 判断当前计轴区段道岔位置状态是否为四开状态
	* 参数说明： const UINT16 acId 计轴Id
	* 返回值  ： FLAG_UNSET: 非四开状态
	*			 FLAG_SET: 四开状态    
	*/
	UINT8_S CheckAcOfSwitchPosIsSK(const UINT16_S acId);

#ifdef __cplusplus
}
#endif

#endif
