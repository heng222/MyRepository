//---------------------------------------------------------------------
//
// File: LibraryGroup.cs
//
// Description:
// The class of LibraryGroup
//
// Author: Louis
//
// Date:2008-7-04
//
// Modify History:
//      Jerry Xu 2007-7-7 Add the property of TimeSliceGroups.
//      Jerry Xu 2007-7-8 Add some methods:DeletePlaylist,UpdatePlaylist
//      Jerry Xu 2008-7-13 Add the method:Update,UpdateTimeSliceGroup,UpdateMessage
//      Kevin 2008-7-18 fix a bug for update message
//      Jerry Xu 2008-12-25 Import gif file:AddFile(string file, string libraryFile, string fileType, int length,SignInfo sign) 
//      Jerry Xu 2009-1-15 Add method:LockScheduler(ILockLibraryItem locker, bool isLock)
//      Jerry Xu 2009-1-15 Update method:LockLibrary(ILockLibraryItem locker, bool isLock)
//      Jerry Xu 2009-1-21 Update method:CanDeleteLibrary(LibraryItem lib)
//      Jerry Xu 2009-3-23 Add methods:BatchLoadFile(List<LibraryFile> listFiles, List<MessageInfo> listMessages, List<MessageReplaceItem> listReplaceMessages ,List<int> listLengths, SignInfo sign),AddFileNoSaveMessage(string file, string libraryFile, string fileType, int length, SignInfo sign)
//      Jerry Xu 2009-3-31 Update method:BatchLoadFile(List<LibraryFile> listFiles, List<MessageInfo> listMessages, List<MessageReplaceItem> listReplaceMessages ,List<int> listLengths, SignInfo sign)
//      Jerry Xu 2009-4-2  Update method:BatchLoadFile(List<LibraryFile> listFiles, List<MessageInfo> listMessages, List<MessageReplaceItem> listReplaceMessages ,List<int> listLengths, SignInfo sign)
//      Jerry Xu 2009-4-22 Update method:ImportTimeSliceGroup(List<MessageFileItem> listFiles, List<MessageItem> listMessages, TimeSliceGroupInfo group, SignInfo sign)
//      Jerry Xu 2009-4-23 Add method:ImportPlaylist(List<MessageFileItem> listFiles, List<MessageItem> listMessages, List<TimeSliceGroupItem> listGroups,List<PlaylistItem> listPlaylists,PlaylistItem playlistItem, SignInfo sign)
//      Jerry Xu 2009-4-27 Add method:GetTimeSliceGroupCurrentAdapters(List<MessageItem> listMessages, List<TimeSliceGroupItem> listGroups,List<TimeSliceGroupAdapters> listAdapter)
//                              UpdateTimeSliceGroupCurrentAdapters(List<TimeSliceGroupAdapters> listAdapter)
//                              Update method: GetTimeSliceGroupCurrentMessageName(TimeSliceGroupInfo group,List<MessageItem> listMessages)
//                         Add class:TimeSliceGroupAdapters
//                              ImportTimeSliceGroup(List<MessageFileItem> listFiles, List<MessageItem> listMessages, TimeSliceGroupInfo group, SignInfo sign)
//                              ImportPlaylist(List<MessageFileItem> listFiles, List<MessageItem> listMessages, List<TimeSliceGroupItem> listGroups,List<PlaylistItem> listPlaylists,PlaylistItem playlistItem, SignInfo sign)
//      Jerry Xu 2009-5-22 Add method: SetLock(ILockLibraryItem item, bool isLock)
//      Jerry Xu 2009-6-4  Update method:ImportTimeSliceGroup(List<MessageFileItem> listFiles, List<MessageItem> listMessages, TimeSliceGroupInfo group, SignInfo sign),
//                         Insert method:UpdateDataTimeSliceGroup(TimeSliceGroupInfo group, MemoryLibraryItem memory, List<MemoryLibraryItemData> listMemory),
//                              SetOldDataTimeSliceGroup(TimeSliceGroupInfo group, MemoryLibraryItem memory, List<MemoryLibraryItemData> listMemory)      
//      Jerry Xu 2009-6-22 Update class:MemoryLibraryItemData
//                         Update method:SetOldDataNew(PlaylistInfo playlist, List<MemoryLibraryItemData> listMemory, List<MessageItem> listMessages, List<TimeSliceGroupItem> listGroups, List<PlaylistItem> listPlaylists),UpdateDataNew(List<MemoryLibraryItem> listMemory, List<MemoryLibraryItemData> listOldMemory),UpdateMessageDataNew(LibraryAdapter adapter, MemoryLibraryItem memory, List<MemoryLibraryItemData> listMemory),UpdateTimeSliceGroupDataNew(MemoryLibraryItem memory, List<MemoryLibraryItemData> listOldMemory),UpdatePlaylistDataNew(MemoryLibraryItem playlist, List<MemoryLibraryItemData> listOldMemory),ImportPlaylist(List<MessageFileItem> listFiles, List<MessageItem> listMessages, List<TimeSliceGroupItem> listGroups,List<PlaylistItem> listPlaylists,PlaylistItem playlistItem, SignInfo sign),SetOldDataTimeSliceGroupNew(TimeSliceGroupInfo group, MemoryLibraryItem memory, List<MemoryLibraryItemData> listMemory),UpdateDataTimeSliceGroupNew(TimeSliceGroupInfo group, MemoryLibraryItem memory, List<MemoryLibraryItemData> listMemory),ImportTimeSliceGroup(List<MessageFileItem> listFiles, List<MessageItem> listMessages, TimeSliceGroupInfo group, SignInfo sign)
//      Jerry Xu 2009-7-14 Add method:GetById(string id)
//
//
// Copyright (C) 2008 by Trans-Lux All rights reserved.
// 
//---------------------------------------------------------------------
using System;
using System.Collections.Generic;
using System.Text;
using ProWrite.Core;
using System.IO;
using System.Xml.Serialization;
using System.ComponentModel;
using System.Drawing.Design;
using System.Security.AccessControl;
using ProWrite.Entity.Library;
using ProWrite.Entity.Library.Controller;
using System.Runtime.Serialization;
using ProWrite.Entity.Shape;
using System.Drawing;
using ProWrite.Entity.Dashboard;
using ProWrite.Entity.Library.ImportExport;
using log4net;

namespace ProWrite.Entity.Library
{
    [Serializable]
    [TypeConverter(typeof(ExpandableObjectConverter))]
    public class LibraryGroup : KeyInfo, IEnumerable<LibraryItem>
    {
        protected static readonly ILog log = LogManager.GetLogger(typeof(LibraryGroup));
        public static readonly LibraryType EditorFilter = LibraryType.Image | LibraryType.Message | LibraryType.Video;
        public static readonly LibraryType PlayListFilter = LibraryType.Message | LibraryType.Playlist | LibraryType.TimeSliceGroup;
        public static readonly LibraryType SchedulerFilter = LibraryType.Message | LibraryType.Playlist | LibraryType.TimeSliceGroup | LibraryType.Schedule | LibraryType.ShowColor;
        public static readonly LibraryType DisplayAllFilter = LibraryType.Video | LibraryType.Image | LibraryType.Message | LibraryType.Playlist | LibraryType.TimeSliceGroup;
        public static readonly LibraryType MLPlaylistFilter = LibraryType.Message | LibraryType.MLPlaylist | LibraryType.TimeSliceGroup;

        #region Non Serialized Fields
        [NonSerialized]
        private LibraryType _typeFilter = EditorFilter;
        [NonSerialized]
        private static ImageController _images;
        [NonSerialized]
        private static VideoController _videos;
        [NonSerialized]
        private int _lockerCounter = 0;
        [NonSerialized]
        private Dictionary<LibraryType, ILibraryController> controllers = new Dictionary<LibraryType, ILibraryController>();
        [NonSerialized]
        private static LibraryGroup _current = null;
        #endregion

        #region Serialized Fields
        private bool _isActive;
        private MessageController _messages = new MessageController();
        private PlaylistController _playlists = new PlaylistController();
        private TimeSliceGroupController _timeSliceGroups = new TimeSliceGroupController();
        private SimpleController<SchedulerInfo> _schedulers = new SimpleController<SchedulerInfo>();
        private MLPlaylistController _mlPlaylistController = new MLPlaylistController();
        #endregion

        #region Serialized Fields Version 2
        #endregion

        
        
        [XmlIgnore]
        [Browsable(false)]
        public bool IsLock
        {
            get { return _lockerCounter > 0; }
            set
            {
                if (value)
                    _lockerCounter++;
                else if (_lockerCounter > 0)
                    _lockerCounter--;
            }
        }

        [XmlIgnore]
        [Browsable(false)]
        public int LockCount
        {
            get { return _lockerCounter; }
        }

        static LibraryGroup()
        {
            RefreshLibraryFiles();
        }

        public LibraryGroup() { }
        public LibraryGroup(string name)
        {
            Check.Require(name, "name", Check.NotNullOrEmpty);
            Name = name;
        }

        
        /// <summary>
        /// Current library group
        /// </summary>
        public static LibraryGroup Current
        {
            get
            {
                return _current;
            }
            set
            {
                if (_current != null)
                    _current._isActive = false;
                _current = value;
                if (_current != null)
                    _current._isActive = true;
            }

        }

        public static void RefreshLibraryFiles()
        {
            _images = new ImageController();
            _videos = new VideoController();
            InitFiles(IOHelper.ImageFiles, LibraryType.Image);
            InitFiles(IOHelper.VideoFiles, LibraryType.Video);
        }

        private static void InitFiles(string[] files, LibraryType type)
        {
            if (files == null || files.Length < 1)
                return;

            foreach (string item in files)
            {
                AddFile(item, type, Path.GetFileName(item));
            }
        }

        public void PopulateController()
        {
            if (controllers == null)
                controllers = new Dictionary<LibraryType, ILibraryController>();

            controllers.Clear();
            controllers[LibraryType.Image] = _images;
            controllers[LibraryType.Video] = _videos;
            controllers[LibraryType.Message] = _messages;
            controllers[LibraryType.TimeSliceGroup] = _timeSliceGroups;
            controllers[LibraryType.Playlist] = _playlists;
            controllers[LibraryType.Schedule] = _schedulers;
            controllers[LibraryType.MLPlaylist] = _mlPlaylistController;
        }

        private Dictionary<LibraryType, ILibraryController> Controllers
        {
            get
            {
                if (controllers != null && controllers.Count > 0)
                    return controllers;
                PopulateController();
                return controllers;
            }
        }


        /// <summary>
        /// populate object relation for message and message proxy
        /// </summary>
        public void PopulateRelation()
        {
            if (_schedulers == null)
                _schedulers = new SimpleController<SchedulerInfo>();
            if (_mlPlaylistController == null)
                _mlPlaylistController = new MLPlaylistController();
            if (_messages == null)
                _messages = new MessageController();
            if (_playlists == null)
                _playlists = new PlaylistController();
            if (_timeSliceGroups == null)
                _timeSliceGroups = new TimeSliceGroupController();
            

            //Check message is valid
            foreach (MessageInfo item in _messages)
                item.PopulateValiad();

            foreach (PlaylistInfo item in _playlists)
                PopulateMessages(item.Items);

            foreach (TimeSliceGroupInfo item in _timeSliceGroups)
                PopulateMessages(item.Items);

            foreach (SchedulerInfo item in _schedulers)
                PopulateMessages(item.Items);

            foreach (MLPlaylistInfo pl in _mlPlaylistController)
                foreach (var item in pl.Items)
                    PopulateMessages(item.Items.ToArray());

        }

        private void PopulateMessages(LibraryAdapter[] libraries)
        {
            if (libraries != null && libraries.Length > 0)
            {
                foreach (LibraryAdapter m in libraries)
                {
                    switch (m.Type)
                    {
                        case LibraryType.MessageProxy:
                            m.Target = _messages.GetById(m.TargetId);
                            break;
                        case LibraryType.PlaylistProxy:
                            m.Target = _playlists.GetById(m.TargetId);
                            break;
                        case LibraryType.TimeSliceGroupProxy:
                            m.Target = _timeSliceGroups.GetById(m.TargetId);
                            break;
                        case LibraryType.MLPlaylistProxy:
                            m.Target = _mlPlaylistController.GetById(m.TargetId);
                            break;
                    }
                }
            }
        }


        public LibraryType TypeFilter
        {
            get { return _typeFilter; }
            set { _typeFilter = value; }
        }

        public void SetLock(ILockLibraryItem item, bool isLock)
        {
            if (item == null)
                return;
            switch (item.Type)
            {
                case LibraryType.Message:
                    LibraryGroup.Current.LockMessage(item, isLock);
                    //MessageInfo message = item as message
                    break;
                case LibraryType.Playlist:
                    LibraryGroup.Current.LockPlaylist(item, isLock);
                    break;
                case LibraryType.Schedule:
                    LibraryGroup.Current.LockScheduler(item, isLock);
                    break;
            }
        }
        
        public void LockLibrary(ILockLibraryItem lockerItem, bool isLock)
        {
            if (lockerItem != null)
            {
                if (controllers.ContainsKey(lockerItem.Type))
                {
                    ILockLibraryItem item = controllers[lockerItem.Type].GetByName(lockerItem.Name) as ILockLibraryItem;
                    if (item != null)
                        item.IsLock = isLock;
                    // reduce lockerItem count
                    if (!isLock)
                    {
                        if (lockerItem.Type == LibraryType.Message)
                        {
                            LockMessage(lockerItem, isLock);
                        }
                        if (lockerItem.Type == LibraryType.Playlist)
                        {
                            LockPlaylist(lockerItem, isLock);
                        }
                        if (lockerItem.Type == LibraryType.Schedule)
                        {
                            LockScheduler(lockerItem, isLock);
                        }
                    }
                }
            }
        }

        /// <summary>
        /// Function: Lock scheduer
        /// Author  : Jerry Xu
        /// Date    : 2009-1-15
        /// </summary>
        /// <param name="locker">ILockLibraryItem</param>
        /// <param name="isLock">bool</param>
        public void LockScheduler(ILockLibraryItem locker, bool isLock)
        {
            SchedulerInfo scheduler = locker as SchedulerInfo;

            if(scheduler==null || scheduler.Items==null || scheduler.Items.Length==0)
                return;
            foreach (AppointmentInfo appoint in scheduler.Items)
            {
                if (appoint.Target != null)
                    appoint.Target.IsLock = isLock;
            }
        }

        public void LockPlaylist(ILockLibraryItem locker, bool isLock)
        {
            PlaylistInfo playlist = locker as PlaylistInfo;

            if (playlist == null || playlist.Items == null || playlist.Items.Length == 0)
                return;
            foreach (LibraryAdapter adapter in playlist.Items)
            {
                if (adapter.Target != null)
                    adapter.Target.IsLock = isLock;
            }
        }

        public void LockMessage(ILockLibraryItem locker, bool isLock)
        {
            MessageInfo message = locker as MessageInfo;

            if (message == null || message.Items == null || message.Items.Length == 0)
                return;
            foreach (ShapeLayer shapelayer in message.Items)
            {
                if (shapelayer.Shape != null)
                {
                    if (shapelayer.Shape.Type == ShapeType.Image)
                    {
                        ShapeImage shapeImage = shapelayer.Shape as ShapeImage;
                        if (!string.IsNullOrEmpty(shapeImage.ImageUrl))
                        {
                            ImageInfo imageInfo = LibraryGroup.Images.GetByPath(shapeImage.ImageUrl);
                            if (imageInfo != null)

                                imageInfo.IsLock = isLock;
                        }
                    }
                    if (shapelayer.Shape.Type == ShapeType.Video)
                    {
                        ShapeVideo shapeVideo = shapelayer.Shape as ShapeVideo;
                        if (!string.IsNullOrEmpty(shapeVideo.VideoUrl))
                        {
                            VideoInfo videoInfo = LibraryGroup.Videos.GetByPath(shapeVideo.VideoUrl);
                            if (videoInfo != null)

                                videoInfo.IsLock = isLock;
                        }
                    }
                }
            }
        }

        public void AddFiles(string[] files)
        {
            if (files != null && files.Length > 0)
            {
                foreach (string file in files)
                {
                    string fileType = Path.GetExtension(file);
                    if (string.IsNullOrEmpty(fileType))
                        continue;
                    fileType = fileType.ToLower();
                    AddFile(file, fileType);
                }
            }
        }

        public void AddFile(string file, string fileType)
        {
            try
            {
                switch (fileType)
                {
                    case Constance.FileExtensionName.AVI:
                    case Constance.FileExtensionName.Mpeg_2:
                    case Constance.FileExtensionName.Wmv:
                        _videos.AddFile(file);
                        break;
                    case Constance.FileExtensionName.Bmp:
                    case Constance.FileExtensionName.Jpeg:
                    case Constance.FileExtensionName.Jpg:
                    case Constance.FileExtensionName.Gif:
                    case Constance.FileExtensionName.Png:
                    case Constance.FileExtensionName.Tif:
                    case Constance.FileExtensionName.Tiff:
                        _images.AddFile(file);
                        break;
                    case Constance.FileExtensionName.Message:
                        _messages.AddFile(file);
                        break;

                }
            }
            catch (Exception ex)
            {
                log.Error(ex.Message, ex);
            }
        }

        public void AddFile(FileItem item)
        {
            try
            {
                switch (item.Type)
                {
                    case LibraryType.Video:
                        _videos.AddFile(item);
                        break;

                    case LibraryType.Image:
                        _images.AddFile(item);
                        break;
                }
            }
            catch (Exception ex)
            {
                log.Error(ex.Message, ex);
            }
        }

        public void AddFile(string file, string fileType,byte[] content)
        {
            try
            {
                switch (fileType)
                {
                    case Constance.FileExtensionName.AVI:
                    case Constance.FileExtensionName.Mpeg_2:
                    case Constance.FileExtensionName.Wmv:
                        _videos.AddFile(file,content);
                        break;
                    case Constance.FileExtensionName.Bmp:
                    case Constance.FileExtensionName.Jpeg:
                    case Constance.FileExtensionName.Jpg:
                    case Constance.FileExtensionName.Gif:
                    case Constance.FileExtensionName.Png:
                    case Constance.FileExtensionName.Tif:
                    case Constance.FileExtensionName.Tiff:
                        _images.AddFile(file,content);
                        break;
                    case Constance.FileExtensionName.Message:
                        _messages.AddFile(file);
                        break;

                }
            }
            catch (Exception ex)
            {
                log.Error(ex.Message, ex);
            }
        }

        public void BatchLoadFile(List<LibraryFile> listFiles, List<MessageInfo> listMessages,SignInfo sign)
        {
            if (listFiles != null && listFiles.Count > 0)
            {
                foreach (LibraryFile item in listFiles)
                {
                    LibraryGroup.Current.AddFile(item.FileName, item.LibraryFileName, Path.GetExtension(item.LibraryFileName).ToLower(), sign);
                }
            }
            if (listMessages != null && listMessages.Count > 0)
            {
                foreach (MessageInfo item in listMessages)
                {
                    LibraryGroup.Current.Messages.Add(item);
                }
            }
        }

        public void BatchLoadFile(List<LibraryFile> listFiles, List<MessageInfo> listMessages, List<int> listLengths, SignInfo sign)
        {
            if (listFiles != null && listFiles.Count > 0)
            {
                for (int i = 0; i < listFiles.Count; i++)
                {
                    LibraryGroup.Current.AddFile(listFiles[i].FileName, listFiles[i].LibraryFileName, Path.GetExtension(listFiles[i].LibraryFileName).ToLower(), listLengths[i], sign);
                }
                //foreach (LibraryFile item in listFiles)
                //{                    
                //    LibraryGroup.Current.AddFile(item.FileName, item.LibraryFileName, Path.GetExtension(item.LibraryFileName).ToLower(), sign);
                //}
            }
            if (listMessages != null && listMessages.Count > 0)
            {
                foreach (MessageInfo item in listMessages)
                {
                    LibraryGroup.Current.Messages.Add(item);
                }
            }
        }

        public void BatchLoadFile(List<LibraryFile> listFiles, List<MessageInfo> listMessages, List<MessageReplaceItem> listReplaceMessages ,List<int> listLengths, SignInfo sign)
        {
            if (listFiles != null && listFiles.Count > 0)
            {
                MessageInfo mes = null;
                for (int i = 0; i < listFiles.Count; i++)
                {
                    mes = LibraryGroup.Current.AddFileNoSaveMessage(listFiles[i].FileName, listFiles[i].LibraryFileName, Path.GetExtension(listFiles[i].LibraryFileName).ToLower(), listLengths[i], sign);
                    
                    var replaceMes = listReplaceMessages.Find(p => { return  p.FileIndex == i && p.IsReplace; });
                    if (replaceMes != null)
                    {
                        replaceMes.Message = mes;
                        replaceMes.Message.Name = Path.GetFileNameWithoutExtension(listFiles[i].FileName);
                        LibraryGroup.Current.Messages.Add(replaceMes.Message);
                    }

                }
                //foreach (LibraryFile item in listFiles)
                //{                    
                //    LibraryGroup.Current.AddFile(item.FileName, item.LibraryFileName, Path.GetExtension(item.LibraryFileName).ToLower(), sign);
                //}
            }
            if (listMessages != null && listMessages.Count > 0)
            {
                for (int i = 0; i < listMessages.Count;i++ )
                {
                    var replaceMes = listReplaceMessages.Find(p => { return p.MessageIndex == i; });
                    if (replaceMes != null)
                    {
                        replaceMes.Message.Name = listMessages[i].Name;
                    }
                    LibraryGroup.Current.Messages.Add(replaceMes.Message);
                }
            }
        }

        #region Import LibraryItem
        #region Import message
        public bool ImportMessage(List<MessageFileItem> listFiles, MessageInfo message, SignInfo sign)
        {
            if (message == null)
                return false;
            if (listFiles != null && listFiles.Count > 0)
            {
                foreach (MessageFileItem item in listFiles)
                {
                    LibraryGroup.Current.AddFile(item.Item);
                }
            }
            if (message != null )            
                return LibraryGroup.Current.Messages.Add(message);                    
            
            return false;
        }
        #endregion

        #region Import playlist
        private class MemoryLibraryItemData
        {
            //NewItem(Id old)
            public MemoryLibraryItem Item;
            //New Name
            public string Name;
            //Old Id
            public string Id;           
            public LibraryType Type;
        }        

        private void ImportSetOldData(PlaylistInfo playlist, List<MemoryLibraryItemData> listMemory, List<MessageItem> listMessages, List<TimeSliceGroupItem> listGroups, List<PlaylistItem> listPlaylists)
        {
            if (playlist == null || playlist.Items == null || playlist.Items.Length == 0)
                return;

            if (listMemory == null)
                listMemory = new List<MemoryLibraryItemData>();


            listMemory.Add(new MemoryLibraryItemData() { Item = playlist, Type = LibraryType.Playlist, Name = playlist.Name, Id = playlist.Id });

            if (listMessages != null && listMessages.Count > 0)
            {
                listMemory.AddRange(listMessages.ConvertAll<MemoryLibraryItemData>(p => 
                { 
                    return new MemoryLibraryItemData() { Item = p.Item, Type = LibraryType.Message, Name = p.Item.Name, Id = p.Item.Id } ;
                }));
            }

            if (listGroups != null && listGroups.Count > 0)
            {
                listMemory.AddRange(listGroups.ConvertAll<MemoryLibraryItemData>(p => 
                { 
                    return new MemoryLibraryItemData() { Item = p.Item, Type = LibraryType.TimeSliceGroup, Name = p.Item.Name, Id = p.Item.Id } ;
                }));
            }
            if (listPlaylists != null && listPlaylists.Count > 0)
            {
                listMemory.AddRange(listPlaylists.ConvertAll<MemoryLibraryItemData>(p => 
                {
                    return new MemoryLibraryItemData() { Item = p.Item, Type = LibraryType.Playlist, Name = p.Item.Name, Id = p.Item.Id };
                }));
            }

        }
       
        private void ImportUpdateNewData(List<MemoryLibraryItem> listMemory, List<MemoryLibraryItemData> listOldMemory)
        {
            if (listOldMemory == null || listMemory == null || listOldMemory.Count == 0 || listMemory.Count == 0 )
                return;

            foreach (MemoryLibraryItem item in listMemory)
            {
                switch (item.Type)
                {
                    case LibraryType.Message:
                        break;
                    case LibraryType.TimeSliceGroup:
                        ImportUpdateTimeSliceGroupNewData(item, listMemory,listOldMemory);
                        break;
                    case LibraryType.Playlist:
                        ImportUpdatePlaylistNewData(item, listMemory, listOldMemory);
                        break;
                }
                
            }
        }

        private void ImportUpdateTimeSliceGroupNewData(MemoryLibraryItem memory,List<MemoryLibraryItem> listMemory, List<MemoryLibraryItemData> listOldMemory)
        {
            TimeSliceGroupInfo group = memory as TimeSliceGroupInfo;
            if (group == null || group.Items == null || group.Items.Length == 0)
                return;

            MemoryLibraryItemData memoryData = null;
            MessageInfo message = null;
            foreach (MessageAdapterInfo item in group.Items)
            {
                memoryData = listOldMemory.Find(p => 
                {
                    return item.TargetId == p.Id;
                });
                if (memoryData != null)
                {
                    message = listMemory.Find(p => { return p.Type == LibraryType.Message && p.Name == memoryData.Name; }) as MessageInfo;
                    item.TargetId = message.Id;
                    item.Target = message;
                }
            }
        }

        private void ImportUpdatePlaylistNewData(MemoryLibraryItem playlist, List<MemoryLibraryItem> listMemory, List<MemoryLibraryItemData> listOldMemory)
        {
            PlaylistInfo pl = playlist as PlaylistInfo;
            if (pl == null || pl.Items == null || pl.Items.Length == 0)
                return;

            MemoryLibraryItemData memoryData = null;
            LibraryItem memory = null;
            foreach (LibraryAdapter item in pl.Items)
            {
                memoryData = listOldMemory.Find(p =>
                {
                    return item.TargetId == p.Id;
                });
                if (memoryData != null)
                {
                    memory = listMemory.Find(p => { return p.Type == memoryData.Type && p.Name == memoryData.Name; });
                    item.TargetId = memory.Id;
                    item.Target = memory as MemoryLibraryItem;
                }
            }
        }

        public bool ImportPlaylist(List<MessageFileItem> listFiles, List<MessageItem> listMessages, List<TimeSliceGroupItem> listGroups,List<PlaylistItem> listPlaylists,PlaylistItem playlistItem, SignInfo sign)
        {
            if (playlistItem == null)
                return false;            

            List<MemoryLibraryItemData> listOldMemory = new List<MemoryLibraryItemData>();
            List<MemoryLibraryItem> listNewMemory = new List<MemoryLibraryItem>();

            //Old referrece data
            ImportSetOldData(playlistItem.Item, listOldMemory,listMessages, listGroups, listPlaylists);

            if (listMessages != null && listMessages.Count > 0)
            {
                foreach (MessageItem item in listMessages)
                {
                    item.Item.Id = Guid.NewGuid().ToString();
                    listNewMemory.Add(item.Item);
                }
            }

            if (listGroups != null && listGroups.Count > 0)
            {
                foreach (TimeSliceGroupItem item in listGroups)
                {
                    item.Item.Id = Guid.NewGuid().ToString();
                    listNewMemory.Add(item.Item);
                }
            }
            if (listPlaylists != null && listPlaylists.Count > 0)
            {
                foreach (PlaylistItem item in listPlaylists)
                {
                    item.Item.Id = Guid.NewGuid().ToString();
                    listNewMemory.Add(item.Item);
                }
            }

            if (playlistItem != null)
            {
                playlistItem.Item.Id = Guid.NewGuid().ToString();
                listNewMemory.Add(playlistItem.Item);
                
                //Update new referrece data
                ImportUpdateNewData(listNewMemory, listOldMemory);

                //Add message files
                if (listFiles != null && listFiles.Count > 0)
                {
                    foreach (MessageFileItem item in listFiles)
                    {
                        LibraryGroup.Current.AddFile(item.Item);
                    }
                }

                //Add libraryItem
                bool flag = ImportAddData(listNewMemory);

                return flag;
            }
            return false;
        }

        private bool ImportAddData(List<MemoryLibraryItem> listMemory)
        {
            if (listMemory == null || listMemory.Count == 0)
                return false;
            foreach (MemoryLibraryItem item in listMemory)
                LibraryGroup.Current.Add(item);
            return true;
        }
        #endregion

        #region Import TimeSliceGroup
        private string GetTimeSliceGroupCurrentMessageName(TimeSliceGroupInfo group, List<MessageItem> listMessages)
        {
            if (group == null || listMessages == null)
                return null;

            var item = listMessages.Find(p => { return p.Item.Id == group.GetMessageID(group.CurrentMessageAdapterID); });
            if (item != null)
                return item.Item.Name;

            return null;
        }

        private void SetOldDataTimeSliceGroupNew(TimeSliceGroupInfo group, List<MemoryLibraryItemData> listMemory, List<MessageItem> listMessages)
        {
            if (group == null || group.Items == null || group.Items.Length == 0)
                return;

            if (listMemory == null)
                listMemory = new List<MemoryLibraryItemData>();

            if (listMessages != null && listMessages.Count > 0)
            {
                listMemory.AddRange(listMessages.ConvertAll<MemoryLibraryItemData>(p =>
                {
                    return new MemoryLibraryItemData() { Item = p.Item, Type = LibraryType.Message, Name = p.Item.Name, Id = p.Item.Id };
                }));
            }
        }

        public bool ImportTimeSliceGroup(List<MessageFileItem> listFiles, List<MessageItem> listMessages, TimeSliceGroupInfo group, SignInfo sign)
        {
            List<MemoryLibraryItem> listMemory = new List<MemoryLibraryItem>();

            if (group == null)
                return false;
            
            List<MemoryLibraryItemData> listOldMemory = new List<MemoryLibraryItemData>();


            if (listMessages != null && listMessages.Count > 0)
            {
                SetOldDataTimeSliceGroupNew(group, listOldMemory, listMessages);

                foreach (MessageItem item in listMessages)
                {
                    item.Item.Id = Guid.NewGuid().ToString();
                    listMemory.Add(item.Item);
                }

                ImportUpdateTimeSliceGroupNewData(group, listMemory, listOldMemory);
            }

            string currentName = GetTimeSliceGroupCurrentMessageName(group, listMessages);

            if (!string.IsNullOrEmpty(currentName))
            {
                foreach (MessageAdapterInfo adapter in group.Items)
                {
                    if (adapter.Id == group.CurrentMessageAdapterID)
                    {
                        //adapter.TargetId = LibraryGroup.Current.Messages.GetByName(currentName).Id;
                        adapter.TargetId = listMemory.Find(p => { return p.Type == LibraryType.Message && p.Name == currentName; }).Id;
                        break;
                    }
                }
            }
            
            if (group != null)
            {
                group.Id = Guid.NewGuid().ToString();
                listMemory.Add(group);

                ImportUpdateTimeSliceGroupNewData(group, listMemory, listOldMemory);

                if (listFiles != null && listFiles.Count > 0)
                {
                    foreach (MessageFileItem item in listFiles)
                    {
                        LibraryGroup.Current.AddFile(item.Item);
                    }
                }

                bool flag = ImportAddData(listMemory);

                return flag;
            }
            return false;
        }
        #endregion
        #endregion

        public MessageInfo AddFile(string file, string libraryFile, string fileType,SignInfo sign)
        {
            try
            {
                FileLibraryItem item;
                switch (fileType)
                {
                    case Constance.FileExtensionName.AVI:
                    case Constance.FileExtensionName.Mpeg_2:
                    case Constance.FileExtensionName.Wmv:
                        item = _videos.AddFile(file, libraryFile) as FileLibraryItem;
                        if (_messages.GetByName(Path.GetFileNameWithoutExtension(item.Name)) != null)
                            return _messages.AddNoSave(item, sign);
                        else
                        {
                            _messages.Add(item, sign);
                            return null;
                        }
                    case Constance.FileExtensionName.Bmp:
                    case Constance.FileExtensionName.Jpeg:
                    case Constance.FileExtensionName.Jpg:
                    case Constance.FileExtensionName.Gif:
                    case Constance.FileExtensionName.Png:
                    case Constance.FileExtensionName.Tif:
                    case Constance.FileExtensionName.Tiff:
                        item = _images.AddFile(file, libraryFile) as FileLibraryItem;
                        if (_messages.GetByName(Path.GetFileNameWithoutExtension(item.Name)) != null)
                            return _messages.AddNoSave(item, sign);
                        else
                        {
                            _messages.Add(item, sign);
                            return null;
                        }
                }
                return null;
            }
            catch (Exception ex)
            {
                log.Error(ex.Message, ex);
                return null;
            }
        }

        public MessageInfo AddFile(string file, string libraryFile, string fileType, int length, SignInfo sign)
        {
            try
            {
                FileLibraryItem item;
                switch (fileType)
                {
                    case Constance.FileExtensionName.AVI:
                    case Constance.FileExtensionName.Mpeg_2:
                    case Constance.FileExtensionName.Wmv:
                        item = _videos.AddFile(file, libraryFile) as FileLibraryItem;
                        if (_messages.GetByName(Path.GetFileNameWithoutExtension(item.Name)) != null)
                            return _messages.AddNoSave(item, length,sign);
                        else
                        {
                            _messages.Add(item, length, sign);
                            return null;
                        }
                    case Constance.FileExtensionName.Bmp:
                    case Constance.FileExtensionName.Jpeg:
                    case Constance.FileExtensionName.Jpg:
                    case Constance.FileExtensionName.Png:
                    case Constance.FileExtensionName.Tif:
                    case Constance.FileExtensionName.Tiff:
                        item = _images.AddFile(file, libraryFile) as FileLibraryItem;
                        if (_messages.GetByName(Path.GetFileNameWithoutExtension(item.Name)) != null)
                            return _messages.AddNoSave(item, sign);
                        else
                        {
                            _messages.Add(item, sign);
                            return null;
                        }
                    case Constance.FileExtensionName.Gif:
                        item = _images.AddFile(file, libraryFile) as FileLibraryItem;
                        if (_messages.GetByName(Path.GetFileNameWithoutExtension(item.Name)) != null)
                            return _messages.AddNoSave(item,length,sign);
                        else
                        {
                            _messages.Add(item, length, sign);
                            return null;
                        }
                }
                return null;
            }
            catch (Exception ex)
            {
                log.Error(ex.Message, ex);
                return null;
            }
        }

        public MessageInfo AddFileNoSaveMessage(string file, string libraryFile, string fileType, int length, SignInfo sign)
        {
            try
            {
                FileLibraryItem item;
                switch (fileType)
                {
                    case Constance.FileExtensionName.AVI:
                    case Constance.FileExtensionName.Mpeg_2:
                    case Constance.FileExtensionName.Wmv:
                        item = _videos.AddFile(file, libraryFile) as FileLibraryItem;
                        return _messages.AddNoSave(item, length, sign);
                        
                    case Constance.FileExtensionName.Bmp:
                    case Constance.FileExtensionName.Jpeg:
                    case Constance.FileExtensionName.Jpg:
                    case Constance.FileExtensionName.Png:
                    case Constance.FileExtensionName.Tif:
                    case Constance.FileExtensionName.Tiff:
                        item = _images.AddFile(file, libraryFile) as FileLibraryItem;
                        return _messages.AddNoSave(item, sign);
                    case Constance.FileExtensionName.Gif:
                        item = _images.AddFile(file, libraryFile) as FileLibraryItem;
                        return _messages.AddNoSave(item, length, sign);
                }
                return null;
            }
            catch (Exception ex)
            {
                log.Error(ex.Message, ex);
                return null;
            }
        }    

        private static FileLibraryItem AddFile(string file, LibraryType type, string libraryName)
        {
            FileLibraryItem item = null;
            IOHelper.SetFileAttribute(file, FileAttributes.ReadOnly);

            switch (type)
            {
                case LibraryType.Image:
                    item = new ImageInfo();
                    item.Name = libraryName;
                    item.Path = file;
                    _images.Add(item as ImageInfo);
                    break;
                case LibraryType.Video:
                    item = new VideoInfo();
                    item.Name = libraryName;
                    item.Path = file;
                    _videos.Add(item as VideoInfo);
                    break;
            }
            return item;
        }

        public bool Contains(LibraryItem item)
        {
            if (item == null || !Controllers.ContainsKey(item.Type))
                return false;
            return controllers[item.Type].Contains(item);
        }

        public LibraryItem GetByName(string name, LibraryType type)
        {
            if (!Controllers.ContainsKey(type))
                return null;
            return controllers[type].GetByName(name);
        }

        public LibraryItem GetById(string id, LibraryType type)
        {
            if (!Controllers.ContainsKey(type))
                return null;
            return controllers[type].GetById(id);
        }        

        public MemoryLibraryItem GetById(string id)
        {
            if(string.IsNullOrEmpty(id))
                return null;

            if (_messages.ContainsById(id))
                return _messages.GetById(id);

            if (_timeSliceGroups.ContainsById(id))
                return _timeSliceGroups.GetById(id);

            if (_playlists.ContainsById(id))
                return _playlists.GetById(id);

            return null;
        }

        public bool Contains(string name, LibraryType type)
        {
            if (!Controllers.ContainsKey(type))
                return false;
            return controllers[type].Contains(name);
        }

        public bool Add(LibraryItem item)
        {
            if (item == null || !Controllers.ContainsKey(item.Type))
                return false;
            MemoryLibraryItem memory = item as MemoryLibraryItem;
            if (memory != null)
                memory.CreateTime = DateTime.Now;
            return controllers[item.Type].Add(item);
        }

        /// <summary>
        /// Remove libraryItem
        /// </summary>
        /// <param name="item">library item</param>
        /// <returns></returns>
        public bool Remove(LibraryItem item)
        {
            if (item == null || !Controllers.ContainsKey(item.Type))
                return false;
            return Controllers[item.Type].Remove(item);
        }

        public bool Update(LibraryItem item)
        {
            if (item == null || !Controllers.ContainsKey(item.Type))
                return false;
            MemoryLibraryItem memory = item as MemoryLibraryItem;
            if (memory != null)
                memory.ModifyTime = DateTime.Now;
            return Controllers[item.Type].Update(item);
        }

        #region Rename
        /// <summary>
        /// Function:Rename 
        /// Author:Jerry Xu
        /// Date:2008-7-7
        /// </summary>
        /// <param name="newName"></param>
        /// <param name="oldName"></param>
        /// <param name="type"></param>
        /// <returns></returns>
        public bool Rename(string newName,string oldName,LibraryType type)
        {
            if (string.IsNullOrEmpty(newName) || newName == oldName)
                return false;

            ILibraryController items = Controllers[type];
            if (items == null)
                return false;

            return items.Rename(newName, oldName);
        }
        #endregion

        public static ImageController Images
        {
            get { return _images; }
        }

        public static VideoController Videos
        {
            get { return _videos; }
        }

        [XmlIgnore]
        [Editor(Constance.Designers.NoneCollection, typeof(UITypeEditor))]
        public MessageController Messages
        {
            get { return _messages; }
            set { _messages = value; }
        }

        [XmlIgnore]
        [Editor(Constance.Designers.NoneCollection, typeof(UITypeEditor))]
        public TimeSliceGroupController TimeSliceGroups
        {
            get { return _timeSliceGroups; }
            set { _timeSliceGroups = value; }
        }

        [XmlIgnore]
        [Editor(Constance.Designers.NoneCollection, typeof(UITypeEditor))]
        public PlaylistController Playlists
        {
            get { return _playlists; }
            set { _playlists = value; }
        }

        [XmlIgnore]
        [Editor(Constance.Designers.NoneCollection, typeof(UITypeEditor))]
        public SimpleController<SchedulerInfo> Schedulers
        {
            get { return _schedulers; }
            set { _schedulers = value; }
        }

        [XmlIgnore]
        [Editor(Constance.Designers.NoneCollection, typeof(UITypeEditor))]
        public MLPlaylistController MLPlaylists
        {
            get { return _mlPlaylistController; }
            set { _mlPlaylistController = value; }
        }

        public bool CanDeleteLibrary(LibraryItem lib)
        {
            if (lib == null)
                return true;

            switch (lib.Type)
            {
                case LibraryType.Image:
                case LibraryType.Video:
                    foreach (MessageInfo item in _messages)
                    {
                        if (item.IsReferenceLibrary(lib))
                            return false;
                    }
                    return true;
                case LibraryType.Message:
                    foreach (TimeSliceGroupInfo item in _timeSliceGroups)
                    {
                        if (item.IsReferenceLibrary(lib))
                            return false;
                    }
                    foreach (PlaylistInfo item in _playlists)
                    {
                        if (item.IsReferenceLibrary(lib))
                            return false;
                    }
                    foreach (SchedulerInfo item in _schedulers)
                    {
                        if (item.IsReferenceLibrary(lib))
                            return false;
                    }
                    return true;
                case LibraryType.TimeSliceGroup:
                    foreach (PlaylistInfo item in _playlists)
                    {
                        if (item.IsReferenceLibrary(lib))
                            return false;
                    }
                    foreach (SchedulerInfo item in _schedulers)
                    {
                        if (item.IsReferenceLibrary(lib))
                            return false;
                    }
                    return true;
                case LibraryType.Playlist:
                    foreach (PlaylistInfo item in _playlists)
                    {
                        if (item.IsReferenceLibrary(lib))
                            return false;
                    }
                    foreach (SchedulerInfo item in _schedulers)
                    {
                        if (item.IsReferenceLibrary(lib))
                            return false;
                    }
                    break;
                case LibraryType.MLPlaylist:
                    foreach (var item in _mlPlaylistController)
                    {
                        if (item.IsReferenceLibrary(lib))
                            return false;
                    }

                    break;
            }

            return true;
        }

        public LibraryDeleteItem CanDeleteLibraryNew(LibraryItem lib)
        {
            LibraryDeleteItem deleteItem = new LibraryDeleteItem();            

            if (lib == null)
                return deleteItem;

            switch (lib.Type)
            {
                case LibraryType.Image:
                case LibraryType.Video:
                    foreach (MessageInfo item in _messages)
                    {
                        if (item.IsReferenceLibrary(lib))
                        {
                            deleteItem.ReferrenceItem = item;
                            deleteItem.State = LibraryState.Referrence;
                            return deleteItem;
                        }
                    }
                    return deleteItem;
                case LibraryType.Message:
                    foreach (TimeSliceGroupInfo item in _timeSliceGroups)
                    {
                        if (item.IsReferenceLibrary(lib))
                        {
                            deleteItem.ReferrenceItem = item;
                            deleteItem.State = LibraryState.Referrence;
                            return deleteItem;
                        }
                    }
                    foreach (PlaylistInfo item in _playlists)
                    {
                        if (item.IsReferenceLibrary(lib))
                        {
                            deleteItem.ReferrenceItem = item;
                            deleteItem.State = LibraryState.Referrence;
                            return deleteItem;
                        }
                    }
                    foreach (SchedulerInfo item in _schedulers)
                    {
                        if (item.IsReferenceLibrary(lib))
                        {
                            deleteItem.ReferrenceItem = item;
                            deleteItem.State = LibraryState.Referrence;
                            return deleteItem;
                        }
                    }
                    return deleteItem;
                case LibraryType.TimeSliceGroup:
                    foreach (PlaylistInfo item in _playlists)
                    {
                        if (item.IsReferenceLibrary(lib))
                        {
                            deleteItem.ReferrenceItem = item;
                            deleteItem.State = LibraryState.Referrence;
                            return deleteItem;
                        }
                    }
                    foreach (SchedulerInfo item in _schedulers)
                    {
                        if (item.IsReferenceLibrary(lib))
                        {
                            deleteItem.ReferrenceItem = item;
                            deleteItem.State = LibraryState.Referrence;
                            return deleteItem;
                        }
                    }
                    return deleteItem;
                case LibraryType.Playlist:
                    foreach (PlaylistInfo item in _playlists)
                    {
                        if (item.IsReferenceLibrary(lib))
                        {
                            deleteItem.ReferrenceItem = item;
                            deleteItem.State = LibraryState.Referrence;
                            return deleteItem;
                        }
                    }
                    foreach (SchedulerInfo item in _schedulers)
                    {
                        if (item.IsReferenceLibrary(lib))
                        {
                            deleteItem.ReferrenceItem = item;
                            deleteItem.State = LibraryState.Referrence;
                            return deleteItem;
                        }
                    }
                    return deleteItem;
                case LibraryType.MLPlaylist:
                    foreach (var item in _mlPlaylistController)
                    {
                        if (item.IsReferenceLibrary(lib))
                        {
                            deleteItem.ReferrenceItem = item;
                            deleteItem.State = LibraryState.Referrence;
                            return deleteItem;
                        }
                    }
                    return deleteItem;
            }

            return deleteItem;
        }

        [OnDeserialized]
        private void Deserialized(StreamingContext ctx)
        {
            if (_isActive)
                _current = this;
        }

        #region IEnumerable<LibraryItem> Members
        public IEnumerator<LibraryItem> GetEnumerator()
        {
            foreach (LibraryItem item in _images)
                yield return item;
            foreach (LibraryItem item in _videos)
                yield return item;
            foreach (LibraryItem item in _messages)
                yield return item;
            foreach (LibraryItem item in _playlists)
                yield return item;
            foreach (LibraryItem item in _timeSliceGroups)
                yield return item;
            foreach (LibraryItem item in _schedulers)
                yield return item;
        }

        #endregion

        #region IEnumerable Members
        System.Collections.IEnumerator System.Collections.IEnumerable.GetEnumerator()
        {
            return GetEnumerator();
        }
        #endregion

        public override string ToString()
        {
            return base.Name;
        }

        protected override void Dispose(bool disposing)
        {
            base.Dispose(disposing);
            if (_messages != null)
            {
                _messages.Dispose();
                _messages = null;
            }
            if (_timeSliceGroups != null)
            {
                _timeSliceGroups.Dispose();
                _timeSliceGroups = null;
            }
            if (_playlists != null)
            {
                _playlists.Dispose();
                _playlists = null;
            }
            if (_schedulers != null)
            {
                _schedulers.Dispose();
                _schedulers = null;
            }
            if (_mlPlaylistController != null)
            {
                _mlPlaylistController.Dispose();
                _mlPlaylistController = null;
            }
            if (controllers != null)
            {
                controllers.Clear();
                controllers = null;
            }
        }
    }
}