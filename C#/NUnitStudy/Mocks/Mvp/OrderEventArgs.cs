using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace NUnitStudy.Mocks.Mvp
{
    public class OrderEventArgs : EventArgs
    {
        public Order Order { get; set; }
    }
}
