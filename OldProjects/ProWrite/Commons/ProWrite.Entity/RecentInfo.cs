using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ProWrite.Core;
using ProWrite.Entity.Library;

namespace ProWrite.Entity
{
    [Serializable]
    public class RecentInfo
    {
        public string LibraryGroupId { get;internal set;}
        public string LibraryId { get; internal set; }
        public string LibraryName { get; internal set; }
        public LibraryType Type { get; internal set; }
        public int Count { get;internal set;}
        public DateTime DateTime { get; internal set; }

        public override string ToString()
        {
            return LibraryName;
        }
    }


    [Serializable]
    public class Recents
    {
        private List<RecentInfo> innerList;

        public Recents()
        {
            innerList = new List<RecentInfo>(10);
            MaxShowCount = 10;
        }

        public int MaxShowCount { get; set; }

        public void Add(MemoryLibraryItem lib)
        {
            if (lib == null)
                return;

            var item = innerList.Find(p => p.LibraryId == lib.Id && p.Type == lib.Type);
            if (item == null)
            {
                item = new RecentInfo { LibraryGroupId = LibraryGroup.Current.Id, LibraryId = lib.Id, LibraryName= lib.Name, Type = lib.Type };
                //innerList.Add(item);
                innerList.Insert(0, item);
            }

            item.Count++;
            item.DateTime = DateTime.Now;
        }

        public void Remove(MemoryLibraryItem lib)
        {
            if (lib == null)
                return;
            var item = innerList.Find(p => p.LibraryId == lib.Id && p.Type == lib.Type);
            if (item != null)
                innerList.Remove(item);
        }

        public IEnumerable<RecentInfo> MessageRecents
        {
            get
            {
                return innerList
                    .Where(p => p.Type == LibraryType.Message)
                    //.OrderByDescending(p => p.DateTime)
                    .Take(MaxShowCount);
            }
        }

        public IEnumerable<RecentInfo> PlaylistRecents
        {
            get
            {
                return innerList
                    .Where(p => p.Type == LibraryType.Playlist)
                    //.OrderByDescending(p => p.DateTime)
                    .Take(MaxShowCount);
            }
        }

        public IEnumerable<RecentInfo> SchedulerRecents
        {
            get
            {
                return innerList
                    .Where(p => p.Type == LibraryType.Schedule)
                    //.OrderByDescending(p => p.DateTime)
                    .Take(MaxShowCount);
            }
        }

        public IEnumerable<RecentInfo> AllRecents
        {
            get
            {
                return innerList
                    //.OrderByDescending(p => p.DateTime)
                    .Take(MaxShowCount);
            }
        }
    }
}
