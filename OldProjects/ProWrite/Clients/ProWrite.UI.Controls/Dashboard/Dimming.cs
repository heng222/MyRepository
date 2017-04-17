//---------------------------------------------------------------------
//
// File: Dimming.cs
//
// Description:
// The control of set Dimming
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
using ProWrite.UFE.Entity;
using ProWrite.Entity.Dashboard;
using ProWrite.UI.Controls.Common;
using ProWrite.Core;

namespace ProWrite.UI.Controls.Dashboard
{
    /// <summary>
    /// Set dimming
    /// </summary>
    public partial class Dimming : XtraForm
    {
        SignInfo sign;
        public Dimming()
        {
            Cursor = Cursors.WaitCursor;
            InitializeComponent();
            Init();
        }

        private void Init()
        {
            ddlDimmingType.Properties.Items.Clear();
            ddlDimmingType.Properties.Items.AddRange(Enum.GetValues(typeof(DimmingType)));
            ddlDimmingType.SelectedIndex = 0;

            sign = ControlService.SignCombo.Current;
            DimmingSet dimming = new DimmingSet();

            dimming.StartTime = "";
            dimming.EndTime = "";

            dimming.Mode = 1;
            dimming.DimType = -1;
            dimming.Value = -1;
            //Send get dimming state command
            sign.Controller.SendAsync(
                Commands.Dimming,
                p =>
                {
                    Cursor = Cursors.Default;
                    if (p.IsSuccessed)
                    {
                        int dimtype = p.Packet.Content.GetProperty<int>("DimType");
                        int value = p.Packet.Content.GetProperty<int>("Value");
                        try
                        {
                            //ddlDimmingType.SelectedIndex = dimtype;
                            spinDimming.Value = value;
                        }
                        catch { }
                    }
                },
                dimming);
        }

        private void btnOk_Click(object sender, EventArgs e)
        {
            Cursor = Cursors.WaitCursor;
            sign = ControlService.SignCombo.Current;

            DimmingSet dimming = new DimmingSet();



            dimming.StartTime = timeStart.Time.GetDateTimeFormats()[113];
            dimming.EndTime = timeEnd.Time.GetDateTimeFormats()[113];

            dimming.Mode = 0;
            dimming.DimType = Convert.ToInt32(DimmingType.Percent);
            dimming.Value = Convert.ToInt32(spinDimming.Text);

            //Send set dimming command
            sign.Controller.SendAsync(
                Commands.Dimming,
                p =>
                {
                    Cursor = Cursors.Default;
                    if (p.IsSuccessed)
                    {
                        MsgBox.Information(Resources.Resource.GetString(Resources.Resource.Strings.SetDimmingSuccessed));//"Dimming Successfully Changed.");
                        Close();
                    }
                    else
                    {
                        MsgBox.Error(Resources.Resource.GetString(Resources.Resource.Strings.SetDimmingFailed));//"Dimming was not changed.Please try again.");
                    }
                },
                dimming);
        }

        private void btnCancel_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void ddlDimmingType_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (ddlDimmingType.SelectedIndex == 0)
            {
                spinDimming.Properties.MaxValue = 100;
                lblPercent.Visible = true;
            }
            else
            {
                spinDimming.Properties.MaxValue = 100;
                lblPercent.Visible = true;
            }
        }

    }
}
