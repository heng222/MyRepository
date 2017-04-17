/*----------------------------------------------------------------
// 公司名称：北京交大微联科技有限公司
// 
// 项目名称：北京地铁15号线ATS项目
//
// 创 建 人：zhangheng
// 创建日期：07/15/2011 09:26:29 
// 邮    箱：zhangheng@bjmut.com
//
// Copyright (C) 北京交大微联科技有限公司 2009-2015 保留所有权利
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
    /// 注册表主键枚举
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
    /// WMI基本封装
    /// </summary>
    public class WmiWrapper
    {
        /// <summary>
        /// 使用指定的参数构建一个<seealso cref="ManagementScope"/>对象
        /// </summary>
        /// <param name="remoteIP">目标机器IP(e.g. 10.115.2.36)，如果是本机，则使用点号(.)标识。</param>
        /// <param name="userName">登录名</param>
        /// <param name="password">密码</param>
        /// <returns>特定的<seealso cref="ManagementScope"/>对象</returns>
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


        #region "注册表操作"
        /// <summary>
        /// 在远程目标机器上创建一个注册表主键
        /// </summary>
        /// <param name="connectionScope">ManagementScope</param>
        /// <param name="machineName">目标机器IP</param>
        /// <param name="BaseKey">注册表分支名</param>
        /// <param name="key">主键名称</param>
        /// <returns>创建成功则返回0</returns>
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
        /// 在远程目标机器上创建一个注册表键值
        /// </summary>
        /// <param name="connectionScope">ManagementScope</param>
        /// <param name="machineName">目标机器IP</param>
        /// <param name="BaseKey">注册表分支名</param>
        /// <param name="key">主键名称</param>
        /// <param name="valueName">键值名称</param>
        /// <param name="value">键值</param>
        /// <returns>创建成功则返回0</returns>
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


        #region "共享操作"

        /// <summary>
        /// 创建远程共享目录
        /// </summary>
        /// <param name="scope">ManagementScope</param>
        /// <param name="folderPath">目标机器要共享的目录路径(e.g. "D:\share" 或 "E:\" )</param>
        /// <param name="shareName">共享名</param>
        /// <param name="description">网络共享文件夹的描述</param>
        public static void CreateShareNetFolder(ManagementScope scope, string folderPath,
            string shareName, string description)
        {
            // 创建一个ManagementClass对像
            ManagementClass managementClass = new ManagementClass(scope, new ManagementPath("Win32_Share"), null);

            // 创建ManagementBaseObject的输入和输出参数
            ManagementBaseObject inParams = managementClass.GetMethodParameters("Create");
            ManagementBaseObject outParams;

            // 设置输入参数
            inParams["Description"] = description;
            inParams["Name"] = shareName;
            inParams["Path"] = folderPath;
            inParams["Type"] = 0; // DISK_DRIVE

            // 其它类型
            //DISK_DRIVE=0x0
            //PRINT_QUEUE=0x1
            //DEVICE = 0x2
            //IPC = 0x3
            //DISK_DRIVE_ADMIN = 0x80000000
            //PRINT_QUEUE_ADMIN=0x80000001
            //DEVICE_ADMIN=0x80000002
            //IPC_ADMIN=0x80000003
            //inParams["MaximunAllowed"] = intMaxConnectionsNum;

            // 调用方法ManagementClass对像
            outParams = managementClass.InvokeMethod("Create", inParams, null);

            // 检测方法是否调用成功
            uint rc = (uint)(outParams["ReturnValue"]);
            
            // 0: success
            // 22: exists
            if (rc != 0 && rc != 22)
            {
                throw new Exception(string.Format("Unable to create net share directiory! code = {0}", rc));
            }
        }

        /// <summary>
        /// 移除远程共享目录
        /// </summary>
        /// <param name="scope">ManagementScope</param>
        /// <param name="ShareName">共享名</param>
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
        /// 用net use命令连接到远程共享目录上，创建网络共享连接。
        /// </summary>
        /// <param name="serverIp">目标ip</param>
        /// <param name="shareName">远程共享名</param>
        /// <param name="userName">远程登录用户</param>
        /// <param name="password">远程登录密码</param>
        /// <param name="timeOut">等待net use命令退出的时间（以毫秒为单位）。</param>
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
                        throw new Exception(string.Format("net use命令执行失败，退出码{0}", process.ExitCode));
                    }
                }
                else
                {
                    throw new Exception(string.Format("net use执行失败，执行超时。"));
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
        /// 用net use delete命令移除网络共享连接
        /// </summary>
        /// <param name="serverIp">目标ip</param>
        /// <param name="shareName">远程共享名</param>
        /// <param name="userName">远程登录用户</param>
        /// <param name="password">远程登录密码</param>
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


        #region "文件/目录操作"

        /// <summary>
        /// 创建远程目录
        /// </summary>
        /// <param name="scope">ManagementScope Instance</param>
        /// <param name="newDirectoryName">要建立的目录名，如果目录名中有空格，必须使用引号括起来。</param>
        /// <example>
        /// WmiShareFunction.CreateRemoteDirectory(ms, @"\\192.168.3.210\Temp\aaa", @"\\192.168.3.210\Temp");
        /// WmiShareFunction.CreateRemoteDirectory(ms, "\"\\\\192.168.3.210\\Temp\\ATS log\"", @"\\192.168.3.210\Temp");
        /// </example>
        public static void CreateRemoteDirectory(ManagementScope scope, string newDirectoryName)
        {
            ObjectGetOptions objectGetOptions = new ObjectGetOptions(null, TimeSpan.MaxValue, true);

            // 创建Win32_ProcessStartup对象并设置相关的参数
            ManagementClass processStartupBatch = new ManagementClass(scope.Path.Path, "Win32_ProcessStartup", objectGetOptions);
            ManagementObject startUpObject = processStartupBatch.CreateInstance();
            startUpObject["ShowWindow"] = 0;

            // 创建对象Win32_Process
            ManagementClass processBatch = new ManagementClass(scope.Path.Path, "Win32_Process", objectGetOptions);

            // 设置Create方法的参数
            ManagementBaseObject inParamsCreate = processBatch.GetMethodParameters("Create");
            inParamsCreate["CommandLine"] = @"cmd /CMd " + newDirectoryName;
            //inParamsCreate["CurrentDirectory"] = currentDir;
            inParamsCreate["ProcessStartupInformation"] = startUpObject;

            // 执行Win32_Process.Create方法
            ManagementBaseObject outParams = null;
            outParams = processBatch.InvokeMethod("Create", inParamsCreate, null);

            // 检测执行结果
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
        /// 将本地资源[文件/目录]拷贝到目标目录。在执行此操作前，如果与目标机器没有建立连接，则先使用CreateShareNetConnect建立网络连接。
        /// </summary>
        /// <param name="scope">ManagementScope Instance</param>
        /// <param name="localResource">要推送的本地资源信息，可以是文件或目录。</param>
        /// <param name="remoteDir">远程目录。(e.g. \\192.168.3.210\Temp)</param>
        /// <param name="overwrite">若为 true，则允许改写现有文件；否则为 false。</param>
        public static void CopyResourceToRemote(
                      ManagementScope scope,
                      string localResource, 
                      string remoteDir,
                      bool overwrite)
        {
            CreateRemoteDirectory(scope, remoteDir);

            // Fix目标目录
            if (remoteDir.LastIndexOf('\\') != (remoteDir.Length - 1))
            {
                remoteDir += "\\";
            }


            // 目录拷贝
            if (Directory.Exists(localResource))
            {
                DirectoryInfo DirInfo = new DirectoryInfo(localResource);

                CopyDirectory(localResource, remoteDir + DirInfo.Name, overwrite);
            }
            // 文件拷贝
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
                throw new Exception(String.Format("指定的本地资源{0}不存在", localResource));
            }

        }

        /// <summary>
        /// 通过远程共享名，递归拷贝指定目录下的所有信息到目标目录
        /// </summary>
        /// <param name="localPath">本地目录</param>
        /// <param name="remotePath">目标目录</param>
        /// <param name="overwrite">若为 true，则允许改写现有文件；否则为 false。</param>
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
        /// 拷贝指定目录下的所有文件(不包括子目录)到目标目录
        /// </summary>
        /// <param name="localPath">本地路径(e.g. C:\\temp)</param>
        /// <param name="desPath">目的路径（e.g. \\targetServer\\shareName\\DirectoryPath）</param>
        /// <param name="overwrite">若为 true，则允许改写现有文件；否则为 false。</param>
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

        #region "其它"
        public static void ListRemoteProcess(ManagementScope scope)
        {
            ManagementObjectSearcher searcher = new ManagementObjectSearcher(scope,
                    new ObjectQuery("SELECT * FROM Win32_PerfFormattedData_PerfProc_Process WHERE name = \"httpd\""));

            Console.WriteLine("进程数：{0}", searcher.Get().Count);

            foreach (ManagementObject queryObj in searcher.Get())
            {
                Console.WriteLine("----------------------------------- ");
                //Console.WriteLine("Win32_Process   instance ");
                //Console.WriteLine("----------------------------------- ");
                Console.WriteLine("Name  :   {0} ", queryObj["Name"]);
                Console.WriteLine("CPU :   {0} ", queryObj["PercentProcessorTime"]);
                Console.WriteLine("内存峰值(K):   {0} ", Int32.Parse(queryObj["WorkingSetPeak"].ToString()) / 1024);
                Console.WriteLine("内存使用(K):   {0} ", Int32.Parse(queryObj["WorkingSet"].ToString()) / 1024);
                Console.WriteLine("线程数:   {0} ", queryObj["ThreadCount"]);
                Console.WriteLine("句柄数:   {0} ", queryObj["HandleCount"]);
                
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
            // 执行 net use，建立到服务器的连接
            WmiWrapper.CreateShareNetConnect("192.168.3.210", "Temp", "wmi", "123", 5000);

            WmiWrapper.CopyResourceToRemote(new ManagementScope(), @"G:\Temp\NxSafeCommLog", @"\\192.168.3.210\Temp\Diag\4", false);

            //WmiWrapper.CopyResourceToRemote(new ManagementScope(), @"G:\Temp\Diag", @"\\192.168.3.210\Temp\Diag\3", false);
            
        }


        [Test(Description = "在指定的目标机器上创建共享目录并打开")]
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

            // 创建net user连接
            //WmiWrapper.CreateShareNetConnect(txtTemp.Text, "", "wmi", "123", 8000);

            // 创建远程共享目录并打开
            //CreateShareFolderAndOpen(scope);

            // 将本地资源拷贝到目标机器
            //ThreadPool.QueueUserWorkItem(new WaitCallback(CopyRscToRemote));
            //CopyRscToRemote(null);

            //WmiWrapper.ListRemoteProcess(scope);
            //WmiWrapper.ListRemoteNetworkAdapterConfiguration(scope);
            //WmiWrapper.ListComputerInfo(scope);
        }
    }
}

// 
// 1. 启用远程管理例外：
// 
// netsh firewall set service remoteadmin enable 
// 禁用远程管理例外：
// 
// netsh firewall set service remoteadmin disable 


// 2. 组件服务中设置我的电脑的COM安全

// 3. wmimgmt.msc命令

// 4. "Administrators"添加用户"network service"


