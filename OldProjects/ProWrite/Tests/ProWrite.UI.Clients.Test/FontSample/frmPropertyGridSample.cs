using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace ProWrite.UI.Clients.Test.FontSample
{
    public partial class frmPropertyGridSample : Form
    {
        private class FontTest
        {
            private string _text;
            public string Text
            {
                set { _text = value; }
                get { return _text; }
            }

            private string _fontName;
            public string FontName
            {
                set{_fontName=value;}
                get{return _fontName;}
            }

            private FontStyle _fontStyle;
            public FontStyle FontStyle
            {
                set{_fontStyle=value;}
                get{return _fontStyle;}
            }

            private float _fontSize;
            public float FontSize
            {
                set{_fontSize=value;}
                get{return _fontSize;}
            }
            
        
        }

        public frmPropertyGridSample()
        {
            InitializeComponent();
        }
        
        private void frmPropertyGridSample_Load(object sender, EventArgs e)
        {
            FontTest test = new FontTest();
            test.Text = "aaa";
            //FontWrapper font = new FontWrapper();
            test.FontName = "Arial";
            test.FontStyle = FontStyle.Italic;
            test.FontSize = 20;

            pgControl.SelectedObject = test;
        }

        private void pgControl_CellValueChanged(object sender, DevExpress.XtraVerticalGrid.Events.CellValueChangedEventArgs e)
        {
            //FieldName
            pgControl.Rows["categoryMisc"].ChildRows["rowFontSize"].GetRowProperties(0).FieldName.ToString();
            //value
            pgControl.Rows["categoryMisc"].ChildRows["rowFontSize"].Grid.EditingValue.ToString();
            //MessageBox.Show(pgControl.Rows["categoryMisc"].ChildRows["rowFontSize"].GetRowProperties(0).Caption.ToString());
            //MessageBox.Show(pgControl.Rows["categoryMisc"].ChildRows["rowFontSize"].GetRowProperties(0).FieldName.ToString());
            //MessageBox.Show(pgControl.Rows["categoryMisc"].ChildRows["rowFontName"].Name.ToString());
            //MessageBox.Show(pgControl.Rows[0].ChildRows[0].Name.ToString());
            //if(e.RecordIndex==1&&e.CellIndex==1)
            //    MessageBox.Show(e.Value.ToString());
        }

    }
}