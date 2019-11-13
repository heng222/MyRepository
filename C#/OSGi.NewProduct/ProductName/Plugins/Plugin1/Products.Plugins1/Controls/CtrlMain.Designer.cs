namespace Products.Plugin1.Controls
{
    partial class CtrlMain
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
            this.btnGenerateSysEvent = new System.Windows.Forms.Button();
            this.btnGenerateOperationLog = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // btnGenerateSysEvent
            // 
            this.btnGenerateSysEvent.Location = new System.Drawing.Point(19, 21);
            this.btnGenerateSysEvent.Name = "btnGenerateSysEvent";
            this.btnGenerateSysEvent.Size = new System.Drawing.Size(136, 23);
            this.btnGenerateSysEvent.TabIndex = 1;
            this.btnGenerateSysEvent.Text = "产生一个系统事件";
            this.btnGenerateSysEvent.UseVisualStyleBackColor = true;
            this.btnGenerateSysEvent.Click += new System.EventHandler(this.btnGenerateSysEvent_Click);
            // 
            // btnGenerateOperationLog
            // 
            this.btnGenerateOperationLog.Location = new System.Drawing.Point(19, 62);
            this.btnGenerateOperationLog.Name = "btnGenerateOperationLog";
            this.btnGenerateOperationLog.Size = new System.Drawing.Size(136, 23);
            this.btnGenerateOperationLog.TabIndex = 2;
            this.btnGenerateOperationLog.Text = "产生一个操作记录";
            this.btnGenerateOperationLog.UseVisualStyleBackColor = true;
            this.btnGenerateOperationLog.Click += new System.EventHandler(this.btnGenerateOperationLog_Click);
            // 
            // CtrlMain
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.btnGenerateOperationLog);
            this.Controls.Add(this.btnGenerateSysEvent);
            this.Name = "CtrlMain";
            this.Size = new System.Drawing.Size(347, 220);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button btnGenerateSysEvent;
        private System.Windows.Forms.Button btnGenerateOperationLog;
    }
}
