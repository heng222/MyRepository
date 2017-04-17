//---------------------------------------------------------------------
//
// File: TimeSliceGroupControl.cs
//
// Description:
// TimeSliceGroup Control 
//
// Author: Jerry Xu
//
// Date:2008-7-3 
//
//Modify History:
//      Jerry Xu 2008-7-8  Resource and Support Globalization
//      Jerry Xu 2008-7-13 Add the method:LoadGroup
//      Jerry Xu 2008-7-13 Add the method:IsExist
//      Jerry Xu 2008-7-13 Add the method:UpdateGroup
//      Jerry Xu 2008-7-13 Add drag drop message to the time slice group from library tree
//      Jerry Xu 2008-7-13 Add the function:edit a time slice group 
//      Jerry Xu 2008-7-13 Add the method:SetCheckedNode
//      Jerry Xu 2008-7-13 Add the event:tlGroup_GetStateImage,tlGroup_GiveFeedback
//      Jerry Xu 2008-7-14 Add the method:EditGroup
//      Jerry Xu 2008-7-15 Update MessageAdapterInfo
//      Jerry Xu 2008-7-16 Delete the property:TimeSliceGroupComboxCtrl
//      Jerry Xu 2008-7-16 Delete the method:IsExist
//      Jerry Xu 2008-7-16 Update method:ReLoadNodes,SetCheckedNode
//      Jerry Xu 2008-7-16 Update event:tlGroup_DragDrop,tlGroup_MouseDown
//      Jerry Xu 2008-7-16 Add the event:tlGroup_AfterDragNode
//      Jerry Xu 2008-7-16 Add the log
//      Jerry Xu 2008-7-17 Update the event: tlGroup_DragDrop,tlGroup_MouseDown
//      Jerry Xu 2008-7-17 Update method: ReLoadNodes,SetCheckedNode,LoadGroupItem
//      Jerry Xu 2008-7-21 Update method:
//      Jerry Xu 2008-7-22 Add event:OnLibraryGroupChanged
//      Jerry Xu 2008-7-23 Update event:tlGroup_DragDrop(MemoryLibraryItem->LibraryItem)
//      Jerry Xu 2008-7-23 Add event:deleteToolStripMenuItem_Click,setDefaultImagetoolStripMenuItem_Click,tlGroup_MouseUp,tlGroup_KeyUp
//      Jerry Xu 2008-7-23 Update event:tlGroup_MouseDown
//      Jerry Xu 2008-7-23 Add method:RemoveLibraryItem
//      Jerry Xu 2008-7-23 Add method:SetDefaultNailImage
//      Jerry Xu 2008-7-24 Delete IsEmpty in if
//      Jerry Xu 2008-7-25 Add method:SetDefaultGroup,InitDefaultGroup
//      Jerry Xu 2008-7-25 Update method:LoadGroup(Add set default group)
//      Jerry Xu 2008-7-25 Add variant define:LibraryGroup.Current,_defaultGroup,_defaultGroupName
//      Jerry Xu 2008-7-25 Add method:RemoveGroup
//      Jerry Xu 2008-7-25 Rename method:RemoveLibraryItem->RemoveMessage
//      Jerry Xu 2008-7-25 Update method:tlGroup_KeyUp(RemoveLibraryItem->RemoveMessage)
//           btneEdit_ButtonClick(Add reference:RemoveGroup)
//      Jerry Xu 2008-7-25 Add variant define:_currentLibraryTree
//      Jerry Xu 2008-8-12 Update event:tlGroup_DragDrop(TreeListNode->LibraryNode)
//      Jerry Xu 2009-2-25 Add method:EnableEditButtonState()
//      Jerry Xu 2009-3-13 Update event:tlGroup_DragDrop(object sender, DragEventArgs e),tlGroup_AfterDragNode(object sender, NodeEventArgs e)
//      Jerry Xu 2009-3-19 Update method:RemoveGroup()
//      Jerry Xu 2009-3-20 Add right menu:New Time Slice Group,Edit Time Slice Group
//      Jerry Xu 2009-3-20 Add event:tsmiNewTimeSliceGroup_Click(object sender, EventArgs e),tsmiEditTimeSliceGroup_Click(object sender, EventArgs e)
//      Jerry Xu 2009-3-20 Update method:EnableEditButtonState()
//      Jerry Xu 2009-3-26 Update method:EditGroup(string name)
//      Jerry Xu 2009-4-20 update method:Init()
//                         Add event:TimeSliceGroupControl_Observers(object sender, LibraryImportTimeSliceGroupMessage msg)
//                         Update event:tlGroup_DragDrop(object sender, DragEventArgs e)
//      Jerry Xu 2009-4-29 Update method:RemoveMessage(),RemoveGroup()
//                         Update event:tlGroup_DragDrop(object sender, DragEventArgs e)
//      Jerry Xu 2009-5-6  Add event:void Controller_RemoveLibraryItemEvent(object sender, RemoveLibraryEventArgs e)
//      Jerry Xu 2009-5-8  Update method:SetDefaultNailImage(),RemoveMessage()
//
// Copyright (C) 2008 by Trans-Lux All rights reserved.
// 
//---------------------------------------------------------------------

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Text;
using System.Windows.Forms;

using DevExpress.XtraEditors;
using DevExpress.XtraEditors.Controls;
using DevExpress.XtraTreeList.Nodes;
using DevExpress.XtraEditors.Repository;
using ProWrite.Entity.Library;
using ProWrite.Resources;
using DevExpress.XtraTreeList.Columns;
using DevExpress.XtraTreeList;
using ProWrite.Core;
using ProWrite.UI.Controls.Common;
using ProWrite.UI.Controls.Library;
using ProWrite.UI.Controls.Common.Messages;
using System.Communication.Messaging;

namespace ProWrite.UI.Controls.Playlist
{
    /// <summary>
    /// Time slice group control
    /// </summary>
    public partial class TimeSliceGroupControl : ControlBase
    {
        /// <summary>
        /// Image index
        /// </summary>
        private enum ImageIndex : byte
        {
            Message = 0,
            //TimeSliceGroup = 0,
            //Message = 1,
            //Playlist = 2
        }

        #region Variant define
        TreeListNode _node;
        //MessageInfo _message;
        MessageAdapterInfo _adpater;
        TimeSliceGroupInfo _currentGroup; //Selected TimeSliceGroupInfo
        private Point _pMouse;
        List<TreeListNode> _nodesList = new List<TreeListNode>(); //Drag source tree list nodes
        TreeListNode[] _nodes; //Drag source tree list nodes
        TreeListNode[] _tempNodes; //Drag destination tree list nodes
        TreeListNode _sourceNode; //Drag source node
        TreeListNode _destinationNode;//Drag Destination naode
        //LibraryGroup _currentLibraryGroup = LibraryGroup.Current; //Current library group
        TimeSliceGroupInfo _defaultGroup; //Per create a new library group info,create a default time slice group.
        private string _defaultGroupName; //Default time slice group name
        LibraryTree _currentLibraryTree = ControlService.LibraryTree;
        #endregion

        public TimeSliceGroupControl()
        {
            InitializeComponent();
            if (!DesignMode)
                Init();
            RegisterHelp();
        }

        private void RegisterHelp()
        {
            this.SetShowHelp(HelpNavigator.Topic, Resource.Helps.PlaylistsTimeSliceGroup);
        }

        #region Property define
        ///// <summary>
        ///// is active control
        ///// </summary>
        //public string GroupName
        //{
        //    get
        //    {
        //        return PlaylistControl.Current.TimeSliceGroupCtrl == this;
        //    }
        //}
        #endregion

        #region Function define
        #region Init
        /// <summary>
        /// Function:Init playlistsbar info
        /// Author: Jerry Xu
        /// Date:2008-5-14
        /// </summary>
        protected override void Init()
        {
            base.Init();
            InitializeResource();
            //InitDefaultGroup();
            LoadGroup();
            EnableEditButtonState();
            ControlService.LibraryTree.LibraryGroupChanged += new EventHandler(OnLibraryGroupChanged);
            tlGroup.ContextMenuStrip = contextMenuStrip1;
            Dock = DockStyle.Fill;
            LocalMessageBus.Subject<LibraryRenameMessage>().Observers += new ObserverHandler<LibraryRenameMessage>(OnLibraryRename);
            LocalMessageBus.Subject<LibraryImportTimeSliceGroupMessage>().Observers += new ObserverHandler<LibraryImportTimeSliceGroupMessage>(TimeSliceGroupControl_Observers);
            ControlService.LibraryTree.Controller.RemoveLibraryItemEvent += new EventHandler<RemoveLibraryEventArgs>(Controller_RemoveLibraryItemEvent);
        }

        void Controller_RemoveLibraryItemEvent(object sender, RemoveLibraryEventArgs e)
        {
            if (e.Type == LibraryType.TimeSliceGroup)
                LoadGroup();
            //throw new NotImplementedException();
        }

        void TimeSliceGroupControl_Observers(object sender, LibraryImportTimeSliceGroupMessage msg)
        {
            //
            LoadGroup();
        }

        public void EnableEditButtonState()
        {
            bool flag = cbeGroup.Properties.Items.Count > 0;
            btneEdit.Properties.Buttons[0].Enabled = btneEdit.Properties.Buttons[2].Enabled = tsmiEditTimeSliceGroup.Enabled = flag;
        }

        /// <summary>
        /// Function:Init default group
        /// Author: Jerry Xu
        /// Date:2008-7-25
        /// </summary>
        private void InitDefaultGroup()
        {
            _defaultGroup = new TimeSliceGroupInfo();
            _defaultGroup.Length = 8;
            _defaultGroup.Name = _defaultGroupName;
            _defaultGroup.IsRandom = false;
        }

        /// <summary>
        /// Function:Set default group
        /// Author: Jerry Xu
        /// Date:2008-7-25
        /// </summary>
        public void SetDefaultGroup()
        {            
            if (LibraryGroup.Current.TimeSliceGroups.Count == 0)
            {
                _currentGroup = _defaultGroup;
                _currentLibraryTree.Add(_currentGroup);

                cbeGroup.Properties.Items.Add(_currentGroup);
                //Set default selected item by index
                cbeGroup.SelectedIndex = 0;
            }
        }

        /// <summary>
        /// Function:Load group info
        /// Author: Jerry Xu
        /// Date:2008-7-13
        /// </summary>
        public void LoadGroup()
        {
            if(LibraryGroup.Current.TimeSliceGroups.Count>0)
            {
                if (_currentGroup!=null && LibraryGroup.Current.TimeSliceGroups.GetByName(_currentGroup.Name) != null)
                {
                    LoadGroup(_currentGroup.Name);
                    return;
                }
            }
             
            //SetDefaultGroup();
            
            //Clear items
             cbeGroup.Properties.Items.Clear();
            int count = LibraryGroup.Current.TimeSliceGroups.Count;
            if (count > 0)
            {
                //Init items
                for (int i = 0; i < count; i++)
                {
                    cbeGroup.Properties.Items.Add(LibraryGroup.Current.TimeSliceGroups[i]);
                }
                //Set default selected item by index
                cbeGroup.SelectedIndex = 0;
                _currentGroup = LibraryGroup.Current.TimeSliceGroups[0];
            }
            else
            {
                cbeGroup.Text = string.Empty;
                tlGroup.Nodes.Clear();
            }
        }

        /// <summary>
        /// Function:Load group info
        /// Author: Jerry Xu
        /// Date:2008-7-13
        /// </summary>
        public void LoadGroup(string groupName)
        {
            //SetDefaultGroup();

            //Clear items
            cbeGroup.Properties.Items.Clear();
            int count = LibraryGroup.Current.TimeSliceGroups.Count;
            if (count > 0)
            {
                //Init items
                for (int i = 0; i < count; i++)
                {                    
                    cbeGroup.Properties.Items.Add(LibraryGroup.Current.TimeSliceGroups[i]);
                    if (LibraryGroup.Current.TimeSliceGroups[i].Name == groupName)
                    {
                        cbeGroup.SelectedIndex = i;
                        _currentGroup = LibraryGroup.Current.TimeSliceGroups[i];                        
                    }
                }
                //Set default selected item by index
                if (string.IsNullOrEmpty(groupName))
                {
                    cbeGroup.SelectedIndex = 0;
                    _currentGroup = LibraryGroup.Current.TimeSliceGroups[0];
                }
            }
            else
            {
                cbeGroup.Text = string.Empty;
                tlGroup.Nodes.Clear();
            }
        }


        public void RefreshGroup()
        {
            LoadGroupItem(LibraryGroup.Current.TimeSliceGroups.GetByName(_currentGroup.Name));
        }
        
        /// <summary>
        /// Function:Load time slice group item info
        /// Author: Jerry Xu
        /// Date:2008-7-9
        /// </summary>
        /// <param name="pGroup">TimeSliceGroupInfo</param>
        public void LoadGroupItem(TimeSliceGroupInfo pGroup)
        {
            //Clear nodes
            tlGroup.Nodes.Clear();
            _nodesList.Clear();

            if (pGroup == null || pGroup.Items==null)
                return;
                

            //_nodes = new TreeListNode[pGroup.Items.Length];
            int i = 0;
            //Init nodes
            foreach (MessageAdapterInfo adapter in pGroup.Items)
            {
                //_message = LibraryGroup.Current.Messages.GetByName(adapter.MessageName);
                _nodesList.Add(tlGroup.AppendNode(adapter.ToArrayTimeSliceGroupItem(pGroup.Length), null, adapter));
                //_nodes[i] = tlGroup.AppendNode(DataGate.ToArrayTimeSliceGroupItem(pGroup.Length,adapter), null, adapter);
                i++;
            }
            this.Invalidate();
        }

        /// <summary>
        /// Function:Set GroupItemControl property
        /// Author: Jerry Xu
        /// Date:2008-7-9
        /// </summary>
        private void SetGroupItemControlProperty()
        {            
            //Active
            tlcIsActive.Caption = Resource.GetString(Resource.Strings.PlayListTimeSliceGroupControlGroupItemActiveTitle);

            //Name
            tlcName.Caption = Resource.GetString(Resource.Strings.PlayListTimeSliceGroupControlGroupItemNameTitle);
            
            //Type
            //tlcType.Caption = Resource.GetString(Resource.Strings.PlayListTimeSliceGroupControlGroupItemTypeTitle);
            
            //Length
            tlcLength.Caption = Resource.GetString(Resource.Strings.PlayListTimeSliceGroupControlGroupItemLengthTitle);

        }

        /// <summary>
        /// Function:Set GroupItemControl property
        /// Author: Jerry Xu
        /// Date:2008-7-9
        /// </summary>
        private void SetGroupItemControlProperty1()
        {
            TreeListColumn column;
            
            //Active
            column = new TreeListColumn();
            column.Name = "tlcIsActive";
            column.Caption = Resource.GetString(Resource.Strings.PlayListTimeSliceGroupControlGroupItemActiveTitle);
            column.ColumnEdit = this.ckEdit;
            column.FieldName = "IsActive";
            column.Visible = true;
            column.VisibleIndex = 0;
            column.Width = 70;

            //Name
            column = new TreeListColumn();
            column.Name = "tlcName";
            column.Caption = Resource.GetString(Resource.Strings.PlayListTimeSliceGroupControlGroupItemNameTitle);
            column.FieldName = "Name";            
            column.Visible = true;
            column.VisibleIndex = 1;
            column.Width = 69;
            
            //Type
            column = new TreeListColumn();
            column.Name = "tlcType";
            column.Caption = Resource.GetString(Resource.Strings.PlayListTimeSliceGroupControlGroupItemTypeTitle);
            column.FieldName = "Type";
            column.Visible = true;
            column.VisibleIndex = 2;
            column.Width = 69;
            
            //Length
            column = new TreeListColumn();
            column.Name = "tlcLength";
            column.Caption = Resource.GetString(Resource.Strings.PlayListTimeSliceGroupControlGroupItemLengthTitle);
            column.FieldName = "LENGTH";
            column.Visible = true;
            column.VisibleIndex = 3;
            column.Width = 69;

            //RepositoryItemCheckEdit ckEdit = new RepositoryItemCheckEdit();
        }
        #endregion

        #region Edit group
        /// <summary>
        /// Function:Edit a group info.
        /// Author  :Jerry Xu
        /// Date    :2008-7-14
        /// </summary>
        /// <param name="name"></param>
        public void EditGroup(string name)
        {
            //Show the edit form
            TimeSliceGroupEditForm group = new TimeSliceGroupEditForm(name);
            //group.GroupName = name;
            //if (this.ParentForm != null)
            //    this.ParentForm.TopMost = true;
            group.ShowModalDialog();
            //Refresh group info
            if (group.IsRefresh)
            {
                LoadGroup(group.GroupName);
                foreach (TreeListNode node in _nodesList)
                {
                    node[2] = Formaters.FormatTime(group.GroupLength);
                }
            }
        }
        #endregion

        #region Save time slice
        /// <summary>
        /// Function:Save time slice
        /// Author  :Jerry Xu
        /// Date    :2008-7-13
        /// </summary>
        private void Save()
        {
            try
            {
                if (_currentGroup != null)
                {
                    _currentGroup.Clear();
                    //bool flag = true;
                    foreach (TreeListNode node in tlGroup.Nodes)
                    {
                        _currentGroup.Add((MessageAdapterInfo)(node.Tag));
                    }
                    //Update group to library group
                    ControlService.LibraryTree.Update(_currentGroup.Copy() as TimeSliceGroupInfo);
                }
            }
            catch (Exception ex)
            {
                //MsgBox.Warning(Resource.GetString(Resource.Strings.SaveFailed));
                DataGate.Log.Error(Resource.GetString(Resource.Strings.SaveFailed), ex);
            }
        }
        #endregion


        #region ReLoad Nodes
        /// <summary>
        /// Function:ReLoad Nodes
        /// Author  :Jerry Xu
        /// Date    :2008-7-15
        /// </summary>
        /// <param name="sourceNode">Source Node:TreeListNode</param>
        /// <param name="destinationNode">Destination Node:TreeListNode</param>
        private void ReLoadNodes(TreeListNode sourceNode,TreeListNode destinationNode)
        {
            //Drag source node is null or destionation node is null, exit
            if (sourceNode == null || destinationNode == null)
                return;
            
            int sourceIndex = 0; //source node index;
            int destinationIndex = 0;//destination node index;
            _nodes = new TreeListNode[_nodesList.Count];
            _nodesList.CopyTo(_nodes, 0);
            for (int i = 0; i < _nodes.Length; i++)
            {
                if (_nodes[i] == sourceNode)
                    sourceIndex = i;
                if (_nodes[i] == destinationNode)
                    destinationIndex = i;                    
            }
            _tempNodes = new TreeListNode[_nodes.Length];
            //drag forward
            if (sourceIndex > destinationIndex)
            {
                for (int i = 0; i < _nodes.Length; i++)
                {
                    if (i < destinationIndex || i > sourceIndex)
                    {
                        _tempNodes[i] = _nodes[i];
                    }
                    if (i == sourceIndex)
                    {
                        _tempNodes[destinationIndex] = _nodes[i];
                    }
                    if (i >= destinationIndex && i < sourceIndex)
                    {
                        _tempNodes[i+1] = _nodes[i];

                    }
                }
            }
            else//Drag backward
            {
                for (int i = 0; i < _nodes.Length; i++)
                {
                    if (i < sourceIndex || i >= destinationIndex)
                    {
                        _tempNodes[i] = _nodes[i];
                    }
                    if (i == sourceIndex)
                    {
                        _tempNodes[destinationIndex-1] = _nodes[i];
                    }
                    if (i > sourceIndex && i < destinationIndex)
                    {
                        _tempNodes[i - 1] = _nodes[i];
                    }
                }
            }
            //Clear nodes
            tlGroup.Nodes.Clear();
            _nodesList.Clear();
            //Reload nodes
            for (int i = 0; i < _tempNodes.Length; i++)
            {
                _adpater = (MessageAdapterInfo)(_tempNodes[i].Tag);
                //_message = LibraryGroup.Current.Messages.GetByName(_adpater.MessageName);
                _nodesList.Add(tlGroup.AppendNode(_adpater.ToArrayTimeSliceGroupItem(_currentGroup.Length), -1, _adpater));
                //_nodes[i] = tlGroup.AppendNode(DataGate.ToArrayTimeSliceGroupItem(_currentGroup.Length ,_adpater), -1, _adpater);
            }
            //Clear source node and destination node
            _sourceNode = null;
            _destinationNode = null;
        }
        #endregion

        /// <summary>
        /// Function: Remove item from messages
        /// Author  ; Jerry Xu
        /// Date    : 2008-7-23 
        /// </summary>
        private void RemoveMessage()
        {
            //未考虑删除时，代理是否有效，删除后，Current未进行替换操作
            if (MsgBox.Confirm(Resource.GetString(Resources.Resource.Strings.ConfirmDeleteItem)) == DialogResult.Yes)
            {
                if (tlGroup.FocusedNode != null && tlGroup.FocusedNode.Tag != null)
                {
                    _nodes = new TreeListNode[_nodesList.Count];
                    _nodesList.CopyTo(_nodes,0);
                    if(_nodes.Length>1)
                    _tempNodes = new TreeListNode[_nodes.Length-1];
                    int t = 0;
                    for (int i = 0; i < _nodes.Length; i++)
                    {
                        if (_nodes[i] != tlGroup.FocusedNode)
                        {
                            _tempNodes[t++] = _nodes[i];
                        }
                    }
                    _nodes = _tempNodes;
                    _nodesList.Clear();
                    if(_nodes!=null && _nodes.Length>0)
                        _nodesList.AddRange(_nodes);
                    //LibraryGroup.Current.Messages.GetByName((tlGroup.FocusedNode.Tag as MessageAdapterInfo).Target.Name).IsLock = false;
                    MessageAdapterInfo adapter = tlGroup.FocusedNode.Tag as MessageAdapterInfo;
                    if (adapter.Id == _currentGroup.CurrentMessageAdapterID)
                    {
                        tlGroup.Nodes.Remove(tlGroup.FocusedNode);
                        if (tlGroup.Nodes.Count > 0)
                            tlGroup.FocusedNode = tlGroup.Nodes[0];
                        else
                            tlGroup.FocusedNode = null;
                        SetDefaultNailImage();
                    }
                    else if (adapter.Target.Id == _currentGroup.NailImageID)
                    {
                        tlGroup.Nodes.Remove(tlGroup.FocusedNode);
                        if (tlGroup.Nodes.Count > 0)
                            tlGroup.FocusedNode = tlGroup.Nodes[0];
                        else
                            tlGroup.FocusedNode = null;
                        SetDefaultNailImage(true);
                    }
                    else
                    {
                        tlGroup.Nodes.Remove(tlGroup.FocusedNode);

                    }
                }
            }
        }

        /// <summary>
        /// Function: Set default nail shape in time slice group
        /// Author  : Jerry Xu
        /// Date    : 2008-7-23
        /// </summary>
        private void SetDefaultNailImage(bool flag)
        {
            if (flag)
            {
                _node = tlGroup.FocusedNode;
                if (_node == null || _node.Tag == null || (_node.Tag as MessageAdapterInfo).Target == null)
                    _currentGroup.NailImageID = string.Empty;
                else
                {
                    _currentGroup.NailImageID = ((MessageAdapterInfo)(_node.Tag)).TargetId;
                }
            }
        }

        /// <summary>
        /// Function: Set default nail shape in time slice group
        /// Author  : Jerry Xu
        /// Date    : 2008-7-23
        /// </summary>
        private void SetDefaultNailImage()
        {
            _node = tlGroup.FocusedNode;
            if (_node == null || _node.Tag == null || (_node.Tag as MessageAdapterInfo).Target == null)
                _currentGroup.CurrentMessageAdapterID = string.Empty;
            else
            {
                _currentGroup.CurrentMessageAdapterID = ((MessageAdapterInfo)(_node.Tag)).Id;
                _currentGroup.NailImageID = ((MessageAdapterInfo)(_node.Tag)).TargetId;
            }
        }

        /// <summary>
        /// Function: Remove group from library group
        /// Author  ; Jerry Xu
        /// Date    : 2008-7-25 
        /// </summary>
        private void RemoveGroup()
        {
            string groupName = _currentGroup.Name;
            if (MsgBox.Confirm(Resource.GetString(Resources.Resource.Strings.ConfirmDeleteItem)) == DialogResult.Yes)
            {
                //if (_currentGroup.Items != null && _currentGroup.Items.Length > 0)
                //{
                //    foreach (MessageAdapterInfo item in _currentGroup.Items)
                //    {
                //        LibraryGroup.Current.Messages.GetByName(item.Target.Name).IsLock = false;
                //    }
                //}
                
                if (_currentLibraryTree.Remove(_currentGroup))
                {
                    //MsgBox.Warning(Resource.GetFormatString(Resource.Strings.LibraryTreeDeleteSuccess, new object[] { LibraryType.TimeSliceGroup.ToString().ToLower(), groupName }));
                    LoadGroup();
                }
                else
                {
                    //MsgBox.Error(Resource.GetString(Resource.Strings.DeleteFailed));
                    MsgBox.Error(Resource.GetFormatString(Resource.Strings.TimeSliceGroupDeleteFailed, new object[] { LibraryType.TimeSliceGroup.ToString(), groupName }));
                }
            }
            //else
            //    MsgBox.Warning(Resource.GetFormatString(Resource.Strings.TimeSliceGroupDeleteFailed, new object[] { LibraryType.TimeSliceGroup.ToString().ToLower(), groupName }));
        }

        /// <summary>
        /// Function: Set current node state
        /// Author  : Jerry Xu
        /// Date    : 2008-7-13
        /// </summary>
        /// <param name="node">TreeListNode:message info</param>
        /// <param name="check">bool</param>
        private void SetCheckedNode(TreeListNode node, bool check)
        {
            MessageAdapterInfo item = (MessageAdapterInfo)(node.Tag);
            tlGroup.FocusedNode = node;
            tlGroup.BeginUpdate();
            node["IsActive"] = check;
            item.IsActive = check;
            tlGroup.EndUpdate();
        }

        #region ISupportGlobalization
        /// <summary>
        /// Initialize resource information
        /// </summary>
        public override void InitializeResource()
        {
            //Init Resource
            //lcGroupTitle.Text = Resource.GetString(Resource.Strings.PlayListTimeSliceGroupControlLabelGroupTitle);
            //Init imagelist
            this.imageList1.TransparentColor = System.Drawing.Color.Magenta;
            imageList1.Images.Add(Resource.GetImage(Resource.Images.InsertMessage16));
            //Init button
            sbtnSave.Text = Resource.GetString(Resource.Strings.Save);
            sbtnSave.Image = Resource.GetImage(Resource.Images.Save16);
            //Set group item property
            SetGroupItemControlProperty();

            tsmiDelete.Text = Resource.GetString(Resource.Strings.Delete);
            tsmiDelete.Image = Resource.GetImage(Resource.Images.Delete16);

            setDefaultImagetoolStripMenuItem.Text = "Set Thumbnail Image";
            setDefaultImagetoolStripMenuItem.Image = Resource.GetImage(Resource.Images.GeneraleNailImage);

            btneEdit.Properties.Buttons[0].Enabled = false;
            btneEdit.Properties.Buttons[2].Enabled = false;
        }
        #endregion //ISupportGlobalization
        #endregion
        
        #region Event define

        private void cbeGroup_SelectedIndexChanged(object sender, EventArgs e)
        {
            try
            {
                _currentGroup = (TimeSliceGroupInfo)(LibraryGroup.Current.TimeSliceGroups[cbeGroup.SelectedIndex]);
                LoadGroupItem(_currentGroup);
            }
            catch(Exception ex)
            {
                DataGate.Log.Error(Resource.GetString(Resource.Strings.PlayListTimeSliceGroupControlLoadGroupInfoException), ex);
            }
        }

        private void btneEdit_ButtonClick(object sender, ButtonPressedEventArgs e)
        {
            try
            {
                if (ControlService.SignCombo.Current == null)
                {
                    MsgBox.Warning(ProWrite.Resources.Resource.GetString(ProWrite.Resources.Resource.Strings.AddNewSignFirst));
                    return;
                }
                switch (e.Button.Kind)
                {
                    case ButtonPredefines.Ellipsis: // Edit
                        EditGroup(LibraryGroup.Current.TimeSliceGroups[cbeGroup.SelectedIndex].Name);
                        break;
                        
                    case ButtonPredefines.Plus: //Add new
                        EditGroup(string.Empty);
                        EnableEditButtonState();
                        break;
                    case ButtonPredefines.Close: //Remove
                        RemoveGroup();
                        EnableEditButtonState();
                        break;
                }
            }
            catch (Exception ex)
            {                
                DataGate.Log.Error(Resource.GetString(Resource.Strings.PlayListTimeSliceGroupControlEditGroupInfoException),ex);
            }
        }

        private void tlGroup_DragEnter(object sender, DragEventArgs e)
        {
            e.Effect = DragDropEffects.Copy | DragDropEffects.Move| DragDropEffects.All;
        }


        void tlGroup_DragObjectStart(object sender, DevExpress.XtraTreeList.DragObjectStartEventArgs e)
        {
            e.Allow = false;
        }

        private void tlGroup_DragDrop(object sender, DragEventArgs e)
        {
            try
            {
                if (cbeGroup.Text == string.Empty || cbeGroup.Properties.Items.Count == 0)
                {
                    if(MsgBox.Confirm(Resource.GetString(Resource.Strings.PlayListTimeSliceGroupControlGroupItemCountEmpty),MessageBoxButtons.YesNo)== DialogResult.Yes)
                        EditGroup(string.Empty);    
                    return;
                }
                if (e.Data.GetDataPresent(typeof(LibraryNode)))
                {
                    _node = (LibraryNode)e.Data.GetData(typeof(LibraryNode));
                    //Is not message
                    if (_node.Tag == null || ((LibraryItem)(_node.Tag)) == null)
                        return;
                    if (((LibraryItem)(_node.Tag)).Type == LibraryType.Message)
                    {
                        _adpater = ((MessageInfo)(_node.Tag)).ToProxy() as MessageAdapterInfo;
                        //Message length is not equal the group length
                        if (_adpater.Target.Length == 0)
                        {
                            MsgBox.Error(Resource.GetString(Resource.Strings.PlayListMessageLengthIsZero));
                            return;
                        }
                        _adpater.TargetId = _adpater.Target.Id;
                        //LibraryGroup.Current.Messages.GetByName(((MessageInfo)(_node.Tag)).Name).IsLock = true;
                        TreeListNode node = tlGroup.AppendNode(_adpater.ToArrayTimeSliceGroupItem(_currentGroup.Length), -1, _adpater); 
                        _nodesList.Add(node);
                        if (_nodesList.Count == 1)
                        {
                            tlGroup.FocusedNode = node;
                            SetDefaultNailImage();
                        }

                        Save();
                    }
                }
                else
                {
                    if (e.Data.GetDataPresent("DevExpress.XtraTreeList.Nodes.TreeListNode", false))
                    {
                        _node = (TreeListNode)e.Data.GetData(typeof(TreeListNode));
                        TreeListHitInfo hInfo = tlGroup.CalcHitInfo(tlGroup.PointToClient(new Point(e.X, e.Y)));

                        _sourceNode = _node;
                        _destinationNode = hInfo.Node;
                        //Save();
                    }
                }
            }
            catch (Exception ex)
            {
                DataGate.Log.Error(Resource.GetString(Resource.Strings.PlayListTimeSliceGroupControlDragDropException),ex);
            }
        }

        private void sbtnSave_Click(object sender, EventArgs e)
        {
            Save();
        }

        private void tlGroup_MouseDown(object sender, MouseEventArgs e)
        {
            try
            {
                tlGroup.SetFocusedNode(tlGroup.CalcHitInfo(new Point(e.X, e.Y)).Node);

                if (tlGroup.FocusedNode != null && tlGroup.FocusedNode.Tag != null && (tlGroup.FocusedNode.Tag as MessageAdapterInfo).Target != null)
                {
                    ControlService.NailImageBox.Image = (tlGroup.FocusedNode.Tag as MessageAdapterInfo).Target.Image;
                    ControlService.RefreshPropertyGrid(tlGroup.FocusedNode.Tag);

                }

                _pMouse = new Point(e.X, e.Y);
                //Get node info by mouse point 
                TreeListHitInfo hInfo = tlGroup.CalcHitInfo(new Point(e.X, e.Y));
                if (e.Button == MouseButtons.Left)
                {
                    //When click the active column，change active state
                    if (hInfo.HitInfoType == HitInfoType.Cell && hInfo.Column.Caption == Resource.GetString(Resource.Strings.PlayListTimeSliceGroupControlGroupItemActiveTitle))
                    {
                        TreeListNode node = hInfo.Node;
                        MessageAdapterInfo item = (MessageAdapterInfo)(hInfo.Node.Tag);
                        SetCheckedNode(node, !item.IsActive);
                        Save();
                    }
                    else
                    {
                        return;
                    }
                }
            }
            catch (Exception ex)
            {
                DataGate.Log.Error(Resource.GetString(Resource.Strings.PlayListTimeSliceGroupControlConfigMessageActiveException), ex);
            }
        }

        private void tlGroup_GetStateImage(object sender, GetStateImageEventArgs e)
        {
            //if (e == null) throw new ArgumentNullException("e");                      
            //e.NodeImageIndex = (int)(ImageIndex.InsertMessage16);
        }

        private void tlGroup_GiveFeedback(object sender, GiveFeedbackEventArgs e)
        {
            e.UseDefaultCursors = false;
        }

        private void tlGroup_AfterDragNode(object sender, NodeEventArgs e)
        {
            //When source node and destination node is null,exit
            if (_sourceNode == null || _destinationNode == null)
                return;
            try
            {                
                //Reload nodes
                ReLoadNodes(_sourceNode, _destinationNode);
                Save();
            }
            catch (Exception ex)
            {
                DataGate.Log.Error(Resource.GetString(Resource.Strings.PlayListTimeSliceGroupControlReloadNodesException), ex);
            }
        }       

        private void OnLibraryGroupChanged(object sender, EventArgs e)
        {
            LoadGroup();           
        }

        private void deleteToolStripMenuItem_Click(object sender, EventArgs e)
        {
            RemoveMessage();
            Save();
            EnableEditButtonState();
        }

        private void setDefaultImagetoolStripMenuItem_Click(object sender, EventArgs e)
        {
            SetDefaultNailImage();
            Save();
        }

        private void tlGroup_MouseUp(object sender, MouseEventArgs e)
        {           
            if ((e.Button & MouseButtons.Right) == MouseButtons.Right)
            {
                if (tlGroup.FocusedNode != null && tlGroup.FocusedNode.Tag != null)
                {
                    tsmiDelete.Enabled = true;
                    setDefaultImagetoolStripMenuItem.Enabled = true;
                }
                else
                {
                    tsmiDelete.Enabled = false;
                    setDefaultImagetoolStripMenuItem.Enabled = false;
                }
                EnableEditButtonState();
                tlGroup.ContextMenuStrip.Show();
            }
            else
                tlGroup.ContextMenuStrip.Hide();
        }

        private void tlGroup_KeyUp(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Delete)
            {
                RemoveMessage();
                Save();
                EnableEditButtonState();
            }
        }

        private void tsmiNewTimeSliceGroup_Click(object sender, EventArgs e)
        {
            try
            {
                if (ControlService.SignCombo.Current == null)
                {
                    MsgBox.Warning(ProWrite.Resources.Resource.GetString(ProWrite.Resources.Resource.Strings.AddNewSignFirst));
                    return;
                }
                EditGroup(string.Empty);
                EnableEditButtonState();
            }
            catch (Exception ex)
            {
                DataGate.Log.Error(Resource.GetString(Resource.Strings.PlayListTimeSliceGroupControlEditGroupInfoException), ex);
            }
        }

        private void tsmiEditTimeSliceGroup_Click(object sender, EventArgs e)
        {
            try
            {
                if (ControlService.SignCombo.Current == null)
                {
                    MsgBox.Warning(ProWrite.Resources.Resource.GetString(ProWrite.Resources.Resource.Strings.AddNewSignFirst));
                    return;
                }
                EditGroup(LibraryGroup.Current.TimeSliceGroups[cbeGroup.SelectedIndex].Name);
            }
            catch (Exception ex)
            {
                DataGate.Log.Error(Resource.GetString(Resource.Strings.PlayListTimeSliceGroupControlEditGroupInfoException), ex);
            }
        }

        void OnLibraryRename(object sender, LibraryRenameMessage msg)
        {
            if (msg.Type == LibraryType.TimeSliceGroup)
                LoadGroup(_currentGroup.Name);
            if (msg.Type == LibraryType.Message)
                LoadGroupItem(_currentGroup);
        }
        #endregion

        
    }
}
