//---------------------------------------------------------------------
//
// File: NavigateForwardAction.cs
//
// Description:
//      Navigate Forward Action class in schedule module
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
using DevExpress.XtraScheduler.Services;
using ProWrite.Core;

namespace ProWrite.UI.Controls.UndoRedo.Action
{
    /// <summary>
    /// Navigate Forward Action class in schedule module
    /// </summary>
    public class NavigateForwardAction:UndoAction
    {
        private IDateTimeNavigationService navigate;
        public NavigateForwardAction(IDateTimeNavigationService navigate)
        {
            Name = "Forward";
            this.navigate = navigate;
        }

        public override void Undo()
        {
            navigate.NavigateBackward();
        }

        public override void Redo()
        {
            navigate.NavigateForward();
        }
    }
}
