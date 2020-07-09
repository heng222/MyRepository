/*----------------------------------------------------------------
// 公司名称：请输入公司名称
// 
// 项目名称：请输入项目名称
//
// 创 建 人：zhangheng
// 创建日期：2013-7-23 15:14:23 
// 邮    箱：heng222_z@163.com
//
// Copyright (C) 公司名称，保留所有权利。
//
//----------------------------------------------------------------*/

namespace Products.Infrastructure.Specification
{
    /// <summary>
    /// 生命周期管理接口
    /// </summary>
    public interface ILifeCycleManagement
    {
        /// <summary>
        /// 打开
        /// </summary>
        void Open();

        /// <summary>
        /// 关闭
        /// </summary>
        void Close();
    }
}
