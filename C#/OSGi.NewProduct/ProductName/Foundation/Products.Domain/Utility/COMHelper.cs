/*----------------------------------------------------------------
// ��˾���ƣ������빫˾����
// 
// ��Ŀ���ƣ�������Ŀ����
//
// �� �� �ˣ�zhangheng
// �������ڣ�2015-4-21 13:19:28 
// ��    �䣺heng222_z@163.com
//
// Copyright (C) ��˾���� 2019����������Ȩ��
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
    /// COM�ؼ������ࡣ
    /// </summary>
    public static class COMHelper
    {        
        private delegate int DllRegisterServer();

        /// <summary>
        /// ע��ָ����DLL��
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
                    throw new Exception(string.Format("û���ҵ��ļ�{0}��DllRegisterServer��ڵ㡣", comPath));
                }

                // ��ȡDllRegisterServer����ָ�롣
                var dllRegFunction = (DllRegisterServer)Marshal.GetDelegateForFunctionPointer(addr,
                    typeof(DllRegisterServer));

                // ִ��DllRegisterServer������
                var rc = dllRegFunction();
                if (rc != 0)
                {
                    throw new Exception(string.Format("DllRegisterServer����0x{0:X}��", rc));
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
