using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Data.Common;
using System.Data;
using System.Diagnostics;
using System.Configuration;
using System.Windows.Forms;
using ProWrite.Core;

namespace ProWrite.UI.Controls
{
    public class LogService
    {
        static DbProviderFactory provider = null;
        static string ConnectionString;
        static string FormatConnectionString = "Data Source={0};Pooling=true;FailIfMissing=false";
        static string TempConnectionString;
        static string TempDBFile; 
        static LogService()
        {
            var providers = DbProviderFactories.GetFactoryClasses();
            ConnectionString = string.Format(FormatConnectionString, Constance.AppPath + "ServerLog.db");
            TempDBFile = Constance.AppPath + "TempLog.db";
            TempConnectionString = string.Format(FormatConnectionString, TempDBFile);

            foreach (DataRow item in providers.Rows)
            {
                if (item[0].ToString() == "SQLite Data Provider")
                {
                    provider = DbProviderFactories.GetFactory(item);
                    break;
                }
            }
        }


        public static void ImportTempData()
        {
            SaveLogs(InternalGetLogs(TempConnectionString, "select * from log"));
            IOHelper.RemoveFile(TempDBFile);
        }


        /// <summary>
        /// select
        /// </summary>
        /// <param name="sql"></param>
        /// <returns></returns>
        public static DataTable GetLogs(string sql)
        {
            return InternalGetLogs(ConnectionString, sql);
        }

        private static DataTable InternalGetLogs(string connectionString, string sql)
        {
            using (var conn = provider.CreateConnection())
            using (var cmd = conn.CreateCommand())
            using (var da = provider.CreateDataAdapter())
            {
                conn.ConnectionString = connectionString;
                cmd.CommandText = sql;
                da.SelectCommand = cmd;

                var tb = new DataTable();
                try
                {
                    conn.Open();
                    da.Fill(tb);
                }
                catch { }
                return tb;
            }
        }

        public static void SaveLogs(DataTable data)
        {
            using (var conn = provider.CreateConnection())
            using (var cmd = conn.CreateCommand())
            using (var da = provider.CreateDataAdapter())
            using(var builder = provider.CreateCommandBuilder())
            {
                conn.ConnectionString = ConnectionString;
                da.SelectCommand = cmd;
                cmd.CommandText = "select * from log";
                builder.DataAdapter = da;

                conn.Open();
                //da.InsertCommand = builder.GetInsertCommand();
                da.UpdateCommand = builder.GetUpdateCommand();
                using (var tx = conn.BeginTransaction())
                {
                    int did = da.Update(data);
                }
            }

           
        }
    }

}
