
using System;
using System.Linq;
using Acl.ServiceManagement;
using Framework.OSGi;
using Platform.Bundles.Bridge;
using Platform.Bundles.Bridge.Utilities;
using Products.Domain.Preferences;
using Products.Infrastructure.Log;
using Products.UAC.Domain;

namespace Products.UAC.Bridge
{
    /// <summary>
    /// ��ϵͳ������
    /// </summary>
    class Activator : BundleActivatorBase, IFrameworkListener, IDisposable
    {
        #region "Filed"
        private bool _disposed = false;
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

            var settings = BuildSettings(context);
            _facade = new UacFacade(settings);

            // ע��IAlarmEntityQueryable�ӿ�
            _facade.ComponentsToRegister.ToList().ForEach(p => ServiceManager.Current.RegisterInstance(p));

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
        private static UacSettings BuildSettings(IBundleContext context)
        {
            var settings = ServiceUtility.GetSettings(context);

            var adminPwd = SettingsUtility.GetByteArray(settings, "AdminPassword", 16);

            return new UacSettings(adminPwd);
        }
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
