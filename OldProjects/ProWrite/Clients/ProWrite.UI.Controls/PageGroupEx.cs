using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using DevExpress.XtraBars.Ribbon;

namespace ProWrite.UI.Controls
{
    public class PageGroupEx : RibbonPageGroup,IHelpPath
    {
        [Browsable(false)]
        public string HelpPath { get; set; }
    }
}
