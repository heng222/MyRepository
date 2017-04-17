using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO;
using ProWrite.Core;
using System.Configuration;
using DevExpress.XtraEditors;
using System.Globalization;
using DevExpress.XtraSpellChecker;
using DevExpress.XtraSpellChecker.Forms;
using ProWrite.UI.Controls.Common;
using ProWrite.DataProviders;
using ProWrite.Entity;

namespace ProWrite.UI.Controls.Editor
{
    public partial class CustomDirtyWordsDictionary : XtraForm
    {
        StreamReader strReader;
        StreamWriter strWriter;
        protected DevExpress.XtraSpellChecker.SharedDictionaryStorage sharedDictionaryStorage1;
        public CustomDirtyWordsDictionary()
        {
            InitializeComponent();
            Init();
        }

        void Init()
        {
            try
            {
                btnLibraryLocation.Text = Config.GetAppSettingValueBytKey("ProFilePath");
                this.btnEditBackupPath.Text = Config.GetAppSettingValueBytKey("BackupFilePath");
                if (string.IsNullOrEmpty(btnEditBackupPath.Text))
                {
                    string backPath =Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.ApplicationData), "ProWrite\\Backup");
                    Config.AddOrUpdateAppSettings("BackupFilePath", backPath);
                    btnEditBackupPath.Text = backPath;
                }
                string autoDeleteDays = Config.GetAppSettingValueBytKey("AutoDeleteFileDays");// ConfigurationManager.AppSettings["AutoDeleteFileDays"];
                if (!string.IsNullOrEmpty(autoDeleteDays))
                {
                    this.chkAutoDelete.Checked = true;
                    spnAutoDelete.Value = Convert.ToInt32(autoDeleteDays);
                }
                else
                {
                    this.chkAutoDelete.Checked = false;
                    spnAutoDelete.Value = 1;
                }
                string autoBackupDays = Config.GetAppSettingValueBytKey("AutoBackupFileDays");
                if (!string.IsNullOrEmpty(autoBackupDays))
                {
                    checkBox2.Checked = true;
                    spnZhouQi.Value = Convert.ToInt32(autoBackupDays);
                }
                else
                {
                    checkBox2.Checked = false;
                    spnZhouQi.Value = 1;
                }

                lblAutoDel1.Enabled = lblAutoDelete2.Enabled = spnAutoDelete.Enabled = chkAutoDelete.Checked;
                lblEvery.Enabled = lblEveryAuto.Enabled = spnZhouQi.Enabled = checkBox2.Checked;

                ddlBackupDate.Properties.Items.Clear();

                try
                {
                    string[] fileList = System.IO.Directory.GetFileSystemEntries(btnEditBackupPath.Text);
                    if (fileList != null && fileList.Length > 0)
                    {
                        for (int i = 0; i < fileList.Length; i++)
                        {
                            if (fileList[i].Contains(".bk"))
                                ddlBackupDate.Properties.Items.Add(fileList[i].Substring(fileList[i].LastIndexOf('\\') + 1, 19));
                        }
                        ddlBackupDate.SelectedIndex = 0;
                    }
                }
                catch { }


                //strReader = new StreamReader(Constance.AppPath + Config.GetAppSettingValueBytKey("ProfaneWordList"));//ConfigurationManager.AppSettings["ProfaneWordList"]);
                ////strReader = new StreamReader(DemoUtils.GetRelativePath("CustomEnglish.dic"));
                ////strWriter = new StreamWriter(Constance.AppPath + ConfigurationManager.AppSettings["ProfaneWordList"]);
                //String txtStr = strReader.ReadToEnd();
                //strReader.Close();
                //strReader.Dispose();
                //List<string> list = new List<string>();
                //while (sr.Read() != -1)
                //{
                //    list.Add(sr.ReadLine());
                //}
                memoEdit1.Text = ServiceManager.Get<DirtyWordList>().ToString();
                strReader = new StreamReader(DemoUtils.GetRelativePath("CustomEnglish.dic"));
                var txtStr = strReader.ReadToEnd();
                strReader.Close();
                strReader.Dispose();
                memoDictionary.Text = txtStr;
            }
            catch { }

        }
        private void btnOK_Click(object sender, EventArgs e)
        {
            bool isRestart = false;
            BackupApply(false);
            if (!string.IsNullOrEmpty(btnLibraryLocation.Text))
            {
                if (Config.GetAppSettingValueBytKey("ProFilePath") != btnLibraryLocation.Text)
                {
                    if (MsgBox.WarningConfirm("Are you sure you want to update the library location?", MessageBoxButtons.YesNo) == DialogResult.No)
                        return;

                    isRestart = true;
                }
            }
            try
            {
                strWriter = new StreamWriter(Constance.AppPath + Config.GetAppSettingValueBytKey("ProfaneWordList"));//ConfigurationManager.AppSettings["ProfaneWordList"]);
                if (strWriter != null)
                {
                    strWriter.Write(memoEdit1.Text);
                    strWriter.Close();
                    strWriter.Dispose();
                }
                strWriter = new StreamWriter(DemoUtils.GetRelativePath("CustomEnglish.dic"));
                if (strWriter != null)
                {
                    strWriter.Write(this.memoDictionary.Text);
                    strWriter.Close();
                    strWriter.Dispose();
                }
            }
            catch { }

            ServiceManager.Remove(typeof(DirtyWordList));
            DirtyWordList.Load();

            //var dirtyWords1 = ServiceManager.Get<DirtyWordList>();
            ////for (int i = 0; i < memoEdit1.Lines.Length; i++)

            ////    dirtyWords1.Add(memoEdit1.Lines[i]);
            if (isRestart)
            {


                Config.CopyDir(Constance.SignImageDir, btnLibraryLocation.Text + "\\Image");
                File.Copy(Constance.BinaryDataFile, btnLibraryLocation.Text + "\\data.binary", true);
                Config.CopyDir(Constance.LibraryDir, btnLibraryLocation.Text + "\\Library");
                Config.CopyDir(Constance.LayoutDir, btnLibraryLocation.Text + "\\Layout");
                Config.CopyDir(Constance.DataPath + "\\log", btnLibraryLocation.Text + "\\log");
                Config.CopyDir(Constance.DataPath + "\\imagetemp", btnLibraryLocation.Text + "\\imagetemp");

                DataGate.Provider.Path = btnLibraryLocation.Text + "\\";
                //ProjectInfo.Current.Clear();
                Application.Restart();
            }
            //List<string> list = new List<string>();
            //strReader = new StreamReader(Constance.AppPath + ConfigurationManager.AppSettings["ProfaneWordList"]);
            //for (int i = 0; i < 1148; i++)
            //    dirtyWords1.Add(strReader.ReadLine());+
            ////}
            //strReader.Close();
            //strReader.Dispose();
            //dirtyWords.AddRange(list);
        }

        private void button1_Click(object sender, System.EventArgs e)
        {

        }

        private void buttonEdit1_Click(object sender, EventArgs e)
        {
            if (folderBrowserDialog1.ShowDialog() == DialogResult.OK)
            {
                btnEditBackupPath.Text = folderBrowserDialog1.SelectedPath;
            }

        }

        private void buttonEdit2_Click(object sender, EventArgs e)
        {
            if (folderBrowserDialog2.ShowDialog() == DialogResult.OK)
            {
                btnLibraryLocation.Text = folderBrowserDialog2.SelectedPath;
            }
        }

        private void btnBackupNow_Click(object sender, EventArgs e)
        {
            if (MsgBox.WarningConfirm("Are you sure you want to backup now?", MessageBoxButtons.YesNo) == DialogResult.Yes)
            {
                try
                {
                    string dateTime = DateTime.Now.ToString("yyyy-MM-dd_HH-mm-ss");
                    //Config.CopyDir(Constance.DataPath, btnEditBackupPath.Text + "\\" + dateTime + ".bk\\");
                    Config.CopyDir(Constance.SignImageDir, btnEditBackupPath.Text + "\\" + dateTime + ".bk\\Image");
                    File.Copy(Constance.BinaryDataFile, btnEditBackupPath.Text + "\\" + dateTime + ".bk\\data.binary", true);
                    Config.CopyDir(Constance.LibraryDir, btnEditBackupPath.Text + "\\" + dateTime + ".bk\\Library");
                    Config.CopyDir(Constance.LayoutDir, btnEditBackupPath.Text + "\\" + dateTime + ".bk\\Layout");
                    Config.CopyDir(Constance.DataPath + "\\log", btnEditBackupPath.Text + "\\" + dateTime + ".bk\\log");

                    Config.CopyDir(Constance.DataPath + "\\imagetemp", btnEditBackupPath.Text + "\\" + dateTime + ".bk\\imagetemp");
                    GetBadkupDateName();
                }
                catch { }
            }
        }



        private void checkBox2_CheckedChanged(object sender, EventArgs e)
        {
            lblEvery.Enabled = lblEveryAuto.Enabled = spnZhouQi.Enabled = checkBox2.Checked;
        }

        private void btnApply_Click(object sender, EventArgs e)
        {
            Cursor = Cursors.WaitCursor;
            BackupApply(true);
            Cursor = Cursors.Default;
        }

        private void RemoveAppSettings(string key)
        {
            var config = ConfigurationManager.OpenExeConfiguration(ConfigurationUserLevel.None);
            //config.AppSettings.Settings.Add("A", "123");
            config.AppSettings.Settings.Remove(key);
            config.Save();
        }

        private void BackupApply(bool b)
        {
            try
            {
                Config.AddOrUpdateAppSettings("BackupFilePath", btnEditBackupPath.Text);
                if (checkBox2.Checked)
                    Config.AddOrUpdateAppSettings("AutoBackupFileDays", spnZhouQi.Value.ToString());
                else
                    Config.AddOrUpdateAppSettings("AutoBackupFileDays", "");
                if (chkAutoDelete.Checked)
                    Config.AddOrUpdateAppSettings("AutoDeleteFileDays", spnAutoDelete.Value.ToString());
                else
                    Config.AddOrUpdateAppSettings("AutoDeleteFileDays", "");
                if (b)
                    MsgBox.Warning("Applied successed.");
            }
            catch
            {
                if (b)
                    MsgBox.Warning("Applied failed.");
            }
        }

        private void btnRestore_Click(object sender, EventArgs e)
        {
            if (MsgBox.WarningConfirm("Ary you sure you want to restore the backup date?", MessageBoxButtons.YesNo) == DialogResult.No)
                return;

            if (ddlBackupDate.Properties.Items.Count <= 0)
            {
                MsgBox.Warning("Sorry,no backup data.");
                return;
            }
            try
            {
                Config.CopyDir(btnEditBackupPath.Text + "\\" + ddlBackupDate.Text + ".bk", Constance.DataPath);
                //Config.CopyDir(btnEditBackupPath.Text + "\\" + ddlBackupDate.Text + ".bk\\SignImage", Constance.SignImageDir);
                DataGate.Provider.Path = Constance.DataPath;// Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.ApplicationData), "ProWrite"/* + VersionCode*/) + "\\";
                DataGate.Provider.Refresh();
                //DataGate.Update();
                //DataGate.Provider.FileName = "data.binary";
                //ProjectInfo.Current.Clear();
                Application.Restart();
                //MsgBox.Warning("Restore successed.");
            }
            catch
            {
                Application.Restart();
                //MsgBox.Warning("Restore failed,please try again.");
            }
        }

        private void chkAutoDelete_CheckedChanged(object sender, EventArgs e)
        {
            lblAutoDel1.Enabled = lblAutoDelete2.Enabled = spnAutoDelete.Enabled = chkAutoDelete.Checked;
        }

        private void btnEditBackupPath_EditValueChanged(object sender, EventArgs e)
        {
            GetBadkupDateName();
        }

        private void GetBadkupDateName()
        {
            try
            {
                ddlBackupDate.Properties.Items.Clear();
                string[] fileList = System.IO.Directory.GetFileSystemEntries(btnEditBackupPath.Text);
                if (fileList != null && fileList.Length > 0)
                {
                    for (int i = 0; i < fileList.Length; i++)
                    {
                        if (fileList[i].Contains(".bk"))
                            ddlBackupDate.Properties.Items.Add(fileList[i].Substring(fileList[i].LastIndexOf('\\') + 1, 19));
                    }
                    ddlBackupDate.SelectedIndex = 0;
                }
            }
            catch { }
        }

        private void btnSetFactoryDefault_Click(object sender, EventArgs e)
        {
            if (MsgBox.WarningConfirm("Are you sure you want to set factory default?", MessageBoxButtons.YesNo) == DialogResult.No)
                return;
            //ServiceManager.Add<bool>(true);

            //File.Copy(Constance.BinaryDataFile, btnLibraryLocation.Text+"\\data.binary", true);
            //Config.CopyDir(Constance.SignImageDir, btnLibraryLocation.Text+"\\SignImage");
            //Config.CopyDir(Constance.LibraryDir, btnLibraryLocation.Text+"\\Library");
            //Config.CopyDir(Constance.LibraryUploadDir, btnLibraryLocation.Text+"\\Upload");
            //Config.CopyDir(Constance.DataPath + "\\log", btnLibraryLocation.Text+"\\log");

            //Config.CopyDir(Constance.DataPath, btnLibraryLocation.Text);

            DataGate.Provider.Path = Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.ApplicationData), "ProWrite"/* + VersionCode*/) + "\\";
            DataGate.Update();
            DataGate.Provider.FileName = "data.binary";
            ProjectInfo.Current.Clear();
            Application.Restart();
            //Config.AddOrUpdateAppSettings("", btnLibraryLocation.Text);
        }

        private void btnSetBackUpDefault_Click(object sender, EventArgs e)
        {
            if (MsgBox.WarningConfirm("Are you sure you want to set factory default?", MessageBoxButtons.YesNo) == DialogResult.No)
                return;

            string backPath = Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.ApplicationData), "ProWrite\\Backup");
            Config.AddOrUpdateAppSettings("BackupFilePath", backPath);
            btnEditBackupPath.Text = backPath;

            Config.AddOrUpdateAppSettings("AutoBackupFileDays","120");
            spnZhouQi.Value = 120;

            checkBox2.Checked = true;
            chkAutoDelete.Checked = true;

            spnAutoDelete.Value = 110;
            Config.AddOrUpdateAppSettings("AutoDeleteFileDays","110");
        }


    }
}
