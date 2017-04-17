//---------------------------------------------------------------------
//
// File: Layer.cs
//
// Description:
// Frame layer class and relation enums
//
// Author: Kevin
//
// Modify history:
//      Kevin  2008-6-19 Kevin 迁移
//      Kevin  2008-6-23 Add comments
//      Kevin  2008-6-24 用事件代替对FrameLayer 的强依赖
//      Kevin  2008-6-25 移除Layer.cs 文件中 EffectType 的重复定义
//      Kevin  2008-6-25 把Layer.cs 文件 中的PeriodOfTimeType枚举存放到Enums文件中
//      Michael 2008-7-14 修改StartTime
//      Michael 2008-7-15 修改ToVideoLayer()方法
//      Jerry Xu 2009-3-13 Update method:Copy()
//      Jerry Xu 2009-5-22 Insert property:IsEmpty
//                         Insert method:CheckIsEmpty()
//      Jerry Xu 2009-5-25 Update method: ToVideoLayer()
// Copyright (C) 2008 by Trans-Lux All rights reserved.
// 
//---------------------------------------------------------------------
using System;
using System.ComponentModel;
using System.Diagnostics;
using System.Drawing.Design;
using System.IO;
using System.Runtime.Serialization;
using System.Xml.Serialization;
using ProWrite.Core;
using ProWrite.Core.Validation;
using ProWrite.Entity.DES;

namespace ProWrite.Entity.Shape
{
    public interface IShapeLayer
    {
        string Name { get; set; }
        float Duration { get;  }
        float StartTime { get;  }
        float EndTime { get;  }
        bool IsVisible { get; set; }
        bool IsDynamicLayer { get; }
        LayerEffect EmphasisEffect { get; set; }
        LayerEffect EntryEffect { get; set; }
        LayerEffect ExitEffect { get; set; }
        ShapeBase Shape { get; set; }
        int ID { get; }
        IShapeLayer Real { get; }
        IShapeLayer Copy();
        //LayerEffect this[EffectType effectType] { get; }
        void SetEffect(LayerEffect effect, bool isDragDrop);
    }
    /// <summary>
    /// Frame layer class
    /// </summary>
    [Serializable]
    [TypeConverter(typeof(ExpandableObjectConverter))]
    [DebuggerDisplay("Name={Name},Start={StartTime},End={EndTime},Length={Duration},Type={_shape.LayerType}")]
    public class ShapeLayer : DisposableObject, IShapeLayer, ICloneable<ShapeLayer>
    {
        #region Non Serialized Fields
        [XmlIgnore]
        [NonSerialized]
        private EventHandler<PropertyChangedEventArgs> _PropertyChanged;
        #endregion

        #region Serialized Fields
        private LayerEffect __emphasisEffect;
        private LayerEffect __entryEffect;
        private LayerEffect __exitEffect;
        private int _id = 0;
        private ShapeBase _shape;
        private float _startTime = 0f;
        private float _endTime = 0f;
        private string _label;
        bool _IsVisible = true;

        private LayerEffect _emphasisEffect
        {
            get
            {
                if (__emphasisEffect == null)
                    __emphasisEffect = LayerEffect.EmptyEffect(this, EffectType.Emphasis);
                return __emphasisEffect;
            }
            set { __emphasisEffect = value; }
        }

        private LayerEffect _entryEffect
        {
            get
            {
                if (__entryEffect == null)
                    __entryEffect = LayerEffect.EmptyEffect(this, EffectType.Entry);
                return __entryEffect;
            }
            set { __entryEffect = value; }
        }

        private LayerEffect _exitEffect
        {
            get
            {
                if (__exitEffect == null)
                    __exitEffect = LayerEffect.EmptyEffect(this, EffectType.Exit);
                return __exitEffect;
            }
            set { __exitEffect = value; }
        }
        #endregion

        #region Serialized Fields Version 2
        #endregion

        public ShapeLayer() : this(null) { }
        public ShapeLayer(ShapeBase shape)
        {
            Shape = shape;
            if (_shape != null && _shape.Type == ShapeType.ShapeDraw) _IsVisible = _shape.IsVisible;

            __entryEffect = LayerEffect.EmptyEffect(this, EffectType.Entry);
            __emphasisEffect = LayerEffect.EmptyEffect(this, EffectType.Emphasis);
            __exitEffect = LayerEffect.EmptyEffect(this, EffectType.Exit);

        }

        #region Events define

        [Browsable(false)]
        public event EventHandler<PropertyChangedEventArgs> PropertyChanged
        {
            add { _PropertyChanged += value; }
            remove { _PropertyChanged -= value; }
        }

        /// <summary>
        /// Update frame layer control
        /// </summary>
        /// <param name="propertyName">property name</param>
        private void OnPropertyChanged(string propertyName, object newValue, object oldValue)
        {
            //if (_PropertyChanged != null)
            //    _PropertyChanged(this, new PropertyChangedEventArgs(propertyName, newValue, oldValue));
        }
        #endregion

        #region Properties define
        public LayerEffect this[EffectType effectType]
        {
            get
            {
                switch (effectType)
                {
                    case EffectType.Entry:
                        return this._entryEffect;
                    case EffectType.Exit:
                        return this._exitEffect;
                    default:
                        return this._emphasisEffect;
                }
            }
            private set
            {
                switch (effectType)
                {
                    case EffectType.Entry:
                        this._entryEffect = value;
                        break; ;
                    case EffectType.Exit:
                        this._exitEffect = value;
                        break;
                    default:
                        _emphasisEffect = value;
                        break;
                }
            }
        }

        public IShapeLayer Real
        {
            get { return this;}
        }

        /// <summary>
        /// get or set layer id
        /// </summary>
        [Browsable(false)]
        public int ID
        {
            get { return _id; }
            set { _id = value; }
        }

        [Browsable(false)]
        [Category("Shape")]
        public ShapeBase Shape
        {
            get { return _shape; }
            set
            {
                _shape = value;
                if (_shape != null)
                    _shape.Tag = this;
            }
        }


        [Category("Layer")]
        public bool IsVisible
        {
            get { return _IsVisible; }
            set
            {
                if (_IsVisible != value)
                {
                    bool old = _IsVisible;
                    _IsVisible = value;

                    Shape.IsVisible = _IsVisible;
                    OnPropertyChanged(_.IsVisible, _IsVisible, old);
                }
            }
        }

        public bool IsEmpty
        {
            get
            {
                return CheckIsEmpty();
            }
        }

        private bool CheckIsEmpty()
        {
            if (this == null || this.Shape == null || !this.IsVisible)
                return true;

            if (this != null && this.IsVisible && this.Shape != null && this.Shape.Type != ShapeType.Image)
                return false;
            if (this != null && this.IsVisible && this.Shape != null && this.Shape.Type == ShapeType.Image && File.Exists((this.Shape as ShapeImage).ImageUrl))
                return false;

            return true;
        }

        /// <summary>
        /// get or set entry effect
        /// </summary>
        [Category("Effect")]
        [Editor(Constance.Designers.EntryEffect, typeof(UITypeEditor))]
        [TypeConverter(typeof(ExpandableObjectConverter))]
        [XmlIgnore]
        public LayerEffect EntryEffect
        {
            get { return _entryEffect; }
            set
            {
                SetEffect(_entryEffect, value as LayerEffect, true);
            }
        }

        /// <summary>
        /// get or set exit effect
        /// </summary>
        [Category("Effect")]
        [Editor(Constance.Designers.ExitEffect, typeof(UITypeEditor))]
        [TypeConverter(typeof(ExpandableObjectConverter))]
        [XmlIgnore]
        public LayerEffect ExitEffect
        {
            get { return _exitEffect; }
            set
            {
                SetEffect(_exitEffect, value as LayerEffect, true);
            }
        }

        /// <summary>
        /// get or set Emphasis effect
        /// </summary>
        [Category("Effect")]
        [Editor(Constance.Designers.EmphasisEffect, typeof(UITypeEditor))]
        [TypeConverter(typeof(ExpandableObjectConverter))]
        [XmlIgnore]
        public LayerEffect EmphasisEffect
        {
            get { return _emphasisEffect; }
            set
            {
                SetEffect(_emphasisEffect, value as LayerEffect, true);
            }
        }


        /// <summary>
        /// get or set layer label
        /// </summary>
        [Category("Layer")]
        [RequiredValidator]
        public string Name
        {
            get { return _label; }
            set
            {
                if (_label != value)
                {
                    string old = _label;
                    _label = value;
                    OnPropertyChanged(_.Name, value, old);
                }
            }
        }

        /// <summary>
        /// get or set start time of layer
        /// </summary>
        [Category("Layer")]
        public float StartTime
        {
            get
            {
                if (!_entryEffect.IsEmpty)
                    return _entryEffect.StartTime;
                return _emphasisEffect.StartTime;
            }
        }

        [Browsable(false)]
        public float EndTime
        {
            get
            {
                if (!_exitEffect.IsEmpty)
                    return _exitEffect.EndTime;
                return _emphasisEffect.EndTime;
            }
        }

        /// <summary>
        /// get or set duration time of layer
        /// </summary>
        [Category("Layer")]
        public float Duration
        {
            get
            {
                return _entryEffect.Duration + _emphasisEffect.Duration + _exitEffect.Duration;
            }
        }

        [Browsable(false)]
        public bool IsDynamicLayer
        {
            get { return _shape == null ? true : _shape.IsDynamicLayer; }
        }
        #endregion

        #region Internal class define
        public class _
        {
            public const string
                Name = "Name"
                , StartTime = "StartTime"
                , EndTime = "EndTime"
                , Duration = "Duration"
                , EntryEffect = "EntryEffect"
                , ExitEffect = "ExitEffect"
                , EmphasisEffect = "EmphasisEffect"
                , IsVisible = "IsVisible"
                , Left = "Left"
                , Width = "Width"
                ;

            static internal string GetEffectPropertyName(EffectType type)
            {
                switch (type)
                {
                    case EffectType.Entry: return EntryEffect;
                    case EffectType.Exit: return ExitEffect;
                    default: return EmphasisEffect;
                }
            }
        }

        #endregion

        #region Functions define
        public void UpdateSignType(SignType signType)
        {
            if (Shape != null)
                Shape.SignType = signType;
            _entryEffect.UpdateSignType(signType);
            _emphasisEffect.UpdateSignType(signType);
            _exitEffect.UpdateSignType(signType);
        }

        IShapeLayer IShapeLayer.Copy()
        {
            return Copy();
        }

        public ShapeLayer Copy()
        {
            ShapeLayer newLayer = new ShapeLayer();
            newLayer._emphasisEffect = _emphasisEffect.Copy(false) as LayerEffect;
            newLayer._emphasisEffect._layer = newLayer;
            newLayer._endTime = EndTime;
            newLayer._entryEffect = _entryEffect.Copy(false) as LayerEffect;
            newLayer._entryEffect._layer = newLayer;
            newLayer._exitEffect = _exitEffect.Copy(false) as LayerEffect;
            newLayer._exitEffect._layer = newLayer;
            newLayer._label = _label;
            newLayer._startTime = StartTime;
            newLayer._shape = _shape.Copy();
            newLayer._IsVisible = _IsVisible;
            return newLayer;
        }

        public void PartialFromTo(ShapeLayer other)
        {
            _emphasisEffect = other._emphasisEffect.Copy(false) as LayerEffect;
            _entryEffect = other._entryEffect.Copy(false) as LayerEffect;
            _exitEffect = other._exitEffect.Copy(false) as LayerEffect;
            if (_entryEffect.IsEmpty)
                _entryEffect.Width = 0;
            if (_exitEffect.IsEmpty)
                _exitEffect.Width = 0;

            _emphasisEffect.Width = other.EmphasisEffect.Width;
        }

        private void SetEffect(LayerEffect target, LayerEffect source, bool isDragDrop)
        {
            if (source != target)
            {
                var old = target.Copy(false) as LayerEffect;
                old._layer = this;

                LayerEffect @new = null;

                @new = source.Copy(isDragDrop);
                if (isDragDrop) @new.PartFromTo(source);
                else @new.FromTo(source);
                //@new.FromTo(source, isDragDrop);

                @new.ShapeLayer = source.ShapeLayer;

                var type = source.Type;
                this[type] = @new;

                OnPropertyChanged(_.GetEffectPropertyName(type), @new, old);
            }
        }

        public void SetEffect(LayerEffect effect, bool isDragDrop)
        {
            SetEffect(this[effect.Type], effect, isDragDrop);
        }


        protected override void Dispose(bool disposing)
        {
            base.Dispose(disposing);
            if (_shape != null)
            {
                _shape.Dispose();
                _shape = null;
            }
            if (_entryEffect != null)
            {
                _entryEffect.Dispose();
                _entryEffect = null;
            }
            if (_emphasisEffect != null)
            {
                _emphasisEffect.Dispose();
                _emphasisEffect = null;
            }
            if (_exitEffect != null)
            {
                _exitEffect.Dispose();
                _exitEffect = null;
            }
            _label = null;
            _PropertyChanged = null;

        }

     
        public void Accept(IDESPaintVisitor visitor)
        {
            visitor.VisitLayer(this);
        }
               

        [OnDeserialized]
        private void Deserialized(StreamingContext ctx)
        {
            if (_shape != null)
                _shape.Tag = this;
        }
        #endregion
    }
}