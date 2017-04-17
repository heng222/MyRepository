using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ProWrite.Entity.Dashboard;
using ProWrite.UFE.Entity;
using ProWrite.Entity.Library;
using ProWrite.Core;
using ProWrite.Entity;
using System.Threading.Tasks;

namespace ProWrite.UFE.Files
{
    public class SchedulerParser
    {
        private SignInfo Sign;
        private SchedulerInfo Item;
        public SchedulerParser(SignInfo sign, SchedulerInfo item)
        {
            Sign = sign;
            Item = item;

            Check.Require(Item, "Item", Check.NotNull);
            Check.Require(Sign, "Sign", Check.NotNull);
        }

        private static bool IsExistInLibraries(MemoryLibraryItem memory, List<UfeFileGenerator> items)
        {
            if (memory == null || (items == null || items.Count == 0))
                return false;
            var item = items.Find(p => { return p.Library != null && p.Library.Id == memory.Id; });
            return item != null;
        }

        private static ExistType IsExistInServerLibraries(MemoryLibraryItem memory,SignInfo Sign)
        {

            foreach (var item in Sign.Controller.Connection.ServerLibraries)
            {
                if (item.Id == memory.Id.ToString())
                {
                    //CreateTime
                    if (memory.ModifyTime > DateTime.Parse(item.ModifyTime))
                        return ExistType.NeededUpdate;
                    else
                        return ExistType.Yes;
                }
            }
            return ExistType.No;
        }

        public ParseResult Parse()
        {
            var messages = Item.Messages;
            var timeSliceGroups = Item.TimeSliceGroups;
            var playlists = Item.Playlists;

            Check.Require(messages != null, "messages != null");
            Check.Require(messages.Count > 0, "messages.Count > 0");

            List<MemoryLibraryItem> items = new List<MemoryLibraryItem>();
            items.AddRange(messages.ToArray());

            if (timeSliceGroups != null && timeSliceGroups.Count > 0)
                items.AddRange(timeSliceGroups.ToArray());

            if (playlists != null && playlists.Count > 0)
                items.AddRange(playlists.ToArray());

           
            ExistType type;
            UfeFileGenerator pair = null;

            ParseResult result = new ParseResult();
            List<UfeFileGenerator> _files = result.Generators;
            List<UfeFileGenerator> _needUpdatedItems = result.NeedUpdatedGenerators;

            foreach (var item in items)
            {
                if (item != null)
                {
                    
                    type = IsExistInServerLibraries(item,Sign);

                    if (type == ExistType.No && !IsExistInLibraries(item, _files))
                        pair = new UfeFileGenerator { Sign = Sign, Library = item };

                    else if (type == ExistType.NeededUpdate && !IsExistInLibraries(item, _needUpdatedItems))
                    {
                        pair = new UfeFileGenerator { Sign = Sign, Library = item };
                        _needUpdatedItems.Add(pair);
                    }

                    if (pair != null) _files.Add(pair);
                }
            }

            Check.Require(_files.Count > 0, "_files.Count > 0");
            return result;
        }

        public static Future<ParseResult> ParseAsync(SignInfo sign, SchedulerInfo item)
        {
            var parser = new SchedulerParser(sign, item);
            return Future.Create<ParseResult>(() => { return parser.Parse(); });
        }

    }

    public class ParseResult
    {
        private List<UfeFileGenerator> _files = new List<UfeFileGenerator>();
        private List<UfeFileGenerator> _needUpdatedItems = new List<UfeFileGenerator>();

        internal List<UfeFileGenerator> NeedUpdatedGenerators
        {
            get
            {
                return _needUpdatedItems;
            }
        }

        public List<UfeFileGenerator> Generators
        {
            get
            {
                return _files;
            }
        }

        public List<UfeFile> Files
        {
            get
            {
                var items = new List<UfeFile>();
                foreach (var item in _files)
                {
                    if (item.Files != null && item.Files.Count > 0)
                        items.AddRange(item.Files);
                }
                return items;
            }
        }

        public List<UfeFile> NeeedUpdateFiles
        {
            get { return _needUpdatedItems.ConvertAll<UfeFile>(p => { return p.File; }); }
        }
    }
}
