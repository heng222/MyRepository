using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using log4net;
using Tamir.SharpSsh;
using System.Threading;
using ProWrite.UFE.Entity;
using System.Collections;
using Tamir.SharpSsh.jsch;
using Tamir.SharpSsh.java.util;
using System.Communication;
using System.Threading.Tasks;

namespace ProWrite.UFE
{
    public class SFtpManager:Sftp,IFtpManager
    {
        public SFtpManager(string sftpHost, string user, string password)
			: base(sftpHost, user, password)
		{
		}

		public SFtpManager(string sftpHost, string user):base(sftpHost,user){}

        //public static SFtpManager Current { get; internal set; }

        public void Open()
        {
            Connect();
        }

        public void DownLoad(string fromFilePath, string toFilePath)
        {
            try
            {
                Get(fromFilePath, toFilePath);
            }
            catch (Exception ex)
            {
                Log.Error(ex.Message, ex);
            }
        }

        internal Task OpenTask { get; set; }
        private bool? isConnected = null;
        public bool? IsConnected
        {
            get
            {
                if (!isConnected.HasValue && OpenTask != null)
                {
                    OpenTask.Wait();
                }
                return isConnected;
            }
            set
            {
                isConnected = value;
            }
        }

        public bool IsNewAddress(string address,string userName,string pwd)
        {
            if (m_session != null)
                return m_session.getHost() != address
                    || Username != userName || Password != pwd;
            else
                return true;
            
        }
        //public IAsyncFuture PutAsync(string fromFilePath, string toFilePath)
        //{
        //    Action<string, string> putFunc = base.Put;

        //    var future = new Future.SimpleFuture();
        //    try
        //    {
        //        future.AsyncResult = putFunc.BeginInvoke(fromFilePath, toFilePath, p =>
        //            {
        //                try
        //                {
        //                    putFunc.EndInvoke(future.AsyncResult);
        //                }
        //                catch (Exception ex)
        //                {
        //                    future.Exception = ex;
        //                }

        //                future.Set();

        //            }, null);
        //    }
        //    catch (Exception ex)
        //    {
        //        future.Exception = ex;
        //    }
        //    return future;

        //}
    }
}
