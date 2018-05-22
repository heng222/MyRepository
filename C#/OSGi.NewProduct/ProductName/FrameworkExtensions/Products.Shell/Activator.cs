using System;
using System.ComponentModel;
using Acl.ServiceManagement;
using Framework.OSGi;
using Platform.Presentation;
using Platform.Presentation.Options;
using Products.Domain;
using Products.Infrastructure.Specification;
using Products.Presentation;
using Products.Shell.ConfigView;
using Products.Shell.MainView;
using Products.Shell.Properties;

namespace Products.Shell
{
    class Activator : Platform.Shell.Activator, IDisposable
    {
        private bool _disposed = false;
        private SystemAttributeImpl _sysAttriImpl = new SystemAttributeImpl();

        ~Activator()
        {
            this.Dispose(false);
        }

        #region "override methods"
        protected override void OnStart()
        {
            // 注册服务
            ServiceManager.Current.RegisterInstance(_sysAttriImpl, typeof(ISystemAttribute));

            // 更新产品属性
            Workbench.Product.ChineseName = _sysAttriImpl.ProjectChsName;
            Workbench.Product.EnglishName = _sysAttriImpl.ProductEnName;
            Workbench.Product.Version = _sysAttriImpl.ProductStringVersion;
            Workbench.Product.Description = _sysAttriImpl.ApplicationDescription;
            Workbench.Product.Company = _sysAttriImpl.CompanyChsFullName;
            Workbench.Product.Copyright = _sysAttriImpl.Copyright;
            
            // 创建相关控件
            Workbench.SendMessage(() =>
            {
                // 添加日志窗体。
                MainWorkSpace.AddPart(new LogControl(), Resources.AppLog);

                // 创建数码管时钟控件
                MainWorkSpace.AddPart(new DNetNixieTubeClockControl(), Resources.NixietubeClock);

                // 常规配置
                IOptionControl optionControl = new GeneralConfigPage();
                Workbench.AddOption(optionControl);
                
                // 日志配置
                var logCfgPage = new LogConfigPage();
                Workbench.AddOption(logCfgPage, logCfgPage);
            });
        }

        protected override void OnStop()
        {
        }

        protected override void OnMainFormShowing(IBundleContext context, CancelEventArgs args)
        {
            //if (NodeContextManager.Current.ControlTypes.Contains(PresentationControlType.Logon))
            //{
            //    var login = ServiceManager.Current.Get<IUserLogOn>();

            //    if (login == null)
            //    {
            //        throw new InvalidOperationException("无法获取用户登录接口。");
            //    }

            //    Workbench.MainForm.CreateGraphics();

            //    var loginresult = login.ShowLogOnDialog();

            //    if (loginresult != UserLogOnResult.Successful)
            //    {
            //        throw new InvalidOperationException("登录失败，退出程序。");
            //    }
            //}
        }

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
        #endregion

        #region "public methods"
        public void Dispose()
        {
            this.Dispose(true);
            GC.SuppressFinalize(this);
        }
        #endregion
    }
}
