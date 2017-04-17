using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace FirstSolution.Domain
{
	public class Product
	{
		public virtual  Guid Id { get; set; }
		public virtual string Name { get; set; }
		public virtual string Category { get; set; }
		public virtual bool Discontinued { get; set; }
	}
}
