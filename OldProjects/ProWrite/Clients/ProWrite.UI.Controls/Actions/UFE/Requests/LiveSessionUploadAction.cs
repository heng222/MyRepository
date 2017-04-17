using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ProWrite.Entity.Dashboard;
using ProWrite.Entity.Live;
using ProWrite.UFE.Files;
using ProWrite.UFE.Entity;
using ProWrite.Entity.Library;
using ProWrite.UFE;
using System.Communication;
using ProWrite.Resources;
using ProWrite.Core;

namespace ProWrite.UI.Controls.Actions.UFE.Requests
{
    public class LiveSessionUploadAction: RequestActionBase
    {
        private SignInfo _sign;
        public SignInfo Sign
        {
            get { return _sign; }
        }
        public bool IsSendMessageToSign = false;
        public string ModelType="message";
        private SessionInfo _sessionInfo;

        private IUFEFileSaver<SessionInfo> Saver = new LiveSessionSaver();
        private List<UfeFile> _files = new List<UfeFile>();
        private ProgressForm _waitForm;

        /// <summary>
        /// Function: Init upload uploadAction 
        /// </summary>
        /// <param name="sign">SignInfo</param>
        /// <param name="sessionInfo">SchedulerInfo:ProWrite</param>
        public LiveSessionUploadAction(SignInfo sign, SessionInfo sessionInfo)
        {
            ProWrite.UI.Controls.Actions.UFE.Responses.UFEResponseService.Init(sign);

            Log.Info("UploadAction Init.");
            Check.Require(sign, "sign", Check.NotNull);
            Check.Require(sessionInfo, "sessionInfo", Check.NotNull);


            _sign = sign;
            _sessionInfo = sessionInfo;

            Saver.Item = _sessionInfo;
            Saver.Sign = _sign;

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

            _waitForm = new ProgressForm(this.Upload,Cancel,_sign);
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
        /// Populate schedule info and delete needUpdatedItems info
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

            _waitForm.Info(Resource.GetString(Resource.Strings.UploadGetLockSuccessful));
            _waitForm.Info(Resource.GetString(Resource.Strings.UploadSchedulerPopulateStart));
            try
            {
                Saver.Populate();
            }
            catch (Exception ex)
            {
                _waitForm.Error(Resource.GetFormatString(Resource.Strings.UploadSchedulerPopulateException, ex.Message), ex);
                return;
            }

            _waitForm.Debug(Resource.GetString(Resource.Strings.UploadSchedulerSaveStart));
            try
            {
                Saver.Save();
            }
            catch (Exception ex)
            {
                _waitForm.Error(Resource.GetString(Resource.Strings.UploadSchedulerSaveException), ex);
                return;
            }

            if (IsCancel)
            {
                _waitForm.SafeClose();
                return;
            }

            _waitForm.Debug(Resource.GetString(Resource.Strings.UploadSchedulerSaveEnd));

            if (!Saver.IsSaveSucessed)
            {
                _waitForm.Error(Resource.GetString(Resource.Strings.UploadSchedulerSaveFailed));
                return;
            }

            List<UfeFile> deleteItems = Saver.DeletedItems;
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
                    _waitForm.SafeClose();
                    return;
                }

                //get task failure
                if (!deleteTask.IsSuccessed)
                {
                    return;
                }
            }


            _files = Saver.Files;
            int count = _files.Count;

            if (count < 1)
            {
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
                _waitForm.Error(Resource.GetString(Resource.Strings.UploadSchedulerLibraryFileEmpty));
                return;
            }

            //Upload library files command
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
                _waitForm.Close();
                return;
            }

            if (!ctx.IsSuccessed)
            {
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
            
            _waitForm.Info(Resource.GetString(Resource.Strings.UploadSchedulerUploadFtpEnd));
            _waitForm.EnabledCancelButton = true;

            const int LiveUploadMode = 2;

            _sign.Controller.SendAsync(Commands.UploadFileCompleted,p =>
                {
                    if (IsCancel)
                    {
                        _waitForm.Close();
                        return;
                    }

                    if (ctx.IsSuccessed&&p.IsSuccessed)
                    {
                        if (IsSendMessageToSign)
                        {
                            _waitForm.Success(Resources.Resource.GetFormatString(Resources.Resource.Strings.UpLoadMessageSuccessful,ModelType,ControlService.SignCombo.Current.Name));
                            IsSendMessageToSign = false;
                        }
                        else
                            _waitForm.Success(Resource.GetString(Resource.Strings.UploadSchedulerUploadSuccessful));
                    }
                    else if(ctx.Packet.ActionError!=null)
                        _waitForm.Error(Resource.GetFormatString(Resource.Strings.UploadSchedulerUploadException, ctx.Packet.ActionError.Message), ctx.Exception);
                    else
                        _waitForm.Error(Resource.GetFormatString(Resource.Strings.UploadSchedulerUploadException, ""), ctx.Exception);
                }, LiveUploadMode);
        }

        private bool PutFile(UfeFile item)
        {
            _waitForm.Info(Resource.GetFormatString(Resource.Strings.UploadSchedulerUploadFtpFileStart, " - " + item.Type + " - " + item.Name + " - " + item.ToFilePath));
            try
            {
                _sign.Controller.Connection.FtpManager.Put(item.FromFilePath, item.ToFilePath);
                _waitForm.Info(Resource.GetFormatString(Resource.Strings.UploadSchedulerUploadFtpFileEnd, " - " + item.Type + " - " + item.Name + " - " + item.ToFilePath));
                return true;
            }
            catch (Exception ex)
            {
                _waitForm.Error(Resource.GetFormatString(Resource.Strings.UploadFailed), ex);
                return false;
            }
        }
    }
}
