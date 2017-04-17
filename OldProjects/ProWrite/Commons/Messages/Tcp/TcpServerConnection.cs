using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Net.Sockets;
using System.Net;
using System.Threading;
using System.Diagnostics;
using System.Communication.Service;
using System.Communication;

namespace System.Net.Tcp
{
    public class TcpServerConnection<TCoding,TPacket> : TcpConnectionBase<Socket,TcpServerParams,TCoding,TPacket>,ISession<TPacket>
        where TPacket :IPacket
        where TCoding :ICoding<TPacket>,new()
    {
        public TcpServerConnection()
        {
        }

        public IFrontController FrontController { get; set; }

        
        
        protected override void OnReceived(TPacket packet)
        {
            base.OnReceived(packet);

            if (FrontController != null)
            {
                FrontController.Process(packet);
                Send(packet);
            }
        }
    }
}
