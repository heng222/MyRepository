using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace ProWrite.UI.Controls.Options.Views
{
    public partial class MessageView :ViewBase<ProWrite.Entity.Settings.MessageTemplate>
    {
        public MessageView()
        {
            InitializeComponent();
        }

        protected override void OnPaint(PaintEventArgs e)
        {
            base.OnPaint(e);
            e.Graphics.DrawString("Message", Font, Brushes.Red, new PointF(200, 200));
        }

        protected override void DoBind()
        {
            colorBackGround.Color = _data.BackGroundColor;
            spinDisPlayTime.Value= _data.DisplayTime;
            ddlIsShowGrid.SelectedItem = _data.IsShowGrid;
        }

        protected override void DoUpdateData()
        {
            _data.IsShowGrid = Boolean.Parse(ddlIsShowGrid.Text);
            _data.BackGroundColor = colorBackGround.Color;
            _data.DisplayTime =Convert.ToInt32(spinDisPlayTime.Value);
        }

        protected override bool ValidateData()
        {
            //if (string.IsNullOrEmpty(txtName.Text))
            //{
            //    MsgBox.Warning("Name does not null.");
            //    return false;
            //}

            return true;
        }
    }
}
