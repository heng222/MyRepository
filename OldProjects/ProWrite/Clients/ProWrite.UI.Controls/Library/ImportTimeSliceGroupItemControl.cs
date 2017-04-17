﻿//---------------------------------------------------------------------
//
// File: ImportTimeSliceGroupItemControl.cs
//      
// Description:
//      import TimesliceGroup rename control
//
// Author: Jerry Xu 2009-4-22
//
// Modify History:
//
// Copyright (C) 2008 by Trans-Lux All rights reserved.
// 
//---------------------------------------------------------------------

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using DevExpress.XtraEditors;
using ProWrite.Core;
using ProWrite.Resources;
using ProWrite.Entity.Library;
using System.IO;
using ProWrite.Entity;
using ProWrite.Entity.Library.ImportExport;
using ProWrite.UI.Controls.Common;

namespace ProWrite.UI.Controls.Library
{
    public partial class ImportTimeSliceGroupItemControl : XtraUserControl
    {
        #region Properties define
        private TimeSliceGroupItem _item = null;
        public TimeSliceGroupItem Item
        {
            get { return _item; }
            set { _item = value; }
        }
        #endregion

        public ImportTimeSliceGroupItemControl(TimeSliceGroupItem item)
        {
            InitializeComponent();

            if (!DesignMode)
            {
                _item = item;
                Init();
            }
        }

        #region Functions define       

        protected void Init()
        {
            InitializeResource();

            teSource.Text = _item.Item.Name;
        }

        public void InitializeResource()
        {
            lcSource.Text = Resource.GetString(Resource.Strings.LibraryImportTimeSliceGroupGroupItemSourceCaption);
            lcDest.Text = Resource.GetString(Resource.Strings.LibraryImportTimeSliceGroupGroupItemTargetCaption);
            sbtnCheck.Text = Resource.GetString(Resource.Strings.LibraryLibraryMessageItemCheckCaption);
        }

        private bool Check()
        {
            if (teDest.Text.Trim() == string.Empty)
            {
                MsgBox.Warning(Resource.GetString(Resource.Strings.NameEmpty));
                teDest.Focus();
                return false;
            }

            if (teDest.Text.Trim().Length > Constance.ImportNameMaxLength)
            {
                MsgBox.Warning(Resource.GetString(Resource.Strings.ImportNameMaxLength));
                teDest.Focus();
                return false;
            }

            if (LibraryGroup.Current.TimeSliceGroups.GetByName(teDest.Text.Trim())!=null)
            {
                MsgBox.Warning(Resource.GetFormatString(Resource.Strings.LibraryImportNameExistInfo, _item.Item.Type.ToString(), teDest.Text.Trim()));
                teDest.Focus();
                return false;           
            }
            else
            {
                _item.IsValid = true;
                _item.Item.Name = teDest.Text.Trim();                
                sbtnCheck.Enabled = false;
                return true;
            }
        }        
        #endregion

        #region Events define        
        private void teDest_TextChanged(object sender, EventArgs e)
        {
            OnImportRename();
        }

        private void sbtnCheck_Click(object sender, EventArgs e)
        {
            if(Check())            
                OnTimeSliceGroupCheck();
        }

        private EventHandler<ImportRenameEventArgs> _ImportRename;
        /// <summary>
        /// Text change event
        /// </summary>
        public event EventHandler<ImportRenameEventArgs> ImportRename
        {
            add { _ImportRename += value; }
            remove { _ImportRename -= value; }
        }
        private void OnImportRename()
        {
            if (_ImportRename != null)
            {
                sbtnCheck.Enabled = true;
                _ImportRename(this, new ImportRenameEventArgs());
            }
        }

        private EventHandler<ImportCheckEventArgs> _TimeSliceGroupCheck;
        public event EventHandler<ImportCheckEventArgs> TimeSliceGroupCheck
        {
            add { _TimeSliceGroupCheck += value; }
            remove { _TimeSliceGroupCheck -= value; }
        }
        private void OnTimeSliceGroupCheck()
        {
            if (_item == null)
                return;
            if (_TimeSliceGroupCheck != null)
                _TimeSliceGroupCheck(this, new ImportCheckEventArgs());

        }       
        #endregion                
    }
}
