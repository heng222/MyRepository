using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ProWrite.UFE.Entity;
using ProWrite.Core;

namespace ProWrite.UFE.Responses
{
    class ChangePasswordAction:UFEAction
    {
        protected override void HandleResponseSuccess(UFEPacket resp)
        {
            if (resp.Content != null)
            {
                var id = resp.Content.GetProperty<int>("UserId");
                var pwd = resp.Content.GetProperty<string>("Password");

                var user = Controller.Connection.Users.Find(p => { return p.Id == id; });
                if (user != null)
                    user.NoSecurityPWD = pwd;
            }
        }
    }
}
