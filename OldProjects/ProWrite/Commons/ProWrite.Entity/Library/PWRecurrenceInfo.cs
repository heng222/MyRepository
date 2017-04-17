//---------------------------------------------------------------------
//
// File: PWRecurrenceInfo.cs
//
// Description:
//      Recurrence entity infomation class
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
using System.Xml.Serialization;
using ProWrite.Core;
using PropertyChangedEventArgs=ProWrite.Entity.PropertyChangedEventArgs;

namespace ProWrite.Entity.Library
{
	/// <summary>
	/// Recurrence entity infomation class
	/// </summary>
	[Serializable]
	[TypeConverter(typeof(ExpandableObjectConverter))]
	public class PWRecurrenceInfo:DisposableObject
    {
        #region Non Serialized Fields
        [NonSerialized]
        [XmlIgnore]
        private EventHandler<PropertyChangedEventArgs> _propChanged;
        #endregion

        #region Serialized Fields
        private PWRecurrenceRange _range;
        private int _occurrenceCount = 1;
        private DateTime _start;
        private DateTime _end;
        private TimeSpan _duration;
        private bool _allDay;
        private PWRecurrenceType _type;
        private int _periodicity;
        private PWWeekDays _weekDays;
        private int _dayNumber;
        private PWWeekOfMonth _weekOfMonth;
        private int _month;
        #endregion

        #region Serialized Fields Version 2
        #endregion

        
        
		/// <summary>
		/// get or set range
		/// </summary>
		public PWRecurrenceRange Range
		{
			get { return _range; }
			set
			{
				if (_range != value)
				{
					PWRecurrenceRange old = _range;
					_range = value;
					OnPropertyChanged(_.Range, value,old);
				}
			}
		}
		/// <summary>
		/// get or set occurrence count
		/// </summary>
		public int OccurrenceCount
		{
			get { return _occurrenceCount; }
			set
			{
				if (_occurrenceCount != value)
				{
					int old = _occurrenceCount;
					_occurrenceCount = value; 
					OnPropertyChanged(_.OccurrenceCount, value,old);
				}
			}
		}
		/// <summary>
		/// get or set start date
		/// </summary>
		public DateTime Start
		{
			get { return _start; }
			set
			{
				if (_start != value)
				{
					DateTime old = _start;
					_start = value; 
					OnPropertyChanged(_.Start, value, old);
				}
			}
		}
		/// <summary>
		/// get or set end date
		/// </summary>
		public DateTime End
		{
			get { return _end; }
			set
			{
				if (_end != value)
				{
					DateTime old = _end;
					_end = value; 
					OnPropertyChanged(_.End, value, old);
				}
			}
		}
		public TimeSpan Duration
		{
			get { return _duration; }
			set
			{
				if (_duration != value)
				{
					TimeSpan old = _duration;
					_duration = value;
					OnPropertyChanged(_.Duration, value,old);
				}
			}
		}
		/// <summary>
		/// get or set all day
		/// </summary>
		public bool AllDay
		{
			get { return _allDay; }
			set
			{
				if (_allDay != value)
				{
					bool old = _allDay;
					_allDay = value; 
					OnPropertyChanged(_.AllDay, value,old);
				}
			}
		}
		/// <summary>
		/// get or set recurrence type
		/// </summary>
		public PWRecurrenceType Type
		{
			get { return _type; }
			set
			{
				if (_type != value)
				{
					PWRecurrenceType old = _type;
					_type = value; 
					OnPropertyChanged(_.Type, value, old);
				}
			}
		}
		/// <summary>
		/// get or set periodicity
		/// </summary>
		public int Periodicity
		{
			get { return _periodicity; }
			set
			{
				if (_periodicity != value)
				{
					int old = _periodicity;
					_periodicity = value;
					OnPropertyChanged(_.Periodicity,value,old);
				}
			}
		}
		/// <summary>
		/// get or set week days
		/// </summary>
		public PWWeekDays WeekDays
		{
			get { return _weekDays; }
			set
			{
				if (_weekDays != value)
				{
					PWWeekDays old = _weekDays;
					_weekDays = value; 
					OnPropertyChanged(_.WeekDays, value,old);
				}
			}
		}
		/// <summary>
		/// get or set day number
		/// </summary>
		public int DayNumber
		{
			get { return _dayNumber; }
			set
			{
				if (_dayNumber != value)
				{
					int old = _dayNumber;
					_dayNumber = value; 
					OnPropertyChanged(_.DayNumber, value, old);
				}
			}
		}
		/// <summary>
		/// get or set week of month
		/// </summary>
		public PWWeekOfMonth WeekOfMonth
		{
			get { return _weekOfMonth; }
			set
			{
				if (_weekOfMonth != value)
				{
					PWWeekOfMonth old = _weekOfMonth;
					_weekOfMonth = value; 
					OnPropertyChanged(_.WeekOfMonth,value,old);
				}
			}
		}
		/// <summary>
		/// get or set month
		/// </summary>
		public int Month
		{
			get { return _month; }
			set
			{
				if (_month != value)
				{
					int old = _month;
					_month = value; 
					OnPropertyChanged(_.Month, value,old);
				}
			}
		}

		#region Constance class
		/// <summary>
		/// Constance class
		/// </summary>
		public class _
		{
			public const string
				Range = "Range"
				, OccurrenceCount = "OccurrenceCount"
				, Type = "Type"
				, Start = "Start"
				, End = "End"
				, Duration = "Duration"
				, AllDay = "AllDay"
				, Periodicity = "Periodicity"
				, WeekDays = "WeekDays"
				, DayNumber = "DayNumber"
				, WeekOfMonth = "WeekOfMonth"
				, Month = "Month"
				;
		}
		#endregion

		
		public event EventHandler<PropertyChangedEventArgs> PropertyChanged
		{
			add { _propChanged += value; }
			remove { _propChanged -= value; }
		}

		protected virtual void OnPropertyChanged(string propertyName,object newValue,object oldValue)
		{
			if (_propChanged != null)
				_propChanged(this, new PropertyChangedEventArgs(propertyName, newValue, oldValue));
		}

        protected override void Dispose(bool disposing)
        {
            base.Dispose(disposing);
            _propChanged = null;
        }
	}
}