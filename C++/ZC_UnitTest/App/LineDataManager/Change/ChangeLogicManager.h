
/********************************************************                                                                                                           
文 件 名： ChangeLogicManager.h
作    者： ZC组
创建时间： 2015.04.18
描述： 切换区域逻辑处理管理  
备注： 无  
********************************************************/ 

#ifndef CHANGE_LOGIC_MANAGER_H
#define CHANGE_LOGIC_MANAGER_H

#ifdef __cplusplus
extern "C" {
#endif

/*************************************************
函数名:  JudgeACIsChangeEnd    
功能描述: 检查输入计轴ID是否属于切换区域终端计轴
输入: const UINT16 acId 待判定计轴
        const UINT8_S dir 运行方向
输出: 无
返回值: RETURN_ERROR 失败
            FLAG_SET  属于
			FLAG_UNSET 不属于
*************************************************/
UINT8_S JudgeACIsChangeEnd(const UINT16_S acId,const UINT8_S dir);

/*************************************************
  函数名: JudgeAcIsInChangeLine     
  功能描述: 检查输入计轴ID是否属于沿指定方向切换区域
  输入: const UINT16 acId 待判定计轴   
       const UINT8_S trainDir 方向
  输出: 无
  返回值: RETURN_SUCESS  属于
			 RETURN_ERROR 不属于
*************************************************/
UINT8_S JudgeAcIsInChangeLine(const UINT16_S acId,const UINT8_S trainDir);

/*
* 功能描述： 计算切换区域内本ZC管辖范围内的逻辑区段信息
* 参数说明： UINT16_S *logicNum，
*            UINT16_S logicIdBuff[]
* 返回值  ： 1,计算成功
*            2,计算失败
*/
UINT8_S CalculatChangeAreaLogicInfoOfZc(UINT16_S zcId,UINT16_S *logicNum,UINT16_S logicIdBuff[]);

#ifdef __cplusplus
}
#endif

#endif 
