using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Communication;
using ProWrite.UFE.Entity;

namespace ProWrite.UFE
{
    public enum ConnectionMode
    {
        None,
        Tcp,
        RS232,
        Modem,
       // Mock,
    }


    public delegate void ReceivedHandler(UFEPacket resp);
    public interface IUFEConnection : IConnection<UFEPacket>
    {
        IFtpManager FtpManager { get; }
        //new IUFEFuture Send(IUFERequest req);
        IAsyncFuture OpenAsync(Action<IAsyncContext<UFEPacket>> completedCallback);

        ConnectionMode Mode { get; }
        ISignInfo Sign { get; set; }
        User User { get; set; }
        User FtpUser { get; set; }
        bool CanLock { get; set; }
        bool Locked { get; set; }
        List<ServerLibraryItem> ServerLibraries { get; set; }
        List<User> Users { get; set; }
    }

}
