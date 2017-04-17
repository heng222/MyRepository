using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace ProWrite.UFE.Entity
{
    [Serializable]
    public class DimmingSet
    {
        public int Mode { get; set; }
        public int Value { get; set; }
        public string StartTime { get; set; }
        public string EndTime { get; set; }
        //public WeeklyChoiceType Date { get; set; }
        public int DimType { get; set; }
    }

    public enum DimmingType
    {
        //Nits=1,
        Percent=2,
    }
}
