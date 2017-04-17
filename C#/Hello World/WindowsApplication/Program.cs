using System;
using System.Collections.Generic;
using System.Windows.Forms;
using System.Threading;

namespace WindowsApplication
{
    static class Program
    {
        /// <summary>
        /// 应用程序的主入口点。
        /// </summary>
        [STAThread]
        static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.ApplicationExit += Application_ApplicationExit;
            Application.ThreadException += Application_ThreadException;
            AppDomain.CurrentDomain.UnhandledException += CurrentDomain_UnhandledException;

            //
            Application.Run(new CommTestForm());
        }

        static void Application_ThreadException(object sender, ThreadExceptionEventArgs e)
        {
        }

        static void Application_ApplicationExit(object sender, EventArgs e)
        {
        }

        /// <summary>
        /// 捕捉当前应用程序域未处理的错误
        /// </summary>
        static void CurrentDomain_UnhandledException(object sender, UnhandledExceptionEventArgs args)
        {
        }
    }
}
