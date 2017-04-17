//---------------------------------------------------------------------
//
// File: MessageInfo.cs
//
// Description:
// Message class 
//
// Author: Kevin
//
// Modify history:
//      Kevin  2008-6-19 把实例方法改造成静态方法
//      Kevin  2008-6-23 Add comments and rename Sign to SignMessage
//      Kevin  2008-6-25 rename SignMessage to MessageInfo
//      Jerry Xu 2008-7-7  Add the property of IsActive,its type is bool and its default value is false
//      Jerry Xu 2008-7-8  Add the method:Copy,NewInstance,FromTo,CopyTo
//      Jerry Xu 2008-7-9  Add the method:ToArrayTimeSliceGroupItem,ToArrayTimeSliceGroupItem
//      Jerry Xu 2008-7-17 Delete the property:IsActive
//      Jerry Xu 2008-12-25 Import gif file:AddImageLayer(FileLibraryItem item,int length, SignInfo sign)、Add(FileLibraryItem item, int length, SignInfo sign) 
//      Jerry Xu 2008-12-29 Add method:GetSignSize()
//      Jerry Xu 2008-12-29 Update method:CreateMessage(Size newSign, IVideoGenerator generator)
//      Jerry Xu 2008-12-31 Update method:AddImageLayer(FileLibraryItem item,int length, SignInfo sign)
//      Jerry Xu 2009-1-4   Update method:CreateVideoMessage(IVideoGenerator generator)
//      Jerry Xu 2009-2-5   Update method:CreateMessage(Size newSign, IVideoGenerator generator)
//      Jerry Xu 2009-2-9   Update method:CreateMessage(Size newSign, IVideoGenerator generator)
//      Jerry Xu 2009-2-12  Update method:CreateMessage(Size newSign, IVideoGenerator generator)
//      Jerry Xu 2009-2-18  Update method:InternalFromTo(MessageInfo message)
//      Jerry Xu 2009-2-19  Update method:CreateVideoMessage(IVideoGenerator generator)
//      Jerry Xu 2009-2-25  Update method:CreateVideoMessage(IVideoGenerator generator)
//      Jerry Xu 2009-3-10  Update method:CreateMessage(Size newSign, IVideoGenerator generator)
//      Jerry Xu 2009-3-11  Update method:CreateMessage(Size newSign, IVideoGenerator generator)
//      Jerry Xu 2009-3-11  Add method:GetVirtualBoundsBySign(ShapeBase shape, Size signSize, int Zoom),Populate(SignInfo newSign),
//      Jerry Xu 2009-3-12  Update method:AddImageLayer(FileLibraryItem item,int length, SignInfo sign)
//      Jerry Xu 2009-3-26  Update method:CreateMessage(SignInfo Sign, IVideoGenerator generator),CreateVideoMessage(IVideoGenerator generator),GetSignSize()，CheckSignIsEqual(Size newSign)
//      Jerry Xu 2009-4-2   Update method:CreateMessage(SignInfo Sign, IVideoGenerator generator)
//      Jerry Xu 2009-4-7   Update method:Populate(SignInfo newSign)
//      Jerry Xu 2009-4-28  Add method:CheckIsEmpty()
//                          Update property:IsEmpty
//      Jerry Xu 2009-5-22  Update method:CheckIsEmpty()
//      Jerry Xu 2009-6-8   Update method:InternalFromTo(MessageInfo message)
// Copyright (C) 2008 by Trans-Lux All rights reserved.
// 
//---------------------------------------------------------------------
using System;
using System.Collections.Generic;
using System.Drawing;
using System.Drawing.Imaging;
using ProWrite.Core;
using System.ComponentModel;
using System.Drawing.Design;
using System.IO;
using log4net;
using ProWrite.Entity.Library;
using ProWrite.Entity.Shape;
using System.Xml.Serialization;
using ProWrite.Entity.Dashboard;
using ProWrite.Entity.Settings;
using ProWrite.Entity.DES;
using ProWrite.UFE;
using ProWrite.UFE.Entity;
using System.Runtime.Serialization;
using ProWrite.Entity.Shape.Visitor;

namespace ProWrite.Entity.Library
{
    /// <summary>
    /// Message enitity class
    /// </summary>
    [Serializable]
    [TypeConverter(typeof(ExpandableObjectConverter))]
    public class MessageInfo : MemoryLibraryItem, IEquatable<MessageInfo>
    {
        #region Non Serialized Fields
        [NonSerialized]
        private bool _isValid = true;
        [NonSerialized]
        private EventHandler _onBackColorChange = null;
        [NonSerialized]
        private EventHandler _onEffectChanged = null;
        #endregion

        #region Serialized Fields
        private Size _origSize = Size.Empty;
        private int _Zoom = 1;
        private Color _backColor = Color.Empty;
        private LayerEffect _emphasisEffect;
        private static readonly ILog _log = LogManager.GetLogger(typeof(MessageInfo));
        private List<ShapeLayer> _layers = new List<ShapeLayer>();
        private bool _isVisable = true;
        #endregion

        #region Serialized Fields Version 2
        [OptionalField]
        private int _playValue;
        #endregion

        public event EventHandler OnBackColorChange
        {
            add { _onBackColorChange += value; }
            remove { _onBackColorChange -= value; }
        }

        public event EventHandler OnEffectChanged
        {
            add { _onEffectChanged += value; }
            remove { _onEffectChanged -= value; }
        }

        #region Properties define


        internal void PopulateValiad()
        {
            string fileName = null;
            //foreach (Layer layer in _staticLayers)
            foreach (ShapeLayer layer in _layers)
            {
                if (layer.Shape != null)
                {
                    switch (layer.Shape.Type)
                    {
                        case ShapeType.Image:
                            fileName = (layer.Shape as ShapeImage).ImageUrl;
                            if (!File.Exists(fileName))
                            {
                                _isValid = false;
                                _log.Error(fileName + " has been deleted!");
                            }
                            else if ((layer.Shape as ShapeImage).FileHandle != null)
                                (layer.Shape as ShapeImage).FileHandle = LibraryGroup.Images.GetByPath(fileName).Id;
                            break;
                        case ShapeType.Video:
                            fileName = (layer.Shape as ShapeVideo).VideoUrl;
                            if (!File.Exists(fileName))
                            {
                                _isValid = false;
                                _log.Error(fileName + " has been deleted!");
                            }
                            else
                                (layer.Shape as ShapeVideo).FileHandle = LibraryGroup.Videos.GetByPath(fileName).Id;
                            break;
                    }
                }

            }
        }

        [Browsable(false)]
        public bool IsValid
        {
            get
            {
                return _isValid;
            }
        }

        public override LibraryType AcceptType
        {
            get
            {
                return LibraryType.Image | LibraryType.Video;
            }
        }

        [ReadOnly(true)]
        public override string Name
        {
            get
            {
                return base.Name;
            }
            set
            {
                base.Name = value;
            }
        }


        public override LibraryType Type
        {
            get { return LibraryType.Message; }
        }

        /// <summary>
        /// get or set message board size
        /// </summary>
        [Browsable(false)]
        public Size Size
        {
            get { return _origSize; }
            set { _origSize = value; }
        }

        /// <summary>
        /// get or set message board size
        /// </summary>
        [Browsable(false)]
        public int Zoom
        {
            get { return _Zoom; }
            set { _Zoom = value; }
        }


        /// <summary>
        /// get or set message board size
        /// </summary>
        [Browsable(false)]
        public int PlayValue
        {
            get { return _playValue; }
            set { _playValue = value; }
        }
        /// <summary>
        /// get or set message board BackColor
        /// </summary>
        [Browsable(true)]
        public Color BackColor
        {
            get { return _backColor; }
            set
            {

                if (_backColor != value
                    && value != Color.Transparent)
                {
                    _backColor = value;
                    if (_onBackColorChange != null)
                        _onBackColorChange(this, new EventArgs());
                }
            }
        }

        public Color ConvertedSignBackColor(SignType signType)
        {
            return SignTypeHandler.ConvertToMonoColor(_backColor, signType);
        }

        [Browsable(false)]
        public ShapeLayer[] Items
        {
            get
            {
                return _layers.ToArray();
            }
            set
            {
                _layers.Clear();
                if (value != null)
                    _layers.AddRange(value);
            }
        }

        public void ReverseItems()
        {
            _layers.Reverse();
        }

        public override bool IsEmpty
        {
            get
            {
                return CheckIsEmpty();
                //return _layers.Count == 0;
            }
        }

        private bool CheckIsEmpty()
        {
            if (this == null || this.Length == 0 || _layers == null || _layers.Count == 0)
                return true;

            foreach (ShapeLayer layer in _layers)
            {
                if (layer != null && layer.IsVisible && layer.Shape != null && layer.Shape.Type != ShapeType.Image)
                    return false;
                if (layer != null && layer.IsVisible && layer.Shape != null && layer.Shape.Type == ShapeType.Image && File.Exists((layer.Shape as ShapeImage).ImageUrl))
                    return false;
            }

            return true;
        }

        [Browsable(false)]
        public bool IsVisible
        {
            set { if (value != IsVisible) _isVisable = value; }
            get { return _isVisable; }
        }

        ///<summary>
        ///get or set Emphasis effect
        ///</summary>
        [Category("Effect")]
        [Editor(Constance.Designers.MessageEmphasisEffect, typeof(UITypeEditor))]
        [XmlIgnore]
        public LayerEffect EmphasisEffect
        {
            get
            {
                if (_emphasisEffect == null)
                {
                    ShapeLayer layer = null;
                    _emphasisEffect = LayerEffect.EmptyEffect(layer, EffectType.Emphasis);
                }
                return _emphasisEffect;
            }
            set
            {
                if (value != _emphasisEffect)
                {
                    if (value != null)
                        _emphasisEffect = value.Copy(false) as LayerEffect;
                    else
                        _emphasisEffect = null;
                    if (_onEffectChanged != null)
                        _onEffectChanged(null, EventArgs.Empty);
                }
            }
        }

        [Browsable(false)]
        public SignType? SignType
        {
            get
            {
                if (_layers.Count == 0)
                    return null;

                return _layers[0].Shape.SignType;
            }
        }
        #endregion

        #region Functions define

        public void UpdateSignType(SignType signType)
        {
            foreach (var item in _layers)
                item.UpdateSignType(signType);
        }

        private bool CanDeleteFile(FileLibraryItem item)
        {
            string fileName = null;

            //foreach (Layer layer in _staticLayers)
            foreach (ShapeLayer layer in _layers)
            {
                switch (item.Type)
                {
                    case LibraryType.Image:
                        if (layer.Shape.Type == ShapeType.Image)
                            fileName = (layer.Shape as ShapeImage).ImageUrl;
                        break;
                    case LibraryType.Video:
                        if (layer.Shape.Type == ShapeType.Video)
                            fileName = (layer.Shape as ShapeVideo).VideoUrl;
                        break;
                }

                if (string.Equals(fileName, item.Path, StringComparison.OrdinalIgnoreCase))
                {
                    return true;
                }
            }

            return false;
        }

        //public bool IsCreateVideo()
        //{
        //    bool result = false;
        //    foreach (ShapeLayer layer in Items)
        //    {
        //        if (layer.Shape.VideoType == LayerType.Video)
        //        {
        //            result = true;
        //            break;
        //        }
        //        if (layer.Shape.Type == ShapeType.Image && ((ShapeImage)layer.Shape).IsGif & IsMultiFrameImageLayer(layer))
        //        {
        //            result = true;
        //            break;
        //        }
        //    }
        //    return result;
        //}

        //private bool IsMultiFrameImageLayer(ShapeLayer layer)
        //{
        //    if (layer.Shape.Type != ShapeType.Image)
        //        return false;
        //    Image gif = Image.FromFile(((ShapeImage)layer.Shape).ImageUrl);
        //    FrameDimension fd = new FrameDimension(gif.FrameDimensionsList[0]);

        //    //获取帧数(gif图片可能包含多帧，其它格式图片一般仅一帧)
        //    int count = gif.GetFrameCount(fd);
        //    if (count > 1)
        //        return true;
        //    return false;
        //}


        public override bool IsReferenceLibrary(LibraryItem library)
        {
            if (library == null)
                return false;
            if ((AcceptType & library.Type) != library.Type)
                return false;

            return CanDeleteFile(library as FileLibraryItem);
        }

        public void AddRange(IShapeLayer[] items)
        {
            _layers.Clear();
            if (items == null || items.Length < 1)
                return;
            foreach (var item in items)
                _layers.Add(item.Copy() as ShapeLayer);
        }

        public bool Add(FileLibraryItem item, SignInfo sign)
        {
            ShapeLayer layer = null;
            if (item.Type == LibraryType.Image)
                layer = AddImageLayer(item, sign);
            else if (item.Type == LibraryType.Video)
                layer = AddVideoLayer(item, sign);
            if (layer != null)
            {
                Add(layer);
                return true;
            }
            return false;
        }

        public bool Add(FileLibraryItem item, int length, SignInfo sign)
        {
            ShapeLayer layer = null;
            if (item.Type == LibraryType.Image)
                layer = AddImageLayer(item, length, sign);
            else if (item.Type == LibraryType.Video)
                layer = AddVideoLayer(item, length, sign);
            if (layer != null)
            {
                Add(layer);
                return true;
            }
            return false;
        }

        private ShapeLayer AddImageLayer(FileLibraryItem item, SignInfo sign)
        {
            if (item == null || sign == null)
                return null;

            ShapeImage shape = new ShapeImage();
            if (!SetSignInfo(shape, sign))
                return null;
            shape.ImageUrl = item.Path;

            shape.IsBackground = true;
            shape.OldVirtualBound = new System.Drawing.Rectangle(0, 0, sign.Width / 2, sign.Height / 2);
            shape.FileHandle = item.Id;
            //shape.ComputeDestBoundBatchLoad();
            ShapeLayer layer = new ShapeLayer(shape);
            layer.Name = "Layer 1";
            //layer.EmphasisEffect.StartTime = 0;
            //layer.EmphasisEffect.EndTime = long.Parse(sign.Template.Message.DisplayTime.ToString());
            layer.EmphasisEffect.Left = 0;
            layer.EmphasisEffect.Width = sign.Template.Message.DisplayTime * Constance.Effect.UnitWidth;
            shape.ComputeDestBoundBatchLoad();
            return layer;
        }

        private ShapeLayer AddImageLayer(FileLibraryItem item, int length, SignInfo sign)
        {
            if (item == null || sign == null)
                return null;

            ShapeImage shape = new ShapeImage();
            if (!SetSignInfo(shape, sign))
                return null;
            shape.ImageUrl = item.Path;

            shape.IsBackground = true;
            shape.OldVirtualBound = new System.Drawing.Rectangle(0, 0, sign.Width / 2, sign.Height / 2);
            //shape.ComputeDestBoundBatchLoad();
            shape.FileHandle = item.Id;
            if (length == -1)
                shape.IsGif = true;
            ShapeLayer layer = new ShapeLayer(shape);
            layer.Name = "Layer 1";
            //layer.EmphasisEffect.StartTime = 0;
            //layer.EmphasisEffect.EndTime = long.Parse(sign.Template.Message.DisplayTime.ToString());
            //layer.EmphasisEffect.Duration = sign.Template.Message.DisplayTime;
            layer.EmphasisEffect.Left = 0;
            layer.EmphasisEffect.Width = sign.Template.Message.DisplayTime * Constance.Effect.UnitWidth;

            shape.Image = Image.FromFile(item.Path);

            shape.ComputeDestBoundBatchLoad();
            return layer;
        }

        private ShapeLayer AddVideoLayer(FileLibraryItem item, int length, SignInfo sign)
        {
            if (item == null || sign == null)
                return null;

            ShapeVideo shape = new ShapeVideo();
            if (!SetSignInfo(shape, sign))
                return null;
            shape.VideoUrl = item.Path;
            shape.IsBackground = true;
            shape.OldVirtualBound = new System.Drawing.Rectangle(0, 0, sign.Width / 2, sign.Height / 2);
            shape.FileHandle = item.Id;

            ShapeLayer layer = new ShapeLayer(shape);
            layer.Name = "Layer 1";
            //layer.EmphasisEffect.StartTime = 0;
            //layer.EmphasisEffect.EndTime = long.Parse(length.ToString());
            //layer.EmphasisEffect.Duration = length;// sign.Template.Message.DefaultLength;
            layer.EmphasisEffect.Left = 0;
            layer.EmphasisEffect.Width = sign.Template.Message.DisplayTime * Constance.Effect.UnitWidth;
            return layer;
        }

        private ShapeLayer AddVideoLayer(FileLibraryItem item, SignInfo sign)
        {
            if (item == null || sign == null)
                return null;

            ShapeVideo shape = new ShapeVideo();
            if (!SetSignInfo(shape, sign))
                return null;
            shape.VideoUrl = item.Path;
            shape.IsBackground = true;
            shape.OldVirtualBound = new System.Drawing.Rectangle(0, 0, sign.Width / 2, sign.Height / 2);
            shape.FileHandle = item.Id;

            ShapeLayer layer = new ShapeLayer(shape);
            layer.Name = "Layer 1";
            layer.EmphasisEffect.Duration = sign.Template.Message.DisplayTime;

            return layer;
        }

        private bool SetSignInfo(ShapeBase shape, SignInfo sign)
        {
            if (shape == null || sign == null)
                return false;
            MessageTemplate message = sign.Template.Message;
            shape.Populate(new System.Drawing.Point(message.LocationX, message.LocationY), new Size(sign.Width, sign.Height), sign.Type, new Size(sign.Width, sign.Height), message.Zoom);
            return true;
        }


        public void Add(ShapeLayer item)
        {

            _layers.Add(item);
        }

        public void Insert(ShapeLayer item, int index)
        {
            if (index >= 0 && index <= _layers.Count)
                _layers.Insert(index, item);
        }

        public bool Delete(ShapeLayer item)
        {
            return _layers.Remove(item);
        }

        public bool Contains(ShapeLayer item)
        {
            return _layers.Contains(item);
        }
        #region IEquatable<MessageInfo> Members

        public bool Equals(MessageInfo other)
        {
            if (other == null)
                return false;

            return true;
        }

        #endregion

        public override bool Equals(object obj)
        {
            return Equals(obj as MessageInfo);
        }

        /// <summary>
        /// Function: Init a new instance of this object
        /// Author  : Jerry Xu
        /// Date    : 2008-7-8 
        /// </summary>
        /// <returns>MemoryLibraryItem(MessageInfo)</returns>
        public override MemoryLibraryItem NewInstance()
        {
            return new MessageInfo();
        }

        //public bool CheckSignIsEqual(Size newSign)
        //{
        //    if (_layers[0].Shape.SignSize == newSign)
        //        return true;
        //    return false;
        //}

        //public System.Drawing.Rectangle GetVirtualBoundsBySign(ShapeBase shape, Size signSize, int Zoom)
        //{
        //    int width = signSize.Width / 4;
        //    int height = signSize.Height / 8;
        //    System.Drawing.Point location = System.Drawing.Point.Empty;

        //    decimal oldSizeRatio = decimal.Divide(shape.SignSize.Width, shape.SignSize.Height);
        //    decimal newSizeRatio = decimal.Divide(signSize.Width, signSize.Height);
        //    decimal tempZoom;
        //    int newWidth = 0, newHeight = 0;
        //    int widthOffset = 0, heightOffset = 0;
        //    if (oldSizeRatio <= newSizeRatio)
        //    {
        //        tempZoom = decimal.Divide(signSize.Height, shape.SignSize.Height);
        //        newWidth = (int)Math.Round(shape.SignSize.Width * tempZoom * Zoom);
        //        widthOffset = (int)Math.Round((double)(signSize.Width * Zoom - newWidth) / 2);
        //        location = new System.Drawing.Point(widthOffset + (int)(shape.LocationX * tempZoom * Zoom), (int)(shape.LocationY * tempZoom * Zoom));
        //    }
        //    else
        //    {
        //        tempZoom = decimal.Divide(signSize.Width, shape.SignSize.Width);
        //        newHeight = (int)Math.Round(shape.SignSize.Height * tempZoom * Zoom);
        //        heightOffset = (int)Math.Round((double)(signSize.Height * Zoom - newHeight) / 2);
        //        location = new System.Drawing.Point((int)(shape.LocationX * tempZoom * Zoom), heightOffset + (int)(shape.LocationY * tempZoom * Zoom));
        //    }
        //    width = (int)(shape.Width * tempZoom * Zoom);
        //    height = (int)(shape.Height * tempZoom * Zoom);
        //    return new System.Drawing.Rectangle(location, new Size(width, height));
        //}

        //public void Populate(SignInfo newSign)
        //{
        //    float _widthScale = 1;
        //    float _heightScale = 1;
        //    int wn = (int)Math.Round(Size.Width * 1.0f / newSign.Width);
        //    int hn = (int)Math.Round(Size.Height * 1.0f / newSign.Height);
        //    Size = newSign;
        //    _widthScale = wn;
        //    _heightScale = hn;
        //    int zoom = 1;
        //    zoom = wn < hn ? wn : hn;
        //    zoom = zoom < 1 ? 1 : zoom;

        //    MessageInfo mes = this;
        //    foreach (ShapeLayer sl in mes.Items)
        //    {
        //        sl.Shape.VirtualBounds = Common.CommonHelper.GetRectangleBySign(sl.Shape.VirtualBounds, sl.Shape.SignSize, _playlistControl._signSize, mes.Zoom);
        //        sl.Shape.DestBounds = Common.CommonHelper.GetRectangleBySign(sl.Shape.DestBounds, sl.Shape.SignSize, _playlistControl._signSize, mes.Zoom);
        //        if (sl.Shape.Type == ShapeType.ShapeDraw)
        //        {
        //            foreach (ShapePaint s in (sl.Shape as ShapeDraw).Childs)
        //            {
        //                s.VirtualBounds = GetVirtualBoundsBySign(s, new Size(newSign.Width, newSign.Height), zoom);
        //                s.Zoom = 1;
        //                s.Populate(s.VirtualLocation, s.VirtualBounds.Size, newSign.Type, new Size(newSign.Width, newSign.Height), zoom);
        //            }
        //            (sl.Shape as ShapeDraw).PopulateSignInfo(newSign.Type, new Size(newSign.Width, newSign.Height), zoom);
        //            (sl.Shape as ShapeDraw).Zoom = 1;
        //        }
        //        else
        //        {
        //            sl.Shape.VirtualBounds = System.Drawing.Rectangle.Empty;
        //            sl.Shape.Zoom = 1;
        //            sl.Shape.VirtualBounds = GetVirtualBoundsBySign(sl.Shape, new Size(newSign.Width, newSign.Height), zoom);

        //            sl.Shape.Populate(sl.Shape.VirtualLocation, sl.Shape.VirtualBounds.Size, newSign.Type, new Size(newSign.Width, newSign.Height), zoom);
        //            if (sl.Shape.Type == ShapeType.Image)
        //                (sl.Shape as ShapeImage).ComputeDestBoundBatchLoad();
        //            if (sl.Shape.Type == ShapeType.Video)
        //                (sl.Shape as ShapeVideo).ComputeDestBound();
        //            sl.Shape.DestBounds = Common.CommonHelper.GetRectangleBySign(sl.Shape.DestBounds, sl.Shape.SignSize, _playlistControl._signSize, _playlistControl._Zoom);
        //        }

        //        sl.Shape.VirtualBounds = Common.CommonHelper.GetRectangleBySign(sl.Shape.VirtualBounds, sl.Shape.SignSize, _playlistControl._signSize, _playlistControl._Zoom);

        //    }
        //    mes.Zoom = zoom;
        //}

        //public void SetZoom(Size newSign)
        //{
        //    int wn = (int)Math.Round(Size.Width * 1.0f / newSign.Width);
        //    int hn = (int)Math.Round(Size.Height * 1.0f / newSign.Height);
        //    _Zoom = wn < hn ? wn : hn;
        //    _Zoom = _Zoom < 1 ? 1 : _Zoom;
        //}

        //public MessageInfo GetMessage()
        //{
        //    if (this == null || this.Items == null || this.Length == 0 || this.Items.Length == 0)
        //        return null;
        //    List<ShapeLayer> layers = new List<ShapeLayer>();
        //    foreach (ShapeLayer layer in this.Items)
        //    {
        //        if (layer.Shape != null && layer.IsVisible && layer.Shape.IsVisible)
        //            layers.Add(layer);
        //    }
        //    if (layers.Count == 0)
        //        return null;

        //    MessageInfo message = this.Copy() as MessageInfo;
        //    message.Items = layers.ToArray();
        //    return message;

        //}


        ///// <summary>
        ///// Function: Create MessageInfo by MessageInfo and Sign.Size
        ///// Author  : Jerry Xu
        ///// Date    : 2008-12-2
        ///// </summary>
        ///// <param name="generator">generatorVideo</param>
        ///// <param name="newSign">Sign.Size</param>
        ///// <returns>MessageInfo</returns>
        //public MessageInfo CreateMessage(SignInfo Sign, IVideoGenerator generator)
        //{
        //    Size newSign = new Size(Sign.Width, Sign.Height);
        //    bool isEqualSign = CheckSignIsEqual(newSign);

        //    MessageInfo newMessage = null;

        //    //Reverse layers
        //    newMessage = this.Copy() as MessageInfo;



        //    var items = this._layers;
        //    ShapeLayer layer = null;
        //    for(int i=0;i<items.Count;i++) 
        //    {
        //        layer = items[i];

        //        if (layer.Shape.Type == ShapeType.Video)
        //        {
        //            if (string.IsNullOrEmpty((layer.Shape as ShapeVideo).VideoUrl))
        //            {
        //                //newMessage._layers.RemoveAt(i);
        //                newMessage._layers.Remove(newMessage._layers.Find(p => { return p.ID == layer.ID; }));
        //                continue;
        //            }

        //        }
        //        else
        //            if (layer.Shape.Type == ShapeType.Image)
        //            {
        //                if (string.IsNullOrEmpty((layer.Shape as ShapeImage).ImageUrl))
        //                {
        //                    //newMessage._layers.RemoveAt(i);
        //                    newMessage._layers.Remove(newMessage._layers.Find(p => { return p.Name == layer.Name; }));
        //                    continue;
        //                }
        //            }

        //        //if (!layer.IsVisible || layer.Shape == null || !layer.Shape.IsVisible)
        //        if (!layer.IsVisible || layer.Shape == null || layer.Duration==0)
        //            newMessage._layers.Remove(newMessage._layers.Find(p => { return p.Name == layer.Name; }));
        //            //newMessage._layers.RemoveAt(i);
        //    }
        //    newMessage._layers.Reverse();


        //    bool isCreateVideo = newMessage.IsCreateVideo();

        //    if (isEqualSign && !isCreateVideo)
        //    {
        //        newMessage.Size = GetSignSize();
        //        return newMessage;
        //    }

        //    //ReInit all message elements by new sign.size
        //    if (!isEqualSign)
        //    {
        //        //newMessage.SetZoom(newSign);
        //        newMessage.Populate(Sign);
        //    }

        //    if (isCreateVideo)
        //        newMessage = newMessage.CreateVideoMessage(generator);

        //    newMessage.Size = GetSignSize();
        //    return newMessage;
        //}


        ///// <summary>
        ///// Function: Get sign size
        ///// Author  : Jerry Xu
        ///// Date    : 2008-12-29
        ///// </summary>
        ///// <returns>Sign Size</returns>
        //public Size GetSignSize()
        //{
        //    //int w = Convert.ToInt32(Math.Ceiling(_origSize.Width * 1.0d / Zoom));
        //    //int h = Convert.ToInt32(Math.Ceiling(_origSize.Height * 1.0 / Zoom));
        //    int w = _layers[0].Shape.SignSize.Width;
        //    int h = _layers[0].Shape.SignSize.Height;
        //    return new Size(w,h);
        //}

        //private void SetElemets()
        //{
        //    if (_layers != null && _layers.Count > 0)
        //    {
        //        foreach (ShapeLayer layer in _layers)
        //        {
        //            if (layer.Shape != null)
        //            {
        //                layer.Shape.Zoom = _Zoom;
        //            }
        //        }
        //    }
        //}

        ///// <summary>
        ///// Function: Create video message 
        ///// Author  : Jerry Xu
        ///// Date    : 2008-12-3 
        ///// </summary>
        ///// <returns>MemoryLibraryItem(MessageInfo)</returns>
        //private MessageInfo CreateVideoMessage(IVideoGenerator generator)
        //{
        //    string fileID = Guid.NewGuid().ToString().Replace("-", "");
        //    string fileName = LocalFilePathMapping.GetFile(FileType.Video, fileID);


        //    MessageInfo message = this.Copy() as MessageInfo;
        //    List<ShapeLayer> layers = new List<ShapeLayer>();

        //    float startTime = 0;
        //    float endTime = 0;
        //    bool first = true;
        //    //Dynamic layers
        //    foreach (var item in message.Items)
        //    {
        //        if (item.Shape.Type == ShapeType.DynamicText || item.Shape.Type == ShapeType.Time || item.Shape.Type == ShapeType.Temperature)
        //        {

        //            layers.Add(item.Copy() as ShapeLayer);
        //        }
        //        else
        //        {
        //            if (first)
        //            {
        //                first = false;
        //                startTime = item.StartTime;
        //                endTime = item.EndTime;
        //            }
        //            else
        //            {
        //                if (item.StartTime < startTime)
        //                    startTime = item.StartTime;
        //                if (item.EndTime > endTime)
        //                    endTime = item.EndTime;
        //            }

        //        }
        //    }            

        //    //Video layer
        //    if(!generator.CreateVideo(this, fileName))
        //        throw new Exception("Generate video file is failure!");

        //    generator = null;

        //    ShapeLayer layer = new ShapeLayer();
        //    ShapeVideo shape = new ShapeVideo();
        //    //layer.EmphasisEffect.StartTime = long.Parse(startTime.ToString());
        //    //layer.EmphasisEffect.EndTime = long.Parse(endTime.ToString()); //long.Parse(message.Length.ToString());
        //    layer.EmphasisEffect.Left = (int)startTime * Constance.Effect.UnitWidth;
        //    layer.EmphasisEffect.Width = (int)endTime * Constance.Effect.UnitWidth;

        //    Size size = this.GetSignSize(); 
        //    shape.VideoUrl = fileName;
        //    shape.DestBounds = new System.Drawing.Rectangle(0, 0, size.Width, size.Height);
        //    //shape.LocationX = 0;
        //    //shape.LocationY = 0;
        //    //shape.Size = GetSignSize();            
        //    //shape.Rect.OffsetX = 0;
        //    //shape.Rect.OffsetY = 0;
        //    //shape.Rect.Width = shape.Size.Width;
        //    //shape.Rect.Height = shape.Size.Height;

        //    shape.VideoFileID = fileID;
        //    layer.Shape = shape.Copy();
        //    layers.Add(layer);

        //    message.Items = layers.ToArray();

        //    return message;
        //}

        /// <summary>
        /// Function: Get data from a object to current object
        /// Author  : Jerry Xu
        /// Date    : 2008-7-8 
        /// </summary>
        /// <param name="memory">MemoryLibraryItem</param>
        public override void FromTo(MemoryLibraryItem memory)
        {
            base.FromTo(memory);

            InternalFromTo(memory as MessageInfo);
        }

        private void InternalFromTo(MessageInfo message)
        {
            Size = message.Size;
            //_imagePath = message._imagePath;
            _isValid = message._isValid;
            _origSize = message._origSize;
            _Zoom = message._Zoom;
            _backColor = message._backColor;
            _isVisable = message._isVisable;
            _playValue = message._playValue;
            if (message._emphasisEffect != null)
            {
                _emphasisEffect = message._emphasisEffect.Copy(false) as LayerEffect;
                _emphasisEffect.Duration = long.Parse(message.Length.ToString());
            }
            AddRange(message.Items);
        }

        public override void FromTo(ILockLibraryItem locker, int lockCounter)
        {
            base.FromTo(locker, lockCounter);
            InternalFromTo(locker as MessageInfo);
        }

        public List<IFileHandle> GetFileHandle(string handle, ShapeType type)
        {
            List<IFileHandle> result = new List<IFileHandle>();
            if (_layers == null || _layers.Count < 1)
                return result;

            foreach (var layer in _layers)
            {
                if (layer == null || layer.Shape == null || layer.Shape.Type != type)
                    continue;
                IFileHandle tmp = layer.Shape as IFileHandle;
                if (tmp != null && tmp.FileHandle == handle)
                    result.Add(tmp);
            }
            return result;
        }



        public object[] ToArrayTimeSliceGroupItem()
        {
            return new object[] { false, Name, Type, LengthText };
        }

        public override LibraryAdapter ToProxy()
        {
            return new MessageAdapterInfo(this);
        }

        public void Accept(IResetSignVisitor visitor)
        {
            if (visitor != null)
                visitor.VisitMessage(this);
        }

        public override int GetHashCode()
        {
            return base.GetHashCode();
        }

        protected override void Dispose(bool disposing)
        {
            base.Dispose(disposing);
            //_imagePath = null;
            //if (_image != null)
            //{
            //    _image.Dispose();
            //    _image = null;
            //}
            if (_layers != null)
            {
                int length = _layers.Count;
                if (length > 0)
                {
                    for (int i = 0; i < length; i++)
                    {
                        _layers[i].Dispose();
                        _layers[i] = null;
                    }
                    _layers.Clear();
                    _layers = null;
                }
            }
            _emphasisEffect = null;
        }
        #endregion

    }
}
