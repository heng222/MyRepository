/*----------------------------------------------------------------
// 公司名称：请输入公司名称
// 
// 项目名称：输入项目名称
//
// 创 建 人：zhangheng
// 创建日期：2015-2-5 20:31:18 
// 邮    箱：heng222_z@163.com
//
// Copyright (C) 公司名称 2019，保留所有权利
//
//----------------------------------------------------------------*/

using System;
using System.IO;
using System.Reflection;

namespace Products.Domain.Utility
{
    /// <summary>
    /// 系统检查器
    /// </summary>
    public sealed class SystemChecker : IDisposable
    {
        private bool _disposed = false;

        private SingletonProcessChecker _singletonChecker;

        /// <summary>
        /// 构造函数
        /// </summary>
        public SystemChecker()
        {

        }

        /// <summary>
        /// 终结函数
        /// </summary>
        ~SystemChecker()
        {
            this.Dispose(false);
        }

        private void Dispose(bool disposing)
        {
            if (!_disposed)
            {
                if (disposing)
                {
                    if (_singletonChecker != null)
                    {
                        _singletonChecker.Dispose();
                        _singletonChecker = null;
                    }
                }

                _disposed = true;
            }
        }

        /// <summary>
        /// 
        /// </summary>
        public void Dispose()
        {
            this.Dispose(true);
            GC.SuppressFinalize(this);
        }

        /// <summary>
        /// 检查系统的配置正确性
        /// </summary>
        public void Check()
        {
            var exeFullPathName = Assembly.GetEntryAssembly().Location;

            // 禁止从网络路径启动。
            if (!this.IsLocalDriver(exeFullPathName)) throw new Exception("禁止从网络路径启动程序！");

            // 单实例检查
            _singletonChecker = new SingletonProcessChecker(exeFullPathName.Replace('\\', '_'));
            if (!_singletonChecker.IsPassed) throw new Exception("程序的一个实例已经在运行。");

            // 冗余DLL文件检查
            RedundantDllFileChecker.Check();
        }

        /// <summary>
        /// 指定的路径是否为本地路径。
        /// </summary>
        private bool IsLocalDriver(string path)
        {
            try
            {
                var di = new DriveInfo(path);
                return di.DriveType != DriveType.Network;
            }
            catch (System.Exception /*ex*/)
            {
                return false;
            }
        }
    }
}
