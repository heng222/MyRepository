using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using NUnit.Framework;

namespace CSharpLearning.异步编程模式.APM
{
    /// <summary>
    /// 命令回应信息。
    /// </summary>
    class CmdResponse
    {
        public override string ToString()
        {
            return DateTime.Now.ToString();
        }
    }

    /// <summary>
    /// TSR 操作类。
    /// </summary>
    class TsrOperation
    {
        private AsyncResult _asyncResult;
        private readonly ManualResetEventSlim _event = new ManualResetEventSlim(false);
        private CmdResponse _cmdRsp;
        private Action<IAsyncResult> _callback;

        class AsyncResult : IAsyncResult
        {
            public bool IsCompleted { get; set; }
            public WaitHandle AsyncWaitHandle { get; set; }
            public object AsyncState { get; set; }
            public bool CompletedSynchronously { get; set; }
        }

        public IAsyncResult BeginFirstSetup(Action<IAsyncResult> callback)
        {
            if (_asyncResult != null) throw new InvalidOperationException();

            _callback = callback;

            this.CreateAsyncResult();

            // 
            _cmdRsp = null;
            _event.Reset();

            // 发送命令。
            this.SendCommand();

            return _asyncResult;
        }

        public CmdResponse EndFirstSetup(IAsyncResult ar)
        {
            _asyncResult = null;

            if (!ar.IsCompleted)
            {
                ar.AsyncWaitHandle.WaitOne();
            }

            // 
            return _cmdRsp;
        }

        private void CreateAsyncResult()
        {
            _asyncResult = new AsyncResult();
            _asyncResult.AsyncWaitHandle = _event.WaitHandle;
        }

        private void SendCommand()
        {
            // 模拟发送数据
            Thread.Sleep(20);

            // 模拟N秒后收到回应。(类似 ReceiveCallBack 函数)
            Task.Factory.StartNew(() =>
              {
                  Thread.Sleep(5000);

                  if (_asyncResult != null)
                  {
                      // 构造命令回应。
                      _cmdRsp = new CmdResponse();

                      // 设置完成标记。
                      _asyncResult.IsCompleted = true;
                      // 激活事件。
                      _event.Set();

                      //
                      if (_callback != null)
                      {
                          _callback.Invoke(_asyncResult);
                          _asyncResult = null;
                      }

                  }
              });

        }
    }

    [TestFixture]
    class IAsynResultTest
    {
        TsrOperation _operation = new TsrOperation();

        private void OnFirstSetupCallback(IAsyncResult ar)
        {
            var cmdRsp = _operation.EndFirstSetup(ar);

            Console.WriteLine($"设置完成，收到回应：{cmdRsp}");
        }

        private void WaitforComplete(byte timeoutSeconds)
        {
            for (int i = 0; i < timeoutSeconds; i++)
            {
                Console.Write(".");
                Thread.Sleep(1000);
            }
        }

        [Test]
        public void Test1()
        {
            CmdResponse cmdRsp;

            // 正常情况。
            _operation.BeginFirstSetup(OnFirstSetupCallback);
            this.WaitforComplete(6);

            // 异常情况（5秒超时，结束操作）。
            var ar = _operation.BeginFirstSetup(OnFirstSetupCallback);
            this.WaitforComplete(2);
            Console.WriteLine("超时，结束操作");
            cmdRsp = _operation.EndFirstSetup(ar);
            Assert.AreEqual(null, cmdRsp);

            // 
            Thread.Sleep(10000);
        }
    }
}
