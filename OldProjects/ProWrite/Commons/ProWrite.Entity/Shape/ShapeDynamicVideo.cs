using System;
using System.Collections.Generic;
using System.Text;
using System.ComponentModel;
using System.Drawing;
using System.Drawing.Design;
using ProWrite.Core;
using ProWrite.Entity.DES;
using ProWrite.Entity.Shape;

namespace ProWrite.Entity.Shape
{
    [Serializable]
    public partial class ShapeDynamicVideo : ShapeBase, IEquatable<ShapeDynamicVideo>
    {
        #region Non Serialized Fields
        #endregion

        #region Serialized Fields
        private string _DataSource = null;
        #endregion

        private class _
		{
			public const string Text = "No Source";
		}

		public ShapeDynamicVideo():this(SignType.RGB)
		{
		}

		public ShapeDynamicVideo(SignType signType)
			: base(signType)
		{
		}

        public string DataSource
        {
            get { return _DataSource; }
            set
            {
                if (value != _DataSource)
                {
                    _DataSource = value;
                }
            }
        }

		#region override property, method

		public override ShapeType Type
		{
			get { return ShapeType.DynamicVideo; }
		}

		public override LayerType LayerType
		{
			get { return LayerType.DynamicVideo; }
		}

		public override ShapeBase NewInstance()
		{
			return new ShapeDynamicVideo();
		}

        public override void FromTo(ShapeBase shape)
        {
            if (shape == null)
                return;
            base.FromTo(shape);
            ShapeDynamicVideo other = shape as ShapeDynamicVideo;
            if (other != null)
            {
                _DataSource = other._DataSource;
            }
        }

        public override void Accept(IVisitor visitor)
        {
            visitor.VisitDynamicVideo(this);
        }
		#endregion

		#region IEquatable<ShapeDynamicVideo> Members

		public bool Equals(ShapeDynamicVideo other)
		{
			if (other == null)
				return false;
            if (other._DataSource != _DataSource)
                return false;
			return base.Equals(other);
		}

		public override bool Equals(object obj)
		{
			return Equals(obj as ShapeDynamicVideo);
		}

		public override int GetHashCode()
		{
			return base.GetHashCode();
		}
		#endregion
    }
}
