using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Windows.Forms;

namespace Products.LogReport
{
    /// <summary>
    /// 报表TabControl 构造器
    /// </summary>
    static class ReportTabControlBuilder
    {
        class MetaDataItem
        {
            public Type ReportControlType;
            public ReportAttribute Attribute;
            public bool HasCreated { get; set; }
        }

        static Dictionary<string, MetaDataItem> metadataItems = null;

        static ReportTabControlBuilder()
        {
            metadataItems = (from t in Assembly.GetExecutingAssembly().GetTypes().Where(p => typeof(QueryControl).IsAssignableFrom(p))
                .Where(p => !p.IsAbstract)
                             let att = t.GetCustomAttributes(typeof(ReportAttribute), false).FirstOrDefault()
                             where att != null
                             select new MetaDataItem
                             {
                                 Attribute = att as ReportAttribute,
                                 ReportControlType = t,
                             }).ToDictionary(p => p.Attribute.DisplayName);
        }

        /// <summary>
        /// 构造TabControl
        /// </summary>
        public static TabControl Build()
        {
            var tabCtl = new TabControl();
            tabCtl.Selected += OnTabCtrlSelected;

            foreach (var item in metadataItems.Values.OrderBy(p => p.Attribute.Order))
            {
                var tabPage = new TabPage { Text = item.Attribute.ReportName, Name = item.Attribute.ReportName };
                tabCtl.TabPages.Add(tabPage);
            }

            if (tabCtl.TabPages.Count > 0)
            {
                FillTabPage(tabCtl.TabPages[0]);
            }

            return tabCtl;
        }

        static void OnTabCtrlSelected(object sender, TabControlEventArgs e)
        {
            var tabPage = e.TabPage;
            FillTabPage(tabPage);
        }

        private static void FillTabPage(TabPage tabPage)
        {
            var metadataItem = metadataItems[tabPage.Text];

            if (!metadataItem.HasCreated)
            {
                var reportControl = new ReportControl { Dock = DockStyle.Fill };
                var queryControl = System.Activator.CreateInstance(metadataItem.ReportControlType) as QueryControl;
                queryControl.ReportName = metadataItem.Attribute.ReportName;
                reportControl.AddQueryControl(queryControl, metadataItem.Attribute.ReportName, metadataItem.Attribute.ReportURL);

                metadataItem.HasCreated = true;

                tabPage.Controls.Add(reportControl);
            }
        }
    }
}
