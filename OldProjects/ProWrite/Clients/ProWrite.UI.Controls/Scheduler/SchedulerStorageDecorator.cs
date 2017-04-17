using System;
//---------------------------------------------------------------------
//
// File: SchedulerStorageDecorator.cs
//      
// Description:
//      Scheduler Storage Decorator class
//
// Author: Kevin 2008-8-14
//
// Modify History:
// Copyright (C) 2008 by Trans-Lux All rights reserved.
// 
//---------------------------------------------------------------------
using System.Collections.Generic;
using System.Text;
using DevExpress.XtraScheduler;
using System.ComponentModel;
using ProWrite.Entity.Library;
using ProWrite.Core;
using ProWrite.UI.Controls.Common;
using ProWrite.UI.Controls.Library;
using System.Drawing;
using DevExpress.XtraBars;
using ProWrite.UI.Controls.Common.Messages;
using System.Reflection;

namespace ProWrite.UI.Controls.Scheduler
{
    /// <summary>
    /// Scheduler Storage Decorator class
    /// </summary>
    public class SchedulerStorageDecorator : SchedulerStorage
    {
        private static readonly FieldInfo _customFields;
        internal ScheduleControl _innerCtrl;

        static SchedulerStorageDecorator()
        {
            _customFields = typeof(PersistentObject).GetField("customFields", BindingFlags.Public | BindingFlags.NonPublic | BindingFlags.Instance | BindingFlags.GetField | BindingFlags.SetField);
        }

        public SchedulerStorageDecorator()
        {

        }

        public SchedulerStorageDecorator(IContainer container)
            : base(container)
        {
        }

        /// <summary>
        /// Insert appointment to schedulestorage
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        protected override void OnAppointmentInserted(object sender, PersistentObjectEventArgs e)
        {
            var appointment = e.Object as Appointment;
            try
            {
                base.OnAppointmentInserted(sender, e);
            }
            catch { }
            _innerCtrl.ChangedService.MarkChanged();
            ControlService.EnableCopyMenu(true);


            if (appointment.CustomFields == null)
            {
                try
                {
                    _customFields.SetValue(appointment, new CustomFieldCollection());
                }
                catch (Exception ex)
                {
                    DataGate.Log.Error("SchedulerStorageDecorator Exception:" + ex.Message);
                }
            }
            if (!_innerCtrl.IsOpen)
                UndoService.AddAppointmentAddedAction(this, appointment);
        }

        /// <summary>
        /// Will happen when appointment deleted
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        protected override void OnAppointmentDeleted(object sender, PersistentObjectEventArgs e)
        {
            try
            {
                base.OnAppointmentDeleted(sender, e);
            }
            catch { }
            _innerCtrl.ChangedService.MarkChanged();
            ControlService.EnableCopyMenu(false);
            Appointment appoint = e.Object as Appointment;
            SetLock(appoint);

            UndoService.AddAppointmentRemovedAction(this, appoint);
        }

        /// <summary>
        /// Set upload lock
        /// </summary>
        /// <param name="appoint"></param>
        private void SetLock(Appointment appoint)
        {
            LibraryType type = (LibraryType)Enum.Parse(typeof(LibraryType), appoint.Description.Replace(" ", ""));
            if (type == LibraryType.Message)
                LibraryGroup.Current.Messages.GetByName(appoint.Subject).IsLock = false;
            if (type == LibraryType.TimeSliceGroup)
                LibraryGroup.Current.TimeSliceGroups.GetByName(appoint.Subject).IsLock = false;
            if (type == LibraryType.Playlist)
                LibraryGroup.Current.Playlists.GetByName(appoint.Subject).IsLock = false;
        }

        /// <summary>
        /// When Appointment changed will happen
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        protected override void OnAppointmentChanged(object sender, PersistentObjectEventArgs e)
        {

            _innerCtrl.ChangedService.MarkChanged();
            try
            {
                base.OnAppointmentChanged(sender, e);
            }
            catch { }
            ControlService.NailImageBox.Image = null;

            AppointmentInfo appointment = _innerCtrl.appointConverter.Convert(e.Object as Appointment);
            ControlService.RefreshPropertyGrid(appointment);
            if (appointment.Target != null)
            {
                Color color = DataGate.FindColorByIndex(appointment.LabelId);
                //LibraryGroup.Current.SetColor(
                ControlService.LibraryTree.Controller.SetColor(appointment.Target, color);//.Refresh();
                ControlService.EnableCopyMenu(true);

                foreach (Appointment app in Appointments.Items)
                {
                    if (app.Subject == appointment.Subject && app.Description.Replace(" ", "") == appointment.Description)
                        app.LabelId = appointment.LabelId;
                }
            }
        }
    }
}
