/******************************************************************************
 *File Name	     :	Vcp_File_Interface.h
 *Copyright	     :	Zhuzhou CSR Times Electric Co.,Ltd. All Rights Reserved.
 *Create Date    :	2014/02/15
 *Module Id      :  SD-SM_PAB-1012
 *Description    :	SM提供的有关PAB的文件操作接口
 *                  以库函数的形式提供
 *
 *+----------+---------------------------------------------------------------+
 *| Design   |    轨道交通信号系统通用安全计算机平台主机插件SM_PAB           |
 *|  File    |    软件详细设计说明书Vcp_File_Interface组件_B.1               |
 *+----------+--------------+------------+-----------------------------------+
 *| Version  |    Author    |    Date    |            Description            |
 *+----------+--------------+------------+-----------------------------------+
 *| C.A.0001 | ZhuHui       | 2014/02/15 |  File Create                      |
 *+----------+--------------+------------+-----------------------------------+
 *
 ******************************************************************************/

/******************************************************************************
 *    Multi-Include-Prevent Start Section
 ******************************************************************************/
#ifndef VCP_FILE_INTERFACE_H_
#define VCP_FILE_INTERFACE_H_

/******************************************************************************
 *    Debug switch Section
 ******************************************************************************/

/******************************************************************************
 *    Include File Section
 ******************************************************************************/
#include "GL_Basic_Type_Definition.h"
#include "Vcp_Service_Interface.h"

/******************************************************************************
 *    Global Macro Define Section
 ******************************************************************************/



typedef enum enum_config_dat_type
{
	ENUM_CONFIG_DAT_TYPE_INVALID = 0x00U,    /*无效配置类型*/
	ENUM_CONFIG_DAT_TYPE_CIAPP = 0x55U,      /*CI APP配置*/
	ENUM_CONFIG_DAT_TYPE_CIID =  0x88U,        /*CI ID配置*/	
	ENUM_CONFIG_DAT_TYPE_RSSPI = 0xAAU,      /*RSSPI配置*/
	ENUM_CONFIG_DAT_TYPE_LOG = 0xCCU      /* 日志配置 */

}ENUM_TYPE_CONFIG_DAT;

typedef struct 
{
	UINT8        filetype;                     /* File Type */
	UINT8        fileid;                       /* File ID */
	UINT32       filesize;                     /* File Size */
	UINT32       fileoffset;                   /* File Offset*/

}ADPTER_PACKED APP_CONFIG_PER_FILE_HEAD;

typedef struct 
{
	UINT32      phymemaddr;                  /*starting physical memory addr*/	
	UINT8       filenum;                     /* File Number */
	APP_CONFIG_PER_FILE_HEAD  perfile[MAX_CFG_FILE_NUMBER];

}ADPTER_PACKED APP_CONFIG_HEAD;


APP_CONFIG_HEAD g_App_Config_Head;


/*最大文件数*/
#define c_VCP_MaxFileNum      (128UL)
/*最大文件名长度*/
#define c_VCP_MaxFileNameLen  (63UL)
/*最大同时读写文件数*/
#define c_VCP_MaxFileRwNum    (6UL)
/*最大缓冲删除文件数*/
#define c_VCP_MaxDelFileNum   (6UL)
/*读写缓冲大小*/
#define c_VCP_RwBuffSize      (1024UL * 1024UL)
/*对齐长度*/
#define c_VCP_SAlignLen       (4UL)

/*列文件目录 F_VCP_FileDir*/
/*缺少空间                    */
#define c_VCP_DirLackSpace          (   -1L)

/*打开 F_VCP_FileOpen*/
/*打开成功                    */
#define c_VCP_FOpenOk               ( 0xF0L)
/*正在打开, 稍后查询结果      */
#define c_VCP_FOpenIng              ( 0xF1L)
/*打开故障                    */
#define c_VCP_FOpenErrFatal         (-0xFFL)
/*错误的文件名长度            */
#define c_VCP_FOpenErrNameLen       (-0xF1L)
/*超过最大读写数              */
#define c_VCP_FOpenErrOverNum       (-0xF2L)
/*冲突, 文件有未结束的操作    */
#define c_VCP_FOpenErrConflict      (-0xF3L)
/*写已存在的文件              */
/*读不存在的文件              */
#define c_VCP_FOpenErrExistent      (-0xF4L)
/*Flash空间不足               */
#define c_VCP_FOpenErrLackSpace     (-0xA1L)

/*写 F_VCP_FileWrite*/
/*正在写                      */
#define c_VCP_FWriteIng             ( 0xA2L)
/*写完成, (Init)              */
#define c_VCP_FWriteDone            ( 0xA3L)
/*写失败                      */
#define c_VCP_FWriteErrFatal        (-0xAFL)
/*无效的句柄                  */
#define c_VCP_FWriteErrHandle       (-0xA0L)
/*等待打开                    */
#define c_VCP_FWriteErrWaitOpen     (-0xA1L)
/*长度不正确(未对齐)          */
#define c_VCP_FWriteErrImproperLen  (-0xA2L)
/*正在关闭                    */
#define c_VCP_FWriteErrClosing      (-0xA3L)
/*超过缓冲区长度,请分片       */
#define c_VCP_FWriteErrOverSize     (-0xA4L)
/*缓冲区中任务过多,请等待     */
#define c_VCP_FWriteErrWait         (-0xA5L)
/*Flash空间不足               */
#define c_VCP_FWriteErrLackSpace    (-0xA6L)

/*读 F_VCP_FileRead*/
/*正在读                      */
#define c_VCP_FReadIng              ( 0xB2L)
/*读完成(读满缓冲), (Init)    */
#define c_VCP_FReadDone             ( 0xB3L)
/*读失败                      */
#define c_VCP_FReadErrFatal         (-0xBFL)
/*无效的句柄                  */
#define c_VCP_FReadErrHandle        (-0xB0L)
/*等待打开                    */
#define c_VCP_FReadErrWaitOpen      (-0xB1L)
/*长度不正确(未对齐)          */
#define c_VCP_FReadErrImproperLen   (-0xB2L)
/*正在关闭                    */
#define c_VCP_FReadErrClosing       (-0xB3L)
/*等待读完成                  */
#define c_VCP_FReadErrWaitDone      (-0xB4L)

/*删 F_VCP_FileDelete*/
/*删除完成(Init)              */
#define c_VCP_FDeleteFinish         ( 0xC0L)
/*正在申请删                  */
#define c_VCP_FDeleteReq            ( 0xC1L)
/*正在删                      */
#define c_VCP_FDeleteIng            ( 0xC2L)
/*删失败, 请重试              */
#define c_VCP_FDeleteErrFatal       (-0xCFL)
/*错误的文件名长度            */
#define c_VCP_FDeleteErrNameLen     (-0xC1L)
/*超过最大删除数              */
#define c_VCP_FDeleteErrOverNum     (-0xC2L)
/*冲突, 文件未关闭            */
#define c_VCP_FDeleteErrConflict    (-0xC3L)
/*删不存在的文件              */
#define c_VCP_FDeleteErrInexistent  (-0xC4L)

/*关闭 F_VCP_FileClose*/
/*关闭完成                    */
#define c_VCP_FCloseFinish          ( 0xF0L)
/*关闭进行中                  */
#define c_VCP_FCloseIng             ( 0xF2L)
/*关闭失败                    */
#define c_VCP_FCloseErrFatal        (-0xFFL)
/*无效的句柄                  */
#define c_VCP_FCloseErrHandle       (-0xF0L)
/*拒绝，一般关闭必须读写完成  */
#define c_VCP_FCloseErrReject       (-0xF1L)
/*校验错误(Init)              */
#define c_VCP_FCloseWErrCheck       (-0xA7L)

/*查询操作状态 */
/*F_VCP_FileStatusInquire & F_VCP_FileStatusInquireExt*/
/*通用*/
/*完成                        */
/*R: 读关闭成功               */
/*W: 写关闭并校验成功         */
/*D: 删完成                   */
#define c_VCP_FInqFinish            ( 0xF0L)
/*正在申请读/写/删            */
#define c_VCP_FInqReq               ( 0xF1L)
/*正在进行读/写/删            */
#define c_VCP_FInqIng               ( 0xF2L)
/*完成申请打开/读/写          */
#define c_VCP_FInqDone              ( 0xF3L)
/*无效的句柄                  */
#define c_VCP_FInqErrHandle         (-0xF0L)
/*操作执行失败,关闭句柄       */
#define c_VCP_FInqErrFatal          (-0xFFL)
/*查询->打开->写*/
/*空间不足   */
#define c_VCP_FInqOpenWErrLackSpace (c_VCP_FOpenErrLackSpace)
/*查询->写*/
/*写结束, 正在检查            */
#define c_VCP_FInqWriteCheck        ( 0xA4L)
/*空间不足                    */
#define c_VCP_FInqWriteLackSpace    ( 0xA5L)
/*校验错误     */
#define c_VCP_FInqWriteErrCheck     (c_VCP_FCloseWErrCheck)

/*释放句柄 F_VCP_FileHandleRelease*/
/*释放句柄成功               */
#define c_VCP_FRlsSuccess           ( 0xF0L)
/*错误的句柄                 */
#define c_VCP_FRlsErrHandle         (-0xF0L)
/*删除未完成, 不允许释放     */
#define c_VCP_FRlsErrReject         (-0xF1L)
/*其他文件正在删除, 无法释放 */
#define c_VCP_FRlsErrWait           (-0xF2L)



/******************************************************************************
 *    Global Struct    Define Section
 ******************************************************************************/
/*定义文件打开方式*/
typedef enum TAG_VCP_FileOpenOption
{
  e_VCP_FOpenRead        = 0,  /*读方式打开文件              */
  e_VCP_FOpenWrite       = 1,  /*写新文件方式打开文件, 带校验*/
  e_VCP_FOpenExchange    = 2,  /*文件信息交换                */
  e_VCP_FOpenWriteNCheck = 3   /*写新文件方式打开文件, 无校验*/
}E_VCP_FileOpenOpt;

/*进度*/
typedef struct TAG_VCP_Progress
{
  UINT32 Total    ; /* 总任务量             */
  UINT32 Done     ; /* 总完成量             */
  UINT32 LastQuota; /* 最后一次申请的任务量 */
}T_VCP_Progress;

/*定义文件详细信息*/
typedef struct TAG_VCP_FileDetail
{
  UINT32     Size ;  /*文件大小    */
  T_RealClk  CTime;  /*创建时间    */
  T_RealClk  LTime;  /*最后访问时间*/
}T_VCP_FileDetail;

/*定义文件列表信息*/
typedef struct TAG_VCP_FileDir
{
  CHARACTER        Name[c_VCP_MaxFileNameLen + 1UL];  /*文件名  */
  T_VCP_FileDetail Detail                          ;  /*文件信息*/
}T_VCP_FileDir;

/*文件操作类型*/
typedef enum TAG_VCP_FileOperateType
{
  e_VCP_FOperateNone     = 0,  /*无*/
  e_VCP_FOperateReading  = 2,  /*读*/
  e_VCP_FOperateWriting  = 3,  /*写*/
  e_VCP_FOperateDeleting = 5   /*删*/
}E_VCP_FileOperateType;

/*文件存在状态*/
typedef enum TAG_VCP_FileExistStatus
{
  e_VCP_FExistUnknown = 0,  /*未知  */
  e_VCP_FExistTrue    = 1,  /*存在  */
  e_VCP_FExistFalse   = 2   /*不存在*/
}E_VCP_FileExistStatus;

/*文件操作信息*/
typedef struct TAG_VCP_FileOperateInfo
{
  E_VCP_FileOperateType Type    ;  /*类型*/
  INT32                 Status  ;  /*状态*/
  T_VCP_Progress        Progress;  /*进度*/
  T_Checksum            CheckSum;  /*校验*/
}T_VCP_FileOperateInfo;

/*文件存在信息*/
typedef struct TAG_VCP_FileExistInfo
{
  E_VCP_FileExistStatus Status;  /*状态*/
  T_VCP_FileDetail      Detail;  /*信息*/
}T_VCP_FileExistInfo;

/*文件交换信息*/
typedef struct TAG_VCP_FileExInfo
{
  T_VCP_FileExistInfo   ExistInfo  ;  /*存在信息*/
  T_VCP_FileOperateInfo OperateInfo;  /*操作信息*/
}T_VCP_FileExInfo;


/******************************************************************************
 *    Global Variable Declare Section
 ******************************************************************************/


/******************************************************************************
 *    Global Prototype Declare Section
 ******************************************************************************/
/******************************************************************************
 *Name      : F_VCP_GetIdleSpace
 *Function  : 获取Flash空闲空间
 *Para      : void
 *Return    : 空闲空间大小(字节)
 *Note      :
 ******************************************************************************/
INT32 F_VCP_GetIdleSpace(void);


/******************************************************************************
 *Name      : F_VCP_FileExist
 *Function  : 查询文件是否存在
 *Para      : @inFileName : 输入文件名
 *Return    : 如果文件存在返回e_TRUE，否则返回e_FALSE
 *Note      :
 ******************************************************************************/
E_SysBool F_VCP_FileExist(const CHARACTER* inFileName);


/******************************************************************************
 *Name      : F_VCP_FileInquire
 *Function  : 获取文件信息
 *Para      : @inFileName    : 输入文件名
 *            @outFileDetail : 输出文件信息(可以为ptrNULL)
 *Return    : 如果获取成功=>返回e_TRUE，否则返回e_FALSE
 *Note      : 对一个打开正在写的文件该函数无效
 ******************************************************************************/
E_SysBool F_VCP_FileInquire(const CHARACTER*  inFileName,
                            T_VCP_FileDetail* outFileDetail);


/******************************************************************************
 *Name      : F_VCP_FileDir
 *Function  : 列出文件列表
 *Para      : @outFileDir : 输出文件列表
 *            @inNum      : 输入文件列表缓冲数量
 *Return    : c_VCP_DirLackSpace表示缓冲区太小，其它表示获取的文件个数
 *Note      :
 ******************************************************************************/
INT32 F_VCP_FileDir(T_VCP_FileDir outFileDir[],
                    const INT32   inNum);


/******************************************************************************
 *Name      : F_VCP_FileOpen
 *Function  : 打开文件(R/W/E)
 *Para      : @inFileName : 输入文件名
 *            @inOpenOpt  : 输入打开类型
 *            @outHUsr    : 输出用户文件句柄
 *Return    : 返回打开状态
 *Note      :
 ******************************************************************************/
INT32 F_VCP_FileOpen(const CHARACTER*        inFileName,
                     const E_VCP_FileOpenOpt inOpenOpt,
                     INT32* const            outHUsr);


/******************************************************************************
 *Name      : F_VCP_FileRead
 *Function  : 读取文件
 *Para      : @inHUsr     : 输入用户句柄
 *            @inReadLen  : 输入读取长度
 *            @inReadBuff : 输入读取数据缓冲
 *Return    : 返回读取状态
 *Note      : 必须此HUsr之前的读请求已经完成，才能响应此次请求
 ******************************************************************************/
INT32 F_VCP_FileRead(const INT32  inHUsr,
                     const UINT32 inReadLen,
                     UINT8*       inReadBuff);


/******************************************************************************
 *Name      : F_VCP_FileWrite
 *Function  : 写入文件
 *Para      : @inHUsr      : 输入用户句柄
 *            @inWriteLen  : 输入写入长度
 *            @inWriteBuff : 输入写入数据缓冲
 *Return    : 返回写入状态
 *Note      :
 ******************************************************************************/
INT32 F_VCP_FileWrite(const INT32  inHUsr,
                      const UINT32 inWriteLen,
                      UINT8*       inWriteBuff);


/******************************************************************************
 *Name      : F_VCP_FileClose / F_VCP_FileCloseExt
 *Function  : 关闭句柄
 *Para      : @inHUsr    : 输入用户句柄
 *            @inIsForce : 输入是否强制关闭 (无效参数)
 *Return    : 返回关闭状态
 *Note      : 为了向后兼容, 两函数行为上有如下区别
 *            F_VCP_FileClose    : 非周期阶段, 系统会主动释放句柄
 *            F_VCP_FileCloseExt : 非周期阶段, 系统不会主动释放句柄
 ******************************************************************************/
INT32 F_VCP_FileClose(const INT32     inHUsr,
                      const E_SysBool inIsForce);
INT32 F_VCP_FileCloseExt(const INT32 inHUsr);


/******************************************************************************
 *Name      : F_VCP_FileDelete
 *Function  : 删除文件
 *Para      : @inFileName : 输入文件名
 *            @outHUsr    : 输出用户句柄
 *Return    : 返回删除状态
 *Note      :
 ******************************************************************************/
INT32 F_VCP_FileDelete(const CHARACTER* inFileName,
                       INT32*           outHUsr);


/******************************************************************************
 *Name      : F_VCP_FileStatusInquire / F_VCP_FileStatusInquireExt
 *Function  : 查询文件句柄状态
 *Para      : @inHUsr         : 输入用户句柄
 *            @outProgress    : 输出进度
 *            @outOperateInfo : 输出操作信息
 *Return    : 返回文件句柄对应状态
 *Note      : 1. 为保证兼容性, F_VCP_FileStatusInquire查询返回c_VCP_FInqFinish或
 *               负值, 平台会主动释放句柄
 *            2. 为方便用户使用, F_VCP_FileStatusInquireExt任何情况下,
 *               平台不会释放句柄, 需要用户通过F_VCP_FileHandleRelease释放
 ******************************************************************************/
INT32 F_VCP_FileStatusInquire(const INT32     inHUsr,
                              T_VCP_Progress* outProgress);
INT32 F_VCP_FileStatusInquireExt(const INT32            inHUsr,
                                 T_VCP_FileOperateInfo* outOperateInfo);



/******************************************************************************
 *Name      : F_VCP_FileHandleRelease
 *Function  : 释放句柄
 *Para      : @inHUsr : 输入用户句柄
 *Return    : 返回文件句柄释放状态
 *Note      :
 ******************************************************************************/
INT32 F_VCP_FileHandleRelease(const INT32 inHUsr);


/******************************************************************************
 *Name      : F_VCP_FileExInfoInquire
 *Function  : 查询交换的文件信息
 *Para      : @inHUsr    : 输入用户句柄
 *            @outExInfo : 输出交换信息
 *Return    : 如果句柄正确返回e_TRUE，否则返回e_FALSE
 *Note      :
 ******************************************************************************/
E_SysBool F_VCP_FileExInfoInquire(const INT32       inHUsr,
                                  T_VCP_FileExInfo* outExInfo);




/******************************************************************************
 *Name      : F_VCP_FileExInfoInquire
 *Function  : 查询交换的文件信息
 *Para      : @inHUsr    : 输入用户句柄
 *            @outExInfo : 输出交换信息
 *Return    : 如果句柄正确返回e_TRUE，否则返回e_FALSE
 *Note      :
 ******************************************************************************/



GM_BOOL CSPADPT_Get_SpeciConfig_Addr_Size(ENUM_TYPE_CONFIG_DAT m_Type, UINT8* m_Addr, UINT32* m_Size);

APP_CONFIG_HEAD* CSPADPT_Get_App_Config_File_Head(void);

VOID* CSPADPT_Get_User_Config_Addr();

#endif



