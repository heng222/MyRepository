using System;
using System.Collections.Generic;
using System.Text;
using ProWrite.UFE.Entity;
using ProWrite.Core;
using System.Communication;

namespace ProWrite.UFE
{
    public partial class UFEFrontController<TConnection>
	{

        private class UserManagerImp:IUserManager
        {
            private UFEFrontController<TConnection> controller;
            public UserManagerImp(UFEFrontController<TConnection> controller)
            {
                this.controller = controller;
            }

            public AsyncFuture<UFEPacket> Login(string account, string password, Action<IAsyncContext<UFEPacket>> callback)
            {
                controller.User.Account = account;
                controller.User.Password = password;
                return controller.SendAsync(Commands.Login,callback, new { Account = controller.User.Account, Password = controller.User.Password });
            }

            public AsyncFuture<UFEPacket> ChangePassword(int userId, string newPwd, Action<IAsyncContext<UFEPacket>> callback)
            {
                return controller.SendAsync(Commands.ChangePassword, callback, new { UserId = userId, Password = Safe.MD5Encrpyt(newPwd) });
            }

            public AsyncFuture<UFEPacket> CreateUser(string account, string pwd, Role role, Action<IAsyncContext<UFEPacket>> callback)
            {
                return controller.SendAsync(Commands.CreateUser, callback, new { Account = account, Password = Safe.MD5Encrpyt(pwd), Role = role });
            }


            public AsyncFuture<UFEPacket> DeleteUser(int userId, Action<IAsyncContext<UFEPacket>> callback)
            {
                return controller.SendAsync(Commands.DeleteUser, callback, userId);
            }

            public AsyncFuture<UFEPacket> UpdateUserRole(int userId, Role newRole, Action<IAsyncContext<UFEPacket>> callback)
            {
                return controller.SendAsync(Commands.UpdateUserRole, callback, new { UserId = userId, Role = newRole });
            }

            public AsyncFuture<UFEPacket> Logoff()
            {
                return controller.SendAsync(Commands.Logoff);
            }

            #region Events
            
            event ReceivedHandler IUserManager.ChangePasswordSuccessed
            {
                add { controller.ActionProcessor[Commands.ChangePassword].SuccessHandler += value; }
                remove { controller.ActionProcessor[Commands.ChangePassword].SuccessHandler -= value; }
            }

            event ReceivedHandler IUserManager.CreateUserSuccessed
            {
                add { controller.ActionProcessor[Commands.CreateUser].SuccessHandler += value; }
                remove { controller.ActionProcessor[Commands.CreateUser].SuccessHandler -= value; }
            }


            event ReceivedHandler IUserManager.DeleteUserSuccessed
            {
                add { controller.ActionProcessor[Commands.DeleteUser].SuccessHandler += value; }
                remove { controller.ActionProcessor[Commands.DeleteUser].SuccessHandler -= value; }
            }

            event ReceivedHandler IUserManager.UpdateUserRoleSuccessed
            {
                add { controller.ActionProcessor[Commands.UpdateUserRole].SuccessHandler += value; }
                remove { controller.ActionProcessor[Commands.UpdateUserRole].SuccessHandler -= value; }
            }
            #endregion
        }
    }
}
