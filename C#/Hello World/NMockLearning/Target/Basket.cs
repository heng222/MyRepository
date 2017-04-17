using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Collections;

namespace NMockLearning.Target
{
    /// <summary>
    /// 购物篮
    /// </summary>
    class Basket
    {
        private ArrayList _basketItems; // 篮子里的具体物品 
        private Guid _basketID;
        private IShoppingDataAccess _dataAccess;

        public Basket(IShoppingDataAccess dataAccess, Guid id)
        {
            _dataAccess = dataAccess;
            _basketID = id;

            _basketItems = new ArrayList();
            _basketItems.AddRange(_dataAccess.LoadBasketItems(id));
        }

        // 向购物篮中增加一个物品 
        public void AddItem(BasketItem item)
        {
            _basketItems.Add(item);
        }

        // 把购物篮保存起来 
        public void Save()
        {
            _dataAccess.SaveBasketItems(_basketID,
                (BasketItem[])_basketItems.ToArray
                (typeof(BasketItem)));
        }

        // 计算购物篮中物品总价格 
        public decimal CalculateSubTotal()
        {
            decimal subTotal = 0;
            foreach (BasketItem item in _basketItems)
            {
                subTotal += item.Price;
            }
            return subTotal;
        }

    }
}
