/*******************************************
文件名	：DmuDataHandle.c
作者	：董欣
创建时间：2016-10
描述	：DSU查询函数
备注	：无
*******************************************/
#include "DmuDataHandle.h"
#include "../../../../Dmu/DmuComm/DataHandle/DmuCommDataHandle.h"
#include "../../../../Common/Convert.h"
#include "../../../../Common/Malloc.h"
#include "../../../../Common/MemSet.h"
#include "../../../../Dmu/DmuComm/DataHandle/DmuCommDataTypeDefine.h"
#include "../../../../Dmu/DmuComm/Data/StaticResSpeedData.h"
#include "../../../../Dmu/DmuComm/Data/LogicSectionData.h"
#include "../../../../Dmu/DmuComm/Data/AxleSectionData.h"
#include "../../../../Dmu/DmuComm/Data/SwitchData.h"
#include "../../../../Dmu/Read/ReadManage.h"
#include "../../../../Dmu/DmuComm/Load/LoadManage.h"
#include "../../TsrAdministrator/TsrDataAdmin.h"

/********************************内部使用函数START****************************/
static UINT8_S OrderLogicSgmt(const UINT16_S* pLogicId,UINT16_S logicNum,UINT16_S *orderpLogicId);
static UINT16_S CheckSingleLogicSgmtTSRSpeed(UINT16_S pLogicId);
static UINT8_S  CheckLastTsrValid(const UINT16_S* pLogicId,const UINT8_S logicNum);
static  UINT8_S CheakTwoLogicRule(BnfLogicSectionStruct *tempLogicSgmt1,BnfLogicSectionStruct *tempLogicSgmt2);

/********************************内部使用函数END******************************/


/*******************************************
函数名	：CheckLogicRealteZc
功能描述：查询出逻辑区段涉及到ZC的ID
输入	：UINT16* logicIds,   逻辑区段ID
		  UINT8 logicNum,     逻辑区段个数
		  UINT8 maxZcNum,     ZC数量
输出	：UINT8* pRelateZcId, 包含ZCID的数组(注：逻辑区段属于哪个ZC，就把相应ZCID写进此数组)
返回值	：1:成功，	0:失败
*******************************************/
UINT8_S CheckLogicRealteZc(const UINT16_S* logicIds, UINT8_S logicNum, UINT8_S maxZcNum, UINT8_S* pRelateZcId,UINT8_S *relateZcNum)
{
	UINT8_S retVal = DEFAULT_ZERO;/*函数返回值*/
	UINT8_S isFlag = 1u;/*1 检查通过  0 检查未通过*/
	UINT16_S i;    /*循环用变量*/
	UINT16_S j = DEFAULT_ZERO;/*循环用变量*/
	BnfLogicSectionStruct* pTempLogicSgmtStr = NULL;  /*用于静态数据库中的逻辑区段结构体指针*/
	BnfSegStruct* pTempSegStru = NULL; /*用于静态数据库中的Seg索引指针*/
	UINT8_S tempZCtndex = DEFAULT_ZERO;           /*用于ZC索引*/

	if(( logicIds != NULL )&&( pRelateZcId != NULL)&&(relateZcNum != NULL)&&( logicNum <= LOGIC_MAX_NUM ))		/*MQH*/
	{
		/*循环清空每一个ZCIds的包含状态*/
		for(i=DEFAULT_ZERO;i<maxZcNum;i++)
		{
			pRelateZcId[i]=DEFAULT_ZERO;
		}

		for (j=DEFAULT_ZERO;j<logicNum;j++)
		{
			/*根据当前逻辑区段的id获取逻辑区段结构体信息*/
			pTempLogicSgmtStr = GetIndexIdLogicSectionDataStru(logicIds[j]);
			if (NULL == pTempLogicSgmtStr)
			{
				/*循环清空每一个ZCIds的包含状态*/
				for(i=DEFAULT_ZERO;i<maxZcNum;i++)
				{
					pRelateZcId[i]=DEFAULT_ZERO;
				}
				retVal = DEFAULT_ZERO;
				isFlag = DEFAULT_ZERO;

			}

			if (1u == isFlag)
			{
				/*根据逻辑区段结构体获取逻辑区段起点Seg的结构体*/
				pTempSegStru = GetIndexIdSegDataStru(pTempLogicSgmtStr->startSegId);

				/*根据输入参数检查ZCIndex是否合法*/
				if (pTempSegStru->segManageZCId <= maxZcNum)
				{
					pRelateZcId[tempZCtndex]=(UINT8_S)(pTempSegStru->segManageZCId);
		            tempZCtndex++;

				}
				else
				{
					/*循环清空每一个ZCIds的包含状态*/
					for(i=DEFAULT_ZERO;i<maxZcNum;i++)
					{
						pRelateZcId[i]=DEFAULT_ZERO;
					}

					retVal = DEFAULT_ZERO;
					isFlag = DEFAULT_ZERO;

				}
				if(DEFAULT_ZERO == isFlag)
				{
					break;
				}
			}
			
		}

		if (1u == isFlag)
		{
			retVal = 1u;
			*relateZcNum = tempZCtndex;
		}
	}
	else
	{
		/*不处理 */
	}
	
	return retVal;
}

/*******************************************
函数名	：CheckSingleTSRSpeedValid
功能描述：判断临时限速数值是否高于设置的临时限速涉及到的逻辑区段的线路设计最高限速值
输入	：UINT16* pLogicId   逻辑区段ID
		  UINT8 logicNum     逻辑区段数量
		  UINT8 speed       设定临时限速速度
输出    ：无
返回值	：2    设置的临时限速数值高于某一个逻辑区段的线路设计最高限速值
		  1    设置的临时限速数值没有高于任何一个逻辑区段的线路设计最高限速值
		  0    查询失败（除以上两种情况，其它均视为查询失败）
*******************************************/
UINT8_S CheckSingleTSRSpeedValid(const UINT16_S* pLogicId,UINT8_S logicNum,UINT8_S speed)
{
	UINT8_S retVal = DEFAULT_ZERO;/*函数返回值*/
	UINT8_S isFlag = 1u;/*1 检查通过  0 检查未通过*/
	UINT8_S i = DEFAULT_ZERO;/*循环使用*/
	UINT16_S tmpLogicSgmtTsrSpeed = DEFAULT_ZERO;/*临时变量：单个逻辑区段所对应的静态限速*/

	if( pLogicId != NULL )
	{
		/*如果临时限速中逻辑区段数量大于最大值，查询失败*/
		if (logicNum > LOGIC_MAX_NUM)
		{
			isFlag = DEFAULT_ZERO;
		}

		for (i=DEFAULT_ZERO;(i<logicNum)&&(1u == isFlag);i++)
		{
			/*查询单个逻辑区段的静态临时限速值*/
			tmpLogicSgmtTsrSpeed=CheckSingleLogicSgmtTSRSpeed(pLogicId[i]);
			/********test******/
			/*tmpLogicSgmtTsrSpeed = 2222;*/
			/*************/
			if (tmpLogicSgmtTsrSpeed != DEFAULT_ZERO)
			{	/*查询成功，返回静态临时限速值,这里需要速度换算*/
				/*chTSRSpeed的单位为km/h,tmpLogicSgmtTsrSpeed的单位为cm/s*/
				if ((FLOAT32_S)speed > ((FLOAT32_S)tmpLogicSgmtTsrSpeed * 0.036))
				{	/*设置的临时限速数值高于某一个逻辑区段的线路设计最高限速值，跳出循环*/
					retVal = 2u;
					break;
				} 
			}
			else
			{	/*查询失败,跳出循环*/
				retVal = DEFAULT_ZERO;
				break;
			}

		}

		if (i == logicNum)
		{
			/*设置的临时限速数值没有高于任何一个逻辑区段的线路设计最高限速值*/
			retVal=1u;
		}
	}
	else
	{
		/*不处理 */
	}
	return retVal;
}

/*******************************************
函数名	：CheckSingleLogicSgmtTSRSpeed
功能描述：求单个逻辑区段的静态限速值
输入	：UINT16 pLogicId  逻辑区段id
输出	：无
返回值	：0x00: 查询失败；
		  !0: 该逻辑区段所对应的静态限速值;
*******************************************/
static UINT16_S CheckSingleLogicSgmtTSRSpeed(UINT16_S pLogicId)
{
	UINT16_S retVal = DEFAULT_ZERO;
	BnfLogicSectionStruct *logicSgmtStru = NULL;
	UINT16_S tempLimitSpeed = DEFAULT_ZERO;/*限速值*/
	UINT16_S retLimitSpeed = DEFAULT_ZERO;/*返回的临时限速值*/
	UINT8_S i = DEFAULT_ZERO;/*循环使用*/

	/*利用管理函数找到逻辑区段表*/
	logicSgmtStru = GetIndexIdLogicSectionDataStru(pLogicId);

	if (NULL != logicSgmtStru)
	{
		if (logicSgmtStru->startSegId == logicSgmtStru->endSegId)
		{
			retVal = GetSegIdOfLimitSpeed(logicSgmtStru->startSegId,logicSgmtStru->startSegOffset,logicSgmtStru->endSegOffset,&tempLimitSpeed);
			retLimitSpeed = tempLimitSpeed;
		}
		else
		{
			/*获取起点SEG的限速值*/
			retVal = GetSegIdOfLimitSpeed(logicSgmtStru->startSegId,logicSgmtStru->startSegOffset,GetSegDataStrulength(logicSgmtStru->startSegId),&tempLimitSpeed);

			if (1u == retVal)
			{
				retLimitSpeed = tempLimitSpeed;
				for (i = DEFAULT_ZERO; i < logicSgmtStru->includeSegIdNum; i++)
				{
					if ((logicSgmtStru->segIdBuff[i] == logicSgmtStru->startSegId)||(logicSgmtStru->segIdBuff[i] == logicSgmtStru->endSegId))
					{
					    /* Do nothing */
					}
					else
					{
						retVal = GetSegIdOfLimitSpeed(logicSgmtStru->segIdBuff[i],DEFAULT_ZERO,GetSegDataStrulength(logicSgmtStru->segIdBuff[i]),&tempLimitSpeed);
						if ((1u == retVal)&&(tempLimitSpeed < retLimitSpeed))
						{
							retLimitSpeed = tempLimitSpeed;
						}
					}
				}
			}

			/*获取终点SEG的限速值*/
			retVal = GetSegIdOfLimitSpeed(logicSgmtStru->endSegId,DEFAULT_ZERO,logicSgmtStru->endSegOffset,&tempLimitSpeed);
			if ((1u == retVal)&&(tempLimitSpeed < retLimitSpeed))
			{
				retLimitSpeed = tempLimitSpeed;
			}
		}

	}


	return retLimitSpeed;
}

/*******************************************
函数名	：CheckSingleTsrLogicIdsValid
功能描述：判断临时限速区域内逻辑区段的有效性
输入	：UINT16* pLogicId   逻辑区段ID
		  UINT8 logicNum     逻辑区段数量
输出	：无
返回值	：1: 该临时限速内同时包含了同一道岔的定位和反位；
		  2: 该临时限速内的逻辑区段不连续;
		  3: 该临时限速内存在ID不合法的逻辑区段;
		  4: 其他原因失败
		  0:成功
*******************************************/
UINT8_S CheckSingleTsrLogicIdsValid(UINT16_S* pLogicId,UINT8_S logicNum)
{
	UINT8_S retVal = DEFAULT_ZERO;/*函数返回值*/
	UINT16_S orderpLogicId[LOGIC_MAX_NUM] = {DEFAULT_ZERO};

	/*临时限速区逻辑区段个数超标*/
	if((pLogicId != NULL ) && (logicNum <= LOGIC_MAX_NUM))
	{
		/*判断设置的临时限速区逻辑区段是否和以前设置的发生规则冲突*/
		retVal = CheckLastTsrValid(pLogicId,logicNum);
		if( 0u == retVal)
		{
			/*判断设置的临时限速区逻辑区段是否发生规则冲突*/
			retVal = OrderLogicSgmt(pLogicId,(UINT16_S)logicNum,orderpLogicId);
		}
		
	}

	return retVal;
}

/*******************************************
函数名	：OrderLogicSgmt
功能描述：给逻辑区段序列排序
输入	：UINT16 pLogicId[DSU_TSRSECTIOM_NUM]  待排序序列
		  UINT16 logicNum             待排序逻辑区段个数
输出	:UINT16 *OrderpLogicId   排序后的序列
输出	：UINT16 *OrderpLogicId   排序后的序列
返回值	：1: 该临时限速内同时包含了同一道岔的定位和反位；
		  2: 该临时限速内的逻辑区段不连续;
		  3: 该临时限速内存在ID不合法的逻辑区段;
		  4: 其他原因失败
		  0:成功
*******************************************/
static UINT8_S OrderLogicSgmt(const UINT16_S* pLogicId,UINT16_S logicNum,UINT16_S *orderpLogicId)
{
	UINT8_S i,j;    /*循环变量*/
	UINT8_S errorRetVal = DEFAULT_ZERO;/*1 有错误返回 0 无错误返回*/
	BnfLogicSectionStruct *logicSgmtAhead,*logicSgmtRear,*tLogicSgmt;   /*逻辑区段临时变量*/
	BnfLogicSectionStruct *tempLogicSgmt1,*tempLogicSgmt2;   /*逻辑区段临时变量*/
	BnfAxleSectionStruct  *tempAxleSgmt1,*tempAxleSgmt2;

	UINT8_S bReturnValue = 4u;
	UINT8_S tmpNum;	/*循环变量--用于遍历计轴区段相邻计轴区段*/
	const UINT8_S AxlelogicNum = 3u;	/*计轴区段相邻计轴区段数量，最大为3*/

	UINT8_S isFind;
	UINT8_S aheadFlag= 1u;
	UINT8_S rearFlag= 1u;
	UINT16_S logicSgmeCount;
	UINT16_S logicLineNum = DEFAULT_ZERO;/*逻辑区段行数*/
	
	if(( pLogicId != NULL) && ( orderpLogicId != NULL ) && ( logicNum <= LOGIC_MAX_NUM))
	{
		tempLogicSgmt1 = GetLogicSectionDataInfo(&logicLineNum);	/*获取逻辑区段的行数及数据*/
		/*判断待排序的逻辑区段序列中任意两个逻辑区段是否包含了同一道岔的定位和反位*/
		for(i=DEFAULT_ZERO;i<(logicNum-1u)&&(DEFAULT_ZERO == errorRetVal);i++)
		{
			tempLogicSgmt1 = GetIndexIdLogicSectionDataStru(pLogicId[i]);
			for(j=i+1u;j<logicNum;j++)
			{
				tempLogicSgmt2 =  GetIndexIdLogicSectionDataStru(pLogicId[j]);
				/*两逻辑区段不属于同一记轴区段且有重合link时，必同时包含了同一道岔的定位和反位*/
				if(tempLogicSgmt1->belongAxleSecId != tempLogicSgmt2->belongAxleSecId)
				{
					if((tempLogicSgmt1->startSegId == tempLogicSgmt2->startSegId)
						|| (tempLogicSgmt1->endSegId == tempLogicSgmt2->endSegId))
					{
						/*返回错误码*/
						bReturnValue = 1u;
						errorRetVal = 1u;
						break;
					}
				}
			}
		}
		/*找到最前端逻辑区段*/
		logicSgmtAhead = GetIndexIdLogicSectionDataStru(pLogicId[0]);
		tLogicSgmt = logicSgmtAhead;
		while((DEFAULT_ZERO == errorRetVal)&&(aheadFlag))
		{
			tempAxleSgmt1 = GetIndexIdAxleSectionDataStru(logicSgmtAhead->belongAxleSecId);
			/*logicSgmtAhead为所在计轴区段的第一个逻辑区段*/
			if(logicSgmtAhead->indexId == tempAxleSgmt1->logicSecId[0])
			{
				/*标记设为0*/
				isFind = DEFAULT_ZERO;
				/*遍历logicSgmtAhead为所在计轴区段的起点相邻计轴区段数组*/
				for (tmpNum=DEFAULT_ZERO;tmpNum<AxlelogicNum;tmpNum++)
				{
					/*计轴区段存在*/
					if (tempAxleSgmt1->orgnAxleSgmtId[tmpNum] != UINT16_MAX)
					{

						/*tempAxleSgmt2为相邻前一个计轴区段*/
						tempAxleSgmt2 = GetIndexIdAxleSectionDataStru(tempAxleSgmt1->orgnAxleSgmtId[tmpNum]);
						/*设tLogicSgmt为相邻前一个计轴区段的最一个逻辑区段*/
						/*当有道岔存在时，逻辑区段和计轴区段为同一个*/
						tLogicSgmt = GetIndexIdLogicSectionDataStru(tempAxleSgmt2->logicSecId[tempAxleSgmt2->includeLogicAxleSecNum-1u]);
						/*遍历数组，如果tLogicSgmt逻辑区段是否在输入的数组中，寻找标志设为1*/

						for(i=DEFAULT_ZERO;i<logicNum;i++)
						{
							/*在的话，往前继续寻找，寻找标记设为1*/
							if(tLogicSgmt->indexId == pLogicId[i])
							{
								logicSgmtAhead = tLogicSgmt;
								isFind = 1u;
								break;
							}
						}

					} 
					else
					{
						/*继续下一个起点相邻计轴区段*/
					}
				}
				/*有两种清空下isfind==0：
				1.当起点端相邻计轴区段全部为0xffff--即为线路起点
				2.不全为0xffff--非线路起点
				当计轴区段处于线路中时，计轴区段的最后一个逻辑区段都不在待排序的逻辑区段序列中*/
				if (isFind == DEFAULT_ZERO)
				{ 
					/*退出while循环*/
					aheadFlag = DEFAULT_ZERO;
					break;
				} 
				else
				{
					/*没有找到第一个逻辑区段，继续*/
				}
			}

			else
			{
				/*tLogicSgmt为起始端相邻逻辑区段*/
				tLogicSgmt = GetIndexIdLogicSectionDataStru(logicSgmtAhead->mainOrgnLogicSgmtId);
				/*遍历数组，看tempLogicSgmt逻辑区段是否在输入的数组中*/
				isFind = DEFAULT_ZERO;
				for(i=DEFAULT_ZERO;i<logicNum;i++)
				{
					/*在的话，往前继续寻找*/
					if(tLogicSgmt->indexId == pLogicId[i])
					{
						logicSgmtAhead = tLogicSgmt;
						isFind = 1u;
						break;
					}
				}
				if(DEFAULT_ZERO == isFind)
				{
					/*找到了最前端*/
					aheadFlag = DEFAULT_ZERO;
				}
			}
		}

		logicSgmeCount = DEFAULT_ZERO;
		orderpLogicId[logicSgmeCount] = logicSgmtAhead->indexId;
		logicSgmtRear = logicSgmtAhead;
		tLogicSgmt = logicSgmtAhead;
		/*向尾端找*/
		while((DEFAULT_ZERO == errorRetVal)&&(rearFlag))
		{
			tempAxleSgmt1 = GetIndexIdAxleSectionDataStru(logicSgmtRear->belongAxleSecId);
			/*logicSgmtRear为所在计轴区段的最后一个逻辑区段*/
			if(logicSgmtRear->indexId == tempAxleSgmt1->logicSecId[tempAxleSgmt1->includeLogicAxleSecNum-1u])
			{
				/*标记设为0*/
				isFind = DEFAULT_ZERO;
				/*遍历logicSgmtAhead为所在计轴区段的起点相邻计轴区段数组*/
				for (tmpNum=DEFAULT_ZERO;tmpNum<AxlelogicNum;tmpNum++)
				{
					/*计轴区段存在*/
					if (tempAxleSgmt1->tmnlAxleSgmtId[tmpNum] != UINT16_MAX)
					{
						/*tempAxleSgmt2为相邻后一个计轴区段*/
						tempAxleSgmt2 = GetIndexIdAxleSectionDataStru(tempAxleSgmt1->tmnlAxleSgmtId[tmpNum]);
						/*设tLogicSgmt为相邻后一个计轴区段的第一个逻辑区段*/
						/*当有道岔存在时，逻辑区段和计轴区段为同一个*/
						tLogicSgmt = GetIndexIdLogicSectionDataStru(tempAxleSgmt2->logicSecId[0]);
						/*遍历数组，如果tLogicSgmt逻辑区段是否在输入的数组中，寻找标志设为1*/

						for(i=DEFAULT_ZERO;i<logicNum;i++)
						{
							/*在的话，往后继续寻找，寻找标记设为1*/
							if(tLogicSgmt->indexId == pLogicId[i])
							{
								logicSgmtRear = tLogicSgmt;
								logicSgmeCount++;
								orderpLogicId[logicSgmeCount] = logicSgmtRear->indexId;
								isFind = 1u;
								break;
							}
						}

					} 
					else
					{
						/*继续下一个起点相邻计轴区段*/
					}
				}
				/*有两种清空下isfind==0：
				1.当起点端相邻计轴区段全部为0xffff--即为线路起点
				2.不全为0xffff--非线路起点
				当计轴区段处于线路中时，计轴区段的最后一个逻辑区段都不在待排序的逻辑区段序列中*/
				if (isFind == DEFAULT_ZERO)
				{ 
					/*退出while循环*/
					rearFlag = DEFAULT_ZERO;
					break;
				} 
				else
				{
					/*没有找到最后一个逻辑区段，继续*/
				}
			}

			else
			{
				/*tLogicSgmt为终端相邻逻辑区段*/
				tLogicSgmt = GetIndexIdLogicSectionDataStru(logicSgmtRear->mainTmnlLogicSgmtId);
				/*遍历数组，看tempLogicSgmt逻辑区段是否在输入的数组中*/
				isFind = DEFAULT_ZERO;
				for(i=DEFAULT_ZERO;i<logicNum;i++)
				{
					/*在的话，往后延*/
					if(tLogicSgmt->indexId == pLogicId[i])
					{
						logicSgmtRear = tLogicSgmt;
						logicSgmeCount++;
						orderpLogicId[logicSgmeCount] = logicSgmtRear->indexId;
						isFind = 1u;
						break;
					}
				}
				if(DEFAULT_ZERO == isFind)
				{
					/*找到了最后端*/
					rearFlag = DEFAULT_ZERO;
				}
			}
		}

		if(DEFAULT_ZERO == errorRetVal)
		{
			if(logicNum==(logicSgmeCount+1u))
			{
				/*下脚标+1 = 个数*/
				bReturnValue = DEFAULT_ZERO;
				
			}
			else
			{
				/*返回错误码*/
				bReturnValue = 2u;
			}
		}
	}
	else
	{
		/*返回错误码*/
		bReturnValue = 4u;
	}
	return bReturnValue;
}

/*******************************************
函数名	：	CheckLastTsrValid
功能描述：  新设置的逻辑区段是否与已设置的逻辑区段存在规则抵触
输入	：  UINT16 pLogicId[DSU_TSRSECTIOM_NUM]  待排序序列
            UINT8_S logicNum             待排序逻辑区段个数	
输出	:   无
返回值	：  1: 该临时限速与与已设置的逻辑区段同一道岔的定位和反位；
		    0:成功
*******************************************/
static UINT8_S  CheckLastTsrValid(const UINT16_S* pLogicId,const UINT8_S logicNum)
{
	Tsr_DataStru_Set_Stru* tempTsrDataStru = NULL;
	BnfLogicSectionStruct *tempLogicSgmt1,*tempLogicSgmt2;   /*逻辑区段临时变量*/
	UINT8_S ii = DEFAULT_ZERO;
	UINT8_S jj = DEFAULT_ZERO;
	UINT8_S kk = DEFAULT_ZERO;
	UINT16_S waitLogicNum = DEFAULT_ZERO;
	UINT8_S retValue = DEFAULT_ZERO;
	UINT8_S retRule = 0u;
	UINT8_S isFalg = 1u;

	if(( pLogicId != NULL)&&(logicNum <= LOGIC_MAX_NUM ))
	{
		tempTsrDataStru = GetTsrDataAdmin();
		/*判断待存的逻辑数目大于要设置的逻辑的数目，把最大的循环体放在里面*/
		if(waitLogicNum <= logicNum)
		{
			for(ii = DEFAULT_ZERO;ii < (tempTsrDataStru->TsrQuan)&&(isFalg == 1u);ii++)
			{
				for(jj = DEFAULT_ZERO;(jj < tempTsrDataStru->CellTsrData[ii].LogicSecQuan)&&(isFalg == 1u);jj++)
				{
					tempLogicSgmt1 = GetIndexIdLogicSectionDataStru(tempTsrDataStru->CellTsrData[ii].LogicSecId[jj]);
				
					for(kk = DEFAULT_ZERO;(kk < logicNum)&&(isFalg == 1u);kk++)
					{
						tempLogicSgmt2 =  GetIndexIdLogicSectionDataStru(pLogicId[kk]);
						/*两逻辑区段不属于同一记轴区段且有重合link时，必同时包含了同一道岔的定位和反位*/
						retRule = CheakTwoLogicRule(tempLogicSgmt1,tempLogicSgmt2);
						if( retRule == 1u)
						{
							isFalg =0u;
							retValue = 1u ;
						}						
					}

				}
	
			}
		}
		else
		{
			for(ii = DEFAULT_ZERO;(ii < logicNum)&&(isFalg == 1u);ii++)
			{
				tempLogicSgmt1 =  GetIndexIdLogicSectionDataStru(pLogicId[ii]);

				for(jj = DEFAULT_ZERO;jj < (tempTsrDataStru->TsrQuan)&&(isFalg == 1u);jj++)
				{
					for(kk = DEFAULT_ZERO;(kk < tempTsrDataStru->CellTsrData[jj].LogicSecQuan)&&(isFalg == 1u);kk++)
					{
						tempLogicSgmt2 = GetIndexIdLogicSectionDataStru(tempTsrDataStru->CellTsrData[jj].LogicSecId[kk]);
						/*两逻辑区段不属于同一记轴区段且有重合link时，必同时包含了同一道岔的定位和反位*/
						retRule = CheakTwoLogicRule(tempLogicSgmt1,tempLogicSgmt2);
						if( retRule == 1u)
						{
							isFalg =0u;
							retValue = 1u ;
						}	
					}
				}
			}
		
		}
	
	}
	return retValue;
}

/*******************************************
函数名  ：	CheakTwoLogicRule
功能描述：  判断是否为同一道岔的定位和反位
输入    ：  BnfLogicSectionStruct *tempLogicSgmt1  逻辑区段表数据结构体
			BnfLogicSectionStruct *tempLogicSgmt2  逻辑区段表数据结构体
输出    :   无
返回值  ：  0 不为同一道岔的定位和反位
			1 是同一道岔的定位和反位
*******************************************/
static  UINT8_S CheakTwoLogicRule(BnfLogicSectionStruct *tempLogicSgmt1,BnfLogicSectionStruct *tempLogicSgmt2)
{
	UINT8_S  retValue =0u;
	/*两逻辑区段不属于同一记轴区段且有重合link时，必同时包含了同一道岔的定位和反位*/
	if(tempLogicSgmt1->belongAxleSecId != tempLogicSgmt2->belongAxleSecId)
	{
		if((tempLogicSgmt1->startSegId == tempLogicSgmt2->startSegId)
			|| (tempLogicSgmt1->endSegId == tempLogicSgmt2->endSegId))
		{
			retValue = 1u ;
		}
	}
	return retValue;
}

