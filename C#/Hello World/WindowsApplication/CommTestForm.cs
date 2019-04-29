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
        private List<ToolStripMenuItem> _topMenuItems = new List<ToolStripMenuItem>();

        /// <summary>
        /// Constructor
        /// </summary>
        public CommTestForm()
        {
            InitializeComponent();

            try
            {
                InitalizeNotifyIcon();
                InitializePropertyGrade();

                var newTabPage = new TabPage("DataGridView Demo");
                newTabPage.Controls.Add(new CtrlDataGridViewDemo());
                this.tabControl1.TabPages.Add(newTabPage);
            }
            catch (System.Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        private IEnumerable<ToolStripItem> GetSrcMenuItem()
        {
            return this.menuStrip1.Items.OfType<ToolStripItem>();
        }

        #region "�ؼ��¼�"
        /// <summary>
        /// Test button click event
        /// </summary>
        private void btnTest_Click(object sender, EventArgs args)
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
        
        /// <summary>
        /// �޷����������档
        /// </summary>
        private void DemoCannotOperaterUi()
        {            
            MessageBox.Show(string.Format("Main thread ID = {0}", Thread.CurrentThread.ManagedThreadId));

            // 
            Task.Factory.StartNew(() =>
            {
                try
                {
                    // ���´�����ʾForm�������治���Բ�����FormҲ��������
                    // ��BeginInvoke��ΪInvoke����Ч����
                    this.BeginInvoke(new Action(() =>
                    {
                        var form2 = new Form();
                        form2.Text = string.Format("Using Invoke/BeginInvoke, TID = {0}", Thread.CurrentThread.ManagedThreadId);
                        form2.ShowInTaskbar = false;
                        form2.ShowDialog();
                    }));

                    // ���´�����ʾForm����������Բ�������Form��������
                    var form1 = new Form();
                    form1.Text = string.Format("Sync call, TID = {0}", Thread.CurrentThread.ManagedThreadId); ;
                    form1.ShowInTaskbar = false;
                    form1.Load += form1_Load;
                    form1.ShowDialog();
                }
                catch (System.Exception ex)
                {
                    // �����޷����� form1_Load�е��쳣��
                    Console.WriteLine(ex);
                }
            });

            this.TopMost = true;

            // �ܽ᣺
            // 1��BeginInvoke����MFC�е�PostMessage��Invoke����SendMessage��
            // 2��Control.BeginInvoke��Invoke ������Control�������߳���ִ�С�
        }

        void form1_Load(object sender, EventArgs e)
        {
            throw new NotImplementedException();
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


        #region "private methods"
               

        class PropertyElement
        {
            public List<PlatformID> PID { get; set; }
            public Color BackColor { get; set; }
            public string Name { get; set; }

            public PropertyElement()
            {
                this.PID = new List<PlatformID> { PlatformID.Win32NT, PlatformID.Unix};
                this.BackColor = Color.AliceBlue;
                this.Name = "user";
            }
        }
        private void InitializePropertyGrade()
        {
            this.propertyGrid1.Dock = DockStyle.Fill;

            this.propertyGrid1.SelectedObject = (new PropertyElement());
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