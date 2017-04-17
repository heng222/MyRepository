//---------------------------------------------------------------------
//
// File: UploadAction.cs
//      
// Description:
//      UploadAction class
//
// Author: Kevin 2008-12-17
//
// Modify History:
//      Jerry Xu 2009-1-15 Update all info resources
//      Jerry Xu 2009-1-20 Update method:Perform(),Upload()
//      Jerry Xu 2009-3-3  Update method:Perform()
//      Jerry Xu 2009-3-4  Update method:Perform(),Upload()
//      Jerry Xu 2009-3-4  Add method:GetLockBefore()
//      Jerry Xu 2009-3-6  Update method:Upload()
//      Jerry Xu 2009-3-30 Update method:Upload()
//
// Copyright (C) 2008 by Trans-Lux All rights reserved.
// 
//---------------------------------------------------------------------

using System;
using System.Collections.Generic;
using System.Communication;
using System.Linq;
using ProWrite.Core;
using ProWrite.Entity.Dashboard;
using ProWrite.Entity.Library;
using ProWrite.Resources;
using ProWrite.UFE;
using ProWrite.UFE.Entity;
using ProWrite.UFE.Files;

namespace ProWrite.UI.Controls.Actions.UFE.Requests
{
    

    public partial class UploadAction : RequestActionBase
    {
        private SignInfo _sign;
        public SignInfo Sign
        {
            get { return _sign; }
        }
        public bool IsSendMessageToSign = false;
        public string ModelType="message";
        private SchedulerInfo _scheduler;

        private IUFEFileSaver<SchedulerInfo> _scheduleSaver = new ScheduleSaver();
        private List<UfeFile> _files = new List<UfeFile>();
        private ProgressForm _waitForm;

        /// <summary>
        /// Function: Init upload uploadAction 
        /// </summary>
        /// <param name="sign">SignInfo</param>
        /// <param name="sessionInfo">SchedulerInfo:ProWrite</param>
        public UploadAction(SignInfo sign, SchedulerInfo scheduler)
        {
            ProWrite.UI.Controls.Actions.UFE.Responses.UFEResponseService.Init(sign);

            Log.Info("UploadAction Init.");
            Check.Require(sign, "sign", Check.NotNull);
            Check.Require(scheduler, "sessionInfo", Check.NotNull);


            _sign = sign;
            _scheduler = scheduler;

            _scheduleSaver.Item = _scheduler;
            _scheduleSaver.Sign = _sign;

        }

        /// <summary>
        /// Function: Do send schedule
        /// </summary>
        public override void Perform()
        {
            _IsCancel = false;
            if (_sign.Controller.Connection.State == ConnectionState.Closed)
                return;

            if (_waitForm != null)
                _waitForm.Dispose();

            _waitForm = new ProgressForm(this.Upload,Cancel, _sign);
            _waitForm.ShowModalDialog(false);


        }

        private void GetLockBefore()
        {
            var ftpMgr = _sign.Controller.Connection.FtpManager;//SFtpManager.Current;

            _waitForm.Info(Resource.GetString(Resource.Strings.UploadSchedulerConnectFTPServer));

            if (ftpMgr == null || !ftpMgr.IsConnected.HasValue || ftpMgr.IsConnected.Equals(false))
            {
                _waitForm.CancelFtp(Resource.GetString(Resource.Strings.UploadFtpServerDisConnection));
                return;
            }

            SchedulerInfo schedule = LibraryGroup.Current.Schedulers.GetByName(_scheduler.Name);
            _scheduleSaver.Item = schedule;

            _files.Clear();
            // delete old upload files
            LocalFilePathMapping.DeleteFiles();

            var task = _sign.Controller.FileManager.GetLock();

            _waitForm.Info(Resource.GetString(Resource.Strings.UploadGetLockStart));
        }

        public void SubscribeFtpEvent()
        {
            Log.Info("subScribeFtpEvent.");
            if (_sign.Controller.Connection.User.IsFtpRole)
            {
                _sign.Controller.Connection.ExceptionFired += new EventHandler<EventArgs<Exception>>(Connection_ExceptionFired);
            }
        }

        void Connection_ExceptionFired(object sender, EventArgs<Exception> e)
        {
            if (_sign.Controller.Connection.User.Status == UserStatus.Online)
            {
                _sign.Controller.FileManager.FreeLock();
            }
            _waitForm.Info(Resource.GetString(Resource.Strings.ConnectionException));
        }

        public void UnsubscribeFtpEvent()
        {
            _sign.Controller.Connection.ExceptionFired -= new EventHandler<EventArgs<Exception>>(Connection_ExceptionFired);
        }

        private bool _IsCancel;
        public void Cancel()
        {
            _IsCancel = true;
            if (AsyncFuture<UFEPacket>.Current != null)
                AsyncFuture<UFEPacket>.Current.Cancel();
        }

        public bool IsCancel
        {
            get
            {
                return _IsCancel;
            }
        }

        /// <summary>
        /// Populate libraries and delete needUpdatedItems info
        /// </summary>
        private void Upload()
        {
            GetLockBefore();

            //Task: get lock
            var getLockTask = AsyncFuture<UFEPacket>.Current;
            while (!getLockTask.IsCompleted && !_IsCancel)
                getLockTask.Wait(50);

            if (getLockTask.IsCancelled)
            {
                _waitForm.Cancel(false);
                return;
            }

            if (IsCancel)
            {
                _waitForm.SafeClose();
                return;
            }

            //get task failure
            if (!getLockTask.IsSuccessed)
            {
                if (getLockTask.Packet.ActionError != null)
                    _waitForm.Error(Resource.GetFormatString(Resource.Strings.UploadGetLockFailed, getLockTask.Packet.ActionError.Message));
                else
                    _waitForm.Error(Resource.GetString(Resource.Strings.UploadGetLockFailedNoParameter));
                return;
            }

            //_waitForm.Info("Get Lock Successed.");
            _waitForm.Info(Resource.GetString(Resource.Strings.UploadGetLockSuccessful));
            //_waitForm.Info("OnDoUpload.");
            _waitForm.Info(Resource.GetString(Resource.Strings.UploadSchedulerPopulateStart));
            try
            {
                //Populate SchedulerInfo
                _scheduleSaver.Populate();
            }
            catch (Exception ex)
            {
                //_waitForm.Error("Populate failed:" + ex.Message, ex);
                _waitForm.Error(Resource.GetFormatString(Resource.Strings.UploadSchedulerPopulateException, ex.Message), ex);
                return;
            }

            //_waitForm.Debug("schedule Saver Start.");
            _waitForm.Debug(Resource.GetString(Resource.Strings.UploadSchedulerSaveStart));
            try
            {
                //Save(Generate) SchedulerInfo
                _scheduleSaver.Save();
            }
            catch (Exception ex)
            {
                //_waitForm.Error("Schedule saved failed.", ex);
                _waitForm.Error(Resource.GetString(Resource.Strings.UploadSchedulerSaveException), ex);
                return;
            }

            if (IsCancel)
            {
                //_waitForm.Info(Resource.GetString(Resource.Strings.UploadFailed));
                //_waitForm.Close();
                _waitForm.SafeClose();
                return;
            }

            //_waitForm.Debug("schedule Saver End.");
            _waitForm.Debug(Resource.GetString(Resource.Strings.UploadSchedulerSaveEnd));

            //Save failure
            if (!_scheduleSaver.IsSaveSucessed)
            {
                //_waitForm.Error("Schedule Saved Failed.");
                _waitForm.Error(Resource.GetString(Resource.Strings.UploadSchedulerSaveFailed));
                return;
            }

            List<UfeFile> deleteItems = _scheduleSaver.DeletedItems;
            if (deleteItems != null && deleteItems.Count > 0)
            {
                var items = from item in deleteItems
                            select new { Id = item.Id, Type = item.Type };
                var deleteTask = _sign.Controller.FileManager.DeleteFile(items.ToArray());

                while (!deleteTask.IsCompleted && !_IsCancel)
                    deleteTask.Wait(50);

                if (deleteTask.IsCancelled)
                {
                    _waitForm.Cancel(false);
                    return;
                }

                if (IsCancel)
                {
                    //_waitForm.Info(Resource.GetString(Resource.Strings.UploadFailed));
                    //IsCancel = false;
                    _waitForm.SafeClose();
                    return;
                }

                //get task failure
                if (!deleteTask.IsSuccessed)
                {
                    //_waitForm.Error("Get lock Failed:" + getLockTask.Packet.ActionError.Message);
                    //if(_sign.Controller.Connection.State== ConnectionState.Opened && _sign.Controller.Connection.User.Status == UserStatus.Online)
                    //    MsgBox.Information(Resource.GetString(Resource.Strings.GetLockFailure));
                    //if (getLockTask.Packet.ActionError != null)
                    //    _waitForm.Error(Resource.GetFormatString(Resource.Strings.UploadGetLockFailed, getLockTask.Packet.ActionError.Message));
                    //else
                    //    _waitForm.Error(Resource.GetString(Resource.Strings.UploadGetLockFailedNoParameter));
                    return;
                }
            }


            _files = _scheduleSaver.Files;
            int count = _files.Count;

            if (count < 1)
            {
                //_waitForm.Error("Schedule is empty!");
                _waitForm.Error(Resource.GetString(Resource.Strings.UploadSchedulerEmpty));
                return;
            }

            var libFiles = new List<UfeFile>();

            //Get library files
            foreach (var item in _files)
                if (item.Type >= FileType.Message)
                    libFiles.Add(item);

            if (libFiles.Count < 1)
            {
                //_waitForm.Error("Library file count == null.");
                _waitForm.Error(Resource.GetString(Resource.Strings.UploadSchedulerLibraryFileEmpty));
                return;
            }

            //Upload library files command
            //_waitForm.Info("Do Upload Start.");
            _waitForm.Info(Resource.GetString(Resource.Strings.UploadSchedulerUploadStart));

            _sign.Controller.SendAsync(Commands.UploadFile, p =>
            {
                _waitForm.EnabledCancelButton = false;
                InternalUploadCallback(p);

            }, libFiles);


        }

        private void InternalUploadCallback(IAsyncContext<UFEPacket> ctx)
        {
            if (IsCancel)
            {
                //_waitForm.Info(Resource.GetString(Resource.Strings.UploadFailed));
                _waitForm.Close();
                return;
            }

            if (!ctx.IsSuccessed)
            {
                //_waitForm.Error("Upload failed." + task.Packet.ActionError.Message, task.Exception);
                string errText = null;
                if (ctx.Exception != null)
                {
                    if (ctx.Packet.ActionError != null && !string.IsNullOrEmpty(ctx.Packet.ActionError.Message))
                        _waitForm.Error(Resource.GetFormatString(Resource.Strings.UploadSchedulerUploadException, ctx.Packet.ActionError.Message), ctx.Exception);
                    else
                        _waitForm.Error(Resource.GetString(Resource.Strings.UploadFailed), ctx.Exception);
                }
                else
                {
                    if (ctx.Packet.ActionError != null && !string.IsNullOrEmpty(ctx.Packet.ActionError.Message))
                        _waitForm.Error(Resource.GetFormatString(Resource.Strings.UploadSchedulerUploadException, ctx.Packet.ActionError.Message), null);
                    else
                        _waitForm.Error(Resource.GetString(Resource.Strings.UploadFailed), null);
                }
                return;
            }

            //Upload all files
            //_waitForm.Info("ftpMgr Upload start.");
            _waitForm.Info(Resource.GetString(Resource.Strings.UploadSchedulerUploadFtpStart));
            if (_sign.Controller.Connection.FtpManager == null || !_sign.Controller.Connection.FtpManager.IsConnected.HasValue)
            {
                _waitForm.Error(Resource.GetString(Resource.Strings.UploadFtpServerDisConnection));
                return;
            }
            foreach (var item in _files)
            {
                if (!PutFile(item))
                    return;
            };
            //_waitForm.Info("ftpMgr Upload End.");
            _waitForm.Info(Resource.GetString(Resource.Strings.UploadSchedulerUploadFtpEnd));
            _waitForm.EnabledCancelButton = true;

            const int UploadMode = 1;
            _sign.Controller.SendAsync(Commands.UploadFileCompleted, p =>
                {
                    if (IsCancel)
                    {
                        _waitForm.Close();
                        return;
                    }

                    //Task: upload all files complete.
                    if (ctx.IsSuccessed&&p.IsSuccessed)
                    //_waitForm.Success("Upload Success.");
                    {
                        if (IsSendMessageToSign)
                        {
                            _waitForm.Success(Resources.Resource.GetFormatString(Resources.Resource.Strings.UpLoadMessageSuccessful,ModelType,ControlService.SignCombo.Current.Name));
                            IsSendMessageToSign = false;
                        }
                        else
                            _waitForm.Success(Resource.GetString(Resource.Strings.UploadSchedulerUploadSuccessful));
                    }
                    else
                        //_waitForm.Error("Upload failed." + task.Packet.ActionError.Message, task.Exception);
                        _waitForm.Error(Resource.GetFormatString(Resource.Strings.UploadSchedulerUploadException, ctx.Packet.ActionError.Message), ctx.Exception);
                }, UploadMode);
        }

        private bool PutFile(UfeFile item)
        {
            //_waitForm.Info("Begin upload - " + item.Type + " - " + item.Name + " - " + item.ToFilePath);
            _waitForm.Info(Resource.GetFormatString(Resource.Strings.UploadSchedulerUploadFtpFileStart, " - " + item.Type + " - " + item.Name + " - " + item.ToFilePath));
            try
            {
                _sign.Controller.Connection.FtpManager.Put(item.FromFilePath, item.ToFilePath);
                //_waitForm.Info("End upload - " + item.Type + " - " + item.Name + " - " + item.ToFilePath);
                _waitForm.Info(Resource.GetFormatString(Resource.Strings.UploadSchedulerUploadFtpFileEnd, " - " + item.Type + " - " + item.Name + " - " + item.ToFilePath));
                return true;
            }
            catch (Exception ex)
            {
                //_waitForm.Error("upload failed - " + item.Type + " - " + item.Name + " - " + item.ToFilePath,ex);
                //_waitForm.Error(Resource.GetFormatString(Resource.Strings.UploadSchedulerUploadFtpFileException, " - " + item.Type + " - " + item.Name + " - " + item.ToFilePath), ex);
                //_waitForm.Error(Resource.GetFormatString(Resource.Strings.UploadFailed), ex);
                _waitForm.Error(Resource.GetFormatString(Resource.Strings.UploadFailed), ex);
                return false;
            }
        }
    }
}
