/*----------------------------------------------------------------
// 公司名称：请输入公司名称
// 
// 项目名称：输入项目名称
//
// 创 建 人：zhangheng
// 创建日期：2015-4-21 13:19:28 
// 邮    箱：heng222_z@163.com
//
// Copyright (C) 公司名称 2019，保留所有权利
//
//----------------------------------------------------------------*/

using System;
using System.Collections.Generic;
using System.Text;
using System.Runtime.InteropServices;
using Acl.Win32API;

namespace Products.Domain.Utility
{
    /// <summary>
    /// COM控件帮助类。
    /// </summary>
    public static class COMHelper
    {        
        private delegate int DllRegisterServer();

        /// <summary>
        /// 注册指定的DLL。
        /// </summary>
        /// <param name="comPath"></param>
        public static void RegServer(string comPath)
        {
            var dllModule = IntPtr.Zero;

            try
            {
                dllModule = Kernel32.LoadLibrary(comPath);

                var addr = Kernel32.GetProcAddress(dllModule, "DllRegisterServer");
                if (addr == IntPtr.Zero)
                {
                    throw new Exception(string.Format("没有找到文件{0}的DllRegisterServer入口点。", comPath));
                }

                // 获取DllRegisterServer函数指针。
                var dllRegFunction = (DllRegisterServer)Marshal.GetDelegateForFunctionPointer(addr,
                    typeof(DllRegisterServer));

                // 执行DllRegisterServer函数。
                var rc = dllRegFunction();
                if (rc != 0)
                {
                    throw new Exception(string.Format("DllRegisterServer返回0x{0:X}。", rc));
                }
            }
            finally
            {
                if (dllModule != IntPtr.Zero)
                {
                    Kernel32.FreeLibrary(dllModule);
                }
            }
        }

        #region "Field"
        #endregion

        #region "Constructor"
        #endregion

        #region "Properties"
        #endregion

        #region "Override methods"
        #endregion

        #region "Private methods"
        #endregion

        #region "Public methods"
        #endregion

    }

}
