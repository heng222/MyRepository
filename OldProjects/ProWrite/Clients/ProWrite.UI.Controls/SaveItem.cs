//---------------------------------------------------------------------
//
// File: SaveItem.cs
//
// Description:
// SaveItem class
//
// Author: Terry 2008-9-9
//      Modify Histories:
//          Jerry Xu 2009-1-9 Add method:Check()
//          Jerry Xu 2009-1-9 Add events:sbtnCheck_Click(object sender, EventArgs e),txtNewName_TextChanged(object sender, EventArgs e)
//          Jerry Xu 2009-1-9 Add properties: IsValid
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
using ProWrite.Entity.Library;
using DevExpress.XtraEditors;
using ProWrite.UI.Controls.Common;
using ProWrite.Resources;

namespace ProWrite.UI.Controls
{
    public partial class SaveItem : XtraUserControl
    {
        private SaveItemInfo _item;
        public SaveItem(IPageController controller, string pageName,bool isEdit,MemoryLibraryItem tag)
        {
            InitializeComponent();
            _item = new SaveItemInfo(controller, pageName,isEdit,tag);
            this.txtNewName.Text = _item.Name;
            this.lblType.Text = tag.Type.ToString();
            ckbYes.Checked = true;
            if (_item.IsEdit)
                this.txtNewName.Enabled = false;
        }

        public SaveItemInfo Item
        {
            get
            {
                _item.SaveResult = ckbYes.Checked ? _Result.Save : _Result.No;
                _item.Name = _item.Tag.Name = txtNewName.Text;
                if (!_item.IsEdit)
                    _item.Tag.Name = _item.Name;
                return _item;
            }
        }

        /// <summary>
        /// Function: Check MemoryLibraryItem name is valid
        /// Author  : Jerry Xu
        /// Date    : 2009-1-9
        /// </summary>
        private void Check()
        {
            string tempName = txtNewName.Text.Trim();
            if (tempName == string.Empty)
            {
                MsgBox.Warning(Resource.GetString(Resource.Strings.NameEmpty));
                txtNewName.Focus();
                return;
            }
            if (!_item.IsEdit && LibraryGroup.Current.GetByName(tempName, _item.Tag.Type) != null)
            {
                MsgBox.Warning(Resource.GetFormatString(Resource.Strings.LibraryImportNameExistInfo, _item.Tag.Type.ToString(), tempName));
                txtNewName.Focus();
                _item.IsValid = false;
                return;
            }
            if (_item.IsEdit && _item.Name != txtNewName.Text.Trim() && LibraryGroup.Current.GetByName(tempName, _item.Tag.Type) != null)
            {
                MsgBox.Warning(Resource.GetFormatString(Resource.Strings.LibraryImportNameExistInfo, _item.Tag.Type.ToString(), tempName));
                txtNewName.Focus();
                _item.IsValid = false;
                return;
            }

            _item.Name = tempName;
            //_item.FileName = Path.GetFileName(_item.LibraryFileName);
            sbtnCheck.Enabled = false;
            _item.IsValid = true;            
        }        

        private void sbtnCheck_Click(object sender, EventArgs e)
        {
            Check();
            if (_item.IsValid)
                OnMemoryCheck(this);
            if (!_item.IsValid)
                sbtnCheck.Enabled = true;
        }

        

        private void txtNewName_TextChanged(object sender, EventArgs e)
        {
            OnMemoryRename();
        }

        private EventHandler<SaveAllMemoryCheckEventArgs> _MemoryCheck;
        public event EventHandler<SaveAllMemoryCheckEventArgs> MemoryCheck
        {
            add { _MemoryCheck += value; }
            remove { _MemoryCheck -= value; }
        }
        private void OnMemoryCheck(SaveItem item)
        {
            if (item == null || item.Item == null)// || !item.Item.IsValid)
                return;

            _MemoryCheck(this, new SaveAllMemoryCheckEventArgs(item));

        }

        private EventHandler<MemoryRenameEventArgs> _MemoryRename;
        public event EventHandler<MemoryRenameEventArgs> MemoryRename
        {
            add { _MemoryRename += value; }
            remove { _MemoryRename -= value; }
        }
        private void OnMemoryRename()
        {
            sbtnCheck.Enabled = true;
            _item.IsValid = false;
            _MemoryRename(this, new MemoryRenameEventArgs());
        }

        private void ckbYes_Click(object sender, EventArgs e)
        {
            //if (_item.IsValid)
                OnMemoryCheck(this);
            if (ckbYes.Checked&&!_item.IsValid)
                sbtnCheck.Enabled = true;
            if (!ckbYes.Checked)
                sbtnCheck.Enabled = false;
            this.txtNewName.Enabled = ckbYes.Checked;
            //sbtnCheck.Enabled = ckbYes.Checked;
        }       
    }


    public class SaveItemInfo
    {
        public SaveItemInfo() { }
        public SaveItemInfo(IPageController controller, string pageName,bool isEdit, MemoryLibraryItem tag)
        {
            _pageController = controller;
            _pageName = pageName;
            _name = tag.Name;
            _isEdit = isEdit;
            _tag = tag;
        }

        private string _name;
        public string Name
        {
            get
            {
                return _name;
            }
            set { _name = value; }
        }

        private string _pageName;
        public string PageName
        {
            get { return _pageName; }
        }

        private bool _isEdit;
        public bool IsEdit
        {
            get { return _isEdit; }
            set { _isEdit = value; }
        }

        private _Result _saveResult;
        public _Result SaveResult
        {
            get { return _saveResult; }
            set { _saveResult = value; }
        }

        private MemoryLibraryItem _tag;
        public MemoryLibraryItem Tag
        {
            get { return _tag; }
        }
        
        private IPageController _pageController;
        public IPageController Controller
        {
            get { return _pageController; }
            set { _pageController = value; }
        }

        private bool _isValid = false;
        public bool IsValid
        {
            get { return _isValid; }
            set { _isValid = value; }
        }
    }


    public enum _Result
    {
        Cancel,
        Save,
        No
    }
}
