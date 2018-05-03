/*----------------------------------------------------------------
// 公司名称：公司名称
// 
// 项目名称：输入项目名称
//
// 创 建 人：zhangheng
// 创建日期：2015-2-5 20:21:11 
// 邮    箱：heng222_z@163.com
//
// Copyright (C) 公司名称 2009，保留所有权利
//
//----------------------------------------------------------------*/

using System;
using System.Collections.Generic;
using System.Text;

namespace Products.Domain.Utility
{
    /// <summary>
    /// 冗余DLL文件检查器
    /// </summary>
    public static class RedundantDllFileChecker
    {   
        /// <summary>
        /// 
        /// </summary>
        public static void Check()
        {
            var result = GetRepeatDllFiles(AppDomain.CurrentDomain.BaseDirectory);
            if (result.Count > 0)
            {
                var tip = new StringBuilder("检测到一个或多个冗余的Dll文件，请确认！\r\n", 128);
                
                foreach (var item in result)
                {
                    tip.AppendFormat("\r\n{0}\r\n", item.Key);

                    int index = 1;
                    foreach (var item1 in item.Value)
                    {
                        tip.AppendFormat("位置{0}：{1}\r\n", index++, item1);
                    }
                }

                throw new Exception(tip.ToString());
            }
        }
  
        /// <summary>
        /// 获取相同文件名且尺寸相等的DLL文件。
        /// </summary>
        /// <param name="path">搜索路径</param>
        /// <returns>以文件名为键，路径列表为值的字典</returns>
        public static IDictionary<string, IList<string>> GetRepeatDllFiles(string path)
        {
            var files = System.IO.Directory.GetFiles(path, @"*.dll", System.IO.SearchOption.AllDirectories);
            Dictionary<string, IList<string>> record = new Dictionary<string, IList<string>>();

            foreach (var item in files)
            {
                var key = System.IO.Path.GetFileName(item);
                if (!record.ContainsKey(key))
                {
                    record[key] = new List<string>();
                }

                record[key].Add(item);
            }

            // 获取文件名重复的文件
            bool done = true;

            do
            {
                done = true;
                foreach (var item in record)
                {
                    if (item.Value.Count == 1)
                    {
                        done = false;
                        record.Remove(item.Key);
                        break;
                    }
                }
            } while (!done);

            // 获取大小重复的文件
            do
            {
                done = true;
                foreach (var item in record)
                {
                    var dic = new Dictionary<long, IList<string>>();

                    foreach (var file in item.Value)
                    {
                        var fileInfo = new System.IO.FileInfo(file);

                        if (!dic.ContainsKey(fileInfo.Length))
                        {
                            dic[fileInfo.Length] = new List<string>();
                        }

                        dic[fileInfo.Length].Add(file);
                    }

                    bool isReapeat = false;
                    foreach (var file in dic)
                    {
                        if (file.Value.Count > 1)
                        {
                            isReapeat = true;
                            break;
                        }
                    }

                    if (!isReapeat)
                    {
                        done = false;
                        record.Remove(item.Key);
                        break;
                    }
                }
            } while (!done);

            return record;
        }

    }
}
