//---------------------------------------------------------------------
//
// File: DashboardTree.cs
//
// Description:
// The control of dashboardtree
//
// Author: terry
//
// Copyright (C) 2008 by ISoftstone Corporation.  All rights reserved.
// 
// Modify history:   
// Terry   2008-6-18   修改内容：当编辑Sign的图片信息后，应发送消息，使Current Sign的图片显示
//      内容应作相应改变。
// Kevin  2008-6-18  重构Get group tree info
// Louis	2008-6-24 Using resource key to get Images 
//
// terry   2008-6-19   代码国际化:添加注释，整理字符串信息
// terry   2008-6-26   当某Sign的Active置为true时，Current Sign默认选中该Sign
//---------------------------------------------------------------------
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Text;
using System.Windows.Forms;
using ProWrite.Entity.Dashboard;
using DevExpress.XtraTreeList.Nodes;
using DevExpress.XtraTreeList;
using ProWrite.Core;
using ProWrite.Resources;
using ProWrite.UI.Controls.Common;
using ProWrite.UI.Controls.Common.Messages;
using ProWrite.Entity.Settings;
using System.Communication.Messaging;
using ProWrite.UFE;
using System.Threading;
using ProWrite.UI.Controls.Actions;
using ProWrite.UI.Controls.Actions.UFE.Requests;
using ProWrite.UI.Controls.Actions.UFE;
using DevExpress.XtraEditors.Repository;
using System.Threading.Tasks;

namespace ProWrite.UI.Controls.Dashboard
{
    /// <summary>
    /// The control of dashboardtree
    /// </summary>
    public partial class DashboardTree : ControlBase
    {
        #region Constants
        /// <summary>
        /// Constants class
        /// </summary>
        public class _
        {
            public const string Name = "Name";
            public const string Active = "Active";
            public const string LogView = "LogView";
            public const string Status = "Status";
            public const string Color = "Color";
            public const string Resolution = "Resolution";
            public const string Connection = "Connection";
            public const string Health = "Health";
            public const string MessageStatus = "Message Status";
            public const string CurrentMessage = "Current Message";

            public const string Type = "Type";
            public const string FreeMemory = "Free Memory";
            public const string SignInfo = "SignInfo";
            public const string ModuleSender = "ProWrite.UI.Modules.DashboardModule";
            public const string e = "e";
            public const int GroupImageIndex = 0;
            public const int SignImageIndex = 1;
            public const int SignConnectImageIndex = 2;
        }
        #endregion

        #region Variables
        /// <summary>
        /// Mouse click location on TreeList
        /// </summary>
        private Point _pMouse;
        #endregion

        public TreeListNode FocusedNode { get { return treeList.FocusedNode; } }
        public TreeList DashboardTreeList { get { return treeList; } }
        public static SignInfo _currentSign = ControlService.SignCombo.Current;
        #region Function

        #region Constructors
        public DashboardTree()
        {
            DataGate.Log.Debug("DashboardTree InitializeComponet start.");
            InitializeComponent();
            DataGate.Log.Debug("DashboardTree No design Mode Init start.");
            if (!DesignMode)
            {
                Init();
                DataGate.Log.Debug("No design Mode InitResource start.");
                InitializeResource();
                RegisterHelp();
            }
            DataGate.Log.Debug("DashboardTree InitializeComponet end.");
        }
        #endregion

        #region Initialization
        protected override void Init()
        {
            base.Init();
            PopulateTree();
            SetTreeImageState();
            //接收消息，判断当前下拉列表是否选中了某一个Sign
            LocalMessageBus.Subject<SelectedSignMessage>().Observers += new ObserverHandler<SelectedSignMessage>(DashboardTree_Observers);
            LocalMessageBus.Subject<InitSystemData>().Observers += new ObserverHandler<InitSystemData>(DashboardTree_Observers);
            //接收菜单消息，判断当前点击的菜单项，以便相应不同的事件
            MessageBus.Subject<GetSignInfoMessage>().Observers += new ObserverHandler<GetSignInfoMessage>(GetSignInfo);
            LocalMessageBus.Subject<PWMessage<MenuCommands>>().Observers += delegate(object sender, PWMessage<MenuCommands> msg)
            {
                switch (msg.Content)
                {
                    case MenuCommands.NewSign:
                        if (!MainForm.IsCancelToNewSign)
                        {
                            ShowSignEditor(DashboardType.Sign);
                        }
                        //MainForm.IsCancelToNewSign = true;
                        break;
                    case MenuCommands.NewSignGroup:
                        if (!MainForm.IsCancelToNewSign)
                        {
                            ShowSignEditor(DashboardType.Group);
                        }
                        //MainForm.IsCancelToNewSign = true;
                        break;
                    case MenuCommands.DashboardEdit:
                        LocalMessageBus.Send(this, new DoubleClickCurrentImage(treeList.FocusedNode.Tag as SignInfo));
                        break;
                }
            };

        }

        void GetSignInfo(object sender, GetSignInfoMessage msg)
        {
            var sign = _currentSign;
            if (sign.DashboardType == DashboardType.Sign
                && sign.Controller.Connection.State == System.Communication.ConnectionState.Opened)
            {
                string signInfo = msg.Resp.GetProperty<string>("Info");
                int height = msg.Resp.GetProperty<int>("Hight");
                int width = msg.Resp.GetProperty<int>("Width");
                SignType signType = EnumHelper.Parse<SignType>(msg.Resp.GetProperty<int>("Type"));

                sign.Height = height;
                //sign.SignInfomation = signInfo + "  :  " + height.ToString() + " x " + width.ToString() + "  :  " + signType.ToString();
                sign.SignInfomation = height.ToString() + " x " + width.ToString();
                sign.Width = width;
                sign.Template.Sign.Width = width;
                sign.Template.Sign.Height = height;
                var message = sign.Template.Message;
                message.ImageLayer.Height = message.ImageLayer.FitToSign ? sign.Height : sign.Height / 2;
                message.ImageLayer.Width = message.ImageLayer.FitToSign ? sign.Width : sign.Width / 2;
                message.VideoLayer.Height = message.VideoLayer.FitToSign ? sign.Height : sign.Height / 2;
                message.VideoLayer.Width = message.VideoLayer.FitToSign ? sign.Width : sign.Width / 2;
                message.TextLayer.Height = message.TextLayer.FitToSign ? sign.Height : sign.Height / 2;
                message.TextLayer.Width = message.TextLayer.FitToSign ? sign.Width : sign.Width / 2;
                message.DynamicTextLayer.Height = message.DynamicTextLayer.FitToSign ? sign.Height : sign.Height / 2;
                message.DynamicTextLayer.Width = message.DynamicTextLayer.FitToSign ? sign.Width : sign.Width / 2;
                sign.Type = signType;

                LocalMessageBus.Send(this, new DataChangedMessage(PWDataType.Dashboard));

                //PopulateTree();
                treeList.FocusedNode = treeList.FindNodeByFieldValue(_.Name, sign.Name);
                ActionHelper.OnConnected();
            }
        }

        public void Delete()
        {
            if (DeleteNode(true))
            {
                PopulateTree();
                SetTreeImageState();
            }
        }

        public override void InitializeResource()
        {
            base.InitializeResource();

            //TODO: InitializeResource
        }

        private void RegisterHelp()
        {
            this.SetShowHelp(HelpNavigator.Topic, Resource.Helps.DashboardSignList);
        }

        void DashboardTree_Observers(object sender, InitSystemData msg)
        {
            LocalMessageBus.Send(this, new DataChangedMessage(PWDataType.Dashboard));
            PopulateTree();
            SetTreeImageState();
            LocalMessageBus.Send(this, new ActiveChange(null, false));
        }

        /// <summary>
        /// 根据Current Sign当前选中的Sign，使treeList定位到该Sign节点
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="msg"></param>
        void DashboardTree_Observers(object sender, SelectedSignMessage msg)
        {
            if (sender != this && msg.CurrentSign != null)
            {
                treeList.FocusedNode = treeList.FindNodeByFieldValue(_.Name, msg.CurrentSign.Name);
            }
        }

        /// <summary>
        /// 双击Current Sign当前选中的Sign，
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="msg"></param>
        void DashboardTree_ObserversDoubleClick(object sender, DoubleClickCurrentImage msg)
        {
            if (msg != null)
            {
                EditDashboardItem(new SignForm(msg.CurrentSign, false), msg.CurrentSign as DashboardItem);
            }
        }
        #endregion

        #region Function define
        /// <summary>
        /// Populate Tree
        /// </summary>
        public void PopulateTree()
        {
            DataGate.Log.Debug("PopulateTree node Clear.");
            treeList.Nodes.Clear();

            DataGate.Log.Debug("PopulateTree DataGate Project RootGroup.");
            PopulateTree(DataGate.Project.RootGroup, null);
            DataGate.Log.Debug("treeList.ExpandAll");

            treeList.ExpandAll();
        }

        /// <summary>
        /// Populate Tree
        /// </summary>
        /// <param name="group">SignGroupInfo</param>
        /// <param name="parentNode">Parent node</param>
        private void PopulateTree(SignGroupInfo group, TreeListNode parentNode)
        {
            DataGate.Log.Debug("SignGroupInof:" + group.Name);
            DataGate.Log.Debug("group.Groups.Length:" + group.Groups.Length);
            //sub-group
            if (group.Groups.Length > 0)
            {
                TreeListNode node = null;
                foreach (SignGroupInfo item in group.Groups)
                {
                    DataGate.Log.Debug("NodeItemArryIndex 1");
                    DataGate.Log.Debug("NodeItemArry:" + item.ItemArray.ToString());// +";parentNode:"+parentNode.ToString());
                    node = treeList.AppendNode(item.ItemArray, parentNode);
                    node.Tag = item;
                    DataGate.Log.Debug("populatetree item." + item.ToString());
                    PopulateTree(item, node);
                }
            }

            if (group.Signs.Length > 0)
            {
                DataGate.Log.Debug("group.Signs.Length :" + group.Signs.Length);
                TreeListNode node = null;
                foreach (SignInfo item in group.Signs)
                {
                    DataGate.Log.Debug("item.name:" + item.Name);
                    if (item.DashboardType == DashboardType.Sign
                        && !item.HasFireConnectionExceptionEvent)
                    {
                        DataGate.Log.Debug("connection exception 1.");
                        item.Controller.Connection.ExceptionFired -= Connection_ExceptionFired;
                        DataGate.Log.Debug("connection exception 2.");
                        item.Controller.Connection.ConnectionClosed -= Connection_ConnectionClosed;
                        DataGate.Log.Debug("connection exception 3.");
                        item.Controller.Connection.ExceptionFired += Connection_ExceptionFired;
                        DataGate.Log.Debug("connection exception 4.");
                        item.Controller.Connection.ConnectionClosed += Connection_ConnectionClosed;
                        //item.Controller.UserManager.GetSignInfoSuccessed+=new ReceivedHandler(UserManager_GetSignInfoSuccessed);
                        //item.Controller.UserManager.GetSignInfoFailed+=new ReceivedHandler(UserManager_GetSignInfoFailed);
                        item.HasFireConnectionExceptionEvent = true;
                        DataGate.Log.Debug("connection exception 5.");
                    }
                    DataGate.Log.Debug("AppendNode item here.");
                    DataGate.Log.Debug("AppendNode:" + item.ItemArray.ToString());// +";parentnode:"+parentNode.ToString());
                    node = treeList.AppendNode(item.ItemArray, parentNode);
                    node.Tag = item;
                    DataGate.Log.Debug("AppendNode end");


                }
            }
            if (ControlService.SignCombo.Current != null)
                treeList.FocusedNode = treeList.FindNodeByFieldValue(_.Name, ControlService.SignCombo.Current.Name);
        }




        /// <summary>
        /// Set default button shape
        /// </summary>
        private void SetDefaultbtn()
        {
            // updated to get shape using resource key by Louis
            btnDelete.Image = ProWrite.Resources.Resource.GetImage(ProWrite.Resources.Resource.Images.RecycleClose16);
            SetDefaultCursor();

        }

        /// <summary>
        /// 改变treeList节点项的Active状态
        /// </summary>
        /// <param name="node"></param>
        /// <param name="check"></param>
        private void SetCheckedNode(TreeListNode node, bool check)
        {
            DashboardItem item = node.Tag as DashboardItem;
            treeList.FocusedNode = node;
            treeList.BeginUpdate();
            node[_.Active] = check;

            if (item.DashboardType == DashboardType.Group)
            {
                SignGroupInfo group = (SignGroupInfo)item;
                group.Active = check;
            }
            else
            {
                SignInfo sign = (SignInfo)item;
                sign.Active = check;
            }
            SetCheckedParentNodes(node, check);
            SetCheckedChildNodes(node, check);
            treeList.EndUpdate();
            //发送消息,DashBoard数据已经修改
            LocalMessageBus.Send(this, new DataChangedMessage(PWDataType.Dashboard));
            //发送消息，DashBoard的Active改变
            LocalMessageBus.Send(this, new ActiveChange(null, false));
        }

        /// <summary>
        /// set checked parentnodes
        /// </summary>
        /// <param name="node"></param>
        /// <param name="check"></param>
        private void SetCheckedParentNodes(TreeListNode node, bool check)
        {
            if (node.ParentNode != null)
            {
                bool b = false;
                for (int i = 0; i < node.ParentNode.Nodes.Count; i++)
                {
                    if (!check.Equals(node.ParentNode.Nodes[i][_.Active]))
                    {
                        b = !b;
                        break;
                    }
                }
                SignGroupInfo group = (SignGroupInfo)node.ParentNode.Tag;
                if (!check)
                {
                    node.ParentNode[_.Active] = b ? true : check;

                    group.Active = b;
                }
                else
                {
                    node.ParentNode[_.Active] = true;

                    group.Active = true;
                }
                SetCheckedParentNodes(node.ParentNode, check);
            }
        }

        /// <summary>
        /// Set checked childnodes
        /// </summary>
        /// <param name="node"></param>
        /// <param name="check"></param>
        private void SetCheckedChildNodes(TreeListNode node, bool check)
        {
            for (int i = 0; i < node.Nodes.Count; i++)
            {
                node.Nodes[i][_.Active] = check;
                DashboardItem item = node.Nodes[i].Tag as DashboardItem;
                item.Active = check;
                SetCheckedChildNodes(node.Nodes[i], check);
            }
        }

        /// <summary>
        /// 当拖动Sign时，修改父节点的Active
        /// </summary>
        /// <param name="node"></param>
        private void SetParentActive(TreeListNode node)
        {
            if (node.ParentNode != null)
            {
                node.ParentNode[_.Active] = true;
                DashboardItem item = node.ParentNode.Tag as DashboardItem;
                item.Active = true;
                SetParentActive(node.ParentNode);
            }
        }

        /// <summary>
        /// Add a sign or a group
        /// </summary>
        /// <param name="type">A sign or a grop</param>
        public void ShowSignEditor(DashboardType type)
        {
            DashboardForm frm = null;

            if (treeList.Nodes.Count <= 0)
            {
                if (type == DashboardType.Group)
                    frm = new SignGroupForm();
                else
                    frm = new SignForm();
            }
            else
            {
                if (treeList.FocusedNode == null)
                    treeList.FocusedNode = treeList.Nodes[0];

                DashboardItem item = treeList.FocusedNode.Tag as DashboardItem;
                if (type == DashboardType.Group)
                {
                    //在Group上点击的Add Sign Group
                    if (item.DashboardType == DashboardType.Group)
                        frm = new SignGroupForm(item as SignGroupInfo);
                    else//在Sign上点击的Add Sign Group
                        frm = new SignGroupForm(item.Parent);
                }
                else
                {

                    //在Group上点击的Add Sign Group
                    if (item.DashboardType == DashboardType.Group)
                    {
                        //判断Sign是否超过20个
                        //if (SignGroupInfo.IsSignCountValid(item as SignGroupInfo))
                        //{
                        //    MsgBox.Warning(Resources.Resource.GetString(Resources.Resource.Strings.SignsCountMoreThanTwenty));
                        //    return;
                        //}
                        frm = new SignForm(item as SignGroupInfo);
                    }
                    else
                    {
                        //判断Sign是否超过20个
                        //if (SignGroupInfo.IsSignCountValid(item.Parent as SignGroupInfo))
                        //{
                        //    MsgBox.Warning(Resources.Resource.GetString(Resources.Resource.Strings.SignsCountMoreThanTwenty));
                        //    return;
                        //}
                        frm = new SignForm(item.Parent);
                    }
                }
            }

            if (frm != null)
            {
                //this.ParentForm.TopMost = true;
                frm.ShowModalDialog();
                //this.ParentForm.TopMost = false;
                if (frm.IsRefresh
                    && frm.DashBoard != null
                    && frm.DashBoard.Name != null)
                {
                    if (type == DashboardType.Sign
                        || type == DashboardType.DemoSign)
                    {
                        LocalMessageBus.Send(this, new DataChangedMessage(PWDataType.Dashboard));

                    }
                    PopulateTree();
                    _currentSign = frm.DashBoard as SignInfo;
                    if (_currentSign != null && frm.IsConnectWebCam)
                    {
                            this.InvokeMethod(() => ControlService.SignImage.RefreshImageCamera(_currentSign));
                    }
                    SetTreeImageState();
                    if (frm.DashBoard != null)
                    {

                        treeList.FocusedNode = treeList.FindNodeByFieldValue(_.Name, frm.DashBoard.Name);
                        if (type == DashboardType.Sign
                            || type == DashboardType.DemoSign)
                        {
                            LocalMessageBus.Send(this, new SelectedSignMessage(frm.DashBoard as SignInfo));
                            ControlService.SignCombo.SelectedItem = frm.DashBoard as SignInfo;
                        }

                    }

                }
            }
        }

        public void SetTreeFocusedNode(SignInfo sign)
        {
            treeList.FocusedNode = treeList.FindNodeByFieldValue(_.Name, sign.Name);
        }

        private void SetTreeImageState()
        {
            foreach (SignInfo sign in DataGate.Project.RootGroup.Signs)
            {
                if (sign.Controller.Connection.State == System.Communication.ConnectionState.Opened)
                {
                    var focusedNode = treeList.FindNodeByFieldValue(_.Name, sign.Name);
                    if (focusedNode != null)
                        focusedNode.ImageIndex = _.SignConnectImageIndex;
                }
            }
        }

        /// <summary>
        /// Denete node
        /// </summary>
        /// <param name="node"></param>
        private bool DeleteNode(TreeListNode node)
        {
            DashboardItem item = node.Tag as DashboardItem;
            SignGroupInfo group = item.Parent;
            if (item.DashboardType == DashboardType.Sign)
            {
                SignInfo sign = item as SignInfo;
                Action successCallback = null;
                Action failCallback = null;
                var action = new LogoffAction(sign, successCallback, failCallback, false);
                action.Perform();
            }
            bool result = false;
            if (item.DashboardType == DashboardType.Group)
                result = group.RemoveGroup(item as SignGroupInfo, true);
            else
                result = group.RemoveSign(item as SignInfo);

            //发送消息,DashBoard数据已经修改
            LocalMessageBus.Send(this, new DataChangedMessage(PWDataType.Dashboard));
            LocalMessageBus.Send(this, new ActiveChange(null, false));
            return result;
        }
        /// <summary>
        /// 
        /// </summary>
        private bool DeleteNode()
        {
            TreeListNode node = treeList.FocusedNode;
            if (node == null)
                return false;
            DashboardItem item = (node.Tag) as DashboardItem;
            string confirm = "";
            if (DeleteValidate(item) != "")
            {
                MsgBox.Error(DeleteValidate(item));
                return false;
            }
            if (item.DashboardType == DashboardType.Group)
            {
                confirm = "Are you sure you want to delete '" + item.Name + "'?";
            }
            else
            {

                confirm = Resources.Resource.GetString(Resources.Resource.Strings.ConfirmDeleteSign);
            }
            if (MsgBox.Confirm("Are you sure you want to delete '" + item.Name + "'?") == DialogResult.No)
            {
                return false;
            }

            return DeleteNode(node);
        }

        private string DeleteValidate(DashboardItem item)
        {
            string result = "";
            if (item.DashboardType == DashboardType.Group)
            {
                SignGroupInfo group = item as SignGroupInfo;
                SignInfo[] list = DashboardItem.FindAllSigns(group);
                if (list.Length > 0)
                {
                    foreach (SignInfo sign in list)
                    {
                        if (sign.RefernceCount > 0)
                            result = "Delete failed,the sign '" + sign.Name + "' is using.";
                        else
                        {
                            if (sign.DashboardType == DashboardType.Sign
                                && sign.Controller.Connection.State != System.Communication.ConnectionState.Closed)
                                result = "Delete failed,please disconnect the sign '" + sign.Name + "' first.";
                        }
                    }
                }
            }
            else
            {
                SignInfo sign = item as SignInfo;
                if (sign.RefernceCount > 0)
                    result = "Delete failed,the sign '" + sign.Name + "' is using.";
                else
                {
                    if (item.DashboardType == DashboardType.Sign)
                    {
                        if (sign.Controller.Connection.State != System.Communication.ConnectionState.Closed)
                            result = "Delete failed,please disconnect first.";
                    }
                }
            }
            return result;

        }
        private bool DeleteNode(bool isMenu)
        {
            TreeListNode node = treeList.FocusedNode;
            if (node == null)
                return false;
            return DeleteNode(node);
        }

        /// <summary>
        /// Set default cursor
        /// </summary>
        private void SetDefaultCursor()
        {
            Cursor = Cursors.Default;
        }
        /// <summary>
        /// get treelist's drag object
        /// </summary>
        /// <param name="data">Node data</param>
        /// <returns></returns>
        private DragObject GetDragObject(IDataObject data)
        {
            return data.GetData(typeof(DragObject)) as DragObject;
        }
        /// <summary>
        /// Get Drag Node
        /// </summary>
        /// <param name="data"></param>
        /// <returns></returns>
        private TreeListNode GetDragNode(IDataObject data)
        {
            return data.GetData(typeof(TreeListNode)) as TreeListNode;
        }

        /// <summary>
        /// Edit sign or group
        /// </summary>
        private void EditDashboardItem(bool isSign)
        {

            if (treeList.Nodes.Count <= 0)
                return;

            if (treeList.FocusedNode == null)
                return;

            DashboardItem item = treeList.FocusedNode.Tag as DashboardItem;
            DashboardForm frm = new DashboardForm();
            /////编辑Group
            if (item.DashboardType == DashboardType.Group)
            {
                if (isSign)
                    return;
                frm = new SignGroupForm(item as SignGroupInfo, item.Parent);
            }
            else////编辑Sign
            {
                frm = new SignForm((SignInfo)item, false);
            }
            EditDashboardItem(frm, item);
        }


        private void EditDashboardItem(DashboardForm frm, DashboardItem item)
        {
            frm.ShowModalDialog();
            if (frm.IsRefresh)
            {
                LocalMessageBus.Send(this, new DataChangedMessage(PWDataType.Dashboard));
                LocalMessageBus.Send(this, new ActiveChange(item as SignInfo, false));
                PopulateTree();
                SetTreeImageState();
                _IsDisconnection = frm.IsDisconnection;
                treeList.FocusedNode = treeList.FindNodeByFieldValue(_.Name, item.Name);
                DashboardItem itemSign = treeList.FocusedNode.Tag as DashboardItem;
                if (itemSign.DashboardType == DashboardType.Sign)
                {
                    SignInfo sign = itemSign as SignInfo;
                    if (sign != null && frm.IsConnectWebCam)
                    {
                        //frm.IsConnectWebCam = false;
                        Task.Create(p =>
                        {
                            ControlService.SignImage.RefreshImageCamera(sign);
                        });
                    }
                    //string toFilePath = Constance.AppPath + sign.Name + ".xml";

                    //var status = Serialiser<StatusInfo>.Xml.Deserialise(toFilePath);
                    //if (status != null && status.Count > 0)
                    //    sign.Status = status[0].StatusValue.ToLower();

                    _currentSign = sign;
                    if (sign.Controller.Connection.State == System.Communication.ConnectionState.Opened)
                    {
                        var action = new SelectedSignAction(sign);
                        action.Perform();
                    }
                    else
                        ActionHelper.OnDisconnected(true);
                }
                else
                {
                    ActionHelper.OnDisconnected(false);
                }
                treeList.FocusedNode = treeList.FindNodeByFieldValue(_.Name, item.Name);
            }
        }
        #endregion

        #endregion

        #region  Event
        /// <summary>
        /// treeList mousedown event
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void treeList_MouseDown(object sender, MouseEventArgs e)
        {
            _pMouse = new Point(e.X, e.Y);
            //取出当前鼠标所在位置的treelist的节点信息
            TreeListHitInfo hInfo = treeList.CalcHitInfo(new Point(e.X, e.Y));

            ////判断鼠标是否是点击到了某一节点上
            if (hInfo.HitInfoType == HitInfoType.Cell || hInfo.HitInfoType == HitInfoType.StateImage || hInfo.HitInfoType == HitInfoType.RowIndicator)
            {
                //发送菜单消息，判断菜单的Delete按钮是否激活
                if (treeList.FocusedNode != null)
                    LocalMessageBus.Send(this, new MenuMessage(MenuCommands.Delete, true));
                DashboardItem item = hInfo.Node.Tag as DashboardItem;
                /////发送菜单消息，判断菜单的InsertSignImage按钮是否激活
                LocalMessageBus.Send(this, new MenuMessage(MenuCommands.DashboardEdit, item.DashboardType != DashboardType.Group));
                /////判断是否选中了Sign,以便Current Sign也选中该Sign
                if (item.DashboardType == DashboardType.Sign
                    || item.DashboardType == DashboardType.DemoSign)
                {
                    if (item.DashboardType == DashboardType.DemoSign)
                        LocalMessageBus.Send(this, new SetPWLogo("green"));
                    else
                        LocalMessageBus.Send(this, new SetPWLogo(item.Status));
                    if (item.Active)
                    {
                        LocalMessageBus.Send(this, new SelectedSignMessage(hInfo.Node.Tag as SignInfo));
                        treeList.FocusedNode = hInfo.Node;
                        ControlService.SignCombo.SelectedItem = hInfo.Node.Tag;
                    }
                }
            }
            else
            {
                ////如果鼠标当前没有点击到treeList的某一节点项上，但是treeList的某一项仍处于选中状态，菜单的Delete按钮也应激活
                bool enabled = (treeList.FocusedNode != null) && (hInfo.HitInfoType == HitInfoType.Empty || hInfo.HitInfoType == HitInfoType.Column || hInfo.HitInfoType == HitInfoType.Row);
                LocalMessageBus.Send(this, new MenuMessage(MenuCommands.Delete, enabled));
            }

            if (e.Button == MouseButtons.Left)
            {

                /////判断鼠标是否点击到了Active列，并改变当前节点项的Active状态
                if (hInfo.HitInfoType == HitInfoType.Cell && hInfo.Column.Caption == _.Active)
                {
                    TreeListNode node = hInfo.Node;
                    DashboardItem item = hInfo.Node.Tag as DashboardItem;
                    SetCheckedNode(node, !item.Active);
                    PopulateTree();
                    SetTreeImageState();
                    //修改Active之后，判断是否在Current Sign中选中当前修改的Sign
                    if (item.DashboardType == DashboardType.Group)
                    {
                        TreeListNode childNode = GetFirstChildSign(node);

                        if (childNode != null)
                        {
                            DashboardItem childItem = childNode.Tag as DashboardItem;
                            if (childItem.DashboardType == DashboardType.Sign)
                                LocalMessageBus.Send(this, new ActiveChange(GetFirstChildSign(node).Tag as SignInfo, true));
                        }
                    }
                    else
                        LocalMessageBus.Send(this, new ActiveChange(item as SignInfo, true));
                }
                //else
                //{
                //    return;
                //}
            }
            else if (e.Button == MouseButtons.Right)////如果点击了右键
            {
                if (hInfo.HitInfoType == HitInfoType.Cell || hInfo.HitInfoType == HitInfoType.StateImage)
                {
                    //如果treeList选中了项,则显示右键菜单的全部内容
                    TreeListNode node = hInfo.Node;
                    treeList.FocusedNode = node;
                    deleteToolStripMenuItem.Visible = true;
                    editToolStripMenuItem.Visible = true;
                    if ((hInfo.Node.Tag as DashboardItem).DashboardType == DashboardType.Group)
                    {
                        addGroupToolStripMenuItem.Visible = false;
                        removeGroupToolStripMenuItem.Visible = false;
                        disConnectToolStripMenuItem.Visible = false;
                        ConnectToolStripMenuItem.Visible = false;
                        showStatusSignToolStripMenuItem.Visible = false;
                        showLogViewToolStripMenuItem.Visible = false;
                        RefreshSignToolStripMenuItem.Visible = false;
                    }
                    else
                    {
                        addGroupToolStripMenuItem.Visible = true;
                        if ((hInfo.Node.Tag as DashboardItem).Parent != DataGate.Project.RootGroup)
                            removeGroupToolStripMenuItem.Visible = true;
                        else
                            removeGroupToolStripMenuItem.Visible = false;
                        if ((hInfo.Node.Tag as SignInfo).Controller.Connection.State == System.Communication.ConnectionState.Opened)
                        {
                            disConnectToolStripMenuItem.Visible = true;
                            ConnectToolStripMenuItem.Visible = false;
                            showLogViewToolStripMenuItem.Visible = true;
                            showStatusSignToolStripMenuItem.Visible = true;
                            RefreshSignToolStripMenuItem.Visible = true;
                            showLogViewToolStripMenuItem.Enabled = true;
                            showStatusSignToolStripMenuItem.Enabled = true;
                            RefreshSignToolStripMenuItem.Enabled = true;
                        }
                        else
                        {
                            disConnectToolStripMenuItem.Visible = false;
                            if ((hInfo.Node.Tag as SignInfo).DashboardType == DashboardType.Sign)
                            {
                                ConnectToolStripMenuItem.Visible = true;

                                showLogViewToolStripMenuItem.Visible = true;
                                showStatusSignToolStripMenuItem.Visible = true;
                                RefreshSignToolStripMenuItem.Visible = true;
                                showLogViewToolStripMenuItem.Enabled = false;
                                showStatusSignToolStripMenuItem.Enabled = false;
                                RefreshSignToolStripMenuItem.Enabled = false;
                            }
                            else
                            {
                                ConnectToolStripMenuItem.Visible = false;

                                showLogViewToolStripMenuItem.Visible = false;
                                showStatusSignToolStripMenuItem.Visible = false;
                                RefreshSignToolStripMenuItem.Visible = false;
                            }
                        }
                    }
                    treeList.ContextMenuStrip = this.contextMenuStrip2;
                }
                else if (hInfo.HitInfoType == HitInfoType.Empty)
                {
                    //如果点击treeList的空白处，则隐藏Edit、delete、Add to group的功能
                    deleteToolStripMenuItem.Visible = false;
                    editToolStripMenuItem.Visible = false;
                    addGroupToolStripMenuItem.Visible = false;
                    removeGroupToolStripMenuItem.Visible = false;
                    disConnectToolStripMenuItem.Visible = false;
                    ConnectToolStripMenuItem.Visible = false;
                    treeList.ContextMenuStrip = this.contextMenuStrip2;
                }
                else
                {
                    treeList.ContextMenuStrip = null;
                }
            }
            if (hInfo != null && hInfo.Node != null)
                treeList.FocusedNode = treeList.FindNodeByID(hInfo.Node.Id);
        }

        void treeList_CustomNodeCellEdit(object sender, DevExpress.XtraTreeList.GetCustomNodeCellEditEventArgs e)
        {
            //if (e.Column.FieldName == "FreeMemory")
            //{
            //    object obj = e.Node.GetValue(1);
            //    object objConnect =e.Node.GetValue(6);
            //    if (obj != null&& objConnect!=null)
            //    {
            //        if (obj.ToString() != DashboardType.Sign.ToString()
            //            || objConnect.ToString() == "Disconnected")
            //        {
            //            e.RepositoryItem = this.repositoryItemTextEdit1;
            //        }
            //    }
            //}
        }

        private TreeListNode GetFirstChildSign(TreeListNode node)
        {
            if (node.FirstNode == null)
                return null;
            DashboardItem item = node.FirstNode.Tag as DashboardItem;
            if (item.DashboardType == DashboardType.Group)
                return GetFirstChildSign(node.FirstNode);
            else
                return node.FirstNode;
        }
        /// <summary>
        /// treelist double click event, double click item,open window to amend the item
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void treeList_DoubleClick(object sender, EventArgs e)
        {
            //判断是不是双击了有效位置
            TreeListHitInfo hInfo = treeList.CalcHitInfo(_pMouse);
            if ((hInfo.HitInfoType == HitInfoType.Cell && (hInfo.Column.Caption == _.Name
                || hInfo.Column.Caption == _.Type
                || hInfo.Column.Caption == _.SignInfo
                || hInfo.Column.Caption == _.Color
                || hInfo.Column.Caption == _.Resolution
                || hInfo.Column.Caption == _.MessageStatus
                || hInfo.Column.Caption == _.CurrentMessage
                || hInfo.Column.Caption == _.Health
                || hInfo.Column.Caption == _.Connection))

                || hInfo.HitInfoType == HitInfoType.StateImage
                || hInfo.HitInfoType == HitInfoType.Row)
            {
                if (treeList.Nodes.Count <= 0)
                {
                    return;
                }
                //如果点击了有效位置，则执行编辑功能
                EditDashboardItem(false);
            }
            if (hInfo.HitInfoType == HitInfoType.Cell
                && hInfo.Column.Caption == _.LogView)
            {
                DashboardItem item = treeList.FocusedNode.Tag as DashboardItem;
                if (item.DashboardType == DashboardType.Sign)
                {
                    if ((item as SignInfo).Controller.Connection.State == System.Communication.ConnectionState.Opened)
                    {
                        LogView view = new LogView();
                        view.ShowModalDialog();
                    }
                    else
                        MsgBox.Error(Resources.Resource.GetString(Resources.Resource.Strings.SendSendToSignLoginFirst));
                }
            }
            if (hInfo.HitInfoType == HitInfoType.Cell
                && hInfo.Column.Caption == _.Status)
            {
                DashboardItem item = hInfo.Node.Tag as DashboardItem;
                if (item.DashboardType == DashboardType.Sign)
                {
                    GetStatus status = new GetStatus(item as SignInfo);
                    status.ShowModalDialog();
                }
            }

        }

        private void repositoryItemProgressBar1_KeyDown(object sender, System.Windows.Forms.KeyEventArgs e)
        {
            int i = 0;
            if (treeList.ActiveEditor == null) return;

            if (e.KeyCode == Keys.Add)
            {
                i = (int)treeList.ActiveEditor.EditValue;
                if (i < 100)
                    treeList.ActiveEditor.EditValue = i + 1;
            }
            if (e.KeyCode == Keys.Subtract)
            {
                i = (int)treeList.ActiveEditor.EditValue;
                if (i > 0)
                    treeList.ActiveEditor.EditValue = i - 1;
            }
        }

        private void treeList_GetStateImage(object sender, GetStateImageEventArgs e)
        {
            if (e == null) throw new ArgumentNullException(_.e);
            //显示Sign的图片

            //e.Node[_.FreeMemory] = 70;
            if (e.Node[_.Type].ToString() == DashboardType.Group.ToString())
            {
                e.NodeImageIndex = _.GroupImageIndex;
            }
            else if (e.Node[_.Type].ToString() == DashboardType.Sign.ToString()
                && e.Node.Tag != null
                && (e.Node.Tag as SignInfo).Controller.Connection.State == System.Communication.ConnectionState.Opened)
            {
                e.NodeImageIndex = _.SignConnectImageIndex;
            }
            else
            {
                e.NodeImageIndex = _.SignImageIndex;
            }
            if (e.Node[_.Type].ToString() == DashboardType.Sign.ToString()
                && e.Node.Tag != null
                && (e.Node.Tag as SignInfo).Controller.Connection.State == System.Communication.ConnectionState.Opened)
            {
                e.NodeImageIndex = _.SignConnectImageIndex;
            }
            //bool d = false;
            //if (e.Node[0].ToString() == "Sign6")
            //    d = (e.Node.Tag as SignInfo).Controller.Connection.State == System.Communication.ConnectionState.Opened;
        }

        /// <summary>
        /// treeList拖拽时间
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void treeList_DragDrop(object sender, DragEventArgs e)
        {
            var dragInfo = treeList.GetDragInsertDirection();
            if (dragInfo != DragInsertDirection.None)
            {
                //dragInfo.can
            }

            //////取出当前鼠标所在位置的节点（被拖入节点）信息
            TreeListHitInfo hi = treeList.CalcHitInfo(treeList.PointToClient(new Point(e.X, e.Y)));
            //if (hi.Node == null)
            //    return;
            DashboardItem itemHi = hi.Node.Tag as DashboardItem;
            TreeListNode node1 = GetDragNode(e.Data);
            if (node1 == null)
                return;
            SignGroupInfo partGroupInfo;
            SignGroupInfo hiParentGroup = null;
            if (hi.Node.ParentNode != null)
            {
                hiParentGroup = hi.Node.ParentNode.Tag as SignGroupInfo;
            }
            ////如果被拖入的节点是Sign,则警告
            if (itemHi.DashboardType == DashboardType.Sign
                || itemHi.DashboardType == DashboardType.DemoSign)
            {
                if (dragInfo != DragInsertDirection.None)
                {
                    if (hi.Node.ParentNode != null)
                    {
                        hiParentGroup = hi.Node.ParentNode.Tag as SignGroupInfo;
                        if ((node1.Tag as DashboardItem).DashboardType == DashboardType.Sign
                            || (node1.Tag as DashboardItem).DashboardType == DashboardType.DemoSign)
                        {
                            if (node1.ParentNode != null)
                            {
                                partGroupInfo = node1.ParentNode.Tag as SignGroupInfo;
                                /////判断被拖入的Group的sign个数是否超过20
                                if (!SignGroupInfo.IsTwoGroupSameRoot(partGroupInfo, hiParentGroup))
                                {
                                    if (SignGroupInfo.IsSignCountValid(hiParentGroup))
                                    {
                                        MsgBox.Warning(Resources.Resource.GetString(Resources.Resource.Strings.SignsCountMoreThanTwenty));
                                        SetDefaultCursor();
                                        return;
                                    }
                                }
                            }
                            else
                            {    /////判断被拖入的Group的sign个数是否超过20

                                if (itemHi.Parent != null
                                    && SignGroupInfo.IsSignCountValid(itemHi.Parent as SignGroupInfo))
                                {
                                    MsgBox.Warning(Resources.Resource.GetString(Resources.Resource.Strings.SignsCountMoreThanTwenty));
                                    SetDefaultCursor();
                                    return;
                                }
                            }
                        }
                        else
                        {
                            partGroupInfo = node1.Tag as SignGroupInfo;
                            if (!SignGroupInfo.IsTwoGroupSameRoot(partGroupInfo, hiParentGroup))
                            {
                                if (SignGroupInfo.IsSignCountValid(hiParentGroup))
                                {
                                    MsgBox.Warning(Resources.Resource.GetString(Resources.Resource.Strings.SignsCountMoreThanTwenty));
                                    SetDefaultCursor();
                                    return;
                                }
                                if (SignGroupInfo.GetChildCountByGroup(partGroupInfo) + SignGroupInfo.GetRootChildCountByGroup(hiParentGroup) > 20)
                                {
                                    MsgBox.Warning(Resources.Resource.GetString(Resources.Resource.Strings.SignsCountMoreThanTwenty));
                                    SetDefaultCursor();
                                    return;
                                }
                            }
                        }
                    }
                    else
                    {

                    }
                }
                else
                {
                    MsgBox.Warning(Resources.Resource.GetString(Resources.Resource.Strings.AddSignGroupUnderSign));
                    SetDefaultCursor();
                    return;
                }
            }

            else
            {
                if ((node1.Tag as DashboardItem).DashboardType == DashboardType.Sign
                    || (node1.Tag as DashboardItem).DashboardType == DashboardType.DemoSign)
                {
                    if (node1.ParentNode != null)
                    {
                        partGroupInfo = node1.ParentNode.Tag as SignGroupInfo;
                        //SignGroupInfo toGroup;
                        //if (itemHi.DashboardType == DashboardType.Sign)
                        //{
                        //    if (hiParentGroup != null)
                        //        toGroup = hiParentGroup;
                        //}
                        //else
                        //    toGroup = itemHi as SignGroupInfo;

                        /////判断被拖入的Group的sign个数是否超过20
                        if (!SignGroupInfo.IsTwoGroupSameRoot(partGroupInfo, itemHi as SignGroupInfo))
                        {
                            if (SignGroupInfo.IsSignCountValid(itemHi as SignGroupInfo))
                            {
                                MsgBox.Warning(Resources.Resource.GetString(Resources.Resource.Strings.SignsCountMoreThanTwenty));
                                SetDefaultCursor();
                                return;
                            }
                        }
                    }
                    else
                    {    /////判断被拖入的Group的sign个数是否超过20

                        if (SignGroupInfo.IsSignCountValid(itemHi as SignGroupInfo))
                        {
                            MsgBox.Warning(Resources.Resource.GetString(Resources.Resource.Strings.SignsCountMoreThanTwenty));
                            SetDefaultCursor();
                            return;
                        }
                    }
                }
                else
                {
                    partGroupInfo = node1.Tag as SignGroupInfo;
                    if (!SignGroupInfo.IsTwoGroupSameRoot(partGroupInfo, itemHi as SignGroupInfo))
                    {
                        //if (SignGroupInfo.IsSignCountValid(itemHi as SignGroupInfo))
                        //{
                        //    MsgBox.Warning(Resources.Resource.GetString(Resources.Resource.Strings.SignsCountMoreThanTwenty));
                        //    SetDefaultCursor();
                        //    return;
                        //}
                        if (SignGroupInfo.GetChildCountByGroup(partGroupInfo) + SignGroupInfo.GetRootChildCountByGroup(itemHi as SignGroupInfo) > 20)
                        {
                            MsgBox.Warning(Resources.Resource.GetString(Resources.Resource.Strings.SignsCountMoreThanTwenty));
                            SetDefaultCursor();
                            return;
                        }
                    }
                }
            }


            ////获取被拖动的节点信息
            DragObject dobj = GetDragObject(e.Data);
            if (dobj != null)
            {
                TreeListNode node = hi.Node;
                if (hi.HitInfoType == HitInfoType.Empty || node != null)
                {
                    ////将被拖动的节点追加到被拖入的节点
                    node = treeList.AppendNode(dobj.DragData, node);
                    node.StateImageIndex = dobj.ImageIndex;
                    treeList.MakeNodeVisible(node);
                    TreeListNode parentNode = node.ParentNode;
                    if (parentNode != null && (e.KeyState & 4) != 0)
                    {
                        int index = -1;
                        if (parentNode.ParentNode != null)
                            index = parentNode.ParentNode.Nodes.IndexOf(parentNode);
                        treeList.MoveNode(node, parentNode.ParentNode);
                        treeList.SetNodeIndex(node, index);
                    }
                }
            }

            if (node1 != null)
            {
                DashboardItem item = node1.Tag as DashboardItem;

                if (dragInfo == DragInsertDirection.None)
                {
                    SignGroupInfo itemGroup = hi.Node.Tag as SignGroupInfo;
                    SignInfo signInfo = null;
                    if (item.DashboardType == DashboardType.Group)
                    {
                        SignInfo[] array = DashboardItem.FindAllSigns(SignGroupInfo.GetRootGroup(item as SignGroupInfo));
                        if (array.Length > 0)
                            signInfo = array[0];
                    }
                    else
                        signInfo = item as SignInfo;
                    if (signInfo != null && !itemGroup.IsSameSignType(signInfo, itemGroup))
                    {
                        MsgBox.Warning("Sign information is not equal");
                        SetDefaultCursor();
                        return;
                    }
                    ///拖动完毕后，改变被拖动节点的Parent

                    //SetCheckedNode(node1, item.Active);
                    if (item.Active)
                    {
                        hi.Node[_.Active] = true;
                        itemHi.Active = true;
                        SetParentActive(hi.Node);
                    }
                    item.Parent = hi.Node.Tag as SignGroupInfo;
                }
                else
                {
                    if (hiParentGroup != null)
                    {
                        if (!hiParentGroup.IsSameSignType(item as SignInfo, hiParentGroup))
                        {
                            MsgBox.Warning("Sign information is not equal");
                            SetDefaultCursor();
                            return;
                        }
                        item.Parent = hiParentGroup;
                    }
                    else
                        item.Parent = DataGate.Project.RootGroup;
                }
            }
            SetDefaultCursor();

        }

        void repositoryItemButtonEdit1_Click(object sender, System.EventArgs e)
        {

        }

        void treeList_DragEnter(object sender, System.Windows.Forms.DragEventArgs e)
        {
        }

        private void treeList_GiveFeedback(object sender, GiveFeedbackEventArgs e)
        {
            e.UseDefaultCursors = false;
        }

        private void treeList_DragObjectStart(object sender, DragObjectStartEventArgs e)
        {
            e.Allow = false;
        }

        private void treeList_DragCancelNode(object sender, EventArgs e)
        {
            string all = e.ToString();
        }


        private void treeList_KeyUp(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Up || e.KeyCode == Keys.Down)
            {
                if (treeList.FocusedNode == null)
                    return;


                DashboardItem item = treeList.FocusedNode.Tag as DashboardItem;
                /////发送菜单消息，判断菜单的InsertSignImage按钮是否激活
                LocalMessageBus.Send(this, new MenuMessage(MenuCommands.Delete, true));
                LocalMessageBus.Send(this, new MenuMessage(MenuCommands.DashboardEdit, item.DashboardType == DashboardType.DemoSign));
                /////判断是否选中了Sign,以便Current Sign也选中该Sign
                if (item.DashboardType == DashboardType.Sign
                   || item.DashboardType == DashboardType.DemoSign)
                    LocalMessageBus.Send(this, new SelectedSignMessage(treeList.FocusedNode.Tag as SignInfo));
            }
            if (e.KeyCode == Keys.Delete)
            {
                TreeListNode node = treeList.FocusedNode;
                if (node == null)
                    return;
                DashboardItem item = (node.Tag) as DashboardItem;
                string confirm = "";
                if (item.DashboardType == DashboardType.Group)
                    confirm = Resources.Resource.GetString(Resources.Resource.Strings.ConfirmDeleteGroup);
                else
                {
                    if (item.DashboardType == DashboardType.Sign)
                    {
                        if ((item as SignInfo).Controller.Connection.State == System.Communication.ConnectionState.Opened)
                        {
                            MsgBox.Error("Delete failed,please disconnect first.");
                            return;
                        }

                    }
                    confirm = Resources.Resource.GetString(Resources.Resource.Strings.ConfirmDeleteSign);
                }
                if (MsgBox.Confirm("Are you sure you want to delete '" + item.Name + "'?") == DialogResult.No)
                {
                    return;
                }
                if (DeleteNode(node))
                {
                    PopulateTree();
                    SetTreeImageState();
                }
                else
                {
                    MsgBox.Warning(Resources.Resource.GetString(Resources.Resource.Strings.DeleteFailed));
                }
            }
        }

        /// <summary>
        /// 删除按钮btnDelete拖拽完成事件
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnDelete_DragDrop(object sender, DragEventArgs e)
        {
            TreeListNode node = GetDragNode(e.Data);
            if (node != null)
            {
                DashboardItem item = (node.Tag) as DashboardItem;
                if (DeleteValidate(item) != "")
                {
                    MsgBox.Error(DeleteValidate(item));
                    return;
                }
                string confirm = "";
                if (item.DashboardType == DashboardType.Group)
                    confirm = Resources.Resource.GetString(Resources.Resource.Strings.ConfirmDeleteGroup);
                else
                {
                    if (item.DashboardType == DashboardType.Sign)
                    {
                        if ((item as SignInfo).Controller.Connection.State == System.Communication.ConnectionState.Opened)
                        {
                            MsgBox.Error("Delete failed,please disconnect first.");
                            btnDelete.Image = ProWrite.Resources.Resource.GetImage(ProWrite.Resources.Resource.Images.RecycleClose16);
                            return;
                        }

                    }
                    confirm = Resources.Resource.GetString(Resources.Resource.Strings.ConfirmDeleteSign);
                }
                if (MsgBox.Confirm("Are you sure you want to delete '" + item.Name + "'?") == DialogResult.No)
                {
                    SetDefaultbtn();
                    return;
                }

                if (DeleteNode(node))
                {
                    PopulateTree();
                    SetTreeImageState();
                }
            }
            SetDefaultbtn();
        }

        private void btnAdd_MouseUp(object sender, MouseEventArgs e)
        {
            this.contextMenuStrip1.Show(btnAdd.PointToScreen(e.Location));
        }

        private void newSignToolStripMenuItem_Click(object sender, EventArgs e)
        {
            ShowSignEditor(DashboardType.Sign);
        }

        private void newSignGroupToolStripMenuItem_Click(object sender, EventArgs e)
        {
            ShowSignEditor(DashboardType.Group);
        }

        private void btnDelete_Click(object sender, EventArgs e)
        {
            TreeListNode node = treeList.FocusedNode;
            if (node == null)
                return;
            DashboardItem item = (node.Tag) as DashboardItem;
            if (DeleteValidate(item) != "")
            {
                MsgBox.Error(DeleteValidate(item));
                return;
            }
            string confirm = "";
            if (item.DashboardType == DashboardType.Group)
                confirm = Resources.Resource.GetString(Resources.Resource.Strings.ConfirmDeleteGroup);
            else
            {
                if (item.DashboardType == DashboardType.Sign)
                {
                    if ((item as SignInfo).Controller.Connection.State == System.Communication.ConnectionState.Opened)
                    {
                        MsgBox.Error("Delete failed,please disconnect first.");
                        return;
                    }

                }
                confirm = Resources.Resource.GetString(Resources.Resource.Strings.ConfirmDeleteSign);
            }
            if (MsgBox.Confirm("Are you sure you want to delete '" + item.Name + "'?") == DialogResult.No)
            {
                return;
            }
            if (DeleteNode(node))
            {
                PopulateTree();
                SetTreeImageState();
            }
            else
            {
                MsgBox.Warning(Resources.Resource.GetString(Resources.Resource.Strings.DeleteFailed));
            }
        }

        /// <summary>
        /// 删除按钮btnDelete拖拽进入事件
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnDelete_DragEnter(object sender, DragEventArgs e)
        {
            TreeListNode node = GetDragNode(e.Data);
            if (node != null)
            {
                e.Effect = DragDropEffects.Move;
                // updated to get shape using resource key by Louis
                btnDelete.Image = ProWrite.Resources.Resource.GetImage(ProWrite.Resources.Resource.Images.RecycleOpen16);
            }
            else
                Cursor = Cursors.No;
        }

        /// <summary>
        /// 删除按钮btnDelete拖拽离开事件
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnDelete_DragLeave(object sender, EventArgs e)
        {
            SetDefaultbtn();
        }

        void RefreshSignToolStripMenuItem_Click(object sender, System.EventArgs e)
        {
            DashboardItem item = this.treeList.FocusedNode.Tag as DashboardItem;

            LogViewAction logAction = new LogViewAction();
            logAction.sign = item as SignInfo;
            logAction.Perform();

            GetStatusAction statusAction = new GetStatusAction();
            statusAction.sign = item as SignInfo;
            statusAction.Perform();


        }

        void showStatusSignToolStripMenuItem_Click(object sender, System.EventArgs e)
        {
            DashboardItem item = this.treeList.FocusedNode.Tag as DashboardItem;
            if (item.DashboardType == DashboardType.Sign)
            {
                GetStatus status = new GetStatus(item as SignInfo);
                status.ShowModalDialog();
            }
        }

        void showLogViewToolStripMenuItem_Click(object sender, System.EventArgs e)
        {
            DashboardItem item = treeList.FocusedNode.Tag as DashboardItem;
            if ((item as SignInfo).Controller.Connection.State == System.Communication.ConnectionState.Opened)
            {
                LogView view = new LogView();
                view.ShowModalDialog();
            }
        }
        /// <summary>
        /// 右键菜单Add to group事件
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void addGroupToolStripMenuItem_Click(object sender, EventArgs e)
        {
            SignForm frmSign = new SignForm(treeList.FocusedNode.Tag as SignInfo, true);
            SignInfo sign = treeList.FocusedNode.Tag as SignInfo;
            //SignGroupForm frmGroup = new SignGroupForm(treeList.FocusedNode.Tag as SignInfo);
            this.ParentForm.TopMost = true;
            frmSign.ShowModalDialog();
            this.ParentForm.TopMost = false;
            if (frmSign.IsRefresh)
            {
                LocalMessageBus.Send(this, new DataChangedMessage(PWDataType.Dashboard));
                PopulateTree();
                SetTreeImageState();
                treeList.FocusedNode = treeList.FindNodeByFieldValue(_.Name, sign.Name);
                LocalMessageBus.Send(this, new SelectedSignMessage(sign));
                DashboardItem itemSign = treeList.FocusedNode.Tag as DashboardItem;
                if (itemSign.DashboardType == DashboardType.Sign)
                {
                    SignInfo sign1 = itemSign as SignInfo;
                    if (sign.Controller.Connection.State == System.Communication.ConnectionState.Opened)
                    {
                        var action = new SelectedSignAction(sign1);
                        action.Perform();
                    }
                }
                else
                {
                    ActionHelper.OnDisconnected(false);
                }
                treeList.FocusedNode = treeList.FindNodeByFieldValue(_.Name, sign.Name);
            }
        }

        void removeGroupToolStripMenuItem_Click(object sender, System.EventArgs e)
        {
            SignInfo sign = treeList.FocusedNode.Tag as SignInfo;
            sign.Parent = DataGate.Project.RootGroup;
            PopulateTree();
            SetTreeImageState();
            treeList.FocusedNode = treeList.FindNodeByFieldValue(_.Name, sign.Name);
        }

        /// <summary>
        /// 右键菜单Edit事件
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void editToolStripMenuItem_Click(object sender, EventArgs e)
        {
            EditDashboardItem(false);
        }


        /// <summary>
        /// 右键菜单的newSign事件
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void newSignGroupToolStripMenuItem1_Click(object sender, EventArgs e)
        {
            ShowSignEditor(DashboardType.Group);
        }

        /// <summary>
        /// 右键菜单的Delete事件
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void deleteToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (DeleteNode())
            {
                PopulateTree();
                SetTreeImageState();
            }
        }
        #endregion

        //public override  TreeListState State
        //{
        //    get { throw new NotImplementedException(); }
        //}
    }


    #region Auxiliary class
    /// <summary>
    /// Get grag object
    /// </summary>
    public class DragObject
    {
        private string[] taskNames = new string[] { "Project", "Deliverable", "Task" };
        private int index;
        public DragObject(int index)
        {
            this.index = index;
        }
        public object DragData { get { return new object[] { taskNames[index], DateTime.Now, 0 }; } }
        public int ImageIndex { get { return index; } }
    }
    #endregion
}
