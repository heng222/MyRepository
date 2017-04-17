//using System;
//using System.Collections.Generic;
//using System.Linq;
//using System.Text;
//using ProWrite.Entity.Library;
//using ProWrite.UFE.Files;
//using ProWrite.UFE.Entity;
//using ProWrite.UFE;
//using ProWrite.UI.Controls.Common.Messages;
//using ProWrite.UI.Controls.Common;
//using ProWrite.Resources;

//namespace ProWrite.UI.Controls.Scheduler
//{
//    public partial class ScheduleControl :ControlPanel<SchedulerInfo, ScheduleControl>,IUFEFileUploader<SchedulerInfo>
//    {
//        private IUFEFileSaver<SchedulerInfo> Saver = new ScheduleSaver();
//        private List<UfeFile> _files;

//        public void Upload(SchedulerInfo schedule)
//        {
//            Check.Require(schedule != null, "schedule != null");
//            Saver.Item = schedule;
//            _sign.Controller.FileManager.GetLock();
//        }

//        private void DeleteTempFiles()
//        {
//            LocalFilePathMapping.DeleteFiles();
//        }

//        public override void SendToSign()
//        {
//            Upload(Model);
//        }

//        void OnDoUpload()
//        {
//            Saver.Item = Model;
//            Saver.Sign = _sign;
//            Saver.Populate();

//            _files = Saver.Files;
//            List<UfeFile> deletedFiles = Saver.NeedUpdatedItems;
//            int count = _files.Count;

//            if (count < 1)
//            {
//                _sign.Controller.FileManager.FreeLock();
//                return;
//            }

//            if (deletedFiles != null && deletedFiles.Count > 0)
//                _sign.Controller.FileManager.DeleteFile(deletedFiles);
//            else
//                DoUpload();

//        }


//        private void DoUpload()
//        {
//            Saver.Save();

//            if (Saver.IsSaveSucessed)
//            {
//                _sign.Controller.FileManager.UploadFile(_files);
//            }
//        }

//        void Connection_ConnectionClosed(object sender, EventArgs e)
//        {
//            UnsubscribeFtpEvent();
//        }

//        private void UnsubscribeFtpEvent()
//        {
//            _sign.Controller.FileManager.GetLockSuccessed -= new ProWrite.UFE.ReceivedHandler(FileManager_GetLockSuccessed);
//            _sign.Controller.FileManager.GetLockFailed -= new ProWrite.UFE.ReceivedHandler(FileManager_GetLockFailed);
//            _sign.Controller.FileManager.FreeLockSuccessed -= new ProWrite.UFE.ReceivedHandler(FileManager_FreeLockSuccessed);
//            _sign.Controller.FileManager.FreeLockFailed -= new ProWrite.UFE.ReceivedHandler(FileManager_FreeLockFailed);
//            _sign.Controller.FileManager.UploadCompletedSuccessed -= new ReceivedHandler(FileManager_UploadCompletedSuccessed);
//            _sign.Controller.FileManager.UploadCompletedFailed -= new ReceivedHandler(FileManager_UploadCompletedFailed);
//            _sign.Controller.FileManager.DeleteFileSuccessed -= new ReceivedHandler(FileManager_DeleteFileSuccessed);
//            _sign.Controller.FileManager.DeleteFileFailed -= new ReceivedHandler(FileManager_DeleteFileFailed);
//        }

//        void FileManager_DeleteFileFailed(UFEPacket resp)
//        {
//            DeleteTempFiles();
//        }

//        void FileManager_DeleteFileSuccessed(UFEPacket resp)
//        {
//            DoUpload();
//        }

//        void OnUserLoginSucessed(UFEPacket resp)
//        {
//            SubscribeFtpEvent();
//        }

//        private void SubscribeFtpEvent()
//        {
//            if (_sign.Controller.Connection.User.IsFtpRole)
//            {
//                _sign.Controller.FileManager.GetLockSuccessed += new ProWrite.UFE.ReceivedHandler(FileManager_GetLockSuccessed);
//                _sign.Controller.FileManager.GetLockFailed += new ProWrite.UFE.ReceivedHandler(FileManager_GetLockFailed);
//                _sign.Controller.FileManager.FreeLockSuccessed += new ProWrite.UFE.ReceivedHandler(FileManager_FreeLockSuccessed);
//                _sign.Controller.FileManager.FreeLockFailed += new ProWrite.UFE.ReceivedHandler(FileManager_FreeLockFailed);
//                _sign.Controller.FileManager.UploadCompletedSuccessed += new ReceivedHandler(FileManager_UploadCompletedSuccessed);
//                _sign.Controller.FileManager.UploadCompletedFailed += new ReceivedHandler(FileManager_UploadCompletedFailed);
//                _sign.Controller.FileManager.DeleteFileSuccessed += new ReceivedHandler(FileManager_DeleteFileSuccessed);
//                _sign.Controller.FileManager.DeleteFileFailed += new ReceivedHandler(FileManager_DeleteFileFailed);
//            }
//        }

//        void FileManager_UploadCompletedFailed(UFEPacket resp)
//        {
//            _files.Clear();
//            _sign.Controller.FileManager.FreeLock();
//            DeleteTempFiles();
//            MsgBox.Warning(Resource.GetString(Resource.Strings.UploadFailed));
//        }

//        void FileManager_UploadCompletedSuccessed(UFEPacket resp)
//        {
//            _files.Clear();
//            _sign.Controller.FileManager.FreeLock();
//            DeleteTempFiles();
//            MsgBox.Information(Resource.GetString(Resource.Strings.UploadSuccessful));
//        }

//        void FileManager_FreeLockFailed(ProWrite.UFE.UFEPacket resp)
//        {
//            _files.Clear();
//            DeleteTempFiles();

//            //int lockUserId = resp.Content.GetProperty<int>("OwnerId");
//            //string lockUserName = resp.Content.GetProperty<string>("OwnerName");
//            //int currentUserId = resp.UserId;
//            //bool enabled = lockUserId == currentUserId;
//            //SetSendToSignEnable(enabled);

//        }

//        void FileManager_FreeLockSuccessed(ProWrite.UFE.UFEPacket resp)
//        {
//            //int lockUserId = resp.Content.GetProperty<int>("OwnerId");
//            //string lockUserName = resp.Content.GetProperty<string>("OwnerName");            
//            //int currentUserId = resp.UserId;
//            //bool enabled = lockUserId == currentUserId;
//            //SetSendToSignEnable(enabled);
//        }

//        void FileManager_GetLockFailed(ProWrite.UFE.UFEPacket resp)
//        {
//            //int lockUserId = resp.Content.GetProperty<int>("OwnerId");
//            //string lockUserName = resp.Content.GetProperty<string>("OwnerName");
//            //int currentUserId = resp.UserId;
//            //bool enabled = lockUserId == currentUserId;
//            //if (enabled && _sign.Controller.Connection.CanFtpOperation)
//            //    _sign.Controller.FileManager.FreeLock();
//            //SetSendToSignEnable(enabled);

//            //MsgBox.Warning(Resource.GetString(Resource.Strings.GetLockFailure));
//        }

//        void FileManager_GetLockSuccessed(ProWrite.UFE.UFEPacket resp)
//        {
//            //int lockUserId = resp.Content.GetProperty<int>("OwnerId");
//            //string lockUserName = resp.Content.GetProperty<string>("OwnerName");
//            //int currentUserId = resp.UserId;

//            //bool enabled = lockUserId == currentUserId;
//            //SetSendToSignEnable(enabled);

//            //if (enabled)
//            if(_sign.Controller.Connection.CanFtpOperation)
//            {
//                OnDoUpload();
//            }
//        }

//        //void SetSendToSignEnable(bool b)
//        //{
//        //    if (ControlService.LibraryTree.Controller.GetNode(Model) == null)
//        //        b = false;
//        //    LocalMessageBus.Send(this, new MenuMessage(
//        //                            new MenuCommand
//        //                            {
//        //                                Command = MenuCommands.SendToSign,
//        //                                Enabled = b
//        //                            }));
//        //}
//    }
//}
