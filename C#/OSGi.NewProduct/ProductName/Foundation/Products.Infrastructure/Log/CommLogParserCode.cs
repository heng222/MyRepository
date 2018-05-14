/*----------------------------------------------------------------
// 公司名称：请输入公司名称
// 
// 产品名称：产品名称
//
// 创 建 人：zhangheng
// 创建日期：2018-7-17 14:34:15 
// 邮    箱：heng222_z@163.com
//
// Copyright (C) 2018 公司名称，保留所有权利。
//
//----------------------------------------------------------------*/

using System;
using System.Collections.Generic;
using System.Text;

namespace Products.Infrastructure.Log
{
    /// <summary>
    /// 通讯日志流解析器编码定义
    /// 高两位字节：项目编号，标准版本为0xFFFF，具体项目使用0x0001~0xEFFF之间的一个值。
    /// 低两位字节：顺序号。
    /// </summary>
    public enum CommLogParserCode : uint
    {
        /// <summary>
        /// 无效值。
        /// </summary>
        None = 0,

        /// <summary>
        /// 本系统内部日志流解析器编号。
        /// </summary>
        Internal = 0xFFFF0001,

        #region "系统1"
        /// <summary>
        /// 本系统 与 System1 间的输入流解析器编号。
        /// </summary>
        System1Input = 0xFFFF0004,
        /// <summary>
        /// 本系统与 System1 间的输出流解析器编号。
        /// </summary>
        System1Output = 0xFFFF0005,
        #endregion


        #region "系统2"
        /// <summary>
        /// 本系统与 System2 间的输入流解析器编号。
        /// </summary>
        System2Input = 0xFFFF0010,
        #endregion

    }
}
