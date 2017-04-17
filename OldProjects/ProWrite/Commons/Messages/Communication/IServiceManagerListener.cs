using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace System.Communication
{
    public interface IServiceManagerListener : IServiceableListener
    {
        void OnAddingService(object sender, CancelEventArgs<IServiceable> e);
        void OnAddedService(object sender, EventArgs<IServiceable> e);

        void OnRemovingService(object sender, CancelEventArgs<string> e);
        void OnRemovedService(object sender, EventArgs<string> e);
    }
}
