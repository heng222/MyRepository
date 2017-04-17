using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using NUnit.Framework;
using System.Collections.Concurrent;
using System.Threading.Tasks;
using System.Threading;

namespace CSharpLearning.Collections.Concurrent
{
    /// <summary>
    /// 
    /// </summary>
    [TestFixture(Description = "BlockingCollection Test")]
    class BlockingCollectionTest
    {
        [Test(Description = "Test 1")]
        public void Test1()
        {
            //IProducerConsumerCollection<int>
            //ConcurrentQueue<int>
            //ConcurrentDictionary<int, string>
            //ConcurrentStack<int>
            //ConcurrentBag<int>
        }

        // Demonstrates:
        //      BlockingCollection<T>.Add()
        //      BlockingCollection<T>.Take()
        //      BlockingCollection<T>.CompleteAdding()
        [Test(Description = "AddTakeCompleteAdding_Test")]
        public void AddTryTakeCompleteAdding_Test()
        {
            var bc = new BlockingCollection<int>();
            using (bc)
            {
                // Spin up a Task to consume the BlockingCollection
                using (Task t2 = Task.Factory.StartNew(() =>
                {
                    try
                    {
                        // Consume consume the BlockingCollection
                        while (!bc.IsCompleted)
                        {
                            int food;
                            if (bc.TryTake(out food, Timeout.Infinite))
                            {
                                Console.WriteLine(string.Format("消费：{0},{1}", 
                                    DateTime.Now.ToString("yyyy-mm-dd HH:MM:ss.fff"), food));
                            }
                        }

                        Console.WriteLine("{0},完成消费!", DateTime.Now.ToString("yyyy-mm-dd HH:MM:ss.fff"));
                    }
                    catch (Exception ex)
                    {
                        Console.WriteLine(ex);
                    }
                }))

                // Spin up a Task to populate the BlockingCollection 
                using (Task t1 = Task.Factory.StartNew(() =>
                {
                    bc.Add(1);
                    Thread.Sleep(1000);

                    bc.Add(2);
                    Thread.Sleep(2000);

                    bc.Add(3);
                    Thread.Sleep(3000);

                    bc.Add(4);
                    Thread.Sleep(4000);

                    bc.CompleteAdding();
                }))

                Task.WaitAll(t1, t2);
            }
        }

        // Demonstrates:
        //      BlockingCollection<T>.Add()
        //      BlockingCollection<T>.CompleteAdding()
        //      BlockingCollection<T>.TryTake()
        //      BlockingCollection<T>.IsCompleted
        [Test(Description = "TryTake_Test")]
        public void TryTake_Test()
        {
            // Construct and fill our BlockingCollection
            using (var bc = new BlockingCollection<int>())
            {
                int NUMITEMS = 10000;
                for (int i = 0; i < NUMITEMS; i++) bc.Add(i);
                bc.CompleteAdding();
                int outerSum = 0;

                // Delegate for consuming the BlockingCollection and adding up all items
                Action action = () =>
                {
                    int localItem;
                    int localSum = 0;

                    while (bc.TryTake(out localItem)) localSum += localItem;
                    Interlocked.Add(ref outerSum, localSum);
                };

                // Launch three parallel actions to consume the BlockingCollection
                Parallel.Invoke(action, action, action);

                Console.WriteLine("Sum[0..{0}) = {1}, should be {2}", NUMITEMS, outerSum, ((NUMITEMS * (NUMITEMS - 1)) / 2));
                Console.WriteLine("bc.IsCompleted = {0} (should be true)", bc.IsCompleted);
            }
        }

        // Demonstrates:
        //      Bounded BlockingCollection<T>
        //      BlockingCollection<T>.TryAddToAny()
        //      BlockingCollection<T>.TryTakeFromAny()
        [Test(Description = "FromToAny_Test")]
        public void FromToAny_Test()
        {
            BlockingCollection<int>[] bcs = new BlockingCollection<int>[2];
            bcs[0] = new BlockingCollection<int>(5); // collection bounded to 5 items
            bcs[1] = new BlockingCollection<int>(5); // collection bounded to 5 items

            // Should be able to add 10 items w/o blocking
            int numFailures = 0;
            for (int i = 0; i < 10; i++)
            {
                if (BlockingCollection<int>.TryAddToAny(bcs, i) == -1) numFailures++;
            }
            Console.WriteLine("TryAddToAny: {0} failures (should be 0)", numFailures);

            // Should be able to retrieve 10 items
            int numItems = 0;
            int item;
            while (BlockingCollection<int>.TryTakeFromAny(bcs, out item) != -1) numItems++;
            Console.WriteLine("TryTakeFromAny: retrieved {0} items (should be 10)", numItems);
        }

        // Demonstrates:
        //      BlockingCollection<T>.Add()
        //      BlockingCollection<T>.CompleteAdding()
        //      BlockingCollection<T>.GetConsumingEnumerable()
        [Test(Description = "GetConsumingEnumerable_Test")]
        public void GetConsumingEnumerable_Test()
        {
            using (BlockingCollection<int> bc = new BlockingCollection<int>())
            {
                // Kick off a producer task
                Task.Factory.StartNew(() =>
                {
                    for (int i = 1; i <= 10; i++)
                    {
                        bc.Add(i);
                        Thread.Sleep(500); // sleep 100 ms between adds
                    }

                    // Need to do this to keep foreach below from hanging
                    bc.CompleteAdding();
                });

                // Now consume the blocking collection with foreach.
                // Use bc.GetConsumingEnumerable() instead of just bc because the
                // former will block waiting for completion and the latter will
                // simply take a snapshot of the current state of the underlying collection.
                foreach (var item in bc.GetConsumingEnumerable())
                {
                    Console.WriteLine(item);
                }
            }
        }
    }
}
