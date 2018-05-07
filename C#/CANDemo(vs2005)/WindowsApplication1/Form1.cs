using System;
using System.Diagnostics;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;


namespace ZlgCanDemo
{
    public partial class Form1 : Form
    {
        UInt32 m_devtype = 4;//USBCAN2
        UInt32 m_bOpen = 0;
        UInt32 m_devind = 0;
        UInt32 m_canind = 0;

        ZhiyuanDeviceType[] m_arrdevtype = new ZhiyuanDeviceType[20];

        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            comboBox_DevIndex.SelectedIndex = 0;
            comboBox_CANIndex.SelectedIndex = 0;
            comboBox_Filter.SelectedIndex = 1; // 滤波方式
            comboBox_Mode.SelectedIndex = 0; // 模式
            comboBox_SendType.SelectedIndex = 2;
            comboBox_FrameType.SelectedIndex = 0;
            comboBox_FrameFormat.SelectedIndex = 0;

            // 初始化设备类型
            Int32 curindex = 0;
            curindex = comboBox_devtype.Items.Add("VCI_PCI5121");
            m_arrdevtype[curindex] = ZhiyuanDeviceType.VCI_PCI5121;
            curindex = comboBox_devtype.Items.Add("VCI_PCI9810");
            m_arrdevtype[curindex] = ZhiyuanDeviceType.VCI_PCI9810;
            curindex = comboBox_devtype.Items.Add("VCI_USBCAN1(I+)");
            m_arrdevtype[curindex] = ZhiyuanDeviceType.VCI_USBCAN1;
            curindex = comboBox_devtype.Items.Add("VCI_USBCAN2(II+)");
            m_arrdevtype[curindex] = ZhiyuanDeviceType.VCI_USBCAN2;
            curindex = comboBox_devtype.Items.Add("VCI_USBCAN2A");
            m_arrdevtype[curindex] = ZhiyuanDeviceType.VCI_USBCAN2A;
            curindex = comboBox_devtype.Items.Add("VCI_PCI9820");
            m_arrdevtype[curindex] = ZhiyuanDeviceType.VCI_PCI9820;
            curindex = comboBox_devtype.Items.Add("VCI_PCI5110");
            m_arrdevtype[curindex] = ZhiyuanDeviceType.VCI_PCI5110;
            curindex = comboBox_devtype.Items.Add("VCI_CANLITE");
            m_arrdevtype[curindex] = ZhiyuanDeviceType.VCI_CANLITE;
            curindex = comboBox_devtype.Items.Add("VCI_ISA9620");
            m_arrdevtype[curindex] = ZhiyuanDeviceType.VCI_ISA9620;
            curindex = comboBox_devtype.Items.Add("VCI_ISA5420");
            m_arrdevtype[curindex] = ZhiyuanDeviceType.VCI_ISA5420;
            curindex = comboBox_devtype.Items.Add("VCI_PC104CAN");
            m_arrdevtype[curindex] = ZhiyuanDeviceType.VCI_PC104CAN;
            curindex = comboBox_devtype.Items.Add("VCI_DNP9810");
            m_arrdevtype[curindex] = ZhiyuanDeviceType.VCI_DNP9810;
            curindex = comboBox_devtype.Items.Add("VCI_PCI9840");
            m_arrdevtype[curindex] = ZhiyuanDeviceType.VCI_PCI9840;
            curindex = comboBox_devtype.Items.Add("VCI_PC104CAN2");
            m_arrdevtype[curindex] = ZhiyuanDeviceType.VCI_PC104CAN2;
            curindex = comboBox_devtype.Items.Add("VCI_PCI9820I");
            m_arrdevtype[curindex] = ZhiyuanDeviceType.VCI_PCI9820I;
            curindex = comboBox_devtype.Items.Add("VCI_PEC9920");
            m_arrdevtype[curindex] = ZhiyuanDeviceType.VCI_PEC9920;
            curindex = comboBox_devtype.Items.Add("VCI_PCIE9221");
            m_arrdevtype[curindex] = ZhiyuanDeviceType.VCI_PCIE9221;
            comboBox_devtype.SelectedIndex = 3;
        }

        private void Form1_FormClosed(object sender, FormClosedEventArgs e)
        {
            if (m_bOpen == 1)
            {
                VciNativeMethods.VCI_CloseDevice(m_devtype, m_devind);
            }
        }

        private void buttonConnect_Click(object sender, EventArgs e)
        {
            if (m_bOpen == 1)
            {
                VciNativeMethods.VCI_CloseDevice(m_devtype, m_devind);
                m_bOpen = 0;
            }
            else
            {
                m_devtype = (uint)m_arrdevtype[comboBox_devtype.SelectedIndex];

                m_devind = (UInt32)comboBox_DevIndex.SelectedIndex;
                m_canind = (UInt32)comboBox_CANIndex.SelectedIndex;
                var rc = VciNativeMethods.VCI_OpenDevice(m_devtype, m_devind, 0);
                if (rc == 0)
                {
                    MessageBox.Show("打开设备失败,请检查设备类型和设备索引号是否正确", "错误",
                            MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                    return;
                }
                //rc = VciNativeMethods.VCI_OpenDevice(m_devtype, m_devind, 0);
                //var error = new VCI_ERR_INFO();
                //VciNativeMethods.VCI_ReadErrInfo(m_devtype, m_devind, 0, ref error);

                m_bOpen = 1;
                var config = new VCI_INIT_CONFIG();
                config.AccCode = Convert.ToUInt32("0x" + textBox_AccCode.Text, 16);
                config.AccMask = Convert.ToUInt32("0x" + textBox_AccMask.Text, 16);
                config.Timing0 = Convert.ToByte("0x" + textBox_Time0.Text, 16);
                config.Timing1 = Convert.ToByte("0x" + textBox_Time1.Text, 16);
                config.Filter = (FilterType)comboBox_Filter.SelectedIndex;
                config.Mode = (WorkMode)comboBox_Mode.SelectedIndex;
                VciNativeMethods.VCI_InitCAN(m_devtype, m_devind, m_canind, ref config);

                // 读取板卡信息
                var boardInf = new VCI_BOARD_INFO();
                VciNativeMethods.VCI_ReadBoardInfo(m_devtype, m_devind, ref boardInf);
                //var serialNo = Encoding.ASCII.GetString(boardInf.str_Serial_Num, 0, boardInf.str_Serial_Num.Length);
                //Console.WriteLine(serialNo);
            }

            buttonConnect.Text = m_bOpen == 1 ? "断开" : "连接";
            timer_rec.Enabled = m_bOpen == 1;
            //button_StartCAN.Enabled = m_bOpen == 1;
            //button_StopCAN.Enabled = m_bOpen == 1;
        }


        private void button_StartCAN_Click(object sender, EventArgs e)
        {
            try
            {
                if (m_bOpen == 0) return;
                VciNativeMethods.VCI_StartCAN(m_devtype, m_devind, m_canind);
                //button_StartCAN.Enabled = false;
            }
            catch (System.Exception ex)
            {
                //button_StartCAN.Enabled = true;
                MessageBox.Show(ex.Message);
            }
        }

        private void button_StopCAN_Click(object sender, EventArgs e)
        {
            if (m_bOpen == 0) return; 
            VciNativeMethods.VCI_ResetCAN(m_devtype, m_devind, m_canind);
            //button_StartCAN.Enabled = true;
        }

        private void button_Send_Click(object sender, EventArgs e)
        {
            if (m_bOpen == 0) return;

            var id = System.Convert.ToUInt32("0x" + textBox_ID.Text, 16);
            var sendType = (SendMode)comboBox_SendType.SelectedIndex;
            var remoteFlag = comboBox_FrameFormat.SelectedIndex; // 是否为远程帧？
            var externFlag = comboBox_FrameType.SelectedIndex; // 是否为扩展帧？
            int sendTimers = int.Parse(textBox1.Text);
            var data = HelperTools.SplitHexText(textBox_Data.Text);

            var sendobj = new VCI_CAN_OBJ();
            sendobj.SendType = sendType;
            sendobj.RemoteFlag = (byte)remoteFlag;
            sendobj.ExternFlag = (byte)externFlag;
            sendobj.ID = id;
            sendobj.DataLen = System.Convert.ToByte(data.Length % 9);
            sendobj.Data = data;

            Task.Factory.StartNew(() =>
            {
                var sw = new Stopwatch();
                sw.Start();

                for (int j = 0; j < sendTimers; j++)
                {
                    var res = VciNativeMethods.VCI_Transmit(m_devtype, m_devind, m_canind, ref sendobj, 1);
                    if (res == 0)
                    {
                        MessageBox.Show("发送失败", "错误", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                        return;
                    }
                }

                sw.Stop();

                Console.WriteLine("发送耗时 = {0} 秒", sw.Elapsed.TotalSeconds);
            });
        }

        /// <summary>
        /// 接收线程。
        /// </summary>
        private void timer_rec_Tick(object sender, EventArgs e)
        {
            var res = VciNativeMethods.VCI_GetReceiveNum(m_devtype, m_devind, m_canind);
            if (res == 0) return;

            var sw = new Stopwatch();
            sw.Start();

            /////////////////////////////////////
            for (int i = 0; i < res; i++)
            {
                var frame = new VCI_CAN_OBJ();
                var len = VciNativeMethods.VCI_Receive(m_devtype, m_devind, m_canind, ref frame, 1, 100);
                if (len <= 0)
                {
                    //注意：如果没有读到数据则必须调用此函数来读取出当前的错误码，  
                    //千万不能省略这一步（即使你可能不想知道错误码是什么）  
                    //VCI_ReadErrInfo(m_devtype, this.m_devind, this.m_canind, ref errInfo);
                }

                ////////////////////////////////////////////////////////
                var sb = new StringBuilder(128);
                sb.AppendFormat("接收到数据:  帧ID:0x{0:X2}  帧格式:", frame.ID);
                sb.AppendFormat("", (frame.RemoteFlag == 0) ? "数据帧 " : "远程帧 ", (frame.ExternFlag == 0) ? "标准帧 " : "扩展帧 ");

                if (frame.RemoteFlag == 0)
                {
                    sb.AppendFormat("数据: {0}", string.Join(" ", frame.Data.Select(p => string.Format("{0:X2}", p))));

                    listBox_Info.Items.Add(sb.ToString());
                    listBox_Info.SelectedIndex = listBox_Info.Items.Count - 1;
                }
            }

            sw.Stop();
            Console.WriteLine("接收耗时 = {0} 秒", sw.Elapsed.TotalSeconds);

        }

        private void comboBox_CANIndex_SelectedIndexChanged(object sender, EventArgs e)
        {
            try
            {
                m_canind = (UInt32)comboBox_CANIndex.SelectedIndex;
            }
            catch (System.Exception /*ex*/)
            {            	
            }
        }
    }
}