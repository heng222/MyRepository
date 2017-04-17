using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ComponentModel;
using System.Drawing;
using ProWrite.Core.Validation;

namespace ProWrite.Entity.Settings
{
    /// <summary>
    /// class of playlistTemplate
    /// </summary>
    [Serializable]
    [TypeConverter(typeof(ExpandableObjectConverter))]
    //[SettingView(SR.Playlist)]
    public class PlayListTemplate : TemplateInfo
    {
        public PlayListTemplate()
        {
            Width = 100;
            Height = 200;
        }
        /// <summary>
        /// 
        /// </summary>
        public Color BackGround
        {
            get { return Get<Color>("BackGround"); }
            set { Set<Color>("BackGround", value); }
        }

        [RangeValidator(10, 9999)]
        [Browsable(false)]
        public int Width
        {
            get { return Get<int>("Width"); }
            set
            {
                if (value >= 10 && value <= 9999)
                    Set<int>("Width", System.Math.Abs(value));
            }
        }

        [RangeValidator(10, 9999)]
        [Browsable(false)]
        public int Height
        {
            get { return Get<int>("Height"); }
            set
            {
                if (value >= 10 && value <= 9999)
                    Set<int>("Height", System.Math.Abs(value));
            }
        }
        private int _excursion;
        public virtual int Excursion
        {
            get { return _excursion; }
            set { _excursion = value; }
        }
        ///// <summary>
        ///// get template type
        ///// </summary>
        //[Category("Type")]
        //[Browsable(false)]
        //public override TemplateType Type
        //{
        //    get { return TemplateType.Playlist; }
        //}

        public override string Caption()
        {
            return SR.Type.Playlist;
        }

        public override string View()
        {
            return SR.View.Playlist;
        }

        public override IEnumerator<TemplateInfo> GetEnumerator()
        {
            yield return null;
        }

        
    }
}
