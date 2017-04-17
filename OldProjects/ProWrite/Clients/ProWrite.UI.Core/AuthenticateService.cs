using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Win32;
using ProWrite.Core;
using System.Security.Cryptography;
using System.Management;
using System.Diagnostics;
using log4net;

namespace ProWrite.UI.Controls
{
    public class AuthenticateParams
    {
        public AuthenticateParams(string productName)
        {
            Debug.Assert(!string.IsNullOrEmpty(productName), "productName != null");
            ProductName = productName;
            MachineCode = "MachineCode";
            RegisterCode = "RegisterCode";
            BeginDate = "BeginDate";
            EndDate = "EndDate";
            LastedDate = "LastedDate";
            SalesNumber = "SalesNumber";
        }

        public string ProductName { get; private set; }
        public string MachineCode { get; set; }
        public string RegisterCode { get; set; }
        public string BeginDate { get; set; }
        public string EndDate { get; set; }
        public string LastedDate { get; set; }
        public string SalesNumber { get; set; }

        public int[] Limiteds { get; set; }
        public bool UnLimited { get; set; }
    }

    public class AuthenticateService : DisposableObject
    {
        RegistryKey registryKey;
        private string CpuId;
        private Cryptographer encry;
        private static readonly ILog log = LogManager.GetLogger(typeof(AuthenticateService));

        public AuthenticateService(string productName)
        {
            //Init(productName);
            encry = new Cryptographer();
            Params = new AuthenticateParams(productName);

            CpuId = fp.Value();
            FailedType = ErrorType.Default;
        }

        private class _
        {
            public const int Unlimited = -1;
            public const int InvalidRegistryKey = -2;
        }

        //private void Init(string productName)
        //{
        //    encry = new Cryptographer();
        //    Params = new AuthenticateParams(productName);

        //    try
        //    {
        //        using (ManagementClass mc = new ManagementClass("Win32_Processor"))
        //        using (ManagementObjectCollection moc = mc.GetInstances())
        //        {
        //            foreach (ManagementObject mo in moc)
        //            {
        //                CpuId = mo.Properties["ProcessorId"].Value.ToString();
        //                break;
        //            }
        //        }
        //    }
        //    catch (Exception e)
        //    {
        //        log.Error(e.Message, e);
        //    }
        //}

        public AuthenticateParams Params { get; private set; }

        private static string MD5Encrpty(string source)
        {
            using (MD5CryptoServiceProvider md5 = new MD5CryptoServiceProvider())
                return BitConverter.ToString(md5.ComputeHash(source.GetBytesUTF8()), 4, 8).Replace("-", "");
        }


        private string Encrpyt(string source)
        {
            try
            {
                return encry.SymmetricEncrpyt(source);
            }
            catch (Exception e)
            {
                log.Error(e.Message, e);
                return source;
            }
        }

        public string Decrpyt(string source)
        {
            try
            {
                return encry.SymmetricDecrpyt(source);
            }
            catch (Exception e)
            {
                log.Error(e.Message, e);
                return source;
            }
        }

        private RegistryKey RegistryKey
        {
            get { return registryKey; }
        }

        public string MachineCode { get; private set; }
        public string RegisterCode { get; private set; }
        private string BeginDate { get; set; }
        public string SalesNumber { get; set; }
        private string EndDate { get; set; }
        public string LastedDate { get; set; }
        public ErrorType FailedType { get; private set; }
        string sKey = "tracsLux";
        Fingerprint fp = new Fingerprint();


        public void CreateSubKey(string salesNumber)
        {
            //if (string.IsNullOrEmpty(salesNumber))
            //    return;
            CodeTimer.Time("CreateSubKey", () =>
            {
                var time = DateTime.Now.ToString();
                BeginDate = Encrpyt(time);
                SalesNumber = Encrpyt(salesNumber);
                var now = (DateTime.Now.Year.ToString()
                                    + convertDateString(DateTime.Now.Month)
                                    + convertDateString(DateTime.Now.Day)).Substring(2);
                MachineCode = Safe.DesEncrypt(now + CpuId + salesNumber, sKey).Replace("-", "");// MD5Encrpty(time + CpuId);

                //MachineCode =  MD5Encrpty(time + CpuId);
                registryKey.SetValue(Params.BeginDate, BeginDate);
                registryKey.SetValue(Params.SalesNumber, SalesNumber);
                registryKey.SetValue(Params.MachineCode, MachineCode);
            });

        }

        private string convertDateString(int datetime)
        {
            return datetime < 10 ? "0" + datetime.ToString() : datetime.ToString();
        }

        public bool HasAuthenticated { get; internal set; }

        public bool Authenticate(string registerCode)
        {
            Check.Assert(!string.IsNullOrEmpty(Params.ProductName), "Params.ProductName != null");
            if (registryKey == null) return false;
            RegisterCode = registerCode;
            return OnAuthenticate();
        }

        public bool Authenticate()
        {
            registryKey = Registry.CurrentUser.OpenSubKey(Params.ProductName, true);

            if (registryKey == null)
            {
                registryKey = Registry.CurrentUser.CreateSubKey(Params.ProductName);

                registryKey.SetValue(Params.RegisterCode, "");
                registryKey.SetValue(Params.EndDate, "");
                registryKey.SetValue(Params.LastedDate, "");
                registryKey.SetValue(Params.SalesNumber, "");
                //CreateSubKey("");
                return false;
            }
            string salesNumber = registryKey.GetValue(Params.SalesNumber, "").ToString().Trim();
            if (string.IsNullOrEmpty(salesNumber))
                return false;
            SalesNumber = Decrpyt(salesNumber);
            RegisterCode = registryKey.GetValue(Params.RegisterCode, "").ToString().Trim();
            string databegin = registryKey.GetValue(Params.BeginDate, "").ToString().Trim();
            if (string.IsNullOrEmpty(databegin))
            {
                //CreateSubKey();
                return false;
            }
            string dateLasted = registryKey.GetValue(Params.LastedDate, "").ToString().Trim();
            if (!string.IsNullOrEmpty(RegisterCode)
                && !string.IsNullOrEmpty(dateLasted))
            {
                DateTime dtLasted;

                if (!DateTime.TryParse(this.Decrpyt(dateLasted), out dtLasted))
                {
                    //CreateSubKey();
                    registryKey.SetValue(Params.RegisterCode, "");
                    registryKey.SetValue(Params.EndDate, "");
                    registryKey.SetValue(Params.LastedDate, "");
                    return false;
                }
                DateTime dtNow = DateTime.Now;
                //DateTime dtLasted = DateTime.Parse(dateLasted);
                TimeSpan tUsedCount = dtNow - dtLasted;

                if (Convert.ToInt32(tUsedCount.TotalDays) < 0)
                {
                    //CreateSubKey();
                    registryKey.SetValue(Params.RegisterCode, "");
                    registryKey.SetValue(Params.EndDate, "");
                    registryKey.SetValue(Params.LastedDate, "");
                    return false;
                }
            }

            BeginDate = Decrpyt(databegin);

            MachineCode = registryKey.GetValue(Params.MachineCode, "").ToString().Trim();
            if (string.IsNullOrEmpty(MachineCode))
            {
                //CreateSubKey();
                return false;
            }


            //如果机器码不符合规范，则重新生成机器码
            if (MachineCode.Length != 48)
            {
                //CreateSubKey();
                return false;
            }
            var date1 = DateTime.Parse(BeginDate);
            var date = (date1.Year.ToString()
                                + convertDateString(date1.Month)
                                + convertDateString(date1.Day)).Substring(2);

            string tmpMachineCode = Safe.DesEncrypt(date + CpuId + SalesNumber, sKey);// MD5Encrpty(BeginDate + CpuId);
            if (!string.Equals(tmpMachineCode, MachineCode))
            {
                var time = DateTime.Now.ToString();
                BeginDate = Encrpyt(time);
                //SalesNumber = Encrpyt(salesNumber);
                var now = (DateTime.Now.Year.ToString()
                                    + convertDateString(DateTime.Now.Month)
                                    + convertDateString(DateTime.Now.Day)).Substring(2);
                MachineCode = Safe.DesEncrypt(now + CpuId + SalesNumber, sKey).Replace("-", "");// MD5Encrpty(time + CpuId);

                //MachineCode =  MD5Encrpty(time + CpuId);
                registryKey.SetValue(Params.BeginDate, BeginDate);
                //registryKey.SetValue(Params.SalesNumber, SalesNumber);
                registryKey.SetValue(Params.MachineCode, MachineCode);
                return false;
            }




            if (string.IsNullOrEmpty(RegisterCode))
            {

                return false;
            }
            if (RegisterCode.Length != 16)
            {

                return false;
            }


            EndDate = registryKey.GetValue(Params.EndDate, "").ToString().Trim();
            return OnAuthenticate();
        }

        private bool OnAuthenticate()
        {
            var keyType = GetKeyType();
            if (keyType == _.Unlimited)
            {
                registryKey.SetValue(Params.RegisterCode, RegisterCode);
                HasAuthenticated = true;
            }
            else if (keyType == _.InvalidRegistryKey)
                HasAuthenticated = false;
            else
                HasAuthenticated = CheckRegisterCode(keyType);

            return HasAuthenticated;
        }

        private int GetKeyType()
        {

            var keyLength = Params.Limiteds.Length;
            var keys = new string[keyLength];
            var keys_2 = new string[keyLength];

            for (int i = 0; i < keyLength; i++)
            {
                keys[i] = MD5Encrpty(MachineCode + Params.Limiteds[i].ToString());
                keys_2[i] = MD5Encrpty("$" + MachineCode + Params.Limiteds[i].ToString());
                if (keys[i] == RegisterCode)
                    return Params.Limiteds[i];
                else if (keys_2[i] == RegisterCode)
                {
                    //registryKey.SetValue("ShowLivePage", "1");
                    return Params.Limiteds[i];
                }

            }

            if (Params.UnLimited)
            {
                var strKeyUnlimited = MD5Encrpty(MachineCode + "unlimited");
                var strKeyUnlimited_2 = MD5Encrpty("$" + MachineCode + "unlimited");
                if (strKeyUnlimited == RegisterCode || strKeyUnlimited_2 == RegisterCode)
                    return -1;
            }

            return -2;
        }

        public bool IsShowLivePage()
        {
            var keyLength = Params.Limiteds.Length;
            var keys = new string[keyLength];
            var keys_2 = new string[keyLength];

            registryKey = Registry.CurrentUser.OpenSubKey(Params.ProductName, true);

            if (registryKey == null)
                return false;
            MachineCode = registryKey.GetValue(Params.MachineCode, "").ToString().Trim();
            if(string.IsNullOrEmpty(MachineCode))
                return false;
            RegisterCode = registryKey.GetValue(Params.RegisterCode, "").ToString().Trim();
            if (string.IsNullOrEmpty(RegisterCode))
                return false;
            for (int i = 0; i < keyLength; i++)
            {
                keys[i] = MD5Encrpty(MachineCode + Params.Limiteds[i].ToString());
                keys_2[i] = MD5Encrpty("$" + MachineCode + Params.Limiteds[i].ToString());
                if (keys[i] == RegisterCode)
                    return false;
                else if (keys_2[i] == RegisterCode)
                    return true;
            }

            if (Params.UnLimited)
            {
                var strKeyUnlimited = MD5Encrpty(MachineCode + "unlimited");
                var strKeyUnlimited_2 = MD5Encrpty("$" + MachineCode + "unlimited");
                if (strKeyUnlimited == RegisterCode)
                    return false;
                else if (strKeyUnlimited_2 == RegisterCode)
                    return true;
            }

            return false;
        }

        public bool CheckRegisterCode(int type)
        {
            DateTime dtBegin;
            string databegin = registryKey.GetValue(Params.BeginDate, "").ToString().Trim();
            BeginDate = Decrpyt(databegin);
            string endDate = registryKey.GetValue(Params.EndDate, "").ToString().Trim();
            if (!string.IsNullOrEmpty(endDate))
                EndDate = Decrpyt(endDate);
            else
                EndDate = "";
            if (!DateTime.TryParse(BeginDate, out dtBegin))
            {
                //CreateSubKey();
                return false;
            }

            DateTime dtEnd;
            if (string.IsNullOrEmpty(EndDate))
            {
                dtEnd = dtBegin.AddDays(type);
                EndDate = dtEnd.ToString();
                registryKey.SetValue(Params.EndDate, Encrpyt(EndDate));
            }
            else
            {
                if (!DateTime.TryParse(EndDate, out dtEnd))
                {
                    //CreateSubKey();
                    return false;
                }
            }

            DateTime dtNow = DateTime.Now;

            TimeSpan tUsedCount = dtNow - dtBegin;
            TimeSpan tRemainCount = dtEnd - dtNow;
            int iUsedDay = Convert.ToInt32(tUsedCount.TotalDays);
            if (iUsedDay < 0)
            {
                //if MsgBox.Confirm("Sorry,Perhaps you have changed your system date,Would you want to rebuild a new register number?") == DialogResult.Yes)
                FailedType = ErrorType.ChangeSystemDate;
                //CreateSubKey();
                return false;
            }

            int iRemainDay = Convert.ToInt32(tRemainCount.TotalDays);
            if (iRemainDay < 0)
            {
                FailedType = ErrorType.Overdue;
                //CreateSubKey();
                registryKey.SetValue(Params.RegisterCode, "");
                registryKey.SetValue(Params.EndDate, "");
                registryKey.SetValue(Params.LastedDate, "");
                registryKey.SetValue(Params.MachineCode, "");
                registryKey.SetValue(Params.BeginDate, "");
                return false;
            }
            RegistryKey.SetValue(Params.LastedDate, Encrpyt(dtNow.ToString()));
            RegistryKey.SetValue(Params.RegisterCode, RegisterCode);
            return true;
        }

        protected override void Dispose(bool disposing)
        {
            if (registryKey != null)
                registryKey.Close();
            base.Dispose(disposing);
        }
    }

    public class ProWriteAuthenticateService : AuthenticateService
    {
        public ProWriteAuthenticateService()
            : base("SOFTWARE\\ProWrite" /*+ ProductInfo.VersionCode.Replace(".","_")*/)
        {
            Params.Limiteds = new int[] { 15, 20, 30, 45, 60, 180 };
            Params.UnLimited = true;
        }
    }

    public enum ErrorType
    {
        Default,
        Overdue,
        ChangeSystemDate,
    }

    public class Fingerprint
    //Fingerprints the hardware
    {
        public string Value()
        {
            return pack(cpuId()
                 + biosId()
                 + diskId());
            //+ baseId()
            //+ videoId());
            //+ macId());
        }
        private string identifier(string wmiClass, string wmiProperty, string wmiMustBeTrue)
        //Return a hardware identifier
        {
            string result = "";
            System.Management.ManagementClass mc = new System.Management.ManagementClass(wmiClass);
            System.Management.ManagementObjectCollection moc = mc.GetInstances();
            foreach (System.Management.ManagementObject mo in moc)
            {
                if (mo[wmiMustBeTrue].ToString() == "True")
                {

                    //Only get the first one
                    if (result == "")
                    {
                        try
                        {
                            result = mo[wmiProperty].ToString();
                            break;
                        }
                        catch
                        {
                        }
                    }

                }
            }
            return result;
        }
        private string identifier(string wmiClass, string wmiProperty)
        //Return a hardware identifier
        {
            string result = "";
            System.Management.ManagementClass mc = new System.Management.ManagementClass(wmiClass);
            System.Management.ManagementObjectCollection moc = mc.GetInstances();
            foreach (System.Management.ManagementObject mo in moc)
            {

                //Only get the first one
                if (result == "" && mo[wmiProperty] != null)
                {
                    try
                    {
                        result = mo[wmiProperty].ToString();
                        break;
                    }
                    catch (Exception e)
                    {
                        Console.WriteLine(e.Message);
                    }
                }

            }
            return result;
        }

        private string cpuId()
        {
            //Uses first CPU identifier available in order of preference
            //Don't get all identifiers, as very time consuming
            string retVal = identifier("Win32_Processor", "UniqueId");
            if (retVal == "") //If no UniqueID, use ProcessorID
            {
                retVal = identifier("Win32_Processor", "ProcessorId");

                if (retVal == "") //If no ProcessorId, use Name
                {
                    retVal = identifier("Win32_Processor", "Name");


                    if (retVal == "") //If no Name, use Manufacturer
                    {
                        retVal = identifier("Win32_Processor", "Manufacturer");
                    }

                    //Add clock speed for extra security
                    retVal += identifier("Win32_Processor", "MaxClockSpeed");
                }
            }

            return retVal;

        }
        private string biosId()
        //BIOS Identifier
        {
            return identifier("Win32_BIOS", "Manufacturer")
            + identifier("Win32_BIOS", "SMBIOSBIOSVersion")
            + identifier("Win32_BIOS", "IdentificationCode")
            + identifier("Win32_BIOS", "SerialNumber")
            + identifier("Win32_BIOS", "ReleaseDate")
            + identifier("Win32_BIOS", "Version");
        }
        private string diskId()
        //Main physical hard drive ID
        {
            return identifier("Win32_DiskDrive", "Model")
            + identifier("Win32_DiskDrive", "Manufacturer")
            + identifier("Win32_DiskDrive", "Signature")
            + identifier("Win32_DiskDrive", "TotalHeads");
        }
        private string baseId()
        //Motherboard ID
        {
            return identifier("Win32_BaseBoard", "Model")
            + identifier("Win32_BaseBoard", "Manufacturer")
            + identifier("Win32_BaseBoard", "Name")
            + identifier("Win32_BaseBoard", "SerialNumber");
        }
        private string videoId()
        //Primary video controller ID
        {
            return identifier("Win32_VideoController", "DriverVersion")
            + identifier("Win32_VideoController", "Name");
        }
        private string macId()
        //First enabled network card ID
        {
            return identifier("Win32_NetworkAdapterConfiguration", "MACAddress", "IPEnabled");
        }
        private string pack(string text)
        //Packs the string to 8 digits
        {
            string retVal;
            int x = 0;
            int y = 0;
            foreach (char n in text)
            {
                y++;
                x += (n * y);
            }

            retVal = x.ToString() + "00000000";

            return retVal.Substring(0, 8);
        }

    }
}
