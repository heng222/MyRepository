using Ex = System.Exception;

namespace Tamir.SharpSsh.java
{
	/// <summary>
	/// Summary description for Exception.
	/// </summary>
	public class Exception : Ex
	{
		public Exception() : base()
		{
		}
		public Exception(string msg) : base(msg)
		{
		}

        public Exception(string msg,Ex innerEx):base(msg,innerEx)
        {

        }

		public virtual string toString()
		{
			return ToString();
		}
	}
}
