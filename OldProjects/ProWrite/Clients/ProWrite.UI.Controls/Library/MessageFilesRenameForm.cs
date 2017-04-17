//---------------------------------------------------------------------
//
// File: MessageFilesRenameForm.cs
//      
// Description:
//      Import message rename form class
//
// Author: Jerry Xu 2008-11-17
//
// Modify History:
//      Jerry Xu 2008-12-29 Import message:File handle
//                          Add new method:UpdateFiles(),SetUrl(ShapeBase shape)
//                          Update event:sbtnSave_Click(object sender, EventArgs e)
//      Jerry Xu 2009-1-12  Update method:InitResource()
//      Jerry Xu 2009-4-20  Update method:
//      Jerry Xu 2009-6-4   Update method:IsExistFile(int index)
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
using ProWrite.Entity.Library.ImportExport;
using ProWrite.Entity.Shape;
using System.IO;
using ProWrite.UI.Controls.Common;

namespace ProWrite.UI.Controls.Library
{
    public partial class MessageFilesRenameForm : XtraForm
    {
        #region Variants define
        private List<MessageFileItem> _files;
        /// <summary>
        /// Rename files
        /// </summary>
        public List<MessageFileItem> Files
        {
            get { return _files; }
        }

        private MessageItem _message;
        /// <summary>
        /// Rename MessageInfos
        /// </summary>
        public MessageItem Message
        {
            get { return _message; }
        }
        #endregion

        public MessageFilesRenameForm(List<MessageFileItem> files, MessageItem messageItem)
        {
            InitializeComponent();

            if (!DesignMode)
            {
                _files = files;
                _message = messageItem;
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
        /// Date    : 2008-11-17
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
        }

        /// <summary>
        /// Function: Generate last data
        /// Author  : Jerry Xu
        /// Date    : 2008-11-17
        /// </summary>
        private void GenerateData()
        {
            _files = new List<MessageFileItem>();
            if (containerFiles.Controls.Count > 0)
            {
                foreach (Control control in containerFiles.Controls)
                {
                    _files.Add((control as ImportFileItemControl).Item);
                }
            }
            if (containerMessage.Controls.Count > 0)
            {
                foreach (Control control in containerMessage.Controls)
                {
                    _message = (control as ImportMessageItemControl).Item;
                }
            }

        }

        /// <summary>
        /// Function: Create form elements
        /// Author  : Jerry Xu
        /// Date    : 2008-11-17
        /// </summary>
        private void CreateFormElements()
        {
            ImportFileItemControl fileItem;
            if (_files != null && _files.Count > 0)
            {
                foreach (MessageFileItem item in _files)
                {
                    fileItem = new ImportFileItemControl(item);
                    fileItem.Dock = DockStyle.Top;
                    fileItem.FileCheck += new EventHandler<ImportCheckEventArgs>(fileItem_FileCheck);
                    fileItem.ImportRename += new EventHandler<ImportRenameEventArgs>(fileItem_LibraryImportRename);
                    //Config container height
                    containerFiles.Height = containerFiles.Height + fileItem.Height;
                    containerFiles.Controls.Add(fileItem);
                }
            }

            ImportMessageItemControl messageItem;
            if (!_message.IsValid)
            {
                messageItem = new ImportMessageItemControl(_message);
                messageItem.Dock = DockStyle.Top;
                messageItem.MessageCheck += new EventHandler<ImportCheckEventArgs>(messageItem_MessageCheck);
                messageItem.ImportRename += new EventHandler<ImportRenameEventArgs>(fileItem_LibraryImportRename);
                //Config container height
                containerMessage.Height = containerMessage.Height + messageItem.Height;
                containerMessage.Controls.Add(messageItem);
            }
            //Expand group files and message
            groupFiles.Expanded = true;
            groupMessage.Expanded = true;
        }

        /// <summary>
        /// Function: Update file url of import message files
        /// Author  : Jerry Xu
        /// Date    : 2008-12-29
        /// </summary>
        private void UpdateFiles()
        {
            if (_message == null || _message.Item == null || _message.Item.Items == null || _message.Item.Items.Length == 0 || _files == null || _files.Count == 0)
                return;
            foreach (ShapeLayer layer in _message.Item.Items)
            {
                if (layer.Shape != null && (layer.Shape.Type == ShapeType.Image || layer.Shape.Type == ShapeType.Video))
                    SetUrl(layer.Shape);
            }
        }

        /// <summary>
        /// Function: Update shape file url 
        /// Author  : Jerry Xu
        /// Date    : 2008-12-29
        /// </summary>
        /// <param name="shape">ShapeBase</param>
        private void SetUrl(ShapeBase shape)
        {
            ShapeImage image = null;
            ShapeVideo video = null;
            if (shape.Type == ShapeType.Image)
                image = shape as ShapeImage;
            if (shape.Type == ShapeType.Video)
                video = shape as ShapeVideo;
            foreach (MessageFileItem item in _files)
            {
                if(item.OldItem!=null)
                {
                    if (shape.Type == ShapeType.Image)
                    {
                        if (item.OldItem.Name == Path.GetFileName(image.ImageUrl))

                            image.ImageUrl = item.Item.Path;
                    }
                    if (shape.Type == ShapeType.Video)
                    {
                        if (item.OldItem.Name == Path.GetFileName(video.VideoUrl))

                            video.VideoUrl = item.Item.Path;
                    }
                }
            }
            
        }
        
        /// <summary>
        /// Function: Check all name is valid
        /// Author  : Jerry Xu
        /// Date    : 2008-11-17
        /// </summary>
        private void Check()
        {
            bool _fileFlag = false;
            bool _messageFlag = false;

            MessageFileItem file;
            if (containerFiles.Controls != null && containerFiles.Controls.Count > 0)
            {
                foreach (Control control in containerFiles.Controls)
                {
                    file = (control as ImportFileItemControl).Item;
                    if (!file.IsValid)
                    {
                        sbtnSave.Enabled = false;
                        _fileFlag = false;
                        return;
                    }
                }
            }
            _fileFlag = true;

            MessageItem item;
            foreach (Control control in containerMessage.Controls)
            {
                item = (control as ImportMessageItemControl).Item;
                if (LibraryGroup.Current.Messages.GetByName(item.Item.Name) != null)
                {
                    sbtnSave.Enabled = false;
                    _messageFlag = false;
                    return;
                }
            }
            _messageFlag = true;

            if (_fileFlag && _messageFlag)
                sbtnSave.Enabled = true;
        }

        /// <summary>
        /// Function: Check input file name is exist in needed rename file list.
        /// Author  : Jerry Xu
        /// Date    : 2008-11-17
        /// </summary>
        /// <param name="index">Current file control index</param>
        /// <returns>bool</returns>
        private bool IsExistFile(int index)
        {
            //LibraryFile file;
            for (int i = 0; i < containerFiles.Controls.Count; i++)
            {
                if (i != index)
                {
                    if ((containerFiles.Controls[i] as ImportFileItemControl).Item.Item.Name == (containerFiles.Controls[index] as ImportFileItemControl).Item.Item.Name)
                    {
                        (containerFiles.Controls[index] as ImportFileItemControl).IsValid = false;
                        MsgBox.Error(Resource.GetFormatString(Resource.Strings.LibraryImportNameExistInfo, new object[] { LibraryType.Image.ToString(), Path.GetFileNameWithoutExtension((containerFiles.Controls[index] as ImportFileItemControl).Item.Item.Path) }));
                        return true;
                    }
                }
            }
            return false;
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
            sbtnSave.Enabled = false;
        }

        /// <summary>
        /// Check file name is valid,then config save button state
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        void fileItem_FileCheck(object sender,ImportCheckEventArgs e)
        {
            int index = containerFiles.Controls.GetChildIndex(sender as ImportFileItemControl);
            if (IsExistFile(index))
                return;
            Check();
        }

        /// <summary>
        /// Check message name is valid,then config save button state
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        void messageItem_MessageCheck(object sender, ImportCheckEventArgs e)
        {
            Check();
        }

        private void sbtnSave_Click(object sender, EventArgs e)
        {
            _isRefresh = true;
            GenerateData();
            UpdateFiles();
            this.Close();
        }

        private void sbtnCancel_Click(object sender, EventArgs e)
        {
            _isRefresh = false;
            this.Close();
        }

        private void MessageFilesRenameForm_FormClosed(object sender, FormClosedEventArgs e)
        {
            _isRefresh = false;
            this.Close();
        }
        #endregion
    }
}