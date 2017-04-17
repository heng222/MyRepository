using System;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;
using ProWrite.Entity.DES;
using System.Drawing;
using ProWrite.Core;
using ProWrite.DES;


namespace ProWrite.UI.Controls.Editor
{
    public partial class MessageControl
    {
        private void InitPlayControl()
        {
            orgiPlayLeft = trackBar1.Left;
            playPanel.Visible = false;
            _playService = new PlayService(this);
            playStopBar.SupportNext = false;
            playStopBar.RegisterService(_playService);
        }

        private class PlayService:IPlayService
        {
            private MessageControl _messageControl;
            private LayerHelper _desHelper = new LayerHelper();
            private int origPlayValue = 0;

            public PlayService(MessageControl messageControl)
            {
                _messageControl = messageControl;
            }

            public string PlayName
            {
                get { return _messageControl._model.Name; }
            }

            public PlayMode Mode
            {
                get { return PlayMode.Editor; }
            }

            public Control PlayPanel
            {
                get { return _messageControl.shapeControl; }
            }

            public void OnStop()
            {
                _messageControl.EnableControl(true);
                _messageControl.playPanel.Visible = false;
                _messageControl.trackBar1.PlayValue = origPlayValue;
            }

            public VideoLayerCollection[] OnPlay()
            {
              

                VideoLayerCollection[] videoArr = new VideoLayerCollection[] { _desHelper.PopulateData(_messageControl) };
               
                return videoArr;
            }

            public void OnPrevious() { }
            public void OnNext() { }

            public void OnPlayCompleted()
            {
                _messageControl.EnableControl(true);
                _messageControl.trackBar1.PlayValue = origPlayValue;
                _messageControl.playPanel.Visible = false;
                _messageControl.Invalidate();
            }

            public void OnPlaying()
            {
                _messageControl.trackBar1.PlayValue++;
            }

        }

        private void EnableControl(bool flag)
        {
            layerEditor.Enabled = flag;
            this.lblNew.Enabled = flag;
            this.lblRecycle.Enabled = flag;
            this.btnThumbNailImage.Enabled = flag;
            this.hScrollBar.Enabled = flag;
            this.trackBar1.Enabled = flag;
            ControlService.PropertyGrid.Enabled = flag;
        }
    }
}
