using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using NUnit.Framework;
using ProWrite.Entity.Dashboard;
using System.Net.Tcp;
using System.Net;
using System.Threading;
using ProWrite.Core;
using log4net.Config;
using System.Reflection;
using log4net;
using System.Communication;

namespace ProWrite.UFE.Test.Upload
{
    [TestFixture]
    public class ConnectionTestBase
    {
        protected SignInfo Sign { get; private set; }
        protected bool IsOnline { get; private set; }


        protected string Address { get; set; }
        protected int Port { get; set; }
        protected string Account { get; set; }
        protected string Password { get; set; }

        protected static log4net.ILog log = LogManager.GetLogger("Controller");

        public ConnectionTestBase()
        {
            Address = "10.10.65.58";//10.10.65.58
            Port = 2011;
            Account = "cmd";
            Password = "123";
            BasicConfigurator.Configure();

            Sign = new SignInfo();
            ProWrite.UI.Controls.Actions.UFE.Responses.UFEResponseService.Init(Sign);
        }



        [SetUp]
        public void Open()
        {
            var connParams = new TcpConnectionParams(new System.Net.IPEndPoint(IPAddress.Parse(Address), Port));
            (Sign.Controller.Connection as TcpUFEConnection).Params = connParams;

            log.Info("Begin Open Connection.");
            Sign.Controller.Connection.OpenAsync(p =>
                {
                    if (!p.IsSuccessed)
                        log.Error(p.Exception.Message + "\r\n\t\t" + p.Exception.StackTrace);
                    else
                    {
                        log.Info("Connection Opened");
                        Sign.Controller.UserManager.Login(Account, Password, cb =>
                            {
                                IsOnline = cb.IsSuccessed;
                                if (!IsOnline)
                                    log.Error(cb.Exception.Message + "\r\n\t\t" + cb.Exception.StackTrace);
                                else
                                    log.Info("Login success.");
                            });
                    }
                });
        }

        [Test]
        public void BlankSign()
        {

            Assert.IsTrue(IsOnline, "User login failed!");
            
            var task = Sign.Controller.MAManager.BlankSign();
            if (!task.IsCompleted)
            {
                task.Wait();

                if (task.IsSuccessed)
                    Console.WriteLine("BlankSign OK!");
                else
                    Console.WriteLine("BlankSign Failed!");

                Assert.IsTrue(task.IsSuccessed);
            }
        }

        [Test]
        public void Perform()
        {
            //IAsyncFuture<UFEPacket> task = AsyncFuture<UFEPacket>.Current;
            //if (task != null && !task.IsCompleted)
            //    task.Wait();

            //Thread.CurrentThread.Join();

            Thread.Sleep(3000);

            Assert.IsTrue(IsOnline, "User login failed!");
            DoPerform();
        }

        protected virtual void DoPerform()
        {
        }

        protected virtual void Destroy()
        {
        }

        [TearDown]
        protected void Close()
        {
            Destroy();

            if (IsOnline)
            {

                var task = Sign.Controller.UserManager.Logoff();
                if (!task.IsCompleted)
                    task.Wait();
                task.Close();
            }
            if (Sign.Controller.Connection.State == System.Communication.ConnectionState.Opened)
                Sign.Controller.Connection.Close();
        }
    }
}
