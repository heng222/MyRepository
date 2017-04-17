using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing.Design;
using System.Windows.Forms.Design;
using System.Windows.Forms;

namespace ProWrite.UI.Controls.Designer
{
    public class EnumTypeEditor : UITypeEditor
    {
        public override UITypeEditorEditStyle GetEditStyle(System.ComponentModel.ITypeDescriptorContext context)
        {
            return UITypeEditorEditStyle.DropDown;
        }


        private EnumListBox enumListbox;
        public override object EditValue(System.ComponentModel.ITypeDescriptorContext context, IServiceProvider provider, object value)
        {
            if (context == null
                || context.Instance == null
                || provider == null)
                return value;

            var service = provider.GetService(typeof(IWindowsFormsEditorService)) as IWindowsFormsEditorService;

            if (service == null)
                return value;

            var enumValue = value as Enum;
            if (enumListbox == null)
            {
                enumListbox = new EnumListBox(enumValue.GetType());
                enumListbox.EditorService = service;
            }

            enumListbox.Populate(enumValue);

            service.DropDownControl(enumListbox);
            return enumListbox.EnumValue;
        }
    }

    
    public partial class EnumListBox : ListBox
    {
        private EnumDescriptionAttribute[] items;
        public EnumListBox(Type type)
        {
            items = EnumHelper.GetEnumDescriptions(type);
            if (items != null && items.Length > 0)
                Items.AddRange(items);
        }

        public IWindowsFormsEditorService EditorService { get; set; }
        
        public void Populate(Enum enumValue)
        {
            
            if (enumValue != null)
            {
                EnumValue = enumValue;

                if (items != null && items.Length > 0)
                {
                    var item = Array.FindIndex<EnumDescriptionAttribute>(items, p => { return p.Value.Equals( enumValue); });
                    SelectedIndex = item;
                }
            }
        }

        protected override void OnSelectedIndexChanged(EventArgs e)
        {
            base.OnSelectedIndexChanged(e);
            if (base.SelectedItem != null)
                EnumValue = SelectedItem.Value;

            if (EditorService != null)
                EditorService.CloseDropDown();
        }
        
        public new EnumDescriptionAttribute SelectedItem
        {
            get
            {
                return base.SelectedItem as EnumDescriptionAttribute;
            }
            set
            {
                base.SelectedItem = value;
            }
        }

        public Enum EnumValue { get; private set; }

        
    }
}
