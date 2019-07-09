namespace Products.Shell.ConfigView
{
    partial class GeneralConfigPage
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
            this.nudOptInterval = new System.Windows.Forms.NumericUpDown();
            this.label5 = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.nudOptInterval)).BeginInit();
            this.SuspendLayout();
            // 
            // nudOptInterval
            // 
            this.nudOptInterval.Location = new System.Drawing.Point(190, 22);
            this.nudOptInterval.Maximum = new decimal(new int[] {
            120,
            0,
            0,
            0});
            this.nudOptInterval.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.nudOptInterval.Name = "nudOptInterval";
            this.nudOptInterval.Size = new System.Drawing.Size(65, 21);
            this.nudOptInterval.TabIndex = 8;
            this.nudOptInterval.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(24, 25);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(161, 12);
            this.label5.TabIndex = 7;
            this.label5.Text = "程序运行时自动优化时间(分)";
            // 
            // OptionGenralView
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.Control;
            this.Controls.Add(this.nudOptInterval);
            this.Controls.Add(this.label5);
            this.Name = "OptionGenralView";
            this.Size = new System.Drawing.Size(350, 216);
            ((System.ComponentModel.ISupportInitialize)(this.nudOptInterval)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.NumericUpDown nudOptInterval;
        private System.Windows.Forms.Label label5;
    }
}
