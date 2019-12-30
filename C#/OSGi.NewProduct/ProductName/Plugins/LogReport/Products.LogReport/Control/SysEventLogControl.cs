using System;
using System.Collections.Generic;
using Acl.Utility;
using Acl.Controls;
using Products.LogReport.Data;
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

        private void InitialUpdate()
        {
            // 初始化事件类型、事件级别
            var customDescriptors = new List<EnumUtility.IEnumFieldDescriptor>();
            customDescriptors.Add(EnumUtility.CreateDescriptor("choose", 0xFF, "--请选择--"));
            cmbEventLevel.BindEnum(customDescriptors, false, new List<EventLevel>() { EventLevel.None });
            cmbEventType.BindEnum(customDescriptors, false, new List<EventType>() { EventType.None });
        }

        protected override object DoQuery()
        {
            DateTime currentDate = DateTime.Now;
            DateTime? tempStart = null, tempStop = null;
            string eventLevel = "";
            string eventType = "";

            this.Invoke(() =>
            {
                var Date1 = DateTime.Parse(this.BeginTime.ToShortDateString());
                var Date2 = DateTime.Parse(this.EndTime.ToShortDateString());

                CheckingStartStopTime(Date1, Date2);

                currentDate = this.BeginTime;

                tempStart = this.BeginTime;
                tempStop = this.EndTime;

                if (cmbEventLevel.SelectedIndex > 0) eventLevel = cmbEventLevel.Text;
                if (cmbEventType.SelectedIndex > 0) eventType = cmbEventType.Text; ;
            }, LogUtility.Log, true);

            if (tempStart == null)
            {
                return new List<SysEventLogInfo>();
            }

            var result = SysEventLogInfoQueryable.Query(tempStart.Value, tempStop.Value, eventLevel, eventType);

            return result;
        }
    }
}
