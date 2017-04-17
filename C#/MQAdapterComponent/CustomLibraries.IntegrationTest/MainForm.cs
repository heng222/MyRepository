using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;


using IBM.WMQ;
using CustomLibraries.MQAdapter;

namespace CustomLibraries.IntegrationTest
{
    public partial class MainForm : Form
    {

        public MainForm()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            try
            {
                string qmName = "QM_TCC_3.60";
                string queueName = "r_1x_tcc_mqr";
                string messageToSend = DateTime.Now.ToString();

                MQQueueManager qMgr = new MQQueueManager(qmName);
                MQQueue queue = qMgr.AccessQueue(queueName, MQC.MQOO_OUTPUT);

                MQMessage message = new MQMessage();
                message.WriteString(messageToSend);
                message.Format = MQC.MQFMT_STRING;
                queue.Put(message);

                queue.Close();
                
            }
            catch (System.Exception ex)
            {
                MessageBox.Show(ex.ToString(), "ERROR", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }
    }
}