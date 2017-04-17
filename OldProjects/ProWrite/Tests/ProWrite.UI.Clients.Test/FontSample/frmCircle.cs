using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Drawing.Drawing2D;

namespace ProWrite.UI.Clients.Test.FontSample
{
    public partial class frmCircle : Form
    {
        public frmCircle()
        {
            InitializeComponent();
        }

        //ʹ�þ�����������
        private void panel1_Paint(object sender, PaintEventArgs e)
        {
            Graphics g;
            SolidBrush MyBrush;
            StringFormat MyFormat;
            GraphicsPath MyPath;
            FontFamily MyFamily;
            PointF[] MyPoints;
            Byte[] MyTypes;
            GraphicsPath NewPath;
            Matrix MyMatrix;
            g = e.Graphics;
            g.Clear(Color.White);
            MyBrush = new SolidBrush(Color.Red);
            //��������ʱ�����ľ���
            //g.TextRenderingHint=TextRenderingHint.ClearTypeGridFit;
            //g.SmoothingMode=SmoothingMode.AntiAlias;
            MyPath = new GraphicsPath();
            MyFormat = new StringFormat();
            MyFamily = new FontFamily("����");
            //��·��������ı�
            MyPath.AddString("1", MyFamily, (int)FontStyle.Regular, 50, new Point(0, 0), MyFormat);
            MyPoints = MyPath.PathPoints;
            
            MyTypes = MyPath.PathTypes;
            //������ˮƽ������ѹ�����ڴ�ֱ�������������
            //MyMatrix = new Matrix((float)0.5, (float)0.0, (float)0.0, (float)3.5, (float)0.0, (float)0.0);

            RectangleF imageBounds = new RectangleF(0, 0, 75 * 10f, 75 * 10f);
            //MyMatrix = new Matrix(imageBounds, MyPoints);


            MyMatrix = new Matrix((float)15.0, (float)0.0, (float)0.0, (float)15.0, (float)0.0, (float)0.0);

            //MyMatrix.Rotate(90);
            //MyMatrix = new Matrix((float)18.5, (float)5.5, (float)5.5, (float)5.5, (float)5.5, (float)5.5);
            MyMatrix.TransformPoints(MyPoints);

            //MyMatrix.TransformVectors(MyPoints);
            
            NewPath = new GraphicsPath(MyPoints, MyTypes);
            g.FillPath(MyBrush, NewPath);

            
        }
    }
}