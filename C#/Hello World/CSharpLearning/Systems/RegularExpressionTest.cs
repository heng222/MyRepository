/*----------------------------------------------------------------
// 公司名称：北京交大微联科技有限公司
// 
// 项目名称：北京地铁15号线ATS项目
//
// 创 建 人：zhangheng
// 创建日期：06/28/2011 09:43:59 
// 邮    箱：zhangheng@bjmut.com
//
// Copyright (C) 北京交大微联科技有限公司 2009-2015 保留所有权利
//
//----------------------------------------------------------------*/

using System;
using System.Collections.Generic;
using System.Text;
using System.Text.RegularExpressions;
using NUnit.Framework;

namespace CSharpLearning
{
    [TestFixture(Description="正则表达式测试")]
    internal class RegularExpressionTest
    {
        public static void Show()
        {

            string input0 = "1,23,12";
            string input1 = "123";
            string input2 = "1";
            string input3 = "1,";
            string input4 = "a";
            string input5 = "1,bb,12";

            string pattern = "^[0-9]+(,[0-9]+)*$"; // 1,60,20 (CSV format)
            //string pattern = "^([0-1]?[0-9]|2[0-3]):[0-5]?[0-9]:[0-5]?[0-9]$"; // 时间

            bool flag0 = Regex.IsMatch(input0, pattern);
            bool flag1 = Regex.IsMatch(input1, pattern);
            bool flag2 = Regex.IsMatch(input2, pattern);
            bool flag3 = Regex.IsMatch(input3, pattern);
            bool flag4 = Regex.IsMatch(input4, pattern);
            bool flag5 = Regex.IsMatch(input5, pattern);

            string ipInput0 = "192.168.3.234";
            string ipInput1 = "192.168.3.256";
            string ipPattern = @"^(\d{1,2}|1\d\d|2[0-4]\d|25[0-5])\.(\d{1,2}|1\d\d|2[0-4]\d|25[0-5])\.(\d{1,2}|1\d\d|2[0-4]\d|25[0-5])\.(\d{1,2}|1\d\d|2[0-4]\d|25[0-5])$";// IP地址
            bool flag6 = Regex.IsMatch(ipInput0, ipPattern);
            bool flag7 = Regex.IsMatch(ipInput1, ipPattern);
        }
    }
}
