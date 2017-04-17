//---------------------------------------------------------------------
//
// File: BlankSignAction.cs
//
// Description:
// The uploadAction class of BlankSign
//
// Author: Terry
//
// Copyright (C) 2008 by ISoftstone Corporation.  All rights reserved.
// 
// Modify history:   
//---------------------------------------------------------------------
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ProWrite.Entity.Dashboard;
using ProWrite.UI.Controls.Actions.UFE;
using ProWrite.UFE;
using System.Communication;
using System.Net.Tcp;
using System.Net.Sockets;
using ProWrite.UI.Controls.Common;
using System.Windows.Forms;

namespace ProWrite.UI.Controls.Actions.UFE.Requests
{
    class ConnectionExceptionAction : RequestActionBase
    {
        Exception _exception;
        public static bool IsCancel = false;

        public ConnectionExceptionAction(Exception e)
        {
            _exception = e;
        }

        public override void Perform()
        {
            NetException ex = _exception as NetException;
            SocketError? errorCode = null;

            if (ex == null)
            {
                SocketException se = _exception as SocketException;
                if (se == null)
                {
                    MsgBox.Error("Sorry,connection failed,please try again");
                }
            }
            else
            {
                errorCode = ex.SocketError;
            }

            if (errorCode.HasValue)
            {
                if (errorCode == SocketError.Success)
                {
                    if (ex.Message.Trim() != "Success")
                    {
                        if (ex.Message.Contains("asyncResult"))
                            return;
                        if (ex.Message == "HostUnreachable")
                            MsgBox.Warning("Host unreachable");
                        else if (ex.Message == "TimedOut")
                            MsgBox.Warning("Unable to connect – connection timed out after multiple attempts");
                        else if (ex.Message == "ConnectionRefused")
                            MsgBox.Warning("Connection refused");
                        else
                            MsgBox.Warning(ex.Message);
                    }
                    return;
                }
                if (IsCancel)
                {
                    IsCancel = false;
                    return;
                }
                if (errorCode.Value.ToString().Contains("asyncResult"))
                    return;
                if (errorCode.Value.ToString() == "HostUnreachable")
                    MsgBox.Warning("Host unreachable");
                else if (errorCode.Value.ToString() == "TimedOut")
                    MsgBox.Warning("Unable to connect – connection timed out after multiple attempts");
                else if (ex.Message == "ConnectionRefused")
                    MsgBox.Warning("Connection Refused");
                else if (errorCode.Value.ToString() == "AddressNotAvailable")
                    MsgBox.Warning("Address or port is not available.");
                else
                    MsgBox.Warning(errorCode.Value.ToString());

                switch (errorCode.Value)
                {
                    case SocketError.AccessDenied:
                        break;
                    case SocketError.AddressNotAvailable:
                    case SocketError.HostNotFound:
                    case SocketError.HostUnreachable:
                        break;
                    case SocketError.NetworkDown:
                    case SocketError.NetworkUnreachable:
                        break;
                    case SocketError.Shutdown:
                        break;
                    case SocketError.TooManyOpenSockets:
                        break;
                }
            }
        }
    }


}
