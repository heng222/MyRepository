using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Windows.Forms;
using DevExpress.XtraBars;
using DevExpress.XtraEditors;
using DevExpress.XtraEditors.Controls;
using DevExpress.XtraEditors.Popup;
using DevExpress.XtraTab;
using ProWrite.Core;
using ProWrite.UI.Controls.Common;

namespace ProWrite.UI.Controls
{
    public class ColorBarItem : BarButtonItemEx
	{
		ColorPopupControlContainer colorPopupControlContainer = new ColorPopupControlContainer();
        public event EventHandler ColorChanged;

        public Color SelectedColor
        {
            get { return colorPopupControlContainer.colorPopup.ResultColor; } 
            set { colorPopupControlContainer.colorPopup.ResultColor = value; }
        }

		public ColorPopupControlContainer ColorPopupControlContainer
		{
			get { return colorPopupControlContainer; }
		}
		public ColorBarItem()
		{
			colorPopupControlContainer.Visible = false;
			ButtonStyle = BarButtonStyle.DropDown;
			DropDownControl = colorPopupControlContainer;
			colorPopupControlContainer.Item = this;
			colorPopupControlContainer.Popup += new EventHandler(OnColorPopup);
            
		}

		void OnColorPopup(object sender, EventArgs e)
		{
			colorPopupControlContainer.Manager = Manager;

			colorPopupControlContainer.colorPopup.ColorChanged += ColorChanged;
		}
	}

	public class ColorPopupControlContainer : PopupControlContainer
	{
		internal ColorPopup colorPopup;
		[
		Browsable(false),
		EditorBrowsable(EditorBrowsableState.Never),
		]
		public Color ResultColor
		{
			get { return colorPopup.ResultColor; }
			set { colorPopup.ResultColor = value; }
		}
		[
		Browsable(false),
		EditorBrowsable(EditorBrowsableState.Never),
		]
		public BarItem Item
		{
			get { return colorPopup.Item; }
			set { colorPopup.Item = value; }
		}
		public Rectangle ColorRectangle
		{
			get { return Rectangle.Empty; }
			set { }
		}
		public ColorPopupControlContainer()
		{
			colorPopup = new ColorPopup(this);
            //CloseOnOuterMouseClick = false;
		}
		[
		Browsable(false),
		EditorBrowsable(EditorBrowsableState.Never),
		]
		public bool DrawColorRectangle
		{
			get { return colorPopup.DrawColorRectangle; }
			set { colorPopup.DrawColorRectangle = value; }
		}
		protected override void OnPopup()
		{
			LookAndFeel.ParentLookAndFeel = Item.Manager.GetController().LookAndFeel;
			colorPopup.CreateTabControl(this);
            base.OnPopup();
		}
		protected override void Dispose(bool disposing)
		{
			if (disposing)
			{
				if (colorPopup != null)
				{
					colorPopup.Dispose();
					colorPopup = null;
				}
			}
			base.Dispose(disposing);
		}
	}

    class ColorPopup : IDisposable
	{
		Color resultColor;
		BarItem item;
		Image initalImage = null;
		PopupControlContainer container;
		Rectangle colorRectangle = new Rectangle(1, 13, 14, 3);
		bool drawColorRectangle = true;
		DevExpress.XtraEditors.Repository.RepositoryItemColorEdit rItem;

	    internal XtraTabControl tabControl;

        PWColorCellsControlViewInfo viewInfo;

        [Browsable(false)]
        public event EventHandler ColorChanged;

        protected void OnColorChanged()
        {
            if (ColorChanged != null)
				ColorChanged(item, EventArgs.Empty);
        }

		internal bool DrawColorRectangle
		{
			get { return drawColorRectangle; }
			set { drawColorRectangle = value; }
		}
		[
		Browsable(false),
		EditorBrowsable(EditorBrowsableState.Never),
		]
		public BarItem Item
		{
			get { return item; }
			set { item = value; }
		}
		Image InitalImage
		{
			get
			{
				if (initalImage == null)
					initalImage = GetInitalImage();
				return initalImage;
			}
		}
		public ColorPopup(PopupControlContainer container)
		{
			this.container = container;
			this.resultColor = Color.Empty;
			CreateTabControl(container);
            //signType = ControlService.SignCombo.Current.Type;

		    MessageBus.Subject<SelectedSignMessage>().Observers += new System.Communication.Messaging.ObserverHandler<SelectedSignMessage>(ColorPopup_Observers);
		}

        private object[] MonoColorList = new
            object[]
                                             {
                                                 Color.Transparent,
                                                 Color.Black
                                             };
        private SignType? signType = null;

        internal void CreateTabControl(PopupControlContainer container)
        {
            if (tabControl != null)
            {

                tabControl.Dispose();
            }
            tabControl = new XtraTabControl();
            tabControl.LookAndFeel.ParentLookAndFeel = container.LookAndFeel;
            tabControl.TabStop = false;
            ColorListBox colorListBox;
            if (signType.HasValue && signType.Value != SignType.RGB)
                colorListBox = CreateColorListBox(MonoColorList);
            else
                colorListBox= CreateColorListBox(ColorListBoxViewInfo.WebColors);

            PWColorCellsControl colorCellsControl = CreateColorCellsControl();
            AddTabPage(tabControl, colorCellsControl, StringId.ColorTabCustom);
            AddTabPage(tabControl, colorListBox, "Standard");
            //AddTabPage(tabControl, new DateEdit(), "Date");
           
            tabControl.Dock = DockStyle.Fill;
            this.container.Controls.Add(tabControl);
            Size size = colorCellsControl.GetBestSize();
            size.Height = GetNearestBestClientHeight(size.Height, colorListBox);
            this.container.Size = tabControl.CalcSizeByPageClient(size);
        }

        void ColorPopup_Observers(object sender, SelectedSignMessage msg)
        {
            signType = msg.CurrentSign.Type;
            viewInfo.SignType = signType;
            tabControl.Invalidate();

        }
		#region IDisposable implementation
		void Dispose(bool disposing)
		{
			if (disposing)
			{
                ColorChanged = null;
				if (rItem != null)
				{
					rItem.Dispose();
					rItem = null;
				}
			}
		}
		public void Dispose()
		{
			Dispose(true);
			GC.SuppressFinalize(this);
		}
		~ColorPopup()
		{
			Dispose(false);
		}
		#endregion
        void AddTabPage(XtraTabControl tabControl, BaseControl control, StringId id)
        {
            XtraTabPage tabPage = new XtraTabPage();
            tabPage.Text = Localizer.Active.GetLocalizedString(id);
            control.Dock = DockStyle.Fill;
            control.BorderStyle = BorderStyles.NoBorder;
            control.LookAndFeel.ParentLookAndFeel = container.LookAndFeel;
            tabPage.Controls.Add(control);
            tabControl.TabPages.Add(tabPage);
        }
        void AddTabPage(XtraTabControl tabControl, BaseControl control, string tabPageText)
        {
            XtraTabPage tabPage = new XtraTabPage();
            tabPage.Text = tabPageText;
            control.Dock = DockStyle.Fill;
            control.BorderStyle = BorderStyles.NoBorder;
            control.LookAndFeel.ParentLookAndFeel = container.LookAndFeel;
            tabPage.Controls.Add(control);
            tabControl.TabPages.Add(tabPage);
        }
        ColorListBox CreateColorListBox(object[] items)
		{
			ColorListBox colorBox = new ColorListBox();
			colorBox.Items.AddRange(items);
			colorBox.EnterColor += new EnterColorEventHandler(OnEnterColor);
			return colorBox;
		}
        PWColorCellsControl CreateColorCellsControl()
		{
            PWColorCellsControl control = new PWColorCellsControl(null, 8, 8);
            viewInfo = new PWColorCellsControlViewInfo(control, 8, 8);
			rItem = new DevExpress.XtraEditors.Repository.RepositoryItemColorEdit();
			rItem.ShowColorDialog = true;
            control.PopupContainer = container;
			control.Properties = rItem;

            control.Properties.ShowCustomColors = false;
            control.EnterColor += new EnterColorEventHandler(OnEnterColor);
            //control.MouseUp += new MouseEventHandler(control_MouseUp);
            
			return control;
		}

        void control_MouseUp(object sender, MouseEventArgs e)
        {
            this.container.CloseOnOuterMouseClick = false;

            PWColorCellsControl control = sender as PWColorCellsControl;
            int cellIndex = viewInfo.GetCellIndex(new Point(e.X, e.Y));
            if ((e.Button & MouseButtons.Left) != 0 && control.Capture)
            {
                if (cellIndex != -1)
                {
                    control.SelectedCellIndex = cellIndex;
                    control.Capture = false;
                    OnEnterColor(control.SelectedCellIndex);
                }
            }
            if ((e.Button & MouseButtons.Right) != 0 && cellIndex >= ColorCellsControlViewInfo.CellColors.Length && rItem.ShowColorDialog)
            {
                ColorDialog cd = new ColorDialog();
                cd.FullOpen = true;
                cd.Color = viewInfo.GetCellColor(cellIndex);

                try
                {
                    if (cd.ShowDialog() == DialogResult.OK)
                    {
                        viewInfo.CustomColors[cellIndex - ColorCellsControlViewInfo.CellColors.Length] = cd.Color;
                        OnEnterColor(cellIndex);
                    }
                }
                catch (Exception ex)
                { }
            }
            this.container.CloseOnOuterMouseClick = true;

        }
        private void OnEnterColor(int index)
        {
            Color clr = viewInfo.GetCellColor(index);
            if (clr == Color.Empty) return;
            OnEnterColor(clr);
        }
		private void OnEnterColor(object sender, EnterColorEventArgs e)
		{
			resultColor = e.Color;
			OnEnterColor(e.Color);
		}
		private void OnEnterColor(Color clr)
		{
			container.HidePopup();
			ResultColor = clr;
		}
		private void UpdateColor()
		{
			if (!drawColorRectangle) return;
			try
			{
				Image image = InitalImage;
				if (image == null) return;
				image = (Image)image.Clone();
				Graphics g = Graphics.FromImage(image);
				g.FillRectangle(new SolidBrush(resultColor), colorRectangle);
				item.Glyph = image;
				item.ImageIndex = -1;
				foreach (BarItemLink link in item.Links)
				{
					link.Invalidate();
				}
			}
			catch { }
		}
		Image GetInitalImage()
		{
			if (item.Glyph == null)
			{
				DevExpress.Utils.ImageCollection iml = item.Images as DevExpress.Utils.ImageCollection;
				if (iml == null)
					return null;
				return (Image)iml.Images[item.ImageIndex];
			}
			return Item.Glyph;
		}
		private int GetNearestBestClientHeight(int height, ColorListBox OwnerControl)
		{
			ColorListBoxViewInfo viewInfo = null;
			try
			{
				viewInfo = (ColorListBoxViewInfo)typeof(ColorListBox).InvokeMember("ViewInfo",
					BindingFlags.GetProperty | BindingFlags.NonPublic | BindingFlags.Instance,
					null, OwnerControl, null);
			}
			catch
			{
				throw new Exception("ColorListBox doesn't contain 'ViewInfo' property");
			}
			int rowHeight = viewInfo.ItemHeight;
			int rows = height / rowHeight;
			if (rows * rowHeight == height)
				return height;
			return (rows + 1) * rowHeight;
		}
		public Color ResultColor
		{
			get { return resultColor; }
			set
			{
				resultColor = value;
				UpdateColor();
                OnColorChanged();
			}
		}
	}



}
