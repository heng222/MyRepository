using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using ProWrite.Entity.Live;

namespace ProWrite.UI.Controls.Live.Sessions
{
	public partial class SmallButtonControl: UserControl
	{
        private MainHotKey _mainKey;
        private SubHotKey _subKey;
        private LiveSign[] _sign;

		public SmallButtonControl()
		{
			InitializeComponent();
		}

        public Color ButtonColor
        {
            set
            {
                this.BackColor = value;
            }
            get
            {
                return this.BackColor;
            }
        }

        public string ButtonName
        {
            set
            {
                this.lblName.Text = value;
            }
            get
            {
                return this.lblName.Text;
            }
        }

        public MainHotKey MainHotKey
        {
            set
            {
                _mainKey = value;
                SetHotKeyText();
            }
            get
            {
                return _mainKey;
            }
        }

        public SubHotKey SubHotKey
        {
            set
            {
                _subKey = value;
                SetHotKeyText();
            }
            get
            {
                return _subKey;
            }
        }

        public LiveSign[] Sign
        {
            set
            {
                _sign = value;
            }
            get
            {
                return _sign;
            }
        }

        public Image BackGroundImage
        {
            get
            {
                return this.BackgroundImage;
            }
            set
            {
                this.BackgroundImage = value;
            }
        }

        private void SetHotKeyText()
        {
            this.lblKeyShortcuts.Text = "(" + _mainKey.ToString() + ")" + " + " + _subKey.ToString();
        }

        private void lblKeyShortcuts_MouseDown(object sender, MouseEventArgs e)
        {
            this.OnMouseDown(e);
        }

        private void lblName_MouseDown(object sender, MouseEventArgs e)
        {
            this.OnMouseDown(e);
        }

	}
}
