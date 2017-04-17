/*----------------------------------------------------------------
// 公司名称：北京交大微联科技有限公司
// 
// 项目名称：北京地铁15号线ATS项目
//
// 创 建 人：zhangheng
// 创建日期：08/05/2011 08:22:58 
// 邮    箱：zhangheng@bjmut.com
//
// Copyright (C) 北京交大微联科技有限公司 2009-2015 保留所有权利
//
//----------------------------------------------------------------*/

using System;
using System.Collections.Generic;
using System.Text;
using System.Linq;
using System.Net.NetworkInformation;
using System.Net;
using NUnit.Framework;
using System.Management;
using System.Threading;

namespace CSharpLearning.Network
{
    [TestFixture]
    public class NetworkUsageTest
    {
        [Test(Description = "获取所有网络接口详情。")]
        public void GetIP_Test1()
        {
            //本地计算机上的网络接口的对象,我的电脑里面以太网网络连接有两个虚拟机的接口和一个本地接口
            var nics = NetworkInterface.GetAllNetworkInterfaces();
            foreach (NetworkInterface adapter in nics)
            {
                bool Pd1 = (adapter.NetworkInterfaceType == NetworkInterfaceType.Ethernet); //判断是否是以太网连接
                if (Pd1)
                {
                    Console.WriteLine("网络适配器名称：" + adapter.Name);
                    Console.WriteLine("网络适配器标识符：" + adapter.Id);
                    Console.WriteLine("适配器连接状态：" + adapter.OperationalStatus.ToString());
                    
                    //IP配置信息
                    IPInterfaceProperties ip = adapter.GetIPProperties();
                    ip.UnicastAddresses.ToList().ForEach(p =>
                    {
                        Console.WriteLine(string.Format("IP: {0} / {1}", p.Address, p.IPv4Mask));
                    });

                    //默认网关
                    ip.GatewayAddresses.ToList().ForEach(p =>
                    {
                        Console.WriteLine(string.Format("网关: {0}", p.Address));  
                    });

                    // DNS服务器地址
                    int DnsCount = ip.DnsAddresses.Count;
                    if (DnsCount > 0)
                    {
                        Console.WriteLine("DNS服务器地址：");   

                        //其中第一个为首选DNS，第二个为备用的，余下的为所有DNS为DNS备用，按使用顺序排列
                        for (int i = 0; i < DnsCount; i++)
                        {
                            Console.WriteLine("              " + ip.DnsAddresses[i].ToString());
                        }
                    }

                    Console.WriteLine("网络接口速度：" + (adapter.Speed / 1000000).ToString("0.0") + "Mbps");
                    Console.WriteLine("接口描述：" + adapter.Description);
                    Console.WriteLine("适配器的媒体访问控制 (MAC) 地址:" + adapter.GetPhysicalAddress().ToString());
                    Console.WriteLine("该接口是否只接收数据包：" + adapter.IsReceiveOnly.ToString());
                    Console.WriteLine("该接口收到的字节数：" + adapter.GetIPv4Statistics().BytesReceived.ToString());
                    Console.WriteLine("该接口发送的字节数：" + adapter.GetIPv4Statistics().BytesSent.ToString());
                    Console.WriteLine("该接口丢弃的传入数据包数：" + adapter.GetIPv4Statistics().IncomingPacketsDiscarded.ToString());
                    Console.WriteLine("该接口丢弃的传出数据包数：" + adapter.GetIPv4Statistics().OutgoingPacketsDiscarded.ToString());
                    Console.WriteLine("该接口有错误的传入数据包数：" + adapter.GetIPv4Statistics().IncomingPacketsWithErrors.ToString());
                    Console.WriteLine("该接口有错误的传出数据包数：" + adapter.GetIPv4Statistics().OutgoingPacketsWithErrors.ToString());
                    Console.WriteLine("该接口协议未知的数据包数：" + adapter.GetIPv4Statistics().IncomingUnknownProtocolPackets.ToString());
                    Console.WriteLine("---------------------------------------------------------------------\n");
                }
            }
            Console.ReadLine();
        }


        [Test(Description = "另一种方式获取IP。")]
        public void GetIP_Test2()
        {
            string stringIP = "";

            var managementClass = new ManagementClass("Win32_NetworkAdapterConfiguration");
            var objCollection = managementClass.GetInstances();

            foreach (var managementObject in objCollection)
            {
                if ((bool)managementObject["IPEnabled"])
                {
                    var ipAddr = (string[])managementObject["IPAddress"];

                    ipAddr.ToList().ForEach(p =>
                    {
                        stringIP += p + " / ";
                    });
                }
            }

            Console.WriteLine(stringIP);
        }  
        

        [Test(Description = "Ping指定IP的机器。")]
        public void PingComputers()
        {
            try
            {
                for (int i = 1; i <= 255; i++)
                {
                    var myPing = new Ping();

                    myPing.PingCompleted += (sender, e) =>
                    {
                        if (e.Reply.Status == IPStatus.Success)
                        {
                            IPHostEntry remoteEntry = Dns.GetHostEntry(e.Reply.Address);
                            //string ips = "";
                            //foreach (IPAddress ip in remoteEntry.AddressList)
                            //{
                            //    ips += ip + ";";
                            //}

                            Console.WriteLine(e.Reply.Address + " | " + remoteEntry.HostName);
                        }
                    };

                    string pingIP = "192.168.3." + i.ToString();
                    myPing.SendAsync(pingIP, 2000, null);
                }
            }
            catch(Exception /*ex*/)
            {
            }

            Thread.Sleep(3000);
        }


    }
}
