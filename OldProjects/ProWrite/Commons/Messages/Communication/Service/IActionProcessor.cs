//using System;
//using System.Collections.Generic;
//using System.Linq;
//using System.Text;

//namespace System.Communication.Service
//{
//    public interface IActionProcessor
//    {
//        void Init();
//        void Destroy();

//        List<IAction> Actions { get; }
//        void Process(IRequest req, IResponse resp);
//    }

//    public interface IActionProcessor<TAction, TRequest, TResponse> : IActionProcessor
//        where TRequest : IRequest
//        where TResponse : IResponse
//        where TAction : IAction<TRequest, TResponse>
//    {

//        new List<TAction> Actions { get; }

//        void Process(TRequest req, TResponse resp);
//    }

//    public abstract class ActionProcessorBase<TAction, TRequest, TResponse> : IActionProcessor<TAction, TRequest, TResponse>
//        where TRequest : IRequest
//        where TResponse : IResponse
//        where TAction : IAction<TRequest, TResponse>
//    {
//        public ActionProcessorBase()
//        {
//            Actions = new List<TAction>();
//        }

//        public virtual void Init() { }
//        public virtual void Destroy() { }

//        public List<TAction> Actions { get; private set; }
//        public abstract void Process(TRequest req, TResponse resp);

//        List<IAction> IActionProcessor.Actions
//        {
//            get { return new List<IAction>(Actions.Cast<IAction>()); }
//        }

//        void IActionProcessor.Process(IRequest req, IResponse resp)
//        {
//            Process((TRequest)req, (TResponse)resp);
//        }
//    }

//}
