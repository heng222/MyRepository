using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ProWrite.UFE.Responses;
using log4net;
using System.Communication;
using ProWrite.Core;

namespace ProWrite.UFE
{
    public interface IUFEActionProcessor : IActionProcessor<IUFEAction, UFEPacket>
    {
    }

    public class UFEActionProcessor : ActionProcessorBase<IUFEAction, UFEPacket>, IActionProcessor<IUFEAction, UFEPacket>
    {
        private Dictionary<Commands, IUFEAction> _actions;
        public UFEActionProcessor()
        {
            _actions = new Dictionary<Commands, IUFEAction>();
        }

        public IUFEFrontController FrontController { get; internal set; }

        public override void Process(UFEPacket resp)
        {
            if (resp == null)
                return;

            IUFEAction action = null;
            lock (resp)
            {
                _actions.TryGetValue(resp.Command, out action);
                if (action == null)
                {
                    //if (resp.Id > 0)
                    //    AsyncFuture<UFEPacket>.OnCompleted(resp);
                    //_log.Warn("No registry [" + resp.Command + "] command action");
                    return;
                }

                //_log.Info("Begin handle [" + resp.Command.ToString() + "]  command");
                action.Perform(resp);
                //_log.Info("End handle [" + resp.Command.ToString() + "]  command");
            }
        }

        public override void Destroy()
        {
            _actions.Clear();
        }

        public void AddAction(Commands cmd, IUFEAction action)
        {
            if (!_actions.ContainsKey(cmd))
                _actions[cmd] = action;
        }

        public override void Init()
        {
            //_actions[Commands.GetSignInfo] = new UFEAction { Controller = FrontController };
            //_actions[Commands.Login] = new ProWrite.UFE.Responses.LoginAction { Controller = FrontController };
            _actions[Commands.ChangePassword] = new ChangePasswordAction { Controller = FrontController };
            _actions[Commands.CreateUser] = new CreateUserAction { Controller = FrontController };
            _actions[Commands.DeleteUser] = new DeleteUserAction { Controller = FrontController };
            _actions[Commands.GetUserList] = new GetUserListAction { Controller = FrontController };
            _actions[Commands.UpdateUserRole] = new UpdateUserRoleAction { Controller = FrontController };
            //_actions[Commands.Logoff] = new LogoffAction { Controller = FrontController }; ;

            //_actions[Commands.GetLock] = new GetLockAction { Controller = FrontController };
            //_actions[Commands.UploadFile] = new FileUploadAction { Controller = FrontController };
            //_actions[Commands.UploadFileCompleted] = new UFEAction { Controller = FrontController };
            _actions[Commands.DownloadFile] = new UFEAction { Controller = FrontController };
            //_actions[Commands.GetFileList] = new UFEAction { Controller = FrontController };
            //_actions[Commands.FreeLock] = new FreeLockAction { Controller = FrontController };
            //_actions[Commands.DeleteFile] = new UFEAction { Controller = FrontController };

            _actions[Commands.GetLog] = new UFEAction { Controller = FrontController };
            _actions[Commands.ClearLog] = new UFEAction { Controller = FrontController };

            //_actions[Commands.InitSetup] = new UFEAction { Controller = FrontController };
            _actions[Commands.GetStatus] = new UFEAction { Controller = FrontController };
            //_actions[Commands.GetHealthStatus] = new UFEAction { Controller = FrontController };
            //_actions[Commands.GetLiveState] = new UFEAction { Controller = FrontController };
            //_actions[Commands.GoLive] = new UFEAction { Controller = FrontController };
            //_actions[Commands.GetQueueList] = new UFEAction { Controller = FrontController };
            //_actions[Commands.QueueList] = new UFEAction { Controller = FrontController };
            //_actions[Commands.GetRendererState] = new UFEAction { Controller = FrontController };
            _actions[Commands.RebootCXC] = new UFEAction { Controller = FrontController };
            _actions[Commands.SetDateTime] = new UFEAction { Controller = FrontController };
            _actions[Commands.Dimming] = new UFEAction { Controller = FrontController };
            _actions[Commands.TempOffset] = new UFEAction { Controller = FrontController };
            _actions[Commands.Play] = new UFEAction { Controller = FrontController };
            _actions[Commands.PlayCompleted] = new UFEAction { Controller = FrontController };
            _actions[Commands.SkipQueueMessage] = new UFEAction { Controller = FrontController };
            _actions[Commands.ClearQueueMessage] = new UFEAction { Controller = FrontController };
            _actions[Commands.StartRender] = new UFEAction { Controller = FrontController };
            _actions[Commands.StopRender] = new UFEAction { Controller = FrontController };
            _actions[Commands.LoadScheduler] = new UFEAction { Controller = FrontController };
            _actions[Commands.Diagnostics] = new UFEAction { Controller = FrontController };

            //_actions[Commands.RefreshSignImage] = new UFEAction { Controller = FrontController };
            _actions[Commands.BlankSign] = new UFEAction { Controller = FrontController };
            _actions[Commands.TestPattern] = new UFEAction { Controller = FrontController };
        }

        public bool Contains(Commands cmd)
        {
            return _actions.ContainsKey(cmd);
        }

        public IUFEAction this[Commands cmd]
        {
            get
            {
                IUFEAction action = null;
                _actions.TryGetValue(cmd, out action);
                return action;
            }
            set
            {
                if (!_actions.ContainsKey(cmd))
                {
                    Check.Require(value, "value", Check.NotNull);
                    _actions[cmd] = value;
                }
                
            }
        }
    }
}
