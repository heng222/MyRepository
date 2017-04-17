//namespace ProWrite.UI.Clients.Test
//{
//    partial class PlayForm
//    {
//        /// <summary>
//        /// 必需的设计器变量。
//        /// </summary>
//        private System.ComponentModel.IContainer components = null;

//        /// <summary>
//        /// 清理所有正在使用的资源。
//        /// </summary>
//        /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
//        protected override void Dispose(bool disposing)
//        {
//            if (disposing && (components != null))
//            {
//                components.Dispose();
//            }
//            base.Dispose(disposing);
//        }

//        #region Windows 窗体设计器生成的代码

//        /// <summary>
//        /// 设计器支持所需的方法 - 不要
//        /// 使用代码编辑器修改此方法的内容。
//        /// </summary>
//        private void InitializeComponent()
//        {
//            this.btnPlay = new System.Windows.Forms.Button();
//            this.textBox1 = new System.Windows.Forms.TextBox();
//            this.pnlPlay = new System.Windows.Forms.Panel();
//            this.btnPause = new System.Windows.Forms.Button();
//            this.btnSave = new System.Windows.Forms.Button();
//            this.btnList = new System.Windows.Forms.Button();
//            this.btnCon = new System.Windows.Forms.Button();
//            this.button1 = new System.Windows.Forms.Button();
//            this.pnlPlay2 = new System.Windows.Forms.Panel();
//            this.button2 = new System.Windows.Forms.Button();
//            this.button3 = new System.Windows.Forms.Button();
//            this.button4 = new System.Windows.Forms.Button();
//            this.pictureBox1 = new System.Windows.Forms.PictureBox();
//            this.button5 = new System.Windows.Forms.Button();
//            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
//            this.SuspendLayout();
//            // 
//            // btnPlay
//            // 
//            this.btnPlay.Location = new System.Drawing.Point(12, 283);
//            this.btnPlay.Name = "btnPlay";
//            this.btnPlay.Size = new System.Drawing.Size(42, 23);
//            this.btnPlay.TabIndex = 0;
//            this.btnPlay.Text = "播放";
//            this.btnPlay.UseVisualStyleBackColor = true;
//            this.btnPlay.Click += new System.EventHandler(this.btnPlay_Click);
//            // 
//            // textBox1
//            // 
//            this.textBox1.Location = new System.Drawing.Point(12, 350);
//            this.textBox1.Name = "textBox1";
//            this.textBox1.Size = new System.Drawing.Size(201, 21);
//            this.textBox1.TabIndex = 2;
//            // 
//            // pnlPlay
//            // 
//            this.pnlPlay.BackColor = System.Drawing.SystemColors.Desktop;
//            this.pnlPlay.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
//            this.pnlPlay.Location = new System.Drawing.Point(12, 12);
//            this.pnlPlay.Name = "pnlPlay";
//            this.pnlPlay.Size = new System.Drawing.Size(278, 243);
//            this.pnlPlay.TabIndex = 3;
//            // 
//            // btnPause
//            // 
//            this.btnPause.Location = new System.Drawing.Point(134, 283);
//            this.btnPause.Name = "btnPause";
//            this.btnPause.Size = new System.Drawing.Size(47, 23);
//            this.btnPause.TabIndex = 4;
//            this.btnPause.Text = "暂停";
//            this.btnPause.UseVisualStyleBackColor = true;
//            this.btnPause.Click += new System.EventHandler(this.btnPause_Click);
//            // 
//            // btnSave
//            // 
//            this.btnSave.Location = new System.Drawing.Point(241, 283);
//            this.btnSave.Name = "btnSave";
//            this.btnSave.Size = new System.Drawing.Size(49, 23);
//            this.btnSave.TabIndex = 5;
//            this.btnSave.Text = " 输出";
//            this.btnSave.UseVisualStyleBackColor = true;
//            this.btnSave.Click += new System.EventHandler(this.btnSave_Click);
//            // 
//            // btnList
//            // 
//            this.btnList.Location = new System.Drawing.Point(60, 283);
//            this.btnList.Name = "btnList";
//            this.btnList.Size = new System.Drawing.Size(68, 23);
//            this.btnList.TabIndex = 6;
//            this.btnList.Text = "List播放";
//            this.btnList.UseVisualStyleBackColor = true;
//            this.btnList.Click += new System.EventHandler(this.btnList_Click);
//            // 
//            // btnCon
//            // 
//            this.btnCon.Location = new System.Drawing.Point(187, 283);
//            this.btnCon.Name = "btnCon";
//            this.btnCon.Size = new System.Drawing.Size(48, 23);
//            this.btnCon.TabIndex = 7;
//            this.btnCon.Text = "继续";
//            this.btnCon.UseVisualStyleBackColor = true;
//            this.btnCon.Click += new System.EventHandler(this.btnCon_Click);
//            // 
//            // button1
//            // 
//            this.button1.Location = new System.Drawing.Point(296, 283);
//            this.button1.Name = "button1";
//            this.button1.Size = new System.Drawing.Size(47, 23);
//            this.button1.TabIndex = 8;
//            this.button1.Text = "播放2";
//            this.button1.UseVisualStyleBackColor = true;
//            this.button1.Click += new System.EventHandler(this.button1_Click);
//            // 
//            // pnlPlay2
//            // 
//            this.pnlPlay2.BackColor = System.Drawing.SystemColors.Desktop;
//            this.pnlPlay2.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
//            this.pnlPlay2.Location = new System.Drawing.Point(241, 312);
//            this.pnlPlay2.Name = "pnlPlay2";
//            this.pnlPlay2.Size = new System.Drawing.Size(293, 59);
//            this.pnlPlay2.TabIndex = 9;
//            // 
//            // button2
//            // 
//            this.button2.Location = new System.Drawing.Point(349, 283);
//            this.button2.Name = "button2";
//            this.button2.Size = new System.Drawing.Size(52, 23);
//            this.button2.TabIndex = 10;
//            this.button2.Text = "下一个";
//            this.button2.UseVisualStyleBackColor = true;
//            this.button2.Click += new System.EventHandler(this.button2_Click);
//            // 
//            // button3
//            // 
//            this.button3.Location = new System.Drawing.Point(407, 283);
//            this.button3.Name = "button3";
//            this.button3.Size = new System.Drawing.Size(52, 23);
//            this.button3.TabIndex = 11;
//            this.button3.Text = "上一个";
//            this.button3.UseVisualStyleBackColor = true;
//            this.button3.Click += new System.EventHandler(this.button3_Click);
//            // 
//            // button4
//            // 
//            this.button4.Location = new System.Drawing.Point(465, 283);
//            this.button4.Name = "button4";
//            this.button4.Size = new System.Drawing.Size(69, 23);
//            this.button4.TabIndex = 12;
//            this.button4.Text = " 输出缩略图";
//            this.button4.UseVisualStyleBackColor = true;
//            this.button4.Click += new System.EventHandler(this.button4_Click);
//            // 
//            // pictureBox1
//            // 
//            this.pictureBox1.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
//            this.pictureBox1.Location = new System.Drawing.Point(296, 12);
//            this.pictureBox1.Name = "pictureBox1";
//            this.pictureBox1.Size = new System.Drawing.Size(400, 200);
//            this.pictureBox1.TabIndex = 13;
//            this.pictureBox1.TabStop = false;
//            // 
//            // button5
//            // 
//            this.button5.Location = new System.Drawing.Point(12, 312);
//            this.button5.Name = "button5";
//            this.button5.Size = new System.Drawing.Size(47, 23);
//            this.button5.TabIndex = 14;
//            this.button5.Text = "停止";
//            this.button5.UseVisualStyleBackColor = true;
//            this.button5.Click += new System.EventHandler(this.button5_Click);
//            // 
//            // PlayForm
//            // 
//            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
//            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
//            this.ClientSize = new System.Drawing.Size(977, 416);
//            this.Controls.Add(this.button5);
//            this.Controls.Add(this.pictureBox1);
//            this.Controls.Add(this.button4);
//            this.Controls.Add(this.button3);
//            this.Controls.Add(this.button2);
//            this.Controls.Add(this.pnlPlay2);
//            this.Controls.Add(this.button1);
//            this.Controls.Add(this.btnCon);
//            this.Controls.Add(this.btnList);
//            this.Controls.Add(this.btnSave);
//            this.Controls.Add(this.btnPause);
//            this.Controls.Add(this.pnlPlay);
//            this.Controls.Add(this.textBox1);
//            this.Controls.Add(this.btnPlay);
//            this.Name = "PlayForm";
//            this.Text = "PlayForm";
//            this.Load += new System.EventHandler(this.PlayForm_Load);
//            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
//            this.ResumeLayout(false);
//            this.PerformLayout();

//        }

//        #endregion

//        private System.Windows.Forms.Button btnPlay;
//        private System.Windows.Forms.TextBox textBox1;
//        private System.Windows.Forms.Panel pnlPlay;
//        private System.Windows.Forms.Button btnPause;
//        private System.Windows.Forms.Button btnSave;
//        private System.Windows.Forms.Button btnList;
//        private System.Windows.Forms.Button btnCon;
//        private System.Windows.Forms.Button button1;
//        private System.Windows.Forms.Panel pnlPlay2;
//        private System.Windows.Forms.Button button2;
//        private System.Windows.Forms.Button button3;
//        private System.Windows.Forms.Button button4;
//        private System.Windows.Forms.PictureBox pictureBox1;
//        private System.Windows.Forms.Button button5;
//    }
//}