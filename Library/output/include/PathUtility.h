
#ifndef _PATHUTILITY_H_OPERATION_5A209330D73C
#define _PATHUTILITY_H_OPERATION_5A209330D73C
//////////////////////////////////////////////////////////////////////////
#include "MuType.h"

// �԰����ļ���Ŀ¼·����Ϣ��ʵ��ִ�в�����
class AFX_EXT_CLASS CPathUtility
{
private:
    CPathUtility(void);
    ~CPathUtility(void);

public:

    //
    // ժҪ:
    //     ����ָ��·���ַ�����Ŀ¼��Ϣ��
    //
    // ����:
    //   fullPath:
    //     �ļ���Ŀ¼��·����
    //   pathName:
    //     Ŀ¼����
    //
    static TString GetDirectoryName(const TString& fullPath);
};

//////////////////////////////////////////////////////////////////////////
#endif