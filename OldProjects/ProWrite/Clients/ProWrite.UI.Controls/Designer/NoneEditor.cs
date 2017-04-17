using System;
using System.Collections.Generic;
using System.Text;
using System.Drawing.Design;
using System.ComponentModel;
using System.ComponentModel.Design;

namespace ProWrite.UI.Controls.Designer
{
    public class NoneCollectionEditor : CollectionEditor
    {
        public NoneCollectionEditor(Type type) : base(type) { }
        public override UITypeEditorEditStyle GetEditStyle(ITypeDescriptorContext context)
        {
            return UITypeEditorEditStyle.None;
        }
    }

    public class NoneEditor : UITypeEditor
    {
        public override UITypeEditorEditStyle GetEditStyle(ITypeDescriptorContext context)
        {
            return UITypeEditorEditStyle.None;
        }
    }


}
