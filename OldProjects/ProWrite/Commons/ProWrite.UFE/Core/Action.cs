using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using log4net;
using System.ComponentModel;
using System.Windows.Forms;
using System.Communication;

namespace ProWrite.UFE
{
    public interface IUFEAction : IAction<UFEPacket>
    {
        ReceivedHandler SuccessHandler { get; set; }
        ReceivedHandler FailHandler { get; set; }
    }

    public class UFEAction : ActionBase<UFEPacket>, IUFEAction
    {
        protected JsonSerializer serializer = new JsonSerializer();
        public IUFEFrontController Controller { get; set; }
        public ReceivedHandler SuccessHandler { get; set; }

        public ReceivedHandler FailHandler { get; set; }

        public static bool CheckForIllegalCrossThreadCalls
        {
            private get
            {
                return Control.CheckForIllegalCrossThreadCalls;
            }
            set
            {
                Control.CheckForIllegalCrossThreadCalls = value;
            }
        }

        protected virtual void HandleResponseSuccess(UFEPacket resp)
        {
        }

        protected virtual void HandleResponseFail(UFEPacket resp)
        {
        }

        public override void Perform(UFEPacket resp)
        {
            ReceivedHandler handler = null;
            try
            {
                if (resp != null && !resp.HasError)
                {
                    //log.Info("Perform success handler");
                    handler = SuccessHandler;
                    HandleResponseSuccess(resp);
                }
                else
                {
                    handler = FailHandler;
                    //log.Info("Perform fail handler: resp null or resp.HasError");
                    HandleResponseFail(resp);
                }

                OnHandler(resp, handler);
            }
            catch(Exception ex)
            {
                Log.Error(ex.Message, ex);
            }
        }

        protected virtual void OnHandler(UFEPacket resp, ReceivedHandler handler)
        {
            //if (resp.Id > 0)
            //{
            //    UFEFuture.OnCompleted(resp);
            //    return;
            //}

            if (handler != null)
            {
                ISynchronizeInvoke hwnd = handler.Target as ISynchronizeInvoke;
                if (hwnd != null)
                {
                    if (hwnd.InvokeRequired)
                        hwnd.Invoke(handler, new object[] { resp });
                    else
                        handler.DynamicInvoke(resp);
                }
                else
                {
                    var old = CheckForIllegalCrossThreadCalls;
                    CheckForIllegalCrossThreadCalls = false;
                    handler.DynamicInvoke(resp);
                    CheckForIllegalCrossThreadCalls = old;
                }
            }
        }

    }
}
