using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using Products.Presentation;
using Products.Infrastructure;
using Products.SystemEvents.Properties;
using Products.Infrastructure.Messages;
using Products.Infrastructure.Events;
using Products.SystemEvents.Utilities;
using Products.Infrastructure.Entities;
using Products.Infrastructure.Types;

namespace Products.SystemEvents.Presentation.Controls
{
    [ProductPart(ControlType = PresentationControlType.SystemEvent)]
    partial class EventsMonitorControl : UserControl
    {
        private readonly UInt32 MaxAlarmCount = 200;

        #region "Field && Constructor"
        public Icon Icon { get { return Resources.Alarm; } }

        /// <summary>
        /// 构造函数。
        /// </summary>
        public EventsMonitorControl()
        {
            InitializeComponent();

            GlobalMessageBuses.SubscribeNewSystemEventGenerated(OnNewSystemEventGenerated);
        }
        #endregion

        #region "private methods"

        private void OnNewSystemEventGenerated(object sender, NewSystemEventArgs args)
        {
            try
            {
                this.BeginInvoke(new Action(() => 
                {
                    this.ShowSystemEvent(args.Value);
                }));                
            }
            catch (System.Exception ex)
            {
                LogUtility.Error(ex);
            }
        }

        private void ShowSystemEvent(EventLog eventLog)
        {
            try
            {
                // 清除无效记录。
                var lastIndex = dataGridView.Rows.Count - 1;
                if (dataGridView.Rows.Count > MaxAlarmCount)
                {
                    dataGridView.Rows.RemoveAt(lastIndex);
                }

                // 创建新行。
                var newRow = new DataGridViewRow();
                newRow.CreateCells(this.dataGridView);
                if (eventLog.Level == EventLevel.First)
                {
                    newRow.Cells[0].Value = Resources.Info_warning;
                    //newRow.DefaultCellStyle.ForeColor = Color.Green;
                }
                else if (eventLog.Level == EventLevel.Second)
                {
                    newRow.Cells[0].Value = Resources.Warning_warning;
                    //newRow.DefaultCellStyle.ForeColor = Color.Blue;
                }
                else
                {
                    newRow.Cells[0].Value = Resources.Error_worning;
                    //newRow.DefaultCellStyle.ForeColor = Color.Red;
                }
                newRow.Cells[1].Value = eventLog.Timestamp;
                newRow.Cells[2].Value = eventLog.Description;

                // 插入到第一行
                this.dataGridView.Rows.Insert(0, newRow);
            }
            catch (System.Exception ex)
            {
                LogUtility.Error(ex);
            }
        }
        #endregion

        #region "控件事件"
        private void removeThisToolStripMenuItem_Click(object sender, EventArgs e)
        {
            try
            {
                var countSelected = dataGridView.SelectedRows.Count;
                for (var i = 0; i < countSelected; i++)
                {
                    var theRow = dataGridView.SelectedRows[i];
                    dataGridView.Rows.Remove(theRow);
                }

                // 
                var eventLog = new EventLog()
                {
                    Level = EventLevel.Second,
                    Description = "删除当前行"
                };
                GlobalMessageBuses.PublishNewSystemEventGenerated(new NewSystemEventArgs(eventLog));
            }
            catch (System.Exception ex)
            {
                MessageBox.Show(ex.ToString());
            }
        }

        private void removeAllToolStripMenuItem_Click(object sender, EventArgs e)
        {
            try
            {
                dataGridView.Rows.Clear();

                // 
                var eventLog = new EventLog()
                {
                    Level = EventLevel.Third,
                    Description = "删除所有行"
                };
                GlobalMessageBuses.PublishNewSystemEventGenerated(new NewSystemEventArgs(eventLog));
            }
            catch (System.Exception ex)
            {
                MessageBox.Show(ex.ToString());
            }
        }

        private void mnSelectAll_Click(object sender, EventArgs e)
        {
            try
            {
                dataGridView.SelectAll();

                // 
                var eventLog = new EventLog() 
                {
                    Level = EventLevel.First,
                    Description = "选择所有"
                };
                GlobalMessageBuses.PublishNewSystemEventGenerated(new NewSystemEventArgs(eventLog));
            }
            catch (System.Exception ex)
            {
                MessageBox.Show(ex.ToString());
            }
        }
        #endregion

    }
}
