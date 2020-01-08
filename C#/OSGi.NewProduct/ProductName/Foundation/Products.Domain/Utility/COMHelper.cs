/*----------------------------------------------------------------
// ��˾���ƣ������빫˾����
// 
// ��Ŀ���ƣ�������Ŀ����
//
// �� �� �ˣ�zhangheng
// �������ڣ�2015-4-21 13:19:28 
// ��    �䣺heng222_z@163.com
//
// Copyright (C) ��˾���� 2009����������Ȩ��
//
//----------------------------------------------------------------*/

using System;
using System.Collections.Generic;
using System.Text;
using System.Runtime.InteropServices;

namespace Products.Domain.Utility
{
    /// <summary>
    /// COM�ؼ������ࡣ
    /// </summary>
    public static class COMHelper
    {
        [System.Diagnostics.CodeAnalysis.SuppressMessage("Microsoft.Design", "CA1060:MovePInvokesToNativeMethodsClass"), DllImport("Kernel32.dll")]
        private static extern IntPtr LoadLibrary(string lpFileName);

        [System.Diagnostics.CodeAnalysis.SuppressMessage("Microsoft.Design", "CA1060:MovePInvokesToNativeMethodsClass"), DllImport("kernel32.dll", SetLastError = true)]
        private static extern IntPtr GetProcAddress(IntPtr hModule, string lpProcName);

        [System.Diagnostics.CodeAnalysis.SuppressMessage("Microsoft.Design", "CA1060:MovePInvokesToNativeMethodsClass"), DllImport("kernel32.dll", EntryPoint = "FreeLibrary", SetLastError = true)]
        [return: MarshalAs(UnmanagedType.Bool)]
        private static extern bool FreeLibrary(IntPtr hModule);
        
        //
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
                dllModule = LoadLibrary(comPath);

                var addr = GetProcAddress(dllModule, "DllRegisterServer");
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
                    FreeLibrary(dllModule);
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
