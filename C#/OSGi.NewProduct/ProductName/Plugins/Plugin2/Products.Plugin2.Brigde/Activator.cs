
using System.IO;
using System.Linq;
using System.Reflection;
using Acl.ServiceManagement;
using Framework.OSGi;
using Platform.Bundles.Bridge;
using Platform.Presentation;
using Products.Infrastructure.Log;

namespace Products.Plugin2.Bridge
{
    /// <summary>
    /// ��ϵͳ������
    /// </summary>
    class Activator : BundleActivatorBase
    {

        /// <summary>
        /// 
        /// </summary>
        public Activator()
            : base(LoggerNames.Plugin2)
        {
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="context"></param>
        protected override void OnStart(IBundleContext context)
        {
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

        /// <summary>
        /// 
        /// </summary>
        /// <param name="context"></param>
        protected override void OnStop(IBundleContext context)
        {

        }

    }
}
