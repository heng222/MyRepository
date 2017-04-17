//---------------------------------------------------------------------
//
// File: ToolBoxControl.cs
//
// Description:
// User Control of tool box 
//
// Author: Kevin 2008-6-30
//
// Modify History:
// Copyright (C) 2008 by Trans-Lux All rights reserved.
// 
//---------------------------------------------------------------------
using System.Windows.Forms;
using DevExpress.XtraNavBar;

using ProWrite.Resources;
using ProWrite.Core;

namespace ProWrite.UI.Controls.Editor
{
	/// <summary>
	/// tool box control
	/// </summary>
	public partial class ToolBoxControl : UserControl
    {

        public ToolBoxControl()
		{
			InitializeComponent();
            Dock = DockStyle.Fill;
           
			if (!DesignMode)
			{
				AddNarBarItem("Text",  ShapeType.Text, Resource.Images.TextLayer16);
				AddNarBarItem("Picture", ShapeType.Image, Resource.Images.Image16);
                AddNarBarItem("Movies & Animations", ShapeType.Video, Resource.Images.Video16);
				//AddNarBarItem("Line",  ShapeType.Line, Resource.Images.Line16);
				//AddNarBarItem("Rectangle",  ShapeType.Rectangle, Resource.Images.Rectangle16);
				//AddNarBarItem("Ellipse", ShapeType.Ellipse, Resource.Images.Ellipse16);
				//AddNarBarItem("Up Arrow", ShapeType.UpArrow, Resource.Images.ArrowUp16);
				//AddNarBarItem("Down Arrow", ShapeType.DownArrow, Resource.Images.ArrowDown16);
				//AddNarBarItem("Left Arrow", ShapeType.LeftArrow, Resource.Images.ArrowLeft16);
				//AddNarBarItem("Right Arrow", ShapeType.RightArrow, Resource.Images.ArrowRight16);
                //AddNarBarItem("DynamicText", ShapeType.DynamicText, Resource.Images.ScrollText16);
                //AddNarBarItem("DynamicVideo", ShapeType.DynamicVideo, Resource.Images.Default);
				//AddNarBarItem("Scroll Text", ShapeType.Marquee, Resource.Images.Default);
                AddNarBarItem("Time & Date", ShapeType.Time, Resource.Images.Time16);
                AddNarBarItem("Temperature", ShapeType.Temperature, Resource.Images.Temp16);
                nbcToolBox.DoubleClick += new System.EventHandler(nbcToolBox_DoubleClick);

			}
            RegisterHelp();
		}

        private void RegisterHelp()
        {
            this.SetShowHelp(HelpNavigator.Topic, Resource.Helps.EditorToolBox);
        }

		/// <summary>
		/// add navigation nar item
		/// </summary>
		/// <param name="caption"></param>
		/// <param name="name"></param>
		/// <param name="type"></param>
		/// <param name="imageName"></param>
		private void AddNarBarItem(string caption, ShapeType type, string imageName)
		{
			ToolBoxNarBarItem item = new ToolBoxNarBarItem(type);
			item.Caption = caption;
			item.Name = caption.Replace(" ","");
			item.SmallImage = Resource.GetImage(imageName);
            item.Hint = caption;
			nbcToolBox.Items.Add(item);
            grpToolBox.ItemLinks.Add(item); 
		}

        void nbcToolBox_DoubleClick(object sender, System.EventArgs e)
        {
            if(MessageControl.Current != null
                && nbcToolBox.PressedLink!=null)
            {
                ToolBoxNarBarItem item = nbcToolBox.PressedLink.Item as ToolBoxNarBarItem;
                if (item != null)
                    MessageControl.Current.AddLayer(item.ShapeType, ShapeAddMode.Menu);
            }
            //MessageBox.Show(nbcToolBox.PressedLink.Item.Name);
        }
	}

	/// <summary>
	/// nar bar item class for tool box
	/// </summary>
	public class ToolBoxNarBarItem : NavBarItem
	{
		private ShapeType _shapeType = ShapeType.Text;

		public ToolBoxNarBarItem()
		{
            
		}

		public ToolBoxNarBarItem(ShapeType shapeType)
		{
			_shapeType = shapeType;
		}

		/// <summary>
		/// get or set shape type
		/// </summary>
		internal ShapeType ShapeType
		{
			get { return _shapeType; }
			set { _shapeType = value; }
		}
	}
}