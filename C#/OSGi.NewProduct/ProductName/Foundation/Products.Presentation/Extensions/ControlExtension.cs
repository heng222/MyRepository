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
using System.Windows.Forms;

using Acl.Log;

namespace Products
{
    /// <summary>
    /// Control ��չ��
    /// </summary>
    public static class ControlExtension
    {
        /// <summary>
        /// ��ӵ�д˿ؼ��Ļ������ھ�����߳���ִ��ָ���ķ�����
        /// </summary>
        public static object InvokeWithCatch(this Control control, Action action, ILog log, bool popupErrDialog = false)
        {
            return control.Invoke(new Action(() =>
            {
                try
                {
                    action();
                }
                catch (Exception ex)
                {
                    if (log != null) log.Error(ex);
                    if (popupErrDialog) MessageBox.Show(ex.Message, "����", MessageBoxButtons.OK, MessageBoxIcon.Error);
                }
            }));
        }

        /// <summary>
        /// ��ӵ�пؼ��Ļ������ھ�����߳��ϣ���ָ���Ĳ����б�ִ��ָ���ķ�����
        /// </summary>
        public static object InvokeWithCatch(this Control control, Action action, ILog log, bool popupErrDialog = false, params object[] args)
        {
            return control.Invoke(new Action(() =>
            {
                try
                {
                    action();
                }
                catch (Exception ex)
                {
                    if (log != null) log.Error(ex);
                    if (popupErrDialog) MessageBox.Show(ex.Message, "����", MessageBoxButtons.OK, MessageBoxIcon.Error);
                }
            }), args);
        }

        /// <summary>
        /// �ڴ����ؼ��Ļ�����������߳����첽ִ��ָ���ķ�����
        /// </summary>
        public static IAsyncResult BeginInvokeWithCatch(this Control control, Action action, ILog log, bool popupErrDialog = false)
        {
            return control.BeginInvoke(new Action(() =>
            {
                try
                {
                    action();
                }
                catch (Exception ex)
                {
                    if (log != null) log.Error(ex);
                    if (popupErrDialog) MessageBox.Show(ex.Message, "����", MessageBoxButtons.OK, MessageBoxIcon.Error);
                }
            }));
        }


        /// <summary>
        /// �ڴ����ؼ��Ļ�����������߳��ϣ���ָ���Ĳ����첽ִ��ָ��������
        /// </summary>
        public static IAsyncResult BeginInvokeWithCatch(this Control control, Action action, ILog log, bool popupErrDialog = false, params object[] args)
        {
            return control.BeginInvoke(new Action(() =>
            {
                try
                {
                    action();
                }
                catch (Exception ex)
                {
                    if (log != null) log.Error(ex);
                    if (popupErrDialog) MessageBox.Show(ex.Message, "����", MessageBoxButtons.OK, MessageBoxIcon.Error);
                }
            }), args);
        }
    }
}
