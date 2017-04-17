//---------------------------------------------------------------------
//
// File: LoadSessionForm.cs
//
// Description:
// LoadSession Form 
//
// Author: Jerry
// Date  : 2009-7-24
//
// Modify history:
//      
// Copyright (C) 2008 by Trans-Lux All rights reserved.
// 
//---------------------------------------------------------------------


using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using ProWrite.UI.Controls.Common;
using DevExpress.XtraEditors.Controls;

namespace ProWrite.UI.Controls.Live.Sessions
{
    public partial class LoadSessionForm : DevExpress.XtraEditors.XtraForm
    {
        public LoadSessionForm()
        {
            InitializeComponent();
            if (!DesignMode)
                Init();
        }

        #region Properties define
        private string _sessionName = string.Empty;
        public string SessionName
        {
            get
            {
                return _sessionName;
            }
        }
        #endregion

        #region Functions define
        private void Init()
        {
            InitSessionList();
        }

        private void InitSessionList()
        {
            lstSession.Items.AddRange(DataGate.SessionInfos.ConvertAll<string>(p => 
                {
                    return p.Name;
                }).ToArray());
            
        }
        #endregion

        #region Events define
        private void btnOK_Click(object sender, EventArgs e)
        {
            if (lstSession.Items.Count == 0)
                _sessionName = null;
            else
            {
                _sessionName = lstSession.SelectedValue.ToString();
            }

            this.Close();
        }
        #endregion

    }
}
