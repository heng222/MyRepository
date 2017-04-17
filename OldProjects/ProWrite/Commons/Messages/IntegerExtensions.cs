using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using System.Threading;
namespace System
{
    /// <summary>
    /// Author:qswang
    /// Create:2008-11-28
    /// Function:Integer方法扩展
    /// </summary>
    public static class IntegerExtensions
    {
        /// <summary>
        /// 整形自增长
        /// </summary>
        /// <param name="n">目标类</param>
        public static void Increment(this int n)
        {
            Interlocked.Increment(ref n);
        }
        /// <summary>
        /// 整形自减少
        /// </summary>
        /// <param name="n">目标类型</param>
        public static void Decrement(this int n)
        {
            Interlocked.Decrement(ref n);
        }
    }
}
