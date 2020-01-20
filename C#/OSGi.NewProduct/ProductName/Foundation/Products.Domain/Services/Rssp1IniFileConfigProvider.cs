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
using Acl.RsspI4net.Config;
using Products.Domain.Preferences;
using Products.Infrastructure.Specification;

namespace Products.Domain.Services
{
    /// <summary>
    /// ����INI�ļ���Rssp1ͨ�Ų����ṩ�ߡ�
    /// </summary>
    public class Rssp1IniFileConfigProvider : IRssp1ParamProvider
    {
        #region "Field"
        private WinIniFile _iniFile;
        #endregion

        #region "Constructor"

        /// <summary>
        /// �������Ĺ��캯����
        /// </summary>
        /// <param name="filePathName">�����ļ�����</param>
        /// <param name="isMachineA">�Ƿ�A����</param>
        /// <param name="redIP">���غ���IP</param>
        /// <param name="blueIP">��������IP</param>
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
        /// ���ڵ��Ƿ���A����
        /// </summary>
        public bool IsMachineA { get; private set; }

        /// <summary>
        /// ��ȡ���ع������ڣ����룩��
        /// </summary>
        public int WorkPeriod { get; private set; }
        
        /// <summary>
        /// ��ȡ���غ���IP
        /// </summary>
        public IPAddress LocalRedIP { get; private set; }
        /// <summary>
        /// ��ȡ��������IP
        /// </summary>
        public IPAddress LocalBlueIP { get; private set; }
        
        /// <summary>
        /// ��ȡRSSP-1���ع���������
        /// </summary>
        public WorkParameters LocalWorkParameter { get; private set; }
        /// <summary>
        /// ��ȡ���ذ�ȫ����
        /// </summary>
        public SafetyParameters LocalSafetyParam { get; private set; }
        /// <summary>
        /// ��ȡ�Ự������
        /// </summary>
        public IEnumerable<Tuple<IEnumerable<UdpParameters>, SessionConfig>> SessionParam { get; private set; }

        #endregion

        #region "Override methods"
        #endregion

        #region "Private methods"
        private void CreateIniFile(string filePathName)
        {
            if (!File.Exists(filePathName)) throw new Exception(string.Format("ָ�����ļ������ڣ�{0}", filePathName));

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
            //var localAddrs = SettingsParser.ParseDictionary(_iniFile.ReadValue("Local", "Address"), new String[] { ",", "��" }, new string[] { "=>" });
            //if (localAddrs.Count < 2) throw new Exception(string.Format("Local.Address��������С��2��"));
            //this.LocalSafetyParam.Addr = (ushort)localAddrs[this.LocalCodeInAts];
            this.LocalSafetyParam.Addr = (ushort)SettingsParser.ParseDecimal(_iniFile.ReadValue("Local", "Address"));
            var sid = SettingsParser.ParseDecimals(_iniFile.ReadValue("Local", "SID"), new string[] { ",", "��" });
            if (sid.Count < 2) throw new Exception(string.Format("Local.SID��������С��2��"));
            this.LocalSafetyParam.SID = sid.Select(p => (uint)p).ToArray();

            // SINIT
            var sinit = SettingsParser.ParseDecimals(_iniFile.ReadValue("Local", "SINIT"), new string[] { ",", "��" });
            if (sinit.Count < 2) throw new Exception(string.Format("Local.SINIT��������С��2��"));
            this.LocalSafetyParam.SINIT = sinit.Select(p => (uint)p).ToArray();

            // DataVersion
            var dataVer = SettingsParser.ParseDecimals(_iniFile.ReadValue("Local", "DATAVER"), new string[] { ",", "��" });
            if (dataVer.Count < 2) throw new Exception(string.Format("Local.DATAVER��������С��2��"));
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
            var sid = SettingsParser.ParseDecimals(_iniFile.ReadValue(section, "SID"), new string[] { ",", "��" });
            if (sid.Count < 2) throw new Exception(string.Format("{0}.SID��������С��2��", section));
            remoteSafetyParam.SID = sid.Select(p => (uint)p).ToArray();
            // SINIT
            var sinit = SettingsParser.ParseDecimals(_iniFile.ReadValue(section, "SINIT"), new string[] { ",", "��" });
            if (sinit.Count < 2) throw new Exception(string.Format("{0}.SINIT��������С��2��", section));
            remoteSafetyParam.SINIT = sinit.Select(p => (uint)p).ToArray();
            // DataVersion
            var dataVer = SettingsParser.ParseDecimals(_iniFile.ReadValue(section, "DATAVER"), new string[] { ",", "��" });
            if (dataVer.Count < 2) throw new Exception(string.Format("{0}.DATAVER��������С��2��", section));
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

                // Read CustomNodeCode��
                var customNodeCode = (ushort)SettingsParser.ParseDecimal(_iniFile.ReadValue(section, "CustomNodeCode"));

                // LoalPort
                var ports = _iniFile.ReadValue(section, "LocalPort").Trim().Split(new string[] { ",", "��" }, StringSplitOptions.RemoveEmptyEntries).ToList();
                if (ports.Count < 1) throw new Exception(string.Format("{0}.LocalPort��������С��1��", section));
                int localRedPort = 0, localBluePort = 0;
                localRedPort = (int)SettingsParser.ParseDecimal(ports[0]);
                localBluePort = ports.Count < 2 ? localRedPort : (int)SettingsParser.ParseDecimal(ports[1]);

                // Create Remote EndPoint
                var remoteEP = SettingsParser.ParseIPEndPoints(_iniFile.ReadValue(section, "RemoteEndPoints"), new string[] { ",", "��" });
                if (remoteEP.Count < 2) throw new Exception(string.Format("{0}.RemoteEndPoints��������С��2��", section));

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
        /// ���� ָ���ĵ�ַ ���� ��Ӧ��ID��
        /// </summary>
        /// <param name="address">���磺0x1E01</param>
        /// <returns>���磺0x9201, 0x9202</returns>
        public List<uint> FindRemoteCode(ushort address)
        {
            return this.SessionParam.Where(p => p.Item2.RemoteParam.Addr == address)
                .Select(p => p.Item2.CustomRemoteCode).ToList();
        }

        /// <summary>
        /// ���ݽڵ���Զ����Ų��Ҷ�Ӧ��RSSP-I��ַ��
        /// </summary>
        /// <param name="customCode">�Զ����ţ����磺0x9201, 0x9202��</param>
        /// <returns>�Զ����Ŷ�Ӧ�ĵ�ַ�����磺0x1E01��</returns>
        public ushort FindAddress(uint customCode)
        {
            return this.SessionParam.Where(p => p.Item2.CustomRemoteCode == customCode)
                .Select(p => p.Item2.RemoteParam.Addr).FirstOrDefault();
        }

        #endregion
    }
}
