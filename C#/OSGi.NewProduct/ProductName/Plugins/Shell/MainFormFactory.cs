using System.Windows.Forms;

using Acl.Presentation;

namespace Products.Shell
{
    class MainFormFactory : IMainFormFactory
    {
        public Form Create()
        {
            return new FrmMain(true);
        }
    }
}
