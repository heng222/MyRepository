
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
    /// 子系统激活器
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

            //// 注册IAlarmEntityQueryable接口
            //ServiceManager.Current.RegisterInstance(facade.AlarmQueryable);

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

        /// <summary>
        /// 
        /// </summary>
        /// <param name="context"></param>
        protected override void OnStop(IBundleContext context)
        {

        }

    }
}
