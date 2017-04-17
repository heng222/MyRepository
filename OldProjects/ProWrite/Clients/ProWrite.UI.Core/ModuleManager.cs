//---------------------------------------------------------------------
//
// File: ModuleManager.cs
//
// Description:
// Module manager, register and display module
//
// Author: Kevin
//
// Modify histories:
//      Jerry Xu 2009-5-12 Update method:LoadModule(string moduleName, object[] args, IPWModule module)
//
// Copyright (C) 2008 by Trans-Lux All rights reserved.
// 
//---------------------------------------------------------------------
using System;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;
using log4net;
using ProWrite.Core;
using ProWrite.UI.Controls.Common;

namespace ProWrite.UI.Controls
{
    /// <summary>
    /// Module Manager, Register and display modules
    /// </summary>
    public class ModuleManager
    {
        /// <summary>
        /// Show module delegate
        /// </summary>
        /// <param name="moduleName"></param>
        public delegate void ShowModuleDelegate(string moduleName,params object[] args);

        private static Dictionary<string, Control> _controls;
        private static Dictionary<string, IPWModule> _modules;
        private static Dictionary<string, ModuleInfo> _moduleInfos;
        private static Control _controlPanel;

        private static IPWModule _currentModuleControl;
        private static readonly ILog _log = LogManager.GetLogger("ProWrite");

        private ModuleManager() { }

        static ModuleManager() 
        {
            _controls = new Dictionary<string, Control>();
            _modules = new Dictionary<string, IPWModule>();
            _moduleInfos = new Dictionary<string, ModuleInfo>();
            _controlPanel = new Panel();
            _controlPanel.Dock = DockStyle.Fill;
        }

        public static ShowModuleDelegate ShowModule;

        /// <summary>
        /// Get current displayed module name
        /// </summary>
        public static string CurrentModuleName
        {
            get
            {
                if (_currentModuleControl != null)
                    return _currentModuleControl.ModuleName;
                return null;
            }
        }       


        public static IPWModule CurrentModuleControl
        {
            get { return _currentModuleControl; }
        }

        public static IPWModule[] Items
        {
            get
            {
                IPWModule[] items = new IPWModule[_modules.Count];
                _modules.Values.CopyTo(items, 0);
                return items;
            }
        }

        /// <summary>
        /// According to the name to display the corresponding module
        /// </summary>
        /// <param name="moduleName"></param>
        public static void DisplayModule(string moduleName,params object[] args)
        {
            if (ShowModule != null)
                ShowModule(moduleName, args);
        }

        public static void LoadModule(string moduleName, object[] args)
        {
            try
            {
                IPWModule targetModule = null;
                _modules.TryGetValue(moduleName, out targetModule);


                if (_currentModuleControl != null)
                {
                    if (targetModule != _currentModuleControl)
                    {
                        _currentModuleControl.IsOnScreen = false;
                        _currentModuleControl.ModuleClosed();
                        _controlPanel.Controls.Clear();
                    }
                }

                if (targetModule != null)
                {
                    LoadModule(moduleName, args, targetModule);
                }
                else if (_moduleInfos.ContainsKey(moduleName))
                {
                    ModuleInfo info = _moduleInfos[moduleName];
                    IPWModule module = info.Module;
                    Register(module, info.Args);
                    LoadModule(moduleName, args, module);
                    _moduleInfos.Remove(moduleName);
                }
                else
                    _log.ErrorFormat("Invalid module:[{0}]", moduleName);
            }
            catch (Exception ex)
            {
                _log.Error("Module :[" + moduleName + "] show fail.", ex);
            }

        }

        private static void LoadModule(string moduleName, object[] args, IPWModule module)
        {
            if (_currentModuleControl != module)
            {
                _currentModuleControl = module;
                module.IsOnScreen = true;
                module.ModuleShowing(args);
                
            }

            if (_controls.ContainsKey(moduleName))
            {
                var moduleCtrl = module as Control;
                _controlPanel.Controls.Add(moduleCtrl);
                _controls[moduleName].Dock = DockStyle.Fill;
            }

            module.ModuleShown(args);
            
        }

        public static void DisplayModule(string moduleName)
        {
            DisplayModule(moduleName, null);
        }

        /// <summary>
        /// According to the Module type, dynamic regiser the module 
        /// </summary>
        /// <param name="moduleType"></param>
        public static void Register(string moduleName,Type moduleType, params object[] args)
        {
            if(string.IsNullOrEmpty(moduleName))
            {
                _log.Error(string.Format("Null module name."));
                return;
            }

            if (_moduleInfos.ContainsKey(moduleName) || _modules.ContainsKey(moduleName))
            {
                _log.WarnFormat("Could not add [{0}] to the registered list. Repeat entry in modules?", moduleName);
                return; 
            }

            if (moduleType == null || !moduleType.IsClass)
            {
                _log.Error("Module type is not null.");
                return;
            }

            Type moduleInterfaceType = typeof(IPWModule);
            if (moduleType.GetInterface(moduleInterfaceType.Name) == null)
            {
                _log.ErrorFormat("Module type must be implement interface [{0}].", moduleInterfaceType.FullName);
            }

            ModuleInfo m = new ModuleInfo();
            m.ModuleType = moduleType;
            m.ModuleName = moduleName;
            m.Args = args;

            _moduleInfos[moduleName] = m;
        }

        public static void Register(string moduleName, Type moduleType)
        {
            Register(moduleName, moduleType, null);
        }

        /// <summary>
        /// Resgiser appointed module
        /// </summary>
        /// <param name="module"></param>
        public static void Register(IPWModule module,params object[] args)
        {

            if (module == null)
            {
                _log.Error("Module is not null.");
                return;
            }

            if (_modules.ContainsKey(module.ModuleName))
            {
                _log.WarnFormat("Could not add [{0}] to the registered list. Repeat entry in modules?", module.ModuleName);
                return; 
            }

            _modules.Add(module.ModuleName, module);
            _log.InfoFormat("Registered module:[{0},{1}]", module.ModuleName, module.GetType().FullName);

            try
            {
                InitModule(module);
            }
            catch (Exception ex)
            {
                _log.Error("Module :[" + module.ModuleName + "] initialize fail.", ex);
            }
        }

        private static void InitModule(IPWModule module)
        {
            module.InitModule();
            module.IsInitialized = true;

            if (!module.IsBackgroud)
            {
                Control control = module.GetControl();
                if (control != null)
                {
                    //moduleControl.Dock = DockStyle.Fill;
                    _controls.Add(module.ModuleName, control);
                }
            }
        }

        public static void Register(IPWModule module)
        {
            Register(module, null);
        }

        public static void Dispose()
        {
            

            ShowModule = null;
            _controlPanel.Dispose();
            _controls.Clear();
            _moduleInfos.Clear();
            _modules.Clear();
            _controlPanel = null;
            _controls = null;
            _moduleInfos = null;
            _modules = null;
        }

        public static ModuleManager Instance = new ModuleManager();
        public static implicit operator Control(ModuleManager moduleManager)
        {
            return _controlPanel;
        }



    }
}
