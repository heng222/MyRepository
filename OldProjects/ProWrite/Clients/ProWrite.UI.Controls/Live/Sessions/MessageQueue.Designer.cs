namespace ProWrite.UI.Controls.Live.Sessions
{
    partial class MessageQueue
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
            this.lbcMessageQueue = new DevExpress.XtraEditors.ListBoxControl();
            this.cmbMessageQueue = new DevExpress.XtraEditors.ComboBoxEdit();
            this.btnUp = new DevExpress.XtraEditors.SimpleButton();
            this.btnDown = new DevExpress.XtraEditors.SimpleButton();
            this.btnDelete = new DevExpress.XtraEditors.SimpleButton();
            this.btnRefresh = new DevExpress.XtraEditors.SimpleButton();
            this.btnSign1 = new DevExpress.XtraEditors.SimpleButton();
            this.btnEject = new DevExpress.XtraEditors.SimpleButton();
            ((System.ComponentModel.ISupportInitialize)(this.lbcMessageQueue)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.cmbMessageQueue.Properties)).BeginInit();
            this.SuspendLayout();
            // 
            // lbcMessageQueue
            // 
            this.lbcMessageQueue.AllowDrop = true;
            this.lbcMessageQueue.Location = new System.Drawing.Point(0, 106);
            this.lbcMessageQueue.Name = "lbcMessageQueue";
            this.lbcMessageQueue.Size = new System.Drawing.Size(234, 305);
            this.lbcMessageQueue.TabIndex = 0;
            this.lbcMessageQueue.DragDrop += new System.Windows.Forms.DragEventHandler(this.lbcMessageQueue_DragDrop);
            this.lbcMessageQueue.DragEnter += new System.Windows.Forms.DragEventHandler(this.lbcMessageQueue_DragEnter);
            this.lbcMessageQueue.SelectedIndexChanged += new System.EventHandler(this.lbcMessageQueue_SelectedIndexChanged);
            // 
            // cmbMessageQueue
            // 
            this.cmbMessageQueue.Location = new System.Drawing.Point(0, 80);
            this.cmbMessageQueue.Name = "cmbMessageQueue";
            this.cmbMessageQueue.Properties.Buttons.AddRange(new DevExpress.XtraEditors.Controls.EditorButton[] {
            new DevExpress.XtraEditors.Controls.EditorButton(DevExpress.XtraEditors.Controls.ButtonPredefines.Combo)});
            this.cmbMessageQueue.Size = new System.Drawing.Size(218, 20);
            this.cmbMessageQueue.TabIndex = 1;
            // 
            // btnUp
            // 
            this.btnUp.Location = new System.Drawing.Point(240, 183);
            this.btnUp.Name = "btnUp";
            this.btnUp.Size = new System.Drawing.Size(57, 23);
            this.btnUp.TabIndex = 2;
            this.btnUp.Text = "Up";
            this.btnUp.Click += new System.EventHandler(this.btnUp_Click);
            // 
            // btnDown
            // 
            this.btnDown.Location = new System.Drawing.Point(240, 222);
            this.btnDown.Name = "btnDown";
            this.btnDown.Size = new System.Drawing.Size(57, 23);
            this.btnDown.TabIndex = 2;
            this.btnDown.Text = "Dn";
            this.btnDown.Click += new System.EventHandler(this.btnDown_Click);
            // 
            // btnDelete
            // 
            this.btnDelete.Location = new System.Drawing.Point(240, 261);
            this.btnDelete.Name = "btnDelete";
            this.btnDelete.Size = new System.Drawing.Size(57, 23);
            this.btnDelete.TabIndex = 2;
            this.btnDelete.Text = "Delete";
            this.btnDelete.Click += new System.EventHandler(this.btnDelete_Click);
            // 
            // btnRefresh
            // 
            this.btnRefresh.Location = new System.Drawing.Point(237, 296);
            this.btnRefresh.Name = "btnRefresh";
            this.btnRefresh.Size = new System.Drawing.Size(60, 23);
            this.btnRefresh.TabIndex = 2;
            this.btnRefresh.Text = "Refresh";
            this.btnRefresh.Click += new System.EventHandler(this.btnRefresh_Click);
            // 
            // btnSign1
            // 
            this.btnSign1.Location = new System.Drawing.Point(17, 12);
            this.btnSign1.Name = "btnSign1";
            this.btnSign1.Size = new System.Drawing.Size(57, 62);
            this.btnSign1.TabIndex = 2;
            this.btnSign1.Text = "Up";
            this.btnSign1.Click += new System.EventHandler(this.btnSign1_Click);
            // 
            // btnEject
            // 
            this.btnEject.Location = new System.Drawing.Point(224, 77);
            this.btnEject.Name = "btnEject";
            this.btnEject.Size = new System.Drawing.Size(57, 23);
            this.btnEject.TabIndex = 2;
            this.btnEject.Text = "Eject";
            this.btnEject.Click += new System.EventHandler(this.btnEject_Click);
            // 
            // MessageQueue
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.btnRefresh);
            this.Controls.Add(this.btnEject);
            this.Controls.Add(this.btnDelete);
            this.Controls.Add(this.btnDown);
            this.Controls.Add(this.btnSign1);
            this.Controls.Add(this.btnUp);
            this.Controls.Add(this.cmbMessageQueue);
            this.Controls.Add(this.lbcMessageQueue);
            this.Name = "MessageQueue";
            this.Size = new System.Drawing.Size(300, 419);
            ((System.ComponentModel.ISupportInitialize)(this.lbcMessageQueue)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.cmbMessageQueue.Properties)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private DevExpress.XtraEditors.ListBoxControl lbcMessageQueue;
        private DevExpress.XtraEditors.ComboBoxEdit cmbMessageQueue;
        private DevExpress.XtraEditors.SimpleButton btnUp;
        private DevExpress.XtraEditors.SimpleButton btnDown;
        private DevExpress.XtraEditors.SimpleButton btnDelete;
        private DevExpress.XtraEditors.SimpleButton btnRefresh;
        private DevExpress.XtraEditors.SimpleButton btnSign1;
        private DevExpress.XtraEditors.SimpleButton btnEject;
    }
}
