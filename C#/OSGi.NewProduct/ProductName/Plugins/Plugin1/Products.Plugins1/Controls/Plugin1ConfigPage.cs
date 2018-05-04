using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using Platform.Presentation.Options;
using Products.Presentation;

namespace Products.Plugins1.Controls
{
    /// <summary>
    /// Plugin1配置页面。
    /// </summary>
    [Option(ConfigNodeNames.Plugins.Plugin1.General, "Plugin1 Config Title")]
    partial class Plugin1ConfigPage : UserControl, IOptionControl
    {
        public Plugin1ConfigPage()
        {
            InitializeComponent();
        }

        public void ApplyChanges()
        {

        }

        public Control View
        {
            get { return this; }
        }
    }
}
