using System;
using System.Drawing;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WindowsApplication
{
    public partial class CommTestForm : Form
    {
        /// <summary>
        /// Constructor
        /// </summary>
        public CommTestForm()
        {
            InitializeComponent();

            InitalizeNotifyIcon();

            CreateCustomTabpages();

            this.btnAsynAwait.Click += this.btnAsynAwait_Click2;
            this.btnAsynAwait.Click += this.btnAsynAwait_Click;
        }

        #region "private methods"
        private void CreateCustomTabpages()
        {
            var newTabPage = new TabPage("DataGridView Demo");
            newTabPage.Controls.Add(new CtrlDataGridViewDemo());
            this.tabControl1.TabPages.Add(newTabPage);

            // 
            newTabPage = new TabPage("PropertyGrid Demo");
            newTabPage.Controls.Add(new CtrlPropertyGridDemo() { Dock = DockStyle.Fill });
            this.tabControl1.TabPages.Add(newTabPage);

        }

        #endregion


        #region "控件事件"
        /// <summary>
        /// Test button click event
        /// </summary>
        private void OnBtnHelpClick(object sender, EventArgs args)
        {
            try
            {
                Console.WriteLine("UI Thread ID = " + Thread.CurrentThread.ManagedThreadId);
                Help.ShowPopup(this, "这里是帮助信息", new Point(100, 100));
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        private void OnBtnCannotOperateUI(object sender, EventArgs e)
        {
            // 总结：
            // 1、BeginInvoke类似MFC中的PostMessage，Invoke类似SendMessage。
            // 2、Control.BeginInvoke与Invoke 都是在Control所属的线程上执行。
            // 3、Show/ShowDialog指定参数Owner后，将在Owner上方显示，否则将显示在后方。
            // 4、Show与ShowDiaglog 的区别是能否与父窗体进行交互。
            // 5、无论在哪个线程调用主窗体的BeginInvoke，效果都一样（参见 form1 与 form2）。

            this.BeginInvoke(new Action(() =>
            {
                var form1 = new Form();
                form1.Text = string.Format("form1, TID = {0}", Thread.CurrentThread.ManagedThreadId);
                form1.ShowDialog();   //     在主窗体上方显示模式对话框。
                form1.ShowDialog(this); // 在主窗体上方显示模式对话框。
            }));

            // 在线程中
            Task.Factory.StartNew(() =>
            {
                try
                {
                    // 注：主窗体最大化后，可以使用Alt+F4关闭后台窗体。

                    // 注：注意 BeginInvoke 与 Invoke 区别。
                    this.BeginInvoke(new Action(() =>
                    {
                        var form2 = new Form();
                        form2.Text = string.Format("form2, TID = {0}", Thread.CurrentThread.ManagedThreadId);
                        form2.ShowInTaskbar = false;

                        // 注：Show、ShowDialog方法的区别；Show与Show(Owner)区别。
                        //form2.TopMost = true; // 指定TopMost为true后，则form2显示在主窗体的前方；否则form2显示在主窗体的后方。

                        form2.Show(this); // 在主窗体上方显示非模式对话框。
                        //form2.Show(); // 在主窗体下方显示非模式对话框。

                        //form2.ShowDialog();   // 在主窗体下方显示模式对话框。
                        //form2.ShowDialog(this); // 在主窗体上方显示模式对话框。
                    }));
                    
                    // 注：
                    var formAsyn = new Form();
                    formAsyn.Text = string.Format("Sync call, TID = {0}", Thread.CurrentThread.ManagedThreadId); ;
                    formAsyn.ShowInTaskbar = false;
                    formAsyn.TopMost = true; // 此处设置TopMost没有任何效果。
                    formAsyn.ShowDialog();
                }
                catch (System.Exception ex)
                {
                    // 这里无法捕获 form1_Load中的异常。
                    Console.WriteLine(ex);
                }
            });
        }

        private async void btnAsynAwait_Click(object sender, EventArgs e)
        {
            try
            {
                await ShowProgressOnButton().ConfigureAwait(true);

                // await ：当前界面线程依然位于就绪队列中。不像调用Wait函数那样进入等待队列。
                // 使用 await 调用 AsyncAwaitFunction，类似使用 Task(AsyncAwaitFunction).ContinueWait( AsyncAwaitFunction 之后的代码）。

                btnAsynAwait.Text = "Asyn/Await";
                MessageBox.Show("ShowProgressOnButton 执行完成！");
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private async Task ShowProgressOnButton()
        {
            await Task.Run(() =>
            {
                for (int i = 0; i < 100; i++)
                {
                    this.BeginInvoke(new Action(() => btnAsynAwait.Text = string.Format("{0}%", i)));
                    Thread.Sleep(100);

                    //if (i == 50) throw new Exception("此异常可以由UI线程捕获");
                }
            }).ConfigureAwait(false);
        }

        private async void btnAsynAwait_Click2(object sender, EventArgs e)
        {
            try
            {
                await ShowProgressOnForm().ConfigureAwait(true);

                this.Text = "CommTestForm";
                MessageBox.Show("ShowProgressOnForm 执行完成！");
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }
        private async Task ShowProgressOnForm()
        {
            await Task.Run(() =>
            {
                for (int i = 0; i < 100; i++)
                {
                    this.BeginInvoke(new Action(() => this.Text = string.Format("{0}%", i)));
                    Thread.Sleep(100);
                }
            }).ConfigureAwait(true);
        }


        /// <summary>
        /// 退出
        /// </summary>
        private void btnExit_Click(object sender, EventArgs e)
        {
            try
            {
                Application.Exit();
            }
            catch (System.Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }


        /// <summary>
        /// 双击托盘图标时
        /// </summary>
        private void appNotifyIcon_MouseDoubleClick(object sender, MouseEventArgs e)
        {
            try
            {
                this.Show();
                this.TopLevel = true;
            }
            catch (System.Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        /// <summary>
        /// 当窗体大小发生变化时
        /// </summary>
        private void CommTestForm_SizeChanged(object sender, EventArgs e)
        {
            try
            {
                if (this.WindowState == FormWindowState.Minimized)
                {
                    this.Hide();
                }
            }
            catch (System.Exception ex)
            {
                MessageBox.Show(ex.Message);
            }

        }

        /// <summary>
        /// 当窗体将要关闭时触发
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void CommTestForm_FormClosing(object sender, FormClosingEventArgs e)
        {
            try
            {
                //if (e.CloseReason == CloseReason.UserClosing)
                //{
                //    e.Cancel = true;
                //    this.Hide();
                //}
            }
            catch (System.Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        private void OnCommTestForm_Load(object sender, EventArgs e)
        {
        }
        #endregion
        
        #region "Notify菜单"

        private void InitalizeNotifyIcon()
        {
            appNotifyIcon.Text = "提示文本...";
        }

        private void restoreToolStripMenuItem_Click(object sender, EventArgs e)
        {
            try
            {
                this.Show();
            }
            catch (System.Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        private void exitToolStripMenuItem_Click(object sender, EventArgs e)
        {
            try
            {
                Application.Exit();
            }
            catch (System.Exception ex)
            {
                MessageBox.Show(ex.Message);
            }

        }

        #endregion
    }
}