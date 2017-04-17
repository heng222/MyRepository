//---------------------------------------------------------------------
//
// File: LibraryDialog.cs
//      
// Description:
//      LibraryDialog class
//
// Author: 
//
// Modify History:
//      Jerry Xu 2009-3-20 Update event:btnOK_Click(object sender, EventArgs e)
//      Jerry Xu 2009-3-25 Update event:btnOK_Click(object sender, EventArgs e)
//      Jerry Xu 2009-4-8  Update event:btnOK_Click(object sender, EventArgs e)
//      Jerry Xu 2009-6-16 Update method:Init(MenuCommands? cmd, LibraryType type)
//                         Add event:tree_MouseDown(object sender, MouseEventArgs e)
//      Jerry Xu 2009-6-19 Update method:Init(MenuCommands? cmd, LibraryType type)
//
//
// Copyright (C) 2008 by Trans-Lux All rights reserved.
// 
//---------------------------------------------------------------------

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using ProWrite.Core;
using ProWrite.Entity.Library;
using DevExpress.XtraEditors;
using ProWrite.UI.Controls.Common;
using ProWrite.UI.Controls.Common.Messages;
using ProWrite.Resources;
using DevExpress.XtraTreeList;
using DevExpress.XtraTreeList.Nodes;
using DevExpress.XtraTreeList.Columns;

namespace ProWrite.UI.Controls.Library
{
    public partial class LibraryDialog : XtraForm
    {
        private LibraryTreeControl tree;
        LibraryTreeControl.CheckedEditOptions checkedOption;
        private bool isOpenLibrary;

        //Open library
        public LibraryDialog(LibraryType type)
        {
            InitializeComponent();
            Init(null, type);
        }

        //Insert library
        public LibraryDialog(MenuCommands cmd, LibraryType type)
        {
            InitializeComponent();
            Init(cmd, type);
        }

        private void Init(MenuCommands? cmd, LibraryType type)
        {
            isOpenLibrary = !cmd.HasValue;
            if(isOpenLibrary)
                tree = new LibraryTreeControl();
            else
                tree = new LibraryTreeControl(false);
            tree.Dock = DockStyle.Fill;
            tree.Size = new Size(292, 411);
            tree.ContextMenuStrip = null;

            tree.OptionsSelection.MultiSelect = !isOpenLibrary;
            this.panelTreeContainer.Controls.Add(tree);

            checkedOption = !isOpenLibrary
                ? LibraryTreeControl.CheckedEditOptions.CheckBox
                : LibraryTreeControl.CheckedEditOptions.Radio;
            tree.ShowColumns(LibraryTreeControl.ColumnOptions.Name
                | LibraryTreeControl.ColumnOptions.Length
                | LibraryTreeControl.ColumnOptions.Checked
                , checkedOption);
            for (int i = 0; i < tree.Columns.Count; i++)
                tree.Columns[i].OptionsColumn.AllowSort = false;

            Text = isOpenLibrary ? "Open Library Dialog" : "Insert Library Dialog";
            tree.MoveFirst();

            btnOK.Click += new EventHandler(btnOK_Click);
            btnCancel.Click += new EventHandler(btnCancel_Click);

            if (isOpenLibrary)
            {
                tree.Type = type;
                var libraries = ModuleManager.CurrentModuleControl.GetProperty<List<MemoryLibraryItem>>("TabControl.OpenedModels");
                if (libraries != null && libraries.Count > 0)
                {
                    tree.HideNodes(libraries);
                }
                //tree.MouseDown += new MouseEventHandler(tree_MouseDown);
                return;
            }

            switch (cmd.Value)
            {
                case MenuCommands.Insert:
                    switch (type)
                    {
                        case LibraryType.Message:
                            tree.Type = LibraryType.Message;
                            break;
                        case LibraryType.Playlist:
                            tree.Type = LibraryType.Message | LibraryType.TimeSliceGroup | LibraryType.Playlist;
                            break;
                        case LibraryType.Schedule:
                            tree.Type = LibraryType.Message | LibraryType.TimeSliceGroup | LibraryType.Playlist;
                            break;
                    }
                    break;
                case MenuCommands.InsertMessage:
                    tree.Type = LibraryType.Message;
                    break;
                case MenuCommands.InsertPlaylist:
                    tree.Type = LibraryType.Playlist;
                    break;
                case MenuCommands.InsertTimeSlice:
                    tree.Type = LibraryType.TimeSliceGroup;
                    break;
            }
            if(checkedOption == LibraryTreeControl.CheckedEditOptions.CheckBox)
                tree.MouseDown += new MouseEventHandler(tree_MouseDown);
        }

        void tree_MouseDown(object sender, MouseEventArgs e)
        {
            tree.OnLibraryDialogMouseDown(sender,e);
        }        

        void btnCancel_Click(object sender, EventArgs e)
        {
            SelectedItems = null;
            DialogResult = DialogResult.Cancel;
            Close();
        }

        void btnOK_Click(object sender, EventArgs e)
        {
            SelectedItems = tree.SelectedItems;
            if (SelectedItems == null || SelectedItems.Length < 1)
            {
                MsgBox.Error("Please select library in the list.");
                return;
            }

            if (isOpenLibrary)
            {
                SelectedItems[0].IsOpen = true;
                bool canOpen = CommonHelper.IsShowOpenDialog(SelectedItems[0].Type);
                LocalMessageBus.Send(null, new MenuMessage(new MenuCommand[]{
                             new MenuCommand{ Command =  MenuCommands.Open,Enabled = canOpen}
                        }));
            }
            
            DialogResult = DialogResult.OK;
            Close();
        }        

        public MemoryLibraryItem[] SelectedItems { get; private set; }

    }
}
