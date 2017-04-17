using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ComponentModel;

namespace System
{
    [Serializable]
    public class EventArgs<TFirst> : EventArgs
    {
        public readonly TFirst First;
        public EventArgs(TFirst first)
        {
            First = first;
        }
    }

    [Serializable]
    public class EventArgs<TFirst,TSecond> : EventArgs<TFirst>
    {
        public readonly TSecond Second;
        public EventArgs(TFirst first,TSecond second):base(first)
        {
            Second = second;
        }
    }

    [Serializable]
    public class CancelEventArgs<TFirst> : CancelEventArgs
    {
        public readonly TFirst First;
        public CancelEventArgs(TFirst first)
        {
            First = first;
        }
    }

    [Serializable]
    public class CancelEventArgs<TFirst,TSecond> : CancelEventArgs<TFirst>
    {
        public readonly TSecond Second;
        public CancelEventArgs(TFirst first, TSecond second)
            : base(first)
        {
            Second = second;
        }
    }


}
