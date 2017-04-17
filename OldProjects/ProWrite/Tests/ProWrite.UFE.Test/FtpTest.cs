using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using NUnit.Framework;
using System.Threading.Tasks;
using Tamir.SharpSsh;
using Tamir.SharpSsh.jsch;


namespace ProWrite.UFE.Test
{
    [TestFixture]
    public class FtpTest
    {
        private Task openFtpTask;
        private Ftp ftp;

        private class Ftp : Sftp
        {
            public Ftp(string host, string user, string pwd) : base(host, user, pwd) { }

            public ChannelSftp Channel
            {
                get { return base.m_channel as ChannelSftp; }
            }
        }

        [SetUp]
        public void Init()
        {
            openFtpTask = Task.Create(p =>
                {
                    ftp = new Ftp("10.10.65.77", "root", "123456");
                    try
                    {
                        ftp.Connect();
                    }
                    catch (Exception ex)
                    {
                        Console.WriteLine(ex.StackTrace);
                    }
                });
        }

        [Test]
        public void CreateDirTest()
        {
            if (openFtpTask != null)
            {
                if (!openFtpTask.IsCompleted)
                    openFtpTask.Wait();
                openFtpTask.Dispose();
                openFtpTask = null;
            }

            Assert.IsNotNull(ftp);
            Assert.IsTrue(ftp.Connected);

            ChannelSftp channel = ftp.Channel;
            Assert.IsTrue(channel.isConnected());

            try
            {
                var vector = channel.ls("wqs");
                if (vector != null && vector.Count > 0)
                    channel.rmdir("wqs");
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.StackTrace);
            }

            string dir = "wqs/";

            try
            {
                channel.mkdir(dir);
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.StackTrace);
            }


            dir = "wqs/a";

            try
            {
                channel.mkdir(dir);
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.StackTrace);
            }

            dir = "wqs/a/aa/";

            try
            {
                channel.mkdir(dir);
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.StackTrace);
            }
          
        }

        [TearDown]
        public void Destroy()
        {
            if (ftp != null && ftp.Connected)
            {
                try
                {
                    ftp.Close();
                }
                catch (Exception ex)
                {
                    Console.WriteLine(ex.StackTrace);
                }

                ftp = null;
            }
        }
    }
}
