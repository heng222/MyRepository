using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace ProWrite.UI.Controls
{
    [AttributeUsage(AttributeTargets.Class)]
    public class LoginFormAttribute : Attribute
    {
    }

    [AttributeUsage(AttributeTargets.Class)]
    public class MainFormAttribute : Attribute
    {
    }

    public interface ILoginForm : IDisposable
    {
        
        AuthenticateService AuthenticateService { get; set; }
        DialogResult ShowDialog();
        DialogResult ShowDialog(IWin32Window owner);
    }


    public interface IMainForm
    {
        void Initialize();
    }
   
}
