/*----------------------------------------------------------------
// ��˾���ƣ������빫˾����
// 
// ��Ŀ���ƣ�������Ŀ����
//
// �� �� �ˣ�zhangheng
// �������ڣ�2015-2-3 21:20:58 
// ��    �䣺zhangheng@163.com
//
// Copyright (C) ��˾���� 2019����������Ȩ��
//
//----------------------------------------------------------------*/
using System.Collections.Generic;

using Acl.ServiceManagement;

using Products.Domain;
using Products.Infrastructure.Log;
using Products.Infrastructure.Types;
using Products.UAC.Domain;

namespace Products.UAC
{
    /// <summary>
    /// ��ϵͳ������
    /// </summary>
    class Activator : FrameworkActivatorBase
    {
        #region "Field"
        private UacFacade _facade;
        #endregion

        #region "Constructor"
        /// <summary>
        /// ���캯��
        /// </summary>
        public Activator()
            : base(LoggerNames.UAC)
        {
        }
        #endregion


        #region "Override methods"

        public override PluginTypes Type
        {
            get { return PluginTypes.UAC; }
        }

        protected override void OnBundleStart(IDictionary<string, string> context)
        {
            var settings = BuildSettings(context);
            _facade = new UacFacade(settings);

            // ע��ӿ�
            _facade.ComponentsToRegister.ForEach(p => ServiceManager.Current.RegisterInstance(p));
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

        #region "private methods"
        private static UacSettings BuildSettings(IDictionary<string, string> settings)
        {
            //var settings = ServiceUtility.GetSettings(context);

            //var adminPwd = SettingsUtility.GetByteArray(settings, "AdminPassword", 16);

            return new UacSettings();
        }
        #endregion

    }
}
