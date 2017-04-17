using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace NMockLearning.Target
{
    public interface IShoppingDataAccess
    {
        string ConnectionString { get; set; }

        event EventHandler<EventArgs> Load;

        string GetProductName(int productID);

        int GetUnitPrice(int productID);

        BasketItem[] LoadBasketItems(Guid basketID);

        void SaveBasketItems(Guid basketID, BasketItem[] basketItems);
    }
}
