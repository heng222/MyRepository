/*----------------------------------------------------------------
// 公司名称：请输入公司名称
// 
// 项目名称：请输入你的公司名称
//
// 创 建 人：zhangheng
// 创建日期：2016-5-11 13:13:43 
// 邮    箱：zhangheng@163.com
//
// Copyright (C) 公司名称 2009，保留所有权利
//
//----------------------------------------------------------------*/

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Acl.Utility;

namespace Products.Infrastructure.Types
{
    /// <summary>
    /// 操作类型
    /// </summary>
    public enum OperationType : byte
    {
        /// <summary>
        /// 无效操作。
        /// </summary>
        [MemberDes("无效操作")]
        None = 0,

        #region "下位机相关操作"
        /// <summary>
        /// 读应答器报文。
        /// </summary>
        [MemberDes("读应答器报文")]
        ReadBalisePackage = 0x02,
        /// <summary>
        /// 修改下位机地址。
        /// </summary>
        [MemberDes("修改下位机地址")]
        ModifyHypMacAddr = 0x04,
        /// <summary>
        /// 查询下位机状态。
        /// </summary>
        [MemberDes("查询下位机状态")]
        QueryHypogyMacState = 0x06,
        #endregion

        #region "节点管理相关操作"
        /// <summary>
        /// 新增节点
        /// </summary>
        [MemberDes("新增节点")]
        AddNewNode = 0x11,
        /// <summary>
        /// 移除节点
        /// </summary>
        [MemberDes("移除节点")]
        RemoveNode = 0x12,
        #endregion
    }
}
