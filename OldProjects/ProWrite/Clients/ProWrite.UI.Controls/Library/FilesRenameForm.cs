//---------------------------------------------------------------------
//
// File: FilesRenameForm.cs
//      
// Description:
//      FilesRenameForm
//
// Author: Jerry Xu 2008-11-6
//
// Modify History:
//      Jerry Xu 2009-1-9 Update method:CreateFormElements()
//      Jerry Xu 2009-1-12  Update method:InitResource()
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
using ProWrite.Core;
using DevExpress.XtraEditors;
using ProWrite.Resources;
using ProWrite.Entity.Library;

namespace ProWrite.UI.Controls.Library
{
    public partial class FilesRenameForm : XtraForm
    {
        #region Variants define
        
        private List<LibraryFile> _files;
        /// <summary>
        /// Rename files 
        /// </summary>
        public List<LibraryFile> Files
        {
            get { return _files; }
        }
        private List<MessageInfo> _messages;
        /// <summary>
        /// Rename MessageInfos
        /// </summary>
        public List<MessageInfo> Messages
        {
            get { return _messages; }
        }
        #endregion

        public FilesRenameForm(List<LibraryFile> files, List<MessageInfo> listMessages)
        {
            InitializeComponent();
            
            if (!DesignMode)
            {
                _files = files;
                _messages = listMessages;
                Init();
            }
        }
        #region Properties define
        private bool _isRefresh = false;
        /// <summary>
        /// Is saved
        /// </summary>
        public bool IsRefresh
        {
            get { return _isRefresh; }
            set { _isRefresh = value; }
        }   
        #endregion

        #region Functions define
        private void Init()
        {
            InitResource();
            CreateFormElements();
        }

        /// <summary>
        /// Function: Init UI resources
        /// Author  : Jerry Xu
        /// Date    : 2008-11-6
        /// </summary>
        private void InitResource()
        {
            this.Text = Resource.GetString(Resource.Strings.LibraryLibraryFileItemTitle);
            sbtnSave.Text = Resource.GetString(Resource.Strings.Save);
            sbtnCancel.Text = Resource.GetString(Resource.Strings.Cancel);
            sbtnSave.Image = Resource.GetImage(Resource.Images.Save16);
            sbtnCancel.Image = Resource.GetImage(Resource.Images.Cancel16);
            sbtnSave.Enabled = false;
            this.ShowIcon = false;

            groupFiles.Expanded = true;
            groupMessage.Expanded = true;
            containerFiles.AutoScroll = false;
            containerMessage.AutoScroll = false;
            navRename.ScrollMode = DevExpress.XtraNavBar.NavBarScrollMode.ScrollAlways;
        }

        /// <summary>
        /// Function: Generate last data
        /// Author  : Jerry Xu
        /// Date    : 2008-11-6
        /// </summary>
        private void GenerateData()
        {
            _files = new List<LibraryFile>();
            foreach (Control control in containerFiles.Controls)
            {
                _files.Add((control as LibraryFileItem).Item);                               
            }

            _messages = new List<MessageInfo>();
            foreach (Control control in containerMessage.Controls)
            {
                _messages.Add((control as LibraryMessageItem).Item);
            }
        }

        /// <summary>
        /// Function: Create form elements
        /// Author  : Jerry Xu
        /// Date    : 2008-11-6
        /// </summary>
        private void CreateFormElements()
        {
            LibraryFileItem fileItem;
            foreach (LibraryFile item in _files)
            {
                fileItem = new LibraryFileItem(item);
                fileItem.Width = containerFiles.Width - 2;
                fileItem.Dock = DockStyle.Top;
                fileItem.LibraryFileCheck += new EventHandler<LibraryFileCheckEventArgs>(fileItem_LibraryFileCheck);
                fileItem.LibraryImportRename += new EventHandler<ImportRenameEventArgs>(fileItem_LibraryImportRename);
                containerFiles.Height = containerFiles.Height + fileItem.Height;
                containerFiles.Controls.Add(fileItem);                
            }

            LibraryMessageItem messageItem;
            foreach (MessageInfo item in _messages)
            {
                messageItem = new LibraryMessageItem(item);
                messageItem.Width = containerMessage.Width - 2;
                messageItem.Dock = DockStyle.Top;
                messageItem.LibraryMessageCheck += new EventHandler<LibraryMessageCheckEventArgs>(messageItem_LibraryMessageCheck);
                messageItem.LibraryImportRename += new EventHandler<ImportRenameEventArgs>(fileItem_LibraryImportRename);
                containerMessage.Height = containerMessage.Height + messageItem.Height;
                containerMessage.Controls.Add(messageItem);
            }
            
        }        

        /// <summary>
        /// Function: Check input file name is exist in needed rename file list.
        /// Author  : Jerry Xu
        /// Date    : 2008-11-6
        /// </summary>
        /// <param name="index">Current file control index</param>
        /// <returns>bool</returns>
        private bool IsExistFile(int index)
        {
            //LibraryFile file;
            for(int i=0;i<containerFiles.Controls.Count;i++)
            {
                if (i != index)
                {
                    if ((containerFiles.Controls[i] as LibraryFileItem).Item.LibraryFileName == (containerFiles.Controls[index] as LibraryFileItem).Item.LibraryFileName)
                    {
                        (containerFiles.Controls[index] as LibraryFileItem).IsValid = false;
                        return true;
                    }
                }                
            }
            return false;
        }

        /// <summary>
        /// Function: Check input message name is exist in needed rename message list.
        /// Author  : Jerry Xu
        /// Date    : 2008-11-6
        /// </summary>
        /// <param name="index">Current message control index</param>
        /// <returns>bool</returns>
        private bool IsExistMessage(int index)
        {
            //LibraryFile file;
            for (int i = 0; i < containerMessage.Controls.Count; i++)
            {
                if (i != index)
                {
                    if ((containerMessage.Controls[i] as LibraryMessageItem).Item.Name == (containerMessage.Controls[index] as LibraryMessageItem).Item.Name)
                    {
                        (containerMessage.Controls[index] as LibraryMessageItem).IsValid = false;
                        return true;
                    }
                }
            }
            return false;
        }

        /// <summary>
        /// Function: Check all name is valid
        /// Author  : Jerry Xu
        /// Date    : 2008-11-6
        /// </summary>
        private void Check()
        {
            bool _fileFlag = false;
            bool _messageFlag = false;

            LibraryFile file;
            //All files name is valid
            foreach (Control control in containerFiles.Controls)
            {
                file = (control as LibraryFileItem).Item;
                if (!file.IsValid)
                {
                    sbtnSave.Enabled = false;
                    _fileFlag = false;
                    return;
                }
            }
            _fileFlag = true;            

            MessageInfo item;
            //All messages name is valid
            foreach (Control control in containerMessage.Controls)
            {
                item = (control as LibraryMessageItem).Item;
                if (LibraryGroup.Current.Messages.GetByName(item.Name) != null)
                {
                    sbtnSave.Enabled = false;
                    _messageFlag = false;
                    return;
                }
            }
            _messageFlag = true;
            
            //All names valid:save button is enable
            if (_fileFlag && _messageFlag)
                sbtnSave.Enabled = true;
        }            
        #endregion

        #region Events define
        /// <summary>
        /// Reinput name event
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e">LibraryImportRenameEventArgs</param>
        void fileItem_LibraryImportRename(object sender, ImportRenameEventArgs e)
        {
            //Config save button is disable
            sbtnSave.Enabled = false;
        }

        /// <summary>
        /// Check file name is valid,then config save button state
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        void fileItem_LibraryFileCheck(object sender, LibraryFileCheckEventArgs e)
        {
            int index = containerFiles.Controls.GetChildIndex(sender as LibraryFileItem);
            if (IsExistFile(index))
                return;
            Check();
        }

        /// <summary>
        /// Check message name is valid,then config save button state
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        void messageItem_LibraryMessageCheck(object sender, LibraryMessageCheckEventArgs e)
        {
            int index = containerMessage.Controls.GetChildIndex(sender as LibraryMessageItem);
            if (IsExistMessage(index))
                return;
            Check();
        }        

        private void sbtnSave_Click(object sender, EventArgs e)
        {
            _isRefresh = true;
            GenerateData();
            this.Close();
        }

        private void sbtnCancel_Click(object sender, EventArgs e)
        {
            _isRefresh = false;
            this.Close();
        }

        private void FilesRenameForm_FormClosed(object sender, FormClosedEventArgs e)
        {
            _isRefresh = false;
            this.Close();
        }
        #endregion        
    }
}
