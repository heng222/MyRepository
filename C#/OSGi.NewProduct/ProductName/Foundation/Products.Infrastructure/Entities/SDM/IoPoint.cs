/*----------------------------------------------------------------
// 公司名称：请输入公司名称
// 
// 项目名称：请输入项目名称
//
// 创 建 人：zhangheng
// 创建日期：2016-5-11 13:13:43 
// 邮    箱：zhangheng@163.com
//
// Copyright (C) 公司名称 2019，保留所有权利
//
//----------------------------------------------------------------*/

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Acl.Data.Annotions;

namespace Products.Infrastructure.Entities
{
    /// <summary>
    /// IO点位定义。
    /// </summary>
    public class IoPoint : Entity
    {
        #region "DB 字段"
        /// <summary>
        /// 名称。
        /// </summary>
        [Column]
        public string Name { get; set; }

        /// <summary>
        /// 点位所属的联锁车站编号。
        /// </summary>
        [Column]
        public ushort CiStationCode { get; set; }
        /// <summary>
        /// 点位所属的板卡在机笼中的位置索引。
        /// </summary>
        [Column]
        public ushort CardIndex { get; set; }
        /// <summary>
        /// 点位在板卡中的位置索引。
        /// </summary>
        [Column]
        public ushort PointIndex { get; set; }

        /// <summary>
        /// 本点位关联的设备类型。
        /// </summary>
        [Column]
        public ushort DeviceType { get; set; }
        /// <summary>
        /// 本点位关联的设备编号。
        /// </summary>
        [Column]
        public ushort DeviceCode { get; set; } 

        #endregion

        #region "Constructor"
        #endregion

        #region "Properties"
        #endregion

        #region "Override methods"
        /// <summary>
        /// 获取此实例的易读性信息。
        /// </summary>
        /// <returns>一个易读性信息。</returns>
        public override string ToString()
        {
            var sb = new StringBuilder(256);

            sb.AppendFormat("编号={0}，名称={1}，", this.Code, this.Name);
            sb.AppendFormat("联锁车站编号={0}，板卡位置={1}，点位索引={2}，", this.CiStationCode, this.CardIndex, this.PointIndex);
            sb.AppendFormat("设备类型={0}，设备编号={1}。", this.DeviceType, this.DeviceCode);

            return sb.ToString();
        }
        #endregion

        #region "Private methods"
        #endregion

        #region "Public methods"
        #endregion

    }
}
