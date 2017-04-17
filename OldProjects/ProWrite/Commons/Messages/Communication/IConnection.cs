using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace System.Communication
{
    public interface IConnection<TPacket> : IConnectionBase<TPacket>
        where TPacket : IPacket
    {
        IAsyncFuture Open();
        event EventHandler ConnectionOpened;

        AsyncFuture<TPacket> SendAsync(TPacket packt);

        AsyncFuture<TPacket> SendAsync(TPacket packet, Action<IAsyncContext<TPacket>> callback);
    }

}
