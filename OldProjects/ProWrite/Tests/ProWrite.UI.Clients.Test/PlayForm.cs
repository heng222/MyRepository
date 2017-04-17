//using System;
//using System.Collections.Generic;
//using System.ComponentModel;
//using System.Data;
//using System.Drawing;
//using System.Drawing.Imaging;
//using System.Text;
//using System.Windows.Forms;
//using System.Linq;
//using DirectShowLib;
//using DirectShowLib.DES;
//using ProWrite.Core;
//using ProWrite.Entity.DES;
//using ProWrite.DES;


//namespace ProWrite.UI.Clients.Test
//{
//    public partial class PlayForm : Form
//    {
//        VideoLayerCollection ds = new VideoLayerCollection();
//        VideoLayerCollection ds2 = new VideoLayerCollection();
//        VideoLayerCollection ds3 = new VideoLayerCollection();
//        VideoLayerCollection[] dsArr = new VideoLayerCollection[3];
//        public PlayForm()
//        {
//            InitializeComponent();
//            Panel.CheckForIllegalCrossThreadCalls = false;
//            Button.CheckForIllegalCrossThreadCalls = false;
//            TextBox.CheckForIllegalCrossThreadCalls = false;
//        }

//        Play myPlay;
//        private void btnPlay_Click(object sender, EventArgs e)
//        {
//            try
//            {
//                if (myPlay!=null && myPlay.CurentState == PlayState.Run)
//                {
//                    myPlay.Stop();
//                    this.btnPlay.Text = "²¥·Å";
//                }
//                else
//                {
//                    myPlay = new Play(ds, null, this.pnlPlay);
//                    myPlay.PlayEvent += new EventHandler(PlayEvent);
//                    myPlay.PlayCompleted += new EventHandler(PlayCompleted);
//                    myPlay.Run();
//                    this.btnPlay.Text = "Í£Ö¹";
//                }
//            }
//            catch (Exception ex)
//            {
//                MessageBox.Show(ex.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
//            }
//        }
//        Play myPlay2;
//        private void button1_Click(object sender, EventArgs e)
//        {
//            //PlayForm frm = new PlayForm();
//            //frm.Show();
//            //try
//            //{
//            //    if (myPlay2 != null && myPlay2.CurentState == PlayState.Run)
//            //    {
//            //        myPlay2.Stop();
//            //        this.button1.Text = "²¥·Å2";
//            //    }
//            //    else
//            //    {
//            //        myPlay2 = new Play(ds2,null, this.pnlPlay);
//            //        //myPlay2.PlayEvent += new EventHandler(PlayEvent);
//            //        //myPlay2.PlayCompleted += new EventHandler(PlayCompleted2);
//            //        myPlay2.RunMulti();
//            //        this.button1.Text = "Í£Ö¹2";
//            //    }
//            //}
//            //catch (Exception ex)
//            //{
//            //    MessageBox.Show(ex.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
//            //}
//            Play  myPlay2 = new Play(ds, new Size(this.pnlPlay.Width, this.pnlPlay.Height));
//            if (myPlay2.OutputVideo("d:\\zzg.mpeg", 0, 12) == true)
//                this.btnPlay.Text = "ok22";
//        }

//        private void PlayCompleted(object o, System.EventArgs e)
//        {
//            this.btnPlay.Text = "²¥·Å";
//            if (myPlay != null)
//            {
//                myPlay.Dispose();
//                myPlay = null;
//            }
//            this.pnlPlay.Refresh();
//        }

//        private void PlayCompleted2(object o, System.EventArgs e)
//        {
//            myPlay2 = null;
//            this.button1.Text = "²¥·Å2";
//            this.Invalidate();
//        }

//        private void PlayEvent(object o, System.EventArgs e)
//        {
//            this.textBox1.Text = this.textBox1.Text + "5";
//        }

//        private static bool ImageLayer(Layer layer)
//        {
//            if (layer.Visible == true && layer.LayerType == LayerType.Image)
//            {
//                return true;
//            }
//            else
//            {
//                return false;
//            }
//        }

//        private void PlayForm_Load(object sender, EventArgs e)
//        {
//            LoadDS();
//            //LoadDS2();
//            //LoadDS3();
//            dsArr[0] = ds;
//            //dsArr[1] = ds2;
//            //dsArr[2] = ds3;
//            dsArr[0].PlayLength = 12;
//            //dsArr[1].PlayLength = 6;
//            //dsArr[2].PlayLength = 10;
//        }

//        private void btnList_Click(object sender, EventArgs e)
//        {
//            myPlay = new Play(dsArr,null,null, this.pnlPlay);
//            myPlay.PlayEvent += new EventHandler(PlayEvent);
//            myPlay.RunList();
//        }

//        private void btnPause_Click(object sender, EventArgs e)
//        {
//            myPlay.Pause();
//        }

//        private void button5_Click(object sender, EventArgs e)
//        {
//            myPlay.Stop();
//            myPlay = null;
//        }

//        private void btnCon_Click(object sender, EventArgs e)
//        {
//            if (myPlay != null && myPlay.CurentState == PlayState.Pause)
//                myPlay.ContinueRun();
//        }

//        private void btnSave_Click(object sender, EventArgs e)
//        {
//            this.btnPlay.Text = "out";
//            myPlay = new Play(ds, new Size(this.pnlPlay.Width,this.pnlPlay.Height));
//            if (myPlay.OutputVideo("d:\\zzg.mpeg", 0, 12) == true)
//                this.btnPlay.Text = "ok";
//        }

//        private void LoadDS()
//        {
//            Layer dsLayer;
//            LayerEffect EntryEFC;
//            LayerEffect exitEFC;
//            LayerEffect EmphEFC;
//            RECT rc;
//            Property[] pro;
            
//            //Ìí¼ÓÍ¼Æ¬²ã1------------
//            //½øÈëÐ§¹û
//            rc = new RECT();
//            rc.Height = 50;
//            rc.Width = 50;
//            rc.OffsetX = 10;
//            rc.OffsetY = 10;
//            EntryEFC = new LayerEffect();
//            EntryEFC.GUID = new Guid("76f363f2-7e9f-4ed7-a6a7-ee30351b6628");
//            EntryEFC.StartTime = 0;
//            EntryEFC.EndTime = 3;
//            EntryEFC.Direction = false;

//            //±³¾°Ð§¹û
//            pro = new Property[3];
//            pro[0] = new Property();
//            pro[0].Name = "Color";
//            pro[0].Value = "0xFFFFFF";
//            pro[1] = new Property();
//            pro[1].Name = "Rate";
//            pro[1].Value = "14";
//            pro[2] = new Property();
//            pro[2].Name = "Amount";
//            pro[2].Value = "0.490";

//            EmphEFC = new LayerEffect();
//            EmphEFC.GUID = new Guid("632BB53B-C02D-4AB1-B041-A14F524812EF");
//            EmphEFC.StartTime = 0;
//            EmphEFC.EndTime = 12;
//            EmphEFC.Property = pro;

//            //ÍË³öÐ§¹û
//            exitEFC = new LayerEffect();
//            exitEFC.GUID = new Guid("4a03dcb9-6e17-4a39-8845-4ee7dc5331a5");
//            exitEFC.StartTime = 10;
//            exitEFC.EndTime = 12;
//            exitEFC.Direction = true;

//            dsLayer = new Layer();
//            dsLayer.ID = 1;
//            dsLayer.Name = "Layer1";
//            dsLayer.Visible = true;
//            dsLayer.Rect = rc;
//            dsLayer.LayerType = LayerType.Image;
//            dsLayer.Level = 1;
//            dsLayer.StartTime = 0;
//            dsLayer.EndTime = 12;
//            dsLayer.FilePath = "D:\\Images\\SSM12111.JPG";
//            dsLayer.EntryEffect = EntryEFC;
//            dsLayer.ExitEffect = exitEFC;
//            dsLayer.EmphasisEffect = EmphEFC;
//            ds.Add(dsLayer);
//            //------------------------

//            //Ìí¼ÓÍ¼Æ¬²ã ±³¾°²ã------------
//            rc = new RECT();
//            rc.Height = this.pnlPlay.Height;
//            rc.Width = this.pnlPlay.Width;
//            rc.OffsetX = 0;
//            rc.OffsetY = 0;

//            dsLayer = new Layer();
//            dsLayer.ID = 0;
//            dsLayer.Name = "Layer4";
//            dsLayer.Visible = true;
//            dsLayer.Rect = rc;
//            dsLayer.LayerType = LayerType.Image;
//            dsLayer.Level = 2;
//            dsLayer.StartTime = 0;
//            dsLayer.EndTime = 12;
//            dsLayer.EntryEffect = EntryEFC;
//            dsLayer.EmphasisEffect = EmphEFC;
//            dsLayer.ExitEffect = exitEFC;
//            dsLayer.FilePath = "D:\\Images\\Sunset.jpg";
//            ds.Add(dsLayer);
//            //------------------------
//            //ds.Sort(new SortComparer<Layer>("Level", false));
            
//        }

//        private void LoadDS2()
//        {
//            Layer dsLayer;
//            LayerEffect EntryEFC;
//            LayerEffect exitEFC;
//            RECT rc;
//            Property[] pro;

//            //Ìí¼ÓÍ¼Æ¬²ã1------------
//            rc = new RECT();
//            rc.Height = 100;
//            rc.Width = 200;
//            rc.OffsetX = 50;
//            rc.OffsetY = 50;
//            pro = new Property[1];
//            pro[0] = new Property();
//            pro[0].Name = "MaskNum";
//            pro[0].Value = "211";

//            EntryEFC = new LayerEffect();
//            EntryEFC.GUID = new Guid("DE75D012-7A65-11D2-8CEA-00A0C9441E20");
//            EntryEFC.StartTime = 2;
//            EntryEFC.EndTime = 5;
//            EntryEFC.Property = pro;
//            EntryEFC.Direction = false;

//            pro = new Property[1];
//            pro[0] = new Property();
//            pro[0].Name = "MaskNum";
//            pro[0].Value = "64";
//            exitEFC = new LayerEffect();
//            exitEFC.GUID = new Guid("DE75D012-7A65-11D2-8CEA-00A0C9441E20");
//            exitEFC.StartTime = 10;
//            exitEFC.EndTime = 13;
//            exitEFC.Property = pro;
//            exitEFC.Direction = true;

//            dsLayer = new Layer();
//            dsLayer.ID = 1;
//            dsLayer.Name = "Layer1";
//            dsLayer.Visible = true;
//            dsLayer.Rect = rc;
//            dsLayer.LayerType = LayerType.Image;
//            dsLayer.Level = 1;
//            dsLayer.StartTime = 2;
//            dsLayer.EndTime = 13;
//            dsLayer.FilePath = "d:\\main.jpg";
//            dsLayer.EntryEffect = EntryEFC;
//            dsLayer.ExitEffect = exitEFC;
//            ds2.Add(dsLayer);
//            //------------------------

//            //Ìí¼ÓÎÄ×Ö²ã 3------------
//            rc = new RECT();
//            rc.Height = this.pnlPlay.Height;
//            rc.Width = this.pnlPlay.Width;
//            rc.OffsetX = 20;
//            rc.OffsetY = 20;

//            TextInfo outText = new TextInfo();
//            outText.Text = "±±¾©°ÂÔË»á£¡";
//            outText.Size = 20;
//            outText.Color = Color.Blue;
//            outText.Font = "Tahoma";
//            outText.BitCount = 8;
//            outText.FontStyle = FontStyle.Bold;
//            outText.RollWay = RollWay.TopToBottom;
//            outText.RollRate = 5;

//            dsLayer = new Layer();
//            dsLayer.ID = 2;
//            dsLayer.Name = "Layer3";
//            dsLayer.Visible = true;
//            dsLayer.Rect = rc;
//            //dsLayer.LayerType = LayerType.Marquee;
//            dsLayer.Level = 2;
//            dsLayer.StartTime = 0;
//            dsLayer.EndTime = 8;
//            dsLayer.TextInfo = outText;
//            ds2.Add(dsLayer);
//            //------------------------

//            //Ìí¼ÓÍ¼Æ¬²ã ±³¾°²ã------------
//            rc = new RECT();
//            rc.Height = this.pnlPlay.Height;
//            rc.Width = this.pnlPlay.Width;
//            rc.OffsetX = 0;
//            rc.OffsetY = 0;

//            dsLayer = new Layer();
//            dsLayer.ID = 3;
//            dsLayer.Name = "Layer2";
//            dsLayer.Visible = true;
//            dsLayer.Rect = rc;
//            dsLayer.LayerType = LayerType.Image;
//            dsLayer.Level = 3;
//            dsLayer.StartTime = 0;
//            dsLayer.EndTime = 16;
//            dsLayer.FilePath = "d:\\Sunset.jpg";
//            ds2.Add(dsLayer);
//            //------------------------
//            ds2.Sort(new SortComparer<Layer>("Level", false));
//        }

//        private void LoadDS3()
//        {
//            Layer dsLayer;
//            LayerEffect EntryEFC;
//            LayerEffect exitEFC;
//            RECT rc;
//            Property[] pro;

//            //Ìí¼ÓÍ¼Æ¬²ã1------------
//            rc = new RECT();
//            rc.Height = 100;
//            rc.Width = 200;
//            rc.OffsetX = 50;
//            rc.OffsetY = 50;
//            pro = new Property[1];
//            pro[0] = new Property();
//            pro[0].Name = "MaskNum";
//            pro[0].Value = "211";

//            EntryEFC = new LayerEffect();
//            EntryEFC.GUID = new Guid("DE75D012-7A65-11D2-8CEA-00A0C9441E20");
//            EntryEFC.StartTime = 2;
//            EntryEFC.EndTime = 5;
//            EntryEFC.Property = pro;
//            EntryEFC.Direction = false;

//            pro = new Property[1];
//            pro[0] = new Property();
//            pro[0].Name = "MaskNum";
//            pro[0].Value = "64";
//            exitEFC = new LayerEffect();
//            exitEFC.GUID = new Guid("DE75D012-7A65-11D2-8CEA-00A0C9441E20");
//            exitEFC.StartTime = 10;
//            exitEFC.EndTime = 13;
//            exitEFC.Property = pro;
//            exitEFC.Direction = true;

//            dsLayer = new Layer();
//            dsLayer.ID = 1;
//            dsLayer.Name = "Layer1";
//            dsLayer.Visible = true;
//            dsLayer.Rect = rc;
//            dsLayer.LayerType = LayerType.Image;
//            dsLayer.Level = 1;
//            dsLayer.StartTime = 2;
//            dsLayer.EndTime = 13;
//            dsLayer.FilePath = "d:\\SSM12091.JPG";
//            dsLayer.EntryEffect = EntryEFC;
//            dsLayer.ExitEffect = exitEFC;
//            ds3.Add(dsLayer);
//            //------------------------

//            //Ìí¼ÓÎÄ×Ö²ã 3------------
//            rc = new RECT();
//            rc.Height = this.pnlPlay.Height;
//            rc.Width = this.pnlPlay.Width;
//            rc.OffsetX = 20;
//            rc.OffsetY = 20;

//            TextInfo outText = new TextInfo();
//            outText.Text = "ÈíÍ¨¶¯Á¦£¡";
//            outText.Size = 20;
//            outText.Color = Color.Blue;
//            outText.Font = "Tahoma";
//            outText.BitCount = 8;
//            outText.FontStyle = FontStyle.Bold;
//            outText.RollWay = RollWay.TopToBottom;
//            outText.RollRate = 5;

//            dsLayer = new Layer();
//            dsLayer.ID = 2;
//            dsLayer.Name = "Layer3";
//            dsLayer.Visible = true;
//            dsLayer.Rect = rc;
//            //dsLayer.LayerType = LayerType.Marquee;
//            dsLayer.Level = 2;
//            dsLayer.StartTime = 0;
//            dsLayer.EndTime = 8;
//            dsLayer.TextInfo = outText;
//            ds3.Add(dsLayer);
//            //------------------------

//            //Ìí¼ÓÍ¼Æ¬²ã ±³¾°²ã------------
//            rc = new RECT();
//            rc.Height = this.pnlPlay.Height;
//            rc.Width = this.pnlPlay.Width;
//            rc.OffsetX = 0;
//            rc.OffsetY = 0;

//            dsLayer = new Layer();
//            dsLayer.ID = 3;
//            dsLayer.Name = "Layer2";
//            dsLayer.Visible = true;
//            dsLayer.Rect = rc;
//            dsLayer.LayerType = LayerType.Image;
//            dsLayer.Level = 3;
//            dsLayer.StartTime = 0;
//            dsLayer.EndTime = 16;
//            dsLayer.FilePath = "d:\\SSM12103.JPG";
//            ds3.Add(dsLayer);
//            //------------------------
//            ds3.Sort(new SortComparer<Layer>("Level", false));
//        }

//        private void LoadMarquee(RollWay rowWary)
//        {
//            Layer layer = new Layer();
//            TextInfo outText = new TextInfo();
//            outText.Text = "How °¢ÈÈ£¡";
//            outText.Size = 20;
//            outText.Color = Color.Blue;
//            outText.Font = "Tahoma";
//            outText.BitCount = 8;
//            outText.FontStyle = FontStyle.Bold;
//            outText.RollWay = rowWary;
//            outText.RollRate = 5;

//            RECT rc = new RECT();
//            rc.Height = this.pnlPlay.Height;
//            rc.Width = this.pnlPlay.Width;
//            rc.OffsetX = 20;
//            rc.OffsetY = 20;

//            layer.ID = 2;
//            layer.Name = "Layer3";
//            layer.Visible = true;
//            layer.Rect = rc;
//            //layer.LayerType = LayerType.Marquee;
//            layer.Level = 2;
//            layer.StartTime = 0;
//            layer.EndTime = 8;
//            layer.TextInfo = outText;
//            ds.Add(layer);
//        }

//        private void button2_Click(object sender, EventArgs e)
//        {
//            if (myPlay != null)
//                myPlay.RunNext(1);
//        }

//        private void button3_Click(object sender, EventArgs e)
//        {
//            if (myPlay != null)
//                myPlay.RunPrev(1);
//        }

//        private void button4_Click(object sender, EventArgs e)
//        {
//            myPlay = new Play(ds,null, this.pnlPlay);
//            //myPlay.PlayEvent += new EventHandler(PlayEvent);
//            //myPlay.PlayCompleted += new EventHandler(PlayCompleted);
//            Image img = myPlay.GetImage(2);
//            pictureBox1.BackgroundImage = img;
//            pictureBox1.Invalidate();
//            //IOHelper.SaveImage(pictureBox1.BackgroundImage, "c:\\zzz.jpg");
//            img.Save("c:\\zzz.jpg", System.Drawing.Imaging.ImageFormat.Jpeg);
//            //myPlay = null;
//        }

        
//    }
//}
