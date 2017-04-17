//---------------------------------------------------------------------
//
// File: LibraryMessageItem.cs
//      
// Description:
//      LibraryMessageItem control
//
// Author: Jerry Xu 2008-11-7
//
// Modify History:
//      Jerry Xu 2009-3-4   Update method:Check()
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
using ProWrite.UI.Controls.Common;

namespace ProWrite.UI.Controls.Library
{
    public partial class LibraryMessageItem : XtraUserControl
    {
        #region Properties define
        private MessageInfo _item = null;
        public MessageInfo Item
        {
            get { return _item; }
            set { _item = value; }
        }
        public bool IsValid
        {
            //get { return _item; }
            set
            {
                sbtnCheck.Enabled = !value;
                //_item.IsValid = value;
                //_item = value; 
            }
        }
        #endregion

        public LibraryMessageItem(MessageInfo item)
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
            teSource.Text = _item.Name;
        }

        /// <summary>
        /// Function: Init UI resources
        /// Author  : Jerry Xu
        /// Date    : 2008-11-7
        /// </summary>
        public void InitializeResource()
        {
            lcSource.Text = Resource.GetString(Resource.Strings.LibraryLibraryMessageItemSourceCaption);
            lcDest.Text = Resource.GetString(Resource.Strings.LibraryLibraryMessageItemDestCaption);
            sbtnCheck.Text = Resource.GetString(Resource.Strings.LibraryLibraryMessageItemCheckCaption);

            teSource.Left = lcSource.Right + 5;
            lcDest.Left = teSource.Right + 5;
            teDest.Left = lcDest.Right + 5;
            sbtnCheck.Left = teDest.Right + 5;
            

        }

        /// <summary>
        /// Function: Check name is valid
        /// Author  : Jerry Xu
        /// Date    : 2008-11-7
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

            if (LibraryGroup.Current.Messages.GetByName(teDest.Text.Trim())!=null)
            {
                MsgBox.Warning(Resource.GetFormatString(Resource.Strings.LibraryImportNameExistInfo, _item.Type.ToString(), teDest.Text.Trim()));
                teDest.Focus();                                
            }
            else
            {
                _item.Name = teDest.Text;
                sbtnCheck.Enabled = false;             
            }
        }        
        #endregion

        #region Events define        
        private void teDest_TextChanged(object sender, EventArgs e)
        {
            OnLibraryImportRename();
        }

        private void sbtnCheck_Click(object sender, EventArgs e)
        {
            Check();
            if (LibraryGroup.Current.Messages.GetByName(teDest.Text) == null)
                OnLibraryMessageCheck(this);
        }

        private EventHandler<ImportRenameEventArgs> _LibraryImportRename;
        /// <summary>
        /// Text change event
        /// </summary>
        public event EventHandler<ImportRenameEventArgs> LibraryImportRename
        {
            add { _LibraryImportRename += value; }
            remove { _LibraryImportRename -= value; }
        }
        private void OnLibraryImportRename()
        {
            sbtnCheck.Enabled = true;
            _LibraryImportRename(this, new ImportRenameEventArgs());
        }       

        private EventHandler<LibraryMessageCheckEventArgs> _LibraryMessageCheck;
        /// <summary>
        /// Message name check event
        /// </summary>
        public event EventHandler<LibraryMessageCheckEventArgs> LibraryMessageCheck
        {
            add { _LibraryMessageCheck += value; }
            remove { _LibraryMessageCheck -= value; }
        }
        private void OnLibraryMessageCheck(LibraryMessageItem item)
        {
            if (item == null || item.Item == null)
                return;

            _LibraryMessageCheck(this, new LibraryMessageCheckEventArgs(item));

        }       
        #endregion        
    }
}
