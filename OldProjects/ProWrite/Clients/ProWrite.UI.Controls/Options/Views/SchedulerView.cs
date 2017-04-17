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
    public partial class SchedulerView : ViewBase<ProWrite.Entity.Settings.SchedulerTemplate>
    {
        public SchedulerView()
        {
            InitializeComponent();
        }

        protected override void OnPaint(PaintEventArgs e)
        {
            base.OnPaint(e);
            e.Graphics.DrawString("Scheduler", Font, Brushes.Red, new PointF(200, 200));
        }

        protected override void DoBind()
        {
            spinPlaylist.Value = Convert.ToInt32(_data.PlayListDisplayTime);
            spinTimeSliceGroup.Value = Convert.ToInt32(_data.TimeSliceGroupDisplayTime);
        }

        protected override void DoUpdateData()
        {
            _data.PlayListDisplayTime = Convert.ToInt32(spinPlaylist.Value);
            _data.TimeSliceGroupDisplayTime = Convert.ToInt32(spinTimeSliceGroup.Value);
        }
    }
}
