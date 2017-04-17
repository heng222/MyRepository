//---------------------------------------------------------------------
//
// File: MessageWrapper.cs
//      
// Description:
//      MessageInfo import and export class
//
// Author: Jerry Xu 2008-11-17
//
// Modify History:
//      Jerry Xu 2008-12-29 Import message:File handle
//                          Update method:Serializing
//      Jerry Xu 2009-1-9   Update methods:Serializing(StreamingContext ctx),Serialized(StreamingContext ctx)
//      Jerry XU 2009-4-27  Update method:Deserialized(StreamingContext ctx),Serializing(StreamingContext ctx)
//                          Add method:DeserializedNailImage()
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
    /// <summary>
    /// MessageInfo import and export class
    /// </summary>
    [Serializable]
    public class MessageWrapper
    {
        private MessageInfo _target;

        private List<FileItem> _images;
        private List<FileItem> _videos;
        private NailImageFileItem _nailItem;
        //private byte[] _nailImage;
        //private string _nailImageName;

        public MessageWrapper() { }

        public MessageWrapper(MessageInfo target)
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

        public NailImageFileItem NailItem
        {
            get { return _nailItem; }
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

            FileItem item = null;
            foreach (ShapeLayer layer in _target.Items)
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

                    _images.Add(new FileItem { Id = image.FileHandle,Name = imageName,Path=image.ImageUrl, Content = content,Type=LibraryType.Image });

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

                    _videos.Add(new FileItem { Id = video.FileHandle, Name = videoName,Path=video.VideoUrl, Content = content, Type = LibraryType.Video });
                }
            }

            if (_images.Count < 1)
                _images = null;
            if (_videos.Count < 1)
                _videos = null;
            if (!string.IsNullOrEmpty(_target.ImagePath)
                && File.Exists(_target.ImagePath))
            {
                _nailItem = new NailImageFileItem();
                _nailItem.MemoryName = _target.Name;
                _nailItem.Type = _target.Type;
                _nailItem.Content = IOHelper.ReadAllBytes(_target.ImagePath);
                _nailItem.Name = Path.GetFileName(_target.ImagePath);
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

        private void DeserializedNailImage()
        {
            //Message
            string targetName = null;
            if (!string.IsNullOrEmpty(_nailItem.Name)
                && _nailItem.Content != null
                && _nailItem.Content.Length > 0)
            {
                targetName = Constance.LibraryNailImageDir + _nailItem.Name;
                if (!File.Exists(targetName))
                    IOHelper.WriteAllBytes(targetName, _nailItem.Content);
                else
                {
                    targetName = Constance.LibraryNailImageDir + Guid.NewGuid().ToString().Replace("-", "") + Constance.FileExtensionName.NailImage;
                    IOHelper.WriteAllBytes(targetName, _nailItem.Content);
                }

                _target.ImagePath = targetName;
            }
        }

        [OnDeserialized]
        private void Deserialized(StreamingContext ctx)
        {
            if (_target == null)
                return;
            if(_nailItem != null)
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

        public MessageInfo Message
        {
            get { return _target; }
        }

        public static implicit operator MessageInfo(MessageWrapper wrapper)
        {
            if (wrapper == null)
                return null;
            return wrapper._target;
        }
    }
}
