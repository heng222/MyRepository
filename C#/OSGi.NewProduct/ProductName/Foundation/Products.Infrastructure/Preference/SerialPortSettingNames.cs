/*----------------------------------------------------------------
// ��˾���ƣ���˾����
// 
// ��Ŀ���ƣ�������Ŀ����
//
// �� �� �ˣ�zhangheng
// �������ڣ�2018-6-9 14:29:22 
// ��    �䣺heng222_z@163.com
//
// Copyright (C) ��˾���ƣ���������Ȩ����
//
//----------------------------------------------------------------*/

namespace Products.Infrastructure.Preference
{
    /// <summary>
    /// �������ñ�������
    /// </summary>
    public abstract class SerialPortSettingNames
    {
        /// <summary>
        /// ����
        /// </summary>
        public const string Name = "SerialPort.Name";

        /// <summary>
        /// ������
        /// </summary>
        public const string Baudrate = "SerialPort.Baudrate";

        /// <summary>
        /// ����λ
        /// </summary>
        public const string Databits = "SerialPort.Databits";

        /// <summary>
        /// ֹͣλ
        /// </summary>
        public const string Stopbits = "SerialPort.Stopbits";

        /// <summary>
        /// ��żУ��
        /// </summary>
        public const string Parity = "SerialPort.Parity";
    }
}
