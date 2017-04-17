using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using NUnit.Framework;
using NUnitStudy.Framework;
using System.IO;
using System.Collections.ObjectModel;

namespace NUnitStudy.Specs
{
    [TestFixture]
    public class TableSpec
    {
        [Test]
        public void Valid_Test()
        {
            Table table = Table.Parse(@"Specs\Table\Contact.data.txt");

            //Assert.That(table.Rows.Count, Is.EqualTo(3));
            //Assert.That(table.Columns.Count, Is.EqualTo(3));

            ////Column Test
            //Assert.That(table.Columns[0], Is.EqualTo("姓名"));
            //Assert.That(table.Columns[1], Is.EqualTo("年龄"));
            //Assert.That(table.Columns[2], Is.EqualTo("性别"));

            Assert.AreEqual(3, table.Rows.Count);
            Assert.AreEqual(3, table.Columns.Count);


        }

        [Test]
        [ExpectedException(typeof(ArgumentNullException))]
        public void None_File_Test()
        {
            Table table = Table.Parse(null);

            //不会执行下面的代码
        }

        [Test]
        //[ExpectedException(typeof(FormatException))]
        public void Invalid_Data_Test()
        {
            Table table = Table.Parse(@"Specs\Table\Invalid.Contact.data.txt");

            //不会执行下面的代码
        }

        [Test]
        public void Empty_Data_Test()
        {
            Table table = Table.Parse(@"Specs\Table\EmptyRow.Contact.data.txt");

            Assert.That(table.Rows.Count, Is.EqualTo(3));
            Assert.That(table.Columns.Count, Is.EqualTo(3));

            foreach (var row in table.Rows)
                foreach (var item in row)
                    Assert.IsEmpty(item);
        }
    }
}
