using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace System.Communication
{
    public interface IActionProcessor
    {
        void Init();
        void Destroy();

        List<IAction> Actions { get; }
        void Process(IPacket packet);
    }

    public interface IActionProcessor<TAction, TPacket> : IActionProcessor
        where TPacket : IPacket
        where TAction : IAction<TPacket>
    {

        new List<TAction> Actions { get; }
        void Process(TPacket packet);
    }

}
