using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using ProWrite.Core;
using ProWrite.Entity.Settings;

namespace ProWrite.UI.Controls.Options.Views
{
    public partial class ImageView : ViewBase<ProWrite.Entity.Settings.ShapeImageTemplate>
    {
        public ImageView()
        {
            InitializeComponent();
        }

        protected override void OnPaint(PaintEventArgs e)
        {
            base.OnPaint(e);
            e.Graphics.DrawString("Image", Font, Brushes.Red, new PointF(200, 200));
        }

        protected override void DoBind()
        {
            txtHeight.Text = _data.Height.ToString();
            txtWidth.Text = _data.Width.ToString();
            ddlFitToSign.SelectedItem = _data.FitToSign;
            ddlSizeMode.SelectedItem = _data.SizeMode;
        }

        protected override void DoUpdateData()
        {
            _data.Height = Convert.ToInt32(txtHeight.Text);
            _data.Width = Convert.ToInt32(txtWidth.Text);
            _data.FitToSign =Boolean.Parse( ddlFitToSign.Text);
            //(SignType)Enum.Parse(typeof(SignType), ddlSignType.SelectedItem.ToString());
            _data.SizeModeType = (ImageSizeMode)Enum.Parse(typeof(ImageSizeMode), ddlSizeMode.SelectedItem.ToString());
        }
    }
}
