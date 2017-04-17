using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Communication;

namespace ProWrite.UFE
{
    public class UFEFilter:FilterBase<UFEPacket>
    {
        public override void DoFilter(UFEPacket packet)
        {
        }
    }

    public class UFEFilterProcessor : FilterProcessorBase<UFEFilter, UFEPacket>
    {
        public override void Process(UFEPacket packet)
        {
        }
    }

}
