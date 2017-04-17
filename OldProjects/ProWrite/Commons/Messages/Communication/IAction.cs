using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace System.Communication
{
    public interface IAction
    {
        void Perform(IPacket packet);
    }

    public interface IAction<TPacket> : IAction
            where TPacket : IPacket
    {
        void Perform(TPacket packet);
    }

}
