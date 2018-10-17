using Products.Infrastructure.Types;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Products.Infrastructure.Specification
{
    /// <summary>
    /// 一个接口，用于描述ATS节点的属性。
    /// </summary>
    public interface INodeAttri
    {
        /// <summary>
        /// 获取节点编号
        /// </summary>
        UInt32 Code { get; }

        /// <summary>
        /// 获取节点类型
        /// </summary>
        NodeType Type { get; }

        /// <summary>
        /// 获取节点名称。
        /// </summary>
        string Name { get; }

        /// <summary>
        /// 获取节点所属的车站或中心编号。
        /// </summary>
        UInt16 StationCode { get; }

        /// <summary>
        /// 获取节点所属车站的名称。
        /// </summary>
        string OwnerStationName { get; }

        /// <summary>
        /// 获取节点所在车站的位置编号，即自然站编号。
        /// </summary>
        UInt16 PassengerStationCode { get; }

        ///// <summary>
        ///// 获取节点位置。
        ///// </summary>
        //NodeLocation Location { get; }

        ///// <summary>
        ///// 获取节点的1系IP地址
        ///// </summary>
        //IPAddress LocalIp1 { get; }

        ///// <summary>
        ///// 获取节点作为服务器时在1系网络中的监听端口
        ///// </summary>
        //int ListenPort1 { get; }

        ///// <summary>
        ///// 获取节点的2系IP地址
        ///// </summary>
        //IPAddress LocalIp2 { get; }

        ///// <summary>
        ///// 获取节点作为服务器时在2系网络中的监听端口
        ///// </summary>
        //int ListenPort2 { get; }

        /// <summary>
        /// 获取节点的邻节点编号。
        /// </summary>
        UInt32 SiblingNodeCode { get; }
    }
}
