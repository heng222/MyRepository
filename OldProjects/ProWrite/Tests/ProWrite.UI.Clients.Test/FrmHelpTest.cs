using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ProWrite.UI.Controls;

namespace ProWrite.UI.Clients.Test
{
    public class FrmHelpTest : System.Windows.Forms.Form
    {
        private System.Windows.Forms.TextBox addressTextBox;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox cityTextBox;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.TextBox stateTextBox;
        private System.Windows.Forms.TextBox zipTextBox;
        private System.Windows.Forms.Label helpLabel;


        public FrmHelpTest()
        {
            this.addressTextBox = new System.Windows.Forms.TextBox();
            this.helpLabel = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.cityTextBox = new System.Windows.Forms.TextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.stateTextBox = new System.Windows.Forms.TextBox();
            this.zipTextBox = new System.Windows.Forms.TextBox();

            // Help Label
            this.helpLabel.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.helpLabel.Location = new System.Drawing.Point(8, 80);
            this.helpLabel.Size = new System.Drawing.Size(272, 72);
            this.helpLabel.Text = "Click the Help button in the title bar, then click a control " +
                "to see a Help tooltip for the control.  Click on a control and press F1 to invoke " +
                "the Help system with a sample Help file.";

            // Address Label
            this.label2.Location = new System.Drawing.Point(16, 8);
            this.label2.Size = new System.Drawing.Size(100, 16);
            this.label2.Text = "Address:";

            // Comma Label
            this.label3.Location = new System.Drawing.Point(136, 56);
            this.label3.Size = new System.Drawing.Size(16, 16);
            this.label3.Text = ",";

            // Sets properties for the different address fields.

            // Address TextBox
            this.addressTextBox.Location = new System.Drawing.Point(16, 24);
            this.addressTextBox.Size = new System.Drawing.Size(264, 20);
            this.addressTextBox.TabIndex = 0;
            this.addressTextBox.Text = "";

            // City TextBox
            this.cityTextBox.Location = new System.Drawing.Point(16, 48);
            this.cityTextBox.Size = new System.Drawing.Size(120, 20);
            this.cityTextBox.TabIndex = 3;
            this.cityTextBox.Text = "";

            // State TextBox
            this.stateTextBox.Location = new System.Drawing.Point(152, 48);
            this.stateTextBox.MaxLength = 2;
            this.stateTextBox.Size = new System.Drawing.Size(32, 20);
            this.stateTextBox.TabIndex = 5;
            this.stateTextBox.Text = "";

            // Zip TextBox
            this.zipTextBox.Location = new System.Drawing.Point(192, 48);
            this.zipTextBox.Size = new System.Drawing.Size(88, 20);
            this.zipTextBox.TabIndex = 6;
            this.zipTextBox.Text = "";

            // Add the controls to the form.
            this.Controls.AddRange(new System.Windows.Forms.Control[] {
                                    this.zipTextBox, this.stateTextBox,
                                    this.label3, this.cityTextBox,
                                    this.label2, this.helpLabel,
                                    this.addressTextBox});

            // Set the form to look like a dialog, and show the HelpButton.    
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.HelpButton = true;
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.ClientSize = new System.Drawing.Size(292, 160);
            this.Text = "Help Provider Demonstration";

        }

        protected override void OnLoad(EventArgs e)
        {
            base.OnLoad(e);

            //HelpManager.Instance.RegisterHelp(this.addressTextBox, System.Windows.Forms.HelpNavigator.Topic, "创建图片.htm");
            //HelpManager.Instance.RegisterHelp(this.cityTextBox, System.Windows.Forms.HelpNavigator.Index, null);
            //HelpManager.Instance.RegisterHelp(this.zipTextBox, System.Windows.Forms.HelpNavigator.KeywordIndex, null);
            //HelpManager.Instance.RegisterHelp(this.stateTextBox, System.Windows.Forms.HelpNavigator.Find, "how are you");

        }
    }

}
