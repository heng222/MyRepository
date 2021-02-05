/*----------------------------------------------------------------
// ��˾���ƣ������빫˾����
// 
// ��Ŀ���ƣ�������Ŀ����
//
// �� �� �ˣ�heng222_z
// �������ڣ�2018/5/28 15:46:41 
// ��    �䣺heng222_z@163.com
//
// Copyright (C) ��˾���ƣ���������Ȩ����
//
//----------------------------------------------------------------*/

using System.Collections.Generic;

using Acl.Presentation;
using Acl.ServiceManagement;

using Products.Domain;
using Products.Infrastructure.Log;
using Products.Infrastructure.Types;
using Products.Plugin1.Controls;
using Products.Presentation;

namespace Products.Plugin1
{
    /// <summary>
    /// ��ϵͳ������
    /// </summary>
    class Activator : FrameworkActivatorBase
    {
        #region "Field"
        private Facade _facade;
        #endregion

        #region "Constructor"
        /// <summary>
        /// ���캯��
        /// </summary>
        public Activator()
            : base(LoggerNames.Plugin1)
        {
        }
        #endregion

        #region "Override methods"

        public override PluginTypes Type { get { return PluginTypes.Plugin1; } }

        protected override void OnBundleStart(IDictionary<string, string> context)
        {
            _facade = new Facade();

            // ע��ӿ�
            _facade.ComponentsToRegister.ForEach(p => ServiceManager.Current.RegisterInstance(p));

            // ������ʾ��
            Workbench.SendMessage(() =>
            {
                // ������ʾ��
                var control = new CtrlMain();
                MainWorkSpace.AddPart(control, control.Icon);

                // �������ҳ�档
                var optionControl = new CtrlConfigPage();
                Workbench.AddOption(optionControl);
            });

            // 
            _facade.Open();
        }

        protected override void OnBundleStop(IDictionary<string, string> context)
        {
            if (_facade != null)
            {
                _facade.Dispose();
                _facade = null;
            }
        }

        protected override void OnFrameworkStarted()
        {

        }
        #endregion


        #region "Private methods"

        #endregion
    }
}
