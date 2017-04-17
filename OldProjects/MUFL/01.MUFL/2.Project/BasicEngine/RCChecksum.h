#pragma once


//crcѭ������У��(Cyclic Redundancy Check)
class AFX_EXT_CLASS CRCChecksum
{
public:

    // CRC16
    static WORD GetCRC16(const BYTE *pBuf, int iLen);

    // CRC32
    static DWORD GetCRC32( const BYTE *pBuf, int iLen );
};




/*//////////////////////////////////////////////////////////////////////

���÷�Χ��CRC-12��ͨ����������6-bit�ַ���;CRC-16��CRC-CCITT��������������

8-bit�ַ���CRC-32��Ӳ�����ݣ����紫��ȡ�

Ӧ�����ӣ�rar,��̫����оƬ��MPEG����оƬ�С�


*///////////////////////////////////////////////////////////////////////

