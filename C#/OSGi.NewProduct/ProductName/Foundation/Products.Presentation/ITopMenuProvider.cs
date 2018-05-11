/*----------------------------------------------------------------
// 公司名称：请输入公司名称
// 
// 项目名称：输入项目名称
//
// 创 建 人：zhangheng
// 创建日期：2015-2-3 21:20:58 
// 邮    箱：zhangheng@163.com
//
// Copyright (C) 公司名称 2009，保留所有权利
//
//----------------------------------------------------------------*/
using System.Collections.Generic;
using System.Windows.Forms;

namespace Products.Presentation
{
    /// <summary>
    /// 一个可以提供顶级菜单的接口。
    /// </summary>
    public interface ITopMenuItemProvider
    {
        /// <summary>
        /// 获取顶级菜单的位置。0表示首位；-1表示不指定位置，由框架自动分配。
        /// </summary>
        int Position { get; }

        /// <summary>
        /// 获取顶级菜单
        /// </summary>
        /// <returns></returns>
        IEnumerable<ToolStripItem> GetTopMenu();
    }
}
