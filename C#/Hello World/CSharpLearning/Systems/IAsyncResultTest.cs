using System;
using System.Threading;
using NUnit.Framework;
using System.Threading.Tasks;

namespace CSharpLearning.Systems
{
    /// <summary>
    /// IAsyncResult接口实现类。
    /// </summary>
    class SimpleAsyncResult<T> : IAsyncResult
    {
        // All of the ordinary async result state.
        private volatile bool _isCompleted;
        private readonly ManualResetEvent _asyncWaitHandle;
        private readonly AsyncCallback _callback;
        private readonly object _asyncState;

        private Exception _exception;
        private T _result;

        public SimpleAsyncResult(Func<T> work, AsyncCallback callback, object state)
        {
            _callback = callback;
            _asyncState = state;
            _asyncWaitHandle = new ManualResetEvent(false);

            RunWorkAsynchronously(work);

            this.CompletedSynchronously = _asyncWaitHandle.WaitOne(0);
        }

        public WaitHandle AsyncWaitHandle { get { return _asyncWaitHandle; } }

        public object AsyncState { get { return _asyncState; } }

        public bool IsCompleted { get { return _isCompleted; } }

        public bool CompletedSynchronously { get; set; }

        // Runs the work on the thread pool, capturing exceptions,
        // results, and signaling completion.
        private void RunWorkAsynchronously(Func<T> work)
        {
            Task.Factory.StartNew(() =>
            {
                try
                {
                    _result = work();
                }
                catch (Exception e)
                {
                    _exception = e;
                }
                finally
                {
                    // Signal completion in the proper order:
                    _isCompleted = true;
                    _asyncWaitHandle.Set();

                    // 
                    if (_callback != null) _callback(this);
                }
            });
        }

        public T End()
        {
            // Wait for the work to finish, if it hasn't already.
            if (!_isCompleted)
            {
                _asyncWaitHandle.WaitOne();
            }

            _asyncWaitHandle.Close();

            // Propagate any exceptions or return the result.
            if (_exception != null) throw _exception;

            return _result;
        }
    }

    /// <summary>
    /// 一个提供了异步操作的类。
    /// </summary>
    class AsynchronizationOperationClass
    {
        public int Work(int sleepyTime)
        {
            Thread.Sleep(sleepyTime);

            return new Random().Next(100);
        }

        public IAsyncResult BeginWork(int sleepyTime, AsyncCallback callback, object state)
        {
            var ar = new SimpleAsyncResult<int>(
                delegate { return Work(sleepyTime); },
                callback,
                state);

            return ar;
        }

        public int EndWork(IAsyncResult asyncResult)
        {
            var simpleResult = asyncResult as SimpleAsyncResult<int>;

            if (simpleResult == null) throw new ArgumentException("Bad async result.");

            return simpleResult.End();
        }
    }


    [TestFixture]
    class IAsyncResultTest
    {
        [Test(Description="异步完成工作。")]
        public void Test1()
        {
            // 定义工作时间。
            int workTime = 3000; 
            var obj = new AsynchronizationOperationClass();

            // 
            var ar = obj.BeginWork(workTime, new AsyncCallback(p =>
            {
                try
                {
                    var rc = obj.EndWork(p);
                    Console.WriteLine("异步完成工作Result = " + rc);
                }
                catch (System.Exception ex)
                {
                    Console.WriteLine(ex.ToString());
                }
            }), null);

            ar.AsyncWaitHandle.WaitOne();

            Assert.AreEqual(false, ar.CompletedSynchronously);
        }
    }
}
