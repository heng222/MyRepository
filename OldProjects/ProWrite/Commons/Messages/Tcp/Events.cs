using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Net.Sockets;
using System.Net;
using System.Runtime.Serialization;
using System.Communication;

namespace System.Net.Tcp
{
    public static class ExtensionMethods
    {

        public static void InvokeAsyncMethod(this Socket socket, Func<SocketAsyncEventArgs,bool> method, EventHandler<SocketAsyncEventArgs> callback, SocketAsyncEventArgs args, Action<Exception> errorCallback, Func<IAsyncFuture> closeSocketback)
        {
            try
            {
                if (!method(args))
                    callback.call(socket, args);
            }
            catch (SocketException ex)
            {
                if (errorCallback != null)
                    errorCallback.call(ex);
                if (closeSocketback != null)
                    closeSocketback.call();
            }
            catch (Exception ex)
            {
                if (errorCallback != null)
                    errorCallback.call(ex);
            }
        }

        public static bool IsLocalAddress(this IPAddress address)
        {
            return address.ToString() == "127.0.0.1";
        }
    }

    [Serializable]
    public class NetException : Exception
    {
        public NetException() { }
        public NetException(SocketError error)
            : base(error.ToString())
        {
            SocketError = error;
        }
        public NetException(string message) : base(message) { }
        public NetException(string message, Exception innerException) : base(message, innerException) { }
        public NetException(SerializationInfo info, StreamingContext context) : base(info, context) { }

        public SocketError SocketError { get; set; }
    }
}
