using System;
using System.Collections.Generic;
using System.Text;
using System.Communication;
using ProWrite.Core;

namespace ProWrite.UFE
{
    public partial class UFEFrontController<TConnection>
	{
        AsyncFuture<UFEPacket> ILogManager.GetLog()
        {
            return SendAsync(Commands.GetLog);
        }

        AsyncFuture<UFEPacket> ILogManager.ClearLog()
        {
            return SendAsync(Commands.ClearLog);
        }
	}
}
