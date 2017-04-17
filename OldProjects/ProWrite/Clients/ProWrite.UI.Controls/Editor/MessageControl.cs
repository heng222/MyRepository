using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Text;
using System.Threading;
using System.Windows.Forms;
using log4net;
using ProWrite.Entity.Library;
using ProWrite.Entity.Shape;
using ProWrite.Core;
using ProWrite.Resources;
using ProWrite.UI.Controls.Common;
using ProWrite.UI.Controls.CopyPaste;
using ProWrite.Entity;
using ProWrite.UI.Controls.Common.Messages;
using System.IO;
using System.Drawing.Imaging;

namespace ProWrite.UI.Controls.Editor
{

    public partial class MessageControl : ControlPanel<MessageInfo, MessageControl>, ILayerService
    //ControlBase
    {
        public delegate void AddedLayerEventHandler(LayerControl layerControl, DevExpress.XtraNavBar.NavBarGroup group);
        public delegate void RemovedLayerEventHandler(LayerControl layerControl, DevExpress.XtraNavBar.NavBarGroup group);

        public event AddedLayerEventHandler AddLayerEvent;
        public event RemovedLayerEventHandler RemoveLayerEvent;

        #region Fields

        private int orgiSlideOffset = -190;//-188;
        private int orgiPlayLeft = 0;
        private float _widthScale = 1;
        private float _heightScale = 1;
        private PlayService _playService;
        private ToolBoxMenu mnuToolBox;
        public int _CreateNailImageTime = 1;
        private int _initPlayLeft = 68;
        private int _Zoom = 1;
        public bool ZoomInEnable = true;
        public bool ZoomOutEnable = true;
        //private MasterLayerControl masterLayerCtl;

        #endregion //End Fields

        #region Propertys

        //public MasterLayerControl MasterLayerControl
        //{
        //    get{ return masterLayerCtl; }
        //}

        //public bool IsImport { get; set; }



        private void EditImage()
        {
            if ( shapeControl.Document.SelectedShape.Type == ShapeType.Image)
            {
                var shapeImage = (shapeControl.Document.SelectedShapes[shapeControl.Document.SelectedShapes.Length-1] as ShapeImage);
                if (shapeImage != null)
                {
                    EditPicture editPicture = new EditPicture(shapeImage);
                    editPicture.ShowModalDialog();
                }
            }
        }

        //private void SetShapImage(Image img)
        //{
        //    (shapeControl.Document.SelectedShape as ShapeImage).Image = img;
        //}

        protected override void DoPopulate()
        {
            shapeControl.ForeColor = SignTypeHandler.ConvertColor(shapeControl.ForeColor, _sign.Type);
            if ( !_model.SignType.HasValue
                 || _model.SignType.Value != _sign.Type)
            {
                _model.BackColor = SignTypeHandler.ConvertColor(_sign.Template.Message.BackGroundColor, _sign.Type);
                _model.UpdateSignType(_sign.Type);
            }
            shapeControl.BackColor = _model.BackColor;
            //Set sign size
            PopulateShapeControlSize();
            OpenMessage(_model);
            _model.OnBackColorChange += delegate
            {
                shapeControl.BackColor = _model.BackColor;
                shapeControl.Invalidate();
                //if (_sign.Template.Message.IsShowGrid)
                //{
                //    shapeControl.BackgroundImage = CommonHelper.GetGridImage(shapeControl.Width, shapeControl.Height, new Size(_Zoom, _Zoom), shapeControl.BackColor);
                //    //shapeControl.Document.ShapeDraw.BackColor = shapeControl.BackColor;
                //}
                _changedService.MarkChanged();
            };
            _model.OnEffectChanged += delegate
            {
                _changedService.MarkChanged();
            };
        }

        private void Panel2_Resize(object sender, System.EventArgs e)
        {
            lblSlide.Height = splitContainer.Panel2.ClientRectangle.Height - lblSlide.Top - panelControl1.Height;
            layerEditor.Height = splitContainer.Panel2.ClientRectangle.Height - playStopBar.Height - panelControl1.Height;
        }

        private void PopulateShapeControlSize()
        {
            if (IsZoomed)
            {
                ZoomInAndOut(_Zoom);
                return;
            }

            if (_signSize != Size.Empty)
            {
                int wn = (int)Math.Floor(splitContainer.Panel1.ClientRectangle.Width * 1.0f / _signSize.Width);
                int hn = (int)Math.Floor(splitContainer.Panel1.ClientRectangle.Height * 1.0f / _signSize.Height);
                _widthScale = wn;
                _heightScale = hn;

                _Zoom = wn < hn ? wn : hn;
                _Zoom = _Zoom < 1 ? 1 : _Zoom;
                int width = _Zoom * _signSize.Width;
                int height = _Zoom * _signSize.Height;
                shapeControl.Size = new Size(width, height);
                shapeControl.Left = (splitContainer.Panel1.ClientRectangle.Width - shapeControl.Width) / 2;
                shapeControl.Top = (splitContainer.Panel1.ClientRectangle.Height - shapeControl.Height) / 2;
                shapeControl.Left = shapeControl.Left < 1 ? 1 : shapeControl.Left;
                shapeControl.Top = shapeControl.Top < 1 ? 1 : shapeControl.Top;
                shapeControl.Document.Zoom = _Zoom;

                //if (_sign.Template.Message.IsShowGrid)
                //{
                //    shapeControl.BackgroundImage = CommonHelper.GetGridImage(width, height, new Size(_Zoom, _Zoom), shapeControl.BackColor);
                //}
            }
            else
            {
                shapeControl.Bounds = splitContainer.Panel1.ClientRectangle;
            }
        }

        private int maxZoomOffset = 0;
        public bool IsZoomed
        {
            get { return maxZoomOffset != 0; }
        }
        public void ZoomIn()
        {
            if (maxZoomOffset >= Constance.MaxZoomOffset)
            {
                ControlService.EnableZoom(MenuCommands.ZoomIn, false);
                ZoomInEnable = false;
                return;
            }
            ControlService.EnableZoom(MenuCommands.ZoomIn, true);
            ControlService.EnableZoom(MenuCommands.ZoomOut, true);
            ZoomInEnable = true;
            ZoomOutEnable = true;
            maxZoomOffset++;
            _Zoom++;
            ZoomInAndOut(_Zoom);
        }

        public void ZoomOut()
        {
            if (_Zoom <= 1)
            {
                ControlService.EnableZoom(MenuCommands.ZoomOut, false);
                ZoomOutEnable = false;
                _Zoom = 1;
                return;
            }
            ControlService.EnableZoom(MenuCommands.ZoomIn, true);
            ControlService.EnableZoom(MenuCommands.ZoomOut, true);
            ZoomInEnable = true;
            ZoomOutEnable = true;

            maxZoomOffset--;
            _Zoom--;
            //_Zoom = _Zoom <= 1 ? 1 : _Zoom;
            ZoomInAndOut(_Zoom);
        }

        private void ZoomInAndOut(int zoomFactor)
        {
            int width = zoomFactor * _signSize.Width;
            int height = zoomFactor * _signSize.Height;
            shapeControl.Size = new Size(width, height);
            shapeControl.Left = splitContainer.Panel1.ClientRectangle.Width - shapeControl.Width > 0 ? (splitContainer.Panel1.ClientRectangle.Width - shapeControl.Width) / 2 : 0;
            shapeControl.Top = splitContainer.Panel1.ClientRectangle.Height - shapeControl.Height > 0 ? (splitContainer.Panel1.ClientRectangle.Height - shapeControl.Height) / 2 : 0;
            shapeControl.Document.Zoom = zoomFactor;

            if (_sign.Template.Message.IsShowGrid && zoomFactor > 1)
            {
                //shapeControl.BackgroundImage = CommonHelper.GetGridImage(width, height, new Size(zoomFactor, zoomFactor), shapeControl.BackColor);
                shapeControl.Invalidate();
            }

        }

        public override void LoadModelInfo()
        {
            List<ShapeLayer> layers = new List<ShapeLayer>();
            foreach (LayerControl frameLayer in _staticContainer.Controls)
            {
                //Delete copy to :saved event haved copy to 
                layers.Add(frameLayer.Layer.Copy() as ShapeLayer );
            }
            foreach (LayerControl frameLayer in _dynamicContainer.Controls)
            {
                //Delete copy to :saved event haved copy to 
                layers.Add(frameLayer.Layer.Copy() as ShapeLayer);
            }
            _model.Items = layers.ToArray();
            _model.Length = TotalTimeLen;
            _model.Size = shapeControl.Size;
            _model.Zoom = _Zoom;
            _model.BackColor = shapeControl.BackColor;
        }

        /// <summary>
        /// get sign container control
        /// </summary>
        public Canvas ShapeControl
        {
            get { return shapeControl; }
        }

        public int Zoom
        {
            get { return _Zoom; }
        }
        #endregion //End Propertys

        /// <summary>
        /// Constructure function
        /// </summary>
        public MessageControl()
        {
            InitializeComponent();
            trackBar1.LblSlide = lblSlide;
            trackBar1.SlideOffset = orgiSlideOffset;
            if (!DesignMode)
                Init();
            RegisterHelp();

            AddLayerEvent += new AddedLayerEventHandler(MessageControl_AddLayerEvent);
            RemoveLayerEvent += new RemovedLayerEventHandler(MessageControl_RemoveLayerEvent);
        }

        void MessageControl_Observers(object sender, EditImage msg)
        {
            if (IsActive)
            {
                if (msg.CurrentShapImage == null)
                    EditImage();
                else
                {
                    shapeControl.Invalidate();
                }
            }
        }


        private void RegisterHelp()
        {
            this.SetShowHelp(HelpNavigator.Topic, Resource.Helps.EditorMessage);
        }

        #region Methods
        public override void InitializeResource()
        {
            base.InitializeResource();
            lblNew.Image = Resource.GetImage(Resource.Images.AddNewLayer);
            btnSave.Image = Resource.GetImage(Resource.Images.Save16);
            lblRecycle.Image = Resource.GetImage(Resource.Images.RecycleClose16);
            trackBar1.BackgroundImage = Resource.GetImage(Resource.Images.PlayBarBackground);
        }

        void splitContainer_SplitterMoved(object sender, EventArgs e)
        {
            lblSlide.Height = splitContainer.Panel2.ClientRectangle.Height - lblSlide.Top - panelControl1.Height;
        }


        /// <summary>
        /// init method
        /// </summary>
        protected override void Init()
        {
            base.Init();
            splitContainer.SplitterMoved += new EventHandler(splitContainer_SplitterMoved);

            lblSlide.Visible = true;
            InitializeResource();
            mnuToolBox = new ToolBoxMenu(this);
            shapeControl.ContextMenuStrip = new CanvasContextMenu(this);
            _changedService.AddService(shapeControl.Document.ChangedService);

            InitLayerContainer();
            layerEditor.Groups[0].GroupClientHeight = LayerControl._.Height;
            layerEditor.Groups[1].GroupClientHeight = LayerControl._.Height;
            //layerEditor.Groups[2].GroupClientHeight = MasterLayerControl._.Height;
            InitPlayControl();
            SubscribeEvent();
            //AddMasterLayer();
            _initPlayLeft = trackBar1.Left;


            #region track bar new
            orgiPlayLeft = trackBar1.Left;

            if (_staticContainer.Controls.Count > 0 && _dynamicContainer.Controls.Count > 0)
            {
                hScrollBar.Maximum =
                    ((_staticContainer.Controls[0] as LayerControl).TimePanelWidth > (_dynamicContainer.Controls[0] as LayerControl).TimePanelWidth ? (_staticContainer.Controls[0] as LayerControl).TimePanelWidth : (_dynamicContainer.Controls[0] as LayerControl).TimePanelWidth)
                    - hScrollBar.Width;
            }
            else
            {
                if (_staticContainer.Controls.Count > 0)
                    hScrollBar.Maximum = (_staticContainer.Controls[0] as LayerControl).TimePanelWidth - hScrollBar.Width;
                if (_dynamicContainer.Controls.Count > 0)
                    hScrollBar.Maximum = (_dynamicContainer.Controls[0] as LayerControl).TimePanelWidth - hScrollBar.Width;
            }
            hScrollBar.Minimum = 0;
            hScrollBar.SmallChange = 5;
            hScrollBar.LargeChange = 5;
            #endregion



            lblSlide.Height = splitContainer.Panel2.ClientRectangle.Height - lblSlide.Top - panelControl1.Height;
        }

        void MessageControl_Observers(object sender, MenuMessage msg)
        {
            btnThumbNailImage.Enabled = shapeControl.Document.Count > 0;

            if (msg.Commands != null && msg.Commands.Length > 0 )
            {
                
                foreach (MenuCommand item in msg.Commands)
                {
                    var enabled = item.Enabled.HasValue ? item.Enabled.Value : false;
                    if (item.Command == MenuCommands.Save)
                    {
                        btnSave.Enabled = enabled;
                        //btnThumbNailImage.Enabled = item.Enabled.Value;
                    }
                    if (item.Command == MenuCommands.Delete)
                    {
                        lblRecycle.Enabled = enabled;
                        //btnThumbNailImage.Enabled = item.Enabled.Value;
                    }

                }
            }
            if (shapeControl.Document.Count <= 0)
                btnSave.Enabled = false;
        }

        public override void SubscribeEvent()
        {
            base.SubscribeEvent();
            shapeControl.LocationChanged += this.OnShapeControlResize;
            shapeControl.Resize += OnShapeControlResize;
            shapeControl.DoubleClick += OnShapeControlDoubleClick;
            shapeControl.DragDrop += OnShapeControlDragDrop;
            shapeControl.DragEnter += OnShapeControlDragEnter;
            shapeControl.KeyUp += OnShapeControlKeyUp;
            shapeControl.Document.ShapeBackgroundChanged += Shapes_ShapeBackgroundChanged;
            shapeControl.Document.ShapePropertyChanged += this.shape_PropertyChanged;
            shapeControl.Document.ShapeSelectedChanged += this.shape_SelectedChanged;
            shapeControl.Document.ShapeRemoveBackground += this.shape_deleteEvent;
            shapeControl.Document.ShapeAddLayers += shape_AddLayers;
            shapeControl.Document.ShapePaintByNetSelected = SetShapePaintLayerSelected;
            this.lblRecycle.DragDrop += lblRecycle_DragDrop;
            this.lblRecycle.DragLeave += lblRecycle_DragLeave;
            this.lblRecycle.DragEnter += lblRecycle_DragEnter;
            this.lblRecycle.Click += lblRecycle_Click; // add by Michael 2008/8/27
            this.lblNew.MouseUp += lblNew_MouseUp;
            this.btnSave.Click += btnSave_Click;
            //hScrollBar.Scroll += hScrollBar_Scroll;
            this.trackBar1.ValueChanged += playTrackBar_ValueChanged;


            hScrollBar.Scroll += hScrollBar_Scroll;
            hScrollBar.ValueChanged += hScrollBar_ValueChanged;
            LocalMessageBus.Subject<FileLibraryRenameMessage>().Observers += OnFileLibraryRename;
            LocalMessageBus.Subject<MenuMessage>().Observers += new System.Communication.Messaging.ObserverHandler<MenuMessage>(MessageControl_Observers);
            LocalMessageBus.Subject<EditImage>().Observers += new System.Communication.Messaging.ObserverHandler<EditImage>(MessageControl_Observers);
            this.panelControl1.Resize += new EventHandler(panelControl1_Resize);
            this.shapeControl.Document.NetSelectedShapes += new EventHandler<NetSelecetedShapesEventArgs>(Document_NetSelectedShapes);
            btnThumbNailImage.Enabled = shapeControl.Document.Count > 0;
        }

        void btnSave_Click(object sender, EventArgs e)
        {
            LocalMessageBus.Send(this, new PWMessage<MenuCommands>(MenuCommands.Save));
        }

        void Document_NetSelectedShapes(object sender, NetSelecetedShapesEventArgs e)
        {
            SetLayerControlByNetSelected(e.SelectedShapes);
        }

        void OnFileLibraryRename(object sender, FileLibraryRenameMessage msg)
        {
            if (msg == null || msg.Item == null)
                return;
            ShapeType type = msg.Item.Type == LibraryType.Image ? ShapeType.Image : ShapeType.Video;
            foreach (var item in shapeControl.Document)
            {
                if (item == null || item.Type != type)
                    continue;
                IFileHandle file = item as IFileHandle;
                if (file == null || file.FileHandle != msg.Item.Id)
                    continue;
                file.FileUrl = msg.Item.Path;
            }
        }

        void panelControl1_Resize(object sender, EventArgs e)
        {
            hScrollBar.Width = panelControl1.DisplayRectangle.Width - hScrollBar.Left;
        }



        public override void UnSubscribeEvent()
        {
            base.UnSubscribeEvent();

            shapeControl.LocationChanged -= OnShapeControlResize;
            shapeControl.Resize -= OnShapeControlResize;
            shapeControl.DoubleClick -= OnShapeControlDoubleClick;
            shapeControl.DragDrop -= OnShapeControlDragDrop;
            shapeControl.DragEnter -= OnShapeControlDragEnter;
            shapeControl.KeyUp -= OnShapeControlKeyUp;
            shapeControl.Document.ShapeBackgroundChanged -= Shapes_ShapeBackgroundChanged;
            shapeControl.Document.ShapePropertyChanged -= shape_PropertyChanged;
            shapeControl.Document.ShapeSelectedChanged -= shape_SelectedChanged;
            shapeControl.Document.ShapeRemoveBackground -= shape_deleteEvent;
            shapeControl.Document.ShapeAddLayers -= shape_AddLayers;

            this.lblRecycle.DragDrop -= lblRecycle_DragDrop;
            this.lblRecycle.DragLeave -= lblRecycle_DragLeave;
            this.lblRecycle.DragEnter -= lblRecycle_DragEnter;
            this.lblNew.MouseUp -= lblNew_MouseUp;

            hScrollBar.Scroll -= hScrollBar_Scroll;
            hScrollBar.ValueChanged -= hScrollBar_ValueChanged;

            LocalMessageBus.Subject<FileLibraryRenameMessage>().Observers -= OnFileLibraryRename;
            LocalMessageBus.Subject<MenuMessage>().Observers -= MessageControl_Observers;

            this.panelControl1.Resize -= new EventHandler(panelControl1_Resize);
        }

        private void OnAddShape(object sender, PWMessage<ShapeType> msg)
        {
            AddLayer(msg.Content, ShapeAddMode.Menu);
        }

        public void SetCreateNailImageTime()
        {
            _CreateNailImageTime = trackBar1.PlayValue;
            //_changedService.MarkChanged();
        }

        public void GenerateNailImageNoWaitCursor()
        {
            int nailImageTime = 1;
            //Image img = NailImageGenerator.GenerateNailImage(Layers, shapeControl, _CreateNailImageTime < 1 ? 1 : _CreateNailImageTime);
            if (trackBar1.PlayValue > _model.Length)
                nailImageTime = _model.Length - 1;
            else if (trackBar1.PlayValue < 1)
                nailImageTime = 1;
            else
                nailImageTime = trackBar1.PlayValue;
            Image img = NailImageGenerator.GenerateNailImage(this, nailImageTime);
            _model.PlayValue = nailImageTime;
            if (img != null)
            {
                _changedService.MarkChanged();

                //_model.ImagePath = Constance.LibraryNailImageDir + DateTime.Now.Ticks.ToString() + ".jpg";
                _model.ImagePath = Constance.LibraryNailImageDir + _model.Id + ".png";

                IOHelper.SaveImage(img, _model.ImagePath, ImageFormat.Png);

            }
        }

        //private void AddMasterLayer()
        //{
        //    ShapeMasterLayer masterLayer = new ShapeMasterLayer();
        //    masterLayerCtl = new MasterLayerControl(masterLayer, true);
        //    layerEditor.Groups[2].ControlContainer.Controls.Add(masterLayerCtl);
        //    SubscribeMasterLayerEvent(masterLayerCtl);
        //}

        #endregion

        #region Events
        private int oldZoom = -1;
        /// <summary>
        /// sign container resize event
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void splitContainer_Resize(object sender, EventArgs e)
        {
            PopulateShapeControlSize();
        }

        /// <summary>
        /// sign container resize event
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void OnShapeControlResize(object sender, EventArgs e)
        {
            if (AutoSize)
            {
                playPanel.Bounds = shapeControl.Bounds;
            }
        }

        /// <summary>
        /// split container panel resize event
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void splitContainerControl1_Panel1_Resize(object sender, EventArgs e)
        {
            PopulateShapeControlSize();
        }

        private void lblRecycle_DragEnter(object sender, DragEventArgs e)
        {
            if (!e.Data.GetDataPresent(typeof(LayerControl)))
            {
                Cursor = Cursors.No;
                return;
            }

            e.Effect = DragDropEffects.Move;
            lblRecycle.Image = Resource.GetImage(Resource.Images.RecycleOpen16);
        }

        private void lblRecycle_DragDrop(object sender, DragEventArgs e)
        {
            SetDefaultbtn();
            if (!e.Data.GetDataPresent(typeof(LayerControl)))
                return;

            //)Resource.GetString(Resource.Strings.ConfirmDeleteLayer))

            if (MsgBox.Confirm(GetDeleteTipMessage()) == DialogResult.No)
                return;
            RemoveLayer(e.Data.GetData(typeof(LayerControl)) as LayerControl);
        }

        void btnThumbNailImage_Click(object sender, System.EventArgs e)
        {
            try
            {
                IOHelper.RemoveFile(_model.ImagePath);
            }
            catch
            {
                ILog _log = LogManager.GetLogger(typeof(IOHelper));
                _log.Error("Remove Thumbnail Image Error.");
            }
            GenerateNailImageNoWaitCursor();
            LocalMessageBus.Send(this, new PWMessage<MenuCommands>(MenuCommands.Save));
            //SetCreateNailImageTime();
        }

        /// <summary>
        /// É¾³ý²ã
        /// add by Michael 2008/8/27
        /// </summary>
        private void lblRecycle_Click(object sender, EventArgs e)
        {

            //Resource.GetString(Resource.Strings.ConfirmDeleteItem))

            if (MsgBox.Confirm(GetDeleteTipMessage()) == DialogResult.Yes)
            {
                RemoveLayer();
                shapeControl.Invalidate();
            }
        }

        public string GetDeleteTipMessage()
        {
            string msg = "";
            List<LayerControl> items = SelectedLayers;
            if (items.Count > 0)
            {
                if (items.Count == 1)
                {
                    //foreach (LayerControl item in items)
                    //    RemoveLayer(item);
                    //UndoService.Commit();
                    LayerControl frameLayer = items[0];
                    Document shapes = shapeControl.Document;
                    ShapeBase shape = frameLayer.Shape;
                    Control container = shape.IsDynamicLayer ? _dynamicContainer : _staticContainer;

                    if (shape.LayerType != LayerType.Paint)
                    {
                        msg = "Are you sure you want to delete this " + shape.Type.ToString().ToLower() + " item?";
                        //InternalRemoveLayer(frameLayer, shapes, container, shape);
                        //SetToolBarDisabled();
                    }
                    else if (shape.Type == ShapeType.ShapeDraw && (shape as ShapeDraw).Count == (shape as ShapeDraw).SelectedShapes.Length
                        && (shape as ShapeDraw).SelectedShapes.Length > 1)
                    {
                        msg = "Are you sure you want to delete shape item?";

                    }
                    else
                    {
                        ShapeBase[] deletedShapes = shapes.ShapeDraw.SelectedShapes;
                        if (deletedShapes != null && deletedShapes.Length > 0)
                        {
                            msg = "Are you sure you want to delete this shape?";
                        }
                    }
                }
                else
                {
                    msg = "Are you sure you want to delete these " + items.Count + " layers?";
                }
            }

            return msg;
        }
        private void lblNew_MouseUp(object sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Right) return;
            mnuToolBox.Show(lblNew.PointToScreen(e.Location));
        }

        private void lblRecycle_DragLeave(object sender, EventArgs e)
        {
            SetDefaultbtn();
        }

        /// <summary>
        /// Set default button shape
        /// </summary>
        private void SetDefaultbtn()
        {
            lblRecycle.Image = Resource.GetImage(Resource.Images.RecycleClose16);
            SetDefaultCursor();
        }

        /// <summary>
        /// Set default cursor
        /// </summary>
        private void SetDefaultCursor()
        {
            Cursor = Cursors.Default;
        }

        /// <summary>
        /// track bar value changed event
        /// </summary>
        /// <param name="value"></param>
        private void playTrackBar_ValueChanged()
        {
            UpdateShapeVisible();
        }

        public void UpdatePos(int left)
        {
            int i = 0;

            for (i = 0; i < _staticContainer.Controls.Count; i++)
            {
                (_staticContainer.Controls[i] as LayerControl).TimePanelLeft = left;
            }

            for (i = 0; i < _dynamicContainer.Controls.Count; i++)
            {
                (_dynamicContainer.Controls[i] as LayerControl).TimePanelLeft = left;
            }

        }

        private void hScrollBar_Scroll(object sender, ScrollEventArgs e)
        {
            #region track bar new
            bool bFlag = true;
            int xDispPos = LayerControl._.OrgiTimePanelLeft;
            int xPlayDispPos = orgiPlayLeft;

            if (_staticContainer.Controls.Count > 0)
            {
                bFlag = SetScrollBarValue(LayerControl._.OrgiTimePanelLeft, (_staticContainer.Controls[0] as LayerControl).TimePanelLeft, e, ref xDispPos);
            }
            else
                bFlag = false;
            if (bFlag)
            {
                UpdatePos(xDispPos);
                UpdatePos(xDispPos);
            }

            bFlag = SetScrollBarValue(orgiPlayLeft, trackBar1.Left, e, ref xPlayDispPos);

            if (bFlag)
            {
                trackBar1.Left = xPlayDispPos;
                lblSlide.Left = trackBar1.Left + trackBar1.SlideValue;
            }
            #endregion
        }

        private bool SetScrollBarValue(int orgiLeft, int Left, ScrollEventArgs e, ref int xPos)
        {
            bool bFlag = true;
            switch (e.Type)
            {
                case ScrollEventType.First:
                    xPos = orgiLeft;
                    break;
                case ScrollEventType.Last:
                    xPos = orgiLeft - hScrollBar.Maximum;
                    break;
                case ScrollEventType.SmallDecrement:
                    xPos = Left + hScrollBar.SmallChange;
                    break;
                case ScrollEventType.SmallIncrement:
                    xPos = Left - hScrollBar.SmallChange;
                    break;
                case ScrollEventType.LargeDecrement:
                    xPos = Left + hScrollBar.LargeChange;
                    break;
                case ScrollEventType.LargeIncrement:
                    xPos = Left - hScrollBar.LargeChange;
                    break;
                case ScrollEventType.ThumbPosition:
                    xPos = orgiLeft - hScrollBar.Value;
                    break;
                default:
                    bFlag = false;
                    break;
            }

            if (bFlag)
            {
                if (xPos > orgiLeft)
                {
                    xPos = orgiLeft;
                }
                else if (xPos < orgiLeft - hScrollBar.Maximum)
                {
                    xPos = orgiLeft - hScrollBar.Maximum;
                }

            }

            return bFlag;
        }

        private void hScrollBar_ValueChanged(object sender, EventArgs e)
        {
            int xDispPos = LayerControl._.OrgiTimePanelLeft - hScrollBar.Value;

            if (xDispPos > LayerControl._.OrgiTimePanelLeft)
            {
                xDispPos = LayerControl._.OrgiTimePanelLeft;
            }
            else if (xDispPos < LayerControl._.OrgiTimePanelLeft - hScrollBar.Maximum)
            {
                xDispPos = LayerControl._.OrgiTimePanelLeft - hScrollBar.Maximum;
            }

            int xPlayDispPos = orgiPlayLeft - hScrollBar.Value;

            if (xPlayDispPos > orgiPlayLeft)
            {
                xPlayDispPos = orgiPlayLeft;
            }
            else if (xPlayDispPos < orgiPlayLeft - hScrollBar.Maximum)
            {
                xPlayDispPos = orgiPlayLeft - hScrollBar.Maximum;
            }


            UpdatePos(xDispPos);

            trackBar1.Left = xPlayDispPos;
            trackBar1.SlideOffset = orgiPlayLeft - trackBar1.Left + orgiSlideOffset;

            if (trackBar1.SlideValue < orgiPlayLeft - trackBar1.Left + 10)
            {
                lblSlide.Visible = false;
            }
            else
            {
                lblSlide.Visible = true;
                lblSlide.Left = trackBar1.Left + trackBar1.SlideValue;
            }
        }

        #endregion //End Events
    }
}
