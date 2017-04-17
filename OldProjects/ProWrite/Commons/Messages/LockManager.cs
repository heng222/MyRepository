using System;
using System.Collections.Generic;
using System.Text;
using System.Threading;

namespace System
{
    public class LockManager
    {
        private readonly static int n = 10;
        static int i;

        [NonSerialized]
        private static int _lock;

        public static void Lock()
        {
            while (Interlocked.CompareExchange(ref _lock, 1, 0) == 1)
            {
                i = 0;
                while (_lock == 1)
                {
                    if (i++ > n)
                    {
                        i = 0;
                        Thread.Sleep(0);
                    }
                }
            }
        }

        public static void UnLock()
        {
            _lock = 0;
        }
    }
}
