using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ProWrite.Core;

namespace ProWrite.UFE.Entity
{
    public class UFESign
    {
        public string Info { get; set; }
        public int Hight { get; set; }
        public int Width { get; set; }
        public SignType Type { get; set; }
    }
}
