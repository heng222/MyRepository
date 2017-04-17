

#ifndef _DIRECTORY_H_OPERATION_1AC3470C
#define _DIRECTORY_H_OPERATION_1AC3470C
//////////////////////////////////////////////////////////////////////////
#include "MuType.h"

//////////////////////////////////////////////////////////////////////////
// 目录操作静态类
class AFX_EXT_CLASS CDirectory
{
private:
    CDirectory(void);
    ~CDirectory(void);

public:
    //
    // 摘要:
    //     确定给定路径是否引用磁盘上的现有目录。
    //
    // 参数:
    //   path:
    //     要测试的路径。
    //
    // 返回结果:
    //     如果 path 引用现有目录，则为 true；否则为 false。
    static BOOL Exists(const TString& path);

    // 摘要:
    //     按 path 的指定创建所有目录和子目录。
    //
    // 参数:
    //   path:
    //     要创建的目录路径。
    //
    static void CreateDirectory(const TString& path);

    //
    // 摘要:
    //     返回指定目录中的文件的名称。
    //
    // 参数:
    //   path:
    //     将从其检索文件的目录。
    //
    // 
    // 例子：
    // std::list<TString> files;
    // CDirectory::GetFiles(_T("C:\\*.*"), files);
    static void GetFiles(const TString& path, std::list<TString>& files);

    // 删除过期的文件
    static void DeleteExpiredFiles(const TString& path, int expiredDays);
};

//////////////////////////////////////////////////////////////////////////
#endif