//---------------------------------------------------------------------
//
// File: PlaylistWrapper.cs
//      
// Description:
//      PlaylistInfo import/export class
//
// Author: Jerry Xu 2009-4-21
//
// Modify History:
//      Jerry Xu 2009-4-20 Update method:SerializingMessage(MessageInfo message)
//      Jerry Xu 2009-4-27 Update method:Serializing(StreamingContext ctx),Deserialized(StreamingContext ctx)
//                         Add method:SerializingMessages(List<MessageInfo> items),SerializingMessage(MessageInfo message),
//                                  GenerateNailImage(MemoryLibraryItem item, NailImageFileItem nailItem),UpdateNailImage(string sourceName, string targetName, List<PlaylistInfo> playlists),
//                                  DeserializedNailImage()
//      Jerry Xu 2009-4-28 Update method:DeserializedNailImage(),:Serializing(StreamingContext ctx)
//      Jerry Xu 2009-4-29 Update property:Playlist
//                         Add methods:DeserializedPlaylist(),SetTargetMessage(LibraryAdapter adapter),SetTargetTimeSliceGroup(LibraryAdapter adapter),SetTargetPlaylist(LibraryAdapter adapter)
//      Jerry Xu 2009-6-19 Update method:Serializing(StreamingContext ctx),DeserializedNailImage()
// Copyright (C) 2008 by Trans-Lux All rights reserved.
// 
//---------------------------------------------------------------------

using System;
using System.Collections.Generic;
using System.Text;
using System.Drawing;
using System.Runtime.Serialization;
using System.IO;
using ProWrite.Core;
using ProWrite.Entity.Library;
using ProWrite.Entity.Shape;
using ProWrite.Entity.Library.ImportExport;

namespace ProWrite.Entity.Library.ImportExport
{
    [Serializable]
    public class PlaylistWrapper
    {
        private PlaylistInfo _target;

        private List<FileItem> _images;
        private List<FileItem> _videos;
        private List<MessageInfo> _messages;
        private List<TimeSliceGroupInfo> _timesliceGroups;
        private List<PlaylistInfo> _playlists;
        //private NailImageFileItem _nailItem;
        private List<NailImageFileItem> _nailItems;

        public PlaylistWrapper() { }

        public PlaylistWrapper(PlaylistInfo target)
        {
            _target = target;
        }

        public List<FileItem> Images
        {
            get
            {
                return _images;
            }
        }

        public List<FileItem> Videos
        {
            get
            {
                return _videos;
            }
        }

        public List<MessageInfo> Messages
        {
            get
            {
                return _messages;
            }
        }

        public List<TimeSliceGroupInfo> TimeSliceGroups
        {
            get
            {
                return _timesliceGroups;
            }
        }

        public List<PlaylistInfo> Playlists
        {
            get
            {
                return _playlists;
            }
        }

        [OnSerializing]
        private void Serializing(StreamingContext ctx)
        {
            if (_target == null
                || _target.Items == null
                || _target.Items.Length < 1)
                return;
            _images = new List<FileItem>();
            _videos = new List<FileItem>();
            _messages = new List<MessageInfo>();
            _timesliceGroups = new List<TimeSliceGroupInfo>();
            _playlists = new List<PlaylistInfo>();

            MessageInfo[] messages = _target.AllMessages;
            TimeSliceGroupInfo[] timesliceGroups = _target.AllTimeSliceGroups;
            PlaylistInfo[] playLists = _target.AllPlaylists;

            if (_nailItems == null)
                _nailItems = new List<NailImageFileItem>();

            if (messages != null && messages.Length > 0)
            {
                _messages.AddRange(messages);
                SerializingMessages(_messages);
            }
            if (timesliceGroups != null && timesliceGroups.Length > 0)
            {
                _timesliceGroups.AddRange(timesliceGroups);
                //SerializingTimeSliceGroups(_timesliceGroups);
            }
            if (playLists != null && playLists.Length > 0)
            {
                _playlists.AddRange(playLists);
                SerializingPlaylists(_playlists);
            }
            
            if (_images.Count < 1)
                _images = null;
            if (_videos.Count < 1)
                _videos = null;
            //if (!string.IsNullOrEmpty(_target.ImagePath)
            //    && File.Exists(_target.ImagePath))
            //{
            //    _nailItem = new NailImageFileItem();
            //    _nailItem.MemoryName = _target.Name;
            //    _nailItem.Type = _target.Type;
            //    _nailItem.Content = IOHelper.ReadAllBytes(_target.ImagePath);
            //    _nailItem.Name = Path.GetFileName(_target.ImagePath);
            //}
        }        

        #region Serializing Messages
        private void SerializingMessages(List<MessageInfo> items)
        {
            if (items == null || items.Count == 0)
                return;
            foreach (MessageInfo item in items)
                SerializingMessage(item);
        }

        private void SerializingMessage(MessageInfo message)
        {
            if (message.Items == null || message.Items.Length == 0)
                return;
            FileItem item = null;
            foreach (ShapeLayer layer in message.Items)
            {
                if (layer.Shape == null)
                    continue;
                if (layer.Shape.Type == ShapeType.Image)
                {
                    ShapeImage image = layer.Shape as ShapeImage;
                    if (image == null
                        || image.Image == null
                        || string.IsNullOrEmpty(image.ImageUrl)
                        || !File.Exists(image.ImageUrl))
                        continue;
                    string imageName = Path.GetFileName(image.ImageUrl);

                    byte[] content = IOHelper.ReadAllBytes(image.ImageUrl);

                    item = _images.Find(p => { return p.Name == imageName; });
                    if (item != null)
                    {
                        if (IOHelper.FileContentCompare(item.Content, content))
                            continue;
                        imageName = "_" + imageName;
                    }

                    _images.Add(new FileItem { Id = image.FileHandle, Name = imageName, Path = image.ImageUrl, Content = content, Type = LibraryType.Image });

                }
                else if (layer.Shape.Type == ShapeType.Video)
                {
                    ShapeVideo video = layer.Shape as ShapeVideo;
                    if (video == null
                        || string.IsNullOrEmpty(video.VideoUrl)
                        || !File.Exists(video.VideoUrl))
                        continue;
                    string videoName = Path.GetFileName(video.VideoUrl);

                    byte[] content = IOHelper.ReadAllBytes(video.VideoUrl);

                    item = _videos.Find(p => { return p.Name == videoName; });
                    if (item != null)
                    {
                        if (IOHelper.FileContentCompare(item.Content, content))
                            continue;
                        videoName = "_" + videoName;
                    }

                    _videos.Add(new FileItem { Id = video.FileHandle, Name = videoName, Path = video.VideoUrl, Content = content, Type = LibraryType.Video });
                }
            }

            if (!string.IsNullOrEmpty(message.ImagePath)
                && File.Exists(message.ImagePath))
            {
                NailImageFileItem nailItem = new NailImageFileItem();
                nailItem = new NailImageFileItem();
                nailItem.MemoryName = message.Name;
                nailItem.Type = message.Type;
                nailItem.Content = IOHelper.ReadAllBytes(message.ImagePath);
                nailItem.Name = Path.GetFileName(message.ImagePath);
                _nailItems.Add(nailItem);
            }
        }
        #endregion

        #region Serializing TimeSliceGroups
        private void SerializingTimeSliceGroups(List<TimeSliceGroupInfo> items)
        {
            if (items == null || items.Count == 0)
                return;
            foreach (TimeSliceGroupInfo item in items)
                SerializingTimeSliceGroup(item);
        }

        private void SerializingTimeSliceGroup(TimeSliceGroupInfo group)
        {
            if (group == null || group.Items == null || group.Items.Length == 0)
                return;

            if (!string.IsNullOrEmpty(group.ImagePath)
                && File.Exists(group.ImagePath))
            {
                NailImageFileItem nailItem = new NailImageFileItem();
                nailItem = new NailImageFileItem();
                nailItem.MemoryName = group.Name;
                nailItem.Type = group.Type;
                nailItem.Content = IOHelper.ReadAllBytes(group.ImagePath);
                nailItem.Name = Path.GetFileName(group.ImagePath);
                _nailItems.Add(nailItem);
            }
        }
        #endregion

        #region Serializing Playlists
        private void SerializingPlaylists(List<PlaylistInfo> items)
        {
            if (items == null || items.Count == 0)
                return;
            foreach (PlaylistInfo item in items)
                SerializingPlaylist(item);
        }

        private void SerializingPlaylist(PlaylistInfo playlist)
        {
            if (playlist == null || playlist.Items == null || playlist.Items.Length == 0)
                return;

            if (!string.IsNullOrEmpty(playlist.ImagePath)
                && File.Exists(playlist.ImagePath))
            {
                NailImageFileItem nailItem = new NailImageFileItem();
                nailItem = new NailImageFileItem();
                nailItem.MemoryName = playlist.Name;
                nailItem.Type = playlist.Type;
                nailItem.Content = IOHelper.ReadAllBytes(playlist.ImagePath);
                nailItem.Name = Path.GetFileName(playlist.ImagePath);
                _nailItems.Add(nailItem);
            }
        }
        #endregion

        [OnSerialized]
        private void Serialized(StreamingContext ctx)
        {
            //if (_images != null)
            //{
            //    _images.Clear();
            //    _images = null;
            //}
            //if (_videos != null)
            //{
            //    _videos.Clear();
            //    _videos = null;
            //}
            //if (_nailImage != null)
            //    _nailImage = null;
        }

        private void GenerateNailImage(MemoryLibraryItem item, NailImageFileItem nailItem)
        {
            string sourceName = null;
            string targetName = null;
            if (!string.IsNullOrEmpty(nailItem.Name)
                && nailItem.Content != null
                && nailItem.Content.Length > 0)
            {
                targetName = Constance.LibraryNailImageDir + nailItem.Name;
                if (!File.Exists(targetName))
                    IOHelper.WriteAllBytes(targetName, nailItem.Content);
                else
                {
                    sourceName = targetName;
                    targetName = Constance.LibraryNailImageDir + Guid.NewGuid().ToString().Replace("-", "") + Constance.FileExtensionName.NailImage;
                    IOHelper.WriteAllBytes(targetName, nailItem.Content);

                    //Update playlist nail shape
                    UpdateNailImage(sourceName, targetName, new List<PlaylistInfo>() { _target });
                    UpdateNailImage(sourceName, targetName,  _playlists);
                }

                item.ImagePath = targetName;
            }
        }

        private void UpdateNailImage(string sourceName, string targetName, List<PlaylistInfo> playlists)
        {
            if (playlists == null || playlists.Count == 0)
                return;
            
            _playlists.ForEach(p => { if (p.ImagePath == sourceName) p.ImagePath = targetName; });
        }

        #region Set Target items tree
        private void DeserializedPlaylist()
        {
            if (_target == null || _target.Items == null || _target.Items.Length == 0)
                return;

            _target.Items.ForEach(p =>
                    {
                        switch (p.Type)
                        {
                            case LibraryType.MessageProxy:
                                SetTargetMessage(p);
                                break;
                            case LibraryType.TimeSliceGroupProxy:
                                SetTargetTimeSliceGroup(p);
                                break;
                            case LibraryType.PlaylistProxy:
                                SetTargetPlaylist(p);
                                break;
                        }
                    }
                );
        }

        private void SetTargetMessage(LibraryAdapter adapter)
        {
            if (adapter == null || _messages == null || _messages.Count == 0)
                return;

            adapter.Target = _messages.Find(p => { return p.Id == adapter.TargetId; });
        }

        private void SetTargetTimeSliceGroup(LibraryAdapter adapter)
        {
            if (adapter == null || _timesliceGroups == null || _timesliceGroups.Count == 0)
                return;

            adapter.Target = _timesliceGroups.Find(p => { return p.Id == adapter.TargetId; });

            if (adapter.Target == null)
                return;

            TimeSliceGroupInfo group = adapter.Target as TimeSliceGroupInfo;

            if (group == null || group.Items == null || group.Items.Length == 0)
                return;

            foreach (LibraryAdapter ada in group.Items)
            {
                SetTargetMessage(ada);
            }
        }

        private void SetTargetPlaylist(LibraryAdapter adapter)
        {
            if (adapter == null || _playlists == null || _playlists.Count == 0)
                return;

            adapter.Target = _playlists.Find(p => { return p.Id == adapter.TargetId; });

            if (adapter.Target == null)
                return;

            PlaylistInfo playlist = adapter.Target as PlaylistInfo;

            if (playlist == null || playlist.Items == null || playlist.Items.Length == 0)
                return;

            playlist.Items.ForEach(p =>
            {
                switch (p.Type)
                {
                    case LibraryType.MessageProxy:
                        SetTargetMessage(p);
                        break;
                    case LibraryType.TimeSliceGroupProxy:
                        SetTargetTimeSliceGroup(p);
                        break;
                    case LibraryType.PlaylistProxy:
                        SetTargetPlaylist(p);
                        break;
                }
            }
                );
        }
        #endregion

        private void DeserializedNailImage()
        {
            //Playlist
            //GenerateNailImage(_target as MemoryLibraryItem, _nailItem);

            //Messages
            if (_messages != null && _messages.Count > 0)
            {
                foreach (MessageInfo item in _messages)
                {
                    var nailItem = _nailItems.Find(p => { return p.Type == item.Type && p.MemoryName == item.Name; });
                    if (nailItem != null)
                        GenerateNailImage(item as MemoryLibraryItem, nailItem as NailImageFileItem);
                }
            }

            //TimeSliceGroups
            //if (_timesliceGroups != null && _timesliceGroups.Count > 0)
            //{
            //    foreach (TimeSliceGroupInfo item in _timesliceGroups)
            //    {
            //        var nailItem = _nailItems.Find(p => { return p.Type == item.Type && p.MemoryName == item.Name; });
            //        if (nailItem != null)
            //            GenerateNailImage(item as MemoryLibraryItem, nailItem as NailImageFileItem);
            //    }
            //}

            //Playlists
            if (_playlists != null && _playlists.Count > 0)
            {
                foreach (PlaylistInfo item in _playlists)
                {
                    var nailItem = _nailItems.Find(p => { return p.Type == item.Type && p.MemoryName == item.Name; });
                    if (nailItem != null)
                        GenerateNailImage(item as MemoryLibraryItem, nailItem as NailImageFileItem);
                }
            }
        }

        

        [OnDeserialized]
        private void Deserialized(StreamingContext ctx)
        {
            if (_target == null)
                return;

            if (_nailItems == null || _nailItems.Count == 0)
                return;

            DeserializedNailImage();

            //DeserializedPlaylist();

            //if (_images != null && _images.Count > 0)
            //{
            //    foreach (FileItem item in _images)
            //    {
            //        targetName = Constance.LibraryImageDir + item.Name;
            //        if (!File.Exists(targetName))
            //        {
            //            //IOHelper.WriteAllBytes(targetName, item.Content);
            //            LibraryGroup.Current.AddFile(targetName, Path.GetExtension(targetName).ToLower(), item.Content);
            //        }
            //    }

            //    _images.Clear();
            //    _images = null;
            //}

            //if (_videos != null && _videos.Count > 0)
            //{
            //    foreach (FileItem item in _videos)
            //    {
            //        targetName = Constance.LibraryVideoDir + item.Name;
            //        if (!File.Exists(targetName))
            //        {
            //            //IOHelper.WriteAllBytes(targetName, item.Content);
            //            LibraryGroup.Current.AddFile(targetName, Path.GetExtension(targetName).ToLower(), item.Content);
            //        }
            //    }

            //    _videos.Clear();
            //    _videos = null;
            //}
        }

        public PlaylistInfo Playlist
        {
            get 
            {
                DeserializedPlaylist();
                return _target; 
            }
        }

        public static implicit operator PlaylistInfo(PlaylistWrapper wrapper)
        {
            if (wrapper == null)
                return null;
            return wrapper._target;
        }
    }
}
