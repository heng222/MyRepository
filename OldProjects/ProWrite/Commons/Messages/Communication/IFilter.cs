using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace System.Communication
{
    public interface IFilter
    {
        void Init();
        void Destroy();
        void DoFilter(IPacket packet);
    }

    public interface IFilter<TPacket> : IFilter
        where TPacket : IPacket
    {
        void DoFilter(TPacket packet);
    }

    public abstract class FilterBase<TPacket> : IFilter<TPacket>
        where TPacket : IPacket
    {
        public virtual void Init() { }
        public virtual void Destroy() { }

        public abstract void DoFilter(TPacket packet);

        void IFilter.DoFilter(IPacket packet)
        {
            DoFilter((TPacket)packet);
        }
    }

}
