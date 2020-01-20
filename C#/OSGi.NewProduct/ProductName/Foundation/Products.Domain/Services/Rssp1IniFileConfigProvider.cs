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
using Acl.RsspI4net.Config;
using Products.Domain.Preferences;
using Products.Infrastructure.Specification;

namespace Products.Domain.Services
{
    /// <summary>
    /// 基于INI文件的Rssp1通信参数提供者。
    /// </summary>
    public class Rssp1IniFileConfigProvider : IRssp1ParamProvider
    {
        #region "Field"
        private WinIniFile _iniFile;
        #endregion

        #region "Constructor"

        /// <summary>
        /// 带参数的构造函数。
        /// </summary>
        /// <param name="filePathName">配置文件名称</param>
        /// <param name="isMachineA">是否A机？</param>
        /// <param name="redIP">本地红网IP</param>
        /// <param name="blueIP">本地蓝网IP</param>
        public Rssp1IniFileConfigProvider(string filePathName, bool isMachineA, IPAddress redIP, IPAddress blueIP)
        {
            this.IsMachineA = isMachineA;
            this.LocalRedIP = redIP;
            this.LocalBlueIP = blueIP;
            
            this.CreateIniFile(filePathName);

            this.BuildSessionParam();
        }

        #endregion

        #region "Properties"
        /// <summary>
        /// 本节点是否是A机？
        /// </summary>
        public bool IsMachineA { get; private set; }

        /// <summary>
        /// 获取本地工作周期（毫秒）。
        /// </summary>
        public int WorkPeriod { get; private set; }
        
        /// <summary>
        /// 获取本地红网IP
        /// </summary>
        public IPAddress LocalRedIP { get; private set; }
        /// <summary>
        /// 获取本地蓝网IP
        /// </summary>
        public IPAddress LocalBlueIP { get; private set; }
        
        /// <summary>
        /// 获取RSSP-1本地工作参数。
        /// </summary>
        public WorkParameters LocalWorkParameter { get; private set; }
        /// <summary>
        /// 获取本地安全参数
        /// </summary>
        public SafetyParameters LocalSafetyParam { get; private set; }
        /// <summary>
        /// 获取会话参数。
        /// </summary>
        public IEnumerable<Tuple<IEnumerable<UdpParameters>, SessionConfig>> SessionParam { get; private set; }

        #endregion

        #region "Override methods"
        #endregion

        #region "Private methods"
        private void CreateIniFile(string filePathName)
        {
            if (!File.Exists(filePathName)) throw new Exception(string.Format("指定的文件不存在！{0}", filePathName));

            _iniFile = new WinIniFile(filePathName);
        }
                
        private void BuildLocalWorkParameter()
        {
            this.WorkPeriod = (int)SettingsParser.ParseDecimal(_iniFile.ReadValue("Local", "WorkPeriod"));

            this.LocalWorkParameter = new WorkParameters();
            this.LocalWorkParameter.IndexError = (uint)SettingsParser.ParseDecimal(_iniFile.ReadValue("Local", "IndexError"));
            this.LocalWorkParameter.MaxUserDataLen = (uint)SettingsParser.ParseDecimal(_iniFile.ReadValue("Local", "MaxUserDataLen"));
            this.LocalWorkParameter.TimeoutCycle = (uint)SettingsParser.ParseDecimal(_iniFile.ReadValue("Local", "TimeoutCycle"));
        }

        private void BuildLocalSafetyParameter()
        {
            this.LocalSafetyParam = new SafetyParameters();

            // address
            //var localAddrs = SettingsParser.ParseDictionary(_iniFile.ReadValue("Local", "Address"), new String[] { ",", "，" }, new string[] { "=>" });
            //if (localAddrs.Count < 2) throw new Exception(string.Format("Local.Address个数不能小于2。"));
            //this.LocalSafetyParam.Addr = (ushort)localAddrs[this.LocalCodeInAts];
            this.LocalSafetyParam.Addr = (ushort)SettingsParser.ParseDecimal(_iniFile.ReadValue("Local", "Address"));
            var sid = SettingsParser.ParseDecimals(_iniFile.ReadValue("Local", "SID"), new string[] { ",", "，" });
            if (sid.Count < 2) throw new Exception(string.Format("Local.SID个数不能小于2。"));
            this.LocalSafetyParam.SID = sid.Select(p => (uint)p).ToArray();

            // SINIT
            var sinit = SettingsParser.ParseDecimals(_iniFile.ReadValue("Local", "SINIT"), new string[] { ",", "，" });
            if (sinit.Count < 2) throw new Exception(string.Format("Local.SINIT个数不能小于2。"));
            this.LocalSafetyParam.SINIT = sinit.Select(p => (uint)p).ToArray();

            // DataVersion
            var dataVer = SettingsParser.ParseDecimals(_iniFile.ReadValue("Local", "DATAVER"), new string[] { ",", "，" });
            if (dataVer.Count < 2) throw new Exception(string.Format("Local.DATAVER个数不能小于2。"));
            this.LocalSafetyParam.DATAVER = dataVer.Select(p => (uint)p).ToArray();
        }

        private List<UdpParameters> CreateUdpParameters(int localRedPort, int localBluePort, 
                                                                    IPEndPoint remoteRedEndPoint, IPEndPoint remoteBlueEndPoint)
        {
            var result = new List<UdpParameters>();

            if (this.LocalRedIP != null && remoteRedEndPoint != null)
            {
                var item = new UdpParameters(new IPEndPoint(this.LocalRedIP, localRedPort), remoteRedEndPoint);
                result.Add(item);
            }

            if (this.LocalBlueIP != null && remoteBlueEndPoint != null)
            {
                var item = new UdpParameters(new IPEndPoint(this.LocalBlueIP, localBluePort), remoteBlueEndPoint);
                result.Add(item);
            }

            return result;
        }

        private SafetyParameters CreateRemoteSafetyParameters(string section)
        {
            var remoteSafetyParam = new SafetyParameters();
            // Address
            remoteSafetyParam.Addr = (ushort)SettingsParser.ParseDecimal(_iniFile.ReadValue(section, "Address"));
            // SID
            var sid = SettingsParser.ParseDecimals(_iniFile.ReadValue(section, "SID"), new string[] { ",", "，" });
            if (sid.Count < 2) throw new Exception(string.Format("{0}.SID个数不能小于2。", section));
            remoteSafetyParam.SID = sid.Select(p => (uint)p).ToArray();
            // SINIT
            var sinit = SettingsParser.ParseDecimals(_iniFile.ReadValue(section, "SINIT"), new string[] { ",", "，" });
            if (sinit.Count < 2) throw new Exception(string.Format("{0}.SINIT个数不能小于2。", section));
            remoteSafetyParam.SINIT = sinit.Select(p => (uint)p).ToArray();
            // DataVersion
            var dataVer = SettingsParser.ParseDecimals(_iniFile.ReadValue(section, "DATAVER"), new string[] { ",", "，" });
            if (dataVer.Count < 2) throw new Exception(string.Format("{0}.DATAVER个数不能小于2。", section));
            remoteSafetyParam.DATAVER = dataVer.Select(p => (uint)p).ToArray();

            return remoteSafetyParam;
        }

        private void BuildSessionParam()
        {
            this.BuildLocalWorkParameter();

            this.BuildLocalSafetyParameter();

            var result = new List<Tuple<IEnumerable<UdpParameters>, SessionConfig>>();

            var index = 1;
            while (index <= 1000)
            {
                var section = string.Format("Remote{0}", index++);
                var keys = _iniFile.ReadValue(section, null);
                if (string.IsNullOrEmpty(keys)) continue;

                // Read CustomNodeCode。
                var customNodeCode = (ushort)SettingsParser.ParseDecimal(_iniFile.ReadValue(section, "CustomNodeCode"));

                // LoalPort
                var ports = _iniFile.ReadValue(section, "LocalPort").Trim().Split(new string[] { ",", "，" }, StringSplitOptions.RemoveEmptyEntries).ToList();
                if (ports.Count < 1) throw new Exception(string.Format("{0}.LocalPort个数不能小于1。", section));
                int localRedPort = 0, localBluePort = 0;
                localRedPort = (int)SettingsParser.ParseDecimal(ports[0]);
                localBluePort = ports.Count < 2 ? localRedPort : (int)SettingsParser.ParseDecimal(ports[1]);

                // Create Remote EndPoint
                var remoteEP = SettingsParser.ParseIPEndPoints(_iniFile.ReadValue(section, "RemoteEndPoints"), new string[] { ",", "，" });
                if (remoteEP.Count < 2) throw new Exception(string.Format("{0}.RemoteEndPoints个数不能小于2。", section));

                // Create UdpParam.
                var udpParam = this.CreateUdpParameters(localRedPort, localBluePort, remoteEP[0], remoteEP[1]);

                // Create Remote SafetyParamters
                var remoteSafetyParam = this.CreateRemoteSafetyParameters(section);

                // 
                var sessionCfg = new SessionConfig(this.LocalWorkParameter, this.LocalSafetyParam, remoteSafetyParam, customNodeCode);
                var sessionParam = new Tuple<IEnumerable<UdpParameters>, SessionConfig>(udpParam, sessionCfg);
                result.Add(sessionParam);
            };

            this.SessionParam = result;
        }
        #endregion

        #region "Public methods"

        /// <summary>
        /// 根据 指定的地址 查找 对应的ID。
        /// </summary>
        /// <param name="address">例如：0x1E01</param>
        /// <returns>例如：0x9201, 0x9202</returns>
        public List<uint> FindRemoteCode(ushort address)
        {
            return this.SessionParam.Where(p => p.Item2.RemoteParam.Addr == address)
                .Select(p => p.Item2.CustomRemoteCode).ToList();
        }

        /// <summary>
        /// 根据节点的自定义编号查找对应的RSSP-I地址。
        /// </summary>
        /// <param name="customCode">自定义编号，例如：0x9201, 0x9202。</param>
        /// <returns>自定义编号对应的地址。例如：0x1E01。</returns>
        public ushort FindAddress(uint customCode)
        {
            return this.SessionParam.Where(p => p.Item2.CustomRemoteCode == customCode)
                .Select(p => p.Item2.RemoteParam.Addr).FirstOrDefault();
        }

        #endregion
    }
}
