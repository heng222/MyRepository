using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO;

namespace ProWrite.UI.Clients.Test
{
    public partial class FrmTemplateTest : Form
    {
        private Rectangle dragBoxFromMouseDown = Rectangle.Empty;

        public FrmTemplateTest()
        {
            InitializeComponent();
            string url = Application.StartupPath + @"\templates.htm";
            if (File.Exists(url) )
                this.webBrowser1.Navigate(url);

            this.webBrowser1.DocumentCompleted += new WebBrowserDocumentCompletedEventHandler(webBrowser1_DocumentCompleted);
            this.webBrowser2.DocumentCompleted += new WebBrowserDocumentCompletedEventHandler(webBrowser2_DocumentCompleted);
              
        }

        void webBrowser2_DocumentCompleted(object sender, WebBrowserDocumentCompletedEventArgs e)
        {
            HtmlElementCollection elems = webBrowser2.Document.GetElementsByTagName("td");
            if (elems != null && elems.Count > 0)
            {
                foreach (HtmlElement elem in elems)
                {
                    if (elem.Id != null)
                    {
                        elem.MouseDown += new HtmlElementEventHandler(OnRegionMouseDown);
                    }
                }
            }
        }

        HtmlElement currentRegion = null;

        void OnRegionMouseDown(object sender, HtmlElementEventArgs e)
        {
            if (currentRegion != null)
                currentRegion.Style = null;
            currentRegion = sender as HtmlElement;
            currentRegion.Style = "border-color = blue;";
        }


        void OnRowMouseMove(object sender, HtmlElementEventArgs e)
        {
            if ((e.MouseButtonsPressed & MouseButtons.Left) == MouseButtons.Left)
            {
                if (dragBoxFromMouseDown != Rectangle.Empty
                    && !dragBoxFromMouseDown.Contains(e.MousePosition.X, e.MousePosition.Y))
                {
                    HtmlElement elem = sender as HtmlElement;
                   
                }
            }
        }

        void OnRowMouseDown(object sender, HtmlElementEventArgs e)
        {
            if (e.MouseButtonsPressed == MouseButtons.Left)
            {
                Size dragSize = SystemInformation.DragSize;

                dragBoxFromMouseDown = new Rectangle(new Point(e.MousePosition.X - (dragSize.Width / 2),
                                                               e.MousePosition.Y - (dragSize.Height / 2)), dragSize);
            }
        }

        void OnRowMouseUp(object sender, HtmlElementEventArgs e)
        {
            dragBoxFromMouseDown = Rectangle.Empty;
        }


        void webBrowser1_DocumentCompleted(object sender, WebBrowserDocumentCompletedEventArgs e)
        {
            HtmlElementCollection elems = webBrowser1.Document.GetElementsByTagName("table");
            if (elems != null && elems.Count > 0)
            {
                foreach (HtmlElement elem in elems)
                {
                    if (elem.Id != null)
                    {
                        elem.Click += new HtmlElementEventHandler(OnTemplateClick);
                    }
                }
            }
        }

        void OnTemplateClick(object sender, HtmlElementEventArgs e)
        {
            HtmlElement elem = sender as HtmlElement;
            this.groupBox1.Text = elem.Id;
            this.webBrowser2.DocumentText = elem.OuterHtml;
        }


    }
}
