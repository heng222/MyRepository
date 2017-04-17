
#ifndef _FILESTREAM_H_20110309PO0987Y_
#define _FILESTREAM_H_20110309PO0987Y_

//////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include "MuType.h"

class AFX_EXT_CLASS CFileStream
{
private:

    std::fstream m_fsFile;


public:

    CFileStream(void);

    ~CFileStream(void);


public:

    // ���ı��ļ�
    void OpenTextFile(LPCTSTR strFileName);

    // �򿪶������ļ�
    void OpenBinaryFile(LPCTSTR strFileName);

    // д��һ���ı�
    void Write(const std::string& strText);
    void Write(const std::wstring& strText);

    // д��һ������������
    void Write(unsigned char* bytes, int bytesSize);

    // д��һ���ı�������
    void WriteLine(const std::string& strText);
    void WriteLine(const std::wstring& strText);
    // д��һ�����з�
    void WriteLine();

    // Flush data
    void Flush();

    // �������
    void Clear();

    // �ر��ļ���
    void Close();

    // �ж��ļ��Ƿ��ڴ�״̬
    bool IsOpen() const;


private:


};

//////////////////////////////////////////////////////////////////////////
#endif