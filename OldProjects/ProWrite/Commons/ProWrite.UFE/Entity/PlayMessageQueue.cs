using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace ProWrite.UFE.Entity
{
    [Serializable]
    public class PlayMessageQueue
    {
        public string MessagePath { get; set; }
        public int QueuePosition { get; set; }
    }

    [Serializable]
    public class SkipMessageQueue
    {
        public string UUID { get; set; }
        public int Position { get; set; }
    }
}
