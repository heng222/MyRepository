using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ComponentModel;

namespace System.Communication
{
    public class ServiceAdapter : DisposableObject, IServiceable
    {
        private volatile bool _started = false;

        protected enum Cancelable
        {
            True,
            False,
        }

        protected class ListenerManager
        {
            private List<IServiceableListener> _listeners;

            public IServiceable Owner { get; set; }

            public ListenerManager()
            {
                _listeners = new List<IServiceableListener>(2);
            }

            public virtual void RegisterListener(IServiceableListener listener)
            {
                if (!_listeners.Contains(listener))
                    _listeners.Add(listener);
            }

            public virtual void RemoveListener(IServiceableListener listener)
            {
                if (_listeners.Contains(listener))
                    _listeners.Remove(listener);
            }

            public Cancelable OnIniting()
            {
                var e = new CancelEventArgs();
                foreach (var item in _listeners)
                {
                    item.OnIniting(Owner, e);
                    if (e.Cancel)
                        return Cancelable.True;
                }

                return Cancelable.False;
            }

            public void OnInited()
            {
                var e = EventArgs.Empty;
                foreach (var item in _listeners)
                    item.OnInited(Owner, e);
            }

            public Cancelable OnStarting()
            {
                var e = new CancelEventArgs();
                foreach (var item in _listeners)
                {
                    item.OnStarting(Owner, e);
                    if (e.Cancel)
                        return Cancelable.True;
                }

                return Cancelable.False;
            }

            public void OnStarted()
            {
                var e = EventArgs.Empty;
                foreach (var item in _listeners)
                    item.OnStarted(Owner, e);
            }

            public Cancelable OnStopping()
            {
                var e = new CancelEventArgs();
                foreach (var item in _listeners)
                {
                    item.OnStopping(Owner, e);
                    if (e.Cancel)
                        return Cancelable.True;
                }

                return Cancelable.False;
            }

            public void OnStopped()
            {
                var e = EventArgs.Empty;
                foreach (var item in _listeners)
                    item.OnStopped(Owner, e);
            }

            public Cancelable OnRestarting()
            {
                var e = new CancelEventArgs();
                foreach (var item in _listeners)
                {
                    item.OnRestarting(Owner, e);
                    if (e.Cancel)
                        return Cancelable.True;
                }

                return Cancelable.False;
            }

            public void OnRestarted()
            {
                var e = EventArgs.Empty;
                foreach (var item in _listeners)
                    item.OnRestarted(Owner, e);
            }

            public Cancelable OnClosing()
            {
                var e = new CancelEventArgs();
                foreach (var item in _listeners)
                {
                    item.OnClosing(Owner, e);
                    if (e.Cancel)
                        return Cancelable.True;
                }

                return Cancelable.False;
            }

            public void OnClosed()
            {
                var e = EventArgs.Empty;
                foreach (var item in _listeners)
                    item.OnClosed(Owner, e);
            }

            public void OnExceptionFired(Exception ex)
            {
                var e = new EventArgs<Exception>(ex);
                foreach (var item in _listeners)
                    item.OnClosed(Owner, e);
            }

        }

        private ListenerManager listenMgr;

        public ServiceAdapter()
        {
            listenMgr = new ListenerManager { Owner = this };
        }

        public string Name { get; set; }

        public void RegisterListener(IServiceableListener listener)
        {
            listenMgr.RegisterListener(listener);
        }

        public void RemoveListener(IServiceableListener listener)
        {
            listenMgr.RemoveListener(listener);
        }

        protected virtual void DoInit() { }
        public void Init()
        {
            if (listenMgr.OnIniting() == Cancelable.True)
                return;

            DoInit();

            listenMgr.OnInited();
        }

        protected virtual void DoStart() { }
        public void Start()
        {
            Check.Require(!_started, "Service already started");
            if (listenMgr.OnStarting() == Cancelable.True)
                return;

            DoStart();
            _started = true;

            listenMgr.OnStarted();
        }

        protected virtual void DoStop() { }
        public void Stop()
        {
            Check.Require(_started, "Service not started");

            if (listenMgr.OnStopping() == Cancelable.True)
                return;

            DoStop();
            _started = false;

            listenMgr.OnStopped();
        }

        public void Restart()
        {
            if (listenMgr.OnRestarting() == Cancelable.True)
                return;

            if (_started)
                Stop();
            Start();

            listenMgr.OnRestarted();
        }

        protected virtual void DoClose() { }
        public void Close()
        {
            if (listenMgr.OnClosing() == Cancelable.True)
                return;

            if (_started)
                Stop();
            DoClose();

            listenMgr.OnClosed();
        }

        public bool IsRunning
        {
            get { return _started; }
        }

        public void OnExceptionFired(Exception ex)
        {
            listenMgr.OnExceptionFired(ex);
        }

        protected override void Dispose(bool disposing)
        {
            listenMgr.OnClosing();
            if (_started)
                Stop();
            DoClose();
            listenMgr.OnClosed();

            base.Dispose(disposing);
        }

    }
}
