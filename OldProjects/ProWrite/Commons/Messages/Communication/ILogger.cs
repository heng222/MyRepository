using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace System.Communication
{
    /// <summary>
    /// 消息日志
    /// </summary>
    public interface ILog
    {
        /// <summary>
        /// 记录调试信息
        /// </summary>
        /// <param name="message">消息</param>
        void Debug(object message);

        /// <summary>
        /// 记录调试信息. 
        /// </summary>
        /// <param name="message">消息</param>
        /// <param name="exception">异常</param>
        void Debug(object message, Exception exception);

        /// <summary>
        /// 记录调试信息.
        /// </summary>
        /// <param name="format">消息格式</param>
        /// <param name="args">消息格式化的参数数组</param>
        void DebugFormat(String format, params Object[] args);

        /// <summary>
        /// 判断消息的优先级是否可以进行记录调试信息.
        /// </summary>
        bool IsDebugEnabled { get; }

        /// <summary>
        /// 记录信息
        /// </summary>
        /// <param name="message">消息</param>
        void Info(object message);

        /// <summary>
        /// 记录信息 
        /// </summary>
        /// <param name="message">消息</param>
        /// <param name="exception">异常</param>
        void Info(object message, Exception exception);

        /// <summary>
        /// 记录信息
        /// </summary>
        /// <param name="format">消息格式</param>
        /// <param name="args">消息格式化的参数数组</param>
        void InfoFormat(String format, params Object[] args);

        /// <summary>
        /// 判断消息的优先级是否可以进行记录信息.
        /// </summary>
        bool IsInfoEnabled { get; }

        /// <summary>
        /// 记录警告信息
        /// </summary>
        /// <param name="message">消息</param>
        void Warn(object message);

        /// <summary>
        /// 记录警告信息 
        /// </summary>
        /// <param name="message">消息</param>
        /// <param name="exception">异常</param>
        void Warn(object message, Exception exception);

        /// <summary>
        /// 记录警告信息
        /// </summary>
        /// <param name="format">消息格式</param>
        /// <param name="args">消息格式化的参数数组</param>
        void WarnFormat(String format, params Object[] args);

        /// <summary>
        /// 判断消息的优先级是否可以进行记录警告信息.
        /// </summary>
        bool IsWarnEnabled { get; }

        /// <summary>
        /// 记录错误信息
        /// </summary>
        /// <param name="message">消息</param>
        void Error(object message);

        /// <summary>
        /// 记录错误信息 
        /// </summary>
        /// <param name="message">消息</param>
        /// <param name="exception">异常</param>
        void Error(object message, Exception exception);

        /// <summary>
        /// 记录错误信息
        /// </summary>
        /// <param name="format">消息格式</param>
        /// <param name="args">消息格式化的参数数组</param>
        void ErrorFormat(String format, params Object[] args);

        /// <summary>
        /// 判断消息的优先级是否可以进行记录错误信息.
        /// </summary>
        bool IsErrorEnabled { get; }

        /// <summary>
        /// 记录致命错误信息
        /// </summary>
        /// <param name="message">消息</param>
        void Fatal(object message);

        /// <summary>
        /// 记录致命错误信息
        /// </summary>
        /// <param name="message">消息</param>
        /// <param name="exception">异常</param>
        void Fatal(object message, Exception exception);

        /// <summary>
        /// 记录致命错误信息
        /// </summary>
        /// <param name="format">消息格式</param>
        /// <param name="args">消息格式化的参数数组</param>
        void FatalFormat(String format, params Object[] args);

        /// <summary>
        /// 判断消息的优先级是否可以进行记录致命错误信息.
        /// </summary>
        bool IsFatalEnabled { get; }
    }

    [Serializable]
    public sealed class NullLogger : ILog
    {
        public static readonly NullLogger Instance = new NullLogger();

        public NullLogger()
        {
        }

        public void Debug(object message)
        {
        }

        public void Debug(object message, Exception exception)
        {
        }

        public void DebugFormat(string format, params Object[] args)
        {
        }

        public bool IsDebugEnabled
        {
            get { return false; }
        }

        public void Info(object message)
        {
        }

        public void Info(object message, Exception exception)
        {
        }

        public void InfoFormat(string format, params Object[] args)
        {
        }

        public bool IsInfoEnabled
        {
            get { return false; }
        }

        public void Warn(object message)
        {
        }

        public void Warn(object message, Exception exception)
        {
        }

        public void WarnFormat(string format, params Object[] args)
        {
        }

        public bool IsWarnEnabled
        {
            get { return false; }
        }

        public void Error(object message)
        {
        }

        public void Error(object message, Exception exception)
        {
        }

        public void ErrorFormat(string format, params Object[] args)
        {
        }

        public bool IsErrorEnabled
        {
            get { return false; }
        }

        public void Fatal(object message)
        {
        }

        public void Fatal(object message, Exception exception)
        {
        }

        public void FatalFormat(string format, params Object[] args)
        {
        }

        public bool IsFatalEnabled
        {
            get { return false; }
        }

    }

    public sealed class Log
    {
        private static ILog log = NullLogger.Instance;
        public static ILog InnerLog
        {
            get
            {
                if (log == null)
                    log = NullLogger.Instance;
                return log;
            }
            set
            {
                log = value;
            }
        }


        public static void Debug(object message)
        {
            InnerLog.Debug(message);
        }


        public static void Debug(object message, Exception exception)
        {
            InnerLog.Debug(message, exception);
        }


        public static void Error(object message)
        {
            InnerLog.Error(message);
        }


        public static void Error(object message, Exception exception)
        {
            InnerLog.Error(message, exception);
        }

        public static void Fatal(object message)
        {
            InnerLog.Fatal(message);
        }


        public static void Fatal(object message, Exception exception)
        {
            InnerLog.Fatal(message, exception);
        }



        public static void Info(object message)
        {
            InnerLog.Info(message);
        }


        public static void Info(object message, Exception exception)
        {
            InnerLog.Info(message, exception);
        }


        public static void Warn(object message)
        {
            InnerLog.Warn(message);
        }


        public static void Warn(object message, Exception exception)
        {
            InnerLog.Warn(message, exception);
        }



        public static bool IsDebugEnabled
        {
            get { return InnerLog.IsDebugEnabled; }
        }


        public static bool IsErrorEnabled
        {
            get { return InnerLog.IsErrorEnabled; }
        }


        public static bool IsFatalEnabled
        {
            get { return InnerLog.IsFatalEnabled; }
        }


        public static bool IsInfoEnabled
        {
            get { return InnerLog.IsInfoEnabled; }
        }


        public static bool IsWarnEnabled
        {
            get { return InnerLog.IsWarnEnabled; }
        }


        public static void DebugFormat(string format, params object[] args)
        {
            InnerLog.DebugFormat(format, args);
        }

        public static void InfoFormat(string format, params object[] args)
        {
            InnerLog.InfoFormat(format, args);
        }

        public static void WarnFormat(string format, params object[] args)
        {
            InnerLog.WarnFormat(format, args);
        }

        public static void ErrorFormat(string format, params object[] args)
        {
            InnerLog.ErrorFormat(format, args);
        }

        public static void FatalFormat(string format, params object[] args)
        {
            InnerLog.FatalFormat(format, args);
        }

    }
}
