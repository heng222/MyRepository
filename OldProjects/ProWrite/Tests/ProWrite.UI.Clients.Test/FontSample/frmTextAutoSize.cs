using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace ProWrite.UI.Clients.Test.FontSample
{
    public partial class frmTextAutoSize : Form
    {
        #region Variant define
        private int MaxWidth = 0;//Text container max width
        private int MaxHeight = 0;//Text container max height
        //private int tempWidth = 0;
        //private int tempHeight = 0;
        //private int tempPosition = 0;
        private string tempString = string.Empty;//Last input text
        private Panel workPanel = null;//Text container
        private PointF fontLocation = new PointF(0f, 0f);//Draw text location
        #endregion

        public frmTextAutoSize()
        {
            InitializeComponent();
            MaxWidth = panel1.Width;
            MaxHeight = panel1.Height;
            workPanel = panel1;
            label1.Text = "MaxWidth:" + panel1.Width.ToString();
            label2.Text = "MaxHeight:" + panel1.Height.ToString();
        }

        #region Function define
        private void AutoSize(string txtOut, Panel panel)
        {
            Graphics graphics = panel.CreateGraphics();
            graphics.Clear(Color.White);

            FontFamily fontFamily = new FontFamily("宋体");
            //创建两个个大小不同的Aria字体
            Font font = new Font(fontFamily, 50, FontStyle.Regular, GraphicsUnit.Pixel);
            Font font2 = new Font(fontFamily, 14, FontStyle.Regular, GraphicsUnit.Pixel);
            SolidBrush brush = new SolidBrush(Color.Black);

            StringFormat fmt = new StringFormat();
            fmt.Alignment = StringAlignment.Center;
            fmt.LineAlignment = StringAlignment.Center;

            SizeF stringSize = new SizeF();
            //测量输出字符串所需要的矩形空间
            stringSize = graphics.MeasureString(txtOut, font);

            if (stringSize.Height > MaxHeight)
            {
                workPanel = (workPanel == panel1 ? panel2 : panel1);


                txtOut = richTextBox1.Text = txtOut.Substring(tempString.Length, txtOut.Length - tempString.Length);

                richTextBox1.Select(0, txtOut.Length);

                stringSize = graphics.MeasureString(tempString, font);

                ReCountLocationF(stringSize);
                
                // 绘制输出文本的限制矩形
                graphics.DrawRectangle(new Pen(Color.Red),
                    fontLocation.X, fontLocation.Y, stringSize.Width, stringSize.Height);
                
                //输出字符串的测量信息
                graphics.DrawString(tempString, font, brush,
                    new RectangleF(fontLocation.X, fontLocation.Y, stringSize.Width, stringSize.Height), fmt);
                tempString = txtOut;
                AutoSize(txtOut, workPanel);
            }
            else
            {
                if (stringSize.Width > MaxWidth)
                {
                    if (stringSize.Height == MaxHeight)
                    {
                        workPanel = (workPanel == panel1 ? panel2 : panel1);
                        txtOut = richTextBox1.Text = txtOut.Substring(tempString.Length - 1, txtOut.Length - tempString.Length);

                        stringSize = graphics.MeasureString(tempString, font);
                        ReCountLocationF(stringSize);
                        // 绘制输出文本的限制矩形
                        graphics.DrawRectangle(new Pen(Color.Red),
                            fontLocation.X, fontLocation.Y, stringSize.Width, stringSize.Height);
                        //输出字符串的测量信息
                        graphics.DrawString(tempString, font, brush,
                            new RectangleF(fontLocation.X, fontLocation.Y, stringSize.Width, stringSize.Height), fmt);

                        AutoSize(txtOut, workPanel);
                    }
                    else
                    {
                        txtOut = richTextBox1.Text = tempString + "\n" + txtOut.Substring(tempString.Length, txtOut.Length - tempString.Length);
                        tempString += "\n";

                        AutoSize(txtOut, workPanel);
                    }
                }
                else
                {
                    ReCountLocationF(stringSize);

                    //graphics.FillRectangle(brush, Location.X * 1.0f, fontLocation.Y * 1.0f, stringSize.Width * 1.0f, stringSize.Height * 1.0f);

                    // 绘制输出文本的限制矩形
                    graphics.DrawRectangle(new Pen(Color.Red),
                        fontLocation.X, fontLocation.Y, stringSize.Width, stringSize.Height);
                    //输出字符串的测量信息
                    graphics.DrawString(txtOut, font, brush,
                        new RectangleF(fontLocation.X, fontLocation.Y, stringSize.Width, stringSize.Height), fmt);
                    tempString = txtOut;
                }
            }
        }

        private void ReAutoSize(string txtOut, Panel panel)
        {
            Graphics graphics = panel.CreateGraphics();
            graphics.Clear(Color.White);

            FontFamily fontFamily = new FontFamily("宋体");
            //创建两个个大小不同的Aria字体
            Font font = new Font(fontFamily, 50, FontStyle.Regular, GraphicsUnit.Pixel);
            Font font2 = new Font(fontFamily, 14, FontStyle.Regular, GraphicsUnit.Pixel);
            SolidBrush brush = new SolidBrush(Color.Black);

            StringFormat fmt = new StringFormat();
            fmt.Alignment = StringAlignment.Center;
            fmt.LineAlignment = StringAlignment.Center;

            SizeF stringSize = new SizeF();
            //测量输出字符串所需要的矩形空间
            stringSize = graphics.MeasureString(txtOut, font);

            if (stringSize.Height > MaxHeight)
            {
                workPanel = (workPanel == panel1 ? panel2 : panel1);


                txtOut = richTextBox1.Text = txtOut.Substring(tempString.Length, txtOut.Length - tempString.Length);

                richTextBox1.Select(0, txtOut.Length);

                stringSize = graphics.MeasureString(tempString, font);

                ReCountLocationF(stringSize);

                // 绘制输出文本的限制矩形
                graphics.DrawRectangle(new Pen(Color.Red),
                    fontLocation.X, fontLocation.Y, stringSize.Width, stringSize.Height);

                //输出字符串的测量信息
                graphics.DrawString(tempString, font, brush,
                    new RectangleF(fontLocation.X, fontLocation.Y, stringSize.Width, stringSize.Height), fmt);
                tempString = txtOut;
                AutoSize(txtOut, workPanel);
            }
            else
            {
                if (stringSize.Width > MaxWidth)
                {
                    if (stringSize.Height == MaxHeight)
                    {
                        workPanel = (workPanel == panel1 ? panel2 : panel1);
                        txtOut = richTextBox1.Text = txtOut.Substring(tempString.Length - 1, txtOut.Length - tempString.Length);

                        stringSize = graphics.MeasureString(tempString, font);
                        ReCountLocationF(stringSize);
                        // 绘制输出文本的限制矩形
                        graphics.DrawRectangle(new Pen(Color.Red),
                            fontLocation.X, fontLocation.Y, stringSize.Width, stringSize.Height);
                        //输出字符串的测量信息
                        graphics.DrawString(tempString, font, brush,
                            new RectangleF(fontLocation.X, fontLocation.Y, stringSize.Width, stringSize.Height), fmt);

                        AutoSize(txtOut, workPanel);
                    }
                    else
                    {
                        txtOut = richTextBox1.Text = tempString + "\n" + txtOut.Substring(tempString.Length, txtOut.Length - tempString.Length);
                        tempString += "\n";

                        AutoSize(txtOut, workPanel);
                    }
                }
                else
                {
                    ReCountLocationF(stringSize);
                    // 绘制输出文本的限制矩形
                    graphics.DrawRectangle(new Pen(Color.Red),
                        fontLocation.X, fontLocation.Y, stringSize.Width, stringSize.Height);
                    //输出字符串的测量信息
                    graphics.DrawString(txtOut, font, brush,
                        new RectangleF(fontLocation.X, fontLocation.Y, stringSize.Width, stringSize.Height), fmt);
                    tempString = txtOut;
                }
            }
        }

        private void ReConfigContainerSize()
        {
            workPanel.Width = int.Parse(txtWidth.Text);
            workPanel.Height = int.Parse(txtHeight.Text);            
            //return stringSize;
        }

        private void ReCountLocationF(SizeF stringSize)
        {
            if (((int)(fontLocation.X + stringSize.Width)) > MaxWidth)
            {
                fontLocation.X -= fontLocation.X + stringSize.Width - MaxWidth;
            }

            if (((int)(fontLocation.Y + stringSize.Height)) > MaxHeight)
            {
                fontLocation.Y -= fontLocation.Y + stringSize.Height - MaxHeight;
            }
            //return stringSize;
        }

        private void MoveCurorLast()
        {
            //让文本框获取焦点
            this.richTextBox1.Focus();
            //设置光标的位置到文本尾
            this.richTextBox1.Select(this.richTextBox1.TextLength, 0);
            //滚动到控件光标处
            this.richTextBox1.ScrollToCaret();
        }
        #endregion

        #region Event define
        private void btnAutoSize_Click(object sender, EventArgs e)
        {
            AutoSize(richTextBox1.Text,panel1);
        }

        private void richTextBox1_TextChanged(object sender, EventArgs e)
        {
            try
            {
                AutoSize(richTextBox1.Text, workPanel);
                MoveCurorLast();
            }
            catch (Exception ex)
            {
            }
        }

        

        private void richTextBox1_KeyDown(object sender, KeyEventArgs e)
        {
            
        }

        private void btnOK_Click(object sender, EventArgs e)
        {
            fontLocation.X = float.Parse(txtOffSetX.Text);
            fontLocation.Y = float.Parse(txtOffSetY.Text);
        }
        #endregion

        private void frmAutoSize_Load(object sender, EventArgs e)
        {

        }

        private void btnSetContainerSize_Click(object sender, EventArgs e)
        {
            ReConfigContainerSize();
            ReAutoSize(richTextBox1.Text,workPanel);
        }
    }
}