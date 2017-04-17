using System;
using System.Collections.Generic;
using System.Text;
using System.Runtime.Serialization;
using System.Threading;
using System.Collections;
using System.Diagnostics;

namespace System
{
    public class WeakReference<T> : WeakReference where T : class
    {
        protected int hashCode = -1;
        public WeakReference() : base(null) { }
        public WeakReference(T target) : base(target) { hashCode = target.GetHashCode(); }
        public WeakReference(T target, bool trackResurrection) : base(target, trackResurrection) { hashCode = target.GetHashCode(); }
       
        public new T Target
        {
            get
            {
                return base.Target as T;
            }
            set
            {
                base.Target = value;
            }
        }

        public override int GetHashCode()
        {
            return hashCode;
        }

        public override bool Equals(object o)
        {
            WeakReference<T> other = o as WeakReference<T>;
            if (other == null)
            {
                return false;
            }
            T item = this.Target;
            if (item == null)
            {
                return false;
            }

            return ((this.hashCode == other.hashCode) && object.Equals(item, other.Target));
        }

        public static implicit operator T(WeakReference<T> o)
        {

            if (o != null && o.Target != null)
                return o.Target;
            return null;
        }

        public static implicit operator WeakReference<T>(T target)
        {
            return new WeakReference<T>(target);
        }
    }

    //public class WeakMap<TKey,TValue> 
    //    where TKey : class
    //    where TValue:class
    //{
    //    private Dictionary<WeakKey, WeakReference<TValue>> _table = new Dictionary<WeakKey, WeakReference<TValue>>();

    //    public TValue this[TKey key]
    //    {
    //        get
    //        {
    //            Debug.Assert(key != null);
    //            TValue o = null;

    //            LockManager.Lock();
    //            if (_table.Count > 0)
    //            {
    //                WeakKey wk = new WeakKey(key);

    //                WeakReference<TValue> val = null;
    //                _table.TryGetValue(wk,out val);
    //                o = (val != null) ? val.Target : default(TValue);
    //            }
    //            LockManager.UnLock();

    //            return o;
    //        }

    //        set
    //        {
    //            Debug.Assert(key != null);

    //            LockManager.Lock();
    //            WeakKey weakkey = new WeakKey(key, _table);
    //            _table[weakkey] = new WeakReference<TValue>(value);
    //            LockManager.UnLock();
    //        }
    //    }

    //    public void Add(TKey key, TValue val)
    //    {
    //        Debug.Assert(key != null);

    //        LockManager.Lock();
    //        _table.Add(new WeakKey(key, _table), new WeakReference<TValue>(val));
    //        LockManager.UnLock();
    //    }

    //    public void Remove(TKey key)
    //    {
    //        Debug.Assert(key != null);

    //        LockManager.Lock();
    //        _table.Remove(new WeakKey(key));
    //        LockManager.UnLock();
    //    }

    //    private class WeakKey : WeakReference<TKey>
    //    {
    //        Dictionary<WeakKey,WeakReference<TValue>> _map;

    //        public WeakKey(TKey key)
    //            : this(key, null)
    //        {
    //        }

    //        public WeakKey(TKey key, Dictionary<WeakKey,WeakReference<TValue>> map)
    //            : base(key)
    //        {
    //            _map = map;
    //        }

    //        public new TKey Target
    //        {
    //            get
    //            {
    //                TKey val = base.Target;

    //                // Takes itself out of the weakmap if the key is gone
    //                if (val == null)
    //                {
    //                    Dictionary<WeakKey,WeakReference<TValue>> map = Interlocked.Exchange(ref _map, null) as Dictionary<WeakKey,WeakReference<TValue>>;

    //                    if (map != null)
    //                        map.Remove(this);
    //                }

    //                return val;
    //            }
    //        }

    //    }
    //}
}
