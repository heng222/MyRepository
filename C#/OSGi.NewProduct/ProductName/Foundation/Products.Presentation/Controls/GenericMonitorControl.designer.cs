using Acl.Controls;
namespace Products.Presentation
{
    partial class GenericMonitorControl
    {
        /// <summary> 
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary> 
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing)
            {
                if (components != null) components.Dispose();

                if (_productCache != null) _productCache.Close();
            }

            base.Dispose(disposing);
        }

        #region 组件设计器生成的代码

        /// <summary> 
        /// 设计器支持所需的方法 - 不要
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(GenericMonitorControl));
            this.splitContainer1 = new System.Windows.Forms.SplitContainer();
            this.splitContainer3 = new System.Windows.Forms.SplitContainer();
            this.chkOutputStreamVisable = new System.Windows.Forms.CheckBox();
            this.chkInputStreamVisable = new System.Windows.Forms.CheckBox();
            this.cbxRemoteIDs = new System.Windows.Forms.ComboBox();
            this.label2 = new System.Windows.Forms.Label();
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            this.splitContainer4 = new System.Windows.Forms.SplitContainer();
            this.tvMessageSummary = new Acl.Controls.DoubleBufferedTreeView();
            this.contextMenuTreeviewSummay = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.openContainedPathToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
            this.clearToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.imageListCommLog = new System.Windows.Forms.ImageList(this.components);
            this.cbxConfidtion3 = new System.Windows.Forms.ComboBox();
            this.cbxConfidtion2 = new System.Windows.Forms.ComboBox();
            this.cmbCondition3Operator = new System.Windows.Forms.ComboBox();
            this.cmbCondition2Operator = new System.Windows.Forms.ComboBox();
            this.cmbCondition1Operator = new System.Windows.Forms.ComboBox();
            this.nudCondition3Value = new System.Windows.Forms.NumericUpDown();
            this.nudCondition2Value = new System.Windows.Forms.NumericUpDown();
            this.nudCondition3Index = new System.Windows.Forms.NumericUpDown();
            this.nudCondition2Index = new System.Windows.Forms.NumericUpDown();
            this.label6 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.nudCondition1Value = new System.Windows.Forms.NumericUpDown();
            this.nudCondition1Index = new System.Windows.Forms.NumericUpDown();
            this.label1 = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.chkConditionEnabled = new System.Windows.Forms.CheckBox();
            this.splitContainer5 = new System.Windows.Forms.SplitContainer();
            this.txtDetail = new System.Windows.Forms.RichTextBox();
            this.contextMenuDetail = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.selectAllToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator2 = new System.Windows.Forms.ToolStripSeparator();
            this.copyToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.chkSyncRefresh = new System.Windows.Forms.CheckBox();
            this.imgListConnectionState = new System.Windows.Forms.ImageList(this.components);
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer1)).BeginInit();
            this.splitContainer1.Panel1.SuspendLayout();
            this.splitContainer1.Panel2.SuspendLayout();
            this.splitContainer1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer3)).BeginInit();
            this.splitContainer3.Panel1.SuspendLayout();
            this.splitContainer3.Panel2.SuspendLayout();
            this.splitContainer3.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer4)).BeginInit();
            this.splitContainer4.Panel1.SuspendLayout();
            this.splitContainer4.Panel2.SuspendLayout();
            this.splitContainer4.SuspendLayout();
            this.contextMenuTreeviewSummay.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.nudCondition3Value)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.nudCondition2Value)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.nudCondition3Index)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.nudCondition2Index)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.nudCondition1Value)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.nudCondition1Index)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer5)).BeginInit();
            this.splitContainer5.Panel1.SuspendLayout();
            this.splitContainer5.Panel2.SuspendLayout();
            this.splitContainer5.SuspendLayout();
            this.contextMenuDetail.SuspendLayout();
            this.SuspendLayout();
            // 
            // splitContainer1
            // 
            this.splitContainer1.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.splitContainer1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.splitContainer1.FixedPanel = System.Windows.Forms.FixedPanel.Panel1;
            this.splitContainer1.Location = new System.Drawing.Point(0, 0);
            this.splitContainer1.Name = "splitContainer1";
            // 
            // splitContainer1.Panel1
            // 
            this.splitContainer1.Panel1.Controls.Add(this.splitContainer3);
            this.splitContainer1.Panel1MinSize = 50;
            // 
            // splitContainer1.Panel2
            // 
            this.splitContainer1.Panel2.Controls.Add(this.splitContainer5);
            this.splitContainer1.Size = new System.Drawing.Size(492, 359);
            this.splitContainer1.SplitterDistance = 297;
            this.splitContainer1.TabIndex = 0;
            // 
            // splitContainer3
            // 
            this.splitContainer3.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.splitContainer3.Dock = System.Windows.Forms.DockStyle.Fill;
            this.splitContainer3.FixedPanel = System.Windows.Forms.FixedPanel.Panel1;
            this.splitContainer3.Location = new System.Drawing.Point(0, 0);
            this.splitContainer3.Name = "splitContainer3";
            this.splitContainer3.Orientation = System.Windows.Forms.Orientation.Horizontal;
            // 
            // splitContainer3.Panel1
            // 
            this.splitContainer3.Panel1.Controls.Add(this.chkOutputStreamVisable);
            this.splitContainer3.Panel1.Controls.Add(this.chkInputStreamVisable);
            this.splitContainer3.Panel1.Controls.Add(this.cbxRemoteIDs);
            this.splitContainer3.Panel1.Controls.Add(this.label2);
            this.splitContainer3.Panel1.Controls.Add(this.pictureBox1);
            // 
            // splitContainer3.Panel2
            // 
            this.splitContainer3.Panel2.Controls.Add(this.splitContainer4);
            this.splitContainer3.Size = new System.Drawing.Size(297, 359);
            this.splitContainer3.SplitterDistance = 53;
            this.splitContainer3.TabIndex = 0;
            // 
            // chkOutputStreamVisable
            // 
            this.chkOutputStreamVisable.AutoSize = true;
            this.chkOutputStreamVisable.Location = new System.Drawing.Point(94, 30);
            this.chkOutputStreamVisable.Name = "chkOutputStreamVisable";
            this.chkOutputStreamVisable.Size = new System.Drawing.Size(84, 16);
            this.chkOutputStreamVisable.TabIndex = 6;
            this.chkOutputStreamVisable.Text = "显示输出流";
            this.chkOutputStreamVisable.UseVisualStyleBackColor = true;
            this.chkOutputStreamVisable.CheckedChanged += new System.EventHandler(this.chkOutputStreamVisable_CheckedChanged);
            // 
            // chkInputStreamVisable
            // 
            this.chkInputStreamVisable.AutoSize = true;
            this.chkInputStreamVisable.Location = new System.Drawing.Point(7, 30);
            this.chkInputStreamVisable.Name = "chkInputStreamVisable";
            this.chkInputStreamVisable.Size = new System.Drawing.Size(84, 16);
            this.chkInputStreamVisable.TabIndex = 5;
            this.chkInputStreamVisable.Text = "显示输入流";
            this.chkInputStreamVisable.UseVisualStyleBackColor = true;
            this.chkInputStreamVisable.CheckedChanged += new System.EventHandler(this.chkInputStreamVisable_CheckedChanged);
            // 
            // cbxRemoteIDs
            // 
            this.cbxRemoteIDs.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.cbxRemoteIDs.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cbxRemoteIDs.FormattingEnabled = true;
            this.cbxRemoteIDs.Location = new System.Drawing.Point(60, 4);
            this.cbxRemoteIDs.MaxDropDownItems = 20;
            this.cbxRemoteIDs.Name = "cbxRemoteIDs";
            this.cbxRemoteIDs.Size = new System.Drawing.Size(203, 20);
            this.cbxRemoteIDs.TabIndex = 2;
            this.cbxRemoteIDs.SelectedIndexChanged += new System.EventHandler(this.cbxRemoteIDs_SelectedIndexChanged);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(5, 7);
            this.label2.Margin = new System.Windows.Forms.Padding(5, 7, 0, 0);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(53, 12);
            this.label2.TabIndex = 0;
            this.label2.Text = "远程设备";
            // 
            // pictureBox1
            // 
            this.pictureBox1.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.pictureBox1.BackgroundImageLayout = System.Windows.Forms.ImageLayout.None;
            this.pictureBox1.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.pictureBox1.Location = new System.Drawing.Point(269, 6);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(16, 16);
            this.pictureBox1.TabIndex = 1;
            this.pictureBox1.TabStop = false;
            // 
            // splitContainer4
            // 
            this.splitContainer4.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.splitContainer4.Dock = System.Windows.Forms.DockStyle.Fill;
            this.splitContainer4.FixedPanel = System.Windows.Forms.FixedPanel.Panel2;
            this.splitContainer4.Location = new System.Drawing.Point(0, 0);
            this.splitContainer4.Name = "splitContainer4";
            this.splitContainer4.Orientation = System.Windows.Forms.Orientation.Horizontal;
            // 
            // splitContainer4.Panel1
            // 
            this.splitContainer4.Panel1.Controls.Add(this.tvMessageSummary);
            // 
            // splitContainer4.Panel2
            // 
            this.splitContainer4.Panel2.Controls.Add(this.cbxConfidtion3);
            this.splitContainer4.Panel2.Controls.Add(this.cbxConfidtion2);
            this.splitContainer4.Panel2.Controls.Add(this.cmbCondition3Operator);
            this.splitContainer4.Panel2.Controls.Add(this.cmbCondition2Operator);
            this.splitContainer4.Panel2.Controls.Add(this.cmbCondition1Operator);
            this.splitContainer4.Panel2.Controls.Add(this.nudCondition3Value);
            this.splitContainer4.Panel2.Controls.Add(this.nudCondition2Value);
            this.splitContainer4.Panel2.Controls.Add(this.nudCondition3Index);
            this.splitContainer4.Panel2.Controls.Add(this.nudCondition2Index);
            this.splitContainer4.Panel2.Controls.Add(this.label6);
            this.splitContainer4.Panel2.Controls.Add(this.label5);
            this.splitContainer4.Panel2.Controls.Add(this.label3);
            this.splitContainer4.Panel2.Controls.Add(this.label4);
            this.splitContainer4.Panel2.Controls.Add(this.nudCondition1Value);
            this.splitContainer4.Panel2.Controls.Add(this.nudCondition1Index);
            this.splitContainer4.Panel2.Controls.Add(this.label1);
            this.splitContainer4.Panel2.Controls.Add(this.label7);
            this.splitContainer4.Panel2.Controls.Add(this.chkConditionEnabled);
            this.splitContainer4.Size = new System.Drawing.Size(297, 302);
            this.splitContainer4.SplitterDistance = 211;
            this.splitContainer4.TabIndex = 3;
            // 
            // tvMessageSummary
            // 
            this.tvMessageSummary.AllowDrop = true;
            this.tvMessageSummary.ContextMenuStrip = this.contextMenuTreeviewSummay;
            this.tvMessageSummary.HideSelection = false;
            this.tvMessageSummary.ImageIndex = 0;
            this.tvMessageSummary.ImageList = this.imageListCommLog;
            this.tvMessageSummary.Location = new System.Drawing.Point(42, 42);
            this.tvMessageSummary.Name = "tvMessageSummary";
            this.tvMessageSummary.SelectedImageIndex = 0;
            this.tvMessageSummary.ShowNodeToolTips = true;
            this.tvMessageSummary.Size = new System.Drawing.Size(102, 96);
            this.tvMessageSummary.TabIndex = 2;
            this.tvMessageSummary.AfterSelect += new System.Windows.Forms.TreeViewEventHandler(this.tvMessageSummary_AfterSelect);
            this.tvMessageSummary.NodeMouseClick += new System.Windows.Forms.TreeNodeMouseClickEventHandler(this.tvMessageSummary_NodeMouseClick);
            // 
            // contextMenuTreeviewSummay
            // 
            this.contextMenuTreeviewSummay.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.openContainedPathToolStripMenuItem,
            this.toolStripSeparator1,
            this.clearToolStripMenuItem});
            this.contextMenuTreeviewSummay.Name = "contextMenuAliveData";
            this.contextMenuTreeviewSummay.Size = new System.Drawing.Size(179, 54);
            // 
            // openContainedPathToolStripMenuItem
            // 
            this.openContainedPathToolStripMenuItem.Name = "openContainedPathToolStripMenuItem";
            this.openContainedPathToolStripMenuItem.Size = new System.Drawing.Size(178, 22);
            this.openContainedPathToolStripMenuItem.Text = "打开持久化目录(&O)";
            this.openContainedPathToolStripMenuItem.Click += new System.EventHandler(this.openContainedPathToolStripMenuItem_Click);
            // 
            // toolStripSeparator1
            // 
            this.toolStripSeparator1.Name = "toolStripSeparator1";
            this.toolStripSeparator1.Size = new System.Drawing.Size(175, 6);
            // 
            // clearToolStripMenuItem
            // 
            this.clearToolStripMenuItem.Name = "clearToolStripMenuItem";
            this.clearToolStripMenuItem.Size = new System.Drawing.Size(178, 22);
            this.clearToolStripMenuItem.Text = "清空(&C)";
            this.clearToolStripMenuItem.Click += new System.EventHandler(this.clearToolStripMenuItem_Click);
            // 
            // imageListCommLog
            // 
            this.imageListCommLog.ImageStream = ((System.Windows.Forms.ImageListStreamer)(resources.GetObject("imageListCommLog.ImageStream")));
            this.imageListCommLog.TransparentColor = System.Drawing.Color.Transparent;
            this.imageListCommLog.Images.SetKeyName(0, "LogRecords_Collapsed");
            this.imageListCommLog.Images.SetKeyName(1, "LogRecords_Expanded");
            this.imageListCommLog.Images.SetKeyName(2, "InputStream");
            this.imageListCommLog.Images.SetKeyName(3, "OutputStream");
            this.imageListCommLog.Images.SetKeyName(4, "OutputStream_Selected");
            this.imageListCommLog.Images.SetKeyName(5, "InputStream_Selected");
            // 
            // cbxConfidtion3
            // 
            this.cbxConfidtion3.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cbxConfidtion3.FormattingEnabled = true;
            this.cbxConfidtion3.Items.AddRange(new object[] {
            "无",
            "且",
            "或"});
            this.cbxConfidtion3.Location = new System.Drawing.Point(4, 58);
            this.cbxConfidtion3.Name = "cbxConfidtion3";
            this.cbxConfidtion3.Size = new System.Drawing.Size(41, 20);
            this.cbxConfidtion3.TabIndex = 14;
            this.cbxConfidtion3.SelectedIndexChanged += new System.EventHandler(this.cbxConfidtion3_SelectedIndexChanged);
            // 
            // cbxConfidtion2
            // 
            this.cbxConfidtion2.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cbxConfidtion2.FormattingEnabled = true;
            this.cbxConfidtion2.Items.AddRange(new object[] {
            "无",
            "且",
            "或"});
            this.cbxConfidtion2.Location = new System.Drawing.Point(4, 34);
            this.cbxConfidtion2.Name = "cbxConfidtion2";
            this.cbxConfidtion2.Size = new System.Drawing.Size(41, 20);
            this.cbxConfidtion2.TabIndex = 16;
            this.cbxConfidtion2.SelectedIndexChanged += new System.EventHandler(this.cbxConfidtion2_SelectedIndexChanged);
            // 
            // cmbCondition3Operator
            // 
            this.cmbCondition3Operator.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cmbCondition3Operator.FormattingEnabled = true;
            this.cmbCondition3Operator.Items.AddRange(new object[] {
            "等于",
            "不等于"});
            this.cmbCondition3Operator.Location = new System.Drawing.Point(181, 60);
            this.cmbCondition3Operator.Name = "cmbCondition3Operator";
            this.cmbCondition3Operator.Size = new System.Drawing.Size(60, 20);
            this.cmbCondition3Operator.TabIndex = 28;
            // 
            // cmbCondition2Operator
            // 
            this.cmbCondition2Operator.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cmbCondition2Operator.FormattingEnabled = true;
            this.cmbCondition2Operator.Items.AddRange(new object[] {
            "等于",
            "不等于"});
            this.cmbCondition2Operator.Location = new System.Drawing.Point(181, 34);
            this.cmbCondition2Operator.Name = "cmbCondition2Operator";
            this.cmbCondition2Operator.Size = new System.Drawing.Size(60, 20);
            this.cmbCondition2Operator.TabIndex = 27;
            // 
            // cmbCondition1Operator
            // 
            this.cmbCondition1Operator.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cmbCondition1Operator.FormattingEnabled = true;
            this.cmbCondition1Operator.Items.AddRange(new object[] {
            "等于",
            "不等于"});
            this.cmbCondition1Operator.Location = new System.Drawing.Point(181, 6);
            this.cmbCondition1Operator.Name = "cmbCondition1Operator";
            this.cmbCondition1Operator.Size = new System.Drawing.Size(60, 20);
            this.cmbCondition1Operator.TabIndex = 26;
            // 
            // nudCondition3Value
            // 
            this.nudCondition3Value.Hexadecimal = true;
            this.nudCondition3Value.Location = new System.Drawing.Point(243, 60);
            this.nudCondition3Value.Maximum = new decimal(new int[] {
            255,
            0,
            0,
            0});
            this.nudCondition3Value.Name = "nudCondition3Value";
            this.nudCondition3Value.Size = new System.Drawing.Size(42, 21);
            this.nudCondition3Value.TabIndex = 25;
            // 
            // nudCondition2Value
            // 
            this.nudCondition2Value.Hexadecimal = true;
            this.nudCondition2Value.Location = new System.Drawing.Point(243, 33);
            this.nudCondition2Value.Maximum = new decimal(new int[] {
            255,
            0,
            0,
            0});
            this.nudCondition2Value.Name = "nudCondition2Value";
            this.nudCondition2Value.Size = new System.Drawing.Size(42, 21);
            this.nudCondition2Value.TabIndex = 24;
            // 
            // nudCondition3Index
            // 
            this.nudCondition3Index.Location = new System.Drawing.Point(73, 60);
            this.nudCondition3Index.Maximum = new decimal(new int[] {
            64000,
            0,
            0,
            0});
            this.nudCondition3Index.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.nudCondition3Index.Name = "nudCondition3Index";
            this.nudCondition3Index.Size = new System.Drawing.Size(61, 21);
            this.nudCondition3Index.TabIndex = 23;
            this.nudCondition3Index.Value = new decimal(new int[] {
            3,
            0,
            0,
            0});
            // 
            // nudCondition2Index
            // 
            this.nudCondition2Index.Location = new System.Drawing.Point(73, 33);
            this.nudCondition2Index.Maximum = new decimal(new int[] {
            64000,
            0,
            0,
            0});
            this.nudCondition2Index.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.nudCondition2Index.Name = "nudCondition2Index";
            this.nudCondition2Index.Size = new System.Drawing.Size(61, 21);
            this.nudCondition2Index.TabIndex = 22;
            this.nudCondition2Index.Value = new decimal(new int[] {
            2,
            0,
            0,
            0});
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(138, 65);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(41, 12);
            this.label6.TabIndex = 21;
            this.label6.Text = "个字节";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(52, 64);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(17, 12);
            this.label5.TabIndex = 19;
            this.label5.Text = "第";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(138, 37);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(41, 12);
            this.label3.TabIndex = 20;
            this.label3.Text = "个字节";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(52, 37);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(17, 12);
            this.label4.TabIndex = 18;
            this.label4.Text = "第";
            // 
            // nudCondition1Value
            // 
            this.nudCondition1Value.Hexadecimal = true;
            this.nudCondition1Value.Location = new System.Drawing.Point(243, 6);
            this.nudCondition1Value.Maximum = new decimal(new int[] {
            255,
            0,
            0,
            0});
            this.nudCondition1Value.Name = "nudCondition1Value";
            this.nudCondition1Value.Size = new System.Drawing.Size(42, 21);
            this.nudCondition1Value.TabIndex = 17;
            // 
            // nudCondition1Index
            // 
            this.nudCondition1Index.Location = new System.Drawing.Point(73, 5);
            this.nudCondition1Index.Maximum = new decimal(new int[] {
            64000,
            0,
            0,
            0});
            this.nudCondition1Index.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.nudCondition1Index.Name = "nudCondition1Index";
            this.nudCondition1Index.Size = new System.Drawing.Size(61, 21);
            this.nudCondition1Index.TabIndex = 15;
            this.nudCondition1Index.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(137, 10);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(41, 12);
            this.label1.TabIndex = 12;
            this.label1.Text = "个字节";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(52, 9);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(17, 12);
            this.label7.TabIndex = 13;
            this.label7.Text = "第";
            // 
            // chkConditionEnabled
            // 
            this.chkConditionEnabled.AutoSize = true;
            this.chkConditionEnabled.Location = new System.Drawing.Point(4, 7);
            this.chkConditionEnabled.Name = "chkConditionEnabled";
            this.chkConditionEnabled.Size = new System.Drawing.Size(48, 16);
            this.chkConditionEnabled.TabIndex = 11;
            this.chkConditionEnabled.Text = "过滤";
            this.chkConditionEnabled.UseVisualStyleBackColor = true;
            this.chkConditionEnabled.CheckedChanged += new System.EventHandler(this.chkConditionEnabled_CheckedChanged);
            // 
            // splitContainer5
            // 
            this.splitContainer5.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.splitContainer5.Dock = System.Windows.Forms.DockStyle.Fill;
            this.splitContainer5.FixedPanel = System.Windows.Forms.FixedPanel.Panel2;
            this.splitContainer5.Location = new System.Drawing.Point(0, 0);
            this.splitContainer5.Name = "splitContainer5";
            this.splitContainer5.Orientation = System.Windows.Forms.Orientation.Horizontal;
            // 
            // splitContainer5.Panel1
            // 
            this.splitContainer5.Panel1.Controls.Add(this.txtDetail);
            // 
            // splitContainer5.Panel2
            // 
            this.splitContainer5.Panel2.Controls.Add(this.chkSyncRefresh);
            this.splitContainer5.Size = new System.Drawing.Size(191, 359);
            this.splitContainer5.SplitterDistance = 321;
            this.splitContainer5.TabIndex = 1;
            // 
            // txtDetail
            // 
            this.txtDetail.ContextMenuStrip = this.contextMenuDetail;
            this.txtDetail.Font = new System.Drawing.Font("Arial", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.txtDetail.HideSelection = false;
            this.txtDetail.Location = new System.Drawing.Point(14, 16);
            this.txtDetail.Name = "txtDetail";
            this.txtDetail.Size = new System.Drawing.Size(100, 96);
            this.txtDetail.TabIndex = 0;
            this.txtDetail.Text = "";
            this.txtDetail.MouseClick += new System.Windows.Forms.MouseEventHandler(this.txtDetail_MouseClick);
            // 
            // contextMenuDetail
            // 
            this.contextMenuDetail.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.selectAllToolStripMenuItem,
            this.toolStripSeparator2,
            this.copyToolStripMenuItem});
            this.contextMenuDetail.Name = "contextMenuDetail";
            this.contextMenuDetail.Size = new System.Drawing.Size(141, 54);
            // 
            // selectAllToolStripMenuItem
            // 
            this.selectAllToolStripMenuItem.Name = "selectAllToolStripMenuItem";
            this.selectAllToolStripMenuItem.Size = new System.Drawing.Size(140, 22);
            this.selectAllToolStripMenuItem.Text = "全部选择(&A)";
            this.selectAllToolStripMenuItem.Click += new System.EventHandler(this.selectAllToolStripMenuItem_Click);
            // 
            // toolStripSeparator2
            // 
            this.toolStripSeparator2.Name = "toolStripSeparator2";
            this.toolStripSeparator2.Size = new System.Drawing.Size(137, 6);
            // 
            // copyToolStripMenuItem
            // 
            this.copyToolStripMenuItem.Name = "copyToolStripMenuItem";
            this.copyToolStripMenuItem.Size = new System.Drawing.Size(140, 22);
            this.copyToolStripMenuItem.Text = "复制(&C)";
            this.copyToolStripMenuItem.Click += new System.EventHandler(this.copyToolStripMenuItem_Click);
            // 
            // chkSyncRefresh
            // 
            this.chkSyncRefresh.AutoSize = true;
            this.chkSyncRefresh.Location = new System.Drawing.Point(14, 8);
            this.chkSyncRefresh.Name = "chkSyncRefresh";
            this.chkSyncRefresh.Size = new System.Drawing.Size(72, 16);
            this.chkSyncRefresh.TabIndex = 1;
            this.chkSyncRefresh.Text = "同步刷新";
            this.chkSyncRefresh.UseVisualStyleBackColor = true;
            this.chkSyncRefresh.CheckedChanged += new System.EventHandler(this.chkSyncRefresh_CheckedChanged);
            // 
            // imgListConnectionState
            // 
            this.imgListConnectionState.ImageStream = ((System.Windows.Forms.ImageListStreamer)(resources.GetObject("imgListConnectionState.ImageStream")));
            this.imgListConnectionState.TransparentColor = System.Drawing.Color.Transparent;
            this.imgListConnectionState.Images.SetKeyName(0, "DeviceOnline");
            this.imgListConnectionState.Images.SetKeyName(1, "DeviceOffline");
            this.imgListConnectionState.Images.SetKeyName(2, "fail");
            this.imgListConnectionState.Images.SetKeyName(3, "success");
            // 
            // GenericMonitorControl
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.splitContainer1);
            this.Name = "GenericMonitorControl";
            this.Size = new System.Drawing.Size(492, 359);
            this.splitContainer1.Panel1.ResumeLayout(false);
            this.splitContainer1.Panel2.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer1)).EndInit();
            this.splitContainer1.ResumeLayout(false);
            this.splitContainer3.Panel1.ResumeLayout(false);
            this.splitContainer3.Panel1.PerformLayout();
            this.splitContainer3.Panel2.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer3)).EndInit();
            this.splitContainer3.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            this.splitContainer4.Panel1.ResumeLayout(false);
            this.splitContainer4.Panel2.ResumeLayout(false);
            this.splitContainer4.Panel2.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer4)).EndInit();
            this.splitContainer4.ResumeLayout(false);
            this.contextMenuTreeviewSummay.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.nudCondition3Value)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.nudCondition2Value)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.nudCondition3Index)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.nudCondition2Index)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.nudCondition1Value)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.nudCondition1Index)).EndInit();
            this.splitContainer5.Panel1.ResumeLayout(false);
            this.splitContainer5.Panel2.ResumeLayout(false);
            this.splitContainer5.Panel2.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer5)).EndInit();
            this.splitContainer5.ResumeLayout(false);
            this.contextMenuDetail.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.SplitContainer splitContainer1;
        private System.Windows.Forms.SplitContainer splitContainer3;
        private System.Windows.Forms.PictureBox pictureBox1;
        private System.Windows.Forms.ImageList imgListConnectionState;
        private System.Windows.Forms.ContextMenuStrip contextMenuTreeviewSummay;
        private System.Windows.Forms.ToolStripMenuItem openContainedPathToolStripMenuItem;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator1;
        private System.Windows.Forms.ToolStripMenuItem clearToolStripMenuItem;
        private System.Windows.Forms.ComboBox cbxRemoteIDs;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.RichTextBox txtDetail;
        private System.Windows.Forms.ContextMenuStrip contextMenuDetail;
        private System.Windows.Forms.ImageList imageListCommLog;
        private System.Windows.Forms.ToolStripMenuItem selectAllToolStripMenuItem;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator2;
        private System.Windows.Forms.ToolStripMenuItem copyToolStripMenuItem;
        private System.Windows.Forms.CheckBox chkOutputStreamVisable;
        private System.Windows.Forms.CheckBox chkInputStreamVisable;
        private System.Windows.Forms.SplitContainer splitContainer4;
        private System.Windows.Forms.ComboBox cbxConfidtion3;
        private System.Windows.Forms.ComboBox cbxConfidtion2;
        private System.Windows.Forms.ComboBox cmbCondition3Operator;
        private System.Windows.Forms.ComboBox cmbCondition2Operator;
        private System.Windows.Forms.ComboBox cmbCondition1Operator;
        private System.Windows.Forms.NumericUpDown nudCondition3Value;
        private System.Windows.Forms.NumericUpDown nudCondition2Value;
        private System.Windows.Forms.NumericUpDown nudCondition3Index;
        private System.Windows.Forms.NumericUpDown nudCondition2Index;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.NumericUpDown nudCondition1Value;
        private System.Windows.Forms.NumericUpDown nudCondition1Index;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.CheckBox chkConditionEnabled;
        private System.Windows.Forms.SplitContainer splitContainer5;
        private System.Windows.Forms.CheckBox chkSyncRefresh;
        private DoubleBufferedTreeView tvMessageSummary;
    }
}
