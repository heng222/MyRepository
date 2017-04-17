using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Moq;
using NUnit.Framework;

namespace NUnitStudy.Mocks.Mvp
{
    [TestFixture]
    public class OrdersPresenterTest
    {
        [Test]
        public void TestPresenterSelection()
        {
            var mockView = new Mock<IOrdersView>();
            var presenter = new OrdersPresenter(mockView.Object);

            Assert.Null(presenter.SelectedOrder);

            mockView.Raise(mv => mv.OrderSelected += null, new OrderEventArgs { Order = new Order("moq", 500) });

            Assert.NotNull(presenter.SelectedOrder);
            Assert.AreEqual("moq", presenter.SelectedOrder.ProductName);
        }
    }
}
