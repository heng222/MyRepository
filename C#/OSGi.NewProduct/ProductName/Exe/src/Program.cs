/*----------------------------------------------------------------
// 公司名称：请输入公司名称
// 
// 项目名称：输入项目名称
//
// 创 建 人：zhangheng
// 创建日期：2015-2-3 21:20:58 
// 邮    箱：zhangheng@163.com
//
// Copyright (C) 公司名称 2019，保留所有权利
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
using Acl.Threading;

using Microsoft.Win32;

using OSGi;

using Products.Domain.Utility;
using Products.Infrastructure.Events;
using Products.Infrastructure.Log;
using Products.Infrastructure.Messages;

namespace Exe
{
    class Program
    {
        private IFramework _framework;

        public Program()
        {
            _framework = FrameworkFactory.NewFramework();
        }


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

                var instance = new Program();

                // 运行
                instance.Run();
            }
            catch (System.Exception ex)
            {
                MessageBox.Show(ex.Message, "错误", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        /// <summary>
        /// 预检查
        /// </summary>
        private void PreCheck()
        {
            new SystemChecker().Check();
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
        private void Run()
        {
            try
            {
                SubscribeSystemEvents();

                // 系统预检查
                PreCheck();

                // 注册COM控件。
                RegisterCOM();

                InitializeLogSystem();

                GlobalMessageBus.SubscribeApplicationExiting(OnProcessKillingForcedly);

                _framework.Init();
                _framework.Start();
                _framework.WaitForStop();
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
                ThreadProxy.Shutdown();
                System.Diagnostics.Process.GetCurrentProcess().Kill();
            }
        }

        /// <summary>
        /// 订阅OS事件。
        /// </summary>
        private static void SubscribeSystemEvents()
        {
            SystemEvents.PowerModeChanged += (sender, e) =>
            {
                LogManager.GetLogger(LoggerNames.Platform)
                    .Warn(string.Format("收到用户挂起或继续系统事件，电源事件模式类型={0}", e.Mode));
            };

            SystemEvents.SessionSwitch += (sender, e) =>
            {
                LogManager.GetLogger(LoggerNames.Platform)
                    .Warn(string.Format("更改当前登录的Windows用户，事件类型={0}", e.Reason));
            };

            SystemEvents.SessionEnded += (sender, e) =>
            {
                LogManager.GetLogger(LoggerNames.Platform)
                    .Warn(string.Format("用户注销或关闭操作系统，事件类型={0}", e.Reason));
            };
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
        /// 当进程异常终止时的处理入口函数。
        /// </summary>
        private static void OnProcessKillingForcedly(object sender, ProcessExitingEventArgs e)
        {
            try
            {
                LocalMessageBus.Current.RemoveAll();
                ShutdownLogSystem();
            }
            catch (System.Exception /*ex*/)
            {
            }
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


