//---------------------------------------------------------------------
//
// File: MessageConverter.cs
//
// Description:
// Message class 
//
// Author: Jerry Xu
//
// Modify history:
//      Kevin  2009-1-4 Update method:ConvertLayerBounds(ShapeBase shape)
//      Jerry Xu 2009-3-3 Update method:ConvertEmphasisEffect(LayerEffect effect)
//      Jerry Xu 2009-3-9 Update method:ConvertFontInfoType(ShapeTextBase shape)
//      Jerry Xu 2009-3-12 Update method:Convert(MessageInfo message)
//      Jerry Xu 2009-3-18 Update method:ConvertEmphasisEffect(LayerEffect effect)
//      Jerry Xu 2009-4-1  Update method:ConvertFontInfoType(ShapeTextBase shape)
//      Jerry Xu 2009-5-8  Update method:ConvertFontInfoType(ShapeTextBase shape)
//      Jerry Xu 2009-5-21 Update method:ConvertLayer(ShapeLayer item)
//
// Copyright (C) 2008 by Trans-Lux All rights reserved.
// 
//---------------------------------------------------------------------

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ProWrite.Core;
using ProWrite.UFE.Entity;
using ProWrite.Entity.DES;
using ProWrite.Entity.Shape;
using System.Drawing;
using ProWrite.Entity.Dashboard;
using ProWrite.Entity.Library;
using System.Globalization;
using System.Drawing.Imaging;

namespace ProWrite.UFE.Files
{
    public abstract class MemoryLibraryItemConverterBase<TSource, TTarget> : ConverterBase<TSource, TTarget> where TSource:MemoryLibraryItem
    {
        protected void ConvertId(TSource library, ref ContentIDType id)
        {
            id.CXCUniqueIdentifier = library.Id;
            id.LibraryName = library.Name;
            id.ProWriteIdentifier = library.Id;
            id.HumanReadableName = library.Name;
            id.Modify.DateTime = library.ModifyTime;
            id.Create.DateTime = library.CreateTime;
            id.Upload.DateTime = DateTime.Now;
        }
    }

    public class MessageConverter : MemoryLibraryItemConverterBase<MessageInfo, FrameObjectType>
    {
        ShapeConverter shapeConverter = new ShapeConverter();

        public UfeFile File { get; private set; }
        public UfeFile NailImageFile { get; private set; }
        private SignInfo _sign;
        /// <summary>
        /// Function: Upload target sign info
        /// Author  : Jerry Xu
        /// Date    : 2008-12-8
        /// </summary>
        public SignInfo Sign
        {
            get
            {
                return _sign;
            }
            set
            {
                if (value != _sign)
                    _sign = value;
            }
        }

        public MessageConverter()
        {
            shapeConverter = new ShapeConverter();
            shapeConverter.Sign = _sign;
            Shapes = new List<ShapePair>();
        }

        public List<ShapePair> Shapes
        {
            get;
            private set;
        }
        /// <summary>
        /// Function: Convert MemoryLibraryItem(MessageInfo) to UfeFile(Need uploaded files)
        /// Author  : Jerry Xu
        /// Date    : 2008-12-8
        /// </summary>
        /// <param name="item">MemoryLibraryItem</param>
        /// <returns>UfeFile</returns>
        private static UfeFile ConvertFile(MemoryLibraryItem item)
        {
            UfeFile file = new UfeFile();
            file.Id = item.Id;
            file.Name = item.Name;
            file.CreateTime = item.CreateTime.ToString();
            file.ModifyTime = item.ModifyTime.ToString();
            file.Length = float.Parse(item.Length.ToString());
            file.FromFilePath = LocalFilePathMapping.GetFile(FileType.Message, file.Id);
            file.ToFilePath = FilePathMapping.GetMessagePath(file.Id);
            file.Type = FileType.Message;
            return file;
        }

        private UfeFile ConvertNailImage(MessageInfo message)
        {
            UfeFile file = new UfeFile();
            file.Id = message.Id;
            file.Name = message.Name;
            file.CreateTime = message.CreateTime.ToString();
            file.ModifyTime = message.ModifyTime.ToString();
            file.Length = float.Parse(message.Length.ToString());
            file.FromFilePath = message.ImagePath;// LocalFilePathMapping.GetFile(FileType.Message, file.Id);
            file.ToFilePath = FilePathMapping.GetNailImagePath(file.Id);
            file.Type = FileType.MessageNailImage;
            Image desImg = IOHelper.GetImageFromFile(message.ImagePath);
            System.IO.File.Copy(message.ImagePath, File.FromFilePath.Replace(".xml", ".png"));
            //Config.CopyDir(message.ImagePath,File.FromFilePath.Replace(".xml",".png"));
            //IOHelper.SaveImage(desImg, File.FromFilePath.Replace(".xml", ".png"), ImageFormat.Png);
            file.Content =  IOHelper.ReadAllBytes(message.ImagePath);
            file.Size = IOHelper.GetFileLength(File.FromFilePath);
            return file;
        }

        /// <summary>
        /// Function: Convert MessageInfo to ufe.Message
        /// Author  : Jerry Xu
        /// Date    : 2008-12-2
        /// </summary>
        /// <param name="message">MessageInfo</param>
        /// <returns>Message</returns>
        public override FrameObjectType Convert(MessageInfo message)
        {
            Shapes.Clear();

            File = ConvertFile(message);
           NailImageFile = ConvertNailImage(message);

            FrameObjectType ufeMessage = new FrameObjectType();
            List<ProWrite.UFE.Entity.FrameContentType> layers = new List<ProWrite.UFE.Entity.FrameContentType>();


#if VERSION_1
            ufeMessage.Id = message.Id;
            ufeMessage.Length = float.Parse(message.Length.ToString());
            ufeMessage.SignBackgroundColor = ConverterHelper.ColorToString(message.BackColor, NumberType.Hex); 
            if (message.EmphasisEffect != null && message.EmphasisEffect.Name != null && message.EmphasisEffect.Duration!=0)
                ufeMessage.EmphasisEffect = ConvertEmphasisEffect(message.EmphasisEffect);
#else
            ConvertId(message, ref ufeMessage.ContentID);

            ufeMessage.MasterLayer.Length = float.Parse(message.Length.ToString());
            ufeMessage.MasterLayer.SignBackgroundColor = ConverterHelper.ColorToString( message.ConvertedSignBackColor(Sign.Type),Sign.Type);
            if (message.EmphasisEffect != null && message.EmphasisEffect.Name != null && message.EmphasisEffect.Duration != 0)
                ufeMessage.MasterLayer.EmphasisEffect = ConvertEmphasisEffect(message.EmphasisEffect);
            //if (message.EmphasisEffect != null && message.EmphasisEffect.Name != null && message.EmphasisEffect.Duration != 0)
            //    ufeMessage.MasterLayer.EntryEffect = ConvertEffect(message.EmphasisEffect);
            //if (message.EmphasisEffect != null && message.EmphasisEffect.Name != null && message.EmphasisEffect.Duration != 0)
            //    ufeMessage.MasterLayer.ExitEffect = ConvertEffect(message.EmphasisEffect);
#endif

            if (message.Items != null && message.Items.Length > 0)
            {
                foreach (ShapeLayer layer in message.Items)
                {
                    if (layer.Shape != null)
                        layers.Add(ConvertLayer(layer));
                }
                ufeMessage.Contents = layers;
            }

            return ufeMessage;
        }


        /// <summary>
        /// Function: Convert LayerEffect to ufe.Effect
        /// Author  : Jerry Xu
        /// Date    : 2008-12-2
        /// </summary>
        /// <param name="effect">LayerEffect</param>
        /// <returns>Effect</returns>
        private static TransitionEffectType ConvertEffect(ILayerEffect effect)
        {
            var ufeEffect = new TransitionEffectType();
//#if VESION_1
            ufeEffect.Name = (TransitionType)Enum.Parse(typeof(TransitionType), effect.Name.ToUpper());
            ufeEffect.Params = ConvertParameter(effect as LayerEffect);
//#else
//            ufeEffect.Effect = effect.ToUFEEffect();
//#endif
            ufeEffect.Length = effect.Duration;

            return ufeEffect;
        }

        /// <summary>
        /// Function: Convert LayerEffect(EmphasisEffectType) to uef.Effect(EmphasisType)
        /// Author  : Jerry Xu
        /// Date    : 2008-12-2
        /// </summary>
        /// <param name="effect">LayerEffect</param>
        /// <returns>Effect</returns>
        private static EmphasisEffectType ConvertEmphasisEffect(ILayerEffect effect)
        {
            var ufeEffect = new EmphasisEffectType();
//#if VERSION_1
            ufeEffect.Name = (EmphasisType)Enum.Parse(typeof(EmphasisType), effect.Name.ToUpper());
             ufeEffect.Params = ConvertParameter(effect as LayerEffect);
//#else
//            ufeEffect.Effect = effect.ToUFEEffect();
//#endif
            ufeEffect.Length = effect.Duration;

            return ufeEffect;
        }

        /// <summary>
        /// Function: Convert Effect.Properties to ufe.Effect.Parameters
        /// Author  : Jerry Xu
        /// Date    : 2008-12-2
        /// </summary>
        /// <param name="effect">LayerEffect</param>
        /// <returns>Parameter[]</returns>
        private static Parameter[] ConvertParameter(LayerEffect effect)
        {
            List<Parameter> parameters = new List<Parameter>();
            Parameter parameter;
            var props = effect.UFEEffect;
            if (props != null && props.Length > 0)
            {
                foreach (var item in props)
                {
                    parameter = new Parameter();
                    parameter.Name = item.Name;
                    parameter.Value = item.Value;
                    parameters.Add(parameter);
                }
            }

            return parameters.ToArray();
        }

        /// <summary>
        /// Function: Convert ShapeLayer to ufe.Layer
        /// Author  : Jerry Xu
        /// Date    : 2008-12-2
        /// </summary>
        /// <param name="layer">ShapeLayer</param>
        /// <returns>Layer</returns>
        private FrameContentType ConvertLayer(ShapeLayer layer)
        {
            var ufeLayer = new ProWrite.UFE.Entity.FrameContentType();
            ufeLayer.Length = long.Parse(layer.Duration.ToString());
            ufeLayer.StartTime = long.Parse(layer.StartTime.ToString());
            if (layer.EntryEffect != null && layer.EntryEffect.Name != null && layer.EntryEffect.Duration != 0)
                ufeLayer.EntryEffect = ConvertEffect(layer.EntryEffect);
            if (layer.EmphasisEffect != null && layer.EmphasisEffect.Name != null && !layer.EmphasisEffect.IsEmpty && layer.EmphasisEffect.Duration != 0)
                ufeLayer.EmphasisEffect = ConvertEmphasisEffect(layer.EmphasisEffect);
            if (layer.ExitEffect != null && layer.ExitEffect.Name != null && layer.ExitEffect.Duration != 0)
                ufeLayer.ExitEffect = ConvertEffect(layer.ExitEffect);

            ufeLayer.Type = ConvertLayerType(layer.Shape.LayerType);
            ufeLayer.Bounds = ConvertLayerBounds(layer.Shape);
            ufeLayer.Text = ConvertTextType(layer.Shape);
            if (layer.Shape != null)
            {
                //ScrollType
                if (layer.Shape.LayerType == LayerType.Temp || layer.Shape.LayerType == LayerType.Time
                    || layer.Shape.LayerType == LayerType.DynamicText)
                {
                    switch (layer.Shape.LayerType)
                    {
                        case LayerType.Time:
                            ufeLayer.DLTSource = 1;
                            ufeLayer.DLTField = (int)(layer.Shape as ShapeTime).DisplayFormat;
                            break;
                        case LayerType.Temp:
                            ufeLayer.DLTSource = 2;
                            ufeLayer.DLTField = (int)(layer.Shape as ShapeTemp).DisplayFormat + 1;
                            break;

                    }
                    ufeLayer.ScrollEffect = ConvertScrollEffectType(layer);
                }

                ufeLayer.DLTisLocal = true;
                var pair = shapeConverter.Convert(layer.Shape);
                if (pair != null)
                {
                    Shapes.Add(pair);
                    if (!string.IsNullOrEmpty(pair.File.ToFilePath))
                        ufeLayer.FileName = pair.File.Id;
                }
            }

            return ufeLayer;
        }


        #region Convert ScrollEffectType functions
        // <summary>
        /// Function: Convert ScrollEffectType
        /// Author  : Jerry Xu
        /// Date    : 2008-12-17
        /// </summary>
        /// <param name="layer">ShapeLayer</param>
        /// <returns>ScrollEffectType</returns>
        private static ScrollEffectType ConvertScrollEffectType(ShapeLayer layer)
        {
            //ScrollEffectType effectType = new ScrollEffectType();

            var effectType = ConvertScrollEffectTypeBaseInfo(layer.Shape as ShapeDynamicTextBase);
            //switch (item.Shape.LayerType)
            //{
            //    case LayerType.Time:
            //        ShapeTime shapeTime = item.Shape as ShapeTime;
            //        effectType.Content.Time = ConvertVariableTimeType(shapeTime, 1);
            //        break;
            //    case LayerType.Temp:
            //        ShapeTemp shapeTemp = item.Shape as ShapeTemp;
            //        effectType.Content.Temp = ConvertVariableTempType(shapeTemp, 2);
            //        break;
            //    case LayerType.DynamicText:
            //        ShapeDynamicText shapeText = item.Shape as ShapeDynamicText;
            //        effectType.Content.Text = ConvertTextType(shapeText);
            //        break;
            //}

            return effectType;
        }

        // <summary>
        /// Function: Convert ScrollEffectType base info
        /// Author  : Jerry Xu
        /// Date    : 2008-12-17
        /// </summary>
        /// <param name="shape">ShapeDynamicTextBase</param>
        /// <returns>ScrollEffectType</returns>
        private static ScrollEffectType ConvertScrollEffectTypeBaseInfo(ShapeDynamicTextBase shape)
        {
            ScrollEffectType effectType = new ScrollEffectType();

            effectType.IsScrolling = shape.RollWay == RollWay.None ? false : true;
            if (shape.RollWay == RollWay.BottomToTop)
                effectType.Direction = ScrollDirectionType.UP;
            if (shape.RollWay == RollWay.TopToBottom)
                effectType.Direction = ScrollDirectionType.DOWN;
            if (shape.RollWay == RollWay.LeftToRight)
                effectType.Direction = ScrollDirectionType.RIGHT;
            if (shape.RollWay == RollWay.RightToLeft)
                effectType.Direction = ScrollDirectionType.LEFT;
            effectType.Speed = float.Parse(shape.RollRate.ToString());
            return effectType;
        }

        // <summary>
        /// Function: Convert FontInfo
        /// Author  : Jerry Xu
        /// Date    : 2008-12-17
        /// </summary>
        /// <param name="shape">ShapeTime</param>
        /// <returns>VariableTimeType</returns>
        private static FontInfoType ConvertFontInfoType(ShapeTextBase shape)
        {
            FontInfoType font = new FontInfoType();
            font.Font = shape.Font.FontFileName;// ? shape.Font.FontFileName + ".TTF" : shape.Font.FontFileName + ".FON";
            Console.WriteLine("MessageConverter Write ===> " + shape.Font.FontFileName);

            //font.Font = shape.Font.Name;
            //font.FontColor = int.Parse(ConverterHelper.ColorToString(shape.ForeColor,NumberType.Decimal));
            //font.FontColor = UInt32.Parse(ConverterHelper.ColorToString(shape.ForeColor, NumberType.Decimal));
            font.FontColor = ConverterHelper.ColorToString(shape.ConveredForeColor(shape.SignType), shape.SignType);//UInt32.Parse(ConverterHelper.ColorToString(shape.ForeColor, NumberType.Hex), NumberStyles.HexNumber);
            font.FontKerning = shape.KernAmount;
            font.FontLead = shape.LeadAmount;
            font.FontSize = shape.Font.Size;

            //font.FontKerning = shape.
            font.Bold = (shape.Font.Style & FontStyle.Bold) == FontStyle.Bold;
            font.Italic = (shape.Font.Style & FontStyle.Italic) == FontStyle.Italic;

            ShapeDynamicTextBase dFont = shape as ShapeDynamicTextBase;

#if VERSION_1
            if (dFont != null)
            {
                font.HorizontalJustify = dFont.Align;
                font.VerticalJustify = dFont.Valign;
            }
            else
            {
                font.HorizontalJustify = shape.TextAlignment;
                font.VerticalJustify = shape.TextVAlignment;
            }
             font.Effect = shape.TextEffect.Effect;
#else
            if (dFont != null)
            {
                font.HorizontalJustify = (TextHorzJustify)((int)dFont.Align);
                font.VerticalJustify = (TextVertJustify)((int)dFont.Valign);
            }
            else
            {
                font.HorizontalJustify = (TextHorzJustify)((int)shape.TextAlignment);
                font.VerticalJustify = (TextVertJustify)((int)shape.TextVAlignment);
            }
            font.Effect =ConvertTextEffect(shape.TextEffect.Effect);
#endif
            //font.HorizontalJustify = shape.TextAlignment;
            //switch(shape.TextVAlignment)
            //{
            //    case Valign.BOTTOM:
            //    case Valign.TOP:
            //        font.VerticalJustify = shape.TextVAlignment;
            //        break;
            //    case Valign.MIDDLE:
            //        font.VerticalJustify = Valign.MIDDLE;
            //        break;
            //}
            //font.VerticalJustify = shape.TextVAlignment; 


            font.ShadeXOffset = shape.TextEffect.ShadowLateralShift;
            font.ShadeYOffset = shape.TextEffect.ShadowVerticalShift;
            font.BubbleSize = shape.TextEffect.OutlineWidth;
            font.EffectColor = ConverterHelper.ColorToString(shape.TextEffect.ConveredEffectColor(shape.SignType), shape.SignType);
            font.BackgroundColor = ConverterHelper.ColorToString(shape.ConveredBackColor(shape.SignType), shape.SignType);

            //v1_9
            //font.Underline = shape.TextAlignment.Underline;
            //font.WordWrap = shape.TextEffect.WordWrap;
            return font;
        }

        private static ProWrite.UFE.Entity.TextEffect ConvertTextEffect(OutlineShadowType source)
        {
            if (source == OutlineShadowType.NONE)
                return ProWrite.UFE.Entity.TextEffect.NONE;
            if (source == OutlineShadowType.BubbleSurround)
                return ProWrite.UFE.Entity.TextEffect.BUBBLE;
            if (source == OutlineShadowType.SHADED)
                return ProWrite.UFE.Entity.TextEffect.SHADED;
            return ProWrite.UFE.Entity.TextEffect.NONE;
        }


        // <summary>
        /// Function: Convert VariableTempType
        /// Author  : Jerry Xu
        /// Date    : 2008-12-17
        /// </summary>
        /// <param name="shape">ShapeTemp</param>
        /// <returns>VariableTempType</returns>
        private static VariableTempType ConvertVariableTempType(ShapeTemp shape, int source)
        {
            VariableTempType effectType = new VariableTempType();
            effectType.FontInfo = ConvertFontInfoType(shape);
            //effectType.Format = shape.DisplayFormat;
            effectType.DLTSource = source;
            effectType.DLTField = (int)shape.DisplayFormat + 1;

            return effectType;
        }

        // <summary>
        /// Function: Convert TextType
        /// Author  : Jerry Xu
        /// Date    : 2008-12-17
        /// </summary>
        /// <param name="shape">ShapeDynamicText</param>
        /// <returns>TextType</returns>
        private static TextType? ConvertTextType(ShapeBase shape)
        {
            var s = shape as ShapeTextBase;
            if (s == null)
                return null;
            TextType effectType = new TextType();
            effectType.FontInfo = ConvertFontInfoType(s);
            effectType.DisplayText = s.Text;

            return effectType;
        }
        #endregion

        /// <summary>
        /// Function: Convert Core.LayerType to UFE.Entity.LayerType
        /// Author  : Jerry Xu
        /// Date    : 2008-12-2
        /// </summary>
        /// <param name="type">Core.LayerType</param>
        /// <returns>UFE.Entity.LayerType</returns>
        private static ProWrite.UFE.Entity.ContentType ConvertLayerType(ProWrite.Core.LayerType type)
        {
            switch (type)
            {
                case ProWrite.Core.LayerType.Paint:
                    return ProWrite.UFE.Entity.ContentType.PAINT;
                case ProWrite.Core.LayerType.Text:
                    return ProWrite.UFE.Entity.ContentType.TEXT;
                case ProWrite.Core.LayerType.Image:
                    return ProWrite.UFE.Entity.ContentType.PNG;
                case ProWrite.Core.LayerType.Video:
                    return ProWrite.UFE.Entity.ContentType.MPEG;
                case ProWrite.Core.LayerType.Time:
                case ProWrite.Core.LayerType.Temp:
                case ProWrite.Core.LayerType.DynamicText:
                    return ProWrite.UFE.Entity.ContentType.DLT;
            }

            return ContentType.PNG;
        }

        /// <summary>
        /// Function: Convert Rectangle to Bounds
        /// Author  : Jerry Xu
        /// Date    : 2008-12-2
        /// </summary>
        /// <param name="shape">ShapeBase</param>
        /// <returns>Bounds</returns>
        private static ProWrite.UFE.Entity.Rectangle ConvertLayerBounds(ShapeBase shape)
        {
            ProWrite.UFE.Entity.Rectangle bounds = new ProWrite.UFE.Entity.Rectangle();
            //ShapeImage shapeImage = shape as ShapeImage;
            if (shape.Type == ShapeType.ShapeDraw || shape.Type == ShapeType.Video)
            {
                bounds.TopLeft.X = 0;
                bounds.TopLeft.Y = 0;
                bounds.BottomRight.X = shape.SignSize.Width;
                bounds.BottomRight.Y = shape.SignSize.Height;
            }
            //else if (shape.Type == ShapeType.Video)
            //{
            //    bounds.TopLeft.X = 0;
            //    bounds.TopLeft.Y = 0;
            //    bounds.BottomRight.X = shape.Rect.Width;
            //    bounds.BottomRight.Y = shape.Rect.Height;
            //}
            else
            {
                bounds.TopLeft.X = shape.Rect.X;
                bounds.TopLeft.Y = shape.Rect.Y;
                bounds.BottomRight.X = shape.Rect.X + shape.Rect.Width;
                bounds.BottomRight.Y = shape.Rect.Y + shape.Rect.Height;
            }

            return bounds;
        }
    }
}
