using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace System.Communication
{
    public interface IActionProcessorFactory
    {
        IActionProcessor CreateActionProcessor();
    }


    public interface IActionProcessorFactory<TActionProcessor, TAction, TPacket> : IActionProcessorFactory
        where TActionProcessor : IActionProcessor<TAction, TPacket>, new()
        where TAction : IAction<TPacket>
        where TPacket : IPacket
    {
        new TActionProcessor CreateActionProcessor();
    }

    public class ActionProcessorFactory<TActionProcessor, TAction, TPacket> : IActionProcessorFactory<TActionProcessor, TAction, TPacket>
        where TActionProcessor : IActionProcessor<TAction, TPacket>, new()
        where TAction : IAction<TPacket>
        where TPacket : IPacket
    {
        public TActionProcessor CreateActionProcessor()
        {
            var processor = new TActionProcessor();
            return processor;
        }

        IActionProcessor IActionProcessorFactory.CreateActionProcessor()
        {
            return CreateActionProcessor();
        }
    }
}
