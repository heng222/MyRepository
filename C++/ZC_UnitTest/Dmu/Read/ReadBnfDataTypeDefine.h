
/*************************************************
  �ļ���   ��ReadBnfDataTypeDefine.h
  ����     ������      
  ����ʱ�� ��2016-8-13
  �������� �� ������������ͷ�ļ�
  ��ע    ���ޡ� 
*************************************************/

#ifndef READ_BNF_DATATYPE_DEFINE_H_
#define READ_BNF_DATATYPE_DEFINE_H_

#include "../../Common/CommonTypes.h"
#include "../../Common/Convert.h"
#include "../../Common/CRC32.h"

#define  BNF_MAX_FILE_LEN        (2u*1024u*1024u)         /*���֧�ֵ��ļ����ȣ�2M��*/
#define  BNF_DATA_INDEX_SIZE      6u                      /*������������*/

/*�������ļ������ݿ�ʼ���*/
#define BNF_FILE_CRCDATA_INDEX      12u                     /*4(����ͷ)+4(���ݱ��)+4(CRC)*/
#define BNF_FILE_DATA_INDEX            16u                     /*4(����ͷ)+4(���ݱ��)+4(CRC)+4����*/

#define BNF_SUB_TAB_VER_LEN             4u                     /*�ӱ�汾����ռ�ֽ���*/
#define BNF_SUB_TAB_CRC_LEN             4u                     /*�ӱ�CRCռ�ֽ���*/
#define BNF_SUB_TAB_TYPE_LEN         1u                     /*�ӱ�����ռ�ֽ���*/

#define BNF_DATA_BLOCK_IDX_LEN         2u                     /*���ݿ�������ռ�ֽ���*/
#define BNF_SUB_TAB_VER_IDX_LEN      1u                     /*�ӱ�汾�����ֶ���ռ�ֽ���*/
#define BNF_SUB_TAB_VER_IDX_LEN      1u                     /*�Ƚϰ汾�����ֶ���ռ�ֽ���*/
#define BNF_CMP_VER_IDX_LEN          1u                     /*�Ƚ��ļ��汾�����ֶ���ռ�ֽ���*/  
#define BNF_CMP_VER_BLOCK_LEN        4u                     /*һ���Ƚ��ļ��汾����ռ�ֽ���*/  



/*�������ļ�����ͷ�ṹ*/
typedef struct BnfDataHeadStruct
{
    UINT32_S  dataSignNum;                                   /*���ݱ�ʶ*/
    UINT32_S  dataFileVersion;                               /*���ݰ汾*/
    UINT32_S  crc;                                           /*���ļ�CRC*/
    UINT32_S  dataLength;                                    /*���ݳ���*/
}BnfDataHeadStruct;


/*�������ļ��и�ϵͳ֮���������ݱȽϰ汾��*/
typedef struct InterSysCmpVerStruct
{
    UINT32_S cmpDataFileVersion;                                    /*�汾��*/
}InterSysCmpVerStruct;


/*�������ļ����ӱ����ݰ汾�Žṹ*/
typedef struct  SubTabVersionStruct
{
    UINT8_S subTabType;
    UINT32_S subTabDataVer;
    UINT32_S subTabDataCrc;
}SubTabVersionStruct; 

/*�����������ļ��洢�Ľṹ��*/
typedef struct BnfDataParseStruct
{
    UINT8_S tableID;                                        /*����*/
    UINT8_S sheetId;                                        /*�䵥���*/
    UINT16_S rowLength;                                     /*�г���*/
    UINT32_S dataLen;                                       /*SHEET����*/
    UINT8_S* pDataBuff;                                     /*�洢���ݵĶ���*/
}BnfDataParseStruct;

#endif
