
/************************************************************************/
/*
    ������TDateTime
    ����������ʱ����
    ���ã�1. ��һ������������ʱ���ַ����н���������ʱ����Ϣ 
    2. �ṩһЩ���õ�����ʱ���У���㷨
    ��ע��
    ����֧�ֵ�����ʱ���ʽ���£�
    5�����룩
    4:5(�ķ�����)
    5:3:6(��ʱ��������)��ע��������Сʱ�������賿��ʱ������ʱ�䣩
    2-28��2��28�գ�
    2-28 5:3:6��2��28�գ�
    2008-2-28��2008��2��28�գ�
    2008-2-28 17:3:6��2008��2��28��17ʱ3��6�룩

    ��֧��վλ����ʽ��
    -2-  ���趨�·�Ϊ2�£��������ڲ��õ�ǰֵ
    2008-- ���趨��
    :23: ���趨��
    -- :: ȫ��ʡ�ԣ����õ�ǰ����ʱ����ΪĬ��ֵ

    ������ܽ�����ָ���Ĳ��֣������Ĭ��ֵ��Ĭ��ֵΪ��ǰ���ڣ�
*/

#ifndef _TDATETIME_H_20081121_
#define _TDATETIME_H_20081121_

//��windows�£����ǿ��ʹ��32λ��time_t���붨�����º꣺
//#ifndef _USE_32BIT_TIME_T
//#define _USE_32BIT_TIME_T
//#endif
#include <time.h>
#include "MuType.h"

class AFX_EXT_CLASS TDateTime
{

public:

    // ���캯�������õ�ǰ������ʱ����ΪĬ��ֵ
    TDateTime();

    // ���캯������time_t���͵ı�����ȡ������ʱ��
    TDateTime(time_t t);

    // ���캯�������ַ�����ȡ������ʱ��
    TDateTime(LPCTSTR str);

public:

    //���ַ����н���������ʱ�䣬δ�������Ĳ��֣����õ�ǰĬ��ֵ
    BOOL ParseDateTime(LPCTSTR szDateTime);

    //����Ϊ��ǰ������ʱ��
    BOOL LoadCurrentDateTime();

    //ת��ΪUNIX��ʽ��time_tʱ����������
    time_t ToUnixDatetime() const;

    // �����趨����ʱ��ֵ
    void FromUnixDatetime(time_t t);

    // У�鵱ǰ���������ʱ�������Ƿ���ȷ
    BOOL IsValid() const;

    // ��ʽ��Ϊ�ַ�������ʽ
    TString ToString() const;

    // ������������
    double operator-(const TDateTime& another) const;

public:

    // ��ȡ��ǰ������ʱ��
    static void Now(TDateTime& now);

    //У��һ��TDateTime���ͱ���������ʱ�������Ƿ���ȷ
    static BOOL IsValid(const TDateTime *obDateTime);

    //�������Ƿ�������
    static BOOL IsLeapYear(int year);

    //У�����������Ƿ���ȷ
    static BOOL ValidateDate(int year);

    //У���������ݺ��·��Ƿ���ȷ
    static BOOL ValidateDate(int year,int month);

    //ȡ�ø�������ݣ��������·ݺ��е�����
    static int GetDaysOfMonth(int year, int month);

    //У������������������Ƿ���ȷ
    static BOOL ValidateDate(int year, int month, int day);

    //���������Сʱ���ݣ��Ƿ���ȷ
    static BOOL ValidateTime(int hour);

    //У�������Сʱ���������Ƿ���ȷ
    static BOOL ValidateTime(int hour,int minute);

    //У�������ʱ�������Ƿ���ȷ
    static BOOL ValidateTime(int hour, int minute, int second);

    //У�����������ʱ�������Ƿ���ȷ
    static BOOL ValidateDateTime(int year, int month, int day,
        int hour, int minute, int second);


private:

    // token���Ͷ���
    typedef enum TokenType
    {
        TT_Null = 0,
        TT_Number =1,
        TT_Minus = 2,
        TT_Colon = 4,
        TT_Blank = 8

    };

    //����ʱ�����Ͷ���
    typedef enum TimePart
    {
        TP_Second = 1,
        TP_Minute = 2,
        TP_Hour = 4,
        TP_Day = 8,
        TP_Month = 16,
        TP_Year = 32
    };

private:    

    // ����ǰ�����������
    void ZeroDateTime(void);

    // �����ַ�ȡ�ø��ַ�����������
    TDateTime::TokenType GetTokenType(TCHAR c);

public:

    // ��
    unsigned short Year;

    // ��
    unsigned char Month;

    // ��
    unsigned char Day;

    // ʱ
    unsigned char Hour;

    // ��
    unsigned char Minute;

    // ��
    unsigned char Second;

    // ����
    unsigned short MilliSeconds;     

};

//////////////////////////////////////////////////////////////////////////
#endif  //#ifndef _TDATETIME_H_20081121_

