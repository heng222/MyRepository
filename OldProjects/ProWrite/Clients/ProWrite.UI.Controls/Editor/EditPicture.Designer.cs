namespace ProWrite.UI.Controls.Editor
{
    partial class EditPicture
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
            this.xtraTabControl1 = new DevExpress.XtraTab.XtraTabControl();
            this.xtraTabPage1 = new DevExpress.XtraTab.XtraTabPage();
            this.simpleButton1 = new DevExpress.XtraEditors.SimpleButton();
            this.rdbOriginalPictureRatio = new System.Windows.Forms.RadioButton();
            this.rdbOverallSignRatio = new System.Windows.Forms.RadioButton();
            this.rdbBoxLayerRatio = new System.Windows.Forms.RadioButton();
            this.rdbNormal = new System.Windows.Forms.RadioButton();
            this.xtraTabPage2 = new DevExpress.XtraTab.XtraTabPage();
            this.simpleButton2 = new DevExpress.XtraEditors.SimpleButton();
            this.btnHorizontal = new DevExpress.XtraEditors.SimpleButton();
            this.btnFlipVertical = new DevExpress.XtraEditors.SimpleButton();
            this.btnRotateLeft = new DevExpress.XtraEditors.SimpleButton();
            this.btnRotatRight = new DevExpress.XtraEditors.SimpleButton();
            this.o = new DevExpress.XtraTab.XtraTabPage();
            this.lblTransparency = new DevExpress.XtraEditors.LabelControl();
            this.lblContrast = new DevExpress.XtraEditors.LabelControl();
            this.labelControl1 = new DevExpress.XtraEditors.LabelControl();
            this.trackBarControl3 = new DevExpress.XtraEditors.TrackBarControl();
            this.tbarCantrast = new DevExpress.XtraEditors.TrackBarControl();
            this.tbarBrightness = new DevExpress.XtraEditors.TrackBarControl();
            this.spnTransparency = new DevExpress.XtraEditors.SpinEdit();
            this.spinEdit2 = new DevExpress.XtraEditors.SpinEdit();
            this.spinEdit1 = new DevExpress.XtraEditors.SpinEdit();
            this.btnApply = new DevExpress.XtraEditors.SimpleButton();
            this.btnReset = new DevExpress.XtraEditors.SimpleButton();
            this.btnOk = new DevExpress.XtraEditors.SimpleButton();
            this.btnCancel = new DevExpress.XtraEditors.SimpleButton();
            this.pictureBox1 = new DevExpress.XtraEditors.PictureEdit();
            this.lblStatus = new DevExpress.XtraEditors.LabelControl();
            ((System.ComponentModel.ISupportInitialize)(this.xtraTabControl1)).BeginInit();
            this.xtraTabControl1.SuspendLayout();
            this.xtraTabPage1.SuspendLayout();
            this.xtraTabPage2.SuspendLayout();
            this.o.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.trackBarControl3)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.trackBarControl3.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.tbarCantrast)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.tbarCantrast.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.tbarBrightness)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.tbarBrightness.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.spnTransparency.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.spinEdit2.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.spinEdit1.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1.Properties)).BeginInit();
            this.SuspendLayout();
            // 
            // xtraTabControl1
            // 
            this.xtraTabControl1.Location = new System.Drawing.Point(338, 20);
            this.xtraTabControl1.Name = "xtraTabControl1";
            this.xtraTabControl1.SelectedTabPage = this.xtraTabPage1;
            this.xtraTabControl1.Size = new System.Drawing.Size(311, 334);
            this.xtraTabControl1.TabIndex = 0;
            this.xtraTabControl1.TabPages.AddRange(new DevExpress.XtraTab.XtraTabPage[] {
            this.xtraTabPage1,
            this.xtraTabPage2,
            this.o});
            this.xtraTabControl1.SelectedPageChanged += new DevExpress.XtraTab.TabPageChangedEventHandler(this.xtraTabControl1_SelectedPageChanged);
            // 
            // xtraTabPage1
            // 
            this.xtraTabPage1.Controls.Add(this.simpleButton1);
            this.xtraTabPage1.Controls.Add(this.rdbOriginalPictureRatio);
            this.xtraTabPage1.Controls.Add(this.rdbOverallSignRatio);
            this.xtraTabPage1.Controls.Add(this.rdbBoxLayerRatio);
            this.xtraTabPage1.Controls.Add(this.rdbNormal);
            this.xtraTabPage1.Name = "xtraTabPage1";
            this.xtraTabPage1.Size = new System.Drawing.Size(302, 303);
            this.xtraTabPage1.Text = "Crop";
            // 
            // simpleButton1
            // 
            this.simpleButton1.Location = new System.Drawing.Point(213, 277);
            this.simpleButton1.Name = "simpleButton1";
            this.simpleButton1.Size = new System.Drawing.Size(75, 23);
            this.simpleButton1.TabIndex = 2;
            this.simpleButton1.Text = "Apply";
            this.simpleButton1.Click += new System.EventHandler(this.btnApply_Click);
            // 
            // rdbOriginalPictureRatio
            // 
            this.rdbOriginalPictureRatio.AutoSize = true;
            this.rdbOriginalPictureRatio.Location = new System.Drawing.Point(114, 170);
            this.rdbOriginalPictureRatio.Name = "rdbOriginalPictureRatio";
            this.rdbOriginalPictureRatio.Size = new System.Drawing.Size(125, 17);
            this.rdbOriginalPictureRatio.TabIndex = 1;
            this.rdbOriginalPictureRatio.Text = "Original Picture Ratio";
            this.rdbOriginalPictureRatio.UseVisualStyleBackColor = true;
            this.rdbOriginalPictureRatio.CheckedChanged += new System.EventHandler(this.rdbNormal_CheckedChanged);
            // 
            // rdbOverallSignRatio
            // 
            this.rdbOverallSignRatio.AutoSize = true;
            this.rdbOverallSignRatio.Location = new System.Drawing.Point(114, 125);
            this.rdbOverallSignRatio.Name = "rdbOverallSignRatio";
            this.rdbOverallSignRatio.Size = new System.Drawing.Size(110, 17);
            this.rdbOverallSignRatio.TabIndex = 1;
            this.rdbOverallSignRatio.Text = "Overall Sign Ratio";
            this.rdbOverallSignRatio.UseVisualStyleBackColor = true;
            this.rdbOverallSignRatio.CheckedChanged += new System.EventHandler(this.rdbNormal_CheckedChanged);
            // 
            // rdbBoxLayerRatio
            // 
            this.rdbBoxLayerRatio.AutoSize = true;
            this.rdbBoxLayerRatio.Location = new System.Drawing.Point(114, 86);
            this.rdbBoxLayerRatio.Name = "rdbBoxLayerRatio";
            this.rdbBoxLayerRatio.Size = new System.Drawing.Size(101, 17);
            this.rdbBoxLayerRatio.TabIndex = 1;
            this.rdbBoxLayerRatio.Text = "Box Layer Ratio";
            this.rdbBoxLayerRatio.UseVisualStyleBackColor = true;
            this.rdbBoxLayerRatio.CheckedChanged += new System.EventHandler(this.rdbNormal_CheckedChanged);
            // 
            // rdbNormal
            // 
            this.rdbNormal.AutoSize = true;
            this.rdbNormal.Checked = true;
            this.rdbNormal.Location = new System.Drawing.Point(114, 51);
            this.rdbNormal.Name = "rdbNormal";
            this.rdbNormal.Size = new System.Drawing.Size(58, 17);
            this.rdbNormal.TabIndex = 1;
            this.rdbNormal.TabStop = true;
            this.rdbNormal.Text = "Normal";
            this.rdbNormal.UseVisualStyleBackColor = true;
            this.rdbNormal.CheckedChanged += new System.EventHandler(this.rdbNormal_CheckedChanged);
            // 
            // xtraTabPage2
            // 
            this.xtraTabPage2.Controls.Add(this.simpleButton2);
            this.xtraTabPage2.Controls.Add(this.btnHorizontal);
            this.xtraTabPage2.Controls.Add(this.btnFlipVertical);
            this.xtraTabPage2.Controls.Add(this.btnRotateLeft);
            this.xtraTabPage2.Controls.Add(this.btnRotatRight);
            this.xtraTabPage2.Name = "xtraTabPage2";
            this.xtraTabPage2.Size = new System.Drawing.Size(302, 303);
            this.xtraTabPage2.Text = "Rotate";
            // 
            // simpleButton2
            // 
            this.simpleButton2.Location = new System.Drawing.Point(213, 277);
            this.simpleButton2.Name = "simpleButton2";
            this.simpleButton2.Size = new System.Drawing.Size(75, 23);
            this.simpleButton2.TabIndex = 1;
            this.simpleButton2.Text = "Apply";
            this.simpleButton2.Click += new System.EventHandler(this.btnApply_Click);
            // 
            // btnHorizontal
            // 
            this.btnHorizontal.Location = new System.Drawing.Point(115, 161);
            this.btnHorizontal.Name = "btnHorizontal";
            this.btnHorizontal.Size = new System.Drawing.Size(145, 23);
            this.btnHorizontal.TabIndex = 0;
            this.btnHorizontal.Text = "Flip Horizontal";
            this.btnHorizontal.Click += new System.EventHandler(this.btnHorizontal_Click);
            // 
            // btnFlipVertical
            // 
            this.btnFlipVertical.Location = new System.Drawing.Point(115, 120);
            this.btnFlipVertical.Name = "btnFlipVertical";
            this.btnFlipVertical.Size = new System.Drawing.Size(145, 23);
            this.btnFlipVertical.TabIndex = 0;
            this.btnFlipVertical.Text = "Flip Vertical";
            this.btnFlipVertical.Click += new System.EventHandler(this.btnFlipVertical_Click);
            // 
            // btnRotateLeft
            // 
            this.btnRotateLeft.Location = new System.Drawing.Point(115, 77);
            this.btnRotateLeft.Name = "btnRotateLeft";
            this.btnRotateLeft.Size = new System.Drawing.Size(145, 23);
            this.btnRotateLeft.TabIndex = 0;
            this.btnRotateLeft.Text = "Rotate Left 90°";
            this.btnRotateLeft.Click += new System.EventHandler(this.btnRotateLeft_Click);
            // 
            // btnRotatRight
            // 
            this.btnRotatRight.Location = new System.Drawing.Point(115, 39);
            this.btnRotatRight.Name = "btnRotatRight";
            this.btnRotatRight.Size = new System.Drawing.Size(145, 23);
            this.btnRotatRight.TabIndex = 0;
            this.btnRotatRight.Text = "Rotate Right 90°";
            this.btnRotatRight.Click += new System.EventHandler(this.btnRotatRight_Click);
            // 
            // o
            // 
            this.o.Controls.Add(this.lblTransparency);
            this.o.Controls.Add(this.lblContrast);
            this.o.Controls.Add(this.labelControl1);
            this.o.Controls.Add(this.trackBarControl3);
            this.o.Controls.Add(this.tbarCantrast);
            this.o.Controls.Add(this.tbarBrightness);
            this.o.Controls.Add(this.spnTransparency);
            this.o.Controls.Add(this.spinEdit2);
            this.o.Controls.Add(this.spinEdit1);
            this.o.Controls.Add(this.btnApply);
            this.o.Name = "o";
            this.o.Size = new System.Drawing.Size(302, 303);
            this.o.Text = "Image";
            // 
            // lblTransparency
            // 
            this.lblTransparency.Location = new System.Drawing.Point(18, 148);
            this.lblTransparency.Name = "lblTransparency";
            this.lblTransparency.Size = new System.Drawing.Size(66, 13);
            this.lblTransparency.TabIndex = 3;
            this.lblTransparency.Text = "Transparency";
            // 
            // lblContrast
            // 
            this.lblContrast.Location = new System.Drawing.Point(18, 100);
            this.lblContrast.Name = "lblContrast";
            this.lblContrast.Size = new System.Drawing.Size(42, 13);
            this.lblContrast.TabIndex = 3;
            this.lblContrast.Text = "Contrast";
            // 
            // labelControl1
            // 
            this.labelControl1.Location = new System.Drawing.Point(18, 53);
            this.labelControl1.Name = "labelControl1";
            this.labelControl1.Size = new System.Drawing.Size(50, 13);
            this.labelControl1.TabIndex = 3;
            this.labelControl1.Text = "Brightness";
            // 
            // trackBarControl3
            // 
            this.trackBarControl3.EditValue = null;
            this.trackBarControl3.Location = new System.Drawing.Point(120, 142);
            this.trackBarControl3.Name = "trackBarControl3";
            this.trackBarControl3.Size = new System.Drawing.Size(104, 45);
            this.trackBarControl3.TabIndex = 2;
            // 
            // tbarCantrast
            // 
            this.tbarCantrast.EditValue = null;
            this.tbarCantrast.Location = new System.Drawing.Point(120, 95);
            this.tbarCantrast.Name = "tbarCantrast";
            this.tbarCantrast.Properties.Maximum = 100;
            this.tbarCantrast.Properties.Minimum = -100;
            this.tbarCantrast.Size = new System.Drawing.Size(104, 45);
            this.tbarCantrast.TabIndex = 2;
            this.tbarCantrast.EditValueChanged += new System.EventHandler(this.tbarCantrast_EditValueChanged);
            // 
            // tbarBrightness
            // 
            this.tbarBrightness.EditValue = null;
            this.tbarBrightness.Location = new System.Drawing.Point(120, 50);
            this.tbarBrightness.Name = "tbarBrightness";
            this.tbarBrightness.Properties.Maximum = 255;
            this.tbarBrightness.Properties.Minimum = -255;
            this.tbarBrightness.Size = new System.Drawing.Size(104, 45);
            this.tbarBrightness.TabIndex = 2;
            this.tbarBrightness.EditValueChanged += new System.EventHandler(this.trackBarControl1_EditValueChanged);
            // 
            // spnTransparency
            // 
            this.spnTransparency.EditValue = new decimal(new int[] {
            0,
            0,
            0,
            0});
            this.spnTransparency.Location = new System.Drawing.Point(246, 141);
            this.spnTransparency.Name = "spnTransparency";
            this.spnTransparency.Properties.Buttons.AddRange(new DevExpress.XtraEditors.Controls.EditorButton[] {
            new DevExpress.XtraEditors.Controls.EditorButton()});
            this.spnTransparency.Size = new System.Drawing.Size(44, 20);
            this.spnTransparency.TabIndex = 1;
            // 
            // spinEdit2
            // 
            this.spinEdit2.EditValue = new decimal(new int[] {
            0,
            0,
            0,
            0});
            this.spinEdit2.Location = new System.Drawing.Point(246, 96);
            this.spinEdit2.Name = "spinEdit2";
            this.spinEdit2.Properties.Buttons.AddRange(new DevExpress.XtraEditors.Controls.EditorButton[] {
            new DevExpress.XtraEditors.Controls.EditorButton()});
            this.spinEdit2.Properties.MaxValue = new decimal(new int[] {
            100,
            0,
            0,
            0});
            this.spinEdit2.Properties.MinValue = new decimal(new int[] {
            100,
            0,
            0,
            -2147483648});
            this.spinEdit2.Size = new System.Drawing.Size(44, 20);
            this.spinEdit2.TabIndex = 1;
            this.spinEdit2.EditValueChanged += new System.EventHandler(this.spinEdit2_EditValueChanged);
            // 
            // spinEdit1
            // 
            this.spinEdit1.EditValue = new decimal(new int[] {
            0,
            0,
            0,
            0});
            this.spinEdit1.Location = new System.Drawing.Point(246, 50);
            this.spinEdit1.Name = "spinEdit1";
            this.spinEdit1.Properties.Buttons.AddRange(new DevExpress.XtraEditors.Controls.EditorButton[] {
            new DevExpress.XtraEditors.Controls.EditorButton()});
            this.spinEdit1.Properties.MaxValue = new decimal(new int[] {
            255,
            0,
            0,
            0});
            this.spinEdit1.Properties.MinValue = new decimal(new int[] {
            255,
            0,
            0,
            -2147483648});
            this.spinEdit1.Size = new System.Drawing.Size(44, 20);
            this.spinEdit1.TabIndex = 1;
            this.spinEdit1.ValueChanged += new System.EventHandler(this.spinEdit1_ValueChanged);
            // 
            // btnApply
            // 
            this.btnApply.Location = new System.Drawing.Point(213, 277);
            this.btnApply.Name = "btnApply";
            this.btnApply.Size = new System.Drawing.Size(75, 23);
            this.btnApply.TabIndex = 0;
            this.btnApply.Text = "Apply";
            this.btnApply.Click += new System.EventHandler(this.btnApply_Click);
            // 
            // btnReset
            // 
            this.btnReset.Location = new System.Drawing.Point(444, 377);
            this.btnReset.Name = "btnReset";
            this.btnReset.Size = new System.Drawing.Size(59, 23);
            this.btnReset.TabIndex = 0;
            this.btnReset.Text = "ReSet";
            this.btnReset.Click += new System.EventHandler(this.btnReset_Click);
            // 
            // btnOk
            // 
            this.btnOk.Location = new System.Drawing.Point(509, 377);
            this.btnOk.Name = "btnOk";
            this.btnOk.Size = new System.Drawing.Size(56, 23);
            this.btnOk.TabIndex = 0;
            this.btnOk.Text = "OK";
            this.btnOk.Click += new System.EventHandler(this.btnOk_Click);
            // 
            // btnCancel
            // 
            this.btnCancel.Location = new System.Drawing.Point(571, 377);
            this.btnCancel.Name = "btnCancel";
            this.btnCancel.Size = new System.Drawing.Size(60, 23);
            this.btnCancel.TabIndex = 0;
            this.btnCancel.Text = "Cancel";
            this.btnCancel.Click += new System.EventHandler(this.btnCancel_Click);
            // 
            // pictureBox1
            // 
            this.pictureBox1.Location = new System.Drawing.Point(12, 46);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Properties.PictureAlignment = System.Drawing.ContentAlignment.TopLeft;
            this.pictureBox1.Properties.ReadOnly = true;
            this.pictureBox1.Properties.ShowMenu = false;
            this.pictureBox1.Size = new System.Drawing.Size(311, 303);
            this.pictureBox1.TabIndex = 1;
            this.pictureBox1.MouseUp += new System.Windows.Forms.MouseEventHandler(this.pictureBox1_MouseUp);
            this.pictureBox1.Paint += new System.Windows.Forms.PaintEventHandler(this.pictureBox1_Paint);
            this.pictureBox1.MouseEnter += new System.EventHandler(this.pictureBox1_MouseEnter);
            this.pictureBox1.MouseMove += new System.Windows.Forms.MouseEventHandler(this.pictureBox1_MouseMove);
            this.pictureBox1.MouseDown += new System.Windows.Forms.MouseEventHandler(this.pictureBox1_MouseDown);
            this.pictureBox1.MouseLeave += new System.EventHandler(this.pictureBox1_MouseLeave);
            // 
            // lblStatus
            // 
            this.lblStatus.Location = new System.Drawing.Point(12, 355);
            this.lblStatus.Name = "lblStatus";
            this.lblStatus.Size = new System.Drawing.Size(40, 13);
            this.lblStatus.TabIndex = 4;
            this.lblStatus.Text = "Location";
            // 
            // EditPicture
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(680, 422);
            this.Controls.Add(this.lblStatus);
            this.Controls.Add(this.pictureBox1);
            this.Controls.Add(this.btnCancel);
            this.Controls.Add(this.btnOk);
            this.Controls.Add(this.btnReset);
            this.Controls.Add(this.xtraTabControl1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.Fixed3D;
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "EditPicture";
            this.ShowIcon = false;
            this.Text = "Edit Picture";
            ((System.ComponentModel.ISupportInitialize)(this.xtraTabControl1)).EndInit();
            this.xtraTabControl1.ResumeLayout(false);
            this.xtraTabPage1.ResumeLayout(false);
            this.xtraTabPage1.PerformLayout();
            this.xtraTabPage2.ResumeLayout(false);
            this.o.ResumeLayout(false);
            this.o.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.trackBarControl3.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.trackBarControl3)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.tbarCantrast.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.tbarCantrast)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.tbarBrightness.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.tbarBrightness)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.spnTransparency.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.spinEdit2.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.spinEdit1.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1.Properties)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private DevExpress.XtraTab.XtraTabControl xtraTabControl1;
        private DevExpress.XtraTab.XtraTabPage xtraTabPage1;
        private DevExpress.XtraTab.XtraTabPage xtraTabPage2;
        private DevExpress.XtraTab.XtraTabPage o;
        private DevExpress.XtraEditors.SimpleButton btnApply;
        private DevExpress.XtraEditors.SimpleButton btnReset;
        private DevExpress.XtraEditors.SimpleButton btnOk;
        private DevExpress.XtraEditors.SimpleButton btnCancel;
        private System.Windows.Forms.RadioButton rdbOriginalPictureRatio;
        private System.Windows.Forms.RadioButton rdbOverallSignRatio;
        private System.Windows.Forms.RadioButton rdbBoxLayerRatio;
        private System.Windows.Forms.RadioButton rdbNormal;
        private DevExpress.XtraEditors.SimpleButton btnHorizontal;
        private DevExpress.XtraEditors.SimpleButton btnFlipVertical;
        private DevExpress.XtraEditors.SimpleButton btnRotateLeft;
        private DevExpress.XtraEditors.SimpleButton btnRotatRight;
        private DevExpress.XtraEditors.SpinEdit spinEdit1;
        private DevExpress.XtraEditors.PictureEdit pictureBox1;
        private DevExpress.XtraEditors.TrackBarControl tbarBrightness;
        private DevExpress.XtraEditors.TrackBarControl tbarCantrast;
        private DevExpress.XtraEditors.TrackBarControl trackBarControl3;
        private DevExpress.XtraEditors.LabelControl lblTransparency;
        private DevExpress.XtraEditors.LabelControl lblContrast;
        private DevExpress.XtraEditors.LabelControl labelControl1;
        private DevExpress.XtraEditors.SpinEdit spnTransparency;
        private DevExpress.XtraEditors.SpinEdit spinEdit2;
        private DevExpress.XtraEditors.SimpleButton simpleButton1;
        private DevExpress.XtraEditors.SimpleButton simpleButton2;
        private DevExpress.XtraEditors.LabelControl lblStatus;
    }
}