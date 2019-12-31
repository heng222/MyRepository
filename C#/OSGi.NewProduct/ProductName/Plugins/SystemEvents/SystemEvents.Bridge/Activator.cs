
using System.Collections.Generic;
using System.Threading.Tasks;
using Acl.ServiceManagement;
using Platform.Presentation;
using Products.Domain;
using Products.Infrastructure.Log;
using Products.Infrastructure.Types;
using Products.Presentation;
using Products.SystemEvents.Bridge.Properties;
using Products.SystemEvents.Controls;
using Products.SystemEvents.Domain;

namespace Products.SystemEvents.Bridge
{
    /// <summary>
    /// 子系统激活器
    /// </summary>
    class Activator : FrameworkActivatorBase
    {
        #region "Filed"
        private EventFacade _facade;
        #endregion

        #region "Constructor"
        /// <summary>
        /// 构造函数
        /// </summary>
        public Activator()
            : base(LoggerNames.SEM)
        {
        }
        #endregion

        #region "Override methods"

        public override PluginType Type
        {
            get { return PluginType.SEM; }
        }

        protected override void OnBundleStart(IDictionary<string, string> context)
        {
            _facade = new EventFacade();

            // 注册 ISystemEventManage 接口
            ServiceManager.Current.RegisterInstance(_facade.SEM);

            // 创建表示层
            Workbench.SendMessage(() =>
            {
                // 创建表示层
                MainWorkSpace.AddPart(new CtrlSysEvents(), Resources.SystemEvent);
                MainWorkSpace.AddPart(new CtrlOperationRecord(), Resources.OperationLog);

                //// 添加配置页面。
                //var optionControl = new Plugin1ConfigPage();
                //Workbench.AddOption(optionControl);
            });
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
            try
            {
                Task.Factory.StartNew(() =>
                {
                    try
                    {
                        _facade.Open();
                    }
                    catch (System.Exception ex)
                    {
                        this.Log.Error(ex);
                    }
                });
            }
            catch (System.Exception ex)
            {
                base.Log.Error(ex);
            }
        }
        #endregion

    }
}
