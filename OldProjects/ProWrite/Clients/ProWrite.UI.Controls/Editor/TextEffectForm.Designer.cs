namespace ProWrite.UI.Controls.Editor
{
	partial class TextEffectForm
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(TextEffectForm));
            this.colorEdit = new PWColorEdit();
            this.outlineWidth = new DevExpress.XtraEditors.SpinEdit();
            this.labelControl1 = new DevExpress.XtraEditors.LabelControl();
            this.labelControl2 = new DevExpress.XtraEditors.LabelControl();
            this.pnlDrawText = new DevExpress.XtraEditors.PanelControl();
            this.radGrpEffect = new DevExpress.XtraEditors.RadioGroup();
            this.shadowEditLateral = new DevExpress.XtraEditors.SpinEdit();
            this.ShadowEditVertical = new DevExpress.XtraEditors.SpinEdit();
            this.labelControl6 = new DevExpress.XtraEditors.LabelControl();
            this.labelControl7 = new DevExpress.XtraEditors.LabelControl();
            this.pnlShadow = new DevExpress.XtraEditors.PanelControl();
            this.pnlOutline = new DevExpress.XtraEditors.PanelControl();
            this.pnlColor = new DevExpress.XtraEditors.PanelControl();
            this.btnOK = new DevExpress.XtraEditors.SimpleButton();
            this.btnCancel = new DevExpress.XtraEditors.SimpleButton();
            ((System.ComponentModel.ISupportInitialize)(this.colorEdit.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.outlineWidth.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pnlDrawText)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.radGrpEffect.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.shadowEditLateral.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.ShadowEditVertical.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pnlShadow)).BeginInit();
            this.pnlShadow.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pnlOutline)).BeginInit();
            this.pnlOutline.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pnlColor)).BeginInit();
            this.pnlColor.SuspendLayout();
            this.SuspendLayout();
            // 
            // colorEdit
            // 
            this.colorEdit.EditValue = System.Drawing.Color.White;
            this.colorEdit.Location = new System.Drawing.Point(93, 9);
            this.colorEdit.Name = "colorEdit";
            this.colorEdit.Properties.Buttons.AddRange(new DevExpress.XtraEditors.Controls.EditorButton[] {
            new DevExpress.XtraEditors.Controls.EditorButton(DevExpress.XtraEditors.Controls.ButtonPredefines.Combo)});
            this.colorEdit.Size = new System.Drawing.Size(100, 20);
            this.colorEdit.TabIndex = 0;
            this.colorEdit.EditValueChanged += new System.EventHandler(this.colorEdit_EditValueChanged);
            // 
            // outlineWidth
            // 
            this.outlineWidth.EditValue = new decimal(new int[] {
            0,
            0,
            0,
            0});
            this.outlineWidth.Location = new System.Drawing.Point(94, 38);
            this.outlineWidth.Name = "outlineWidth";
            this.outlineWidth.Properties.Buttons.AddRange(new DevExpress.XtraEditors.Controls.EditorButton[] {
            new DevExpress.XtraEditors.Controls.EditorButton()});
            this.outlineWidth.Properties.DisplayFormat.FormatType = DevExpress.Utils.FormatType.Numeric;
            this.outlineWidth.Properties.EditFormat.FormatType = DevExpress.Utils.FormatType.Numeric;
            this.outlineWidth.Properties.IsFloatValue = false;
            this.outlineWidth.Properties.Mask.EditMask = "N00";
            this.outlineWidth.Properties.MaxLength = 1000;
            this.outlineWidth.Properties.MaxValue = new decimal(new int[] {
            1000,
            0,
            0,
            0});
            this.outlineWidth.Properties.EditValueChanged += new System.EventHandler(this.outlineEditTop_Properties_EditValueChanged);
            this.outlineWidth.Size = new System.Drawing.Size(39, 20);
            this.outlineWidth.TabIndex = 1;
            // 
            // labelControl1
            // 
            this.labelControl1.Location = new System.Drawing.Point(16, 10);
            this.labelControl1.Name = "labelControl1";
            this.labelControl1.Size = new System.Drawing.Size(57, 13);
            this.labelControl1.TabIndex = 5;
            this.labelControl1.Text = "Effect Color";
            // 
            // labelControl2
            // 
            this.labelControl2.Location = new System.Drawing.Point(14, 41);
            this.labelControl2.Name = "labelControl2";
            this.labelControl2.Size = new System.Drawing.Size(63, 13);
            this.labelControl2.TabIndex = 6;
            this.labelControl2.Text = "Outline Width";
            // 
            // pnlDrawText
            // 
            this.pnlDrawText.Appearance.BackColor = System.Drawing.Color.DimGray;
            this.pnlDrawText.Appearance.Options.UseBackColor = true;
            this.pnlDrawText.BorderStyle = DevExpress.XtraEditors.Controls.BorderStyles.Style3D;
            this.pnlDrawText.Location = new System.Drawing.Point(12, 214);
            this.pnlDrawText.Name = "pnlDrawText";
            this.pnlDrawText.Size = new System.Drawing.Size(469, 141);
            this.pnlDrawText.TabIndex = 10;
            // 
            // radGrpEffect
            // 
            this.radGrpEffect.Location = new System.Drawing.Point(4, -2);
            this.radGrpEffect.Name = "radGrpEffect";
            this.radGrpEffect.Properties.Appearance.BackColor = System.Drawing.Color.Transparent;
            this.radGrpEffect.Properties.Appearance.Options.UseBackColor = true;
            this.radGrpEffect.Properties.BorderStyle = DevExpress.XtraEditors.Controls.BorderStyles.NoBorder;
            this.radGrpEffect.Properties.Items.AddRange(new DevExpress.XtraEditors.Controls.RadioGroupItem[] {
            new DevExpress.XtraEditors.Controls.RadioGroupItem(null, "NONE"),
            new DevExpress.XtraEditors.Controls.RadioGroupItem(null, "SHADED"),
            new DevExpress.XtraEditors.Controls.RadioGroupItem(null, "OUTLINE")});
            this.radGrpEffect.Size = new System.Drawing.Size(66, 123);
            this.radGrpEffect.TabIndex = 14;
            this.radGrpEffect.SelectedIndexChanged += new System.EventHandler(this.radGrpEffect_SelectedIndexChanged);
            // 
            // shadowEditLateral
            // 
            this.shadowEditLateral.EditValue = new decimal(new int[] {
            10,
            0,
            0,
            0});
            this.shadowEditLateral.Location = new System.Drawing.Point(90, 10);
            this.shadowEditLateral.Name = "shadowEditLateral";
            this.shadowEditLateral.Properties.Buttons.AddRange(new DevExpress.XtraEditors.Controls.EditorButton[] {
            new DevExpress.XtraEditors.Controls.EditorButton()});
            this.shadowEditLateral.Properties.DisplayFormat.FormatType = DevExpress.Utils.FormatType.Numeric;
            this.shadowEditLateral.Properties.EditFormat.FormatType = DevExpress.Utils.FormatType.Numeric;
            this.shadowEditLateral.Properties.MaxValue = new decimal(new int[] {
            1000,
            0,
            0,
            0});
            this.shadowEditLateral.Properties.MinValue = new decimal(new int[] {
            1000,
            0,
            0,
            -2147483648});
            this.shadowEditLateral.Properties.EditValueChanged += new System.EventHandler(this.shadowEditLateral_Properties_EditValueChanged);
            this.shadowEditLateral.Size = new System.Drawing.Size(39, 20);
            this.shadowEditLateral.TabIndex = 15;
            // 
            // ShadowEditVertical
            // 
            this.ShadowEditVertical.EditValue = new decimal(new int[] {
            10,
            0,
            0,
            0});
            this.ShadowEditVertical.Location = new System.Drawing.Point(90, 44);
            this.ShadowEditVertical.Name = "ShadowEditVertical";
            this.ShadowEditVertical.Properties.Buttons.AddRange(new DevExpress.XtraEditors.Controls.EditorButton[] {
            new DevExpress.XtraEditors.Controls.EditorButton()});
            this.ShadowEditVertical.Properties.DisplayFormat.FormatType = DevExpress.Utils.FormatType.Numeric;
            this.ShadowEditVertical.Properties.EditFormat.FormatType = DevExpress.Utils.FormatType.Numeric;
            this.ShadowEditVertical.Properties.MaxValue = new decimal(new int[] {
            1000,
            0,
            0,
            0});
            this.ShadowEditVertical.Properties.MinValue = new decimal(new int[] {
            1000,
            0,
            0,
            -2147483648});
            this.ShadowEditVertical.Properties.EditValueChanged += new System.EventHandler(this.ShadowEditVertical_Properties_EditValueChanged);
            this.ShadowEditVertical.Size = new System.Drawing.Size(39, 20);
            this.ShadowEditVertical.TabIndex = 16;
            // 
            // labelControl6
            // 
            this.labelControl6.Location = new System.Drawing.Point(16, 13);
            this.labelControl6.Name = "labelControl6";
            this.labelControl6.Size = new System.Drawing.Size(58, 13);
            this.labelControl6.TabIndex = 17;
            this.labelControl6.Text = "Lateral Shift";
            // 
            // labelControl7
            // 
            this.labelControl7.Location = new System.Drawing.Point(16, 51);
            this.labelControl7.Name = "labelControl7";
            this.labelControl7.Size = new System.Drawing.Size(60, 13);
            this.labelControl7.TabIndex = 18;
            this.labelControl7.Text = "Vertical Shift";
            // 
            // pnlShadow
            // 
            this.pnlShadow.AlwaysScrollActiveControlIntoView = false;
            this.pnlShadow.BorderStyle = DevExpress.XtraEditors.Controls.BorderStyles.NoBorder;
            this.pnlShadow.Controls.Add(this.labelControl6);
            this.pnlShadow.Controls.Add(this.labelControl7);
            this.pnlShadow.Controls.Add(this.shadowEditLateral);
            this.pnlShadow.Controls.Add(this.ShadowEditVertical);
            this.pnlShadow.Location = new System.Drawing.Point(70, 39);
            this.pnlShadow.Name = "pnlShadow";
            this.pnlShadow.Size = new System.Drawing.Size(216, 68);
            this.pnlShadow.TabIndex = 19;
            this.pnlShadow.Visible = false;
            // 
            // pnlOutline
            // 
            this.pnlOutline.BorderStyle = DevExpress.XtraEditors.Controls.BorderStyles.NoBorder;
            this.pnlOutline.Controls.Add(this.outlineWidth);
            this.pnlOutline.Controls.Add(this.labelControl2);
            this.pnlOutline.Location = new System.Drawing.Point(70, 49);
            this.pnlOutline.Name = "pnlOutline";
            this.pnlOutline.Size = new System.Drawing.Size(200, 73);
            this.pnlOutline.TabIndex = 20;
            this.pnlOutline.Visible = false;
            // 
            // pnlColor
            // 
            this.pnlColor.BorderStyle = DevExpress.XtraEditors.Controls.BorderStyles.NoBorder;
            this.pnlColor.Controls.Add(this.colorEdit);
            this.pnlColor.Controls.Add(this.labelControl1);
            this.pnlColor.Location = new System.Drawing.Point(70, 4);
            this.pnlColor.Name = "pnlColor";
            this.pnlColor.Size = new System.Drawing.Size(200, 39);
            this.pnlColor.TabIndex = 21;
            this.pnlColor.Visible = false;
            // 
            // btnOK
            // 
            this.btnOK.Image = ((System.Drawing.Image)(resources.GetObject("btnOK.Image")));
            this.btnOK.Location = new System.Drawing.Point(118, 121);
            this.btnOK.Name = "btnOK";
            this.btnOK.Size = new System.Drawing.Size(67, 23);
            this.btnOK.TabIndex = 22;
            this.btnOK.Text = "Save";
            this.btnOK.Click += new System.EventHandler(this.btnOK_Click);
            // 
            // btnCancel
            // 
            this.btnCancel.DialogResult = System.Windows.Forms.DialogResult.Cancel;
            this.btnCancel.Image = ((System.Drawing.Image)(resources.GetObject("btnCancel.Image")));
            this.btnCancel.Location = new System.Drawing.Point(194, 121);
            this.btnCancel.Name = "btnCancel";
            this.btnCancel.Size = new System.Drawing.Size(67, 23);
            this.btnCancel.TabIndex = 23;
            this.btnCancel.Text = "Cancel";
            this.btnCancel.Click += new System.EventHandler(this.btnCancel_Click);
            // 
            // TextEffectForm
            // 
            this.AcceptButton = this.btnOK;
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.CancelButton = this.btnCancel;
            this.ClientSize = new System.Drawing.Size(269, 151);
            this.Controls.Add(this.pnlOutline);
            this.Controls.Add(this.btnCancel);
            this.Controls.Add(this.btnOK);
            this.Controls.Add(this.pnlShadow);
            this.Controls.Add(this.pnlColor);
            this.Controls.Add(this.radGrpEffect);
            this.Controls.Add(this.pnlDrawText);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "TextEffectForm";
            this.ShowIcon = false;
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
            this.Text = "Select Text Effect";
            this.Load += new System.EventHandler(this.TextEffectForm_Load);
            ((System.ComponentModel.ISupportInitialize)(this.colorEdit.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.outlineWidth.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pnlDrawText)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.radGrpEffect.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.shadowEditLateral.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.ShadowEditVertical.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pnlShadow)).EndInit();
            this.pnlShadow.ResumeLayout(false);
            this.pnlShadow.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pnlOutline)).EndInit();
            this.pnlOutline.ResumeLayout(false);
            this.pnlOutline.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pnlColor)).EndInit();
            this.pnlColor.ResumeLayout(false);
            this.pnlColor.PerformLayout();
            this.ResumeLayout(false);

		}

		#endregion

		private PWColorEdit colorEdit;
		private DevExpress.XtraEditors.SpinEdit outlineWidth;
		private DevExpress.XtraEditors.LabelControl labelControl1;
		private DevExpress.XtraEditors.LabelControl labelControl2;
		private DevExpress.XtraEditors.PanelControl pnlDrawText;
		private DevExpress.XtraEditors.RadioGroup radGrpEffect;
		private DevExpress.XtraEditors.SpinEdit shadowEditLateral;
		private DevExpress.XtraEditors.SpinEdit ShadowEditVertical;
		private DevExpress.XtraEditors.LabelControl labelControl6;
		private DevExpress.XtraEditors.LabelControl labelControl7;
		private DevExpress.XtraEditors.PanelControl pnlShadow;
		private DevExpress.XtraEditors.PanelControl pnlOutline;
		private DevExpress.XtraEditors.PanelControl pnlColor;
		private DevExpress.XtraEditors.SimpleButton btnOK;
		private DevExpress.XtraEditors.SimpleButton btnCancel;
	}
}