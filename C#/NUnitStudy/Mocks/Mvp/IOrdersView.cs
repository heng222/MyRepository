using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace NUnitStudy.Mocks.Mvp
{
    public interface IOrdersView
    {
        event EventHandler<OrderEventArgs> OrderSelected;
    }
}
