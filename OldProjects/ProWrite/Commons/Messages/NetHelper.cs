using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;

namespace System.Net
{
    public static class NetHelper
    {
        [Flags]
        private enum ConnectionFlag
        {
            /// <summary>
            /// Local system has a valid connection to the Internet, but it might or might not be currently connected.
            /// </summary>
            INTERNET_CONNECTION_CONFIGURED = 0x40,
            /// <summary>
            /// Local system uses a local area network to connect to the Internet.
            /// </summary>
            INTERNET_CONNECTION_LAN = 0x02,
            /// <summary>
            /// Local system uses a modem to connect to the Internet.
            /// </summary>
            INTERNET_CONNECTION_MODEM = 0x01,
            /// <summary>
            /// No longer used.
            /// </summary>
            INTERNET_CONNECTION_MODEM_BUSY = 0x08,
            /// <summary>
            /// Local system is in offline mode.
            /// </summary>
            INTERNET_CONNECTION_OFFLINE = 0x20,
            /// <summary>
            /// Local system uses a proxy server to connect to the Internet.
            /// </summary>
            INTERNET_CONNECTION_PROXY = 0x04,
        }
        [DllImport("wininet.dll")]
        private extern static bool InternetGetConnectedState(out long connectionDescription, int reservedValue);

        public static bool InternetConnectedState
        {
            get
            {
                long desc;
                var state = InternetGetConnectedState(out desc, 0);
                return state;
            }
        }
    }
}
