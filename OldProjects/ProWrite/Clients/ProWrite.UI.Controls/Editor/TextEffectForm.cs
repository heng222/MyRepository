using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Drawing.Text;
using System.Text;
using System.Windows.Forms;
using DevExpress.XtraEditors;
using ProWrite.Core;
using ProWrite.Entity.Shape;

namespace ProWrite.UI.Controls.Editor
{
	public partial class TextEffectForm : XtraForm
	{
		public TextEffect TextEffect { get; set;}
		private string _sampleText = "Text";
		public string SampleText
		{
			get { return _sampleText;}
			set { _sampleText = value;}
		}

		public TextEffectForm( TextEffect textEffect)
		{
			InitializeComponent();
			if(!DesignMode)
			{
				if(textEffect == null)
				{
					TextEffect = new TextEffect();
                    TextEffect.EffectColor = Color.Black;
					TextEffect.Effect = OutlineShadowType.NONE;
					TextEffect.OutlineWidth = 1;
					TextEffect.ShadowLateralShift = 1;
					TextEffect.ShadowVerticalShift = 1;
				}
				else
					this.TextEffect = textEffect;
			}
		}

		private void DrawString(Graphics graphics)
		{
			graphics.Clear(Color.White);
			//对文本使用去锯齿的边缘处理
			graphics.TextRenderingHint = TextRenderingHint.AntiAlias;

			using(FontFamily fontFamily = new FontFamily("Arial"))
            using (Font font = new Font(fontFamily, 100, FontStyle.Bold, GraphicsUnit.Pixel))
            {
                //文本输出框
                RectangleF textout = new RectangleF(font.Height,
                    pnlDrawText.Height / 2, pnlDrawText.Width, pnlDrawText.Height);

                //SolidBrush redBrush = new SolidBrush(Color.Red);
                Brush redBrush = Brushes.Red;

                switch (radGrpEffect.SelectedIndex)
                {
                    case 0:		//None
                        graphics.DrawString(_sampleText, font, redBrush, new Point(27, 27));
                        break;
                    case 1:		//Shadow
                        //draw shadow first
                        using (SolidBrush solidBrush = new SolidBrush(Color.FromArgb(100, Color.Black)))
                        {
                            graphics.DrawString(_sampleText, font, solidBrush, new Point(37, 37));
                            //draw text
                            graphics.DrawString(_sampleText, font, redBrush, new PointF(27, 27));
                        }
                        break;
                    case 2:		//Outline
                        using (GraphicsPath path = new GraphicsPath())
                        {
                            // Add a string
                            path.AddString(_sampleText, fontFamily, 1, font.Size, new PointF(27, 27), StringFormat.GenericDefault);
                            //Fill it 
                            graphics.FillPath(redBrush, path);
                            // Select the pen
                            using (Pen pen = new Pen(new SolidBrush(Color.Black), 4))
                            {
                                //outline it 
                                graphics.DrawPath(pen, path);
                                //g.DrawPath(&penOutline,&path);
                            }
                        }
                        break;
                }
            }
		}


		private void radGrpEffect_SelectedIndexChanged(object sender, EventArgs e)
		{
			switch(radGrpEffect.SelectedIndex)
			{
				case 0:		//None
					pnlColor.Visible = false;
					pnlOutline.Visible = false;
					pnlShadow.Visible = false;
					TextEffect.Effect = OutlineShadowType.NONE;
					break;
				case 1:		//Shadow
					pnlColor.Visible = true;
					pnlOutline.Visible = false;
					pnlShadow.Visible = true;
					pnlShadow.BringToFront();
                    TextEffect.Effect = OutlineShadowType.SHADED;
					break;
				case 2:		//Outline
					pnlColor.Visible = true;
					pnlOutline.Visible = true;
					pnlShadow.Visible = false;
					pnlOutline.BringToFront();
                    TextEffect.Effect = OutlineShadowType.OUTLINE; 
					break;
			}
			this.pnlDrawText.Invalidate();
		}

		private void TextEffectForm_Load(object sender, EventArgs e)
		{
			colorEdit.EditValue = this.TextEffect.EffectColor;
			radGrpEffect.SelectedIndex = TextEffect.EffectIndex;
			outlineWidth.Value = TextEffect.OutlineWidth;
			shadowEditLateral.Value = TextEffect.ShadowLateralShift;
			ShadowEditVertical.Value = TextEffect.ShadowVerticalShift;

		}

		private void pnlDrawText_Paint(object sender, PaintEventArgs e)
		{
			DrawString(e.Graphics);
		}

		private void colorEdit_EditValueChanged(object sender, EventArgs e)
		{
			TextEffect.EffectColor = (Color)colorEdit.EditValue;
		}

		private void shadowEditLateral_Properties_EditValueChanged(object sender, EventArgs e)
		{
			TextEffect.ShadowLateralShift = (int) shadowEditLateral.Value;
		}

		private void outlineEditTop_Properties_EditValueChanged(object sender, EventArgs e)
		{
			TextEffect.OutlineWidth = (int)outlineWidth.Value;
		}

		private void ShadowEditVertical_Properties_EditValueChanged(object sender, EventArgs e)
		{
			TextEffect.ShadowVerticalShift = (int) ShadowEditVertical.Value;
		}

		private void btnOK_Click(object sender, EventArgs e)
		{
			this.DialogResult = DialogResult.OK;
		}

		void btnCancel_Click(object sender, System.EventArgs e)
		{
			this.DialogResult = DialogResult.Cancel;
		}
	}
}