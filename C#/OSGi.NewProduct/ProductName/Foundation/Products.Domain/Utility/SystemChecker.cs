/*----------------------------------------------------------------
// ��˾���ƣ������빫˾����
// 
// ��Ŀ���ƣ�������Ŀ����
//
// �� �� �ˣ�zhangheng
// �������ڣ�2015-2-5 20:31:18 
// ��    �䣺heng222_z@163.com
//
// Copyright (C) ��˾���� 2019����������Ȩ��
//
//----------------------------------------------------------------*/

using System;
using System.IO;
using System.Reflection;

namespace Products.Domain.Utility
{
    /// <summary>
    /// ϵͳ�����
    /// </summary>
    public sealed class SystemChecker : IDisposable
    {
        private bool _disposed = false;

        private SingletonProcessChecker _singletonChecker;

        /// <summary>
        /// ���캯��
        /// </summary>
        public SystemChecker()
        {

        }

        /// <summary>
        /// �սắ��
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
        /// ���ϵͳ��������ȷ��
        /// </summary>
        public void Check()
        {
            var exeFullPathName = Assembly.GetEntryAssembly().Location;

            // ��ֹ������·��������
            if (!this.IsLocalDriver(exeFullPathName)) throw new Exception("��ֹ������·����������");

            // ��ʵ�����
            _singletonChecker = new SingletonProcessChecker(exeFullPathName.Replace('\\', '_'));
            if (!_singletonChecker.IsPassed) throw new Exception("�����һ��ʵ���Ѿ������С�");

            // ����DLL�ļ����
            RedundantDllFileChecker.Check();
        }

        /// <summary>
        /// ָ����·���Ƿ�Ϊ����·����
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
