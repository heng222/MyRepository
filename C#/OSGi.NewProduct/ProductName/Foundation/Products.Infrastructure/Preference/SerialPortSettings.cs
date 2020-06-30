using System;
using System.Collections.Generic;
using System.IO.Ports;
using System.Linq;
using System.Text;

namespace Products.Infrastructure.Preference
{
    /// <summary>
    /// 串口配置参数类
    /// </summary>
    public sealed class SerialPortSettings
    {
        /// <summary>
        /// 串口名称
        /// </summary>
        public string Name { get; set; }

        /// <summary>
        /// 波特率
        /// </summary>
        public int BaudRate { get; set; }

        /// <summary>
        /// 数据位
        /// </summary>
        public int Databits { get; set; }

        /// <summary>
        /// 停止位
        /// </summary>
        public StopBits Stopbits { get; set; }

        /// <summary>
        /// 奇偶校验
        /// </summary>
        public Parity Parity { get; set; }

        /// <summary>
        /// 构造一个串口配置参数类
        /// </summary>
        /// <param name="portName">串口名称</param>
        /// <param name="baudRate">波特率</param>
        /// <param name="dataBits">数据位</param>
        /// <param name="stopBits">停止位</param>
        /// <param name="parity">奇偶校验</param>
        public SerialPortSettings(string portName, int baudRate = 9600,
            Parity parity = Parity.None, int dataBits = 8, StopBits stopBits = StopBits.None)
        {
            this.Name = portName;
            this.BaudRate = baudRate;
            this.Databits = dataBits;
            this.Stopbits = stopBits;
            this.Parity = parity;
        }
    }
}
