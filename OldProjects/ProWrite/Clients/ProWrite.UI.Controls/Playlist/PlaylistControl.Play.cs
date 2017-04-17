using System;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;
using System.Drawing;
using ProWrite.Entity.DES;
using ProWrite.Core;
using ProWrite.Entity.Library;
using ProWrite.Resources;
using ProWrite.UI.Controls.Common;
using ProWrite.Entity.Shape;

namespace ProWrite.UI.Controls.Playlist
{
	public partial class PlaylistControl
	{
        private void InitPlayControl()
        {
            _initPlayLeft = trackBar1.Left;
            playPanel.Visible = true;
            _playService = new PlayService(this);
            playStopBar.RegisterService(_playService);
        }

        private class PlayService : IPlayService
        {
            private PlaylistControl _playlistControl;
            private LayerHelper _desHelper = new LayerHelper();
            private int origPlayValue = 0;
            List<VideoLayerCollection> _msgs;

            public PlayService(PlaylistControl playlistControl)
            {
                _playlistControl = playlistControl;
            }

            public string PlayName
            {
                get { return _playlistControl._model.Name; }
            }

            public PlayMode Mode
            {
                get { return PlayMode.Playlist; }
            }

            public Control PlayPanel
            {
                get { return _playlistControl.playPanel; }
            }

            private ShapeLayer[] ReverseLayer(ShapeLayer[] items)
            {
                List<ShapeLayer> layers = new List<ShapeLayer>();
                foreach (ShapeLayer layer in items)
                {
                    layers.Add(layer);
                }
                layers.Reverse();
                return layers.ToArray();
            }

            public VideoLayerCollection[] OnPlay()
            {

                _playlistControl.LoadModelInfo();

                _playlistControl.trackBar1.PlayValue = 0;
                origPlayValue = _playlistControl.trackBar1.PlayValue;
                _playlistControl.playPanel.Visible = true;
                _msgs = new List<VideoLayerCollection>();
                foreach (PlaylistItemControl item in _playlistControl.dragDropControl.Controls)
                {
                    switch (item.PlaylistItem.Target.Type)
                    {
                        case LibraryType.Message:
                            //ProWrite.DES.DESHelper.CreateVideo(item.PlaylistItem.Target.Copy() as MessageInfo, "d:\\aaa.mpeg");
                            var msg = NewLayer(item.PlaylistItem.Target.Copy() as MessageInfo,
                                                item.PlaylistItem.Target.Length, "", true, null);
                            msg.Zoom = _playlistControl._Zoom;
                            _msgs.Add(msg);

                            //_msgs.Add(NewLayer(item.PlaylistItem.Target.Copy() as MessageInfo, item.PlaylistItem.Target.Length, "", true, null));
                            break;
                        case LibraryType.TimeSliceGroup:
                            TimeSliceGroupInfo group = null;
                            MessageInfo message = null;
                            group = LibraryGroup.Current.TimeSliceGroups.GetByName(item.PlaylistItem.Target.Name);
                            if (group.Items != null && group.Items.Length > 0)
                            {
                                for (int i = 0; i < group.Items.Length; i++)
                                {
                                    if (group.Items[i].Name == ((TimeSliceGroupAdapterInfo)item.PlaylistItem).CurrentMessageAdapterName && group.Items[i].Target != null && group.Items[i].IsActive)
                                    {
                                        message = group.Items[i].Target as MessageInfo;
                                        break;
                                    }
                                }
                                if (message == null)
                                {
                                    DataGate.SetPlaylistTimeSlieceGroupCurrentMessageAdapterName(_playlistControl._model, false);
                                    for (int i = 0; i < group.Items.Length; i++)
                                    {
                                        if (group.Items[i].Name == ((TimeSliceGroupAdapterInfo)item.PlaylistItem).CurrentMessageAdapterName && group.Items[i].Target != null && group.Items[i].IsActive)
                                        {
                                            message = group.Items[i].Target as MessageInfo;
                                            break;
                                        }
                                    }
                                }
                            }

                            if (message != null)
                            {
                                _msgs.Add(NewLayer(message.Copy() as MessageInfo,group.Length, group.Name,true, LibraryType.TimeSliceGroup));
                            }
                            break;
                        case LibraryType.Playlist:
                            //add by michael 2008-12-8
                            // edit by Louis 2009-1-5
                            PlaylistInfo list = LibraryGroup.Current.Playlists.GetByName(item.PlaylistItem.Target.Name);
                            if (list != null && list.AllMessages.Length > 0)
                            {
                                _msgs.Add(NewLayer(list.AllMessages[0].Copy() as MessageInfo, list.AllMessages[0].Length, list.Name, true, LibraryType.Playlist));
                                for (int i = 1; i < list.AllMessages.Length; i++)
                                    _msgs.Add(NewLayer(list.AllMessages[i].Copy() as MessageInfo, list.AllMessages[i].Length, list.Name, false, LibraryType.Playlist));
                            }
                            //foreach (MessageInfo mes in list.AllMessages)
                            //{
                            //    _msgs.Add(NewLayer(mes.Copy() as MessageInfo, mes.Length, list.Name, LibraryType.Playlist));
                            //}
                            break;
                    }
                }
                if(_msgs.Count>0)
                    _playlistControl.EnableControl(false);
                return _msgs.ToArray();
            }
            
            //add by michael 2008-12-8
            private VideoLayerCollection NewLayer(MessageInfo mes, long playLength, string ParentName, bool isNewStart, LibraryType? groupType)
            {
                VideoLayerCollection layer = null;
                foreach (ShapeLayer sl in mes.Items)
                {
                    //sl.Shape.VirtualBounds = Common.CommonHelper.GetRectangleBySign(sl.Shape.VirtualBounds, sl.Shape.SignSize, _playlistControl._signSize, mes.Zoom);
                    //sl.Shape.DestBounds = Common.CommonHelper.GetRectangleBySign(sl.Shape.DestBounds, sl.Shape.SignSize, _playlistControl._signSize, mes.Zoom);
                    if (sl.Shape.Type == ShapeType.ShapeDraw)
                    {
                        foreach (ShapePaint s in (sl.Shape as ShapeDraw).Childs)
                        {
                            s.VirtualBounds = Common.CommonHelper.GetVirtualBoundsBySign(s, _playlistControl._signSize, _playlistControl._Zoom);
                            s.Populate(s.VirtualLocation, s.VirtualBounds.Size, ControlService.SignCombo.Current.Type, _playlistControl._signSize, _playlistControl._Zoom);
                        }
                        (sl.Shape as ShapeDraw).PopulateSignInfo(ControlService.SignCombo.Current.Type, _playlistControl._signSize, sl.Shape.Zoom);
                    }
                    else
                    {
                        sl.Shape.VirtualBounds = Common.CommonHelper.GetVirtualBoundsBySign(sl.Shape, _playlistControl._signSize, _playlistControl._Zoom);
                        sl.Shape.Populate(sl.Shape.VirtualLocation, sl.Shape.VirtualBounds.Size, ControlService.SignCombo.Current.Type, _playlistControl._signSize, _playlistControl._Zoom);
                        if (sl.Shape.Type == ShapeType.Image)
                            (sl.Shape as ShapeImage).ComputeDestBoundBatchLoad();
                        if (sl.Shape.Type == ShapeType.Video)
                            (sl.Shape as ShapeVideo).ComputeDestBound();
                        //sl.Shape.DestBounds = Common.CommonHelper.GetRectangleBySign(sl.Shape.DestBounds, sl.Shape.SignSize, _playlistControl._signSize, _playlistControl._Zoom);
                    }

                    //sl.Shape.VirtualBounds = Common.CommonHelper.GetRectangleBySign(sl.Shape.VirtualBounds, sl.Shape.SignSize, _playlistControl._signSize, _playlistControl._Zoom);

                }
                layer = _desHelper.PopulateData(ReverseLayer(mes.Items));
                layer.SignType = ControlService.SignCombo.SignType;
                //item.VideoSize = new Size(ControlService.SignCombo.Current.Width, ControlService.SignCombo.Current.Height);
                layer.VideoSize = _playlistControl.playPanel.Size;
                layer.Name = mes.Name;
                layer.Zoom = _playlistControl._Zoom;
                layer.BackColor = mes.BackColor;
                layer.PlayLength = playLength;
                layer.ParentName = ParentName;
                layer.EmphasisEffect = mes.EmphasisEffect;
                layer.IsNewStart = isNewStart;
                layer.GroupType = groupType;
                return layer;
            }

            public void OnPlayCompleted()
            {
                _playlistControl.trackBar1.PlayValue = origPlayValue;
                _playlistControl.playPanel.Visible = true;
				_playlistControl.EnableControl(true);
                _playlistControl.Invalidate();           
                DataGate.SetPlaylistTimeSlieceGroupCurrentMessageAdapterName(_playlistControl._model, false);
            }

            public void OnPlaying()
            {
                _playlistControl.trackBar1.PlayValue++;//_messageControl.trackBar1.UnitWidth;                
            }

        }
	}
}
