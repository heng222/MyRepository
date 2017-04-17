#include "StdAfx.h"

#include "TDateTime.h"
#include <sys/timeb.h>
#include <time.h>



#pragma warning(disable:4996)

//////////////////////////////////////////////////////////////////////////

TDateTime::TDateTime()
{
    LoadCurrentDateTime();
}

TDateTime::TDateTime(time_t t)
{
    FromUnixDatetime(t);
}    

TDateTime::TDateTime(LPCTSTR str)
{
    this->ParseDateTime(str);
}

TDateTime::TokenType TDateTime::GetTokenType(TCHAR c)
{
    if ((c >= _T('0')) && (c <= _T('9')))
    {
        return TT_Number;
    }
    else if (_T('-') == c)
    {
        return TT_Minus;
    }
    else if (_T('/') == c)
    {
        return TT_Minus;
    }
    else if (_T(' ') == c)
    {
        return TT_Blank;
    }
    else if( _T(':') == c)
    {
        return TT_Colon;
    }
    else
    {
        return TT_Null;
    }
}

BOOL TDateTime::ParseDateTime(LPCTSTR szDateTime)
{
    int len = _tcslen(szDateTime) - 1;
    
    TimePart timePart = TP_Second;
    int pw =1;//加权
    signed short year=-1;
    signed char month=-1,day=-1,hour=-1,minute=-1,second=-1;
    //过滤尾部空格
    while((len>=0) && (' ' == szDateTime[len]))
        len--;
    if (len<0) return FALSE;


    while(len>=0){

        TCHAR c = szDateTime[len];

        switch( GetTokenType(c))
        {
        case TT_Null: goto ParseDateTimeString_FALSE;
        case TT_Number:
            switch(timePart)
            {
            case TP_Second:
                if (second<0 )
                    second = c-'0';
                else
                    second += (c-'0') * pw;
                pw *= 10;
                break;
            case TP_Minute:
                if (minute<0 )
                    minute = c-'0';
                else
                    minute += (c-'0') * pw;
                pw *= 10;
                break;
            case TP_Hour:
                if (hour<0 )
                    hour = c-'0';
                else
                    hour += (c-'0') * pw;
                pw *= 10;
                break;
            case TP_Day:
                if (day<0 )
                    day = c-'0';
                else
                    day += (c-'0') * pw;
                pw *= 10;
                break;
            case TP_Month:
                if (month<0 )
                    month = c-'0';
                else
                    month += (c-'0') * pw;
                pw *= 10;
                break;
            case TP_Year:
                if (year<0 )
                    year = c-'0';
                else
                    year += (c-'0') * pw;
                pw *= 10;
                break;
            default:
                return FALSE;
            }
            break;
        case TT_Minus:
            switch(timePart)
            {
            case TP_Second: //如果没有给定时间信息，则跳过，直接升级到日期
                pw =1;
                timePart = TP_Month; //提升                
                day = second;
                second = -1;  //将解析到的秒信息改为日期信息
                break;
            case TP_Minute: goto ParseDateTimeString_FALSE;                
            case TP_Hour: goto ParseDateTimeString_FALSE;
            case TP_Day:
                pw =1;
                timePart = TP_Month; //提升                
                break;
            case TP_Month:
                pw =1;
                timePart = TP_Year; //提升                
                break;
            case TP_Year: goto ParseDateTimeString_FALSE;                
            default: goto ParseDateTimeString_FALSE;
            }
            break;
        case TT_Colon:
            switch(timePart)
            {
            case TP_Second:
                pw =1;
                timePart = TP_Minute; //提升                    
                break;
            case TP_Minute: 
                pw =1;
                timePart = TP_Hour; //提升                    
                break;
            case TP_Hour: goto ParseDateTimeString_FALSE;
            case TP_Day: goto ParseDateTimeString_FALSE;                
            case TP_Month: goto ParseDateTimeString_FALSE;                
            case TP_Year: goto ParseDateTimeString_FALSE;                
            default: goto ParseDateTimeString_FALSE;
            }
            break;
        case TT_Blank:
            if (TP_Hour == timePart){
                timePart = TP_Day; //提升
                pw =1;
            }else if (TP_Year == timePart){  //前导空格
                goto ParseDateTimeString_OK;//认为结束                
            }else{//在其他部分不能出现空格
                goto ParseDateTimeString_FALSE;
            }
            break;
        }
        len -- ;
    }

ParseDateTimeString_OK:
    if (year>0)
        Year = year;
    if (month>0)
        Month = month;
    if (day>0)
        Day = day;
    if (hour>=0)
        Hour = hour;
    if (minute>=0)
        Minute = minute;
    if (second>=0)
        Second = second;

    if (IsValid()){
        return TRUE;
    }else{
        ZeroDateTime();
        return FALSE;
    }

ParseDateTimeString_FALSE:
    ZeroDateTime();
    return FALSE;
}

BOOL TDateTime::LoadCurrentDateTime()
{    
    _timeb tb;
    _ftime(&tb);

    FromUnixDatetime(tb.time);

    this->MilliSeconds = tb.millitm;

    return TRUE;
}

void TDateTime::FromUnixDatetime(time_t t)
{
    struct tm *tt = localtime(&t);
    Year = tt->tm_year + 1900;
    Month = tt->tm_mon + 1;
    Day = tt->tm_mday;
    Hour = tt->tm_hour;
    Minute = tt->tm_min;
    Second = tt->tm_sec;
}

void TDateTime::ZeroDateTime(void)
{
    Year = 0;
    Month = 0;
    Day = 0;
    Hour = 0;
    Minute = 0;
    Second = 0;
    MilliSeconds = 0;
}


/// <summary>
/// 判定给定的年份是否是润年
/// </summary>
/// <param name="year">需要判定的年份</param>
/// <returns>true:给定的年份是润年。false:给定的年份不是润年。</returns>
BOOL TDateTime::IsLeapYear(int year)
{
    return ((year % 4 == 0) && (year % 100 != 0) || (year % 400 == 0));                               
}

/// <summary>
/// 判定给定的年份是否有效。
/// </summary>
/// <param name="year">给定的年份</param>
/// <returns>true:有效,false:无效</returns>
BOOL TDateTime::ValidateDate(int year)
{
    return (year > 0) && (year <= 9999);
}

/// <summary>
/// 判定给定的年月是否有效
/// </summary>
/// <param name="year">给定的年份</param>
/// <param name="month">给定的月份</param>
/// <returns>true:有效。false:无效。</returns>
BOOL TDateTime::ValidateDate(int year,int month)
{
    if (!ValidateDate(year))
        return FALSE;
    return (month > 0) && (month < 13);
}

/// <summary>
/// 得到一个月份的天数
/// </summary>
/// <param name="year">年</param>
/// <param name="month">月</param>
/// <returns>返回该年该月的总天数，如果给定的参数有错误，则返回0</returns>
int TDateTime::GetDaysOfMonth(int year, int month)
{
    if (!ValidateDate(year, month))
    {
        return 0;
    }

    if (month == 4 || month == 6 || month == 9 || month == 11)
    {
        return 30;
    }
    else if (month == 1 || month == 3 || month == 5
        || month == 7 || month == 8 || month == 10 || month == 12)
    {
        return 31;
    }
    else if (2 == month)
    {
        if (IsLeapYear(year))//如果是闰年
        {
            return 29;
        }
        else
        {
            return 28;
        }
    }

    return 0;
}

/// <summary>
/// 判定给定的年月日是否是一个有效的日期
/// </summary>
/// <param name="year">给定的年份</param>
/// <param name="month">给定的月份</param>
/// <param name="day">给定的日子</param>
/// <returns>true:给定的年月日是一个有效的日期。false:不是一个有效的日期。</returns>
BOOL TDateTime::ValidateDate(int year, int month, int day)
{
    if (!ValidateDate(year, month))
        return FALSE;

    if ((day < 1) || (day > GetDaysOfMonth(year, month)))
        return FALSE;

    return TRUE;                        
}

/// <summary>
/// 判定给定的小事是否有效
/// </summary>
/// <param name="hour">给定的小时</param>
/// <returns>true:有效;false:无效</returns>
BOOL TDateTime::ValidateTime(int hour)
{
    return (hour >= 0) && (hour < 24);
}

/// <summary>
/// 判定给定的小时和分钟是否有效。
/// </summary>
/// <param name="hour">给定的小时</param>
/// <param name="minute">给定的分钟</param>
/// <returns>true:有效;false:无效</returns>
BOOL TDateTime::ValidateTime(int hour,int minute)
{
    if (!ValidateTime(hour))
        return FALSE;
    return (minute >= 0) && (minute < 60);
}

/// <summary>
/// 判定给定的小时、分钟、秒时否有效
/// </summary>
/// <param name="hour">给定的小时</param>
/// <param name="minute">给定的分钟</param>
/// <param name="second">给定的秒</param>
/// <returns>true:有效;false:无效</returns>
BOOL TDateTime::ValidateTime(int hour, int minute, int second)
{
    if (!ValidateTime(hour,minute))
        return FALSE;
    return (second >= 0) && (second < 60);
}

/// <summary>
/// 判定给定的年月日时分秒是否是一个有效的日期时间
/// </summary>
/// <param name="year">给定的年份</param>
/// <param name="month">给定的月份</param>
/// <param name="day">给定的日子</param>
/// <param name="hour">给定的小时</param>
/// <param name="minute">给定的分钟</param>
/// <param name="second">给定的秒</param>
/// <returns>true:有效;false:无效</returns>
BOOL TDateTime::ValidateDateTime(int year, int month, int day,
                            int hour, int minute, int second)
{
    return ValidateDate(year, month, day)
        && ValidateTime(hour, minute, second);
}

void TDateTime::Now(TDateTime& now)
{
    now.LoadCurrentDateTime();
}

BOOL TDateTime::IsValid() const
{
    return TDateTime::IsValid(this);
}   

TString TDateTime::ToString() const
{
    TCHAR buf1[30];

    _sntprintf_s(buf1, 30, _T("%d-%02d-%02d %02d:%02d:%02d"), 
        this->Year, this->Month, this->Day, this->Hour, this->Minute, this->Second);

    return buf1;
}


double TDateTime::operator-(const TDateTime& another) const
{
    time_t difference = this->ToUnixDatetime() - another.ToUnixDatetime();
    return difference / 86400.0; // 1 day = 86400 senconds
}

BOOL TDateTime::IsValid(const TDateTime *obDateTime)
{
    return ValidateDateTime(obDateTime->Year,obDateTime->Month, obDateTime->Day,
        obDateTime->Hour, obDateTime->Minute, obDateTime->Second);
}

time_t TDateTime::ToUnixDatetime() const
{    
    tm tt;
    tt.tm_year = Year - 1900;
    tt.tm_mon = Month -1;
    tt.tm_mday = Day;
    tt.tm_hour = Hour;
    tt.tm_min = Minute;
    tt.tm_sec = Second;
    return mktime(&tt); 
}
