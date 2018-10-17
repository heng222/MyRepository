
using System;
using System.Collections.Generic;
using OSGi;
using Platform.Presentation;
using Products.Domain;
using Products.Infrastructure.Log;
using Products.Infrastructure.Types;
using Products.Plugin1.Controls;
using Products.Presentation;

namespace Products.Plugin1.Bridge
{
    /// <summary>
    /// 子系统激活器
    /// </summary>
    class Activator : FrameworkActivatorBase
    {
        #region "Filed"
        #endregion

        #region "Constructor"
        /// <summary>
        /// 构造函数
        /// </summary>
        public Activator()
            : base(LoggerNames.Plugin1)
        {
        }
        #endregion

        #region "Override methods"

        public override PluginType Type
        {
            get { return PluginType.Plugin1; }
        }

        protected override void OnPluginStart(IDictionary<string, string> context)
        {
            // 创建表示层
            Workbench.SendMessage(() =>
            {
                // 创建表示层
                var control = new Plugin1Control1();
                MainWorkSpace.AddPart(control, control.Icon);

                // 添加配置页面。
                var optionControl = new Plugin1ConfigPage();
                Workbench.AddOption(optionControl);
            });
        }
        
        protected override void OnPluginStop(IDictionary<string, string> context)
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


        #region "Private methods"

        #endregion
    }
}
