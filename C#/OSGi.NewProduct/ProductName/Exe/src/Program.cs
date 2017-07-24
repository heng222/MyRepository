/*----------------------------------------------------------------
// 公司名称：公司名称
// 
// 产品名称：ProductsName
//
// 创 建 人：zhangheng
// 创建日期：2011-1-5 10:45:39 
// 邮    箱：heng222_z@163.com
//
// Copyright (C) 2011 ACL，保留所有权利。
//
//----------------------------------------------------------------*/

using System;
using System.Configuration;
using System.Linq;
using System.Reflection;
using System.Threading;
using System.Windows.Forms;
using Acl.CommStreamLog;
using Acl.Log;
using Acl.MessageBus;
using Products.Domain.Utility;
using Products.Infrastructure.Log;

namespace ProductName
{
    static class Program
    {
        private static SystemChecker _systemCheker = new SystemChecker();

        /// <summary>
        /// 应用程序的主入口点。
        /// </summary>
        [STAThread]
        static void Main(params string[] args)
        {
            try
            {
                Application.EnableVisualStyles();
                Application.SetCompatibleTextRenderingDefault(false);
                Application.ThreadException += OnApplicationThreadException;
                Application.ApplicationExit += OnApplicationExit;
                AppDomain.CurrentDomain.UnhandledException += OnDomainUnhandledExceptionOccurs;

                // 系统预检查
                PreCheck();

                // 注册COM控件。
                RegisterCOM();

                // 添加探测路径到本NET进程中。
                AppendCustomPrivatePath();

                // 添加VC运行时库路径到进程Path变量。
                AppendCommLibPathToPathVirable();

                // 运行
                Run();
            }
            catch (System.Exception ex)
            {
                MessageBox.Show(ex.Message, "错误", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        /// <summary>
        /// 预检查
        /// </summary>
        private static void PreCheck()
        {
            _systemCheker.Check();
        }

        /// <summary>
        /// 注册配置文件中指定的COM控件。
        /// </summary>
        private static void RegisterCOM()
        {
            string comKey = null;

            if (Environment.Is64BitProcess) comKey = "COM_X64"; else comKey = "COM_X86";

            var dictLocalSettings = ConfigurationManager.AppSettings;
            var comValue = dictLocalSettings[comKey];

            if (!string.IsNullOrWhiteSpace(comValue))
            {
                var comListToRegister = comValue.Split(';');

                comListToRegister.ToList().ForEach((p) =>
                {
                    var privatePath = AppDomain.CurrentDomain.BaseDirectory;
                    var commPath = string.Format(@"{0}{1}", privatePath, p.Trim());

                    try
                    {
                        COMHelper.RegServer(commPath);
                    }
                    catch (System.Exception /*ex*/)
                    {
                        //MessageBox.Show(string.Format("{0}注册失败，请手工注册。原因：{1}",commPath, ex.Message),
                        //    "警告", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                    }
                });
            }
        }

        /// <summary>
        /// 运行
        /// </summary>
        private static void Run()
        {
            try
            {
                InitializeLogSystem();

                Framework.OSGi.Launch.Launcher.Run();
            }
            catch (System.Reflection.TargetInvocationException ex)
            {
                LogManager.GetLogger(LoggerNames.Platform).Error(ex.InnerException);
                MessageBox.Show(ex.InnerException.Message, "错误", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
            catch (Exception ex)
            {
                LogManager.GetLogger(LoggerNames.Platform).Error(ex);
                MessageBox.Show(ex.Message, "错误", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
            finally
            {
                LocalMessageBus.Current.RemoveAll();
                ShutdownLogSystem();
                System.Diagnostics.Process.GetCurrentProcess().Kill();
            }
        }

        /// <summary>
        /// 初始化日志系统
        /// </summary>
        private static void InitializeLogSystem()
        {
            // 初始化日志管理器
            UInt16 expiredDays = 30;
            try
            {
                expiredDays = Convert.ToUInt16(ConfigurationManager.AppSettings["AppLogFileExpiredDays"]);
            }
            catch (System.Exception /*ex*/)
            { }

            LogManager.Initialize("log4net.config.xml", expiredDays);
            LogManager.GetLogger(LoggerNames.Platform).Info("程序运行日志库完成初始化...");

            // 初始化通信流日志库
            LogManager.GetLogger(LoggerNames.Platform).Info("正在初始化通信日志库...");
            CommStreamLogManager.Open();
        }

        /// <summary>
        /// 关闭日志系统
        /// </summary>
        private static void ShutdownLogSystem()
        {
            LogManager.GetLogger(LoggerNames.Platform).Info("正在关闭通信日志库...");
            CommStreamLogManager.Close();

            LogManager.GetLogger(LoggerNames.Platform).Info("正在关闭程序运行日志库...");
            LogManager.Shutdown();
        }

        /// <summary>
        /// 添加程序公共库目录到进程的Path路径中
        /// </summary>
        private static void AppendCommLibPathToPathVirable()
        {
            var exePath = AppDomain.CurrentDomain.BaseDirectory;
            var virableName = "Path";
            var virableTaget = EnvironmentVariableTarget.Process;

            // 保存初始Path值。
            var orginalPathValue = Environment.GetEnvironmentVariable(virableName, virableTaget);

            // 将要添加到Path变量中的值。
            var newAppendValue = string.Format(@";{0}x86", exePath);
            if (Environment.Is64BitProcess)
            {
                newAppendValue = string.Format(@";{0}x64", exePath);
            }

            if (!orginalPathValue.Contains(newAppendValue))
            {
                Environment.SetEnvironmentVariable(virableName,
                    orginalPathValue + newAppendValue,
                    virableTaget);
            }
        }

        /// <summary>
        /// 添加自定义目录到.NET程序探测路径中
        /// </summary>
        private static void AppendCustomPrivatePath()
        {
            // VC运行时目录（“\x86”或“\x64”）
            string privatePath = string.Format(@"x86");
            if (Environment.Is64BitOperatingSystem)
            {
                privatePath = string.Format(@"x64");
            }

            AppendPrivatePath(privatePath);
        }

        /// <summary>
        /// AppendPrivatePath
        /// </summary>
        private static void AppendPrivatePath(string appendPath)
        {
            string privatePath = AppDomain.CurrentDomain.SetupInformation.PrivateBinPath + ";" + appendPath;

            AppDomain.CurrentDomain.SetData("PRIVATE_BINPATH", privatePath);
            AppDomain.CurrentDomain.SetData("BINPATH_PROBE_ONLY", privatePath);
            var m = typeof(AppDomainSetup).GetMethod("UpdateContextProperty", BindingFlags.NonPublic | BindingFlags.Static);
            var funsion = typeof(AppDomain).GetMethod("GetFusionContext", BindingFlags.NonPublic | BindingFlags.Instance);
            m.Invoke(null, new object[] { funsion.Invoke(AppDomain.CurrentDomain, null), "PRIVATE_BINPATH", privatePath });
        }
        
        /// <summary>
        /// OnApplicationExit
        /// </summary>
        private static void OnApplicationExit(object sender, EventArgs e)
        {
        }

        /// <summary>
        /// 捕捉当前应用程序域未处理的错误
        /// </summary>
        private static void OnDomainUnhandledExceptionOccurs(object sender, UnhandledExceptionEventArgs args)
        {
            try
            {
                string info = string.Format("AppDomain（ID={0}，Name={1}）中未处理的异常。\r\n{2}",
                    AppDomain.CurrentDomain.Id,
                    AppDomain.CurrentDomain.FriendlyName,
                    (Exception)args.ExceptionObject);

                LogManager.GetLogger(LoggerNames.Platform).Error(info);

                MessageBox.Show(info, "ERROR", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
            catch
            {
            }
        }

        /// <summary>
        /// 在发生未捕获线程异常时发生
        /// </summary>
        private static void OnApplicationThreadException(object sender, ThreadExceptionEventArgs args)
        {
            try
            {
                string info = string.Format("AppDomain（ID={0}，Name={1}）程序中未捕获的线程异常。\r\n{2}",
                    AppDomain.CurrentDomain.Id,
                    AppDomain.CurrentDomain.FriendlyName,
                    args.Exception);

                LogManager.GetLogger(LoggerNames.Platform).Error(info);

                MessageBox.Show(info, "ERROR", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
            catch
            {
            }
        }
    }

}


