//---------------------------------------------------------------------
//
// File: ImportFileItemControl.cs
//      
// Description:
//      import file rename control
//
// Author: Jerry Xu 2009-4-22
//
// Modify History:
//      Jerry Xu 2009-5-12 Update method:Check(),Init()
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
    /// <summary>
    /// PlaylistInfo import file rename control
    /// </summary>
    public partial class ImportFileItemControl : XtraUserControl
    {
        #region Properties define
        private MessageFileItem _item = null;
        /// <summary>
        /// Message file item
        /// </summary>
        public MessageFileItem Item
        {
            get { return _item; }
            set { _item = value; }
        }

        /// <summary>
        /// Name is valid
        /// </summary>
        public bool IsValid
        {
            set
            {
                sbtnCheck.Enabled = !value;
                _item.IsValid = value;
            }
        }
        #endregion

        public ImportFileItemControl(MessageFileItem item)
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
            teSource.Text = Path.GetFileNameWithoutExtension(_item.Item.Name);
        }

        /// <summary>
        /// Function: Init UI resources
        /// Author  : Jerry Xu
        /// Date    : 2008-11-17
        /// </summary>
        public void InitializeResource()
        {
            lcSource.Text = Resource.GetString(Resource.Strings.LibraryLibraryFileItemSourceCaption);
            lcDest.Text = Resource.GetString(Resource.Strings.LibraryLibraryFileItemDestCaption);
            sbtnCheck.Text = Resource.GetString(Resource.Strings.LibraryLibraryFileItemCheckCaption);
        }

        /// <summary>
        /// Function: Check name is valid
        /// Author  : Jerry Xu
        /// Date    : 2008-11-17
        /// </summary>
        private void Check()
        {
            if (teDest.Text.Trim() == string.Empty)
            {
                MsgBox.Warning(Resource.GetString(Resource.Strings.NameEmpty));
                teDest.Focus();
                return;
            }

            if (teDest.Text.Trim().Length > Constance.ImportNameMaxLength)
            {
                MsgBox.Warning(Resource.GetString(Resource.Strings.ImportNameMaxLength));
                teDest.Focus();
                return;
            }

            if (IOHelper.IsExist(_item.Item.Path, teDest.Text.Trim(), _item.Item.Type) == FileExistType.Yes)
            {
                MsgBox.Warning(Resource.GetFormatString(Resource.Strings.LibraryImportNameExistInfo, _item.Item.Type.ToString(), teDest.Text.Trim()));
                teDest.Focus();                
                _item.IsValid = false;
            }
            else
            {
                _item.Item.Path = IOHelper.GetLibraryFileName(_item.Item.Name, teDest.Text.Trim(), _item.Item.Type);
                _item.Item.Name = Path.GetFileName(_item.Item.Path);
                sbtnCheck.Enabled = false;
                _item.IsValid = true;
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
            Check();
            if (_item.IsValid)
                OnFileCheck();
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

        private EventHandler<ImportCheckEventArgs> _FileCheck;
        /// <summary>
        /// Message file name check event
        /// </summary>
        public event EventHandler<ImportCheckEventArgs> FileCheck
        {
            add { _FileCheck += value; }
            remove { _FileCheck -= value; }
        }
        private void OnFileCheck()
        {
            if (_item == null || _item.Item == null || !_item.IsValid)
                return;
            if (_FileCheck != null)
                _FileCheck(this, new ImportCheckEventArgs());

        }       
        #endregion
    }
}
