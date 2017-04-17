//---------------------------------------------------------------------
//
// File: BlankSignAction.cs
//
// Description:
// The uploadAction class of BlankSign
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
    /// <summary>
    /// The uploadAction class of BlankSign
    /// </summary>
    public class BlankSignAction : UFERequestActionBase
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
            blankSign.Flag = 1;
            Cursor.Current = Cursors.WaitCursor;
            //Send BlankSign Command for Start stop
            DataGate.Log.Info("Start Stop.Content:blankSign.Mode=0,blankSign.Flag=0");
            sign.Controller.SendAsync(
                Id,
                p =>
                {
                    Cursor.Current = Cursors.Default;
                    if (!p.IsSuccessed)
                    {
                        DataGate.Log.Error("Stop failed.");
                        if (p.Packet.HasError)
                            log.Error(p.Packet.ActionError.Message);
                        if (p.Exception != null)
                            log.Error(p.Exception.Message, p.Exception);

                        //MsgBox.Error(Resources.Resource.GetString(Resources.Resource.Strings.SetBlankSignFailed));//"Blank sign failed.");
                    }
                    else
                    {
                        if (!ServiceManager.Get<bool>())
                        {
                            ServiceManager.Remove<bool>();
                            ServiceManager.Add<bool>(true);
                        }
                        //ControlService.CurrentClip.SetPicImageNull();

                        DataGate.Log.Info("Stop successed.");
                        sign.IsBlankSign = false;
                        //MsgBox.Information(Resources.Resource.GetString(Resources.Resource.Strings.SetBlankSignSuccessed));//"Blank sign successed");
                        ActionHelper.OnBlankSign();//false);
                    }
                },
                blankSign);
        }
    }
}
