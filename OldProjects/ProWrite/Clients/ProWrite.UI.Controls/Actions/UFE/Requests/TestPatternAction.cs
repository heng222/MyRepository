//---------------------------------------------------------------------
//
// File: TestPatternAction.cs
//
// Description:
// The uploadAction class of TestPattern
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
using ProWrite.Core;
using ProWrite.UFE;
using ProWrite.UI.Controls.Common;
using ProWrite.Entity.Dashboard;
using System.Windows.Forms;
using ProWrite.UFE.Entity;
using ProWrite.UI.Controls.Dashboard;

namespace ProWrite.UI.Controls.Actions.UFE.Requests
{
    /// <summary>
    /// The uploadAction class of TestPattern
    /// </summary>
    public class TestPatternAction : UFERequestActionBase
    {
        public override void Perform()
        {
            SignInfo sign = ControlService.SignCombo.Current;

            TestPatternEntity testPattern = new TestPatternEntity();
            testPattern.Type = 2;
            testPattern.Mode = 0;
            testPattern.Flag = 1;
            sign.Controller.SendAsync(
                Commands.TestPattern,
                p =>
                    {
                        //Cursor = Cursors.Default;
                        if (p.IsSuccessed)
                        {
                            MsgBox.Information(
                                Resources.Resource.GetString(Resources.Resource.Strings.SetTestPatternSuccessed));
                                //"Set testpattern successed.");
                            //Close();
                        }
                        else
                        {
                            MsgBox.Error(Resources.Resource.GetString(Resources.Resource.Strings.SetTestPatternFailed));
                                //"Sorry,Set testpattern failed,please try again.");
                        }
                    },
                testPattern);

            //using (TestPattern dlg = new TestPattern())
            //    dlg.ShowModalDialog();
        }
    }
}
