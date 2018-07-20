/*******************************************
* �ļ���	��  DmuZcDataHandle.h
* ��  ��	��  ZC��
* ����ʱ��	��  2015-5-25
* ��������	��	ZC��ѯ����
* ��  ע	��  ��
*******************************************/
#ifndef DMU_ZC_DATAHANDLE_H_
#define DMU_ZC_DATAHANDLE_H_

#include "../../../Common/CommonTypes.h"

#define LXS_MA_SEC_SUP_MAX_NUM						5U								/*��ʱ����������MA�����غϲ��ֵ����ֶ��������*/			


#ifdef __cplusplus
extern "C" {
#endif

/*������Ϣ�ṹ�嶨��*/
typedef struct AreaInfoStruct
{
	UINT16_S  startSegId;						/*���SEGID*/
	UINT32_S  startSegOffSet;					/*���SEGƫ����*/
	UINT16_S  endSegId;						/*�յ�SEGID*/
	UINT32_S  endSegOffSet;					/*�յ�SEGƫ����*/
}AreaInfoStruct;

/*******************************************
* ������	�� ZcBnfDataInit
* ��������: ��ʼ��ZC�����ļ�
* ����˵����UINT8* bnfFileAddr   �������ļ��ĵ�ַ
* ����ֵ��1:�ɹ���	0:ʧ��
*/
INT8_S ZcBnfDataInit(CHAR_S* bnfFileAddr);

/*******************************************
* ������	�� GetLineOverlapOfSwitchNum
* ���������� ��ȡ�������ΰ����ĵ�������
* ����˵���� const UINT16 overlapId,��������ID
* ����ֵ  �� 0xffff: ��ȡ����ʧ��
*			>0:��������
*/
UINT16_S GetLineOverlapOfSwitchNum(const UINT16_S overlapId);

/*******************************************
* ������	�� GetLineRouteOfObsInfo
* ���������� ��ȡ��·��Ӧ�źŻ�ID
* ����˵���� const UINT16 routeId,��·ID
*            UINT16_S obsInfoBuf[]���ϰ�����Ϣ���飨id,���ͣ�
* ����ֵ  �� 0xffff: ��ȡ����ʧ��
*			>=0:�ϰ�������(����PSD,ESB)
*/
UINT16_S GetLineRouteOfObsInfo(const UINT16_S routeId,UINT16_S obsInfoBuf[]);

/*******************************************
* ������	�� GetLineSignalDefaultStatus
* ���������� ��ȡ��·�źŻ�Ĭ��״̬
* ����˵���� const UINT16 signalId,�źŻ�ID
* ����ֵ  �� 0: ��ȡ����ʧ��
*			0x55/0xaa:Ĭ��״̬
*/
UINT16_S GetLineSignalDefaultStatus(const UINT16_S signalId);


/*******************************************
* ������	�� GetLineCbtcLightOffType
* ���������� ��ȡ��·�źŻ�CBTC�г���������(Ԥ��)
* ����˵���� const UINT16 signalId,�źŻ�ID
* ����ֵ  �� 0: ��ȡ����ʧ��
*			0x55/0xaa:CBTC�г���������
*/
UINT8_S GetLineCbtcLightOffType(const UINT16_S signalId);

/*******************************************
* ������	�� GetLineCrossType
* ���������� ��ȡ��·�źŻ���ѹ����(Ԥ��)
* ����˵���� const UINT16 signalId,�źŻ�ID
* ����ֵ  �� 0: ��ȡ����ʧ��
*			0x55/0xaa:��ѹ����
*/
UINT8_S GetLineCrossType(const UINT16_S signalId);

/*******************************************
* ������	�� GetLineCrashType
* ���������� ��ȡ��·�źŻ����ź�����
* ����˵���� const UINT16 signalId,�źŻ�ID
* ����ֵ  �� 0: ��ȡ����ʧ��
*			0x55/0xaa:���ź�����
*/
UINT16_S GetLineCrashType(const UINT16_S signalId);

/*******************************************
* ������	�� GetLineSwitchPosition
* ���������� ��ȡ��·����λ����Ϣ��������/���ߣ�
* ����˵���� const UINT16 switchId,����ID
* ����ֵ  �� 0: ��ȡ����ʧ��
*			0xaa/0x55:������/����
*/
UINT8_S GetLineSwitchPosition(const UINT16_S switchId);


/*******************************************
* ������	�� GetLineAcType
* ���������� ��ȡ������������
* ����˵���� const UINT16 acId����������ID
* ����ֵ  �� 0: ��ȡʧ��
*			0x55-������������;0xaa-��������������
*/
UINT8_S GetLineAcType(const UINT16_S acId);

/*******************************************
* ������	�� GetLineAcIncludeSwitchInfo
* ���������� ��ȡ�������ΰ���������Ϣ
* ����˵���� const UINT16 acId����������ID
*            UINT8_S *switchNum,��������
*            UINT16_S switchIdBuf[]������ID����
* ����ֵ  �� 0: ��ȡʧ��
*		    1: ��ȡ�ɹ�
*/
UINT8_S GetLineAcIncludeSwitchInfo(const UINT16_S acId,UINT8_S *switchNum,UINT16_S switchIdBuf[]);

/*******************************************
* ������	�� CheckPositionBelongAc
* ���������� ��ѯλ��������������
* ����˵���� const UINT16 segId,SEG��ID
* ����ֵ  �� 0: ��ȡʧ��
*		    >0: ����AC
*/
UINT16_S CheckPositionBelongAc(const UINT16_S segId);

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
UINT8_S CheckAcTopPosition(const UINT16_S acId,const UINT16_S dir,UINT16_S *segId,UINT32_S *offset);

/*******************************************
* ������	��  CheckAcTerminalPosition
* ���������� ��ѯ���������ն�λ��
* ����˵���� const UINT16 acId,��������ID
*            const UINT16_S dir,�г������seg���������з���
*			 UINT16_S *segId,seg��ID
*			 UINT32_S *offset,�����seg��ƫ����
* ����ֵ  �� 0: ��ȡʧ��
*		    1: ��ȡ�ɹ�
*/
UINT8_S CheckAcTerminalPosition(const UINT16_S acId,const UINT16_S dir,UINT16_S *seg,UINT32_S *offset);

/*******************************************
* ������	��  CheckSwitchBelongAc
* ���������� ��ѯ�������ζ�Ӧ�ļ�������
* ����˵���� const UINT16 switchId,����ID
*            UINT8_S *acNum,������������
*            UINT16_S acIdBuf[],��������ID����
* ����ֵ  �� 0: ��ȡʧ��
*		    1: ��ȡ�ɹ�
*/
UINT8_S CheckSwitchBelongAc(const UINT16_S switchId,UINT8_S *acNum,UINT16_S acIdBuf[]);

/*******************************************
* ������	��  CheckFrontACStatus
* ���������� ��ѯǰ����������(�����ڶ�λ��λ)
* ����˵���� const UINT16 acId,��������ID
*            const UINT8_S dir,�г����з���
*            UINT16_S *frontAcId,ǰ����������ID
* ����ֵ  ��0: ��ȡʧ��
*		    1: ��ȡ�ɹ�
*           2: ��·�յ�ʧ��
*           3: ����ԭ��ʧ��
*/
UINT8_S CheckFrontACStatus(const UINT16_S acId,const UINT8_S dir,UINT16_S *frontAcId);

/*******************************************
* ������	��  CheckRearACStatus
* ���������� ��ѯ�󷽼�������(�����ڶ�λ��λ)
* ����˵����  const UINT16 acId,��������ID
*            const UINT8_S dir,�г����з���
*            UINT16_S *rearAcId,�󷽼�������ID
* ����ֵ  �� 0: ��ȡʧ��
*		     1: ��ȡ�ɹ�
*            2: ��·�յ�ʧ��
*            3: ����ԭ��ʧ��
*/
UINT8_S CheckRearACStatus(const UINT16_S acId,const UINT8_S dir,UINT16_S *rearAcId);

/*******************************************
* ������	��  CheckFrontACCanStatus
* ���������� ��ѯǰ���������ο��ܵ�����(�����п���Ϊ�Ŀ�)
* ����˵���� const UINT16 acId,��������ID
*            const UINT8_S dir,�г����з���
*            UINT16_S *frontAcId,ǰ����������ID
* ����ֵ  �� 0��ʧ��
*			1���ɹ�
*			2����·��ͷ����ʧ��
*			3������ԭ����ʧ��
*/
UINT8_S CheckFrontACCanStatus(const UINT16_S acId,const UINT8_S dir,UINT8_S* frontAcNum, UINT16_S *frontAcIdBuff);

/*******************************************
* ������	�� CheckRearACCanStatus
* ���������� ��ѯ�󷽼�������(�����п���Ϊ�Ŀ�)
* ����˵����  const UINT16 acId,��������ID
*            const UINT8_S dir,�г����з���
*            UINT16_S *rearAcId,�󷽼�������ID
* ����ֵ  �� 0��ʧ��
*			1���ɹ�
*			2����·��ͷ����ʧ��
*			3������ԭ����ʧ��
*/
UINT8_S CheckRearACCanStatus(const UINT16_S acId,const UINT8_S dir,UINT8_S* rearAcNum, UINT16_S *rearAcIdBuff);

/*******************************************
* ������	�� CheckDistanceBetweenTwoPoints
* ���������� ��ѯ����֮��ľ�������
* ����˵����  const UINT16 seg1,seg��ID
*            const UINT32_S offset1,seg��ƫ����
*            const UINT16_S seg2,seg��ID
*            const UINT32_S offset2,seg��ƫ����
*            UINT8_S dir,���з���
* ����ֵ  �� 0xffffffff: ��ȡʧ��
*		    ����: ��ȡ�ɹ�
*/
UINT32_S CheckDistanceBetweenTwoPoints(const UINT16_S seg1,const UINT32_S offset1,const UINT16_S seg2,const UINT32_S offset2,UINT8_S dir);

/*******************************************
* ������	�� CheckPointNearestSignalBaseDir
* ���������� ��ѯ���ڷ����������������ͬ�����źŻ�
* ����˵���� const UINT8 dir,���з���
*            const UINT16_S seg, seg��ID
*            const UINT32_S offset,seg��ƫ����
*            UINT16_S *outSignalId,�źŻ���ID
* ����ֵ  �� 0: ��ȡʧ��
*		    1: ��ȡ�ɹ�
*/
UINT8_S CheckPointNearestSignalBaseDir(const UINT8_S dir,const UINT16_S seg,const UINT32_S offset,UINT16_S *outSignalId);

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
UINT8_S CheckLocRelationBetweenTwoPoints(const UINT16_S seg1,const UINT32_S offset1,const UINT16_S seg2,const UINT32_S offset2,UINT8_S dir);

/*******************************************
* ������	�� CheckPointBelongToOutCbtcArea
* ���������� ��ѯĳ�����Ƿ������˳�CBTC����
* ����˵���� UINT16_S wTrainHeadSeg, 
*          UINT32_S dwTrainHeadOffset
* ����ֵ  �� 0: ��ȡʧ��
*		    1: ����
*            2: ������
*/
UINT8_S CheckPointBelongToOutCbtcArea(UINT16_S wTrainHeadSeg, UINT32_S dwTrainHeadOffset);

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

UINT8_S CheckAcOrderBetweenTwoPoints(const UINT16_S seg1,const UINT16_S seg2,const UINT8_S dir,UINT8_S *acNum,UINT16_S acIdBuff[]);

/*******************************************
* ������	�� GetLineSegBelongZcId
* ���������� ��ѯSeg����ZC
* ����˵���� const UINT16_S segId,
* ����ֵ  �� 0: ��ȡʧ��
*		    >0: ����ZC
*/
UINT16_S GetLineSegBelongZcId(const UINT16_S segId);

/*******************************************
* ������	�� CheckPointBelongTocondominiumLineOfHand
* ���������� ��ѯ���Ƿ�λ���л�������ƽ�������
* ����˵����  const UINT16 condominiumLineId �ƽ�����SEGID
*			  const UINT16_S seg ��������SEGID
*             const UINT32_S offset,����Link��ƫ����
* ����ֵ  �� 0: ��ȡʧ��
*		    1: ����
*            2: ������
*/
UINT8_S CheckPointBelongTocondominiumLineOfHand(const UINT16_S condominiumLineId,const UINT16_S seg,const UINT32_S offset);

/*******************************************
* ������	��CheckAcBelongToStation
* ������������ѯĳ�����������Ƿ�����վ̨����
* ����˵���� const UINT16_S acId
* ����ֵ  �� 0: ��ȡʧ��
*		    1: ����
*            2: ������
*/
UINT8_S CheckAcBelongToStation(const UINT16_S acId);

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
UINT8_S CheckSwitchOrderBetweenTwoPoints(const UINT16_S seg1,const UINT16_S seg2,UINT8_S dir,UINT8_S *switchNum,UINT16_S swtichIdBuff[]);

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
UINT8_S CheckPsdOrderBetweenTwoPoints(const UINT16_S seg1,const UINT16_S seg2,UINT8_S dir,UINT8_S *psdNum,UINT16_S psdIdBuff[]);

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
UINT8_S CheckEsbOrderBetweenTwoPoints(const UINT16_S seg1,const UINT16_S seg2,UINT8_S dir,UINT8_S *esbNum,UINT16_S esbIdBuff[]);

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
UINT8_S CheckSuperpositionBetweenTwoArea(const UINT8_S logicSectionNum, const UINT16_S logicSectionId[],const AreaInfoStruct maArea,const UINT8_S dir,UINT8_S *superAreaNum,AreaInfoStruct superArea[]);

/*******************************************
* ������	�� CheckPointReclosingAtQuitCbtc
* ���������� ��ѯĳ�����Ƿ���˳�CBTC�����յ��غ�
* ����˵���� const UINT16_S seg,
*          const UINT32_S offset
* ����ֵ  �� 
*    0,��ѯʧ��
*    1,�غ�
*    2,���غ�
*/
UINT8_S CheckPointReclosingAtQuitCbtc(const UINT16_S seg,const UINT32_S offset);

/*******************************************
* ������	��  CheckPointBelongToArea
* ���������� ��ѯĳ�����Ƿ�����ĳ������
* ����˵���� const UINT16_S startSeg,
*          const UINT32_S startOffset,
*          const UINT16_S endSeg,
*          const UINT32_S endOffset,
*          const UINT16_S checkSeg,
*          const UINT32_S checkOffset,
*          const UINT8_S dir
* ����ֵ  �� 
*    0,������
*    1,����
*/
UINT8_S CheckPointBelongToArea(const UINT16_S startSeg,const UINT32_S startOffset,const UINT16_S endSeg,const UINT32_S endOffset,const UINT16_S checkSeg,const UINT32_S checkOffset,const UINT8_S dir);

/*******************************************
* ������	�� GetLineAcLength
* ���������� ��ѯ�������γ���
* ����˵���� const UINT16_S acId,
*          UINT32_S *acLength
* ����ֵ  �� 
*    0,��ѯʧ��
*    1,��ѯ�ɹ�
*/
UINT8_S GetLineAcLength(const UINT16_S acId,UINT32_S *acLength);

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
UINT8_S CheckPointBelongDrButtonId(const UINT16_S seg,const UINT32_S offset,UINT16_S *drButtonId);

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
UINT8_S CheckSignalPostion(const UINT16_S signalId,UINT16_S *seg,UINT32_S *offset);

/*******************************************
* ������	��  CheckFirstAcOfSignal
* ���������� ��ѯ�źŻ��ڷ���һ����������
* ����˵���� const UINT16_S signalId,
*          UINT16_S * acId
* ����ֵ  �� 
*    0,��ѯʧ��
*    1,��ѯ�ɹ�
*/
UINT8_S CheckFirstAcOfSignal(const UINT16_S signalId,UINT16_S * acId);

/*******************************************
* ������	�� CheckOutsideAcOfSignal
* ���������� ��ѯ�źŻ��ⷽ��һ����������
* ����˵���� const UINT16 signalId, �źŻ�ID
*            UINT16_S * acId,�źŻ��ⷽ��һ����������ID
* ����ֵ  �� 
*    0,��ѯʧ��
*    1,��ѯ�ɹ�
*/
UINT8_S CheckOutsideAcOfSignal(const UINT16_S signalId,UINT16_S * acId);

/*******************************************
* ������	�� CheckAcLength
* ���������� ��ѯ�������γ���
* ����˵���� const UINT16_S acId �������α��
*          UINT32_S *length �������γ���
* ����ֵ  �� 
*    0,��ѯʧ��
*    1,��ѯ�ɹ�
*/
UINT8_S CheckAcLength(const UINT16_S acId,UINT32_S *length);

/*******************************************
* ������	��  GetLineRouteAreaType
* ���������� ��ѯ��·��������
* ����˵���� 
* ����ֵ  �� 
*    0,��ѯʧ��
*   >0,��������
*/
UINT8_S GetLineRouteAreaType(const UINT16_S routeId);

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
UINT8_S CheckLogicIdBetweenPoints(const UINT8_S selfFlag,const UINT16_S headSeg,const UINT32_S headOffset,const UINT16_S TailSeg,const UINT32_S TailOffset,const UINT8_S direction,UINT16_S logicSectionId[]);

/*******************************************
* ������	�� CheckPointBelongReverseArea
* ���������� ��ѯĳ�����Ƿ������۷���
* ����˵���� const UINT16 segId,Seg���
* ����ֵ  �� 
*    0,�������۷���
*    1,�����۷���
*/
UINT8_S CheckPointBelongReverseArea(const UINT16_S segId);

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
UINT8_S CheckAcOrderAccordLineSwitchId(const UINT16_S lineSwitchId,UINT8_S *acNum,UINT16_S acIdBuff[]);

#if 0
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
UINT8_S CalculatePointOfInsideLink(const UINT8_S dir,const UINT16_S segId,const UINT32_S offset,UINT16_S *outSegId);
#endif

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
UINT8_S CalculatePointOfInsideLink(const UINT8_S dir,const UINT16_S segId,const UINT32_S offset,UINT16_S *outSegId);

/*******************************************
* ������	�� CheckFrontLink
* ���������� ���㵱ǰSegǰ��Seg
* ����˵���� const UINT8 dir,����
*            const UINT16_S segId,��ǰsegId
*            UINT16_S *outSegId,���seg
* ����ֵ  �� 0:��ȡʧ��
*            1:��ȡ�ɹ�
*/
UINT8_S CheckFrontLink(const UINT8_S dir,const UINT16_S segId,UINT16_S *outSegId);

/*******************************************
* ������	�� CheckPointQuitCbtcIsFindPoint
* ���������� ��ѯĳ�����Ƿ������˳�CBTC������
* ����˵���� 
* ����ֵ  �� 
*    1,����
*    2,������
*	 0,��ѯʧ��
*/
UINT8_S CheckPointQuitCbtcIsFindPoint(const UINT16_S seg,const UINT32_S offset,const UINT8_S dir);


#ifdef __cplusplus
}
#endif

#endif
