
using System;
using Framework.OSGi;
using Platform.Bundles.Bridge;
using Platform.Presentation;
using Products.Infrastructure.Log;
using Products.Plugin1.Controls;
using Products.Presentation;

namespace Products.Plugin1.Bridge
{
    /// <summary>
    /// 子系统激活器
    /// </summary>
    class Activator : BundleActivatorBase, IFrameworkListener, IDisposable
    {
        #region "Filed"
        private bool _disposed = false;

        #endregion

        #region "Constructor"
        /// <summary>
        /// 构造函数
        /// </summary>
        public Activator()
            : base(LoggerNames.Plugin1)
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
            //var facade = new AlarmFacade();
            //_lifeCycle = facade;
            //_lifeCycle.Open();

            //// 注册IAlarmEntityQueryable接口
            //ServiceManager.Current.RegisterInstance(facade.AlarmQueryable);

            // 创建表示层
            Workbench.SendMessage(() =>
            {
                // 获取所需要的服务
                //var alarmEntity = ServiceManager.Current.Get<IAlarmEntityQueryable>();


                // 创建表示层
                var control = new Plugin1Control1();
                MainWorkSpace.AddPart(control, control.Icon);

                // 添加配置页面。
                var optionControl = new Plugin1ConfigPage();
                Workbench.AddOption(optionControl);
            });
        }

        protected override void OnStop(IBundleContext context)
        {
            //if (_commLifeCycle != null)
            //{
            //    _commLifeCycle.Close();
            //}
        }
        #endregion

        #region "private methods"

        //private static AtpSettings BuildAtpSettings(IBundleContext context)
        //{
        //    var settings = ServiceUtility.GetSettings(context);
        //    var safetyProtocol = (SafetyCommProtocol)settings.Get<byte>("SafetyProtocol");
        //    var commLogExpiredDays = (byte)SettingsUtility.GetDecimal(settings, "CommLogExpiredDays", 1, 255, 7);
        //    var isMachineA = NodeContextManager.LocalNodeCode < NodeContextManager.SiblingCode;

        //    IPAddress redIP, blueIP;
        //    if (NodeContextManager.LocalNodeType == NodeType.TrainTestLineWorkstation)
        //    {
        //        redIP = IPAddress.Parse(settings.Get<string>("TestLineRedIP"));
        //        blueIP = IPAddress.Parse(settings.Get<string>("TestLineBlueIP"));
        //    }
        //    else
        //    {
        //        if (isMachineA)
        //        {
        //            redIP = IPAddress.Parse(settings.Get<string>("RedNetIP1"));
        //            blueIP = IPAddress.Parse(settings.Get<string>("BlueNetIP1"));
        //        }
        //        else
        //        {
        //            redIP = IPAddress.Parse(settings.Get<string>("RedNetIP2"));
        //            blueIP = IPAddress.Parse(settings.Get<string>("BlueNetIP2"));
        //        }
        //    }

        //    // DSU Index
        //    byte dsuIndex = 1;
        //        dsuIndex = (byte)SettingsUtility.GetDecimal(settings, "MainLineDsuIndex", 1, 255, 1);

        //    result.CommLogExpiredDays = commLogExpiredDays;

        //    return result;
        //}
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
                                //this.Log.Error(ex);
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
