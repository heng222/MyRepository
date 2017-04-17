using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ProWrite.UFE.Entity;
using System.Xml.Serialization;

namespace ProWrite.UFE.Entity
{

    /// <summary>
    /// Library type
    /// </summary>
    public enum ServerLibraryType : byte
    {
        Message,// = IncludeFileType.FrameObject,
        TimesliceGroup,// = IncludeFileType.TimeSliceGroup,
        Playlist,// = IncludeFileType.Playlist,
        Schedule,//= IncludeFileType.Schedule,
        TemplateMessage,// = IncludeFileType.TemplateFrameObject,
        None,
    }

    /// <summary>
    /// Library uploade mode
    /// </summary>
    [Flags]
    public enum UploadMode
    {
        Scheduler = 1,//by scheduler upload
        Live = Scheduler * 2,//by live upload
        All = Scheduler + Live,//by scheduler and live upload
    }

    [Serializable]
    public class IdObject
    {
        private string _id;
        public string Id
        {
            get { return _id; }
            set
            {
                if (!string.Equals(value, _id))
                {
                    _id = value.Replace("-", "");
                }
            }
        }
        public IdObject()
        {
            Id = Guid.NewGuid().ToString();
        }
    }

    [Serializable]
    public class ServerLibraryItem : IdObject
    {

        public string Name;
        public ServerLibraryType Type;
        public float Length = 1;

        public string CreateTime { get; set; }
        public string ModifyTime { get; set; }

        public UploadMode UploadMode { get; set; }

        public object[] ToArray()
        {
            return new object[] { Name, Type, null };
        }

    }

    [Serializable]
    public class LiveItem : IdObject
    {
        public string Name { get; set; }
        public ServerLibraryItem Library { get; set; }

    }

    [Serializable]
    public class LiveCategory : IdObject
    {
        public string Name { get; set; }
        public List<LiveItem> Items { get; set; }
    }

    [Serializable]
    public class HotItem : IdObject
    {
        public string Name { get; set; }
        public LiveItem Item { get; set; }
        public PlayLevel Level { get; set; }
    }

    [Serializable]
    public class QueueItem : IdObject, IComparable<QueueItem>
    {
        public string ReginId { get; set; }
        public string Name { get; set; }
        public ServerLibraryItem Library { get; set; }
        public PlayLevel Level { get; set; }


        #region IComparable<QueueItem> Members
        public int CompareTo(QueueItem other)
        {
            if (other == null)
                return 1;
            int result = other.Level - Level;
            if (result == 0)
                return 0;
            else if (result > 0)
                return 1;
            else
                return -1;
        }
        #endregion
    }
    [Serializable]
    public class LiveInfo
    {
        [XmlIgnore]
        public bool CanFtpOperation { get; set; }

        [XmlIgnore]
        public List<ServerLibraryItem> ServerLibraries { get; set; }

        [XmlIgnore]
        public string Templates { get; set; }

        [XmlIgnore]
        public string TemplateInstance { get; set; }

        [XmlIgnore]
        public string TemplateInstanceTd { get; set; }

        [XmlIgnore]
        public string QueSelectedPageName { get; set; }


        [XmlIgnore]
        public List<string> QueTabPageNames { get; set; }

        [XmlIgnore]
        public List<LiveCategory> LiveCategories { get; set; }

        [XmlIgnore]
        public List<HotItem> HotItems { get; set; }

        public HotItem GetLiveHotItem(string id)
        {
            if (HotItems == null || HotItems.Count == 0)
                return null;
            foreach (HotItem item in HotItems)
            {
                if (item.Id == id)
                    return item;
            }
            return null;
        }


        public bool ContainsLiveCategory(string categoryName)
        {
            if (LiveCategories == null || LiveCategories.Count == 0)
                return false;
            foreach (LiveCategory item in LiveCategories)
            {
                if (item.Name == categoryName)
                    return true;
            }
            return false;
        }

        public LiveCategory GetLiveCategoryByName(string categoryName)
        {
            if (LiveCategories == null || LiveCategories.Count == 0)
                return null;
            foreach (LiveCategory item in LiveCategories)
            {
                if (item.Name == categoryName)
                    return item;
            }
            return null;
        }

    }

}
