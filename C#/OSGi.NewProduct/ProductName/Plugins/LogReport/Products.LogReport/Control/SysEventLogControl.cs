using System;
using System.Collections;
using System.Collections.Generic;
using System.Windows.Forms;

using Acl.Utility;

using Products.Infrastructure.Types;

namespace Products.LogReport.Control
{
    [Report("系统事件", "系统事件", "Products.LogReport.ReportForm.SysEventLog.rdlc", Order = 5)]
    partial class SysEventLogControl : QueryControl
    {
        public SysEventLogControl()
        {
            InitializeComponent();

            InitialUpdate();
        }

        #region "Properties"
        public EventLevel EventLevel { get; private set; }
        public EventType EventType { get; private set; }
        #endregion

        #region "Private methods"

        private void InitialUpdate()
        {
            // 初始化事件类型、事件级别
            var customDescriptors = new List<EnumUtility.IEnumFieldDescriptor>();
            customDescriptors.Add(EnumUtility.CreateDescriptor("choose", 0xFF, "--请选择--"));
            cmbEventLevel.BindEnum(customDescriptors, false, new EventLevel[] { EventLevel.None });
            cmbEventType.BindEnum(customDescriptors, false, new EventType[] { EventType.None });
        }
        #endregion

        #region "Protected methods"
        protected override ICollection DoQuery()
        {
            return SysEventLogInfoQueryable.Query(this.BeginTime, this.EndTime, this.EventLevel, this.EventType);
        }
        #endregion

        #region "控件事件处理函数"
        #endregion


        #region "控件事件"

        private void cmbEventLevel_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (cmbEventLevel.SelectedIndex > 0)
                this.EventLevel = cmbEventLevel.GetEnumValue<EventLevel>().Value;
            else
                this.EventLevel = EventLevel.None;
        }

        private void cmbEventType_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (cmbEventType.SelectedIndex > 0)
                this.EventType = cmbEventType.GetEnumValue<EventType>().Value;
            else
                this.EventType = EventType.None;
        }
        #endregion
    }
}
