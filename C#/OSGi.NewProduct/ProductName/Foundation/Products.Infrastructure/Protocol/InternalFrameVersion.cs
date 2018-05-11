

using System;
using System.Collections.Generic;
using System.Text;

namespace Products.Infrastructure.Protocol
{
    /// <summary>
    /// 通信协议版本号
    /// </summary>
    public enum InternalFrameVersion : byte
    {
        /// <summary>
        /// 无效
        /// </summary>
        None = 0,

        /// <summary>
        /// 第一版
        /// </summary>
        First = 0x01,
        ///// <summary>
        ///// 第二版
        ///// </summary>
        //Second = 0x02,
        ///// <summary>
        ///// 第三版
        ///// </summary>
        //Third = 0x03,
        ///// <summary>
        ///// 第四版
        ///// </summary>
        //Fourth = 0x04,
    }
}
