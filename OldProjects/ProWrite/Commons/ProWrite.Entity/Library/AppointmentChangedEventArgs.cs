//---------------------------------------------------------------------
//
// File: AppointmentConverter.cs
//      
// Description:
//      Appointment proxy property changed event class
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

namespace ProWrite.Entity.Library
{
	/// <summary>
	/// Appointment proxy property changed event class
	/// </summary>
	public class AppointmentChangedEventArgs:EventArgs
	{
		/// <summary>
		/// Appointment proxy
		/// </summary>
		public readonly AppointmentInfo Appointment;
		/// <summary>
		/// RecurrenceInfo proxy
		/// </summary>
		public readonly PWRecurrenceInfo Recurrence;
		/// <summary>
		/// Property name
		/// </summary>
		public readonly string ProperyName;

		public AppointmentChangedEventArgs(AppointmentInfo appointment, PWRecurrenceInfo rec, string propertyName)
		{
			Appointment = appointment;
			Recurrence = rec;
			ProperyName = propertyName;
		}

		/// <summary>
		/// Is Appointment proxy property changed
		/// </summary>
		public bool IsAppointment
		{
			get { return Appointment != null; }
		}
	}
}