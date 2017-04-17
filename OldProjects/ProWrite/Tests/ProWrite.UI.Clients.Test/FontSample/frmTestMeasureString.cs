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

			//����һ�����������ı����ַ���
			string txtOut="123456789\n";
			txtOut+="ABCDEFGHIJKLM\n";
			txtOut+="һ�����������߰˾�";

			FontFamily   fontFamily=new FontFamily("Arial");
			//������������С��ͬ��Aria����
			Font  font=new Font(fontFamily, 30, FontStyle.Regular, GraphicsUnit.Pixel);
			Font  font2=new Font(fontFamily, 14, FontStyle.Regular, GraphicsUnit.Pixel);
			SolidBrush brush=new SolidBrush(Color.Black);

			StringFormat fmt=new StringFormat();
			fmt.Alignment=StringAlignment.Center;
			fmt.LineAlignment=StringAlignment.Center;

			SizeF stringSize = new SizeF();			
			//��������ַ�������Ҫ�ľ��οռ�
			stringSize=graphics.MeasureString(txtOut,font);

			string tmp=string.Empty;
			tmp=string.Format("����ַ�������Ҫ�Ŀ��Ϊ:{0:F2}  �߶�Ϊ{1:F2}",
				stringSize.Width,stringSize.Height,font.Height);

			// ��������ı������ƾ���
			graphics.DrawRectangle(new Pen(Color.Red),
				10.0f,10.0f,stringSize.Width,stringSize.Height);
			//����ַ����Ĳ�����Ϣ
			graphics.DrawString(txtOut,font,brush,
				new RectangleF(10.0f,10.0f,stringSize.Width,stringSize.Height),fmt);
			graphics.TranslateTransform(0,10+stringSize.Height);
			graphics.DrawString(tmp,font2,brush,new PointF(0,0));
		}
    }
}