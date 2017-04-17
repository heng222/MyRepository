using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Net;
using System.Diagnostics;
using System.Communication;

namespace System.Net.Tcp
{
    public class TcpServerParams : ConnectionParams
    {
        public TcpServerParams(IPEndPoint endPoint)
            : this(
                endPoint
                , SR.EOF
                , SR.HeartPacket
                , SR.HeartInterval
                , SR.MaxConnections
                , SR.BufferSize
                , SR.ConnectionBlockLog
                , SR.MaxPendingConnections)
        {
        }

        public TcpServerParams(
            IPEndPoint endPoint
            , byte[] packetSeparateFlag
            , byte[] heartPacket
            , int heartTicket
            , int maxConnections
            , int bufferSize
            , int connBacklog
            , int maxPendingConnections):base(endPoint,packetSeparateFlag,heartPacket,heartTicket,bufferSize)
        {
            
            Debug.Assert(maxConnections > 0);
            Debug.Assert(maxPendingConnections > 0);
            
            
            MaxConnections = maxConnections;
            if (connBacklog > 0)
                ConnectionBacklog = connBacklog;
            else
                ConnectionBacklog = 100;
            MaxPendingConnections = maxPendingConnections;
        }
        
        public int MaxConnections { get; private set; }
        public int ConnectionBacklog { get; private set; }
        public int MaxPendingConnections { get; private set; }
    }
}
