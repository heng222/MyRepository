/*************************************************
  �ļ���   ��ReadManage.h
  ����     ������      
  ����ʱ�� ��2016-8-13
  �������� �� ��ȡBnf�ļ�����
			��ȡBnf�ļ������ܿɷֽ����£�
			1��	�����ݺ���ע�����
			2��	�����ݴ���
			3��	��ȡ�������ݳ��ȣ�
			4��	��ȡ�������ݣ�
			5��	��ȡϵͳ��Ƚ����ݰ汾�ţ�
			6��	��ȡ�������������ļ��汾�ţ�
			7��	��ȡ�������������ļ���
			8��	��ȡ�������������ļ���·��ţ�
			9��	��ȡ�����ӱ�CRC��
			10��	��ȡ�����ӱ�汾�ţ�
  ��ע    ���ޡ� 
*************************************************/

#ifndef READ_MANAGE_H_
#define READ_MANAGE_H_

#include "../../Common/CommonTypes.h"
#include "ReadDataTypeDefine.h"


/*������ṹ��*/
typedef struct ReadObjectStruct
{
    INT8_S (*ReadData)(const CHAR_S* bnfFileAddr); /*������*/
    INT8_S (*GetCfgDataLen)(UINT8_S mainType, UINT8_S subType,UINT32_S* dataLen, UINT8_S* indexId); /*��ȡ�������ݳ���*/
    INT8_S (*GetCfgData)(UINT16_S rowLength,UINT32_S dataLen, UINT8_S indexId,UINT8_S* dataBuf);    /*��ȡ��������*/
    
    INT8_S (*GetDataFileVersion)(UINT32_S* dataFileVersion);                                        /*��ȡ�����ļ��汾��*/
    INT8_S (*GetDataFileCrc)(UINT32_S* dataFileCrc);                                                /*��ȡ�����ļ�CRC*/
    INT8_S (*GetDataFileSignNum)(UINT32_S* dataFileSignNum);                                        /*��ȡ�����ļ���·���*/
    
    INT8_S (*GetInterSysCmpDataFileVer)(const UINT8_S verIndex,UINT32_S* dataVersion);              /*��ȡ�������ݰ汾*/
    INT8_S (*GetDataSubTabVer)(const UINT8_S subTabType,UINT32_S* subTabVersion);                   /*��ȡ���������ӱ�汾��*/                                          
    INT8_S (*GetDataSubTabCrc)(const UINT8_S subTabType,UINT32_S* subTabCrc);                       /*��ȡ���������ӱ�CRC*/

} ReadObjectStruct;


#ifdef __cplusplus
extern "C" {
#endif



/*
* ���������� ������
* ����˵���� void
* ����ֵ  �� void       
*/
void ReadManage(void);


/*
* ���������� ������
* ����˵���� 
* ������� :bnfFileAddr �������ļ���ַ
* ����ֵ  �� 0 �ɹ�
            -1 ����ָ��Ϊ��
             1:�򿪶������ļ�ʧ��
             2:��ȡ�������ļ�ʧ��
             3:У��ʧ�ܣ��汾�Ų�һ��
             4:���ݱ�ʶ������
             5:�����������ļ��ĵ�ַΪ��
*/
INT8_S ReadData(CHAR_S* bnfFileAddr);


/*
* ���������� ��ȡ�������ݳ���
* ����˵���� 
  ���������dataType ��������   �ɲ�ѯ�����궨�巽ʽ����
            sheetID ����ID      �����        
  ���������indexId   �ṹ��ָ��ƫ��
            dataLength ���ݳ���
* ����ֵ  �� 0 �ɹ�
            -1 ����ָ��Ϊ��
            1�ӿڷ�������
            2������������ͺͱ���Ŵ���
*/
INT8_S GetConfigDataLen(UINT8_S mainType, UINT8_S subType,UINT32_S* dataLen, UINT8_S* indexId);

/*
* ���������� ��ȡ��������
* ����˵���� 
  ���������UINT16 rowLength   �������ܳ���
              dataLength ���ݳ���
            indexId   �ṹ��ָ��ƫ��    
  ���������dataBuf   ���ݵ�ַ
* ����ֵ  �� 0 �ɹ�
            -1 ����ָ��Ϊ��
            1�ӿڷ�������
            2��ȡ����ʧ��
*/
INT8_S GetConfigData(UINT16_S rowLength,UINT32_S dataLen, UINT8_S indexId,UINT8_S* dataBuf);



/*
* ���������� ��ȡϵͳ��Ƚ����ݰ汾��
* ����˵���� 
* �������: const UINT8_S verIndex 
* �������:dataVersion   ���ݰ汾��
* ����ֵ  �� 0 �ɹ�
            -1 ����ָ��Ϊ��
            1���ݶ�ȡ���ɹ�
*/
INT8_S DmuGetIntSysCmpDataFileVer(const UINT8_S cmpVerIndex ,UINT32_S* dataVersion);


/*
* ���������� ��ȡ�������������ļ��汾��
* ����˵���� 
* �������: ��
* �������:dataVersion   �������������ļ��汾��
* ����ֵ  �� 0 �ɹ�
            -1 ����ָ��Ϊ��
            1���ݶ�ȡ���ɹ�
*/
INT8_S DmuGetDataFileVersion(UINT32_S* dataFileVersion);

/*
* ���������� ��ȡ�������������ļ�CRC
* ����˵���� 
* �������: ��
* �������:dataFileCrc   �������������ļ�CRC
* ����ֵ  �� 0 �ɹ�
            -1 ����ָ��Ϊ��
            1���ݶ�ȡ���ɹ�
*/
INT8_S DmuGetDataFileCrc(UINT32_S* dataFileCrc);

/*
* ���������� ��ȡ�������������ļ���·���
* ����˵���� 
* �������: ��
* �������:dataFileCrc   �������������ļ���·���
* ����ֵ  �� 0 �ɹ�
                          -1 ����ָ��Ϊ��
                          1���ݶ�ȡ���ɹ�
*/
INT8_S DmuGetDataFileSignNum(UINT32_S* dataFileSignNum);

/*
* ���������� ��ȡ�����ӱ�CRC
*����˵����
    ���������const UINT8_S subTabType    �����ӱ�����(���вμ�ReadDataTypeDefine.h����صĶ���)
    ���������subTabDataCrc    4�ֽ�CRC
* ����ֵ  �� 0 �ɹ�
            -1 ����ָ��Ϊ��
            1���ݶ�ȡ���ɹ�
*/
INT8_S  DmuGetDataSubTabCrc(const UINT8_S subTabType,UINT32_S* subTabDataCrc);



/*
* ���������� ��ȡ�����ӱ�汾��
*����˵����
    ���������const UINT8_S subTabType    �����ӱ�����(���вμ�ReadDataTypeDefine.h����صĶ���)
    ���������subTabDataVer    4�ֽڰ汾��
* ����ֵ  �� 0 �ɹ�
            -1 ����ָ��Ϊ��
            1���ݶ�ȡ���ɹ�
*/
INT8_S  DmuGetDataSubTabVer(const UINT8_S subTabType,UINT32_S* subTabDataVer);





#ifdef __cplusplus
}
#endif

#endif
