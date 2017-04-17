using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using DevExpress.XtraEditors;

namespace ProWrite.UI.Controls
{
    public partial class MonoColorDialog : DevExpress.XtraEditors.XtraForm
    {
        public MonoColorDialog()
        {
            InitializeComponent();
            //hslColorSlider1.SelectedHSLColor = new HSLColor(Color.FromArgb(255, 191, 63));//Color.Red);
        }

        public MonoColorDialog(Color color)
        {
            InitializeComponent();
            hslColorSlider1.SelectedHSLColor = new HSLColor(color);//Color.Red);
         }

        Color m_selectedColor = Color.Black;
        bool lockColorTable = false;
        private void hslColorSlider1_SelectedValueChanged(object sender, EventArgs e)
        {

            Color selcol = hslColorSlider1.SelectedHSLColor.Color;
            if (selcol != null && selcol != m_selectedColor)
            {
                m_selectedColor = selcol;
                m_colorSample.Refresh();
            }
            UpdateInfo();
        }
        void UpdateInfo()
        {
            Color c = Color.FromArgb((int)Math.Floor(255f * m_opacity), m_selectedColor);
            HSLColor selectedHSLColor = hslColorSlider1.SelectedHSLColor;
            txtBoxHue.Text = selectedHSLColor.Hue.ToString();
            txtBoxLum.Text = selectedHSLColor.Lightness.ToString();
            txtBoxSat.Text = selectedHSLColor.Saturation.ToString();
            txtBoxRed.Text = c.R.ToString();
            txtBoxGreen.Text = c.G.ToString();
            txtBoxBlue.Text = c.B.ToString();
            //string info = string.Format("{0} aRGB({1}, {2}, {3}, {4})", hslColorSlider1.SelectedHSLColor.ToString(), c.A, c.R, c.G, c.B);
            //m_infoLabel.Text = info;
        }
        float m_opacity = 1;
        private void labelRotate2_Paint(object sender, PaintEventArgs e)
        {
            Rectangle r = m_colorSample.ClientRectangle;
            r.Inflate(-4, -4);

            int width = r.Width;
            r.Width /= 2;

            Color c = Color.FromArgb((int)Math.Floor(255f * m_opacity), m_selectedColor);
            SolidBrush b = new SolidBrush(c);
            e.Graphics.FillRectangle(b, r);

            r.X += r.Width;

            e.Graphics.FillRectangle(Brushes.White, r);
            c = Color.FromArgb(255, m_selectedColor);
            b = new SolidBrush(c);
            e.Graphics.FillRectangle(b, r);

        }

        public Color Color { get { return Color.FromArgb((int) Math.Floor(255f*m_opacity), m_selectedColor); } }

        private void btnOk_Click(object sender, EventArgs e)
        {
            this.DialogResult = System.Windows.Forms.DialogResult.OK;
            this.Close();
        }

        private void btnCancel_Click(object sender, EventArgs e)
        {
            this.DialogResult = System.Windows.Forms.DialogResult.Cancel;
            this.Close();
        }

    }
}