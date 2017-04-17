using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace NUnitStudy.Study
{
    using NUnit.Framework;

     [TestFixture]
    public class ExplicitTest
    {
        [Test,Explicit]
        public void Test()
        {
            NullReferenceException expected = null;

            try
            {
                string str = null;

                str.Trim();
            }
            catch (NullReferenceException ex)
            {
                expected = ex;
            }

            Assert.IsNotNull(expected);
        }

        [Test, ExpectedException(typeof(NullReferenceException))]
        public void Test2()
        {
            string str = null;

            str.Trim();
        }
    }
}
