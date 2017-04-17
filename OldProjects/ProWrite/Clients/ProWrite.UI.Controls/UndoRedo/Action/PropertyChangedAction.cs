//---------------------------------------------------------------------
//
// File: PropertyChangedAction.cs
//
// Description:
//      Property changed uploadAction class
//
// Author: Kevin 2008-8-4
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
using System.Reflection;
using ProWrite.UI.Controls.Editor;
using log4net;
using DevExpress.XtraScheduler;
using ProWrite.UI.Controls.Scheduler;

namespace ProWrite.UI.Controls.UndoRedo.Action
{
    /// <summary>
    /// Property changed uploadAction class
    /// </summary>
    public class PropertyChangedAction : UndoAction
    {
        /// <summary>
        /// old value
        /// </summary>
        private PropertyItem[] _items;
        private object _target = null;
        internal static readonly ILog _log = LogManager.GetLogger("Undo Manager");


        public PropertyChangedAction(object target, string propetyName, object newValue, object oldValue)
            : this(target, new PropertyItem(target, propetyName, newValue, oldValue))
        {


        }

        public PropertyChangedAction(object target, params PropertyItem[] items)
        {
            _items = items;

            Name = string.Format("{0}.{1} propetry changed.", target.GetType().Name, _items[0].Name);
            _target = target;
        }

        /// <summary>
        /// undo
        /// </summary>
        public override void Undo()
        {
            try
            {
                foreach (PropertyItem item in _items)
                {
                    if (item.Target.GetType().Name == "Appointment")
                    {
                        Appointment app = item.Target as Appointment;
                        for (int i = 0; i < ScheduleControl.Current.Scheduler.Storage.Appointments.Count; i++)
                        {
                            if (ScheduleControl.Current.Scheduler.Storage.Appointments[i].Subject == app.Subject)
                                item.Target = ScheduleControl.Current.Scheduler.Storage.Appointments[i];
                        }

                    }
                    item.Prop.SetValue(item.Target, item.OldValue, null);
                }
                ControlService.RefreshPropertyGrid(_target);
                Invalidate();
            }
            catch (Exception ex)
            {
                _log.Error(ex.Message, ex);
            }
            finally
            {
            }
        }

        private static void Invalidate()
        {
            if (MessageControl.Current != null && MessageControl.Current.IsActive)
            {
                MessageControl.Current.ShapeControl.Invalidate();
                MessageControl.Current.Invalidate();
            }
        }

        /// <summary>
        /// redo
        /// </summary>
        public override void Redo()
        {
            try
            {
                foreach (PropertyItem item in _items)
                {
                    if (item.Target.GetType().Name == "Appointment")
                    {
                        Appointment app = item.Target as Appointment;
                        for (int i = 0; i < ScheduleControl.Current.Scheduler.Storage.Appointments.Count; i++)
                        {
                            if (ScheduleControl.Current.Scheduler.Storage.Appointments[i].Subject == app.Subject)
                                item.Target = ScheduleControl.Current.Scheduler.Storage.Appointments[i];
                        }
                    }
                    item.Prop.SetValue(item.Target, item.NewValue, null);
                }
                ControlService.RefreshPropertyGrid(_target);
                Invalidate();
            }
            catch (Exception ex)
            {
                _log.Error(ex.Message, ex);
            }
            finally
            {
            }
        }
    }

    public class PropertyItem
    {
        public object Target;
        public readonly string Name;
        public readonly object OldValue;
        public readonly object NewValue;

        public PropertyInfo Prop = null;

        public PropertyItem(string propetyName, object newValue, object oldValue)
        {
            Check.Require(propetyName, "propertyName", Check.NotNullOrEmpty);
            NewValue = newValue;
            OldValue = oldValue;
            Name = propetyName;
        }

        public PropertyItem(object target, string propetyName, object newValue, object oldValue)
            : this(propetyName, newValue, oldValue)
        {
            Target = target;
        }
    }
}
