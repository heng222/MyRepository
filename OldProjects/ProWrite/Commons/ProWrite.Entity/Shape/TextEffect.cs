using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Xml.Serialization;
using ProWrite.Core;

namespace ProWrite.Entity.Shape
{
    [Serializable]
	public class TextEffect
	{
        #region Non Serialized Fields
        [NonSerialized]
        [XmlIgnore]
        private EventHandler<PropertyChangedEventArgs> _propertyChanged;
        #endregion

        #region Serialized Fields
        private OutlineShadowType _effect;
        private Color _color = Color.Black;
        private int _shadowLateralShift = 1;
        private int _shasowVerticalShift = 1;
        private int _outlineWidth = 1;
        #endregion

        #region Serialized Fields Version 2
        #endregion


        /// <summary>
		/// Property changed event
		/// </summary>
		public event EventHandler<PropertyChangedEventArgs> PropertyChanged
		{
			add { _propertyChanged += value; }
			remove { _propertyChanged -= value; }
		}

		protected virtual void OnPropertyChanged(string propertyName, object newValue, object oldValue)
		{
			if (_propertyChanged != null)
				_propertyChanged(this, new PropertyChangedEventArgs(propertyName, newValue, oldValue));
		}

    	
		public OutlineShadowType Effect 
		{ get {return _effect;}
			set
			{
				if (value != _effect)
				{
					OutlineShadowType old = _effect;
					_effect = value;
					OnPropertyChanged("Effect", value, old);
				}

			}
		}

        internal void UpdateEffectColor(SignType signType)
        {
            _color = SignTypeHandler.ConvertColor(_color, signType);
        }

        public Color ConveredEffectColor(SignType signType)
        {
            return SignTypeHandler.ConvertToMonoColor(_color, signType); 
        }
    	
		public Color EffectColor 
		{ 
			get { return _color;}
			set
				{
					if (value != _color)
					{
						Color old = _color;
						_color = value;
						OnPropertyChanged("EffectColor", value, old);
					}
				}
			}

    	

    	public int ShadowLateralShift
    	{
    		get { return _shadowLateralShift;}
    		set
    		{
    			if (value != _shadowLateralShift)
    			{
    				int old = _shadowLateralShift;
					_shadowLateralShift = value;
    				OnPropertyChanged("ShadowLateralShift", value, old);
    			}
    		}
    	}

        
		public int ShadowVerticalShift
		{
			get { return _shasowVerticalShift; }
			set
			{
				if (value != _shasowVerticalShift)
				{
					int old = _shasowVerticalShift;
					_shasowVerticalShift = value;
					OnPropertyChanged("ShadowVerticalShift", value, old);
				}
			}
		}

        
		public int OutlineWidth
		{
			get { return _outlineWidth; }
			set
			{
				if (value != _outlineWidth)
				{
					int old = _outlineWidth;
					_outlineWidth = value;
					OnPropertyChanged("OutlineWidth", value, old);
				}
			}
		}


		public int EffectIndex
		{
			get
			{
				switch(Effect)
				{
					case OutlineShadowType.NONE:
						return 0;
                    case OutlineShadowType.SHADED:
						return 1;
                    case OutlineShadowType.OUTLINE:
						return 2;
					default:
						return 0;
				}
			}
		}

        public bool IsHasEvent
        {
            get { return _propertyChanged != null && _propertyChanged.GetInvocationList().Length > 0; }
        }


		public override string ToString()
		{
			{
				return Effect.ToString();
			}
		}

		public TextEffect Copy()
		{
			TextEffect clone = new TextEffect();
			//target.Caption = Caption;
			clone._effect = Effect;
			clone._color = EffectColor;
			clone._outlineWidth = OutlineWidth;
			clone._shadowLateralShift = ShadowLateralShift;
			clone._shasowVerticalShift = ShadowVerticalShift;
			return clone;
		}
	}
}