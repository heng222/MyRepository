using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Drawing;
using System.Linq;
using System.Windows.Forms;
using System.Threading.Tasks;
using System.Threading;

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


        #region "�ؼ��¼�"
        /// <summary>
        /// Test button click event
        /// </summary>
        private void OnBtnHelpClick(object sender, EventArgs args)
        {
            try
            {
                Help.ShowPopup(this, "�����ǰ�����Ϣ", new Point(100, 100));
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        private void OnBtnCannotOperateUI(object sender, EventArgs e)
        {
            // �ܽ᣺
            // 1��BeginInvoke����MFC�е�PostMessage��Invoke����SendMessage��
            // 2��Control.BeginInvoke��Invoke ������Control�������߳���ִ�С�
            // 3��Show/ShowDialogָ������Owner�󣬽���Owner�Ϸ���ʾ��������ʾ�ں󷽡�
            // 4��Show��ShowDiaglog ���������ܷ��븸������н�����
            // 5���������ĸ��̵߳����������BeginInvoke��Ч����һ�����μ� form1 �� form2����

            this.BeginInvoke(new Action(() =>
            {
                var form1 = new Form();
                form1.Text = string.Format("form1, TID = {0}", Thread.CurrentThread.ManagedThreadId);
                form1.ShowDialog();   //     ���������Ϸ���ʾģʽ�Ի���
                form1.ShowDialog(this); // ���������Ϸ���ʾģʽ�Ի���
            }));

            // ���߳���
            Task.Factory.StartNew(() =>
            {
                try
                {
                    // ע����������󻯺󣬿���ʹ��Alt+F4�رպ�̨���塣

                    // ע��ע�� BeginInvoke �� Invoke ����
                    this.BeginInvoke(new Action(() =>
                    {
                        var form2 = new Form();
                        form2.Text = string.Format("form2, TID = {0}", Thread.CurrentThread.ManagedThreadId);
                        form2.ShowInTaskbar = false;

                        // ע��Show��ShowDialog����������Show��Show(Owner)����
                        //form2.TopMost = true; // ָ��TopMostΪtrue����form2��ʾ���������ǰ��������form2��ʾ��������ĺ󷽡�

                        form2.Show(this); // ���������Ϸ���ʾ��ģʽ�Ի���
                        //form2.Show(); // ���������·���ʾ��ģʽ�Ի���

                        //form2.ShowDialog();   // ���������·���ʾģʽ�Ի���
                        //form2.ShowDialog(this); // ���������Ϸ���ʾģʽ�Ի���
                    }));
                    
                    // ע��
                    var formAsyn = new Form();
                    formAsyn.Text = string.Format("Sync call, TID = {0}", Thread.CurrentThread.ManagedThreadId); ;
                    formAsyn.ShowInTaskbar = false;
                    formAsyn.TopMost = true; // �˴�����TopMostû���κ�Ч����
                    formAsyn.ShowDialog();
                }
                catch (System.Exception ex)
                {
                    // �����޷����� form1_Load�е��쳣��
                    Console.WriteLine(ex);
                }
            });
        }        

        /// <summary>
        /// �˳�
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
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
        /// ˫������ͼ��ʱ
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
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
        /// �������С�����仯ʱ
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
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
        /// �����彫Ҫ�ر�ʱ����
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
        
        #region "Notify�˵�"

        private void InitalizeNotifyIcon()
        {
            appNotifyIcon.Text = "��ʾ�ı�...";
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