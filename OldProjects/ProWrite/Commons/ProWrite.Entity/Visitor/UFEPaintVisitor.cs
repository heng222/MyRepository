using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ProWrite.Core;
using System.Drawing;
using System.Drawing.Imaging;
using System.Communication;
using ProWrite.Unsafe;

namespace ProWrite.Entity.Shape
{
    //上传给UFE的绘制访问器
    public class UFEPaintVisitor : Visitor.VisitorAdapter
    {
        private UFEPaintVisitor() { }
        public static readonly UFEPaintVisitor Instance = new UFEPaintVisitor();

        public string ImageFile { get; set; }

        public override void VisitImage(ShapeImage shape)
        {
            try
            {
                if (string.IsNullOrEmpty(shape.ImageUrl))
                    return;

                var _image = shape.Image;
                var _imageUrl = shape.ImageUrl;

                if (_image == null)
                    _image = IOHelper.GetImageFromFile(_imageUrl);

                if (_image == null)
                {
                    _image = Image.FromFile(_imageUrl);
                    var fd = new FrameDimension(_image.FrameDimensionsList[0]);

                    _image.SelectActiveFrame(fd, 0);
                }

                shape.UpdateDestBounds();
                if (shape.DestBounds == Rectangle.Empty)
                    shape.DestBounds = shape.VirtualBounds;

                int desWidth = shape.DestBounds.Width / shape.Zoom;
                int desHeight = shape.DestBounds.Height / shape.Zoom;

                var desImg = new Bitmap(desWidth, desHeight);
                using (Graphics g = Graphics.FromImage(desImg))
                {
                    g.Clear(Color.Transparent);
                    g.DrawImage(_image, new Rectangle(0, 0, desWidth, desHeight), new Rectangle(0, 0, _image.Width, _image.Height), GraphicsUnit.Pixel);
                }

                if (desImg != null)
                {
                    IOHelper.SaveImage(desImg, ImageFile, ImageFormat.Png);
                }

                if (desImg != _image)
                    desImg.Dispose();
            }
            catch (Exception ex)
            {
                Log.Error(ex.Message, ex);
                ImageFile = null;
            }
            
        }

        public override void VisitShapeDraw(ShapeDraw shapeDraw)
        {
            using (Image png = new Bitmap(shapeDraw.SignSize.Width * shapeDraw.Zoom, shapeDraw.SignSize.Height * shapeDraw.Zoom, PixelFormat.Format32bppArgb))
            {
                using (Graphics g = Graphics.FromImage(png))
                {
                    g.Clear(Color.Transparent);

                    foreach (ShapePaint shape in shapeDraw.Childs)
                        shape.DrawOutputImage(g);
                }

                using (Bitmap outbmp = ImageHelper.ReSizeImage(png, shapeDraw.SignSize.Width, shapeDraw.SignSize.Height) as Bitmap)
                {
                    //产生背景为透明的Gif图片
                    //GifImageHelper gifTransparent = new GifImageHelper();
                    //Bitmap gifOut = gifTransparent.Quantize(outbmp);
                    try
                    {
                        outbmp.Save(ImageFile, ImageFormat.Png);
                    }
                    catch (Exception e)
                    {
                        ImageFile = string.Empty;
                        Log.Error("Shape GenerateUploadImage Error: " + e.Message);
                    }
                }
            }
        }

        public override void VisitLabel(ShapeLabel shape)
        {
            try
            {
                var _labelImageActual = shape._labelImageActual;
                if (_labelImageActual == null
                    && !string.IsNullOrEmpty(shape.Text)
                    && (shape.IsChanged || shape.LabelImage == null))
                {
                    var FontMgr = shape.FontMgr;
                    FontMgr.ShowGrid = false;
                    //Zoom       
                    FontMgr.ScaleIndex = 1;
                    //Paint type
                    FontMgr.SetStyle(shape.FrameSizeFixed, shape.FontSizeFixed);
                    //Font info
                    FontMgr.TextColor = shape.ConveredForeColor(shape.SignType);//.SourceForeColor;
                    FontMgr.BackColor = shape.ConveredBackColor(shape.SignType);//.SourceBackColor;
                    FontMgr.FontName = shape.Font.Name;
                    FontMgr.FontHeight = shape.Font.Size;
                    FontMgr.Alignment = shape.TextAlignment;
                    FontMgr.LineAlignment = shape.TextVAlignment;
                    FontMgr.Bold = (shape.Font.Style & FontStyle.Bold) == FontStyle.Bold;
                    FontMgr.Italic = (shape.Font.Style & FontStyle.Italic) == FontStyle.Italic;
                    FontMgr.KernAmount = shape.KernAmount;
                    FontMgr.LeadAmount = shape.LeadAmount;

                    FontMgr.FrameSize = shape.Size;
                    FontMgr.Text = shape.Text;

                    switch (shape.TextEffect.Effect)
                    {
                        case OutlineShadowType.SHADED:
                            FontMgr.SetShadowAttri(shape.TextEffect.EffectColor, shape.TextEffect.ShadowLateralShift, shape.TextEffect.ShadowVerticalShift);
                            break;
                        case OutlineShadowType.OUTLINE:
                            FontMgr.SetOutlineAttri(shape.TextEffect.EffectColor, (ushort)(shape.TextEffect.OutlineWidth));
                            break;
                        case OutlineShadowType.NONE:
                            FontMgr.CancelTextEffect();
                            break;
                    }

                    shape.PaintImageInShape(null);
                    shape.IsChanged = false;
                }
               
                try
                {
                    _labelImageActual = shape._labelImageActual;
                    _labelImageActual.Save(ImageFile, ImageFormat.Png);
                }
                catch (Exception e)
                {
                    ImageFile = string.Empty;
                    Log.Error("Shape GenerateUploadImage Error: " + e.Message, e);
                }
                finally
                {
                    _labelImageActual.Dispose();
                }
            }
            catch (Exception e)
            {
                Log.Error("Label GenerateUploadImage Error: " + e.Message, e);
            }
        }

        
    }
}
