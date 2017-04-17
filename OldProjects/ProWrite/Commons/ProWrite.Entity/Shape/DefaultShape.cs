//---------------------------------------------------------------------
//
// File: DefaultShape.cs
//
// Description:
// Default Shape class
//
// Author: Kevin 2008-6-27
//
// Modify History:
// Copyright (C) 2008 by Trans-Lux All rights reserved.
// 
//---------------------------------------------------------------------
using System;
using ProWrite.Core;
using System.ComponentModel;
using System.Drawing;

namespace ProWrite.Entity.Shape
{
	/// <summary>
	/// Default Shape class
	/// </summary>
	[Serializable]
	[TypeConverter(typeof(ExpandableObjectConverter))]
	public class DefaultShape : ShapeBase
	{
        #region Non Serialized Fields
        #endregion

        #region Serialized Fields
        #endregion

        #region Serialized Fields Version 2
        #endregion

        #region Methods
       

		public override ShapeType Type
		{
			get { return ShapeType.Default; }
		}

		public override LayerType LayerType
		{
			get { return LayerType.Paint; }
		}

		public override ShapeBase NewInstance()
		{
			return new DefaultShape();
		}
		#endregion //End Methods
	}
}