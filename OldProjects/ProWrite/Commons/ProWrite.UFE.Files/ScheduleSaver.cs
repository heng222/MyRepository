//---------------------------------------------------------------------
//
// File: ScheduleManager.cs
//
// Description:
// ScheduleManager class
//
// Author: 
//
//Modify History:
//      Jerry Xu  2008-12-6 
//      Jerry Xu  2008-12-30 Delete multiple thread
//      Jerry Xu  2009-1-4 Update Properties:Files
//      Jerry Xu  2009-1-4 Update method:Populate
//      Jerry Xu  2009-3-6 Update method:IsDeleteServerLibraries(SchedulerInfo schedule)
//      Jerry Xu  2009-3-26 Add method:IsDeleteServerLibraries(List<UfeFile> items)
//      Jerry Xu  2009-3-26 Update method:Populate()
//      Jerry Xu  2009-3-30 Update method:Populate(),IsDeleteServerLibraries(List<UfeFile> items)
//                          Update property:DeletedItems
//      Jerry Xu  2009-4-1  Update method:Populate()
//      Jerry Xu  2009-4-1  Add method:CreateDeleteSourceFiles(List<MessageInfo> messages, List<TimeSliceGroupInfo> timeSliceGroups, List<PlaylistInfo> playlists)
//
// Copyright (C) 2008 by Trans-Lux All rights reserved.
// 
//---------------------------------------------------------------------

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml.Serialization;
using log4net;
using ProWrite.Core;
using ProWrite.UFE.Entity;
using ProWrite.Entity.Shape;
using ProWrite.Entity.DES;
using System.Drawing;
using ProWrite.Entity.Dashboard;
using System.IO;
using ProWrite.Entity.Library;
using System.Threading.Tasks;
using System.Threading;

namespace ProWrite.UFE.Files
{
    /// <summary>
    /// SchedulerInfo uploaded class:create local uploaded files(SchedulerInfo)
    /// </summary>
    public class ScheduleSaver : IUFEFileSaver<SchedulerInfo>
    {
    
        private static readonly ILog log = LogManager.GetLogger("FileUpload");
        //private Task _createDirTask;
        //private List<Task> _converterTasks;
        /// <summary>
        /// Save schedule to local is succeeded.
        /// </summary>
        public bool IsSaveSucessed { get; set; }

        // <summary>
        /// Function: Save SchedulerInfo to local
        /// Author  : Jerry Xu
        /// Date    : 2008-12-6
        /// </summary>
        public void Save()
        {
            try
            {
                log.Debug("ScheduleSaver Save Start.");
           
                int fileCount = _files.Count;
                
                foreach (var item in _files)
                {
                    item.GenerateFile();
                }
               
                IsSaveSucessed = true;
            }
            catch (Exception ex)
            {
                log.Error("Schedule saved error:" + ex.Message);
                IsSaveSucessed = false;
            }
        }


        #region IUFEFileSaver<SchedulerInfo> Members

        private SignInfo _sign;
        /// Function: Upload target sign info
        /// Author  : Jerry Xu
        /// Date    : 2008-12-8
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

        private SchedulerInfo _item;
        /// <summary>
        /// Function: Current SchedulerInfo
        /// Author  : Jerry Xu
        /// Date    : 2008-12-8
        /// </summary>
        public SchedulerInfo Item
        {
            get
            {
                return _item;
            }
            set
            {
                _item = value;
            }
        }

        private List<UfeFile> _deletedItems = new List<UfeFile>();
        /// <summary>
        /// Function: Need updated items(MemoryLibraryItem):No used
        /// Author  : Jerry Xu
        /// Date    : 2008-12-8
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
        /// Author  : Jerry Xu
        /// Date    : 2008-12-8
        /// </summary>
        public List<UfeFile> NeedUpdatedItems
        {
            get
            {
                return _needUpdatedItems.ConvertAll<UfeFile>(p => { p.File.IsUpdate = true; return p.File; });
            }
        }

        private List<UfeFileGenerator> _files = new List<UfeFileGenerator>();
        private List<UfeFile> _ufeFiles = new List<UfeFile>();

        /// <summary>
        /// Function: List UfeFile(Need uploaded files)
        /// Author  : Jerry Xu
        /// Date    : 2008-12-8
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
        /// Author  : Jerry Xu
        /// Date    : 2008-12-8
        /// </summary>
        /// <param name="memory">MemoryLibraryItem</param>
        /// <returns>ExistType</returns>
        private ExistType IsExistInServerLibraries(MemoryLibraryItem memory)
        {

            foreach (var item in _sign.Controller.Connection.ServerLibraries)
            {
                if (item.Id == memory.Id.ToString())
                {
                    //CreateTime
                    if(CompareDateTime(memory.ModifyTime,DateTime.Parse(item.ModifyTime)))
                    //if (memory.ModifyTime > DateTime.Parse(item.ModifyTime))
                        return ExistType.NeededUpdate;
                    else
                        return ExistType.Yes;
                }
            }
            return ExistType.No;
        }


       

        private bool CompareDateTime(DateTime first, DateTime second)
        {
            //Year
            if (first.Year>second.Year)
                return true;
            else if (first.Year < second.Year)
                return false;
            else if (first.Year == second.Year)
            {
                //Month
                if (first.Month>second.Month)
                    return true;
                else if (first.Month < second.Month)
                    return false;
                else if (first.Month == second.Month)
                {
                    //Day
                    if (first.Day>second.Day)
                        return true;
                    else if (first.Day < second.Day)
                        return false;
                    else if (first.Day == second.Day)
                    {
                        //Hour
                        if (first.Hour>second.Hour)
                            return true;
                        else if (first.Hour < second.Hour)
                            return false;
                        else if (first.Hour == second.Hour)
                        {
                            //Minute
                            if (first.Minute>second.Minute)
                                return true;
                            else if (first.Minute < second.Minute)
                                return false;
                            else if (first.Minute == second.Minute)
                            {
                                //Second
                                if (first.Second>second.Second)
                                    return true;
                                else if (first.Second < second.Second)
                                    return false;
                                else if (first.Second == second.Second)
                                {
                                    return false;
                                }
                            }
                        }
                    }
                }
            }

            return false;
           
        }

        /// <summary>
        /// Function: Is exist in local libraries
        /// Author  : Jerry Xu
        /// Date    : 2008-12-8
        /// </summary>
        /// <param name="memory">MemoryLibraryItem</param>
        /// <param name="items">List<MemoryLibraryItem></param>
        /// <returns>bool</returns>
        private bool IsExistInLibraries(MemoryLibraryItem memory, List<UfeFileGenerator> items)
        {
            if(memory==null || (items==null || items.Count==0))
                return false;
            var item = items.Find(p => { return p.Library != null && p.Library.Id == memory.Id; });
            return item != null;
        }

        /// <summary>
        /// Function: Is exist in server libraries
        /// Author  : Jerry Xu
        /// Date    : 2008-12-8
        /// </summary>
        /// <param name="memory">MemoryLibraryItem</param>
        /// <returns>ExistType</returns>
        private void IsDeleteServerLibraries(List<UfeFile> items)
        {
            UfeFile file = null;
            FileType type = FileType.Message;
            foreach (var item in _sign.Controller.Connection.ServerLibraries)
            {
                var memory = items.Find(p => { return p.Id == item.Id; });
                if (memory == null)
                {
                    file = new UfeFile();
                    file.Id = item.Id;
                    if (item.Type == ServerLibraryType.Message)
                    {
                        type = FileType.Message;
                        file.Type = type;
                        _deletedItems.Add(file);

                        //TODO:Add nail image to delete
                        //file = new UfeFile();
                        //file.Id = item.Id;
                        //file.Type = FileType.MessageNailImage;
                        //_deletedItems.Add(file);
                    }
                    else if (item.Type == ServerLibraryType.TimesliceGroup)
                        type = FileType.TimesliceGroup;
                    else if (item.Type == ServerLibraryType.Playlist)
                        type = FileType.Playlist;
                    else if (item.Type == ServerLibraryType.Schedule)
                        type = FileType.Schedule;
                    //else if(item.Type == ServerLibraryType.


                    file.Type = type;
                    _deletedItems.Add(file);
                }
            }
        }

        public void Populate()
        {
            if(_item==null)
                return;
            
            _files.Clear();
            _needUpdatedItems.Clear();
            _deletedItems.Clear();

           
            LocalFilePathMapping.CreateDirectories(true);
           
            CreateLibrary<SchedulerInfo>(_item);
            var messages = _item.Messages;
            var timeSliceGroups = _item.TimeSliceGroups;
            var playlists = _item.Playlists;

            if (messages != null && messages.Count > 0)
                CreateLibrary<MessageInfo>(messages.ToArray());

            if (timeSliceGroups != null && timeSliceGroups.Count > 0)
                CreateLibrary<TimeSliceGroupInfo>(timeSliceGroups.ToArray());

            if (playlists != null && playlists.Count > 0)
                CreateLibrary<PlaylistInfo>(playlists.ToArray());

            List<UfeFile> deletedFiles = CreateDeleteSourceFiles(messages, timeSliceGroups, playlists);

            IsDeleteServerLibraries(deletedFiles);

            _files.ForEach(item => item.Populate());
        }

        private List<UfeFile> CreateDeleteSourceFiles(List<MessageInfo> messages, List<TimeSliceGroupInfo> timeSliceGroups, List<PlaylistInfo> playlists)
        {
            List<UfeFile> deletedFiles = new List<UfeFile>();
            UfeFile file;
            if (_item != null)
            {
                file = new UfeFile();
                file.Id = _item.Id;
                file.Type = FileType.Schedule;
                deletedFiles.Add(file);
            }

            if (messages != null && messages.Count > 0)
            {
                foreach (MessageInfo item in messages)
                {
                    file = new UfeFile();
                    file.Id = item.Id;
                    file.Type = FileType.Message;
                    deletedFiles.Add(file);

                    //Add Nail Image to delete
                    //file = new UfeFile();
                    //file.Id = item.Id;
                    //file.Type = FileType.MessageNailImage;
                    //deletedFiles.Add(file);
                }
            }

            if (timeSliceGroups != null && timeSliceGroups.Count > 0)
            {
                foreach (TimeSliceGroupInfo item in timeSliceGroups)
                {
                    file = new UfeFile();
                    file.Id = item.Id;
                    file.Type = FileType.TimesliceGroup;
                    deletedFiles.Add(file);
                }
            }

            if (playlists != null && playlists.Count > 0)
            {
                foreach (PlaylistInfo item in playlists)
                {
                    file = new UfeFile();
                    file.Id = item.Id;
                    file.Type = FileType.Playlist;
                    deletedFiles.Add(file);
                }
            }
            return deletedFiles;
        }

        
        

        private void CreateLibrary<T>(params T[] libraries) where T : MemoryLibraryItem
        {
            if (libraries != null && libraries.Length > 0)
            {
                ExistType type;

                //Parallel.ForEach<T>(libraries, item =>
                foreach (var item in libraries)
                {
                    if (item != null)
                    {
                        UfeFileGenerator pair = null;
                        type = IsExistInServerLibraries(item);
                        if (type == ExistType.No && !IsExistInLibraries(item, _files))
                            pair = new UfeFileGenerator { Sign = _sign, Library = item };
                        else if (type == ExistType.NeededUpdate && !IsExistInLibraries(item, _needUpdatedItems))
                        {
                            pair = new UfeFileGenerator { Sign = _sign, Library = item };
                            pair.IsUpdate = true;
                            //_needUpdatedItems.Add(pair);
                        }

                        if (pair != null)
                        {
                            _files.Add(pair);
                        }
                    }
                }
                //});
            }
        }      
        #endregion
    }

    public class UfeFileGenerator:IEquatable<UfeFileGenerator>
    {
        private static Dictionary<ProWrite.Core.LibraryType, Func<IUfeFileLibraryConverter>> _converters = new Dictionary<ProWrite.Core.LibraryType, Func<IUfeFileLibraryConverter>>();
        static UfeFileGenerator()
        {
            _converters[ProWrite.Core.LibraryType.Schedule] = () =>  new UfeFileScheduleConverter();
            _converters[ProWrite.Core.LibraryType.Playlist] = () => new UfeFilePlaylistConverter(); 
            _converters[ProWrite.Core.LibraryType.TimeSliceGroup] = () => new UfeFileTimeSliceGroupConverter();
            _converters[ProWrite.Core.LibraryType.Message] = () =>  new UfeFileMessageConverter(); 
        }

        internal UploadMode UploadMode;
        internal bool IsUpdate;

        private IUfeFileLibraryConverter _converter;
        public SignInfo Sign { get; set; }

        private MemoryLibraryItem _library = null;
        public MemoryLibraryItem Library
        {
            get { return _library; }
            set
            {
                _library = value;
                _converter = _converters[value.Type]();
                _converter.Sign = Sign;
                //Populate();
            }
        }

        private List<UfeFile> _files = new List<UfeFile>();
        public List<UfeFile> Files
        {
            get
            {
                _files.ForEach(item =>
                {
                    item.UploadMode = UploadMode;
                    item.IsUpdate = IsUpdate;
                });
                return _files;
            }
            private set
            {
                _files = value;
            }
        }

        public UfeFile File
        {
            get { return _files[0]; }
        }


        internal void Populate()
        {
            Check.Require(_library != null, "_library != null");
            object result = _converter.Convert(_library);
            UfeFile file = result as UfeFile;
            if (file != null)
                _files.Add(file);
            else
            {
                List<UfeFile> files = result as List<UfeFile>;
                if (files != null)
                    _files = files;
            }
        }

        public void GenerateFile()
        {
            _converter.Generate();
        }

        public bool Equals(UfeFileGenerator other)
        {
            if (other == null)
                return false;
            if (!Sign.Equals(other.Sign))
                return false;
            if (!Library.Equals(other.Library))
                return false;
            return true;

        }

        public override bool Equals(object obj)
        {
            return Equals(obj as UfeFileGenerator);
        }

        public override int GetHashCode()
        {
            return 134 ^ Sign.GetHashCode() ^ Library.GetHashCode();
        }
    }
}
