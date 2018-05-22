using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using Platform.Presentation;

namespace Products.Shell
{
    class DemoFormFactory : IMainFormFactory
    {
        public Form Create()
        {
            return new FrmMain(true);
        }
    }
}
