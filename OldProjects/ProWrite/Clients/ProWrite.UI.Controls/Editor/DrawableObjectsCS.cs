using System;
using System.Drawing;
using System.Collections;
using System.Drawing.Drawing2D;
using System.Windows.Forms;
using DevExpress.XtraEditors;

namespace ProWrite.UI.Controls.Editor
{
    /// <summary>
    /// DrawableObjectsCS 的摘要说明。
    /// </summary>

    //基类
    public abstract class DShape
    {
        public abstract void Draw(Graphics g);
        protected Rectangle bounding;
        protected Point[] pointlist;
        public abstract void pointchange(Point[] p);
        public virtual GraphicsPath pathChange(GraphicsPath path, bool pick)
        {
            return null;
        }
        protected Color penColor;
        protected float penWidth;
    }

    //填充图形接口
    public interface IFillable
    {
        void Fill(Graphics g);
        Color FillBrushColor
        {
            get;
            set;
        }
    }

    //画点
    public class DPoint : DShape
    {
        public DPoint(Point[] p, Color penColor, float penWidth)
        {
            this.penColor = penColor;
            this.penWidth = penWidth;
            this.pointchange(p);
        }

        public override void pointchange(Point[] p)
        {
            pointlist = new Point[p.Length];
            int i = 0;
            foreach (Point tempPoint in p)
            {
                pointlist[i++] = tempPoint;
            }
            bounding = new Rectangle(pointlist[0], new Size((int)penWidth, (int)penWidth));
        }

        public override void Draw(Graphics g)
        {
            using (Pen p = new Pen(penColor, penWidth))
            {
                g.DrawRectangle(p, bounding);
                if (this.penWidth > 1)
                {
                    using (Brush b = new SolidBrush(penColor))
                    {
                        g.FillRectangle(b, bounding);
                    }
                }
            }
        }
    }

    //画线
    public class DLine : DShape
    {
        protected Point p1;
        protected Point p2;
        public DLine(Point[] p, Color penColor, float penWidth)
        {
            this.pointchange(p);
            this.penColor = penColor;
            this.penWidth = penWidth;
        }

        public override void pointchange(Point[] p)
        {
            pointlist = new Point[p.Length];
            int i = 0;
            foreach (Point tempPoint in p)
            {
                pointlist[i++] = tempPoint;
            }
            p1 = pointlist[0];
            p2 = pointlist[1];
        }

        public override void Draw(Graphics g)
        {
            using (Pen p = new Pen(penColor, penWidth))
            {
                g.DrawLine(p, p1, p2);
            }
        }
    }

    //路径
    public class DPLine : DShape
    {
        protected Point p1;
        protected Point p2;
        protected DashStyle style;
        protected System.Drawing.Drawing2D.LineCap scap;
        protected System.Drawing.Drawing2D.LineCap ecap;
        public DPLine(Point start, Point end, Color penColor, DashStyle style, System.Drawing.Drawing2D.LineCap scap, System.Drawing.Drawing2D.LineCap ecap)
        {
            p1 = start;
            p2 = end;
            this.penColor = penColor;
            this.style = style;
            this.scap = scap;
            this.ecap = ecap;
        }
        public override void pointchange(Point[] p)
        {
        }
        public override void Draw(Graphics g)
        {
            using (Pen p = new Pen(penColor))
            {
                p.DashStyle = style;
                p.StartCap = scap;
                p.EndCap = ecap;
                p.Width = 8;
                g.DrawLine(p, p1, p2);
            }
        }
    }


    //空心圆
    public class DHollowCircle : DShape
    {
        public DHollowCircle(Point[] p, Color penColor, float penWidth)
        {
            this.pointchange(p);
            this.penColor = penColor;
            this.penWidth = penWidth;
        }

        public override void pointchange(Point[] p)
        {
            this.pointlist = new Point[p.Length];
            int i = 0;
            foreach (Point tempPoint in p)
            {
                pointlist[i++] = tempPoint;
            }
            int Distance = (int)Math.Sqrt(Math.Pow((pointlist[0].X - pointlist[1].X), 2.0) + Math.Pow((pointlist[0].Y - pointlist[1].Y), 2.0));
            pointlist[0].Offset(-Distance, -Distance);
            int diameter = Distance * 2;
            bounding = new Rectangle(pointlist[0], new Size(diameter, diameter));
        }

        public override void Draw(Graphics g)
        {
            using (Pen p = new Pen(penColor, penWidth))
            {
                g.DrawEllipse(p, bounding);
            }
        }
    }

    //实心圆
    public class DFilledCircle : DHollowCircle, IFillable
    {
        protected Color brushColor;
        public DFilledCircle(Point[] p, Color penColor, float penWidth, Color brushColor)
            : base(p, penColor, penWidth)
        {
            this.brushColor = brushColor;
        }

        public void Fill(Graphics g)
        {
            using (Brush b = new SolidBrush(brushColor))
            {
                g.FillEllipse(b, bounding);
            }
        }
        public Color FillBrushColor
        {
            get
            {
                return brushColor;
            }
            set
            {
                brushColor = value;
            }
        }
        public override void Draw(Graphics g)
        {
            Fill(g);
            //base.Draw(g);
        }
    }

    //空心椭圆
    public class DHollowEllipse : DShape
    {
        public DHollowEllipse(Point[] p, Color penColor, float penWidth)
        {
            this.pointchange(p);
            this.penColor = penColor;
            this.penWidth = penWidth;
        }

        public override void pointchange(Point[] p)
        {
            pointlist = new Point[p.Length];
            int i = 0;
            foreach (Point tempPoint in p)
            {
                pointlist[i++] = tempPoint;
            }
            bounding = new Rectangle(pointlist[0], new Size(pointlist[1].X - pointlist[0].X, pointlist[1].Y - pointlist[0].Y));
        }
        public override void Draw(Graphics g)
        {
            using (Pen p = new Pen(penColor, penWidth))
            {
                g.DrawEllipse(p, bounding);
            }
        }
    }

    //实心椭圆
    public class DFilledEllipse : DHollowEllipse, IFillable
    {
        protected Color brushColor;
        public DFilledEllipse(Point[] p, Color penColor, float penWidth, Color brushColor)
            : base(p, penColor, penWidth)
        {
            this.brushColor = brushColor;
        }
        public void Fill(Graphics g)
        {
            using (Brush b = new SolidBrush(brushColor))
            {
                g.FillEllipse(b, bounding);
            }
        }
        public Color FillBrushColor
        {
            get
            {
                return brushColor;
            }
            set
            {
                brushColor = value;
            }
        }
        public override void Draw(Graphics g)
        {
            Fill(g);
            //base.Draw(g);
        }
    }

    //空心矩形
    public class DHollowRectangle : DHollowEllipse
    {
        public DHollowRectangle(Point[] p, Color penColor, float penWidth)
            : base(p, penColor, penWidth)
        {
        }
        public override void Draw(Graphics g)
        {
            using (Pen p = new Pen(penColor, penWidth))
            {
                g.DrawRectangle(p, bounding);
            }
        }
    }

    public class DPRectangle : DShape
    {
        protected DashStyle style;
        public DPRectangle(Rectangle rect, Color penColor, DashStyle style)
        {
            bounding = rect;
            this.penColor = penColor;
            this.style = style;
        }
        public override void pointchange(Point[] p)
        {
        }
        public override void Draw(Graphics g)
        {
            using (Pen p = new Pen(penColor))
            {
                p.DashStyle = style;
                g.DrawRectangle(p, bounding);
            }
        }
    }

    //实心矩形
    public class DFilledRectangle : DHollowRectangle, IFillable
    {
        protected Color brushColor;
        public DFilledRectangle(Point[] p, Color penColor, float penWidth, Color brushColor)
            : base(p, penColor, penWidth)
        {
            this.brushColor = brushColor;
        }
        public void Fill(Graphics g)
        {
            using (Brush b = new SolidBrush(brushColor))
            {
                g.FillRectangle(b, bounding);
            }
        }
        public Color FillBrushColor
        {
            get
            {
                return brushColor;
            }
            set
            {
                brushColor = value;
            }
        }
        public override void Draw(Graphics g)
        {
            Fill(g);
            //base.Draw(g);
        }
    }

    //画路径
    public class DPath : DShape
    {
        protected GraphicsPath Path;
        public DPath(GraphicsPath Path, Color penColor, float penWidth)
        {
            this.Path = Path;
            this.penColor = penColor;
            this.penWidth = penWidth;
        }
        public override void pointchange(Point[] p)
        {
        }
        public override GraphicsPath pathChange(GraphicsPath path, bool pick)
        {
            if (pick == true)
                return this.Path;
            else
            {
                this.Path = path;
                return null;
            }
        }
        public override void Draw(Graphics g)
        {
            using (Pen p = new Pen(penColor, penWidth))
            {
                g.DrawPath(p, Path);
            }
        }
        public GraphicsPath mousePath
        {
            get
            {

                return Path;
            }
        }
    }

    //橡皮擦
    public class DEraser : DShape
    {
        protected Region region;
        protected Color brushColor;
        public DEraser(Point p, Color brushColor, int Size)
        {
            p.Offset(-Size, -Size);
            bounding = new Rectangle(p, new Size(Size * 2, Size * 2));
            this.region = new Region(bounding); ;
            this.brushColor = brushColor;
        }
        public override void pointchange(Point[] p)
        {
        }
        public override void Draw(Graphics g)
        {
            using (Brush b = new SolidBrush(brushColor))
            {
                g.FillRegion(b, region);
            }
        }
    }

    //文本
    public class DText : DShape
    {
        protected Color brushColor;
        protected string Text;
        protected Font font;
        public DText(Point[] p, Color brushColor, string Text, Size size, Font font)
        {
            bounding = new Rectangle(p[0], size);
            this.brushColor = brushColor;
            this.Text = Text;
            this.font = font;
        }
        public override void pointchange(Point[] p)
        {
        }
        public override void Draw(Graphics g)
        {
            using (Brush b = new SolidBrush(brushColor))
            {
                g.DrawString(Text, font, b, bounding);
            }
        }
    }

    //画弧
    public class DArc : DHollowCircle
    {
        protected float angle1;
        protected float angle2;
        public DArc(Point[] p, Color penColor, float penWidth, float angle1, float angle2)
            : base(p, penColor, penWidth)
        {
            this.angle1 = angle1;
            this.angle2 = angle2;
        }
        public override void Draw(Graphics g)
        {
            using (Pen p = new Pen(penColor, penWidth))
            {
                g.DrawArc(p, bounding, angle1, angle2);
            }
        }
    }

    //画多边形
    public class DPolygon : DShape
    {
        public DPolygon(Point[] p, Color penColor, float penWidth)
        {
            this.pointchange(p);
            this.penColor = penColor;
            this.penWidth = penWidth;
        }
        public override void pointchange(Point[] p)
        {
            pointlist = new Point[p.Length];
            int i = 0;
            foreach (Point tempPoint in p)
            {
                pointlist[i++] = tempPoint;
            }
        }
        public override void Draw(Graphics g)
        {
            using (Pen p = new Pen(penColor, penWidth))
            {
                g.DrawPolygon(p, pointlist);
            }
        }
    }

    //基数样条
    public class DCurve : DPolygon
    {
        public DCurve(Point[] p, Color penColor, float penWidth)
            : base(p, penColor, penWidth)
        {
        }
        public override void Draw(Graphics g)
        {
            using (Pen p = new Pen(penColor, penWidth))
            {
                g.DrawCurve(p, pointlist);
            }
        }
    }

    //闭合样条
    public class DClosedCurve : DCurve
    {
        public DClosedCurve(Point[] p, Color penColor, float penWidth)
            : base(p, penColor, penWidth)
        {
        }
        public override void Draw(Graphics g)
        {
            using (Pen p = new Pen(penColor, penWidth))
            {
                g.DrawClosedCurve(p, pointlist);
            }
        }
    }

    //Beziers
    public class DBeziers : DPolygon
    {
        public DBeziers(Point[] p, Color penColor, float penWidth)
            : base(p, penColor, penWidth)
        {
        }
        public override void Draw(Graphics g)
        {
            using (Pen p = new Pen(penColor, penWidth))
            {
                g.DrawBeziers(p, pointlist);
            }
        }
    }

    public class DRegion : DShape
    {
        protected Region newRegion;
        public DRegion(GraphicsPath path)
        {
            newRegion = new Region(path);
        }
        public override void pointchange(Point[] p)
        {
        }
        public override void Draw(Graphics g)
        {
        }

        public Region region
        {
            get
            {
                return newRegion;
            }
        }
    }

    //图像
    public class DImage : DShape
    {
        protected Image image;
        public DImage(Point p, Image image)
        {
            bounding = new Rectangle(p, new Size(image.Width, image.Height));
            this.image = image;
        }
        public override void pointchange(Point[] p)
        {
        }
        public override void Draw(Graphics g)
        {
            g.DrawImage(image, bounding);
        }
    }

    //图形集合
    public class DShapeList : CollectionBase
    {
        DrawCollection wholeList = new DrawCollection();
        public new int Count
        {
            get
            {
                return wholeList.Count;
            }
        }

        public void Add(DShape d)
        {
            wholeList.Add(d);
        }

        public new void RemoveAt(int i)
        {
            wholeList.RemoveAt(i);
        }

        //索引器
        public DShape this[int newshapeIndex]
        {
            get
            {
                return (DShape)wholeList[newshapeIndex];
            }
            set
            {
                wholeList[newshapeIndex] = value;
            }
        }

        public void DrawList(Graphics g)
        {
            if (wholeList.Count != 0)
            {
                foreach (DShape d in wholeList)
                    d.Draw(g);
            }
        }
        //public IFillable[] GetFilledList() 
        //{
        //return (IFillable[])filledList.ToArray(typeof(IFillable));
        //}   
    }

    public class DrawCollection : CollectionBase
    {
        public void Add(DShape d)
        {
            List.Add(d);
        }

        public new void RemoveAt(int i)
        {
            List.RemoveAt(i);
        }
        public DShape this[int shapeIndex]
        {
            get
            {
                return (DShape)List[shapeIndex];
            }
            set
            {
                List[shapeIndex] = value;
            }
        }
    }
    public class NewRegion : CollectionBase
    {
        protected ProWrite.UI.Controls.Editor.EditPicture.ImageType newType;
        public Region this[int regionIndex]
        {
            get
            {
                return (Region)List[regionIndex];
            }
            set
            {
                List[regionIndex] = value;
            }
        }
        public void Add(Region newRegion)
        {
            List.Add(newRegion);
        }

        public new void RemoveAt(int i)
        {
            List.RemoveAt(i);
        }
        public void Remove(Region oldRegion)
        {
            List.Remove(oldRegion);
        }
        public NewRegion()
        {
        }
    }

    public class NewRegionArray : CollectionBase
    {
        public Region[] this[int regionIndex]
        {
            get
            {
                return (Region[])List[regionIndex];
            }
            set
            {
                List[regionIndex] = value;
            }
        }
        public void Add(Region[] newRegion)
        {
            List.Add(newRegion);
        }
        public void Remove(Region[] oldRegion)
        {
            List.Remove(oldRegion);
        }

        public new void RemoveAt(int i)
        {
            List.RemoveAt(i);
        }

        public NewRegionArray()
        {
        }
    }

    public class PointCollection : CollectionBase
    {
        public Point this[int pointIndex]
        {
            get
            {
                return (Point)List[pointIndex];
            }
            set
            {
                List[pointIndex] = value;
            }
        }
        public void Add(Point newPoint)
        {
            List.Add(newPoint);
        }
        public void RemoveRange(int x, int y)
        {
            for (int i = y - 1; i >= 0; i--)
            {
                List.RemoveAt(i);
            }
        }
        public void AddRange(Point[] point)
        {
            foreach (Point p in point)
            {
                List.Add(p);
            }
        }
        public PointCollection()
        {
        }
    }

    public class PointArrayCollection : CollectionBase
    {
        public Point[] this[int pointIndex]
        {
            get
            {
                return (Point[])List[pointIndex];
            }
            set
            {
                List[pointIndex] = value;
            }
        }
        public void Add(Point[] newPointArray)
        {
            List.Add(newPointArray);
        }
        public void RemoveRange(int x, int y)
        {
            for (int i = y - 1; i >= 0; i--)
            {
                List.RemoveAt(i);
            }
        }
        /*public void AddRange(Point[] point)
        {
            foreach(Point p in point)
            {
                List.Add(p);
            }
        } */
        public PointArrayCollection()
        {
        }
    }

    public class TypeI : CollectionBase
    {
        public int this[int intIndex]
        {
            get
            {
                return (int)List[intIndex];
            }
            set
            {
                List[intIndex] = value;
            }
        }
        public void Add(ProWrite.UI.Controls.Editor.EditPicture.ImageType type)
        {
            List.Add(type);
        }
        public new void RemoveAt(int i)
        {
            List.RemoveAt(i);
        }
    }
    public class Number : CollectionBase
    {
        public int this[int intIndex]
        {
            get
            {
                return (int)List[intIndex];
            }
            set
            {
                List[intIndex] = value;
            }
        }
        public void Add(int i)
        {
            List.Add(i);
        }
    }

    public class MousePoint
    {
        private Point pStart;
        private Point pEnd;
        private Point pRealStart;
        private Point pRealEnd;
        private Size pRealSize;
        private Rectangle pRect;
        private GraphicsPath pPath;
        public MousePoint(int X, int Y)
        {
            //
            // TODO: 在此处添加构造函数逻辑
            //
            pStart.X = X;
            pStart.Y = Y;
            pEnd.X = X;//Point.Empty;
            pEnd.Y = Y;
            pRealStart = Point.Empty;
            pRealEnd = Point.Empty;
            pRealSize = Size.Empty;
            pRect = Rectangle.Empty;
        }

        public int EndX
        {
            set
            {
                pEnd.X = value;
            }
            get
            {
                return pEnd.X;
            }
        }

        public int EndY
        {
            set
            {
                pEnd.Y = value;
            }
            get
            {
                return pEnd.Y;
            }
        }

        public Point StartP
        {
            get
            {
                //ChangeToReal();
                if (pRealStart == Point.Empty) return pStart;
                return pRealStart;
            }
            set
            {
                pRealStart = value;
            }
        }

        public Point EndP
        {
            get
            {
                //ChangeToReal();
                if (pRealEnd == Point.Empty) return pEnd;
                return pRealEnd;
            }
        }

        public Size newSize
        {
            get
            {
                return pRealSize;
            }
        }

        public Rectangle Rect
        {
            get
            {
                ChangeToReal();
                pRect.Location = pRealStart;
                pRect.Size = pRealSize;
                return pRect;
            }
        }

        public GraphicsPath Path
        {
            set
            {
                pPath = value;
            }
            get
            {
                return pPath;
            }
        }

        //矩形橡皮筋
        private void ChangeToReal()
        {
            //In first quadrant
            if ((pEnd.X > pStart.X) && (pEnd.Y > pStart.Y))
            {
                pRealStart = pStart;
                pRealEnd = pEnd;
                pRealSize = new Size(pRealEnd.X - pRealStart.X, pRealEnd.Y - pRealStart.Y);
                return;
            }

            //In second quadrant
            if ((pEnd.X < pStart.X) && (pEnd.Y < pStart.Y))
            {
                pRealEnd = pStart;
                pRealStart = pEnd;
                pRealSize = new Size(pRealEnd.X - pRealStart.X, pRealEnd.Y - pRealStart.Y);
                return;
            }

            //In third quadrant
            if ((pEnd.X < pStart.X) && (pEnd.Y > pStart.Y))
            {
                pRealStart.X = pEnd.X;
                pRealStart.Y = pStart.Y;
                pRealEnd.X = pStart.X;
                pRealEnd.Y = pEnd.Y;
                pRealSize = new Size(pRealEnd.X - pRealStart.X, pRealEnd.Y - pRealStart.Y);
                return;
            }

            //In forth quadrant
            if ((pEnd.X > pStart.X) && (pEnd.Y < pStart.Y))
            {
                pRealStart.X = pStart.X;
                pRealStart.Y = pEnd.Y;
                pRealEnd.X = pEnd.X;
                pRealEnd.Y = pStart.Y;
                pRealSize = new Size(pRealEnd.X - pRealStart.X, pRealEnd.Y - pRealStart.Y);
                return;
            }
        }
    }

    public static class ImageExtension
    {
        /// <summary>
        /// Crops an shape according to a selection rectangel
        /// </summary>
        /// <param name="shape">
        /// the shape to be cropped
        /// </param>
        /// <param name="selection">
        /// the selection
        /// </param>
        /// <returns>
        /// cropped shape
        /// </returns>
        public static Image Crop(this Image image, Rectangle selection)
        {
            Bitmap bmp = image as Bitmap;

            // Check if it is a bitmap:
            if (bmp == null)
                throw new ArgumentException("Kein gültiges Bild (Bitmap)");
            try
            {
                // Crop the shape:
                Bitmap cropBmp = bmp.Clone(selection, bmp.PixelFormat);

                // Release the resources:
                image.Dispose();

                return cropBmp;
            }
            catch
            { return null; }
        }
        //---------------------------------------------------------------------
        /// <summary>
        /// Fits an shape to the size of a picturebox
        /// </summary>
        /// <param name="shape">
        /// shape to be fit
        /// </param>
        /// <param name="picBox">
        /// picturebox in that the shape should fit
        /// </param>
        /// <returns>
        /// fitted shape
        /// </returns>
        /// <remarks>
        /// Although the picturebox has the SizeMode-property that offers
        /// the same functionality an OutOfMemory-Exception is thrown
        /// when assigning images to a picturebox several times.
        /// 
        /// AFAIK the SizeMode is designed for assigning an shape to
        /// picturebox only once.
        /// </remarks>
        public static Image Fit2PictureBox(this Image image, PictureEdit picBox)
        {
            if (image == null)
                return null;
            Bitmap bmp = null;
            Graphics g;

            // Scale:
            double scaleY = (double)image.Width / picBox.Width;
            double scaleX = (double)image.Height / picBox.Height;
            double scale = scaleY < scaleX ? scaleX : scaleY;

            // Create new bitmap:
            bmp = new Bitmap(
                (int)((double)image.Width / scale),
                (int)((double)image.Height / scale));

            // Set resolution of the new shape:
            bmp.SetResolution(
                image.HorizontalResolution,
                image.VerticalResolution);

            // Create graphics:
            g = Graphics.FromImage(bmp);

            // Set interpolation mode:
            g.InterpolationMode = InterpolationMode.HighQualityBicubic;

            // Draw the new shape:
            g.DrawImage(
                image,
                new Rectangle(			// Ziel
                    0, 0,
                    bmp.Width, bmp.Height),
                new Rectangle(			// Quelle
                    0, 0,
                    image.Width, image.Height),
                GraphicsUnit.Pixel);

            // Release the resources of the graphics:
            g.Dispose();

            // Release the resources of the origin shape:
            image.Dispose();

            return bmp;
        }

        public static Image Fit2PictureBox(this Image image, PictureEdit picBox, Point[] arr)
        {
            if (image == null)
                return null;
            Bitmap bmp = null;
            Graphics g;
            int width = arr[1].X - arr[0].X;
            int height = arr[1].Y - arr[0].Y;
            // Scale:
            double scaleY = (double)image.Width / picBox.Width;
            double scaleX = (double)image.Height / picBox.Height;
            double scale = scaleY < scaleX ? scaleX : scaleY;

            // Create new bitmap:
            bmp = new Bitmap(
                (int)((double)image.Width / scale),
                (int)((double)image.Height / scale));

            // Set resolution of the new image:
            bmp.SetResolution(
                image.HorizontalResolution,
                image.VerticalResolution);

            // Create graphics:
            g = Graphics.FromImage(bmp);

            // Set interpolation mode:
            g.InterpolationMode = InterpolationMode.HighQualityBicubic;
            //var arr = arry[0];

            g.DrawImage(
                           image,
                           new Rectangle(			// Ziel
                               arr[0].X, arr[0].Y,
                               width, height),
                           new Rectangle(			// Quelle
                               0, 0,
                               image.Width, image.Height),
                           GraphicsUnit.Pixel);

            // Draw the new image:
            //g.DrawImage(
            //    image,
            //    new Rectangle(			// Ziel
            //        0, 0,
            //        bmp.Width, bmp.Height),
            //    new Rectangle(			// Quelle
            //        0, 0,
            //        image.Width, image.Height),
            //    GraphicsUnit.Pixel);

            // Release the resources of the graphics:
            g.Dispose();

            // Release the resources of the origin image:
            image.Dispose();

            return bmp;
        }
    }
}
