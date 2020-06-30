/*----------------------------------------------------------------
// 公司名称：请输入公司名称
// 
// 项目名称：输入项目名称
//
// 创 建 人：zhangheng
// 创建日期：2015-2-3 21:20:58 
// 邮    箱：zhangheng@163.com
//
// Copyright (C) 公司名称 2019，保留所有权利
//
//----------------------------------------------------------------*/

using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading;

using Products.Infrastructure.Entities;

namespace Products.Persistence
{
    static class HelperTools
    {
        public static readonly string CurrentDllPath;

        static HelperTools()
        {
            CurrentDllPath = Path.GetDirectoryName(Assembly.GetExecutingAssembly().Location);
        }

        /// <summary>
        /// 将逗号分割的表名转换为可枚举类型。
        /// </summary>
        public static IEnumerable<string> SplitTableNames(string tableNames)
        {
            return tableNames.Split(',').Where(p => !string.IsNullOrWhiteSpace(p))
                .Select(p => p.Replace("\t", "").Replace("\n", "").Trim()).Where(p => !string.IsNullOrWhiteSpace(p));
        }
        /// <summary>
        /// 修正URL中的文件路径。
        /// </summary>
        /// <param name="orginalValue">数据库配置URL，例如：Data Source=staticConfig.db;Journal Mode=WAL;</param>
        /// <returns>例如：Data Source=.\data\staticConfig.db;Journal Mode=WAL;</returns>
        public static string FixSQLiteDbUrl(string orginalValue)
        {
            var key = "Data Source";
            var items = orginalValue.Split(new string[] { ";", "；" }, StringSplitOptions.RemoveEmptyEntries);

            var dbFileName = Path.GetFileName(items.Where(p => p.Contains(key)).First()
                .Split(new string[] { "=" }, StringSplitOptions.RemoveEmptyEntries)[1]);

            var exePath = Thread.GetDomain().BaseDirectory;

            var allDbFiles = System.IO.Directory.GetFiles(exePath, dbFileName, System.IO.SearchOption.AllDirectories);
            if (allDbFiles.Count() != 1)
            {
                throw new Exception(string.Format("文件{0}的个数不为1。", dbFileName));
            }

            var sb = new StringBuilder(64);
            sb.AppendFormat("{0}={1};", key, allDbFiles.First());
            sb.Append(string.Join(";", items.Where(p => !p.Contains(key))));

            return sb.ToString();
        }

        /// <summary>
        /// 构建实体信息格式字符串。
        /// </summary>
        /// <returns>例如："Products.Infrastructure.{0},Products.Infrastructure"</returns>
        public static string BuildEntityFormat()
        {
            var entityType = typeof(Entity);
            var items = entityType.FullName.Split('.');
            var assemblyName = entityType.Assembly.FullName.Split(',').First();

            var sb = new StringBuilder(64);
            sb.Append(string.Join(".", items.Take(items.Length - 1)));
            sb.Append(".{0},");
            sb.Append(assemblyName);

            return sb.ToString();
        }
    }
}
