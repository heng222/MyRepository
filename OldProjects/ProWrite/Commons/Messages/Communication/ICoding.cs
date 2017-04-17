using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace System.Communication
{
    public interface ICoding<TPacket>
        where TPacket : IPacket
    {
        byte[] EncodePacket(TPacket req);

        TPacket DecodePacket(byte[] req);
    }

}
