using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using ProWrite.Entity.Dashboard;
using ProWrite.UI.Controls.Common;
using ProWrite.Core;
using ProWrite.UFE.Entity;

namespace ProWrite.UI.Controls
{
    public partial class TestCommand : Form
    {
        public TestCommand()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            

            TestPlay play = new TestPlay();
            play.MessagePath = "Message";
            play.QueuePosition = 13;
            ExecuteCommand(Commands.Play, play);
            //Send reboot command to UFE
            
        }

        private void ExecuteCommand(Commands cmd, object body)
        {
            SignInfo sign = ControlService.SignCombo.Current;

            Cursor.Current = Cursors.WaitCursor;
            this.richTextBox1.Text += DateTime.Now.ToString() + ":   Begin send " + cmd.ToString()+"\n";
            sign.Controller.SendAsync(cmd, p =>
            {
                Cursor.Current = Cursors.Default;
                if (!p.IsSuccessed)
                {
                    if (p.Packet.HasError)
                        this.richTextBox1.Text += DateTime.Now.ToString() + ":   " + p.Packet.ActionError.Message + "\n";
                    if (p.Exception != null)
                        this.richTextBox1.Text += DateTime.Now.ToString() + ":   " + p.Exception.Message + "\n";
                }
                else
                {
                    this.richTextBox1.Text += DateTime.Now.ToString() + ":   " + cmd.ToString() + " Successed. \n";
                    //if(cmd == Commands.TimeZone)
                    //    this.richTextBox1.Text += DateTime.Now.ToString() + ":   Receive content '" + p.Packet.Content.GetProperty<string>("Location")+"'";
                }
            }, body);
        }
        private void button2_Click(object sender, EventArgs e)
        {
            TestSkipQueueMessage skip = new TestSkipQueueMessage();
            skip.Position = 12;
            skip.UUID = "34d";
            ExecuteCommand(Commands.SkipQueueMessage,skip);
        }

        private void button3_Click(object sender, EventArgs e)
        {
            ExecuteCommand(Commands.ClearQueueMessage);
        }

        private void button7_Click(object sender, EventArgs e)
        {
            ExecuteCommand(Commands.StartRender);
        }

        private void button8_Click(object sender, EventArgs e)
        {
            ExecuteCommand(Commands.StopRender);
        }

        private void button4_Click(object sender, EventArgs e)
        {
            ExecuteCommand(Commands.PlayCompleted);
        }

        private void button5_Click(object sender, EventArgs e)
        {
            //Cursor = Cursors.WaitCursor;
            //this.richTextBox1.Text += "Send 'TimeZone' command.\n";
            //SignInfo sign = ControlService.SignCombo.Current;
            //sign = ControlService.SignCombo.Current;
            TimeZoneSet timeZone = new TimeZoneSet();
            timeZone.Mode = 0;
            timeZone.Location = "US/Aleutian";

            ////Send set timezone command
            //sign.Controller.SendAsync(
            //    Commands.TimeZone,
            //    p =>
            //    {
            //        Cursor = Cursors.Default;
            //        if (p.IsSuccessed)
            //        {
            //            this.richTextBox1.Text += "Time Zone Successfully Changed.\n";
                        
            //        }
            //        else
            //        {
            //            this.richTextBox1.Text+="Time Zone was not changed.Please try again.";
            //        }
            //    },
            //    timeZone);

            ExecuteCommand(Commands.TimeZone,timeZone);
        }

        private void button6_Click(object sender, EventArgs e)
        {
            ExecuteCommand(Commands.GetLiveState);
        }

        private void button9_Click(object sender, EventArgs e)
        {
            TestGoLive golive = new TestGoLive();
            golive.Mode = 1;

            ExecuteCommand(Commands.GoLive,golive);
        }

        private void button10_Click(object sender, EventArgs e)
        {
            ExecuteCommand(Commands.GetQueueList);
        }

        private void button11_Click(object sender, EventArgs e)
        {
            ExecuteCommand(Commands.QueueList);
        }

        private void button12_Click(object sender, EventArgs e)
        {
            ExecuteCommand(Commands.GetConnectionType);
        }

        private void button13_Click(object sender, EventArgs e)
        {
            ExecuteCommand(Commands.GetSerialInfo);
        }

        private void button14_Click(object sender, EventArgs e)
        {
            TestDataSourceManager datasource = new TestDataSourceManager();
            datasource.Mode = 1;
            datasource.Path = 35;
            ExecuteCommand(Commands.DataSourceManager,datasource);
        }

        private void button17_Click(object sender, EventArgs e)
        {
            TestDataPassThrough passThrough = new TestDataPassThrough();
            passThrough.Flag = 12;
            passThrough.Indicator = 43;
            passThrough.Data = 45;

            SourceData data = new SourceData();
            data.FieldId =1;
            data.FieldContent ="dfef";
            passThrough.SourceData = new List<SourceData>();
            passThrough.SourceData.Add(data);

            //Commands cmd = Commands.DataPassThrough;

            //if (ControlService.SignCombo.Current == null)
            //{
            //    MsgBox.Warning(Resources.Resource.GetString(Resources.Resource.Strings.AddNewSignFirst));
            //    return;
            //}
            //SignInfo sign = ControlService.SignCombo.Current;

            //Cursor.Current = Cursors.WaitCursor;
            ////Send reboot command to UFE
            //this.richTextBox1.Text += DateTime.Now.ToString() + ":   Begin send " + cmd.ToString() + "\n";
            //sign.Controller.SendAsync(cmd, p =>
            //{
            //    Cursor.Current = Cursors.Default;
            //    if (!p.IsSuccessed)
            //    {
            //        if (p.Packet.HasError)
            //            this.richTextBox1.Text += DateTime.Now.ToString() + ":   " + p.Packet.ActionError.Message + "\n";
            //        if (p.Exception != null)
            //            this.richTextBox1.Text += DateTime.Now.ToString() + ":   " + p.Exception.Message + "\n";
            //    }
            //    else
            //        this.richTextBox1.Text += DateTime.Now.ToString() + ":   " + cmd.ToString() + " Successed. \n";
            //},passThrough);
            ExecuteCommand(Commands.DataPassThrough,passThrough);
        }

        private void button15_Click(object sender, EventArgs e)
        {
            TestGetDBSourceData getdb = new TestGetDBSourceData();
            getdb.Indicator = 22;
            ExecuteCommand(Commands.GetDBSourceData,getdb);
        }

        private void button16_Click(object sender, EventArgs e)
        {
            TestEnableDBSource enable = new TestEnableDBSource();
            enable.Flag = 1;
            enable.Indicator = 3;
            ExecuteCommand(Commands.EnableDBSource,enable);
        }


        private void ExecuteCommand(Commands cmd)
        {
            if (ControlService.SignCombo.Current == null)
            {
                MsgBox.Warning(Resources.Resource.GetString(Resources.Resource.Strings.AddNewSignFirst));
                return;
            }
            SignInfo sign = ControlService.SignCombo.Current;

            Cursor.Current = Cursors.WaitCursor;
            //Send reboot command to UFE
            this.richTextBox1.Text += DateTime.Now.ToString() + ":   Begin send " + cmd.ToString() + "\n";
            sign.Controller.SendAsync(cmd, p =>
            {
                Cursor.Current = Cursors.Default;
                if (!p.IsSuccessed)
                {
                    if (p.Packet.HasError)
                        this.richTextBox1.Text += DateTime.Now.ToString() + ":   " + p.Packet.ActionError.Message + "\n";
                    if (p.Exception != null)
                        this.richTextBox1.Text += DateTime.Now.ToString() + ":   " + p.Exception.Message + "\n";
                }
                else
                {
                    this.richTextBox1.Text += DateTime.Now.ToString() + ":   " + cmd.ToString() + " Successed. \n";
                    if (cmd == Commands.GetConnectionType)
                    {
                        this.richTextBox1.Text += DateTime.Now.ToString() + ":   Receive content:{Type:" 
                            + p.Packet.Content.GetProperty<int>("Type") 
                            + " Port:" 
                            + p.Packet.Content.GetProperty<string>("Port") 
                            + "}\n";
                    }
                    if (cmd == Commands.GetSerialInfo)
                    {
                        this.richTextBox1.Text += DateTime.Now.ToString() + ":   Receive content:{CXCSerialNumbe:"
                                                   + p.Packet.Content.GetProperty<string>("CXCSerialNumbe")
                                                   + " SalesOrderNumber:"
                                                   + p.Packet.Content.GetProperty<string>("SalesOrderNumber")
                                                   + " ModulePartNumber:"
                                                   + p.Packet.Content.GetProperty<string>("ModulePartNumber")
                                                   + " CXCPartNumber:"
                                                   + p.Packet.Content.GetProperty<string>("CXCPartNumber")
                                                   + " FirmwareVersionNumber:"
                                                   + p.Packet.Content.GetProperty<string>("FirmwareVersionNumber")
                                                   + " FPGAVersionNumber:"
                                                   + p.Packet.Content.GetProperty<string>("FPGAVersionNumber")
                                                   + " MAVersionNumber:"
                                                   + p.Packet.Content.GetProperty<string>("MAVersionNumber")
                                                   + " MABuildDate:"
                                                   + p.Packet.Content.GetProperty<string>("MABuildDate")
                                                   + "}\n";
                    }
                }
            });
        }

    }

    [Serializable]
    public class TestPlay
    {
        public int QueuePosition { get; set; }

        public string MessagePath { get; set; }
    }


    [Serializable]
    public class TestSkipQueueMessage
    {
        public int Position { get; set; }

        public string UUID { get; set; }
    }
    [Serializable]
    public class TestGoLive
    {
        public int Mode { get; set; }
    }

    [Serializable]
    public class TestDataSourceManager
    {
        public int Mode{ get; set; }

        public int Path { get; set; }
    }

    [Serializable]
    public class TestDataPassThrough
    {
        public int Indicator { get; set; }

        public int Flag { get; set; }

        public int Data { get; set; }

      public  List<SourceData> SourceData { get; set; }
    }

    [Serializable]
    public class SourceData
    {
        public string FieldContent { get; set; }
        public Int64 FieldId { get; set; }
    }

    [Serializable]
    public class TestGetDBSourceData
    {
        public int Indicator { get; set; }
    }

    [Serializable]
    public class TestEnableDBSource
    {
        public int Indicator { get; set; }

        public int Flag { get; set; }
    }
}
