//---------------------------------------------------------------------
//
// File: DesHelper.cs
//
// Description:
//  
//
// Author: Jerry Xu
//
// DateTime:2008-5-15
//
// Modify history:
//      Jerry Xu 2008-6-23 All the methods in Common and Dataches were replaced with these methods in DataGate
//      Kevin    2008-6-23 Update sign type string to SignType      
//      Jerry Xu 2008-6-25 Resource string
//      Jerry Xu 2008-6-27 Log
//      Jerry Xu 2008-7-1  Record the system exception to the log  
//      Jerry Xu 2008-7-3  Add comments
//      Jerry Xu 2008-7-3  private variant:add "_"
//      Jerry Xu 2009-5-22 Update method:PopulateData(ShapeLayer[] layers)
//      Jerry Xu 2009-6-5  Insert method:PopulateData(MessageInfo msg ,Rectangle imageSize)
//
// Copyright (C) 2008 by Trans-Lux All rights reserved.
// 
//---------------------------------------------------------------------

using System;
using System.Collections.Generic;
using System.Text;
using System.Linq;
using ProWrite.Entity.DES;
using ProWrite.Entity.Library;
using ProWrite.Entity.Shape;
using System.Data;
using System.Drawing;
using ProWrite.Resources;
using ProWrite.Core;
using ProWrite.UI.Controls.Common;
using ProWrite.UI.Controls.Editor;

namespace ProWrite.UI.Controls
{
    /// <summary>
    /// Play data convert class
    /// </summary>
    public class LayerHelper
    {
        #region Variant define
        private short _level = 0;
        private VideoLayerCollection _videoLayers = new VideoLayerCollection();

        #endregion

        public LayerHelper()
        {
        }

        #region Function define
        #region Append item
        /// <summary>
        /// Function:Append item
        /// Description:
        /// Author:Kevin
        /// Date:2008-7-2
        /// </summary>
        /// <param name="item">item</param>
        private bool AppendLayer(ShapeLayer layer)
        {
            Layer videoLayer = DESLayerConverter.Instance.Convert(layer); //layer.ToVideoLayer();
            if (videoLayer == null)
                return false;

            videoLayer.Level = _level++;//(short)item.LayerIndex;
            _videoLayers.Add(videoLayer);
            return true;
        }
        #endregion

        #region Get VideoLayerCollection by item
        /// <summary>
        /// Function:Get VideoLayerCollection
        /// Description:
        /// Author:Kevin
        /// Date:2008-7-2
        /// </summary>
        /// <param name="dlayer">Daynamic item</param>
        /// <param name="slayer">static item</param>
        /// <returns>VideoLayerCollection</returns>
        public VideoLayerCollection PopulateData(ShapeLayer[] layers)
        {
            var shapeLayers = layers.Reverse();
            _videoLayers = new VideoLayerCollection();
            long PlayLength = 0;
            if (layers == null || layers.Length < 1)
                return _videoLayers;

            _level = 0;

            foreach (var layer in shapeLayers)
            {
                if (!layer.IsEmpty)
                {
                    if (AppendLayer(layer))
                    {
                        if (layer.EndTime > PlayLength)
                            PlayLength = (long)layer.EndTime;
                    }
                }
            }

            //CheckMarquee();
            _videoLayers.PlayLength = PlayLength;
            return _videoLayers;
        }

        public VideoLayerCollection PopulateData(MessageControl msgCtrl)
        {
            var layers = msgCtrl.Layers;
            var videoLayers = PopulateData(layers);
            videoLayers.SignType = msgCtrl.Sign.Type;
            videoLayers.VideoSize = msgCtrl.ShapeControl.Size;
            videoLayers.BackColor = msgCtrl.ShapeControl.BackColor;
            videoLayers.Name = msgCtrl.Model.Name;
            videoLayers.Zoom = msgCtrl.Zoom;
            videoLayers.EmphasisEffect = msgCtrl.Model.EmphasisEffect;
            return videoLayers;
        }

        public VideoLayerCollection PopulateData(MessageInfo msg ,Rectangle imageSize)
        {
            var layers = msg.Items;
            var videoLayers = PopulateData(layers);
            videoLayers.SignType = ControlService.SignCombo.Current.Type;
            videoLayers.VideoSize = imageSize.Size;
            videoLayers.BackColor = msg.BackColor;
            videoLayers.Name =  msg.Name;
            videoLayers.Zoom = msg.Zoom;
            videoLayers.EmphasisEffect = msg.EmphasisEffect;
            return videoLayers;
        }

      
        private void AppendEmptyLayer()
        {
            ShapeLayer layer = new ShapeLayer();
            layer.Shape = new DefaultShape();
            layer.EmphasisEffect.Duration = _videoLayers[0].EndTime - _videoLayers[0].StartTime;
            AppendLayer(layer);
        }

        #endregion

        #endregion
    }
}
