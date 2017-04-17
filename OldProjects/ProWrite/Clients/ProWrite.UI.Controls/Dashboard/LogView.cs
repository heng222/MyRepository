using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using ProWrite.Entity.Dashboard;
using ProWrite.UFE.Entity;
using ProWrite.Core;
using ProWrite.UI.Controls.Common;
using ProWrite.UFE;
using System.Reflection;
using ProWrite.UI.Controls.Actions.UFE.Requests;
using DevExpress.XtraEditors;

namespace ProWrite.UI.Controls.Dashboard
{
    public partial class LogView : XtraForm
    {
        private SignInfo sign;
        List<LogInfo> list;

        DataSet dataset = new DataSet();
        DataTable table = new DataTable();
        LogViewAction logViewAction = new LogViewAction();
        public LogView()
        {
            InitializeComponent();
            Init();
        }
        private void Init()
        {
            sign = ControlService.SignCombo.Current;
        }

        private void LogView_Load(object sender, EventArgs e)
        {

        }

        public static DataTable convert2Table<T>(List<T> list)
        {

            DataTable table = new DataTable();


            if (list.Count > 0)
            {


                PropertyInfo[] properties = list[0].GetType().GetProperties();

                List<string> columns = new List<string>();
                foreach (PropertyInfo pi in properties)
                {

                    table.Columns.Add(pi.Name);

                    columns.Add(pi.Name);

                }
                foreach (T item in list)
                {
                    object[] cells = getValues(columns, item);

                    table.Rows.Add(cells);
                }

            }


            return table;

        }


        private static object[] getValues(List<string> columns, object instance)
        {

            object[] ret = new object[columns.Count];


            for (int n = 0; n < ret.Length; n++)
            {

                PropertyInfo pi = instance.GetType().GetProperty(columns[n]);

                object value = pi.GetValue(instance, null);

                ret[n] = value;

            }
            return ret;

        }

        private void btnRefresh_Click(object sender, EventArgs e)
        {
            if (ControlService.SignCombo.Current.Controller.Connection.State != System.Communication.ConnectionState.Opened)
            {
                MsgBox.Error(Resources.Resource.GetString(Resources.Resource.Strings.SendSendToSignLoginFirst));
                return;
            }
            Cursor = Cursors.WaitCursor;

            LogViewGet log = new LogViewGet();
            log.Mode = 0;
            log.Type = 0;
            string sql = " 1=1";
            if (!string.IsNullOrEmpty(cmbVersion.Text))
                sql = sql + " and Version = " + cmbVersion.Text;
            if (!string.IsNullOrEmpty(txtLevel.Text))
                sql += " and Level like '%" + txtLevel.Text + "%'";
            if (table.Rows.Count > 0)
            {
                //table = convert2Table<LogInfo>(list);
                DataTable t = new DataTable("table");
                DataRow[] rows = table.Select(sql);
                t.Columns.Add("Version");
                t.Columns.Add("Date");
                t.Columns.Add("Level");
                t.Columns.Add("Content");
                for (int i = 0; i < rows.Length; i++)
                    t.Rows.Add(rows[i].ItemArray);
                //DataView view = table.Select(sql).
                this.gridControl1.DataSource = t;// table.Select(sql);
                return;
            }
            log.DateTime = "20090810090112";
            log.SQL = "";
            //Send set dimming command
            sign.Controller.SendAsync(
                Commands.GetLog,
                p =>
                {
                    Cursor = Cursors.Default;
                    if (p.IsSuccessed)
                    {
                        JsonSerializer serializer = new JsonSerializer();

                        list = serializer.ConvertToType<List<LogInfo>>(p.Packet.Content);

                        //= p.Packet.Content.GetProperty<List<LogInfo>>("List");
                        if (list != null && list.Count > 0)
                        {
                            table = convert2Table<LogInfo>(list);

                            DataTable t = new DataTable();
                            DataRow[] rows = table.Select(sql);
                            t.Columns.Add("Version");
                            t.Columns.Add("Date");
                            t.Columns.Add("Level");
                            t.Columns.Add("Content");
                            for (int i = 0; i < rows.Length; i++)
                                t.Rows.Add(rows[i].ItemArray);
                            //DataView view = table.Select(sql).
                            this.gridControl1.DataSource = t;// table.Select(sql);
                        }
                        //int totalSize = p.Packet.Content.GetProperty<int>("TotalSize");
                    }
                    else
                    {
                        MsgBox.Error(Resources.Resource.GetString(Resources.Resource.Strings.SetDimmingFailed));//"Dimming was not changed.Please try again.");
                    }
                },
                log);
        }

        private void btnSelect_Click(object sender, EventArgs e)
        {
            
            string sql = "select * from Log where 1=1";
            //select * from log where cast(date as int) between 0 and 20090814015102
            if (!string.IsNullOrEmpty(cmbVersion.Text))
                sql = sql + " and Version = '" + cmbVersion.Text+"'";
            if (!string.IsNullOrEmpty(txtLevel.Text))
                sql += " and Level like '%" + txtLevel.Text + "%'";
            double begin = 0;
            double end = 0;
            if (!string.IsNullOrEmpty(dateStart.Text))
                begin = Convert.ToDouble(dateStart.DateTime.Date.ToString("yyyyMMdd") + timeStart.Time.ToString("hhmmss"));
            if(!string.IsNullOrEmpty(dateEnd.Text))
                end = Convert.ToDouble(dateEnd.DateTime.Date.ToString("yyyyMMdd") + timeEnd.Time.ToString("hhmmss"));
            if(begin!=0)
                sql+=" and cast(date as int) >=" + begin;
            if (end != 0)
                sql += " and cast(date as int) <="+ end;

            this.gridControl1.DataSource = LogService.GetLogs(sql);
            
        }

        private void btnExport_Click(object sender, EventArgs e)
        {

            saveFileDialog1.ShowDialog();
        }

        private void openFileDialog1_FileOk(object sender, CancelEventArgs e)
        {
            //gridView1.ExportToExcelOld("LogView"+DateTime.Now.ToString());
            
        }

        private void btnCancel_Click(object sender, EventArgs e)
        {
            Close();
        }

        private void controlNavigator1_ButtonClick(object sender, DevExpress.XtraEditors.NavigatorButtonClickEventArgs e)
        {
            
        }

        private void saveFileDialog1_FileOk(object sender, CancelEventArgs e)
        {
            string fileName = saveFileDialog1.FileName;
            gridView1.ExportToXls(fileName);
            //gridControl1.ExportToXls(fileName);
        }

        
    }
}
