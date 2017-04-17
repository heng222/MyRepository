using System;
using System.Collections.Generic;
using System.Text;
using DevExpress.XtraTab;
using System.Windows.Forms;
using DevExpress.Utils;
using log4net;
using ProWrite.Core;
using ProWrite.UI.Controls.Common;
using ProWrite.UI.Controls.Editor;
using System.Xml.Serialization;
using System.ComponentModel;
using ProWrite.UI.Controls.Common.Messages;
using DevExpress.XtraBars;

namespace ProWrite.UI.Controls
{
    [XmlRoot(ElementName = "Ribbon", Namespace = "ProWrite")]
    public class _Ribbon
    {
        [XmlAttribute]
        public string ApplicationIconKey;
        public _ApplicationMenu ApplicationMenu;
        [XmlArrayItem(ElementName="PopMenu")]
        public List<_PopMenu> PopMenus;
        [XmlArrayItem(ElementName = "RibbonPage")]
        public List<_RibbonPage> Pages;

        [XmlArrayItem(ElementName="BarItem")]
        public List<_BarItem> BarItems;

    }

    public class _RibbonPage
    {
        [XmlAttribute]
        [DefaultValue(false)]
        public bool IsDefaultPage;

        [XmlAttribute]
        [DefaultValue("")]
        public string CaptionKey;

        [XmlAttribute]
        [DefaultValue("")]
        public string ModuleName;

        [XmlAttribute]
        [DefaultValue("")]
        public string ModuleClazz;

        [XmlArrayItem(ElementName = "RibbonPageGroup")]
        public List<_RibbonPageGroup> Groups;
    }

    public partial class _RibbonPageGroup
    {

        [XmlArrayItem("Item", IsNullable = false)]
        public List<_BarItemRef> Items;

        [XmlAttribute]
        [DefaultValue("")]
        public string Name;

        [XmlAttribute]
        [DefaultValue("")]
        public string CaptionKey;

        [XmlAttribute]
        [DefaultValue(false)]
        public bool ShowCaptionButton;
    }

    public partial class _BarItemRef
    {
        [XmlAttribute]
        public string Ref;

        [XmlAttribute]
        [DefaultValue(false)]
        public bool BeginGroup;

        [XmlAttribute]
        [DefaultValue("")]
        public string KeyTip;

        [XmlAttribute]
        [DefaultValue("")]
        public string DropDownKeyTip;

        [XmlAttribute]
        [DefaultValue(false)]
        public bool ButtonGroup;
    }

    public partial class _BarItem
    {

        [XmlAttribute]
        [DefaultValue("")]
        public string Name;

        [XmlAttribute]
        [DefaultValue("")]
        public string CaptionKey;

        [XmlAttribute]
        [DefaultValue("")]
        public string HintKey;

        [XmlAttribute]
        [DefaultValue("")]
        public string ImageKey;

        [XmlAttribute]
        [DefaultValue(Keys.None)]
        public Keys Shortcut;

        [XmlAttribute]
        [DefaultValue("")]
        public string Clazz;

        [XmlAttribute]
        [DefaultValue(true)]
        public bool Enable;

        [XmlAttribute]
        [DefaultValue(BarItemVisibility.Always)]
        public BarItemVisibility Visiblity;

        

        [XmlAttribute]
        [DefaultValue(MenuCommands.None)]
        public MenuCommands Command;

        [XmlAttribute]
        [DefaultValue("")]
        public string CommandHandler;

        public _BarItem()
        {
            this.Enable = true;
        }
    }

    public partial class _BarButtonItem:_BarItem
    {
        [XmlAttribute]
        [DefaultValue(BarButtonStyle.Default)]
        public BarButtonStyle ButtonStyle;

        [XmlAttribute]
        [DefaultValue("")]
        public string DropDownControl;
    }

    public enum BarItemType
    {

        BarButtonItem,
        BarCheckItem,
        BarSubItem,
        BarStaticItem,
        RibbonGalleryBarItem,
        BarButtonGroup,
        Custom
    }

    public class _PopMenu
    {
        [XmlArrayItem("Item", IsNullable = false)]
        public string[] Items;

        [XmlAttribute()]
        public string Name;
    }

    public class _ApplicationMenu
    {
        public List<string> Items;
    }
}