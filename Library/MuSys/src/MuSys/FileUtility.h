

#ifndef _FILE_H_OPERATION_AFFA31BC5045
#define _FILE_H_OPERATION_AFFA31BC5045
//////////////////////////////////////////////////////////////////////////
#include "MuType.h"

//////////////////////////////////////////////////////////////////////////
// �ļ�����������
class AFX_EXT_CLASS CFileUtility
{
private:
    CFileUtility(void);
    ~CFileUtility(void);

public:
    //
    // ժҪ:
    //     ����ָ���ļ���Ŀ¼�Ĵ������ں�ʱ�䡣
    //
    // ����:
    //   path:
    //     Ҫ��ȡ�䴴�����ں�ʱ����Ϣ���ļ���Ŀ¼��
    //
    // ���ؽ��:
    //     һ�� System.DateTime �ṹ����������Ϊָ���ļ���Ŀ¼�Ĵ������ں�ʱ�䡣��ֵ�ñ���ʱ���ʾ��
    static time_t GetCreationTime(const TString& path);

    //
    // ժҪ:
    //     ɾ��ָ�����ļ���
    //
    // ����:
    //   path:
    //     Ҫɾ�����ļ������ơ�
    static void Delete(const TString& path);

};


//////////////////////////////////////////////////////////////////////////
#endif