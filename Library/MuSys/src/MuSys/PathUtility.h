
#ifndef _PATHUTILITY_H_OPERATION_5A209330D73C
#define _PATHUTILITY_H_OPERATION_5A209330D73C
//////////////////////////////////////////////////////////////////////////
#include "MuType.h"

// 对包含文件或目录路径信息的实例执行操作。
class AFX_EXT_CLASS CPathUtility
{
private:
    CPathUtility(void);
    ~CPathUtility(void);

public:

    //
    // 摘要:
    //     返回指定路径字符串的目录信息。
    //
    // 参数:
    //   fullPath:
    //     文件或目录的路径。
    //   pathName:
    //     目录名称
    //
    static TString GetDirectoryName(const TString& fullPath);
};

//////////////////////////////////////////////////////////////////////////
#endif