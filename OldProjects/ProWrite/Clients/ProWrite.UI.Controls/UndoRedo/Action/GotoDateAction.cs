//---------------------------------------------------------------------
//
// File: GotoDateAction.cs
//
// Description:
//      Goto Date Action class in schedule module
//
// Author: Kevin 2008-8-7
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
using DevExpress.XtraScheduler.Services;
using DevExpress.XtraScheduler;

namespace ProWrite.UI.Controls.UndoRedo.Action
{
    /// <summary>
    /// Goto Date Action class in schedule module
    /// </summary>
    public class GotoDateAction:UndoAction
    {
        private IDateTimeNavigationService navigate;
        private DateTime newValue;
        private DateTime oldValue;
        private SchedulerViewType newViewType;
        private SchedulerViewType oldViewType;

        public GotoDateAction(
            IDateTimeNavigationService navigate
            , DateTime newValue
            , DateTime oldValue
            , SchedulerViewType newViewType
            , SchedulerViewType oldViewType)
        {
            Name = "Goto date";
            this.navigate = navigate;
            this.newValue = newValue;
            this.oldValue = oldValue;
            this.newViewType = newViewType;
            this.oldViewType = oldViewType;
        }

        public override void Undo()
        {
            navigate.GoToDate(oldValue,oldViewType);
        }

        public override void Redo()
        {
            navigate.GoToDate(newValue,newViewType);
        }
    }
}
