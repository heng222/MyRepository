using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Drawing.Imaging;
using System.Drawing.Drawing2D;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Windows.Forms;
using DevExpress.XtraBars;
using DevExpress.XtraEditors;
using DevExpress.XtraEditors.Controls;
using DevExpress.XtraEditors.Popup;
using DevExpress.XtraTab;
using DevExpress.XtraEditors.Repository;
using ProWrite.Entity.Settings;

namespace ProWrite.UI.Controls
{
    public partial class LineBarItem : BarEditItemEx 
    {
        #region member
            private RepositoryItemImageComboBox innerRepositoryItemImageComboBox;
            private ImageList InnerImageList = null;
        #endregion

        public RepositoryItemImageComboBox RepositoryItemImageComboBox
        {
            get{ return innerRepositoryItemImageComboBox;}
            set { innerRepositoryItemImageComboBox = value; }
        }

        public event EventHandler LineDashStyleChanged;
        
        public LineBarItem()
        {
            InnerImageList = new ImageList();

            innerRepositoryItemImageComboBox = new DevExpress.XtraEditors.Repository.RepositoryItemImageComboBox();
            innerRepositoryItemImageComboBox.AllowFocused = false;
           
            //innerRepositoryItemImageComboBox.Name = "innerRepositoryItemImageComboBox";
         
            Edit = innerRepositoryItemImageComboBox;
            
            //PaintStyle = DevExpress.XtraBars.BarItemPaintStyle.Caption;
            
            if (!DesignMode)
                InitValues();
        }

        private void InitValues()
        {
            InnerImageList.ImageSize = new Size(32, 16);
            innerRepositoryItemImageComboBox.LargeImages = InnerImageList;

            int i = 0;
            using (Pen pen = new Pen(Color.Black, 2))
            {
                Brush brush = Brushes.White;
                //foreach (LineCap cap in Enum.GetValues(typeof(LineCap)))
                //{
                //    if (
                //        cap == LineCap.Custom
                //        || cap == LineCap.NoAnchor
                //        || cap == LineCap.Square
                //        || cap == LineCap.AnchorMask
                //        //   || cap == LineCap.Round
                //        //    || cap == LineCap.RoundAnchor
                //        || cap == LineCap.SquareAnchor
                //        //   || cap == LineCap.Flat
                //        //  || cap == LineCap.DiamondAnchor
                //        || cap == LineCap.Triangle
                //        // || cap == LineCap.ArrowAnchor
                //        ) continue;
                var styles = Enum.GetValues(typeof(DashStyle));
                foreach (DashStyle dash in styles)
                {
                    if (dash == DashStyle.Custom) continue;

                    Bitmap bmp = new Bitmap(32, 16, PixelFormat.Format24bppRgb);
                    using (Graphics graph = Graphics.FromImage(bmp))
                    {
                        graph.FillRectangle(brush, 0, 0, 32, 16);

                        //pen.StartCap = cap;
                        //pen.DashOffset = 8;
                        pen.DashStyle = dash;

                        graph.DrawLine(pen, new Point(0, 7), new Point(32, 7));

                        InnerImageList.Images.Add(dash.ToString(), bmp);
                    }
                    innerRepositoryItemImageComboBox.Items.Add(new DevExpress.XtraEditors.Controls.ImageComboBoxItem("", dash, i));
                    
                    i++;
                }
            }
            EditValue = DashStyle.Solid;

            innerRepositoryItemImageComboBox.EditValueChanged += LineDashStyleChanged;
        }

        public DashStyle LineDashStyle
        {
            get
            {
                if (EditValue != null)
                    return (DashStyle)EditValue;
                else
                    return DashStyle.Solid;
            }
            set
            {
                EditValue = value;
            }
        }

    }

    public partial class LineStyleRepositoryItemEdit : RepositoryItemImageComboBox
    {
        private static readonly Pen pen = new Pen(Color.Black, 2);
        private static readonly Brush brush = Brushes.White;

        public LineStyleRepositoryItemEdit()
        {
            InitValues();
        }

        private void InitValues()
        {

            int i = 0;
            ImageList InnerImageList = new ImageList();
            InnerImageList.ImageSize = new Size(32, 16);
           
            
            var styles = Enum.GetValues(typeof(DashKind));
            foreach (var dash in styles)
            {

                Bitmap bmp = new Bitmap(32, 16, PixelFormat.Format24bppRgb);
                using (Graphics graph = Graphics.FromImage(bmp))
                {
                    graph.FillRectangle(brush, 0, 0, 32, 16);
                    pen.DashStyle =(DashStyle) dash;
                    graph.DrawLine(pen, new Point(0, 7), new Point(32, 7));
                    InnerImageList.Images.Add(dash.ToString(), bmp);
                }
                Items.Add(new DevExpress.XtraEditors.Controls.ImageComboBoxItem("", dash, i));

                i++;
            }
            LargeImages = InnerImageList;
            //EditValueChanged += LineDashStyleChanged;
        }

    }
}
