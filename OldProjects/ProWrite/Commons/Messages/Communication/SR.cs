using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace System.Communication
{
    class SR
    {
        public static readonly string EOFString = "#EOF#";
        public static readonly byte[] EOF = EOFString.GetBytesUTF8();
        public static readonly string HeartPacketString = "Command:Heart";
        public static readonly byte[] HeartPacket = HeartPacketString.GetBytesUTF8();
        public static readonly int HeartInterval = 10000;
        public static readonly int HeartIntervalTime = 12;
        public static readonly string PacketSeparateFlag = EOFString;
        public static readonly int BufferSize = 1024;

        public const int MaxConnections = 50000;
        public const int ConnectionBlockLog = 100;
        public const int MaxPendingConnections = 200;
    }
}
