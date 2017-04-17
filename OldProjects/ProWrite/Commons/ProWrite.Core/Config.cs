using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Configuration;
using System.Communication;
using System.IO;

namespace ProWrite.Core
{
    public class Config
    {
        private static Helper helper = new Helper();

        public static void AddOrUpdateAppSettings(string key, string value)
        {
            helper.AddOrUpdateSettings(key, value);
        }
        public static string GetAppSettingValueBytKey(string key)
        {
            return helper.GetAppSettingValueBytKey(key);
        }
        public static void CopyDir(string srcPath, string aimPath)
        {
            try
            {
                // 检查目标目录是否以目录分割字符结束如果不是则添加之 
                if (aimPath[aimPath.Length - 1] != System.IO.Path.DirectorySeparatorChar)
                {
                    aimPath += System.IO.Path.DirectorySeparatorChar;
                }

                // 判断目标目录是否存在如果不存在则新建之 
                if (!System.IO.Directory.Exists(aimPath))
                {
                    System.IO.Directory.CreateDirectory(aimPath);
                }

                // 得到源目录的文件列表，该里面是包含文件以及目录路径的一个数组 
                // 如果你指向copy目标文件下面的文件而不包含目录请使用下面的方法 
                // string[] fileList = Directory.GetFiles(srcPath); 
                string[] fileList = System.IO.Directory.GetFileSystemEntries(srcPath);

                // 遍历所有的文件和目录 
                foreach (string file in fileList)
                {
                    // 先当作目录处理如果存在这个目录就递归Copy该目录下面的文件 
                    if (System.IO.Directory.Exists(file))
                    {
                        CopyDir(file, aimPath + System.IO.Path.GetFileName(file));
                    }

                    // 否则直接Copy文件 
                    else
                    {
                        System.IO.File.Copy(file, aimPath + System.IO.Path.GetFileName(file), true);
                    }
                }
            }

            catch (Exception e)
            {

            }
        }

        public static void DeleteFolder(string dir)
         {
             foreach (string d in Directory.GetFileSystemEntries(dir))
             {
                 if (File.Exists(d))
                 {
                     FileInfo fi = new FileInfo(d);
                     if (fi.Attributes.ToString().IndexOf("ReadOnly") != -1)
                         fi.Attributes = FileAttributes.Normal;
                     File.Delete(d);//直接删除其中的文件   
                 }
                 else
                     DeleteFolder(d);//递归删除子文件夹   
             }
             Directory.Delete(dir);//删除已空文件夹   
         }  

        private class Helper
        {
            private Configuration config = null;
            private KeyValueConfigurationCollection settings;
            public Helper()
            {
                config = ConfigurationManager.OpenExeConfiguration(ConfigurationUserLevel.None);
                settings = config.AppSettings.Settings;
            }

            public void AddOrUpdateSettings(string key,string value)
            {
                if (string.IsNullOrEmpty(key))
                    return;

                try
                {
                    if (settings.AllKeys.Contains(key))
                        settings.Remove(key);
                    settings.Add(key, value);
                    //settings[""].
                    config.Save();
                }
                catch (Exception ex)
                {
                    Log.Error(ex.Message, ex);
                }
            }
            public string GetAppSettingValueBytKey(string key)
            {
                if (settings[key] != null)
                    return settings[key].Value;
                else
                    return "";
            }
        }
    }
}
