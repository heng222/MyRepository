//---------------------------------------------------------------------
//
// File: DialogForm.cs
//
// Description:
// Diaglog form base class 
//
// Author: Kevin
//
// Copyright (C) 2008 by Trans-Lux All rights reserved.
// 
// Modification History
// Louis 2008-6-24 Using resource key to get Images 
//---------------------------------------------------------------------
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using DevExpress.XtraEditors;
using ProWrite.Core;
using ProWrite.Resources;

namespace ProWrite.UI.Controls
{
    /// <summary>
    /// Dialog form base class, it support internationalization function interface
    /// </summary>
    public partial class DialogForm : XtraForm, ISupportGlobalization 
    {
        public DialogForm()
        {
            InitializeComponent();
        }

        /// <summary>
        /// Initialize user data
        /// </summary>
        protected virtual void Init()
        {
        }

        /// <summary>
        /// Load user data and resource infomation
        /// </summary>
        /// <param name="e"></param>
        protected override void OnLoad(EventArgs e)
        {
            base.OnLoad(e);
            InitializeResource();
            Init();

        }

        #region ISupportGlobalization Members
        private bool _isSupportGlobalization;

        /// <summary>
        /// Get or set whether it support internationalization function
        /// </summary>
        public bool IsSupportGlobalization
        {
            get
            {
                return _isSupportGlobalization;
            }
            set
            {
                _isSupportGlobalization = value;
            }
        }

        /// <summary>
        /// Initialize resource information
        /// </summary>
        public virtual void InitializeResource()
        {
			btnSave.Image = Resource.GetImage(Resource.Images.Save16); 
			btnSave.Text = Resource.GetString(Resource.Strings.Save);
            btnSave.ToolTip = btnSave.Text;
			btnCancel.Image = Resource.GetImage(Resource.Images.Cancel16); 
			btnCancel.Text = Resource.GetString(Resource.Strings.Cancel);
            btnCancel.ToolTip = btnCancel.Text;
        }

        /// <summary>
        /// Refresh the resource if it support internationalization ,otherwise don't refresh
        /// </summary>
        public void RefreshResource()
        {
            if (IsSupportGlobalization)
                InitializeResource();
        }

        #endregion //ISupportGlobalization Members

        #region Event Members
        protected virtual void OnOk()
        {
            
        }

        protected virtual void OnCancel()
        {
            Close();
        }

        /// <summary>
        /// Cancel event 
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnCancel_Click(object sender, EventArgs e)
        {
            OnCancel();
        }

        /// <summary>
        /// Ok envent
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnSave_Click(object sender, EventArgs e)
        {
            OnOk();
        }
        #endregion // Event Members
    }
}