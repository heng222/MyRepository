//---------------------------------------------------------------------
//
// File: TestPattern.cs
//
// Description:
// The control of set TestPattern
//
// Author: Terry
//
// Copyright (C) 2008 by ISoftstone Corporation.  All rights reserved.
// 
// Modify history:   
//---------------------------------------------------------------------
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using DevExpress.XtraEditors;
using ProWrite.UFE.Entity;
using ProWrite.Entity.Dashboard;
using ProWrite.UI.Controls.Common;
using System.IO;
using System.Drawing.Imaging;
using ProWrite.Core;

namespace ProWrite.UI.Controls.Dashboard
{
    /// <summary>
    /// Set testpattern
    /// </summary>
    public partial class TestPattern : XtraForm
    {
        SignInfo sign;
        public TestPattern()
        {
            Cursor = Cursors.WaitCursor;
            InitializeComponent();
            Init();
        }

        private void Init()
        {
            ddlType.Properties.Items.Clear();
            ddlType.Properties.Items.AddRange(Enum.GetValues(typeof(TestPatternType)));
            ddlType.SelectedIndex = 0;

            sign = ControlService.SignCombo.Current;

            TestPatternEntity testPattern = new TestPatternEntity();

            testPattern.Mode = 1;
            
            //Send get dimming state command
            sign.Controller.SendAsync(
                Commands.TestPattern,
                p =>
                {
                    Cursor = Cursors.Default;
                    if (p.IsSuccessed)
                    {
                        //int dimtype = p.Packet.Content.GetProperty<int>("DimType");
                        //int value = p.Packet.Content.GetProperty<int>("Value");
                        //try
                        //{
                        //    //ddlDimmingType.SelectedIndex = dimtype;
                        //    spinDimming.Value = value;
                        //}
                        //catch { }
                    }
                },
                testPattern);
        }

        private void btnOk_Click(object sender, EventArgs e)
        {
            Cursor = Cursors.WaitCursor;
            sign = ControlService.SignCombo.Current;
            TestPatternEntity testPattern = new TestPatternEntity();
            testPattern.Type = ddlType.SelectedIndex;
            testPattern.Mode = 0;
            testPattern.Flag = 1;
            if (ddlType.SelectedIndex == 9)
            {
                if (string.IsNullOrEmpty(btnFile.Text))
                {
                    MsgBox.Error("Sorry,the filedoc mustn't be empty");
                    return;
                }
                string suffix=btnFile.Text.Substring(btnFile.Text.LastIndexOf(".")+1);
                testPattern.Suffix = suffix;
                List<ImageFormat> listFormat= new List<ImageFormat>();
                listFormat.Add(ImageFormat.Bmp);
                listFormat.Add(ImageFormat.Emf);
                listFormat.Add(ImageFormat.Gif);
                listFormat.Add(ImageFormat.Icon);
                listFormat.Add(ImageFormat.Jpeg);
                listFormat.Add(ImageFormat.MemoryBmp);
                listFormat.Add(ImageFormat.Png);
                listFormat.Add(ImageFormat.Tiff);
                listFormat.Add(ImageFormat.Wmf);


                ImageFormat imageFormat = ImageFormat.Jpeg;

                if (suffix.ToUpper() == ImageFormat.Jpeg.ToString().ToUpper()
                    || suffix.ToUpper() == "JPG")
                    imageFormat = ImageFormat.Jpeg;
                else
                {
                    foreach (ImageFormat item in listFormat)
                    {
                        if (item.ToString().ToUpper() == suffix.ToUpper())
                            imageFormat = item;
                    }
                }
                //else if(
                Image image = Image.FromFile(btnFile.Text);
                MemoryStream ms = new MemoryStream();
                image.Save(ms,imageFormat);

                byte[] bytes = ms.GetBuffer();


                testPattern.FileLoc = ms.GetBuffer();// ToByte(shape);
                
                //testPattern.Value = UInt64;

            }
            else
            {
                //Image shape = Image.FromFile(btnFile.Text);
                //TestPatternEntity testPattern = new TestPatternEntity();
                //testPattern.FileLoc = ToByte(shape);
                //testPattern.Type = ddlType.SelectedIndex;

                UInt64 str10 = 0xFF000000;
                UInt64 r = Convert.ToUInt64(colorEdit.Color.R) << 16;
                UInt64 g = Convert.ToUInt64(colorEdit.Color.G) << 8;
                UInt64 b = Convert.ToUInt64(colorEdit.Color.B);
                str10 += r + g + b;
                testPattern.Value = str10;

            }
            
            sign.Controller.SendAsync(
                Commands.TestPattern,
                p =>
                {
                    Cursor = Cursors.Default;
                    if (p.IsSuccessed)
                    {
                        MsgBox.Information(Resources.Resource.GetString(Resources.Resource.Strings.SetTestPatternSuccessed));//"Set testpattern successed.");
                        Close();
                    }
                    else
                    {
                        MsgBox.Error(Resources.Resource.GetString(Resources.Resource.Strings.SetTestPatternFailed));//"Sorry,Set testpattern failed,please try again.");
                    }
                },
                testPattern);
        }        

        private void simpleButton2_Click(object sender, EventArgs e)
        {
            Close();
        }

        private void btnFile_Click(object sender, EventArgs e)
        {
            openFileDialog1.ShowDialog();
        }

        private void openFileDialog1_FileOk(object sender, CancelEventArgs e)
        {
            if (GetFilesSize(openFileDialog1.FileName) > 1013760)
            {
                MsgBox.Error("Sorry,the file size must be less than 990K.");
                //openFileDialog1.ShowDialog();
                return;
            }
            btnFile.Text = openFileDialog1.FileName;

        }

        /// <summary>
        /// Get files size by path
        /// </summary>
        /// <param name="path"></param>
        /// <returns></returns>
        public static long GetFilesSize(String path)
        {
            System.IO.FileInfo f = new FileInfo(path);
            return f.Length;
        } 

        /// <summary>
        /// Convert shape to byte
        /// </summary>
        /// <param name="imageData"></param>
        /// <returns></returns>
        public byte[] ToByte(Image imageData)
        {
            MemoryStream Ms = new MemoryStream();
            imageData.Save(Ms, System.Drawing.Imaging.ImageFormat.Bmp);
            byte[] imgByte = new byte[Ms.Length];
            Ms.Position = 0;
            Ms.Read(imgByte, 0, Convert.ToInt32(Ms.Length));
            Ms.Close();

            return imgByte;

        }
        
        private void ddlType_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (ddlType.SelectedIndex == 9)
            {
                btnFile.Enabled = true;
                colorEdit.Enabled = false;
            }
            else
            {
                btnFile.Enabled = false;
                colorEdit.Enabled = true;
            }
        }

    }
}
