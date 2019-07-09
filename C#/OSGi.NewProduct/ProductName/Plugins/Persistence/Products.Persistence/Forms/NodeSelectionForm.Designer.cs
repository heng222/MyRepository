namespace Products.Persistence
{
    partial class NodeSelectionForm
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.label1 = new System.Windows.Forms.Label();
            this.cbxNodeNames = new System.Windows.Forms.ComboBox();
            this.btnLaunch = new System.Windows.Forms.Button();
            this.btnCancel = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(14, 20);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(53, 12);
            this.label1.TabIndex = 0;
            this.label1.Text = "节点名称";
            // 
            // cbxNodeNames
            // 
            this.cbxNodeNames.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cbxNodeNames.FormattingEnabled = true;
            this.cbxNodeNames.Location = new System.Drawing.Point(69, 18);
            this.cbxNodeNames.Name = "cbxNodeNames";
            this.cbxNodeNames.Size = new System.Drawing.Size(275, 20);
            this.cbxNodeNames.TabIndex = 1;
            // 
            // btnLaunch
            // 
            this.btnLaunch.DialogResult = System.Windows.Forms.DialogResult.OK;
            this.btnLaunch.Location = new System.Drawing.Point(154, 55);
            this.btnLaunch.Name = "btnLaunch";
            this.btnLaunch.Size = new System.Drawing.Size(75, 23);
            this.btnLaunch.TabIndex = 2;
            this.btnLaunch.Text = "启动(&L)";
            this.btnLaunch.UseVisualStyleBackColor = true;
            // 
            // btnCancel
            // 
            this.btnCancel.DialogResult = System.Windows.Forms.DialogResult.Cancel;
            this.btnCancel.Location = new System.Drawing.Point(260, 55);
            this.btnCancel.Name = "btnCancel";
            this.btnCancel.Size = new System.Drawing.Size(75, 23);
            this.btnCancel.TabIndex = 3;
            this.btnCancel.Text = "取消(&C)";
            this.btnCancel.UseVisualStyleBackColor = true;
            // 
            // NodeSelectionForm
            // 
            this.AcceptButton = this.btnLaunch;
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.CancelButton = this.btnCancel;
            this.ClientSize = new System.Drawing.Size(368, 92);
            this.ControlBox = false;
            this.Controls.Add(this.btnCancel);
            this.Controls.Add(this.btnLaunch);
            this.Controls.Add(this.cbxNodeNames);
            this.Controls.Add(this.label1);
            this.Name = "NodeSelectionForm";
            this.ShowIcon = false;
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "选择期望启动的节点";
            this.TopMost = true;
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.ComboBox cbxNodeNames;
        private System.Windows.Forms.Button btnLaunch;
        private System.Windows.Forms.Button btnCancel;
    }
}