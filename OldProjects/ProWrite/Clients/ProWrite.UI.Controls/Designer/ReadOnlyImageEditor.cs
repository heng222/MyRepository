using System;
using System.Collections.Generic;
using System.Text;
using System.Drawing.Design;
using System.ComponentModel;
using System.Drawing;

namespace ProWrite.UI.Controls.Designer
{
    public class ReadOnlyImageEditor : NoneEditor
    {
        public ReadOnlyImageEditor() { }
        public override bool GetPaintValueSupported(ITypeDescriptorContext context)
        {
            return true;
        }

        public override void PaintValue(PaintValueEventArgs e)
        {
            Image image = e.Value as Image;
            if (image != null)
            {
                Rectangle bounds = e.Bounds;
                bounds.Width--;
                bounds.Height--;
                e.Graphics.DrawRectangle(SystemPens.WindowFrame, bounds);
                e.Graphics.DrawImage(image, e.Bounds);
            }
        }

    }
}
