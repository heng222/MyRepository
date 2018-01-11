namespace CShapApp
{
    partial class Form1
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

        #region Windows 窗体设计器生成的代码

        /// <summary>
        /// 设计器支持所需的方法 - 不要
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            this.button1 = new System.Windows.Forms.Button();
            this.tabControl1 = new System.Windows.Forms.TabControl();
            this.tabPagePscada = new System.Windows.Forms.TabPage();
            this.tabPageBas = new System.Windows.Forms.TabPage();
            this.btnShowBasView = new System.Windows.Forms.Button();
            this.tabControl1.SuspendLayout();
            this.SuspendLayout();
            // 
            // button1
            // 
            this.button1.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.button1.Location = new System.Drawing.Point(16, 334);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(92, 28);
            this.button1.TabIndex = 0;
            this.button1.Text = "显示PACADA";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.ShowPscada_Click);
            // 
            // tabControl1
            // 
            this.tabControl1.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.tabControl1.Controls.Add(this.tabPagePscada);
            this.tabControl1.Controls.Add(this.tabPageBas);
            this.tabControl1.Location = new System.Drawing.Point(12, 12);
            this.tabControl1.Name = "tabControl1";
            this.tabControl1.SelectedIndex = 0;
            this.tabControl1.Size = new System.Drawing.Size(681, 302);
            this.tabControl1.TabIndex = 1;
            // 
            // tabPagePscada
            // 
            this.tabPagePscada.Location = new System.Drawing.Point(4, 22);
            this.tabPagePscada.Name = "tabPagePscada";
            this.tabPagePscada.Padding = new System.Windows.Forms.Padding(3);
            this.tabPagePscada.Size = new System.Drawing.Size(673, 276);
            this.tabPagePscada.TabIndex = 0;
            this.tabPagePscada.Text = "PSCADA";
            this.tabPagePscada.UseVisualStyleBackColor = true;
            // 
            // tabPageBas
            // 
            this.tabPageBas.Location = new System.Drawing.Point(4, 22);
            this.tabPageBas.Name = "tabPageBas";
            this.tabPageBas.Padding = new System.Windows.Forms.Padding(3);
            this.tabPageBas.Size = new System.Drawing.Size(673, 276);
            this.tabPageBas.TabIndex = 1;
            this.tabPageBas.Text = "BAS";
            this.tabPageBas.UseVisualStyleBackColor = true;
            // 
            // btnShowBasView
            // 
            this.btnShowBasView.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.btnShowBasView.Location = new System.Drawing.Point(143, 334);
            this.btnShowBasView.Name = "btnShowBasView";
            this.btnShowBasView.Size = new System.Drawing.Size(96, 28);
            this.btnShowBasView.TabIndex = 2;
            this.btnShowBasView.Text = "显示BAS";
            this.btnShowBasView.UseVisualStyleBackColor = true;
            this.btnShowBasView.Click += new System.EventHandler(this.btnShowBasView_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(705, 379);
            this.Controls.Add(this.btnShowBasView);
            this.Controls.Add(this.tabControl1);
            this.Controls.Add(this.button1);
            this.Name = "Form1";
            this.Text = "FormDemo";
            this.tabControl1.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.TabControl tabControl1;
        private System.Windows.Forms.TabPage tabPagePscada;
        private System.Windows.Forms.TabPage tabPageBas;
        private System.Windows.Forms.Button btnShowBasView;
    }
}

