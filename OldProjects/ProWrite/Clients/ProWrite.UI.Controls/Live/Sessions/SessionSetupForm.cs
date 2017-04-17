//---------------------------------------------------------------------
//
// File: SessionSetupForm.cs
//
// Description:
// SessionSetup Form  
//
// Author: Jerry
// Date  : 2009-7-16
//
// Modify history:
//      Jerry Xu 2009-8-3 Add method:InitResource()
//      
// Copyright (C) 2008 by Trans-Lux All rights reserved.
// 
//---------------------------------------------------------------------

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using DevExpress.XtraEditors;
using ProWrite.Resources;
using ProWrite.Core;
using ProWrite.Entity.Live;
using ProWrite.UI.Controls.Common;

namespace ProWrite.UI.Controls.Live.Sessions
{
    public partial class SessionSetupForm : DevExpress.XtraEditors.XtraForm
    {

        public SessionSetupForm()
        {
            InitializeComponent();
            if (!DesignMode)
                Init();
        }

        /// <summary>
        /// Init code
        /// </summary>
        private void Init()
        {
            InitResource();

            sessionSetupControl1.InitNew();
            sessionSetupControl1.Model.ChangedService.AcceptedChanged += new EventHandler(ChangedService_AcceptedChanged);
            sessionSetupControl1.Model.ChangedService.ModelChanged += new EventHandler(ChangedService_ModelChanged);
            sessionSetupControl1.OnSessionChange += new EventHandler(sessionSetupControl1_OnSessionChange);

            MessageBus.Subject<SessionNameChangeMessage>().Observers += new System.Communication.Messaging.ObserverHandler<SessionNameChangeMessage>(SessionSetupForm_Observers);
        }

        void SessionSetupForm_Observers(object sender, SessionNameChangeMessage msg)
        {
            if (sessionSetupControl1.Model != null && sessionSetupControl1.Model == SessionInfo.Current && !string.IsNullOrEmpty(msg.Name))
            {
                if(msg.IsChange)
                    this.Text = "* " + msg.Name;
                else
                    this.Text = msg.Name;
            }
        }

        /// <summary>
        /// Init resource
        /// </summary>
        private void InitResource()
        {
            this.Text = Resource.GetString(Resource.Strings.LiveSessionSesssionSetupFormTitleDefault);
        }

        private bool Save()
        {
            bool saveResult = true;

            if (sessionSetupControl1.Model != null && sessionSetupControl1.Model.ChangedService.HasChanged)
            {
                DialogResult result = DialogResult.Cancel;
                result = MsgBox.Confirm(Resource.GetString(Resource.Strings.DialogConfirmInfo), MessageBoxButtons.YesNo);
                switch (result)
                {
                    case DialogResult.Yes:
                        if (sessionSetupControl1.Save())
                        {
                            saveResult = true;
                        }
                        else
                        {
                            saveResult = false;
                        }
                        break;
                    case DialogResult.No:
                        saveResult = true;
                        break;
                }
            }
            return saveResult;
        }

        /// <summary>
        /// Session change event:exec the code when new session and open session
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        void sessionSetupControl1_OnSessionChange(object sender, EventArgs e)
        {
            sessionSetupControl1.Model.ChangedService.AcceptedChanged += new EventHandler(ChangedService_AcceptedChanged);
            sessionSetupControl1.Model.ChangedService.ModelChanged += new EventHandler(ChangedService_ModelChanged);
            MessageBus.Subject<SessionNameChangeMessage>().Observers += new System.Communication.Messaging.ObserverHandler<SessionNameChangeMessage>(SessionSetupForm_Observers);
        }

        void ChangedService_ModelChanged(object sender, EventArgs e)
        {
            if (!Text.StartsWith("* "))
            {
                Text = "* " + Text;                
            }
        }

        void ChangedService_AcceptedChanged(object sender, EventArgs e)
        {
            if (Text.StartsWith("* "))
            {                
                Text = Text.Remove(0, 2);
            }
        }

        private void btnOK_Click(object sender, EventArgs e)
        {
            if (sessionSetupControl1.Save())
            {
                this.DialogResult = DialogResult.OK;
                this.Close();
            }
        }

        private void btnCancel_Click(object sender, System.EventArgs e)
        {
            SessionSetupForm_FormClosing(sender, new FormClosingEventArgs(CloseReason.FormOwnerClosing, false));
        }

        private void SessionSetupForm_FormClosing(object sender, System.Windows.Forms.FormClosingEventArgs e)
        {
            if (!Save())
            {
                e.Cancel = true;
            }
        }
        
    }
}