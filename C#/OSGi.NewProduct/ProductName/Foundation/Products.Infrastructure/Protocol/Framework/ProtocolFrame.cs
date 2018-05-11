/*----------------------------------------------------------------
// 公司名称：请输入公司名称
// 
// 项目名称：请输入项目名称
//
// 创 建 人：zhangheng
// 创建日期：03/02/2012 15:13:23 
// 邮    箱：heng222_z@163.com
//
// Copyright (C) 公司名称 2009-2015 保留所有权利
//
//----------------------------------------------------------------*/

using System;
using System.Collections.Generic;
using System.Text;

namespace Products.Infrastructure.Protocol.Framework
{
    /// <summary>
    /// 通讯协议帧基类定义
    /// </summary>
    public abstract class ProtocolFrame
    {
        #region "Filed"
        /// <summary>
        /// 协议的种类
        /// </summary>
        private ProtocolKind _kind;
        #endregion

        #region "Constructor"
        /// <summary>
        /// 使用指定的参数初始化一个协议报文
        /// </summary>
        /// <param name="type">协议种类</param>
        protected ProtocolFrame(ProtocolKind type)
        {
            _kind = type;
        }
        #endregion

        #region "Properties"
        /// <summary>
        /// 获取协议的种类
        /// </summary>
        public ProtocolKind ProtocolKind
        {
            get { return _kind; }
        }
        #endregion

        #region "Virtual methods"

        #endregion

        #region "Private methods"
        #endregion

        #region "Public methods"
        #endregion
    }
}
