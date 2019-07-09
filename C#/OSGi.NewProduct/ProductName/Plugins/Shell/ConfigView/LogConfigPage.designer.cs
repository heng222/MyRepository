namespace Products.Shell.ConfigView
{
    partial class LogConfigPage
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
            this.nudDiagFileExpiredDays = new System.Windows.Forms.NumericUpDown();
            this.label3 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.rBtnGlobal = new System.Windows.Forms.RadioButton();
            this.rBtnIndependent = new System.Windows.Forms.RadioButton();
            this.cbxGlobalLoglevel = new System.Windows.Forms.ComboBox();
            this.flowLayoutPanel = new System.Windows.Forms.FlowLayoutPanel();
            this.splitContainer1 = new System.Windows.Forms.SplitContainer();
            ((System.ComponentModel.ISupportInitialize)(this.nudDiagFileExpiredDays)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer1)).BeginInit();
            this.splitContainer1.Panel1.SuspendLayout();
            this.splitContainer1.Panel2.SuspendLayout();
            this.splitContainer1.SuspendLayout();
            this.SuspendLayout();
            // 
            // nudDiagFileExpiredDays
            // 
            this.nudDiagFileExpiredDays.Location = new System.Drawing.Point(142, 11);
            this.nudDiagFileExpiredDays.Maximum = new decimal(new int[] {
            60,
            0,
            0,
            0});
            this.nudDiagFileExpiredDays.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.nudDiagFileExpiredDays.Name = "nudDiagFileExpiredDays";
            this.nudDiagFileExpiredDays.Size = new System.Drawing.Size(65, 21);
            this.nudDiagFileExpiredDays.TabIndex = 8;
            this.nudDiagFileExpiredDays.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(15, 16);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(125, 12);
            this.label3.TabIndex = 7;
            this.label3.Text = "程序运行日志保存天数";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(15, 45);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(101, 12);
            this.label1.TabIndex = 9;
            this.label1.Text = "程序日志保存级别";
            // 
            // rBtnGlobal
            // 
            this.rBtnGlobal.AutoSize = true;
            this.rBtnGlobal.Checked = true;
            this.rBtnGlobal.Location = new System.Drawing.Point(36, 73);
            this.rBtnGlobal.Name = "rBtnGlobal";
            this.rBtnGlobal.Size = new System.Drawing.Size(71, 16);
            this.rBtnGlobal.TabIndex = 10;
            this.rBtnGlobal.TabStop = true;
            this.rBtnGlobal.Text = "全局设置";
            this.rBtnGlobal.UseVisualStyleBackColor = true;
            this.rBtnGlobal.CheckedChanged += new System.EventHandler(this.radioButton1_CheckedChanged);
            // 
            // rBtnIndependent
            // 
            this.rBtnIndependent.AutoSize = true;
            this.rBtnIndependent.Location = new System.Drawing.Point(36, 106);
            this.rBtnIndependent.Name = "rBtnIndependent";
            this.rBtnIndependent.Size = new System.Drawing.Size(71, 16);
            this.rBtnIndependent.TabIndex = 11;
            this.rBtnIndependent.Text = "独立设置";
            this.rBtnIndependent.UseVisualStyleBackColor = true;
            // 
            // cbxGlobalLoglevel
            // 
            this.cbxGlobalLoglevel.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cbxGlobalLoglevel.FormattingEnabled = true;
            this.cbxGlobalLoglevel.Location = new System.Drawing.Point(113, 71);
            this.cbxGlobalLoglevel.Name = "cbxGlobalLoglevel";
            this.cbxGlobalLoglevel.Size = new System.Drawing.Size(121, 20);
            this.cbxGlobalLoglevel.TabIndex = 12;
            // 
            // flowLayoutPanel
            // 
            this.flowLayoutPanel.AutoScroll = true;
            this.flowLayoutPanel.Dock = System.Windows.Forms.DockStyle.Fill;
            this.flowLayoutPanel.Location = new System.Drawing.Point(0, 0);
            this.flowLayoutPanel.Name = "flowLayoutPanel";
            this.flowLayoutPanel.Size = new System.Drawing.Size(394, 203);
            this.flowLayoutPanel.TabIndex = 20;
            // 
            // splitContainer1
            // 
            this.splitContainer1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.splitContainer1.FixedPanel = System.Windows.Forms.FixedPanel.Panel1;
            this.splitContainer1.IsSplitterFixed = true;
            this.splitContainer1.Location = new System.Drawing.Point(0, 0);
            this.splitContainer1.Name = "splitContainer1";
            this.splitContainer1.Orientation = System.Windows.Forms.Orientation.Horizontal;
            // 
            // splitContainer1.Panel1
            // 
            this.splitContainer1.Panel1.Controls.Add(this.label3);
            this.splitContainer1.Panel1.Controls.Add(this.nudDiagFileExpiredDays);
            this.splitContainer1.Panel1.Controls.Add(this.cbxGlobalLoglevel);
            this.splitContainer1.Panel1.Controls.Add(this.label1);
            this.splitContainer1.Panel1.Controls.Add(this.rBtnIndependent);
            this.splitContainer1.Panel1.Controls.Add(this.rBtnGlobal);
            // 
            // splitContainer1.Panel2
            // 
            this.splitContainer1.Panel2.Controls.Add(this.flowLayoutPanel);
            this.splitContainer1.Size = new System.Drawing.Size(394, 336);
            this.splitContainer1.SplitterDistance = 132;
            this.splitContainer1.SplitterWidth = 1;
            this.splitContainer1.TabIndex = 21;
            // 
            // LogConfigPage
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.splitContainer1);
            this.Name = "LogConfigPage";
            this.Size = new System.Drawing.Size(394, 336);
            this.Load += new System.EventHandler(this.LogConfigPage_Load);
            ((System.ComponentModel.ISupportInitialize)(this.nudDiagFileExpiredDays)).EndInit();
            this.splitContainer1.Panel1.ResumeLayout(false);
            this.splitContainer1.Panel1.PerformLayout();
            this.splitContainer1.Panel2.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer1)).EndInit();
            this.splitContainer1.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.NumericUpDown nudDiagFileExpiredDays;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.RadioButton rBtnGlobal;
        private System.Windows.Forms.RadioButton rBtnIndependent;
        private System.Windows.Forms.ComboBox cbxGlobalLoglevel;
        private System.Windows.Forms.FlowLayoutPanel flowLayoutPanel;
        private System.Windows.Forms.SplitContainer splitContainer1;
    }
}
