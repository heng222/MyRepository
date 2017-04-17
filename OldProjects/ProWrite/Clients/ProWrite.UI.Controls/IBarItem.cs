using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using DevExpress.XtraBars;
using System.ComponentModel;
using ProWrite.UI.Controls.Common.Messages;

namespace ProWrite.UI.Controls
{
    public interface IHelpPath
    {
        string HelpPath { get; set; }
    }

    public interface IBarItem : IHelpPath
    {
        string Caption { get; set; }
        bool Enabled { get; set; }
        BarItemVisibility Visibility{ get;set;}
        MenuCommands Command { get; set; }
        event ItemClickEventHandler ItemClick;
        object Tag { get; set; }

    }

    public interface IPropertySetBarItem:IBarItem
    {
        string SourcePropertyName { get; set; }
        string TargetPropertyName { get; set; }
    }

    public class BarButtonItemEx : BarButtonItem, IPropertySetBarItem
    {
        [Browsable(false)]
        public MenuCommands Command { get; set; }
        public string SourcePropertyName { get; set; }
        public string TargetPropertyName { get; set; }

        [Browsable(false)]
        public string HelpPath { get; set; }

        public bool IsFireEvent = true;

        protected override void RaiseDownChanged()
        {
            if(IsFireEvent)
                base.RaiseDownChanged();
        }
        
    }

    public class BarEditItemEx : BarEditItem, IPropertySetBarItem
    {
        [Browsable(false)]
        [EditorBrowsable( EditorBrowsableState.Never)]
        public MenuCommands Command { get; set; }
        public string SourcePropertyName { get; set; }
        public string TargetPropertyName { get; set; }

        [Browsable(false)]
        public string HelpPath { get; set; }
    }

}
