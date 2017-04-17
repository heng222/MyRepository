using System;
using System.Collections.Generic;
using System.Drawing;
using System.Text;

namespace ProWrite.Entity.Library
{
	public class LibraryItemColor
	{
		private string _name;
		private Color _color;

		public LibraryItemColor(string name, Color color)
		{
			_name = name;
			_color = color;
		}

		public string Name
		{
			get { return _name;}
		}

		public Color Color
		{
			get { return _color;}
		}
	}
}