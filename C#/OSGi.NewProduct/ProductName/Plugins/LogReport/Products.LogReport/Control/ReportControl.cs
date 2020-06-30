using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

using Microsoft.Reporting.WinForms;

namespace Products.LogReport
{
    partial class ReportControl : UserControl
    {
        public ReportControl()
        {
            InitializeComponent();
            _reportViewer1.LocalReport.EnableHyperlinks = true;
        }

        public void AddQueryControl(QueryControl ctrlQuery, string reportName, string reportPath)
        {
            ctrlQuery.Dock = DockStyle.Fill;
            _panelQuery.Controls.Add(ctrlQuery);

            _reportViewer1.LocalReport.ReportEmbeddedResource = reportPath;

            ctrlQuery.SetReportView(_reportViewer1, reportName);
        }

        private void reportViewer1_Drillthrough(object sender, DrillthroughEventArgs e)
        {
            var localReport = (LocalReport)e.Report;
            localReport.DataSources.Add(_reportViewer1.LocalReport.DataSources["DataSet1"]);
        }
    }
}
