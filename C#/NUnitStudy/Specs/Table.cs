using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Collections.ObjectModel;
using NUnit.Framework;
using System.IO;

namespace NUnitStudy.Framework
{
    // 测试数据表
    public class Table:IEnumerable<Table.Row>
    {
        public ReadOnlyCollection<string> Columns { get; private set; }

        public ReadOnlyCollection<Row> Rows
        {
            get { return new ReadOnlyCollection<Row>(rows); }
        }

        public class Row:IEnumerable<string>
        {
            public ReadOnlyCollection<string> Columns { get; private set; }
            public ReadOnlyCollection<string> Values { get; private set; }

            public string this[string columnName]
            {
                get
                {
                    if (string.IsNullOrEmpty(columnName))
                        throw new ArgumentNullException("columnName");

                    var index = Columns.IndexOf(columnName);

                    if (index == -1)
                    {
                        throw new ArgumentException("列名:'"+ columnName + "'不存在!");
                    }

                    return Values[index];
                }
            }

            public string this[int columnIndex]
            {
                get
                {

                    if (columnIndex<0|| columnIndex >= Columns.Count)
                    {
                        throw new IndexOutOfRangeException();
                    }

                    return Values[columnIndex];
                }
            }

            internal Row(ReadOnlyCollection<string> columns, string[] values)
            {
                Columns = columns;
                Values = new ReadOnlyCollection<string>(values);
            }

            public override string ToString()
            {
                var sb = new StringBuilder(300);

                for (int i = 0; i < Columns.Count; i++)
                {
                    sb.AppendFormat("{0} = {1},", Columns[i], Values[i]);
                }

                sb.Length = sb.Length - 1;

                return sb.ToString();
            }

            public IEnumerator<string> GetEnumerator()
            {
                return Values.GetEnumerator();
            }

            System.Collections.IEnumerator System.Collections.IEnumerable.GetEnumerator()
            {
                return Values.GetEnumerator();
            }
        }

        public override string ToString()
        {
            return string.Join(Environment.NewLine, rows.Select(p => p.ToString()).ToArray());
        }

        private List<Row> rows;

        private Table(string[] columns)
        {
            Columns = new ReadOnlyCollection<string>(columns);
            rows = new List<Row>();
        }

        /// <summary>
        /// 解析单元测试数据的数据表
        /// </summary>
        /// <param name="file">数据文件</param>
        /// <param name="seporator">分隔符</param>
        /// <param name="commentPrefix">注释前缀标识符</param>
        /// <returns></returns>
        /// <exception cref="System.ArgumentNullException">当测试数据文件名时触发该异常</exception>
        /// <exception cref="System.FormatException">当文件内容为空、数据列为空、数据行为空以及定义的列数与实际数据行中的列数不匹配时触发该异常</exception>
        public static Table Parse(string file,char seporator ='|',string commentPrefix = "#" )
        {
            if (string.IsNullOrEmpty(file))
                throw new ArgumentNullException("file", "测试数据文件名不能为空！");

            var lines = File.ReadAllLines(file)
               .Where(p => !string.IsNullOrEmpty(p))
               .Where(p => !string.IsNullOrWhiteSpace(p))
               .Where(p => !p.StartsWith(commentPrefix))
               .ToArray();

            if (lines.Length == 0)
            {
                throw new FormatException("测试数据文件内容不能为空！");
            }

            var columns = lines[0].Trim().Split(seporator)
                    .Where(col => !string.IsNullOrEmpty(col))
                    .Select(col => col.Trim())
                    .ToArray();

            if (columns.Length == 0)
            {
                throw new FormatException("测试数据列不能为空！");
            }

            lines = lines.Skip(1).ToArray();

            var table = new Table(columns);

            foreach (var line in lines)
            {
                var values = line.Trim().Split(seporator)
                    .Where(col => !string.IsNullOrEmpty(col))
                    .Select(col => col.Trim())
                    .ToArray();

                if (values.Length == 0)
                {
                    throw new FormatException("测试数据行不能为空！");
                }

                if (values.Length != columns.Length)
                {
                    throw new FormatException(string.Format("定义的列数'{0}'与实际数据行'{1}'中的列数不匹配! 行数据：'{2}'" ,columns.Length,values.Length,line));
                }

                var row = new Table.Row(table.Columns, values);

                table.rows.Add(row);
            }

            return table;
        }

        public IEnumerator<Table.Row> GetEnumerator()
        {
            return rows.GetEnumerator();
        }

        System.Collections.IEnumerator System.Collections.IEnumerable.GetEnumerator()
        {
            return rows.GetEnumerator();
        }
    }
}
