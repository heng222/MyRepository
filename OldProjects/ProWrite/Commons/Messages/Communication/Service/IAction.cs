//using System;
//using System.Collections.Generic;
//using System.Linq;
//using System.Text;

//namespace System.Communication.Service
//{
//    public interface IAction
//    {
//        void Init();
//        void Destroy();
//        void Perform(IPacket packet);
//    }

//    public interface IAction<TRequest, TResponse> : IAction
//        where TRequest : IRequest
//        where TResponse : IResponse
//    {
//        void Perform(TRequest req, TResponse resp);
//    }

//    public abstract class ActionBase<TRequest, TResponse> : IAction<TRequest, TResponse>
//        where TRequest : IRequest
//        where TResponse : IResponse
//    {
//        public virtual void Init() { }
//        public virtual void Destroy() { }

//        public abstract void Perform(TRequest req, TResponse resp);

//        void IAction.Perform(IRequest req, IResponse resp)
//        {
//            Perform((TRequest)req, (TResponse)resp);
//        }
//    }

//}
