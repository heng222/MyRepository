/*----------------------------------------------------------------
// 公司名称：请输入公司名称
// 
// 项目名称：输入项目名称
//
// 创 建 人：heng222_z
// 创建日期：2018/5/28 15:46:41 
// 邮    箱：heng222_z@163.com
//
// Copyright (C) 公司名称，保留所有权利。
//
//----------------------------------------------------------------*/

using System.Collections.Generic;

using Acl.Presentation;
using Acl.ServiceManagement;

using Products.Domain;
using Products.Infrastructure.Log;
using Products.Infrastructure.Types;
using Products.Plugin1.Controls;
using Products.Presentation;

namespace Products.Plugin1
{
    /// <summary>
    /// 子系统激活器
    /// </summary>
    class Activator : FrameworkActivatorBase
    {
        #region "Field"
        private Facade _facade;
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

        public override PluginTypes Type { get { return PluginTypes.Plugin1; } }

        protected override void OnBundleStart(IDictionary<string, string> context)
        {
            _facade = new Facade();

            // 注册接口
            _facade.ComponentsToRegister.ForEach(p => ServiceManager.Current.RegisterInstance(p));

            // 创建表示层
            Workbench.SendMessage(() =>
            {
                // 创建表示层
                var control = new CtrlMain();
                MainWorkSpace.AddPart(control, control.Icon);

                // 添加配置页面。
                var optionControl = new CtrlConfigPage();
                Workbench.AddOption(optionControl);
            });

            // 
            _facade.Open();
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

        }
        #endregion


        #region "Private methods"

        #endregion
    }
}
