using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ProWrite.Core;

namespace ProWrite.Entity.Live
{
    public interface ILiveItem : IKeyInfo
    {
        /// <summary>
        /// get library type
        /// </summary>
        LiveType Type { get; }
        object[] ToArray();
    }

    public interface ILockLiveItem : ILiveItem
    {
        bool IsLock { get; set; }
        int LockCount { get; }
        void FromTo(ILockLiveItem item, int lockCounter);
    }
}
