/*----------------------------------------------------------------
// ��˾���ƣ������빫˾����
// 
// ��Ŀ���ƣ�������Ŀ����
//
// �� �� �ˣ�zhangheng
// �������ڣ�2015-6-11 7:48:57 
// ��    �䣺zhangheng@163.com
//
// Copyright (C) ��˾���� 2019����������Ȩ��
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
                throw new ArgumentException("��Ч��SmartPart���ͣ�SmartPart������ֱ�ӻ��Ӽ̳���Control��!");
            }

            if (this.MainControls.ContainsKey(info))
            {
                throw new Exception(string.Format("����Ϊ {0} �Ŀؼ��ظ����볢���Ƴ���ͬ�Ŀؼ�������������", info.ControlType));
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
