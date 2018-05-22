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
            // ע�����
            ServiceManager.Current.RegisterInstance(_sysAttriImpl, typeof(ISystemAttribute));

            // ���²�Ʒ����
            Workbench.Product.ChineseName = _sysAttriImpl.ProjectChsName;
            Workbench.Product.EnglishName = _sysAttriImpl.ProductEnName;
            Workbench.Product.Version = _sysAttriImpl.ProductStringVersion;
            Workbench.Product.Description = _sysAttriImpl.ApplicationDescription;
            Workbench.Product.Company = _sysAttriImpl.CompanyChsFullName;
            Workbench.Product.Copyright = _sysAttriImpl.Copyright;
            
            // ������ؿؼ�
            Workbench.SendMessage(() =>
            {
                // �����־���塣
                MainWorkSpace.AddPart(new LogControl(), Resources.AppLog);

                // ���������ʱ�ӿؼ�
                MainWorkSpace.AddPart(new DNetNixieTubeClockControl(), Resources.NixietubeClock);

                // ��������
                IOptionControl optionControl = new GeneralConfigPage();
                Workbench.AddOption(optionControl);
                
                // ��־����
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
            //        throw new InvalidOperationException("�޷���ȡ�û���¼�ӿڡ�");
            //    }

            //    Workbench.MainForm.CreateGraphics();

            //    var loginresult = login.ShowLogOnDialog();

            //    if (loginresult != UserLogOnResult.Successful)
            //    {
            //        throw new InvalidOperationException("��¼ʧ�ܣ��˳�����");
            //    }
            //}
        }

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
