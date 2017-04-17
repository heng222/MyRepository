using System;
using System.Collections.Generic;
using System.Text;
using System.Collections;

namespace System.Collections.Generic
{
    public class SynDictionary<TKey, TValue> : Dictionary<TKey, TValue>
    {
        public readonly object InnerLocker = new object();

        public new void Add(TKey key, TValue value)
        {
            if (key != null)
            {
                lock (InnerLocker)
                {
                    base.Add(key, value);
                }
            }
        }

        public new TValue this[TKey key]
        {
            get
            {
                if (key != null && ContainsKey(key))
                    return base[key];
                return default(TValue);
            }
            set
            {
                if (key != null)
                {
                    lock (InnerLocker)
                    {
                        base.Add(key, value);
                    }
                }
            }
        }

        public new bool Remove(TKey key)
        {
            if (!ContainsKey(key))
                return false;
            lock (InnerLocker)
                return base.Remove(key);
        }

        public new void Clear()
        {
            lock (InnerLocker)
            {
                base.Clear();
            }
        }
    }

    class SynList<T> : List<T>
    {
        protected readonly object InnerLocker = new object();

        public new void Add(T item)
        {
            lock (InnerLocker)
                base.Add(item);
        }

        public new bool Remove(T item)
        {
            if (Contains(item))
                lock (InnerLocker)
                    base.Remove(item);
            return false;
        }
    }

    public interface IPriortyQueue<T> where T: IComparable<T>
    {
        void Put(T item);
        T Pop();
        T Top();
        int Count { get;}
        void Clear();
        bool Contains(T item);
        object SyncRoot { get;}
        bool IsSynchronized { get;}
    }

    /// <summary>
    /// Priority Queue based on stack
    /// </summary>
    /// <typeparam name="TMessage"></typeparam>
    [Serializable]
    public class PriorityQueue<T> : IPriortyQueue<T> where T : IComparable<T>
    {
        [NonSerialized]
        private T[] heap;
        [NonSerialized]
        private int count;
        [NonSerialized]
        private int maxSize;
        [NonSerialized]

        private readonly object InnerLocker = new object();

        public object SyncRoot { get { return InnerLocker; } }

        public virtual bool IsSynchronized { get { return false; } }

        public PriorityQueue() : this(10) { }
        public PriorityQueue(int maxSize)
        {
            count = 0;
            int heapSize = maxSize + 1;
            heap = new T[heapSize];
            this.maxSize = maxSize;
        }

        private bool LessThan(T a, T b)
        {
            return a.CompareTo(b) < 0;
        }

        private static int URShift(int number, int bits)
        {
            if (number >= 0)
                return number >> bits;
            else
                return (number >> bits) + (2 << ~bits);
        }

        public bool Contains(T item)
        {
            if (count < 1)
                return false;
            for (int i = 0; i < count; i++)
            {
                if (object.Equals(heap[i], item))
                    return true;
            }
            return false;
        }

        private void InternalPut(T item)
        {
            count++;
            heap[count] = item;
            UpHeap();
        }

        public void Put(T item)
        {
            if (count < maxSize - 1)
            {
                InternalPut(item);
            }
            else if (count > 0 && !LessThan(item, Top()))
            {
                heap[1] = item;
                AdjustTop();
            }
            else
            {
                maxSize *= 2;
                Array.Resize<T>(ref heap, maxSize);
                InternalPut(item);
            }
        }

        public T Top()
        {
            if (count > 0)
                return heap[1];
            else
                return default(T);
        }

        public T Pop()
        {
            if (count > 0)
            {
                T result = heap[1]; // save first value
                heap[1] = heap[count]; // move last to first
                heap[count] = default(T); // permit GC of objects
                count--;
                DownHeap(); // adjust heap
                return result;
            }
            else
                return default(T);
        }
       
        /**/
        /// <summary>Should be called when the Object at top changes values.  Still log(n)
        /// worst case, but it's at least twice as fast to <pre>
        /// { pq.top().change(); pq.adjustTop(); }
        /// </pre> instead of <pre>
        /// { o = pq.pop(); o.change(); pq.push(o); }
        /// </pre>
        /// </summary>
        public void AdjustTop()
        {
            DownHeap();
        }


        public int Count
        {
            get { return count; }
        }

        public void Clear()
        {
            for (int i = 0; i <= count; i++)
                heap[i] = default(T);
            count = 0;
        }

        private void UpHeap()
        {
            int i = count;
            T node = heap[i]; // save bottom node
            int j = URShift(i, 1);
            while (j > 0 && LessThan(node, heap[j]))
            {
                heap[i] = heap[j]; // shift parents down
                i = j;
                j = URShift(j, 1);
            }
            heap[i] = node; // install saved node
        }

        private void DownHeap()
        {
            int i = 1;
            T node = heap[i]; // save top node
            int j = i << 1; // find smaller child
            int k = j + 1;
            if (k <= count && LessThan(heap[k], heap[j]))
            {
                j = k;
            }
            while (j <= count && LessThan(heap[j], node))
            {
                heap[i] = heap[j]; // shift up child
                i = j;
                j = i << 1;
                k = j + 1;
                if (k <= count && LessThan(heap[k], heap[j]))
                {
                    j = k;
                }
            }
            heap[i] = node; // install saved node
        }

        private class SynPriorityQueue: IPriortyQueue<T>
        {
            private IPriortyQueue<T> InnerQueue;
            public SynPriorityQueue(IPriortyQueue<T> queue)
            {
                this.InnerQueue = queue;
            }



            #region IPriortyQueue<TMessage> Members

            public void Put(T item)
            {
                lock (InnerQueue.SyncRoot)
                    InnerQueue.Put(item);
            }

            public T Pop()
            {
                lock (InnerQueue.SyncRoot)
                    return InnerQueue.Pop();
            }

            public T Top()
            {
                return InnerQueue.Top();
            }

            public int Count
            {
                get
                {
                   return InnerQueue.Count;
                }
            }

            public void Clear()
            {
                lock (InnerQueue.SyncRoot)
                    InnerQueue.Clear();
            }

            public bool Contains(T item)
            {
                lock (InnerQueue.SyncRoot)
                    return InnerQueue.Contains(item);
            }

            public object SyncRoot
            {
                get { return InnerQueue.SyncRoot; }
            }

            public bool IsSynchronized
            {
                get { return true; }
            }

            #endregion
        }

        public static IPriortyQueue<T> Synchronized(IPriortyQueue<T> innerQueue)
        {
            return new SynPriorityQueue(innerQueue);
        }
    }

    
}
