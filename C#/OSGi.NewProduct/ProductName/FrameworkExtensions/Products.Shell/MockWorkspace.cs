/*----------------------------------------------------------------
// 公司名称：公司名称
// 
// 项目名称：输入项目名称
//
// 创 建 人：zhangheng
// 创建日期：2015-6-11 7:48:57 
// 邮    箱：zhangheng@163.com
//
// Copyright (C) 公司名称 2009，保留所有权利
//
//----------------------------------------------------------------*/

using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Windows.Forms;
using Acl;
using Platform.Presentation;
using Products.Presentation;

namespace Products.Shell
{

    class MockWorkspace : IWorkspace
    {
        internal List<Tuple<ProductPartAttribute, Control>> MainControls = new List<Tuple<ProductPartAttribute, Control>>();

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
            Guard.NotNull(smartPart, "smartPart");

            var info = smartPartInfo as ProductPartAttribute;
            var smartPartType = smartPart.GetType();

            if (info == null)
            {
                info = smartPartType.GetCustomAttributes(false).OfType<ProductPartAttribute>().FirstOrDefault();
            }

            Guard.NotNull(info, "info");

            var control = smartPart as Control;
            if (control == null)
                throw new ArgumentException("无效的SmartPart类型，SmartPart必须是直接或间接继承与Control类!");

            control.Dock = DockStyle.Fill;
            MainControls.Add(new Tuple<ProductPartAttribute,Control>(info, control));
        }

#pragma warning disable 67
        public event EventHandler<WorkspaceEventArgs> SmartPartActivated;

        public event EventHandler<WorkspaceCancelEventArgs> SmartPartClosing;
#pragma warning restore 67

        public System.Collections.ObjectModel.ReadOnlyCollection<object> SmartParts
        {
            get { return new ReadOnlyCollection<object>(MainControls.Select(p=>p.Item2).ToArray()); }
        }
    }
}
