using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Net.Sockets;
using System.Communication;

namespace System.Net.Tcp
{
    public interface ITcpServerConnectionFactory<TConnection, TCoding,TPacket>
        where TConnection : TcpServerConnection<TCoding, TPacket>, new()
        where TCoding: ICoding<TPacket>,new()
        where TPacket: IPacket
    {
        TConnection CreateConnection(Socket socket
            , SocketAsyncEventArgs receiveAsyncEvent);
    }

    public class TcpServerConnectionFactory<TConnection, TCoding, TPacket>:ITcpServerConnectionFactory<TConnection,TCoding,TPacket>
        where TConnection : TcpServerConnection<TCoding, TPacket>, new()
        where TCoding : ICoding<TPacket>, new()
        where TPacket : IPacket
    {
        public TConnection CreateConnection(Socket socket
            , SocketAsyncEventArgs receiveAsyncEvent)
        {
            TConnection conn = new TConnection();
            conn.Init(socket, receiveAsyncEvent, new TCoding());
            return conn;
        }
    }

}
