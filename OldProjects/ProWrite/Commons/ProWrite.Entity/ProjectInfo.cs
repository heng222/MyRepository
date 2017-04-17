//---------------------------------------------------------------------
//
// File: ProjectInfo.cs
//
// Description:
// 
//
// Author: Kevin
//
// Modify History:
//      Jerry Xu 2008-7-8  Delete properties:PlayListDataSet,ListLibraryInfo,ListPlayListsInfo,ListSetMemoryLibraryItem
//      Jerry Xu 2009-3-25 Update method:AddDefaultItem()
//      Jerry Xu 2009-7-16 Add property:SessionInfos
//
// Copyright (C) 2008 by Trans-Lux All rights reserved.
// 
//---------------------------------------------------------------------
using System;
using System.Collections.Generic;
using System.Text;
using System.Configuration;
using System.IO;
using System.Xml.Serialization;
using ProWrite.Core;
using System.Reflection;
using System.Runtime.Serialization;
using ProWrite.Entity.Dashboard;
using ProWrite.Entity.Library;
using ProWrite.Entity.Settings;
using ProWrite.Entity.DataManager;
using ProWrite.Entity.Live;

namespace ProWrite.Entity
{
	[Serializable]
	public class ProjectInfo:IDisposable
	{
		public ProjectInfo()
		{
			_rootSign = new SignGroupTree();
			_templates = new TemplateGroups();
			_libraryGroups = new LibraryGroups();
            _sessionInfos = new SessionInfos();
            _sources = new ListSet<DataItem>();
            _recents = new Recents();
		}

        public static ProjectInfo Current { get; set; }
        
        [OptionalField]
        private ListSet<DataItem> _sources;
        [OptionalField]
        private string _currentModule;

        [OptionalField]
        private Recents _recents;


        public Recents Recents
        {
            get
            {
                return _recents;
            }
        }

        public string LastModule
        {
            get { return _currentModule; }
            set { _currentModule = value; }
        }

        public ListSet<DataItem> DataSources { get { return _sources; } set { _sources = value; } }
       
		private SignGroupTree _rootSign;
		public SignGroupTree RootGroup
		{
			get
			{
				return _rootSign;
			}
			set { _rootSign = value; }
		}

        private SessionInfos _sessionInfos;
        public SessionInfos SessionInfos
        {
            get
            {

                return _sessionInfos;
            }
            set { _sessionInfos = value; }
        }

		private LibraryGroups _libraryGroups;
		public LibraryGroups LibraryGroups
		{
			get
			{
                
				return _libraryGroups;
			}
			set { _libraryGroups = value; }
		}

        private List<LiveCategory> _lstCategory;
        public List<LiveCategory> ListCategories
        {
            get
            {
                return _lstCategory;
            }
        }

		private TemplateGroups _templates;
		public TemplateGroups Templates
		{
            get
            {
                if (_templates == null)
                    _templates = new TemplateGroups();
                if (_templates.Count == 0)
                    _templates.AddDefaultItem();
                return _templates;
            }
			set { _templates = value; }
		}

        public void Clear()
        {
            _rootSign.Dispose();
            _templates.Dispose();
            _libraryGroups.Dispose();
            _sessionInfos.Dispose();
            _sources.Dispose();
            

            _rootSign = new SignGroupTree();
            _templates = new TemplateGroups();
            _libraryGroups = new LibraryGroups();
            _sessionInfos = new SessionInfos();
            _sources = new ListSet<DataItem>();
            _recents = new Recents();
        }
		public void AddDefaultItem()
		{
			if (_templates == null)
			{
				_templates = new TemplateGroups();
				_templates.AddDefaultItem();
			}
			if (_rootSign == null)
			{
				_rootSign = new SignGroupTree();
				//_rootSign.AddDefaultItem();
			}
			if (_libraryGroups == null)
			{
				_libraryGroups = new LibraryGroups();
				_libraryGroups.AddDefaultItem();
			}
            if (_sessionInfos == null)
            {
                _sessionInfos = new SessionInfos();
            }
            if (_sources == null)
            {
                _sources = new ListSet<DataItem>();
            }
            if (_recents == null)
            {
                _recents = new Recents();
            }
            if(_lstCategory == null)
                _lstCategory = new List<LiveCategory>();
		}

		[OnDeserialized]
		private void Deserialized(StreamingContext ctx)
		{
			AddDefaultItem();
		}


		public bool HasChanges
		{
			get
			{
				return RootGroup.IsChanged;
			}
		}

		public void AcceptChanges()
		{
			RootGroup.AcceptChanges();
		}

        #region IDisposable Members

        public void Dispose()
        {
            if (_sessionInfos != null)
            {
                _sessionInfos.Dispose();
                _sessionInfos = null;
            }
            if (_libraryGroups != null)
            {
                _libraryGroups.Dispose();
                _libraryGroups = null;
            }
            if (_rootSign != null)
            {
                _rootSign.Dispose();
                SignGroupTree._allSigns.Dispose();
                SignGroupTree._allSigns.Clear();
                SignGroupTree._allSigns = null;
                SignGroupTree._allGroups.Dispose();
                SignGroupTree._allGroups.Clear();
                SignGroupTree._allGroups = null;
            }
            if (_sources != null)
            {
                _sources.Clear();
                _sources = null;
            }

        }

        #endregion
    }
}