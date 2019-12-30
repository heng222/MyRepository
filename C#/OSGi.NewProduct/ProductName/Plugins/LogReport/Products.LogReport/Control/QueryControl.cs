using System;
using System.Diagnostics;
using System.Diagnostics.CodeAnalysis;
using System.Windows.Forms;
using Acl.Threading;
using Acl.Controls;
using Microsoft.Reporting.WinForms;

namespace Products.LogReport
{
    partial class QueryControl : UserControl
    {
        #region "Field"
        /// <summary>
        /// 监测查询耗事
        /// </summary>
        private Stopwatch _stopWatch = new System.Diagnostics.Stopwatch();
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
            this.dtEnd.Value = DateTime.Now;
            this.dtBegin.Value = this.dtEnd.Value - TimeSpan.FromDays(30);
        }
        #endregion


        public void SetReportView(ReportViewer rptView, string reportName)
        {
            this.ReportView = rptView;
            this.ReportName = reportName;
            rptView.Hyperlink += OnReportViewHyperlinkClick;
        }

        protected virtual void OnReportViewHyperlinkClick(object sender, HyperlinkEventArgs e)
        {
        }

        protected virtual object DoQuery() { return null; }

        [SuppressMessage("Microsoft.Reliability", "CA2001:AvoidCallingProblematicMethods", MessageId = "System.GC.Collect")]
        private void btnQuery_Click(object sender, EventArgs e)
        {
            object reportDataSource = null;
            try
            {
                this.Cursor = Cursors.WaitCursor;
                btnQuery.Enabled = false;

                ThreadProxy.QueueUserWorkItem(() =>
                {
                    try
                    {
                        ReportView.LocalReport.DataSources.Clear();

                        _stopWatch.Restart();

                        reportDataSource = DoQuery();
                    }
                    catch (Exception ex)
                    {
                        LogUtility.Error(ex);
                        MessageBox.Show(ex.ToString(), "错误", MessageBoxButtons.OK, MessageBoxIcon.Error);
                        return;
                    }
                    finally
                    {
                        _stopWatch.Stop();
                        btnQuery.Invoke(() =>
                        {
                            btnQuery.Enabled = true;
                            this.Cursor = Cursors.Default;
                        });
                    }

                    LogUtility.Info(string.Format("方法名DoQuery--模块{0}--耗事{1}ms--记录条数{2}",
                        ReportName,
                        _stopWatch.ElapsedMilliseconds,
                        (reportDataSource as System.Collections.ICollection).Count));

                    ReportView.Invoke(() =>
                        {
                            ReportView.LocalReport.DataSources.Add(new ReportDataSource("DataSet1", reportDataSource));
                            ReportView.RefreshReport();

                            ReportView.LocalReport.ReleaseSandboxAppDomain();
                            GC.Collect();
                        });
                });
            }
            catch (Exception ex)
            {
                LogUtility.Error(ex);
                MessageBox.Show(ex.ToString(), "错误", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }
        }

        public void CheckingStartStopTime(DateTime dt1, DateTime dt2)
        {
            if (dt1 > dt2)
            {
                throw new Exception("起始时间大于结束时间！");
            }

            if (GetCountDays(dt1, dt2.AddMonths(-1)) > 0)
            {
                throw new Exception("查询范围大于一个月！");
            }
        }

        /// <summary>
        /// 计算两个日期相差的天数
        /// </summary>
        public int GetCountDays(DateTime timeS, DateTime timeE)
        {
            try
            {
                System.DateTime Date1 = timeS;
                System.DateTime Date2 = timeE;

                TimeSpan diff1 = Date2.Subtract(Date1);
                int countDay = Convert.ToInt32(diff1.TotalDays);//.ToString();


                if (countDay < 0)
                {
                    return -1;
                }
                return countDay;
            }
            catch
            {
                return -1;
            }
        }

        public int GetTimeMinuteABS(DateTime start, DateTime end, bool isABS)
        {
            try
            {
                System.DateTime Date1 = start;
                System.DateTime Date2 = end;

                TimeSpan diff1 = Date2.Subtract(Date1);
                int count = Convert.ToInt32(diff1.TotalMinutes);//.ToString();

                if (isABS)
                    return System.Math.Abs(count);
                else
                    return count;
            }
            catch
            {
                return 0;
            }
        }

        public int GetTimeSecondesABS(DateTime start, DateTime end, bool isABS)
        {
            try
            {
                System.DateTime Date1 = start;
                System.DateTime Date2 = end;

                TimeSpan diff1 = Date2.Subtract(Date1);
                int count = Convert.ToInt32(diff1.TotalSeconds);//.ToString();

                if (isABS)
                    return System.Math.Abs(count);
                else
                    return count;
            }
            catch
            {
                return 0;
            }
        }

        public void UpdataText(System.Windows.Forms.Control control, string value)
        {
            if (control.InvokeRequired)
            {
                Action<string> actionDelegate = (x) => { control.Text = x; };

                control.Invoke(actionDelegate, value);
            }
            else
            {
                control.Text = value;
            }
        }
    }
}
