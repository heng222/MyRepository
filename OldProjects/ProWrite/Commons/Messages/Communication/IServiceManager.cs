using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace System.Communication
{
    public interface IServiceManager : IServiceable
    {
        IServiceable[] Services { get; }
        void AddService(IServiceable service);
        void RemoveService(string serviceName);
    }
}
