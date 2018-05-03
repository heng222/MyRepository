/*----------------------------------------------------------------
// ��˾���ƣ���˾����
// 
// ��Ŀ���ƣ�������Ŀ����
//
// �� �� �ˣ�zhangheng
// �������ڣ�2015-2-5 20:21:11 
// ��    �䣺heng222_z@163.com
//
// Copyright (C) ��˾���� 2009����������Ȩ��
//
//----------------------------------------------------------------*/

using System;
using System.Collections.Generic;
using System.Text;

namespace Products.Domain.Utility
{
    /// <summary>
    /// ����DLL�ļ������
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
                var tip = new StringBuilder("��⵽һ�����������Dll�ļ�����ȷ�ϣ�\r\n", 128);
                
                foreach (var item in result)
                {
                    tip.AppendFormat("\r\n{0}\r\n", item.Key);

                    int index = 1;
                    foreach (var item1 in item.Value)
                    {
                        tip.AppendFormat("λ��{0}��{1}\r\n", index++, item1);
                    }
                }

                throw new Exception(tip.ToString());
            }
        }
  
        /// <summary>
        /// ��ȡ��ͬ�ļ����ҳߴ���ȵ�DLL�ļ���
        /// </summary>
        /// <param name="path">����·��</param>
        /// <returns>���ļ���Ϊ����·���б�Ϊֵ���ֵ�</returns>
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

            // ��ȡ�ļ����ظ����ļ�
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

            // ��ȡ��С�ظ����ļ�
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
