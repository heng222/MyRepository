//---------------------------------------------------------------------
//
// File: AppointmentAddedAction.cs
//
// Description:
//      Appointment added uploadAction class
//
// Author: Kevin 2008-8-14
// 
// Modify History:
//
// Copyright (C) 2008 by Trans-Lux All rights reserved.
// 
//---------------------------------------------------------------------
using System;
using System.Collections.Generic;
using System.Text;
using ProWrite.Core;
using DevExpress.XtraScheduler;
using ProWrite.UI.Controls.Scheduler;
using System.Windows.Forms;
using ProWrite.Entity.Library;

namespace ProWrite.UI.Controls.UndoRedo.Action
{
    /// <summary>
    /// Appointment added uploadAction class
    /// </summary>
    public class AppointmentAddedAction : UndoAction
    {
        private SchedulerStorage _storage;
        private Appointment _appointment;
        private RecurrenceInfo _recurrenceInfo;
        private BindingSource myBindingSource = new BindingSource();
        public AppointmentAddedAction(SchedulerStorage storage, Appointment appointment)
        {
            _storage = storage;
            _appointment = appointment;
            if (appointment.RecurrenceInfo != null)
            {
                _recurrenceInfo = appointment.RecurrenceInfo;
                _recurrenceInfo.AllDay = _appointment.RecurrenceInfo.AllDay;
                _recurrenceInfo.DayNumber = _appointment.RecurrenceInfo.DayNumber;
                _recurrenceInfo.Start = _appointment.RecurrenceInfo.Start;
                _recurrenceInfo.Duration = _appointment.RecurrenceInfo.Duration;
                _recurrenceInfo.End = _appointment.RecurrenceInfo.End;
                _recurrenceInfo.Month = _appointment.RecurrenceInfo.Month;
                _recurrenceInfo.OccurrenceCount = _appointment.RecurrenceInfo.OccurrenceCount;
                _recurrenceInfo.Periodicity = _appointment.RecurrenceInfo.Periodicity;
                _recurrenceInfo.Range = (RecurrenceRange)_appointment.RecurrenceInfo.Range;

                _recurrenceInfo.Type = (RecurrenceType)_appointment.RecurrenceInfo.Type;
                _recurrenceInfo.WeekDays = (WeekDays)_appointment.RecurrenceInfo.WeekDays;
                _recurrenceInfo.WeekOfMonth = (WeekOfMonth)_appointment.RecurrenceInfo.WeekOfMonth;
            }
            Name = "Add appointment-" + appointment.Subject;
        }

        public override void Undo()
        {
            
            for (int i = 0; i < _storage.Appointments.Count; i++)
            {
                if (_storage.Appointments[i].Subject == _appointment.Subject)
                    _appointment = _storage.Appointments[i];
            }
            _storage.Appointments.Remove(_appointment);
        }

        public override void Redo()
        {
            Appointment appNew;
            if (_recurrenceInfo != null)
                appNew = new Appointment(AppointmentType.Pattern);
            else
                appNew = new Appointment();
            appNew.Subject = _appointment.Subject;
            appNew.LabelId = _appointment.LabelId;
            appNew.StatusId = 0;
            appNew.Start = _appointment.Start;


            appNew.Duration = _appointment.Duration;
            appNew.End = _appointment.End;
            appNew.Description = _appointment.Description;
            appNew.HasReminder = _appointment.HasReminder;

            if (_recurrenceInfo != null)
            {
                appNew.RecurrenceInfo.AllDay = _recurrenceInfo.AllDay;
                appNew.RecurrenceInfo.DayNumber = _recurrenceInfo.DayNumber;
                appNew.RecurrenceInfo.Start = _recurrenceInfo.Start;
                appNew.RecurrenceInfo.Duration = _recurrenceInfo.Duration;
                appNew.RecurrenceInfo.End = _recurrenceInfo.End;
                appNew.RecurrenceInfo.Month = _recurrenceInfo.Month;
                appNew.RecurrenceInfo.OccurrenceCount = _recurrenceInfo.OccurrenceCount;
                appNew.RecurrenceInfo.Periodicity = _recurrenceInfo.Periodicity;
                appNew.RecurrenceInfo.Range = (RecurrenceRange)_recurrenceInfo.Range;

                appNew.RecurrenceInfo.Type = (RecurrenceType)_recurrenceInfo.Type;
                appNew.RecurrenceInfo.WeekDays = (WeekDays)_recurrenceInfo.WeekDays;
                appNew.RecurrenceInfo.WeekOfMonth = (WeekOfMonth)_recurrenceInfo.WeekOfMonth;
            }
            _storage.Appointments.Add(appNew);
            //appNew.Dispose();

        }
    }
}
