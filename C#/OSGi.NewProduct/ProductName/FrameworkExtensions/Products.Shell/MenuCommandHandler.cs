using System;
using System.Diagnostics;
using System.Windows.Forms;
using Acl;
using Acl.MessageBus;
using Acl.ServiceManagement;
using Platform.Presentation;
using Platform.Presentation.CommonControl;

namespace Products.Shell
{
    class MenuCommandHandler : IDisposable
    {
        private bool _disposed = false;
        private CompositeDisposable _subscribers = new CompositeDisposable();

        public MenuCommandHandler()
        {
            Subscribe("Local://MenuMessageHandler/ExitApplication", OnExitApplication);
            Subscribe("Local://MenuMessageHandler/About", OnAbout);
            Subscribe("Local://MenuMessageHandler/Settings", OnSettings);

            Subscribe("Local://MenuMessageHandler/OpenExeFolder", OnOpenExeFolder);

        }

        ~MenuCommandHandler()
        {
            this.Dispose(false);
        }

        private void Subscribe(string topic, Action<object, EventArgs> handler)
        {
            _subscribers.AddDisposable(LocalMessageBus.Current.Subscribe<EventArgs>(topic, handler));
        }

        private void OnExitApplication(object sender, EventArgs e)
        {
            Workbench.MainForm.Close();
        }


        private void OnAbout(object sender, EventArgs e)
        {
            Workbench.AboutBox.TopMost = true;
            Workbench.AboutBox.StartPosition = FormStartPosition.CenterScreen;
            Workbench.AboutBox.ShowDialog(Workbench.MainForm);
        }
        
        private void OnSettings(object sender, EventArgs e)
        {
            Workbench.OptionManager.Title = "选项";
            Workbench.OptionManager.Show(Workbench.MainForm);
        }

        private void OnOpenExeFolder(object sender, EventArgs e)
        {
            Process.Start("explorer.exe", AppDomain.CurrentDomain.BaseDirectory);
        }

        private void OnShowMainForm(object sender, EventArgs e)
        {
            Workbench.MainForm.Show();
        }
        

        protected virtual void Dispose(bool disposing)
        {
            if (!_disposed)
            {
                if (disposing)
                {
                    if (_subscribers != null)
                    {
                        _subscribers.Dispose();
                    }
                }
                _disposed = true;
            }
        }

        public void Dispose()
        {
            this.Dispose(true);
            GC.SuppressFinalize(this);
        }
    }
}
