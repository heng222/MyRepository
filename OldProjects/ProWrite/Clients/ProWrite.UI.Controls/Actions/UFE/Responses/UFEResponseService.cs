using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ProWrite.UFE;
using ProWrite.Entity.Dashboard;
using ProWrite.Core;

namespace ProWrite.UI.Controls.Actions.UFE.Responses
{
    public static class UFEResponseService
    {
        
        public static void Init(SignInfo sign)
        {
            
            var controller = sign.Controller;
            var actionProcessor = controller.ActionProcessor;

            if (!actionProcessor.Contains(Commands.GetSignInfo))
            {
                ProxyAction action = new GetSignInfoAction { Controller = controller };
                actionProcessor.AddAction(action.Id, action);

                action = new LoginAction { Controller = controller };
                actionProcessor.AddAction(action.Id, action);

                action = new LogoffAction { Controller = controller };
                actionProcessor.AddAction(action.Id, action);

                action = new GetLockAction { Controller = controller };
                actionProcessor.AddAction(action.Id, action);

                action = new FreeLockAction { Controller = controller };
                actionProcessor.AddAction(action.Id, action);

                action = new UploadFileCompletedAction { Controller = controller };
                actionProcessor.AddAction(action.Id, action);
            }

        }
    }
}
