using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ProWrite.UFE.Files;
using ProWrite.Entity.Library;
using ProWrite.UI.Controls.Actions.UFE.Requests;

namespace ProWrite.UFE.Test.Upload
{
    public abstract class UploadBaseTest:ConnectionTestBase
    {
        private UploadAction action = null;
        public UploadBaseTest()
        {
            Address = "10.10.65.58";
            Account = "file";
        }

        
        protected override void DoPerform()
        {
            base.DoPerform();

            //if (Sign.Controller.Connection.CanLock)
            //{
            //    action = new UploadAction(Sign, Scheduler);
            //    action.SubscribeFtpEvent();

            //    action.Perform();
            //}
            
        }

        protected abstract SchedulerInfo Scheduler { get; }

        protected override void Destroy()
        {
            base.Destroy();

            if (action != null)
                action.UnsubscribeFtpEvent();
        }
    }
}
