namespace ProWrite.UI.Controls.Editor.Effect
{
    partial class eucLine
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

        #region Component Designer generated code

        /// <summary> 
        /// Required method for Designer support - do not modify 
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.ddlLagSpacing = new DevExpress.XtraEditors.SpinEdit();
            this.label2 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.ddlDirection = new DevExpress.XtraEditors.ComboBoxEdit();
            this.label4 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.ddlPullPoint = new DevExpress.XtraEditors.SpinEdit();
            this.label3 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.ddlLineWidth = new DevExpress.XtraEditors.SpinEdit();
            this.label7 = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.ddlLagSpacing.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.ddlDirection.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.ddlPullPoint.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.ddlLineWidth.Properties)).BeginInit();
            this.SuspendLayout();
            // 
            // ddlLagSpacing
            // 
            this.ddlLagSpacing.EditValue = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.ddlLagSpacing.Location = new System.Drawing.Point(124, 77);
            this.ddlLagSpacing.Name = "ddlLagSpacing";
            this.ddlLagSpacing.Properties.Buttons.AddRange(new DevExpress.XtraEditors.Controls.EditorButton[] {
            new DevExpress.XtraEditors.Controls.EditorButton()});
            this.ddlLagSpacing.Properties.MaxValue = new decimal(new int[] {
            100,
            0,
            0,
            0});
            this.ddlLagSpacing.Properties.MinValue = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.ddlLagSpacing.Size = new System.Drawing.Size(122, 21);
            this.ddlLagSpacing.TabIndex = 18;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(47, 82);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(65, 12);
            this.label2.TabIndex = 17;
            this.label2.Text = "Lag Spacing";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(252, 82);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(47, 12);
            this.label5.TabIndex = 21;
            this.label5.Text = "(1-100)";
            // 
            // ddlDirection
            // 
            this.ddlDirection.Location = new System.Drawing.Point(124, 12);
            this.ddlDirection.Name = "ddlDirection";
            this.ddlDirection.Properties.Buttons.AddRange(new DevExpress.XtraEditors.Controls.EditorButton[] {
            new DevExpress.XtraEditors.Controls.EditorButton(DevExpress.XtraEditors.Controls.ButtonPredefines.Combo)});
            this.ddlDirection.Size = new System.Drawing.Size(122, 21);
            this.ddlDirection.TabIndex = 23;
            this.ddlDirection.SelectedIndexChanged += new System.EventHandler(ddlDirection_SelectedIndexChanged);
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(47, 17);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(59, 12);
            this.label4.TabIndex = 22;
            this.label4.Text = "Direction";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(252, 49);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(53, 12);
            this.label1.TabIndex = 26;
            this.label1.Text = "(1-1000)";
            this.label1.Visible = false;
            // 
            // ddlPullPoint
            // 
            this.ddlPullPoint.EditValue = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.ddlPullPoint.Location = new System.Drawing.Point(124, 44);
            this.ddlPullPoint.Name = "ddlPullPoint";
            this.ddlPullPoint.Properties.Buttons.AddRange(new DevExpress.XtraEditors.Controls.EditorButton[] {
            new DevExpress.XtraEditors.Controls.EditorButton()});
            this.ddlPullPoint.Properties.MaxValue = new decimal(new int[] {
            1000,
            0,
            0,
            0});
            this.ddlPullPoint.Properties.MinValue = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.ddlPullPoint.Size = new System.Drawing.Size(122, 21);
            this.ddlPullPoint.TabIndex = 25;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(47, 49);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(59, 12);
            this.label3.TabIndex = 24;
            this.label3.Text = "Pull Point";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(252, 115);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(47, 12);
            this.label6.TabIndex = 29;
            this.label6.Text = "(1-100)";
            // 
            // ddlLineWidth
            // 
            this.ddlLineWidth.EditValue = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.ddlLineWidth.Location = new System.Drawing.Point(124, 110);
            this.ddlLineWidth.Name = "ddlLineWidth";
            this.ddlLineWidth.Properties.Buttons.AddRange(new DevExpress.XtraEditors.Controls.EditorButton[] {
            new DevExpress.XtraEditors.Controls.EditorButton()});
            this.ddlLineWidth.Properties.MaxValue = new decimal(new int[] {
            100,
            0,
            0,
            0});
            this.ddlLineWidth.Properties.MinValue = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.ddlLineWidth.Size = new System.Drawing.Size(122, 21);
            this.ddlLineWidth.TabIndex = 28;
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(47, 115);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(59, 12);
            this.label7.TabIndex = 27;
            this.label7.Text = "Line Width";
            // 
            // eucLine
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.label6);
            this.Controls.Add(this.ddlLineWidth);
            this.Controls.Add(this.label7);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.ddlPullPoint);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.ddlDirection);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.ddlLagSpacing);
            this.Controls.Add(this.label2);
            this.Name = "eucLine";
            ((System.ComponentModel.ISupportInitialize)(this.ddlLagSpacing.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.ddlDirection.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.ddlPullPoint.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.ddlLineWidth.Properties)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }



        #endregion

        private DevExpress.XtraEditors.SpinEdit ddlLagSpacing;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label5;
        private DevExpress.XtraEditors.ComboBoxEdit ddlDirection;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label1;
        private DevExpress.XtraEditors.SpinEdit ddlPullPoint;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label6;
        private DevExpress.XtraEditors.SpinEdit ddlLineWidth;
        private System.Windows.Forms.Label label7;
    }
}
