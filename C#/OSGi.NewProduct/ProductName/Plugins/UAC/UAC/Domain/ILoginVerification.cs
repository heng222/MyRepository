/*----------------------------------------------------------------
// 公司名称：公司名称
// 
// 产品名称：ATS
//
// 创 建 人：heng222_z
// 创建日期：2018/5/22 14:14:21 
// 邮    箱：heng222_z@163.com
//
// Copyright (C) 2018 ATS，保留所有权利。
//
//----------------------------------------------------------------*/

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Products.UAC.Domain
{
    /// <summary>
    /// 登录验证接口。
    /// </summary>
    interface ILoginVerification
    {
        /// <summary>
        /// 登录
        /// </summary>
        void LogOn(string userName, byte[] pwdMd5);
        
        /// <summary>
        /// 注销
        /// </summary>
        void Logoff(string userName);
    }
}
