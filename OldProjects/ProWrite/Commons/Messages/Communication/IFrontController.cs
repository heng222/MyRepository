using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace System.Communication
{
    public interface IFrontController<TConnection, TFilterProcessor, TFilter, TActionProcessor, TAction, TPacket>
        where TConnection : IConnection<TPacket>, new()
        where TFilterProcessor:IFilterProcessor<TFilter,TPacket>,new()
        where TFilter: IFilter<TPacket>
        where TActionProcessor : IActionProcessor<TAction, TPacket>, new()
        where TAction : IAction<TPacket>
        where TPacket : IPacket
    {
        void Init();
        void Destroy();

        object this[string key] { get; set; }
        TConnection Connection { get; }

        TFilterProcessor FilterProcessor { get; }
        TActionProcessor ActionProcessor { get; }

        void Send(TPacket packet);
        AsyncFuture<TPacket> SendAsync(TPacket packet);
        AsyncFuture<TPacket> SendAsync(TPacket packet, Action<IAsyncContext<TPacket>> callback);

        void Process(TPacket packet);
    }

}
