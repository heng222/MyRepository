//---------------------------------------------------------------------
//
// File: GenerateKey.cs
//
// Description:
// The class of safe
//
// Author: Terry
//
// Copyright (C) 2008 by Trans-Lux All rights reserved.
// Terry 2008-6-26 添加部分注释 
//---------------------------------------------------------------------
using System;
using System.Collections.Generic;
using System.Management;
using System.Security.Cryptography;
using System.Text;
using System.IO;

namespace ProWrite.Core
{
    /// <summary>
    /// The class of safe
    /// </summary>
	public class Safe:IDisposable
	{
        const string KEY_64 = "VavicApp";
        const string IV_64 = "VavicApp";
        private SymmetricAlgorithm mobjCryptoService;
        private string Key;
        public Safe()
        {
            mobjCryptoService = new RijndaelManaged();
            Key = "lijianfufaicaixiaoke";
        }
        /**/
        /// <summary>
        /// 获得密钥
        /// </summary>
        /// <returns>密钥</returns>
        private byte[] GetLegalKey()
        {
            string sTemp = Key;
            mobjCryptoService.GenerateKey();
            byte[] bytTemp = mobjCryptoService.Key;
            int KeyLength = bytTemp.Length;
            if (sTemp.Length > KeyLength)
                sTemp = sTemp.Substring(0, KeyLength);
            else if (sTemp.Length < KeyLength)
                sTemp = sTemp.PadRight(KeyLength, ' ');
            return ASCIIEncoding.ASCII.GetBytes(sTemp);
        }
        /**/
        /// <summary>
        /// 获得初始向量IV
        /// </summary>
        /// <returns>初试向量IV</returns>
        private byte[] GetLegalIV()
        {
            string sTemp = "caoxiaokeailijianfu";
            mobjCryptoService.GenerateIV();
            byte[] bytTemp = mobjCryptoService.IV;
            int IVLength = bytTemp.Length;
            if (sTemp.Length > IVLength)
                sTemp = sTemp.Substring(0, IVLength);
            else if (sTemp.Length < IVLength)
                sTemp = sTemp.PadRight(IVLength, ' ');
            return ASCIIEncoding.ASCII.GetBytes(sTemp);
        }
        /**/
        /// <summary>
        /// 加密方法
        /// </summary>
        /// <param name="Source">待加密的串</param>
        /// <returns>经过加密的串</returns>
        public string Encrypto(string Source)
        {
            byte[] bytIn = UTF8Encoding.UTF8.GetBytes(Source);
            mobjCryptoService.Key = GetLegalKey();
            mobjCryptoService.IV = GetLegalIV();

            using (ICryptoTransform encrypto = mobjCryptoService.CreateEncryptor())
            using (MemoryStream ms = new MemoryStream())
            using (CryptoStream cs = new CryptoStream(ms, encrypto, CryptoStreamMode.Write))
            {
                cs.Write(bytIn, 0, bytIn.Length);
                cs.FlushFinalBlock();
                ms.Close();
                byte[] bytOut = ms.ToArray();
                return BitConverter.ToString(bytOut);
            }
        }
        /**/
        /// <summary>
        /// 解密方法
        /// </summary>
        /// <param name="Source">待解密的串</param>
        /// <returns>经过解密的串</returns>
        public string Decrypto(string Source)
        {
            byte[] bytIn = BitStr_ToBytes(Source);
            mobjCryptoService.Key = GetLegalKey();
            mobjCryptoService.IV = GetLegalIV();
            using (MemoryStream ms = new MemoryStream(bytIn, 0, bytIn.Length))
            using (ICryptoTransform encrypto = mobjCryptoService.CreateDecryptor())
            using (CryptoStream cs = new CryptoStream(ms, encrypto, CryptoStreamMode.Read))
            using (StreamReader sr = new StreamReader(cs))
                return sr.ReadToEnd();
        }

        static public byte[] BitStr_ToBytes(string bit_str)
        {
            string[] arrSplit = new string[16];
            for (int i = 0; i < bit_str.Length; i = i + 2)
            {
                arrSplit[i / 2] = bit_str.Substring(i, 2);
            }
            byte[] byteTemp = new byte[arrSplit.Length];
            for (int i = 0; i < byteTemp.Length; i++)
            {
                byteTemp[i] = byte.Parse(arrSplit[i], System.Globalization.NumberStyles.AllowHexSpecifier);
            }
            return byteTemp;
        }

        /// <summary>
        /// MD5 16-bit encryption
        /// </summary>
        /// <param name="ConvertString"></param>
        /// <returns></returns>
        public static string GetMd5Str(string ConvertString)
        {
            using (MD5CryptoServiceProvider md5 = new MD5CryptoServiceProvider())
                return BitConverter.ToString(md5.ComputeHash(UTF8Encoding.Default.GetBytes(ConvertString)), 4, 8).Replace("-", "");
        }

        /// <summary>
        /// Kevin - 2008-9-24 Added
        /// </summary>
        /// <param name="str"></param>
        /// <returns></returns>
        public static string MD5Encrpyt(string str)
        {
            if (string.IsNullOrEmpty(str))
                return null;
            byte[] toCompute = Encoding.Unicode.GetBytes(str);
            using (MD5CryptoServiceProvider md5 = new MD5CryptoServiceProvider())
            {
                byte[] hashed = md5.ComputeHash(toCompute, 0, toCompute.Length);
                return Convert.ToBase64String(hashed);
            }
        }
        /// <summary>
        /// MD5 32-bit encryption
        /// </summary>
        /// <param name="str"></param>
        /// <returns></returns>
        static string UserMd5(string str)
        {
            string cl = str;
            string pwd = "";
            
            // After the encryption is a byte array type　
            byte[] s = null;
            using (MD5 md5 = MD5.Create())
                s = md5.ComputeHash(Encoding.UTF8.GetBytes(cl));

            // Will types of bytes array conversion to a string
            for (int i = 0; i < s.Length; i++)
            {
                pwd = pwd + s[i].ToString("X");
            }
            return pwd;
        }
        /// <summary>
        /// Get cupID
        /// </summary>
        /// <returns></returns>
        public static string GetCpuID()
        {
            try
            {
                using (ManagementClass mc = new ManagementClass("Win32_Processor"))
                using (ManagementObjectCollection moc = mc.GetInstances())
                {
                    string strCpuID = null;
                    foreach (ManagementObject mo in moc)
                    {
                        strCpuID = mo.Properties["ProcessorId"].Value.ToString();
                        break;
                    }
                    moc.Dispose();
                    mc.Dispose();
                    return strCpuID;
                }
            }
            catch
            {
                return "";
            }
        }

        /// <summary>
        /// DES 32-bit encryption
        /// </summary>
        /// <param name="data">Encryption string</param>
        /// <returns></returns>
        public static string Encode(string data)
        {
            byte[] byKey = System.Text.ASCIIEncoding.ASCII.GetBytes(KEY_64);
            byte[] byIV = System.Text.ASCIIEncoding.ASCII.GetBytes(IV_64);

            using (DESCryptoServiceProvider cryptoProvider = new DESCryptoServiceProvider())
            using (MemoryStream ms = new MemoryStream())
            using (CryptoStream cst = new CryptoStream(ms, cryptoProvider.CreateEncryptor(byKey, byIV), CryptoStreamMode.Write))
            using (StreamWriter sw = new StreamWriter(cst))
            {
                sw.Write(data);
                sw.Flush();
                cst.FlushFinalBlock();
                sw.Flush();
                string result = Convert.ToBase64String(ms.GetBuffer(), 0, (int)ms.Length);
                sw.Dispose();
                cst.Dispose();
                ms.Dispose();
                return result;
            }
            //return  BitConverter.ToString(ms.GetBuffer(), 0, (int)ms.Length);

        }

        /// <summary>
        /// DES Decryption
        /// </summary>
        /// <param name="data">Decryption string</param>
        /// <returns></returns>
        public static string Decode(string data)
        {
            byte[] byKey = System.Text.ASCIIEncoding.ASCII.GetBytes(KEY_64);
            byte[] byIV = System.Text.ASCIIEncoding.ASCII.GetBytes(IV_64);

            byte[] byEnc;
            try
            {
                byEnc = Convert.FromBase64String(data);
            }
            catch
            {
                return null;
            }

            using(DESCryptoServiceProvider cryptoProvider = new DESCryptoServiceProvider())
            using (MemoryStream ms = new MemoryStream(byEnc))
            using (CryptoStream cst = new CryptoStream(ms, cryptoProvider.CreateDecryptor(byKey, byIV), CryptoStreamMode.Read))
            using (StreamReader sr = new StreamReader(cst))
            {
                return sr.ReadToEnd();
            }
        }

        /// <summary>
        /// 加密原函数
        /// </summary>
        /// <param name="pToEncrypt"></param>
        /// <param name="sKey"></param>
        /// <returns></returns>
        public static  string DesEncrypt(string pToEncrypt, string sKey)
        {
            DESCryptoServiceProvider des = new DESCryptoServiceProvider();
            byte[] inputByteArray = Encoding.Default.GetBytes(pToEncrypt);
            des.Key = ASCIIEncoding.ASCII.GetBytes(sKey);
            des.IV = ASCIIEncoding.ASCII.GetBytes(sKey);
            MemoryStream ms = new MemoryStream();
            CryptoStream cs = new CryptoStream(ms, des.CreateEncryptor(), CryptoStreamMode.Write);
            cs.Write(inputByteArray, 0, inputByteArray.Length);
            cs.FlushFinalBlock();
            StringBuilder ret = new StringBuilder();
            foreach (byte b in ms.ToArray())
            {
                ret.AppendFormat("{0:X2}", b);
            }
            ret.ToString();
            return ret.ToString();
            //return a;
        }
        /// <summary>
        /// 解密原函数
        /// </summary>
        /// <param name="pToDecrypt"></param>
        /// <param name="sKey"></param>
        /// <returns></returns>
        public static string DesDecrypt(string pToDecrypt, string sKey)
        {
            DESCryptoServiceProvider des = new DESCryptoServiceProvider();
            byte[] inputByteArray = new byte[pToDecrypt.Length / 2];
            for (int x = 0; x < pToDecrypt.Length / 2; x++)
            {
                int i = (Convert.ToInt32(pToDecrypt.Substring(x * 2, 2), 16));
                inputByteArray[x] = (byte)i;
            }
            des.Key = ASCIIEncoding.ASCII.GetBytes(sKey);
            des.IV = ASCIIEncoding.ASCII.GetBytes(sKey);
            MemoryStream ms = new MemoryStream();
            CryptoStream cs = new CryptoStream(ms, des.CreateDecryptor(), CryptoStreamMode.Write);
            cs.Write(inputByteArray, 0, inputByteArray.Length);
            cs.FlushFinalBlock();
            StringBuilder ret = new StringBuilder();
            return System.Text.Encoding.Default.GetString(ms.ToArray());
        }



        #region IDisposable Members

        public void Dispose()
        {
            if (this.mobjCryptoService != null)
            {
                IDisposable disp = mobjCryptoService as IDisposable;
                if (disp != null)
                    disp.Dispose();
                mobjCryptoService = null;
            }
        }

        #endregion
    }
}
