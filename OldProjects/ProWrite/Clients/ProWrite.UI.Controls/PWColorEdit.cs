using System;
using System.Collections;
using System.Collections.Generic;
using System.ComponentModel;
using System.Diagnostics;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using DevExpress.LookAndFeel;

using DevExpress.XtraEditors;
using DevExpress.XtraEditors.Controls;
using DevExpress.XtraEditors.Drawing;
using DevExpress.XtraEditors.Registrator;
using DevExpress.XtraEditors.Repository;
using DevExpress.XtraEditors.ViewInfo;
using DevExpress.XtraEditors.Popup;
using DevExpress.XtraTab;
using ProWrite.Core;
using ProWrite.UI.Controls.Common;
using EditorRegistrationInfo = DevExpress.XtraEditors.Registrator.EditorRegistrationInfo;

namespace ProWrite.UI.Controls
{
    public class PWColorEdit : ColorEdit
    {
        static PWColorEdit()
        {
            RepositoryItemPWColorEdit.Register();
        }
        public PWColorEdit()
        {
        }

        protected override PopupBaseForm CreatePopupForm()
        {
            return new PWPopupColorEditForm(this);
        }

        public override string EditorTypeName
        {
            get { return RepositoryItemPWColorEdit.EditorName; }
        }

        [DesignerSerializationVisibility(DesignerSerializationVisibility.Content)]
        public new RepositoryItemPWColorEdit Properties
        {
            get { return base.Properties as RepositoryItemPWColorEdit; }
        }

    }

    public class PWPopupColorEditForm : PopupColorEditForm
    {
        private PWPopupColorBuilder builder;
        public PWPopupColorEditForm(ColorEdit ownerEdit)
            : base(ownerEdit)
        {
        }
        protected override PopupColorBuilder CreatePopupColorEditBuilder()
        {
            if (builder == null)
                builder = new PWPopupColorBuilder(this);
            return builder;
        }

        [Category(CategoryName.Properties)]
        public new RepositoryItemPWColorEdit Properties { get { return base.Properties as RepositoryItemPWColorEdit; } }
        public new PWColorEdit OwnerEdit { get { return base.OwnerEdit as PWColorEdit; } }

        [Category(CategoryName.Focus)]
        public override bool FormContainsFocus { get { return base.ContainsFocus || builder.CellsControl.LockFocus; } }
        public override bool AllowMouseClick(Control control, Point mousePosition)
        {
            return control == this || this.Contains(control) ?
                                                                 true
                       : builder.CellsControl.LockFocus;
        }

    }

    public class PopupColorEditWrapper : IPopupColorEdit
    {
        private IPopupColorEdit RealProxy;
        public PopupColorEditWrapper(IPopupColorEdit realProxy)
        {
            RealProxy = realProxy;
        }

        #region IPopupColorEdit Members

        public void ClosePopup()
        {
            RealProxy.ClosePopup();
        }

        public Color Color
        {
            get
            {

                return RealProxy.Color;
            }
        }

        public ColorListBox CreateColorListBox()
        {
            return RealProxy.CreateColorListBox();
        }

        public ColorEditTabControlBase CreateTabControl()
        {
            return new PWColorEditTabControlBase();
        }

        public object EditValue
        {
            get
            {
                return RealProxy.EditValue;
            }
        }

        public bool IsPopupOpen
        {
            get { return RealProxy.IsPopupOpen; }
        }

        public UserLookAndFeel LookAndFeel
        {
            get { return RealProxy.LookAndFeel; }
        }

        public void OnColorChanged()
        {
            RealProxy.OnColorChanged();
        }

        public RepositoryItemColorEdit Properties
        {
            get { return RealProxy.Properties; }
        }

        #endregion
    }

    public class PWPopupColorBuilder : PopupColorBuilder
    {
        public PWPopupColorBuilder(IPopupColorEdit owner)
            : base(new PopupColorEditWrapper(owner))
        {
            LocalMessageBus.Subject<SelectedSignMessage>().Observers += new System.Communication.Messaging.ObserverHandler<SelectedSignMessage>(PWPopupColorBuilder_Observers);
        }

        private SignType? signType = ControlService.SignCombo.Current.Type;

        void PWPopupColorBuilder_Observers(object sender, SelectedSignMessage msg)
        {
            signType = msg.CurrentSign.Type;
        }

        private object[] MonoColorList = new
            object[]
                                             {
                                                 Color.Transparent,
                                                 Color.Black
                                             }; 

        protected override void SetTabPageProperties(int pageIndex, PopupBaseForm shadowForm)
        {
            BaseControl control = null;
            XtraTabPage tabPage = this.TabControl.TabPages[pageIndex];
            ColorListBox colorBox = null;

            control = new PWColorCellsControl(shadowForm); 
            control.Size = (control as PWColorCellsControl).GetBestSize();
            switch (pageIndex)
            {
                case 0:
                    tabPage.Text = Localizer.Active.GetLocalizedString(StringId.ColorTabCustom);
                    control = new PWColorCellsControl(shadowForm);
                    (control as PWColorCellsControl).Properties = Owner.Properties;
                    (control as PWColorCellsControl).EnterColor += new EnterColorEventHandler(OnEnterColor);
                    control.Size = (control as PWColorCellsControl).GetBestSize();
                    tabPage.PageVisible = Properties.ShowCustomColors;
                    break;
                case 1:
                    tabPage.Text = Localizer.Active.GetLocalizedString(StringId.ColorTabWeb);
                    colorBox = CreateColorListBox();
                    colorBox.HighlightedItemStyle = Properties.HighlightedItemStyle;
                    
                    if (signType.HasValue && signType.Value != SignType.RGB)
                        colorBox.Items.AddRange(MonoColorList);
                    else
                        colorBox.Items.AddRange(ColorListBoxViewInfo.WebColors);
                    colorBox.EnterColor += new EnterColorEventHandler(OnEnterColor);
                    colorBox.SelectedIndexChanged += new EventHandler(OnSelectedIndexChanged);
                    colorBox.Size = control.Size;
                    //colorBox.Size = GetBestListBoxSize(colorBox);
                    control = colorBox;
                    tabPage.PageVisible = Properties.ShowWebColors;
                    break;
                case 2:
                    tabPage.Text = Localizer.Active.GetLocalizedString(StringId.ColorTabSystem);
                    colorBox = CreateColorListBox();
                    colorBox.HighlightedItemStyle = Properties.HighlightedItemStyle;
                    colorBox.Items.AddRange(ColorListBoxViewInfo.SystemColors);
                    colorBox.EnterColor += new EnterColorEventHandler(OnEnterColor);
                    colorBox.SelectedIndexChanged += new EventHandler(OnSelectedIndexChanged);
                    colorBox.Size = control.Size;
                    //colorBox.Size = GetBestListBoxSize(colorBox);
                    control = colorBox;
                    tabPage.PageVisible = false;
                    break;
            }
            if (control == null)
                return;
            control.Dock = DockStyle.Fill;
            control.BorderStyle = BorderStyles.NoBorder;
            if (Owner.LookAndFeel != null)
                control.LookAndFeel.Assign(Owner.LookAndFeel);
            tabPage.Controls.Add(control);
        }

        public new PWColorEditTabControlBase TabControl { get { return base.TabControl as PWColorEditTabControlBase; } }

        public override void ProcessKeyDown(KeyEventArgs e)
        {
            if (e.Handled)
                return;
            if (e.KeyCode == Keys.Tab)
            {
                TabControl.OnProcessTabKey(e);
                e.Handled = true;
                return;
            }
            if (TabControl.SelectedTabPage.Text == Localizer.Active.GetLocalizedString(StringId.ColorTabCustom))
                ((PWColorCellsControl)TabControl.SelectedTabPage.Controls[0]).ProcessKeyDown(e);
                //((PWColorCellsControlEx)TabControl.SelectedTabPage.Controls[0]).ProcessKeyDown(e);
            else
                ((ColorListBox)TabControl.SelectedTabPage.Controls[0]).ProcessKeyDown(e);
        }

        protected override bool FindEditColor(Color clr)
        {
            if (Properties.ShowSystemColors)
            {
                for (int i = 0; i < ColorListBoxViewInfo.SystemColors.Length; i++)
                {
                    if (ColorListBoxViewInfo.SystemColors[i].Equals(clr))
                    {
                        TabControl.OnSelectPageByCaption(Localizer.Active.GetLocalizedString(StringId.ColorTabSystem));
                        (TabControl.SelectedTabPage.Controls[0] as ColorListBox).SetSelectedIndex(i);
                        return true;
                    }
                }
            }
            if (Properties.ShowWebColors)
            {
                for (int i = 0; i < ColorListBoxViewInfo.WebColors.Length; i++)
                {
                    if (ColorListBoxViewInfo.WebColors[i].Equals(clr))
                    {
                        TabControl.OnSelectPageByCaption(Localizer.Active.GetLocalizedString(StringId.ColorTabWeb));
                        (TabControl.SelectedTabPage.Controls[0] as ColorListBox).SetSelectedIndex(i);
                        return true;
                    }
                }
            }
            if (Properties.ShowCustomColors)
            {
                TabControl.OnSelectPageByCaption(Localizer.Active.GetLocalizedString(StringId.ColorTabCustom));
                PWColorCellsControl ctl = TabControl.SelectedTabPage.Controls[0] as PWColorCellsControl;
                //PWColorCellsControlEx ctl = TabControl.SelectedTabPage.Controls[0] as PWColorCellsControlEx;
                for (int i = 0; i < PWColorCellsControlViewInfo.CellColorsRGB.Length; i++)
                {
                    if (PWColorCellsControlViewInfo.CellColorsRGB[i] == clr)
                    {
                        ctl.SelectedCellIndex = i;
                        return true;
                    }
                }
                PWColorCellsControlViewInfo vi = ctl._ViewInfo as PWColorCellsControlViewInfo;
                for (int i = 0; i < vi.CustomColors.Length; i++)
                {
                    if (vi.CustomColors[i] == clr)
                    {
                        ctl.SelectedCellIndex = i + PWColorCellsControlViewInfo.CellColorsRGB.Length;
                        return true;
                    }
                }
                ctl.SelectedCellIndex = PWColorCellsControlViewInfo.CellColorsRGB.Length;
            }
            TabControl.SelectedTabPageIndex = 0;
            return false;
        }

        //public new PWColorCellsControlEx CellsControl
        //{
        //    get { return ((PWColorCellsControlEx)TabControl.TabPages[0].Controls[0]); }
        //}
        public new PWColorCellsControl CellsControl
        {
            get { return ((PWColorCellsControl)TabControl.TabPages[0].Controls[0]); }
        }

        public new PWColorCellsControlViewInfo CellsViewInfo
        {
            get { return (((PWColorCellsControl)TabControl.TabPages[0].Controls[0])._ViewInfo as PWColorCellsControlViewInfo); }
            //get { return (((PWColorCellsControlEx)TabControl.TabPages[0].Controls[0])._ViewInfo as PWColorCellsControlViewInfo); }
        }
        public override Size CalcContentSize()
        {
            Size size = CellsControl.GetBestSize();
            //size.Height = (TabControl.TabPages[1].Controls[0] as ColorListBox).ViewInfo.GetNearestBestClientHeight(size.Height);
            return TabControl.CalcSizeByPageClient(size);
        }
    }

    public class PWColorEditTabControlBase : ColorEditTabControlBase
    {
        internal void OnProcessTabKey(KeyEventArgs tabArgs)
        {
            base.ProcessTabKey(tabArgs);
        }
        internal void OnSelectPageByCaption(string caption)
        {
            base.SelectPageByCaption(caption);
        }

    }

    [DevExpress.XtraEditors.Registrator.UserRepositoryItem("Register")]
    public class RepositoryItemPWColorEdit : RepositoryItemColorEdit
    {
        static RepositoryItemPWColorEdit()
        {
            Register();
        }
        public RepositoryItemPWColorEdit()
        {

        }

        internal const string EditorName = "MyColorEdit";

        public static void Register()
        {
            EditorRegistrationInfo.Default.Editors.Add(new EditorClassInfo(EditorName, typeof(PWColorEdit),
                                                                           typeof(RepositoryItemPWColorEdit), typeof(ColorEditViewInfo),
                                                                           new ColorEditPainter(), true, null));
        }
        public override string EditorTypeName
        {
            get { return EditorName; }
        }

        //protected override string GetColorDisplayText(Color editValue)
        //{
        //    object color = editValue;

        //    ColorHelper.TryConvertToKnownColor(ref color);
        //    return base.GetColorDisplayText((Color)color);
        //}

    }

    class ColorHelper
    {
        static ColorHelper()
        {
            knownColorsHash = InitKnownColorsHash();
        }
        private ColorHelper() { }

        private static Hashtable knownColorsHash;

        private static Hashtable InitKnownColorsHash()
        {
            System.Array knownColors = System.Enum.GetValues(typeof(KnownColor));
            Hashtable hashtable = new Hashtable(knownColors.Length);
            foreach (KnownColor knownColorObject in knownColors)
            {
                Color color = Color.FromKnownColor(knownColorObject);
                int argbValue = color.ToArgb();
                if (color.IsSystemColor && hashtable.ContainsKey(argbValue))
                    continue;
                hashtable[argbValue] = knownColorObject;
            }
            return hashtable;
        }

        public static bool TryConvertToKnownColor(ref object color)
        {
            KnownColor knownColor = GetKnownColor(color);
            if (knownColor != 0)
            {
                color = Color.FromKnownColor(knownColor);
                return true;
            }
            return false;
        }

        public static KnownColor GetKnownColor(Color color)
        {
            KnownColor knownColor = color.ToKnownColor();
            if (knownColor == 0)
                knownColor = GetKnownColor(color.ToArgb());
            return knownColor;
        }
        public static KnownColor GetKnownColor(int argb)
        {
            object result = knownColorsHash[argb];
            if (result == null)
                return 0;
            return (KnownColor)result;
        }

        public static KnownColor GetKnownColor(object color)
        {
            if (color is KnownColor)
                return (KnownColor)color;
            if (color is Color)
                return GetKnownColor((Color)color);
            if (color is int)
                return GetKnownColor((int)color);
            return 0;
        }
    }
}