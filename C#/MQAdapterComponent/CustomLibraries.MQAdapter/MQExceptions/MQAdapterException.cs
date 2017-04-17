using System;

namespace CustomLibraries.MQAdapter
{
	/// <summary>
	/// Summary description for MQAdapterException.
	/// </summary>
	public class MQAdapterException:ApplicationException
	{
		public MQAdapterException(string exception):base(exception)
		{
			
		}
	}
}
