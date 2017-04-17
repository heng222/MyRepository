//---------------------------------------------------------------------
//
// File: UnBlankSignAction.cs
//
// Description:
// The uploadAction class of UnBlankSign
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
using ProWrite.Entity.Dashboard;
using ProWrite.UI.Controls.Common;
using ProWrite.UFE;
using System.Windows.Forms;
using ProWrite.UFE.Entity;
using ProWrite.Core;

namespace ProWrite.UI.Controls.Actions.UFE.Requests
{
    public class UnBlankSignAction : UFERequestActionBase
    {
        public override Commands Id
        {
            get { return Commands.BlankSign; }
        }

        public override void Perform()
        {
            if (ControlService.SignCombo.Current == null)
            {
                MsgBox.Warning(Resources.Resource.GetString(Resources.Resource.Strings.AddNewSignFirst));
                return;
            }

            SignInfo sign = ControlService.SignCombo.Current;
            BlankSign blankSign = new BlankSign();
            blankSign.Mode = 0;
            blankSign.Flag = 0;
            Cursor.Current = Cursors.WaitCursor;
            DataGate.Log.Info("Start Play.Content:blankSign.Mode=0,blankSign.Flag=1");
            sign.Controller.SendAsync(
                Id,
                p =>
                {
                    Cursor.Current = Cursors.Default;
                    if (!p.IsSuccessed)
                    {
                        DataGate.Log.Error("Play failed.");
                        if (p.Packet.HasError)
                            log.Error(p.Packet.ActionError.Message);
                        if (p.Exception != null)
                            log.Error(p.Exception.Message, p.Exception);

                       // MsgBox.Error(Resources.Resource.GetString(Resources.Resource.Strings.SetUnBlankSignFailed));//"Unblank sign failed.");
                    }
                    else
                    {
                        DataGate.Log.Info("Play successed.");
                        sign.IsBlankSign = true;
                       // MsgBox.Information(Resources.Resource.GetString(Resources.Resource.Strings.SetUnBlankSignSuccessed));//"Unblank sign successed.");
                        ActionHelper.OnBlankSign();//true);
                    }
                },
                blankSign);

            //sign.Controller.SendAsync(Id, p =>
            //{
            //    Cursor.Current = Cursors.Default;
            //    if (!p.IsSuccessed)
            //    {
            //        if (p.Packet.HasError)
            //            log.Error(p.Packet.ActionError.Message);
            //        if (p.Exception != null)
            //            log.Error(p.Exception.Message, p.Exception);

            //        MsgBox.Error("Blank sign failed.");
            //    }
            //});
        }
    }
}
