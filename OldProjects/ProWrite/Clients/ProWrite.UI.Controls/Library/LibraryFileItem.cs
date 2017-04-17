//---------------------------------------------------------------------
//
// File: LibraryFileItem.cs
//      
// Description:
//      LibraryFileItem control
//
// Author: Jerry Xu 2008-11-7
//
// Modify History:
//      Jerry Xu 2009-3-4   Update method:Check()
//      Jerry Xu 2009-3-31  Update method:Check()
//      Jerry Xu 2009-4-2   Update method:Check()
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
using ProWrite.UI.Controls.Common;

namespace ProWrite.UI.Controls.Library
{
    public partial class LibraryFileItem : XtraUserControl
    {
        #region Properties define
        private LibraryFile _item = null;
        /// <summary>
        /// Library file
        /// </summary>
        public LibraryFile Item
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

        public LibraryFileItem(LibraryFile item)
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
            teSource.Text = _item.FileName;
        }

        /// <summary>
        /// Function: Init UI resources
        /// Author  : Jerry Xu
        /// Date    : 2008-11-7
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


            if (IOHelper.IsExist(_item.FileName, teDest.Text.Trim(), _item.Type) == FileExistType.Yes ) 
            {
                MsgBox.Warning(Resource.GetFormatString(Resource.Strings.LibraryImportNameExistInfo, _item.Type.ToString(), teDest.Text.Trim()));
                teDest.Focus();                
                _item.IsValid = false;
            }
            //else if(LibraryGroup.Current.Messages.GetByName(teDest.Text.Trim())!=null && !_item.IsValidMessage)
            //{
            //    MsgBox.Warning(Resource.GetFormatString(Resource.Strings.LibraryImportNameExistInfo, LibraryType.Message.ToString(), teDest.Text.Trim()));
            //    teDest.Focus();
            //    _item.IsValid = false;
            //}
            else
            {
                _item.LibraryFileName = IOHelper.GetLibraryFileName(_item.FileName, teDest.Text.Trim(), _item.Type);
                //_item.FileName = Path.GetFileName(_item.LibraryFileName);
                sbtnCheck.Enabled = false;
                _item.IsValid = true;
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
            if (_item.IsValid)
                OnLibraryFileCheck(this);
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

        private EventHandler<LibraryFileCheckEventArgs> _LibraryFileCheck;
        /// <summary>
        /// Library file name check event
        /// </summary>
        public event EventHandler<LibraryFileCheckEventArgs> LibraryFileCheck
        {
            add { _LibraryFileCheck += value; }
            remove { _LibraryFileCheck -= value; }
        }
        private void OnLibraryFileCheck(LibraryFileItem item)
        {
            if (item == null || item.Item == null || !item.Item.IsValid)
                return;

            _LibraryFileCheck(this, new LibraryFileCheckEventArgs(item));

        }       
        #endregion

        #region Init behind code
        private LabelControl lcSource;
        private TextEdit teSource;
        private LabelControl lcDest;
        private TextEdit teDest;
        private SimpleButton sbtnCheck;
        private void InitializeComponent()
        {
            this.sbtnCheck = new DevExpress.XtraEditors.SimpleButton();
            this.teDest = new DevExpress.XtraEditors.TextEdit();
            this.teSource = new DevExpress.XtraEditors.TextEdit();
            this.lcDest = new DevExpress.XtraEditors.LabelControl();
            this.lcSource = new DevExpress.XtraEditors.LabelControl();
            ((System.ComponentModel.ISupportInitialize)(this.teDest.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.teSource.Properties)).BeginInit();
            this.SuspendLayout();
            // 
            // sbtnCheck
            // 
            this.sbtnCheck.Location = new System.Drawing.Point(641, 3);
            this.sbtnCheck.Name = "sbtnCheck";
            this.sbtnCheck.Size = new System.Drawing.Size(75, 23);
            this.sbtnCheck.TabIndex = 9;
            this.sbtnCheck.Text = "Check";
            this.sbtnCheck.Click += new System.EventHandler(this.sbtnCheck_Click);
            // 
            // teDest
            // 
            this.teDest.Location = new System.Drawing.Point(436, 4);
            this.teDest.Name = "teDest";
            this.teDest.Size = new System.Drawing.Size(199, 20);
            this.teDest.TabIndex = 8;
            this.teDest.TextChanged += new System.EventHandler(this.teDest_TextChanged);
            // 
            // teSource
            // 
            this.teSource.Location = new System.Drawing.Point(118, 4);
            this.teSource.Name = "teSource";
            this.teSource.Properties.ReadOnly = true;
            this.teSource.Size = new System.Drawing.Size(199, 20);
            this.teSource.TabIndex = 7;
            // 
            // lcDest
            // 
            this.lcDest.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.lcDest.Location = new System.Drawing.Point(323, 4);
            this.lcDest.Name = "lcDest";
            this.lcDest.Size = new System.Drawing.Size(78, 13);
            this.lcDest.TabIndex = 6;
            this.lcDest.Text = "Target file name";
            // 
            // lcSource
            // 
            this.lcSource.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.lcSource.Location = new System.Drawing.Point(5, 4);
            this.lcSource.Name = "lcSource";
            this.lcSource.Size = new System.Drawing.Size(79, 13);
            this.lcSource.TabIndex = 5;
            this.lcSource.Text = "Source file name";
            // 
            // LibraryFileItem
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.sbtnCheck);
            this.Controls.Add(this.teDest);
            this.Controls.Add(this.teSource);
            this.Controls.Add(this.lcDest);
            this.Controls.Add(this.lcSource);
            this.Name = "LibraryFileItem";
            this.Size = new System.Drawing.Size(720, 29);
            ((System.ComponentModel.ISupportInitialize)(this.teDest.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.teSource.Properties)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

    }
}
