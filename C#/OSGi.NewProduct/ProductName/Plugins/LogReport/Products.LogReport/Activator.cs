/*----------------------------------------------------------------
// 公司名称：请输入公司名称
// 
// 项目名称：输入项目名称
//
// 创 建 人：zhangheng
// 创建日期：2015-2-3 21:20:58 
// 邮    箱：zhangheng@163.com
//
// Copyright (C) 公司名称 2019，保留所有权利
//
//----------------------------------------------------------------*/

using System.Collections.Generic;

using Acl.Presentation;

using Products.Domain;
using Products.Infrastructure.Log;
using Products.Infrastructure.Types;
using Products.LogReport.Properties;
using Products.Presentation;

namespace Products.LogReport
{
    /// <summary>
    /// 子系统激活器
    /// </summary>
    class Activator : FrameworkActivatorBase
    {
        #region "Field"

        #endregion

        #region "constructor"
        public Activator()
            : base(LoggerNames.LogReport)
        {
        }

        #endregion

        #region "override methods"
        public override PluginTypes Type { get { return PluginTypes.LogReport; } }

        protected override void OnBundleStart(IDictionary<string, string> context)
        {
            // 创建表示层
            var cfg = new ProductPartAttribute("11F0FAE2-2728-479D-AC9F-C6E63E1BACE5", "日志报告") { DefaultIcon = Resources.LogQuery };
            Workbench.SendMessage(() => MainWorkSpace.AddPart(ReportTabControlBuilder.Build(), cfg));
        }

        protected override void OnBundleStop(IDictionary<string, string> context)
        {

        }

        protected override void OnFrameworkStarted()
        {
        }
        #endregion

        #region "private methods"
        #endregion

        #region "public methods"
        #endregion

    }
}
