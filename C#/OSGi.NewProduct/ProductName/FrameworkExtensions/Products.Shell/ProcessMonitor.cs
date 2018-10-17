using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Diagnostics;
using Acl;

namespace Products.Shell
{
    class ProcessMonitor : BooleanDisposable
    {
        private System.Timers.Timer timer;
        //private Process process;
        private Action<string> _log;
        private Action _processKillingHandler;

        public ProcessMonitor(Action<string> log, Action processKillingHandler)
        {
            this._log = log;
            this._processKillingHandler = processKillingHandler;

            //process = Process.GetCurrentProcess();
        }

        public void Start()
        {
            timer = new System.Timers.Timer();
            timer.Interval = 10 * 1000;
            timer.Elapsed += new System.Timers.ElapsedEventHandler(timer_Elapsed);
            timer.Start();
        }

        void timer_Elapsed(object sender, System.Timers.ElapsedEventArgs e)
        {
            CloseTimer();

            if (_log != null)
            {
                _log("ATS 系统超过10秒没有正常结束，系统将强制结束!");
            }

            if (_processKillingHandler != null)
            {
                _processKillingHandler();
            }

            System.Diagnostics.Process.GetCurrentProcess().Kill();
        }

        private void CloseTimer()
        {
            if (timer != null)
            {
                timer.Elapsed -= timer_Elapsed;
                timer.Dispose();
                timer = null;
            }
        }

        protected override void Dispose(bool disposing)
        {
            if (disposing)
            {
                CloseTimer();
            }
            base.Dispose(disposing);
        }
    }
}
