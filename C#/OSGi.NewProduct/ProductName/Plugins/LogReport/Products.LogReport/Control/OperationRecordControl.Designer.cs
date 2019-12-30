namespace Products.LogReport.Control
{
    partial class OperationRecordControl
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
            this.cbxExecuteMode = new System.Windows.Forms.ComboBox();
            this.label6 = new System.Windows.Forms.Label();
            this.cmbOperateType = new System.Windows.Forms.ComboBox();
            this.label5 = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // cbxExecuteMode
            // 
            this.cbxExecuteMode.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cbxExecuteMode.FormattingEnabled = true;
            this.cbxExecuteMode.Items.AddRange(new object[] {
            "--请选择--",
            "自动执行",
            "手动执行"});
            this.cbxExecuteMode.Location = new System.Drawing.Point(663, 13);
            this.cbxExecuteMode.Name = "cbxExecuteMode";
            this.cbxExecuteMode.Size = new System.Drawing.Size(121, 20);
            this.cbxExecuteMode.TabIndex = 31;
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(606, 17);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(53, 12);
            this.label6.TabIndex = 30;
            this.label6.Text = "执行方式";
            // 
            // cmbOperateType
            // 
            this.cmbOperateType.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cmbOperateType.FormattingEnabled = true;
            this.cmbOperateType.Location = new System.Drawing.Point(464, 13);
            this.cmbOperateType.Name = "cmbOperateType";
            this.cmbOperateType.Size = new System.Drawing.Size(121, 20);
            this.cmbOperateType.TabIndex = 29;
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(408, 17);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(53, 12);
            this.label5.TabIndex = 28;
            this.label5.Text = "操作类型";
            // 
            // OperationRecordControl
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.cbxExecuteMode);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.cmbOperateType);
            this.Controls.Add(this.label5);
            this.Name = "OperationRecordControl";
            this.Controls.SetChildIndex(this.label5, 0);
            this.Controls.SetChildIndex(this.cmbOperateType, 0);
            this.Controls.SetChildIndex(this.label6, 0);
            this.Controls.SetChildIndex(this.cbxExecuteMode, 0);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ComboBox cbxExecuteMode;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.ComboBox cmbOperateType;
        private System.Windows.Forms.Label label5;

    }
}
