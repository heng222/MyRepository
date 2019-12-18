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
using System.Drawing;
using System.Linq;
using System.Windows.Forms;
using Acl.Utility;
using Products.Infrastructure.Entities;
using Products.Infrastructure.Messages;
using Products.Infrastructure.Specification;
using Products.Infrastructure.Types;
using Products.Presentation;
using Products.SystemEvents.Utilities;

namespace Products.SystemEvents.Controls
{
    /// <summary>
    /// 操作记录显示控件。
    /// </summary>
    [ProductPart(ControlType = PresentationControlType.OperationLog)]
    partial class OperationLogControl : UserControl
    {
        #region "Constants"
        private readonly UInt32 MaxCount = 100;
        private const string ColumNameCode = "编号";
        private const string ColumNameOperationTime = "操作时间";
        private const string ColumNameOperationType = "操作类型";
        private const string ColumNameExeMode = "执行方式";
        private const string ColumNameTarget = "目标设备";
        private const string ColumNameOperationDescription = "操作描述";
        private const string ColumNameResultType = "操作结果";
        private const string ColumNameResultTime = "结果时间";
        private const string ColumNameResultDescription = "结果描述";
        #endregion

        #region "Field && Constructor"

        /// <summary>
        /// 构造函数。
        /// </summary>
        public OperationLogControl()
        {
            InitializeComponent();
            this.CreateHandle();

            this.InitalizeDataGridView();

            GlobalMessageBus.SubscribeOperationLogChanged(OnNewOperatonLog);
        }
        #endregion


        #region  "private methods"

        private void OnNewOperatonLog(object sender, Infrastructure.Events.OpeationLogCreateOrUpdateEventArgs args)
        {
            try
            {
                this.Invoke(() =>
                {
                    this.ShowOperationLog(args.Value);
                }, LogUtility.Log);
            }
            catch (System.Exception ex)
            {
                LogUtility.Error(ex);
            }
        }
        private void ShowOperationLog(OperationLog log)
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
                    theRow = new DataGridViewRow();
                    theRow.Tag = log.Code;
                    theRow.CreateCells(this.dataGridView, new object[] { "" });

                    // 插入到第一行
                    dataGridView.Rows.Insert(0, theRow);
                }

                // 更新数据。
                if (theRow.Cells[ColumNameCode].Value == null || string.IsNullOrEmpty(theRow.Cells[ColumNameCode].Value.ToString()))
                {
                    theRow.Cells[ColumNameCode].Value = log.Code;
                    theRow.Cells[ColumNameOperationTime].Value = log.Timestamp.ToString("yyyy-MM-dd HH:mm:ss.fff");
                    theRow.Cells[ColumNameOperationType].Value = EnumUtility.GetDescription(log.OperationType);
                    theRow.Cells[ColumNameExeMode].Value = log.IsManual ? "手动" : "自动";
                    theRow.Cells[ColumNameExeMode].Tag = log.IsManual;

                    var theNode = GlobalServices.Repository.Where<SystemNode>(p => p.Code == log.TargetDeviceCode).FirstOrDefault();
                    if (theNode != null)
                    {
                        theRow.Cells[ColumNameTarget].Value = string.Format("{0}_{1}", log.TargetDeviceCode, theNode.Name);
                    }
                    else
                    {
                        theRow.Cells[ColumNameTarget].Value = string.Format("{0}", log.TargetDeviceCode);
                    }
                }

                // 更新操作结果。
                theRow.Cells[ColumNameOperationDescription].Value = log.OperationDescription;
                theRow.Cells[ColumNameResultType].Value = EnumUtility.GetDescription(log.ResultType);
                theRow.Cells[ColumNameResultType].Tag = log.ResultType;
                theRow.Cells[ColumNameResultTime].Value = (log.ResultTimestamp != DateTime.MinValue) ? log.ResultTimestamp.ToString("yyyy-MM-dd HH:mm:ss.fff") : "";
                theRow.Cells[ColumNameResultDescription].Value = log.ResultDescription;
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
                if (theRow.Tag != null && Convert.ToUInt32(theRow.Tag) == code)
                {
                    return theRow;
                }
            }

            return null;
        }
        
        private void InitalizeDataGridView()
        {
            //dataGridView.BorderStyle = BorderStyle.None;
            dataGridView.Dock = DockStyle.Fill;
            dataGridView.Columns.Clear();

            // 创建列
            var newColum = new DataGridViewTextBoxColumn() { Name = ColumNameCode };
            dataGridView.Columns.Add(newColum);
            newColum = new DataGridViewTextBoxColumn() { Name = ColumNameOperationTime };
            dataGridView.Columns.Add(newColum);
            newColum = new DataGridViewTextBoxColumn() { Name = ColumNameOperationType };
            dataGridView.Columns.Add(newColum);
            newColum = new DataGridViewTextBoxColumn() { Name = ColumNameExeMode };
            dataGridView.Columns.Add(newColum);
            newColum = new DataGridViewTextBoxColumn() { Name = ColumNameTarget };
            dataGridView.Columns.Add(newColum);
            newColum = new DataGridViewTextBoxColumn() { Name = ColumNameOperationDescription };
            dataGridView.Columns.Add(newColum);
            newColum = new DataGridViewTextBoxColumn() { Name = ColumNameResultType };
            dataGridView.Columns.Add(newColum);
            newColum = new DataGridViewTextBoxColumn() { Name = ColumNameResultTime };
            dataGridView.Columns.Add(newColum);
            newColum = new DataGridViewTextBoxColumn() { Name = ColumNameResultDescription };
            dataGridView.Columns.Add(newColum);

            // 设置列格式
            for (int i = 0; i < dataGridView.ColumnCount; i++)
            {
                dataGridView.Columns[i].MinimumWidth = 30;
                dataGridView.Columns[i].Width = 80;
                dataGridView.Columns[i].AutoSizeMode = DataGridViewAutoSizeColumnMode.DisplayedCells;
            }
            dataGridView.Columns[ColumNameOperationDescription].MinimumWidth = 80;
            dataGridView.Columns[ColumNameOperationDescription].AutoSizeMode = DataGridViewAutoSizeColumnMode.Fill;
        }

        #endregion


        #region "菜单事件"

        private void clearAllToolStripMenuItem_Click(object sender, EventArgs e)
        {
            try
            {
                this.dataGridView.Rows.Clear();
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
                // 操作结果
                var theResultCell = dataGridView.Rows[e.RowIndex].Cells[ColumNameResultType];
                if (theResultCell.Tag != null)
                {
                    var resultType = (OperationResult)theResultCell.Tag;
                    if (resultType == OperationResult.Success)
                    {
                        theResultCell.Style.ForeColor = Color.DarkGreen;
                    }
                    else if (resultType == OperationResult.Failure)
                    {
                        theResultCell.Style.BackColor = Color.Red;
                    }
                    else if (resultType == OperationResult.Timeout)
                    {
                        theResultCell.Style.BackColor = Color.Yellow;
                    }
                }

                // 执行方式
                var theExecuteStyleCell = dataGridView.Rows[e.RowIndex].Cells[ColumNameExeMode];
                if (theExecuteStyleCell.Tag != null)
                {
                    var isManual = (bool)theExecuteStyleCell.Tag;
                    theExecuteStyleCell.Style.ForeColor = isManual ? Color.Blue : Color.DarkGray;
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
