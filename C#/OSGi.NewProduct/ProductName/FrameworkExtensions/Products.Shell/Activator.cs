
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

        #region "IBundleActivator ��Ա"
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

                // ����ShellFactory
                Workbench.SetMainFormFactory(new MainFormFactory());

                // ��ʼ�� Shell ���弰�ؼ�
                InitializeShellFormAndControls();

                // ���²�Ʒ����
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



        #region IBundleListener ��Ա
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


        #region "IFrameworkListener ��Ա"
        /// <summary>
        /// 
        /// </summary>
        public void FrameworkEvent(FrameworkEvent e)
        {
            if (e.Type == FrameworkEventType.Started)
            {
                ShowMainForm(e.Bundle.Context);

                //�ر�����
                CloseSplashScreen();
            }
            else if (e.Type == FrameworkEventType.Stopped)
            {
                CloseMainFormMonitor();

                Workbench.Shutdown();
            }
        }
        #endregion


        #region "IDisposable ��Ա"
        protected virtual void Dispose(bool disposing)
        {
            if (!_disposed)
            {
                if (disposing)
                {
                    // TODO: �ͷ��й���Դ.
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
            // ���û����н���
            var strText = "��������ʱ�������ش����Ƿ�����ֹͣ��" + "\r\n��Ϣ��" + ex.Message;
            var strCaption = "��������";
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
                    _log.Error("�ر�����ʱ�������⣬" + ex.Message, ex);
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
                _log.Info("���ڴ���������");

                Workbench.CreateMainForm();

                //���������ڼ�������ÿ��10���鴰�ھ���Ƿ���ڣ���������رս���
                _mainFormMonitor = new MainFormCloseMonitor(Workbench.MainForm, _log.Warn, OnProcessKilling);
                
                // �����־���塣
                MainWorkSpace.AddPart(new LogControl(), Resources.AppLog);

                // ���������ʱ�ӿؼ�
                MainWorkSpace.AddPart(new NixieTubeClockControl(), Resources.NixietubeClock);

                // ��������
                IOptionControl optionControl = new GeneralConfigPage();
                Workbench.AddOption(optionControl);

                // ��־����
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
                    //// ����OnMainFormShowing�¼���
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
                    _log.Error("UI �̳߳����쳣�����������˳�������ԭ��:" + ex.Message, ex);
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
