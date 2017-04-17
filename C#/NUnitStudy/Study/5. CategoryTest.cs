using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using NUnit.Framework;

namespace NUnitStudy.Study
{
    [TestFixture]
    public class Category1Test
    {
        [Test]
        [Category("Math")]
        public void AddTest()
        {
            Assert.AreEqual(2, 1 + 1);
        }
    }

    [TestFixture]
    public class Category2Test
    {
        [Test]
        [Category("Math")]
        public void SubTest()
        {
            Assert.AreEqual(2, 3 - 1);
        }
    }
}
