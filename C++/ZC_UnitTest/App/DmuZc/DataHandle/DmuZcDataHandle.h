/*******************************************
* 文件名	：  DmuZcDataHandle.h
* 作  者	：  ZC组
* 创建时间	：  2015-5-25
* 功能描述	：	ZC查询函数
* 备  注	：  无
*******************************************/
#ifndef DMU_ZC_DATAHANDLE_H_
#define DMU_ZC_DATAHANDLE_H_

#include "../../../Common/CommonTypes.h"

#define LXS_MA_SEC_SUP_MAX_NUM						5U								/*临时限速区域与MA区域重合部分的最大分段区域个数*/			


#ifdef __cplusplus
extern "C" {
#endif

/*区域信息结构体定义*/
typedef struct AreaInfoStruct
{
	UINT16_S  startSegId;						/*起点SEGID*/
	UINT32_S  startSegOffSet;					/*起点SEG偏移量*/
	UINT16_S  endSegId;						/*终点SEGID*/
	UINT32_S  endSegOffSet;					/*终点SEG偏移量*/
}AreaInfoStruct;

/*******************************************
* 函数名	： ZcBnfDataInit
* 功能描述: 初始化ZC数据文件
* 参数说明：UINT8* bnfFileAddr   二进制文件的地址
* 返回值：1:成功，	0:失败
*/
INT8_S ZcBnfDataInit(CHAR_S* bnfFileAddr);

/*******************************************
* 函数名	： GetLineOverlapOfSwitchNum
* 功能描述： 获取保护区段包含的道岔数量
* 参数说明： const UINT16 overlapId,保护区段ID
* 返回值  ： 0xffff: 获取数据失败
*			>0:道岔数量
*/
UINT16_S GetLineOverlapOfSwitchNum(const UINT16_S overlapId);

/*******************************************
* 函数名	： GetLineRouteOfObsInfo
* 功能描述： 获取进路对应信号机ID
* 参数说明： const UINT16 routeId,进路ID
*            UINT16_S obsInfoBuf[]，障碍物信息数组（id,类型）
* 返回值  ： 0xffff: 获取数据失败
*			>=0:障碍物数量(道岔，PSD,ESB)
*/
UINT16_S GetLineRouteOfObsInfo(const UINT16_S routeId,UINT16_S obsInfoBuf[]);

/*******************************************
* 函数名	： GetLineSignalDefaultStatus
* 功能描述： 获取线路信号机默认状态
* 参数说明： const UINT16 signalId,信号机ID
* 返回值  ： 0: 获取数据失败
*			0x55/0xaa:默认状态
*/
UINT16_S GetLineSignalDefaultStatus(const UINT16_S signalId);


/*******************************************
* 函数名	： GetLineCbtcLightOffType
* 功能描述： 获取线路信号机CBTC列车亮灭类型(预留)
* 参数说明： const UINT16 signalId,信号机ID
* 返回值  ： 0: 获取数据失败
*			0x55/0xaa:CBTC列车亮灭类型
*/
UINT8_S GetLineCbtcLightOffType(const UINT16_S signalId);

/*******************************************
* 函数名	： GetLineCrossType
* 功能描述： 获取线路信号机跨压类型(预留)
* 参数说明： const UINT16 signalId,信号机ID
* 返回值  ： 0: 获取数据失败
*			0x55/0xaa:跨压类型
*/
UINT8_S GetLineCrossType(const UINT16_S signalId);

/*******************************************
* 函数名	： GetLineCrashType
* 功能描述： 获取线路信号机闯信号类型
* 参数说明： const UINT16 signalId,信号机ID
* 返回值  ： 0: 获取数据失败
*			0x55/0xaa:闯信号类型
*/
UINT16_S GetLineCrashType(const UINT16_S signalId);

/*******************************************
* 函数名	： GetLineSwitchPosition
* 功能描述： 获取线路道岔位置信息（车辆段/正线）
* 参数说明： const UINT16 switchId,道岔ID
* 返回值  ： 0: 获取数据失败
*			0xaa/0x55:车辆段/正线
*/
UINT8_S GetLineSwitchPosition(const UINT16_S switchId);


/*******************************************
* 函数名	： GetLineAcType
* 功能描述： 获取计轴区段类型
* 参数说明： const UINT16 acId，计轴区段ID
* 返回值  ： 0: 获取失败
*			0x55-正线联锁计轴;0xaa-车辆段联锁计轴
*/
UINT8_S GetLineAcType(const UINT16_S acId);

/*******************************************
* 函数名	： GetLineAcIncludeSwitchInfo
* 功能描述： 获取计轴区段包含道岔信息
* 参数说明： const UINT16 acId，计轴区段ID
*            UINT8_S *switchNum,道岔数量
*            UINT16_S switchIdBuf[]，道岔ID数组
* 返回值  ： 0: 获取失败
*		    1: 获取成功
*/
UINT8_S GetLineAcIncludeSwitchInfo(const UINT16_S acId,UINT8_S *switchNum,UINT16_S switchIdBuf[]);

/*******************************************
* 函数名	： CheckPositionBelongAc
* 功能描述： 查询位置所属计轴区段
* 参数说明： const UINT16 segId,SEG的ID
* 返回值  ： 0: 获取失败
*		    >0: 所属AC
*/
UINT16_S CheckPositionBelongAc(const UINT16_S segId);

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
UINT8_S CheckAcTopPosition(const UINT16_S acId,const UINT16_S dir,UINT16_S *segId,UINT32_S *offset);

/*******************************************
* 函数名	：  CheckAcTerminalPosition
* 功能描述： 查询计轴区段终端位置
* 参数说明： const UINT16 acId,计轴区段ID
*            const UINT16_S dir,列车相对于seg的期望运行方向
*			 UINT16_S *segId,seg的ID
*			 UINT32_S *offset,相对于seg的偏移量
* 返回值  ： 0: 获取失败
*		    1: 获取成功
*/
UINT8_S CheckAcTerminalPosition(const UINT16_S acId,const UINT16_S dir,UINT16_S *seg,UINT32_S *offset);

/*******************************************
* 函数名	：  CheckSwitchBelongAc
* 功能描述： 查询道岔区段对应的计轴区段
* 参数说明： const UINT16 switchId,道岔ID
*            UINT8_S *acNum,计轴区段数量
*            UINT16_S acIdBuf[],计轴区段ID数组
* 返回值  ： 0: 获取失败
*		    1: 获取成功
*/
UINT8_S CheckSwitchBelongAc(const UINT16_S switchId,UINT8_S *acNum,UINT16_S acIdBuf[]);

/*******************************************
* 函数名	：  CheckFrontACStatus
* 功能描述： 查询前方计轴区段(道岔在定位或定位)
* 参数说明： const UINT16 acId,计轴区段ID
*            const UINT8_S dir,列车运行方向
*            UINT16_S *frontAcId,前方计轴区段ID
* 返回值  ：0: 获取失败
*		    1: 获取成功
*           2: 线路终点失败
*           3: 道岔原因失败
*/
UINT8_S CheckFrontACStatus(const UINT16_S acId,const UINT8_S dir,UINT16_S *frontAcId);

/*******************************************
* 函数名	：  CheckRearACStatus
* 功能描述： 查询后方计轴区段(道岔在定位或定位)
* 参数说明：  const UINT16 acId,计轴区段ID
*            const UINT8_S dir,列车运行方向
*            UINT16_S *rearAcId,后方计轴区段ID
* 返回值  ： 0: 获取失败
*		     1: 获取成功
*            2: 线路终点失败
*            3: 道岔原因失败
*/
UINT8_S CheckRearACStatus(const UINT16_S acId,const UINT8_S dir,UINT16_S *rearAcId);

/*******************************************
* 函数名	：  CheckFrontACCanStatus
* 功能描述： 查询前方计轴区段可能的序列(道岔有可能为四开)
* 参数说明： const UINT16 acId,计轴区段ID
*            const UINT8_S dir,列车运行方向
*            UINT16_S *frontAcId,前方计轴区段ID
* 返回值  ： 0，失败
*			1，成功
*			2，线路尽头导致失败
*			3，道岔原因导致失败
*/
UINT8_S CheckFrontACCanStatus(const UINT16_S acId,const UINT8_S dir,UINT8_S* frontAcNum, UINT16_S *frontAcIdBuff);

/*******************************************
* 函数名	： CheckRearACCanStatus
* 功能描述： 查询后方计轴区段(道岔有可能为四开)
* 参数说明：  const UINT16 acId,计轴区段ID
*            const UINT8_S dir,列车运行方向
*            UINT16_S *rearAcId,后方计轴区段ID
* 返回值  ： 0，失败
*			1，成功
*			2，线路尽头导致失败
*			3，道岔原因导致失败
*/
UINT8_S CheckRearACCanStatus(const UINT16_S acId,const UINT8_S dir,UINT8_S* rearAcNum, UINT16_S *rearAcIdBuff);

/*******************************************
* 函数名	： CheckDistanceBetweenTwoPoints
* 功能描述： 查询两点之间的距离区段
* 参数说明：  const UINT16 seg1,seg的ID
*            const UINT32_S offset1,seg的偏移量
*            const UINT16_S seg2,seg的ID
*            const UINT32_S offset2,seg的偏移量
*            UINT8_S dir,运行方向
* 返回值  ： 0xffffffff: 获取失败
*		    其他: 获取成功
*/
UINT32_S CheckDistanceBetweenTwoPoints(const UINT16_S seg1,const UINT32_S offset1,const UINT16_S seg2,const UINT32_S offset2,UINT8_S dir);

/*******************************************
* 函数名	： CheckPointNearestSignalBaseDir
* 功能描述： 查询基于方向的离给定点最近的同方向信号机
* 参数说明： const UINT8 dir,运行方向
*            const UINT16_S seg, seg的ID
*            const UINT32_S offset,seg的偏移量
*            UINT16_S *outSignalId,信号机的ID
* 返回值  ： 0: 获取失败
*		    1: 获取成功
*/
UINT8_S CheckPointNearestSignalBaseDir(const UINT8_S dir,const UINT16_S seg,const UINT32_S offset,UINT16_S *outSignalId);

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
UINT8_S CheckLocRelationBetweenTwoPoints(const UINT16_S seg1,const UINT32_S offset1,const UINT16_S seg2,const UINT32_S offset2,UINT8_S dir);

/*******************************************
* 函数名	： CheckPointBelongToOutCbtcArea
* 功能描述： 查询某个点是否属于退出CBTC区域
* 参数说明： UINT16_S wTrainHeadSeg, 
*          UINT32_S dwTrainHeadOffset
* 返回值  ： 0: 获取失败
*		    1: 属于
*            2: 不属于
*/
UINT8_S CheckPointBelongToOutCbtcArea(UINT16_S wTrainHeadSeg, UINT32_S dwTrainHeadOffset);

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

UINT8_S CheckAcOrderBetweenTwoPoints(const UINT16_S seg1,const UINT16_S seg2,const UINT8_S dir,UINT8_S *acNum,UINT16_S acIdBuff[]);

/*******************************************
* 函数名	： GetLineSegBelongZcId
* 功能描述： 查询Seg所属ZC
* 参数说明： const UINT16_S segId,
* 返回值  ： 0: 获取失败
*		    >0: 所属ZC
*/
UINT16_S GetLineSegBelongZcId(const UINT16_S segId);

/*******************************************
* 函数名	： CheckPointBelongTocondominiumLineOfHand
* 功能描述： 查询点是否位于切换区域的移交区域内
* 参数说明：  const UINT16 condominiumLineId 移交区域SEGID
*			  const UINT16_S seg 点所处的SEGID
*             const UINT32_S offset,所在Link的偏移量
* 返回值  ： 0: 获取失败
*		    1: 属于
*            2: 不属于
*/
UINT8_S CheckPointBelongTocondominiumLineOfHand(const UINT16_S condominiumLineId,const UINT16_S seg,const UINT32_S offset);

/*******************************************
* 函数名	：CheckAcBelongToStation
* 功能描述：查询某个计轴区段是否属于站台区域
* 参数说明： const UINT16_S acId
* 返回值  ： 0: 获取失败
*		    1: 属于
*            2: 不属于
*/
UINT8_S CheckAcBelongToStation(const UINT16_S acId);

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
UINT8_S CheckSwitchOrderBetweenTwoPoints(const UINT16_S seg1,const UINT16_S seg2,UINT8_S dir,UINT8_S *switchNum,UINT16_S swtichIdBuff[]);

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
UINT8_S CheckPsdOrderBetweenTwoPoints(const UINT16_S seg1,const UINT16_S seg2,UINT8_S dir,UINT8_S *psdNum,UINT16_S psdIdBuff[]);

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
UINT8_S CheckEsbOrderBetweenTwoPoints(const UINT16_S seg1,const UINT16_S seg2,UINT8_S dir,UINT8_S *esbNum,UINT16_S esbIdBuff[]);

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
UINT8_S CheckSuperpositionBetweenTwoArea(const UINT8_S logicSectionNum, const UINT16_S logicSectionId[],const AreaInfoStruct maArea,const UINT8_S dir,UINT8_S *superAreaNum,AreaInfoStruct superArea[]);

/*******************************************
* 函数名	： CheckPointReclosingAtQuitCbtc
* 功能描述： 查询某个点是否和退出CBTC区域终点重合
* 参数说明： const UINT16_S seg,
*          const UINT32_S offset
* 返回值  ： 
*    0,查询失败
*    1,重合
*    2,不重合
*/
UINT8_S CheckPointReclosingAtQuitCbtc(const UINT16_S seg,const UINT32_S offset);

/*******************************************
* 函数名	：  CheckPointBelongToArea
* 功能描述： 查询某个点是否属于某个区域
* 参数说明： const UINT16_S startSeg,
*          const UINT32_S startOffset,
*          const UINT16_S endSeg,
*          const UINT32_S endOffset,
*          const UINT16_S checkSeg,
*          const UINT32_S checkOffset,
*          const UINT8_S dir
* 返回值  ： 
*    0,不属于
*    1,属于
*/
UINT8_S CheckPointBelongToArea(const UINT16_S startSeg,const UINT32_S startOffset,const UINT16_S endSeg,const UINT32_S endOffset,const UINT16_S checkSeg,const UINT32_S checkOffset,const UINT8_S dir);

/*******************************************
* 函数名	： GetLineAcLength
* 功能描述： 查询计轴区段长度
* 参数说明： const UINT16_S acId,
*          UINT32_S *acLength
* 返回值  ： 
*    0,查询失败
*    1,查询成功
*/
UINT8_S GetLineAcLength(const UINT16_S acId,UINT32_S *acLength);

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
UINT8_S CheckPointBelongDrButtonId(const UINT16_S seg,const UINT32_S offset,UINT16_S *drButtonId);

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
UINT8_S CheckSignalPostion(const UINT16_S signalId,UINT16_S *seg,UINT32_S *offset);

/*******************************************
* 函数名	：  CheckFirstAcOfSignal
* 功能描述： 查询信号机内方第一个计轴区段
* 参数说明： const UINT16_S signalId,
*          UINT16_S * acId
* 返回值  ： 
*    0,查询失败
*    1,查询成功
*/
UINT8_S CheckFirstAcOfSignal(const UINT16_S signalId,UINT16_S * acId);

/*******************************************
* 函数名	： CheckOutsideAcOfSignal
* 功能描述： 查询信号机外方第一个计轴区段
* 参数说明： const UINT16 signalId, 信号机ID
*            UINT16_S * acId,信号机外方第一个计轴区段ID
* 返回值  ： 
*    0,查询失败
*    1,查询成功
*/
UINT8_S CheckOutsideAcOfSignal(const UINT16_S signalId,UINT16_S * acId);

/*******************************************
* 函数名	： CheckAcLength
* 功能描述： 查询计轴区段长度
* 参数说明： const UINT16_S acId 计轴区段编号
*          UINT32_S *length 计轴区段长度
* 返回值  ： 
*    0,查询失败
*    1,查询成功
*/
UINT8_S CheckAcLength(const UINT16_S acId,UINT32_S *length);

/*******************************************
* 函数名	：  GetLineRouteAreaType
* 功能描述： 查询进路区域属性
* 参数说明： 
* 返回值  ： 
*    0,查询失败
*   >0,区域属性
*/
UINT8_S GetLineRouteAreaType(const UINT16_S routeId);

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
UINT8_S CheckLogicIdBetweenPoints(const UINT8_S selfFlag,const UINT16_S headSeg,const UINT32_S headOffset,const UINT16_S TailSeg,const UINT32_S TailOffset,const UINT8_S direction,UINT16_S logicSectionId[]);

/*******************************************
* 函数名	： CheckPointBelongReverseArea
* 功能描述： 查询某个点是否属于折返轨
* 参数说明： const UINT16 segId,Seg编号
* 返回值  ： 
*    0,不属于折返轨
*    1,属于折返轨
*/
UINT8_S CheckPointBelongReverseArea(const UINT16_S segId);

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
UINT8_S CheckAcOrderAccordLineSwitchId(const UINT16_S lineSwitchId,UINT8_S *acNum,UINT16_S acIdBuff[]);

#if 0
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
UINT8_S CalculatePointOfInsideLink(const UINT8_S dir,const UINT16_S segId,const UINT32_S offset,UINT16_S *outSegId);
#endif

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
UINT8_S CalculatePointOfInsideLink(const UINT8_S dir,const UINT16_S segId,const UINT32_S offset,UINT16_S *outSegId);

/*******************************************
* 函数名	： CheckFrontLink
* 功能描述： 计算当前Seg前方Seg
* 参数说明： const UINT8 dir,方向
*            const UINT16_S segId,当前segId
*            UINT16_S *outSegId,输出seg
* 返回值  ： 0:获取失败
*            1:获取成功
*/
UINT8_S CheckFrontLink(const UINT8_S dir,const UINT16_S segId,UINT16_S *outSegId);

/*******************************************
* 函数名	： CheckPointQuitCbtcIsFindPoint
* 功能描述： 查询某个点是否属于退出CBTC区域内
* 参数说明： 
* 返回值  ： 
*    1,属于
*    2,不属于
*	 0,查询失败
*/
UINT8_S CheckPointQuitCbtcIsFindPoint(const UINT16_S seg,const UINT32_S offset,const UINT8_S dir);


#ifdef __cplusplus
}
#endif

#endif
