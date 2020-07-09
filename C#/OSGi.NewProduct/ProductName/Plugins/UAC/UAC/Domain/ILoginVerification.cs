/*----------------------------------------------------------------
// 公司名称：请输入公司名称
// 
// 项目名称：输入项目名称
//
// 创 建 人：zhangheng
// 创建日期：2015-2-3 21:20:58 
// 邮    箱：zhangheng@163.com
//
// Copyright (C) 公司名称 2019，保留所有权利
//
//----------------------------------------------------------------*/

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
        void Logoff();
    }
}
