namespace Products.SystemEvents.Controls
{
    partial class EventsMonitorControl
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
            if (disposing && (components != null))
            {
                components.Dispose();
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
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle5 = new System.Windows.Forms.DataGridViewCellStyle();
            this.dataGridView = new System.Windows.Forms.DataGridView();
            this.contextMenuStrip1 = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.confirmThisToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.confirmAllToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
            this.removeThisToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.removeAllToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.configToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.level = new System.Windows.Forms.DataGridViewImageColumn();
            this.timestamp = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.eventType = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.description = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.ConfirmTime = new System.Windows.Forms.DataGridViewTextBoxColumn();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView)).BeginInit();
            this.contextMenuStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // dataGridView
            // 
            this.dataGridView.AllowUserToAddRows = false;
            this.dataGridView.AllowUserToDeleteRows = false;
            this.dataGridView.AllowUserToResizeRows = false;
            this.dataGridView.BackgroundColor = System.Drawing.SystemColors.Control;
            this.dataGridView.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.level,
            this.timestamp,
            this.eventType,
            this.description,
            this.ConfirmTime});
            this.dataGridView.ContextMenuStrip = this.contextMenuStrip1;
            this.dataGridView.Dock = System.Windows.Forms.DockStyle.Fill;
            this.dataGridView.Location = new System.Drawing.Point(0, 0);
            this.dataGridView.MultiSelect = false;
            this.dataGridView.Name = "dataGridView";
            this.dataGridView.ReadOnly = true;
            this.dataGridView.RowHeadersVisible = false;
            this.dataGridView.RowTemplate.Height = 23;
            this.dataGridView.SelectionMode = System.Windows.Forms.DataGridViewSelectionMode.FullRowSelect;
            this.dataGridView.Size = new System.Drawing.Size(538, 90);
            this.dataGridView.TabIndex = 2;
            this.dataGridView.RowPrePaint += new System.Windows.Forms.DataGridViewRowPrePaintEventHandler(this.dataGridView_RowPrePaint);
            // 
            // contextMenuStrip1
            // 
            this.contextMenuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.confirmThisToolStripMenuItem,
            this.confirmAllToolStripMenuItem,
            this.toolStripSeparator1,
            this.removeThisToolStripMenuItem,
            this.removeAllToolStripMenuItem,
            this.configToolStripMenuItem});
            this.contextMenuStrip1.Name = "MenuCollocateAlarm";
            this.contextMenuStrip1.Size = new System.Drawing.Size(153, 142);
            this.contextMenuStrip1.Opening += new System.ComponentModel.CancelEventHandler(this.contextMenuStrip1_Opening);
            // 
            // confirmThisToolStripMenuItem
            // 
            this.confirmThisToolStripMenuItem.Image = global::Products.SystemEvents.Properties.Resources.Confirm;
            this.confirmThisToolStripMenuItem.Name = "confirmThisToolStripMenuItem";
            this.confirmThisToolStripMenuItem.Size = new System.Drawing.Size(169, 22);
            this.confirmThisToolStripMenuItem.Text = "确认(&C)";
            this.confirmThisToolStripMenuItem.Click += new System.EventHandler(this.confirmThisToolStripMenuItem_Click);
            // 
            // confirmAllToolStripMenuItem
            // 
            this.confirmAllToolStripMenuItem.Name = "confirmAllToolStripMenuItem";
            this.confirmAllToolStripMenuItem.Size = new System.Drawing.Size(169, 22);
            this.confirmAllToolStripMenuItem.Text = "全部确认";
            this.confirmAllToolStripMenuItem.Click += new System.EventHandler(this.confirmAllToolStripMenuItem_Click);
            // 
            // toolStripSeparator1
            // 
            this.toolStripSeparator1.Name = "toolStripSeparator1";
            this.toolStripSeparator1.Size = new System.Drawing.Size(166, 6);
            // 
            // removeThisToolStripMenuItem
            // 
            this.removeThisToolStripMenuItem.Image = global::Products.SystemEvents.Properties.Resources.Remove;
            this.removeThisToolStripMenuItem.Name = "removeThisToolStripMenuItem";
            this.removeThisToolStripMenuItem.Size = new System.Drawing.Size(169, 22);
            this.removeThisToolStripMenuItem.Text = "删除(D)";
            this.removeThisToolStripMenuItem.Click += new System.EventHandler(this.removeThisToolStripMenuItem_Click);
            // 
            // removeAllToolStripMenuItem
            // 
            this.removeAllToolStripMenuItem.Image = global::Products.SystemEvents.Properties.Resources.RemoveAll;
            this.removeAllToolStripMenuItem.Name = "removeAllToolStripMenuItem";
            this.removeAllToolStripMenuItem.Size = new System.Drawing.Size(169, 22);
            this.removeAllToolStripMenuItem.Text = "全部删除";
            this.removeAllToolStripMenuItem.Click += new System.EventHandler(this.removeAllToolStripMenuItem_Click);
            // 
            // configToolStripMenuItem
            // 
            this.configToolStripMenuItem.Name = "configToolStripMenuItem";
            this.configToolStripMenuItem.Size = new System.Drawing.Size(152, 22);
            this.configToolStripMenuItem.Text = "配置...";
            this.configToolStripMenuItem.Click += new System.EventHandler(this.configToolStripMenuItem_Click);
            // 
            // level
            // 
            this.level.HeaderText = "级别";
            this.level.Image = global::Products.SystemEvents.Properties.Resources.Info;
            this.level.ImageLayout = System.Windows.Forms.DataGridViewImageCellLayout.Zoom;
            this.level.MinimumWidth = 20;
            this.level.Name = "level";
            this.level.ReadOnly = true;
            this.level.Resizable = System.Windows.Forms.DataGridViewTriState.False;
            this.level.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.Automatic;
            this.level.Width = 36;
            // 
            // timestamp
            // 
            this.timestamp.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.DisplayedCells;
            dataGridViewCellStyle5.Alignment = System.Windows.Forms.DataGridViewContentAlignment.MiddleCenter;
            this.timestamp.DefaultCellStyle = dataGridViewCellStyle5;
            this.timestamp.HeaderText = "时间";
            this.timestamp.MinimumWidth = 20;
            this.timestamp.Name = "timestamp";
            this.timestamp.ReadOnly = true;
            this.timestamp.Width = 54;
            // 
            // eventType
            // 
            this.eventType.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.DisplayedCells;
            this.eventType.HeaderText = "类型";
            this.eventType.Name = "eventType";
            this.eventType.ReadOnly = true;
            this.eventType.ToolTipText = "事件类型";
            this.eventType.Width = 54;
            // 
            // description
            // 
            this.description.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.Fill;
            this.description.HeaderText = "描 述";
            this.description.MinimumWidth = 60;
            this.description.Name = "description";
            this.description.ReadOnly = true;
            // 
            // ConfirmTime
            // 
            this.ConfirmTime.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.DisplayedCells;
            this.ConfirmTime.HeaderText = "确认时间";
            this.ConfirmTime.Name = "ConfirmTime";
            this.ConfirmTime.ReadOnly = true;
            this.ConfirmTime.Width = 78;
            // 
            // EventsMonitorControl
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.dataGridView);
            this.Name = "EventsMonitorControl";
            this.Size = new System.Drawing.Size(538, 90);
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView)).EndInit();
            this.contextMenuStrip1.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.DataGridView dataGridView;
        private System.Windows.Forms.ContextMenuStrip contextMenuStrip1;
        private System.Windows.Forms.ToolStripMenuItem removeThisToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem removeAllToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem confirmThisToolStripMenuItem;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator1;
        private System.Windows.Forms.ToolStripMenuItem confirmAllToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem configToolStripMenuItem;
        private System.Windows.Forms.DataGridViewImageColumn level;
        private System.Windows.Forms.DataGridViewTextBoxColumn timestamp;
        private System.Windows.Forms.DataGridViewTextBoxColumn eventType;
        private System.Windows.Forms.DataGridViewTextBoxColumn description;
        private System.Windows.Forms.DataGridViewTextBoxColumn ConfirmTime;
    }
}
