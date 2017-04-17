using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace System.Communication
{
    public abstract class ActionBase<TPacket> : IAction<IPacket>
           where TPacket : IPacket
    {
        public abstract void Perform(TPacket packet);

        void IAction.Perform(IPacket packet)
        {
            Perform((TPacket)packet);
        }

        #region IAction<IPacket> Members

        void IAction<IPacket>.Perform(IPacket packet)
        {
            Perform((TPacket)packet);
        }

        #endregion
    }
}
