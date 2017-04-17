//---------------------------------------------------------------------
//
// File: GenerateKey.cs
//
// Description:
// Winform of Generate Key 
//
// Author: Terry
//
// Copyright (C) 2008 by Trans-Lux All rights reserved.
// Terry 2008-6-26 添加部分注释 
//---------------------------------------------------------------------
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Management;
using Microsoft.Win32;
using System.Text.RegularExpressions;
using System.Security.Cryptography;
using System.IO;

namespace ProWrite.SerialGen
{
    /// <summary>
    /// Winform of Generate Key
    /// </summary>
    public partial class SerialGen : Form
    {
        string registerKey;
        int txtLength = 6;
        string sKey = "tracsLux";
        private static string MD5Encrpty(string source)
        {
            using (MD5CryptoServiceProvider md5 = new MD5CryptoServiceProvider())
                return BitConverter.ToString(md5.ComputeHash(Encoding.UTF8.GetBytes(source)), 4, 8).Replace("-", "");
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


        #region event

        /// <summary>
        /// Constructor
        /// </summary>
        public SerialGen()
        {
            InitializeComponent();
        }

        private void btnParse_Click(object sender, EventArgs e)
        {
            lblSalesNumber.Text = "";
            label1.Text = "";
            label2.Text = "";
            const string RegsterError = "Register Number is invalid and Please try again";
            //校验输入数据是否合法
            if (txtMone.Text.Trim() == "" || txtMtwo.Text.Trim() == "" || txtMthree.Text.Trim() == "" || txtMfour.Text.Trim() == "")
            {
                MessageBox.Show(this, RegsterError, "", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                return;
            }
            if (txtMone.Text.Trim().Length < txtLength || txtMtwo.Text.Trim().Length < txtLength || txtMthree.Text.Trim().Length < txtLength || txtMfour.Text.Trim().Length < txtLength)
            {
                MessageBox.Show(this, RegsterError, "", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                return;
            }

            var reg = txtMone.Text.ToUpper() + txtMtwo.Text.ToUpper() + txtMthree.Text.ToUpper() + txtMfour.Text.ToUpper()
               + txtMFive.Text.ToUpper() + txtMsix.Text.ToUpper() + txtMseven.Text.ToUpper() + txtMeight.Text.ToUpper();
            try
            {
                var dec = DesDecrypt(reg, sKey);
                lblSalesNumber.Text = Convert.ToInt32(dec.Substring(14, 6)).ToString();
                label2.Text = dec.Substring(6, 8);
                var date = dec.Substring(0, 6);
                date = "20" + date.Substring(0, 2) + "-" + date.Substring(2, 2) + "-" + date.Substring(4, 2);
                label1.Text = DateTime.Parse(date).ToShortDateString();
            }
            catch
            {
                MessageBox.Show(this, RegsterError, "", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                return;
            }
        }

        /// <summary>
        /// 生成序列号的按钮事件
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnCreate_Click(object sender, EventArgs e)
        {
            const string RegsterError = "Register Number is invalid and Please try again";
            //校验输入数据是否合法
            if (txtMone.Text.Trim() == "" || txtMtwo.Text.Trim() == "" || txtMthree.Text.Trim() == "" || txtMfour.Text.Trim() == "")
            {
                MessageBox.Show(this, RegsterError, "", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                return;
            }
            if (txtMone.Text.Trim().Length < txtLength || txtMtwo.Text.Trim().Length < txtLength || txtMthree.Text.Trim().Length < txtLength || txtMfour.Text.Trim().Length < txtLength)
            {
                MessageBox.Show(this, RegsterError, "", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                return;
            }
            registerKey = txtMone.Text.ToUpper() + txtMtwo.Text.ToUpper() + txtMthree.Text.ToUpper() + txtMfour.Text.ToUpper()
                 + txtMFive.Text.ToUpper() + txtMsix.Text.ToUpper() + txtMseven.Text.ToUpper() + txtMeight.Text.ToUpper();
            if (rbtnSixty.Checked)
            {
                registerKey += "60";
            }
            else if (this.rbtnFifteen.Checked)
            {
                registerKey += "15";
            }
            else if (this.rbtnTwenty.Checked)
            {
                registerKey += "20";
            }
            else if (this.rbtnThirty.Checked)
            {
                registerKey += "30";
            }
            else if (this.rbtnFoutyFive.Checked)
            {
                registerKey += "45";
            }
            else if (rbtnHelfYear.Checked)
            {
                registerKey += "180";
            }
            else
            {
                registerKey += "unlimited";
            }

            if (chkShowLivePage.Checked)
                registerKey = "$" + registerKey;
            //根据不同的选项，生成不同有效期的序列号
            string safeStr = MD5Encrpty(registerKey);
            //将生成的序列号显示在界面
            txtKey.Text = safeStr.Substring(0, 4) + " - " + safeStr.Substring(4, 4) + " - "
                          + safeStr.Substring(8, 4) + " - " + safeStr.Substring(12, 4);
        }

        /// <summary>
        /// 当文本框输入超过4个，则自动跳转到下一文本框
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void txtMone_TextChanged(object sender, EventArgs e)
        {
            if (txtMone.Text.Length == txtLength)
            {
                txtMtwo.Focus();
            }
        }

        private void txtMtwo_TextChanged(object sender, EventArgs e)
        {
            if (txtMtwo.Text.Length == txtLength)
            {
                txtMthree.Focus();
            }
        }

        private void txtMthree_TextChanged(object sender, EventArgs e)
        {
            if (txtMthree.Text.Length == txtLength)
            {
                txtMfour.Focus();
            }
        }

        /// <summary>
        /// 各个文本框的输入限制
        /// </summary>
        /// <param name="sender">sender</param>
        /// <param name="e">KeyPressEventArgs</param>
        private void txtMone_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (Convert.ToInt32(e.KeyChar) == 22)
            {
                e.Handled = false;
                var str = Clipboard.GetText();
                if (str.Length == 48)
                {
                    txtMone.Text = str.Substring(0, 6);
                    txtMtwo.Text = str.Substring(6, 6);
                    txtMthree.Text = str.Substring(12, 6);
                    txtMfour.Text = str.Substring(18, 6);
                    txtMFive.Text = str.Substring(24, 6);
                    txtMsix.Text = str.Substring(30, 6);
                    txtMseven.Text = str.Substring(36, 6);
                    txtMeight.Text = str.Substring(42, 6);
                    btnParse.Focus();
                    return;
                }
                else
                {
                    e.Handled = false;
                    return;
                }
            }
            if ((Convert.ToInt32(e.KeyChar) == txtLength))
            {
                e.Handled = false;
            }
            else
            {
                //Regex numRegex = new Regex(@"^(-?[0-9]*[.]*[0-9]*)$");
                //是否输入数字
                Regex numRegex = new Regex(@"^([0-9]*)$");
                Match Result = numRegex.Match(Convert.ToString(e.KeyChar));
                if (Result.Success)
                {
                    e.Handled = false;
                    return;
                }
                else
                {
                    bool b = true;
                    //输入十六进制的字符
                    int[] s = { 3, 22, 26, 65, 66, 67, 68, 69, 70, 97, 98, 99, 100, 101, 102 };
                    for (int i = 0; i < s.Length; i++)
                    {
                        if (Convert.ToInt32(e.KeyChar) == s[i])
                        {
                            e.Handled = false;
                            return;
                        }
                    }
                    if (b)
                    {
                        e.Handled = false;
                        return;
                    }
                }
            }
        }
        #endregion

        private void txtMfour_TextChanged(object sender, EventArgs e)
        {
            if (txtMfour.Text.Length == txtLength)
            {
                txtMFive.Focus();
            }
        }

        private void txtMFive_TextChanged(object sender, EventArgs e)
        {
            if (txtMFive.Text.Length == txtLength)
            {
                txtMsix.Focus();
            }
        }

        private void txtMsix_TextChanged(object sender, EventArgs e)
        {
            if (txtMsix.Text.Length == txtLength)
            {
                txtMseven.Focus();
            }
        }

        private void txtMseven_TextChanged(object sender, EventArgs e)
        {
            if (txtMseven.Text.Length == txtLength)
            {
                txtMeight.Focus();
            }
        }

        private void txtMeight_TextChanged(object sender, EventArgs e)
        {
            if (txtMeight.Text.Length == txtLength)
            {
                this.btnParse.Focus();
            }
        }

        private void btnCoyp_Click(object sender, EventArgs e)
        {
            if (!string.IsNullOrEmpty(txtKey.Text))
                Clipboard.SetText(txtKey.Text.Replace(" - ", "").Trim());
        }

        private void btnReset_Click(object sender, EventArgs e)
        {
            txtMone.Text = txtMtwo.Text = txtMthree.Text = txtMfour.Text = txtMFive.Text
                = txtMsix.Text = txtMseven.Text = txtMeight.Text = "";
        }

    }
}