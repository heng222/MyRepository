using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using ProWrite.Entity.DES;
using ProWrite.Entity.DES.Effect;

namespace ProWrite.UI.Controls.Editor.Effect
{
    public partial class eucLine : eucBase<EffectLine>
    {
        int height = ControlService.SignCombo.Current.Height;
        int width = ControlService.SignCombo.Current.Width;
        public eucLine()
        {
            InitializeComponent();
        }

        protected override void DoBind()
        {
            foreach (EffectLine.DirectionWays item in Enum.GetValues(typeof(EffectLine.DirectionWays)))
            {
                this.ddlDirection.Properties.Items.Add(item);
            }
            //double d =Convert.ToDouble(_effect.PullPoint * height) / 238;
            //string ss = (d).ToString();
            int result = _effect.PullPoint;//(int)Math.Round(float.Parse(ss));
            if (result == 0)
                result = 1;
            this.ddlPullPoint.Value = result ;
            this.ddlLagSpacing.Value = _effect.LagSpacing;
            this.ddlLineWidth.Value = _effect.LineWidth;
            this.ddlDirection.SelectedIndex = (int)_effect.DirectionWay;
        }

        protected override void DoSave()
        {
            
           // _effect.PullPoint = ((int)this.ddlPullPoint.Value * 238) / height;
            _effect.PullPoint = (int)ddlPullPoint.Value;

            _effect.LagSpacing = (int)this.ddlLagSpacing.Value;
            _effect.LineWidth = (int)this.ddlLineWidth.Value;
            if (this.ddlDirection.SelectedItem != null && Enum.IsDefined(typeof(EffectLine.DirectionWays), this.ddlDirection.SelectedItem))
            {
                _effect.DirectionWay = (EffectLine.DirectionWays)Enum.ToObject(typeof(EffectLine.DirectionWays), this.ddlDirection.SelectedIndex);
            }
        }

        void ddlDirection_SelectedIndexChanged(object sender, System.EventArgs e)
        {
            if (ddlDirection.SelectedIndex == 0 || ddlDirection.SelectedIndex == 1)
                ddlPullPoint.Properties.MaxValue = height;
            else
                ddlPullPoint.Properties.MaxValue = width;
        }

        private Point ConvertLocation(Point location, bool flag)
        {
            Point rc = new Point();
            int width = ControlService.SignCombo.Current.Width;
            int height = ControlService.SignCombo.Current.Height;
            if (flag)
            {
                rc.X = (location.X * 384) / width;
                rc.Y = (location.Y * 288) / height;
            }
            else
            {
                rc.X = (location.X * width) / 384;
                rc.Y = (location.Y * height) / 288;
            }
            return rc;
        }
    }
}
