/*----------------------------------------------------------------
// 公司名称：请输入公司名称
// 
// 项目名称：请输入项目名称
//
// 创 建 人：zhangheng
// 创建日期：2016-5-11 13:13:43 
// 邮    箱：zhangheng@163.com
//
// Copyright (C) 公司名称 2019，保留所有权利
//
//----------------------------------------------------------------*/

using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.Text;

namespace Products.Infrastructure.Exceptions
{
    /// <summary>
    /// 程序启动被取消异常。
    /// </summary>
    public sealed class LanuchCanceledException : Exception
    {
        #region "Field"
        #endregion

        #region "Constructor"
        /// <summary>
        /// 初始化一个 <seealso cref="LanuchCanceledException"/> 类的新实例。
        /// </summary>
        public LanuchCanceledException()
            : base()
        {

        }
        /// <summary>
        /// 使用指定的错误消息初始化<seealso cref="LanuchCanceledException"/>类的新实例。
        /// </summary>
        /// <param name="message">描述错误的消息。</param>
        public LanuchCanceledException(string message)
            : base(message)
        {

        }

        /// <summary>
        /// 使用指定错误消息和对作为此异常原因的内部异常的引用来初始化 <seealso cref="LanuchCanceledException"/> 类的新实例。
        /// </summary>
        /// <param name="message">解释异常原因的错误消息。</param>
        /// <param name="ex">导致当前异常的异常；如果未指定内部异常，则是一个 null 引用（在 Visual Basic 中为 Nothing）。</param>
        public LanuchCanceledException(string message, Exception ex)
            : base(message, ex)
        {

        }

        /// <summary>
        /// 用序列化数据初始化<seealso cref="LanuchCanceledException"/>类的新实例。
        /// </summary>
        /// <param name="info">System.Runtime.Serialization.SerializationInfo，它存有有关所引发异常的序列化的对象数据。</param>
        /// <param name="context">System.Runtime.Serialization.StreamingContext，它包含有关源或目标的上下文信息。</param>
        private LanuchCanceledException(SerializationInfo info, StreamingContext context)
            : base(info, context)
        {

        }
        #endregion

        #region "Properties"
        #endregion

        #region "Override methods"
        #endregion

        #region "Private methods"
        #endregion

        #region "Public methods"
        #endregion

    }
}
