using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Drawing;
using ProWrite.Core;

namespace ProWrite.UI.Controls.Editor
{
    public partial class LayerControl
    {
        class EffectMouseEventHook
        {
            private LayerControl _layerCtrl;
            private Point _lastPoint = Point.Empty;
            internal int _lastEffectContainerWidth = 0; 

            public EffectMouseEventHook(LayerControl layerCtrl)
            {
                _layerCtrl = layerCtrl;
            }

            private void MouseDown(object sender, MouseEventArgs e)
            {
                UndoService.BeginTransaction("Effect mouse down event.");
                if (e.Button == MouseButtons.Left)
                {
                    _lastPoint.X = Cursor.Position.X;
                    _lastPoint.Y = Cursor.Position.Y;
                }

                UndoService.AddAction(new EffectMouseEventAction(_layerCtrl));
            }

            private void MouseMove(object sender, MouseEventArgs e)
            {
                if (e.Button == MouseButtons.Left)
                {
                    Point currentPoint = new Point(Cursor.Position.X, Cursor.Position.Y);
                    var offset = currentPoint.X - _lastPoint.X;
                    if (Math.Abs(offset) >= Constance.Effect.UnitWidth)
                    {
                        offset = offset/Constance.Effect.UnitWidth*Constance.Effect.UnitWidth;
                        int left = 0;
                        if (_layerCtrl.plLeft.Width + offset <= 0)
                        {
                            left = _layerCtrl.plLeft.Width;
                            _layerCtrl.plLeft.Width = 0;
                            _layerCtrl.plRight.Width += left;

                            _lastPoint.X = _lastPoint.X - left;
                            _lastPoint.Y = currentPoint.Y;

                        }
                        else
                        {
                            _layerCtrl.plLeft.Width += offset;
                            _layerCtrl.plRight.Width -= offset;
                            _lastPoint.X = currentPoint.X;
                            _lastPoint.Y = currentPoint.Y;
                        }
                        _layerCtrl.MoveUpdateEffect();

                        MessageControl.Current.SetShapeVisible(_layerCtrl);
                        //_layerCtrl.MoveUpdateEffect();
                        ControlService.RefreshPropertyGrid(_layerCtrl._layer);
                        MessageControl.Current.ChangedService.MarkChanged();
                        //SessionState.Instance["EffectMouseMove"] = true;

                        _layerCtrl.SetMaxWidth();
                    }
                    //SessionState.Instance.Remove("EffectMouseMove");
                }
            }

            private void MouseUp(object sender, MouseEventArgs e)
            {
                _layerCtrl.OnLayerMouseUp(sender, e);

                UndoService.Commit();
            }


            public void SubscribeEvent()
            {
                SubscribeMouseEvent(_layerCtrl.splitter1);
                SubscribeMouseEvent(_layerCtrl.splitter2);
                SubscribeMouseEvent(_layerCtrl.splitter3);
                SubscribeMouseEvent(_layerCtrl.splitter4);
                SubscribeMouseEvent(_layerCtrl.ctlEmphasis);
                SubscribeMouseEvent(_layerCtrl.ctlEntryEffect);
                SubscribeMouseEvent(_layerCtrl.ctlExitEffect);

               
                _lastEffectContainerWidth = _layerCtrl.EffectContainer.Width;
                _layerCtrl.EffectContainer.SizeChanged += new EventHandler(EffectContainer_SizeChanged);
            }

            private void SubscribeMouseEvent(Control ctrl)
            {
                ctrl.MouseDown += MouseDown;
                ctrl.MouseMove += MouseMove;
                ctrl.MouseUp += MouseUp;
            }

            private void UnsubscribeMouseEvent(Control ctrl)
            {
                ctrl.MouseDown -= MouseDown;
                ctrl.MouseMove -= MouseMove;
                ctrl.MouseUp -= MouseUp;
            }

          

            void EffectContainer_SizeChanged(object sender, EventArgs e)
            {
                if (_layerCtrl.EffectContainer.Width != _lastEffectContainerWidth)
                {
                    _layerCtrl.EffectContainer.Width = _lastEffectContainerWidth;
                    _layerCtrl.HScrollBarCtrl.Maximum = _layerCtrl.EffectContainer.Width +_.ScrollWidth;
                    _layerCtrl.TrackBarCtrl.Width += _layerCtrl.EffectContainer.Width + _.ScrollWidth;
                }
            }

            public void UnSubscribeEvent()
            {
                UnsubscribeMouseEvent(_layerCtrl.splitter1);
                UnsubscribeMouseEvent(_layerCtrl.splitter2);
                UnsubscribeMouseEvent(_layerCtrl.splitter3);
                UnsubscribeMouseEvent(_layerCtrl.splitter4);
                UnsubscribeMouseEvent(_layerCtrl.ctlEmphasis);
                UnsubscribeMouseEvent(_layerCtrl.ctlEntryEffect);
                UnsubscribeMouseEvent(_layerCtrl.ctlExitEffect);

                _layerCtrl.EffectContainer.SizeChanged -= EffectContainer_SizeChanged;
            }
        }

        class EffectMouseEventAction:UndoAction
        {
            private LayerControl layerCtrl;
            private int[] OldData;

            public EffectMouseEventAction(LayerControl layerCtrl)
            {
                this.layerCtrl = layerCtrl;
                OldData = new int[]{ layerCtrl.EffectContainer.Left, layerCtrl.splitter1.Left, layerCtrl.splitter2.Left, layerCtrl.splitter3.Left, layerCtrl.splitter4.Left };
            }

            public override void Undo()
            {
                var tmpData = new int[] { layerCtrl.EffectContainer.Left, layerCtrl.splitter1.Left, layerCtrl.splitter2.Left, layerCtrl.splitter3.Left, layerCtrl.splitter4.Left };
                layerCtrl.EffectContainer.Left = OldData[0];
                layerCtrl.splitter1.Left = OldData[1];
                layerCtrl.splitter2.Left = OldData[2];
                layerCtrl.splitter3.Left = OldData[3];
                layerCtrl.splitter4.Left = OldData[4];

                OldData = tmpData;
            }

            public override void Redo()
            {
                Undo();
            }
        }
    }
}
