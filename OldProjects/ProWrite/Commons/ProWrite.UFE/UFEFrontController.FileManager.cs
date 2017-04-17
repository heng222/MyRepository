//---------------------------------------------------------------------
//
// File: FileManagerImp.cs
//
// Description:
//
//
// Author: 
//
//Modify History:
//      Jerry Xu  2009-3-6 Add method:IFileManager.DeleteFile(List<UfeFile> files)
//      Jerry Xu  2009-3-30 Update method:IFileManager.DeleteFile(ICollection files)

//
// Copyright (C) 2008 by Trans-Lux All rights reserved.
// 
//---------------------------------------------------------------------

using System;
using System.Collections.Generic;
using System.Text;
using ProWrite.UFE.Entity;
using System.Communication;
using System.Collections;
using ProWrite.Core;

namespace ProWrite.UFE
{
    public partial class UFEFrontController<TConnection>
	{
        class FileManagerImp : IFileManager
        {
            private UFEFrontController<TConnection> controller;
            public FileManagerImp(UFEFrontController<TConnection> controller)
            {
                this.controller = controller;
            }

            AsyncFuture<UFEPacket> IFileManager.GetLock()
            {
                const uint retryCount = 10;
                return controller.SendAsync(Commands.GetLock, null, retryCount);
            }

            event ReceivedHandler IFileManager.GetLockSuccessed
            {
                add { controller.ActionProcessor[Commands.GetLock].SuccessHandler += value; }
                remove { controller.ActionProcessor[Commands.GetLock].SuccessHandler -= value; }
            }

            //AsyncFuture<UFEPacket> IFileManager.UploadFile(List<UfeFile> files)
            //{
            //    Check.Require(files != null, "files != null");
            //    Check.Require(files.Count > 0, "files.Count > 0");

            //    return controller.SendAsync(Commands.UploadFile, files);
            //}

            //AsyncFuture<UFEPacket> IFileManager.DownloadFile(List<UfeFile> files)
            //{
            //    Check.Require(files != null, "files != null");
            //    Check.Require(files.Count > 0, "files.Count > 0");


            //    return controller.SendAsync(Commands.DownloadFile, files);
            //}

            AsyncFuture<UFEPacket> IFileManager.DeleteFile(ICollection files)
            {
                Check.Require(files != null, "files != null");
                Check.Require(files.Count > 0, "files.Count > 0");

                return controller.SendAsync(Commands.DeleteFile, files);
            }

            //event ReceivedHandler IFileManager.DownloadFilesSuccessed
            //{
            //    add { controller.ActionProcessor[Commands.DownloadFile].SuccessHandler += value; }
            //    remove { controller.ActionProcessor[Commands.DownloadFile].SuccessHandler -= value; }
            //}

            //event ReceivedHandler IFileManager.UploadFilesSuccessed
            //{
            //    add { controller.ActionProcessor[Commands.UploadFile].SuccessHandler += value; }
            //    remove { controller.ActionProcessor[Commands.UploadFile].SuccessHandler -= value; }
            //}

            AsyncFuture<UFEPacket> IFileManager.FreeLock()
            {
                return controller.SendAsync(Commands.FreeLock);
            }
        }
       
     }
}
