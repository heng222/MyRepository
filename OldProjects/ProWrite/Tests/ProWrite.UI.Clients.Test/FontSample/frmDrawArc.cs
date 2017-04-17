using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace ProWrite.UI.Clients.Test.FontSample
{
    public partial class frmDrawArc : Form
    {

        public frmDrawArc()
        {
            InitializeComponent();
        }

        private void Form11_Paint(object sender, PaintEventArgs e)
        {
            DrawArcFloat(e);    
        }

        public   void   DrawArcFloat(PaintEventArgs   e)    
        {    
            //   Create   pen.    
            Pen   blackPen=   new   Pen(Color.Black,   3);    
            //   Create   coordinates   of   rectangle   to   bound   ellipse.    
            float   x   =   50;    
            float   y   =   50;    
            float   width   =   1000.5F;    
            float   height   =   1000.5F;    
            //   Create   start   and   sweep   angles   on   ellipse.    
            float   startAngle   =     45.0F;    
            float   sweepAngle   =   270.0F;    
            //   Draw   arc   to   screen.    
            e.Graphics.DrawArc(blackPen,   x,   y,   width,   height,   startAngle,   sweepAngle);    
        }    
     
    }    
}

//int  width  =  cameraImage.Width/4;   
//int  height  =  cameraImage.Height/4;   
//Bitmap  bitmap  =  new  Bitmap(width,  height);   
//for  (int  i  =  0;  i  <width;  i++)   
//{   
//     for  (int  j  =  0;  j  <  height;  j++)   
//     {   
//           bitmap.SetPixel(i,  j,  cameraImage.GetPixel(i  +  width,j+height));   
//     }   
//}   
//return  bitmap; 
//    }
//}