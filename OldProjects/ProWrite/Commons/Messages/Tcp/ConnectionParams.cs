using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Communication;

namespace System.Net.Tcp
{
    public class ConnectionParams
    {
        public ConnectionParams(IPEndPoint endPoint
            , byte[] packetSeparateFlag
            , byte[] heartPacket
            , int heartInterval
            , int bufferSize)
        {
            Check.Require(endPoint != null);
            EndPoint = endPoint;

            Check.Require(bufferSize > 0);
            BufferSize = bufferSize;

            Check.Require(packetSeparateFlag!= null, "packetSeparateFlag != null");
            Check.Require(packetSeparateFlag.Length > 0, "packetSeparateFlag.Length > 0");
            Check.Require(heartPacket !=null, "heartPacket != null");
            Check.Require(heartPacket.Length > 0, "heartPacket.Length > 0");
            Check.Require(heartInterval > 0, "heartInterval > 0");

            PacketSeparateFlag = packetSeparateFlag;
            HeartPacket = heartPacket;
            HeartInterval = heartInterval;

            SendTimeout = 5000;
            ReceiveTimeout = 5000;
        }

        public ConnectionParams(IPEndPoint endPoint)
            :this(endPoint, SR.EOF,SR.HeartPacket,SR.HeartInterval, SR.BufferSize)
        {
        }

        public IPEndPoint EndPoint { get; private set; }
        public byte[] PacketSeparateFlag { get; private set; }
        public byte[] HeartPacket { get; private set; }
        public int HeartInterval { get; private set; }
        public int BufferSize { get; private set; }
        public int SendTimeout { get; protected set; }
        public int ReceiveTimeout { get; protected set; }

    }
}
