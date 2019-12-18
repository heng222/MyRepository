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

using System;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;
using Acl.Utility;
using Products.Infrastructure;
using Products.Infrastructure.Entities;
using Products.Infrastructure.Events;
using Products.Infrastructure.Messages;
using Products.Infrastructure.Specification;
using Products.Infrastructure.Types;
using Products.Presentation;
using Products.SystemEvents.Properties;
using Products.SystemEvents.Utilities;

namespace Products.SystemEvents.Controls
{
    /// <summary>
    /// 系统事件监视控件。
    /// </summary>
    [ProductPart(ControlType = PresentationControlType.SystemEvent)]
    partial class EventsMonitorControl : UserControl
    {
        private readonly UInt32 MaxCount = 100;

        private const byte ConfirmTimeIndex = 4;

        #region "Field && Constructor"

        /// <summary>
        /// 构造函数。
        /// </summary>
        public EventsMonitorControl()
        {
            InitializeComponent();
            this.CreateHandle();

            GlobalMessageBus.SubscribeNewSystemEventGenerated(OnNewSystemEventGenerated);
        }
        #endregion

        #region "private methods"

        private void OnNewSystemEventGenerated(object sender, NewSystemEventArgs args)
        {
            try
            {
                this.Invoke(() =>
                {
                    this.ShowSysEventLog(args.Value);
                }, LogUtility.Log);
            }
            catch (System.Exception ex)
            {
                LogUtility.Error(ex);
            }
        }

        private void ShowSysEventLog(SysEventLog log)
        {
            try
            {
                // 清除无效记录
                if (dataGridView.Rows.Count > MaxCount) { dataGridView.Rows.RemoveAt(dataGridView.Rows.Count - 1); }

                // 查找对应的行。
                var theRow = this.FindGridRow(log.Code);
                if (theRow == null)
                {
                    // 创建新行。
                    theRow = new DataGridViewRow() { Tag = log };
                    theRow.CreateCells(this.dataGridView, new object[] { "" });

                    // 插入到第一行
                    dataGridView.Rows.Insert(0, theRow);
                }

                // 更新内容。
                int index = 0;
                if (log.Level == EventLevel.First)
                {
                    theRow.Cells[index++].Value = Resources.Info;
                    //newRow.DefaultCellStyle.ForeColor = Color.Green;
                }
                else if (log.Level == EventLevel.Second)
                {
                    theRow.Cells[index++].Value = Resources.Warning;
                }
                else
                {
                    theRow.Cells[index++].Value = Resources.Error;
                }
                theRow.Cells[index++].Value = log.Timestamp.ToString("yyyy-MM-dd HH:mm:ss.fff");
                theRow.Cells[index++].Value = EnumUtility.GetDescription(log.TypeCode);
                theRow.Cells[index++].Value = log.Description;

                var confirmEnabled = GlobalServices.SEM.GetConfirmEnabled(log.TypeCode);
                if (confirmEnabled)
                {
                    theRow.Cells[index++].Value = log.ConfirmTime != DateTime.MinValue ? log.ConfirmTime.ToString("yyyy-MM-dd HH:mm:ss.fff") : "";
                }
                else
                {
                    theRow.Cells[index++].Value = "无需确认";
                }
                theRow.Cells[ConfirmTimeIndex].Tag = confirmEnabled;
            }
            catch (System.Exception ex)
            {
                LogUtility.Error(ex);
            }
        }

        private DataGridViewRow FindGridRow(uint code)
        {
            var rawCout = this.dataGridView.Rows.Count;
            for (int i = 0; i < rawCout; i++)
            {
                var theRow = this.dataGridView.Rows[i];
                if (theRow.Tag != null && (theRow.Tag as SysEventLog).Code == code)
                {
                    return theRow;
                }
            }

            return null;
        }

        #endregion

        #region "菜单事件"

        private void contextMenuStrip1_Opening(object sender, CancelEventArgs e)
        {
            try
            {
                configToolStripMenuItem.Enabled = GlobalServices.UAC.Contains(SystemPrivilege.EditSysParam);
            }
            catch (System.Exception ex)
            {
                LogUtility.Error(ex.Message);
            }
        }

        private void confirmThisToolStripMenuItem_Click(object sender, EventArgs e)
        {
            try
            {
                var timeNow = DateTime.Now;
                var rows = dataGridView.SelectedRows;

                for (var i = 0; i < rows.Count; i++)
                {
                    var theLog = rows[i].Tag as SysEventLog;
                    var confirmEnabled = GlobalServices.SEM.GetConfirmEnabled(theLog.TypeCode);
                    if (confirmEnabled && !theLog.IsConfirmed)
                    {
                        theLog.ConfirmTime = timeNow;
                        GlobalMessageBus.PublishNewSystemEventGenerated(new NewSystemEventArgs(theLog));
                    }
                }
            }
            catch (System.Exception ex)
            {
                MessageBox.Show(ex.ToString());
            }
        }

        private void confirmAllToolStripMenuItem_Click(object sender, EventArgs e)
        {
            try
            {
                var timeNow = DateTime.Now;
                var rows = dataGridView.Rows;

                for (var i = 0; i < rows.Count; i++)
                {
                    var theLog = rows[i].Tag as SysEventLog;
                    var confirmEnabled = GlobalServices.SEM.GetConfirmEnabled(theLog.TypeCode);
                    if (confirmEnabled && !theLog.IsConfirmed)
                    {
                        theLog.ConfirmTime = timeNow;
                        GlobalMessageBus.PublishNewSystemEventGenerated(new NewSystemEventArgs(theLog));
                    }
                }
            }
            catch (System.Exception ex)
            {
                MessageBox.Show(ex.ToString());
            }
        }

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
            }
            catch (System.Exception ex)
            {
                MessageBox.Show(ex.ToString());
            }
        }


        private void configToolStripMenuItem_Click(object sender, EventArgs e)
        {
            try
            {

            }
            catch (System.Exception ex)
            {
                MessageBox.Show(ex.ToString());
            }
        }
        #endregion

        #region "控件事件"
        private void dataGridView_RowPrePaint(object sender, DataGridViewRowPrePaintEventArgs e)
        {
            try
            {
                // 确认时间
                var cellConfirmTime = dataGridView.Rows[e.RowIndex].Cells[ConfirmTimeIndex];

                if (cellConfirmTime.Tag != null)
                {
                    var needConfirm = (bool)cellConfirmTime.Tag;
                    var text = cellConfirmTime.Value.ToString();

                    if (needConfirm)
                    {
                        if (!string.IsNullOrWhiteSpace(text))
                        {
                            cellConfirmTime.Style.ForeColor = Color.DarkGreen;
                        }
                        else
                        {
                            cellConfirmTime.Style.BackColor = Color.LightYellow;
                        }
                    }
                    else
                    {
                        cellConfirmTime.Style.ForeColor = Color.LightGray;
                    }
                }
            }
            catch (System.Exception ex)
            {
                LogUtility.Error(ex);
            }
        }
        #endregion
    }
}
