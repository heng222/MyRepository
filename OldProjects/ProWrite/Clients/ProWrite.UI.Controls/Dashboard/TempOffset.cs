//---------------------------------------------------------------------
//
// File: TempOffset.cs
//
// Description:
// The control of set TempOffset
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
    /// Set tempoffset
    /// </summary>
    public partial class TempOffset : XtraForm
    {
        SignInfo sign;
        public TempOffset()
        {
            Cursor = Cursors.WaitCursor;
            InitializeComponent();
            Init();
        }

        private void Init()
        {
            ddlTempType.Properties.Items.Clear();
            ddlTempType.Properties.Items.AddRange(Enum.GetValues(typeof(TempSetType)));
            ddlTempType.SelectedIndex = 0;

            sign = ControlService.SignCombo.Current;

            TempSet tempSet = new TempSet();

            tempSet.Type = -1;
            tempSet.Value = "";
            tempSet.Mode = 1;

            sign.Controller.SendAsync(
                Commands.TempOffset,
                p =>
                {
                    Cursor = Cursors.Default;
                    if (p.IsSuccessed)
                    {
                        int type = p.Packet.Content.GetProperty<int>("Type");
                        string value = p.Packet.Content.GetProperty<string>("Value");

                        ddlTempType.SelectedIndex = type;
                        txtTemp.Text = value;
                    }

                },
                tempSet);

        }

        private void btnSave_Click(object sender, EventArgs e)
        {
            if (string.IsNullOrEmpty(txtTemp.Text))
            {
                MsgBox.Warning(Resources.Resource.GetString(Resources.Resource.Strings.TempoffsetNotEmpty));//"Sorry,the temperature value can't be empty.");
                return;
            }
            Cursor = Cursors.WaitCursor;
            sign = ControlService.SignCombo.Current;

            TempSet tempSet = new TempSet();
            if (ddlTempType.Text == TempSetType.Celsius.ToString())
                tempSet.Type = Convert.ToInt32(TempSetType.Celsius);
            else if (ddlTempType.Text == TempSetType.Fahrenheit.ToString())
                tempSet.Type = Convert.ToInt32(TempSetType.Fahrenheit);
            else if (ddlTempType.Text == TempSetType.Kelvin.ToString())
                tempSet.Type = Convert.ToInt32(TempSetType.Kelvin);
            //else if (ddlTempType.Text == TempSetType.NullTempType.ToString())
            //    tempSet.Type = Convert.ToInt32(TempSetType.NullTempType);
            else if (ddlTempType.Text == TempSetType.Rankine.ToString())
                tempSet.Type = Convert.ToInt32(TempSetType.Rankine);
            tempSet.Value = txtTemp.Text;
            tempSet.Mode = 0;

            sign.Controller.SendAsync(
                Commands.TempOffset,
                p =>
                {
                    Cursor = Cursors.Default;
                    if (p.IsSuccessed)
                    {
                        MsgBox.Information(Resources.Resource.GetString(Resources.Resource.Strings.SetTempoffsetSuccessed));//"Temp offset Successfully Changed.");
                        Close();
                    }
                    else
                    {
                        MsgBox.Error(Resources.Resource.GetString(Resources.Resource.Strings.SetTempoffsetFailed));//"Temp offset was not changed.Please try again.");
                    }
                },
                tempSet);

            //var task = sign.Controller.MAManager.SetTempOffset(txtTemp.Text + ddlTempType.Text);

            //if (!task.IsCompleted)
            //    task.Wait();

            //Cursor = Cursors.Default;

            //var isSuccessed = task.IsSuccessed;
            //task.Close();

            //if (!isSuccessed)
            //    MsgBox.Warning("Sorry,Set Temp offset failed,please try again");
            //else
            //{
            //    MsgBox.Warning("Set Temp offset successed");
            //    this.Close();
            //}
        }

        private void btnCancel_Click(object sender, EventArgs e)
        {
            Close();
        }
        
        private void txtTemp_KeyPress(object sender, KeyPressEventArgs e)
        {

        }

        private void txtTemp_TextChanged(object sender, EventArgs e)
        {

        }

    }
}
