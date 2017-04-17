using System;
using System.Collections.Generic;
using System.Text;

namespace System
{
    public interface IChangedServiceProvider
    {
        ChangedService ChangedService { get;}
    }

    [Serializable]
    public class ChangedService : DisposableObject
    {
        private bool _isChanged;
        private bool _isFireAcceptedChangedEvent = true;
        private long _changedServiceCount = 0;
        private List<ChangedService> services;
        public event EventHandler ModelChanged;
        public event EventHandler AcceptedChanged;

        public ChangedService()
        {
        }

        //在SuspendChanged之后，恢复操作，且必须成对出现
        public void ResumeChanged()
        {
            _changedServiceCount--;
            if (services != null)
                foreach (ChangedService item in services)
                    item._changedServiceCount--;
        }
        //挂起变化的后续事件操作
        public void SuspendChanged()
        {
            _changedServiceCount++;
            if (services != null)
                foreach (ChangedService item in services)
                    item._changedServiceCount++;
        }

        public void MarkChanged()
        {
            if (_changedServiceCount <= 0)
            {
                _isChanged = true;
                OnModelChanged(this,EventArgs.Empty);
            }
        }

        protected void OnModelChanged(object sender,EventArgs e)
        {
            if (ModelChanged != null)
                ModelChanged(sender, e);
        }

        protected void OnAcceptedChanged(object sender, EventArgs e)
        {
            if (AcceptedChanged != null)
                AcceptedChanged(sender, e);
        }

        public bool HasChanged
        {
            get
            {
                return _isChanged;
            }
        }

        public void AcceptChanged()
        {
            _isChanged = false;
            if (_isFireAcceptedChangedEvent)
                OnAcceptedChanged(this,EventArgs.Empty);
            if (services != null)
                foreach (ChangedService item in services)
                    item._isChanged = false;
        }

        public void AddService(ChangedService service)
        {
            if (service == null)
                return;
            if (services == null)
                services = new List<ChangedService>();
            service._isFireAcceptedChangedEvent = false;
            service.ModelChanged += new EventHandler(service_ModelChanged);
            services.Add(service);
        }

        public void RemoveService(ChangedService service)
        {
            if (service == null)
                return;
            if (services == null)
                return;
            if (!services.Contains(service))
                return;
            service.ModelChanged -= service_ModelChanged;
            services.Remove(service);
            if (services.Count == 0)
                services = null;
        }

        void service_ModelChanged(object sender, EventArgs e)
        {
            MarkChanged();
        }

        protected override void Dispose(bool disposing)
        {
            base.Dispose(disposing);

            if (services != null)
            {
                foreach (ChangedService item in services)
                {
                    item.Dispose();
                }
                services.Clear();
                services = null;
            }

            ModelChanged = null;
        }
    }
}