/*----------------------------------------------------------------
// ��˾���ƣ���˾����
// 
// ��Ŀ���ƣ�������Ŀ����
//
// �� �� �ˣ�zhangheng
// �������ڣ�2015-6-11 7:48:57 
// ��    �䣺zhangheng@163.com
//
// Copyright (C) ��˾���� 2009����������Ȩ��
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
                throw new ArgumentException("��Ч��SmartPart���ͣ�SmartPart������ֱ�ӻ��Ӽ̳���Control��!");

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
