//---------------------------------------------------------------------
//
// File: NavigateDecorator.cs
//      
// Description:
//      Navigate Decorator class
//
// Author: Kevin 2008-8-7
//
// Modify History:
// Copyright (C) 2008 by Trans-Lux All rights reserved.
// 
//---------------------------------------------------------------------
using System;
using System.Collections.Generic;
using System.Text;
using DevExpress.XtraScheduler.Services;
using DevExpress.XtraScheduler;

namespace ProWrite.UI.Controls.Scheduler
{
    /// <summary>
    /// Navigate Decorator class
    /// </summary>
    public class NavigateDecorator : IDateTimeNavigationService
    {
        private IDateTimeNavigationService _innerNavigate;
        private SchedulerControl _control;
        public NavigateDecorator(SchedulerControl control, IDateTimeNavigationService navigate)
        {
            _innerNavigate = navigate;
            _control = control;
        }

        #region IDateTimeNavigationService Members
        /// <summary>
        /// go to date
        /// </summary>
        /// <param name="date"></param>
        /// <param name="viewType"></param>
        public void GoToDate(DateTime date, SchedulerViewType viewType)
        {
            DateTime old = _control.SelectedInterval.Start;
            SchedulerViewType oldViewType = _control.ActiveViewType;
            _innerNavigate.GoToDate(date, viewType);
            UndoService.AddGotoDateAction(_innerNavigate, _control.SelectedInterval.Start, old, viewType, oldViewType);
        }

        /// <summary>
        /// go to date
        /// </summary>
        /// <param name="date"></param>
        public void GoToDate(DateTime date)
        {
            GoToDate(date, _control.ActiveViewType);
        }

        /// <summary>
        /// go to today
        /// </summary>
        public void GoToToday()
        {
            _innerNavigate.GoToDate(DateTime.Now, _control.ActiveViewType);
        }

        /// <summary>
        /// navigate backward
        /// </summary>
        public void NavigateBackward()
        {
            _innerNavigate.NavigateBackward();
            UndoService.AddNavigateBackwardAction(_innerNavigate);
        }

        /// <summary>
        /// navigate forward
        /// </summary>
        public void NavigateForward()
        {
            _innerNavigate.NavigateForward();
            UndoService.AddNavigateForwardAction(_innerNavigate);
        }

        #endregion
    }
}
