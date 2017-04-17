namespace ProWrite.UI.Controls.Live.Sessions
{
    partial class CategoryControl
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
            this.btnAddMsg = new DevExpress.XtraEditors.SimpleButton();
            this.btnRemoveMsg = new DevExpress.XtraEditors.SimpleButton();
            this.ctlCategories = new ProWrite.UI.Controls.Live.Sessions.CategoriesControl();
            this.ctlLibrary = new ProWrite.UI.Controls.Live.Sessions.LibraryCategoryControl();
            this.SuspendLayout();
            // 
            // btnAddMsg
            // 
            this.btnAddMsg.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.btnAddMsg.Location = new System.Drawing.Point(244, 169);
            this.btnAddMsg.Name = "btnAddMsg";
            this.btnAddMsg.Size = new System.Drawing.Size(82, 23);
            this.btnAddMsg.TabIndex = 2;
            this.btnAddMsg.Text = "&Add  >>";
            this.btnAddMsg.Click += new System.EventHandler(this.btnAddMsg_Click);
            // 
            // btnRemoveMsg
            // 
            this.btnRemoveMsg.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.btnRemoveMsg.Location = new System.Drawing.Point(244, 198);
            this.btnRemoveMsg.Name = "btnRemoveMsg";
            this.btnRemoveMsg.Size = new System.Drawing.Size(82, 23);
            this.btnRemoveMsg.TabIndex = 3;
            this.btnRemoveMsg.Text = "<< &Remove";
            this.btnRemoveMsg.Click += new System.EventHandler(this.btnRemoveMsg_Click);
            // 
            // ctlCategories
            // 
            this.ctlCategories.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.ctlCategories.Location = new System.Drawing.Point(335, 0);
            this.ctlCategories.Name = "ctlCategories";
            this.ctlCategories.Size = new System.Drawing.Size(258, 359);
            this.ctlCategories.TabIndex = 4;
            // 
            // ctlLibrary
            // 
            this.ctlLibrary.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.ctlLibrary.Location = new System.Drawing.Point(0, 1);
            this.ctlLibrary.Name = "ctlLibrary";
            this.ctlLibrary.Size = new System.Drawing.Size(237, 358);
            this.ctlLibrary.TabIndex = 0;
            // 
            // CategoryControl
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.ctlCategories);
            this.Controls.Add(this.btnRemoveMsg);
            this.Controls.Add(this.btnAddMsg);
            this.Controls.Add(this.ctlLibrary);
            this.Name = "CategoryControl";
            this.Size = new System.Drawing.Size(593, 359);
            this.ResumeLayout(false);

        }

        #endregion

        private LibraryCategoryControl ctlLibrary;
        private DevExpress.XtraEditors.SimpleButton btnAddMsg;
        private DevExpress.XtraEditors.SimpleButton btnRemoveMsg;
        private CategoriesControl ctlCategories;
    }
}
