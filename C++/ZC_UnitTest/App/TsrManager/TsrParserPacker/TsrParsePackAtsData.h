/*******************************************
文件名	：TsrParsePackAtsData.h
作者	：董欣
创建时间：2016-10
描述	：ATS数据解析组包文件
备注	：无
*******************************************/

#ifndef TSR_PARSEPACK_ATS_DATA_H_
#define TSR_PARSEPACK_ATS_DATA_H_

#include "../../../Common/CommonTypes.h"
#include "../TsrAdministrator/TsrDataAdmin.h"
#include "../../../Common/CircQueueStruct.h"

#ifdef __cplusplus
extern "C" {
#endif

#define APPLENPOS_IN_REPLYTOATS 10U/*发往ZC的信息帧中 应用层数据长度距离起始字节的偏移量*/
#define MSGLENPOS_IN_REPLYTOATS 12U/*发往ZC的信息帧中 报文总长度距离起始字节的偏移量*/
#define LENGTH_FIELD_BYTES      2U/*长度字段所占字节数*/

/*ATS发送给ZC的动态数据信息结构体*/
typedef struct S_TSR_DATASTRU_FROMATS
{
	UINT32_S AtsID;/*ATS ID*/
	UINT32_S TargetID;/*目标ID*/
	UINT16_S AtsCmdType;/*ATS命令类型*/
	UINT16_S RandomNo;/*随机数*/
	Tsr_DataStru_Cell_Stru TsrCellData;/*ATS设置的单个临时限速信息*/
	UINT32_S Ats_Crc32;/*ATS发送的CRC信息*/
}Tsr_DataStru_FromAts;

/*ZC发送给ATS的数据信息结构体*/
typedef struct S_TSR_DATASTRU_TOATS
{
	UINT16_S msgType_res;/*应答报文类型：初始值0/正常值0x0072 0x0074 0x0091 0x0093 0x00A1 0x00A3/其他值非法/*/
	UINT16_S msgType_auto;/*主动汇报报文类型：初始值0/正常值0x0070 0x0080/其他值非法/*/
	UINT8_S replyCode;/*回应码*/
	Tsr_DataStru_Set_Stru TsrSetData;/*回复的临时限速信息*/
}Tsr_DataStru_ToATS;

/*******************************************
函数名	：GetAtsCmdType
功能描述：获取ATS发送过来的命令类型
输入	：无
输出	：无
返回值	：ATS发送过来的命令类型
*******************************************/
extern UINT16_S GetAtsCmdType(void);

/*******************************************
函数名	：GetLastTsrCellData
功能描述：获取首次操作的单个临时限速信息
输入	：无
输出	：无
返回值	：首次操作的单个临时限速信息
*******************************************/
extern Tsr_DataStru_Cell_Stru* GetLastTsrCellData(void);

/*******************************************
函数名	：ClearLastTsrCellData
功能描述：清空首次操作的单个临时限速信息
输入	：无
输出	：无
返回值	：无
*******************************************/
extern void ClearLastTsrCellData(void);

/*******************************************
函数名	：GetRcvFromAtsData
功能描述：获取ATS发来的数据信息结构体
输入	：无
输出	：无
返回值	：ATS发来的数据信息结构体
*******************************************/
extern Tsr_DataStru_FromAts* GetRcvFromAtsData(void);

/*******************************************
函数名	：ClearRcvFromAtsData
功能描述：清除ATS发来的数据信息结构体
输入	：无
输出	：无
返回值	：无
*******************************************/
extern void ClearRcvFromAtsData();

/*******************************************
函数名	：SetAtsCmdCrc32
功能描述：设置g_AtsCmdCrc32
输入	：UINT32_S crc32
输出	：无
返回值	：无
*******************************************/
extern void SetAtsCmdCrc32(UINT32_S crc32);

/*******************************************
函数名	：GetAtsSendTsrFsAndSsTime
功能描述：获取首次二次计时时间
输入	：无
输出	：无
返回值	：AtsSendTsrFsAndSsTime首次二次计时时间
*******************************************/
extern UINT16_S GetAtsSendTsrFsAndSsTime(void);

/*******************************************
函数名	：AddAtsSendTsrFsAndSsTime
功能描述：累加首次二次计时时间
输入	：无
输出	：无
返回值	：无
*******************************************/
extern void AddAtsSendTsrFsAndSsTime(void);

/*******************************************
函数名	：SetAtsSendTsrFsAndSsTime
功能描述：设置首次二次计时时间
输入	：fsAndSsTime首次二次计时时间
输出	：无
返回值	：无
*******************************************/
extern void SetAtsSendTsrFsAndSsTime(UINT16_S fsAndSsTime);

/*******************************************
函数名	：GetTsrCellDataFromAts
功能描述：获取ATS发送的临时限速信息
输入	：无
输出	：无
返回值	：ATS发送的临时限速信息
*******************************************/
extern Tsr_DataStru_Cell_Stru* GetTsrCellDataFromAts(void);

/*******************************************
函数名	：SetLastAtsCmdType
功能描述：设置ATS最近一次命令类型
输入	：lastCmdTypeATS最近一次命令类型
输出	：无
返回值	：无
*******************************************/
extern void SetLastAtsCmdType(UINT8_S lastCmdType);

/*******************************************
函数名	：SetReplyToAtsAutoCmdValue
功能描述：设置 主动回复ATS的命令信息值
          包括：重启汇报/正常汇报
输入	：回复ATS的命令信息值
输出	：无
返回值	：无
*******************************************/
extern void SetReplyToAtsAutoCmdValue(UINT8_S replyToAtsCmd);

/*******************************************
函数名	：WriteReplyToAtsData
功能描述：写临时限速信息到 发送给ZC的数据结构
输入	：无
输出	：无
返回值	：无
*******************************************/
extern void WriteReplyToAtsData(const Tsr_DataStru_Set_Stru* tsrDataStru);

/*******************************************
函数名	：ClearReplyToAtsData
功能描述：清空 向ATS发送的数据信息结构体
输入	：无
输出	：无
返回值	：无
*******************************************/
extern void ClearReplyToAtsData(void);

/*******************************************
函数名	：CheckAtsInputData
功能描述：检查ATS输入数据的合法性
输入	：无
输出	：无
返回值	：0失败，1成功
*******************************************/
extern UINT8_S CheckAtsInputData(void);


/*******************************************
函数名	：ParseRcvFromAtsDataFrame
功能描述：解析ATS发送来的数据帧
输入	：const UINT8_S* dataBuf, 数据缓冲区
		  const UINT16_S dataLength, 数据长度
输出	：无
返回值	：0: 数据解析失败
		  1: 数据解析成功
*******************************************/
extern UINT8_S ParseRcvFromAtsDataFrame(const UINT8_S* dataBuf, const UINT16_S dataLength);

/*******************************************
函数名	：PackReplyToAtsData
功能描述：组包ATS数据
输入	：无
输出	：无
返回值	：0：失败；1：成功
*******************************************/
extern UINT8_S PackReplyToAtsData(void);

/*******************************************
函数名	：CalcCrc
功能描述：计算ATS发送过来命令的CRC值
输入	：无
输出	：无
返回值	：计算的CRC值
*******************************************/
extern UINT32_S CalcCrc(void);


/*******************************************
函数名  : GetReplyToAtsDataStru
功能描述：获取发往ATS数据信息结构体
输入    ：无
输出    ：无
返回值	：replyToAtsData  发往ATS数据信息结构体
*******************************************/
extern Tsr_DataStru_ToATS* GetReplyToAtsDataStru(void);

#ifdef __cplusplus
}
#endif
#endif