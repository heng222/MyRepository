//---------------------------------------------------------------------
//
// File: DataProvider.cs
//
// Description:
// Data Provider
//
// Author: Kevin
//
// Copyright (C) 2008 by Trans-Lux All rights reserved.
// 
//---------------------------------------------------------------------
using System;
using System.Collections.Generic;
using System.Text;
using System.Threading;
using ProWrite.Core;
using log4net;
using ProWrite.Entity.Library;
using ProWrite.Entity;
using System.Runtime.Serialization.Formatters.Binary;
using System.IO;
using System.Diagnostics;
using ProWrite.Entity.Dashboard;
using System.Threading.Tasks;

namespace ProWrite.DataProviders
{
    public class DataProvider : IAutoUpdateDataProvider<ProjectInfo>, IDisposable
    {
        private static readonly ILog log = LogManager.GetLogger(typeof(DataProvider));
        private ProjectInfo _project;
        private bool _isRuning = false;
        private readonly object _InnerLocker = new object();
        private BinaryFormatter _fmt = new BinaryFormatter();
        private Task _loadTask = null;

        public DataProvider()
        {
            _loadTask = Task.Create(p => { DoLoad(); });
        }


        private string FullName
        {
            get
            {
                if (!string.IsNullOrEmpty(Path) && !string.IsNullOrEmpty(FileName))
                    return Path + FileName;
                else
                {
                    try
                    {
                        Config.AddOrUpdateAppSettings("ProFilePath", Constance.DataPath+"\\");
                    }
                    catch
                    { }
                    return Constance.BinaryDataFile;
                }
            }
        }

        public string Path
        {
            get
            {
                return Config.GetAppSettingValueBytKey("ProFilePath");
            }
            set 
            {
                try
                {
                    Config.AddOrUpdateAppSettings("ProFilePath", value);
                }
                catch
                { }
            }
        }
        public string FileName
        {
            get
            {
                string fileName =Config.GetAppSettingValueBytKey("ProFileName");
                if (string.IsNullOrEmpty(fileName))
                    return "data.binary";
                else
                    return fileName;
            }
            set
            {
               
                Config.AddOrUpdateAppSettings("ProFileName", value);
            }
        }


        private int _interval = 10;
        public int Interval
        {
            get
            {
                return _interval;
            }
            set
            {
                if (_interval != value)
                {
                    Check.Assert(value > 0);
                    _interval = value;
                }
            }
        }

        public bool IsRuning
        {
            get { return _isRuning; }
        }

        public void Start()
        {
        }

        public void Stop()
        {
        }

        public void Refresh()
        {
            DoLoad();
        }

        private void DoLoad()
        {
            if (_project != null)
                _project.RootGroup.Clear();

            log.Info("Loading Project info Start");

            Stream stream = null;

            try
            {
                if (File.Exists(FullName))
                {
                    stream = File.OpenRead(FullName);
                    log.Info("Serializing " + this.GetType().Name);
                    _project = _fmt.Deserialize(stream) as ProjectInfo;
                    log.Info("Serializing " + this.GetType().Name);
                }
            }
            catch (Exception ex)
            {
                log.Error(ex.Message, ex);
                Debug.WriteLine(ex.Message);
            }
            finally
            {
                if (stream != null)
                {
                    stream.Dispose();
                    stream = null;
                }
            }

            if (_project == null)
            {
                _project = new ProjectInfo();
                _project.AddDefaultItem();
            }
            else
            {
                _project.RootGroup.PopulateRelation();
                _project.LibraryGroups.PopulateRelation();
                _project.AcceptChanges();
            }

            ProjectInfo.Current = _project;

            log.Info("Loaded Project Done");
        }

        private bool DoUpdate()
        {
            bool flag = true;

            //var task = Task.Create(p =>
            //{
            log.Info("Updating Project info...");
            lock (_InnerLocker)
            {
                Stream stream = null;
                try
                {
                    if (!File.Exists(FullName))
                        stream = File.Create(FullName);
                    else
                        stream = new FileStream(FullName, FileMode.OpenOrCreate);

                    log.Info("Serializing " + this.GetType().Name);
                    _fmt.Serialize(stream, _project);
                    log.Info("Serialized " + this.GetType().Name);
                }
                catch (Exception ex)
                {
                    flag = false;
                    log.Error(ex.Message, ex);
                    Debug.WriteLine(ex.Message);
                }
                finally
                {
                    if (stream != null)
                    {
                        stream.Dispose();
                        stream = null;
                    }
                }
            }
            log.Info("Updated Project info...");
            //});

            //if (!task.IsCompleted)
            //{
            //    task.Wait();
            //    task.Dispose();
            //    task = null;
            //}

            return flag;
        }

        public ProjectInfo Get()
        {
            if (_loadTask != null && !_loadTask.IsCompleted)
            {
                _loadTask.Wait();
                _loadTask.Dispose();
                _loadTask = null;
            }
            return _project;
        }

        public bool Update(ProjectInfo project)
        {
            _project = project;
            return DoUpdate();
        }

        public bool Update()
        {
            return DoUpdate();
        }

        #region IDisposable Members

        public void Dispose()
        {
            Stop();
            _project.Dispose();
        }

        #endregion


        #region IDataProvider Members

        object IDataProvider.Get()
        {
            return _project;
        }

        bool IDataProvider.Update(object project)
        {
            return Update(project as ProjectInfo);
        }

        #endregion
    }
}
