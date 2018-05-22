
using System;
using Framework.OSGi;
using Platform.Bundles.Bridge;
using Products.Infrastructure.Log;

namespace Products.Plugin2.Bridge
{
    /// <summary>
    /// ��ϵͳ������
    /// </summary>
    class Activator : BundleActivatorBase, IFrameworkListener, IDisposable
    {
        #region "Filed"
        private bool _disposed = false;

        #endregion

        #region "Constructor"
        /// <summary>
        /// ���캯��
        /// </summary>
        public Activator()
            : base(LoggerNames.Plugin2)
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
            // ��Ӽ�����
            context.AddFrameworkListener(this);
            //var facade = new AlarmFacade();
            //_lifeCycle = facade;
            //_lifeCycle.Open();

            //// ע��IAlarmEntityQueryable�ӿ�
            //ServiceManager.Current.RegisterInstance(facade.AlarmQueryable);

            //// ������ʾ��
            //Workbench.SendMessage(() =>
            //{
            //    // ��ȡ����Ҫ�ķ���
            //    var alarmEntity = ServiceManager.Current.Get<IAlarmEntityQueryable>();

            //    // �����ļ����·��
            //    var cfgPath = Path.GetDirectoryName(Assembly.GetExecutingAssembly().Location) + @"\Config\";

            //    // ������ʾ��
            //    var control = new AlarmControlManager(
            //        alarmEntity,
            //        cfgPath,
            //        NodeContextManager.Current);

            //    control.Initialize();

            //    // ����������ӿؼ�
            //    var partAttri = new AtsPartAttribute { ControlType = PresentationControlType.AlarmControl, DefaultIcon = control.Icon };
            //    MainWorkSpace.AddPart(control.View, partAttri);

            //    // ��ӱ�������ҳ�档
            //    var optionControl = new AlarmConfigPage(alarmEntity, cfgPath);
            //    Workbench.AddOption(optionControl);
            //});
        }

        protected override void OnStop(IBundleContext context)
        {

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

        #region IFrameworkListener ��Ա

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

                //                Log.Info("���ڴ�ͨѶ���...");
                //                _commLifeCycle.Open();
                //                Log.Info("ͨѶ����Ѵ򿪡�");
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

        #region "IDisposable ��Ա"
        protected virtual void Dispose(bool disposing)
        {
            if (!_disposed)
            {
                if (disposing)
                {
                    // �ڴ˴��ͷ��й���Դ
                }

                // �ڴ˴��Ƿ���й���Դ��

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
