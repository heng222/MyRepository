/*----------------------------------------------------------------
// ��˾���ƣ������빫˾����
// 
// ��Ŀ���ƣ���������Ĺ�˾����
//
// �� �� �ˣ�zhangheng
// �������ڣ�2016-5-11 13:13:43 
// ��    �䣺zhangheng@163.com
//
// Copyright (C) ��˾���� 2009����������Ȩ��
//
//----------------------------------------------------------------*/

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Products.Infrastructure.Entities
{
    /// <summary>
    /// IO��λ���塣
    /// </summary>
    public class IoPoint : Entity
    {
        #region "DB �ֶ�"
        /// <summary>
        /// ���ơ�
        /// </summary>
        public string Name { get; set; }

        /// <summary>
        /// ��λ������������վ��š�
        /// </summary>
        public ushort CiStationCode { get; set; }
        /// <summary>
        /// ��λ�����İ忨�ڻ����е�λ��������
        /// </summary>
        public ushort CardIndex { get; set; }
        /// <summary>
        /// ��λ�ڰ忨�е�λ��������
        /// </summary>
        public ushort PointIndex { get; set; }

        /// <summary>
        /// ����λ�������豸���͡�
        /// </summary>
        public ushort DeviceType { get; set; }
        /// <summary>
        /// ����λ�������豸��š�
        /// </summary>
        public ushort DeviceCode { get; set; } 

        #endregion

        #region "Constructor"
        #endregion

        #region "Properties"
        #endregion

        #region "Override methods"
        /// <summary>
        /// ��ȡ��ʵ�����׶�����Ϣ��
        /// </summary>
        /// <returns>һ���׶�����Ϣ��</returns>
        public override string ToString()
        {
            var sb = new StringBuilder(256);

            sb.AppendFormat("���={0}������={1}��", this.Code, this.Name);
            sb.AppendFormat("������վ���={0}���忨λ��={1}����λ����={2}��", this.CiStationCode, this.CardIndex, this.PointIndex);
            sb.AppendFormat("�豸����={0}���豸���={1}��", this.DeviceType, this.DeviceCode);

            return sb.ToString();
        }
        #endregion

        #region "Private methods"
        #endregion

        #region "Public methods"
        #endregion

    }
}