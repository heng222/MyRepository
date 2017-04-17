//---------------------------------------------------------------------
//
// File: TimeSliceGroupWrapper.cs
//      
// Description:
//      TimeSliceGroupInfo import/export class
//
// Author: Jerry Xu 2008-11-17
//
// Modify History:
//      Jerry Xu 2009-4-20 Update method:SerializingMessage(MessageInfo message)
//      Jerry Xu 2009-4-27 Update method:Serializing(StreamingContext ctx),Deserialized(StreamingContext ctx)
//                         Add method:SerializingMessage(MessageInfo message),
//                                  GenerateNailImage(MemoryLibraryItem item, NailImageFileItem nailItem)
//                                  DeserializedNailImage()
//
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
    public class TimeSliceGroupWrapper
    {
        private TimeSliceGroupInfo _target;

        private List<FileItem> _images;
        private List<FileItem> _videos;
        private List<MessageInfo> _messages;
        private NailImageFileItem _nailItem;
        private List<NailImageFileItem> _nailItems;

        public TimeSliceGroupWrapper() { }

        public TimeSliceGroupWrapper(TimeSliceGroupInfo target)
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

        public NailImageFileItem NailItem
        {
            get { return _nailItem; }
        }


        public List<NailImageFileItem> NailItems
        {
            get
            {
                return _nailItems;
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

            MessageInfo message = null;
            MessageInfo temp = null;

            _nailItems = new List<NailImageFileItem>();
            foreach (MessageAdapterInfo adapter in _target.Items)
            {
                if (adapter != null && adapter.Target != null && (adapter.Target as MessageInfo).Items != null && (adapter.Target as MessageInfo).Items.Length > 0)
                {
                    message = adapter.Target as MessageInfo;
                    temp = _messages.Find(p => { return p.Name == message.Name; });
                    if (temp != null)
                    {                      
                       continue;                 
                    }                    
                    _messages.Add(message);
                    SerializingMessage(message);
                }
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

        private void SerializingMessage(MessageInfo message)
        {
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
        }

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
                    targetName = Constance.LibraryNailImageDir + Guid.NewGuid().ToString().Replace("-", "") + Constance.FileExtensionName.NailImage;
                    IOHelper.WriteAllBytes(targetName, nailItem.Content);
                }

                item.ImagePath = targetName;
            }
        }

        private void DeserializedNailImage()
        {
            //TimeSliceGroup
            //if(_nailItem != null)
            //    GenerateNailImage(_target as MemoryLibraryItem, _nailItem);

            //Messages
            if(_messages == null || _messages.Count==0)
                return;
            foreach (MessageInfo item in _messages)
            {
                var nailItem = _nailItems.Find(p => { return p.Type == item.Type && p.MemoryName == item.Name; });
                if (nailItem != null)
                    GenerateNailImage(item as MemoryLibraryItem, nailItem as NailImageFileItem);
            }
        }

        [OnDeserialized]
        private void Deserialized(StreamingContext ctx)
        {
            if (_target == null)
                return;

            DeserializedNailImage();



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

        public TimeSliceGroupInfo Group
        {
            get { return _target; }
        }

        public static implicit operator TimeSliceGroupInfo(TimeSliceGroupWrapper wrapper)
        {
            if (wrapper == null)
                return null;
            return wrapper._target;
        }
    }
}
