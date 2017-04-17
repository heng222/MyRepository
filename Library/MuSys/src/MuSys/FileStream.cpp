#include "StdAfx.h"
#include "FileStream.h"
#include "StringUtility.h"

//////////////////////////////////////////////////////////////////////////

using namespace std;

CFileStream::CFileStream(void)
{
}

CFileStream::~CFileStream(void)
{
    Close();
}

void CFileStream::OpenTextFile(LPCTSTR strFileName)
{
    if (m_fsFile.is_open())
    {
        m_fsFile.close();
    }

    // 以文本、追加、可读可写方式打开
    m_fsFile.open(strFileName, ios::app | ios::in | ios::out);

    // 使用系统默认的本地设置
    m_fsFile.imbue(locale(""));    
}


void CFileStream::OpenBinaryFile(LPCTSTR strFileName)
{
    if (m_fsFile.is_open())
    {
        m_fsFile.close();
    }

    // 以二进制、追加、可读可写方式打开
    m_fsFile.open(strFileName, ios::binary | ios::app | ios::in | ios::out);
}


void CFileStream::Write(const std::string& strText)
{
    m_fsFile<<strText.c_str();
}

void CFileStream::Write(const std::wstring& strText)
{
    std::string ansiString = CStringUtility::UnicodeToAnsi(strText);

    this->Write(ansiString);
}

void CFileStream::Write(unsigned char* bytes, int bytesSize)
{
    m_fsFile.write((LPCSTR)bytes, bytesSize);
}

void CFileStream::WriteLine(const std::string& strText)
{
    this->Write(strText);
    this->WriteLine();
}

void CFileStream::WriteLine(const std::wstring& strText)
{
    this->Write(strText);
    this->WriteLine();
}

void CFileStream::WriteLine()
{
    m_fsFile<<endl;
}

void CFileStream::Flush()
{
    m_fsFile.flush();
}

void CFileStream::Clear()
{
    m_fsFile.clear();
}

void CFileStream::Close()
{
    if (m_fsFile.is_open())
    {
        m_fsFile.close();
    }
}

bool CFileStream::IsOpen() const
{
    return m_fsFile.is_open();
}