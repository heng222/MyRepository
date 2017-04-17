using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Threading;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using DevExpress.XtraEditors;
using DevExpress.XtraTreeList.Nodes;
using DirectShowLib;
using DirectShowLib.DES;
using ProWrite.Core;
using ProWrite.Resources;
using ProWrite.Entity.DES;
using ProWrite.UI.Controls.Common;
using ProWrite.DES;


namespace ProWrite.UI.Controls
{
    public partial class PlayForm : XtraForm
    {
        private VideoLayerCollection[] messages = null;
        private Play myPlay = null;
        private int curNum = 0;
        private long curLength = 0;
        private long PlayLength = 0;
        private Size videoSize = Size.Empty;
        private Oper curOper = Oper.AgainPlay;
        private int latestParentNodeId = -1;

        public int Zoom { get; set; }

        #region Events
        public PlayForm()
        {
            InitializeComponent();
            RegisterHelp();
            this.KeyPreview = true;
            this.KeyPress += new KeyPressEventHandler(PlayForm_KeyPress);
        }

        void PlayForm_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (e.KeyChar == (char)27)
            {
                this.Close();
            }

        }

        public PlayForm(VideoLayerCollection[] _messages)
            : this()
        {
            messages = _messages;
        }

        private void PlayForm_Load(object sender, EventArgs e)
        {
            if (messages != null)
            {
                imageCollection1.AddImage(Resources.Resource.GetImage(Resource.Images.MessageIcon16x16));
                imageCollection1.AddImage(Resources.Resource.GetImage(Resource.Images.PlaylistIcon16x16));
                imageCollection1.AddImage(Resources.Resource.GetImage(Resource.Images.InsertTimeSliceGroup16));
                SetPlayPanel();
                LoadList();
                StartPlay();
            }
        }

        void treeList1_DragObjectStart(object sender, DevExpress.XtraTreeList.DragObjectStartEventArgs e)
        {
            e.Allow = false;
        }

        private void RegisterHelp()
        {
            this.SetShowHelp(HelpNavigator.Topic, Resources.Resource.Helps.PlaylistsPlayer);
        }

        private void PlayForm_FormClosed(object sender, FormClosedEventArgs e)
        {
            if (myPlay != null)
            {
                curOper = Oper.StopPlay;
                myPlay.Stop();
            }
            foreach (VideoLayerCollection vd in messages)
            {
                for (int i = vd.Count - 1; i >= 0; i--)
                {
                    vd.RemoveAt(i);
                }
            }
            messages = null;
            GC.Collect();
            //Control.CheckForIllegalCrossThreadCalls = true;
        }

        private void PlayForm_Resize(object sender, EventArgs e)
        {
            SetPlayPanel();
            if (!videoSize.Equals(this.pnlPlay.Size))
            {
                videoSize = this.pnlPlay.Size;
                if (myPlay != null)
                {
                    myPlay.ResizeVideoWindow(videoSize);
                }
            }
        }

        private void btnPlay_Click(object sender, EventArgs e)
        {
            try
            {
                curOper = Oper.AgainPlay;
                if (myPlay == null)
                {
                    StartPlay();
                }
                else if (myPlay != null && myPlay.CurentState == PlayState.Run)
                {
                    myPlay.Pause();
                    SetButton(PlayState.Pause);
                }
                else if (myPlay != null && myPlay.CurentState == PlayState.Pause)
                {
                    myPlay.ContinueRun();
                    SetButton(PlayState.Run);
                }
            }
            catch
            {
                PlayCompleted(this, new EventArgs());
            }
        }

        private void btnStop_Click(object sender, EventArgs e)
        {
            try
            {
                if (myPlay != null)
                {
                    curOper = Oper.StopPlay;
                    myPlay.Stop();
                }
            }
            catch
            {
                PlayCompleted(this, new EventArgs());
            }
        }

        private void btnPrevious_Click(object sender, EventArgs e)
        {
            try
            {
                if (myPlay != null)
                {
                    curOper = Oper.PrevPlay;
                    string oldNodeParentName =
                        (treeList1.FocusedNode.GetValue("Message") as VideoLayerCollection).ParentName;
                    int oldNodeId = treeList1.FocusedNode.Id;

                    if (string.IsNullOrEmpty(oldNodeParentName))
                        treeList1.MovePrev();
                    else
                        treeList1.FocusedNode = treeList1.FindNodeByID(getPreviousNodeId(oldNodeId));

                    myPlay.Stop();
                }
            }
            catch
            {
                PlayCompleted(this, new EventArgs());
            }
            #region old code
            //try
            //{
            //    if (myPlay != null)
            //    {
            //        curOper = Oper.PrevPlay;
            //        int m = -1;

            //        if (this.gridList.Rows[curNum].Cells["Parent"].Value.ToString() != "")
            //        {
            //            for (int i = curNum; i >= 0; i--)
            //            {
            //                if (this.gridList.Rows[i].Cells["Parent"].Value != this.gridList.Rows[curNum].Cells["Parent"].Value)
            //                {
            //                    m = i;
            //                    break;
            //                }
            //            }
            //            if (m == -1)
            //                m = 0;
            //        }
            //        else
            //        {
            //            m = curNum - 1;
            //        }

            //        if (m == 0)
            //        {
            //            curNum = 1;
            //        }
            //        else
            //        {
            //            if (this.gridList.Rows[m].Cells["Parent"].Value.ToString() != "")
            //            {
            //                int n = 0;
            //                bool IsExit = false;
            //                for (n = m; n >= 0; n--)
            //                {
            //                    if (this.gridList.Rows[n].Cells["Parent"].Value != this.gridList.Rows[m].Cells["Parent"].Value)
            //                    {
            //                        IsExit = true;
            //                        break;
            //                    }
            //                }
            //                curNum = IsExit ? n + 2 : n + 1;
            //            }
            //            else
            //            {
            //                curNum = m + 1;
            //            }
            //        }

            //        myPlay.Stop();
            //    }
            //}
            //catch
            //{
            //    PlayCompleted(this, new EventArgs());
            //}
            #endregion
        }

        private void btnNext_Click(object sender, EventArgs e)
        {
            try
            {
                if (myPlay != null)
                {
                    curOper = Oper.NextPlay;
                    string oldNodeParentName =
                        (treeList1.FocusedNode.GetValue("Message") as VideoLayerCollection).ParentName;
                    int oldNodeId = treeList1.FocusedNode.Id;

                    if (string.IsNullOrEmpty(oldNodeParentName))
                    {
                        treeList1.MoveNext();
                    }
                    else
                    {
                        if (btnNext.Enabled && treeList1.FocusedNode == treeList1.FocusedNode.ParentNode.LastNode)
                            treeList1.MoveNext();
                        else
                            treeList1.FocusedNode = treeList1.FocusedNode.ParentNode.LastNode;
                        //treeList1.FocusedNode = treeList1.FindNodeByID(getNextNodeId(oldNodeId, oldNodeParentName));
                    }
                    myPlay.Stop();
                }
            }
            catch
            {
                PlayCompleted(this, new EventArgs());
            }

                #region old code
            //try
            //{
            //    if (myPlay != null)
            //    {
            //        curOper = Oper.NextPlay;
            //        if (this.gridList.Rows[curNum].Cells["Parent"].Value.ToString() != "")
            //        {
            //            for (int i = curNum; i < this.gridList.Rows.Count; i++)
            //            {
            //                if (this.gridList.Rows[i].Cells["Parent"].Value != this.gridList.Rows[curNum].Cells["Parent"].Value)
            //                {
            //                    curNum = i - 1;
            //                    break;
            //                }
            //            }
            //        }
            //        myPlay.Stop();
            //    }
            //}
            //catch
            //{
            //    PlayCompleted(this, new EventArgs());
            //}
            #endregion

        }

        private int getNextNodeId(int oldNodeId, string oldNodeParentName)
        {
            TreeListNode oldNode = treeList1.FindNodeByID(oldNodeId);
            int nodeId = oldNodeId;
            while(true)
            {
                VideoLayerCollection message =
                    treeList1.FindNodeByID(++nodeId).GetValue("Message") as VideoLayerCollection;
                if(message == null) // for the case parent node
                    break;
                if (message.ParentName != oldNodeParentName) // for the case Message
                    break;
            }
            if(nodeId == oldNodeId + 1)
                return nodeId;
            return nodeId - 1;
        }

        private void PlayEvent(object o, System.EventArgs e)
        {
            this.PlayBar.Value = this.PlayBar.Value + 1;
        }

        private int getPreviousNodeId(int oldNodeId)
        {
            if (oldNodeId == latestParentNodeId + 1)
                return latestParentNodeId - 1;
            if (oldNodeId == treeList1.FocusedNode.ParentNode.FirstNode.Id && btnPrevious.Enabled)
                return treeList1.FocusedNode.ParentNode.Id - 1;
            return treeList1.FocusedNode.ParentNode.FirstNode.Id;
        }

        private void PlayCompleted(object o, System.EventArgs e)
        {
            if (myPlay != null)
            {
                myPlay.Dispose();
                myPlay = null;
            }
            videoSize = Size.Empty;
            SetButton(PlayState.Stop);
            this.PlayBar.Value = 0;
            this.lblCurTime.Text = "00:00";
            this.pnlPlay.Refresh();
            this.lblButton.Visible = false;
            this.lblTop.Visible = false;
            this.Invalidate();
            GC.Collect();
            GC.WaitForPendingFinalizers();

            int oldNodeId = treeList1.FocusedNode.Id;

            switch(curOper)
            {
                case Oper.PrevPlay:
                case Oper.NextPlay:
                    curOper = Oper.AgainPlay;
                    StartPlay();
                    break;
                case Oper.StopPlay:
                    break;
                default:
                    if (treeList1.MoveNext().Id != oldNodeId)
                        StartPlay();
                    else
                        treeList1.MoveFirst();
                    break;

            }
            //LoadList();
            //if (curOper == Oper.PrevPlay)
            //{
            //    curOper = Oper.AgainPlay;
            //    StartPlay();
            //}
            //else if (curOper == Oper.NextPlay)
            //{
                
            //}
            //else if (treeList1.MoveNext().Id != oldNodeId && curOper != Oper.StopPlay)
            //{
            //    curOper = Oper.AgainPlay;
            //    StartPlay();
            //}

            //if (curOper == Oper.NextPlay)
            ////{
            ////    curNum++;
            ////}
            ////else if (curOper == Oper.PrevPlay)
            ////{
            ////    curNum--;
            ////}
            ////else if (curOper == Oper.StopPlay)
            ////{
            ////    curNum = this.gridList.Rows.Count;
            ////}

            ////if (curNum >= 0 && curNum < this.gridList.Rows.Count)
            ////{
            ////    this.gridList.Rows[curNum].Selected = true;
            ////    curOper = Oper.NextPlay;
            ////    StartPlay();
            ////}
            ////else if (curNum == this.gridList.Rows.Count)
            ////{
            ////    curNum = 0;
            ////    this.gridList.Rows[0].Selected = true;
            ////}

        #region old code
            //if (myPlay != null)
            //{
            //    myPlay.Dispose();
            //    myPlay = null;
            //}
            //videoSize = Size.Empty;
            //SetButton(PlayState.Stop);
            //this.PlayBar.Value = 0;
            //this.lblCurTime.Text = "00:00";
            //this.pnlPlay.Refresh();
            //this.lblButton.Visible = false;
            //this.lblTop.Visible = false;
            //this.Invalidate();
            //GC.Collect();
            //GC.WaitForPendingFinalizers();
            //if (curOper == Oper.NextPlay)
            //{
            //    curNum++;
            //}
            //else if (curOper == Oper.PrevPlay)
            //{
            //    curNum--;
            //}
            //else if (curOper == Oper.StopPlay)
            //{
            //    curNum = this.gridList.Rows.Count;
            //}

            //if (curNum >= 0 && curNum < this.gridList.Rows.Count)
            //{
            //    this.gridList.Rows[curNum].Selected = true;
            //    curOper = Oper.NextPlay;
            //    StartPlay();
            //}
            //else if (curNum == this.gridList.Rows.Count)
            //{
            //    curNum = 0;
            //    this.gridList.Rows[0].Selected = true;
            //}
        #endregion

        }
        #endregion

        #region Methods

        private void LoadList()
        {
            long total = 0;
            int nodeId = -1;
            treeList1.BeginUnboundLoad();

            foreach (VideoLayerCollection item in messages)
            {
                TreeListNode node;
                if (item.IsNewStart)
                    nodeId = -1;
                if(!string.IsNullOrEmpty(item.ParentName))
                {
                    TreeListNode parentNode = treeList1.FindNodeByID(nodeId);
                    if ( parentNode == null)
                    {
                        parentNode = treeList1.AppendNode(new object[] { item.ParentName, "", null }, null);
                        //parentNode.HasChildren = true;
                        nodeId = parentNode.Id;
                        SetNodeImage(parentNode, item.GroupType);
                    }
                    node = treeList1.AppendNode(new object[] { item.Name, Common.CommonHelper.FormatTimeToMinute(item.PlayLength), item }, parentNode);
                }
                else
                {
                    node = treeList1.AppendNode(new object[] { item.Name, Common.CommonHelper.FormatTimeToMinute(item.PlayLength), item }, null);
                }
                node.HasChildren = true;
                SetNodeImage(node, LibraryType.Message);
                total += item.PlayLength;
            }
            this.lblTotalList.Text = this.lblTotalList.Text + Common.CommonHelper.FormatTimeToMinute(total);
            treeList1.ExpandAll();
            treeList1.EndUnboundLoad();


            //total = 0;
            //this.gridList.AutoGenerateColumns = false;
            //this.gridList.DataSource = messages;
            //for (int i = 0; i < this.gridList.Rows.Count; i++)
            //{
            //    this.gridList.Rows[i].Cells["seq"].Value = (i + 1).ToString();
            //    this.gridList.Rows[i].Cells["length"].Value = Common.CommonHelper.FormatTimeToMinute(messages[i].PlayLength);
            //    total += messages[i].PlayLength;
            //}
            //this.lblTotalList.Text = this.lblTotalList.Text + Common.CommonHelper.FormatTimeToMinute(total);
        }

        private void SetNodeImage(TreeListNode node, LibraryType? message)
        {
            switch (message)
            {
                case null:
                case LibraryType.Message:
                    node.StateImageIndex = 0;
                    break;
                case LibraryType.Playlist:
                    node.StateImageIndex = 1;
                    break;
                case LibraryType.TimeSliceGroup:
                    node.StateImageIndex = 2;
                    break;
            }
        }

        public void SetPlayTitle(PlayMode mode,string name)
        {
            if (mode == PlayMode.Editor)
            {
                this.Text = "Message Player";
            }
            else
            {
                this.Text = "Playlist Player";
            }
            this.lblTitle.Text = name;
        }

        private void SetPlayPanel()
        {
            if (videoSize != Size.Empty)
            {
                if (videoSize.Width > videoSize.Height)
                {
                    this.pnlPlay.Width = this.pnlParent.Width;
                    this.pnlPlay.Height = this.pnlPlay.Width * videoSize.Height / videoSize.Width;
                }
                else
                {
                    this.pnlPlay.Height = this.pnlParent.Height;
                    this.pnlPlay.Width = this.pnlPlay.Height * videoSize.Width / videoSize.Height;
                }
                this.pnlPlay.Left = (this.pnlParent.Width - this.pnlPlay.Width) / 2;
                this.pnlPlay.Top = (this.pnlParent.Height - this.pnlPlay.Height) / 2;
            }
            this.lblTop.Top = this.pnlPlay.Top - 1;
            this.lblButton.Top = this.pnlPlay.Top + this.pnlPlay.Height;
            this.lblTop.Width = this.pnlParent.Width;
            this.lblButton.Width = this.pnlParent.Width;
        }

        private void SetPlayBar(int min,int max)
        {
            this.PlayBar.Minimum = min * (int)DESConsts.FPS;
            this.PlayBar.Maximum = max * (int)DESConsts.FPS;
            this.PlayBar.Value = 0;
        }

        private void SetButton(PlayState curState)
        {
            if (curState == PlayState.Run)
            {
                btnPlay.NormalImage = Resource.GetImage(Resource.Images.PauseNormal);
                btnPlay.HoverImage = Resource.GetImage(Resource.Images.PauseHover);
                btnPlay.PushedImage = Resource.GetImage(Resource.Images.PausePush);
                btnPlay.DisabledImage = Resource.GetImage(Resource.Images.PauseDisable);
                btnPlay.Enabled = true;
                btnStop.Enabled = true;
                this.btnToolTip.SetToolTip(this.btnPlay, "Pause");
                SetPreviousNextBtns();
            }
            else if (curState == PlayState.Pause)
            {
                btnPlay.NormalImage = Resource.GetImage(Resource.Images.PlayNormal);
                btnPlay.HoverImage = Resource.GetImage(Resource.Images.PlayHover);
                btnPlay.PushedImage = Resource.GetImage(Resource.Images.PlayPush);
                btnPlay.DisabledImage = Resource.GetImage(Resource.Images.PlayDisable);
                btnPlay.Enabled = true;
                btnStop.Enabled = true;
                btnPrevious.Enabled = false;
                btnNext.Enabled = false;
                this.btnToolTip.SetToolTip(this.btnPlay, "Play");
            }
            else if (curState == PlayState.Stop)
            {
                btnPlay.NormalImage = Resource.GetImage(Resource.Images.PlayNormal);
                btnPlay.HoverImage = Resource.GetImage(Resource.Images.PlayHover);
                btnPlay.PushedImage = Resource.GetImage(Resource.Images.PlayPush);
                btnPlay.DisabledImage = Resource.GetImage(Resource.Images.PlayDisable);
                btnPlay.Enabled = true;
                btnStop.Enabled = false;
                btnPrevious.Enabled = false;
                btnNext.Enabled = false;
                this.btnToolTip.SetToolTip(this.btnPlay, "Play");
            }

            if (messages!=null && messages.Length <= 1)
            {
                btnPrevious.Enabled = false;
                btnNext.Enabled = false;
            }
        }

        private void StartPlay()
        {
            Control.CheckForIllegalCrossThreadCalls = false;
            VideoLayerCollection message;
            while ((message = (VideoLayerCollection)treeList1.FocusedNode.GetValue("Message")) == null)
            {
                latestParentNodeId = treeList1.FocusedNode.Id;
                treeList1.MoveNext();
            }
            if (myPlay == null)
            {
                SetPlayBar(0, (int)message.PlayLength);
                this.lblCurName.Text = message.Name;
                this.lblTotalTime.Text = CommonHelper.FormatTimeToMinute(message.PlayLength);
                videoSize = message.VideoSize;
                pnlPlay.Size = videoSize;
                myPlay = new Play(message, new DESVideoCallBack((int)(curLength / DESConsts.UNITS), this.PlayBar, this.lblCurTime), this.pnlPlay);
                myPlay.PlayCompleted += new EventHandler(PlayCompleted);
                myPlay.Run();
                this.lblButton.Visible = true;
                this.lblTop.Visible = true;
                SetPlayPanel();
                SetButton(PlayState.Run);

                if (!videoSize.Equals(this.pnlPlay.Size))
                {
                    videoSize = this.pnlPlay.Size;
                    myPlay.ResizeVideoWindow(videoSize);
                }

                if (!videoSize.Equals(this.pnlPlay.Size))
                {
                    videoSize = this.pnlPlay.Size;
                    myPlay.ResizeVideoWindow(videoSize);
                }

            }
            ////int msgCount = messages.Length;
            //Control.CheckForIllegalCrossThreadCalls = false;
            ////curNum = this.treeList1.get
            //curNum = this.gridList.SelectedRows.Count > 0 ? this.gridList.SelectedRows[0].Index : 0;
            //curLength = 0;
            //if (messages[curNum].PlayLength <= 0)
            //{
            //    curNum++;
            //    if (curNum >= this.gridList.Rows.Count)
            //        return;
            //    this.gridList.Rows[curNum].Selected = true;
            //    StartPlay();
            //}

            //if (myPlay == null)
            //{
            //    SetPlayBar(0, (int)messages[curNum].PlayLength);
            //    this.gridList.Rows[curNum].Selected = true;
            //    this.lblCurName.Text = this.gridList.SelectedRows[0].Cells["Name"].Value.ToString();
            //    this.lblTotalTime.Text = this.gridList.SelectedRows[0].Cells["length"].Value.ToString();
            //    videoSize = messages[curNum].VideoSize;
            //    pnlPlay.Size = videoSize;
            //    myPlay = new Play(messages[curNum], new DESVideoCallBack((int)(curLength / DESConsts.UNITS), this.PlayBar, this.lblCurTime), this.pnlPlay);
            //    myPlay.PlayCompleted += new EventHandler(PlayCompleted);
            //    myPlay.Run();
            //    this.lblButton.Visible = true;
            //    this.lblTop.Visible = true;
            //    PlayLength = Common.CommonHelper.FormatTime(messages[curNum].PlayLength);
            //    SetPlayPanel();
            //    SetButton(PlayState.Run);

            //    if (!videoSize.Equals(this.pnlPlay.Size))
            //    {
            //        videoSize = this.pnlPlay.Size;
            //        myPlay.ResizeVideoWindow(videoSize);
            //    }

            //    if (msgCount > 1 && curNum == 0)
            //    {
            //        btnPrevious.Enabled = false;
            //        btnNext.Enabled = true;
            //    }
            //    else if (msgCount > 1 && curNum == msgCount - 1)
            //    {
            //        btnPrevious.Enabled = true;
            //        btnNext.Enabled = false;
            //    }
            //    else if (msgCount > 1)
            //    {
            //        btnPrevious.Enabled = true;
            //        btnNext.Enabled = true;
            //    }
            //}

            #region grid old code
            //int msgCount = messages.Length;
            //Control.CheckForIllegalCrossThreadCalls = false;
            //curNum = this.gridList.SelectedRows.Count > 0 ? this.gridList.SelectedRows[0].Index : 0;
            //curLength = 0;
            //if (messages[curNum].PlayLength <= 0)
            //{
            //    curNum++;
            //    if (curNum >= this.gridList.Rows.Count)
            //        return;
            //    this.gridList.Rows[curNum].Selected = true;
            //    StartPlay();
            //}

            //if (myPlay == null)
            //{
            //    SetPlayBar(0, (int)messages[curNum].PlayLength);
            //    this.gridList.Rows[curNum].Selected = true;
            //    this.lblCurName.Text = this.gridList.SelectedRows[0].Cells["Name"].Value.ToString();
            //    this.lblTotalTime.Text = this.gridList.SelectedRows[0].Cells["length"].Value.ToString();
            //    videoSize = messages[curNum].VideoSize;
            //    pnlPlay.Size = videoSize;
            //    myPlay = new Play(messages[curNum], new DESVideoCallBack((int)(curLength / DESConsts.UNITS), this.PlayBar, this.lblCurTime), this.pnlPlay);
            //    myPlay.PlayCompleted += new EventHandler(PlayCompleted);
            //    myPlay.Run();
            //    this.lblButton.Visible = true;
            //    this.lblTop.Visible = true;
            //    PlayLength = Common.CommonHelper.FormatTime(messages[curNum].PlayLength);
            //    SetPlayPanel();
            //    SetButton(PlayState.Run);

            //    if (!videoSize.Equals(this.pnlPlay.Size))
            //    {
            //        videoSize = this.pnlPlay.Size;
            //        myPlay.ResizeVideoWindow(videoSize);
            //    }

            //    if (msgCount > 1 && curNum == 0)
            //    {
            //        btnPrevious.Enabled = false;
            //        btnNext.Enabled = true;
            //    }
            //    else if (msgCount > 1 && curNum == msgCount - 1)
            //    {
            //        btnPrevious.Enabled = true;
            //        btnNext.Enabled = false;
            //    }
            //    else if (msgCount > 1)
            //    {
            //        btnPrevious.Enabled = true;
            //        btnNext.Enabled = true;
            //    }
            //}

            #endregion


        }

        /// <summary>
        ///  Current Oper Type
        /// </summary>
        private enum Oper
        {
            PrevPlay,
            NextPlay,
            AgainPlay,
            StopPlay
        }
        #endregion

        private void treeList1_BeforeFocusNode(object sender, DevExpress.XtraTreeList.BeforeFocusNodeEventArgs e)
        {
            if (e.Node.GetValue("Message") == null)
            {
                latestParentNodeId = e.Node.Id;
                if (curOper == Oper.PrevPlay)
                {
                    treeList1.MovePrev();
                }
                else
                    treeList1.MoveNext();
            }
        }

        private void treeList1_AfterFocusNode(object sender, DevExpress.XtraTreeList.NodeEventArgs e)
        {
            SetPreviousNextBtns();
        }

        private void SetPreviousNextBtns()
        {
            if (curOper == Oper.StopPlay)
            {
                btnPrevious.Enabled = false;
                btnNext.Enabled = false;
            }
            else
            {
                btnPrevious.Enabled =
                    treeList1.FocusedNode != treeList1.Nodes.FirstNode
                    && !(treeList1.Nodes[0].GetValue("Message") == null
                         && treeList1.FocusedNode.Id == 1);

                btnNext.Enabled = EnableNextBtn();
            }
        }

        private bool EnableNextBtn()
        {
            if(treeList1.FocusedNode.ParentNode == null)
            {
                return treeList1.Nodes.IndexOf(treeList1.FocusedNode) != treeList1.Nodes.Count - 1;
            }
            return !(treeList1.FocusedNode.Id == treeList1.FocusedNode.ParentNode.LastNode.Id && treeList1.Nodes.IndexOf(treeList1.FocusedNode.ParentNode) == treeList1.Nodes.Count - 1);
            //return !(treeList1.FocusedNode.Id == treeList1.FocusedNode.ParentNode.LastNode.Id && treeList1.FocusedNode.ParentNode.Id == treeList1.Nodes.Count - 1);
        }
    }
}
