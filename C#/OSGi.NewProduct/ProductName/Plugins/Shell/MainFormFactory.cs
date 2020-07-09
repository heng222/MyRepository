using System.Windows.Forms;

using Platform.Presentation;

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
