
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

    // 打开文本文件
    void OpenTextFile(LPCTSTR strFileName);

    // 打开二进制文件
    void OpenBinaryFile(LPCTSTR strFileName);

    // 写入一行文本
    void Write(const std::string& strText);
    void Write(const std::wstring& strText);

    // 写入一个二进制数据
    void Write(unsigned char* bytes, int bytesSize);

    // 写入一行文本并换行
    void WriteLine(const std::string& strText);
    void WriteLine(const std::wstring& strText);
    // 写入一个换行符
    void WriteLine();

    // Flush data
    void Flush();

    // 清空数据
    void Clear();

    // 关闭文件流
    void Close();

    // 判断文件是否处于打开状态
    bool IsOpen() const;


private:


};

//////////////////////////////////////////////////////////////////////////
#endif