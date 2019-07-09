
using System.Collections.Generic;
using Platform.Presentation;
using Products.Domain;
using Products.Infrastructure.Log;
using Products.Infrastructure.Types;
using Products.Presentation;
using Products.SystemEvents.Controls;

namespace Products.SystemEvents.Bridge
{
    /// <summary>
    /// ��ϵͳ������
    /// </summary>
    class Activator : FrameworkActivatorBase
    {
        #region "Filed"
        #endregion

        #region "Constructor"
        /// <summary>
        /// ���캯��
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
            //var facade = new AlarmFacade();
            //_lifeCycle = facade;
            //_lifeCycle.Open();

            //// ע��IAlarmEntityQueryable�ӿ�
            //ServiceManager.Current.RegisterInstance(facade.AlarmQueryable);

            // ������ʾ��
            Workbench.SendMessage(() =>
            {
                // ��ȡ����Ҫ�ķ���
                //var alarmEntity = ServiceManager.Current.Get<IAlarmEntityQueryable>();


                // ������ʾ��
                var control = new EventsMonitorControl();
                MainWorkSpace.AddPart(control, control.Icon);

                //// �������ҳ�档
                //var optionControl = new Plugin1ConfigPage();
                //Workbench.AddOption(optionControl);
            });
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

    }
}
