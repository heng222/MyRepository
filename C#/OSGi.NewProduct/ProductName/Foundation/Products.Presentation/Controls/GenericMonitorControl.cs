﻿using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using Acl.Collections;
using Acl.Controls;
using Products.Infrastructure.Protocol.Framework;

namespace Products.Presentation
{
    /// <summary>
    /// 外部子系统通用监视控件
    /// </summary>
    public partial class GenericMonitorControl : UserControl
    {
        /// <summary>
        /// Definition of Tag of Treeview's node.
        /// </summary>
        private class TreeNodeTag
        {
            /// <summary>
            /// The stream.
            /// </summary>
            public byte[] Stream { get; set; }
            /// <summary>
            /// The stream parser.
            /// </summary>
            public IStreamFrameParser<byte> Parser { get; set; }
            /// <summary>
            /// Data descriptor.
            /// </summary>
            public object DataDescriptor { get; set; }

            /// <summary>
            /// 
            /// </summary>
            /// <param name="stream"></param>
            /// <param name="parser"></param>
            public TreeNodeTag(byte[] stream, IStreamFrameParser<byte> parser = null)
            {
                if (stream == null) throw new ArgumentNullException();

                this.Stream = stream;
                this.Parser = parser;
            }
        }

        /// <summary>
        /// Incoming data event arguments.
        /// </summary>
        private class IncomingData
        {
            public string RemoteDeviceID { get; set; }
            public byte[] Stream { get; set; }
            public IStreamFrameParser<byte> Parser { get; set; }
            public DateTime CreationTime { get; private set; }
            public object DataDescriptor { get; set; }

            public IncomingData(string remoteDeviceID, byte[] stream, IStreamFrameParser<byte> parser)
            {
                this.CreationTime = DateTime.Now;

                this.RemoteDeviceID = remoteDeviceID;
                this.Stream = stream;
                this.Parser = parser;
            }
        }

        /// <summary>
        /// Outgoing data event arguments.
        /// </summary>
        private class OutgoingData
        {
            public string RemoteDeviceID { get; set; }
            public byte[] Stream { get; set; }
            public IStreamFrameParser<byte> Parser { get; set; }
            public string ToolTipText { get; set; }
            public DateTime CreationTime { get; private set; }
            public object DataDescriptor { get; set; }

            public OutgoingData(string remoteDeviceID, byte[] stream, IStreamFrameParser<byte> parser, string toolTipText)
            {
                this.CreationTime = DateTime.Now;

                this.RemoteDeviceID = remoteDeviceID;
                this.Stream = stream;
                this.Parser = parser;
                this.ToolTipText = toolTipText;
            }
        }

        #region "Field"
        /// <summary>
        /// The input stream frame default parser.
        /// </summary>
        private IStreamFrameParser<byte> _inputStreamDefaultParser;
        /// <summary>
        /// The output stream frame default parser.
        /// </summary>
        private IStreamFrameParser<byte> _outputStreamDefaultParser;

        /// <summary>
        /// Product cache for incoming data.
        /// </summary>
        private ProductCache<IncomingData> _inputProductCache;
        /// <summary>
        /// Product cache for outgoing data.
        /// </summary>
        private ProductCache<OutgoingData> _outputProductCache;

        /// <summary>
        /// key = Remote Device ID.
        /// value = Remote Device state.(true for connected)
        /// </summary>
        private Dictionary<string, bool> _remoteDeviceState = new Dictionary<string, bool>();

        #endregion

        #region "Constructor"
        /// <summary>
        /// 构造函数
        /// </summary>
        /// <param name="defaultInputStreamParser">输入流默认解析器</param>
        /// <param name="defaultOutputStreamParser">输出流默认解析器</param>
        /// <param name="remoteDeviceCodes">需要监视的设备编号集合。</param>
        /// <param name="timeout">事件的刷新周期，0表示立即刷新。</param>
        public GenericMonitorControl(
            IStreamFrameParser<byte> defaultInputStreamParser = null,
            IStreamFrameParser<byte> defaultOutputStreamParser = null,
            IEnumerable<string> remoteDeviceCodes = null,
            uint timeout = 500)
        {
            InitializeComponent();

            this.CreateHandle();
            
            _inputStreamDefaultParser = defaultInputStreamParser;
            _outputStreamDefaultParser = defaultOutputStreamParser;

            this.MaxSummaryCount = 100;

            // 更新UI
            this.InitializeUI();

            // 初始化需要监控的远程设备编号。
            if (remoteDeviceCodes != null)
            {
                remoteDeviceCodes.ToList().ForEach(p => this.SetConnectionState(p, false));
            }

            // 创建缓存池。
            CreateProductCache(timeout);
        }
        #endregion

        #region "properites"
        ///// <summary>
        ///// 获取/设置一个值，用于表明是否实时显示协议帧。
        ///// </summary>
        //public bool AliveFrameEnabled
        //{
        //    get { return _aliveFrameEnabled; }
        //    set
        //    {
        //        _aliveFrameEnabled = value;
        //        this.enableAliveDataToolStripMenuItem.Checked = value;
        //    }
        //}
        /// <summary>
        /// 是否显示输入流。
        /// </summary>
        public bool IncomingStreamVisable
        {
            get { return _IncomingStreamVisable; }
            set
            {
                _IncomingStreamVisable = value;
                this.chkInputStreamVisable.Checked = value;
            }
        }
        private bool _IncomingStreamVisable = false;

        /// <summary>
        /// 是否显示输出流。
        /// </summary>
        public bool OutgoingStreamVisable
        {
            get { return _OutgoingStreamVisable; }
            set
            {
                _OutgoingStreamVisable = value;
                this.chkOutputStreamVisable.Checked = value;
            }
        }
        private bool _OutgoingStreamVisable = false;

        /// <summary>
        /// 获取/设置通信日志的路径。
        /// </summary>
        public string CommLogPath { get; set; }

        /// <summary>
        /// 获取/设置显示的最大消息个数。默认值100。
        /// </summary>
        public ushort MaxSummaryCount { get; set; }

        /// <summary>
        /// 获取上下文菜单的所有项
        /// </summary>
        public ToolStripItemCollection ContextMenuItems
        {
            get { return this.contextMenuTreeviewSummay.Items; }
        }
        #endregion

        #region "public methods"
        /// <summary>
        /// 设置连接状态
        /// </summary>
        /// <param name="remoteDeviceID">设备ID</param>
        /// <param name="connected">设备连接状态</param>
        public void SetConnectionState(string remoteDeviceID, bool connected)
        {
            try
            {
                this.BeginInvoke(() =>
                {
                    // 更新数据
                    if (!_remoteDeviceState.ContainsKey(remoteDeviceID))
                    {
                        _remoteDeviceState.Add(remoteDeviceID, connected);

                        cbxRemoteIDs.Items.Add(remoteDeviceID);
                    }
                    else
                    {
                        _remoteDeviceState[remoteDeviceID] = connected;

                        // 如果当前选择项与指定的参数一致，则更新当前的设备状态。
                        if (cbxRemoteIDs.Text == remoteDeviceID)
                        {
                            this.UpdateConnectionImage(remoteDeviceID);
                        }
                    }

                    if (cbxRemoteIDs.Items.Count == 1)
                    {
                        cbxRemoteIDs.SelectedIndex = 0;
                    }
                });
            }
            catch (System.Exception /*ex*/)
            {            	
            }
        }

        /// <summary>
        /// 添加一条接收到的流
        /// </summary>
        /// <param name="remoteDeviceID">远程设备编号</param>
        /// <param name="stream">数据流</param>
        /// <param name="parser">数据流对应的解析器</param>
        /// <param name="dataDescriptor">数据描述器</param>
        public void AddIncomingStream(string remoteDeviceID, byte[] stream, IStreamFrameParser<byte> parser = null, object dataDescriptor = null)
        {
            _inputProductCache.AddProduct(new IncomingData(remoteDeviceID, stream, parser) { DataDescriptor = dataDescriptor });
        }

        /// <summary>
        /// 添加一条发送出去的字节流
        /// </summary>
        /// <param name="remoteDeviceID">远程设备编号</param>
        /// <param name="stream">数据流</param>
        /// <param name="parser">数据流对应的解析器</param>
        /// <param name="toolTipText">当鼠标悬停在TreeNode之上时显示的文字。</param>
        /// <param name="dataDescriptor">数据描述器</param>
        public void AddOutgoingStream(string remoteDeviceID, byte[] stream, IStreamFrameParser<byte> parser = null,
            string toolTipText = null, object dataDescriptor = null)
        {
            _outputProductCache.AddProduct(new OutgoingData(remoteDeviceID, stream, parser, toolTipText) { DataDescriptor = dataDescriptor });
        }

        /// <summary>
        /// 复位到初始状态
        /// </summary>
        public void Reset()
        {
            try
            {
                this.cbxRemoteIDs.Items.Clear();
                this.tvMessageSummary.Nodes.Clear();
                this.txtDetail.Clear();
            }
            catch (System.Exception /*ex*/)
            {            	
            }
        }
        #endregion

        #region "private method"

        private void InitializeUI()
        {
            this.splitContainer3.IsSplitterFixed = true;
            //this.splitContainer4.IsSplitterFixed = true;
            this.splitContainer5.IsSplitterFixed = true;
            this.pictureBox1.BorderStyle = BorderStyle.None;
            this.txtDetail.Dock = DockStyle.Fill;
            this.tvMessageSummary.Dock = DockStyle.Fill;
            this.pictureBox1.Image = imgListConnectionState.Images["DeviceOffline"];
            this.cbxConfidtion2.SelectedIndex = 0;
            this.cbxConfidtion3.SelectedIndex = 0;
            this.cmbCondition1Operator.SelectedIndex = 0;
            this.cmbCondition2Operator.SelectedIndex = 0;
            this.cmbCondition3Operator.SelectedIndex = 0; 

            this.RefresshFilterPanel();
        }
                
        private void UpdateConnectionImage(string deviceID)
        {
            try
            {
                bool connected = _remoteDeviceState[deviceID];

                this.BeginInvoke(() =>
                {
                    if (connected)
                    {
                        this.pictureBox1.Image = imgListConnectionState.Images["DeviceOnline"];
                    }
                    else
                    {
                        this.pictureBox1.Image = imgListConnectionState.Images["DeviceOffline"];
                    }
                });
            }
            catch (System.Exception /*ex*/)
            {
                this.pictureBox1.Image = this.pictureBox1.ErrorImage;

                throw;
            }
        }

        /// <summary>
        /// 刷新过滤界面
        /// </summary>
        private void RefresshFilterPanel()
        {
            this.nudCondition1Index.Enabled = this.chkConditionEnabled.Checked;
            this.cmbCondition1Operator.Enabled = this.chkConditionEnabled.Checked;
            this.nudCondition1Value.Enabled = this.chkConditionEnabled.Checked;
            this.cbxConfidtion2.Enabled = this.chkConditionEnabled.Checked;
            this.cbxConfidtion3.Enabled = this.chkConditionEnabled.Checked;

            this.nudCondition2Index.Enabled = this.chkConditionEnabled.Checked && (this.cbxConfidtion2.SelectedIndex != 0);
            this.cmbCondition2Operator.Enabled = this.chkConditionEnabled.Checked && (this.cbxConfidtion2.SelectedIndex != 0);
            this.nudCondition2Value.Enabled = this.chkConditionEnabled.Checked && (this.cbxConfidtion2.SelectedIndex != 0);

            this.nudCondition3Index.Enabled = this.chkConditionEnabled.Checked && (this.cbxConfidtion3.SelectedIndex != 0);
            this.cmbCondition3Operator.Enabled = this.chkConditionEnabled.Checked && (this.cbxConfidtion3.SelectedIndex != 0);
            this.nudCondition3Value.Enabled = this.chkConditionEnabled.Checked && (this.cbxConfidtion3.SelectedIndex != 0);
        }

        /// <summary>
        /// 
        /// </summary>
        /// <returns>true表示过滤指定的用户数据（显示），false表示不过滤(不显示)。</returns>
        private bool FilterStream(byte[] userData)
        {
            try
            {
                if (!chkConditionEnabled.Checked)
                {
                    return true;
                }

                int index = 1; // 表示第几个字节。
                byte value = 0; // 表示过滤的值。
                bool result = true;

                // 条件1
                index = Convert.ToInt32(nudCondition1Index.Value);
                value = Convert.ToByte(nudCondition1Value.Value);

                if (cmbCondition1Operator.SelectedIndex == 0)
                {
                    result = (value == userData[index - 1]);
                }
                else
                {
                    result = (value != userData[index - 1]);
                }

                // 条件2
                int condition2 = cbxConfidtion2.SelectedIndex; // “且”/“或”
                if (condition2 != 0)
                {
                    index = Convert.ToInt32(nudCondition2Index.Value);
                    value = Convert.ToByte(nudCondition2Value.Value);

                    bool filtered2 = true;
                    if (cmbCondition2Operator.SelectedIndex == 0)
                    {
                        filtered2 = (value == userData[index - 1]);
                    }
                    else
                    {
                        filtered2 = (value != userData[index - 1]);
                    }

                    if (condition2 == 1)
                    {
                        result = result && filtered2;
                    }
                    else
                    {
                        result = result || filtered2;
                    }
                }

                // 条件3
                int condition3 = cbxConfidtion3.SelectedIndex; // “且”/“或”
                if (condition3 != 0)
                {
                    index = Convert.ToInt32(nudCondition3Index.Value);
                    value = Convert.ToByte(nudCondition3Value.Value);

                    bool filtered3 = true;
                    if (cmbCondition3Operator.SelectedIndex == 0)
                    {
                        filtered3 = (value == userData[index - 1]);
                    }
                    else
                    {
                        filtered3 = (value != userData[index - 1]);
                    }

                    if (condition3 == 1)
                    {
                        result = result && filtered3;
                    }
                    else
                    {
                        result = result || filtered3;
                    }
                }

                return result;
            }
            catch (System.Exception /*ex*/)
            {
                return true;
            }
        }

        /// <summary>
        /// 显示当前选中节点的信息。
        /// </summary>
        private void ShowSelectedInfo(TreeNodeTag tag)
        {
            if (tag == null)
            {
                throw new ArgumentNullException();
            }

            // 清空原内容
            txtDetail.Text = "";

            // 取出上下文
            var stream = tag.Stream;

            // 构建流的原始内容
            var streamContent = new StringBuilder(256);
            if (tag.DataDescriptor != null)
            {
                streamContent.AppendFormat("{0} \r\n", tag.DataDescriptor);
            }
            else
            {
                streamContent.Append("原始字节流：\r\n");
                foreach (var item in stream)
                {
                    streamContent.AppendFormat("{0:X2} ", item);
                }
            }

            // 解析流
            if (tag.Parser != null)
            {
                string msg;
                try
                {
                    msg = tag.Parser.Parse(stream, 0).ToString();
                }
                catch (System.Exception ex)
                {
                    msg = ex.ToString();
                }

                streamContent.AppendFormat("\r\n\r\n解析后：\r\n{0}", msg);
            }

            txtDetail.Text = streamContent.ToString();
        }

        private void CreateProductCache(uint timeout)
        {
            _inputProductCache = new ProductCache<IncomingData>(timeout);
            _inputProductCache.ThreadName = "GenericMonitorControl输入流缓冲池线程";
            _inputProductCache.ProductCreated += OnIncomingCacheProductCreated;
            _inputProductCache.Open();

            _outputProductCache = new ProductCache<OutgoingData>(timeout);
            _outputProductCache.ThreadName = "GenericMonitorControl输出流缓冲池线程";
            _outputProductCache.ProductCreated += OnOutgoingCacheProductCreated;
            _outputProductCache.Open();
        }

        private void OnIncomingCacheProductCreated(object sender, ProductCreatedEventArgs<IncomingData> e)
        {
            bool flag = false;

            try
            {
                flag = this.IncomingStreamVisable && this.IsHandleCreated;

                //if (flag)
                //{
                //    this.Invoke(new Action(() => this.tvMessageSummary.BeginUpdate()));
                //}

                foreach (var data in e.Products)
                {
                    // 如果RemoteDevice中没有包含此ID，则添加。
                    if (!_remoteDeviceState.ContainsKey(data.RemoteDeviceID))
                    {
                        _remoteDeviceState.Add(data.RemoteDeviceID, false);
                        this.Invoke(() =>cbxRemoteIDs.Items.Add(data.RemoteDeviceID));
                    }

                    if (flag)
                    {
                        this.Invoke(() => this.ShowIncomingStream(data));
                    }
                }
            }
            catch (System.Exception /*ex*/)
            {
            }
            //finally
            //{
            //    try
            //    {
            //        if (flag)
            //        {
            //            this.Invoke(new Action(() =>this.tvMessageSummary.EndUpdate()));
            //        }
            //    }
            //    catch (System.Exception /*ex*/)
            //    {                	
            //    }
            //}
        }

        private void OnOutgoingCacheProductCreated(object sender, ProductCreatedEventArgs<OutgoingData> e)
        {
            bool flag = false;

            try
            {
                flag = this.OutgoingStreamVisable && this.IsHandleCreated;

                //if (flag)
                //{
                //    this.Invoke(() => this.tvMessageSummary.BeginUpdate());
                //}

                foreach (var data in e.Products)
                {
                    // 如果RemoteDevice中没有包含此ID，则添加。
                    if (!_remoteDeviceState.ContainsKey(data.RemoteDeviceID))
                    {
                        _remoteDeviceState.Add(data.RemoteDeviceID, false);
                        this.Invoke(() => cbxRemoteIDs.Items.Add(data.RemoteDeviceID));
                    }

                    if (flag)
                    {
                        this.Invoke(() => this.ShowOutgoingStream(data));
                    }
                }
            }
            catch (System.Exception /*ex*/)
            {
            }
            //finally
            //{
            //    try
            //    {
            //        if (flag)
            //        {
            //            this.Invoke(new Action(() => this.tvMessageSummary.EndUpdate()));
            //        }
            //    }
            //    catch (System.Exception /*ex*/)
            //    {
            //    }
            //}
        }

        private void ShowIncomingStream(IncomingData theData)
        {
            try
            {
                string remoteDeviceID = theData.RemoteDeviceID;
                byte[] stream = theData.Stream;
                IStreamFrameParser<byte> parser = theData.Parser;

                if (this.IncomingStreamVisable
                    && this.cbxRemoteIDs.Text == remoteDeviceID
                    && this.FilterStream(stream))
                {
                    // clear 
                    if (tvMessageSummary.Nodes.Count > this.MaxSummaryCount)
                    {
                        tvMessageSummary.Nodes.RemoveAt(0);
                    }

                    // 如果没有指定解析器，则使用默认的解析器。
                    if (parser == null) parser = _inputStreamDefaultParser;

                    // Create a node
                    TreeNode node = new TreeNode();
                    node.Tag = new TreeNodeTag(stream, parser) { DataDescriptor = theData.DataDescriptor };                    
                    node.Text = string.Format("{0}, {1}", remoteDeviceID, theData.CreationTime.ToString("yyyy-MM-dd HH:mm:ss.fff"));
                    node.ImageKey = "InputStream";
                    node.SelectedImageKey = "InputStream_Selected";

                    // Add Node
                    tvMessageSummary.Nodes.Add(node);
                }
            }
            catch (System.Exception ex)
            {
                this.txtDetail.Text = ex.ToString();
            }
        }
        
        private void ShowOutgoingStream(OutgoingData theData)
        {
            try
            {
                string remoteDeviceID = theData.RemoteDeviceID;
                byte[] stream = theData.Stream;
                IStreamFrameParser<byte> parser = theData.Parser;
                string toolTipText = theData.ToolTipText;

                if (this.OutgoingStreamVisable
                    && this.cbxRemoteIDs.Text == remoteDeviceID
                    && this.FilterStream(stream))
                {
                    // clear 
                    if (tvMessageSummary.Nodes.Count > this.MaxSummaryCount)
                    {
                        tvMessageSummary.Nodes.RemoveAt(0);
                    }

                    // 如果没有指定解析器，则使用默认的解析器。
                    if (parser == null) parser = _outputStreamDefaultParser;

                    // Create a node
                    TreeNode node = new TreeNode();
                    node.Tag = new TreeNodeTag(stream, parser) { DataDescriptor = theData.DataDescriptor };   
                    node.Text = string.Format("{0}, {1}", remoteDeviceID, theData.CreationTime.ToString("yyyy-MM-dd HH:mm:ss.fff"));
                    node.ImageKey = "OutputStream";
                    node.SelectedImageKey = "outputStream_Selected";
                    node.ToolTipText = toolTipText;
                    node.ForeColor = Color.Blue;

                    // Add Node
                    tvMessageSummary.Nodes.Add(node);
                }
            }
            catch (System.Exception ex)
            {
                this.txtDetail.Text = ex.ToString();
            }

        }
        #endregion


        #region "控件事件"
        /// <summary>
        /// 远程设备ID选择项发生变化
        /// </summary>
        private void cbxRemoteIDs_SelectedIndexChanged(object sender, EventArgs e)
        {
            try
            {
                UpdateConnectionImage(cbxRemoteIDs.Text);

                this.tvMessageSummary.Nodes.Clear();
            }
            catch (System.Exception ex)
            {
                MessageBox.Show(ex.Message, "错误", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        /// <summary>
        /// 状态树节点单击事件
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void tvMessageSummary_NodeMouseClick(object sender, TreeNodeMouseClickEventArgs e)
        {
            try
            {
                // 仅当鼠标点击才会响应，键盘的上下键操作不会响应。
            }
            catch (System.Exception ex)
            {
                txtDetail.Text += ex.ToString();
            }
        }

        /// <summary>
        /// tvSummay树形控件的选择事件
        /// </summary>
        private void tvMessageSummary_AfterSelect(object sender, TreeViewEventArgs e)
        {
            try
            {
                if (this.chkSyncRefresh.Checked)
                {
                    this.ShowSelectedInfo(e.Node.Tag as TreeNodeTag);
                }
            }
            catch (System.Exception ex)
            {
                txtDetail.Text += ex.ToString();
            }
        }

        private void chkInputStreamVisable_CheckedChanged(object sender, EventArgs e)
        {
            try
            {
                this._IncomingStreamVisable = this.chkInputStreamVisable.Checked;
            }
            catch (System.Exception ex)
            {
                MessageBox.Show(ex.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void chkOutputStreamVisable_CheckedChanged(object sender, EventArgs e)
        {
            try
            {
                this._OutgoingStreamVisable = this.chkOutputStreamVisable.Checked;
            }
            catch (System.Exception ex)
            {
                MessageBox.Show(ex.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void chkConditionEnabled_CheckedChanged(object sender, EventArgs e)
        {
            try
            {
                this.RefresshFilterPanel();
            }
            catch (System.Exception ex)
            {
                MessageBox.Show(ex.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void cbxConfidtion2_SelectedIndexChanged(object sender, EventArgs e)
        {
            try
            {
                this.RefresshFilterPanel();
            }
            catch (System.Exception ex)
            {
                MessageBox.Show(ex.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void cbxConfidtion3_SelectedIndexChanged(object sender, EventArgs e)
        {
            try
            {
                this.RefresshFilterPanel();
            }
            catch (System.Exception ex)
            {
                MessageBox.Show(ex.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void chkSyncRefresh_CheckedChanged(object sender, EventArgs e)
        {
            try
            {
                if (this.chkSyncRefresh.Checked && this.tvMessageSummary.SelectedNode != null)
                {
                    this.ShowSelectedInfo(this.tvMessageSummary.SelectedNode.Tag as TreeNodeTag);
                }
            }
            catch (System.Exception ex)
            {
                MessageBox.Show(ex.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }
        #endregion

        #region "TreeviewSummay上下文菜单响应函数"

        private void openContainedPathToolStripMenuItem_Click(object sender, EventArgs e)
        {
            try
            {
                if (!string.IsNullOrEmpty(this.CommLogPath))
                {
                    System.Diagnostics.Process.Start("explorer", this.CommLogPath);
                }
                else
                {
                    MessageBox.Show("日志路径不可用。", "提示", 
                        MessageBoxButtons.OK, MessageBoxIcon.Information);
                }
            }
            catch (System.Exception /*ex*/)
            {
            }
        }

        private void clearToolStripMenuItem_Click(object sender, EventArgs e)
        {
            try
            {
                this.tvMessageSummary.Nodes.Clear();
                this.txtDetail.Clear();
            }
            catch (System.Exception /*ex*/)
            {            	
            }
        }
        #endregion

        #region "txtDetail上下文菜单响应函数"
        private void selectAllToolStripMenuItem_Click(object sender, EventArgs e)
        {
            try
            {
                this.txtDetail.Focus();
                this.txtDetail.SelectionStart = 0;
                this.txtDetail.SelectionLength = txtDetail.TextLength;
            }
            catch (System.Exception ex)
            {
                MessageBox.Show(ex.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void copyToolStripMenuItem_Click(object sender, EventArgs e)
        {
            try
            {
                this.txtDetail.Copy();
            }
            catch (System.Exception ex)
            {
                MessageBox.Show(ex.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }
        #endregion
    }
}