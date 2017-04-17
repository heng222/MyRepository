using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace System.Communication.Service
{
    public interface ISession<TPacket> : IConnectionBase<TPacket>
        where TPacket : IPacket
    {
        //event Action<TRequest> Received;

        //void Send(TResponse resp);

        IFrontController FrontController { get; set; }
    }


}
