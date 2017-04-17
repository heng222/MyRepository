//using System;
//using System.Collections.Generic;
//using System.Linq;
//using System.Text;

//namespace System.Communication.Service
//{
//    public interface IActionProcessorFactory
//    {
//        IActionProcessor CreateActionProcessor();
//    }


//    public interface IActionProcessorFactory<TActionProcessor, TAction, TRequest, TResponse> : IActionProcessorFactory
//        where TActionProcessor : IActionProcessor<TAction, TRequest, TResponse>, new()
//        where TAction : IAction<TRequest, TResponse>
//        where TRequest : IRequest
//        where TResponse : IResponse
//    {
//        new TActionProcessor CreateActionProcessor();
//    }

//    public class ActionProcessorFactory<TActionProcessor, TAction, TRequest, TResponse>
//        : IActionProcessorFactory<TActionProcessor, TAction, TRequest, TResponse>
//        where TActionProcessor : IActionProcessor<TAction, TRequest, TResponse>, new()
//        where TAction : IAction<TRequest, TResponse>
//        where TRequest : IRequest
//        where TResponse : IResponse
//    {
//        public TActionProcessor CreateActionProcessor()
//        {
//            var processor = new TActionProcessor();
//            return processor;
//        }

//        IActionProcessor IActionProcessorFactory.CreateActionProcessor()
//        {
//            return CreateActionProcessor();
//        }
//    }
//}
