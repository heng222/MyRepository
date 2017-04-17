using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace System.Communication.Service
{
    public interface IFrontController : IServiceManager
    {
        IFilterProcessor FilterProcessor { get; }
        IActionProcessor ActionProcessor { get; }

        void Process(IPacket packet);

        new IIOService[] Services { get; }
        void AddService(IIOService service);
    }


    public interface IFrontController<
        TFilterProcessorFactory
        , TFilterProcessor
        , TFilter
        , TActionProcessorFactory
        , TActionProcessor
        , TAction
        , TPacket> : IFrontController
        where TFilterProcessorFactory : IFilterProcessorFactory<TFilterProcessor, TFilter, TPacket>, new()
        where TFilterProcessor : IFilterProcessor<TFilter, TPacket>, new()
        where TFilter : IFilter<TPacket>
        where TActionProcessorFactory : IActionProcessorFactory<TActionProcessor, TAction, TPacket>, new()
        where TActionProcessor : IActionProcessor<TAction, TPacket>, new()
        where TAction : IAction<TPacket>
        where TPacket : IPacket
    {
        new TFilterProcessor FilterProcessor { get; }
        new TActionProcessor ActionProcessor { get; }

        void Process(TPacket packet);
    }

    public abstract class FrontControllerBase<
        TFilterProcessor
        , TFilter
        , TActionProcessor
        , TAction
        , TPacket>
        : ServiceAdapter, IFrontController<
            FilterProcessorFactory<TFilterProcessor, TFilter, TPacket>
            , TFilterProcessor
            , TFilter
            , ActionProcessorFactory<TActionProcessor, TAction, TPacket>
            , TActionProcessor
            , TAction
            , TPacket>
        where TFilterProcessor : IFilterProcessor<TFilter, TPacket>, new()
        where TFilter : IFilter<TPacket>
        where TActionProcessor : IActionProcessor<TAction, TPacket>, new()
        where TAction : IAction<TPacket>
        where TPacket : IPacket
    {
        private List<IIOService> services = null;

        private TFilterProcessor filterProcessor;
        private TActionProcessor actionProcessor;

        private FrontControllerListenManager listenMgr;

        public FrontControllerBase()
        {
            listenMgr = new FrontControllerListenManager();

            filterProcessor = new FilterProcessorFactory<TFilterProcessor, TFilter, TPacket>().CreateFilterProcessor();
            actionProcessor = new ActionProcessorFactory<TActionProcessor, TAction, TPacket>().CreateActionProcessor();
            services = new List<IIOService>();
        }

        protected class FrontControllerListenManager : ListenerManager
        {
            private List<IServiceManagerListener> _listeners;

            public FrontControllerListenManager()
            {
                _listeners = new List<IServiceManagerListener>(2);
            }

            public override void RegisterListener(IServiceableListener listener)
            {
                base.RegisterListener(listener);

                var fc = listener as IServiceManagerListener;
                if (fc != null)
                    _listeners.Add(fc);
            }

            public override void RemoveListener(IServiceableListener listener)
            {
                base.RemoveListener(listener);

                var fc = listener as IServiceManagerListener;
                if (fc != null)
                    _listeners.Remove(fc);
            }

            public Cancelable OnAddingService(IServiceable svc)
            {
                var e = new CancelEventArgs<IServiceable>(svc);
                foreach (var item in _listeners)
                {
                    item.OnAddingService(Owner, e);
                    if (e.Cancel)
                        return Cancelable.True;
                }

                return Cancelable.False;
            }

            public void OnAddedService(IServiceable svc)
            {
                var e = new EventArgs<IServiceable>(svc);
                foreach (var item in _listeners)
                    item.OnAddedService(Owner, e);
            }

            public Cancelable OnRemovingService(string servieName)
            {
                var e = new CancelEventArgs<string>(servieName);
                foreach (var item in _listeners)
                {
                    item.OnRemovingService(Owner, e);
                    if (e.Cancel)
                        return Cancelable.True;
                }

                return Cancelable.False;
            }

            public void OnRemovedService(string serviceName)
            {
                var e = new EventArgs<string>(serviceName);
                foreach (var item in _listeners)
                    item.OnRemovedService(Owner, e);
            }
        }


        protected override void DoInit()
        {
            filterProcessor.Init();
            actionProcessor.Init();
        }

        public TFilterProcessor FilterProcessor
        {
            get { return filterProcessor; }
        }

        IFilterProcessor IFrontController.FilterProcessor
        {
            get { return filterProcessor; }
        }

        public TActionProcessor ActionProcessor
        {
            get { return actionProcessor; }
        }

        IActionProcessor IFrontController.ActionProcessor
        {
            get { return actionProcessor; }
        }

        IServiceable[] IServiceManager.Services
        {
            get { return services.ConvertAll<IServiceable>((s) => { return s; }).ToArray(); }
        }

        public IIOService[] Services
        {
            get { return services.ToArray(); }
        }


        public void AddService(IIOService service)
        {
            if (service == null)
                return;

            if (services.Contains(service))
                return;

            if (listenMgr.OnAddingService(service) == Cancelable.True)
                return;

            DoAddService(service);

            listenMgr.OnAddedService(service);
        }

        private void DoAddService(IIOService service)
        {
            if (service.FrontController == null || service.FrontController != this)
                service.FrontController = this;
            lock (services)
                this.services.Add(service);
        }

        void IServiceManager.AddService(IServiceable service)
        {
            AddService((IIOService)service);
        }

        private void DoRemoveService(IIOService service)
        {
            if (service.FrontController != this)
                service.FrontController = null;
            this.services.Remove(service);
        }

        public void RemoveService(string serviceName)
        {
            if (string.IsNullOrEmpty(serviceName))
                return;
            var service = services.Find(p => { return p.Name == serviceName; });
            if (service == null)
                return;

            if (listenMgr.OnRemovingService(serviceName) == Cancelable.True)
                return;

            DoRemoveService(service);
            listenMgr.OnRemovedService(serviceName);
        }

        protected override void DoStart()
        {
            foreach (var svc in services)
                svc.Start();
        }

        protected override void DoStop()
        {
            foreach (var svc in services)
                svc.Stop();
        }

        protected override void DoClose()
        {
            foreach (var svc in services)
                svc.Close();

            if (filterProcessor != null)
                filterProcessor.Destroy();
            if (actionProcessor != null)
                actionProcessor.Destroy();
        }

        public abstract void Process(TPacket packet);

        void IFrontController.Process(IPacket packet)
        {
            Process((TPacket)packet);
        }
    }

}
