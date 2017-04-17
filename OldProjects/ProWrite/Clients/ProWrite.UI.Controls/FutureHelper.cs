using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Communication;
using System.Threading;
using System.ComponentModel;
using System.Windows.Forms;
using log4net;

namespace ProWrite.UI.Controls
{
    //public static class FutureHelper
    //{
    //    private static ILog log = LogManager.GetLogger("FutureHelper");
    //    public static void Execute(this IAsyncFuture future, Action successCallback, Action failedCallback)
    //    {
    //        ThreadPool.QueueUserWorkItem(p =>
    //        {
    //            if (!future.IsCompleted)
    //                future.Wait();

    //            if (future.IsSuccessed)
    //            {
    //                if (successCallback != null)
    //                    SafeCall(successCallback, null);
    //            }
    //            else
    //            {
    //                if (failedCallback != null)
    //                    SafeCall(failedCallback, null);
    //            }
    //        }, null);
    //    }

    //    private static void SafeCall(Delegate handler, params object[] args)
    //    {
    //        if (handler != null)
    //        {
    //            try
    //            {
    //                ISynchronizeInvoke hwnd = FormHelper.ActiveForm;
    //                if (hwnd != null)
    //                {
    //                    if (hwnd.InvokeRequired)
    //                        hwnd.Invoke(handler, args);
    //                    else
    //                        handler.DynamicInvoke(args);
    //                }
    //                else
    //                {
    //                    var old = Control.CheckForIllegalCrossThreadCalls;
    //                    Control.CheckForIllegalCrossThreadCalls = false;
    //                    handler.DynamicInvoke(args);
    //                    Control.CheckForIllegalCrossThreadCalls = old;
    //                }
    //            }
    //            catch (Exception ex)
    //            {
    //                log.Error(ex.Message, ex);
    //            }
    //        }
    //    }
    //}
}
