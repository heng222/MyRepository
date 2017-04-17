//---------------------------------------------------------------------
//
// File: SessionSetupControl.cs
//
// Description:
// SessionSetupControl UserControl 
//
// Author: Jerry
// Date  : 2009-7-16
//
// Modify history:
//      
// Copyright (C) 2008 by Trans-Lux All rights reserved.
// 
//---------------------------------------------------------------------

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using ProWrite.Entity.Live;
using ProWrite.UI.Controls.Common;
using ProWrite.Resources;
using ProWrite.Core;
using ProWrite.UI.Controls.Modules;

namespace ProWrite.UI.Controls.Live.Sessions
{
    public partial class SessionSetupControl : ControlBase
    {
        private const string ErrorNoSessionName = "Please type session name";
        private const string ErrorSameSessionName = "Current the session has exist same name in library.";

        #region Variants define
        //private SessionSetupControl _sessionControl;
        private SessionInfo _session;
        #endregion

        #region Event define
        public event EventHandler OnSessionChange = null;
        #endregion

        public SessionSetupControl()
        {
            InitializeComponent();
            if (!DesignMode)
                Init();

        }

        #region Properties define
        public SessionInfo Model
        {
            get { return _session; }            
        }

        public string SessionName
        {
            get
            {
                return sessionGeneralControl1.SessionName;
            }
        }

        #endregion

        #region Functions define
        protected override void Init()
        {
            sessionGeneralControl1.OnDeleteSession += new EventHandler(sessionGeneralControl1_OnDeleteSession);
        }

        private void SessionChange()
        {
            if (OnSessionChange != null)
                OnSessionChange(this, new EventArgs());
        }

        public void InitNew()
        {
            _session = new SessionInfo();
            SessionInfo.Current = _session;

            sessionGeneralControl1.New();
            signList1.New();
            hotButtonControl1.New();

            _session.ChangedService.AcceptChanged();
        }

        private void New()
        {
            _session = new SessionInfo();
            SessionInfo.Current = _session;
            SessionInfo.Current.IsNew = true;
            SessionChange();
            
            sessionGeneralControl1.New();
            signList1.New();
            categoryControl1.New();
            hotButtonControl1.New();
            MessageBus.Send(this, new SessionNameChangeMessage(Resource.GetString(Resource.Strings.LiveSessionSesssionSetupFormTitleDefault), false));
            _session.ChangedService.AcceptChanged();
        }

        private bool SaveCheck()
        {
            bool checkResult = true;

            if (SessionName.Trim() == string.Empty)
            {
                checkResult = false;
                tabSession.SelectedTabPageIndex = 0;
                MessageBox.Show(ErrorNoSessionName, "Save", MessageBoxButtons.OK, MessageBoxIcon.Information);
            }

            if (checkResult)
            {
                for (int i = 0; i < DataGate.Project.SessionInfos.Count; i++)
                {
                    if (SessionName.ToLower() == DataGate.Project.SessionInfos[i].Name.ToLower() &&
                        SessionInfo.Current.IsNew)
                    {
                        checkResult = false;
                        MessageBox.Show(ErrorSameSessionName, "Save", MessageBoxButtons.OK, MessageBoxIcon.Information);
                        break;
                    }
                }
            }

            return checkResult;
        }

        private void LoadSession()
        {
            //Load form
            LoadSessionForm frm = new LoadSessionForm();
            frm.ShowDialog();

            if (string.IsNullOrEmpty(frm.SessionName))
                return;

            SessionInfo.Current = _session = DataGate.Project.SessionInfos.GetByName(frm.SessionName).Copy();
            SessionInfo.Current.IsNew = false;

            //set session
            if (string.IsNullOrEmpty(frm.SessionName) || _session == null)
                return;

            SessionChange();

            sessionGeneralControl1.LoadSession();
            signList1.LoadSession();
            categoryControl1.LoadSession();
            hotButtonControl1.LoadSession();

            MessageBus.Send(this, new SessionNameChangeMessage(_session.Name, false));
            _session.ChangedService.AcceptChanged();
        }

        public bool Save()
        {
            bool saveResult = false;

            if (SaveCheck())
            {
                sessionGeneralControl1.Save();
                _session.AddSigns(signList1.SignListItems.ToArray());
                categoryControl1.Save();
                hotButtonControl1.Save();

                if (_session.IsNew)
                {
                    if (SessionCommon.AddSession(_session.Copy()))
                    {
                        MsgBox.Information(Resource.GetString(Resource.Strings.LiveSessionAddSuccessful));
                        _session.ChangedService.AcceptChanged();
                    }
                    else
                        MsgBox.Information(Resource.GetString(Resource.Strings.LiveSessionAddFailure));
                }
                else
                {
                    if (SessionCommon.UpdateSession())
                    {
                        MsgBox.Information(Resource.GetString(Resource.Strings.LiveSessionUpdateSuccessful));
                        _session.ChangedService.AcceptChanged();
                    }
                    else
                    {
                        MsgBox.Information(Resource.GetString(Resource.Strings.LiveSessionUpdateFailure));
                    }
                }

                saveResult = true;
            }
            //LiveModule live = new LiveModule();
            //live.InitTabControl();
            return saveResult;
        }

        #endregion

        private void btnSave_Click(object sender, EventArgs e)
        {
            Save();
        }

        private void btnLoad_Click(object sender, EventArgs e)
        {
            LoadSession();           
        }

        private void btnNew_Click(object sender, EventArgs e)
        {
            New();
        }

        private void sessionGeneralControl1_OnDeleteSession(object sender, EventArgs e)
        {
            New();
        }

        private void tabSession_SelectedPageChanged(object sender, DevExpress.XtraTab.TabPageChangedEventArgs e)
        {
            hotButtonControl1.SignList = signList1.SignList;
        }

    }
}
