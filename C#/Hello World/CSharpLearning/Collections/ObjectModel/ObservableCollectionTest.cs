using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using NUnit.Framework;
using System.Collections.ObjectModel;
using System.Collections.Specialized;

namespace CSharpLearning.Collections.ObjectModel
{
    [TestFixture]
    class ObservableCollectionTest
    {
        public void Test1()
        {
            var data = new ObservableCollection<string>();
            data.CollectionChanged += data_CollectionChanged;
            data.Add("One");
            data.Add("Three");
            data.Insert(1, "Two");
            data.Remove("Two");
        }

        void data_CollectionChanged(object sender, NotifyCollectionChangedEventArgs e)
        {
            try
            {
                Console.WriteLine(e.Action);
            }
            catch (System.Exception ex)
            {
                Console.WriteLine(ex);	
            }
        }
    }
}
