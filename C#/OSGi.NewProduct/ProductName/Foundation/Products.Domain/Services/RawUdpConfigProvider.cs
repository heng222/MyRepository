/*----------------------------------------------------------------
// ��˾���ƣ������빫˾����
// 
// ��Ŀ���ƣ�������Ŀ����
//
// �� �� �ˣ�zhangheng
// �������ڣ�2015-2-2 10:43:04 
// ��    �䣺heng222_z@163.com
//
// Copyright (C) ��˾���� 2019����������Ȩ��
//
//----------------------------------------------------------------*/

using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Net;
using System.Reflection;
using Acl.IO;
using Products.Domain.Preferences;
using Products.Infrastructure.Specification;

namespace Products.Domain.Services
{
    /// <summary>
    /// ��UPDͨ�Ų����ṩ����
    /// </summary>
    public class RawUdpConfigProvider : IRawUdpParamProvider
    {
        #region "Field"
        #endregion

        #region "Constructor"
        /// <summary>
        /// ���캯��
        /// </summary>
        /// <param name="cfgFilePath">�����ļ���·����</param>
        /// <param name="localIp">����ͨ��IP��ַ</param>
        public RawUdpConfigProvider(string cfgFilePath, IPAddress localIp)
        {
            this.RemoteEndPoints = new Dictionary<uint, IPEndPoint>();
            this.LocalEndPoint = new IPEndPoint(localIp, 0);

            this.Initialize(cfgFilePath);
        }
        #endregion

        #region "Properties"
        /// <summary>
        /// ��ȡ�����ս�㡣
        /// </summary>
        public IPEndPoint LocalEndPoint { get; private set; }

        /// <summary>
        /// ��ȡ�Է��ս�㼯�ϡ�
        /// </summary>
        public Dictionary<uint, IPEndPoint> RemoteEndPoints { get; private set; }

        #endregion

        #region "Override methods"
        #endregion

        #region "Private methods"

        private void Initialize(string fileName)
        {
            if (!File.Exists(fileName))
            {
                throw new Exception(string.Format("ָ�����ļ������ڣ�{0}", fileName));
            }

            var iniFile = new WinIniFile(fileName);

            // Parse Local Port.
            var value = iniFile.ReadValue("Local", "Port");
            this.LocalEndPoint.Port = (int)SettingsParser.ParseDecimal(value);

            //
            var index = 1;
            while (index <= 100)
            {
                var section = string.Format("Remote{0}", index++);
                var keys = iniFile.ReadValue(section, null);
                if (string.IsNullOrEmpty(keys)) continue;

                var remoteId = (ushort)SettingsParser.ParseDecimal(iniFile.ReadValue(section, "ID"));
                var endPoint = SettingsParser.ParseIPEndPoint(iniFile.ReadValue(section, "IPEndPoint"));

                this.RemoteEndPoints.Add(remoteId, endPoint);
            }
        }
        #endregion

        #region "Public methods"
        /// <summary>
        /// ���� IPEndPoint ��ȡ ��Ӧ��Զ�̽ڵ��š�
        /// </summary>
        /// <param name="endPoint">IP�ս�㡣</param>
        /// <returns>Զ�̽ڵ��š�</returns>
        public uint GetRemoteCode(IPEndPoint endPoint)
        {
            return this.RemoteEndPoints.Where(p => p.Value.ToString() == endPoint.ToString())
                .Select(p => p.Key).FirstOrDefault();
        }
        #endregion

    }
}
