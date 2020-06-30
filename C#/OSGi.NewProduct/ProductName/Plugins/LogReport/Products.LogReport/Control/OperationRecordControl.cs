using System;
using System.Collections;
using System.Collections.Generic;

using Acl.Controls;
using Acl.Utility;

using Products.Infrastructure.Types;

namespace Products.LogReport.Control
{
    [Report("操作记录", "操作记录", "Products.LogReport.ReportForm.OperationLog.rdlc", Order = 5)]
    partial class OperationRecordControl : QueryControl
    {
        #region "Constructor"
        public OperationRecordControl()
        {
            InitializeComponent();

            InitialUpate();
        }
        #endregion

        #region "Properties"
        public OperationType OperationType { get; private set; }

        public bool? IsManual { get; private set; }
        #endregion


        #region "private methods"
        private void InitialUpate()
        {
            var customDescriptors = new List<EnumUtility.IEnumFieldDescriptor>();
            customDescriptors.Add(EnumUtility.CreateDescriptor("choose", 0xFF, "--请选择--"));

            // 初始化执行类型
            cbxExecuteMode.SelectedIndex = 0;

            // 初始化操作类型
            cmbOperateType.BindEnum(customDescriptors, false, new List<OperationType>() { OperationType.None });
        }
        #endregion

        #region "Protected methods"
        protected override ICollection DoQuery()
        {
            return OperationRecordQueryable.Query(this.BeginTime, this.EndTime, this.OperationType, this.IsManual);
        }
        #endregion

        #region "控件事件"
        private void cmbOperateType_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (cmbOperateType.SelectedIndex > 0)
                this.OperationType = cmbOperateType.GetEnumValue<OperationType>().Value;
            else
                this.OperationType = OperationType.None;
        }

        private void cbxExecuteMode_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (cbxExecuteMode.SelectedIndex > 0)
                this.IsManual = cbxExecuteMode.SelectedIndex == 2;
            else
                this.IsManual = null;
        }
        #endregion
    }
}
