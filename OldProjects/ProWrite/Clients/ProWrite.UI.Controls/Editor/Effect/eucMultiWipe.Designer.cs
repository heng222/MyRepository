namespace ProWrite.UI.Controls.Editor.Effect
{
    partial class eucMultiWipe
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
            this.spVerticalWipes = new DevExpress.XtraEditors.SpinEdit();
            this.spHorizontalWipes = new DevExpress.XtraEditors.SpinEdit();
            this.lblHorizontalWipes = new DevExpress.XtraEditors.LabelControl();
            this.lblVerticalWipes = new DevExpress.XtraEditors.LabelControl();
            this.labelControl1 = new DevExpress.XtraEditors.LabelControl();
            this.labelControl2 = new DevExpress.XtraEditors.LabelControl();
            ((System.ComponentModel.ISupportInitialize)(this.spVerticalWipes.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.spHorizontalWipes.Properties)).BeginInit();
            this.SuspendLayout();
            // 
            // spVerticalWipes
            // 
            this.spVerticalWipes.EditValue = new decimal(new int[] {
            0,
            0,
            0,
            0});
            this.spVerticalWipes.Location = new System.Drawing.Point(129, 52);
            this.spVerticalWipes.Name = "spVerticalWipes";
            this.spVerticalWipes.Properties.Buttons.AddRange(new DevExpress.XtraEditors.Controls.EditorButton[] {
            new DevExpress.XtraEditors.Controls.EditorButton()});
            this.spVerticalWipes.Properties.MaxValue = new decimal(new int[] {
            50,
            0,
            0,
            0});
            this.spVerticalWipes.Size = new System.Drawing.Size(75, 20);
            this.spVerticalWipes.TabIndex = 8;
            // 
            // spHorizontalWipes
            // 
            this.spHorizontalWipes.EditValue = new decimal(new int[] {
            0,
            0,
            0,
            0});
            this.spHorizontalWipes.Location = new System.Drawing.Point(129, 15);
            this.spHorizontalWipes.Name = "spHorizontalWipes";
            this.spHorizontalWipes.Properties.Buttons.AddRange(new DevExpress.XtraEditors.Controls.EditorButton[] {
            new DevExpress.XtraEditors.Controls.EditorButton()});
            this.spHorizontalWipes.Properties.MaxValue = new decimal(new int[] {
            50,
            0,
            0,
            0});
            this.spHorizontalWipes.Size = new System.Drawing.Size(75, 20);
            this.spHorizontalWipes.TabIndex = 7;
            // 
            // lblHorizontalWipes
            // 
            this.lblHorizontalWipes.Location = new System.Drawing.Point(28, 18);
            this.lblHorizontalWipes.Name = "lblHorizontalWipes";
            this.lblHorizontalWipes.Size = new System.Drawing.Size(81, 13);
            this.lblHorizontalWipes.TabIndex = 6;
            this.lblHorizontalWipes.Text = "HorizontalWipes:";
            // 
            // lblVerticalWipes
            // 
            this.lblVerticalWipes.Location = new System.Drawing.Point(28, 55);
            this.lblVerticalWipes.Name = "lblVerticalWipes";
            this.lblVerticalWipes.Size = new System.Drawing.Size(68, 13);
            this.lblVerticalWipes.TabIndex = 5;
            this.lblVerticalWipes.Text = "VerticalWipes:";
            // 
            // labelControl1
            // 
            this.labelControl1.Location = new System.Drawing.Point(210, 18);
            this.labelControl1.Name = "labelControl1";
            this.labelControl1.Size = new System.Drawing.Size(22, 13);
            this.labelControl1.TabIndex = 5;
            this.labelControl1.Text = "0-50";
            this.labelControl1.Visible = false;
            // 
            // labelControl2
            // 
            this.labelControl2.Location = new System.Drawing.Point(210, 55);
            this.labelControl2.Name = "labelControl2";
            this.labelControl2.Size = new System.Drawing.Size(22, 13);
            this.labelControl2.TabIndex = 5;
            this.labelControl2.Text = "0-50";
            this.labelControl2.Visible = false;
            // 
            // eucMultiWipe
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.spVerticalWipes);
            this.Controls.Add(this.spHorizontalWipes);
            this.Controls.Add(this.lblHorizontalWipes);
            this.Controls.Add(this.labelControl2);
            this.Controls.Add(this.labelControl1);
            this.Controls.Add(this.lblVerticalWipes);
            this.Name = "eucMultiWipe";
            this.Size = new System.Drawing.Size(247, 91);
            ((System.ComponentModel.ISupportInitialize)(this.spVerticalWipes.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.spHorizontalWipes.Properties)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private DevExpress.XtraEditors.SpinEdit spVerticalWipes;
        private DevExpress.XtraEditors.SpinEdit spHorizontalWipes;
        private DevExpress.XtraEditors.LabelControl lblHorizontalWipes;
        private DevExpress.XtraEditors.LabelControl lblVerticalWipes;
        private DevExpress.XtraEditors.LabelControl labelControl1;
        private DevExpress.XtraEditors.LabelControl labelControl2;
    }
}
