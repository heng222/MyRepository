//---------------------------------------------------------------------
//
// File: VideoGenerator.cs
//      
// Description:
//      VideoGenerator class
//
// Author: 
//
// Modify History:
//      2009-1-14 Jerry Xu Update method:CreateVideo(MessageInfo mes, string fileurl)
//
// Copyright (C) 2008 by Trans-Lux All rights reserved.
// 
//---------------------------------------------------------------------

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ProWrite.Entity;
using ProWrite.Entity.Library;
using ProWrite.Entity.DES;
using ProWrite.Entity.Shape;
using ProWrite.Core;
using System.Drawing;
using DirectShowLib;
using System.Threading;

namespace ProWrite.DES
{
    public class VideoGenerator :  IVideoGenerator
    {
       // private static IDESPaintVisitor Visitor = new DESPaintVisitor();
        public bool CreateVideo(MessageInfo mes, string fileurl)
        {
            Check.Require(mes, "mes", Check.NotNull);
            Check.Require(fileurl, "fileurl", Check.NotNullOrEmpty);
            Check.Require(mes.Size != Size.Empty, "mes.Size != null");

            bool result = false;
            var layers = PopulateData(mes.Items);

            foreach (Layer layer in layers)
            {
                layer.Rect = new Rectangle(layer.Rect.X / mes.Zoom, layer.Rect.Y / mes.Zoom, layer.Rect.Width / mes.Zoom, layer.Rect.Height / mes.Zoom);
                //item.Rect = new Rectangle(item.Rect.Height / mes.Zoom, item.Rect.Width / mes.Zoom, item.Rect.X / mes.Zoom, item.Rect.Y / mes.Zoom);
            }

            layers.BackColor = mes.BackColor;
            layers.SignType = SignType.RGB;
            //layers.VideoSize = mes.GetSignSize();
            layers.VideoSize = mes.Items[0].Shape.SignSize;
            layers.Name = mes.Name;
            layers.Zoom = 1;
            //layers.Zoom = mes.Zoom;
            layers.PlayLength = mes.Length;
            layers.ParentName = "";
            layers.EmphasisEffect = mes.EmphasisEffect;
            if(layers.Count>1)            
                layers.Sort(new SortComparer<Layer>("Level", false));
            var DynamicTextDS = layers.FindAll(item => { return item.LayerType == LayerType.DynamicText; });

            IBaseFilter ibfVideoCompressor = GetVideoCompressor("Indeo?video 5.10 Compression Filter");
            PlayState PlayState = ProWrite.Core.PlayState.Stop;

            var des = new DESCombine(DESConsts.FPS, DESConsts.BitCount, layers.VideoSize.Width, layers.VideoSize.Height, layers);
            des.Completed += delegate { PlayState = PlayState.Stop; };
            des.RenderToVideo(MediaSubType.Mpeg2Video, fileurl, ibfVideoCompressor, null, null, null, DynamicTextDS, 0, mes.Length, layers.VideoSize);
            des.StartRendering();

            PlayState = PlayState.Run;
            while (PlayState == PlayState.Run)
            {
                Thread.Sleep(100);
            }

            des.Dispose();
            des = null;

            if (System.IO.File.Exists(fileurl))
                result = true;
           
            return result;
        }

        /// <summary>
        /// 根据名称返回相应的Filter
        /// </summary>
        /// <param name="sName"></param>
        private IBaseFilter GetVideoCompressor(string sName)
        {
            IBaseFilter ibf = null;

            DsDevice[] dsd = DsDevice.GetDevicesOfCat(FilterCategory.VideoCompressorCategory);
            int x;

            for (x = 0; x < dsd.Length; x++)
            {
                if (dsd[x].Name == sName)
                {
                    Guid grf = typeof(IBaseFilter).GUID;
                    object o;
                    dsd[x].Mon.BindToObject(null, null, ref grf, out o);
                    ibf = o as IBaseFilter;
                    break;
                }
            }

            return ibf;
        }


        private VideoLayerCollection PopulateData(ShapeLayer[] layers)
        {
            int level = 0;
            VideoLayerCollection videoLayers = new VideoLayerCollection();
            Layer layer;

            long PlayLength = 0;
            if (layers == null || layers.Length < 1)
                return videoLayers;

            foreach (var item in layers)
            {
                if (item.IsVisible)
                {
                    if (item.Shape.Type != ShapeType.Temperature && item.Shape.Type != ShapeType.Time)
                    {
                        //item.Accept(Visitor);
                        //layer = item.ToVideoLayer();
                        layer = DESLayerConverter.Instance.Convert(item);
                        layer.Level = level++;
                        videoLayers.Add(layer);
                    }
                    if (item.EndTime > PlayLength)
                        PlayLength = (long)item.EndTime;
                }
            }

            videoLayers.PlayLength = PlayLength;
            return videoLayers;
        }
    }
}
