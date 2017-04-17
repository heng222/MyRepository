using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace System.Communication
{
    public interface IFilterProcessor
    {
        void Init();
        void Destroy();

        List<IFilter> Filters { get; }
        void Process(IPacket packet);
    }

    public interface IFilterProcessor<TFilter, TPacket> : IFilterProcessor
        where TPacket : IPacket
        where TFilter : IFilter<TPacket>
    {

        new List<TFilter> Filters { get; }

        void Process(TPacket packet);

    }

    public abstract class FilterProcessorBase<TFilter, TPacket> : IFilterProcessor<TFilter, TPacket>
        where TPacket : IPacket
        where TFilter : IFilter<TPacket>
    {
        public FilterProcessorBase()
        {
            Filters = new List<TFilter>();
        }

        public virtual void Init() { }
        public virtual void Destroy() { }

        public List<TFilter> Filters { get; private set; }
        public abstract void Process(TPacket packet);

        List<IFilter> IFilterProcessor.Filters
        {
            get { return new List<IFilter>(Filters.Cast<IFilter>()); }
        }

        void IFilterProcessor.Process(IPacket packet)
        {
            Process((TPacket)packet);
        }
    }

}
