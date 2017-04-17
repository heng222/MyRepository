using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace NMockLearning.Target
{
    public class BasketItem
    {
        public int ProductID { get; set; }

        public decimal Price { get; set; }

        public BasketItem(int id, decimal price)
        {
            this.ProductID = id;
            this.Price = price;
        }
    }
}
