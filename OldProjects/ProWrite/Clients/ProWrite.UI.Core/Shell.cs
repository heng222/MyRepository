using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;
using log4net.Config;
using ProWrite.UI.Controls.Common;
using ProWrite.Core;
using System.IO;
using ProWrite.UI.Controls.Common.Messages;
using System.Diagnostics;
using System.Runtime.InteropServices;
using System.Reflection;
using System.Drawing;
using ProWrite.Entity.Dashboard;
using ProWrite.Entity;
using System.Configuration;
using System.Communication;
using System.Data;
using System.Data.Common;
using System.Runtime.Serialization;

namespace ProWrite.UI.Controls
{
    public class Shell
    {
        private Form mainForm = null;
        private static bool? HasAuthenticated;


        public static void Run(params string[] args)
        {            
            int length = Enum.GetValues(typeof(MenuCommands)).Length;

            //int[] a = new int[length];
            //((int[])Enum.GetValues(typeof(MenuCommands))).CopyTo(a, 0);
            //string[] b = new string[length];
            //((string[])Enum.GetNames(typeof(MenuCommands))).CopyTo(b, 0);

            //string c = "";
            //for (int i = 0; i < length; i++)
            //{
            //    c += b[i].ToString() + ":" + a[i].ToString() + "\n";
            //}
            //MessageBox.Show(c);

            Shell pg = new Shell();
            ServiceManager.Add<Shell>(pg);
            //args = new string[] { "c:\\New Message5.pme" };     
            Test();
            pg.DoRun(args);
        }
        private static void Test()
        {
            
        }
        public void DoRun(params string[] args)
        {
            ArgInfo argInfo = null;
            //MessageBox.Show("Hello!");
            if (args != null && args.Length == 1)
            {
                argInfo = ArgInfo.Parse(args[0]);
            }

            var currentPro = Process.GetCurrentProcess();

            bool created;
            using (Mutex mtx = new Mutex(true, API.mainWindowName, out created))
            {
                if (!created)
                {
                    if (argInfo != null)
                        HandlerPreviewProcessInfo(args, currentPro);
                    return;
                }

                var loginTask = Task.Create(p => ShowSplash());

                CodeTimer.Time("Start Main Form", () =>
                {
                    Application.EnableVisualStyles();
                    Application.SetCompatibleTextRenderingDefault(false);

                    XmlConfigurator.Configure();
                    Log.InnerLog = new ProWrite.Core.Logger("-Sys-");

                    string moduleName = null;
                    object[] argArrary = null;

                    mainForm = StartHelper.CreateMainForm();
                    (mainForm as IMainForm).Initialize();

                    var profile = ServiceManager.Get<ProjectProfile>();
                    Task registerModuleTask = null;
                    registerModuleTask = Task.Create(p =>
                    {

                        if (moduleName == null)
                            moduleName = profile.DefaultModule;

                        var moduleInfo = profile.Modules.First(m => m.ModuleName == moduleName);
                        ModuleManager.Register(moduleInfo.Module);

                        var modules = profile.Modules.Where(m => m.ModuleName != moduleName);
                        foreach (var m in modules)
                            ModuleManager.Register(m.Module);
                    });



                    var timer = ServiceManager.Get<System.Windows.Forms.Timer>();
                    mainForm.Shown += (s, e) =>
                        {
                            ModuleManager.DisplayModule(ModuleNames.Editor);//moduleName);
                            ModuleManager.DisplayModule(moduleName);
                            timer.Tick += delegate
                            {
                                timer.Stop();

                                if (argInfo != null)
                                {
                                    moduleName = argInfo.ModuleName;
                                    argArrary = new object[] { argInfo.Importer.OnImportOpen(args[0]), true };
                                    ModuleManager.DisplayModule(moduleName, argArrary);
                                }

                                if (!registerModuleTask.IsCompleted)
                                {
                                    registerModuleTask.Wait();
                                    registerModuleTask.Dispose();
                                }
                                if (!loginTask.IsCompleted)
                                {
                                    loginTask.Wait();
                                    loginTask.Dispose();
                                }

                                //TODO:
                                DirtyWordList.Load();
                            };
                            timer.Start();
                        };

                    ServiceManager.Add<bool>(false);
                    filter = new UserPreferenceChangingFilter();
                    Application.AddMessageFilter(filter);
                    Application.ThreadException += new ThreadExceptionEventHandler(Application_ThreadException);
                    Application.ApplicationExit += new EventHandler(Application_ApplicationExit);
                });

                while (!HasAuthenticated.HasValue)
                    loginTask.Wait(50);
                var ewh = ServiceManager.Get<System.Threading.EventWaitHandle>();
                ewh.Set();

                if (!HasAuthenticated.Value)
                {
                    Application.Exit();
                    return;
                }

                Application.Run(mainForm);
            }
        }

        private static void HandlerPreviewProcessInfo(string[] args, Process currentPro)
        {
            //MessageBox.Show("Open message!");

            int hwnd = API.FindWindow(null, API.mainWindowName);
            if (hwnd != 0)
            {
                API.COPYDATASTRUCT cds;
                cds.dwData = IntPtr.Zero;
                cds.lpData = args[0];
                cds.cbData = args[0].Length + 1;

                API.SendMessage(hwnd, API.WM_COPYDATA, 0, ref cds);
            }
        }

        public class ArgInfo
        {
            public IImportExport Importer;
            public string Extension;
            public string ModuleName;

            public static ArgInfo Parse(string file)
            {

                var factory = StartHelper.CreateImportExportFactory();

                var ret = new ArgInfo();
                ret.Importer = factory.Create(file);
                ret.Extension = factory.Extension;
                ret.ModuleName = factory.ModuleName;
                return ret;
            }
        }

        private static class StartHelper
        {
            internal static Type LoginFormType;
            static Type MainFormType;
            static Type ImportExportFactoryType;
            static StartHelper()
            {

                Parse();

            }

            private static void Parse()
            {
                var profile = ProjectProfileParser.Parse();

                var startDll = ConfigurationManager.AppSettings["StartDll"];
                if (string.IsNullOrEmpty(startDll))
                    startDll = "ProWrite.UI.Controls.dll";
                startDll = Constance.AppPath + startDll;
                var a = Assembly.LoadFile(startDll);
                Debug.Assert(a != null);

                List<ModuleInfo> modules = new List<ModuleInfo>();

                foreach (var t in a.GetTypes())
                {
                    if (t.IsClass)
                    {
                        if (t.GetCustomAttributes(typeof(LoginFormAttribute), false).FirstOrDefault() != null)
                        {
                            LoginFormType = t;
                        }
                        if (t.GetCustomAttributes(typeof(MainFormAttribute), false).FirstOrDefault() != null)
                        {
                            MainFormType = t;
                        }
                        if (t.GetCustomAttributes(typeof(ImportExportFactoryAttribute), false).FirstOrDefault() != null)
                        {
                            ImportExportFactoryType = t;
                        }
                        var m = (PWModuleAttribute)t.GetCustomAttributes(typeof(PWModuleAttribute), false).FirstOrDefault();
                        if (m != null)
                        {
                            modules.Add(new ModuleInfo { ModuleName = m.Name, ModuleType = t });
                        }
                    }

                }

                profile.Modules = modules.ToArray();
            }

            public static ILoginForm CreateLoginForm()
            {
                try
                {
                    return (ILoginForm)Activator.CreateInstance(LoginFormType);
                }
                catch (Exception ex)
                {
                    Log.Error(ex.Message, ex);
                    return null;
                }
            }

            public static Form CreateMainForm()
            {
                try
                {
                    return (Form)Activator.CreateInstance(MainFormType);
                }
                catch (Exception ex)
                {
                    Log.Error(ex.Message, ex);
                    return null;
                }
            }

            public static IImportExportFactory CreateImportExportFactory()
            {
                try
                {
                    return (IImportExportFactory)Activator.CreateInstance(ImportExportFactoryType);
                }
                catch (Exception ex)
                {
                    Log.Error(ex.Message, ex);
                    return null;
                }
            }

        }

        private class SplashForm : Form
        {
            System.Windows.Forms.Timer timer = new System.Windows.Forms.Timer();
            public SplashForm()
            {

                BackColor = Color.Gainsboro;
                ForeColor = Color.Bisque;

                AutoScaleDimensions = new SizeF(6F, 13F);
                AutoScaleMode = AutoScaleMode.Font;
                MaximizeBox = false;
                MinimizeBox = false;
                Name = "SplashForm";


                FormBorderStyle = FormBorderStyle.None;
                StartPosition = FormStartPosition.CenterScreen;
                ShowInTaskbar = false;
                TransparencyKey = Color.Gainsboro;
                TopMost = true;


                timer.Interval = 5;
                timer.Tick += new EventHandler(timer_Tick);
                ServiceManager.Add<System.Windows.Forms.Timer>(timer);

                this.InvokeMethod(() =>
                {
                    Image img = Image.FromStream(Assembly.GetExecutingAssembly().GetManifestResourceStream("ProWrite.UI.Controls.Splash.png"));
                    BackgroundImage = img;
                    ClientSize = new Size(img.Size.Width + 1, img.Height);
                });

            }

            void timer_Tick(object sender, EventArgs e)
            {
                timer.Stop();
                timer.Tick -= timer_Tick;

                AutoResetEvent waitHandle = new AutoResetEvent(false);
                ServiceManager.Add<System.Threading.EventWaitHandle>(waitHandle);

                AuthenticateService authenticateService = new ProWriteAuthenticateService();
                var hasAuth = authenticateService.Authenticate();

                if (hasAuth)
                {
                    HasAuthenticated = true;
                }
                else
                {
                    using (var loginForm = StartHelper.CreateLoginForm())
                    {
                        loginForm.AuthenticateService = authenticateService;

                        loginForm.ShowDialog(this);
                        HasAuthenticated = authenticateService.HasAuthenticated;
                    }
                }

                waitHandle.WaitOne();

                ServiceManager.Remove<System.Threading.EventWaitHandle>();
                waitHandle.Close();

                Hide();
                Close();
            }

            protected override void OnShown(EventArgs e)
            {
                base.OnShown(e);
                timer.Start();
                TopMost = false;
            }


        }

        private static void ShowSplash()
        {
            CodeTimer.Time("ShowSplash", () =>
            {
                using (var form = new SplashForm())
                    form.ShowDialog();
            });
        }

        private UserPreferenceChangingFilter filter;
        private class UserPreferenceChangingFilter : IMessageFilter
        {
            public bool PreFilterMessage(ref Message m)
            {
                if (m.Msg == 0x201a || m.Msg == 0x2015)
                    return true;
                return false;
            }
        }

        private void Application_ApplicationExit(object sender, EventArgs e)
        {
            try
            {
                Application.RemoveMessageFilter(filter);
                var listSigns = SignInfo.AllSigns;
                if (listSigns != null && listSigns.Length > 0)
                {
                    foreach (SignInfo item in listSigns)
                    {
                        if (item.DashboardType == ProWrite.Core.DashboardType.Sign
                            && item.Controller.Connection.State != System.Communication.ConnectionState.Closed)
                            item.Controller.Connection.Close();
                    }
                }


                ProjectInfo.Current.LastModule = ModuleManager.CurrentModuleName;

                var modules = ModuleManager.Items;
                if (modules != null && modules.Length > 0)
                {
                    foreach (var m in modules)
                    {
                        m.SaveLayout();
                    }
                }

                IDataProvider dp = ServiceManager.Get<IDataProvider>();
                if (dp != null)
                    dp.Update();

                if (mainForm != null)
                {
                    mainForm.Dispose();
                    mainForm = null;
                }

            }
            catch (Exception ex)
            {
                Log.Error("MainForm Exception: " + ex.Message);
            }
            finally
            {
            }
        }


        private void Application_ThreadException(object sender, ThreadExceptionEventArgs e)
        {
            Log.Error(e.Exception.Message, e.Exception);

            IDataProvider dp = ServiceManager.Get<IDataProvider>();
            if (dp != null)
                dp.Update();

            MessageBox.Show(e.Exception.ToString());
        }

    }
}
