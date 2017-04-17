using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ProWrite.UFE.Entity;

namespace ProWrite.UFE.Responses
{
    class UpdateUserRoleAction:UFEAction
    {
        protected override void HandleResponseSuccess(UFEPacket resp)
        {
            var result = serializer.ConvertToType<User>(resp.Content); 
            if (result != null)
            {
                var user = Controller.Connection.Users.Find(p => { return p.Id == result.Id; });
                if (user != null)
                    user.Role = result.Role;
            }
        }
    }
}
