using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace System.Communication
{
    public interface IConnectionFactory<TConnection, TPacket>
        where TConnection : IConnection<TPacket>, new()
        where TPacket : IPacket
    {
        TConnection CreateConnection();
    }

    public class ConnectionFactory<TConnection, TPacket> : IConnectionFactory<TConnection, TPacket>
        where TConnection : IConnection<TPacket>, new()
        where TPacket : IPacket
    {
        public TConnection CreateConnection()
        {
            return new TConnection();
        }
    }

}
