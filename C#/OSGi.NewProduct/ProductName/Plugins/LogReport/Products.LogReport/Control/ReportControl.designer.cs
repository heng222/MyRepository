namespace Products.LogReport
{
    partial class ReportControl
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
            this._panelQuery = new System.Windows.Forms.Panel();
            this.panResult = new System.Windows.Forms.Panel();
            this._reportViewer1 = new Microsoft.Reporting.WinForms.ReportViewer();
            this.splitContainer1 = new System.Windows.Forms.SplitContainer();
            this.panResult.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer1)).BeginInit();
            this.splitContainer1.Panel1.SuspendLayout();
            this.splitContainer1.Panel2.SuspendLayout();
            this.splitContainer1.SuspendLayout();
            this.SuspendLayout();
            // 
            // _panelQuery
            // 
            this._panelQuery.Dock = System.Windows.Forms.DockStyle.Fill;
            this._panelQuery.Location = new System.Drawing.Point(0, 0);
            this._panelQuery.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this._panelQuery.Name = "_panelQuery";
            this._panelQuery.Size = new System.Drawing.Size(860, 109);
            this._panelQuery.TabIndex = 0;
            // 
            // panResult
            // 
            this.panResult.Controls.Add(this._reportViewer1);
            this.panResult.Dock = System.Windows.Forms.DockStyle.Fill;
            this.panResult.Location = new System.Drawing.Point(0, 0);
            this.panResult.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.panResult.Name = "panResult";
            this.panResult.Size = new System.Drawing.Size(860, 239);
            this.panResult.TabIndex = 1;
            // 
            // _reportViewer1
            // 
            this._reportViewer1.BackColor = System.Drawing.SystemColors.Control;
            this._reportViewer1.Dock = System.Windows.Forms.DockStyle.Fill;
            this._reportViewer1.Location = new System.Drawing.Point(0, 0);
            this._reportViewer1.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this._reportViewer1.Name = "reportViewer1";
            this._reportViewer1.Size = new System.Drawing.Size(852, 244);
            this._reportViewer1.TabIndex = 0;
            this._reportViewer1.ZoomMode = Microsoft.Reporting.WinForms.ZoomMode.PageWidth;
            this._reportViewer1.Drillthrough += new Microsoft.Reporting.WinForms.DrillthroughEventHandler(this.reportViewer1_Drillthrough);
            // 
            // splitContainer1
            // 
            this.splitContainer1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.splitContainer1.FixedPanel = System.Windows.Forms.FixedPanel.Panel1;
            this.splitContainer1.Location = new System.Drawing.Point(0, 0);
            this.splitContainer1.Name = "splitContainer1";
            this.splitContainer1.Orientation = System.Windows.Forms.Orientation.Horizontal;
            // 
            // splitContainer1.Panel1
            // 
            this.splitContainer1.Panel1.Controls.Add(this._panelQuery);
            // 
            // splitContainer1.Panel2
            // 
            this.splitContainer1.Panel2.Controls.Add(this.panResult);
            this.splitContainer1.Size = new System.Drawing.Size(860, 352);
            this.splitContainer1.SplitterDistance = 109;
            this.splitContainer1.TabIndex = 2;
            // 
            // ReportControl
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.splitContainer1);
            this.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.Name = "ReportControl";
            this.Size = new System.Drawing.Size(860, 352);
            this.panResult.ResumeLayout(false);
            this.splitContainer1.Panel1.ResumeLayout(false);
            this.splitContainer1.Panel2.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer1)).EndInit();
            this.splitContainer1.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Panel _panelQuery;
        private System.Windows.Forms.Panel panResult;
        private Microsoft.Reporting.WinForms.ReportViewer _reportViewer1;
        private System.Windows.Forms.SplitContainer splitContainer1;
    }
}
