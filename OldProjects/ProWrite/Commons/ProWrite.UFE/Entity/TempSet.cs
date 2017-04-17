using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace ProWrite.UFE.Entity
{
    [Serializable]
    public class TempSet
    {
        public int Mode { get; set; }
        public int Type { get; set; }
        public string Value { get; set; }
    }

    public enum TempSetType
    {
        Fahrenheit=0,  // F = C * (9/5) + 32
        // F = R - 459.67
        // F = K * (9/5) - 459.67
        Celsius=1,     // C = (F - 32) * (5/9)
        // C = (R - 491.67) * (5/9)
        // C = K - 273.15
        Kelvin=2,      // K = C + 273.15
        // K = R * (5/9)
        // K = (F + 459.67) * (5/9)
        Rankine=3,     // R = C + 273.15 * (9/5)
        // R = F + 459.67
        // R = K * (9/5)
        //NullTempType=4, // Invalid or non set type
    }
}
