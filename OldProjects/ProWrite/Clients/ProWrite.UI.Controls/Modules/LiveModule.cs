using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Text;
using System.Windows.Forms;
using ProWrite.UI.Controls;
using ProWrite.UI.Controls.Common;
using ProWrite.UI.Controls.Library;
using ProWrite.Entity.Library;
using ProWrite.Core;
using ProWrite.Resources;
using ProWrite.Entity.Dashboard;
using ProWrite.UFE;
using ProWrite.UI.Controls.Common.Messages;
using ProWrite.UI.Controls.Live.Sessions;
using DevExpress.XtraTab;
using ProWrite.Entity.Live;
using ProWrite.UI.Controls.Actions.UFE.Requests;

namespace ProWrite.UI.Controls.Modules
{
    [PWModule(ModuleNames.Live)]
    public partial class LiveModule : ModuleControl
    {
        //private LiveTabControl TabControl;
        //private UFE.Live1.LibraryTree Tree;

        public LiveModule()
        {
            InitializeComponent();

            //Tree = new ProWrite.UI.Controls.UFE.Live1.LibraryTree();
            //RegisterDockPanel(dockPanelLibrary, Tree, Docks.UfeLibrary);
            Actions[MenuCommands.SessionSetup] = SessionSetup;
            Actions[MenuCommands.Sync] = SessionSync;
            InitTabControl();
        }

        /// <summary>
        /// 初始化Livemodule主界面的Tabcontrol
        /// </summary>
        public void InitTabControl()
        {
            tabCategories.TabPages.Clear();
            int count = DataGate.SessionInfos.Count;

            foreach (LiveCategory item in DataGate.SessionInfos[2].SessionCategories)
            {
                XtraTabPage tabPage = new XtraTabPage();
                tabPage.Text = item.Name;


                CategoriesControl categoriesControl = new CategoriesControl();
                item.CheckedState = true;
                categoriesControl.AddRemoveCategory(item);
                categoriesControl.Dock = DockStyle.Fill;
                categoriesControl.IsMainForm = true;
                tabPage.Controls.Add(categoriesControl);

                tabCategories.TabPages.Add(tabPage);

            }

            if (tabCategories.TabPages.Count > 0)
                tabCategories.SelectedTabPage = tabCategories.TabPages[0];
        }

        private void SessionSetup()
        {
            SessionSetupForm frm = null;

            try
            {
                frm = new SessionSetupForm();
                if (frm.ShowModalDialog() == DialogResult.OK)
                {
                    InitTabControl();
                }
            }
            finally
            {
                if (frm != null)
                    frm.Dispose();
            }
        }

        private void SessionSync()
        {
            LiveSessionUploadAction action = new LiveSessionUploadAction(ControlService.SignCombo.Current,SessionInfo.Current);
            action.Perform();
        }

        public override void ModuleShown(params object[] args)
        {
            if (args != null && args[0] is bool)
            {
                bool flag = (bool)args[0];
                if (flag)
                {
                    //ControlService.LiveTree = Tree; 
                    //TabControl.AddPage();
                }
            }
            base.ModuleShown(args);
        }


        protected override void ModuleClosed()
        {
            base.ModuleClosed();
        }

        protected override void InitModule()
        {
            base.InitModule();

            //TabControl = new LiveTabControl();
            //TabControl.Dock = DockStyle.Fill;
            //Controls.Add(TabControl);



        }

        /// <summary>
        /// Module Name
        /// </summary>
        public override string ModuleName
        {
            get { return ModuleNames.Live; }
        }

        public override Dictionary<Docks, string> DockMap
        {
            get
            {
                return ProWrite.UI.Controls.DockMap.Live;
            }
        }

        protected override DevExpress.XtraBars.Docking.DockManager DockManager
        {
            get
            {
                return this.dockManager1;
            }
        }
    }
}
