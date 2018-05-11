
using System.IO;
using System.Linq;
using System.Reflection;
using Acl.ServiceManagement;
using Framework.OSGi;
using Platform.Bundles.Bridge;
using Platform.Presentation;
using Products.Plugins1.Controls;
using Products.Presentation;
using Products.Infrastructure;
using System.Net;
using Products.Domain.Preferences;
using Acl.Configuration;
using Platform.Bundles.Bridge.Utilities;

namespace Products.Plugin1.Brigde
{
    /// <summary>
    /// Alarm子系统激活器
    /// </summary>
    class Activator : BundleActivatorBase
    {
        /// <summary>
        /// 
        /// </summary>
        public Activator()
            : base("Plugin1")
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

            // 创建表示层
            Workbench.SendMessage(() =>
            {
                // 获取所需要的服务
                //var alarmEntity = ServiceManager.Current.Get<IAlarmEntityQueryable>();


                // 创建表示层
                var control = new Plugin1Control1() { Text = "P1C1_实例1"};
                MainWorkSpace.AddPart(control, control.Icon);

                var control2 = new Plugin1Control1() { Text = "P1C1_实例2" };
                MainWorkSpace.AddPart(control2, control.Icon);

                // 添加配置页面。
                var optionControl = new Plugin1ConfigPage();
                Workbench.AddOption(optionControl);
            });
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="context"></param>
        protected override void OnStop(IBundleContext context)
        {

        }

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
    }
}
