using System;
using System.ComponentModel;
using System.Collections.Generic;
using System.Diagnostics;
using System.Text;
using System.Windows.Forms;

using System.Drawing;
using ProWrite.Resources;
using ProWrite.Core;

namespace ProWrite.UI.Controls.Editor
{
    public partial class ToolBoxMenu : ContextMenuStrip
    {
        private MessageControl _messageControl;
        private EventHandler onClick; 
        public ToolBoxMenu(MessageControl messageControl)
        {
            _messageControl = messageControl;
            onClick = delegate(object sender, EventArgs e)
            {
                ToolBoxMenuItem item = sender as ToolBoxMenuItem;
                if (item != null)
                    _messageControl.AddLayer(item.ShapeType, ShapeAddMode.Menu);
            };

            if (!DesignMode)
            {
                AddMenuItem("Text", ShapeType.Text, Resource.Images.TextLayer16);
                AddMenuItem("Picture", ShapeType.Image, Resource.Images.Image16);
                AddMenuItem("Movies && Animations", ShapeType.Video, Resource.Images.Video16);
                AddSeparetor();
                //AddMenuItem("Line", ShapeType.Line, Resource.Images.Line16);
                //AddMenuItem("Rectangle", ShapeType.Rectangle, Resource.Images.Rectangle16);
                //AddMenuItem("Ellipse", ShapeType.Ellipse, Resource.Images.Ellipse16);
                //AddMenuItem("Up Arrow", ShapeType.UpArrow, Resource.Images.ArrowUp16);
                //AddMenuItem("Down Arrow", ShapeType.DownArrow, Resource.Images.ArrowDown16);
                //AddMenuItem("Left Arrow", ShapeType.LeftArrow, Resource.Images.ArrowLeft16);
                //AddMenuItem("Right Arrow", ShapeType.RightArrow, Resource.Images.ArrowRight16);
                //AddSeparetor();
                //AddMenuItem("Dynamic Text", ShapeType.DynamicText, Resource.Images.ScrollText16);
                AddMenuItem("Time && Date", ShapeType.Time, Resource.Images.Time16);
                AddMenuItem("Temperature", ShapeType.Temperature, Resource.Images.Temp16);
            }
        }

        private void AddMenuItem(string caption, ShapeType type, string imageFile)
        {
            ToolBoxMenuItem item = new ToolBoxMenuItem();
            item.Text = caption;
            item.Image = Resource.GetImage(imageFile);
            item.ShapeType = type;
            item.Click += onClick;
            Items.Add(item);
        }

        private void AddSeparetor()
        {
            this.Items.Add(new ToolStripSeparator());
        }

        protected override void Dispose(bool disposing)
        {
            base.Dispose(disposing);
            onClick = null;
        }
    }

    public class ToolBoxMenuItem : ToolStripMenuItem
    {
        internal ShapeType ShapeType; 
    }
}
