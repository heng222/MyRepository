//---------------------------------------------------------------------
//
// File: AppointmentInfo.cs
//
// Description:
// 
//
// Author: Kevin 2008-7-22
//
// Copyright (C) 2008 by Trans-Lux All rights reserved.
// 
//---------------------------------------------------------------------
using System;
using System.Collections.Generic;
using System.Text;
using System.ComponentModel;
using ProWrite.Core;
using System.Xml.Serialization;
using PropertyChangedEventArgs = ProWrite.Entity.PropertyChangedEventArgs;
using ProWrite.Core.Validation;
using System.Communication.Messaging;

namespace ProWrite.Entity.Library
{
    [Serializable]
    [TypeConverter(typeof(ExpandableObjectConverter))]
    public class AppointmentInfo : LibraryAdapter
    {
        #region Constance class
        public class _
        {
            public const string Subject = "Subject";
            public const string Location = "Location";
            public const string Description = "Description";

            public const string AllDay = "AllDay";
            public const string ExactTiming = "ExactTiming";
            public const string PlayMessageOnce = "PlayMessageOnce";
            public const string ResourceId = "ResourceId";
            public const string LabelId = "LabelId";
            public const string StatusId = "StatusId";

            public const string HasReminder = "HasReminder";
            public const string Start = "Start";
            public const string Duration = "Duration";
            public const string End = "End";
            public const string RecurrenceInfo = "RecurrenceInfo";
        }
        #endregion

        #region Non Serialized Fields
        [NonSerialized]
        [XmlIgnore]
        private EventHandler<PropertyChangedEventArgs> _propChanged;
        #endregion

        #region Serialized Fields
        private string _subject;
        private string _location;
        private string _description;
        private bool _allDay;
        private bool _exactTiming;
        private bool _playMessageOnce;
        private bool _hasReminder;
        private int _resourceId;
        private int _labelId;
        private int _statusId;
        private PWAppointmentType _type;
        private DateTime _start;
        private DateTime _end;
        private TimeSpan _duration;
        private PWRecurrenceInfo _recurrenceInfo;
        private string _customFields;
        #endregion

        #region Serialized Fields Version 2
        #endregion

        public AppointmentInfo()
        {
            MessageBus.Subject<LibraryRenameMessage>().Observers += new ObserverHandler<LibraryRenameMessage>(OnLibraryRename);
            MessageBus.Subject<LibraryLenghtChangedMessage>().Observers += new ObserverHandler<LibraryLenghtChangedMessage>(OnLibraryLengthChaged);
        }

        void OnLibraryLengthChaged(object sender, LibraryLenghtChangedMessage msg)
        {
            if (Subject == msg.Name
                && Description == msg.Type.ToString())
            {
                double length = Convert.ToDouble(msg.Length) / 3600;

                if (PlayMessageOnce&& Description == LibraryType.Message.ToString())
                {
                    Duration = TimeSpan.FromHours(length);
                    //apt.End = apt.Start.AddSeconds(item.Length);
                }
                //else if (Description == LibraryType.Playlist.ToString())
                //    apt.Duration = TimeSpan.FromHours(ControlService.SignCombo.Current.Template.Scheduler.PlayListDisplayTime);
                //else if (Description == LibraryType.TimeSliceGroup.ToString())
                //{
                //    apt.Duration = TimeSpan.FromHours(ControlService.SignCombo.Current.Template.Scheduler.TimeSliceGroupDisplayTime);
                //    apt.Description = "Time Slice Group";
                //}
            }
        }
        void OnLibraryRename(object sender, LibraryRenameMessage msg)
        {
            if (Subject == msg.OldName
                && Description == msg.Type.ToString())
            {
                Subject = msg.NewName;
            }

        }
        
        #region Events
        
        public event EventHandler<PropertyChangedEventArgs> MemeberPropertyChanged
        {
            add { _propChanged += value; }
            remove { _propChanged -= value; }
        }

        protected virtual void OnMemeberPropertyChanged(string propertyName, object newValue, object oldValue)
        {
            if (_propChanged != null)
                _propChanged(this, new PropertyChangedEventArgs(propertyName, newValue, oldValue));
        }
        #endregion

        [XmlIgnore]
        [Browsable(false)]
        public override MemoryLibraryItem Target
        {
            get
            {
                if (_target != null)
                    return _target;
                _target = LibraryGroup.Current.GetById(_targetId, LibraryType.Message) as MemoryLibraryItem;

                if (_target == null)
                    _target = LibraryGroup.Current.GetById(_targetId, LibraryType.Playlist) as MemoryLibraryItem;
                if (_target == null)
                    _target = LibraryGroup.Current.GetById(_targetId, LibraryType.TimeSliceGroup) as MemoryLibraryItem;

                return _target;
            }

            set
            {
                base.Target = value;
                _target = value;
            }
        }

        #region Properties
        /// <summary>
        /// get or set subject
        /// </summary>
        [RequiredValidator]
        [StringLengthValidator(1, 200)]
        [ReadOnly(true)]
        public string Subject
        {
            get { return Target.Name; }// _subject; }
            set
            {
                if (_subject != value)
                {
                    string old = _subject;
                    _subject = value;
                    OnMemeberPropertyChanged(_.Subject, old, value);
                }
            }
        }
        [Browsable(false)]
        public string CustomFilds
        {
            get { return _customFields; }
            set
            {
                if (_customFields != value)
                    _customFields = value;
            }
        }
        /// <summary>
        /// get or set location
        /// </summary>
        [Browsable(false)]
        public string Location
        {
            get { return _subject+_description; }
            set
            {
                if (_location != value)
                {
                    string old = _location;
                    _location = value;
                    OnMemeberPropertyChanged(_.Location, value, old);
                }
            }
        }
        /// <summary>
        /// get or set subject
        /// </summary>
        [DisplayName("Type")]
        [ReadOnly(true)]
        public string Description
        {
            get { return _description; }
            set
            {
                if (_description != value)
                {
                    string old = _description;
                    _description = value;
                    OnMemeberPropertyChanged(_.Description, value, old);
                }
            }
        }
        /// <summary>
        /// get or set allday
        /// </summary>
        [ReadOnly(true)]
        public bool AllDay
        {
            get { return _allDay; }
            set
            {
                if (_allDay != value)
                {
                    bool old = _allDay;
                    _allDay = value;
                    OnMemeberPropertyChanged(_.AllDay, value, old);
                }
            }
        }
        private bool _hasExceptions;
        /// <summary>
        /// get or set allday
        /// </summary>
        [ReadOnly(true)]
        public bool HasExceptions
        {
            get { return _hasExceptions; }
            set
            {
                if (_hasExceptions != value)
                {
                    _hasExceptions = value;
                    //OnMemeberPropertyChanged(_.AllDay, value, old);
                }
            }
        }

        private bool _isException;
        /// <summary>
        /// get or set allday
        /// </summary>
        [ReadOnly(true)]
        public bool IsException
        {
            get { return _isException; }
            set
            {
                if (_isException != value)
                {
                    _isException = value;
                    //OnMemeberPropertyChanged(_.AllDay, value, old);
                }
            }
        }

        /// <summary>
        /// get or set exact timing
        /// </summary>
        //[ReadOnly(true)]
        [Browsable(false)]
        public bool ExactTiming
        {
            get { return _exactTiming; }
            set
            {
                if (_exactTiming != value)
                {
                    bool old = _exactTiming;
                    _exactTiming = value;
                    OnMemeberPropertyChanged(_.ExactTiming, value, old);
                }
            }
        }

        /// <summary>
        /// get or set PlayMessageOnce
        /// </summary>
        //[ReadOnly(true)]
        [Browsable(false)]
        public bool PlayMessageOnce
        {
            get { return _playMessageOnce; }
            set
            {
                if (_playMessageOnce != value)
                {
                    bool old = _playMessageOnce;
                    _playMessageOnce = value;
                    OnMemeberPropertyChanged(_.PlayMessageOnce, value, old);
                }
            }
        }


        /// <summary>
        /// get or set has Reminder
        /// </summary>
        [Browsable(false)]
        public bool HasReminder
        {
            get { return _hasReminder; }
            set
            {
                if (_hasReminder != value)
                {
                    bool old = _hasReminder;
                    _hasReminder = value;
                    OnMemeberPropertyChanged(_.HasReminder, value, old);
                }
            }
        }
        /// <summary>
        /// get or set resource Id
        /// </summary>
        [Browsable(false)]
        public int ResourceId
        {
            get { return _resourceId; }
            set
            {
                if (_resourceId != value)
                {
                    int old = _resourceId;
                    _resourceId = value;
                    OnMemeberPropertyChanged(_.ResourceId, value, old);
                }
            }
        }
        /// <summary>
        /// get or set label id
        /// </summary>
        [Browsable(false)]
        public int LabelId
        {
            get { return _labelId; }
            set
            {
                if (_labelId != value)
                {
                    int old = _labelId;
                    _labelId = value;
                    OnMemeberPropertyChanged(_.LabelId, value, old);
                }
            }
        }
        /// <summary>
        /// get or set status id
        /// </summary>
        [Browsable(false)]
        public int StatusId
        {
            get { return _statusId; }
            set
            {
                if (_statusId != value)
                {
                    int old = _statusId;
                    _statusId = value;
                    OnMemeberPropertyChanged(_.StatusId, value, old);
                }
            }
        }
        /// <summary>
        /// get or set appointment type
        /// </summary>
        [Browsable(false)]
        public PWAppointmentType AppointmentType
        {
            get { return _type; }
            set
            {
                _type = value;
            }
        }
        /// <summary>
        /// get or set start dat
        /// </summary>
        [ReadOnly(true)]
        public DateTime Start
        {
            get { return _start; }
            set
            {
                if ( _start != value)
                {
                    DateTime old = _start;
                    _start = value;
                    //if (Description == "Message")
                    //    _start = old;
                    OnMemeberPropertyChanged(_.Start, value, old);
                }
            }
        }
        /// <summary>
        /// get or set end date
        /// </summary>
        [ReadOnly(true)]
        public DateTime End
        {
            get { return _end; }
            set
            {
                if (_end != value)
                {
                    DateTime old = _end;
                    _end = value;
                    //if (Description == "Message")
                    //    _end = old;
                    OnMemeberPropertyChanged(_.End, value, old);
                }
            }
        }
        /// <summary>
        /// get or set duration
        /// </summary>
        [ReadOnly(true)]
        public TimeSpan Duration
        {
            get { return _duration; }
            set
            {
                if (_duration != value)
                {
                    TimeSpan old = _duration;
                    _duration = value;
                    OnMemeberPropertyChanged(_.Duration, value, old);
                }
            }
        }
        [Browsable(false)]
        public PWRecurrenceInfo RecurrenceInfo
        {
            get { return _recurrenceInfo; }
            set { _recurrenceInfo = value; }
        }
        #endregion

        #region override methods

        /// <summary>
        /// Function: Init a new instance of this object
        /// Author  : Jerry Xu
        /// Date    : 2008-7-8 
        /// </summary>
        /// <returns>LibraryAdapter</returns>
        public override LibraryAdapter NewInstance()
        {
            return new AppointmentInfo();
        }

        /// <summary>
        /// Function: Get data from a object to current object
        /// Author  : Jerry Xu
        /// Date    : 2008-7-8 
        /// </summary>
        /// <param name="memory">LibraryAdapter</param>
        public override void FromTo(LibraryAdapter item)
        {
            //this.Caption = memory.Caption;
            base.FromTo(item);

            //TODO:
            AppointmentInfo adp = item as AppointmentInfo;
            _allDay = adp._allDay;
            _description = adp._description;
            _duration = adp._duration;
            _end = adp._end;
            _hasReminder = adp._hasReminder;
            _labelId = adp._labelId;
            _location = adp._location;
            _exactTiming = adp._exactTiming;
            _playMessageOnce = adp._playMessageOnce;
            if (adp._recurrenceInfo != null)
            {
                _recurrenceInfo = CloneManager.Clone<PWRecurrenceInfo>(adp._recurrenceInfo);
            }
            else
            {
                _recurrenceInfo = null;
            }

            _resourceId = adp._resourceId;
            _start = adp._start;
            _statusId = adp._statusId;
            _subject = adp._subject;
            _type = adp._type;
        }

        public override LibraryType Type
        {
            get
            {
                return LibraryType.Appointment;
            }
        }

        public override string ToString()
        {
            return _subject;
        }
        #endregion

        protected override void Dispose(bool disposing)
        {
            base.Dispose(disposing);
            _subject = null;
            _location = null;
            _description = null;
            if (_recurrenceInfo != null)
            {
                _recurrenceInfo.Dispose();
                _recurrenceInfo = null;
            }
            _propChanged = null;
            MessageBus.Subject<LibraryRenameMessage>().Observers -= OnLibraryRename;
        }
    }
}