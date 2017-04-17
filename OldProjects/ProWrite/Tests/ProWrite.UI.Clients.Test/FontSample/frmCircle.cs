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

        //使用矩阵缩放文字
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
            //减少缩放时产生的锯形
            //g.TextRenderingHint=TextRenderingHint.ClearTypeGridFit;
            //g.SmoothingMode=SmoothingMode.AntiAlias;
            MyPath = new GraphicsPath();
            MyFormat = new StringFormat();
            MyFamily = new FontFamily("宋体");
            //在路径中添加文本
            MyPath.AddString("1", MyFamily, (int)FontStyle.Regular, 50, new Point(0, 0), MyFormat);
            MyPoints = MyPath.PathPoints;
            
            MyTypes = MyPath.PathTypes;
            //定义在水平方向上压缩，在垂直方向上拉伸矩阵
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