using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace System.Communication
{
    public interface IServiceable
    {
        string Name { get; set; }

        void Init();

        void RegisterListener(IServiceableListener listener);
        void RemoveListener(IServiceableListener listener);

        void Start();
        void Stop();
        void Restart();
        void Close();

        bool IsRunning { get; }
    }

}
