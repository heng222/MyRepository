/*----------------------------------------------------------------
// ��˾���ƣ���������΢���Ƽ����޹�˾
// 
// ��Ŀ���ƣ���������15����ATS��Ŀ
//
// �� �� �ˣ�zhangheng
// �������ڣ�07/15/2011 09:26:29 
// ��    �䣺zhangheng@bjmut.com
//
// Copyright (C) ��������΢���Ƽ����޹�˾ 2009-2015 ��������Ȩ��
//
//----------------------------------------------------------------*/

using System;
using System.Diagnostics;
using System.IO;
using System.Management;
using NUnit.Framework;

namespace CSharpLearning
{

    /// <summary>
    /// ע�������ö��
    /// </summary>
    public enum RootKey : uint
    {
        HKEY_CLASSES_ROOT = 0x80000000,
        HKEY_CURRENT_USER = 0x80000001,
        HKEY_LOCAL_MACHINE = 0x80000002,
        HKEY_USERS = 0x80000003,
        HKEY_CURRENT_CONFIG = 0x80000005
    }

    /// <summary>
    /// WMI������װ
    /// </summary>
    public class WmiWrapper
    {
        /// <summary>
        /// ʹ��ָ���Ĳ�������һ��<seealso cref="ManagementScope"/>����
        /// </summary>
        /// <param name="remoteIP">Ŀ�����IP(e.g. 10.115.2.36)������Ǳ�������ʹ�õ��(.)��ʶ��</param>
        /// <param name="userName">��¼��</param>
        /// <param name="password">����</param>
        /// <returns>�ض���<seealso cref="ManagementScope"/>����</returns>
        public static ManagementScope BuildManagementScope(string remoteIP, string userName, string password)
        {
            ConnectionOptions options = new ConnectionOptions();
            options.Username = userName;
            options.Password = password;

            //options.Authority = "ntdlmdomain:DOMAIN";
            options.Impersonation = ImpersonationLevel.Impersonate;
            options.EnablePrivileges = true;
            //options.Authentication = AuthenticationLevel.Connect;
            //options.Authority
            ManagementScope scope = new ManagementScope(
                    "\\\\" + remoteIP + "\\root\\cimv2",
                    options);

            return scope;
        }


        #region "ע������"
        /// <summary>
        /// ��Զ��Ŀ������ϴ���һ��ע�������
        /// </summary>
        /// <param name="connectionScope">ManagementScope</param>
        /// <param name="machineName">Ŀ�����IP</param>
        /// <param name="BaseKey">ע����֧��</param>
        /// <param name="key">��������</param>
        /// <returns>�����ɹ��򷵻�0</returns>
        public static int CreateRemoteKey(ManagementScope connectionScope,
                                  string machineName,
                                  RootKey BaseKey,
                                  string key)
        {
            try
            {
                ObjectGetOptions objectGetOptions = new ObjectGetOptions(null, System.TimeSpan.MaxValue, true);
                connectionScope.Path = new ManagementPath(@"\\" + machineName + @"\root\DEFAULT:StdRegProv");
                connectionScope.Connect();
                ManagementClass registryTask = new ManagementClass(connectionScope,
                               new ManagementPath(@"DEFAULT:StdRegProv"), objectGetOptions);
                ManagementBaseObject methodParams = registryTask.GetMethodParameters("CreateKey");

                methodParams["hDefKey"] = BaseKey;
                methodParams["sSubKeyName"] = key;

                ManagementBaseObject exitCode = registryTask.InvokeMethod("CreateKey",
                                                                      methodParams, null);
            }
            catch (ManagementException /*ex*/)
            {
                return -1;
            }
            return 0;
        }

        /// <summary>
        /// ��Զ��Ŀ������ϴ���һ��ע����ֵ
        /// </summary>
        /// <param name="connectionScope">ManagementScope</param>
        /// <param name="machineName">Ŀ�����IP</param>
        /// <param name="BaseKey">ע����֧��</param>
        /// <param name="key">��������</param>
        /// <param name="valueName">��ֵ����</param>
        /// <param name="value">��ֵ</param>
        /// <returns>�����ɹ��򷵻�0</returns>
        public static int CreateRemoteValue(ManagementScope connectionScope,
                                    string machineName,
                                    RootKey BaseKey,
                                    string key,
                                    string valueName,
                                    string value)
        {
            try
            {
                ObjectGetOptions objectGetOptions = new ObjectGetOptions(null, System.TimeSpan.MaxValue, true);
                connectionScope.Path = new ManagementPath(@"\\" + machineName + @"\root\DEFAULT:StdRegProv");
                connectionScope.Connect();
                ManagementClass registryTask = new ManagementClass(connectionScope,
                               new ManagementPath(@"DEFAULT:StdRegProv"), objectGetOptions);
                ManagementBaseObject methodParams = registryTask.GetMethodParameters("SetStringValue");

                methodParams["hDefKey"] = BaseKey;
                methodParams["sSubKeyName"] = key;
                methodParams["sValue"] = value;
                methodParams["sValueName"] = valueName;

                ManagementBaseObject exitCode = registryTask.InvokeMethod("SetStringValue",
                                                                         methodParams, null);
            }
            catch (ManagementException /*ex*/)
            {
                return -1;
            }
            return 0;
        }

        #endregion


        #region "�������"

        /// <summary>
        /// ����Զ�̹���Ŀ¼
        /// </summary>
        /// <param name="scope">ManagementScope</param>
        /// <param name="folderPath">Ŀ�����Ҫ�����Ŀ¼·��(e.g. "D:\share" �� "E:\" )</param>
        /// <param name="shareName">������</param>
        /// <param name="description">���繲���ļ��е�����</param>
        public static void CreateShareNetFolder(ManagementScope scope, string folderPath,
            string shareName, string description)
        {
            // ����һ��ManagementClass����
            ManagementClass managementClass = new ManagementClass(scope, new ManagementPath("Win32_Share"), null);

            // ����ManagementBaseObject��������������
            ManagementBaseObject inParams = managementClass.GetMethodParameters("Create");
            ManagementBaseObject outParams;

            // �����������
            inParams["Description"] = description;
            inParams["Name"] = shareName;
            inParams["Path"] = folderPath;
            inParams["Type"] = 0; // DISK_DRIVE

            // ��������
            //DISK_DRIVE=0x0
            //PRINT_QUEUE=0x1
            //DEVICE = 0x2
            //IPC = 0x3
            //DISK_DRIVE_ADMIN = 0x80000000
            //PRINT_QUEUE_ADMIN=0x80000001
            //DEVICE_ADMIN=0x80000002
            //IPC_ADMIN=0x80000003
            //inParams["MaximunAllowed"] = intMaxConnectionsNum;

            // ���÷���ManagementClass����
            outParams = managementClass.InvokeMethod("Create", inParams, null);

            // ��ⷽ���Ƿ���óɹ�
            uint rc = (uint)(outParams["ReturnValue"]);
            
            // 0: success
            // 22: exists
            if (rc != 0 && rc != 22)
            {
                throw new Exception(string.Format("Unable to create net share directiory! code = {0}", rc));
            }
        }

        /// <summary>
        /// �Ƴ�Զ�̹���Ŀ¼
        /// </summary>
        /// <param name="scope">ManagementScope</param>
        /// <param name="ShareName">������</param>
        public static void RemoveShareNetFolder(ManagementScope scope, string ShareName)
        {
            ObjectQuery selectQuery = new ObjectQuery("Select * from Win32_Share Where Name = '" + ShareName + "'");
            ManagementObjectSearcher searcher = new ManagementObjectSearcher(scope, selectQuery);
            foreach (ManagementObject mo in searcher.Get())
            {
                mo.InvokeMethod("Delete", null, null);
            }
        }

        /// <summary>
        /// ��net use�������ӵ�Զ�̹���Ŀ¼�ϣ��������繲�����ӡ�
        /// </summary>
        /// <param name="serverIp">Ŀ��ip</param>
        /// <param name="shareName">Զ�̹�����</param>
        /// <param name="userName">Զ�̵�¼�û�</param>
        /// <param name="password">Զ�̵�¼����</param>
        /// <param name="timeOut">�ȴ�net use�����˳���ʱ�䣨�Ժ���Ϊ��λ����</param>
        public static void CreateShareNetConnect(string serverIp, string shareName,
            string userName, string password, int timeOut)
        {
            Process process = new Process();
            try
            {
                process.StartInfo.FileName = "net.exe";
                if (String.IsNullOrEmpty(shareName))
                {
                    process.StartInfo.Arguments = @"use \\" + serverIp + " \"" + password + "\" /user:\"" + userName + "\" ";
                }
                else
                {
                    process.StartInfo.Arguments = @"use \\" + serverIp + @"\" + shareName + " \"" + password + "\" /user:\"" + userName + "\" ";
                }
                process.StartInfo.CreateNoWindow = true;
                process.StartInfo.UseShellExecute = false;
                process.Start();

                if (process.WaitForExit(timeOut))
                {
                    if (process.ExitCode != 0)
                    {
                        throw new Exception(string.Format("net use����ִ��ʧ�ܣ��˳���{0}", process.ExitCode));
                    }
                }
                else
                {
                    throw new Exception(string.Format("net useִ��ʧ�ܣ�ִ�г�ʱ��"));
                }
            }
            catch (System.Exception ex)
            {
                throw ex;
            }
            finally
            {
                process.Close();
            }
        }

        /// <summary>
        /// ��net use delete�����Ƴ����繲������
        /// </summary>
        /// <param name="serverIp">Ŀ��ip</param>
        /// <param name="shareName">Զ�̹�����</param>
        /// <param name="userName">Զ�̵�¼�û�</param>
        /// <param name="password">Զ�̵�¼����</param>
        public static void RemoveShareNetConnect(string serverIp, string shareName,
            string userName, string password)
        {
            Process process = new Process();
            try
            {
                process.StartInfo.FileName = "net.exe";
                if (String.IsNullOrEmpty(shareName))
                {
                    process.StartInfo.Arguments = @"use \\" + serverIp + " /delete";
                }
                else
                {
                    process.StartInfo.Arguments = @"use \\" + serverIp + @"\" + shareName + " /delete";
                }
                process.StartInfo.CreateNoWindow = true;
                process.StartInfo.UseShellExecute = false;
                process.Start();
                process.WaitForExit();
            }
            catch (System.Exception /*ex*/)
            {
            }
            finally
            {
                process.Close();
            }
        }

        #endregion


        #region "�ļ�/Ŀ¼����"

        /// <summary>
        /// ����Զ��Ŀ¼
        /// </summary>
        /// <param name="scope">ManagementScope Instance</param>
        /// <param name="newDirectoryName">Ҫ������Ŀ¼�������Ŀ¼�����пո񣬱���ʹ��������������</param>
        /// <example>
        /// WmiShareFunction.CreateRemoteDirectory(ms, @"\\192.168.3.210\Temp\aaa", @"\\192.168.3.210\Temp");
        /// WmiShareFunction.CreateRemoteDirectory(ms, "\"\\\\192.168.3.210\\Temp\\ATS log\"", @"\\192.168.3.210\Temp");
        /// </example>
        public static void CreateRemoteDirectory(ManagementScope scope, string newDirectoryName)
        {
            ObjectGetOptions objectGetOptions = new ObjectGetOptions(null, TimeSpan.MaxValue, true);

            // ����Win32_ProcessStartup����������صĲ���
            ManagementClass processStartupBatch = new ManagementClass(scope.Path.Path, "Win32_ProcessStartup", objectGetOptions);
            ManagementObject startUpObject = processStartupBatch.CreateInstance();
            startUpObject["ShowWindow"] = 0;

            // ��������Win32_Process
            ManagementClass processBatch = new ManagementClass(scope.Path.Path, "Win32_Process", objectGetOptions);

            // ����Create�����Ĳ���
            ManagementBaseObject inParamsCreate = processBatch.GetMethodParameters("Create");
            inParamsCreate["CommandLine"] = @"cmd /CMd " + newDirectoryName;
            //inParamsCreate["CurrentDirectory"] = currentDir;
            inParamsCreate["ProcessStartupInformation"] = startUpObject;

            // ִ��Win32_Process.Create����
            ManagementBaseObject outParams = null;
            outParams = processBatch.InvokeMethod("Create", inParamsCreate, null);

            // ���ִ�н��
            uint rc = (uint)(outParams.Properties["ReturnValue"].Value);
            if (rc == 2)
            {
                throw new Exception("Access Denied!");
            }
            else if (rc == 3)
            {
                throw new Exception("Insufficient Privilege!");
            }
            else if (rc == 8)
            {
                throw new Exception("Unknown failure!");
            }
            else if (rc == 9)
            {
                throw new Exception("Path Not Found!");
            }
            else if (rc == 21)
            {
                throw new Exception("Invalid Parameter!");
            }
        }

        /// <summary>
        /// ��������Դ[�ļ�/Ŀ¼]������Ŀ��Ŀ¼����ִ�д˲���ǰ�������Ŀ�����û�н������ӣ�����ʹ��CreateShareNetConnect�����������ӡ�
        /// </summary>
        /// <param name="scope">ManagementScope Instance</param>
        /// <param name="localResource">Ҫ���͵ı�����Դ��Ϣ���������ļ���Ŀ¼��</param>
        /// <param name="remoteDir">Զ��Ŀ¼��(e.g. \\192.168.3.210\Temp)</param>
        /// <param name="overwrite">��Ϊ true���������д�����ļ�������Ϊ false��</param>
        public static void CopyResourceToRemote(
                      ManagementScope scope,
                      string localResource, 
                      string remoteDir,
                      bool overwrite)
        {
            CreateRemoteDirectory(scope, remoteDir);

            // FixĿ��Ŀ¼
            if (remoteDir.LastIndexOf('\\') != (remoteDir.Length - 1))
            {
                remoteDir += "\\";
            }


            // Ŀ¼����
            if (Directory.Exists(localResource))
            {
                DirectoryInfo DirInfo = new DirectoryInfo(localResource);

                CopyDirectory(localResource, remoteDir + DirInfo.Name, overwrite);
            }
            // �ļ�����
            else if (File.Exists(localResource))
            {
                FileInfo localFileInfo = new FileInfo(localResource);

                string remoteFile = remoteDir + localFileInfo.Name;
                FileInfo remoteFileInfo = new FileInfo(remoteFile);

                if ((remoteFileInfo.Exists && overwrite) || !remoteFileInfo.Exists)
                {
                    File.Copy(localResource, remoteFile, overwrite);
                }
            }
            else
            {
                throw new Exception(String.Format("ָ���ı�����Դ{0}������", localResource));
            }

        }

        /// <summary>
        /// ͨ��Զ�̹��������ݹ鿽��ָ��Ŀ¼�µ�������Ϣ��Ŀ��Ŀ¼
        /// </summary>
        /// <param name="localPath">����Ŀ¼</param>
        /// <param name="remotePath">Ŀ��Ŀ¼</param>
        /// <param name="overwrite">��Ϊ true���������д�����ļ�������Ϊ false��</param>
        public static void CopyDirectory(string localPath, string remotePath, bool overwrite)
        {
            if (!Directory.Exists(remotePath))
            {
                Directory.CreateDirectory(remotePath);
            }

            DirectoryInfo dir = new DirectoryInfo(localPath);
            DirectoryInfo[] dirs = dir.GetDirectories();
            CopyFiles(dir, remotePath, overwrite);

            if (dirs.Length > 0)
            {
                foreach (DirectoryInfo temDirectoryInfo in dirs)
                {
                    string sourceDirectoryFullName = temDirectoryInfo.FullName;
                    string destDirectoryFullName = sourceDirectoryFullName.Replace(localPath, remotePath);

                    if (!Directory.Exists(destDirectoryFullName))
                    {
                        Directory.CreateDirectory(destDirectoryFullName);
                    }

                    //CopyFile(temDirectoryInfo, destDirectoryFullName, overwrite);

                    CopyDirectory(sourceDirectoryFullName, destDirectoryFullName, overwrite);
                }
            }
        }

        /// <summary>
        /// ����ָ��Ŀ¼�µ������ļ�(��������Ŀ¼)��Ŀ��Ŀ¼
        /// </summary>
        /// <param name="localPath">����·��(e.g. C:\\temp)</param>
        /// <param name="desPath">Ŀ��·����e.g. \\targetServer\\shareName\\DirectoryPath��</param>
        /// <param name="overwrite">��Ϊ true���������д�����ļ�������Ϊ false��</param>
        public static void CopyFiles(DirectoryInfo localPath, string desPath, bool overwrite)
        {
            string sourcePath = localPath.FullName;
            FileInfo[] files = localPath.GetFiles();

            foreach (FileInfo file in files)
            {
                string sourceFileFullName = file.FullName;
                string destFileFullName = sourceFileFullName.Replace(sourcePath, desPath);
                FileInfo destFileInfo = new FileInfo(destFileFullName);
                
                if (!destFileInfo.Exists || (destFileInfo.Exists && overwrite))
                {
                    file.CopyTo(destFileFullName, overwrite);
                }
            }
        }

        #endregion

        #region "����"
        public static void ListRemoteProcess(ManagementScope scope)
        {
            ManagementObjectSearcher searcher = new ManagementObjectSearcher(scope,
                    new ObjectQuery("SELECT * FROM Win32_PerfFormattedData_PerfProc_Process WHERE name = \"httpd\""));

            Console.WriteLine("��������{0}", searcher.Get().Count);

            foreach (ManagementObject queryObj in searcher.Get())
            {
                Console.WriteLine("----------------------------------- ");
                //Console.WriteLine("Win32_Process   instance ");
                //Console.WriteLine("----------------------------------- ");
                Console.WriteLine("Name  :   {0} ", queryObj["Name"]);
                Console.WriteLine("CPU :   {0} ", queryObj["PercentProcessorTime"]);
                Console.WriteLine("�ڴ��ֵ(K):   {0} ", Int32.Parse(queryObj["WorkingSetPeak"].ToString()) / 1024);
                Console.WriteLine("�ڴ�ʹ��(K):   {0} ", Int32.Parse(queryObj["WorkingSet"].ToString()) / 1024);
                Console.WriteLine("�߳���:   {0} ", queryObj["ThreadCount"]);
                Console.WriteLine("�����:   {0} ", queryObj["HandleCount"]);
                
            }
        }

        public static void ListRemoteNetworkAdapterConfiguration(ManagementScope scope)
        {
            ManagementObjectSearcher searcher = new ManagementObjectSearcher(scope,
                    new ObjectQuery("SELECT * FROM Win32_NetworkAdapterConfiguration"));

            foreach (ManagementObject queryObj in searcher.Get())
            {
                Console.WriteLine("----------------------------------- ");
                Console.WriteLine("IPAddress:   {0} ", (queryObj["IPAddress"] as string[])[0]);
                Console.WriteLine("IPSubnet:   {0} ", (queryObj["IPSubnet"] as string[])[0]);
                Console.WriteLine("DefaultIPGateway (K):   {0} ", (queryObj["DefaultIPGateway"] as string[])[0]);

            }
        }

        public static void ListComputerInfo(ManagementScope scope)
        {
            ObjectQuery oq = new ObjectQuery("SELECT * FROM Win32_OperatingSystem");

            ManagementObjectSearcher searcher = new ManagementObjectSearcher(scope, oq);

            foreach (ManagementObject queryObj in searcher.Get())
            {
                Console.WriteLine("----------------------------------- ");
                Console.WriteLine("CSName: {0} ", queryObj["CSName"]);
            }


        }
        #endregion
    }

    [TestFixture]
    public class WMITest
    {
        [Test]
        public void Test1()
        {
            // ִ�� net use��������������������
            WmiWrapper.CreateShareNetConnect("192.168.3.210", "Temp", "wmi", "123", 5000);

            WmiWrapper.CopyResourceToRemote(new ManagementScope(), @"G:\Temp\NxSafeCommLog", @"\\192.168.3.210\Temp\Diag\4", false);

            //WmiWrapper.CopyResourceToRemote(new ManagementScope(), @"G:\Temp\Diag", @"\\192.168.3.210\Temp\Diag\3", false);
            
        }


        [Test(Description = "��ָ����Ŀ������ϴ�������Ŀ¼����")]
        public void Test2(ManagementScope scope)
        {
            string sharename = "BJM15ATS";
            string ip = "txtIP.Text";
            string username = "txtUserName.Text";
            string password = "txtPassword.Text";
            string folder = "txtRemoteFolder.Text";

            if (scope.IsConnected)
            {
                WmiWrapper.CreateShareNetFolder(scope, folder, sharename, "BJM15-ATS Software Folder");

                WmiWrapper.RemoveShareNetConnect(ip, sharename, username, password);
                WmiWrapper.CreateShareNetConnect(ip, sharename, username, password, 5000);

                Process.Start("explorer", @"\\" + ip + @"\" + sharename);

                //WmiWrapper.RemoveShareNetFolder(scope, sharename);
            }
        }

        [Test]
        public void Test3()
        {
            //ManagementScope scope = WmiWrapper.BuildManagementScope(ip, username, password);
            //scope.Connect();

            // ����net user����
            //WmiWrapper.CreateShareNetConnect(txtTemp.Text, "", "wmi", "123", 8000);

            // ����Զ�̹���Ŀ¼����
            //CreateShareFolderAndOpen(scope);

            // ��������Դ������Ŀ�����
            //ThreadPool.QueueUserWorkItem(new WaitCallback(CopyRscToRemote));
            //CopyRscToRemote(null);

            //WmiWrapper.ListRemoteProcess(scope);
            //WmiWrapper.ListRemoteNetworkAdapterConfiguration(scope);
            //WmiWrapper.ListComputerInfo(scope);
        }
    }
}

// 
// 1. ����Զ�̹������⣺
// 
// netsh firewall set service remoteadmin enable 
// ����Զ�̹������⣺
// 
// netsh firewall set service remoteadmin disable 


// 2. ��������������ҵĵ��Ե�COM��ȫ

// 3. wmimgmt.msc����

// 4. "Administrators"����û�"network service"


