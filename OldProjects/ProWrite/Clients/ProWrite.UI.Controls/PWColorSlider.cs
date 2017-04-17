using System;
using System.Collections.Generic;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using DevExpress.XtraEditors;

namespace ProWrite.UI.Controls
{
    public class PWColorSlider : ColorSlider
    {

        HSLColor m_selectedColor = new HSLColor();
        public HSLColor SelectedHSLColor
        {
            get
            {
                if (Color2 == Color.White)
                    m_selectedColor.Lightness = Percent;
                else
                    m_selectedColor.Lightness = Percent / 2;
                return m_selectedColor;
            }
            set
            {
                if (m_selectedColor == value)
                    return;
                m_selectedColor = value;
                value.Lightness = 0.5;
                Color2 = Color.FromArgb(255, value.Color);
                //Percent = (float)m_selectedColor.Lightness ;
                Percent = (float)m_selectedColor.Lightness * 2;
                Refresh();//Invalidate(Util.Rect(BarRectangle));
            }
        }

        protected override void SetPercent(PointF mousepoint)
        {
            base.SetPercent(mousepoint);
            //m_selectedColor.Lightness = Percent ;
            m_selectedColor.Lightness = Percent / 2;
            Refresh();
        }
        protected override void SetPercent(float percent)
        {
            base.SetPercent(percent);
            m_selectedColor.Lightness = percent / 100;
            SelectedHSLColor = m_selectedColor;
        }
    }

    public class ColorSlider : LabelRotate
    {
        public event EventHandler SelectedValueChanged;
        Orientation m_orientation = Orientation.Vertical;
        public Orientation Orientation
        {
            get { return m_orientation; }
            set { m_orientation = value; }
        }

        public enum eNumberOfColors
        {
            Use2Colors,
            Use3Colors,
        }
        eNumberOfColors m_numberOfColors = eNumberOfColors.Use2Colors;
        public eNumberOfColors NumberOfColors
        {
            get { return m_numberOfColors; }
            set { m_numberOfColors = value; }
        }
        public enum eValueOrientation
        {
            MinToMax,
            MaxToMin,
        }
        eValueOrientation m_valueOrientation = eValueOrientation.MinToMax;
        public eValueOrientation ValueOrientation
        {
            get { return m_valueOrientation; }
            set { m_valueOrientation = value; }
        }
        float m_percent = 0;
        public float Percent
        {
            get { return m_percent; }
            set
            {
                // ok so it is not really percent, but a value between 0 - 1.
                if (value < 0) value = 0;
                if (value > 1) value = 1;
                if (value != m_percent)
                {
                    m_percent = value;
                    if (SelectedValueChanged != null)
                        SelectedValueChanged(this, null);
                    Invalidate();
                }

            }
        }

        Color m_color1 = Color.Black;
        Color m_color2 = Color.FromArgb(255, 127, 127, 127);
        Color m_color3 = Color.White;
        public Color Color1
        {
            get { return m_color1; }
            set { m_color1 = value; }
        }
        public Color Color2
        {
            get { return m_color2; }
            set { m_color2 = value; }
        }
        public Color Color3
        {
            get { return m_color3; }
            set { m_color3 = value; }
        }

        Padding m_barPadding = new Padding(12, 5, 24, 10);
        public Padding BarPadding
        {
            get { return m_barPadding; }
            set
            {
                m_barPadding = value;
                Invalidate();
            }
        }

        public ColorSlider()
        {
        }

        protected override void OnGotFocus(EventArgs e)
        {
            base.OnGotFocus(e);
            Invalidate();
        }
        protected override void OnLostFocus(EventArgs e)
        {
            base.OnLostFocus(e);
            Invalidate();
        }
        protected override void OnPaint(PaintEventArgs e)
        {
            base.OnPaint(e);
            DrawColorBar(e.Graphics);

            if (Focused)
            {
                RectangleF lr = ClientRectangleF;
                lr.Inflate(-2, -2);
                ControlPaint.DrawFocusRectangle(e.Graphics, Util.Rect(lr));
            }
        }
        protected override void OnMouseMove(MouseEventArgs e)
        {
            base.OnMouseMove(e);
            PointF mousepoint = new PointF(e.X, e.Y);
            if (e.Button == MouseButtons.Left)
                SetPercent(mousepoint);
        }
        protected override void OnMouseDown(MouseEventArgs e)
        {
            base.OnMouseDown(e);
            Focus();
            PointF mousepoint = new PointF(e.X, e.Y);
            if (e.Button == MouseButtons.Left)
                SetPercent(mousepoint);
        }
        protected override bool ProcessDialogKey(Keys keyData)
        {
            float percent = Percent * 100;
            int step = 0;
            if ((keyData & Keys.Up) == Keys.Up)
                step = 1;
            if ((keyData & Keys.Down) == Keys.Down)
                step = -1;
            if ((keyData & Keys.Control) == Keys.Control)
                step *= 5;
            if (step != 0)
            {
                SetPercent((float)Math.Round(percent + step));
                return true;
            }
            return base.ProcessDialogKey(keyData);
        }
        protected virtual void SetPercent(float percent)
        {
            Percent = percent / 100;
        }
        protected virtual void SetPercent(PointF mousepoint)
        {
            RectangleF cr = ClientRectangleF;
            RectangleF br = BarRectangle;
            mousepoint.X += cr.X - br.X;
            mousepoint.Y += cr.Y - br.Y;
            Percent = GetPercentSet(BarRectangle, Orientation, mousepoint);
            Refresh();
        }
        protected RectangleF BarRectangle
        {
            get
            {
                RectangleF r = ClientRectangle;
                r.X += BarPadding.Left;
                r.Width -= BarPadding.Right;
                r.Y += BarPadding.Top;
                r.Height -= BarPadding.Bottom;
                return r;
            }
        }
        protected float GetPercentSet(RectangleF r, Orientation orientation, PointF mousepoint)
        {
            float percentSet = 0;
            if (orientation == Orientation.Vertical)
            {
                if (m_valueOrientation == eValueOrientation.MaxToMin)
                    percentSet = 1 - ((mousepoint.Y - r.Y / r.Height) / r.Height);
                else
                    percentSet = mousepoint.Y / r.Height;
            }
            if (orientation == Orientation.Horizontal)
                if (m_valueOrientation == eValueOrientation.MaxToMin)
                    percentSet = 1 - ((mousepoint.X - r.X / r.Width) / r.Width);
                else
                    percentSet = (mousepoint.X / r.Width);
            if (percentSet < 0)
                percentSet = 0;
            if (percentSet > 100)
                percentSet = 100;
            return percentSet;
        }
        protected void DrawSelector(Graphics dc, RectangleF r, Orientation orientation, float percentSet)
        {
            Pen pen = new Pen(Color.CadetBlue);
            percentSet = Math.Max(0, percentSet);
            percentSet = Math.Min(1, percentSet);
            if (orientation == Orientation.Vertical)
            {
                float selectorY = (float)Math.Floor(r.Top + (r.Height - (r.Height * percentSet)));
                if (m_valueOrientation == eValueOrientation.MaxToMin)
                    selectorY = (float)Math.Floor(r.Top + (r.Height - (r.Height * percentSet)));
                else
                    selectorY = (float)Math.Floor(r.Top + (r.Height * percentSet));

                dc.DrawLine(pen, r.X, selectorY, r.Right, selectorY);

                Image image = SelectorImages.Image(SelectorImages.eIndexes.Right);
                float xpos = r.Right;
                float ypos = selectorY - image.Height / 2;
                dc.DrawImageUnscaled(image, (int)xpos, (int)ypos);

                image = SelectorImages.Image(SelectorImages.eIndexes.Left);
                xpos = r.Left - image.Width;
                dc.DrawImageUnscaled(image, (int)xpos, (int)ypos);
            }
            if (orientation == Orientation.Horizontal)
            {
                float selectorX = 0;
                if (m_valueOrientation == eValueOrientation.MaxToMin)
                    selectorX = (float)Math.Floor(r.Left + (r.Width - (r.Width * percentSet)));
                else
                    selectorX = (float)Math.Floor(r.Left + (r.Width * percentSet));

                dc.DrawLine(pen, selectorX, r.Top, selectorX, r.Bottom);

                Image image = SelectorImages.Image(SelectorImages.eIndexes.Up);
                float xpos = selectorX - image.Width / 2;
                float ypos = r.Bottom;
                dc.DrawImageUnscaled(image, (int)xpos, (int)ypos);

                image = SelectorImages.Image(SelectorImages.eIndexes.Down);
                ypos = r.Top - image.Height;
                dc.DrawImageUnscaled(image, (int)xpos, (int)ypos);
            }
        }
        protected void DrawColorBar(Graphics dc)
        {
            RectangleF lr = BarRectangle;
            if (m_numberOfColors == eNumberOfColors.Use2Colors)
                Util.Draw2ColorBar(dc, lr, Orientation, m_color1, m_color2);
            else
                Util.Draw3ColorBar(dc, lr, Orientation, m_color1, m_color2, m_color3);
            DrawSelector(dc, lr, Orientation, (float)Percent);
        }
    }

    public class LabelRotate : XtraUserControl
    {
        float m_textAngle = 0;
        ContentAlignment m_rotatePointAlignment = ContentAlignment.MiddleCenter;
        ContentAlignment m_textAlignment = ContentAlignment.MiddleLeft;

        public new string Text
        {
            get { return base.Text; }
            set
            {
                base.Text = value;
                Refresh();
            }
        }
        public float TextAngle
        {
            get { return m_textAngle; }
            set
            {
                m_textAngle = value;
                Invalidate();
            }
        }
        public ContentAlignment TextAlign
        {
            get { return m_textAlignment; }
            set
            {
                m_textAlignment = value;
                Invalidate();
            }
        }
        public ContentAlignment RotatePointAlignment
        {
            get { return m_rotatePointAlignment; }
            set
            {
                m_rotatePointAlignment = value;
                Invalidate();
            }
        }

        Color m_frameColor = Color.CadetBlue;
        public LabelRotate()
        {
            SetStyle(ControlStyles.SupportsTransparentBackColor, true);
            this.Text = string.Empty;
            this.DoubleBuffered = true;
            this.SetStyle(ControlStyles.OptimizedDoubleBuffer | ControlStyles.UserPaint, true);
        }
        protected override void OnPaint(PaintEventArgs e)
        {
            using (SolidBrush b = new SolidBrush(BackColor))
            {
                e.Graphics.FillRectangle(b, ClientRectangle);
            }

            RectangleF lr = ClientRectangleF;
            Pen framepen = new Pen(m_frameColor, 1);
            Util.DrawFrame(e.Graphics, lr, 6, m_frameColor);
            if (Text.Length > 0)
            {
                StringFormat format = new StringFormat();
                string alignment = TextAlign.ToString();

                if (((int)TextAlign & (int)(ContentAlignment.BottomLeft | ContentAlignment.MiddleLeft | ContentAlignment.TopLeft)) != 0)
                    format.Alignment = StringAlignment.Near;

                if (((int)TextAlign & (int)(ContentAlignment.BottomCenter | ContentAlignment.MiddleCenter | ContentAlignment.TopCenter)) != 0)
                    format.Alignment = StringAlignment.Center;

                if (((int)TextAlign & (int)(ContentAlignment.BottomRight | ContentAlignment.MiddleRight | ContentAlignment.TopRight)) != 0)
                    format.Alignment = StringAlignment.Far;

                if (((int)TextAlign & (int)(ContentAlignment.BottomLeft | ContentAlignment.BottomCenter | ContentAlignment.BottomRight)) != 0)
                    format.LineAlignment = StringAlignment.Far;

                if (((int)TextAlign & (int)(ContentAlignment.MiddleLeft | ContentAlignment.MiddleCenter | ContentAlignment.MiddleRight)) != 0)
                    format.LineAlignment = StringAlignment.Center;

                if (((int)TextAlign & (int)(ContentAlignment.TopLeft | ContentAlignment.TopCenter | ContentAlignment.TopRight)) != 0)
                    format.LineAlignment = StringAlignment.Near;

                Rectangle r = ClientRectangle;
                r.X += Padding.Left;
                r.Y += Padding.Top;
                r.Width -= Padding.Right;
                r.Height -= Padding.Bottom;

                using (SolidBrush b = new SolidBrush(ForeColor))
                {
                    if (TextAngle == 0)
                    {
                        e.Graphics.DrawString(Text, Font, b, r, format);
                    }
                    else
                    {
                        PointF center = Util.Center(ClientRectangle);
                        switch (RotatePointAlignment)
                        {
                            case ContentAlignment.TopLeft:
                                center.X = r.Left;
                                center.Y = r.Top;
                                break;
                            case ContentAlignment.TopCenter:
                                center.Y = r.Top;
                                break;
                            case ContentAlignment.TopRight:
                                center.X = r.Right;
                                center.Y = r.Top;
                                break;
                            case ContentAlignment.MiddleLeft:
                                center.X = r.Left;
                                break;
                            case ContentAlignment.MiddleCenter:
                                break;
                            case ContentAlignment.MiddleRight:
                                center.X = r.Right;
                                break;
                            case ContentAlignment.BottomLeft:
                                center.X = r.Left;
                                center.Y = r.Bottom;
                                break;
                            case ContentAlignment.BottomCenter:
                                center.Y = r.Bottom;
                                break;
                            case ContentAlignment.BottomRight:
                                center.X = r.Right;
                                center.Y = r.Bottom;
                                break;
                        }
                        center.X += Padding.Left;
                        center.Y += Padding.Top;
                        center.X -= Padding.Right;
                        center.Y -= Padding.Bottom;

                        e.Graphics.TranslateTransform(center.X, center.Y);
                        e.Graphics.RotateTransform(TextAngle);

                        e.Graphics.DrawString(Text, Font, b, new PointF(0, 0), format);
                        e.Graphics.ResetTransform();
                    }
                }
            }
            RaisePaintEvent(this, e);
        }
        protected RectangleF ClientRectangleF
        {
            get
            {
                RectangleF r = ClientRectangle;
                r.Width -= 1;
                r.Height -= 1;
                return r;
            }
        }

    }

    public struct HSLColor
    {
        double m_hue;
        double m_saturation;
        double m_lightness;
        // http://en.wikipedia.org/wiki/HSL_color_space

        public double Hue
        {
            get { return m_hue; }
            set { m_hue = value; }
        }
        public double Saturation
        {
            get { return m_saturation; }
            set { m_saturation = value; }
        }
        public double Lightness
        {
            get { return m_lightness; }
            set
            {
                m_lightness = value;
                if (m_lightness < 0)
                    m_lightness = 0;
                if (m_lightness > 1)
                    m_lightness = 1;
            }
        }
        public HSLColor(double hue, double saturation, double lightness)
        {
            m_hue = Math.Min(360, hue);
            m_saturation = Math.Min(1, saturation);
            m_lightness = Math.Min(1, lightness);
        }
        public HSLColor(Color color)
        {
            m_hue = 0;
            m_saturation = 1;
            m_lightness = 1;
            FromRGB(color);
        }
        public Color Color
        {
            get { return ToRGB(); }
            set { FromRGB(value); }
        }
        void FromRGB(Color cc)
        {
            double r = (double)cc.R / 255d;
            double g = (double)cc.G / 255d;
            double b = (double)cc.B / 255d;

            double min = Math.Min(Math.Min(r, g), b);
            double max = Math.Max(Math.Max(r, g), b);
            // calulate hue according formula given in
            // "Conversion from RGB to HSL or HSV"
            m_hue = 0;
            if (min != max)
            {
                if (r == max && g >= b)
                {
                    m_hue = 60 * ((g - b) / (max - min)) + 0;
                }
                else
                    if (r == max && g < b)
                    {
                        m_hue = 60 * ((g - b) / (max - min)) + 360;
                    }
                    else
                        if (g == max)
                        {
                            m_hue = 60 * ((b - r) / (max - min)) + 120;
                        }
                        else
                            if (b == max)
                            {
                                m_hue = 60 * ((r - g) / (max - min)) + 240;
                            }
            }
            // find lightness
            m_lightness = (min + max) / 2;

            // find saturation
            if (m_lightness == 0 || min == max)
                m_saturation = 0;
            else
                if (m_lightness > 0 && m_lightness <= 0.5)
                    m_saturation = (max - min) / (2 * m_lightness);
                else
                    if (m_lightness > 0.5)
                        m_saturation = (max - min) / (2 - 2 * m_lightness);
        }
        Color ToRGB()
        {
            // convert to RGB according to
            // "Conversion from HSL to RGB"

            double r = m_lightness;
            double g = m_lightness;
            double b = m_lightness;
            if (m_saturation == 0)
                return Color.FromArgb(255, (int)(r * 255), (int)(g * 255), (int)(b * 255));

            double q = 0;
            if (m_lightness < 0.5)
                q = m_lightness * (1 + m_saturation);
            else
                q = m_lightness + m_saturation - (m_lightness * m_saturation);
            double p = 2 * m_lightness - q;
            double hk = m_hue / 360;

            // r,g,b colors
            double[] tc = new double[3] { hk + (1d / 3d), hk, hk - (1d / 3d) };
            double[] colors = new double[3] { 0, 0, 0 };

            for (int color = 0; color < colors.Length; color++)
            {
                if (tc[color] < 0)
                    tc[color] += 1;
                if (tc[color] > 1)
                    tc[color] -= 1;

                if (tc[color] < (1d / 6d))
                    colors[color] = p + ((q - p) * 6 * tc[color]);
                else
                    if (tc[color] >= (1d / 6d) && tc[color] < (1d / 2d))
                        colors[color] = q;
                    else
                        if (tc[color] >= (1d / 2d) && tc[color] < (2d / 3d))
                            colors[color] = p + ((q - p) * 6 * (2d / 3d - tc[color]));
                        else
                            colors[color] = p;

                colors[color] *= 255; // convert to value expected by Color
            }
            return Color.FromArgb(255, (int)colors[0], (int)colors[1], (int)colors[2]);
        }

        public static bool operator !=(HSLColor left, HSLColor right)
        {
            return !(left == right);
        }
        public static bool operator ==(HSLColor left, HSLColor right)
        {
            return (left.Hue == right.Hue &&
                    left.Lightness == right.Lightness &&
                    left.Saturation == right.Saturation);
        }
        public override string ToString()
        {
            string s = string.Format("HSL({0:f2}, {1:f2}, {2:f2})", Hue, Saturation, Lightness);
            return s;
        }

    }

    class Util
    {
        public static Rectangle Rect(RectangleF rf)
        {
            Rectangle r = new Rectangle();
            r.X = (int)rf.X;
            r.Y = (int)rf.Y;
            r.Width = (int)rf.Width;
            r.Height = (int)rf.Height;
            return r;
        }
        public static RectangleF Rect(Rectangle r)
        {
            RectangleF rf = new RectangleF();
            rf.X = (float)r.X;
            rf.Y = (float)r.Y;
            rf.Width = (float)r.Width;
            rf.Height = (float)r.Height;
            return rf;
        }
        public static Point Point(PointF pf)
        {
            return new Point((int)pf.X, (int)pf.Y);
        }
        public static PointF Center(RectangleF r)
        {
            PointF center = r.Location;
            center.X += r.Width / 2;
            center.Y += r.Height / 2;
            return center;
        }

        public static void DrawFrame(Graphics dc, RectangleF r, float cornerRadius, Color color)
        {
            Pen pen = new Pen(color);
            if (cornerRadius <= 0)
            {
                dc.DrawRectangle(pen, Rect(r));
                return;
            }
            cornerRadius = (float)Math.Min(cornerRadius, Math.Floor(r.Width) - 2);
            cornerRadius = (float)Math.Min(cornerRadius, Math.Floor(r.Height) - 2);

            GraphicsPath path = new GraphicsPath();
            path.AddArc(r.X, r.Y, cornerRadius, cornerRadius, 180, 90);
            path.AddArc(r.Right - cornerRadius, r.Y, cornerRadius, cornerRadius, 270, 90);
            path.AddArc(r.Right - cornerRadius, r.Bottom - cornerRadius, cornerRadius, cornerRadius, 0, 90);
            path.AddArc(r.X, r.Bottom - cornerRadius, cornerRadius, cornerRadius, 90, 90);
            path.CloseAllFigures();
            dc.DrawPath(pen, path);
        }
        public static void Draw2ColorBar(Graphics dc, RectangleF r, Orientation orientation, Color c1, Color c2)
        {
            RectangleF lr1 = r;
            float angle = 0;

            if (orientation == Orientation.Vertical)
                angle = 270;
            if (orientation == Orientation.Horizontal)
                angle = 0;

            if (lr1.Height > 0 && lr1.Width > 0)
            {
                LinearGradientBrush lb1 = new LinearGradientBrush(lr1, c1, c2, angle, false);
                dc.FillRectangle(lb1, lr1);
                lb1.Dispose();
            }
        }
        public static void Draw3ColorBar(Graphics dc, RectangleF r, Orientation orientation, Color c1, Color c2, Color c3)
        {
            // to draw a 3 color bar 2 gradient brushes are needed
            // one from c1 - c2 and c2 - c3
            RectangleF lr1 = r;
            RectangleF lr2 = r;
            float angle = 0;

            if (orientation == Orientation.Vertical)
            {
                angle = 270;

                lr1.Height = lr1.Height / 2;
                lr2.Height = r.Height - lr1.Height;
                lr2.Y += lr1.Height;
            }
            if (orientation == Orientation.Horizontal)
            {
                angle = 0;

                lr1.Width = lr1.Width / 2;
                lr2.Width = r.Width - lr1.Width;
                lr1.X = lr2.Right;
            }

            if (lr1.Height > 0 && lr1.Width > 0)
            {
                LinearGradientBrush lb2 = new LinearGradientBrush(lr2, c1, c2, angle, false);
                LinearGradientBrush lb1 = new LinearGradientBrush(lr1, c2, c3, angle, false);

                dc.FillRectangle(lb1, lr1);
                dc.FillRectangle(lb2, lr2);

                lb1.Dispose();
                lb2.Dispose();
            }
            // with some sizes the first pixel in the gradient rectangle shows the opposite color
            // this is a workaround for that problem
            if (orientation == Orientation.Vertical)
            {
                Pen pc2 = new Pen(c2, 1);
                Pen pc3 = new Pen(c3, 1);
                dc.DrawLine(pc3, lr1.Left, lr1.Top, lr1.Right - 1, lr1.Top);
                dc.DrawLine(pc2, lr2.Left, lr2.Top, lr2.Right - 1, lr2.Top);
                pc2.Dispose();
                pc3.Dispose();
            }

            if (orientation == Orientation.Horizontal)
            {
                Pen pc1 = new Pen(c1, 1);
                Pen pc2 = new Pen(c2, 1);
                Pen pc3 = new Pen(c3, 1);
                dc.DrawLine(pc1, lr2.Left, lr2.Top, lr2.Left, lr2.Bottom - 1);
                dc.DrawLine(pc2, lr2.Right, lr2.Top, lr2.Right, lr2.Bottom - 1);
                dc.DrawLine(pc3, lr1.Right, lr1.Top, lr1.Right, lr1.Bottom - 1);
                pc1.Dispose();
                pc2.Dispose();
                pc3.Dispose();
            }
        }
    }

    class SelectorImages
    {
        public enum eIndexes
        {
            Right,
            Left,
            Up,
            Down,
            Donut,
        }

        static private ImageList m_imageList = null;
        static public ImageList ImageList()
        {
            Type t = typeof(SelectorImages);
            if (m_imageList == null)
                m_imageList = ImagesUtil.GetToolbarImageList(t, "Resources.colorbarIndicators.bmp", new Size(12, 12), Color.Magenta);
            return m_imageList;
        }
        static public Image Image(eIndexes index)
        {
            return ImageList().Images[(int)index];
        }
    }

    class ImagesUtil
    {
        static public ImageList GetToolbarImageList(Type type, string resourceName, Size imageSize, Color transparentColor)
        {
            System.Drawing.Bitmap bitmap = Properties.Resources.colorbarIndicators;// new System.Drawing.Bitmap(type, resourceName);
            ImageList imageList = new ImageList();
            imageList.ImageSize = imageSize;
            imageList.TransparentColor = transparentColor;
            imageList.Images.AddStrip(bitmap);
            imageList.ColorDepth = ColorDepth.Depth24Bit;
            return imageList;
        }
    }

}
