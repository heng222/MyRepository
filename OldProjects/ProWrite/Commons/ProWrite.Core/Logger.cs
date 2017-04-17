using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Communication;

namespace ProWrite.Core
{
    public class Logger : ILog
    {
        private log4net.ILog log = null;

        public Logger(Type type)
        {
            log = log4net.LogManager.GetLogger(type);
        }

        public Logger(string name)
        {
            log = log4net.LogManager.GetLogger(name);
        }

        public void Debug(object message)
        {
            log.Debug(message);
        }


        public void Debug(object message, Exception exception)
        {
            log.Debug(message, exception);
        }


        public void Error(object message)
        {
            log.Error(message);
        }


        public void Error(object message, Exception exception)
        {
            log.Error(message, exception);
        }

        public void Fatal(object message)
        {
            log.Fatal(message);
        }


        public void Fatal(object message, Exception exception)
        {
            log.Fatal(message, exception);
        }



        public void Info(object message)
        {
            log.Info(message);
        }


        public void Info(object message, Exception exception)
        {
            log.Info(message, exception);
        }


        public void Warn(object message)
        {
            log.Warn(message);
        }


        public void Warn(object message, Exception exception)
        {
            log.Warn(message, exception);
        }



        public bool IsDebugEnabled
        {
            get { return log.IsDebugEnabled; }
        }


        public bool IsErrorEnabled
        {
            get { return log.IsErrorEnabled; }
        }


        public bool IsFatalEnabled
        {
            get { return log.IsFatalEnabled; }
        }


        public bool IsInfoEnabled
        {
            get { return log.IsInfoEnabled; }
        }


        public bool IsWarnEnabled
        {
            get { return log.IsWarnEnabled; }
        }


        public void DebugFormat(string format, params object[] args)
        {
            log.DebugFormat(format, args);
        }

        public void InfoFormat(string format, params object[] args)
        {
            log.InfoFormat(format, args);
        }

        public void WarnFormat(string format, params object[] args)
        {
            log.WarnFormat(format, args);
        }

        public void ErrorFormat(string format, params object[] args)
        {
            log.ErrorFormat(format, args);
        }

        public void FatalFormat(string format, params object[] args)
        {
            log.FatalFormat(format, args);
        }

    }
}
