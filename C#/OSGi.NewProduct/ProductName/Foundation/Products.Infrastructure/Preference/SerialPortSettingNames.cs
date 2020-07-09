/*----------------------------------------------------------------
// 公司名称：公司名称
// 
// 项目名称：输入项目名称
//
// 创 建 人：zhangheng
// 创建日期：2018-6-9 14:29:22 
// 邮    箱：heng222_z@163.com
//
// Copyright (C) 公司名称，保留所有权利。
//
//----------------------------------------------------------------*/

namespace Products.Infrastructure.Preference
{
    /// <summary>
    /// 串口配置变量名称
    /// </summary>
    public abstract class SerialPortSettingNames
    {
        /// <summary>
        /// 名称
        /// </summary>
        public const string Name = "SerialPort.Name";

        /// <summary>
        /// 波特率
        /// </summary>
        public const string Baudrate = "SerialPort.Baudrate";

        /// <summary>
        /// 数据位
        /// </summary>
        public const string Databits = "SerialPort.Databits";

        /// <summary>
        /// 停止位
        /// </summary>
        public const string Stopbits = "SerialPort.Stopbits";

        /// <summary>
        /// 奇偶校验
        /// </summary>
        public const string Parity = "SerialPort.Parity";
    }
}
