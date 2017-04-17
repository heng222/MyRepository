

#ifndef _FILE_H_OPERATION_AFFA31BC5045
#define _FILE_H_OPERATION_AFFA31BC5045
//////////////////////////////////////////////////////////////////////////
#include "MuType.h"

//////////////////////////////////////////////////////////////////////////
// 文件操作工具类
class AFX_EXT_CLASS CFileUtility
{
private:
    CFileUtility(void);
    ~CFileUtility(void);

public:
    //
    // 摘要:
    //     返回指定文件或目录的创建日期和时间。
    //
    // 参数:
    //   path:
    //     要获取其创建日期和时间信息的文件或目录。
    //
    // 返回结果:
    //     一个 System.DateTime 结构，它被设置为指定文件或目录的创建日期和时间。该值用本地时间表示。
    static time_t GetCreationTime(const TString& path);

    //
    // 摘要:
    //     删除指定的文件。
    //
    // 参数:
    //   path:
    //     要删除的文件的名称。
    static void Delete(const TString& path);

};


//////////////////////////////////////////////////////////////////////////
#endif