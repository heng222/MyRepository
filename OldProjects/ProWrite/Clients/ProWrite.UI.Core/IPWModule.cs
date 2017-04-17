//---------------------------------------------------------------------
//
// File: IPWModule.cs
//
// Description:
// Module Interface
//
// Author: Kevin
//
// Copyright (C) 2008 by Trans-Lux All rights reserved.
// 
//---------------------------------------------------------------------
using System;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;
using System.Reflection;
using log4net;
using System.Xml.Serialization;
using System.Xml;
using System.IO;
using System.Configuration;
using System.Communication;
using ProWrite.Core;

namespace ProWrite.UI.Controls.Common
{
	/// <summary>
	/// Module Interface
	/// </summary>
	public interface IPWModule
	{
		/// <summary>
		/// Initialize module
		/// </summary>
		void InitModule(params object[] args);
		/// <summary>
		/// Get or set  whether the module has been initialized 
		/// </summary>
		bool IsInitialized { get; set;}
        void ModuleShowing(params object[] args);
		/// <summary>
		/// Display Module
		/// </summary>
		void ModuleShown(params object[] args);
		/// <summary>
		/// Hide Module
		/// </summary>
		void ModuleClosed(params object[] args);
        void AddSaveItem(ISaveAllController ctx,List<string> emptyLibrary);
		/// <summary>
		/// The module is or not on the screen
		/// </summary>
		bool IsOnScreen { get;set;}
		/// <summary>
		/// It judge whether the application run on background
		/// </summary>
		bool IsBackgroud { get;}
		/// <summary>
		/// Module Name
		/// </summary>
		string ModuleName { get;}
		/// <summary>
		/// Return corresponding control of the module 
		/// </summary>
		/// <returns></returns>
		Control GetControl();

        void LoadLayout();
        void SaveLayout();
	}

    [Serializable]
    [XmlType(Namespace = ProjectProfile.Namespace)]
    [XmlRoot("ProjectProfile", Namespace = ProjectProfile.Namespace, IsNullable = false)]
    public partial class ProjectProfile
    {
        public const string Namespace = "http://schemas.microsoft.com/ProjectProfile/1.0";
        [XmlElement("Module")]
        public ModuleInfo[] Modules;
        [XmlAttribute]
        public string DefaultModule;
        [XmlAttribute]
        public string LoginForm;
        [XmlAttribute]
        public string MainForm;
        [XmlAttribute]
        public string ImportExportFactory;

    }

    [AttributeUsage(AttributeTargets.Class)]
    public class PWModuleAttribute:Attribute
    {
        public PWModuleAttribute(string name)
        {
            Name = name;
        }
        public string Name { get; private set; }
        public bool IsDefault { get; set; }
    }

	[Serializable]
    [XmlType(Namespace = ProjectProfile.Namespace)]
	public class ModuleInfo
	{
        public ModuleInfo()
        {
        }

        [XmlAttribute(AttributeName="Name")]
        public string ModuleName { get; set; }
        [XmlAttribute(AttributeName = "Type")]
        public string ClassName { get; set; }
        [XmlIgnore]
        public Type ModuleType { get; set; }

		private IPWModule _module;

        [XmlIgnore]
        public object[] Args { get; set; }

		public IPWModule Module
		{
			get
			{
				if (_module != null)
					return _module;

				if (ModuleType == null)
					PopulateModuleType();

				if (ModuleType == null)
					return null;

				try
				{
					_module = Activator.CreateInstance(ModuleType) as IPWModule;
				}
				catch (Exception ex)
				{
					Log.Error(string.Format("Create Module:[{0}] fail.", typeof(IPWModule).FullName), ex);
				}

				return _module;
			}
		}
        
		private void PopulateModuleType()
		{
			
			try
			{

                Type tmpType = TypeParseHelper.Parse(ClassName);
				if (tmpType == null || !tmpType.IsClass)
				{
					Log.Error("Module type is not null.");
					return;
				}

				Type moduleInterfaceType = typeof(IPWModule);
				if (tmpType.GetInterface(moduleInterfaceType.Name) == null)
				{
					Log.ErrorFormat("Module type must be implement interface [{0}].", moduleInterfaceType.FullName);
				}
				else
				{
					ModuleType = tmpType;   
				}
			}
			catch (Exception ex)
			{
				Log.Error(string.Format("Null module Type for {0}", ClassName), ex);
			}
		}

		public bool IsEmpty
		{
			get
			{
				return ModuleType == null;
			}
		}
	}

    public class ProjectProfileParser
    {
        
        public static ProjectProfile Parse()
        {            
            ProjectProfile profile = new ProjectProfile();
            profile.DefaultModule = ModuleNames.Dashboard;
            ServiceManager.Add<ProjectProfile>(profile);
            return profile;
            //string profile = ConfigurationManager.AppSettings["ProjectProfile"];
            //if (string.IsNullOrEmpty(profile))
            //{
            //    throw new Exception("ProjectProfile.xml does not exists!");
            //}
            //else
            //    profile = Constance.AppPath + profile;
            //string xml = null;
            //try
            //{
            //    xml = File.ReadAllText(profile);
            //    var o = XmlValidationHelper.DeserializeXml<ProjectProfile>(xml, "ProWrite.UI.Controls.ProjectProfile.xsd", ProjectProfile.Namespace);
            //    ServiceManager.Add<ProjectProfile>(o);
            //    return o;
            //}
            //catch (Exception ex)
            //{
            //    Log.Error(ex.Message, ex);
            //    return null;
            //}
        }
    }

    internal static class XmlValidationHelper
    {
        public static TRootElement DeserializeXml<TRootElement>(string xml, string xsdResourceName, string schemaUri)
        {
            XmlSerializer serializer = new XmlSerializer(typeof(TRootElement));

            using (XmlReader reader = GetValidatingReader(xml, xsdResourceName, schemaUri))
                return (TRootElement)serializer.Deserialize(reader);
        }

        public static XmlReader GetValidatingReader(string xml, string xsdResourceName, string schemaUri)
        {
            Stream stream = Assembly.GetExecutingAssembly().GetManifestResourceStream(xsdResourceName);
            XmlTextReader schemaReader = new XmlTextReader(stream);
            stream.Dispose();

            XmlReaderSettings settings = new XmlReaderSettings();
            settings.Schemas.Add(schemaUri, schemaReader);
            StringReader xmlStringReader = new StringReader(xml);
            XmlReader catalogReader = XmlReader.Create(xmlStringReader, settings);

            return catalogReader;
        }
    }

    internal static class TypeParseHelper
    {
        public static Type Parse(string typeName)
        {
            if (string.IsNullOrEmpty(typeName))
            {
                Log.Error(string.Format("Null Type for {0}", typeName));
                return null;
            }

            try
            {
                var arr = typeName.Split(',');
                var a = Assembly.Load(arr[1]);
                return a.GetType(arr[0]);
            }
            catch (Exception ex)
            {
                Log.Error(string.Format("Null Type for {0}", typeName), ex);
                return null;
            }
        }
    }

	/// <summary>
	/// Module name constance
	/// </summary>
	public class ModuleNames
	{
		public const string Dashboard = "Dashboard";
		public const string Editor = "Editor";
		public const string Playlists = "Playlists";
		public const string Scheduler = "Scheduler";
		public const string Live = "Live";
		public const string Manager = "Manager";
        public const string MLPlaylist = "MLPlaylist";
	}
}