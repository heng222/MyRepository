namespace ProWrite.UI.Clients.Test.FontSample
{
    partial class frmCLIForm
    {
        /// <summary>
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        ///<summary>
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

        #region Windows 窗体设计器生成的代码

        /// <summary>
        /// 设计器支持所需的方法 - 不要
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            this.button1 = new System.Windows.Forms.Button();
            this.btn_outline = new System.Windows.Forms.Button();
            this.BTN_NONEFFECT = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // button1
            // 
            this.button1.AutoSize = true;
            this.button1.Location = new System.Drawing.Point(91, 4);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(75, 25);
            this.button1.TabIndex = 1;
            this.button1.Text = "Shadow";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // btn_outline
            // 
            this.btn_outline.Location = new System.Drawing.Point(172, 4);
            this.btn_outline.Name = "btn_outline";
            this.btn_outline.Size = new System.Drawing.Size(75, 25);
            this.btn_outline.TabIndex = 2;
            this.btn_outline.Text = "Outline";
            this.btn_outline.UseVisualStyleBackColor = true;
            this.btn_outline.Click += new System.EventHandler(this.btn_outline_Click);
            // 
            // BTN_NONEFFECT
            // 
            this.BTN_NONEFFECT.Location = new System.Drawing.Point(10, 4);
            this.BTN_NONEFFECT.Name = "BTN_NONEFFECT";
            this.BTN_NONEFFECT.Size = new System.Drawing.Size(75, 25);
            this.BTN_NONEFFECT.TabIndex = 3;
            this.BTN_NONEFFECT.Text = "NoEffect";
            this.BTN_NONEFFECT.UseVisualStyleBackColor = true;
            this.BTN_NONEFFECT.Click += new System.EventHandler(this.NonEffect_Click);
            // 
            // frmCLIForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(426, 288);
            this.Controls.Add(this.BTN_NONEFFECT);
            this.Controls.Add(this.btn_outline);
            this.Controls.Add(this.button1);
            this.Name = "frmCLIForm";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "frmCLIForm";
            this.SizeChanged += new System.EventHandler(this.frmCLIForm_SizeChanged);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Button btn_outline;
        private System.Windows.Forms.Button BTN_NONEFFECT;
    }
}