using System.Drawing;
using ProWrite.Resources;

namespace ProWrite.UI.Controls.Editor
{
    partial class LayerControl
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(LayerControl));
            this.EffectContainer = new EffectContinerControl();
            this.lblLayerType = new DevExpress.XtraEditors.PictureEdit();
            this.lblVisible = new DevExpress.XtraEditors.PictureEdit();
            this.foresidePanel = new DevExpress.XtraEditors.PanelControl();
            this.lblLayerName = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.EffectContainer)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.lblVisible.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.foresidePanel)).BeginInit();
            this.foresidePanel.SuspendLayout();
            this.SuspendLayout();
            // 
            // TimePanel
            // 
            this.EffectContainer.AllowDrop = true;
            this.EffectContainer.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            //this.EffectContainer.Dock = System.Windows.Forms.DockStyle.Fill;
            this.EffectContainer.Appearance.BackColor = System.Drawing.Color.Gainsboro;
            this.EffectContainer.Appearance.Options.UseBackColor = true;
            this.EffectContainer.BorderStyle = DevExpress.XtraEditors.Controls.BorderStyles.NoBorder;
            this.EffectContainer.Location = new System.Drawing.Point(200, 0);
            this.EffectContainer.Name = "TimePanel";
            this.EffectContainer.Size = new System.Drawing.Size(440, 29);
            this.EffectContainer.TabIndex = 13;
            //this.EffectContainer.Dock = System.Windows.Forms.DockStyle.Fill;
            // 
            // lblLayerType
            // 
            this.lblLayerType.EditValue = ((object)(resources.GetObject("lblVisible.EditValue"))); 
            this.lblLayerType.Location = new System.Drawing.Point(32, 2);
            this.lblLayerType.Name = "lblLayerType";
            this.lblLayerType.Properties.BorderStyle = DevExpress.XtraEditors.Controls.BorderStyles.Office2003;
            this.lblLayerType.Properties.NullText = " ";
            this.lblLayerType.Properties.ShowMenu = false;
            this.lblLayerType.Size = new System.Drawing.Size(30, 25);
            this.lblLayerType.TabIndex = 10;
            // 
            // lblVisible
            // 
            this.lblVisible.EditValue = ((object)(resources.GetObject("lblVisible.EditValue")));
            this.lblVisible.Location = new System.Drawing.Point(2, 2);
            this.lblVisible.Name = "lblVisible";
            this.lblVisible.Properties.BorderStyle = DevExpress.XtraEditors.Controls.BorderStyles.Office2003;
            this.lblVisible.Properties.NullText = " ";
            this.lblVisible.Properties.ShowMenu = false;
            this.lblVisible.Size = new System.Drawing.Size(30, 25);
            this.lblVisible.TabIndex = 4;
            this.lblVisible.ToolTip = "Visible";
            // 
            // foresidePanel
            // 
            this.foresidePanel.AllowDrop = true;
            this.foresidePanel.Appearance.BackColor = System.Drawing.Color.Gainsboro;
            this.foresidePanel.Appearance.Options.UseBackColor = true;
            
            this.foresidePanel.Controls.Add(this.lblLayerName);
            this.foresidePanel.Controls.Add(this.lblLayerType);
            this.foresidePanel.Controls.Add(this.lblVisible);
            this.foresidePanel.Location = new System.Drawing.Point(0, 0);
            this.foresidePanel.Name = "foresidePanel";
            this.foresidePanel.Size = new System.Drawing.Size(200, 29);
            this.foresidePanel.TabIndex = 14;
            //this.foresidePanel.Dock = System.Windows.Forms.DockStyle.Left;
            // 
            // lblLayerName
            // 
            this.lblLayerName.AllowDrop = true;
            this.lblLayerName.BackColor = System.Drawing.Color.Gainsboro;
            this.lblLayerName.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.lblLayerName.ForeColor = System.Drawing.Color.ForestGreen;
            this.lblLayerName.Location = new System.Drawing.Point(62, 2);
            this.lblLayerName.Margin = new System.Windows.Forms.Padding(0);
            this.lblLayerName.Name = "lblLayerName";
            this.lblLayerName.Size = new System.Drawing.Size(136, 25);
            this.lblLayerName.TabIndex = 12;
            this.lblLayerName.Text = "New Layer";
            this.lblLayerName.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // LayerControl
            // 
            this.AllowDrop = true;
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.AutoValidate = System.Windows.Forms.AutoValidate.EnableAllowFocusChange;
            this.BackColor = Color.WhiteSmoke;// System.Drawing.Color.FromArgb(((int)(((byte)(200)))), ((int)(((byte)(200)))), ((int)(((byte)(200)))));
            this.Controls.Add(this.foresidePanel);
            this.Controls.Add(this.EffectContainer);
            this.DoubleBuffered = true;
            //this.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.ForeColor = System.Drawing.SystemColors.Highlight;
            this.Name = "LayerControl";
            this.Size = new System.Drawing.Size(628, 29);
            ((System.ComponentModel.ISupportInitialize)(this.EffectContainer)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.lblVisible.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.foresidePanel)).EndInit();
            this.foresidePanel.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private DevExpress.XtraEditors.PanelControl EffectContainer;
        //private System.Windows.Forms.Label lblLayerType;
        //private System.Windows.Forms.Label lblVisible;
        private DevExpress.XtraEditors.PictureEdit lblLayerType;
        private DevExpress.XtraEditors.PictureEdit lblVisible;
        private DevExpress.XtraEditors.PanelControl foresidePanel;
        private System.Windows.Forms.Label lblLayerName;

    }
}
