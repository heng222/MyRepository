/*************************************************
  文件名   ：ReadManage.h
  作者     ：董欣      
  创建时间 ：2016-8-13
  功能描述 ： 读取Bnf文件管理
			读取Bnf文件管理功能可分解如下：
			1）	读数据函数注册管理；
			2）	读数据处理；
			3）	获取配置数据长度；
			4）	获取配置数据；
			5）	获取系统间比较数据版本号；
			6）	获取整个配置数据文件版本号；
			7）	获取整个配置数据文件；
			8）	获取整个配置数据文件线路编号；
			9）	获取数据子表CRC；
			10）	获取数据子表版本号；
  备注    ：无。 
*************************************************/

#ifndef READ_MANAGE_H_
#define READ_MANAGE_H_

#include "../../Common/CommonTypes.h"
#include "ReadDataTypeDefine.h"


/*读对象结构体*/
typedef struct ReadObjectStruct
{
    INT8_S (*ReadData)(const CHAR_S* bnfFileAddr); /*读数据*/
    INT8_S (*GetCfgDataLen)(UINT8_S mainType, UINT8_S subType,UINT32_S* dataLen, UINT8_S* indexId); /*获取配置数据长度*/
    INT8_S (*GetCfgData)(UINT16_S rowLength,UINT32_S dataLen, UINT8_S indexId,UINT8_S* dataBuf);    /*获取配置数据*/
    
    INT8_S (*GetDataFileVersion)(UINT32_S* dataFileVersion);                                        /*获取数据文件版本号*/
    INT8_S (*GetDataFileCrc)(UINT32_S* dataFileCrc);                                                /*获取数据文件CRC*/
    INT8_S (*GetDataFileSignNum)(UINT32_S* dataFileSignNum);                                        /*获取数据文件线路编号*/
    
    INT8_S (*GetInterSysCmpDataFileVer)(const UINT8_S verIndex,UINT32_S* dataVersion);              /*获取配置数据版本*/
    INT8_S (*GetDataSubTabVer)(const UINT8_S subTabType,UINT32_S* subTabVersion);                   /*获取配置数据子表版本号*/                                          
    INT8_S (*GetDataSubTabCrc)(const UINT8_S subTabType,UINT32_S* subTabCrc);                       /*获取配置数据子表CRC*/

} ReadObjectStruct;


#ifdef __cplusplus
extern "C" {
#endif



/*
* 功能描述： 读管理
* 参数说明： void
* 返回值  ： void       
*/
void ReadManage(void);


/*
* 功能描述： 读数据
* 参数说明： 
* 输入参数 :bnfFileAddr 二进制文件地址
* 返回值  ： 0 成功
            -1 函数指针为空
             1:打开二进制文件失败
             2:读取二进制文件失败
             3:校验失败，版本号不一致
             4:数据标识检查错误
             5:二进制数据文件的地址为空
*/
INT8_S ReadData(CHAR_S* bnfFileAddr);


/*
* 功能描述： 获取配置数据长度
* 参数说明： 
  输入参数：dataType 数据类型   由查询函数宏定义方式给出
            sheetID 数据ID      表单编号        
  输出参数：indexId   结构体指针偏移
            dataLength 数据长度
* 返回值  ： 0 成功
            -1 函数指针为空
            1接口防护错误
            2传入的数据类型和表单编号错误
*/
INT8_S GetConfigDataLen(UINT8_S mainType, UINT8_S subType,UINT32_S* dataLen, UINT8_S* indexId);

/*
* 功能描述： 获取配置数据
* 参数说明： 
  输入参数：UINT16 rowLength   所有列总长度
              dataLength 数据长度
            indexId   结构体指针偏移    
  输出参数：dataBuf   数据地址
* 返回值  ： 0 成功
            -1 函数指针为空
            1接口防护错误
            2拷取数据失败
*/
INT8_S GetConfigData(UINT16_S rowLength,UINT32_S dataLen, UINT8_S indexId,UINT8_S* dataBuf);



/*
* 功能描述： 获取系统间比较数据版本号
* 参数说明： 
* 输入参数: const UINT8_S verIndex 
* 输出参数:dataVersion   数据版本号
* 返回值  ： 0 成功
            -1 函数指针为空
            1数据读取不成功
*/
INT8_S DmuGetIntSysCmpDataFileVer(const UINT8_S cmpVerIndex ,UINT32_S* dataVersion);


/*
* 功能描述： 获取整个配置数据文件版本号
* 参数说明： 
* 输入参数: 无
* 输出参数:dataVersion   整个配置数据文件版本号
* 返回值  ： 0 成功
            -1 函数指针为空
            1数据读取不成功
*/
INT8_S DmuGetDataFileVersion(UINT32_S* dataFileVersion);

/*
* 功能描述： 获取整个配置数据文件CRC
* 参数说明： 
* 输入参数: 无
* 输出参数:dataFileCrc   整个配置数据文件CRC
* 返回值  ： 0 成功
            -1 函数指针为空
            1数据读取不成功
*/
INT8_S DmuGetDataFileCrc(UINT32_S* dataFileCrc);

/*
* 功能描述： 获取整个配置数据文件线路编号
* 参数说明： 
* 输入参数: 无
* 输出参数:dataFileCrc   整个配置数据文件线路编号
* 返回值  ： 0 成功
                          -1 函数指针为空
                          1数据读取不成功
*/
INT8_S DmuGetDataFileSignNum(UINT32_S* dataFileSignNum);

/*
* 功能描述： 获取数据子表CRC
*参数说明：
    输出参数：const UINT8_S subTabType    数据子表类型(具有参见ReadDataTypeDefine.h中相关的定义)
    输出参数：subTabDataCrc    4字节CRC
* 返回值  ： 0 成功
            -1 函数指针为空
            1数据读取不成功
*/
INT8_S  DmuGetDataSubTabCrc(const UINT8_S subTabType,UINT32_S* subTabDataCrc);



/*
* 功能描述： 获取数据子表版本号
*参数说明：
    输出参数：const UINT8_S subTabType    数据子表类型(具有参见ReadDataTypeDefine.h中相关的定义)
    输出参数：subTabDataVer    4字节版本号
* 返回值  ： 0 成功
            -1 函数指针为空
            1数据读取不成功
*/
INT8_S  DmuGetDataSubTabVer(const UINT8_S subTabType,UINT32_S* subTabDataVer);





#ifdef __cplusplus
}
#endif

#endif
