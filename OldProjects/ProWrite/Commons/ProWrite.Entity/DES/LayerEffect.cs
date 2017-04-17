//---------------------------------------------------------------------
//
// File: LayerEffect.cs
//
// Description:
//  
//
// Author: 
//
// DateTime:
//
// Modify history:
//      Jerry Xu 2009-1-12 Update method:Deserialized(StreamingContext ctx)
//      Jerry Xu 2009-3-3  Update method:FromTo(LayerEffect effect)
//      Jerry Xu 2009-4-10 Update property:Width,Duration
//                         Delete property:AllDuration
//                         Update method:FromTo(LayerEffect effect)
//      Jerry Xu 2009-5-21 Update property:Duration is readonly
//
// Copyright (C) 2008 by Trans-Lux All rights reserved.
// 
//---------------------------------------------------------------------

using System;
using System.Collections.Generic;
using System.Text;
using System.ComponentModel;
using System.Xml.Serialization;
using ProWrite.Core;
using System.Runtime.Serialization;
using ProWrite.Entity.DES;
using ProWrite.Entity.Shape;
using PropertyChangedEventArgs=ProWrite.Entity.PropertyChangedEventArgs;
using System.Drawing;
using System.Diagnostics;

namespace ProWrite.Entity.DES
{
	[Serializable]
    [DebuggerDisplay("Name={Name},Type={Type},Width={Width},Left={Left},Duration={Duration}")]
    public abstract class LayerEffect : DisposableObject, IEquatable<LayerEffect>, IEditableObject,IDisposable,ILayerEffect
	{
        public abstract LayerEffect Copy(bool isAddNewEffect);
        public abstract LayerEffect Copy();
        public abstract LayerEffect Create();
        public abstract Property[] ToPropertyArray();
        public virtual object ToUFEEffect() { return null; }
        [Browsable(false)]
        public virtual Property[] UFEEffect { get { return null; } }

        public string ColorToString(Color _color)
        {
            //SignType? signType = null;
            //if (Layer != null && Layer.Shape != null)
            //    signType = Layer.Shape.SignType;
            //else
            //    signType = SignType.RGB;

            return ConverterHelper.ColorToHexString(_color);
            //return _color.ToString();
        }

        public enum Kinds
        {
            Snow,
            Rain,
            Bijou,
            Sparkle,
            Flash,
            WrapAround,

            Bounce,
            Coalesce,
            BlackHole,
            Fade,
            Filter,
            Slot,
            Interleave,
            Line,
            MultiWipe,
            Push,
            Radar,
            Venetian,
            Travel,

            Copy,
            Slide,
            Wipe
        }

		[XmlIgnore]
		[NonSerialized]
		public EventHandler<PropertyChangedEventArgs> PropertyChanged;

		/// <summary>
		/// Update frame layer controlzoo
		/// </summary>
		/// <param name="propertyName">property name</param>
		private void OnPropertyChanged(string propertyName, object newValue, object oldValue)
		{
            //if (IsEdit)
            //    return;
            //if (PropertyChanged != null && (_layer != null/* || _masterLayer != null*/))
            //    PropertyChanged(this, new PropertyChangedEventArgs(propertyName, newValue, oldValue));
		}

        [NonSerialized]
        private int _editLevel = 0;
        [Browsable(false)]
        public bool IsEdit
        {
            get { return _editLevel > 0; }
        }

        #region IEditableObject Members

        public void BeginEdit()
        {
            _editLevel++;
        }

        public void CancelEdit()
        {
            _editLevel--;
        }

        public void EndEdit()
        {
            _editLevel--;
        }

        #endregion

		[NonSerialized]
		internal ShapeLayer _layer;
        //[NonSerialized]
        //internal ShapeMasterLayer _masterLayer;

        public ShapeLayer Layer { get { return _layer; } set { _layer = value; } }

        private EffectType _type = EffectType.Entry;
        public LayerEffect() { }

        public LayerEffect(EffectType type, ShapeLayer layer)
        {
            _layer = layer;
            Init(type);
        }

        //public LayerEffect(EffectType type, ShapeMasterLayer masterLayer)
        //{
        //    _masterLayer = masterLayer;
        //    Init(type);
        //}

        [Serializable]
        private class EmptyEffect1 : LayerEffect
        {
            public EmptyEffect1(EffectType type, ShapeLayer layer) : base(type, layer) { }

            //public EmptyEffect1(ShapeMasterLayer masterLayer, EffectType type) : base(type, masterLayer) { }

            public override Property[] ToPropertyArray()
            {
                return null;
            }

            public override LayerEffect Create()
            {
                return new EmptyEffect1(_type, _layer);
            }

            public override LayerEffect Copy(bool isAddNewEffect)
            {
                var clone = new EmptyEffect1(_type, _layer);
                clone.FromTo(this, isAddNewEffect);
                return clone;
            }

            public override LayerEffect Copy()
            {
                var clone = new EmptyEffect1(_type, _layer);
                clone.FromTo(this);
                return clone;
            }

            public override void FromTo(LayerEffect effect)
            {
                base.FromTo(effect);
            }
        }

        //public static LayerEffect EmptyEffect(ShapeMasterLayer layer)
        //{
        //    var effect = new EmptyEffect1(layer, EffectType.None);
        //    effect._name = "None";
        //    return effect;
        //}

        public static LayerEffect EmptyEffect(ShapeLayer layer)
        {
            var effect = new EmptyEffect1(EffectType.None,layer);
            effect._name = "None";
            return effect;
        }

        public static LayerEffect EmptyEffect(ShapeLayer layer, EffectType type)
        {
            var effect = new EmptyEffect1(type, layer);
            effect._name = "None";
            return effect;
        }

        //public static LayerEffect EmptyEffect(ShapeMasterLayer masterLayer, EffectType type)
        //{
        //    var effect = new EmptyEffect1(masterLayer, type);
        //    effect._name = "None";
        //    return effect;
        //}

        public const string NoneString = "None";

        protected void Init(EffectType type)
        {
            _type = type;
            _StartTime = 0;
            _left = 0;
            switch (type)
            {
                case EffectType.Entry:
                    _EndTime = 0;
                    _width = (int)_EndTime * Constance.TrackBar.UnitWidth;
                    break;
                case EffectType.Emphasis:
                    _EndTime = 0;
                    _width = (int)_EndTime * Constance.TrackBar.UnitWidth;
                    break;
                case EffectType.Exit:
                    _Direction = true;
                    _EndTime = 0;
                    _width = (int)_EndTime * Constance.TrackBar.UnitWidth;
                    break;
                case EffectType.None:
                    break;
            }
        }

        [Browsable(false)]
        [XmlIgnore]
        public ShapeLayer ShapeLayer
        {
            get { return _layer; }
            set { _layer = value;}
        }

		private string _name;
        [ReadOnly(true)]
		public string Name
		{
			get { return _name; }
			set
			{
				if (!string.Equals(value, _name))
				{
                    //string old = _name;
					_name = value;
                    //OnPropertyChanged(ShapeLayer._.Name, value, old);
				}
			}
		}

        /// <summary>
        /// get empty effect
        /// </summary>
        public static LayerEffect Empty
        {
            get { return new EmptyEffect1(EffectType.None, null); }
        }

		/// <summary>
		/// get effect type
		/// </summary>
		[Browsable(false)]
		[XmlIgnore]
		public EffectType Type
		{
			get { return _type; }
			set { _type = value; }
		}

		private Guid _GUID = Guid.Empty;
		[Browsable(false)]
		public Guid GUID
		{
			get { return _GUID; }
			set
			{
				if (value != GUID)
				{
					_GUID = value;
				}
			}
		}

		[XmlIgnore]
		private long _StartTime;

        [Browsable(false)]
        public long StartTime
        {
            get
            {
                return (long)Left / Constance.Effect.UnitWidth;
            }
        }

		[XmlIgnore]
		private long _EndTime;

        [Browsable(false)]
        public long EndTime
        {
            get
            {
                return StartTime + Duration;
            }
        }

        [XmlIgnore]
        private int _left;

        [XmlIgnore]
        [Browsable(false)]
        public int Left
        {
            get
            {
                return _left;
            }
            set
            {
                if (_left != value)
                {
                    var old = _left;
                    _left = value;
                    OnPropertyChanged(ShapeLayer._.Left, value, old);
                }
            }
        }

        [XmlIgnore]
        private int _width;

        [XmlIgnore]
        [Browsable(false)]
        public int Width
        {
            get
            {
                return _width;
            }
            set
            {
                if (_width != value)
                {
                    var old = _width;
                    _width = value;
                    OnPropertyChanged(ShapeLayer._.Width, value, old);

                }
            }
        }

		/// <summary>
		/// get or set duration
		/// </summary>
		[XmlIgnore]
        [Browsable(true)]
        [ReadOnly(true)]
        [DisplayName("Duration")]
		public long Duration
		{
			get
			{
                if (IsEmpty && (_type == EffectType.Entry || _type == EffectType.Exit))
                {
                    return 0;
                }
                else
                {
                    return _width == 0 ? 0 : (long)_width / Constance.Effect.UnitWidth; // _EndTime - _StartTime;
                }
			}
			set
			{
                long old = Duration;
                //if(this.Layer != null) //if current effect is not message display effect
                    _width = (int)value * Constance.TrackBar.UnitWidth;
                OnPropertyChanged(ShapeLayer._.Duration, value, old);

			}
		}

        [XmlIgnore]
		private bool _Direction = false;

        private class _StateString
        {
            public const string Enter = "1";
            public const string Exit = "0";
        }

        protected string StateString
        {
            get { return !State ? _StateString.Enter : _StateString.Exit; }
        }

        [XmlIgnore]
        [Browsable(false)]
        public bool State
        {
            get
            {
                return _type == EffectType.Entry ? false : true;
            }
        }

        private bool _IsSystem = false;
        /// <summary>
        /// get or set group name
        /// </summary>
        [Browsable(false)]
        [XmlIgnore]
        public bool IsSystem
        {
            get { return _IsSystem; }
            set { _IsSystem = value; }
        }

		[Browsable(false)]
		public bool IsEmpty
		{
			get
			{
				return (string.IsNullOrEmpty(_name) || _name == "None" )&&this.Type != EffectType.Emphasis;
			}
		}

	    public LayerEffect Real
	    {
	        get { return this;}
	    }

        internal void PartialFromTo(LayerEffect effect)
        {
            if (effect == null)
                effect = Empty;
            _name = effect._name;
            _GUID = effect._GUID;
            _Direction = effect._Direction;
            _IsSystem = effect._IsSystem;
            _left = effect._left;
            _width = effect._width;
            if (Duration == 0)
                Init(effect._type);
        }

        public void PartFromTo(LayerEffect effect)
        {
            if (effect == null)
                effect = Empty;
            _type = effect._type;
            _name = effect._name;
            _Direction = effect._Direction;
            _GUID = effect._GUID;
            _IsSystem = effect._IsSystem;
            _layer = effect._layer;
        }

        public virtual void FromTo(LayerEffect effect)
        {
            if (effect == null)
                effect = Empty;
            _Direction = effect._Direction;
            _name = effect._name;
            _type = effect._type;
            _GUID = effect._GUID;
            _left = effect._left;
            _width = effect._width;
            _IsSystem = effect._IsSystem;
            _layer = effect._layer;
        }
        public virtual void FromTo(LayerEffect effect, bool isAddNewEffect)
        {
            if (effect == null)
                effect = Empty;
            _Direction = effect._Direction;
            _name = effect._name;
            _type = effect._type;
            _GUID = effect._GUID;
            if (isAddNewEffect)
            {
                _left = 0;
                _width = effect.Type == EffectType.Emphasis? 64:16;
            }
            else
            {
                _left = effect._left;
                _width = effect._width;
            }
            _IsSystem = effect._IsSystem;
            _layer = effect._layer;
        }

		public override int GetHashCode()
		{
			return base.GetHashCode();
		}

		public bool Equals(LayerEffect other)
		{
			if (other == null)
				return false;
			if (Type != other.Type)
				return false;
			return base.Equals(other);
		}

		public override bool Equals(object obj)
		{
			return Equals(obj as LayerEffect);
		}

        protected override void Dispose(bool disposing)
        {
            _name = null;
            this.PropertyChanged = null;
        }

        public override string ToString()
        {
            return this.Name;

        }

        protected virtual internal void UpdateSignType(SignType signType)
        {
            
        }
    }

    [Serializable]
    public abstract class LayerEffect<TEffect> : LayerEffect
        where TEffect : LayerEffect, new()
    {
        public override LayerEffect Create()
        {
            return new TEffect();
        }

        public override LayerEffect Copy(bool isAddNewEffect)
        {
            TEffect effect = new TEffect();
            //effect.FromTo(this);
            effect.FromTo(this, isAddNewEffect);
            return effect;
        }

        public override LayerEffect Copy()
        {
            TEffect effect = new TEffect();
            effect.FromTo(this);
            //effect.FromTo(this, isAddNewEffect);
            return effect;
        }

        [Browsable(false)]
        public int Zoom
        {
            protected get
            {
                if (ShapeLayer != null && ShapeLayer.Shape != null)
                    return ShapeLayer.Shape.Zoom;
                return _zoom;
            }
            set
            {
                _zoom = value;
            }
        }
        [OptionalField]
        private int _zoom = 1;

        protected int PopulatePixel(int sourcePixel)
        {
            var zoom = Zoom;
            if (zoom > 0)
                return sourcePixel * zoom;
            return (int)(sourcePixel / zoom);
        }
    }

    public interface ILayerEffect
    {
        string Name { get; set; }
        long StartTime { get; }
        long EndTime { get; }
        long Duration { get; set; }
        EffectType Type { get; set; }
        Guid GUID { get; set; }
        bool IsEmpty { get; }
        int Left { get; set; }
        int Width { get; set; }

        LayerEffect Copy();
        //LayerEffect Copy(bool isAddNewEffect);
        void FromTo(LayerEffect effect);

        LayerEffect Real { get; }
    }

    public interface  IFromTo<T>
    {
        void FromTo(T t);
    }

}

namespace ProWrite.Entity
{
    public static class ShapeExtensions
    {
        public static int PopulatePixel(this int sourcePixel, int zoom)
        {
            if (zoom > 0)
                return sourcePixel * zoom;
            return (int)(sourcePixel / zoom);
        }
    }
}