using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Threading;
using ProWrite.Core;

namespace ProWrite.UI.Clients.Test
{
    public partial class FrmWorkerThreadTest : Form
    {
        private Controller controller;
        public FrmWorkerThreadTest()
        {
            InitializeComponent();
            Thread.CurrentThread.Name = "UIThread";
            controller = new Controller();
            controller.Update += new EventHandler<EventArgs<string>>(controller_Update);
            //Test2();
            Test();
        }

        private void Test2()
        {
            controller.Run();
            Thread.Sleep(500);
            controller.Update -= controller_Update;
        }

        void controller_Update(object sender, EventArgs<string> e)
        {
            listBox1.Items.Add(e.Arg);
        }

        private void Test()
        {
            const int threadCount = 10;
            Thread[] threads = new Thread[threadCount];
            for (int i = 0; i < threadCount; i++)
            {
                int j = i + 1;
                threads[i] = NewThread(o => listBox1.Items.Add(Thread.CurrentThread.Name + " received " + o), "thread" + j.ToString());
            }

            foreach (Thread thread in threads)
                thread.Start();
        }

        //private AtomicCounter counter = new AtomicCounter();
        int counter = 1;
        private Thread NewThread(Action<string> f,string threadName)
        {
            //f = f.Create() as Action<string>;
            Thread thread = new Thread(o =>
                {
                    for (int i = 1; i <= 10; i++)
                    {
                        f(String.Format("update {0,4} from {1}", counter++, Thread.CurrentThread.Name));
                    }
                });
            

            thread.Name = threadName;
            thread.IsBackground = true;
            return thread;
        }
    }

    public class EventArgs<T> : EventArgs
    {
        public EventArgs(T arg)
        {
            Arg = arg;
        }
        public readonly T Arg;
    }

    public class Controller
    {
        private EventHandler<EventArgs<string>> _Update;

        public event EventHandler<EventArgs<string>> Update
        {
            //add { _Update += value.Create() as EventHandler<EventArgs<string>>; }
            add { _Update += value; }
            remove { _Update -= value; }
        }

        public void Run()
        {
            const int threadCount = 10;
            Thread[] threads = new Thread[threadCount];
            for (int i = 0; i < threadCount; i++)
            {
                int j = i + 1;
                threads[i] = NewThread( "thread" + j.ToString());
            }

            foreach (Thread thread in threads)
                thread.Start();
        }

        int counter = 1;
        private Thread NewThread(string threadName)
        {
            Thread thread = new Thread(o =>
            {
                for (int i = 1; i <= 10; i++)
                {
                    if (_Update != null)
                        _Update(this, new EventArgs<string>(String.Format("{0} from {1}", counter++, Thread.CurrentThread.Name)));
                }
            });


            thread.Name = threadName;
            thread.IsBackground = true;
            return thread;
        }
    }
}
