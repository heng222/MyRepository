//---------------------------------------------------------------------
//
// File: ImportMessageItemControl.cs
//      
// Description:
//      import message rename control
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
    public partial class ImportMessageItemControl : XtraUserControl
    {
        #region Properties define
        private MessageItem _item = null;
        public MessageItem Item
        {
            get { return _item; }
            set { _item = value; }
        }
        #endregion

        public ImportMessageItemControl(MessageItem item)
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
            lcSource.Text = Resource.GetString(Resource.Strings.LibraryLibraryMessageItemSourceCaption);
            lcDest.Text = Resource.GetString(Resource.Strings.LibraryLibraryMessageItemDestCaption);
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

            if (LibraryGroup.Current.Messages.GetByName(teDest.Text.Trim())!=null)
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
                OnMessageCheck();
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

        private EventHandler<ImportCheckEventArgs> _MessageCheck;
        public event EventHandler<ImportCheckEventArgs> MessageCheck
        {
            add { _MessageCheck += value; }
            remove { _MessageCheck -= value; }
        }
        private void OnMessageCheck()
        {
            if (_item == null || _item.Item == null || !_item.IsValid)
                return;
            if(_MessageCheck!=null)
                _MessageCheck(this, new ImportCheckEventArgs());

        }       
        #endregion        
    }
}
