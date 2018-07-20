/*******************************************
文件名	：ParsePackInterfaceDefine.h
作者	：董欣
创建时间：2016-10
描述	：接口数据头文件
备注	：无
*******************************************/

#ifndef PARSEPACK_INTERFACE_DEFINE_H_
#define PARSEPACK_INTERFACE_DEFINE_H_

/*ATS到DSU命令宏定义*/
#define ZC_TO_ATS_TSR_NORMAL_REPORT        0x0080         /*正常汇报TSR*/
#define ZC_TO_ATS_TSR_RESET_REPORT         0x0070         /*重启后汇报TSR*/
#define ATS_TO_ZC_TSR_FRT_CONFIRM          0x0071u         /*首次上电确认*/
#define ZC_TO_ATS_TSR_FRT_CONFIRM_REPLY   0x0072u         /*首次上电确认回复*/
#define ATS_TO_ZC_TSR_SEC_CONFIRM         0x0073u         /*再次上电确认*/
#define ZC_TO_ATS_TSR_SEC_CONFIRM_REPLY   0x0074u         /*再次上电确认回复*/
#define ATS_TO_ZC_TSR_FRT_SET              0x0090u         /*首次设置*/
#define ZC_TO_ATS_TSR_FRT_SET_REPLY       0x0091u         /*首次设置回复*/
#define ATS_TO_ZC_TSR_SEC_SET              0x0092u         /*再次设置*/
#define ZC_TO_ATS_TSR_SEC_SET_REPLY        0x0093u         /*再次设置回复*/
#define ATS_TO_ZC_TSR_FRT_CANCEL           0x00A0u         /*首次取消*/
#define ZC_TO_ATS_TSR_FRT_CANCEL_REPLY     0x00A1u         /*首次取消回复*/
#define ATS_TO_ZC_TSR_SEC_CANCEL           0x00A2u         /*再次取消*/
#define ZC_TO_ATS_TSR_SEC_CANCEL_REPLY     0x00A3u         /*再次取消回复*/

/*TSR回应码-通用*/
#define TSR_UNKNOWN                0u                 /*未知（DSU给ATS首次设置应答信息）*/
#define TSR_OK                     1u                 /*成功*/
#define TSR_RANDOMCODE_SEC_DIFFER_FROM_FIR                     2u                 /*二次命令与首次命令的随机码不一致*/
#define TSR_OUTOFSETTIME_BETWEEN_FIR_SEC_CMD    3u/*等待二次命令超时*/
#define TSR_CRC32_CHECK_ERROR    4u/*二次命令CRC32校核失败*/
#define TSR_ATS_FRMAE_TYPE_INCORRECT    5u/*ATS报文类型错误*/
/*TSR回应码-上电确认*/
#define TSR_FIR_CONFIRM_CMD_INCORRECT        20u/*首次去上电上电确认命令错误（之前有其他的命令）*/
#define TSR_SEC_CONFIRM_CMD_INCORRECT        21u/*二次去上电上电确认命令错误（之前的命令不是首次上电确认命令）*/
#define TSR_FIR_CONFIRM_CMD_INCORRECT_YETCONFIRMED        22u/*首次去上电上电确认命令错误（系统状态已转为正常工作后又发送了首次上电确认命令）*/
/*TSR回应码-设置临时限速*/
#define TSR_FIR_SET_CMD_INCORRECT        30u/*首次设置临时限速命令错误（之前有其他的命令）*/
#define TSR_SEC_SET_CMD_INCORRECT        31u/*二次设置临时限速命令错误（之前的命令不是首次设置临时限速命令）*/
#define TSR_TSRQUANTITY_OVERFLOW            32u/*设置临时限速个数大于最大值*/
#define TSR_FIR_SET_TSRSPEEDVALUE_OVERFLOW            33u/*首次设置临时限速的速度大于最大限速值*/
#define TSR_FIR_SET_TSRSPEEDVALUE_GREATERTHAN_STATICDEFAULTVALUE            34u/*首次设置临时限速的速度大于本次设置逻辑区段最小静态限速值*/
#define TSR_SEC_SET_TSRSPEEDVALUE_DIFFERFROMFIR            35u/*二次和首次设置临时限速的速度不一致*/
#define TSR_FIR_SET_TSRLOGICSECTIONQUANTITY_OVERFLOW            36u/*首次设置临时限速的逻辑区段个数大于最大逻辑区段个数*/
#define TSR_FIR_SET_NOTCOMPLYWITHRULES_LOGICSECTIONOUTOFTHISZC            37u/*首次设置临时限速的逻辑区段规则抵触（逻辑区段存在不属于本ZC内）*/
#define TSR_FIR_SET_NOTCOMPLYWITHRULES_LOGICSECTIONHASBEENSET            38u/*首次设置临时限速的逻辑区段规则抵触（逻辑区段和已经设置的临时限速的逻辑区段有重合）*/
#define TSR_FIR_SET_NOTCOMPLYWITHRULES_LOGICSECTIONSARENOTONEBYONE            39u/*首次设置临时限速的逻辑区段规则抵触（逻辑区段不连续）*/
#define TSR_FIR_SET_NOTCOMPLYWITHRULES_LOGSECATBOTHSWITCHPOSITON_A            40u/*首次设置临时限速的逻辑区段规则抵触（逻辑区段包含某个道岔的定反位）*/
#define TSR_FIR_SET_NOTCOMPLYWITHRULES_LOGSECATBOTHSWITCHPOSITON_B            41u/*首次设置临时限速的逻辑区段规则抵触（逻辑区段同已经设置临时限速逻辑区段包含某个道岔的定反位）*/
#define TSR_SEC_SET_TSRLOGICSECTIONQUANTITY_OVERFLOW            42u/*二次设置临时限速的逻辑区段个数大于最大逻辑区段个数*/
#define TSR_SEC_SET_TSRLOGICSECTIONQUANTITY_DIFFERFROMFIR            43u/*二次和首次设置临时限速的逻辑区段个数不一致*/
#define TSR_SEC_SET_TSRLOGICSECTIONID_DIFFERFROMFIR            44u/*二次和首次设置临时限速的逻辑区段ID不一致*/
/*TSR回应码-取消临时限速*/
#define TSR_FIR_CANCEL_CMD_INCORRECT            60u/*首次取消临时限速命令错误（之前有其他的命令）*/
#define TSR_SEC_CANCEL_CMD_INCORRECT            61u/*二次取消临时限速命令错误（之前的命令不是首次取消临时限速命令）*/
#define TSR_FIR_CANCEL_CMD_INCORRECT_ZCHASNOTSR            64u/*首次取消临时限速错误（ZC没有临时限速）*/
#define TSR_FIR_CANCEL_TSRLOGICSECTIONQUANTITY_OVERFLOW           65u/*首次取消临时限速的逻辑区段个数大于最大逻辑区段个数*/
#define TSR_FIR_CANCEL_CMD_INCORRECT_NOTSET           66u/*首次取消临时限速错误（没有找到对应设置的临时限速）*/
#define TSR_SEC_CANCEL_TSRLOGICSECTIONQUANTITY_OVERFLOW           67u/*二次取消临时限速的逻辑区段个数大于最大逻辑区段个数*/
#define TSR_SEC_CANCEL_TSRLOGICSECTIONQUANTITY_DIFFERFROMFIR           68u/*二次和首次设置临时限速的逻辑区段个数不一致*/
#define TSR_SEC_CANCEL_TSRLOGICSECTIONID_DIFFERFROMFIR           69u/*二次和首次设置临时限速的逻辑区段ID不一致*/

/*最近一次ATS设置命令类型*/
#define LAST_ATS_SET_CMD_DEFAULT    0u              /*默认值 没有命令*/
#define LAST_ATS_FR_SET_CMD         1u				/*首次设置命令*/
#define LAST_ATS_FR_CANCEL_CMD      2u				/*首次取消命令*/
#define LAST_ATS_FR_CONFIRM_CMD     3u				/*首次去上电命令*/
#define LAST_ATS_SR_SET_CMD         4u
#define LAST_ATS_SR_CANSCEL_CMD      5u
#define LAST_ATS_SR_CONFIRM_CMD     6u

#endif 
