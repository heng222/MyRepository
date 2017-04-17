namespace ProWrite.UI.Clients.Test.FontSample
{
    partial class frmPropertyGridSample
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
            this.pgControl = new DevExpress.XtraVerticalGrid.PropertyGridControl();
            ((System.ComponentModel.ISupportInitialize)(this.pgControl)).BeginInit();
            this.SuspendLayout();
            // 
            // pgControl
            // 
            this.pgControl.Location = new System.Drawing.Point(27, 30);
            this.pgControl.Name = "pgControl";
            this.pgControl.ServiceProvider = null;
            this.pgControl.Size = new System.Drawing.Size(223, 200);
            this.pgControl.TabIndex = 0;
            this.pgControl.CellValueChanged += new DevExpress.XtraVerticalGrid.Events.CellValueChangedEventHandler(this.pgControl_CellValueChanged);
            // 
            // frmPropertyGridSample
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(292, 266);
            this.Controls.Add(this.pgControl);
            this.Name = "frmPropertyGridSample";
            this.Text = "frmPropertyGridSample";
            this.Load += new System.EventHandler(this.frmPropertyGridSample_Load);
            ((System.ComponentModel.ISupportInitialize)(this.pgControl)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private DevExpress.XtraVerticalGrid.PropertyGridControl pgControl;

    }
}