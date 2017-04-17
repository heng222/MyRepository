using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace NUnitStudy.Mocks.Mvp
{
    public class OrdersPresenter
    {
        public OrdersPresenter(IOrdersView view)
        {
            view.OrderSelected += (sender, args) => DoOrderSelection(args.Order);
        }

        public Order SelectedOrder { get; private set; }

        private void DoOrderSelection(Order selectedOrder)
        {
            // Do something when the view selects an order.
            SelectedOrder = selectedOrder;
        }
    }
}
