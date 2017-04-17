using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using DevExpress.XtraEditors;

namespace ProWrite.UI.Clients.Test.FontSample
{
    public partial class frmMain : XtraForm
    {
        public frmMain()
        {
            InitializeComponent();
            trackBarNew1.lblInnerSlide.Visible = true;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            frmFontZoom0 frm = new frmFontZoom0();
            frm.Show();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            frmFontZoomAPI frm = new frmFontZoomAPI();
            frm.Show();
        }

        private void button3_Click(object sender, EventArgs e)
        {
            frmCircle frm = new frmCircle();
            frm.Show();
        }

        private void button4_Click(object sender, EventArgs e)
        {
            frmFontSize frm = new frmFontSize();
            frm.Show();
        }

        private void button5_Click(object sender, EventArgs e)
        {
            FormScrollBar frm = new FormScrollBar();
            frm.Show();
        }

        private void button6_Click(object sender, EventArgs e)
        {
            frmPictureBrowseAndConfig frm = new frmPictureBrowseAndConfig();
            frm.Show();
        }

        private void button7_Click(object sender, EventArgs e)
        {
            frmDrawArc frm = new frmDrawArc();
            frm.Show();
        }

        private void button8_Click(object sender, EventArgs e)
        {
            //Form12 frm = new Form12();
            //frm.Show();
        }

        private void button9_Click(object sender, EventArgs e)
        {
            //Form13 frm = new Form13();
            //frm.Show();
        }

        private void button10_Click(object sender, EventArgs e)
        {
            PrivateFontSample frm = new PrivateFontSample();
            frm.Show();
        }

        private void button11_Click(object sender, EventArgs e)
        {
            ProWriteFont frm = new ProWriteFont();
            frm.Show();
        }

        private void button12_Click(object sender, EventArgs e)
        {
            frmFontZoom1 frm = new frmFontZoom1();
            frm.Show();
        }

        private void button13_Click(object sender, EventArgs e)
        {
            frmFontZoom frm = new frmFontZoom();
            frm.Show();
        }

        private void button14_Click(object sender, EventArgs e)
        {
            frmFontZoom3 frm = new frmFontZoom3();
            frm.Show();
        }

        private void button15_Click(object sender, EventArgs e)
        {
            frmTestMeasureString frm = new frmTestMeasureString();
            frm.Show();
        }

        private void button16_Click(object sender, EventArgs e)
        {
            frmTextAutoSize frm = new frmTextAutoSize();
            frm.Show();
        }

        private void btnTextShadow_Click(object sender, EventArgs e)
        {
            frmTextShadow frm = new frmTextShadow();
            frm.Show();
        }

        private void btnFontBmpSample_Click(object sender, EventArgs e)
        {
            //frmFontBmpSample frm = new frmFontBmpSample();
            //frm.Show();
        }

        private void btnTextOutlineSample_Click(object sender, EventArgs e)
        {
            frmTextOutlineSample frm = new frmTextOutlineSample();
            frm.Show();
        }

        private void button17_Click(object sender, EventArgs e)
        {
            //frmTestDragDropPanel frm = new frmTestDragDropPanel();
            //frm.Show();
        }

        private void btnFont_Click(object sender, EventArgs e)
        {
            FontSelectForm frm = new FontSelectForm();
            //frm.Show();
        }

        private void btnProperty_Click(object sender, EventArgs e)
        {
            frmPropertyGridSample frm = new frmPropertyGridSample();
            frm.Show();
        }

        private void btnImage_Click(object sender, EventArgs e)
        {
            frmImageButton frm = new frmImageButton();
            frm.Show();
        }

        private void btnPanelControlResize_Click(object sender, EventArgs e)
        {
            frmPanelControlResize frm = new frmPanelControlResize();
            frm.Show();
        }
    }
}