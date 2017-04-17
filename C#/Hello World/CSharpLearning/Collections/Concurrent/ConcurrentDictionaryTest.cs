using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using NUnit.Framework;
using System.Collections.Concurrent;

namespace CSharpLearning.Collections.Concurrent
{
    [TestFixture(Description = "ConcurrentDictionary Test")]
    class ConcurrentDictionaryTest
    {
        [Test]
        public void Test1()
        {
            // We know how many items we want to insert into the ConcurrentDictionary.
            // So set the initial capacity to some prime number above that, to ensure that
            // the ConcurrentDictionary does not need to be resized while initializing it.
            int NUMITEMS = 64;
            int initialCapacity = 101;

            // The higher the concurrencyLevel, the higher the theoretical number of operations
            // that could be performed concurrently on the ConcurrentDictionary.  However, global
            // operations like resizing the dictionary take longer as the concurrencyLevel rises. 
            // For the purposes of this example, we'll compromise at numCores * 2.
            int numProcs = Environment.ProcessorCount;
            int concurrencyLevel = numProcs * 2;

            // Construct the dictionary with the desired concurrencyLevel and initialCapacity
            var cd = new ConcurrentDictionary<int, int>(concurrencyLevel, initialCapacity);

            // Initialize the dictionary
            for (int i = 0; i < NUMITEMS; i++) cd[i] = i * i;

            Console.WriteLine("The square of 23 is {0} (should be {1})", cd[23], 23 * 23);
            
        }

        // Demonstrates:
        //      ConcurrentDictionary<TKey, TValue>.TryAdd()
        //      ConcurrentDictionary<TKey, TValue>.TryUpdate()
        //      ConcurrentDictionary<TKey, TValue>.TryRemove()
        [Test]
        public void Test2()
        {
            int numFailures = 0; // for bookkeeping

            // Construct an empty dictionary
            var cd = new ConcurrentDictionary<int, string>();

            // This should work
            if (!cd.TryAdd(1, "one"))
            {
                Console.WriteLine("CD.TryAdd() failed when it should have succeeded");
                numFailures++;
            }

            // This shouldn't work -- key 1 is already in use
            if (cd.TryAdd(1, "uno"))
            {
                Console.WriteLine("CD.TryAdd() succeeded when it should have failed");
                numFailures++;
            }

            // Now change the value for key 1 from "one" to "uno" -- should work
            if (!cd.TryUpdate(1, "uno", "one"))
            {
                Console.WriteLine("CD.TryUpdate() failed when it should have succeeded");
                numFailures++;
            }

            // Try to change the value for key 1 from "eine" to "one" 
            //    -- this shouldn't work, because the current value isn't "eine"
            if (cd.TryUpdate(1, "one", "eine"))
            {
                Console.WriteLine("CD.TryUpdate() succeeded when it should have failed");
                numFailures++;
            }

            // Remove key/value for key 1.  Should work.
            string value1;
            if (!cd.TryRemove(1, out value1))
            {
                Console.WriteLine("CD.TryRemove() failed when it should have succeeded");
                numFailures++;
            }

            // Remove key/value for key 1.  Shouldn't work, because I already removed it
            string value2;
            if (cd.TryRemove(1, out value2))
            {
                Console.WriteLine("CD.TryRemove() succeeded when it should have failed");
                numFailures++;
            }

            // If nothing went wrong, say so
            if (numFailures == 0) Console.WriteLine("  OK!");
        }
    }
}
