
using System.Collections.Generic;
using System.Linq;
using Acl.ServiceManagement;
using Products.Domain;
using Products.Domain.Preferences;
using Products.Infrastructure.Log;
using Products.Infrastructure.Types;
using Products.UAC.Domain;
using Products.Domain.Utility;

namespace Products.UAC.Bridge
{
    /// <summary>
    /// 子系统激活器
    /// </summary>
    class Activator : FrameworkActivatorBase
    {
        #region "Filed"
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

        public override PluginType Type
        {
            get { return PluginType.UAC; }
        }

        protected override void OnBundleStart(IDictionary<string, string> context)
        {
            var settings = BuildSettings(context);
            _facade = new UacFacade(settings);

            // 注册IAlarmEntityQueryable接口
            _facade.ComponentsToRegister.ToList().ForEach(p => ServiceManager.Current.RegisterInstance(p));
        }

        protected override void OnBundleStop(IDictionary<string, string> context)
        {
            //if (_commLifeCycle != null)
            //{
            //    _commLifeCycle.Close();
            //}
        }

        protected override void OnFrameworkStarted()
        {

        }
        #endregion

        #region "private methods"
        private static UacSettings BuildSettings(IDictionary<string, string> settings)
        {
            var adminPwd = GlobalHelper.SplitHexText(settings["AdminPassword"]);

            return new UacSettings(adminPwd);
        }
        #endregion

    }
}
