using System;
using System.Collections.Generic;
using System.Text;
using ProWrite.Core;

using ProWrite.Entity;
using ProWrite.Entity.DES;
using ProWrite.Entity.Shape;
using System.Drawing;
using ProWrite.Resources;
using System.Windows.Forms;
using System.ComponentModel;

namespace ProWrite.UI.Controls.Editor
{
    public partial class LayerControl
    {
        public delegate bool PopulateTimeLengthHandler(int layerId, int pos);
        public delegate void DragLayerHandler(LayerControl target, LayerControl data);
        public delegate void LayerMouseUpHandler(LayerControl owner, Control sender, MouseEventArgs e);
        //public delegate void LayerMouseLeaveHandler(LayerControl owner, Control sender, EventArgs e);

        [NonSerialized]
        private PopulateTimeLengthHandler _populateTimeLength;
        [NonSerialized]
        private DragLayerHandler _dragLayer;
        [NonSerialized]
        private LayerMouseUpHandler _layerMouseUp;

        public event LayerMouseUpHandler LayerMouseUp
        {
            add { _layerMouseUp += value; }
            remove { _layerMouseUp -= value; }
        }
        //[NonSerialized]
        //private LayerMouseLeaveHandler _layerMouseLeave;

        //public event LayerMouseLeaveHandler LayerMouseLeave
        //{
        //    add { _layerMouseLeave += value; }
        //    remove { _layerMouseLeave -= value; }
        //}
        public event PopulateTimeLengthHandler PopulateTimeLength
        {
            add { _populateTimeLength += value; }
            remove { _populateTimeLength -= value; }
        }

        public event DragLayerHandler DragLayer
        {
            add 
            { 
                if(_dragLayer == null)
                    _dragLayer += value;
            }
            remove { _dragLayer -= value; }
        }

        private void OnDragLayer(LayerControl data)
        {
            if (data != null
                && _dragLayer != null
                && _layer.Shape.IsDynamicLayer == data._layer.Shape.IsDynamicLayer && !data.Shape.IsBackground
                && !_layer.Shape.IsBackground)
            {
                _dragLayer(this, data);
            }
        }

       

        internal abstract class Images
        {
            public static readonly Image[] ImageList;
            public static readonly int Visible = 7;
            public static readonly int UnVisible = -1;
            static Images()
            {
                ImageList = new Image[]
                {
                    Resource.GetImage(Resource.Images.Text30)
                    ,Resource.GetImage(Resource.Images.shape30)
                    ,Resource.GetImage(Resource.Images.Image30)
                    ,Resource.GetImage(Resource.Images.Video30)
                    ,Resource.GetImage(Resource.Images.ScrollText30)
                    ,Resource.GetImage(Resource.Images.Time30)
                    ,Resource.GetImage(Resource.Images.Temp30)
                    ,Resource.GetImage(Resource.Images.ScrollText30)
                }
                ;
            }
        }

        #region Propeties
        [Browsable(false)]
        [EditorBrowsable(EditorBrowsableState.Never)]
        [DesignerSerializationVisibility(DesignerSerializationVisibility.Hidden)]
        public int TimePanelLeft
        {
            get
            {
                return EffectContainer.Left;
            }
            set
            {
                EffectContainer.Left = value;
            }
        }

        [Browsable(false)]
        [EditorBrowsable(EditorBrowsableState.Never)]
        [DesignerSerializationVisibility(DesignerSerializationVisibility.Hidden)]
        public int TimePanelWidth
        {
            get
            {
                return EffectContainer.Width;
            }
            set
            {
                EffectContainer.Width = value;
            }
        }

        [Browsable(false)]
        [EditorBrowsable(EditorBrowsableState.Never)]
        [DesignerSerializationVisibility(DesignerSerializationVisibility.Hidden)]
        public int LayerLeft
        {
            get
            {
                return plLeft.Width;
            }
            set
            {
                plLeft.Width = value;
            }
        }

        [Browsable(false)]
        [EditorBrowsable(EditorBrowsableState.Never)]
        [DesignerSerializationVisibility(DesignerSerializationVisibility.Hidden)]
        public int LayerRight
        {
            get
            {
                return ctlExitEffect.Visible ? splitter4.Right : splitter3.Right;
            }
        }

        [Browsable(false)]
        [EditorBrowsable(EditorBrowsableState.Never)]
        [DesignerSerializationVisibility(DesignerSerializationVisibility.Hidden)]
        public int PlRightWidth
        {
            get
            {
                return plRight.Width;
            }
            set
            {
                plRight.Width = value;
            }
        }

        [Browsable(false)]
        [EditorBrowsable(EditorBrowsableState.Never)]
        [DesignerSerializationVisibility(DesignerSerializationVisibility.Hidden)]
        public int StartTime
        {
            get { return (int)(LayerLeft / Constance.TrackBar.UnitWidth); }
        }

        [Browsable(false)]
        [EditorBrowsable(EditorBrowsableState.Never)]
        [DesignerSerializationVisibility(DesignerSerializationVisibility.Hidden)]
        public int EndTime
        {
            get
            {   return (int)(LayerRight / Constance.TrackBar.UnitWidth); }
        }

        [Browsable(false)]
        [EditorBrowsable(EditorBrowsableState.Never)]
        [DesignerSerializationVisibility(DesignerSerializationVisibility.Hidden)]
        public int Duration
        {
            get { return EndTime - StartTime; }
        }


        [Browsable(false)]
        [EditorBrowsable(EditorBrowsableState.Never)]
        [DesignerSerializationVisibility(DesignerSerializationVisibility.Hidden)]
        public ILayerEffect EntryEffect
        {
            get
            {  
                return _layer.EntryEffect;
            }

        }

        [Browsable(false)]
        [EditorBrowsable(EditorBrowsableState.Never)]
        [DesignerSerializationVisibility(DesignerSerializationVisibility.Hidden)]
        public ILayerEffect ExitEffect
        {
            get
            {
                return _layer.ExitEffect;
            }
        }

        [Browsable(false)]
        [EditorBrowsable(EditorBrowsableState.Never)]
        [DesignerSerializationVisibility(DesignerSerializationVisibility.Hidden)]
        public ILayerEffect EmphasisEffect
        {
            get
            {
                return _layer.EmphasisEffect;
            }
        }

        

        [Browsable(false)]
        [EditorBrowsable(EditorBrowsableState.Never)]
        [DesignerSerializationVisibility(DesignerSerializationVisibility.Hidden)]
        public DevExpress.XtraEditors.HScrollBar HScrollBarCtrl
        {
            get { return hScrollBarCtrl; }
            set { hScrollBarCtrl = value; }
        }

        [Browsable(false)]
        [EditorBrowsable(EditorBrowsableState.Never)]
        [DesignerSerializationVisibility(DesignerSerializationVisibility.Hidden)]
        public ShapeBase Shape
        {
            get { return _layer.Shape; }
            internal set { _layer.Shape = value; }
        }

        [Browsable(false)]
        [EditorBrowsable(EditorBrowsableState.Never)]
        [DesignerSerializationVisibility(DesignerSerializationVisibility.Hidden)]
        public TrackBarNew TrackBarCtrl
        {
            get { return _trackBarCtrl; }
            set { _trackBarCtrl = value; }
        }

        //public bool LayerVisible
        //{
        //    get { return lblVisible.EditValue != null; }
        //    set
        //    {
        //        lblVisible.EditValue = (value ? Resource.GetImage(Resource.Images.VisiableLayer) : null);
        //        _layer.IsVisible = value;
        //        UpdateShapeVisible();
        //    }
        //}

        [Browsable(false)]
        [EditorBrowsable(EditorBrowsableState.Never)]
        [DesignerSerializationVisibility(DesignerSerializationVisibility.Hidden)]
        public bool IsSelected
        {
            get { return _IsSelected; }
            set
            {
                _IsSelected = value;
                if (_IsSelected)
                    SetInputFocus();
                else
                    LostInputFocus();

                Canvas.ControlMenuItemEnable(_layer.Shape);

            }
        }

        public static LayerControl CurrentDrag
        {
            get { return _currentdrag; }
            set { _currentdrag = value; }
        }

        public static LayerControl CurrentShif
        {
            get { return _currentshif; }
            set { _currentshif = value; }
        }

        public static LayerControl Current
        {
            get { return _current; }
            set
            {
                _current = value;

                if (_current == null)
                    return;

                ShapeBase shape = _current._layer.Shape;
                if (shape == null)
                    return;

                MessageControl messageControl = MessageControl.Current;
                if (messageControl != null)
                {
                    messageControl.ShapeControl.Document.Select(shape);
                    messageControl.ShapeControl.Invalidate();
                }
            }
        }

        [Browsable(false)]
        [EditorBrowsable(EditorBrowsableState.Never)]
        [DesignerSerializationVisibility(DesignerSerializationVisibility.Hidden)]
        public IShapeLayer Layer
        {
            get
            {
                return _layer;
            }
        }

        [Browsable(false)]
        [EditorBrowsable(EditorBrowsableState.Never)]
        [DesignerSerializationVisibility(DesignerSerializationVisibility.Hidden)]
        public IShapeLayer LayerReal
        {
            get
            {
                return _layer.Real;
            }
        }
        #endregion 
    }
}
