
using System;
using System.Linq;
using System.Windows.Forms;
using Acl.Log;
using Acl.ServiceManagement;
using Acl.Threading;
using OSGi;
using Platform.Presentation;
using Platform.Presentation.Options;
using Products.Domain;
using Products.Infrastructure.Events;
using Products.Infrastructure.Messages;
using Products.Infrastructure.Specification;
using Products.Presentation;
using Products.Shell.ConfigView;
using Products.Shell.MainView;
using Products.Shell.Properties;

namespace Products.Shell
{
    class Activator : IBundleActivator, IBundleListener, IFrameworkListener, IDisposable
    {
        #region "Field"
        private bool _disposed = false;
        private SystemAttributeImpl _sysAttriImpl = new SystemAttributeImpl();
        private SplashScreenManager _splashSrceen = null;
        private ILog _log;
        private MainFormCloseMonitor _mainFormMonitor;
        private ProcessMonitor _processMonitor = null;
        #endregion

        #region "Constructor && Desctructor"
        public Activator()
        {
            _log = LogManager.GetLogger("Shell");

            Workbench.SubscribeDispatcherExceptionEvent(ex => _log.Error(ex.Message, ex));
            Workbench.SubscribeTaskExceptionEvent(ex => _log.Error(ex.Message, ex));

            ServiceManager.Current.RegisterInstance(_sysAttriImpl, typeof(ISystemAttribute));
        }

        ~Activator()
        {
            this.Dispose(false);
        }
        #endregion

        #region "IBundleActivator 成员"
        public void Start(IBundleContext context)
        {
            try
            {
                context.AddFrameworkListener(this);
                context.AddBundleListener(this);

                this.OpenSplashScreen(); 
                
                //NodeContextManager.Initialize();

                var dto = context.Framework.Adapt<OSGi.Dto.Framework.FrameworkDto>();
                foreach (var key in dto.Properties.Keys)
                {
                    Workbench.Context.Add(key, dto.Properties[key]);
                }

                this.InitProductProperty(context);

                this.InitializeComponentMetaData();

                this.UpdateOptimizeInterval(context);

                // 设置ShellFactory
                Workbench.SetMainFormFactory(new MainFormFactory());

                // 初始化 Shell 窗体及控件
                InitializeShellFormAndControls();

                // 更新产品属性
                UpdateProductProperty();
            }
            catch (Exception ex)
            {
                HandleAppStartError(ex);
            }
        }

        public void Stop(IBundleContext context)
        {
            context.RemoveFrameworkListener(this);
            context.RemoveBundleListener(this);

            CloseSplashScreen();
            CloseMainFormMonitor();
            ClosProcessMonitor();
        }

        #endregion



        #region IBundleListener 成员
        /// <summary>
        /// 
        /// </summary>
        void IBundleListener.BundleChanged(BundleEvent e)
        {
            if (e.Type == BundleEventType.Stopping)
            {
                if (_processMonitor == null)
                {
                    _processMonitor = new ProcessMonitor(_log.Warn, OnProcessKilling);
                    _processMonitor.Start();
                }
            }
        }

        #endregion


        #region "IFrameworkListener 成员"
        /// <summary>
        /// 
        /// </summary>
        public void FrameworkEvent(FrameworkEvent e)
        {
            if (e.Type == FrameworkEventType.Started)
            {
                ShowMainForm(e.Bundle.Context);

                //关闭闪屏
                CloseSplashScreen();
            }
            else if (e.Type == FrameworkEventType.Stopped)
            {
                CloseMainFormMonitor();

                Workbench.Shutdown();
            }
        }
        #endregion


        #region "IDisposable 成员"
        protected virtual void Dispose(bool disposing)
        {
            if (!_disposed)
            {
                if (disposing)
                {
                    // TODO: 释放托管资源.
                }
                _disposed = true;
            }
        }

        public void Dispose()
        {
            this.Dispose(true);
            GC.SuppressFinalize(this);
        }
        #endregion

        #region "private methods"

        private void HandleAppStartError(Exception ex)
        {
            // 与用户进行交互
            var strText = "程序启动时发生严重错误，是否立即停止？" + "\r\n信息：" + ex.Message;
            var strCaption = "启动错误";
            var btns = MessageBoxButtons.YesNo;
            var icons = MessageBoxIcon.Error;

            var ownerForm = Application.OpenForms.Cast<Form>().FirstOrDefault();
            if (ownerForm == null)
            {
                ShowMessageBox(ex, strText, strCaption, btns, icons, ownerForm);
            }
            else
            {
                if (ownerForm.InvokeRequired)
                {
                    ownerForm.Invoke(new Action(() => ShowMessageBox(ex, strText, strCaption, btns, icons, ownerForm)));
                }
                else
                {
                    ShowMessageBox(ex, strText, strCaption, btns, icons, ownerForm);
                }
            }
        }

        private static void ShowMessageBox(Exception ex, string strText, string strCaption, MessageBoxButtons btns, MessageBoxIcon icons, Form ownerForm)
        {
            var rc = MessageBox.Show(ownerForm, strText, strCaption, btns, icons);
            if (rc == DialogResult.Yes)
            {
                throw ex;
            }
        }

        private void OpenSplashScreen()
        {
            _splashSrceen = new SplashScreenManager();
            ThreadProxy.QueueUserWorkItem(() =>
            {
                try
                {
                    if (_splashSrceen == null) return;
                    _splashSrceen.OpenSplashScreen();
                }
                catch (Exception ex)
                {
                    _log.Error(ex.Message, ex);
                }
            });
        }

        private void CloseSplashScreen()
        {
            ThreadProxy.QueueUserWorkItem(() =>
            {
                try
                {
                    if (_splashSrceen == null) return;
                    _splashSrceen.CloseSplashScreen();
                    _splashSrceen = null;
                }
                catch (System.Exception ex)
                {
                    _log.Error("关闭闪屏时出现问题，" + ex.Message, ex);
                }
            });
        }

        private void InitProductProperty(IBundleContext context)
        {
            Workbench.Product.ChineseName = context.GetProperty("Product.ChineseName");
            Workbench.Product.EnglishName = context.GetProperty("Product.EnglishName");
            Workbench.Product.Version = context.GetProperty("Product.Version");
            Workbench.Product.Description = context.GetProperty("Product.Description");
            Workbench.Product.Company = context.GetProperty("Product.Company");
            Workbench.Product.Copyright = context.GetProperty("Product.Copyright");

            Workbench.OptionManager.Title = context.GetProperty("OptionTitle");
        }

        private void UpdateProductProperty()
        {
            Workbench.Product.ChineseName = _sysAttriImpl.ProjectChsName;
            Workbench.Product.EnglishName = _sysAttriImpl.ProductEnName;
            Workbench.Product.Version = _sysAttriImpl.ProductStringVersion;
            Workbench.Product.Description = _sysAttriImpl.ApplicationDescription;
            Workbench.Product.Company = _sysAttriImpl.CompanyChsFullName;
            Workbench.Product.Copyright = _sysAttriImpl.Copyright;
        }

        private void InitializeComponentMetaData()
        {
            Workbench.ComponentMetadataLoader = () => FrameworkFactory.CurrentFramework.Context
                        .Bundles
                        .Where(p => p.BundleId != 0)
                        .Select(p => new object[]
                            {
                                p.SymbolicName,
                                p.Version,
                                p.State,
                                p.Headers[Constants.BundleDescription]
                            });
        }

        private void UpdateOptimizeInterval(IBundleContext context)
        {
            if (context.Bundle.Headers.ContainsKey("OptimizeInterval"))
            {
                int value;
                if (!int.TryParse(context.Bundle.Headers["OptimizeInterval"], out value)) { value = 30; }

                Workbench.OptimizeInterval = value;
            }
        }

        private void InitializeShellFormAndControls()
        {
            Workbench.SendMessage(() =>
            {
                _log.Info("正在创建主窗体");

                Workbench.CreateMainForm();

                //创建主窗口监视器，每隔10秒检查窗口句柄是否存在，不存在则关闭进程
                _mainFormMonitor = new MainFormCloseMonitor(Workbench.MainForm, _log.Warn, OnProcessKilling);
                
                // 添加日志窗体。
                MainWorkSpace.AddPart(new LogControl(), Resources.AppLog);

                // 创建数码管时钟控件
                MainWorkSpace.AddPart(new NixieTubeClockControl(), Resources.NixietubeClock);

                // 常规配置
                IOptionControl optionControl = new GeneralConfigPage();
                Workbench.AddOption(optionControl);

                // 日志配置
                var logCfgPage = new LogConfigPage();
                Workbench.AddOption(logCfgPage, logCfgPage);
            });
        }
        
        private void OnProcessKilling()
        {
            GlobalMessageBuses.PublishApplicationExiting(new ProcessExitingEventArgs(), null);
            //LocalMessageBus.Current.Publish(topic: AtsMessageTopics.OnProcessKilling);
        }

        private void ClosProcessMonitor()
        {
            if (_processMonitor != null)
            {
                _processMonitor.Dispose();
                _processMonitor = null;
            }
        }

        private void ShowMainForm(IBundleContext context)
        {
            Workbench.PostMessage(() =>
            {
                try
                {
                    //// 引发OnMainFormShowing事件。
                    //var args = new CancelEventArgs();
                    //OnMainFormShowing(context, args);

                    //if (!args.Cancel)
                    //{
                    //    // Show main form
                    //    Workbench.ShowMainForm();
                    //}
                    Workbench.ShowMainForm();
                }
                catch (System.Exception ex)
                {
                    _log.Error("UI 线程出现异常，主窗口已退出，错误原因:" + ex.Message, ex);
                }
                finally
                {
                    FrameworkFactory.CurrentFramework.Stop();
                }
            });
        }

        private void CloseMainFormMonitor()
        {
            if (_mainFormMonitor != null)
            {
                _mainFormMonitor.Dispose();
                _mainFormMonitor = null;
            }
        }
        #endregion


    }
}
