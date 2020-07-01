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

using Products.Resource;

namespace Products.Infrastructure.Log
{
    /// <summary>
    /// 通讯日志流解析器编码定义
    /// </summary>
    public abstract class CommLogParserCode
    {
        /// <summary>
        /// 无效值。
        /// </summary>
        public static readonly uint None = 0;

        /// <summary>
        /// 本系统内部日志流解析器编号。
        /// </summary>
        public static readonly UInt32 Internal = (uint)((ProductResources.ProjectCode << 16) + 0x0001);


        #region "系统1"
        /// <summary>
        /// 本系统 与 System1 间的输入流解析器编号。
        /// </summary>
        public static readonly UInt32 System1Input = (uint)((ProductResources.ProjectCode << 16) + 0x0004);
        /// <summary>
        /// 本系统与 System1 间的输出流解析器编号。
        /// </summary>
        public static readonly UInt32 System1Output = (uint)((ProductResources.ProjectCode << 16) + 0x0005);
        #endregion
    }
}
