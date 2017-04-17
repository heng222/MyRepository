using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ProWrite.Core;
using System.ComponentModel;
using System.Drawing;

namespace ProWrite.Entity.Library
{
    [Serializable]
    [TypeConverter(typeof(ExpandableObjectConverter))]
    public class MLPlaylistInfo:MemoryLibraryItem
    {
        public override ProWrite.Core.LibraryType Type
        {
            get { return ProWrite.Core.LibraryType.MLPlaylist; }
        }

        private ListSet<RegionInfo> _items = new ListSet<RegionInfo>();
        public ListSet<RegionInfo> Items
        {
            get
            {
                return _items;
            }
            set
            {
                _items.Clear();
                if (value != null && value.Count > 0)
                    foreach (var item in value)
                        _items.Add(item.Copy() as RegionInfo);
            }
        }

        public bool IsPlaylist
        {
            get { return _items.Count == 1; }
        }

        public override LibraryType AcceptType
        {
            get
            {
                return LibraryType.Message | LibraryType.Playlist | LibraryType.MLPlaylist| LibraryType.TimeSliceGroup;
            }
        }

        public override bool IsReferenceLibrary(LibraryItem library)
        {
            if ((AcceptType & library.Type) != library.Type)
                return false;

            foreach (var rg in _items)
            {
                foreach (var item in rg.Items)
                {
                    if (item != null
                        && item.Target != null
                        && item.Target.Type == library.Type
                        && item.Target.Name == library.Name)
                        return true;
                }

            }
            return false;
        }

        public bool IsReferenceMessage(MessageInfo msg)
        {
            foreach (var rg in _items)
            {
                foreach (var item in rg.Items)
                {
                    if (item != null
                        && item.Type == LibraryType.MessageProxy
                        && item.Target != null
                        && item.Target.Name == msg.Name)
                        return true;
                }

            }
            return false;
        }


        public override MemoryLibraryItem NewInstance()
        {
            return new MLPlaylistInfo();
        }

        public override void FromTo(MemoryLibraryItem memory)
        {
            base.FromTo(memory);
            var item = memory as MLPlaylistInfo;
            if (item != null)
            {
                if (item._items != null && item._items.Count > 0)
                {
                    foreach (var region in item._items)
                        _items.Add(region.Copy() as RegionInfo);
                }
            }
        }

        public override LibraryAdapter ToProxy()
        {
            return new MLPlaylistAdapterInfo { TargetId = Id, Target = this };
        }
    }

    [Serializable]
    public class RegionInfo : MemoryLibraryItem
    {
        public override ProWrite.Core.LibraryType Type
        {
            get { return ProWrite.Core.LibraryType.Region; }
        }

        public Rectangle Bounds { get; set; }

        private ListSet<LibraryAdapter> _items = new ListSet<LibraryAdapter>();

        public ListSet<LibraryAdapter> Items
        {
            get
            {
                return _items;
            }
            set
            {
                _items.Clear();
                if (value != null && value.Count > 0)
                    foreach (var item in value)
                        _items.Add(item.Copy());
            }
        }

        public override MemoryLibraryItem NewInstance()
        {
            return new RegionInfo();
        }

        public override void FromTo(MemoryLibraryItem memory)
        {
            base.FromTo(memory);
            var item = memory as RegionInfo;
            if (item != null)
            {
                if (item._items != null && item._items.Count > 0)
                {
                    foreach (var adp in item._items)
                        _items.Add(adp.Copy());
                }
            }
        }
    }

    [Serializable]
    public class MLPlaylistAdapterInfo : LibraryAdapter
    {
        public override LibraryAdapter NewInstance()
        {
            return new MLPlaylistAdapterInfo();
        }

        public override LibraryType Type
        {
            get { return LibraryType.MLPlaylistProxy; }
        }
    }
}
