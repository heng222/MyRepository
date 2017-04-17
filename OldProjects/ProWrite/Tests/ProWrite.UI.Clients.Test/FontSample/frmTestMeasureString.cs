using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace ProWrite.UI.Clients.Test.FontSample
{
    public partial class frmTestMeasureString : Form
    {
        public frmTestMeasureString()
        {
            InitializeComponent();
        }

        
        private void Font_MeasureString_Click(object sender, System.EventArgs e)
		{
			Graphics graphics=this.CreateGraphics();
			graphics.Clear(Color.White);

			//设置一个包含三行文本的字符串
			string txtOut="123456789\n";
			txtOut+="ABCDEFGHIJKLM\n";
			txtOut+="一二三四五六七八九";

			FontFamily   fontFamily=new FontFamily("Arial");
			//创建两个个大小不同的Aria字体
			Font  font=new Font(fontFamily, 30, FontStyle.Regular, GraphicsUnit.Pixel);
			Font  font2=new Font(fontFamily, 14, FontStyle.Regular, GraphicsUnit.Pixel);
			SolidBrush brush=new SolidBrush(Color.Black);

			StringFormat fmt=new StringFormat();
			fmt.Alignment=StringAlignment.Center;
			fmt.LineAlignment=StringAlignment.Center;

			SizeF stringSize = new SizeF();			
			//测量输出字符串所需要的矩形空间
			stringSize=graphics.MeasureString(txtOut,font);

			string tmp=string.Empty;
			tmp=string.Format("输出字符串所需要的宽度为:{0:F2}  高度为{1:F2}",
				stringSize.Width,stringSize.Height,font.Height);

			// 绘制输出文本的限制矩形
			graphics.DrawRectangle(new Pen(Color.Red),
				10.0f,10.0f,stringSize.Width,stringSize.Height);
			//输出字符串的测量信息
			graphics.DrawString(txtOut,font,brush,
				new RectangleF(10.0f,10.0f,stringSize.Width,stringSize.Height),fmt);
			graphics.TranslateTransform(0,10+stringSize.Height);
			graphics.DrawString(tmp,font2,brush,new PointF(0,0));
		}
    }
}