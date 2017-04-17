

#ifndef _DIRECTORY_H_OPERATION_1AC3470C
#define _DIRECTORY_H_OPERATION_1AC3470C
//////////////////////////////////////////////////////////////////////////
#include "MuType.h"

//////////////////////////////////////////////////////////////////////////
// Ŀ¼������̬��
class AFX_EXT_CLASS CDirectory
{
private:
    CDirectory(void);
    ~CDirectory(void);

public:
    //
    // ժҪ:
    //     ȷ������·���Ƿ����ô����ϵ�����Ŀ¼��
    //
    // ����:
    //   path:
    //     Ҫ���Ե�·����
    //
    // ���ؽ��:
    //     ��� path ��������Ŀ¼����Ϊ true������Ϊ false��
    static BOOL Exists(const TString& path);

    // ժҪ:
    //     �� path ��ָ����������Ŀ¼����Ŀ¼��
    //
    // ����:
    //   path:
    //     Ҫ������Ŀ¼·����
    //
    static void CreateDirectory(const TString& path);

    //
    // ժҪ:
    //     ����ָ��Ŀ¼�е��ļ������ơ�
    //
    // ����:
    //   path:
    //     ����������ļ���Ŀ¼��
    //
    // 
    // ���ӣ�
    // std::list<TString> files;
    // CDirectory::GetFiles(_T("C:\\*.*"), files);
    static void GetFiles(const TString& path, std::list<TString>& files);

    // ɾ�����ڵ��ļ�
    static void DeleteExpiredFiles(const TString& path, int expiredDays);
};

//////////////////////////////////////////////////////////////////////////
#endif