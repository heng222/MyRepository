/********************************************************
*                                                                                                            
* �� �� ���� ACConfigData.h  
* ����ʱ�䣺 2015-05-01
* ��    �ߣ� 
* ���������� �����������ݹ���  
* ��  ע  ��  ��
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

	/*���������������ݽṹ��*/
	typedef struct SAcConfigDataStruct
	{
		UINT16_S AcId;      		/*��������ID*/
		UINT16_S BelongCiId;    	/*��������ID*/
		UINT16_S BelongZcId;      /*����ZCID*/
		UINT8_S  AcType;			/*�������ͣ�0x55-������������;0xaa-��������������*/
		UINT8_S  ChangeAttribute;  /*���Ṳ���������ԣ�1�����ڹ������������ڱ�ZC;2�����ڹ�����������������ZC;3�������ڹ�������C*/
		UINT8_S  SwitchNum;       /*�������ΰ����ĵ�������*/
		SwitchInAcStruct SwitchInAcStru[AC_SWITCH_SUM_MAX]; /*�������ΰ����ĵ�����Ϣ*/
		UINT8_S  LogicSectionNum;                             /*�������ΰ������߼���������*/
		UINT16_S LogicSectionIdBuff[SIZE_MAX_SECTIONNUM];      /*�������ΰ������߼�����Id����*/
	} AcConfigDataStruct;

	/*��������*/
    /*
    * ���������� ��ȡָ��ID����������
    * ����˵���� const UINT16 acId, ����ID
    * ����ֵ  �� LOCAL_AC_SUM_MAX �� AC_SUM_MAX: ��ȡ����ʧ��
    *			<LOCAL_AC_SUM_MAX: ���ҳɹ�
    */
	UINT16_S GetAcConfigBufIndex(const UINT16_S acId);

	/*
	* ���������� ��ȡ���ᵱǰ����
	* ����˵���� void    
	* ����ֵ  �� 0: ��ȡ��������ʧ��
	*			>0: ���ᵱǰ����
	*/
	UINT16_S GetAcCurSum(void);

	/*
	* ���������� ��ȡָ�������±��Ӧ�ļ�������ID
	* ����˵���� const UINT16 bufIndex, �����±�    
	* ����ֵ  �� 0: ��ȡ����ʧ��
	*			>0: ACID      
	*/
	UINT16_S GetAcId(const UINT16_S bufIndex);

	/*
	* ���������� ��ȡָ��ID������������ID
	* ����˵���� const UINT16 acId, ����ID    
	* ����ֵ  �� 0: ��ȡ����ʧ��
	*			>0: ��������ID      
	*/
	UINT16_S GetAcBelongCiId(const UINT16_S acId);

	/*
	* ���������� ��ȡָ��ID��������Zc ID
	* ����˵���� const UINT16 acId, ����ID    
	* ����ֵ  �� 0: ��ȡ����ʧ��
	*			>0: ����ZC ID      
	*/
	UINT16_S GetAcBelongZcId(const UINT16_S acId);

	/*
	* ���������� ��ȡָ��ID������������
	* ����˵���� const UINT16 acId, ����ID    
	* ����ֵ  �� 0: ��ȡ����ʧ��
	*			 0x55-������������
	0xaa-��������������   
	*/
	UINT8_S GetAcType(const UINT16_S acId);

    /*
    * ���������� ��ȡָ��ID����߽������
    * ����˵���� const UINT16 acId, ����ID    
    * ����ֵ  �� 0:������
    *            FLAG_SET:����
    */
	UINT8_S GetAcBoundaryType(const UINT16_S acId);

	/*
	* ���������� ��ȡָ��ID��������ĵ�������
	* ����˵���� const UINT16 acId, ����ID    
	* ����ֵ  �� 0xff: ��ȡ����ʧ��
	*			>=0: �������� 
	*/
	UINT8_S GetAcSwitchNum(const UINT16_S acId);

	/*
	* ���������� ��ȡָ��ID��������ĵ�����Ϣ
	* ����˵���� const UINT16 acId, ����ID 
	*            const UINT8_S bufSize,��С
	*            SwitchInAcStruct switchInAcStruBuff[],������Ϣ
	* ����ֵ  �� 0: ��ȡ����ʧ��
	*			 1: ��ȡ���ݳɹ�   
	*/
	UINT8_S GetAcSwitchInfo(const UINT16_S acId,const UINT8_S bufSize,SwitchInAcStruct switchInAcStruBuff[]);

	/*
	* ���������� ��ȡָ���������ΰ������߼���������
	* ����˵���� const UINT16 acId, ��������Id    
	* ����ֵ  �� 0: ��ȡ����ʧ��
	*			>0: ����      
	*/
	UINT16_S GetAcLogicSectionNum(const UINT16_S acId);

	/*
	* ���������� ��ȡָ���������ΰ������߼�����Id����
	* ����˵���� const UINT16 bufIndex, �����±�    
	*            const UINT16_S bufSize,��������С
	*            UINT16_S logicSectionIdBuff[],�������
	* ����ֵ  �� 0: ��ȡ����ʧ��
	*			 1: ��ȡ�ɹ�      
	*/
	UINT8_S GetAcLogicSectionIdBuf(const UINT16_S acId,const UINT16_S bufSize,UINT16_S logicSectionIdBuff[]);
	
#ifdef __cplusplus
}
#endif

#endif
