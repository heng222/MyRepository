using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ComponentModel;
using ProWrite.Core.Validation;

namespace ProWrite.Entity.Settings
{
    /// <summary>
    /// class of playlistTemplate
    /// </summary>
    [Serializable]
    [TypeConverter(typeof(ExpandableObjectConverter))]
    //[SettingView(SR.Scheduler)]
    public class SchedulerTemplate : TemplateInfo
    {
        private double playlistDisplayTime;
        private double timeSliceGroupDisplayTime;
        public SchedulerTemplate()
        {
            playlistDisplayTime = 2;
            timeSliceGroupDisplayTime = 2;
        }

        [Category("Default Display Time")]
        //[RangeValidator(1, 24)]
        [DisplayName("PlayList Display Time(h)")]
        public double PlayListDisplayTime
        {
            get { return playlistDisplayTime; }
            set
            {
                if (value > 0 && value <= 24)
                    playlistDisplayTime = value;
            }
        }

        ////[RangeValidator(1, 24)]
        //[Category("Default Display Time")]
        //[Browsable(false)]
        //public double MessageDisplayTime
        //{
        //    get { return Get<double>("MessageDisplayTime"); }
        //    set
        //    {
        //        if (value > 0 && value <= 24)
        //            Set<double>("MessageDisplayTime", System.Math.Abs(value));
        //    }
        //}

        //[RangeValidator(1, 24)]
        [Category("Default Display Time")]
        [DisplayName("Time Slice Group Display Time(h)")]
        public double TimeSliceGroupDisplayTime
        {
            get { return timeSliceGroupDisplayTime; }
            set
            {
                if (value > 0 && value <= 24)
                    timeSliceGroupDisplayTime = value;
            }
        }

        private bool _NeverAskAgain = true;
        [Browsable(false)]
        public virtual bool NeverAskAgain
        {
            get { return _NeverAskAgain; }
            set { _NeverAskAgain = value; }
        }

        ///// <summary>
        ///// get template type
        ///// </summary>
        //[Category("Type")]
        //[Browsable(false)]
        //public override TemplateType Type
        //{
        //    get { return TemplateType.Scheduler; }
        //}

        public override string Caption()
        {
            return SR.Type.Scheduler;
        }

        public override string View()
        {
            return SR.View.Scheduler;
        }

        public override IEnumerator<TemplateInfo> GetEnumerator()
        {
            yield return null;
        }

       
    }

}
