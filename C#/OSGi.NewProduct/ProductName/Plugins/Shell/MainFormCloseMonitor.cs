using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Windows.Forms;

using Acl;

namespace Products.Shell
{
    class MainFormCloseMonitor : BooleanDisposable
    {
        private System.Timers.Timer timer;
        private Action<string> _log;
        private Action _processKillingHandler;

        public MainFormCloseMonitor(Form form, Action<string> log, Action processKillingHandler)
        {
            if (form == null) throw new ArgumentNullException("form");
            this._log = log;
            this._processKillingHandler = processKillingHandler;

            form.Shown += new EventHandler(OnMainFormShow);
        }

        void OnMainFormShow(object sender, EventArgs e)
        {
            (sender as Form).Shown -= OnMainFormShow;
            StartTimer();
        }

        private void StartTimer()
        {
            timer = new System.Timers.Timer();
            timer.Interval = 10 * 1000;
            timer.Elapsed += OnTimerElapsed;
            timer.Start();
        }

        private void OnTimerElapsed(object sender, System.Timers.ElapsedEventArgs e)
        {
            //判断当前进程主窗口句柄不存在则强制介绍进程
            if (Process.GetCurrentProcess().MainWindowHandle == IntPtr.Zero)
            {
                CloseTimer();

                if (_log != null)
                {
                    _log("系统超过10秒没有正常结束，系统将强制结束!");
                }

                if (_processKillingHandler != null)
                {
                    _processKillingHandler();
                }

                System.Diagnostics.Process.GetCurrentProcess().Kill();
            }
        }

        private void CloseTimer()
        {
            if (timer != null)
            {
                timer.Elapsed -= OnTimerElapsed;
                timer.Dispose();
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
