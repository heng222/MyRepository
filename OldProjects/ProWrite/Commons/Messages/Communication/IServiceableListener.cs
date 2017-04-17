using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ComponentModel;

namespace System.Communication
{
    public interface IServiceableListener : IEventListener
    {
        void OnIniting(object sender, CancelEventArgs e);
        void OnInited(object sender, EventArgs e);

        void OnStarting(object sender, CancelEventArgs e);
        void OnStarted(object sender, EventArgs e);

        void OnStopping(object sender, CancelEventArgs e);
        void OnStopped(object sender, EventArgs e);

        void OnRestarting(object sender, CancelEventArgs e);
        void OnRestarted(object sender, EventArgs e);

        void OnClosing(object sender, CancelEventArgs e);
        void OnClosed(object sender, EventArgs e);

        void OnExceptionFired(object sender, EventArgs<Exception> e);
    }
}
