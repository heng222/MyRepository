using System;
using System.Collections.Generic;
using System.Text;

namespace ProWrite.Entity
{
	public class PropertyChangedEventArgs:EventArgs
	{
		public string Name;
		public readonly object NewValue;
		public readonly object OldValue;

		public PropertyChangedEventArgs(string name, object newValue, object oldValue)
		{
			Name = name;
			NewValue = newValue;
			OldValue = oldValue;
		}
	}
}