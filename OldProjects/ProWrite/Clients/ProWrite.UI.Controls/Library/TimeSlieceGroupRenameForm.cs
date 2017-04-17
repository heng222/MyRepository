//---------------------------------------------------------------------
//
// File: TimeSlieceGroupRenameForm.cs
//      
// Description:
//      TimeSliceGroupInfo import rename form
//
// Author: Jerry Xu 2008-11-17
//
// Modify History:
//      Jerry Xu 2009-4-20 Update method:CreateFormElements()
//      Jerry Xu 2009-4-20 Add methods:UpdateFilesOther(),UpdateFiles(MessageInfo message),SetUrl(ShapeBase shape),IsExistFile(int index)
//      Jerry Xu 2009-4-20 Update event:fileItem_FileCheck(object sender, TimeSliceGroupFileCheckEventArgs e)
//      Jerry Xu 2009-6-4  Insert method:IsExistMessage(int index)
//      Jerry Xu 2009-6-4  Update event:messageItem_MessageCheck(object sender, ImportCheckEventArgs e)
//      Jerry Xu 2009-6-4  Update method:IsExistFile(int index)
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
    public partial class TimeSlieceGroupRenameForm : XtraForm
    {
        #region Variants define
        private bool _timeSliceGroupFlag = false;
        private bool _isValid = false;

        private List<MessageFileItem> _files;
        public List<MessageFileItem> Files
        {
            get { return _files; }
        }
        private List<MessageItem> _messages;
        public List<MessageItem> Messages
        {
            get { return _messages; }
        }
        private TimeSliceGroupItem _group;
        public TimeSliceGroupItem Group
        {
            get { return _group; }
        }
        #endregion

        public TimeSlieceGroupRenameForm(List<MessageFileItem> files, List<MessageItem> messages, TimeSliceGroupItem groupItem)
        {
            InitializeComponent();
            _files = files;
            _messages = messages;
            _group = groupItem;
            if (!DesignMode)
                Init();
        }
        #region Properties define
        private bool _isRefresh = false;
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

        private void InitResource()
        {
            this.Text = Resource.GetString(Resource.Strings.LibraryLibraryFileItemTitle);
            sbtnSave.Text = Resource.GetString(Resource.Strings.Save);
            sbtnCancel.Text = Resource.GetString(Resource.Strings.Cancel);
            sbtnSave.Image = Resource.GetImage(Resource.Images.Save16);
            sbtnCancel.Image = Resource.GetImage(Resource.Images.Cancel16);
            sbtnSave.Enabled = false;
        }

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
            _messages = new List<MessageItem>();
            if (containerMessage.Controls.Count > 0)
            {
                foreach (Control control in containerMessage.Controls)
                {
                    _messages.Add((control as ImportMessageItemControl).Item);
                }
            }

            if (containerTimeSliceGroup.Controls.Count > 0)
            {
                foreach (Control control in containerTimeSliceGroup.Controls)
                {
                    _group = (control as ImportTimeSliceGroupItemControl).Item;
                }
            }
        }
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
                    containerFiles.Height = containerFiles.Height + fileItem.Height;
                    containerFiles.Controls.Add(fileItem);
                }
            }

            ImportMessageItemControl messageItem;
            if (_messages != null && _messages.Count > 0)
            {
                foreach (MessageItem item in _messages)
                {
                    messageItem = new ImportMessageItemControl(item);
                    messageItem.Dock = DockStyle.Top;
                    messageItem.MessageCheck += new EventHandler<ImportCheckEventArgs>(messageItem_MessageCheck);
                    messageItem.ImportRename += new EventHandler<ImportRenameEventArgs>(fileItem_LibraryImportRename);
                    containerMessage.Height = containerMessage.Height + messageItem.Height;
                    containerMessage.Controls.Add(messageItem);
                }
            }            

            ImportTimeSliceGroupItemControl groupItem;
            if (!_group.IsValid)
            {
                groupItem = new ImportTimeSliceGroupItemControl(_group);
                groupItem.Dock = DockStyle.Top;
                groupItem.TimeSliceGroupCheck += new EventHandler<ImportCheckEventArgs>(groupItem_TimeSliceGroupCheck);
                groupItem.ImportRename += new EventHandler<ImportRenameEventArgs>(fileItem_LibraryImportRename);
                containerTimeSliceGroup.Height = containerTimeSliceGroup.Height + groupItem.Height;
                containerTimeSliceGroup.Controls.Add(groupItem);
            }

            //Expand group files and messages and timeSliceGroup
            groupFiles.Expanded = true;
            groupMessage.Expanded = true;
            groupTimeSliceGroup.Expanded = true;
        }

        /// <summary>
        /// Function: Update file url of import message files
        /// Author  : Jerry Xu
        /// Date    : 2009-4-20
        /// </summary>
        private void UpdateFilesOther()
        {
            if (_group == null || _group.Item == null || _group.Item.Items == null || _group.Item.Items.Length == 0 || _files == null || _files.Count == 0)
                return;

            foreach (MessageAdapterInfo message in _group.Item.Items)
            {
                if(message!=null && message.Target!=null)
                    UpdateFiles(message.Target as MessageInfo);
            }    
        }


        /// <summary>
        /// Function: Update file url of import message files
        /// Author  : Jerry Xu
        /// Date    : 2009-4-20
        /// </summary>
        private void UpdateFiles(MessageInfo message)
        {
            if (message == null || message.Items == null || message.Items.Length == 0 || _files == null || _files.Count == 0)
                return;
            foreach (ShapeLayer layer in message.Items)
            {
                if (layer.Shape != null && (layer.Shape.Type == ShapeType.Image || layer.Shape.Type == ShapeType.Video))
                    SetUrl(layer.Shape);
            }
        }

        /// <summary>
        /// Function: Update shape file url 
        /// Author  : Jerry Xu
        /// Date    : 2009-4-20
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
                if (item.OldItem != null)
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

        private void Check()
        {
            MessageFileItem item;
            if (containerFiles.Controls != null && containerFiles.Controls.Count > 0)
            {
                foreach (Control control in containerFiles.Controls)
                {
                    item = (control as ImportFileItemControl).Item;
                    if (!item.IsValid)
                    {
                        sbtnSave.Enabled = false;
                        return;
                    }
                }
            }

            MessageItem messageItem;
            if (containerMessage.Controls != null && containerMessage.Controls.Count > 0)
            {
                foreach (Control control in containerMessage.Controls)
                {
                    messageItem = (control as ImportMessageItemControl).Item;
                    if (!messageItem.IsValid)
                    {
                        sbtnSave.Enabled = false;
                        return;
                    }
                }
            }

            if (containerTimeSliceGroup.Controls.Count == 0)
                _timeSliceGroupFlag = true;
            else
            {
                _group.IsValid = (containerTimeSliceGroup.Controls[0] as ImportTimeSliceGroupItemControl).Item.IsValid;
                if (!_group.IsValid)
                {
                    sbtnSave.Enabled = false;
                    return;
                }
            }

            sbtnSave.Enabled = true;
        }

        /// <summary>
        /// Function: Check input file name is exist in needed rename file list.
        /// Author  : Jerry Xu
        /// Date    : 2009-4-20
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

        /// <summary>
        /// Function: Check input message name is exist in needed rename message list.
        /// Author  : Jerry Xu
        /// Date    : 2009-6-4
        /// </summary>
        /// <param name="index">Current message control index</param>
        /// <returns>bool</returns>
        private bool IsExistMessage(int index)
        {            
            for (int i = 0; i < containerMessage.Controls.Count; i++)
            {
                if (i != index)
                {
                    if ((containerMessage.Controls[i] as ImportMessageItemControl).Item.Item.Name == (containerMessage.Controls[index] as ImportMessageItemControl).Item.Item.Name)
                    {
                        (containerMessage.Controls[index] as ImportMessageItemControl).Item.IsValid = false;
                        MsgBox.Error(Resource.GetFormatString(Resource.Strings.LibraryImportNameExistInfo, new object[] { LibraryType.Message.ToString(), (containerMessage.Controls[index] as ImportMessageItemControl).Item.Item.Name }));
                        return true;
                    }
                }
            }
            return false;
        }      

        void fileItem_LibraryImportRename(object sender, ImportRenameEventArgs e)
        {
            sbtnSave.Enabled = false;
        }

        void groupItem_TimeSliceGroupCheck(object sender, ImportCheckEventArgs e)
        {
            Check();
        }

        void messageItem_MessageCheck(object sender, ImportCheckEventArgs e)
        {
            int index = containerMessage.Controls.GetChildIndex(sender as ImportMessageItemControl);
            if (IsExistMessage(index))
                return;
            Check();
        }        

        void fileItem_FileCheck(object sender, ImportCheckEventArgs e)
        {
            int index = containerFiles.Controls.GetChildIndex(sender as ImportFileItemControl);
            if (IsExistFile(index))
                return;
            Check();
        }        
        #endregion

        #region Events define
        private void sbtnSave_Click(object sender, EventArgs e)
        {
            _isRefresh = true;
            GenerateData();
            UpdateFilesOther();
            this.Close();
        }

        private void sbtnCancel_Click(object sender, EventArgs e)
        {
            _isRefresh = false;
            this.Close();
        }
        #endregion

        private void TimeSlieceGroupRenameForm_FormClosed(object sender, FormClosedEventArgs e)
        {
            _isRefresh = false;
            this.Close();
        }
    }
}