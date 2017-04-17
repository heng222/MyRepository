using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using NMockLearning.Target;
using NMock;
using NUnit.Framework;

namespace NMockLearning.Tests
{
    [TestFixture]
    public class BasketTest
    {
        [Test]
        public void Test1()
        {
            var basketId1 = Guid.NewGuid();

            // crate mock
            var mock = new MockFactory();
            var access = mock.CreateMock<IShoppingDataAccess>();

            var itemQueue = new Queue<BasketItem>();
            itemQueue.Enqueue(new BasketItem(1, 1));
            itemQueue.Enqueue(new BasketItem(2, 2));
            itemQueue.Enqueue(new BasketItem(2, 3));

            access.Expects.One.Method(p => p.LoadBasketItems(basketId1)).
                With(basketId1).
                Will(Return.Value(itemQueue.ToArray()));
            
            // create basket1.
            var basket1 = new Basket(access.MockObject, basketId1);
            var totalPrice = basket1.CalculateSubTotal();
            Assert.AreEqual(6, totalPrice);
        }

        void MockObject_Load(object sender, EventArgs e)
        {
            throw new NotImplementedException();
        }

        [Test]
        public void Test2()
        {
            var basketId1 = Guid.NewGuid();

            // crate mock
            var mock = new MockFactory();
            var access = mock.CreateMock<IShoppingDataAccess>();

            var itemQueue = new Queue<BasketItem>();
            itemQueue.Enqueue(new BasketItem(1, 1));
            itemQueue.Enqueue(new BasketItem(2, 2));
            itemQueue.Enqueue(new BasketItem(2, 3));

            access.Expects.Any.Method(p => p.LoadBasketItems(basketId1)).
                WithAnyArguments().
                Will(Return.Value(itemQueue.ToArray()));

            // create basket1.
            var basket1 = new Basket(access.MockObject, basketId1);
            var totalPrice = basket1.CalculateSubTotal();
            Assert.AreEqual(6, totalPrice);

            // create basket2
            var basketId2 = Guid.NewGuid();
            var basket2 = new Basket(access.MockObject, basketId2);
            totalPrice = basket2.CalculateSubTotal();
            Assert.AreEqual(6, totalPrice);
        }
    }
}
