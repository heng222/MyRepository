//---------------------------------------------------------------------
//
// File: ScheduleControl.cs
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
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Text;
using System.Windows.Forms;
using DevExpress.XtraScheduler.Drawing;
using DevExpress.XtraTreeList.Nodes;
using ProWrite.Entity.Library;
using DevExpress.XtraTreeList;
using DevExpress.XtraScheduler;
using DevExpress.XtraScheduler.Localization;
using DevExpress.XtraScheduler.Services;
using DevExpress.XtraEditors;
using ProWrite.UI.Controls.Common;
using ProWrite.UI.Controls.Scheduler;
using ProWrite.UI.Controls.Library;
using System.Reflection;
using DevExpress.XtraScheduler.Native;
using ProWrite.UI.Controls.UndoRedo.Action;
using ProWrite.Core;
using ProWrite.Entity.Settings;
using ProWrite.UI.Controls.Common.Messages;
using System.Communication.Messaging;
using ProWrite.UI.Controls.Actions.UFE.Requests;
using DevExpress.Utils.Menu;
using DevExpress.XtraBars;
using System.IO;
using DevExpress.XtraScheduler.UI;
using ProWrite.UI.Controls.Editor;



namespace ProWrite.UI.Controls.Scheduler
{
    /// <summary>
    /// show sessionInfo and edit sessionInfo 
    /// </summary>
    public partial class ScheduleControl : ControlPanel<SchedulerInfo, ScheduleControl>
    {
        private IDateTimeNavigationService _navigate;
        DateTime oldEnd;
        DateTime oldStart;
        TimeSpan oldDuration;
        int oldLabelId;
        public bool IsOpen = false;

        private UploadAction _uploadAction = null;
        private bool _IsTimeSliceEmpty = false;
        MyAppointmentFormController controller;
        private BindingSource myBindingSource = new BindingSource();
        protected override void DoPopulate()
        {
            IsOpen = true;
            if (_model != null && _model.Items != null && _model.Items.Length > 0)
            {
                foreach (AppointmentInfo item in _model.Items)
                {
                    Appointment appNew;
                    if (item.RecurrenceInfo != null)
                        appNew = new Appointment(AppointmentType.Pattern);
                    else
                        appNew = new Appointment();
                    appNew.Subject = item.Subject;
                    //appNew.Location = item.Subject + item.Description;
                    appNew.LabelId = item.LabelId;
                    appNew.StatusId = 0;
                    appNew.Start = item.Start;
                    appNew.AllDay = item.AllDay;

                    appNew.Duration = item.Duration;
                    appNew.End = item.End;
                    appNew.Description = item.Description;
                    appNew.HasReminder = item.HasReminder;
                    if (item.Type == LibraryType.TimeSliceGroup)
                        appNew.Description = "Time Slice Group";
                    appNew.CustomFields["Only"] = item.Subject
                        + item.Description
                        + item.Start.ToString()
                        + item.End.ToString();

                    if (item.RecurrenceInfo != null)
                    {
                        appNew.RecurrenceInfo.AllDay = item.RecurrenceInfo.AllDay;
                        appNew.RecurrenceInfo.DayNumber = item.RecurrenceInfo.DayNumber;
                        appNew.RecurrenceInfo.Start = item.RecurrenceInfo.Start;
                        appNew.RecurrenceInfo.Duration = item.RecurrenceInfo.Duration;
                        appNew.RecurrenceInfo.End = item.RecurrenceInfo.End;
                        appNew.RecurrenceInfo.Month = item.RecurrenceInfo.Month;
                        appNew.RecurrenceInfo.OccurrenceCount = item.RecurrenceInfo.OccurrenceCount;
                        appNew.RecurrenceInfo.Periodicity = item.RecurrenceInfo.Periodicity;
                        appNew.RecurrenceInfo.Range = (RecurrenceRange)item.RecurrenceInfo.Range;

                        appNew.RecurrenceInfo.Type = (RecurrenceType)item.RecurrenceInfo.Type;
                        appNew.RecurrenceInfo.WeekDays = (WeekDays)item.RecurrenceInfo.WeekDays;
                        appNew.RecurrenceInfo.WeekOfMonth = (WeekOfMonth)item.RecurrenceInfo.WeekOfMonth;
                    }
                    schedulerStorage1.Appointments.Add(appNew);
                }
            }

            _uploadAction = new UploadAction(_sign, _model);
            LocalMessageBus.Send(null, new MenuMessage(new MenuCommand[]{
                new MenuCommand{ Command= MenuCommands.Copy, Enabled = schedulerControl1.SelectedAppointments.Count > 0, Visibility = ItemVisibility.Always}
                , new MenuCommand{ Command= MenuCommands.Delete, Enabled = schedulerControl1.SelectedAppointments.Count > 0, Visibility = ItemVisibility.Always}
                }));

            if (_sign.Controller.Connection.User.Status != ProWrite.UFE.UserStatus.Online)
            {
                LocalMessageBus.Subject<LoginSuccessMessage>().Observers += (s, e) =>
                {
                    if (s == _sign)
                    {
                        _uploadAction.SubscribeFtpEvent();
                    }
                };
                // _sign.Controller.UserManager.LoginSuccessed += p => { _uploadAction.SubscribeFtpEvent(); };
            }
            else
                _uploadAction.SubscribeFtpEvent();

            _sign.Controller.Connection.ConnectionClosed += delegate { _uploadAction.UnsubscribeFtpEvent(); };
            IsOpen = false;
        }


        static Stream GetFileStream(string fileName)
        {
            return new StreamReader(fileName).BaseStream;
        }

        public override void InsertLibrary(params MemoryLibraryItem[] items)
        {
            if (items != null)
            {

                AppointmentBaseCollection appointments = new AppointmentBaseCollection();

                var extends = new Dictionary<string, bool>();

                Array.ForEach<MemoryLibraryItem>(items, item => { _model.Add(new AppointmentInfo { Subject = item.Name, ExactTiming = false, PlayMessageOnce = false, Target = item }); });
                //Array.ForEach<AppointmentInfo>(_model.Items, p => { extends[p.Subject] = p.ExactTiming; });

                string emptyTimeSliceGroup = "";
                for (int i = 0; i < items.Length; i++)
                {
                    _IsTimeSliceEmpty = false;
                    if (items[i].Type == LibraryType.TimeSliceGroup)
                    {

                        TimeSliceGroupInfo timeSlice = items[i] as TimeSliceGroupInfo;
                        if (timeSlice.Items == null || timeSlice.Items.Length <= 0)
                        {
                            _IsTimeSliceEmpty = true;
                            if (string.IsNullOrEmpty(emptyTimeSliceGroup))
                                emptyTimeSliceGroup += "\n\t" + "'" + items[i].Name + "'" + "\n";
                            else
                                emptyTimeSliceGroup += "\t'" + items[i].Name + "'" + "\n";
                        }
                        else
                            _IsTimeSliceEmpty = false;
                    }
                    if (!_IsTimeSliceEmpty)
                    {
                        appointments = GetNewData(items[i]);

                        foreach (Appointment app in appointments)
                        {
                            Appointment appNew;
                            if (app.RecurrenceInfo != null)
                                appNew = new Appointment(AppointmentType.Pattern);
                            else
                                appNew = new Appointment();
                            appNew.Subject = app.Subject;
                            //appNew.Location = app.Subject + app.Description;
                            appNew.LabelId = app.LabelId;
                            appNew.StatusId = 0;
                            appNew.Start = app.Start;
                            appNew.AllDay = true;

                            appNew.Duration = app.Duration;
                            appNew.End = app.End;
                            appNew.Description = app.Description;
                            appNew.HasReminder = app.HasReminder;
                            if (items[i].Type == LibraryType.TimeSliceGroup)
                                appNew.Description = "Time Slice Group";
                            appNew.CustomFields["Only"] = app.Subject
                                 + app.Description
                                 + app.Start.ToString()
                                 + app.End.ToString();
                            if (app.RecurrenceInfo != null)
                            {
                                appNew.RecurrenceInfo.AllDay = app.RecurrenceInfo.AllDay;
                                appNew.RecurrenceInfo.DayNumber = app.RecurrenceInfo.DayNumber;
                                appNew.RecurrenceInfo.Start = app.RecurrenceInfo.Start;
                                appNew.RecurrenceInfo.Duration = app.RecurrenceInfo.Duration;
                                appNew.RecurrenceInfo.End = app.RecurrenceInfo.End;
                                appNew.RecurrenceInfo.Month = app.RecurrenceInfo.Month;
                                appNew.RecurrenceInfo.OccurrenceCount = app.RecurrenceInfo.OccurrenceCount;
                                appNew.RecurrenceInfo.Periodicity = app.RecurrenceInfo.Periodicity;
                                appNew.RecurrenceInfo.Range = (RecurrenceRange)app.RecurrenceInfo.Range;

                                appNew.RecurrenceInfo.Type = (RecurrenceType)app.RecurrenceInfo.Type;
                                appNew.RecurrenceInfo.WeekDays = (WeekDays)app.RecurrenceInfo.WeekDays;
                                appNew.RecurrenceInfo.WeekOfMonth = (WeekOfMonth)app.RecurrenceInfo.WeekOfMonth;
                            }
                            schedulerStorage1.Appointments.Add(appNew);

                        }
                    }
                }
                if (!string.IsNullOrEmpty(emptyTimeSliceGroup))
                {
                    MsgBox.Warning("Sorry,can not add empty Time Slice Group:" + emptyTimeSliceGroup + " into a sessionInfo.");
                }
                ChangedService.MarkChanged();
                LocalMessageBus.Send(null, new MenuMessage(new MenuCommand[]{
                new MenuCommand{ Command= MenuCommands.Copy, Enabled = schedulerControl1.SelectedAppointments.Count > 0, Visibility = ItemVisibility.Always}
                , new MenuCommand{ Command= MenuCommands.Delete, Enabled = schedulerControl1.SelectedAppointments.Count > 0, Visibility = ItemVisibility.Always}
                }));
            }
        }


        public void AddAppointments(params AppointmentInfo[] items)
        {
            if (items != null)
            {
                AppointmentBaseCollection appointments;
                List<Appointment> listApp = new List<Appointment>();
                for (int i = 0; i < items.Length; i++)
                {
                    appointments = new AppointmentBaseCollection();
                    appointments.Add(AppointmentConverter.Convert(items[i]));
                    foreach (Appointment item in appointments)
                    {
                        Appointment appNew;
                        if (item.RecurrenceInfo != null)
                            appNew = new Appointment(AppointmentType.Pattern);
                        else
                            appNew = new Appointment();
                        appNew.Subject = item.Subject;
                        //appNew.Location = item.Subject + item.Description;
                        appNew.LabelId = item.LabelId;
                        appNew.StatusId = 0;
                        appNew.Start = item.Start;
                        appNew.AllDay = item.AllDay;

                        appNew.Duration = item.Duration;
                        appNew.End = item.End;
                        appNew.Description = item.Description;
                        appNew.HasReminder = item.HasReminder;

                        appNew.CustomFields["Only"] = item.Subject
                             + item.Description
                             + item.Start.ToString()
                             + item.End.ToString();

                        if (item.RecurrenceInfo != null)
                        {
                            appNew.RecurrenceInfo.AllDay = item.RecurrenceInfo.AllDay;
                            appNew.RecurrenceInfo.DayNumber = item.RecurrenceInfo.DayNumber;
                            appNew.RecurrenceInfo.Start = item.RecurrenceInfo.Start;
                            appNew.RecurrenceInfo.Duration = item.RecurrenceInfo.Duration;
                            appNew.RecurrenceInfo.End = item.RecurrenceInfo.End;
                            appNew.RecurrenceInfo.Month = item.RecurrenceInfo.Month;
                            appNew.RecurrenceInfo.OccurrenceCount = item.RecurrenceInfo.OccurrenceCount;
                            appNew.RecurrenceInfo.Periodicity = item.RecurrenceInfo.Periodicity;
                            appNew.RecurrenceInfo.Range = (RecurrenceRange)item.RecurrenceInfo.Range;

                            appNew.RecurrenceInfo.Type = (RecurrenceType)item.RecurrenceInfo.Type;
                            appNew.RecurrenceInfo.WeekDays = (WeekDays)item.RecurrenceInfo.WeekDays;
                            appNew.RecurrenceInfo.WeekOfMonth = (WeekOfMonth)item.RecurrenceInfo.WeekOfMonth;
                        }
                        schedulerStorage1.Appointments.Add(appNew);
                    }
                }

                ChangedService.ResumeChanged();
                LocalMessageBus.Send(null, new MenuMessage(new MenuCommand[]{
                new MenuCommand{ Command= MenuCommands.Copy, Enabled = schedulerControl1.SelectedAppointments.Count > 0, Visibility = ItemVisibility.Always}
                , new MenuCommand{ Command= MenuCommands.Delete, Enabled = schedulerControl1.SelectedAppointments.Count > 0, Visibility = ItemVisibility.Always}
                }));
            }
        }


        /// <summary>
        /// Load sessionInfo information
        /// </summary>
        public override void LoadModelInfo()
        {
            var extends = new Dictionary<string, bool>();
            var extendsPlayMessage = new Dictionary<string, bool>();

            Array.ForEach<AppointmentInfo>(_model.Items, p => { extends[p.Subject] = p.ExactTiming; });

            Array.ForEach<AppointmentInfo>(_model.Items, p =>
            {
                //string location = "";
                //if (p.Location == p.Subject)
                //    location = p.Subject + "Message";
                //else
                //    location = p.Location;
                extendsPlayMessage[p.Subject] = p.PlayMessageOnce;
            });
            _model.Clear();

            if (schedulerStorage1.Appointments.Count > 0)
            {
                foreach (Appointment item in schedulerStorage1.Appointments.Items)
                {
                    var info = appointConverter.Convert(item);

                    info.ExactTiming = extends[item.Subject];
                    info.PlayMessageOnce = extendsPlayMessage[item.Subject];
                    //info.PlayMessageOnce = extends[item.Location];
                    _model.Add(info);

                }
            }
            //Array.ForEach<AppointmentInfo>(_model.Items, p => { extends[p.Subject] = p.PlayMessageOnce; });
            //foreach (AppointmentInfo item in _model.Items)
            //{
            //    if (item.Description == LibraryType.Message.ToString())
            //        item.PlayMessageOnce = extendsPlayMessage[item.Subject];
            //}

            _model.SchedulerViewType = (PWSchedulerViewType)ViewType;
        }

        public static string[] Users = new string[] { "Peter Dolan", "Ryan Fischer", "Andrew Miller", "Tom Hamlett",
                                                        "Jerry Campbell", "Carl Lucas", "Mark Hamilton", "Steve Lee" };

        [NonSerialized]
        internal AppointmentConverter appointConverter = new AppointmentConverter();

        internal SchedulerControl Scheduler { get { return schedulerControl1; } }

        private bool isEdit = true;
        public ScheduleControl()
        {
            SchedulerLocalizer.Active = new MyLocalizer();
            InitializeComponent();
            if (!DesignMode)
            {
                dateLbl.Text = System.DateTime.Now.ToShortDateString();
                schedulerControl1.OptionsCustomization.AllowInplaceEditor = UsedAppointmentType.None;

                schedulerControl1.GroupType = SchedulerGroupType.Resource;
                schedulerStorage1.Appointments.ResourceSharing = true;
                schedulerStorage1.Appointments.Labels.Clear();
                foreach (LibraryItemColor itemColor in DataGate.LibraryItemColors)
                {
                    schedulerStorage1.Appointments.Labels.Add(new AppointmentLabel(itemColor.Color, itemColor.Name));
                }
                schedulerStorage1._innerCtrl = this;

                IDateTimeNavigationService navigate = schedulerControl1.Services.DateTimeNavigation;
                navigate.GoToToday();

                _navigate = new NavigateDecorator(schedulerControl1, navigate);
                schedulerControl1.Services.RemoveService(typeof(IDateTimeNavigationService));
                schedulerControl1.Services.AddService(typeof(IDateTimeNavigationService), _navigate);
                ControlService.LibraryTree.Controller.LibraryColorChanged +=
                    new EventHandler<LibraryTreeControl.LibraryColorChangedEventArgs>(Controller_LibraryColorChanged);
                MessageBus.Subject<LibraryRenameMessage>().Observers += new ObserverHandler<LibraryRenameMessage>(OnLibraryRename);
                MessageBus.Subject<LibraryLenghtChangedMessage>().Observers += new ObserverHandler<LibraryLenghtChangedMessage>(OnLibraryLengthChaged);
            }
            RegisterHelp();
        }

        private void RegisterHelp()
        {
            this.SetShowHelp(HelpNavigator.Topic, Resources.Resource.Helps.SchedulerCalendar);
        }

        void OnLibraryLengthChaged(object sender, LibraryLenghtChangedMessage msg)
        {
            var extends = new Dictionary<string, bool>();
            var extendsPlayMessage = new Dictionary<string, bool>();

            Array.ForEach<AppointmentInfo>(_model.Items, p => { extends[p.Subject] = p.ExactTiming; });

            Array.ForEach<AppointmentInfo>(_model.Items, p =>
            {
                extendsPlayMessage[p.Subject] = p.PlayMessageOnce;
            });

            foreach (Appointment appointment in schedulerStorage1.Appointments.Items)
            {
                if (appointment.Subject == msg.Name
                    && appointment.Description == msg.Type.ToString())
                {
                    var info = appointConverter.Convert(appointment);

                    double length = Convert.ToDouble(msg.Length) / 3600;
                    if (info.PlayMessageOnce
                        && appointment.Description == LibraryType.Message.ToString())
                        appointment.Duration = TimeSpan.FromHours(length);

                }
            }
            foreach (AppointmentInfo item in _model.Items)
            {
                if (item.Subject == msg.Name
                                  && item.Target.Type == msg.Type)
                {
                    double length = Convert.ToDouble(msg.Length) / 3600;
                    if (item.PlayMessageOnce && item.Description == LibraryType.Message.ToString())
                        item.Duration = TimeSpan.FromHours(length);
                }
            }


        }

        void OnLibraryRename(object sender, LibraryRenameMessage msg)
        {
            foreach (Appointment appointment in schedulerStorage1.Appointments.Items)
            {
                if (appointment.Subject == msg.OldName
                    && appointment.Description == msg.Type.ToString())
                {
                    appointment.Subject = msg.NewName;

                }
            }
            foreach (AppointmentInfo item in _model.Items)
            {
                if (item.Subject == msg.OldName
                                  && item.Target.Type == msg.Type)
                {
                    item.Subject = msg.NewName;
                }
            }
        }

        void Controller_LibraryColorChanged(object sender, LibraryTreeControl.LibraryColorChangedEventArgs e)
        {
            foreach (Appointment app in schedulerStorage1.Appointments.Items)
            {
                if (app.Subject == e.LibraryName && app.Description.Replace(" ", "") == e.LibraryTypeItem.ToString())
                    app.LabelId = e.ColorId;
            }
        }


        public static void FillResources(SchedulerStorage storage, int count)
        {
            ResourceCollection resources = storage.Resources.Items;
            storage.BeginUpdate();
            try
            {
                int cnt = Math.Min(count, Users.Length);
                for (int i = 1; i <= cnt; i++)
                    resources.Add(new Resource(i, Users[i - 1]));
            }
            finally
            {
                storage.EndUpdate();
            }
        }

        public override void SendToSign()
        {
            _uploadAction.Perform();
        }

        private void todayBtn_Click(object sender, EventArgs e)
        {
            GotoToday();

        }

        private void GotoToday()
        {
            _navigate.GoToToday();
        }

        private void priviousBtn_Click(object sender, EventArgs e)
        {
            _navigate.NavigateBackward();
        }

        private void nextBtn_Click(object sender, EventArgs e)
        {
            _navigate.NavigateForward();
        }

        private void schedulerControl1_SelectionChanged(object sender, EventArgs e)
        {
            dateLbl.Text = schedulerControl1.SelectedInterval.Start.ToShortDateString();
            //if (schedulerControl1.SelectedAppointments.Count > 0)
            //{
            //    AppointmentInfo appointment = appointConverter.Convert(schedulerControl1.SelectedAppointments[0]);
            //    ControlService.RefreshPropertyGrid(appointment);
            //    if (appointment.Target != null)
            //        ControlService.NailImageBox.Image = appointment.Target.Image;

            //}
        }

        private void schedulerControl1_ActiveViewChanged(object sender, EventArgs e)
        {
            cbView.EditValue = schedulerControl1.ActiveViewType;
        }

        private void schedulerControl1_DragEnter(object sender, DragEventArgs e)
        {
            //TreeListNode node = GetDragNode(e.Data);
            LibraryNode node = (LibraryNode)e.Data.GetData(typeof(LibraryNode));
            if (node == null || node.Tag == null)
                return;
            schedulerControl1.Focus();
            schedulerControl1.SelectedAppointments.Clear();
            e.Effect = DragDropEffects.Move;
            _IsTimeSliceEmpty = false;
            if ((node.Tag as MemoryLibraryItem).Type == LibraryType.TimeSliceGroup)
            {
                TimeSliceGroupInfo timeSlice = (node.Tag as MemoryLibraryItem) as TimeSliceGroupInfo;
                if (timeSlice.Items == null || timeSlice.Items.Length <= 0)
                    _IsTimeSliceEmpty = true;
                else
                    _IsTimeSliceEmpty = false;

            }
            if (_IsTimeSliceEmpty)
            {
                //schedulerStorage1.Appointments[schedulerStorage1.Appointments.Count - 1].Delete();
                MsgBox.Warning("Sorry,can not add empty Time Slice Group into a sessionInfo");
                return;//schedulerStorage1.Appointments.Remove(schedulerStorage1.Appointments[schedulerStorage1.Appointments.Count - 1]);
            }


            this.schedulerControl1.DoDragDrop(GetDragData(node.Tag as MemoryLibraryItem), DragDropEffects.All);

            //if (IsRepeatStartTime())
            //{
            //    schedulerStorage1.Appointments.Remove(schedulerStorage1.Appointments[schedulerStorage1.Appointments.Count]);
            //    MsgBox.Warning("Sorry,a start time is allowed has only one appointment");
            //}
        }

        private void schedulerControl1_AppointmentDrop(object sender, AppointmentDragEventArgs e)
        {
            if (e.EditedAppointment.Description == LibraryType.Message.ToString()
                && e.EditedAppointment.AllDay
                && !e.SourceAppointment.AllDay)
            {
                AppointmentInfo info = Array.Find<AppointmentInfo>(this.Model.Items, p => { return p.Subject == e.EditedAppointment.Subject; });
                if (info.PlayMessageOnce)
                {
                    e.Allow = false;
                    e.Handled = true;
                    return;
                }
                //e.EditedAppointment.AllDay = false;
                //e.EditedAppointment.Start = e.SourceAppointment.Start;
                //e.EditedAppointment.End = e.SourceAppointment.End;
                //e.EditedAppointment.Duration = e.SourceAppointment.Duration;
            }
            if (e.SourceAppointment.RecurrenceInfo != null)
            {
                DeleteRecurrenceConfirmDialog dialog = new DeleteRecurrenceConfirmDialog();
                dialog.ShowDialog();
                int result = dialog.DeleteRecurrence;
                if (result == 0) //MsgBox.Confirm("Any exceptions associated with this recurring appointment will be lost. Proceed?") == DialogResult.No)
                {
                    e.Allow = false;
                    e.Handled = true;
                    return;
                }
                else
                {
                    //IsOpen = true;
                    UndoManager.BeginTransaction("app");
                    RecurrenceInfo recurrence = e.SourceAppointment.RecurrenceInfo;

                    Appointment aptEdit = e.EditedAppointment;
                    var parttern = e.SourceAppointment.RecurrencePattern;
                    if (parttern != null)
                        parttern.Delete();

                    Appointment appNew;
                    Appointment app = e.SourceAppointment;
                    //appNew.RecurrencePattern = e.SourceAppointment.RecurrencePattern;
                    if (recurrence != null && result == 1)
                        appNew = new Appointment(AppointmentType.Pattern);
                    else
                        appNew = new Appointment();
                    appNew.Subject = aptEdit.Subject;
                    //appNew.Location = aptEdit.Subject + aptEdit.Description;
                    appNew.LabelId = aptEdit.LabelId;
                    appNew.StatusId = 0;
                    appNew.Start = aptEdit.Start;


                    appNew.Duration = aptEdit.Duration;
                    appNew.End = aptEdit.End;
                    appNew.Description = aptEdit.Description;
                    appNew.HasReminder = aptEdit.HasReminder;
                    if (aptEdit.Description == LibraryType.TimeSliceGroup.ToString())
                        appNew.Description = "Time Slice Group";
                    appNew.CustomFields["Only"] = aptEdit.Subject
                        + aptEdit.Description
                        + aptEdit.Start.ToString()
                        + aptEdit.End.ToString();

                    if (recurrence != null && result == 1)
                    {

                        appNew.RecurrenceInfo.AllDay = recurrence.AllDay;
                        appNew.RecurrenceInfo.DayNumber = recurrence.DayNumber;
                        appNew.RecurrenceInfo.Start = aptEdit.Start;
                        appNew.RecurrenceInfo.Duration = aptEdit.Duration;
                        appNew.RecurrenceInfo.End = aptEdit.End;
                        appNew.RecurrenceInfo.Month = recurrence.Month;
                        appNew.RecurrenceInfo.OccurrenceCount = recurrence.OccurrenceCount;
                        appNew.RecurrenceInfo.Periodicity = recurrence.Periodicity;
                        appNew.RecurrenceInfo.Range = (RecurrenceRange)recurrence.Range;

                        appNew.RecurrenceInfo.Type = (RecurrenceType)recurrence.Type;
                        appNew.RecurrenceInfo.WeekDays = (WeekDays)recurrence.WeekDays;
                        appNew.RecurrenceInfo.WeekOfMonth = (WeekOfMonth)recurrence.WeekOfMonth;
                    }

                    schedulerStorage1.Appointments.Add(appNew);
                    IsOpen = false;

                }


                UndoManager.Commit();
                e.Allow = false;
                e.Handled = true;
                //return;
                //controller = new MyAppointmentFormController(this.Scheduler, e.SourceAppointment);
                //controller.RemoveRecurrence();
                //schedulerControl1.OptionsBehavior.RecurrentAppointmentEditAction = RecurrentAppointmentAction.Series;
                //controller.Start = e.EditedAppointment.Start;
                //controller.End = e.EditedAppointment.End;

                ////controller. = e.SourceAppointment.Duration;
                //controller.ApplyChanges();
            }
            else if (false)//e.EditedAppointment.AllDay)
            {
                UndoManager.BeginTransaction("app");
                RecurrenceInfo recurrence = e.SourceAppointment.RecurrenceInfo;
                Appointment aptEdit = e.EditedAppointment;
                var parttern = e.SourceAppointment.RecurrencePattern;
                if (parttern != null)
                    parttern.Delete();

                Appointment appNew;
                Appointment app = e.SourceAppointment;
                //appNew.RecurrencePattern = e.SourceAppointment.RecurrencePattern;
                appNew = new Appointment(AppointmentType.Pattern);
                appNew.Subject = aptEdit.Subject;
                //appNew.Location = aptEdit.Subject + aptEdit.Description;
                appNew.LabelId = aptEdit.LabelId;
                appNew.StatusId = 0;
                appNew.Start = aptEdit.Start;


                appNew.Duration = aptEdit.Duration;
                appNew.End = aptEdit.End;
                appNew.Description = aptEdit.Description;
                appNew.HasReminder = aptEdit.HasReminder;
                if (aptEdit.Description == LibraryType.TimeSliceGroup.ToString())
                    appNew.Description = "Time Slice Group";
                appNew.CustomFields["Only"] = aptEdit.Subject
                    + aptEdit.Description
                    + aptEdit.Start.ToString()
                    + aptEdit.End.ToString();


                    appNew.RecurrenceInfo.AllDay = true;
                    appNew.RecurrenceInfo.DayNumber = 1;
                    appNew.RecurrenceInfo.Start = DateTime.Now;
                    appNew.RecurrenceInfo.Duration = TimeSpan.FromDays(10);
                    //appNew.RecurrenceInfo.End = DateTime.Now.AddYears(1);
                    appNew.RecurrenceInfo.Month = 1;
                    appNew.RecurrenceInfo.OccurrenceCount = 10;
                    appNew.RecurrenceInfo.Periodicity = 1;
                    appNew.RecurrenceInfo.Range = RecurrenceRange.NoEndDate;

                    appNew.RecurrenceInfo.Type = RecurrenceType.Daily;
                    appNew.RecurrenceInfo.WeekDays = WeekDays.EveryDay;
                    appNew.RecurrenceInfo.WeekOfMonth = WeekOfMonth.None;

                schedulerStorage1.Appointments.Add(appNew);
                IsOpen = false;
                e.SourceAppointment.Delete();


                UndoManager.Commit();
                e.Allow = false;
                e.Handled = true;
            }


            DateTime srcStart = e.SourceAppointment.Start;

            if (srcStart != DateTime.MinValue)
            {
                DateTime newStart = e.EditedAppointment.Start;
                oldEnd = e.SourceAppointment.End;
                oldStart = e.SourceAppointment.Start;
                oldDuration = e.SourceAppointment.Duration;
                DateTime newEnd = e.EditedAppointment.End;

            }
            AppointmentInfo appointment = appointConverter.Convert(e.EditedAppointment);
            //if (appointment.Description == "Message" && appointment.Target != null)
            //    appointment.End = appointment.Start.AddSeconds(appointment.Target.Length);
            ControlService.RefreshPropertyGrid(appointment);
            GetNailImage(appointment);



        }

        void schedulerControl1_KeyDown(object sender, System.Windows.Forms.KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Delete)
            {

                DeleteAppointment();
            }
        }


        void schedulerControl1_MouseDown(object sender, System.Windows.Forms.MouseEventArgs e)
        {
            int count = schedulerControl1.SelectedAppointments.Count;

            if (count == 1)
            {
                oldEnd = schedulerControl1.SelectedAppointments[0].End;
                oldStart = schedulerControl1.SelectedAppointments[0].Start;
                oldDuration = schedulerControl1.SelectedAppointments[0].Duration;
                oldLabelId = schedulerControl1.SelectedAppointments[0].LabelId;
            }
            LocalMessageBus.Send(null, new MenuMessage(new MenuCommand[]{
                new MenuCommand{ Command= MenuCommands.Copy, Enabled = count > 0, Visibility = ItemVisibility.Always}
                , new MenuCommand{ Command= MenuCommands.Delete, Enabled = count > 0, Visibility = ItemVisibility.Always}
                }));

            dateLbl.Text = schedulerControl1.SelectedInterval.Start.ToShortDateString();
            if (schedulerControl1.SelectedAppointments.Count > 0)
            {
                AppointmentInfo appointment = appointConverter.Convert(schedulerControl1.SelectedAppointments[0]);
                ControlService.RefreshPropertyGrid(appointment);
                GetNailImage(appointment);
            }
        }

        private static void GetNailImage(AppointmentInfo appointment)
        {
            if (appointment.Target != null)
                ControlService.NailImageBox.Image = appointment.Target.Image;
            if (ControlService.NailImageBox.Image == null)
            {
                Rectangle rectangle = new Rectangle(0, 0, ControlService.SignCombo.Current.Width, ControlService.SignCombo.Current.Height);
                MessageInfo message = null;
                if (appointment.Target as MessageInfo != null)
                    message = appointment.Target as MessageInfo;
                else if (appointment.Target as PlaylistInfo != null)
                {
                    PlaylistInfo playlist = appointment.Target as PlaylistInfo;
                    message = LibraryGroup.Current.Messages.GetById(playlist.NailImageID);
                }
                else if (appointment.Target as TimeSliceGroupInfo != null)
                {
                    TimeSliceGroupInfo timeslicegroup = appointment.Target as TimeSliceGroupInfo;
                    message = LibraryGroup.Current.Messages.GetById(timeslicegroup.NailImageID);
                }
                //message.Zoom = 1;
                if (message.Image == null)
                {
                    rectangle = new Rectangle(0, 0, message.Size.Width, message.Size.Height);

                    ControlService.NailImageBox.Image = message.Image = NailImageGenerator.GenerateNailImage(message, rectangle);
                }
                else
                    ControlService.NailImageBox.Image = message.Image;
            }
        }


        void schedulerControl1_AppointmentResized(object sender, DevExpress.XtraScheduler.AppointmentResizeEventArgs e)
        {
            if (e.EditedAppointment.Description == LibraryType.Message.ToString())
            {
                AppointmentInfo info = Array.Find<AppointmentInfo>(this.Model.Items, p => { return p.Subject == e.EditedAppointment.Subject; });
                if (info.PlayMessageOnce)
                {
                    e.EditedAppointment.Start = e.SourceAppointment.Start;
                    e.EditedAppointment.End = e.SourceAppointment.End;
                    e.EditedAppointment.Duration = e.SourceAppointment.Duration;
                    return;
                }
            }
            //else
            //{
            if (e.SourceAppointment.RecurrenceInfo != null)
            {
                DeleteRecurrenceConfirmDialog dialog = new DeleteRecurrenceConfirmDialog();
                dialog.ShowDialog();
                int result = dialog.DeleteRecurrence;
                if (result == 0) //MsgBox.Confirm("Any exceptions associated with this recurring appointment will be lost. Proceed?") == DialogResult.No)
                {
                    e.Allow = false;
                    e.Handled = true;
                    return;
                }
                else
                {
                    //IsOpen = true;
                    UndoManager.BeginTransaction("app");
                    RecurrenceInfo recurrence = e.SourceAppointment.RecurrenceInfo;

                    Appointment aptEdit = e.EditedAppointment;
                    var parttern = e.SourceAppointment.RecurrencePattern;
                    if (parttern != null)
                        parttern.Delete();

                    Appointment appNew;
                    Appointment app = e.SourceAppointment;
                    //appNew.RecurrencePattern = e.SourceAppointment.RecurrencePattern;
                    if (recurrence != null && result == 1)
                        appNew = new Appointment(AppointmentType.Pattern);
                    else
                        appNew = new Appointment();
                    appNew.Subject = aptEdit.Subject;
                    //appNew.Location = aptEdit.Subject + aptEdit.Description;
                    appNew.LabelId = aptEdit.LabelId;
                    appNew.StatusId = 0;
                    appNew.Start = aptEdit.Start;


                    appNew.Duration = aptEdit.Duration;
                    appNew.End = aptEdit.End;
                    appNew.Description = aptEdit.Description;
                    appNew.HasReminder = aptEdit.HasReminder;
                    if (aptEdit.Description == LibraryType.TimeSliceGroup.ToString())
                        appNew.Description = "Time Slice Group";
                    appNew.CustomFields["Only"] = aptEdit.Subject
                        + aptEdit.Description
                        + aptEdit.Start.ToString()
                        + aptEdit.End.ToString();

                    if (recurrence != null && result == 1)
                    {

                        appNew.RecurrenceInfo.AllDay = recurrence.AllDay;
                        appNew.RecurrenceInfo.DayNumber = recurrence.DayNumber;
                        appNew.RecurrenceInfo.Start = aptEdit.Start;
                        appNew.RecurrenceInfo.Duration = aptEdit.Duration;
                        appNew.RecurrenceInfo.End = aptEdit.End;
                        appNew.RecurrenceInfo.Month = recurrence.Month;
                        appNew.RecurrenceInfo.OccurrenceCount = recurrence.OccurrenceCount;
                        appNew.RecurrenceInfo.Periodicity = recurrence.Periodicity;
                        appNew.RecurrenceInfo.Range = (RecurrenceRange)recurrence.Range;

                        appNew.RecurrenceInfo.Type = (RecurrenceType)recurrence.Type;
                        appNew.RecurrenceInfo.WeekDays = (WeekDays)recurrence.WeekDays;
                        appNew.RecurrenceInfo.WeekOfMonth = (WeekOfMonth)recurrence.WeekOfMonth;
                    }

                    schedulerStorage1.Appointments.Add(appNew);
                    IsOpen = false;
                }

                UndoManager.Commit();
                e.Allow = false;
                e.Handled = true;

            }

        }

        void schedulerControl1_MouseMove(object sender, System.Windows.Forms.MouseEventArgs e)
        {
            if (schedulerControl1.SelectedAppointments.Count > 0)
            {
                AppointmentInfo appointment = appointConverter.Convert(schedulerControl1.SelectedAppointments[0]);
                ControlService.RefreshPropertyGrid(appointment);
                GetNailImage(appointment);

            }
        }

        /// <summary>
        /// Get Drag Node
        /// </summary>
        /// <param name="data"></param>
        /// <returns></returns>
        private TreeListNode GetDragNode(IDataObject data)
        {
            return data.GetData(typeof(TreeListNode)) as TreeListNode;
        }

        public void DeleteAppointment()
        {
            if (schedulerControl1.SelectedAppointments.Count > 0)
            {
                int count = schedulerControl1.SelectedAppointments.Count;
                if (count == 1)
                {
                    if (MsgBox.Confirm("Are you sure you want to delete '" + schedulerControl1.SelectedAppointments[0].Subject + "'?") == DialogResult.No)
                        return;
                }
                else
                {
                    if (MsgBox.Confirm("Are you sure you want to delete these " + count.ToString() + " items?") == DialogResult.No)
                        return;
                }
                MyAppointmentFormController controller;

                for (int i = count - 1; i >= 0; i--)
                {
                    AppointmentInfo appointment = appointConverter.Convert(schedulerControl1.SelectedAppointments[i]);

                    ILockLibraryItem locker = appointment.Target as ILockLibraryItem;
                    if (locker != null)
                        locker.IsLock = false;
                    if (schedulerControl1.SelectedAppointments[i].RecurrenceInfo != null)
                    {
                        var parttern = schedulerControl1.SelectedAppointments[i].RecurrencePattern;
                        if (parttern != null)
                            parttern.Delete();
                        //controller = new MyAppointmentFormController(schedulerControl1, schedulerControl1.SelectedAppointments[i]);
                        //controller.RemoveRecurrence();
                    } //schedulerStorage1.Appointments.Remove(schedulerControl1.SelectedAppointments[i]);
                    else
                        schedulerControl1.SelectedAppointments[i].Delete();
                }
            }
        }
        private bool IsRepeatStartTime()
        {
            bool result = false;
            int count = schedulerStorage1.Appointments.Count;
            List<DateTime> list = new List<DateTime>();
            for (int i = 0; i < count - 1; i++)
            {
                list.Add(schedulerStorage1.Appointments[i].Start);
            }
            foreach (DateTime dt in list)
            {
                if (dt == schedulerStorage1.Appointments[count - 1].Start)
                {
                    result = true;
                }
            }
            return result;
        }
        SchedulerDragData GetDragData(MemoryLibraryItem item)
        {
            if (item == null)
                return null;
            ILockLibraryItem locker = item as ILockLibraryItem;
            if (locker != null)
                locker.IsLock = true;
            if (item.Type == LibraryType.TimeSliceGroup)
            {
                TimeSliceGroupInfo timeSlice = item as TimeSliceGroupInfo;
                if (timeSlice.Items == null || timeSlice.Items.Length <= 0)
                    _IsTimeSliceEmpty = true;
                else
                    _IsTimeSliceEmpty = false;

            }
            AppointmentBaseCollection appointments = new AppointmentBaseCollection();
            Appointment apt = schedulerStorage1.CreateAppointment(AppointmentType.Normal);
            apt.Subject = item.Name;
            //apt.Location = item.Name + item.Type.ToString();
            apt.LabelId = DataGate.FindColorIndex(item.Color);
            apt.StatusId = 0;
            apt.Description = item.Type.ToString();
            double length = Convert.ToDouble(item.Length) / 3600;

            if (item.Type == LibraryType.Message)
            {
                apt.Duration = TimeSpan.FromHours(length);
                apt.End = apt.Start.AddSeconds(item.Length);
            }
            else if (item.Type == LibraryType.Playlist)
                apt.Duration = TimeSpan.FromHours(ControlService.SignCombo.Current.Template.Scheduler.PlayListDisplayTime);
            else if (item.Type == LibraryType.TimeSliceGroup)
            {
                apt.Duration = TimeSpan.FromHours(ControlService.SignCombo.Current.Template.Scheduler.TimeSliceGroupDisplayTime);
                apt.Description = "Time Slice Group";
            }
            string ss = apt.Subject
                        + apt.Description
                        + apt.Start.ToString()
                        + apt.End.ToString();
            apt.CustomFields["CustomName"] = ss;
            appointments.Add(apt);
            _model.Add(new AppointmentInfo { Subject = apt.Subject, ExactTiming = false, PlayMessageOnce = false, Target = item, });
            isEdit = false;
            return new SchedulerDragData(appointments, 0);
        }
        private AppointmentBaseCollection GetNewData(MemoryLibraryItem item)
        {
            if (item == null)
                return null;
            ILockLibraryItem locker = item as ILockLibraryItem;
            if (locker != null)
                locker.IsLock = true;
            AppointmentBaseCollection appointments = new AppointmentBaseCollection();
            Appointment apt = schedulerStorage1.CreateAppointment(AppointmentType.Normal);
            apt.Subject = item.Name;
            //apt.Location = item.Name + item.Type.ToString();
            apt.LabelId = DataGate.FindColorIndex(item.Color);
            apt.StatusId = 0;
            apt.Start = DateTime.Parse(DateTime.Now.ToString());

            double length = Convert.ToDouble(item.Length) / 3600;

            if (item.Type == LibraryType.Message)
            {
                apt.Duration = TimeSpan.FromHours(length);
                apt.End = apt.Start.AddSeconds(item.Length);
            }
            else if (item.Type == LibraryType.Playlist)
                apt.Duration = TimeSpan.FromHours(ControlService.SignCombo.Current.Template.Scheduler.PlayListDisplayTime);
            else if (item.Type == LibraryType.TimeSliceGroup)
            {
                apt.Duration = TimeSpan.FromHours(ControlService.SignCombo.Current.Template.Scheduler.TimeSliceGroupDisplayTime);
                apt.Description = "Time Slice Group";
            }
            apt.Description = item.Type.ToString();

            appointments.Add(apt);
            return appointments;
        }

        private void schedulerControl1_DragLeave(object sender, EventArgs e)
        {
            Cursor = Cursors.Default;
        }

        Rectangle dragBoxFromMouseDown = Rectangle.Empty;

        private void schedulerControl1_EditAppointmentFormShowing(object sender, AppointmentFormEventArgs e)
        {
            Appointment apt = e.Appointment;
            if (schedulerStorage1.Appointments.IsNewAppointment(apt))
            {
                e.Handled = true;
                return;
            }
            bool openRecurrenceForm = apt.IsRecurring && schedulerStorage1.Appointments.IsNewAppointment(apt);


            bool isSupportRecurrence = schedulerControl1.SupportsRecurrence;


            MyAppointmentEditForm f = new MyAppointmentEditForm(this, apt, openRecurrenceForm);
            e.DialogResult = f.ShowModalDialog();
            e.Handled = true;

            if (apt.Type == AppointmentType.Pattern && schedulerControl1.SelectedAppointments.Contains(apt))
                schedulerControl1.SelectedAppointments.Remove(apt);

            schedulerControl1.Refresh();
        }

        private void schedulerControl1_PreparePopupMenu(object sender, PreparePopupMenuEventArgs e)
        {
            if (e.Menu.Items.Count == 6)
            {
                DXMenuItem ddd = new DXMenuItem("&Delete", delegate
                {
                    DeleteAppointment();
                });
                e.Menu.Items.RemoveAt(3);
                e.Menu.Items.Add(ddd);
            }
            if (e.Menu.Items.Count == 7)
            {
                e.Menu.Items[0].Visible = false;
                e.Menu.Items[1].Visible = false;
                e.Menu.Items[2].Visible = false;
                e.Menu.Items[3].Visible = false;
                e.Menu.Items[6].GetType();
            }
            if (e.Menu.Items.Count == 8)
            {
                e.Menu.Items[0].Visible = false;
                e.Menu.Items[1].Visible = false;
                e.Menu.Items[2].Visible = false;
                e.Menu.Items[3].Visible = false;
                e.Menu.Items[7].GetType();
            }
        }

        void schedulerControl1_CustomDrawDayViewAllDayArea(object sender, DevExpress.XtraScheduler.CustomDrawObjectEventArgs e)
        {
            if (schedulerStorage1.Appointments != null)
            {
                AllDayAreaCell cell = (AllDayAreaCell)e.ObjectInfo;
                Brush brush;
                brush = Brushes.LightGreen;
                e.Cache.FillRectangle(brush, e.Bounds);
                e.Graphics.DrawString(@"  Drag content here to be played continuously, with no end date.", cell.Appearance.Font, Brushes.Gray, e.Bounds, cell.Appearance.TextOptions.GetStringFormat());
                e.Handled = true;
            }
        }


        void schedulerStorage1_AppointmentsChanged(object sender, DevExpress.XtraScheduler.PersistentObjectsEventArgs e)
        {

            if (schedulerControl1.SelectedAppointments.Count > 0)
            {
                DateTime newStart = this.schedulerControl1.SelectedAppointments[0].Start;
                DateTime newEnd = this.schedulerControl1.SelectedAppointments[0].End;
                TimeSpan newDuration = this.schedulerControl1.SelectedAppointments[0].Duration;
                int newLabelId = this.schedulerControl1.SelectedAppointments[0].LabelId;
                if (newLabelId != oldLabelId)
                {
                    UndoService.AddPropertyChangedAction(schedulerControl1.SelectedAppointments[0], new PropertyItem[]
                    {
                        new PropertyItem("LabelId",newLabelId,oldLabelId)
                    });
                }
                if (oldStart != newStart)
                {
                    if (oldEnd != newEnd)
                    {
                        UndoService.AddPropertyChangedAction(schedulerControl1.SelectedAppointments[0], new PropertyItem[]
                    {
                        new PropertyItem("Start",newStart,oldStart)
                        , new PropertyItem ("End",newEnd,oldEnd)
                    });
                    }
                    else
                    {
                        UndoService.AddPropertyChangedAction(schedulerControl1.SelectedAppointments[0], new PropertyItem[]
                    {
                        new PropertyItem("Start",newStart,oldStart)
                        ,new PropertyItem("Duration",newDuration,oldDuration)
                    });
                    }
                }
                else if (oldEnd != newEnd)
                {

                    UndoService.AddPropertyChangedAction(schedulerControl1.SelectedAppointments[0], new PropertyItem[]
                    {
                        new PropertyItem("End",newEnd,oldEnd)
                    });
                }

            }
        }

        private void cbView_SelectedIndexChanged(object sender, EventArgs e)
        {
            ViewType = (SchedulerViewType)cbView.EditValue;
        }

        public SchedulerViewType ViewType
        {
            set
            {
                SchedulerViewType item = (SchedulerViewType)cbView.EditValue;
                if (item != value)
                {
                    cbView.EditValue = value;
                }

                SchedulerViewType old = schedulerControl1.ActiveViewType;
                schedulerControl1.ActiveViewType = value;
                UndoService.AddPropertyChangedAction(this, "ViewType", value, old);
            }
            get { return (SchedulerViewType)cbView.EditValue; }
        }

    }


    /// <summary>
    /// 
    /// </summary>
    public class MyLocalizer : SchedulerLocalizer
    {
        public override string GetLocalizedString(SchedulerStringId id)
        {
            switch (id)
            {
                case SchedulerStringId.Caption_PrevAppointment:
                    return "Previous Play Task";
                case SchedulerStringId.Caption_NextAppointment:
                    return "Next Play Task";
                default:
                    return base.GetLocalizedString(id);
            }
        }
    }
}
