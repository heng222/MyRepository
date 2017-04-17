//---------------------------------------------------------------------
//
// File: GeneralControl.cs
//
// Description:
// GeneralControl UserControl 
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
using ProWrite.Core;
using ProWrite.Entity.Live;
using ProWrite.UI.Controls.Common;

namespace ProWrite.UI.Controls.Live.Sessions
{
    public partial class GeneralControl : ControlBase
    {
        public event EventHandler OnDeleteSession = null;

        public GeneralControl()
        {
            InitializeComponent();
            if (!DesignMode)
                Init();
        }

        #region Variants define
        private bool _isCanChange = true;
        private const string Note_DelectSessionInfo = "Do you want delete the session:{0}?";
        #endregion

        #region Properties define
        private SessionInfo _session = null;
        
        public SessionInfo Model
        {
            get { return _session; }
            set 
            { 
                _session = value;
                if(_session!=null && _session!=value && _session.IsNew == false)
                    LoadSession();
            }
        }
        
        #endregion

        #region Functions define
        public override void SubscribeEvent()
        {
            base.SubscribeEvent();
        }

        public override void UnSubscribeEvent()
        {
            base.UnSubscribeEvent();
        }

        protected override void Init()
        {
            sbtnDeleteSession.Enabled = false;
        }

        public void New()
        {
            _isCanChange = false;
            if (SessionInfo.Current != null)
                _session = SessionInfo.Current;
            chkAlert.Checked = _session.IsAlert;
            pnlCenterAlert.Enabled = _session.IsAlert;
            teSessionName.Text = string.Empty;
            seYellow.Value = 0;
            seRed.Value = 0;
            seAutoQueueCounter.Value = 0;
            rgCounter.EditValue = true;
            rgNail.EditValue = true;
            _isCanChange = true;
            teSessionName.Enabled = true;
        }

        public void Save()
        {
            teSessionName.Enabled = false;
            sbtnDeleteSession.Enabled = true;

            if (!SessionInfo.Current.IsNew)
            {
                bool check = true;

                for (int i = 0; i < DataGate.Project.SessionInfos.Count; i++)
                {
                    if (SessionName.ToLower() == DataGate.Project.SessionInfos[i].Name)
                    {
                        check = false;
                    }
                }

                if (check)
                {
                    SessionInfo.Current.IsNew = true;
                    SessionInfo.Current.Name = SessionName;
                }
            }
        }

        public string SessionName
        {
            get
            {
                return teSessionName.Text;
            }
        }

        public void LoadSession()
        {
            _isCanChange = false;
            if (SessionInfo.Current != null)
                _session = SessionInfo.Current;
            teSessionName.Text = _session.Name;
            teSessionName.Enabled = true;
            pnlCenterAlert.Enabled = _session.IsAlert;
            chkAlert.Checked = _session.IsAlert;

            if (_session.IsAlert)
            {
                if(_session.YellowAlert!=null)
                    seYellow.Value = _session.YellowAlert.Length;
                if(_session.RedALert!=null)
                    seRed.Value = _session.RedALert.Length;
            }
            seAutoQueueCounter.Value = _session.AutoQueueCounter;

            rgCounter.EditValue = _session.IsVisibleCounter;
            rgNail.EditValue = _session.IsNail;
            _isCanChange = true;
            sbtnDeleteSession.Enabled = true;
        }

        private void SetAlertState(bool flag)
        {
            pnlCenterAlert.Enabled = flag;
            _session.IsAlert = flag;
        }

        #endregion

        #region Events define

        #endregion

        private void pnlCenter_Paint(object sender, PaintEventArgs e)
        {

        }

        private void chkAlert_CheckedChanged(object sender, EventArgs e)
        {
            if(_isCanChange)
                SetAlertState(chkAlert.Checked);            
        }

        private void teSessionName_TextChanged(object sender, EventArgs e)
        {
            if (_isCanChange)
                _session.Name = teSessionName.Text;
        }

        private void seYellow_ValueChanged(object sender, EventArgs e)
        {
            if (_isCanChange)
                _session.YellowAlert.Length = (int)seYellow.Value;
        }

        private void seRed_ValueChanged(object sender, EventArgs e)
        {
            if (_isCanChange)
                _session.RedALert.Length = (int)seRed.Value;
        }

        private void seAutoQueueCounter_ValueChanged(object sender, EventArgs e)
        {
            if (_isCanChange)
             _session.AutoQueueCounter = (int)seAutoQueueCounter.Value;
        }

        private void rgCounter_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (_isCanChange)
                _session.IsVisibleCounter = (bool)rgCounter.EditValue;
        }

        private void rgNail_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (_isCanChange)
                _session.IsNail = (bool)rgNail.EditValue;
            
        }

        private void sbtnDeleteSession_Click(object sender, System.EventArgs e)
        {
            if (DataGate.SessionInfos.IndexOf(SessionInfo.Current) >= 0)
            {
                if (MessageBox.Show(string.Format(Note_DelectSessionInfo,SessionInfo.Current.Name), "Delete SessionInfo", MessageBoxButtons.YesNo, MessageBoxIcon.Question) == DialogResult.Yes)
                {
                    DataGate.SessionInfos.Remove(SessionInfo.Current);
                    if (OnDeleteSession != null) 
                        OnDeleteSession(sender, e);
                }
            }
        }

        private void SpinEdit_EditValueChanging(object sender, DevExpress.XtraEditors.Controls.ChangingEventArgs e)
        {
            if(e.NewValue.ToString().IndexOf('-') >= 0 && int.Parse(e.NewValue.ToString()) > 0 && int.Parse(e.NewValue.ToString()) < 65535)
            {
                e.Cancel = true; 
            }
        }

    }
}
