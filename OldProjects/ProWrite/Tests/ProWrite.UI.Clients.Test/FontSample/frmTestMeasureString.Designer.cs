namespace ProWrite.UI.Clients.Test.FontSample
{
    partial class frmTestMeasureString
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
            this.Font_MeasureString = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // Font_MeasureString
            // 
            this.Font_MeasureString.Location = new System.Drawing.Point(-3, 231);
            this.Font_MeasureString.Name = "Font_MeasureString";
            this.Font_MeasureString.Size = new System.Drawing.Size(75, 23);
            this.Font_MeasureString.TabIndex = 0;
            this.Font_MeasureString.Text = "button1";
            this.Font_MeasureString.UseVisualStyleBackColor = true;
            this.Font_MeasureString.Click += new System.EventHandler(this.Font_MeasureString_Click);
            // 
            // frmTestMeasureString
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(463, 298);
            this.Controls.Add(this.Font_MeasureString);
            this.Name = "frmTestMeasureString";
            this.Text = "frmTestMeasureString";
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button Font_MeasureString;
    }
}