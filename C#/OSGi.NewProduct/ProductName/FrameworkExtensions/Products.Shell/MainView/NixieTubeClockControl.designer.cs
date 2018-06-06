namespace Products.Shell.MainView
{
    partial class NixieTubeClockControl
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
            this.contextMenuStrip1 = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.dateWeekVisableToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.progressbarToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.contextMenuStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // contextMenuStrip1
            // 
            this.contextMenuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.dateWeekVisableToolStripMenuItem,
            this.progressbarToolStripMenuItem});
            this.contextMenuStrip1.Name = "contextMenuStrip1";
            this.contextMenuStrip1.Size = new System.Drawing.Size(153, 70);
            // 
            // dateWeekVisableToolStripMenuItem
            // 
            this.dateWeekVisableToolStripMenuItem.Name = "dateWeekVisableToolStripMenuItem";
            this.dateWeekVisableToolStripMenuItem.Size = new System.Drawing.Size(152, 22);
            this.dateWeekVisableToolStripMenuItem.Text = "日期星期(&D)";
            this.dateWeekVisableToolStripMenuItem.Click += new System.EventHandler(this.OnDateWeekVisableToolStripMenuItem_Click);
            // 
            // progressbarToolStripMenuItem
            // 
            this.progressbarToolStripMenuItem.Name = "progressbarToolStripMenuItem";
            this.progressbarToolStripMenuItem.Size = new System.Drawing.Size(152, 22);
            this.progressbarToolStripMenuItem.Text = "进度条(&S)";
            this.progressbarToolStripMenuItem.Click += new System.EventHandler(this.OnProgressbarToolStripMenuItem_Click);
            // 
            // NixieTubeClockControl
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ContextMenuStrip = this.contextMenuStrip1;
            this.Name = "NixieTubeClockControl";
            this.Size = new System.Drawing.Size(325, 118);
            this.contextMenuStrip1.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.ContextMenuStrip contextMenuStrip1;
        private System.Windows.Forms.ToolStripMenuItem dateWeekVisableToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem progressbarToolStripMenuItem;
    }
}
