//---------------------------------------------------------------------
//
// File: Packet.cs
//
// Description:
// Packet class
//
// Author: Kevin
// 
// Modify History:
//          Jerry Xu 2009-3-6 Add method:IFileManager DeleteFile(List<UfeFile> files);
//          Jerry Xu 2009-3-30 Update method:AsyncFuture<UFEPacket> DeleteFile(ICollection files);
//
// Copyright (C) 2008 by Trans-Lux All rights reserved.
// 
//---------------------------------------------------------------------
using System;
using System.Collections.Generic;
using System.Text;
using System.IO;
using System.Linq;
using System.Xml.Serialization;
using ProWrite.Core;
using System.Web.Script.Serialization;
using System.Runtime.Serialization;
using System.Communication;
using log4net;
using ProWrite.UFE.Responses;
using ProWrite.UFE.Entity;
using System.Collections;

namespace ProWrite.UFE
{
    public interface IUserManager
    {
        AsyncFuture<UFEPacket> Login(string account, string password, Action<IAsyncContext<UFEPacket>> callback);

        AsyncFuture<UFEPacket> ChangePassword(int userId, string newPassword, Action<IAsyncContext<UFEPacket>> callback);
        event ReceivedHandler ChangePasswordSuccessed;

        AsyncFuture<UFEPacket> CreateUser(string account, string pwd, Role role, Action<IAsyncContext<UFEPacket>> callback);
        event ReceivedHandler CreateUserSuccessed;

        AsyncFuture<UFEPacket> DeleteUser(int userId, Action<IAsyncContext<UFEPacket>> callback);
        event ReceivedHandler DeleteUserSuccessed;

        AsyncFuture<UFEPacket> UpdateUserRole(int userId, Role newRole, Action<IAsyncContext<UFEPacket>> callback);
        event ReceivedHandler UpdateUserRoleSuccessed;

        AsyncFuture<UFEPacket> Logoff();
    }

    public interface IFileManager
    {

        AsyncFuture<UFEPacket> GetLock();
        event ReceivedHandler GetLockSuccessed;

        //AsyncFuture<UFEPacket> UploadFile(List<UfeFile> files);
        //event ReceivedHandler UploadFilesSuccessed;

        //AsyncFuture<UFEPacket> DownloadFile(List<UfeFile> files);
        //event ReceivedHandler DownloadFilesSuccessed;

        AsyncFuture<UFEPacket> DeleteFile(ICollection files);

        AsyncFuture<UFEPacket> FreeLock();
        
    }

    public interface ILogManager
    {
        AsyncFuture<UFEPacket> GetLog();

        AsyncFuture<UFEPacket> ClearLog();
    }

    public interface IMAManager
    {
        AsyncFuture<UFEPacket> GetStatus();

        AsyncFuture<UFEPacket> SetDateTime(string date);

        AsyncFuture<UFEPacket> SetTempOffset(string temp);
        
        AsyncFuture<UFEPacket> SetDimming(List<DimmingSet> list);

        AsyncFuture<UFEPacket> Play(string playId, int level, int type, long regionId);
        
        event ReceivedHandler PlayCompleted;


        AsyncFuture<UFEPacket> SkipQueueMessage();

        AsyncFuture<UFEPacket> ClearQueueMessage();
        
        AsyncFuture<UFEPacket> StartRender();

        AsyncFuture<UFEPacket> StopRender();

        AsyncFuture<UFEPacket> LoadScheduler();

        AsyncFuture<UFEPacket> Diagnostics();

        AsyncFuture<UFEPacket> BlankSign();
       
        //void RefreshSignImage();

        AsyncFuture<UFEPacket> TestPattern();
    }

    public interface IUFEFrontController : IDisposable
    {
        AsyncFuture<UFEPacket> SendAsync(Commands cmd);
        AsyncFuture<UFEPacket> SendAsync(Commands cmd, object body);
        AsyncFuture<UFEPacket> SendAsync(Commands cmd, Action<IAsyncContext<UFEPacket>> callback, object body);
        AsyncFuture<UFEPacket> SendAsync(Commands cmd, Action<IAsyncContext<UFEPacket>> callback);

        IUFEConnection Connection { get; }
        ISignInfo Sign { get; }
        IUserManager UserManager { get; }
        IFileManager FileManager { get; }
        ILogManager LogManager { get; }
        IMAManager MAManager { get; }

        UFEActionProcessor ActionProcessor { get; }
    }

    public interface IUFEFrontController<TConnection>
        : IFrontController<TConnection, UFEFilterProcessor, UFEFilter, UFEActionProcessor, IUFEAction, UFEPacket>
        , IUFEFrontController
        where TConnection : IUFEConnection, new()
    {

    }
}
