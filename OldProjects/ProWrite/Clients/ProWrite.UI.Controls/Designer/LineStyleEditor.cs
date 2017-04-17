//using System;
//using System.Collections.Generic;
//using System.Linq;
//using System.Text;
//using System.Drawing.Design;
//using ProWrite.Entity.Settings;
//using System.Drawing;

//namespace ProWrite.UI.Controls.Designer
//{
//    public class LineStyleEditor : UITypeEditor
//    {
//        private IWindowsFormsEditorService service = null;

//        public override UITypeEditorEditStyle GetEditStyle(System.ComponentModel.ITypeDescriptorContext context)
//        {
//            return UITypeEditorEditStyle.DropDown;
//        }

//        public override bool GetPaintValueSupported(System.ComponentModel.ITypeDescriptorContext context)
//        {
//            return true;
//        }

//        public override void PaintValue(PaintValueEventArgs e)
//        {
//            base.PaintValue(e);

//            var styles = Enum.GetValues(typeof(DashKind));
//            foreach (DashKind dash in styles)
//            {
//                Bitmap bmp = new Bitmap(32, 16, PixelFormat.Format24bppRgb);
//                using (Graphics graph = Graphics.FromImage(bmp))
//                {
//                    graph.FillRectangle(brush, 0, 0, 32, 16);

//                    //pen.StartCap = cap;
//                    //pen.DashOffset = 8;
//                    pen.DashStyle = dash;

//                    graph.DrawLine(pen, new Point(0, 7), new Point(32, 7));

//                    InnerImageList.Images.Add(dash.ToString(), bmp);
//                }
//                innerRepositoryItemImageComboBox.Items.Add(new DevExpress.XtraEditors.Controls.ImageComboBoxItem("", dash, i));

//                i++;
//            }
//        }

//        public override object EditValue(System.ComponentModel.ITypeDescriptorContext context, IServiceProvider provider, object value)
//        {
//            if (context == null
//                || context.Instance == null
//                || provider == null)
//                return value;

          
//            return value;

//        }
//    }
//}
