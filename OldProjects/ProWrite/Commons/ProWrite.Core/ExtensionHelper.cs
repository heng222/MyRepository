using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;

namespace ProWrite.Core
{
    public static class MathsExtension
    {
        public static int GetRoundInt(this double self)
        {
            return (int)Math.Round(self, 0);
        }

        public static int GetRoundInt(this int self, int zoom)
        {
            return (self * 1d / zoom).GetRoundInt();
        }
    }

    public static class PointsExtension
    {
        public static Point PointMultiplyInt(this Point self, int v)
        {
            self.X = self.X * v;
            self.Y = self.Y * v;
            return self;
        }

        public static Point PointMultiplyDouble(this Point self, double v)
        {
            self.X = (self.X * v).GetRoundInt();
            self.Y = (self.Y * v).GetRoundInt();
            return self;
        }

        public static Point PointSubPoint(this Point self, Point subOperand)
        {
            return new Point(self.X - subOperand.X, self.Y - subOperand.Y);
        }

        public static Point PointPlusPoint(this Point selft, Point plusOperand)
        {
            return new Point(selft.X + plusOperand.X, selft.Y + plusOperand.Y);
        }
        
    }

    public static class RectangleExtension
    {
        public static Rectangle ScaleRectangeByZoom(this Rectangle self, double zoom)
        {
            int x = (self.X * zoom).GetRoundInt();
            int y = (self.Y * zoom).GetRoundInt();
            int w = (self.Width * zoom).GetRoundInt();
            int h = (self.Height * zoom).GetRoundInt();
            return new Rectangle(x, y, w, h);
        }
    }

   
}
