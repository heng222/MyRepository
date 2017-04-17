//---------------------------------------------------------------------
//
// File: DateTimeSet.cs
//
// Description:
// The control of DateTimeSet
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
using ProWrite.Entity.Dashboard;
using ProWrite.UI.Controls.Common;
using ProWrite.UFE.Entity;
using ProWrite.Core;

namespace ProWrite.UI.Controls.Dashboard
{
    /// <summary>
    /// Set date time
    /// </summary>
    public partial class DateTimeSet : XtraForm
    {
        SignInfo sign;
        public DateTimeSet()
        {
            Cursor = Cursors.WaitCursor;
            InitializeComponent();
            Init();
        }

        private void Init()
        {
            sign = ControlService.SignCombo.Current;
            DateAndTime datetime = new DateAndTime();
            datetime.Mode = 1;
            datetime.CurrentTime = "";

            //Get datetime state of UFE
            sign.Controller.SendAsync(
                Commands.SetDateTime,
                p =>
                {
                    Cursor = Cursors.Default;
                    if (p.IsSuccessed)
                    {
                        string str = p.Packet.Content.GetProperty<string>("CurrentTime");
                        try
                        {
                            string date = str.Substring(8, 4) + "-" + str.Substring(0, 2) + "-" + str.Substring(2, 2);
                            string time = str.Substring(4, 2) + ":" + str.Substring(6, 2) + ":" + str.Substring(str.Length - 2, 2);
                            string year = str.Substring(8, 4);
                            timeEdit1.Time = DateTime.Parse(str);
                            ddlDate.DateTime = DateTime.Parse(str).Date;
                        }
                        catch { }
                    }
                },
                datetime);
        }

        private void btnSave_Click(object sender, EventArgs e)
        {
            Cursor = Cursors.WaitCursor;
            sign = ControlService.SignCombo.Current;
            DateAndTime datetime = new DateAndTime();
            var date = ddlDate.DateTime.ToString("MMdd")
                + timeEdit1.Time.ToString("HHmm")
                + ddlDate.DateTime.Year.ToString() + "."
                + timeEdit1.Time.ToString("ss");
            datetime.Mode = 0;
            datetime.CurrentTime = date;
            string date1 = date.Substring(8, 4) + "-" + date.Substring(0, 2) + "-" + date.Substring(0, 2);
            string time = date.Substring(4, 4) + date.Substring(date.Length - 2, 2);
            string year = date.Substring(8, 4);

            //Send set datetime command
            sign.Controller.SendAsync(
                Commands.SetDateTime,
                p =>
                {
                    Cursor = Cursors.Default;
                    if (p.IsSuccessed)
                    {
                        MsgBox.Information(Resources.Resource.GetString(Resources.Resource.Strings.SetDateTimeSuccessed));//"Time & Date Successfully Changed.");
                        Close();
                    }
                    else
                    {
                        MsgBox.Error(Resources.Resource.GetString(Resources.Resource.Strings.SetDateTimeFailed));//"Time & Date were not changed.Please try again.");
                    }
                },
                datetime);
        }

        private void btnCancel_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void btnSameTime_Click(object sender, EventArgs e)
        {
            ddlDate.DateTime = DateTime.Now;
            timeEdit1.Time = DateTime.Now;
        }
    }
}
