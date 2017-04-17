using System;
using System.Collections.Generic;
using System.Text;
using System.Drawing;
using System.Xml.Serialization;
using ProWrite.Core;
using System.Diagnostics;

namespace ProWrite.Entity.DES
{
	/// <summary>
	/// ADD by zhouzg 2008-4-23
	/// function:compsitor info
	/// </summary>
    //[Serializable]
    //public struct RECT
    //{
    //    public int Height;
    //    public int Width;
    //    public int OffsetX;
    //    public int OffsetY;
    //    public RECT(int height, int width, int offsetX, int offsetY)
    //    {
    //        Height = height;
    //        Width = width;
    //        OffsetX = offsetX;
    //        OffsetY = offsetY;
    //    }
    //}

	/// <summary>
	/// ADD by zhouzg 2008-4-23
	/// function:Effect Property
	/// </summary>
	[Serializable]
    [DebuggerDisplay("Name={_name},Value={_value}")]
	public class Property:DisposableObject
	{

		private string _name;
		private string _value;


		public Property() { }

		public Property(string name,object value)
		{
			_name = name;
			_value = value.ToString();
		}

		/// <summary>
		/// get or set property name
		/// </summary>
		[XmlAttribute]
		public string Name
		{
			get { return _name; }
			set { _name = value; }
		}

		/// <summary>
		/// get or set property value
		/// </summary>
		[XmlAttribute]
		public string Value
		{
			get { return _value; }
			set { _value = value; }
		}

        
        public Property Copy()
        {
            Property clone = new Property();
            clone._name = _name;
            clone._value = _value;
            return clone;
        }
    }
}