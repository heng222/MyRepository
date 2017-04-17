//---------------------------------------------------------------------
//
// File: LibraryTree.cs
//      
// Description:
//      Library tree class
//
// Author: Kevin 2008-7-28
//
// Modify History:
//      Jerry Xu 2009-1-14 Update method:LibraryTree()
//      Jerry Xu 2009-1-14 Add method:LibraryTree_Observers(object sender, LibraryGroupActionStateMessage msg)
//      Jerry Xu 2009-2-19 Update Event:OnLibraryGroupEvent(object sender, ButtonPressedEventArgs e),LibraryTree_Observers(object sender, LibraryGroupActionStateMessage msg)
//                         Update method:RemoveButtonStatus()
//      Jerry Xu 2009-3-17 Update event:LibraryTree_Observers(object sender, LibraryGroupActionStateMessage msg)
//      Jerry Xu 2009-3-18 Update method:Add(LibraryItem item)
//
// Copyright (C) 2008 by Trans-Lux All rights reserved.
// 
//---------------------------------------------------------------------
using System;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;
using DevExpress.XtraEditors.Controls;
using DevExpress.XtraTreeList;
using DevExpress.XtraTreeList.Nodes;

using ProWrite.Entity.Library;
using ProWrite.Resources;
using DevExpress.XtraEditors;
using ProWrite.Core;
using ProWrite.UI.Controls.Common;
using ProWrite.UI.Controls.Common.Messages;

namespace ProWrite.UI.Controls.Library
{
    /// <summary>
    /// Library tree class
    /// </summary>
    public class LibraryTree:UserControl
    {
        //private LibraryGroupCombo cmbLibraries;
        private ButtonEdit btnEdit;
        private LibraryTreeControl tvLibrary;
        LibraryGroupLookup lookUpLibraryGrp;
        private Panel topPanel;
        private bool buttonEditState = true;
        private bool buttonDeleteState = true;

        public LibraryTree()
        {
            if (!DesignMode)
                InitComponent();
            lookUpLibraryGrp.EditValueChanged += lookUpLibraryGrp_EditValueChanged;
            lookUpLibraryGrp.QueryPopUp += lookUpLibraryGrp_QueryPopUp;                       
            
            //Config library group control state message
            LocalMessageBus.Subject<LibraryGroupActionStateMessage>().Observers += new System.Communication.Messaging.ObserverHandler<LibraryGroupActionStateMessage>(LibraryTree_Observers);
        }

        /// <summary>
        /// Function: Config library group control state
        /// Author  : Jerry Xu
        /// Date    : 2009-1-14
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="msg">LibraryGroupActionStateMessage</param>
        void LibraryTree_Observers(object sender, LibraryGroupActionStateMessage msg)
        {
            //Config library group control state
            lookUpLibraryGrp.Enabled = msg.CanEdit;
            //Config library group edit buttons state
            //for (int i = 0; i < btnEdit.Properties.Buttons.Count;i++ )
            //{                
            //    btnEdit.Properties.Buttons[i].Enabled = msg.CanEdit;
            //}
            buttonEditState = msg.CanEdit;
            LocalMessageBus.Send(this, new MenuMessage(MenuCommands.NewLibraryGroup, buttonEditState));
            //Config library group remove button state
            if(lookUpLibraryGrp.Enabled)
                RemoveButtonStatus();
        }

        /// <summary>
        /// get library tree controller
        /// </summary>
		public LibraryTreeControl Controller
        {
            get { return tvLibrary; }
        }

        private void InitComponent()
        {
            
            lookUpLibraryGrp = new LibraryGroupLookup();
            
            btnEdit = new ButtonEdit();
            btnEdit.Anchor = AnchorStyles.Top | AnchorStyles.Right;
            btnEdit.Location = new Point(166, 3);
            btnEdit.Properties.Buttons.AddRange(new EditorButton[] {
                new EditorButton(ButtonPredefines.Ellipsis, "Rename"),
                new EditorButton(ButtonPredefines.Plus, "Add New"),
                new EditorButton(ButtonPredefines.Close, "Delete")});
            btnEdit.Properties.TextEditStyle = TextEditStyles.HideTextEditor;
            btnEdit.Size = new System.Drawing.Size(64, 21);
            btnEdit.TabIndex = 2;
            this.btnEdit.ButtonClick += new ButtonPressedEventHandler(OnLibraryGroupEvent);

            topPanel = new Panel();
            topPanel.Size = new Size(227, 23);
            topPanel.Dock = DockStyle.Top;
            topPanel.Controls.Add(btnEdit);
            topPanel.Controls.Add(lookUpLibraryGrp);

            tvLibrary = new LibraryTreeControl();
            tvLibrary.Dock = DockStyle.Fill;
            tvLibrary.Location = new Point(3, 27);
            tvLibrary.Size = new System.Drawing.Size(227, 280);
            tvLibrary.TabIndex = 1;

            Size = new Size(233, 310);
            AutoScaleDimensions = new SizeF(6F, 13F);
            AutoScaleMode = AutoScaleMode.Font;
            Dock = DockStyle.Fill;
            Controls.Add(tvLibrary);
            Controls.Add(topPanel);
            LoadGroup();
        }

        /// <summary>
        /// Function: Load LibraryTree(Group and tree:content,and relation)
        /// Author  : Jerry Xu
        /// Date    : 2008-12-24
        /// </summary>
        private void LoadGroup()
        {
            DataGate.AddLibraryGroup(lookUpLibraryGrp.EditValue as string);
            OnLibraryGroupChanged();
            tvLibrary.Populate();
        }

        private void lookUpLibraryGrp_EditValueChanged(object sender, EventArgs e)
        {
            LoadGroup();
        }

        private void lookUpLibraryGrp_QueryPopUp(object sender, CancelEventArgs e)
        {
            foreach (LookUpColumnInfo col in lookUpLibraryGrp.Properties.Columns)
            {
                if (col.Caption != "Name") col.Visible = false;
            }
        }


        /// <summary>
        /// Add new library group
        /// </summary>
        public bool AddLibraryGroup()
        {
            // get group name from Inputdialog
            string groupName = InputDialog.GetInputValue(Resource.GetString(Resource.Strings.EditLibraryGrpName));

            if (string.IsNullOrEmpty(groupName))
                return false;
            

            if (DataGate.Project.LibraryGroups.Contains(groupName))
            {
                MsgBox.Error(Resource.GetFormatString(Resource.Strings.NameAlreadyExist,"library"));
                return false;
            }

            if (DataGate.AddLibraryGroup(groupName))
            {
                RemoveButtonStatus();
                lookUpLibraryGrp.Populate(groupName);
                //tvLibrary = new LibraryTreeControl();
                tvLibrary.Populate();
                tvLibrary.SetCurrentGroupEvent();
                return true;
            }

            return false;
        }        


        /// <summary>
        /// Add new library group
        /// </summary>
        private bool UpdateLibraryGroup()
        {
            //get group name from Inputdialog
            string groupName = InputDialog.GetInputValue(Resource.GetString(Resource.Strings.AddNewLibraryGrpName),LibraryGroup.Current.Name);

            if (string.IsNullOrEmpty(groupName))
                return false;

            if (DataGate.Project.LibraryGroups.Contains(groupName))
            {
                MsgBox.Error(Resource.GetFormatString(Resource.Strings.NameAlreadyExist, "library"));
                return false;
            }

            LibraryGroup.Current.Name = groupName;
            lookUpLibraryGrp.Populate(groupName);
            tvLibrary.Populate();
            return true;
        }

        /// <summary>
        /// Add new library group
        /// </summary>
        private void RemoveLibraryGroup()
        {
            if (MsgBox.Confirm(Resource.GetString(Resources.Resource.Strings.ConfirmDeleteItem)) == DialogResult.Yes)
            {
                DataGate.Project.LibraryGroups.Remove(LibraryGroup.Current);

                lookUpLibraryGrp.Populate();
                tvLibrary.Populate();
            }

            RemoveButtonStatus();
        }

        private void RemoveButtonStatus()
        {
            if (DataGate.Project.LibraryGroups.Count < 2)
                buttonDeleteState = false;
            //btnEdit.Properties.Buttons[3].Enabled = false;
            else
                buttonDeleteState = true;
                //btnEdit.Properties.Buttons[3].Enabled = true;
        }

        public event EventHandler LibraryGroupChanged;

        private void OnLibraryGroupChanged()
        {
            //if (_currentGroup == null)
            //    return;
            if (LibraryGroupChanged != null)
                LibraryGroupChanged(this, null);
        }

        public bool Add(LibraryItem item)
        {
            bool flag = tvLibrary.Add(item);
            if (flag)
            {
                if (item.Type == LibraryType.TimeSliceGroup)
                    LibraryGroup.Current.TimeSliceGroups.Add(item);
                //DataGate.SetCurrentLibraryGroup(LibraryGroup.Current.Name);
            }
            LocalMessageBus.Send(this, new MenuMessage(MenuCommands.InsertMessage, LibraryGroup.Current.Messages.Count > 0));
            LocalMessageBus.Send(this, new MenuMessage(MenuCommands.InsertTimeSlice, LibraryGroup.Current.TimeSliceGroups.Count > 0));
            LocalMessageBus.Send(this, new MenuMessage(MenuCommands.InsertPlaylist, LibraryGroup.Current.Playlists.Count > 0));
            return flag;
        }

        public bool Update(LibraryItem item)
        {
            return tvLibrary.Update(item);
        }

        public bool Remove(LibraryItem item)
        {
            return tvLibrary.Remove(item);
        }        

        void OnLibraryGroupEvent(object sender, ButtonPressedEventArgs e)
        {            
            switch (e.Button.Kind)
            {
                case ButtonPredefines.Ellipsis: // Rename
                    if (buttonEditState && !LibraryGroup.Current.IsLock)
                        UpdateLibraryGroup();
                    else
                        MsgBox.Error(Resource.GetString(Resource.Strings.LibraryGroupEdit));
                    break;
                case ButtonPredefines.Plus: //Add new
                    if (buttonEditState && !LibraryGroup.Current.IsLock)
                        AddLibraryGroup();
                    else
                        MsgBox.Error(Resource.GetString(Resource.Strings.LibraryGroupEdit));
                    break;
                case ButtonPredefines.Close: //Remove

                    if (DataGate.Project.LibraryGroups.Count > 1 && !LibraryGroup.Current.IsLock)
                        RemoveLibraryGroup();
                    else
                        MsgBox.Error(Resource.GetString(Resource.Strings.LibraryGroupDelete));
                    break;
            }
        }

        protected override void Dispose(bool disposing)
        {
            LocalMessageBus.Subject<LibraryGroupActionStateMessage>().Observers -= new System.Communication.Messaging.ObserverHandler<LibraryGroupActionStateMessage>(LibraryTree_Observers);
        }
    }
}
