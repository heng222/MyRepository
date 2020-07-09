/*----------------------------------------------------------------
// 公司名称：请输入公司名称
// 
// 项目名称：输入项目名称
//
// 创 建 人：zhangheng
// 创建日期：2015-2-2 10:43:04 
// 邮    箱：heng222_z@163.com
//
// Copyright (C) 公司名称 2019，保留所有权利
//
//----------------------------------------------------------------*/

namespace Products.Infrastructure
{
    /// <summary>
    /// 用户登录结果
    /// </summary>
    public enum UserLogOnResult
    {
        /// <summary>
        /// 取消
        /// </summary>
        Canceled,

        /// <summary>
        /// 验证成功
        /// </summary>
        Successful,

        /// <summary>
        /// 验证失败
        /// </summary>
        Failure,
    }

    /// <summary>
    /// 用户登录接口
    /// </summary>
    public interface IUserLogOn
    {
        /// <summary>
        /// 显示登录对话框。
        /// </summary>
        /// <returns>用户登录结果</returns>
        UserLogOnResult ShowLogOnDialog();
    }
}
