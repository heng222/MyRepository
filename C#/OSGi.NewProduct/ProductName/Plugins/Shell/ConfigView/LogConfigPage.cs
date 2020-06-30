/*----------------------------------------------------------------
// 公司名称：请输入公司名称
// 
// 产品名称：产品名称
//
// 创 建 人：zhangheng
// 创建日期：2013-7-17 13:53:09 
// 邮    箱：heng222_z@163.com
//
// Copyright (C) 公司名称，保留所有权利。
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
    /// 程序日志配置视图
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

            // 全局设置组合框
            this.cbxGlobalLoglevel.SelectedIndex = (int)LogSettings.Level;
            this.cbxGlobalLoglevel.DrawItem += this.OnLogSaveLevelComboBox_DrawItem;

            // 独立设置组合框
            flowLayoutPanel.Controls.Clear();
            foreach (ILog item in _appLogHandlers)
            {
                // 创建标签
                Label label = new Label();
                label.Text = string.Format("{0}", item.Name);
                label.Width = 80;
                flowLayoutPanel.Controls.Add(label);

                // 创建ComboBox
                #region "创建ComboBox"
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

                // 对齐控件
            }


            // 默认全局设置
            this.rBtnGlobal.Checked = false;
            this.rBtnIndependent.Checked = true;
        }
        #endregion


        #region IOptionView 成员
        /// <summary>
        /// 
        /// </summary>
        public string Title
        {
            get { return "程序运行日志"; }
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


        #region "控件事件"

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
        /// 报警设置（全局、独立）
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
        /// 报警级别组合框
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
                        //设置鼠标悬浮ComboBox的item的背景色
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
        /// 日志的保存级别发生变化时发生。
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
