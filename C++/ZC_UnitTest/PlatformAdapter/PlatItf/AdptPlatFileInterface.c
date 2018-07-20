/********************************************************
* 
* 文 件 名： AdptPlatFileInterface.c
* 作    者： 董欣 
* 创建时间： 2016-09-01 
* 功能描述： 适配层提供给平台层的文件操作接口文件  
* 备    注： 无 
* 
********************************************************/ 

#include "../../cspadpt/GL_Basic_Type_Definition.h"
#include "AdptPlatFileInterface.h"
#include "../../cspadpt/Vcp_File_Interface.h"
#include "../../Common/MemSet.h"
/*
*  功能描述：判断文件是否存在函数
*  参数说明:const CHAR* fileName  文件名称
*  返回值:    1存在   0 不存在
*/
UINT8_S AdptPlatFileExist(const CHAR_S* fileName)
{
    UINT8_S retVal = 0u;/*函数返回值*/
    E_SysBool retIsExit = e_FALSE;/*文件是否存在*/

    if ( fileName != NULL )
    {
        retIsExit = F_VCP_FileExist(fileName);

        if (retIsExit == e_TRUE)
        {
            retVal = 1u;
        } 
        else
        {
            retVal = 0u;
        }
    }

    return retVal;
}

/*
*  功能描述：获取文件信息
*  参数说明:  inFileName    : 输入文件名
*             outFileDetail : 输出文件信息(可以为ptrNULL)
*  返回值:    1获取成功   0 获取失败
*  注: 对一个打开正在写的文件该函数无效
*/
UINT8_S AdptPlatFileInquire(const CHAR_S* fileName, AdptFileDetailStruct* outFileDetail)
{
    UINT8_S retVal = 0u;
    E_SysBool result = e_FALSE;
    T_VCP_FileDetail vcpFileDetail = {0u};

    if ((NULL != outFileDetail) && (NULL != fileName))
    {
        result = F_VCP_FileInquire(fileName,&vcpFileDetail);

        if(e_TRUE == result)
        {
            outFileDetail->Size = vcpFileDetail.Size;

            outFileDetail->CTime.Year = vcpFileDetail.CTime.Year;
            outFileDetail->CTime.Month = vcpFileDetail.CTime.Month;
            outFileDetail->CTime.Day = vcpFileDetail.CTime.Day;
            outFileDetail->CTime.MiSec = vcpFileDetail.CTime.MiSec;

            outFileDetail->LTime.Year = vcpFileDetail.LTime.Year;
            outFileDetail->LTime.Month = vcpFileDetail.LTime.Month;
            outFileDetail->LTime.Day = vcpFileDetail.LTime.Day;
            outFileDetail->LTime.MiSec = vcpFileDetail.LTime.MiSec;

            retVal = 1u;
        }
        else
        {
            retVal = 0u;
        }
    }

    return retVal;
}


/*
*  功能描述：  文件打开函数
*  参数说明:const char* fileName        文件的地址
*            const UINT8 openMode        文件打开方式        
*            FILEType *pfile                句柄
*  返回值:    1成功   0 失败
*/
UINT8_S AdptPlatFileOpen(const CHAR_S* fileName, const UINT8_S openMode, FILEType *pfile)
{
    UINT8_S  retVal = 0u;/*函数返回值*/
    INT32_S  tmpRet = 0;/*函数返回值*/

    if ((NULL != pfile) && (NULL != fileName))
    {
        switch (openMode)
        {
            case AdptFOpenRead:
                tmpRet = F_VCP_FileOpen(fileName, e_VCP_FOpenRead, pfile);
                break;
            case AdptFOpenWrite:
                tmpRet = F_VCP_FileOpen(fileName, e_VCP_FOpenWrite, pfile);
                break;
            case AdptFOpenWriteNCheck:
                tmpRet = F_VCP_FileOpen(fileName, e_VCP_FOpenWriteNCheck, pfile);
                break;
            case AdptFOpenExchange:
                tmpRet = F_VCP_FileOpen(fileName, e_VCP_FOpenExchange, pfile);
                break;
            default:
                break;
        }

        if (c_VCP_FOpenOk == tmpRet)
        {
            retVal = 1u;
        } 
        else
        {
            retVal = 0u;
        }
    }

    return retVal;
}

/*
*  功能描述： 文件读取函数
*  参数说明:    const FILEType pfile                
*            const CHAR* fileName        二进制文件
*            UINT8* dataBuf                数据存储缓存
            UINT32 count                缓存大小
*  返回值:    0 读取失败   >0 文件大小
*/
UINT32_S AdptPlatFileRead (const FILEType pfile,const CHAR_S* fileName,UINT8_S* dataBuf, UINT32_S count)
{
    UINT32_S dataLen = 0u;/*读取数据长度*/
    E_SysBool tmpRetVal = e_FALSE;/*函数返回值*/
    T_VCP_FileDetail outFileDetail = {0u};
    INT32_S retRead = 0;/*读取是否成功*/

    if ((NULL != dataBuf) && (NULL != fileName))
    {
        MemorySet(&outFileDetail, sizeof(T_VCP_FileDetail), 0u, sizeof(T_VCP_FileDetail));

        retRead = F_VCP_FileRead(pfile, count, dataBuf);

        if (retRead == c_VCP_FReadDone)
        {
            tmpRetVal = F_VCP_FileInquire(fileName, &outFileDetail);

            if (e_TRUE == tmpRetVal)
            {
                dataLen = outFileDetail.Size;
            }
        }
    }


    return dataLen;
}

/*
*  功能描述：文件写函数
*  参数说明:const FILEType* fileHUsr,const UINT32 writeLen,UINT8Type writeDataBuf
*  返回值:    1写成功   0 写失败
*/
UINT8_S AdptPlatFileWrite(const FILEType fileHUsr, const UINT32_S writeLen, UINT8_S *writeDataBuf)
{
    UINT8_S retVal = 0u;/*函数返回值*/
    INT32_S retLen = 0;/*文件写返回值*/

    if (NULL != writeDataBuf)
    {
        retLen = F_VCP_FileWrite(fileHUsr, writeLen, writeDataBuf);

        if (retLen == c_VCP_FWriteDone)
        {
            retVal = 1u;
        } 
        else
        {
            retVal = 0u;
        }
    }

    return retVal;
}


/*
*  功能描述：  文件关闭函数文件会主动释放句柄
*  参数说明:FILEType *pfile                句柄或文件
*  返回值:    1成功   0 失败
*/
UINT8_S AdptPlatFileClose(FILEType fileHUsr)
{
    UINT8_S retVal = 0u;/*函数返回值*/
    INT32_S retClose = 0;/*关闭是否成功*/

    retClose = F_VCP_FileClose(fileHUsr, e_TRUE);

    if (retClose == c_VCP_FCloseFinish)
    {
        retVal = 1u;
    } 
    else
    {
        retVal = 0u;
    }

    return retVal;
}

/*
*  功能描述：  文件释放句柄 
*  参数说明:FILEType *pfile                句柄或文件
*  返回值:    1成功   0 失败
*/
UINT8_S AdptPlatFileRelease(FILEType fileHUsr)
{
    UINT8_S retVal = 0u;/*函数返回值*/
    INT32_S retRelease = 0;/*关闭是否成功*/

    retRelease = F_VCP_FileHandleRelease(fileHUsr);

    if (retRelease == c_VCP_FRlsSuccess)
    {
        retVal = 1u;
    } 
    else
    {
        retVal = 0u;
    }

    return retVal;
}


/*
*  功能描述：文件删除函数
*  参数说明:const CHAR* fileName  文件名称
*  返回值:    1删除成功   0 删除失败
*/
UINT8_S AdptPlatFileDelete(const CHAR_S* fileName, FILEType* fileHUsr)
{
    UINT8_S retVal = 0u;/*函数返回值*/
    INT32_S retDelete = 0;/*文件删除返回值*/

    if ((NULL != fileHUsr) && (NULL != fileName))
    {
        retDelete = F_VCP_FileDelete(fileName,fileHUsr);

        if (retDelete == c_VCP_FDeleteFinish)
        {
            retVal = 1u;
        } 
        else
        {
            retVal = 0u;
        }
    }

    return retVal;
}
/*
*  功能描述：查询文件句柄状态
*  参数说明:   fileName  文件名称
*              outProgress 输出进度
*  返回值:   查询操作状态
*/
UINT8_S AdptPlatFileStatusInquire(const FILEType inHUsr, AdptProgressStruct* outProgress)
{
    UINT8_S retVal = 0u;
    INT32_S fileStatus = 0;
    T_VCP_Progress vcpProgress = {0u};

    fileStatus = F_VCP_FileStatusInquire(inHUsr,&vcpProgress); /*查询文件状态*/

    if(NULL != outProgress)
    {
        outProgress->Done = vcpProgress.Done;
        outProgress->LastQuota = vcpProgress.LastQuota;
        outProgress->Total = vcpProgress.Total;

    }

    if (fileStatus == c_VCP_FInqFinish)
    {
        retVal = FILE_INQ_FINISH;
    } 
    else if (fileStatus == c_VCP_FInqDone)
    {
        retVal = FILE_INQ_REQ_DONE;
    }
    else if (fileStatus == c_VCP_FInqErrHandle)
    {
        retVal = FILE_INQ_ERR_HANDLE;
    }
    else
    {
        retVal = FILE_INQ_ERR_FATAL;
    }

    return retVal;
}

/*
*  功能描述：查询另一机的文件状态和大小 
*  参数说明:   inHUsr  文件句柄 
*              outStatus 文件状态 
*              size 文件大小
*  返回值:   0 查询失败  1 查询成功
*/
UINT8_S AdptPlatFileExcStatusInquire(const FILEType inHUsr, UINT8_S* outStatus, UINT32_S* size)
{
    UINT8_S retVal = 0u;
    E_SysBool tempRet = e_FALSE;
    INT32_S fileStatus = 0u;
    T_VCP_FileExInfo outExInfo = {0u};

    tempRet = F_VCP_FileExInfoInquire(inHUsr, &outExInfo);

    if ( e_TRUE == tempRet )
    {
        fileStatus = outExInfo.OperateInfo.Status;

        if (fileStatus == c_VCP_FInqFinish)
        {
            *outStatus = FILE_INQ_FINISH;
        } 
        else if (fileStatus == c_VCP_FInqDone)
        {
            *outStatus = FILE_INQ_REQ_DONE;
        }
        else if (fileStatus == c_VCP_FInqErrHandle)
        {
            *outStatus = FILE_INQ_ERR_HANDLE;
        }
        else
        {
            *outStatus = FILE_INQ_ERR_FATAL;
        }

        *size = outExInfo.ExistInfo.Detail.Size;

        retVal = 1u;
    }
    else
    {
        *outStatus = FILE_INQ_ERR_HANDLE;
        *size = 0u;

        retVal = 0u;
    }

    return retVal;
}

