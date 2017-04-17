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
    public partial class frmTextOutlineSample : Form
    {
        public frmTextOutlineSample()
        {
            InitializeComponent();
        }

        private void TextHaloEffectView()
        {
            //Text
            string text = "ABC";
            //Font
            FontFamily fontFamily = new FontFamily("Arial");
            Font font = new Font(fontFamily, 100, FontStyle.Bold, GraphicsUnit.Pixel);

            //Graphics
            Graphics g = CreateGraphics();
            g.Clear(Color.Black);

            //客户区大小
        Rectangle clientRect = ClientRectangle;
        Size clientSize = ClientSize;     
                    
        RectangleF clientRectF = new RectangleF((float)clientRect.X,(float)clientRect.Y,(float)clientRect.Width,(float)clientRect.Height);
        SolidBrush brush = new SolidBrush(Color.Black);
            g.FillRectangle(brush,clientRectF);
            Image bitmap = new Bitmap(clientSize.Width/5,clientSize.Height/5,g);           

            //创建文字路径 
        GraphicsPath gPath = new GraphicsPath();
        //Add the string in the chosen style. 
        int style = (int)FontStyle.Regular;
        Point point = new Point(20,20);
            float emHeight = 100;
            StringFormat format = StringFormat.GenericDefault;
            
            //gPath.AddString(L"文字光圈",-1,&FontFamily(L"宋体"),style,100,Point(20,20),NULL);
            gPath.AddString(text,font.FontFamily,style,emHeight,point,format);
            //位图Graphics
            Graphics bmpg = Graphics.FromImage(bitmap);
            //Create a matrix that shrinks the drawing output by the fixed ratio. 
            //Matrix mx(1.0f/5,0,0,1.0f/5,-(1.0f/5),-(1.0f/5));
            Matrix mx = new Matrix(1.0f / 5, 0, 0, 1.0f / 5, -(1.0f / 5), -(1.0f / 5));
            PointF[] MyPoints;
            //Choose an appropriate smoothing mode for the halo. 
            bmpg.SmoothingMode = SmoothingMode.AntiAlias;// -SetSmoothingMode(SmoothingModeAntiAlias);
            //Transform the graphics object so that the same half may be used for both halo and text output. 
        
            //变换为位图的1/5，放大后将和实际文本相仿
            //bmpg-SetTransform(&mx);
            //MyPoints = gPath.PathPoints;

            //mx.TransformPoints(MyPoints);

            bmpg.TranslateTransform(1.0f / 5, 1.0f / 5);
            //bmpg.ScaleTransform(1.0f / 5,1.0f / 5);
            //Using a suitable pen...
            //Pen p(Color::Yellow,3);
            Pen p = new Pen(Color.Yellow,3);
            //Draw around the outline of the path
            //bmpg-DrawPath(&p,&gPath);
            bmpg.DrawPath(p,gPath);
            //and then fill in for good measure. 
            //bmpg-FillPath(&SolidBrush(Color::Yellow),&gPath);
            SolidBrush brush1 = new SolidBrush(Color.Yellow);
            bmpg.FillPath(brush1,gPath);
            //this just shifts the effect a little bit so that the edge isn''t cut off in the demonstration 
            //移动50，50
            //g.SetTransform(&Matrix(1,0,0,1,50,50));
            bmpg.TranslateTransform(5, 5);
            //setup the smoothing mode for path drawing
            //g.SetSmoothingMode(SmoothingModeAntiAlias);
            g.SmoothingMode = SmoothingMode.AntiAlias;
            //and the interpolation mode for the expansion of the halo bitmap 
            //g.SetInterpolationMode(InterpolationModeHighQualityBicubic);
            g.SmoothingMode = SmoothingMode.HighQuality;
            //expand the halo making the edges nice and fuzzy. 
            //g.DrawImage(&bm,ClientRectangle,0,0,bm.GetWidth(),bm.GetHeight(),UnitPixel);
            g.DrawImage(bitmap, clientRect, 0, 0, bitmap.Width, bitmap.Height, GraphicsUnit.Pixel);
            //Redraw the original text 
            //g.FillPath(&SolidBrush(Color::Black),&gPath);
            g.FillPath(brush, gPath);
            //and you''re done. 

        }

        private void TextHaloEffectView1()
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
            string text = "ABC";
            g = CreateGraphics();
            g.Clear(Color.White);
            MyBrush = new SolidBrush(Color.Red);
            //减少缩放时产生的锯形
            //g.TextRenderingHint=TextRenderingHint.ClearTypeGridFit;
            //g.SmoothingMode=SmoothingMode.AntiAlias;
            MyPath = new GraphicsPath();
            MyFormat = new StringFormat();
			MyFamily = new FontFamily("");
            //在路径中添加文本
            MyPath.AddString(text, MyFamily, (int)FontStyle.Regular, 30, new Point(0, 0), MyFormat);
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

        private void TextHaloEffectView2()
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
            string text = "ABC";
            g = CreateGraphics();
            g.Clear(Color.White);
            
            //客户区大小
            Rectangle clientRect = ClientRectangle;
            Size clientSize = ClientSize;

            RectangleF clientRectF = new RectangleF((float)clientRect.X, (float)clientRect.Y, (float)clientRect.Width, (float)clientRect.Height);
            SolidBrush brush = new SolidBrush(Color.Black);
            g.FillRectangle(brush, clientRectF);

            Image bitmap = new Bitmap(clientSize.Width / 5, clientSize.Height / 5, g);

            //创建文字路径 
            MyBrush = new SolidBrush(Color.Red);
            //减少缩放时产生的锯形
            //g.TextRenderingHint=TextRenderingHint.ClearTypeGridFit;
            //g.SmoothingMode=SmoothingMode.AntiAlias;
            MyPath = new GraphicsPath();
            MyFormat = new StringFormat();
            MyFamily = new FontFamily("");
            //在路径中添加文本
            MyPath.AddString(text, MyFamily, (int)FontStyle.Regular, 100, new Point(0, 0), MyFormat);
            MyPoints = MyPath.PathPoints;

            MyTypes = MyPath.PathTypes;
            //位图Graphics
            Graphics bmpg = Graphics.FromImage(bitmap);
            //Create a matrix that shrinks the drawing output by the fixed ratio. 
            //Matrix mx(1.0f/5,0,0,1.0f/5,-(1.0f/5),-(1.0f/5));
            Matrix mx = new Matrix(1.0f / 5, 0, 0, 1.0f / 5, -(1.0f / 5), -(1.0f / 5));
            //Choose an appropriate smoothing mode for the halo. 
            bmpg.SmoothingMode = SmoothingMode.AntiAlias;// -SetSmoothingMode(SmoothingModeAntiAlias);
            //Transform the graphics object so that the same half may be used for both halo and text output. 

            //变换为位图的1/5，放大后将和实际文本相仿
            mx.TransformPoints(MyPoints);

            bmpg.TranslateTransform(1.0f / 5, 1.0f / 5);
            //bmpg.ScaleTransform(1.0f / 5,1.0f / 5);
            //Using a suitable pen...
            //Pen p(Color::Yellow,3);
            Pen p = new Pen(Color.Yellow, 3);
            //Draw around the outline of the path
            //bmpg-DrawPath(&p,&gPath);
            bmpg.DrawPath(p, MyPath);
            //and then fill in for good measure. 
            //bmpg-FillPath(&SolidBrush(Color::Yellow),&gPath);
            SolidBrush brush1 = new SolidBrush(Color.Yellow);
            bmpg.FillPath(brush1, MyPath);
            MyPoints = MyPath.PathPoints;
            //变换为位图的1/5，放大后将和实际文本相仿
            mx.TransformPoints(MyPoints);
            //this just shifts the effect a little bit so that the edge isn''t cut off in the demonstration 
            //移动50，50
            //g.SetTransform(&Matrix(1,0,0,1,50,50));
            bmpg.TranslateTransform(50, 50);
            //setup the smoothing mode for path drawing
            //g.SetSmoothingMode(SmoothingModeAntiAlias);
            g.SmoothingMode = SmoothingMode.AntiAlias;
            //and the interpolation mode for the expansion of the halo bitmap 
            //g.SetInterpolationMode(InterpolationModeHighQualityBicubic);
            g.SmoothingMode = SmoothingMode.HighQuality;
            //expand the halo making the edges nice and fuzzy. 
            //g.DrawImage(&bm,ClientRectangle,0,0,bm.GetWidth(),bm.GetHeight(),UnitPixel);
            g.DrawImage(bitmap, clientRect, 0, 0, bitmap.Width, bitmap.Height, GraphicsUnit.Pixel);
            //Redraw the original text 
            //g.FillPath(&SolidBrush(Color::Black),&gPath);
            g.FillPath(brush, MyPath);

            MyPoints = MyPath.PathPoints;
            //变换为位图的1/5，放大后将和实际文本相仿
            mx.TransformPoints(MyPoints);
            //this just shifts the effect a little bit so that the edge isn''t cut off in the demonstration 
            //移动50，50
            //g.SetTransform(&Matrix(1,0,0,1,50,50));
            bmpg.TranslateTransform(50, 50);
            //setup the smoothing mode for path drawing
            //g.SetSmoothingMode(SmoothingModeAntiAlias);
            g.SmoothingMode = SmoothingMode.AntiAlias;
            //and the interpolation mode for the expansion of the halo bitmap 
            //g.SetInterpolationMode(InterpolationModeHighQualityBicubic);
            g.SmoothingMode = SmoothingMode.HighQuality;
            //expand the halo making the edges nice and fuzzy. 
            //g.DrawImage(&bm,ClientRectangle,0,0,bm.GetWidth(),bm.GetHeight(),UnitPixel);

            g.DrawImage(bitmap, clientRect, 50, 50, bitmap.Width, bitmap.Height, GraphicsUnit.Pixel);
            //and you''re done. 

        }

        /// <summary>
        /// Create the outline geometry based on the formatted text.
        /// </summary>
        public void CreateText()
        {
            //FontStyle fontStyle = FontStyles.Normal;
            //FontWeight fontWeight = FontWeights.Medium;

            //if (Bold == true) fontWeight = FontWeights.Bold;
            //if (Italic == true) fontStyle = FontStyles.Italic;

            //// Create the formatted text based on the properties set.
            //FormattedText formattedText = new FormattedText(
            //    Text,
            //    CultureInfo.GetCultureInfo("en-us"),
            //    FlowDirection.LeftToRight,
            //    new Typeface(
            //        Font,
            //        fontStyle,
            //        fontWeight,
            //        FontStretches.Normal),
            //    FontSize,
            //    Brushes.Black // This brush does not matter since we use the geometry of the text. 
            //    );

            //// Build the geometry object that represents the text.
            //_textGeometry = formattedText.BuildGeometry(new Point(0, 0));

            //// Build the geometry object that represents the text hightlight.
            //if (Highlight == true)
            //{
            //    _textHighLightGeometry = formattedText.BuildHighlightGeometry(new Point(0, 0));
            //}
        }

        /// <summary>
        /// OnRender override draws the geometry of the text and optional highlight.
        /// </summary>
        /// <param name="drawingContext">Drawing context of the OutlineText control.</param>
        //protected override void OnRender(DrawingContext drawingContext)
        //{
        //    // Draw the outline based on the properties that are set.
        //    drawingContext.DrawGeometry(Fill, new Pen(Stroke, StrokeThickness), _textGeometry);

        //    // Draw the text highlight based on the properties that are set.
        //    if (Highlight == true)
        //    {
        //        drawingContext.DrawGeometry(null, new Pen(Stroke, StrokeThickness), _textHighLightGeometry);
        //    }
        //}


        private void frmTextOutlineSample_Load(object sender, EventArgs e)
        {

        }

        private void frmTextOutlineSample_Paint(object sender, PaintEventArgs e)
        {
            TextHaloEffectView2();
        }
    }
}