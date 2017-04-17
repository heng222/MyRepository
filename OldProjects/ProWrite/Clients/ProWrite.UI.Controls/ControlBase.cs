//---------------------------------------------------------------------
//
// File: ControlBase.cs
//
// Description:
// Control base class,  it support internationalization function interface
//
// Author: Kevin
//
// Copyright (C) 2008 by Trans-Lux All rights reserved.
// 
//---------------------------------------------------------------------
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Text;
using System.Windows.Forms;
using DevExpress.XtraEditors;
using ProWrite.Core;

namespace ProWrite.UI.Controls
{
    /// <summary>
    /// Control base class, it support internationalization function interface
    /// </summary>
    [Serializable]
    public partial class ControlBase : UserControl, ISupportGlobalization
    {
        public ControlBase()
        {
            InitializeComponent();
        }

        public virtual void SubscribeEvent()
        {
        }

        public virtual void UnSubscribeEvent()
        {
        }

        public virtual void RegisterHelp()
        {
        }

        public SessionState Session
        {
            get { return SessionState.Instance; }
        }

        /// <summary>
        /// initialize user data
        /// </summary>
        protected virtual void Init()
        {
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
        }
        /// <summary>
        /// Refresh the resource if it support internationalization ,otherwise don't refresh
        /// </summary>
        public void RefreshResource()
        {
            if (IsSupportGlobalization)
                InitializeResource();
        }

        #endregion

    }
}
