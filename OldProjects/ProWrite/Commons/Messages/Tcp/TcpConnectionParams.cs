using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Net;
using Org.Mentalis.Network.ProxySocket;
using System.Diagnostics;
using System.Communication;

namespace System.Net.Tcp
{
    public class TcpConnectionParams:ConnectionParams
    {
        public TcpConnectionParams(IPEndPoint endPoint
            , byte[] packetSeparateFlag
            , byte[] heartPacket
            , int heartTicket
            , int bufferSize)
            : base(endPoint,packetSeparateFlag,heartPacket,heartTicket,bufferSize)
        {
        }

        public TcpConnectionParams(IPEndPoint endPoint
            , IPEndPoint proxyEndPoint
            , ProxyTypes proxyType
            , string proxyUser
            , string proxyPassword)
            :this(endPoint
                , SR.EOF
                , SR.HeartPacket
                , SR.HeartInterval
                , SR.BufferSize
                , proxyEndPoint
                , proxyType
                , proxyUser
                , proxyPassword)
        {
        }

        public TcpConnectionParams(IPEndPoint endPoint)
            :base(endPoint)
        {
        }

        public TcpConnectionParams(IPEndPoint endPoint
            , byte[] packetSeparateFlag
            , byte[] heartPacket
            , int heartTicket
            , int bufferSize
            , IPEndPoint proxyEndPoint
            , ProxyTypes proxyType
            , string proxyUser
            , string proxyPassword):base(endPoint,packetSeparateFlag,heartPacket,heartTicket,bufferSize)
        {
            if (proxyEndPoint != null 
                && proxyType != ProxyTypes.None)
            {
                ProxyEndPoint = proxyEndPoint;
                ProxyType = proxyType;
                ProxyUser = proxyUser;
                ProxyPassword = proxyPassword;
            }
        }

        public IPEndPoint ProxyEndPoint { get;private set; }

        public ProxyTypes ProxyType { get; private set; }

        public string ProxyUser { get;private set; }

        public string ProxyPassword { get;private set; }
    }
}
