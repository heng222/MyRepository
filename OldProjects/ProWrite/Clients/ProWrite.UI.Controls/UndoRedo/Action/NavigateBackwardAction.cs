//---------------------------------------------------------------------
//
// File: NavigateBackwardAction.cs
//
// Description:
//      Navigate Backward Action class in schedule module
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

namespace ProWrite.UI.Controls.UndoRedo.Action
{
    /// <summary>
    /// Navigate Backward Action class in schedule module
    /// </summary>
    public class NavigateBackwardAction:UndoAction
    {
        private IDateTimeNavigationService navigate;
        public NavigateBackwardAction(IDateTimeNavigationService navigate)
        {
            Name = "Backward";
            this.navigate = navigate;
        }

        public override void Undo()
        {
            navigate.NavigateForward();
        }

        public override void Redo()
        {
            navigate.NavigateBackward();
        }
    }
}
