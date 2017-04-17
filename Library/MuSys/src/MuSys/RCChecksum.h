#pragma once


//crc循环冗余校验(Cyclic Redundancy Check)
class AFX_EXT_CLASS CRCChecksum
{
public:

    // CRC16
    static WORD GetCRC16(const BYTE *pBuf, int iLen);

    // CRC32
    static DWORD GetCRC32( const BYTE *pBuf, int iLen );
};




/*//////////////////////////////////////////////////////////////////////

适用范围：CRC-12码通常用来传送6-bit字符串;CRC-16及CRC-CCITT码则用是来传送

8-bit字符。CRC-32：硬盘数据，网络传输等。

应用例子：rar,以太网卡芯片、MPEG解码芯片中。


*///////////////////////////////////////////////////////////////////////

