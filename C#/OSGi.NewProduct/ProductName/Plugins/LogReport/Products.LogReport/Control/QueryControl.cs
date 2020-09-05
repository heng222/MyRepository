using System;
using System.Collections;
using System.Diagnostics;
using System.Diagnostics.CodeAnalysis;
using System.Windows.Forms;

using Acl.Controls;
using Acl.Threading;

using Microsoft.Reporting.WinForms;

namespace Products.LogReport
{
    partial class QueryControl : UserControl
    {
        #region "Field"
        /// <summary>
        /// 监测查询耗事
        /// </summary>
        private Stopwatch _stopWatch = new Stopwatch();
        #endregion

        #region "Properties"
        /// <summary>
        /// 
        /// </summary>
        public string ReportName { get; set; }

        /// <summary>
        /// 
        /// </summary>
        protected ReportViewer ReportView { get; private set; }

        /// <summary>
        /// 获取起始时间。
        /// </summary>
        public DateTime BeginTime { get { return this.dtBegin.Value; } }
        /// <summary>
        /// 获取终结时间。
        /// </summary>
        public DateTime EndTime { get { return this.dtEnd.Value; } }
        #endregion

        #region "Constructor"
        /// <summary>
        /// 构造函数。
        /// </summary>
        protected QueryControl()
        {
            InitializeComponent();

            // 初始化开始时间与结束时间
            this.dtBegin.Value = DateTime.Now - TimeSpan.FromDays(30);
            this.dtEnd.Value = DateTime.Now + TimeSpan.FromHours(1);
        }
        #endregion

        #region "Private methods"
        private void UpdateControls(bool enabled)
        {
            this.Invoke(() =>
            {
                this.Cursor = enabled ? Cursors.Default : Cursors.WaitCursor;
                btnQuery.Enabled = enabled;
            });
        }

        private void CheckingBeginEndTime()
        {
            if (this.BeginTime > this.EndTime)
            {
                throw new Exception("起始时间不能大于结束时间！");
            }

            //if ((this.BeginTime - this.EndTime).Duration().TotalDays > 31)
            //{
            //    throw new Exception("查询范围不能大于一个月！");
            //}
        }

        [SuppressMessage("Microsoft.Reliability", "CA2001:AvoidCallingProblematicMethods", MessageId = "System.GC.Collect")]
        private void SetDataSource(ICollection dataSource)
        {
            this.Invoke(() =>
            {
                ReportView.LocalReport.DataSources.Add(new ReportDataSource("DataSet1", dataSource));
                ReportView.RefreshReport();

                // 释放资源
                ReportView.LocalReport.ReleaseSandboxAppDomain();
                GC.Collect();
            });
        }
        #endregion

        #region "Protected methods"
        protected virtual ICollection DoQuery() { return null; }

        protected virtual void OnReportViewHyperlinkClick(object sender, HyperlinkEventArgs e)
        {
        }
        #endregion

        #region "Public methods"
        public void SetReportView(ReportViewer rptView, string reportName)
        {
            this.ReportView = rptView;
            this.ReportName = reportName;
            rptView.Hyperlink += OnReportViewHyperlinkClick;
        }
        #endregion

        #region "控件事件处理函数"

        private void label2_Click(object sender, EventArgs e)
        {
            dtEnd.Value = DateTime.Now;
        }

        private void btnQuery_Click(object sender, EventArgs e)
        {
            try
            {
                // 
                CheckingBeginEndTime();

                // 
                this.ReportView.LocalReport.DataSources.Clear();

                ThreadProxy.QueueUserWorkItem(() =>
                {
                    ICollection dataSource = null;

                    try
                    {
                        UpdateControls(false);

                        _stopWatch.Restart();
                        dataSource = DoQuery();
                    }
                    catch (Exception ex)
                    {
                        dataSource = null;
                        MessageBox.Show(ex.Message, "错误", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    }
                    finally
                    {
                        _stopWatch.Stop();
                        UpdateControls(true);
                    }

                    if (dataSource == null) return;

                    LogUtility.Debug(string.Format("DoQuery--{0}--耗时{1}ms--记录数{2}", ReportName, _stopWatch.ElapsedMilliseconds, dataSource.Count));

                    this.SetDataSource(dataSource);
                });
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message, "错误", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void dtBegin_ValueChanged(object sender, EventArgs e)
        {
            try
            {
                dtEnd.MinDate = dtBegin.Value;
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message, "错误", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }
        #endregion


    }
}
