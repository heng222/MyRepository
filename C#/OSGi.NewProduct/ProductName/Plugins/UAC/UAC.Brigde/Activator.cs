
using System;
using System.Linq;
using Acl.ServiceManagement;
using OSGi;
using Platform.Bundles.Bridge;
using Platform.Bundles.Bridge.Utilities;
using Products.Domain.Preferences;
using Products.Infrastructure.Log;
using Products.UAC.Domain;

namespace Products.UAC.Bridge
{
    /// <summary>
    /// 子系统激活器
    /// </summary>
    class Activator : BundleActivatorBase, IFrameworkListener, IDisposable
    {
        #region "Filed"
        private bool _disposed = false;
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

        ~Activator()
        {
            this.Dispose(false);
        }
        #endregion


        #region "Protected methods"

        protected override void OnStart(IBundleContext context)
        {
            // 添加监听器
            context.AddFrameworkListener(this);

            var settings = BuildSettings(context);
            _facade = new UacFacade(settings);

            // 注册IAlarmEntityQueryable接口
            _facade.ComponentsToRegister.ToList().ForEach(p => ServiceManager.Current.RegisterInstance(p));

            //// 创建表示层
            //Workbench.SendMessage(() =>
            //{
            //    // 获取所需要的服务
            //    var alarmEntity = ServiceManager.Current.Get<IAlarmEntityQueryable>();

            //    // 配置文件存放路径
            //    var cfgPath = Path.GetDirectoryName(Assembly.GetExecutingAssembly().Location) + @"\Config\";

            //    // 创建表示层
            //    var control = new AlarmControlManager(
            //        alarmEntity,
            //        cfgPath,
            //        NodeContextManager.Current);

            //    control.Initialize();

            //    // 向主窗体添加控件
            //    var partAttri = new AtsPartAttribute { ControlType = PresentationControlType.AlarmControl, DefaultIcon = control.Icon };
            //    MainWorkSpace.AddPart(control.View, partAttri);

            //    // 添加报警配置页面。
            //    var optionControl = new AlarmConfigPage(alarmEntity, cfgPath);
            //    Workbench.AddOption(optionControl);
            //});
        }

        protected override void OnStop(IBundleContext context)
        {

        }
        #endregion

        #region "private methods"
        private static UacSettings BuildSettings(IBundleContext context)
        {
            var settings = ServiceUtility.GetSettings(context);

            var adminPwd = SettingsUtility.GetByteArray(settings, "AdminPassword", 16);

            return new UacSettings(adminPwd);
        }
        #endregion

        #region IFrameworkListener 成员

        public void FrameworkEvent(FrameworkEvent e)
        {
            try
            {
                //if (e.Type == FrameworkEventType.Started)
                //{
                //    ThreadPool.QueueUserWorkItem((p) =>
                //    {
                //        try
                //        {
                //            if (_commLifeCycle != null)
                //            {
                //                Thread.Sleep(3000);

                //                Log.Info("正在打开通讯组件...");
                //                _commLifeCycle.Open();
                //                Log.Info("通讯组件已打开。");
                //            }

                //            Thread.Sleep(10000);
                //            CommStreamLogManager.DeleteExpiredLog();
                //        }
                //        catch (System.Exception /*ex*/)
                //        {
                //              this.Log.Error(ex);
                //        }
                //    });
                //}
            }
            catch (System.Exception ex)
            {
                base.Log.Error(ex);
            }
        }

        #endregion

        #region "IDisposable 成员"
        protected virtual void Dispose(bool disposing)
        {
            if (!_disposed)
            {
                if (disposing)
                {
                    // 在此处释放托管资源
                }

                // 在此处是否非托管资源。

                _disposed = true;
            }
        }

        public void Dispose()
        {
            this.Dispose(true);
            GC.SuppressFinalize(this);
        }
        #endregion
    }
}
