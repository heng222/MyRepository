using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace ProWrite.Entity.Settings
{
    class SR
    {
        public class View
        {
            public const string TemplateGroup = "ProWrite.UI.Controls.Options.Views.TemplateGroupView";

            public const string Sign = "ProWrite.UI.Controls.Options.Views.SignView";
            public const string Scheduler = "ProWrite.UI.Controls.Options.Views.SchedulerView";
            public const string Playlist = "ProWrite.UI.Controls.Options.Views.PlaylistView";
            public const string Message = "ProWrite.UI.Controls.Options.Views.MessageView";


            public const string DynamicText = "ProWrite.UI.Controls.Options.Views.SignView";
            public const string Paint = "ProWrite.UI.Controls.Options.Views.PaintView";
            public const string Image = "ProWrite.UI.Controls.Options.Views.ImageView";
            public const string Video = "ProWrite.UI.Controls.Options.Views.VideoView";
            public const string Time = "ProWrite.UI.Controls.Options.Views.TimeView";
            public const string Text = "ProWrite.UI.Controls.Options.Views.TextView";
            public const string Temperature = "ProWrite.UI.Controls.Options.Views.TemperatureView";
            public const string Line = "ProWrite.UI.Controls.Options.Views.LineView";
        }

        [Serializable]
        public class Type
        {
            public const string Sign = "Sign",
            Message = "Message",
            Playlist = "Playlist",
            TimeScliceGroup = "",
            Scheduler = "Scheduler",
            Shape = "Shape",
            Paint = "Paint Layer",
            Line = "Line",
            Text = "Text Layer",
            Image = "Picture Layer",
            DynamicText = "Dynamic Text Layer",
            Temperature = "Temperature Layer",
            Time = "Time Layer",
            Video = "Video Layer";
        }
    }
}
