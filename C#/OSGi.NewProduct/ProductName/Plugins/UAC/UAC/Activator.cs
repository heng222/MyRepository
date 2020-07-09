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

using Acl.ServiceManagement;

using Products.Domain;
using Products.Infrastructure.Log;
using Products.Infrastructure.Types;
using Products.UAC.Domain;

namespace Products.UAC
{
    /// <summary>
    /// 子系统激活器
    /// </summary>
    class Activator : FrameworkActivatorBase
    {
        #region "Field"
        private UacFacade _facade;
        #endregion

        #region "Constructor"
        /// <summary>
        /// 构造函数
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

            // 注册接口
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
