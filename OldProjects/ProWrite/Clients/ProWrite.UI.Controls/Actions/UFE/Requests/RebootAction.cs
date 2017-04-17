//---------------------------------------------------------------------
//
// File: RebootAction.cs
//
// Description:
// The uploadAction class of Reboot
//
// Author: Terry
//
// Copyright (C) 2008 by ISoftstone Corporation.  All rights reserved.
// 
// Modify history:   
//---------------------------------------------------------------------
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ProWrite.UFE;
using ProWrite.UI.Controls.Common;
using ProWrite.Entity.Dashboard;
using System.Windows.Forms;
using ProWrite.Core;

namespace ProWrite.UI.Controls.Actions.UFE.Requests
{
    /// <summary>
    /// The uploadAction class of Reboot
    /// </summary>
    public class RebootAction : UFERequestActionBase
    {
        public override Commands Id
        {
            get { return Commands.RebootCXC; }
        }

        public RebootAction()
        {
        }

        public override void Perform()
        {
            if (ControlService.SignCombo.Current == null)
            {
                MsgBox.Warning(Resources.Resource.GetString(Resources.Resource.Strings.AddNewSignFirst));
                return;
            }

            SignInfo sign = ControlService.SignCombo.Current;
            if (MsgBox.Confirm(Resources.Resource.GetFormatString(Resources.Resource.Strings.RebootCXC, sign.Name)) != DialogResult.Yes)
                return;

            Cursor.Current = Cursors.WaitCursor;
            //Send reboot command to UFE
            sign.Controller.SendAsync(Id, p =>
            {
                Cursor.Current = Cursors.Default;
                if (!p.IsSuccessed)
                {
                    if (p.Packet.HasError)
                        log.Error(p.Packet.ActionError.Message);
                    if (p.Exception != null)
                        log.Error(p.Exception.Message, p.Exception);

                    MsgBox.Error(Resources.Resource.GetString(Resources.Resource.Strings.RebootCXC));
                }
            });
        }
    }
}
