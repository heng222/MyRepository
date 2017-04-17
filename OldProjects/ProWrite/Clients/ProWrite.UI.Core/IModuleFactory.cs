using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace ProWrite.UI.Controls
{
    public interface IModuleFactory
    {
        void Create(string moduleName);
    }
}
