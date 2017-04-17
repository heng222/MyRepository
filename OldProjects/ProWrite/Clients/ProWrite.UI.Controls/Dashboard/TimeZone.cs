//---------------------------------------------------------------------
//
// File: TimeZone.cs
//
// Description:
// The control of set TimeZone
//
// Author: Terry
//
// Copyright (C) 2008 by ISoftstone Corporation.  All rights reserved.
// 
// Modify history:   
//---------------------------------------------------------------------
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using DevExpress.XtraEditors;
using DevExpress.XtraScheduler;
using ProWrite.Entity.Dashboard;
using ProWrite.UFE.Entity;
using ProWrite.UI.Controls.Common;
using ProWrite.Core;

namespace ProWrite.UI.Controls.Dashboard
{
    /// <summary>
    /// Set timezone
    /// </summary>
    public partial class TimeZone : XtraForm
    {
        SignInfo sign;

        public TimeZone()
        {
            Cursor = Cursors.WaitCursor;
            InitializeComponent();
            Init();
        }

        private void Init()
        {
            sign = ControlService.SignCombo.Current;
            TimeZoneSet timeZone = new TimeZoneSet();
            timeZone.Mode = 1;
            timeZone.Location = "";
            //Send get timezone state command form UFE
            sign.Controller.SendAsync(
                Commands.TimeZone,
                p =>
                {
                    Cursor = Cursors.Default;
                    if (p.IsSuccessed)
                    {
                        ddlTimeZoneType.Text =  p.Packet.Content.GetProperty<string>("Location");
                    }
                    
                },
                timeZone);
        }

        private void btnOk_Click(object sender, EventArgs e)
        {
            Cursor = Cursors.WaitCursor;
            sign = ControlService.SignCombo.Current;
            TimeZoneSet timeZone = new TimeZoneSet();
            timeZone.Mode = 0;
            timeZone.Location = ddlTimeZoneType.Text.ToString();

            //Send set timezone command
            sign.Controller.SendAsync(
                Commands.TimeZone,
                p =>
                {
                    Cursor = Cursors.Default;
                    if (p.IsSuccessed)
                    {
                        MsgBox.Information(Resources.Resource.GetString(Resources.Resource.Strings.SetTimeZoneSuccessed));//"Time Zone Successfully Changed.");
                        Close();
                    }
                    else
                    {
                        MsgBox.Error(Resources.Resource.GetString(Resources.Resource.Strings.SetTimeZoneFailed));//"Time Zone was not changed.Please try again.");
                    }
                },
                timeZone);
        }
        
    }
}
