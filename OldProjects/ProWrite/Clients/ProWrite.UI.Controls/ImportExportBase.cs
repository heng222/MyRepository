//---------------------------------------------------------------------
//
// File: ImportExportBase.cs
//      
// Description:
//      ImportExportBase class
//
// Author: Kevin 2009-3-27
//
// Modify History:
//      Jerry Xu 2009-4-1 Update method:MemoryLibraryItem OnImportOpen(string fileName)
//      Jerry Xu 2009-4-22 Add class:TimeSliceGroupImportExport
//                         Update class:ImportExportBase
//      Jerry Xu 2009-4-29 Update method:OnImportOpen(string fileName)
//      Jerry Xu 2009-4-30 Update method:ImportPlaylistRename(List<MessageFileItem> listFiles, List<MessageItem> listMessages, List<TimeSliceGroupItem> listTimesliceGroups, List<PlaylistItem> listPlaylists, PlaylistItem playlistItem)
//      Jerry Xu 2009-6-19 Update method:IImportExport Create(string fileName)
//
// Copyright (C) 2008 by Trans-Lux All rights reserved.
// 
//---------------------------------------------------------------------

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using ProWrite.Core;
using ProWrite.UI.Controls.Common;
using ProWrite.UI.Controls.Common.Messages;
using ProWrite.Entity.Library;
using ProWrite.Entity.Library.ImportExport;
using ProWrite.Entity.Library.Controller;
using System.IO;
using ProWrite.Resources;
using ProWrite.Entity.Shape;
using ProWrite.UI.Controls.Library;

namespace ProWrite.UI.Controls
{
    [ImportExportFactory] 
    public class ImportExportFactory : IImportExportFactory
    {
        public string Extension { get; private set; }
        public string ModuleName { get; private set; }
        public IImportExport Create(string fileName)
        {
            if (string.IsNullOrEmpty(fileName))
                return null;

            try
            {
                Extension = Path.GetExtension(fileName);
            }
            catch
            {
                return null;
            }

            DataGate.Load();
            switch (Extension)
            {
                case Constance.FileExtensionName.Message:
                    ModuleName = ModuleNames.Editor;
                    return new MessageImportExport();
                case Constance.FileExtensionName.TimeSliceGroup:
                    ModuleName = ModuleNames.Playlists;
                    return new TimeSliceGroupImportExport();
                case Constance.FileExtensionName.Playlist:
                    ModuleName = ModuleNames.Playlists;
                    return new PlaylistImportExport();
                case Constance.FileExtensionName.Scheduler:
                    ModuleName = ModuleNames.Scheduler;
                    return new SchedulerImportExport();
            }
            return null;
        }
    }

    public abstract class ImportExportBase:IImportExport
    {
        public abstract void OnImport(string fileName);
        public abstract void OnExport(string fileName, LibraryItem item);
        public abstract MemoryLibraryItem OnImportOpen(string fileName);
        public abstract void OnExportOpen(string fileName);

        private List<MessageFileItem> _listFiles;
        public List<MessageFileItem> ListFiles
        {
            get
            {
                if (_listFiles == null)
                    _listFiles = new List<MessageFileItem>();
                return _listFiles;
            }            
        }

        /// <summary>
        /// Function: Update file handle of import message files
        /// Author  : Jerry Xu
        /// Date    : 2008-12-29
        /// </summary>
        /// <param name="message">MessageInfo</param>
        /// <param name="files">List<FileItem></param>
        public void UpdateFiles(MessageInfo message, List<FileItem> files)
        {
            if (message == null || message.Items == null || message.Items.Length == 0 || files == null || files.Count == 0)
                return;

            string filepath = null;
            foreach (FileItem file in files)
            {
                filepath = IOHelper.GetLibraryFileName(file.Name, string.Empty, file.Type);
                file.Path = filepath;
            }
            foreach (ShapeLayer layer in message.Items)
            {
                if (layer.Shape != null && (((layer.Shape.Type == ShapeType.Image) && !string.IsNullOrEmpty((layer.Shape as ShapeImage).ImageUrl)) || ((layer.Shape.Type == ShapeType.Video) && !string.IsNullOrEmpty((layer.Shape as ShapeVideo).VideoUrl))))
                    SetHandleID(layer.Shape, files);
            }
        }

        /// <summary>
        /// Function: Update shape file handle 
        /// Author  : Jerry Xu
        /// Date    : 2008-12-29
        /// </summary>
        /// <param name="shape">ShapeBase</param>
        /// <param name="files">List<FileItem></param>
        private void SetHandleID(ShapeBase shape, List<FileItem> files)
        {
            ShapeImage image = null;
            ShapeVideo video = null;
            if (shape.Type == ShapeType.Image)
                image = shape as ShapeImage;
            if (shape.Type == ShapeType.Video)
                video = shape as ShapeVideo;
            foreach (FileItem item in files)
            {
                item.Id = Guid.NewGuid().ToString().Replace("-", "");
                if (!string.IsNullOrEmpty(item.Name))
                {
                    if (shape.Type == ShapeType.Image)
                    {
                        if (item.Name == Path.GetFileName(image.ImageUrl))
                        {
                            image.FileHandle = item.Id;
                            //libraryFileName = IOHelper.GetLibraryFileName(item.Name, string.Empty, LibraryType.Image);
                            image.ImageUrl = item.Path; //libraryFileName;
                        }
                    }
                    if (shape.Type == ShapeType.Video)
                    {
                        if (item.Name == Path.GetFileName(video.VideoUrl))
                        {
                            video.FileHandle = item.Id;
                            //libraryFileName = IOHelper.GetLibraryFileName(item.Name, string.Empty, LibraryType.Video);
                            video.VideoUrl = item.Path;// libraryFileName;
                        }
                    }
                }
            }

        }

        public void AddFiles(List<FileItem> files, List<MessageFileItem> listFiles)
        {
            if (files == null || files.Count == 0)
                return;
            MessageFileItem messageFile;
            if (_listFiles == null)
                _listFiles = new List<MessageFileItem>();
            foreach (FileItem file in files)
            {
                FileExistType type = IOHelper.IsExist(file.Path, "", file.Type);

                //add file
                if (type == FileExistType.No)
                {
                    string libraryFileName = IOHelper.GetLibraryFileName(file.Name, string.Empty, file.Type);
                    file.Path = libraryFileName;
                    //
                    messageFile = new MessageFileItem();
                    file.Path = libraryFileName;
                    messageFile.Item = file;
                    messageFile.OldItem = file.Copy();
                    messageFile.IsValid = true;
                    //
                    _listFiles.Add(messageFile);
                    //LibraryGroup.Current.AddFile(file);
                }
                else if (type == FileExistType.Yes)
                {
                    //rename file
                    messageFile = new MessageFileItem();
                    string libraryFileName = IOHelper.GetLibraryFileName(file.Name, string.Empty, file.Type);
                    file.Path = libraryFileName;
                    messageFile.Item = file;
                    messageFile.OldItem = file.Copy();
                    messageFile.IsValid = false;
                    //file.Id = 
                    listFiles.Add(messageFile);
                }
            }
        }

        public void SetLibraryFileLocalPath(MessageInfo message)
        {
            if (message == null || message.Items == null || message.Items.Length == 0)
                return;

            ShapeImage shapeImage = null;
            ShapeVideo shapeVideo = null;
            string filepath = null;
            foreach (ShapeLayer layer in message.Items)
            {
                if (layer.Shape != null && (layer.Shape.Type == ShapeType.Image || layer.Shape.Type == ShapeType.Video))
                {
                    if (layer.Shape.Type == ShapeType.Image)
                    {
                        shapeImage = layer.Shape as ShapeImage;
                        if (!string.IsNullOrEmpty(shapeImage.ImageUrl))
                        {
                            filepath = IOHelper.GetLibraryFileName(Path.GetFileName(shapeImage.ImageUrl), string.Empty, LibraryType.Image);
                            shapeImage.ImageUrl = filepath;
                            //shapeImage.FileHandle = 
                        }

                    }
                    if (layer.Shape.Type == ShapeType.Video)
                    {
                        shapeVideo = layer.Shape as ShapeVideo;
                        if (!string.IsNullOrEmpty(shapeVideo.VideoUrl))
                        {
                            filepath = IOHelper.GetLibraryFileName(Path.GetFileName(shapeVideo.VideoUrl), string.Empty, LibraryType.Image);
                            shapeVideo.VideoUrl = filepath;
                            //shapeImage.FileHandle = 
                        }
                    }
                }
            }
        }
    }

    public class MessageImportExport:ImportExportBase
    {
        private string _name;
        private MemoryLibraryItem _item;
        //List<MessageFileItem> _listFiles;
        MessageInfo _message;
 

        private bool _isSucceed;
        public override void OnImport(string fileName)
        {
            if (string.IsNullOrEmpty(fileName) || !File.Exists(fileName) || Path.GetExtension(fileName) != Constance.FileExtensionName.Message)
                return;
            Import(fileName);
        }

        public override void OnExport(string fileName,LibraryItem item)
        {
            if (string.IsNullOrEmpty(fileName) || item == null || item.Type != LibraryType.Message)
                return;
            MessageController.Save(fileName, item as MessageInfo);
        }

        public override MemoryLibraryItem OnImportOpen(string fileName)
        {
            ImportFile(fileName);

            LocalMessageBus.Send(null, new MenuMessage(new MenuCommand[]{
                new MenuCommand{ Command= MenuCommands.InsertMessage, Enabled = LibraryGroup.Current.Messages.Count > 0}
                , new MenuCommand{ Command =  MenuCommands.InsertTimeSlice,Enabled = LibraryGroup.Current.TimeSliceGroups.Count > 0}
                , new MenuCommand{ Command= MenuCommands.InsertPlaylist, Enabled = LibraryGroup.Current.Playlists.Count > 0}

                }));
            if (_isSucceed && !string.IsNullOrEmpty(_name))
                return LibraryGroup.Current.Messages.GetByName(_name);
            //else
            //    MsgBox.Error(Resource.GetFormatString(Resource.Strings.LibraryOpenFailure, new object[] { LibraryType.Message.ToString(), Path.GetFileNameWithoutExtension(fileName) }));

            return null;
        }

        public override void OnExportOpen(string fileName)
        {
            throw new NotImplementedException();
        }

        /// <summary>
        /// Function: Import file
        /// </summary>
        /// <param name="fileName">string</param>
        private void Import(string fileName)
        {            
            List<FileItem> images;
            List<FileItem> videos;
           // List<MessageInfo> messages;
            string itemName = Path.GetFileNameWithoutExtension(fileName);
            
            MessageInfo message;
            MessageWrapper messageWrapper = MessageController.Load(fileName);
            if (messageWrapper != null)
            {
                images = messageWrapper.Images;
                videos = messageWrapper.Videos;
                message = messageWrapper.Message;
                message.Id = Guid.NewGuid().ToString();
                message.Name = itemName;

                if ((images != null && images.Count > 0) || (videos != null && videos.Count > 0) || message != null)
                {
                    //_listFiles = new List<MessageFileItem>();                    
                    if (images != null && images.Count > 0)
                        UpdateFiles(message, images);
                    if (videos != null && videos.Count > 0)
                        UpdateFiles(message, videos);
                    ImportMessage(images, videos, message);
                }
            }
            else
                MsgBox.Error(Resource.GetFormatString(Resource.Strings.LibraryTreeImportFailure, new object[] { LibraryType.Message.ToString().ToLower() }));

            return;               
        }      

        private void ImportMessage(List<FileItem> images, List<FileItem> videos, MessageInfo messageInfo)
        {
            if ((images == null || images.Count == 0) && (videos == null || videos.Count == 0) && messageInfo == null)
                return;
            List<MessageFileItem> listFiles = new List<MessageFileItem>();
            List<MessageInfo> listMessages = new List<MessageInfo>();
            MessageInfo message = null;
            MessageItem messageItem = null;
            //bool isValid = false;
            //if (images != null && images.Count > 0)
            //{

            //MessageFileItem messageFile = null;

            AddFiles(images, listFiles);
            AddFiles(videos, listFiles);
            message = LibraryGroup.Current.Messages.GetByName(messageInfo.Name);
            messageItem = new MessageItem();
            messageItem.Item = messageInfo.Copy() as MessageInfo;
            if (message != null)
                messageItem.IsValid = false;
            else
                messageItem.IsValid = true;
            //Batch load file :rename file and message
            ImportMessageRename(listFiles, messageItem);
            //}
        }

        private void ImportMessageRename(List<MessageFileItem> listFiles, MessageItem messageItem)
        {

            if (messageItem == null || messageItem.Item == null)
                return;

            if ((listFiles != null && listFiles.Count > 0) || !messageItem.IsValid)
            {
                MessageFilesRenameForm frm = new MessageFilesRenameForm(listFiles, messageItem);
                frm.ShowModalDialog();
                if (frm.IsRefresh)
                {                   
                    ListFiles.AddRange(frm.Files);
                    _isSucceed = LibraryGroup.Current.ImportMessage(ListFiles, frm.Message.Item, ControlService.SignCombo.Current);
                    _name = frm.Message.Item.Name;                   
                }
            }
            else
            {
                if(ListFiles.Count>0)
                    _isSucceed = LibraryGroup.Current.ImportMessage(ListFiles, messageItem.Item, ControlService.SignCombo.Current);
                else
                    _isSucceed = LibraryGroup.Current.Messages.Add(messageItem.Item);
                _name = messageItem.Item.Name;
            }
        }        

        /// <summary>
        /// Function: Import file
        /// </summary>
        /// <param name="fileName">string</param>
        private void ImportFile(string fileName)
        {
            if (string.IsNullOrEmpty(fileName))
                return;
            List<FileItem> images;
            List<FileItem> videos;
            List<MessageInfo> messages;
            string itemName = Path.GetFileNameWithoutExtension(fileName);
            _name = itemName;

            MessageInfo message;
            MessageWrapper messageWrapper = MessageController.Load(fileName);
            if (messageWrapper != null)
            {
                images = messageWrapper.Images;
                videos = messageWrapper.Videos;
                message = messageWrapper.Message;
                message.Id = Guid.NewGuid().ToString();
                message.Name = itemName;

                if ((images != null && images.Count > 0) || (videos != null && videos.Count > 0) || message != null)
                {
                    if (images != null && images.Count > 0)
                        UpdateFiles(message, images);
                    if (videos != null && videos.Count > 0)
                        UpdateFiles(message, videos);
                    ImportMessage(images, videos, message);
                }
            }
            else
                MsgBox.Error(Resource.GetFormatString(Resource.Strings.LibraryTreeImportFailure, new object[] { LibraryType.Message.ToString().ToLower() }));

            return;
                
            
        }

        //private bool IsRename(List<MessageFileItem> listFiles, MessageItem messageItem)
        //{
        //    if ((listFiles == null || listFiles.Count == 0) && messageItem == null)
        //        return false;
            
        //}
    }

    public class TimeSliceGroupImportExport : ImportExportBase
    {
        private string _name;
        private MemoryLibraryItem _item;
        private bool _isSucceed;

        List<MessageItem> _listMessages;

        public override void OnImport(string fileName)
        {
            if (string.IsNullOrEmpty(fileName) || !File.Exists(fileName) || Path.GetExtension(fileName) != Constance.FileExtensionName.TimeSliceGroup)
                return;
            Import(fileName);
        }

        public override MemoryLibraryItem OnImportOpen(string fileName)
        {
            ImportFile(fileName);

            LocalMessageBus.Send(null, new MenuMessage(new MenuCommand[]{
                new MenuCommand{ Command= MenuCommands.InsertMessage, Enabled = LibraryGroup.Current.Messages.Count > 0}
                , new MenuCommand{ Command =  MenuCommands.InsertTimeSlice,Enabled = LibraryGroup.Current.TimeSliceGroups.Count > 0}
                , new MenuCommand{ Command= MenuCommands.InsertPlaylist, Enabled = LibraryGroup.Current.Playlists.Count > 0}

                }));
            if (_isSucceed && !string.IsNullOrEmpty(_name))
                return LibraryGroup.Current.TimeSliceGroups.GetByName(_name);
            //else
            //    MsgBox.Error(Resource.GetFormatString(Resource.Strings.LibraryOpenFailure, new object[] { LibraryType.Message.ToString(), Path.GetFileNameWithoutExtension(fileName) }));

            return null;
        }

        public override void OnExport(string fileName, LibraryItem item)
        {
            if (string.IsNullOrEmpty(fileName) || item == null || item.Type != LibraryType.TimeSliceGroup)
                return;
            TimeSliceGroupController.Save(fileName, item as TimeSliceGroupInfo);
        }

        public override void OnExportOpen(string fileName)
        {
            throw new NotImplementedException();
        }

        /// <summary>
        /// Function: Import file
        /// </summary>
        /// <param name="fileName">string</param>
        private void Import(string fileName)
        {
            List<FileItem> images;
            List<FileItem> videos;
            List<MessageInfo> messages;
            string itemName = Path.GetFileNameWithoutExtension(fileName);

            TimeSliceGroupInfo group;
            TimeSliceGroupWrapper groupWrapper = TimeSliceGroupController.Load(fileName);
            if (groupWrapper != null)
            {
                images = groupWrapper.Images;
                videos = groupWrapper.Videos;
                messages = groupWrapper.Messages;
                group = groupWrapper.Group;
                group.Id = Guid.NewGuid().ToString();
                group.Name = itemName;
                if ((images != null && images.Count > 0) || (videos != null && videos.Count > 0) || (messages != null && messages.Count > 0) || group != null)
                    ImportTimeSliceGroup(images, videos, messages, group);
            }
            else
                MsgBox.Error(Resource.GetFormatString(Resource.Strings.LibraryTreeImportFailure, new object[] { LibraryType.TimeSliceGroup.ToString().ToLower() }));
            return;
            
        }

        #region Import TimeSliceGroup
        private void ImportTimeSliceGroup(List<FileItem> images, List<FileItem> videos, List<MessageInfo> messages, TimeSliceGroupInfo groupInfo)
        {
            if ((images == null || images.Count == 0) && (videos == null || videos.Count == 0) && (messages == null || messages.Count == 0) && groupInfo == null)
                return;
            List<MessageFileItem> listFiles = new List<MessageFileItem>();
            List<MessageItem> listMessages = new List<MessageItem>();
            TimeSliceGroupInfo group = null;
            TimeSliceGroupItem groupItem = null;
            //bool isValid = false;
            //if (images != null && images.Count > 0)
            //{

            //MessageFileItem messageFile = null;

            AddFiles(images, listFiles);
            AddFiles(videos, listFiles);
            AddMessages(messages, listMessages);
            group = LibraryGroup.Current.TimeSliceGroups.GetByName(groupInfo.Name);
            groupItem = new TimeSliceGroupItem();
            groupItem.Item = groupInfo.Copy() as TimeSliceGroupInfo;
            groupItem.IsValid = false;
            if (group == null)
                groupItem.IsValid = true;
            //Batch load file :rename file and message
            ImportTimeSliceGroupRename(listFiles, listMessages, groupItem);
            //}
        }

        private void ImportTimeSliceGroupRename(List<MessageFileItem> listFiles, List<MessageItem> listMessages, TimeSliceGroupItem groupItem)
        {
            if (groupItem == null || groupItem.Item == null)
                return;
            if ((listFiles != null && listFiles.Count > 0) || (listMessages != null && listMessages.Count > 0) || !groupItem.IsValid)
            {
                TimeSlieceGroupRenameForm frm = new TimeSlieceGroupRenameForm(listFiles, listMessages, groupItem);
                frm.ShowModalDialog();
                if (frm.IsRefresh)
                {
                    ListFiles.AddRange(frm.Files);
                    if (_listMessages == null)
                        _listMessages = new List<MessageItem>();
                    _listMessages.AddRange(frm.Messages);                    
                    _isSucceed = LibraryGroup.Current.ImportTimeSliceGroup(ListFiles, _listMessages, frm.Group.Item, ControlService.SignCombo.Current);
                    _name = frm.Group.Item.Name;
                    LocalMessageBus.Send(this, new LibraryImportTimeSliceGroupMessage(frm.Group.Item.Name, frm.Group.Item.Type));
                }
            }
            else
            {
                if ((ListFiles.Count > 0) || (_listMessages != null && _listMessages.Count > 0))
                    _isSucceed = LibraryGroup.Current.ImportTimeSliceGroup(ListFiles, _listMessages, groupItem.Item, ControlService.SignCombo.Current);
                else
                    _isSucceed = LibraryGroup.Current.TimeSliceGroups.Add(groupItem.Item);
                _name = groupItem.Item.Name;

                LocalMessageBus.Send(this, new LibraryImportTimeSliceGroupMessage(groupItem.Item.Name, groupItem.Item.Type));
            }

        }
        #endregion        

        /// <summary>
        /// Function: Update file handle of import message files
        /// Author  : Jerry Xu
        /// Date    : 2008-12-29
        /// </summary>
        /// <param name="message">MessageInfo</param>
        /// <param name="files">List<FileItem></param>
        private void UpdateFilesOther(List<MessageInfo> messages, List<FileItem> files)
        {
            if (messages == null || messages.Count == 0 || files == null || files.Count == 0)
                return;

            foreach (MessageInfo message in messages)
            {
                UpdateFiles(message, files);
            }

        }

        #region Add Items
        private void AddMessages(List<MessageInfo> items, List<MessageItem> listItems)
        {
            MessageInfo memory;
            MessageItem memoryItem;
            if (_listMessages == null)
                _listMessages = new List<MessageItem>();
            foreach (MessageInfo item in items)
            {
                memory = LibraryGroup.Current.Messages.GetByName(item.Name);
                //SetLibraryFileLocalPath(item);
                if (memory == null)
                {
                    memoryItem = new MessageItem();
                    memoryItem.Item = item;
                    memoryItem.IsValid = true;
                    _listMessages.Add(memoryItem);
                    //LibraryGroup.Current.Messages.Add(item);
                }
                else
                {
                    memoryItem = new MessageItem();
                    memoryItem.Item = item;
                    memoryItem.IsValid = false;
                    listItems.Add(memoryItem);
                }

            }
        }        
        #endregion        

        /// <summary>
        /// Function: Import file
        /// </summary>
        /// <param name="fileName">string</param>
        private void ImportFile(string fileName)
        {
            if (string.IsNullOrEmpty(fileName))
                return;
            List<FileItem> images;
            List<FileItem> videos;
            List<MessageInfo> messages;
            string itemName = Path.GetFileNameWithoutExtension(fileName);

            TimeSliceGroupInfo group;
            TimeSliceGroupWrapper groupWrapper = TimeSliceGroupController.Load(fileName);
            if (groupWrapper != null)
            {
                images = groupWrapper.Images;
                videos = groupWrapper.Videos;
                messages = groupWrapper.Messages;
                group = groupWrapper.Group;
                group.Id = Guid.NewGuid().ToString();
                group.Name = itemName;
                if ((images != null && images.Count > 0) || (videos != null && videos.Count > 0) || (messages != null && messages.Count > 0) || group != null)
                    ImportTimeSliceGroup(images, videos, messages, group);
            }
            else
                MsgBox.Error(Resource.GetFormatString(Resource.Strings.LibraryTreeImportFailure, new object[] { LibraryType.TimeSliceGroup.ToString().ToLower() }));
            return;
        }        
    }

    public class PlaylistImportExport : ImportExportBase
    {
        private string _name;
        private MemoryLibraryItem _item;
        private bool _isSucceed;

        List<MessageItem> _listMessages;
        List<TimeSliceGroupItem> _listTimeSliceGroups;
        List<PlaylistItem> _listPlaylists;

        public override void OnImport(string fileName)
        {
            if (string.IsNullOrEmpty(fileName) || !File.Exists(fileName) || Path.GetExtension(fileName) != Constance.FileExtensionName.Playlist)
                return;
            Import(fileName);
        }

        public override void OnExport(string fileName, LibraryItem item)
        {
            if (string.IsNullOrEmpty(fileName) || item == null || item.Type != LibraryType.Playlist)
                return;
            PlaylistController.Save(fileName, item as PlaylistInfo);
        }

        public override MemoryLibraryItem OnImportOpen(string fileName)
        {
            ImportFile(fileName);

            LocalMessageBus.Send(null, new MenuMessage(new MenuCommand[]{
                new MenuCommand{ Command= MenuCommands.InsertMessage, Enabled = LibraryGroup.Current.Messages.Count > 0}
                , new MenuCommand{ Command =  MenuCommands.InsertTimeSlice,Enabled = LibraryGroup.Current.TimeSliceGroups.Count > 0}
                , new MenuCommand{ Command= MenuCommands.InsertPlaylist, Enabled = LibraryGroup.Current.Playlists.Count > 0}

                }));
            if (_isSucceed && !string.IsNullOrEmpty(_name))
                return LibraryGroup.Current.Playlists.GetByName(_name);
            //else
            //    MsgBox.Error(Resource.GetFormatString(Resource.Strings.LibraryOpenFailure, new object[] { LibraryType.Playlist.ToString(), Path.GetFileNameWithoutExtension(fileName) }));

            return null;
        }

        public override void OnExportOpen(string fileName)
        {
            throw new NotImplementedException();
        }

        /// <summary>
        /// Function: Import file
        /// </summary>
        /// <param name="fileName">string</param>
        private void Import(string fileName)
        {
            List<FileItem> images;
            List<FileItem> videos;
            List<MessageInfo> messages;
            PlaylistInfo playlist;
            List<TimeSliceGroupInfo> timesliceGroups;
            List<PlaylistInfo> playlists;
            string itemName = Path.GetFileNameWithoutExtension(fileName);

            PlaylistWrapper playlistWrapper = PlaylistController.Load(fileName);
            if (playlistWrapper != null)
            {
                images = playlistWrapper.Images;
                videos = playlistWrapper.Videos;
                messages = playlistWrapper.Messages;
                timesliceGroups = playlistWrapper.TimeSliceGroups;
                playlists = playlistWrapper.Playlists;

                playlist = playlistWrapper.Playlist;
                playlist.Id = Guid.NewGuid().ToString();
                playlist.Name = itemName;

                if ((images != null && images.Count > 0) || (videos != null && videos.Count > 0) || (messages != null && messages.Count > 0) || (timesliceGroups != null && timesliceGroups.Count > 0) || (playlists != null && playlists.Count > 0) || playlist != null)
                {
                    if (images != null && images.Count > 0)
                        UpdateFilesOther(messages, images);
                    if (videos != null && videos.Count > 0)
                        UpdateFilesOther(messages, videos);
                    //if (playlists != null)
                    //{
                    //    playlists.Add(playlist);
                    //}
                    ImportPlaylist(images, videos, messages, timesliceGroups, playlists, playlist);
                }
            }
            else
                MsgBox.Error(Resource.GetFormatString(Resource.Strings.LibraryTreeImportFailure, new object[] { LibraryType.Playlist.ToString().ToLower() }));
            return;
        }

        /// <summary>
        /// Function: Update file handle of import message files
        /// Author  : Jerry Xu
        /// Date    : 2008-12-29
        /// </summary>
        /// <param name="message">MessageInfo</param>
        /// <param name="files">List<FileItem></param>
        private void UpdateFilesOther(List<MessageInfo> messages, List<FileItem> files)
        {
            if (messages == null || messages.Count == 0 || files == null || files.Count == 0)
                return;

            foreach (MessageInfo message in messages)
            {
                UpdateFiles(message, files);
            }
        }

        #region Import Playlist
        private void ImportPlaylist(List<FileItem> images, List<FileItem> videos, List<MessageInfo> messages, List<TimeSliceGroupInfo> timesliceGroups, List<PlaylistInfo> playlists, PlaylistInfo playlistInfo)
        {
            if ((images == null || images.Count == 0) && (videos == null || videos.Count == 0) && (messages == null || messages.Count == 0) && (timesliceGroups == null || timesliceGroups.Count == 0) && (playlists == null || playlists.Count == 0) && playlistInfo == null)
                return;
            List<MessageFileItem> listFiles = new List<MessageFileItem>();
            List<MessageItem> listMessages = new List<MessageItem>();
            List<TimeSliceGroupItem> listTimeSliceGroups = new List<TimeSliceGroupItem>();
            List<PlaylistItem> listPlaylists = new List<PlaylistItem>();

            PlaylistInfo playlist = null;
            PlaylistItem playlistItem = null;
            bool isValid = false;
            //if (images != null && images.Count > 0)
            //{

            MessageFileItem messageFile = null;

            AddFiles(images, listFiles);
            AddFiles(videos, listFiles);
            AddMessages(messages, listMessages);
            AddTimeSliceGroups(timesliceGroups, listTimeSliceGroups);
            AddPlaylists(playlists, listPlaylists);

            playlist = LibraryGroup.Current.Playlists.GetByName(playlistInfo.Name);
            playlistItem = new PlaylistItem();
            playlistItem.Item = playlistInfo.Copy() as PlaylistInfo;
            playlistItem.IsValid = false;
            if (playlist == null)
                playlistItem.IsValid = true;
            //Batch load file :rename file and message
            ImportPlaylistRename(listFiles, listMessages, listTimeSliceGroups, listPlaylists, playlistItem);
            //}
        }

        private void ImportPlaylistRename(List<MessageFileItem> listFiles, List<MessageItem> listMessages, List<TimeSliceGroupItem> listTimesliceGroups, List<PlaylistItem> listPlaylists, PlaylistItem playlistItem)
        {
            if (playlistItem == null || playlistItem.Item == null)
                return;
            if ((listFiles != null && listFiles.Count > 0) || (listMessages != null && listMessages.Count > 0) || (listTimesliceGroups != null && listTimesliceGroups.Count > 0) || (listPlaylists != null && listPlaylists.Count > 0) || !playlistItem.IsValid)
            {
                //Add playlistItem in listPlaylists

                PlaylistRenameForm frm = new PlaylistRenameForm(listFiles, listMessages,listTimesliceGroups,listPlaylists,playlistItem);
                frm.ShowModalDialog();
                if (frm.IsRefresh)
                {
                    ListFiles.AddRange(frm.Files);
                    if (_listMessages == null)
                        _listMessages = new List<MessageItem>();
                    _listMessages.AddRange(frm.Messages);
                    if (_listTimeSliceGroups == null)
                        _listTimeSliceGroups = new List<TimeSliceGroupItem>();
                    if (_listPlaylists == null)
                        _listPlaylists = new List<PlaylistItem>();
                    _listTimeSliceGroups.AddRange(frm.TimeSliceGroups);
                    _listPlaylists.AddRange(frm.Playlists);
                    _isSucceed = LibraryGroup.Current.ImportPlaylist(ListFiles, _listMessages, _listTimeSliceGroups, _listPlaylists, frm.PlaylistItem, ControlService.SignCombo.Current);
                    _name = frm.PlaylistItem.Item.Name;
                    if(_listTimeSliceGroups!=null && _listTimeSliceGroups.Count>0)
                        LocalMessageBus.Send(this, new LibraryImportTimeSliceGroupMessage(null, LibraryType.TimeSliceGroup));
                }
            }
            else
            {
                if(ListFiles.Count>0 || (_listMessages!=null && _listMessages.Count>0) || (_listTimeSliceGroups!=null && _listTimeSliceGroups.Count>0) || (_listPlaylists!=null && _listPlaylists.Count>0))
                    _isSucceed = LibraryGroup.Current.ImportPlaylist(ListFiles, _listMessages, _listTimeSliceGroups, _listPlaylists, playlistItem, ControlService.SignCombo.Current);
                else
                    _isSucceed = LibraryGroup.Current.Playlists.Add(playlistItem.Item);
                _name = playlistItem.Item.Name;
                if (_listTimeSliceGroups != null && _listTimeSliceGroups.Count > 0)
                    LocalMessageBus.Send(this, new LibraryImportTimeSliceGroupMessage(null, LibraryType.TimeSliceGroup));
                //LocalMessageBus.Send(this, new LibraryImportTimeSliceGroupMessage(playlistItem.Item.Name, playlistItem.Item.Type));
            }
        }
        #endregion

        #region Add Items
        private void AddMessages(List<MessageInfo> items, List<MessageItem> listItems)
        {
            MessageInfo memory;
            MessageItem memoryItem;
            if (_listMessages == null)
                _listMessages = new List<MessageItem>();
            foreach (MessageInfo item in items)
            {
                memory = LibraryGroup.Current.Messages.GetByName(item.Name);
                //SetLibraryFileLocalPath(item);
                if (memory == null)
                {
                    memoryItem = new MessageItem();
                    memoryItem.Item = item;
                    memoryItem.IsValid = true;
                    _listMessages.Add(memoryItem);
                    //LibraryGroup.Current.Messages.Add(item);
                }
                else
                {
                    memoryItem = new MessageItem();
                    memoryItem.Item = item;
                    memoryItem.IsValid = false;
                    listItems.Add(memoryItem);
                }

            }
        }      

        private void AddTimeSliceGroups(List<TimeSliceGroupInfo> items, List<TimeSliceGroupItem> listItems)
        {
            TimeSliceGroupInfo memory;
            TimeSliceGroupItem memoryItem;
            if (_listTimeSliceGroups == null)
                _listTimeSliceGroups = new List<TimeSliceGroupItem>();
            foreach (TimeSliceGroupInfo item in items)
            {
                memory = LibraryGroup.Current.TimeSliceGroups.GetByName(item.Name);
                //SetLibraryFileLocalPath(item);
                if (memory == null)
                {
                    memoryItem = new TimeSliceGroupItem();
                    memoryItem.Item = item;
                    memoryItem.IsValid = true;
                    _listTimeSliceGroups.Add(memoryItem);
                    //listItems.Add(memoryItem);
                    //LibraryGroup.Current.TimeSliceGroups.Add(item);
                }
                else
                {
                    memoryItem = new TimeSliceGroupItem();
                    memoryItem.Item = item;
                    memoryItem.IsValid = false;
                    listItems.Add(memoryItem);
                }

            }
        }
        private void AddPlaylists(List<PlaylistInfo> items, List<PlaylistItem> listItems)
        {
            PlaylistInfo memory;
            PlaylistItem memoryItem;
            if (_listPlaylists == null)
                _listPlaylists = new List<PlaylistItem>();
            foreach (PlaylistInfo item in items)
            {
                memory = LibraryGroup.Current.Playlists.GetByName(item.Name);
                //SetLibraryFileLocalPath(item);
                if (memory == null)
                {
                    memoryItem = new PlaylistItem();
                    memoryItem.Item = item;
                    memoryItem.IsValid = true;
                    _listPlaylists.Add(memoryItem);
                    //LibraryGroup.Current.Playlists.Add(item);
                }
                else
                {
                    memoryItem = new PlaylistItem();
                    memoryItem.Item = item;
                    memoryItem.IsValid = false;
                    listItems.Add(memoryItem);
                }

            }
        }
        #endregion

        /// <summary>
        /// Function: Import file
        /// </summary>
        /// <param name="fileName">string</param>
        private void ImportFile(string fileName)
        {
            List<FileItem> images;
            List<FileItem> videos;
            List<MessageInfo> messages;
            PlaylistInfo playlist;
            List<TimeSliceGroupInfo> timesliceGroups;
            List<PlaylistInfo> playlists;
            string itemName = Path.GetFileNameWithoutExtension(fileName);

            PlaylistWrapper playlistWrapper = PlaylistController.Load(fileName);
            if (playlistWrapper != null)
            {
                images = playlistWrapper.Images;
                videos = playlistWrapper.Videos;
                messages = playlistWrapper.Messages;
                timesliceGroups = playlistWrapper.TimeSliceGroups;
                playlists = playlistWrapper.Playlists;

                playlist = playlistWrapper.Playlist;
                playlist.Id = Guid.NewGuid().ToString();
                playlist.Name = itemName;

                if ((images != null && images.Count > 0) || (videos != null && videos.Count > 0) || (messages != null && messages.Count > 0) || (timesliceGroups != null && timesliceGroups.Count > 0) || (playlists != null && playlists.Count > 0) || playlist != null)
                {
                    if (images != null && images.Count > 0)
                        UpdateFilesOther(messages, images);
                    if (videos != null && videos.Count > 0)
                        UpdateFilesOther(messages, videos);
                    //if (playlists != null)
                    //{
                    //    playlists.Add(playlist);
                    //}
                    ImportPlaylist(images, videos, messages, timesliceGroups, playlists, playlist);
                }
            }
            else
                MsgBox.Error(Resource.GetFormatString(Resource.Strings.LibraryTreeImportFailure, new object[] { LibraryType.Playlist.ToString().ToLower() }));
            return;
        }        
    }

    public class SchedulerImportExport : ImportExportBase
    {

        public override void OnImport(string fileName)
        {
            if (string.IsNullOrEmpty(fileName) || !File.Exists(fileName) || Path.GetExtension(fileName) != Constance.FileExtensionName.Scheduler)
                return;
            //Import(fileName);
        }

        public override void OnExport(string fileName, LibraryItem item)
        {
            if (string.IsNullOrEmpty(fileName) || item == null || item.Type != LibraryType.Schedule)
                return;
            //ScheduleController.Save(fileName, item as SchedulerInfo);
        }

        public override MemoryLibraryItem OnImportOpen(string fileName)
        {
            throw new NotImplementedException();
        }

        public override void OnExportOpen(string fileName)
        {
            throw new NotImplementedException();
        }
    }


}
