using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Acl.Utility;

namespace WpfApplication
{
    /// <summary>
    /// 列车行驶位置类型
    /// </summary>
    public enum PostionType:byte
    {
        /// <summary>
        /// 未知
        /// </summary>
        [MemberDes("未知方向")]
        Unknow = 0x03,
        /// <summary>
        /// 上行
        /// </summary>
        [MemberDes("上行")]
        Up = 0x00,
        /// <summary>
        /// 下行
        /// </summary>
        [MemberDes("下行")]
        Down = 0x01,
        /// <summary>
        /// 停车场或车辆段
        /// </summary>
        [MemberDes("车辆段")]
        Park = 0x04
    }
}
