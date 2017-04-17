using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace System.Communication
{
    public interface IFilterProcessorFactory
    {
        IFilterProcessor CreateFilterProcessor();
    }

    public interface IFilterProcessorFactory<TFilterProcessor, TFilter, TPacket> : IFilterProcessorFactory
        where TFilterProcessor : IFilterProcessor<TFilter, TPacket>, new()
        where TFilter : IFilter<TPacket>
        where TPacket : IPacket
    {
        new TFilterProcessor CreateFilterProcessor();
    }

    public class FilterProcessorFactory<TFilterProcessor, TFilter, TPacket>
        : IFilterProcessorFactory<TFilterProcessor, TFilter, TPacket>
        where TFilterProcessor : IFilterProcessor<TFilter, TPacket>, new()
        where TFilter : IFilter<TPacket>
        where TPacket : IPacket
    {
        public TFilterProcessor CreateFilterProcessor()
        {
            var processor = new TFilterProcessor();
            return processor;
        }

        IFilterProcessor IFilterProcessorFactory.CreateFilterProcessor()
        {
            return CreateFilterProcessor();
        }
    }

}
