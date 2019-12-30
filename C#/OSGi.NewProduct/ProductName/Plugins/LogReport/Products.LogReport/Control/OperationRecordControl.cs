using System;
using System.Collections.Generic;
using System.Linq;
using Acl.Utility;
using Acl.Controls;
using Products.LogReport.Data;
using Products.Infrastructure.Types;

namespace Products.LogReport.Control
{
    [Report("操作记录", "操作记录", "Products.LogReport.ReportForm.OperationRecord.rdlc", Order = 5)]
    partial class OperationRecordControl : QueryControl
    {
        public OperationRecordControl()
        {
            InitializeComponent();

            InitialUpate();
        }

        private void InitialUpate()
        {
            var customDescriptors = new List<EnumUtility.IEnumFieldDescriptor>();
            customDescriptors.Add(EnumUtility.CreateDescriptor("choose", 0xFF, "--请选择--"));

            // 初始化执行类型
            cbxExecuteMode.SelectedIndex = 0;
            
            // 初始化操作类型
            cmbOperateType.BindEnum(customDescriptors, false, new List<OperationType>() { OperationType.None });
        }

        protected override object DoQuery()
        {
            var operationType = OperationType.None;
            bool? isManual = null;

            this.Invoke(() =>
            {
                var Date1 = DateTime.Parse(this.BeginTime.ToShortDateString());
                var Date2 = DateTime.Parse(this.EndTime.ToShortDateString());

                CheckingStartStopTime(Date1, Date2);
                
                if (cmbOperateType.SelectedIndex > 0) operationType = cmbOperateType.GetEnumValue<OperationType>().Value;
                if (cbxExecuteMode.SelectedIndex > 0) isManual = cbxExecuteMode.SelectedIndex == 2;
            }, LogUtility.Log, true);

            if (isManual == null)
            {
                return new List<OperationRecordInfo>();
            }
            else
            {
                return OperationRecordQueryable.Query(this.BeginTime, this.EndTime, operationType, isManual).ToList();
            }
        }
    }
}
