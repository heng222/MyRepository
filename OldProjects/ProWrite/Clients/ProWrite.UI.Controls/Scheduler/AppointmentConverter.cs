//---------------------------------------------------------------------
//
// File: AppointmentConverter.cs
//      
// Description:
//      Appointment converter class
//
// Author: Kevin 2008-7-23
//
// Modify History:
// Copyright (C) 2008 by Trans-Lux All rights reserved.
// 
//---------------------------------------------------------------------
using System;
using System.Collections.Generic;
using System.Text;
using DevExpress.XtraScheduler;

using ProWrite.Entity;
using ProWrite.Entity.Library;
using System.Reflection;
using log4net;
using ProWrite.Core;

namespace ProWrite.UI.Controls.Scheduler
{
    /// <summary>
    /// Appointment converter class
    /// </summary>
    public class AppointmentConverter
    {
        
        private Appointment _appointment;
        private static readonly ILog _log = LogManager.GetLogger("Appoint converter");

        /// <summary>
        /// Constance class _
        /// </summary>
        public class _
        {
            public const string LibraryName = "LibraryName";
            public const string LibraryType = "LibraryType";
        }

        private static MethodInfo SetCurrenceInfoMethod = null;
        static AppointmentConverter()
        {
            SetCurrenceInfoMethod = typeof(Appointment).GetMethod("SetRecurrenceInfo", BindingFlags.Instance | BindingFlags.NonPublic);
        }

        /// <summary>
        /// convert Appointment to AppointmentInfo
        /// </summary>
        /// <param name="appointment"></param>
        /// <returns></returns>
        public AppointmentInfo Convert(Appointment appointment)
        {
            AppointmentInfo _proxy;

            _appointment = appointment;

            if (appointment == null)
                return null;

            _proxy = new AppointmentInfo();
            _proxy.Subject = appointment.Subject;
            _proxy.AllDay = appointment.AllDay;
            _proxy.AppointmentType = (PWAppointmentType)appointment.Type;
            _proxy.Description = appointment.Description;
            _proxy.HasExceptions = appointment.HasExceptions;
            _proxy.IsException = appointment.IsException;
            _proxy.Duration = appointment.Duration;
            _proxy.End = appointment.End;
            _proxy.HasReminder = appointment.HasReminder;
            _proxy.LabelId = appointment.LabelId;
            _proxy.Location = appointment.Location;
            //_proxy.ResourceId = appointment.ResourceId;
            _proxy.Start = appointment.Start;
            _proxy.StatusId = appointment.StatusId;
            if (appointment.CustomFields["Only"] == null)
            {
                appointment.CustomFields["Only"] = appointment.Subject
                        + appointment.Description
                        + appointment.Start.ToString()
                        + appointment.End.ToString();
            }
            _proxy.CustomFilds = appointment.Subject
                        + appointment.Description
                        + appointment.Start.ToString()
                        + appointment.End.ToString();
            if (appointment.RecurrenceInfo != null)
            {
                PWRecurrenceInfo recurrence = new PWRecurrenceInfo();
                recurrence.AllDay = appointment.RecurrenceInfo.AllDay;
                recurrence.DayNumber = appointment.RecurrenceInfo.DayNumber;
                recurrence.Duration = appointment.RecurrenceInfo.Duration;
                recurrence.End = appointment.RecurrenceInfo.End;
                recurrence.Month = appointment.RecurrenceInfo.Month;
                recurrence.OccurrenceCount = appointment.RecurrenceInfo.OccurrenceCount;
                recurrence.Periodicity = appointment.RecurrenceInfo.Periodicity;
                recurrence.Range =(PWRecurrenceRange) appointment.RecurrenceInfo.Range;
                recurrence.Start = appointment.RecurrenceInfo.Start;
                recurrence.Type = (PWRecurrenceType)appointment.RecurrenceInfo.Type;
                recurrence.WeekDays = (PWWeekDays)appointment.RecurrenceInfo.WeekDays;
                recurrence.WeekOfMonth = (PWWeekOfMonth)appointment.RecurrenceInfo.WeekOfMonth;

                _proxy.RecurrenceInfo = recurrence;
            }


            _proxy.Target = GetLibrary(appointment);

            _proxy.MemeberPropertyChanged += this.OnProxyPropertyChanged;
            if (_proxy.RecurrenceInfo != null)
                _proxy.RecurrenceInfo.PropertyChanged += this.OnProxyPropertyChanged;

            return _proxy;
        }

        /// <summary>
        /// convert AppointmentInfo to Appointment
        /// </summary>
        /// <param name="proxy"></param>
        /// <returns></returns>
        public static Appointment Convert(AppointmentInfo proxy)
        {
            if (proxy == null)
                return null;
            Appointment appointment;
            if (proxy.RecurrenceInfo != null)
                appointment = new Appointment(AppointmentType.Pattern);
            else
                appointment = new Appointment();
            appointment.Subject = proxy.Subject;
            appointment.Start = proxy.Start;
            appointment.AllDay = proxy.AllDay;
            appointment.Description = proxy.Description;
            appointment.Duration = proxy.Duration;

            appointment.End = proxy.End;
            appointment.HasReminder = proxy.HasReminder;
            //appointment.HasExceptions = proxy.HasExceptions;
            //appointment.IsException=proxy.IsException ;
            //appointment.IsRecurring = false;
            appointment.LabelId = proxy.LabelId;
            appointment.Location = proxy.Location;
            appointment.ResourceId = proxy.ResourceId;
            appointment.CustomFields["Only"] = proxy.CustomFilds;
            
            appointment.StatusId = proxy.StatusId;
            if (proxy.RecurrenceInfo != null)
            {
                RecurrenceInfo recurrence = appointment.RecurrenceInfo;
                recurrence.AllDay = proxy.RecurrenceInfo.AllDay;
                recurrence.DayNumber = proxy.RecurrenceInfo.DayNumber;
                recurrence.Start = proxy.RecurrenceInfo.Start;
                recurrence.Duration = proxy.RecurrenceInfo.Duration;
                recurrence.End = proxy.RecurrenceInfo.End;
                recurrence.Month = proxy.RecurrenceInfo.Month;
                recurrence.OccurrenceCount = proxy.RecurrenceInfo.OccurrenceCount;
                recurrence.Periodicity = proxy.RecurrenceInfo.Periodicity;
                recurrence.Range = (RecurrenceRange)proxy.RecurrenceInfo.Range;
                
                recurrence.Type = (RecurrenceType)proxy.RecurrenceInfo.Type;
                recurrence.WeekDays = (WeekDays)proxy.RecurrenceInfo.WeekDays;
                recurrence.WeekOfMonth = (WeekOfMonth) proxy.RecurrenceInfo.WeekOfMonth;

                //AddRecurrenceInfo(appointment, recurrence);
            }

            return appointment;
        }

        /// <summary>
        /// Add recurrence info in appointment
        /// </summary>
        /// <param name="appointment"></param>
        /// <param name="recurrence"></param>
        private static void AddRecurrenceInfo(Appointment appointment, RecurrenceInfo recurrence)
        {
            
            try
            {
                SetCurrenceInfoMethod.Invoke(appointment, new object[] { recurrence });
            }
            catch (Exception ex)
            {
                _log.Error(ex.Message, ex);
            }
        }

        /// <summary>
        /// get library by appointment customer fields
        /// </summary>
        /// <param name="appointment"></param>
        /// <returns></returns>
        private static MemoryLibraryItem GetLibrary(Appointment appointment)
        {
            //if (appointment.CustomFields.Count == 0)
            //    return null;
            MemoryLibraryItem item = null;
            try
            {
                LibraryType type =EnumHelper.Parse<LibraryType>(appointment.Description.Replace(" ",""));
                LibraryGroup libraryGroup = LibraryGroup.Current;
                string name = appointment.Subject;
                if (string.IsNullOrEmpty(name))
                    return null;

                switch (type)
                {
                    case LibraryType.Message:
                        item = libraryGroup.Messages.GetByName(name);
                        break;
                    case LibraryType.Playlist:
                        item = libraryGroup.Playlists.GetByName(name);
                        break;
                    case LibraryType.TimeSliceGroup:
                        item = libraryGroup.TimeSliceGroups.GetByName(name);
                        break;
                }
            }
            catch (Exception ex)
            {
                _log.Error(ex.Message, ex);
            }
            return item;
        }

        /// <summary>
        /// proxy property changed event
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        void OnProxyPropertyChanged(object sender, PropertyChangedEventArgs e)
        {
            UndoService.AddPropertyChangedAction(sender, e.Name, e.NewValue, e.OldValue);
            AppointmentInfo _proxy = sender as AppointmentInfo;
            if (sender is AppointmentInfo)
            {
                switch (e.Name)
                {
                    case AppointmentInfo._.AllDay:
                        _appointment.AllDay = _proxy.AllDay;
                        break;
                    case AppointmentInfo._.Description:
                        _appointment.Subject = _proxy.Subject;
                        break;
                    case AppointmentInfo._.Duration:
                        _appointment.Duration = _proxy.Duration;
                        break;
                    case AppointmentInfo._.End:
                        _appointment.End = _proxy.End;
                        break;
                    case AppointmentInfo._.HasReminder:
                        _appointment.HasReminder = _proxy.HasReminder;
                        break;
                    case AppointmentInfo._.LabelId:
                        _appointment.LabelId = _proxy.LabelId;
                        break;
                    case AppointmentInfo._.Location:
                        _appointment.Location = _proxy.Location;
                        break;
                    case AppointmentInfo._.ResourceId:
                        _appointment.ResourceId = _proxy.ResourceId;
                        break;
                    case AppointmentInfo._.Start:
                        _appointment.Start = _proxy.Start;
                        break;
                    case AppointmentInfo._.StatusId:
                        _appointment.StatusId = _proxy.StatusId;
                        break;
                    case AppointmentInfo._.Subject:
                        _appointment.Subject = _proxy.Subject;
                        break;
                }
            }
            else
            {
                if (_appointment.RecurrenceInfo == null)
                    return;
                switch (e.Name)
                {
                    case PWRecurrenceInfo._.AllDay:
                        _appointment.RecurrenceInfo.AllDay = _proxy.RecurrenceInfo.AllDay;
                        break;
                    case PWRecurrenceInfo._.DayNumber:
                        _appointment.RecurrenceInfo.DayNumber = _proxy.RecurrenceInfo.DayNumber;
                        break;
                    case PWRecurrenceInfo._.Duration:
                        _appointment.RecurrenceInfo.Duration = _proxy.RecurrenceInfo.Duration;
                        break;
                    case PWRecurrenceInfo._.End:
                        _appointment.RecurrenceInfo.End = _proxy.RecurrenceInfo.End;
                        break;
                    case PWRecurrenceInfo._.Month:
                        _appointment.RecurrenceInfo.Month = _proxy.RecurrenceInfo.Month;
                        break;
                    case PWRecurrenceInfo._.OccurrenceCount:
                        _appointment.RecurrenceInfo.OccurrenceCount = _proxy.RecurrenceInfo.OccurrenceCount;
                        break;
                    case PWRecurrenceInfo._.Periodicity:
                        _appointment.RecurrenceInfo.Periodicity = _proxy.RecurrenceInfo.Periodicity;
                        break;
                    case PWRecurrenceInfo._.Range:
                        _appointment.RecurrenceInfo.Range = (RecurrenceRange)_proxy.RecurrenceInfo.Range;
                        break;
                    case PWRecurrenceInfo._.Start:
                        _appointment.RecurrenceInfo.Start = _proxy.RecurrenceInfo.Start;
                        break;
                    case PWRecurrenceInfo._.Type:
                        _appointment.RecurrenceInfo.Type = (RecurrenceType)_proxy.RecurrenceInfo.Type;
                        break;
                    case PWRecurrenceInfo._.WeekDays:
                        _appointment.RecurrenceInfo.WeekDays = (WeekDays)_proxy.RecurrenceInfo.WeekDays;
                        break;
                    case PWRecurrenceInfo._.WeekOfMonth:
                        _appointment.RecurrenceInfo.WeekOfMonth = (WeekOfMonth)_proxy.RecurrenceInfo.WeekOfMonth;
                        break;
                }
            }
        }
    }
}
