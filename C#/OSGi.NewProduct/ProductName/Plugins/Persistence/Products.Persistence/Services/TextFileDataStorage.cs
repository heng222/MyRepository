/*----------------------------------------------------------------
// 公司名称：请输入公司名称
// 
// 项目名称：输入项目名称
//
// 创 建 人：zhangheng
// 创建日期：2015-2-3 21:20:58 
// 邮    箱：zhangheng@163.com
//
// Copyright (C) 公司名称 2009，保留所有权利
//
//----------------------------------------------------------------*/

using System;
using System.Collections;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Linq.Expressions;
using System.Reflection;
using System.Text;
using Products.Domain.Preferences;
using Products.Infrastructure.Entities;

namespace Products.Persistence.Implementation
{
    /// <summary>
    /// 基于文本文件的数据存储。
    /// </summary>
    class TextFileDataStorage
    {
        #region "Field"
        private List<IoDriverPoint> _ioDriverPoints = new List<IoDriverPoint>();
        private List<IoCollectionPoint> _ioCollectionPoints = new List<IoCollectionPoint>();

        private Dictionary<string, IQueryable> _mapping = new Dictionary<string, IQueryable>();
        #endregion

        #region "Constructor"
        public TextFileDataStorage()
        {
            this.ReadTextFiles();

            this.InitMapping();
        }
        #endregion

        #region "Properties"
        #endregion

        #region "Override methods"
        #endregion

        #region "Private methods"
        private void InitMapping()
        {
            _mapping[typeof(IoDriverPoint).FullName] = _ioDriverPoints.AsQueryable();
            _mapping[typeof(IoCollectionPoint).FullName] = _ioDriverPoints.AsQueryable();
        }

        private void ReadTextFiles()
        {
            var filePath = string.Format(@"{0}\Data\Text", System.IO.Path.GetDirectoryName(Assembly.GetExecutingAssembly().Location));

            var fileName = string.Format(@"{0}\DriverPoints.ini", filePath);
            this.ReadIoDriverPoints(fileName);

            fileName = string.Format(@"{0}\CollectionPoints.ini", filePath);
            this.ReadIoCollectionPoints(fileName);
        }

        private void ReadIoDriverPoints(string fileName)
        {
            using (var sr = new StreamReader(fileName, Encoding.Unicode))
            {
                try
                {
                    while (!sr.EndOfStream)
                    {
                        string textLine = sr.ReadLine().Trim();
                        if (textLine.Length > 1 && !IsComment(textLine))
                        {
                            var items = textLine.Split(new char[] { ',', '，', ' ', '\t', ';', '#' }, StringSplitOptions.RemoveEmptyEntries);

                            if (items.Length >= 7)
                            {
                                var index = 0;

                                var record = new IoDriverPoint();

                                record.Code = (ushort)(SettingsParser.ParseDecimal(items[index++]));
                                record.Name = items[index++];
                                record.CardIndex = (ushort)(SettingsParser.ParseDecimal(items[index++]));
                                record.PointIndex = (ushort)(SettingsParser.ParseDecimal(items[index++]));

                                // DeviceType 为 道岔，需要转换为 整型。
                                //record.DeviceType = (ushort)(SettingsParser.ParseDecimal(items[index++]));
                                index++;

                                record.CiStationCode = (ushort)(SettingsParser.ParseDecimal(items[index++]));
                                record.DeviceCode = (ushort)(SettingsParser.ParseDecimal(items[index++]));

                                _ioDriverPoints.Add(record);
                            }
                            else
                            {
                                throw new Exception(string.Format("元素个数小于规定的值。"));
                            }
                        }
                    }
                }
                catch (System.Exception ex)
                {
                    throw new Exception(String.Format("读取文件{0}时发生异常， {1}", fileName, ex.Message), ex);
                }
            }
        }

        private void ReadIoCollectionPoints(string fileName)
        {
            using (var sr = new StreamReader(fileName, Encoding.Unicode))
            {
                try
                {
                    while (!sr.EndOfStream)
                    {
                        string textLine = sr.ReadLine().Trim();
                        if (textLine.Length > 1 && !IsComment(textLine))
                        {
                            var items = textLine.Split(new char[] { ',', '，', ' ', '\t', ';', '#' }, StringSplitOptions.RemoveEmptyEntries);

                            if (items.Length >= 7)
                            {
                                var index = 0;

                                var record = new IoCollectionPoint();

                                record.Code = (ushort)(SettingsParser.ParseDecimal(items[index++]));
                                record.Name = items[index++];
                                record.CardIndex = (ushort)(SettingsParser.ParseDecimal(items[index++]));
                                record.PointIndex = (ushort)(SettingsParser.ParseDecimal(items[index++]));

                                // DeviceType 为 道岔，需要转换为 整型。
                                //record.DeviceType = (ushort)(SettingsParser.ParseDecimal(items[index++]));
                                index++;

                                record.CiStationCode = (ushort)(SettingsParser.ParseDecimal(items[index++]));
                                record.DeviceCode = (ushort)(SettingsParser.ParseDecimal(items[index++]));

                                _ioCollectionPoints.Add(record);
                            }
                            else
                            {
                                throw new Exception(string.Format("元素个数小于规定的值。"));
                            }
                        }
                    }
                }
                catch (System.Exception ex)
                {
                    throw new Exception(String.Format("读取文件{0}时发生异常， {1}", fileName, ex.Message), ex);
                }
            }
        }

        private bool IsComment(string textLine)
        {
            if (string.IsNullOrWhiteSpace(textLine))
            {
                return true;
            }

            return (textLine[0] == '#') || (textLine[0] == ';') || (textLine[0] == '/');
        }
        #endregion

        #region IRepository 成员

        public IList<T> Where<T>(Expression<Func<T, bool>> predicate = null) where T : Entity
        {
            var typeT = typeof(T);
            IQueryable theList = null;

            var flag = _mapping.TryGetValue(typeT.FullName, out theList);
            if (!flag) return new List<T>();

            // 
            if (predicate == null)
            {
                return (theList as IQueryable<T>).Where(p => p != null).ToList();
            }
            else
            {
                return (theList as IQueryable<T>).Where(predicate).ToList();
                //return theList.OfType<T>().AsQueryable<T>().Where(predicate).ToList();
            }
        }
        #endregion
    }
}
