using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace ProWrite.UFE.Entity
{
    [Serializable]
    public class TestPatternEntity
    {
        public UInt64 Value { get; set; }
        public byte[] FileLoc { get; set; }
        public int Type { get; set; }
        public int Flag { get; set; }
        public int Mode { get; set; }
        public string Suffix { get; set; }
    }

    public enum TestPatternType
    {
        PatternDisable = 0,
        // FILL = Fill the screen with a color
        //    color defined as a long RGB
        Fill=1,
        // HRAMP = Fill sign with horizontal ramp incremented by an 
        //         indicated number of pixels
        Hramp=2,
        // VRAMP = Fill sign with vertical ramp incremented by an 
        //         indicated number of pixels
        Vramp=3,
        // CROSS = Fill sign with a cross pattern
        Cross=4,
        // DIAGONAL = Fill sign with a diagonal pattern
        Diagonal=5,
        // VERTICAL = Fill sign with a vertical pattern
        Vertical=6,
        // COLORBAR = Fill sign with color bars (canned colors)
        ColorBar=7,
        // COLORGRID = Fill sign with color grid (canned colors)
        ColorGrid=8,
        // CUSTOM = Load a specific image and tile as pattern
        Custom=9,

    }
}
