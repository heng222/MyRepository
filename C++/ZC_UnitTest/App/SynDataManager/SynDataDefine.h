/************************************************************************
*
* 文件名   ：  SynDataDefine.h
* 创建时间 ：  2015.04.18
* 作者     ：  ZC组
* 功能描述 ：  2系同步宏定义
* 备  注   ：  无
*
************************************************************************/
#ifndef SYN_DATA_DEFINE_H_
#define SYN_DATA_DEFINE_H_

/*发送的帧*/
#define SYN_DATA_MAX_NUM  100000U    /*帧数据的最大长度*/
#define SYN_DATA_CONTENT_HEAD1  0xFFU    /*帧的头信息1*/
#define SYN_DATA_CONTENT_HEAD2  0xF0U   /*帧的头信息2*/

#define SYN_DATA_START_INDEX  10U          /*帧内容开始下标*/
#endif 
