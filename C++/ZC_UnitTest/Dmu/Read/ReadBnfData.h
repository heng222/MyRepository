/*************************************************
  文件名   ：ReadBnfData.h
  作者     ：董欣      
  创建时间 ：2016-8-13
  功能描述 ： 读Bnf配置数据头文件
			DmuCommonRead组件的功能可分解如下：
			1）	读取二进制文件并且保存到内存
			2）	获取二进制文件数据标识；
			3）	获取二进制文件CRC；
			4）	获取二进制文件线路编号；
			5）	获取二进制文件中此输入类型的数据长度和对应的index；
			6）	获取二进制文件中此输入类型的数据信息；
			7）	获取系统间要比较的数据文件的版本号；
			8）	获取数据子表的版本号；
			9）	获取系统间要比较的数据文件的CRC。
			
  备注    ：无。 
*************************************************/

#ifndef READ_BNF_DATA_H_
#define READ_BNF_DATA_H_


#include "ReadBnfDataTypeDefine.h"

#ifdef __cplusplus
extern "C" {
#endif


/*********************************************
* 函数功能 ：读取二进制文件并且保存到内存
* 参数说明 ：
* 输入参数 :bnfFileName 二进制文件地址
* 返回值：0:成功
*         1:打开二进制文件失败
          2:读取二进制文件失败
          3:校验失败，版本号不一致
          5:二进制数据文件的地址为空
**********************************/
INT8_S ReadBnfData(const CHAR_S * bnfFileName);


/**********************************************
*函数功能：获取二进制文件数据标识
*参数说明：
  输出参数：dataFileVersion    4字节  数据标识
*返回值：   0成功，1数据读取不成功
**********************************************/
INT8_S  GetBnfDataFileVersion(UINT32_S* dataFileVersion);

/**********************************************
*函数功能：获取二进制文件CRC
*参数说明：
  输出参数：dataFileCrc    4字节  CRC
*返回值：   0成功，1数据读取不成功
**********************************************/
INT8_S  GetBnfDataFileCrc(UINT32_S* dataFileCrc);
/**********************************************
*函数功能：获取二进制文件线路编号
*参数说明：
  输出参数：dataFileSignNum    4字节  线路编号
*返回值：   0成功，1数据读取不成功
**********************************************/
INT8_S  GetBnfDataFileSignNum(UINT32_S* dataFileSignNum);

/**********************************************************
*函数功能：获取二进制文件中此输入类型的数据长度和对应的index
*参数说明：
  输入参数：dataType 数据类型   由查询函数宏定义方式给出
            sheetID 数据ID      表单编号        
  输出参数：indexId   结构体指针偏移
            dataLength 数据长度
*返回值：   0成功
            1接口防护错误
            2传入的数据类型和表单编号错误
**********************************************************/
INT8_S GetReadBnfDataLen(UINT8_S dataType, UINT8_S sheetID , UINT32_S * dataLength, UINT8_S* indexId);

/**********************************************************
*函数功能：获取二进制文件中此输入类型的数据信息
*参数说明：
  输入参数：UINT16 rowLength   所有列总长度
              dataLength 数据长度
            indexId   结构体指针偏移
  输出参数：dataBuff   数据地址指针
*返回值：   0成功
            1入口参数检查不通过
            2拷取数据失败
**********************************************************/
INT8_S GetReadBnfDataInfo(UINT16_S rowLength,UINT32_S dataLength,UINT8_S indexId, UINT8_S * dataBuff);

/**********************************************
*函数功能：获取系统间要比较的数据文件的版本号
*参数说明：
    输出参数：const UINT8_S verIndex    获取数据版本号的编号(具有参见ReadDataTypeDefine.h中相关的定义)
    输出参数：bnfVersion    4字节版本号
*返回值：   0成功，1数据读取不成功
**********************************************/
INT8_S  GetInterSysCmpDataFileVer(const UINT8_S verIndex,UINT32_S* bnfVersion);


/**********************************************
*函数功能：获取数据子表的版本号
*参数说明：
    输出参数：const UINT8_S subTabType    数据子表类型(具有参见ReadDataTypeDefine.h中相关的定义)
    输出参数：subTabVersion    4字节版本号
*返回值：   0成功，1数据读取不成功
**********************************************/
INT8_S  GetDataSubTabVer(const UINT8_S subTabType,UINT32_S* subTabVersion);

/**********************************************
*函数功能：获取系统间要比较的数据文件的CRC
*参数说明：
    输出参数：const UINT8_S cmpDataFileType    系统间比较数据文件类型(具有参见ReadDataTypeDefine.h中相关的定义)
    输出参数：bnfCrc    4字节Crc
*返回值：   0成功，1数据读取不成功
**********************************************/
INT8_S  GetDataSubTabCrc(const UINT8_S subTabType,UINT32_S* subTabDataCrc);



#ifdef __cplusplus
}
#endif

#endif
