using System;
using System.Collections.Generic;
using System.Text;
using System.Reflection;
using System.Runtime.InteropServices;

namespace System.Communication.Messaging
{
    /// <summary>
    /// Message event delegate
    /// </summary>
    /// <typeparam name="TMessage"></typeparam>
    /// <param name="sender"></param>
    /// <param name="msg"></param>
    public delegate void ObserverHandler<TMessage>(object sender, TMessage msg);
}
