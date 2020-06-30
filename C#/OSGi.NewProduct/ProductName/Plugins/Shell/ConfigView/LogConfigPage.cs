/*----------------------------------------------------------------
// ��˾���ƣ������빫˾����
// 
// ��Ʒ���ƣ���Ʒ����
//
// �� �� �ˣ�zhangheng
// �������ڣ�2013-7-17 13:53:09 
// ��    �䣺heng222_z@163.com
//
// Copyright (C) ��˾���ƣ���������Ȩ����
//
//----------------------------------------------------------------*/
using System;
using System.Collections.Generic;
using System.Drawing;
using System.Windows.Forms;

using Acl.Log;

using Platform.Presentation.Options;

using Products.Infrastructure.Log;
using Products.Presentation;

namespace Products.Shell.ConfigView
{
    /// <summary>
    /// ������־������ͼ
    /// </summary>
    public partial class LogConfigPage : UserControl, IOptionControl, IOptionInfo//, IAppConfigPage
    {

        //private AppConfigNode _cfgNode = new AppConfigNode();
        private List<ILog> _appLogHandlers = new List<ILog>();

        /// <summary>
        /// 
        /// </summary>
        public LogConfigPage()
        {
            InitializeComponent();

            //
            foreach (string levelName in LogLevelManager.LogLevelNames)
            {
                cbxGlobalLoglevel.Items.Add(levelName);
            }
        }

        #region "private methods"

        /// <summary>
        /// 
        /// </summary>
        private void Initialize()
        {
            nudDiagFileExpiredDays.Value = LogSettings.ExpiredDays;
            _appLogHandlers.AddRange(LogManager.GetCurrentLoggers());

            // ȫ��������Ͽ�
            this.cbxGlobalLoglevel.SelectedIndex = (int)LogSettings.Level;
            this.cbxGlobalLoglevel.DrawItem += this.OnLogSaveLevelComboBox_DrawItem;

            // ����������Ͽ�
            flowLayoutPanel.Controls.Clear();
            foreach (ILog item in _appLogHandlers)
            {
                // ������ǩ
                Label label = new Label();
                label.Text = string.Format("{0}", item.Name);
                label.Width = 80;
                flowLayoutPanel.Controls.Add(label);

                // ����ComboBox
                #region "����ComboBox"
                ComboBox cbxNew = new ComboBox();
                cbxNew.Width = 100;
                cbxNew.Tag = item;
                cbxNew.DropDownStyle = ComboBoxStyle.DropDownList;
                foreach (string levelName in LogLevelManager.LogLevelNames)
                {
                    cbxNew.Items.Add(levelName);
                }
                cbxNew.Enabled = !this.rBtnGlobal.Checked;
                cbxNew.SelectedIndex = (int)item.LogLevel;
                flowLayoutPanel.Controls.Add(cbxNew);
                item.LogLevelChanged += LogSaveLevelItemChanged;

                // DrawItem event
                //cbxNew.DrawMode = DrawMode.IsNormal;
                cbxNew.DrawItem += OnLogSaveLevelComboBox_DrawItem;
                #endregion

                // ����ؼ�
            }


            // Ĭ��ȫ������
            this.rBtnGlobal.Checked = false;
            this.rBtnIndependent.Checked = true;
        }
        #endregion


        #region IOptionView ��Ա
        /// <summary>
        /// 
        /// </summary>
        public string Title
        {
            get { return "����������־"; }
        }

        string IOptionInfo.Name { get { return ConfigNodeNames.Environment.Log; } }

        /// <summary>
        /// 
        /// </summary>
        public Control View
        {
            get { return this; }
        }
        ///// <summary>
        ///// 
        ///// </summary>
        //public AppConfigNode Node
        //{
        //    get { return _cfgNode; }
        //}

        /// <summary>
        /// Apply changes
        /// </summary>
        public void ApplyChanges()
        {
            LogSettings.ExpiredDays = (ushort)nudDiagFileExpiredDays.Value;

            if (rBtnGlobal.Checked)
            {
                LogSettings.Level = (LogLevel)this.cbxGlobalLoglevel.SelectedIndex;

                foreach (ILog item in _appLogHandlers)
                {
                    item.LogLevel = LogSettings.Level;
                }
            }
            else
            {
                foreach (Control item in flowLayoutPanel.Controls)
                {
                    if (item is ComboBox)
                    {
                        ComboBox logLevelCbx = (ComboBox)item;
                        ILog appHandler = logLevelCbx.Tag as ILog;
                        appHandler.LogLevel = (LogLevel)logLevelCbx.SelectedIndex;
                    }
                }
            }
        }
        #endregion

        #region "private methods"
        #endregion


        #region "�ؼ��¼�"

        private void LogConfigPage_Load(object sender, EventArgs e)
        {
            try
            {
                this.Initialize();
            }
            catch (System.Exception /*ex*/)
            {
            }
        }
        /// <summary>
        /// �������ã�ȫ�֡�������
        /// </summary>
        private void radioButton1_CheckedChanged(object sender, EventArgs e)
        {
            try
            {
                if (rBtnGlobal.Checked)
                {
                    this.cbxGlobalLoglevel.DrawMode = DrawMode.OwnerDrawFixed;
                    this.cbxGlobalLoglevel.Enabled = true;

                    foreach (Control item in flowLayoutPanel.Controls)
                    {
                        if (item is ComboBox)
                        {
                            ((ComboBox)item).DrawMode = DrawMode.Normal;
                            item.Enabled = false;
                        }
                    }
                }
                else
                {
                    this.cbxGlobalLoglevel.DrawMode = DrawMode.Normal;
                    this.cbxGlobalLoglevel.Enabled = false;

                    foreach (Control item in flowLayoutPanel.Controls)
                    {
                        if (item is ComboBox)
                        {
                            ((ComboBox)item).DrawMode = DrawMode.OwnerDrawFixed;
                            item.Enabled = true;
                        }
                    }
                }
            }
            catch (System.Exception /*ex*/)
            {

            }
        }

        /// <summary>
        /// ����������Ͽ�
        /// </summary>
        private void OnLogSaveLevelComboBox_DrawItem(object sender, DrawItemEventArgs e)
        {
            try
            {
                ComboBox comboBox1 = sender as ComboBox;


                using (Pen fColor = new Pen(Color.Black), bColor = new Pen(Color.White))
                {
                    LogLevel level = (LogLevel)e.Index;
                    if (level == LogLevel.Debug)
                    {
                        fColor.Color = Color.DarkGreen;
                    }
                    else if (level == LogLevel.Information)
                    {
                        fColor.Color = Color.Green;
                        //bColor.Color = Color.Green;
                    }
                    else if (level == LogLevel.Warning)
                    {
                        fColor.Color = Color.Black;
                        bColor.Color = Color.Yellow;
                    }
                    else if (level == LogLevel.Error
                        || level == LogLevel.Fatal)
                    {
                        fColor.Color = Color.Red;
                        //bColor.Color = Color.Red;
                    }

                    if ((e.State & DrawItemState.Focus) != 0)
                    {
                        //�����������ComboBox��item�ı���ɫ
                        e.Graphics.FillRectangle(Brushes.Blue, e.Bounds);
                    }
                    else
                    {
                        e.Graphics.FillRectangle(bColor.Brush, e.Bounds);
                    }

                    e.Graphics.DrawString((string)comboBox1.Items[e.Index], this.Font, fColor.Brush, e.Bounds);
                }
            }
            catch (System.Exception /*ex*/)
            {
            }
        }

        /// <summary>
        /// ��־�ı��漶�����仯ʱ������
        /// </summary>
        private void LogSaveLevelItemChanged(object sender, LogLevelChangedEventArgs args)
        {
            try
            {
                foreach (Control item in flowLayoutPanel.Controls)
                {
                    ComboBox cbxLogLevel = item as ComboBox;

                    if (cbxLogLevel != null)
                    {
                        ILog log = cbxLogLevel.Tag as ILog;

                        if (item.Tag == sender
                            && cbxLogLevel.SelectedIndex != (int)log.LogLevel)
                        {
                            cbxLogLevel.SelectedIndex = (int)log.LogLevel;
                        }
                    }
                }
            }
            catch (System.Exception /*ex*/)
            {
            }
        }
        #endregion
    }
}
