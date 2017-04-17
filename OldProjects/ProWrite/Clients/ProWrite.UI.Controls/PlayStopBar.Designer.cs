using System.Windows.Forms;
namespace ProWrite.UI.Controls
{
	partial class PlayStopBar
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
			this.btnPlay = new ProWrite.UI.Controls.ImageButton();
			this.btnStop = new ProWrite.UI.Controls.ImageButton();
			this.btnPrevious = new ProWrite.UI.Controls.ImageButton();
			this.btnNext = new ProWrite.UI.Controls.ImageButton();
            this.btnToolTip = new ToolTip();
			this.SuspendLayout();
			// 
			// btnPlay
			// 
			this.btnPlay.BackColor = System.Drawing.Color.Transparent;
			this.btnPlay.Location = new System.Drawing.Point(0, 2);
			this.btnPlay.Name = "btnPlay";
			this.btnPlay.Size = new System.Drawing.Size(38, 38);
			this.btnPlay.TabIndex = 0;
			this.btnPlay.Text = "Play";
            this.btnToolTip.SetToolTip(this.btnPlay, "Preview");
			// 
			// btnStop
			// 
			this.btnStop.BackColor = System.Drawing.Color.Transparent;
			this.btnStop.Location = new System.Drawing.Point(35, 2);
			this.btnStop.Name = "btnStop";
			this.btnStop.Size = new System.Drawing.Size(22, 38);
			this.btnStop.TabIndex = 1;
			this.btnStop.Text = "Stop";
            this.btnToolTip.SetToolTip(this.btnStop, "Stop");
			// 
			// btnPrevious
			// 
			this.btnPrevious.BackColor = System.Drawing.Color.Transparent;
			this.btnPrevious.Location = new System.Drawing.Point(82, 9);
			this.btnPrevious.Name = "btnPrevious";
			this.btnPrevious.Size = new System.Drawing.Size(27, 27);
			this.btnPrevious.TabIndex = 2;
			this.btnPrevious.Text = "Play";
            this.btnToolTip.SetToolTip(this.btnPrevious, "Play Previous");

			// 
			// btnNext
			// 
			this.btnNext.BackColor = System.Drawing.Color.Transparent;
			this.btnNext.Location = new System.Drawing.Point(109, 9);
			this.btnNext.Name = "btnNext";
			this.btnNext.Size = new System.Drawing.Size(27, 27);
			this.btnNext.TabIndex = 3;
			this.btnNext.Text = "Play";
            this.btnToolTip.SetToolTip(this.btnNext, "Play Next");

			// 
			// PlayStopBar
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.Controls.Add(this.btnStop);
			this.Controls.Add(this.btnPlay);
			this.Controls.Add(this.btnNext);
			this.Controls.Add(this.btnPrevious);
			this.Name = "PlayStopBar";
			this.Size = new System.Drawing.Size(181, 44);
			this.ResumeLayout(false);

		}

		#endregion

		private ImageButton btnPlay;
		private ImageButton btnStop;
		private ImageButton btnPrevious;
		private ImageButton btnNext;
        private ToolTip btnToolTip;
	}
}
