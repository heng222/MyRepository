/*----------------------------------------------------------------
// 公司名称：请输入公司名称
// 
// 项目名称：输入项目名称
//
// 创 建 人：zhangheng
// 创建日期：2015-2-2 10:43:04 
// 邮    箱：heng222_z@163.com
//
// Copyright (C) 公司名称 2019，保留所有权利
//
//----------------------------------------------------------------*/

using System;
using System.Windows.Forms;

using Acl.Log;

namespace Products
{
    /// <summary>
    /// Control 扩展。
    /// </summary>
    public static class ControlExtension
    {
        /// <summary>
        /// 在拥有此控件的基础窗口句柄的线程上执行指定的方法。
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
                    if (popupErrDialog) MessageBox.Show(ex.Message, "错误", MessageBoxButtons.OK, MessageBoxIcon.Error);
                }
            }));
        }

        /// <summary>
        /// 在拥有控件的基础窗口句柄的线程上，用指定的参数列表执行指定的方法。
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
                    if (popupErrDialog) MessageBox.Show(ex.Message, "错误", MessageBoxButtons.OK, MessageBoxIcon.Error);
                }
            }), args);
        }

        /// <summary>
        /// 在创建控件的基础句柄所在线程上异步执行指定的方法。
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
                    if (popupErrDialog) MessageBox.Show(ex.Message, "错误", MessageBoxButtons.OK, MessageBoxIcon.Error);
                }
            }));
        }


        /// <summary>
        /// 在创建控件的基础句柄所在线程上，用指定的参数异步执行指定方法。
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
                    if (popupErrDialog) MessageBox.Show(ex.Message, "错误", MessageBoxButtons.OK, MessageBoxIcon.Error);
                }
            }), args);
        }
    }
}
