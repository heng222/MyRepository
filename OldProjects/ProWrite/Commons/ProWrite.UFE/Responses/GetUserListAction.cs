using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ProWrite.UFE.Entity;

namespace ProWrite.UFE.Responses
{
    class GetUserListAction:UFEAction
    {
        protected override void HandleResponseSuccess(UFEPacket resp)
        {
            if (Controller != null)
            {
                Controller.Connection.Users = serializer.ConvertToType<List<User>>(resp.Content);
            }
            base.HandleResponseSuccess(resp);
        }
    }
}
