/*----------------------------------------------------------------
// ��˾���ƣ���������΢���Ƽ����޹�˾
// 
// ��Ŀ���ƣ���������15����ATS��Ŀ
//
// �� �� �ˣ�zhangheng
// �������ڣ�08/05/2011 08:22:58 
// ��    �䣺zhangheng@bjmut.com
//
// Copyright (C) ��������΢���Ƽ����޹�˾ 2009-2015 ��������Ȩ��
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
        [Test(Description = "��ȡ��������ӿ����顣")]
        public void GetIP_Test1()
        {
            //���ؼ�����ϵ�����ӿڵĶ���,�ҵĵ���������̫����������������������Ľӿں�һ�����ؽӿ�
            var nics = NetworkInterface.GetAllNetworkInterfaces();
            foreach (NetworkInterface adapter in nics)
            {
                bool Pd1 = (adapter.NetworkInterfaceType == NetworkInterfaceType.Ethernet); //�ж��Ƿ�����̫������
                if (Pd1)
                {
                    Console.WriteLine("�������������ƣ�" + adapter.Name);
                    Console.WriteLine("������������ʶ����" + adapter.Id);
                    Console.WriteLine("����������״̬��" + adapter.OperationalStatus.ToString());
                    
                    //IP������Ϣ
                    IPInterfaceProperties ip = adapter.GetIPProperties();
                    ip.UnicastAddresses.ToList().ForEach(p =>
                    {
                        Console.WriteLine(string.Format("IP: {0} / {1}", p.Address, p.IPv4Mask));
                    });

                    //Ĭ������
                    ip.GatewayAddresses.ToList().ForEach(p =>
                    {
                        Console.WriteLine(string.Format("����: {0}", p.Address));  
                    });

                    // DNS��������ַ
                    int DnsCount = ip.DnsAddresses.Count;
                    if (DnsCount > 0)
                    {
                        Console.WriteLine("DNS��������ַ��");   

                        //���е�һ��Ϊ��ѡDNS���ڶ���Ϊ���õģ����µ�Ϊ����DNSΪDNS���ã���ʹ��˳������
                        for (int i = 0; i < DnsCount; i++)
                        {
                            Console.WriteLine("              " + ip.DnsAddresses[i].ToString());
                        }
                    }

                    Console.WriteLine("����ӿ��ٶȣ�" + (adapter.Speed / 1000000).ToString("0.0") + "Mbps");
                    Console.WriteLine("�ӿ�������" + adapter.Description);
                    Console.WriteLine("��������ý����ʿ��� (MAC) ��ַ:" + adapter.GetPhysicalAddress().ToString());
                    Console.WriteLine("�ýӿ��Ƿ�ֻ�������ݰ���" + adapter.IsReceiveOnly.ToString());
                    Console.WriteLine("�ýӿ��յ����ֽ�����" + adapter.GetIPv4Statistics().BytesReceived.ToString());
                    Console.WriteLine("�ýӿڷ��͵��ֽ�����" + adapter.GetIPv4Statistics().BytesSent.ToString());
                    Console.WriteLine("�ýӿڶ����Ĵ������ݰ�����" + adapter.GetIPv4Statistics().IncomingPacketsDiscarded.ToString());
                    Console.WriteLine("�ýӿڶ����Ĵ������ݰ�����" + adapter.GetIPv4Statistics().OutgoingPacketsDiscarded.ToString());
                    Console.WriteLine("�ýӿ��д���Ĵ������ݰ�����" + adapter.GetIPv4Statistics().IncomingPacketsWithErrors.ToString());
                    Console.WriteLine("�ýӿ��д���Ĵ������ݰ�����" + adapter.GetIPv4Statistics().OutgoingPacketsWithErrors.ToString());
                    Console.WriteLine("�ýӿ�Э��δ֪�����ݰ�����" + adapter.GetIPv4Statistics().IncomingUnknownProtocolPackets.ToString());
                    Console.WriteLine("---------------------------------------------------------------------\n");
                }
            }
            Console.ReadLine();
        }


        [Test(Description = "��һ�ַ�ʽ��ȡIP��")]
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
        

        [Test(Description = "Pingָ��IP�Ļ�����")]
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
