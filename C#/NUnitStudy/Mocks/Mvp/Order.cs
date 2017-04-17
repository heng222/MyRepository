using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace NUnitStudy.Mocks.Mvp
{
    public class Order
    {
        public string ProductName { get; private set; }
        public int Quantity { get; private set; }

        public Order(string productName, int quantity)
        {
            this.ProductName = productName;
            this.Quantity = quantity;
        }
    }

}
