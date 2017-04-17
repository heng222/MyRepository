using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using NUnit.Framework;
using ProWrite.UFE;
using System.Threading;
using System.IO.Ports;

namespace ProWrite.UFE.Test
{
    [TestFixture]
    public class RS232ConnectionTest
    {
        [Test]
        public void Test()
        {
            //RS232Connection conn = new RS232Connection();
            //RS232Params p = new RS232Params();
            //p.PortName = "COM1";
            //p.StopBits = System.IO.Ports.StopBits.One;
            //p.BaudRate = 9600;
            //p.DataBits = 8;
            //p.Parity = System.IO.Ports.Parity.None;
            //conn.Params = p;

            //var rs = conn.Open();
            //if (!rs.IsCompleted)
            //    rs.Wait();

            //Assert.IsTrue(rs.IsSuccessed);

            //UFEPacket packet = new UFEPacket { Command = Commands.Login, Content = new  {Account="adm", Password="123" } };
            //var ar = conn.SendAsync(packet);

            //Thread.Sleep(1000);
            //conn.Close();

            using (SerialPort sp = new SerialPort("COM1", 9600, Parity.None, 8, StopBits.One))
            {
                
                sp.Open();
                bool connected = true;
                //Thread thread = new Thread(() =>
                //{
                //    while (connected)
                //    {
                //        try
                //        {
                //            Console.WriteLine(sp.ReadLine());
                //        }
                //        catch (Exception ex)
                //        {
                //            Console.WriteLine(ex.Message +"\r\n"+ ex.StackTrace);
                //        }
                //    }
                //});

                //thread.Start();
                int n = 0;
                sp.DataReceived += (s, e) =>
                {
                    if (e.EventType == SerialData.Chars)
                    {
                        int length = sp.BytesToRead;
                        byte[] bytes = new byte[length];
                        sp.Read(bytes, 0, length);
                        Console.WriteLine(bytes.GetStringUTF8());
                        n++;
                        if (n > 5)
                            connected = false;
                    }
                };

                for (int i = 1; i < 101; i++)
                    sp.WriteLine(i.ToString());

                while (connected)
                    n++;

                sp.Close();
            }
        }

       
    }
}
