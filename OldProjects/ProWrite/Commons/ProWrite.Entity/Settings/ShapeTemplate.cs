//---------------------------------------------------------------------
//
// File: ShapeTemplate.cs
//      
// Description:
//      Shape template  base class
//
// Author: Kevin 2008-8-1
//
// Modify History:
// Copyright (C) 2008 by Trans-Lux All rights reserved.
// 
//---------------------------------------------------------------------

using System;
using System.Collections.Generic;
using System.Text;
using System.ComponentModel;

namespace ProWrite.Entity.Settings
{
	/// <summary>
	/// Shape template  base class
	/// </summary>
	[Serializable]
	[TypeConverter(typeof(ExpandableObjectConverter))]
	public abstract class ShapeTemplate:TemplateInfo
	{
		public override IEnumerator<TemplateInfo> GetEnumerator()
		{
			return null;
		}

        [NonSerialized]
        private SignTemplateInfo _sign;
        [Browsable(false)]
        public SignTemplateInfo Sign
        {
            get { return _sign; }
            set
            {
                if (value != null)
                {
                    if (_sign != null)
                        _sign.PropertyChanged -= OnSignSizeChanged;
                    _sign = value;
                    _sign.PropertyChanged += new PropertyChangedEventHandler(OnSignSizeChanged);
                }
            }
        }

        private bool _fitToSign;
        public virtual bool FitToSign
        {
            get { return _fitToSign; }
            set { _fitToSign = value; }
        }

        protected virtual void OnSignSizeChanged(object sender, System.ComponentModel.PropertyChangedEventArgs e)
        {
        }
	}
}