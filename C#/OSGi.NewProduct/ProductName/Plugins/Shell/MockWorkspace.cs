/*----------------------------------------------------------------
// 公司名称：请输入公司名称
// 
// 项目名称：输入项目名称
//
// 创 建 人：zhangheng
// 创建日期：2015-6-11 7:48:57 
// 邮    箱：zhangheng@163.com
//
// Copyright (C) 公司名称 2019，保留所有权利
//
//----------------------------------------------------------------*/

using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Windows.Forms;

using Acl.Presentation;

using Products.Presentation;

namespace Products.Shell
{
    class MockWorkspace : IWorkspace
    {
        internal Dictionary<ProductPartAttribute, Control> MainControls = new Dictionary<ProductPartAttribute, Control>();

        public void Activate(object smartPart)
        {
        }

        public object ActiveSmartPart
        {
            get { return null; }
        }

        public void ApplySmartPartInfo(object smartPart, ISmartPartInfo smartPartInfo)
        {

        }

        public void Close(object smartPart)
        {

        }

        public void Hide(object smartPart)
        {

        }

        public void Show(object smartPart)
        {
            Show(smartPart, null);
        }

        public void Show(object smartPart, ISmartPartInfo smartPartInfo)
        {
            var info = smartPartInfo as ProductPartAttribute;
            var smartPartType = smartPart.GetType();

            if (info == null)
            {
                info = smartPartType.GetCustomAttributes(false).OfType<ProductPartAttribute>().FirstOrDefault();
            }

            var control = smartPart as Control;
            if (control == null)
            {
                throw new ArgumentException("无效的SmartPart类型，SmartPart必须是直接或间接继承与Control类!");
            }

            if (this.MainControls.ContainsKey(info))
            {
                throw new Exception(string.Format("类型为 {0} 的控件重复，请尝试移除相同的控件或者重命名。", info.ControlType));
            }

            control.Dock = DockStyle.Fill;
            MainControls[info] = control;
        }

#pragma warning disable 67
        public event EventHandler<WorkspaceEventArgs> SmartPartActivated;

        public event EventHandler<WorkspaceCancelEventArgs> SmartPartClosing;
#pragma warning restore 67

        public ReadOnlyCollection<object> SmartParts
        {
            get { return new ReadOnlyCollection<object>(MainControls.Values.ToArray()); }
        }
    }
}
