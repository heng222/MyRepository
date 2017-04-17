using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ProWrite.UFE.Entity;

namespace ProWrite.UFE.Responses
{
    class CreateUserAction:UFEAction
    {
        protected override void HandleResponseSuccess(UFEPacket resp)
        {
            var result = serializer.ConvertToType<User>(resp.Content);
            if (result != null)
            {
                Controller.Connection.Users.Add(result);
            }
        }
    }
}
