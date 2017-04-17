using System;
using System.Collections.Generic;
using System.Linq;
using log4net;
using ProWrite.Core;
using ProWrite.Entity.Dashboard;
using ProWrite.Entity.Library;
using ProWrite.Entity.Live;
using ProWrite.UFE.Entity;

namespace ProWrite.UFE.Files
{
    public class LiveSessionSaver:IUFEFileSaver<SessionInfo>
    {
        private static readonly ILog log = LogManager.GetLogger("Live session saver");
      
        /// <summary>
        /// Save libraries to local is succeeded.
        /// </summary>
        public bool IsSaveSucessed { get; set; }

        // <summary>
        /// Function: Save libraries to local
        /// </summary>
        public void Save()
        {
            try
            {
                log.Debug("Live session Save Start.");

                int fileCount = _files.Count;

                foreach (var item in _files)
                {
                    item.GenerateFile();
                }

                IsSaveSucessed = true;
            }
            catch (Exception ex)
            {
                log.Error("Live session saved error:" + ex.Message);
                IsSaveSucessed = false;
            }
        }


                                                                                                                                                                    #region IUFEFileSaver<SessionInfo> Members

        private SignInfo _sign;
        /// Function: Upload target sign info
        public SignInfo Sign
        {
            get
            {
                return _sign;
            }
            set
            {
                if (value != _sign)
                    _sign = value;
            }
        }

        /// <summary>
        /// Function: Current Item
        /// </summary>
        public SessionInfo Item { get; set; }

        private List<UfeFile> _deletedItems = new List<UfeFile>();
        /// <summary>
        /// Function: Need updated items(MemoryLibraryItem):No used
        /// </summary>
        public List<UfeFile> DeletedItems
        {
            get
            {
                return _deletedItems;
            }
        }

        private List<UfeFileGenerator> _needUpdatedItems = new List<UfeFileGenerator>();
        /// <summary>
        /// Function: Need updated items(MemoryLibraryItem):No used
        /// </summary>
        public List<UfeFile> NeedUpdatedItems
        {
            get
            {
                return _needUpdatedItems.ConvertAll<UfeFile>(p => { p.File.IsUpdate = true; return p.File; });
            }
        }

        private HashSet<UfeFileGenerator> _files = new HashSet<UfeFileGenerator>();
        private List<UfeFile> _ufeFiles = new List<UfeFile>();

        /// <summary>
        /// Function: List UfeFile(Need uploaded files)
        /// </summary>
        public List<UfeFile> Files
        {
            get
            {

                _ufeFiles.Clear();
                foreach (var item in _files)
                {
                    if (item.Files != null && item.Files.Count > 0)
                        _ufeFiles.AddRange(item.Files);
                }

                return _ufeFiles;
            }
        }

        /// <summary>
        /// Function: Is exist in server libraries
        /// </summary>
        /// <param name="memory">MemoryLibraryItem</param>
        /// <returns>ExistType</returns>
        private ExistType IsExistInServerLibraries(MemoryLibraryItem memory)
        {
            foreach (var item in _sign.Controller.Connection.ServerLibraries)
            {
                if (item.Id == memory.Id)
                {
                    if (CompareDateTime(memory.ModifyTime, DateTime.Parse(item.ModifyTime)))
                        return ExistType.NeededUpdate;
                    else
                        return ExistType.Yes;
                }
            }
            return ExistType.No;
        }




        private static bool CompareDateTime(DateTime first, DateTime second)
        {
            //Year
            if (first.Year != second.Year)
                return false;
            if (first.Month != second.Month)
                return false;
            if (first.Day != second.Day)
                return false;
            if (first.Hour != second.Hour)
                return false;
            if (first.Minute != second.Minute)
                return false;
            if (first.Second != second.Second)
                return false;

            return true;
        }

      

        /// <summary>
        /// Function: Is exist in server libraries
        /// </summary>
        /// <param name="memory">MemoryLibraryItem</param>
        /// <returns>ExistType</returns>
        private void IsDeleteServerLibraries(List<UfeFile> items)
        {
            UfeFile file = null;
            FileType type = FileType.Message;
            foreach (var item in _sign.Controller.Connection.ServerLibraries)
            {
                var memory = items.FirstOrDefault(p => p.Id == item.Id);
                if (memory == null)
                {
                    file = new UfeFile();
                    file.Id = item.Id;
                    if (item.Type == ServerLibraryType.Message)
                    {
                        type = FileType.Message;
                        file.Type = type;
                        _deletedItems.Add(file);
                    }
                    else if (item.Type == ServerLibraryType.TimesliceGroup)
                        type = FileType.TimesliceGroup;
                    else if (item.Type == ServerLibraryType.Playlist)
                        type = FileType.Playlist;
                    else if (item.Type == ServerLibraryType.Schedule)
                        type = FileType.Schedule;

                    file.Type = type;
                    _deletedItems.Add(file);
                }
            }
        }

        public void Populate()
        {
            if (Item == null)
                return;

            _files.Clear();
            _needUpdatedItems.Clear();
            _deletedItems.Clear();

        
            LocalFilePathMapping.CreateDirectories(true);

            var memoryLibs = Item.MemoryLibraries;
            CreateLibrary(memoryLibs);

            List<UfeFile> deletedFiles = CreateDeleteSourceFiles(memoryLibs);

            IsDeleteServerLibraries(deletedFiles);

            _files.ForEach(item => item.Populate());
        }

        protected virtual List<UfeFile> CreateDeleteSourceFiles(MemoryLibraryItem[] messages)
        {
            List<UfeFile> deletedFiles = new List<UfeFile>();
            
            if (messages != null && messages.Length > 0)
            {
               
                foreach (var item in messages)
                {
                    var file = new UfeFile();
                    file.Id = item.Id;
                    switch (item.Type)
                    {
                        case LibraryType.Message:
                            file.Type = FileType.Message;
                            break;
                        case LibraryType.TimeSliceGroup:
                            file.Type = FileType.TimesliceGroup;
                            break;
                        case LibraryType.Playlist :
                            file.Type = FileType.Playlist;
                            break;
                        case LibraryType.Schedule:
                            file.Type = FileType.Schedule;
                            break;
                    }
                    deletedFiles.Add(file);
                }
            }

           
            return deletedFiles;
        }




        private void CreateLibrary(params MemoryLibraryItem[] libraries)
        {
            if (libraries == null || libraries.Length == 0)
                return;

            foreach (var item in libraries)
            {
                if (item == null) continue;

                var serverLibs = Sign.Controller.Connection.ServerLibraries;
                if (serverLibs.Count == 0)
                    _files.Add(new UfeFileGenerator { Sign = _sign, Library = item });
                else
                {
                    foreach (var serverItem in Sign.Controller.Connection.ServerLibraries)
                    {
                        UfeFileGenerator pair = null;

                        if (item.Id == serverItem.Id
                            && CompareDateTime(DateTime.Parse(serverItem.ModifyTime), item.ModifyTime))
                        {

                            pair = new UfeFileGenerator { Sign = _sign, Library = item };
                            pair.IsUpdate = true;

                            if ((serverItem.UploadMode & UploadMode.Scheduler) == UploadMode.Scheduler)
                                pair.UploadMode = UploadMode.All;
                            else
                                pair.UploadMode = UploadMode.Live;
                        }
                        else
                        {
                            pair = new UfeFileGenerator { Sign = _sign, Library = item, UploadMode = UploadMode.Live, };
                        }

                        if (pair != null)
                        {
                            _files.Add(pair);
                        }
                    }
                }
            }


        }
        #endregion
    }
}
