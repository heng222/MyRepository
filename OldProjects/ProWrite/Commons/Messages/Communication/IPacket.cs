using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace System.Communication
{
    public interface IPacket
    {
        int Id { get; set; }
        bool HasError { get;}
    }

    
}
