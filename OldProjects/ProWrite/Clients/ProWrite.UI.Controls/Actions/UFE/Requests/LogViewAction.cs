using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ProWrite.UI.Controls.Dashboard;
using ProWrite.Entity.Dashboard;
using ProWrite.Core;
using ProWrite.UFE;
using ProWrite.UI.Controls.Common;
using System.Data;
using ProWrite.UFE.Entity;
using System.Reflection;
using Microsoft.Win32;
using System.Diagnostics;
using System.IO;
using System.IO.Compression;
using System.Runtime.Serialization.Formatters.Binary;
using System.Collections;
using System.Runtime.Serialization;

namespace ProWrite.UI.Controls.Actions.UFE.Requests
{
    class LogViewAction : RequestActionBase
    {
        public SignInfo sign
        {
            get;
            set;
        }
        List<LogInfo> list;
        public override void Perform()
        {
            if (sign.Controller.Connection.State != System.Communication.ConnectionState.Opened)
                return;
            LogViewGet logview = new LogViewGet();
            logview.Mode = 0;
            logview.Type = 0;
            DataTable tempTable = LogService.GetLogs("select date from log order by date desc");

            bool isDownLoad = false;
            logview.DateTime = "10020101120000";
            if (tempTable.Rows.Count > 0)
                logview.DateTime = tempTable.Rows[0][0].ToString();
            else
            {
                isDownLoad = true;
                logview.Mode = 2;
            }
            logview.SQL = "";
            isDownLoad = true;

            sign.Controller.SendAsync(
                Commands.GetLog,
                p =>
                {
                    //Cursor = Cursors.Default;
                    if (p.IsSuccessed)
                    {
                        string toFilePath = Constance.AppPath + "UFEQueryResult.gz";// Environment.GetFolderPath(Environment.SpecialFolder.ApplicationData) + "\\ProWrite\\Library\\";

                        if (!isDownLoad)
                        {
                            if (p.Packet.Download.ToString() == "0")
                            {
                                JsonSerializer serializer = new JsonSerializer();

                                list = serializer.ConvertToType<List<LogInfo>>(p.Packet.Content);

                                if (list != null && list.Count > 0)
                                {
                                    DataTable table = convert2Table<LogInfo>(list);

                                    LogService.SaveLogs(table);
                                }
                            }
                            else
                            {
                                string fromFilePath = "/mnt/sdcard/.ufe/data/logs/UFEQueryResult.gz";

                                sign.Controller.Connection.FtpManager.DownLoad(fromFilePath, toFilePath);
                                FileRar.UnCompressRAR("UFEQueryResult.gz");
                                LogService.ImportTempData();
                            }
                        }
                        else
                        {
                            string fromFilePath = "/mnt/sdcard/.ufe/data/logs/sqlite.gz";
                            toFilePath = Constance.AppPath + "sqlite.gz";
                            sign.Controller.Connection.FtpManager.DownLoad(fromFilePath, toFilePath);
                            FileRar.UnCompressRAR("sqlite.gz");
                            LogService.ImportTempData();
                        }
                    }
                    else
                    {
                        
                    }
                },
                logview);
        }

        public static DataTable convert2Table<T>(List<T> list)
        {

            DataTable table = new DataTable();


            if (list.Count > 0)
            {


                PropertyInfo[] properties = list[0].GetType().GetProperties();

                List<string> columns = new List<string>();


                foreach (PropertyInfo pi in properties)
                {

                    table.Columns.Add(pi.Name);

                    columns.Add(pi.Name);

                }


                foreach (T item in list)
                {

                    object[] cells = getValues(columns, item);

                    table.Rows.Add(cells);

                }

            }


            return table;

        }


        private static object[] getValues(List<string> columns, object instance)
        {

            object[] ret = new object[columns.Count];


            for (int n = 0; n < ret.Length; n++)
            {

                PropertyInfo pi = instance.GetType().GetProperty(columns[n]);

                object value = pi.GetValue(instance, null);

                ret[n] = value;

            }


            return ret;

        }

    }

    public class FileRar
    {

        public static void UnCompressRAR(string fileName)
        {
            string FilePath = Constance.AppPath + fileName;
            string TargetPath = Constance.AppPath + "TempLog.db";
            if(fileName == "sqlite.gz")
                TargetPath = Constance.AppPath + "ServerLog.db";
            IOHelper.RemoveFile(TargetPath);
            using (Stream source = File.OpenRead(FilePath))
            using (var destination = new FileStream(TargetPath, FileMode.CreateNew))
            using (GZipStream input = new GZipStream(source, CompressionMode.Decompress, true))
            {
                byte[] bytes = new byte[4096];
                int n;
                while ((n = input.Read(bytes, 0, bytes.Length)) != 0)
                {
                    destination.Write(bytes, 0, n);
                }

                destination.Flush();
                destination.Position = 0;
            }

            IOHelper.RemoveFile(FilePath);
        }
    }
  

}
