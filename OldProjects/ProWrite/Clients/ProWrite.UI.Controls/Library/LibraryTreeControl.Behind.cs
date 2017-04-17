//---------------------------------------------------------------------
//
// File: LibraryNode.cs
//      
// Description:
//      Library node class
//
// Author: Kevin 2008-7-28
//
// Modify History:
//      Jerry Xu 2008-12-29 Import message:File handle
//                          Update methods:AddFiles(List<FileItem> files, List<MessageFileItem> listFiles),Import(string fileName)
//                          Add new methods:UpdateFiles(MessageInfo message,List<FileItem> files),SetHandleID(ShapeBase shape, List<FileItem> files)
//      Jerry Xu 2009-1-5   Update method:SetHandleID(ShapeBase shape, List<FileItem> files)
//      Jerry Xu 2009-2-26  Update method:private void Import(string fileName)
//      Jerry Xu 2009-3-18  Update method:OnImport()
//      Jerry Xu 2009-4-20  Add methods:SetImportExportFilter(),UpdateFilesOther(List<MessageInfo> messages, List<FileItem> files)
//      Jerry Xu 2009-4-20  Update methods:OnImport(),Import(string fileName),ImportTimeSliceGroupRename(List<MessageFileItem> listFiles, List<MessageItem> listMessages, 
//                              TimeSliceGroupItem groupItem),OnExport(),SetRightMenuState()
//      Jerry Xu 2009-4-23  Update method:Import(string fileName),Export(string fileName),SetRightMenuState()
//      Jerry Xu 2009-4-28  Update method:SetRightMenuState()
//                          Add method:CheckIsExport()
//      Jerry Xu 2009-5-5   Up method:SetRightMenuState()
//      Jerry Xu 2009-6-16  Update method:InitComponent()
// Copyright (C) 2008 by Trans-Lux All rights reserved.
// 
//---------------------------------------------------------------------
using System;
using System.Collections.Generic;
using System.Text;
using DevExpress.XtraEditors.Repository;
using DevExpress.XtraTreeList;
using ProWrite.DES;
using ProWrite.Entity;
using ProWrite.Entity.Library;
using DevExpress.XtraTreeList.Nodes;
using DevExpress.Utils;
using ProWrite.Resources;
using System.Windows.Forms;
using DevExpress.XtraTreeList.Columns;
using ProWrite.UI.Controls.Editor;
using ProWrite.Entity.Library.Controller;
using ProWrite.Core;
using DevExpress.XtraEditors.Controls;
using DevExpress.XtraEditors;
using ProWrite.Entity.Library.ImportExport;
using System.IO;
using ProWrite.Entity.Shape;
using ProWrite.UI.Controls.Common;
using ProWrite.UI.Controls.Common.Messages;
using System.Drawing;

namespace ProWrite.UI.Controls.Library
{
    public partial class LibraryTreeControl
    {
        protected override TreeListNode CreateNode(int nodeID, TreeListNodes owner, object tag)
        {
            return new LibraryNode(nodeID, owner);
        }

        protected override void RaiseCellValueChanged(CellValueChangedEventArgs e)
        {
            LibraryNode node = e.Node as LibraryNode;
            if (e.Column == Columns[0])
            {
                node[e.Column] = e.Value;
                RefreshRowsInfo();
            }
            base.RaiseCellValueChanged(e);
        }
        protected override DevExpress.XtraEditors.Container.EditorContainerHelper CreateHelper()
        {
            return new LibraryTreeListContainerHelper(this);
        }

        private class LibraryTreeListContainerHelper : TreeListContainerHelper
        {
            public LibraryTreeListContainerHelper(TreeList owner) : base(owner) { }
            public override void ActivateEditor(DevExpress.XtraEditors.Repository.RepositoryItem ritem, DevExpress.XtraEditors.Container.UpdateEditorInfoArgs args)
            {
                args = new DevExpress.XtraEditors.Container.UpdateEditorInfoArgs(args.MakeReadOnly, args.Bounds, args.Appearance, Owner.FocusedNode.Tag, args.LookAndFeel, args.ErrorText);
                base.ActivateEditor(ritem, args);
            }
        }
        private class LibraryContextMenuStrip : ContextMenuStrip
        {
            LibraryTreeControl _target;
            ToolStripMenuItem _rename;
            ToolStripMenuItem _delete;
            ToolStripSeparator _separator;
            ToolStripMenuItem _import;
            ToolStripMenuItem _export;
            string _filter;
            LibraryType _importExportType;

            public LibraryContextMenuStrip(LibraryTreeControl target)
            {
                _target = target;

                _rename = new ToolStripMenuItem(Resource.GetString(Resource.Strings.LibraryTreeControlRightMenuRenameTitle));
                _rename.Image = Resource.GetImage(Resource.Images.Rename);
                Items.Add(_rename);
                _rename.Click += delegate
                {
                    bool flag = target.RenameLibraryItem();
                };
                _delete = new ToolStripMenuItem(Resource.GetString(Resource.Strings.LibraryTreeControlRightMenuDeleteTitle));
                _delete.Image = Resource.GetImage(Resource.Images.Delete);
                Items.Add(_delete);
                _delete.Click += delegate
                {
                    //target.RemoveLibraryItem();
                    target.RemoveLibraryItemNew();
                };

                _separator = new ToolStripSeparator();
                Items.Add(_separator);
                _import = new ToolStripMenuItem(Resource.GetString(Resource.Strings.LibraryTreeControlRightMenuImportTitle));
                _import.Image = Resource.GetImage(Resource.Images.Import16);
                Items.Add(_import);
                _import.Click += delegate
                {
                    OnImport();
                };

                _export = new ToolStripMenuItem(Resource.GetString(Resource.Strings.LibraryTreeControlRightMenuExportTitle));
                _export.Image = Resource.GetImage(Resource.Images.Export16);
                Items.Add(_export);
                _export.Click += delegate
                {
                    OnExport();
                };
#if DEBUG
                //Menu Item for generate upload video
                //add by Louis
                ToolStripMenuItem uploadVideo = new ToolStripMenuItem("Generate Upload Video");
                Items.Add(uploadVideo);
                uploadVideo.Click += delegate
                                         {
                                             IVideoGenerator _videoGenerator = new VideoGenerator();
                                             string fileName = "d:\\1.mpg";
                                             if (_videoGenerator.CreateVideo(_target.FocusedNode.Library as MessageInfo,
                                                                         fileName))
                                             //if (DESHelper.CreateVideo(_target.FocusedNode.Library as MessageInfo, fileName))
                                                 MessageBox.Show("successful!");
                                         };
#endif
            }

            private void OnImport1()
            {
                //string[] files = null;
                //using (OpenFileDialog dlg = new OpenFileDialog())
                //{
                //    dlg.Filter = "Message file(*.mes)|*.mes";
                //    dlg.Title = "Import message files";
                //    dlg.Multiselect = true;
                //    DialogResult result = dlg.ShowModalDialog();
                //    if (result == DialogResult.OK
                //        || result == DialogResult.Yes)
                //    {
                //        files = dlg.FileNames;
                //    }
                //}

                //if (files == null || files.Length < 1)
                //    return;
                //foreach (string file in files)
                //{
                //    List<FileItem> images;
                //    List<FileItem> videos;
                //    MessageInfo message;
                //    MessageWrapper item = MessageController.Load(file);
                //    if (item != null)
                //    {
                //        images = item.Images;
                //        videos = item.Videos;
                //        message = item.Message;

                //        //item.Name = DateTime.Now.Ticks.ToString();
                //    }
                //    //_target.Add(item);
                //}

            }

            private void SetImportExportFilter()
            {
                NodeType nodeType = _target.FocusedNode.NodeType;
                switch(nodeType)
                {
                    case NodeType.Message:
                    case NodeType.Messages:
                        _filter = Constance.FileFilter.ImportExportMessage;
                        break;
                    case NodeType.TimeSliceGroup:
                    case NodeType.TimeSliceGroups:
                        _filter = Constance.FileFilter.ImportExportTimeSliceGroup;
                        break;
                    case NodeType.Playlist:
                    case NodeType.Playlists:
                        _filter = Constance.FileFilter.ImportExportPlaylist;
                        break;
                    case NodeType.Scheduler:
                    case NodeType.Schedulers:
                        _filter = Constance.FileFilter.ImportExportSchedule;
                        break;
                
                }
                //_import.Enabled = _export.Enabled = (nodeType == NodeType.Message || nodeType == NodeType.TimeSliceGroup);
                //_import.Enabled = (nodeType == NodeType.Messages || nodeType == NodeType.TimeSliceGroups);
            }

            #region Import
            /// <summary>
            /// Mouse right menu:Import 
            /// </summary>
            public void OnImport()
            {
                string[] files = null;
                using (OpenFileDialog dlg = new OpenFileDialog())
                {

                    dlg.Filter = _filter; //Constance.FileFilter.ImportExport;
                    dlg.Title = "Import library files";
                    dlg.Multiselect = true;
                    DialogResult result = dlg.ShowModalDialog();
                    if (result == DialogResult.OK
                        || result == DialogResult.Yes)
                    {
                        files = dlg.FileNames;
                    }
                    else
                        return;              
                }

                if (files == null || files.Length < 1)
                    return;
                foreach (string file in files)
                {                    
                    Import(file);
                }
                LocalMessageBus.Send(this, new MenuMessage(MenuCommands.InsertMessage, LibraryGroup.Current.Messages.Count > 0));
                LocalMessageBus.Send(this, new MenuMessage(MenuCommands.InsertTimeSlice, LibraryGroup.Current.TimeSliceGroups.Count > 0));
                LocalMessageBus.Send(this, new MenuMessage(MenuCommands.InsertPlaylist, LibraryGroup.Current.Playlists.Count > 0));

            }

            /// <summary>
            /// Function: Import file
            /// </summary>
            /// <param name="fileName">string</param>
            private void Import(string fileName)
            {
                if (string.IsNullOrEmpty(fileName))
                    return;

                IImportExport import = new ImportExportFactory().Create(fileName);
                import.OnImport(fileName);                
            }            
            #endregion

            #region Export
            private void SetImportExportState()
            {
                if (_target == null || _target.FocusedNode == null || _target.FocusedNode.Library == null || _target.FocusedNode.Library.IsEmpty)
                {
                    _export.Enabled = false;
                    return;
                }

                NodeType nodeType = _target.FocusedNode.NodeType;

                _import.Enabled = _export.Enabled = (nodeType == NodeType.Message || nodeType == NodeType.TimeSliceGroup || nodeType == NodeType.Playlist);
                _import.Enabled = (nodeType == NodeType.Messages || nodeType == NodeType.TimeSliceGroups || nodeType == NodeType.Playlists);
            }
            private void OnExport()
            {
                //if (!CheckIsExport())                
                //    return;                

                using (SaveFileDialog dlg = new SaveFileDialog())
                {
                    dlg.Filter = _filter; //Constance.FileFilter.ImportExport;
                    dlg.Title = "Export library";

                    dlg.FileName = _target.FocusedNode.Library.Name;
                    DialogResult result = dlg.ShowModalDialog();
                    if (result == DialogResult.OK
                        || result == DialogResult.Yes)
                    {
                        Export(dlg.FileName);                        
                    }
                }
            }

            private void Export(string fileName)
            {
                if (string.IsNullOrEmpty(fileName) || _target.FocusedNode.Library==null)
                    return;

                IImportExport import = new ImportExportFactory().Create(fileName);
                import.OnExport(fileName, _target.FocusedNode.Library);                     
            }
            #endregion

            #region Other functions
            protected override void OnOpening(System.ComponentModel.CancelEventArgs e)
            {
                base.OnOpening(e);
                if (_target.FocusedNode == null)
                {
                    e.Cancel = true;
                    return;
                }

                SetRightMenuState();
                SetImportExportFilter();
            }

            private void SetRightMenuState()
            {
                _target.ContextMenuStrip.Visible = true;

                NodeType nodeType = _target.FocusedNode.NodeType;

                if (_target.FocusedNode.Library != null)
                {
                    _rename.Enabled = true;
                    _delete.Enabled = true;
                }
                else
                {
                    _rename.Enabled = false;
                    _delete.Enabled = false;
                }

                _import.Enabled = _export.Enabled = (nodeType == NodeType.Message || nodeType == NodeType.TimeSliceGroup || nodeType == NodeType.Playlist);
                _import.Enabled = (nodeType == NodeType.Messages || nodeType == NodeType.TimeSliceGroups || nodeType == NodeType.Playlists);

                //if (nodeType == NodeType.Videos
                //    || nodeType == NodeType.Images || nodeType == NodeType.Schedulers)
                //{
                //    if (_target.FocusedNode.ParentNode == null)
                //    {
                //        _import.Visible = _export.Visible = false;
                //        _rename.Visible = false;
                //        _delete.Visible = false;
                //        this.Visible = false;
                //    }
                //}

                if (_target == null || _target.FocusedNode == null || _target.FocusedNode.Library == null || _target.FocusedNode.Library.IsEmpty)
                {
                    _export.Enabled = false;
                    return;
                }

            }

            private void SetRightMenuState1()
            {
                _target.ContextMenuStrip.Visible = true;
                NodeType nodeType = _target.FocusedNode.NodeType;
                _import.Visible = _export.Visible = (nodeType == NodeType.Message || nodeType == NodeType.TimeSliceGroup);
                _import.Visible = (nodeType == NodeType.Messages || nodeType == NodeType.TimeSliceGroups);
                
                if (_target.FocusedNode.Library != null)
                {
                    _rename.Visible = true;
                    _delete.Visible = true;
                    _rename.Enabled = true;
                    _delete.Enabled = true;
                }
                else
                {
                    _rename.Enabled = false;
                    _delete.Enabled = false;
                    _rename.Visible = false;
                    _delete.Visible = false;
                }
                if (nodeType == NodeType.Videos
                    || nodeType == NodeType.Images || nodeType == NodeType.Playlists || nodeType == NodeType.Schedulers)
                {
                    if (_target.FocusedNode.ParentNode == null)
                    {
                        _import.Visible = _export.Visible = false;
                        _rename.Visible = false;
                        _delete.Visible = false;
                        this.Visible = false;
                    }
                }
            }
            #endregion
        }



        public class LibraryColorChangedEventArgs : EventArgs
        {
            public readonly string LibraryName;
            public readonly LibraryType LibraryTypeItem;
            public readonly int ColorId;

            public LibraryColorChangedEventArgs(string name, int colorId, LibraryType libraryType)
            {
                LibraryName = name;
                LibraryTypeItem = libraryType;
                ColorId = colorId;
            }
        }

        private TreeListColumn colorColumn;
        private TreeListColumn nameColumn;
        private TreeListColumn typeColumn;
        private TreeListColumn lengthColumn;
        private TreeListColumn activeColumn;

        [Flags]
        public enum ColumnOptions : byte
        {
            Name = 1,
            Type = 2,
            Length = 4,
            Color = 8,
            Checked = 16,
        }

        public enum CheckedEditOptions : byte
        {
            CheckBox = 1,
            Radio = 2,
        }

        public void ShowColumns(ColumnOptions options, CheckedEditOptions? checkedEditOptions)
        {
            nameColumn.Visible = (options & ColumnOptions.Name) == ColumnOptions.Name;
            typeColumn.Visible = (options & ColumnOptions.Type) == ColumnOptions.Type;
            lengthColumn.Visible = (options & ColumnOptions.Length) == ColumnOptions.Length;
            colorColumn.Visible = (options & ColumnOptions.Color) == ColumnOptions.Color;
            activeColumn.Visible = (options & ColumnOptions.Checked) == ColumnOptions.Checked;

            if (!checkedEditOptions.HasValue)
            {
                activeColumn.ColumnEdit = null;
            }
            else
            {
                //activeColumn.ColumnEdit = this.repositoryItemCheckEdit;

                if (checkedEditOptions.Value == CheckedEditOptions.CheckBox)
                {
                    repositoryItemCheckEdit.CheckStyle = CheckStyles.Standard;
                }
                else
                {
                    repositoryItemCheckEdit.CheckStyle = CheckStyles.Radio;
                    //repositoryItemCheckEdit.RadioGroupIndex = 1;
                    //repositoryItemCheckEdit.CheckStateChanged += repositoryItemCheckEdit_CheckStateChanged;
                }
                //repositoryItemCheckEdit.CheckStateChanged += repositoryItemCheckEdit_CheckStateChanged;
            }
        }

        //void repositoryItemCheckEdit_CheckStateChanged(object sender, EventArgs e)
        //{
        //    CheckEdit checkEdit = sender as CheckEdit;
        //    if (checkEdit != null)
        //    {
        //        if (checkEdit.Checked)
        //        {
        //            if (FocusedNode.Library == null)
        //            {
        //                checkEdit.Checked = false;
        //            }
        //            else
        //            {
        //                SetNodeUnChecked(_rootNodes[LibraryType.Message]);
        //                SetNodeUnChecked(_rootNodes[LibraryType.TimeSliceGroup]);
        //                SetNodeUnChecked(_rootNodes[LibraryType.Playlist]);
        //                SetNodeUnChecked(_rootNodes[LibraryType.Scheduler]);
        //            }
        //        }
        //    }
        //}

        private void SetNodeUnChecked(LibraryNode nodes)
        {
            if (!nodes.Visible)
                return;
            foreach (LibraryNode node in nodes.Nodes)
            {
                node.SetValue("Checked", node.Focused);
            }
        }

        public void HideNodes(List<MemoryLibraryItem> items)
        {
            if (items == null)
                return;
            var rootNode = _rootNodes[items[0].Type];
            foreach (LibraryNode node in rootNode.Nodes)
            {
                if (items.ContainsByName(node.Library.Name))
                    node.Visible = false;
            }
        }

        public MemoryLibraryItem[] SelectedItems
        {
            get
            {
                LibraryGroup group = LibraryGroup.Current;
                if (group == null)
                    return null;

                //comments out by louis
                //if (activeColumn.ColumnEdit == null)
                //    return null;



                List<MemoryLibraryItem> items = new List<MemoryLibraryItem>();

                PopulateNodes(items, _rootNodes[LibraryType.Message]);
                PopulateNodes(items, _rootNodes[LibraryType.TimeSliceGroup]);
                PopulateNodes(items, _rootNodes[LibraryType.Playlist]);
                PopulateNodes(items, _rootNodes[LibraryType.Schedule]);


                return items.ToArray();
            }
        }


        private void PopulateNodes(List<MemoryLibraryItem> items, LibraryNode nodes)
        {
            if (!nodes.Visible)
                return;

            object nodeValue = null;
            bool hasChecked = false;
            bool isSingleSelect = repositoryItemCheckEdit.CheckStyle == CheckStyles.Radio;

            foreach (LibraryNode node in nodes.Nodes)
            {
                nodeValue = node.GetValue("Checked");
                if (nodeValue != null)
                {
                    hasChecked = (bool)nodeValue;
                    if (hasChecked)
                    {
                        items.Add(node.Library as MemoryLibraryItem);
                        if (isSingleSelect)
                            break;
                    }
                }
            }
        }
        

        //public void OnMouseDown(object sender, MouseEventArgs e)
        //{
        //    TreeListNode treeNode = CalcHitInfo(new Point(e.X, e.Y)).Node;
        //    SetFocusedNode(treeNode);

        //    TreeListHitInfo hInfo = CalcHitInfo(new Point(e.X, e.Y));
        //    if (e.Button == MouseButtons.Left)
        //    {
        //        //When click the active column£¬change active state
        //        if (hInfo.HitInfoType == HitInfoType.Cell && hInfo.Column.Caption.ToLower() == "checked")
        //        {
        //            TreeListNode node = hInfo.Node;
        //            SetCheckedNode(treeNode as LibraryNode, node["Checked"]);
        //        }
        //        else
        //        {
        //            return;
        //        }
        //    }
        //}

        ///// <summary>
        ///// Function: Set current node state
        ///// Author  : Jerry Xu
        ///// Date    : 2008-7-13
        ///// </summary>
        ///// <param name="node">TreeListNode:message info</param>
        ///// <param name="check">bool</param>
        //private void SetCheckedNode(LibraryNode node, object check)
        //{
        //    tree.FocusedNode = node;
        //    tree.BeginUpdate();
        //    bool flag = (bool)check;
        //    node["Checked"] = !flag;
        //    tree.EndUpdate();

        //}

        private RepositoryItemColorEdit repositoryItemColorEdit = new RepositoryItemColorEdit();
        private RepositoryItemCheckEdit repositoryItemCheckEdit = new RepositoryItemCheckEdit();

        private void InitComponent()
        {
            repositoryItemColorEdit.ShowCustomColors = false;
            repositoryItemColorEdit.ShowSystemColors = false;
            RepositoryItems.Add(repositoryItemColorEdit);
            RepositoryItems.Add(repositoryItemCheckEdit);

            repositoryItemCheckEdit.AutoHeight = false;
            repositoryItemCheckEdit.NullStyle = StyleIndeterminate.Unchecked;

            nameColumn = Columns.AddField("Name");
            nameColumn.Visible = true;
            nameColumn.OptionsColumn.AllowEdit = false;
            typeColumn = Columns.AddField("Type");
            typeColumn.Visible = false;
            typeColumn.OptionsColumn.AllowEdit = false;
            lengthColumn = Columns.AddField("Length");
            lengthColumn.Visible = true;
            lengthColumn.OptionsColumn.AllowEdit = false;
            colorColumn = Columns.AddField("Color");
            colorColumn.Visible = false;
            colorColumn.OptionsColumn.AllowEdit = true;
            activeColumn = Columns.AddField("Checked");
            activeColumn.Visible = false;
            //if(ModuleManager.CurrentModuleName == 
            activeColumn.OptionsColumn.AllowEdit = true;


            Dock = DockStyle.Fill;
            //OptionsBehavior.AutoChangeParent = false;
            //OptionsBehavior.AutoNodeHeight = false;
            //OptionsBehavior.AutoSelectAllInEditor = false;
            //OptionsBehavior.CloseEditorOnLostFocus = false;
            //OptionsBehavior.Editable = true;
            //OptionsBehavior.ExpandNodeOnDrag = false;
            //OptionsBehavior.ImmediateEditor = false;
            //OptionsBehavior.KeepSelectedOnClick = false;
            //OptionsBehavior.MoveOnEdit = false;
            //OptionsBehavior.ResizeNodes = false;
            //OptionsBehavior.SmartMouseHover = false;
            OptionsView.ShowButtons = false;
            OptionsView.ShowColumns = true;
            OptionsView.ShowFocusedFrame = false;
            OptionsView.ShowHorzLines = false;
            OptionsView.ShowRoot = false;
            OptionsView.ShowVertLines = false;
            OptionsMenu.EnableColumnMenu = false;
            OptionsMenu.EnableFooterMenu = false;
            TreeLevelWidth = 12;

            ImageList imgList;
            imgList = new ImageList();
            imgList.Images.Add(Resource.GetImage(Resource.Images.Image16));
            imgList.Images.Add(Resource.GetImage(Resource.Images.Video16));
            imgList.Images.Add(Resource.GetImage(Resource.Images.MessageIcon16x16));
            imgList.Images.Add(Resource.GetImage(Resource.Images.InsertTimeSliceGroup16));
            imgList.Images.Add(Resource.GetImage(Resource.Images.PlaylistIcon16x16));
            imgList.Images.Add(Resource.GetImage(Resource.Images.SchedulerIcon16x16));
            SelectImageList = imgList;
            ContextMenuStrip = new LibraryContextMenuStrip(this);


        }


        private void InitComponent(bool isInsert)
        {
            repositoryItemColorEdit.ShowCustomColors = false;
            repositoryItemColorEdit.ShowSystemColors = false;
            RepositoryItems.Add(repositoryItemColorEdit);
            RepositoryItems.Add(repositoryItemCheckEdit);

            repositoryItemCheckEdit.AutoHeight = false;
            repositoryItemCheckEdit.NullStyle = StyleIndeterminate.Unchecked;

            nameColumn = Columns.AddField("Name");
            nameColumn.Visible = true;
            nameColumn.OptionsColumn.AllowEdit = false;
            typeColumn = Columns.AddField("Type");
            typeColumn.Visible = false;
            typeColumn.OptionsColumn.AllowEdit = false;
            lengthColumn = Columns.AddField("Length");
            lengthColumn.Visible = true;
            lengthColumn.OptionsColumn.AllowEdit = false;
            colorColumn = Columns.AddField("Color");
            colorColumn.Visible = false;
            colorColumn.OptionsColumn.AllowEdit = true;
            activeColumn = Columns.AddField("Checked");
            activeColumn.Visible = false;
            //if(ModuleManager.CurrentModuleName == 
            activeColumn.OptionsColumn.AllowEdit = isInsert;


            Dock = DockStyle.Fill;
            //OptionsBehavior.AutoChangeParent = false;
            //OptionsBehavior.AutoNodeHeight = false;
            //OptionsBehavior.AutoSelectAllInEditor = false;
            //OptionsBehavior.CloseEditorOnLostFocus = false;
            //OptionsBehavior.Editable = true;
            //OptionsBehavior.ExpandNodeOnDrag = false;
            //OptionsBehavior.ImmediateEditor = false;
            //OptionsBehavior.KeepSelectedOnClick = false;
            //OptionsBehavior.MoveOnEdit = false;
            //OptionsBehavior.ResizeNodes = false;
            //OptionsBehavior.SmartMouseHover = false;
            OptionsView.ShowButtons = false;
            OptionsView.ShowColumns = true;
            OptionsView.ShowFocusedFrame = false;
            OptionsView.ShowHorzLines = false;
            OptionsView.ShowRoot = false;
            OptionsView.ShowVertLines = false;
            OptionsMenu.EnableColumnMenu = false;
            OptionsMenu.EnableFooterMenu = false;
            TreeLevelWidth = 12;

            ImageList imgList;
            imgList = new ImageList();
            imgList.Images.Add(Resource.GetImage(Resource.Images.Image16));
            imgList.Images.Add(Resource.GetImage(Resource.Images.Video16));
            imgList.Images.Add(Resource.GetImage(Resource.Images.MessageIcon16x16));
            imgList.Images.Add(Resource.GetImage(Resource.Images.InsertTimeSliceGroup16));
            imgList.Images.Add(Resource.GetImage(Resource.Images.PlaylistIcon16x16));
            imgList.Images.Add(Resource.GetImage(Resource.Images.SchedulerIcon16x16));
            SelectImageList = imgList;
            ContextMenuStrip = new LibraryContextMenuStrip(this);


        }
    }
}
