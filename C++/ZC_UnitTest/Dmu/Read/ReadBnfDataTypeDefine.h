
/*************************************************
  文件名   ：ReadBnfDataTypeDefine.h
  作者     ：董欣      
  创建时间 ：2016-8-13
  功能描述 ： 配置数据申明头文件
  备注    ：无。 
*************************************************/

#ifndef READ_BNF_DATATYPE_DEFINE_H_
#define READ_BNF_DATATYPE_DEFINE_H_

#include "../../Common/CommonTypes.h"
#include "../../Common/Convert.h"
#include "../../Common/CRC32.h"

#define  BNF_MAX_FILE_LEN        (2u*1024u*1024u)         /*最大支持的文件长度（2M）*/
#define  BNF_DATA_INDEX_SIZE      6u                      /*数据索引表编号*/

/*二进制文件中数据开始标记*/
#define BNF_FILE_CRCDATA_INDEX      12u                     /*4(数据头)+4(数据标记)+4(CRC)*/
#define BNF_FILE_DATA_INDEX            16u                     /*4(数据头)+4(数据标记)+4(CRC)+4长度*/

#define BNF_SUB_TAB_VER_LEN             4u                     /*子表版本号所占字节数*/
#define BNF_SUB_TAB_CRC_LEN             4u                     /*子表CRC占字节数*/
#define BNF_SUB_TAB_TYPE_LEN         1u                     /*子表类型占字节数*/

#define BNF_DATA_BLOCK_IDX_LEN         2u                     /*数据块索引所占字节数*/
#define BNF_SUB_TAB_VER_IDX_LEN      1u                     /*子表版本个数字段所占字节数*/
#define BNF_SUB_TAB_VER_IDX_LEN      1u                     /*比较版本个数字段所占字节数*/
#define BNF_CMP_VER_IDX_LEN          1u                     /*比较文件版本个数字段所占字节数*/  
#define BNF_CMP_VER_BLOCK_LEN        4u                     /*一个比较文件版本块所占字节数*/  



/*二进制文件数据头结构*/
typedef struct BnfDataHeadStruct
{
    UINT32_S  dataSignNum;                                   /*数据标识*/
    UINT32_S  dataFileVersion;                               /*数据版本*/
    UINT32_S  crc;                                           /*主文件CRC*/
    UINT32_S  dataLength;                                    /*数据长度*/
}BnfDataHeadStruct;


/*二进制文件中各系统之间配置数据比较版本号*/
typedef struct InterSysCmpVerStruct
{
    UINT32_S cmpDataFileVersion;                                    /*版本号*/
}InterSysCmpVerStruct;


/*二进制文件各子表数据版本号结构*/
typedef struct  SubTabVersionStruct
{
    UINT8_S subTabType;
    UINT32_S subTabDataVer;
    UINT32_S subTabDataCrc;
}SubTabVersionStruct; 

/*解析二进制文件存储的结构体*/
typedef struct BnfDataParseStruct
{
    UINT8_S tableID;                                        /*表编号*/
    UINT8_S sheetId;                                        /*变单编号*/
    UINT16_S rowLength;                                     /*列长度*/
    UINT32_S dataLen;                                       /*SHEET长度*/
    UINT8_S* pDataBuff;                                     /*存储数据的队列*/
}BnfDataParseStruct;

#endif
