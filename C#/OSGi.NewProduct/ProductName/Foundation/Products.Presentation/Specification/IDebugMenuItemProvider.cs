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
using System.Collections.Generic;
using System.Windows.Forms;

namespace Products.Presentation.Specification
{
    /// <summary>
    /// 一个可以提供调试菜单的接口。
    /// </summary>
    public interface IDebugMenuItemProvider
    {
        /// <summary>
        /// 获取菜单项。
        /// </summary>
        /// <returns>菜单项列表。</returns>
        IEnumerable<ToolStripItem> GetMenuItems();
    }
}
