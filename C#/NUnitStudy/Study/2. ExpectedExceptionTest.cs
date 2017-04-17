using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using NUnit.Framework;

namespace NUnitStudy.Study
{
    [TestFixture]
    public class ExpectedExceptionTest
    {
        [Test]
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
