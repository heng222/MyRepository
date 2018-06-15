using System;
using System.IO.Ports;
using System.Windows.Forms;
using Products.Infrastructure.Preference;

namespace Products.Presentation
{
    /// <summary>
    /// 串口参数配置控件
    /// </summary>
    public partial class SerialPortSettingsUserControl : UserControl
    {
        /// <summary>
        /// 构造函数
        /// </summary>
        public SerialPortSettingsUserControl()
        {
            InitializeComponent();

            // 初始化串口设置信息
            InitializeSerialPortName();
        }

        private void InitializeSerialPortName()
        {
            string[] serialPort = SerialPort.GetPortNames();

            cbxComName.Items.AddRange(serialPort);
            if (cbxComName.Items.Count > 0)
            {
                cbxComName.SelectedIndex = 0;
            }
            cbxBaudRate.SelectedIndex = 3;
            cbxParity.SelectedIndex = 0;
            cbxStopBits.SelectedIndex = 0;
            cbxDatabits.SelectedIndex = 0;
        }

        /// <summary>
        /// 
        /// </summary>
        /// <returns></returns>
        public SerialPortSettings GetSettings()
        {
            if (cbxComName.SelectedIndex == -1)
            {
                throw new ArgumentException("无可用的串口。");
            }

            SerialPortSettings result = new SerialPortSettings(cbxComName.Text);
            result.BaudRate = Convert.ToInt32(cbxBaudRate.Text);
            result.Parity = (Parity)(cbxParity.SelectedIndex);
            result.Stopbits = (StopBits)(cbxStopBits.SelectedIndex+1);
            result.Databits = Convert.ToInt32(cbxDatabits.Text);

            return result;
        }
    }
}
