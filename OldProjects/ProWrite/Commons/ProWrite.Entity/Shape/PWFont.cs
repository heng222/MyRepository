using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace ProWrite.Entity.Shape
{
	public class PWFont
	{
		public String Name { get; set; }
		public List<int> Size { get; set; }
		public override string ToString()
		{
			return Name;
		}
	}
}
