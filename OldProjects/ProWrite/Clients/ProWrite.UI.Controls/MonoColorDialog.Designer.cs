namespace ProWrite.UI.Controls
{
    partial class MonoColorDialog
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
            this.btnOk = new DevExpress.XtraEditors.SimpleButton();
            this.btnCancel = new DevExpress.XtraEditors.SimpleButton();
            this.labelControl1 = new DevExpress.XtraEditors.LabelControl();
            this.labelControl2 = new DevExpress.XtraEditors.LabelControl();
            this.labelControl3 = new DevExpress.XtraEditors.LabelControl();
            this.labelControl4 = new DevExpress.XtraEditors.LabelControl();
            this.labelControl5 = new DevExpress.XtraEditors.LabelControl();
            this.labelControl6 = new DevExpress.XtraEditors.LabelControl();
            this.labelControl7 = new DevExpress.XtraEditors.LabelControl();
            this.txtBoxHue = new System.Windows.Forms.TextBox();
            this.txtBoxBlue = new System.Windows.Forms.TextBox();
            this.txtBoxGreen = new System.Windows.Forms.TextBox();
            this.txtBoxRed = new System.Windows.Forms.TextBox();
            this.txtBoxLum = new System.Windows.Forms.TextBox();
            this.txtBoxSat = new System.Windows.Forms.TextBox();
            this.m_colorSample = new ProWrite.UI.Controls.LabelRotate();
            this.hslColorSlider1 = new ProWrite.UI.Controls.PWColorSlider();
            this.SuspendLayout();
            // 
            // btnOk
            // 
            this.btnOk.Location = new System.Drawing.Point(88, 232);
            this.btnOk.Name = "btnOk";
            this.btnOk.Size = new System.Drawing.Size(48, 23);
            this.btnOk.TabIndex = 13;
            this.btnOk.Text = "OK";
            this.btnOk.Click += new System.EventHandler(this.btnOk_Click);
            // 
            // btnCancel
            // 
            this.btnCancel.DialogResult = System.Windows.Forms.DialogResult.Cancel;
            this.btnCancel.Location = new System.Drawing.Point(143, 232);
            this.btnCancel.Name = "btnCancel";
            this.btnCancel.Size = new System.Drawing.Size(44, 23);
            this.btnCancel.TabIndex = 14;
            this.btnCancel.Text = "Cancel";
            this.btnCancel.Click += new System.EventHandler(this.btnCancel_Click);
            // 
            // labelControl1
            // 
            this.labelControl1.Location = new System.Drawing.Point(56, 6);
            this.labelControl1.Name = "labelControl1";
            this.labelControl1.Size = new System.Drawing.Size(51, 13);
            this.labelControl1.TabIndex = 15;
            this.labelControl1.Text = "Color|Solid";
            // 
            // labelControl2
            // 
            this.labelControl2.Location = new System.Drawing.Point(58, 135);
            this.labelControl2.Name = "labelControl2";
            this.labelControl2.Size = new System.Drawing.Size(23, 13);
            this.labelControl2.TabIndex = 16;
            this.labelControl2.Text = "Hue:";
            // 
            // labelControl3
            // 
            this.labelControl3.Location = new System.Drawing.Point(61, 162);
            this.labelControl3.Name = "labelControl3";
            this.labelControl3.Size = new System.Drawing.Size(20, 13);
            this.labelControl3.TabIndex = 17;
            this.labelControl3.Text = "Sat:";
            // 
            // labelControl4
            // 
            this.labelControl4.Location = new System.Drawing.Point(58, 189);
            this.labelControl4.Name = "labelControl4";
            this.labelControl4.Size = new System.Drawing.Size(23, 13);
            this.labelControl4.TabIndex = 18;
            this.labelControl4.Text = "Lum:";
            // 
            // labelControl5
            // 
            this.labelControl5.Location = new System.Drawing.Point(129, 189);
            this.labelControl5.Name = "labelControl5";
            this.labelControl5.Size = new System.Drawing.Size(24, 13);
            this.labelControl5.TabIndex = 21;
            this.labelControl5.Text = "Blue:";
            // 
            // labelControl6
            // 
            this.labelControl6.Location = new System.Drawing.Point(120, 162);
            this.labelControl6.Name = "labelControl6";
            this.labelControl6.Size = new System.Drawing.Size(33, 13);
            this.labelControl6.TabIndex = 20;
            this.labelControl6.Text = "Green:";
            // 
            // labelControl7
            // 
            this.labelControl7.Location = new System.Drawing.Point(130, 135);
            this.labelControl7.Name = "labelControl7";
            this.labelControl7.Size = new System.Drawing.Size(23, 13);
            this.labelControl7.TabIndex = 19;
            this.labelControl7.Text = "Red:";
            // 
            // txtBoxHue
            // 
            this.txtBoxHue.Location = new System.Drawing.Point(88, 135);
            this.txtBoxHue.Name = "txtBoxHue";
            this.txtBoxHue.Size = new System.Drawing.Size(28, 21);
            this.txtBoxHue.TabIndex = 22;
            this.txtBoxHue.Text = "255";
            // 
            // txtBoxBlue
            // 
            this.txtBoxBlue.Location = new System.Drawing.Point(159, 189);
            this.txtBoxBlue.Name = "txtBoxBlue";
            this.txtBoxBlue.Size = new System.Drawing.Size(28, 21);
            this.txtBoxBlue.TabIndex = 23;
            this.txtBoxBlue.Text = "255";
            // 
            // txtBoxGreen
            // 
            this.txtBoxGreen.Location = new System.Drawing.Point(159, 162);
            this.txtBoxGreen.Name = "txtBoxGreen";
            this.txtBoxGreen.Size = new System.Drawing.Size(28, 21);
            this.txtBoxGreen.TabIndex = 24;
            this.txtBoxGreen.Text = "255";
            // 
            // txtBoxRed
            // 
            this.txtBoxRed.Location = new System.Drawing.Point(159, 135);
            this.txtBoxRed.Name = "txtBoxRed";
            this.txtBoxRed.Size = new System.Drawing.Size(28, 21);
            this.txtBoxRed.TabIndex = 25;
            this.txtBoxRed.Text = "255";
            // 
            // txtBoxLum
            // 
            this.txtBoxLum.Location = new System.Drawing.Point(88, 190);
            this.txtBoxLum.Name = "txtBoxLum";
            this.txtBoxLum.Size = new System.Drawing.Size(28, 21);
            this.txtBoxLum.TabIndex = 26;
            this.txtBoxLum.Text = "255";
            // 
            // txtBoxSat
            // 
            this.txtBoxSat.Location = new System.Drawing.Point(88, 162);
            this.txtBoxSat.Name = "txtBoxSat";
            this.txtBoxSat.Size = new System.Drawing.Size(28, 21);
            this.txtBoxSat.TabIndex = 27;
            this.txtBoxSat.Text = "255";
            // 
            // m_colorSample
            // 
            this.m_colorSample.Location = new System.Drawing.Point(56, 23);
            this.m_colorSample.Name = "m_colorSample";
            this.m_colorSample.RotatePointAlignment = System.Drawing.ContentAlignment.MiddleCenter;
            this.m_colorSample.Size = new System.Drawing.Size(131, 95);
            this.m_colorSample.TabIndex = 11;
            this.m_colorSample.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.m_colorSample.TextAngle = 0F;
            this.m_colorSample.Paint += new System.Windows.Forms.PaintEventHandler(this.labelRotate2_Paint);
            // 
            // hslColorSlider1
            // 
            this.hslColorSlider1.BarPadding = new System.Windows.Forms.Padding(12, 5, 24, 10);
            this.hslColorSlider1.Color1 = System.Drawing.Color.Black;
            this.hslColorSlider1.Color2 = System.Drawing.Color.White;
            this.hslColorSlider1.Color3 = System.Drawing.Color.Transparent;
            this.hslColorSlider1.ForeColor = System.Drawing.Color.Black;
            this.hslColorSlider1.Location = new System.Drawing.Point(12, 7);
            this.hslColorSlider1.Name = "hslColorSlider1";
            this.hslColorSlider1.NumberOfColors = ProWrite.UI.Controls.ColorSlider.eNumberOfColors.Use2Colors;
            this.hslColorSlider1.Orientation = System.Windows.Forms.Orientation.Vertical;
            this.hslColorSlider1.Percent = 0F;
            this.hslColorSlider1.RotatePointAlignment = System.Drawing.ContentAlignment.MiddleCenter;
            this.hslColorSlider1.Size = new System.Drawing.Size(38, 203);
            this.hslColorSlider1.TabIndex = 0;
            this.hslColorSlider1.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.hslColorSlider1.TextAngle = 0F;
            this.hslColorSlider1.ValueOrientation = ProWrite.UI.Controls.ColorSlider.eValueOrientation.MaxToMin;
            this.hslColorSlider1.SelectedValueChanged += new System.EventHandler(this.hslColorSlider1_SelectedValueChanged);
            // 
            // MonoColorDialog
            // 
            this.AcceptButton = this.btnOk;
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.CancelButton = this.btnCancel;
            this.ClientSize = new System.Drawing.Size(200, 267);
            this.Controls.Add(this.txtBoxSat);
            this.Controls.Add(this.txtBoxLum);
            this.Controls.Add(this.txtBoxRed);
            this.Controls.Add(this.txtBoxGreen);
            this.Controls.Add(this.txtBoxBlue);
            this.Controls.Add(this.txtBoxHue);
            this.Controls.Add(this.labelControl5);
            this.Controls.Add(this.labelControl6);
            this.Controls.Add(this.labelControl7);
            this.Controls.Add(this.labelControl4);
            this.Controls.Add(this.labelControl3);
            this.Controls.Add(this.labelControl2);
            this.Controls.Add(this.labelControl1);
            this.Controls.Add(this.btnCancel);
            this.Controls.Add(this.btnOk);
            this.Controls.Add(this.m_colorSample);
            this.Controls.Add(this.hslColorSlider1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "MonoColorDialog";
            this.ShowIcon = false;
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
            this.Text = "Color";
            this.TopMost = true;
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private PWColorSlider hslColorSlider1;
        private LabelRotate m_colorSample;
        private DevExpress.XtraEditors.SimpleButton btnOk;
        private DevExpress.XtraEditors.SimpleButton btnCancel;
        private DevExpress.XtraEditors.LabelControl labelControl1;
        private DevExpress.XtraEditors.LabelControl labelControl2;
        private DevExpress.XtraEditors.LabelControl labelControl3;
        private DevExpress.XtraEditors.LabelControl labelControl4;
        private DevExpress.XtraEditors.LabelControl labelControl5;
        private DevExpress.XtraEditors.LabelControl labelControl6;
        private DevExpress.XtraEditors.LabelControl labelControl7;
        private System.Windows.Forms.TextBox txtBoxHue;
        private System.Windows.Forms.TextBox txtBoxBlue;
        private System.Windows.Forms.TextBox txtBoxGreen;
        private System.Windows.Forms.TextBox txtBoxRed;
        private System.Windows.Forms.TextBox txtBoxLum;
        private System.Windows.Forms.TextBox txtBoxSat;
    }
}