/*----------------------------------------------------------------
// 公司名称：公司名称
// 
// 产品名称：ATS
//
// 创 建 人：heng222_z
// 创建日期：2017/9/4 16:55:25 
// 邮    箱：heng222_z@163.com
//
// Copyright (C) 2017 ATS，保留所有权利。
//
//----------------------------------------------------------------*/

using System.Windows.Forms;

using WeifenLuo.WinFormsUI.Docking;

namespace Products.Ats.Shell.Utilities
{
    static class ShellHelper
    {
        public static DockState Convert(DockStyle value)
        {
            if (value == DockStyle.Left) return DockState.DockLeft;
            else if (value == DockStyle.Right) return DockState.DockRight;
            else if (value == DockStyle.Top) return DockState.DockTop;
            else if (value == DockStyle.Bottom) return DockState.DockBottom;
            else if (value == DockStyle.Fill) return DockState.Document;
            else return DockState.DockBottom;
        }

        public static DockAlignment Convert(AnchorStyles value)
        {
            if (value == AnchorStyles.Left) return DockAlignment.Left;
            else if (value == AnchorStyles.Right) return DockAlignment.Right;
            else if (value == AnchorStyles.Top) return DockAlignment.Top;
            else if (value == AnchorStyles.Bottom) return DockAlignment.Bottom;
            else return DockAlignment.Left;
        }
    }
}
