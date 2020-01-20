/*----------------------------------------------------------------
// 公司名称：请输入公司名称
// 
// 项目名称：输入项目名称
//
// 创 建 人：zhangheng
// 创建日期：2015-2-2 10:43:04 
// 邮    箱：heng222_z@163.com
//
// Copyright (C) 公司名称 2019，保留所有权利
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
    /// 裸UPD通信参数提供器。
    /// </summary>
    public class RawUdpConfigProvider : IRawUdpParamProvider
    {
        #region "Field"
        #endregion

        #region "Constructor"
        /// <summary>
        /// 构造函数
        /// </summary>
        /// <param name="cfgFilePath">配置文件的路径。</param>
        /// <param name="localIp">本地通信IP地址</param>
        public RawUdpConfigProvider(string cfgFilePath, IPAddress localIp)
        {
            this.RemoteEndPoints = new Dictionary<uint, IPEndPoint>();
            this.LocalEndPoint = new IPEndPoint(localIp, 0);

            this.Initialize(cfgFilePath);
        }
        #endregion

        #region "Properties"
        /// <summary>
        /// 获取本地终结点。
        /// </summary>
        public IPEndPoint LocalEndPoint { get; private set; }

        /// <summary>
        /// 获取对方终结点集合。
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
                throw new Exception(string.Format("指定的文件不存在！{0}", fileName));
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
        /// 根据 IPEndPoint 获取 对应的远程节点编号。
        /// </summary>
        /// <param name="endPoint">IP终结点。</param>
        /// <returns>远程节点编号。</returns>
        public uint GetRemoteCode(IPEndPoint endPoint)
        {
            return this.RemoteEndPoints.Where(p => p.Value.ToString() == endPoint.ToString())
                .Select(p => p.Key).FirstOrDefault();
        }
        #endregion

    }
}
