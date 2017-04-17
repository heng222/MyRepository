namespace ProWrite.UI.Controls.Editor.Effect
{
    partial class eucWrapAround
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
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.ddlBackColor = new PWColorEdit();
            this.tracRate = new DevExpress.XtraEditors.TrackBarControl();
            this.ddlDirection = new DevExpress.XtraEditors.ComboBoxEdit();
            this.label1 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.spinSpacing = new DevExpress.XtraEditors.SpinEdit();
            ((System.ComponentModel.ISupportInitialize)(this.ddlBackColor.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.tracRate)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.tracRate.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.ddlDirection.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.spinSpacing.Properties)).BeginInit();
            this.SuspendLayout();
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(44, 11);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(30, 13);
            this.label2.TabIndex = 2;
            this.label2.Text = "Rate";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(160, 13);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(56, 13);
            this.label3.TabIndex = 4;
            this.label3.Text = "BackColor";
            this.label3.Visible = false;
            // 
            // ddlBackColor
            // 
            this.ddlBackColor.EditValue = System.Drawing.Color.Empty;
            this.ddlBackColor.Location = new System.Drawing.Point(227, 10);
            this.ddlBackColor.Name = "ddlBackColor";
            this.ddlBackColor.Properties.Buttons.AddRange(new DevExpress.XtraEditors.Controls.EditorButton[] {
            new DevExpress.XtraEditors.Controls.EditorButton(DevExpress.XtraEditors.Controls.ButtonPredefines.Combo)});
            this.ddlBackColor.Size = new System.Drawing.Size(96, 20);
            this.ddlBackColor.TabIndex = 5;
            this.ddlBackColor.Visible = false;
            // 
            // tracRate
            // 
            this.tracRate.EditValue = 5;
            this.tracRate.Location = new System.Drawing.Point(90, 11);
            this.tracRate.Name = "tracRate";
            this.tracRate.Properties.AutoSize = false;
            this.tracRate.Properties.BorderStyle = DevExpress.XtraEditors.Controls.BorderStyles.Simple;
            this.tracRate.Properties.Maximum = 96;
            this.tracRate.Properties.Minimum = 1;
            this.tracRate.Properties.Orientation = System.Windows.Forms.Orientation.Vertical;
            this.tracRate.Size = new System.Drawing.Size(32, 153);
            this.tracRate.TabIndex = 7;
            this.tracRate.Value = 5;
            // 
            // ddlDirection
            // 
            this.ddlDirection.Location = new System.Drawing.Point(227, 10);
            this.ddlDirection.Name = "ddlDirection";
            this.ddlDirection.Properties.Buttons.AddRange(new DevExpress.XtraEditors.Controls.EditorButton[] {
            new DevExpress.XtraEditors.Controls.EditorButton(DevExpress.XtraEditors.Controls.ButtonPredefines.Combo)});
            this.ddlDirection.Size = new System.Drawing.Size(96, 20);
            this.ddlDirection.TabIndex = 11;
            ddlDirection.SelectedIndexChanged +=new System.EventHandler(ddlDirection_SelectedIndexChanged);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(160, 13);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(49, 13);
            this.label1.TabIndex = 12;
            this.label1.Text = "Direction";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(160, 61);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(46, 13);
            this.label4.TabIndex = 12;
            this.label4.Text = "Spacing\r\n";
            // 
            // spinSpacing
            // 
            this.spinSpacing.EditValue = new decimal(new int[] {
            0,
            0,
            0,
            0});
            this.spinSpacing.Location = new System.Drawing.Point(227, 58);
            this.spinSpacing.Name = "spinSpacing";
            this.spinSpacing.Properties.Buttons.AddRange(new DevExpress.XtraEditors.Controls.EditorButton[] {
            new DevExpress.XtraEditors.Controls.EditorButton()});
            this.spinSpacing.Size = new System.Drawing.Size(100, 20);
            this.spinSpacing.TabIndex = 33;
            // 
            // eucWrapAround
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.spinSpacing);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.ddlDirection);
            this.Controls.Add(this.tracRate);
            this.Controls.Add(this.ddlBackColor);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Name = "eucWrapAround";
            this.Size = new System.Drawing.Size(362, 208);
            ((System.ComponentModel.ISupportInitialize)(this.ddlBackColor.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.tracRate.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.tracRate)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.ddlDirection.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.spinSpacing.Properties)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private PWColorEdit ddlBackColor;
        private DevExpress.XtraEditors.TrackBarControl tracRate;
        private DevExpress.XtraEditors.ComboBoxEdit ddlDirection;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label4;
        private DevExpress.XtraEditors.SpinEdit spinSpacing;
    }
}
