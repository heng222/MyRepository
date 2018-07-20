/*******************************************
* 文件名	：  ZcCommConfigData.c
* 作  者	：  ZC组
* 创建时间	：  2015-5-25
* 功能描述	：	载入ZcCommConfigData数据管理
* 备  注	：  无
*******************************************/

#include "ZcCommConfigData.h"
#include "../../../Dmu/Read/ReadDataTypeDefine.h"
#include "../../../Common/Malloc.h"
#include "../../../Dmu/DmuComm/DataHandle/DmuCommDataTypeDefine.h"

static BnfZcCommConfigStruct* gZcCommConfigDataStru = NULL;   /*定义ZcCommConfigData数据结构体*/
static UINT16_S gLineNumZcCommConfig = 0U;/*表行数*/

/*******************************************
* 函数名	：  MallocZcCommConfigDataStru
* 功能描述	：	给ZcCommConfigDataStru结构体指针分配空间
* 输入：  UINT16_S lineNum 表的数据行数
* 输出：  无
* 返回值：  无
*******************************************/
void MallocZcCommConfigDataStru(UINT16_S lineNum)
{
    if ((lineNum > 0U)&&(NULL == gZcCommConfigDataStru))
    {
        gZcCommConfigDataStru = (BnfZcCommConfigStruct*)MemoryMalloc(((UINT32_S)(lineNum*sizeof(BnfZcCommConfigStruct))));
        gLineNumZcCommConfig = lineNum;
    }
}

/*******************************************
* 函数名	：  GetZcCommConfigData
* 功能描述	：	获取ZcCommConfigData数据
* 输入：  无
* 输出：  无
* 返回值：  BnfZcCommConfigStruct* ZcCommConfigData数据指针
*******************************************/
BnfZcCommConfigStruct *GetZcCommConfigData(void)
{
    return gZcCommConfigDataStru;
}

/*******************************************
* 函数名	：  GetZcCommConfigDataInfo
* 功能描述	：	获取ZcCommConfigData信息
* 输入：  无
* 输出：  UINT16* lineNum  数据行数
* 返回值： BnfZcCommConfigStruct* ZcCommConfigData信息指针
*******************************************/
BnfZcCommConfigStruct *GetZcCommConfigDataInfo(UINT16_S* lineNum)
{
    if (NULL != lineNum)
    {
        *lineNum = gLineNumZcCommConfig;
    }
    
    return gZcCommConfigDataStru;
}
/*******************************************
* 函数名	：  GetZcCommConfigDataStruzcSendAtsDataCycle
* 功能描述	：	获取指定IDZcCommConfigDataStru的ZC向ATS发送数据周期时间(ms)
* 输入：  无
* 输出：  无
* 返回值：  UINT32_NULL: 获取数据失败
*			!=UINT32_NULL: ZC向ATS发送数据周期时间(ms)
*******************************************/
UINT32_S GetZcCommConfigDataStruzcSendAtsDataCycle(void)
{
    UINT32_S retVal = UINT32_NULL;/*函数返回值*/

    if (NULL != gZcCommConfigDataStru)
    {
        retVal = gZcCommConfigDataStru[0].zcSendAtsDataCycle;
    }
    else
    {
        /*不处理*/
    }
    return retVal;
}

