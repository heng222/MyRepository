
//using System;
//using System.ComponentModel;
//using System.Drawing;
//using System.IO;
//using System.Xml.Serialization;
//using System.Drawing.Design;
//using System.Runtime.Serialization;

//using ProWrite.Core;
//using ProWrite.Entity.DES;
//using ProWrite.Entity.Shape;
//using ProWrite.Core.Validation;

//using PropertyChangedEventArgs = ProWrite.Entity.PropertyChangedEventArgs;

//namespace ProWrite.Entity.Shape
//{
//    /// <summary>
//    /// Frame layer class
//    /// </summary>
//    [Serializable]
//    [TypeConverter(typeof(ExpandableObjectConverter))]
//    public class ShapeMasterLayer : DisposableObject
//    {
//        #region Non Serialized Fields
//        [XmlIgnore]
//        [NonSerialized]
//        private EventHandler<PropertyChangedEventArgs> _PropertyChanged;
//        [NonSerialized]
//        private static int _validRange = 50;
//        private EventHandler _onBackColorChange = null;

//        #endregion

//        #region Serialized Fields

//        private Color _backColor = Color.Black;
//        private int _id = 0;
//        private float _startTime = 0f;
//        private float _endTime = 0f;
//        private string _label;
//        private bool _IsVisible = true;
//        private ShapeBase _shape;
//        private LayerEffect __emphasisEffect;

//        private LayerEffect _emphasisEffect
//        {
//            get
//            {
//                if (__emphasisEffect == null)
//                {
//                    __emphasisEffect = LayerEffect.EmptyEffect(this, EffectType.Emphasis);
//                }
//                return __emphasisEffect;
//            }
//            set { __emphasisEffect = value; }
//        }

//        #endregion

//        #region Serialized Fields Version 2
//        #endregion

//        //public ShapeMasterLayer() : this(null) { }
//        public ShapeMasterLayer()
//        {
//            __emphasisEffect = LayerEffect.EmptyEffect(this, EffectType.Emphasis);
//        }

//        #region Events define
        
//        [Browsable(false)]
//        public event EventHandler<PropertyChangedEventArgs> PropertyChanged
//        {
//            add { _PropertyChanged += value; }
//            remove { _PropertyChanged -= value; }
//        }

//        /// <summary>
//        /// Update frame layer control
//        /// </summary>
//        /// <param name="propertyName">property name</param>
//        private void OnPropertyChanged(string propertyName, object newValue, object oldValue)
//        {
//            if (_PropertyChanged != null)
//                _PropertyChanged(this, new PropertyChangedEventArgs(propertyName, newValue, oldValue));
//        }
//        #endregion

//        #region Properties define
//        public static int MaxRange
//        {
//            get { return _validRange; }
//        }

//        /// <summary>
//        /// get or set layer id
//        /// </summary>
//        [Browsable(false)]
//        public int ID
//        {
//            get { return _id; }
//            set { _id = value; }
//        }

//        [Category("MasterLayer")]
//        public bool IsVisible
//        {
//            get { return _IsVisible; }
//            set
//            {
//                if (_IsVisible != value)
//                {
//                    bool old = _IsVisible;
//                    _IsVisible = value;

//                    OnPropertyChanged(_.IsVisible, _IsVisible, old);
//                }
//            }
//        }
       
//        /// <summary>
//        /// get or set Emphasis effect
//        /// </summary>
//        [Category("Effect")]
//        [Editor(Constance.Designers.EmphasisEffect, typeof(UITypeEditor))]
//        [XmlIgnore]
//        public LayerEffect EmphasisEffect
//        {
//            get { return _emphasisEffect; }
//            set
//            {
//                if (_emphasisEffect != value)
//                {
//                    float lastEndTime = EndTime;
//                    LayerEffect old = _emphasisEffect.Copy();
//                    old._masterLayer = this;
//                    if (old.IsEmpty)
//                        __emphasisEffect = value.Create();
//                    _emphasisEffect.PartialFromTo(value);
//                    _emphasisEffect.Duration = Convert.ToInt64(lastEndTime);
//                    OnPropertyChanged(_.EmphasisEffect, _emphasisEffect, old);
//                }
//            }
//        }

//        /// <summary>
//        /// get or set layer label
//        /// </summary>
//        [Category("MasterLayer")]
//        [RequiredValidator]
//        public string Name
//        {
//            get { return _label; }
//            set
//            {
//                if (_label != value)
//                {
//                    string old = _label;
//                    _label = value;
//                    OnPropertyChanged(_.Name, value, old);
//                }
//            }
//        }

//        /// <summary>
//        /// get or set message board BackColor
//        /// </summary>
//        [Category("MasterLayer")]
//        [Browsable(true)]
//        public Color BackGroundColor
//        {
//            get { return _backColor; }
//            set
//            {

//                if (_backColor != value
//                    && value != Color.Transparent)
//                {
//                    Color old = _backColor;
//                    _backColor = value;

//                    OnPropertyChanged(_.BackGroundColor, value, old);

//                    //if (_onBackColorChange != null)
//                    //    _onBackColorChange(this, new EventArgs());
//                }
//            }
//        }

//        /// <summary>
//        /// get or set start time of layer
//        /// </summary>
//        [Category("MasterLayer")]
//        public float StartTime
//        {
//            get
//            {
//                return _emphasisEffect.StartTime;
//            }
//        }

//        [Category("MasterLayer")]
//        public float EndTime
//        {
//            get
//            {
//                return _emphasisEffect.Width / Constance.TrackBar.UnitWidth;
//            }
//        }

//        /// <summary>
//        /// get or set duration time of layer
//        /// </summary>
//        [Browsable(false)] 
//        [Category("MasterLayer")]
//        public float Duration
//        {
//            get
//            {
//                return EndTime - StartTime;
//            }
//        }
        
//        #endregion

//        #region Internal class define
//        public class _
//        {
//            public const string
//                  Name = "Name"
//                , StartTime = "StartTime"
//                , EndTime = "EndTime"
//                , Duration = "Duration"
//                , EmphasisEffect = "EmphasisEffect"
//                , IsVisible = "IsVisible"
//                , Left = "Left"
//                , Width = "Width"
//                , BackGroundColor = "BackGroundColor"
//                ;
//        }
//        #endregion

//        #region Functions define
        
//        [OnDeserialized]
//        private void Deserialized(StreamingContext ctx)
//        {
//            if (_shape != null)
//                _shape.Tag = this;
//        }

//        #endregion
//    }
//}
