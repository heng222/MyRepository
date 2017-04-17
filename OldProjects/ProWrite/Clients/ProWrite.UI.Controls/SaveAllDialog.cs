//---------------------------------------------------------------------
//
// File: SaveAllDialog.cs
//
// Description:
// Save all dialog 
//
// Author: 
//      Modify Histories:
//          Jerry Xu 2009-1-9 Add methods:Init(),InitResource(),IsExist(int index),Check()
//          Jerry Xu 2009-1-9 Add events:item_MemoryCheck(object sender, SaveAllMemoryCheckEventArgs e),item_MemoryRename(object sender, MemoryRenameEventArgs e)
//          Jerry Xu 2009-1-9 Update methods:SaveAllDialog(),AddItem(IPageController controller, string name, bool isEdit,MemoryLibraryItem tag)
//
// Copyright (C) 2008 by Trans-Lux All rights reserved.
// 
//---------------------------------------------------------------------

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using ProWrite.Entity.Library;
using DevExpress.XtraEditors;

namespace ProWrite.UI.Controls
{
    public partial class SaveAllDialog : XtraForm, ISaveAllController
    {
        private _Result _saveResult;

        public _Result SaveResult
        {
            get { return _saveResult; }
        }

        public SaveAllDialog()
        {
            InitializeComponent();
            if (!DesignMode)
                Init();
            btnYes.Enabled = false;
        }

        private void Init()
        {
            InitResource();
            //CreateFormElements();
        }

        private void InitResource()
        {
            //this.Text = Resource.GetString(Resource.Strings.LibraryLibraryFileItemTitle);
            //sbtnSave.Text = Resource.GetString(Resource.Strings.Save);
            //sbtnCancel.Text = Resource.GetString(Resource.Strings.Cancel);
            //sbtnSave.Image = Resource.GetImage(Resource.Images.Save16);
            //sbtnCancel.Image = Resource.GetImage(Resource.Images.Cancel16);
            btnYes.Enabled = false;
        }

        public void AddItem(
            IPageController controller
            , string name
            , bool isEdit
            ,MemoryLibraryItem tag)
        {
            if (controller == null
                || string.IsNullOrEmpty(name)
                || tag == null)
                return;
            SaveItem item = new SaveItem(controller, name, isEdit, tag);
            if (panel.Controls.Count > 0)
                item.Location = new Point(0, panel.Controls[panel.Controls.Count - 1].Top + 35);
            item.MemoryCheck += new EventHandler<SaveAllMemoryCheckEventArgs>(item_MemoryCheck);
            item.MemoryRename += new EventHandler<MemoryRenameEventArgs>(item_MemoryRename);
            panel.Controls.Add(item);
        }

        /// <summary>
        /// Function: Check name is exist in dialog
        /// Author  : Jerry Xu
        /// Date    : 2009-1-9
        /// </summary>
        /// <param name="index">SaveItem index</param>
        /// <returns>bool</returns>
        private bool IsExist(int index)
        {
            //LibraryFile file;
            for (int i = 0; i < panel.Controls.Count; i++)
            {
                if (i != index)
                {
                    if ((panel.Controls[i] as SaveItem).Item.Name == (panel.Controls[index] as SaveItem).Item.Name)
                    {
                        (panel.Controls[index] as SaveItem).Item.IsValid = false;
                        return true;
                    }
                }
            }
            return false;
        }

        /// <summary>
        /// Function: Check all name is valid
        /// Author  : Jerry Xu
        /// Date    : 2009-1-9
        /// </summary>
        private void Check()
        {
            SaveItemInfo item;
            foreach (Control control in panel.Controls)
            {
                item = (control as SaveItem).Item;
                if (item.SaveResult == _Result.Save&& !item.IsValid)
                {
                    btnYes.Enabled = false;
                    return;
                }
            }

            btnYes.Enabled = true;
        }

        void item_MemoryCheck(object sender, SaveAllMemoryCheckEventArgs e)
        {
            int index = panel.Controls.GetChildIndex(sender as SaveItem);
            if (IsExist(index))
                return;
            Check();
        }

        void item_MemoryRename(object sender, MemoryRenameEventArgs e)
        {
            btnYes.Enabled = false;
        }

        public int Count
        {
            get { return panel.Controls.Count; }
        }

        public List<SaveItemInfo> Items
        {
            get
            {
                List<SaveItemInfo> items = new List<SaveItemInfo>();
                foreach (SaveItem item in panel.Controls)
                {
                    items.Add(item.Item);
                }
                return items;
            }
        }

        private void btnYes_Click(object sender, EventArgs e)
        {
            _saveResult = _Result.Save;
            Close();
        }

        private void btnNo_Click(object sender, EventArgs e)
        {
            _saveResult = _Result.No;
            Close();
        }

        private void btnCancel_Click(object sender, EventArgs e)
        {
            _saveResult = _Result.Cancel;
            Close();
        }

    }

}