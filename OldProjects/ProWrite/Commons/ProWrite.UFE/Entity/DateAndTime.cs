﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace ProWrite.UFE.Entity
{
    [Serializable]
    public class DateAndTime
    {
        public int Mode { get; set; }
        public string CurrentTime { get; set; }
    }
}
