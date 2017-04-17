using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Communication;
using System.Threading;

namespace System.Tcp
{
    public class HeartBeatMonitor
    {
        private HeartBeatMonitor()
        {
            items = new Dictionary<MonitorItem, byte>();
            heartBeatCheckTimer = new System.Timers.Timer();
            heartBeatCheckTimer.Interval = 1000;
            heartBeatCheckTimer.Elapsed += new System.Timers.ElapsedEventHandler(timer_Elapsed);
        }

        private static HeartBeatMonitor instance;
        public static HeartBeatMonitor Instance
        {
            get
            {
                if (instance == null)
                {
                    Interlocked.CompareExchange<HeartBeatMonitor>(ref instance, new HeartBeatMonitor(), null);
                }
                return instance;
            }
        }

        void timer_Elapsed(object sender, System.Timers.ElapsedEventArgs e)
        {
            MonitorItem[] array = null;
            lock (trackLocker)
            {
                array = items.Keys.ToArray();
            }

            if (array != null && array.Length > 0)
            {
                foreach (var item in array)
                {
                    
                    var timespan = DateTime.Now - item.CurrentTime;
                    var tick = timespan.TotalMilliseconds;
                    if (tick > HeartInterval * HeartCheckCount)
                    {
                        item.Connection.Close();
                        lock (trackLocker)
                        {
                            items.Remove(item);
                        }
                    }
                }
            }
        }

        public double Interval
        {
            get { return heartBeatCheckTimer.Interval; }
            set
            {
                if (value != heartBeatCheckTimer.Interval)
                    heartBeatCheckTimer.Interval = value;
            }
        }

        private System.Timers.Timer heartBeatCheckTimer;
        private volatile object trackLocker = new object();
        private Dictionary<MonitorItem,byte> items;
        private const byte placeHold = 0;

        public int HeartInterval { get; set; }
        public int HeartCheckCount { get; set; }

        public void Stop()
        {
            heartBeatCheckTimer.Stop();
        }

        public void Start()
        {
            heartBeatCheckTimer.Start();
        }

        public void AddItem(MonitorItem item)
        {
            if (item != null)
            {
                lock (trackLocker)
                {
                    items[item] = placeHold;
                    Monitor.Pulse(trackLocker);
                }
            }
        }

        public void RemoveItem(IConnectionBase conn)
        {
            if (conn == null || items.Count < 1)
                return;

            MonitorItem[] array = null;
            lock (trackLocker)
            {
                array = items.Keys.ToArray();
                var item = Array.Find<MonitorItem>(array, p => { return p.Connection == conn; });
                if (item != null)
                {
                    items.Remove(item);
                }
            }
        }

        public class MonitorItem
        {
            public IConnectionBase Connection;
            public DateTime CurrentTime;
            public DateTime LastTime;
        }
    }
}
