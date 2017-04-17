using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading;
using System.Windows.Forms;
using System.Collections;

using ProWrite.Entity;
using ProWrite.Entity.Dashboard;
using ProWrite.Entity.Library;
using ProWrite.DataProviders;
using ProWrite.UFE;
using ProWrite.UFE.Files;
using ProWrite.UI.Controls;
using ProWrite.UFE.Entity;

namespace ProWrite.UI.Clients.Test.FontSample
{
    public partial class Form1 : Form
    {
        private IUFEFileSaver<SchedulerInfo> _scheduleSaver;
        private List<UfeFile> _files;
        private SignInfo _sign;
        //struct CShapeUserDefinedStruct
        //{
        //    public int a;
        //}

        public Form1()
        {
            InitializeComponent();

            _sign = ControlService.SignCombo.Current;
            _scheduleSaver = new ScheduleSaver { Sign = _sign };
            LocalFilePathMapping.CreateDirectories(true);
            //CShapeUserDefinedStruct cc = new CShapeUserDefinedStruct();
            //cc.a = 1;

            //List<string> b = new List<string>();
            ////b.Sort(
            //SortedList<string, string> a = new SortedList<string, string>();
            ////a.Add(
            ////IntPtr
            //Dictionary<string, string> c = new Dictionary<string, string>();
            //c.OrderBy(
        }

        private void simpleButton1_Click(object sender, EventArgs e)
        {
            UfeFileMessageConverter converter = new UfeFileMessageConverter();

            IDataProvider<ProjectInfo> Provider;
            Provider = new DataProvider();
            LibraryGroup.Current = Provider.Get().LibraryGroups[0];

            MessageInfo message = LibraryGroup.Current.Messages.GetByName("text");
            SignInfo sign = new SignInfo();
            sign.Width = 100;
            sign.Height = 64;
            converter.Sign = sign;
            converter.Convert(message);
            converter.Generate();
            //IDataProvider<ProjectInfo> Provider;
            //Provider = new DataProvider();
            //LibraryGroup.Current = Provider.Get().LibraryGroups[0];

            //MessageInfo message = LibraryGroup.Current.Messages.GetByName("a");
            //MessageSaver manager = new MessageSaver();
            //Size newSign = new Size(100, 200);
            ////manager.NewSize = newSign;
            //SignInfo sign = new SignInfo();
            //sign.Width = 200;
            //sign.Height = 100;
            //manager.Sign = sign;
            //manager.Item = message;
            //manager.Save();
        }

        private void simpleButton2_Click(object sender, EventArgs e)
        {
            UfeFileMessageConverter converter = new UfeFileMessageConverter();

            IDataProvider<ProjectInfo> Provider;
            Provider = new DataProvider();
            LibraryGroup.Current = Provider.Get().LibraryGroups[0];

            MessageInfo message = LibraryGroup.Current.Messages.GetByName("Image");
            SignInfo sign = new SignInfo();
            sign.Width = 100;
            sign.Height = 64;
            converter.Sign = sign;
            converter.Convert(message);
            converter.Generate();
        }

        private void simpleButton3_Click(object sender, EventArgs e)
        {
            UfeFileMessageConverter converter = new UfeFileMessageConverter();

            IDataProvider<ProjectInfo> Provider;
            Provider = new DataProvider();
            LibraryGroup.Current = Provider.Get().LibraryGroups[0];

            MessageInfo message = LibraryGroup.Current.Messages.GetByName("Paint");
            SignInfo sign = new SignInfo();
            sign.Width = 100;
            sign.Height = 64;
            converter.Sign = sign;
            converter.Convert(message);
            converter.Generate();
        }

        private void backgroundWorker1_DoWork(object sender, DoWorkEventArgs e)
        {
            // Do not access the form's BackgroundWorker reference directly.
            // Instead, use the reference provided by the sender parameter.
            BackgroundWorker bw = sender as BackgroundWorker;

            // Extract the argument.
            int arg = (int)e.Argument;

            // Start the time-consuming operation.
            e.Result = TimeConsumingOperation(bw, arg);

            // If the operation was canceled by the user, 
            // set the DoWorkEventArgs.Cancel property to true.
            if (bw.CancellationPending)
            {
                e.Cancel = true;
            }
        }

        // This event handler demonstrates how to interpret 
        // the outcome of the asynchronous operation implemented
        // in the DoWork event handler.
        private void backgroundWorker1_RunWorkerCompleted(
            object sender,
            RunWorkerCompletedEventArgs e)
        {
            if (e.Cancelled)
            {
                // The user canceled the operation.
                MessageBox.Show("Operation was canceled");
            }
            else if (e.Error != null)
            {
                // There was an error during the operation.
                string msg = String.Format("An error occurred: {0}", e.Error.Message);
                MessageBox.Show(msg);
            }
            else
            {
                // The operation completed normally.
                string msg = String.Format("Result = {0}", e.Result);
                MessageBox.Show(msg);
            }
        }

        // This method models an operation that may take a long time 
        // to run. It can be cancelled, it can raise an exception,
        // or it can exit normally and return a result. These outcomes
        // are chosen randomly.
        private int TimeConsumingOperation(
            BackgroundWorker bw,
            int sleepPeriod)
        {
            int result = 0;

            Random rand = new Random();

            while (!bw.CancellationPending)
            {
                bool exit = false;

                switch (rand.Next(3))
                {
                    // Raise an exception.
                    case 0:
                        {
                            throw new Exception("An error condition occurred.");
                            break;
                        }

                    // Sleep for the number of milliseconds
                    // specified by the sleepPeriod parameter.
                    case 1:
                        {
                            Thread.Sleep(sleepPeriod);
                            break;
                        }

                    // Exit and return normally.
                    case 2:
                        {
                            result = 23;
                            exit = true;
                            break;
                        }

                    default:
                        {
                            break;
                        }
                }

                if (exit)
                {
                    break;
                }
            }

            return result;
        }

        private void simpleButton4_Click(object sender, EventArgs e)
        {
            //ProWrite.UI.Controls.ProgressFrom form = new ProgressFrom();
            //form.Show();
            //this.backgroundWorker1.RunWorkerAsync(2000);

        }

        private void simpleButton5_Click(object sender, EventArgs e)
        {
            this.backgroundWorker1.CancelAsync();

        }
    }
}
