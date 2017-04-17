using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace ProWrite.UFE.Responses
{
    class DeleteUserAction:UFEAction
    {
        protected override void HandleResponseSuccess(UFEPacket resp)
        {
            var id = serializer.ConvertToType<int>(resp.Content);
            var user = Controller.Connection.Users.Find(p => { return p.Id == id; });
            if (user != null)
            {
                Controller.Connection.Users.Remove(user);
            }
        }
    }
}
