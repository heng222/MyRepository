//---------------------------------------------------------------------
//
// File: MyAppointmentEditForm.cs
//
// Description:
// The UI of show sessionInfo and edit sessionInfo 
//
// Author: terry
//
// Copyright (C) 2008 by ISoftstone Corporation.  All rights reserved.
//
//Modify history:   
//---------------------------------------------------------------------
using System;
using System.Windows.Forms;
using DevExpress.XtraScheduler;
using DevExpress.XtraScheduler.UI;
using DevExpress.XtraEditors.Controls;
using ProWrite.Entity.Library;
using System.Drawing;
using ProWrite.Core;

namespace ProWrite.UI.Controls.Scheduler
{
    public partial class MyAppointmentEditForm : DevExpress.XtraEditors.XtraForm
    {
        SchedulerControl control;
        ScheduleControl scheCtrl;
        Appointment apt;
        AppointmentInfo appInfo;
        bool openRecurrenceForm = false;
        bool isRecurrence = false;
        int suspendUpdateCount;
        private DevExpress.XtraEditors.CheckEdit checkAllDay;

        MyAppointmentFormController controller;
        AppointmentConverter appConverter = new AppointmentConverter();

        public MyAppointmentEditForm(ScheduleControl scheControl, Appointment apt, bool openRecurrenceForm)
        {
            scheCtrl = scheControl;
            control = scheCtrl.Scheduler;
            this.openRecurrenceForm = openRecurrenceForm;
            this.controller = new MyAppointmentFormController(control, apt);

            this.apt = apt;
            //
            // Required for Windows Form Designer support
            //
            SuspendUpdate();
            InitializeComponent();
            ResumeUpdate();
            populateLookup();
            UpdateForm();
            controller.Start = this.dtStart.DateTime.Date + this.timeStart.Time.TimeOfDay;
            controller.End = this.dtEnd.DateTime.Date + this.timeEnd.Time.TimeOfDay;
            isRecurrence = apt.IsRecurring;
            if (apt.Description != LibraryType.Message.ToString())
                this.chkPlayOnce.Enabled = false;
            else
            {
                if (apt.IsRecurring || isRecurrence)
                    this.chkPlayOnce.Enabled = false;
                else
                    chkPlayOnce.Enabled = !apt.AllDay;
            }
            //{
            //    //dtStart.Enabled = false;
            //    dtEnd.Enabled = false;
            //    //timeStart.Enabled = false;
            //    timeEnd.Enabled = false;
            //    checkAllDay.Enabled = false;
            //}
            if (apt.RecurrenceInfo != null)
            {
                dtStart.Enabled = false;
                dtEnd.Enabled = false;
                timeStart.Enabled = false;
                timeEnd.Enabled = false;
                //checkAllDay.Enabled = false;
            }
        }

        protected AppointmentStorage Appointments
        {
            get { return control.Storage.Appointments; }
        }

        protected bool IsUpdateSuspended { get { return suspendUpdateCount > 0; } }

        protected void SuspendUpdate()
        {
            suspendUpdateCount++;
        }

        protected void ResumeUpdate()
        {
            if (suspendUpdateCount > 0)
                suspendUpdateCount--;
        }

        private void populateLookup()
        {
            populateLookup(string.Empty);
        }

        private void populateLookup(string libraryGrpName)
        {
            LibraryGroup list = LibraryGroup.Current;
            if (list == null)
                return;
        }

        private void btnAddRec_Click(object sender, System.EventArgs e)
        {
            OnRecurrenceButton();
        }

        void OnRecurrenceButton()
        {
            ShowRecurrenceForm();
        }

        void ShowRecurrenceForm()
        {

            if (!control.SupportsRecurrence)
                return;

            // Prepare to edit appointment's recurrence.
            Appointment editedAptCopy = controller.EditedAppointmentCopy;
            Appointment editedPattern = controller.EditedPattern;
            Appointment patternCopy = controller.PrepareToRecurrenceEdit();

            AppointmentRecurrenceForm dlg = new AppointmentRecurrenceForm(patternCopy, control.OptionsView.FirstDayOfWeek, controller);
            dlg.Text = "Schedule Recurrence";
            dlg.ShowIcon = false;
            // Required for skins support.
            dlg.LookAndFeel.ParentLookAndFeel = this.LookAndFeel.ParentLookAndFeel;
            dlg.Controls[5].Text = "Play Time";
            dlg.Controls[4].Controls[5].Visible = false;
            dlg.Controls[4].Controls[7].Visible = false;
            dlg.Controls[4].Controls[3].Controls[1].Visible = false;
            //dlg.Controls[4].Height = 120;
            dlg.Controls[4].Controls[6].Location = new Point(16, 40);
            dlg.Controls[4].Controls[4].Location = new Point(16, 78);
            if (editedAptCopy.Description == "Message")
            {
                dlg.Controls[5].Controls[1].Enabled = false;
                //dlg.Controls[5].Controls[3].Enabled = false;
                dlg.Controls[5].Controls[0].Enabled = false;
            }
            DialogResult result = dlg.ShowModalDialog();
            dlg.Dispose();

            if (result == DialogResult.Abort)
            {
                controller.RemoveRecurrence();
                isRecurrence = false;
                dtStart.Enabled = true;
                dtEnd.Enabled = !chkPlayOnce.Checked;
                chkPlayOnce.Enabled = !checkAllDay.Checked;
                timeStart.Enabled = true;
                timeEnd.Enabled = !chkPlayOnce.Checked; //apt.Description != LibraryType.Message.ToString();
            }
            else
                if (result == DialogResult.OK)
                {
                    controller.ApplyRecurrence(patternCopy);
                    isRecurrence = true;
                    chkPlayOnce.Checked = false;
                    chkPlayOnce.Enabled = false;
                    chkPlayOnce.Enabled = false;
                    checkAllDay.Enabled = true;
                    if (controller.EditedAppointmentCopy != editedAptCopy)
                        UpdateForm();

                }
            UpdateIntervalControls();
            if (isRecurrence)
            {
                dtStart.Enabled = false;
                dtEnd.Enabled = false;
                timeStart.Enabled = false;
                timeEnd.Enabled = false;
            }
        }

        private void btnOK_Click(object sender, System.EventArgs e)
        {
            // Required to check appointment's conflicts.
            if (!controller.IsConflictResolved())
                return;
            //if (apt.RecurrenceInfo != null)
            //{

            controller.Subject = txSubject.Text;
            controller.AllDay = this.checkAllDay.Checked;
            //controller.
            controller.Start = this.dtStart.DateTime.Date + this.timeStart.Time.TimeOfDay;
            controller.End = this.dtEnd.DateTime.Date + this.timeEnd.Time.TimeOfDay;
            AppointmentInfo info = Array.Find<AppointmentInfo>(scheCtrl.Model.Items, p => { return p.Subject == controller.Subject; });
            if (info != null)
            {
                info.ExactTiming = checkEdit1.Checked;
                info.PlayMessageOnce = chkPlayOnce.Checked;
            }
            //if(info.PlayMessageOnce)
            //    controller.End = controller.Start + apt.
            // Save all changes made to the appointment edited in a form.
            controller.ApplyChanges();
            //}
        }

        void UpdateForm()
        {
            SuspendUpdate();
            try
            {
                txSubject.Text = controller.Subject;
                lblType.Text = controller.Description;

                dtStart.DateTime = controller.Start.Date;
                dtEnd.DateTime = controller.End.Date;

                timeStart.Time = DateTime.MinValue.AddTicks(controller.Start.TimeOfDay.Ticks);
                timeEnd.Time = DateTime.MinValue.AddTicks(controller.End.TimeOfDay.Ticks);
                checkAllDay.Checked = controller.AllDay;
                AppointmentInfo info = Array.Find<AppointmentInfo>(scheCtrl.Model.Items, p => { return p.Subject == controller.Subject; });
                if (info != null)
                {
                    checkEdit1.Checked = info.ExactTiming;
                    chkPlayOnce.Checked = info.PlayMessageOnce;
                    dtEnd.Enabled = !info.PlayMessageOnce;
                    timeEnd.Enabled = !info.PlayMessageOnce;
                    checkAllDay.Enabled = !info.PlayMessageOnce;

                }

            }
            finally
            {
                ResumeUpdate();
            }
            UpdateIntervalControls();
        }

        private void MyAppointmentEditForm_Activated(object sender, System.EventArgs e)
        {
            // Required to show the recurrence form.
            if (openRecurrenceForm)
            {
                openRecurrenceForm = false;
                OnRecurrenceButton();
            }
        }

        private void dtStart_EditValueChanged(object sender, System.EventArgs e)
        {
            if (!IsUpdateSuspended)
                controller.Start = dtStart.DateTime.Date + timeStart.Time.TimeOfDay;
            UpdateIntervalControls();
        }

        protected virtual void UpdateIntervalControls()
        {
            if (IsUpdateSuspended)
                return;

            SuspendUpdate();
            try
            {
                dtStart.EditValue = controller.Start.Date;
                dtEnd.EditValue = controller.End.Date;
                timeStart.EditValue = controller.Start.TimeOfDay;
                timeEnd.EditValue = controller.End.TimeOfDay;
                if (!chkPlayOnce.Checked && !isRecurrence)
                {
                    dtStart.Enabled = !controller.AllDay;
                    dtEnd.Enabled = !controller.AllDay;
                    timeStart.Enabled = !controller.AllDay;
                    timeEnd.Enabled = !controller.AllDay;
                }

            }
            finally
            {
                ResumeUpdate();
            }
        }

        private void timeStart_EditValueChanged(object sender, System.EventArgs e)
        {
            if (!IsUpdateSuspended)
                controller.Start = dtStart.DateTime.Date + timeStart.Time.TimeOfDay;
            UpdateIntervalControls();
        }

        private void timeEnd_EditValueChanged(object sender, System.EventArgs e)
        {
            if (IsUpdateSuspended) return;
            if (IsIntervalValid())
                controller.End = dtEnd.DateTime + timeEnd.Time.TimeOfDay;
            else
                timeEnd.EditValue = controller.End.TimeOfDay;
        }

        private void dtEnd_EditValueChanged(object sender, System.EventArgs e)
        {
            if (IsUpdateSuspended) return;
            if (IsIntervalValid())
                controller.End = dtEnd.DateTime + timeEnd.Time.TimeOfDay;
            else
                dtEnd.EditValue = controller.End.Date;
        }

        bool IsIntervalValid()
        {
            DateTime start = dtStart.DateTime + timeStart.Time.TimeOfDay;
            DateTime end = dtEnd.DateTime + timeEnd.Time.TimeOfDay;
            return end >= start;
        }

        private void checkAllDay_CheckedChanged(object sender, System.EventArgs e)
        {
            controller.AllDay = this.checkAllDay.Checked;
            if (apt.Description == LibraryType.Message.ToString())
            {
                if (isRecurrence)
                    chkPlayOnce.Enabled = false;
                else
                    chkPlayOnce.Enabled = !checkAllDay.Checked;
            }
            if (!IsUpdateSuspended)
                UpdateAppointmentStatus();

            UpdateIntervalControls();
        }

        void UpdateAppointmentStatus()
        {
            //AppointmentStatus currentStatus = edStatus.Status;
            //AppointmentStatus newStatus = controller.UpdateAppointmentStatus(currentStatus);
            //if (newStatus != currentStatus)
            //    edStatus.Status = newStatus;
        }

        private void chkPlayOnce_CheckedChanged(object sender, EventArgs e)
        {
            if (isRecurrence)
                return;
            dtEnd.Enabled = !chkPlayOnce.Checked;
            timeEnd.Enabled = !chkPlayOnce.Checked;
            checkAllDay.Enabled = !chkPlayOnce.Checked;
            if (chkPlayOnce.Checked)
                checkAllDay.Checked = false;
            appInfo = appConverter.Convert(apt);

            controller.Start = dtStart.DateTime.Date + timeStart.Time.TimeOfDay;
            double length = Convert.ToDouble(appInfo.Target.Length) / 3600;
            if (chkPlayOnce.Checked)
                controller.End = controller.Start.AddSeconds(appInfo.Target.Length);
            else
                controller.End = controller.Start + apt.Duration;
            //dtStart.EditValue = controller.Start.Date;
            //dtEnd.EditValue = controller.End.Date;
            //timeStart.EditValue = controller.Start.TimeOfDay;
            //timeEnd.EditValue = controller.End.TimeOfDay;
            UpdateIntervalControls();
        }

    }
    public class MyAppointmentFormController : AppointmentFormController
    {

        public string CustomName { get { return (string)EditedAppointmentCopy.CustomFields["CustomName"]; } set { EditedAppointmentCopy.CustomFields["CustomName"] = value; } }
        public string CustomStatus { get { return (string)EditedAppointmentCopy.CustomFields["CustomStatus"]; } set { EditedAppointmentCopy.CustomFields["CustomStatus"] = value; } }

        string SourceCustomName { get { return (string)SourceAppointment.CustomFields["CustomName"]; } set { SourceAppointment.CustomFields["CustomName"] = value; } }
        string SourceCustomStatus { get { return (string)SourceAppointment.CustomFields["CustomStatus"]; } set { SourceAppointment.CustomFields["CustomStatus"] = value; } }

        public MyAppointmentFormController(SchedulerControl control, Appointment apt)
            : base(control, apt)
        {
        }

        public override bool IsAppointmentChanged()
        {
            if (base.IsAppointmentChanged())
                return true;
            return SourceCustomName != CustomName ||
                SourceCustomStatus != CustomStatus;
        }

        protected override void ApplyCustomFieldsValues()
        {
            SourceCustomName = CustomName;
            SourceCustomStatus = CustomStatus;
        }
    }
}
