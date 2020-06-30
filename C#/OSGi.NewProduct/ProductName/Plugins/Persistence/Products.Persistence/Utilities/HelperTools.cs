/*----------------------------------------------------------------
// ��˾���ƣ������빫˾����
// 
// ��Ŀ���ƣ�������Ŀ����
//
// �� �� �ˣ�zhangheng
// �������ڣ�2015-2-3 21:20:58 
// ��    �䣺zhangheng@163.com
//
// Copyright (C) ��˾���� 2019����������Ȩ��
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
        /// �����ŷָ�ı���ת��Ϊ��ö�����͡�
        /// </summary>
        public static IEnumerable<string> SplitTableNames(string tableNames)
        {
            return tableNames.Split(',').Where(p => !string.IsNullOrWhiteSpace(p))
                .Select(p => p.Replace("\t", "").Replace("\n", "").Trim()).Where(p => !string.IsNullOrWhiteSpace(p));
        }
        /// <summary>
        /// ����URL�е��ļ�·����
        /// </summary>
        /// <param name="orginalValue">���ݿ�����URL�����磺Data Source=staticConfig.db;Journal Mode=WAL;</param>
        /// <returns>���磺Data Source=.\data\staticConfig.db;Journal Mode=WAL;</returns>
        public static string FixSQLiteDbUrl(string orginalValue)
        {
            var key = "Data Source";
            var items = orginalValue.Split(new string[] { ";", "��" }, StringSplitOptions.RemoveEmptyEntries);

            var dbFileName = Path.GetFileName(items.Where(p => p.Contains(key)).First()
                .Split(new string[] { "=" }, StringSplitOptions.RemoveEmptyEntries)[1]);

            var exePath = Thread.GetDomain().BaseDirectory;

            var allDbFiles = System.IO.Directory.GetFiles(exePath, dbFileName, System.IO.SearchOption.AllDirectories);
            if (allDbFiles.Count() != 1)
            {
                throw new Exception(string.Format("�ļ�{0}�ĸ�����Ϊ1��", dbFileName));
            }

            var sb = new StringBuilder(64);
            sb.AppendFormat("{0}={1};", key, allDbFiles.First());
            sb.Append(string.Join(";", items.Where(p => !p.Contains(key))));

            return sb.ToString();
        }

        /// <summary>
        /// ����ʵ����Ϣ��ʽ�ַ�����
        /// </summary>
        /// <returns>���磺"Products.Infrastructure.{0},Products.Infrastructure"</returns>
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
