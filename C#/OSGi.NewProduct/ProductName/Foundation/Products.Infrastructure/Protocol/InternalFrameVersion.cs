

using System;
using System.Collections.Generic;
using System.Text;

namespace Products.Infrastructure.Protocol
{
    /// <summary>
    /// ͨ��Э��汾��
    /// </summary>
    public enum InternalFrameVersion : byte
    {
        /// <summary>
        /// ��Ч
        /// </summary>
        None = 0,

        /// <summary>
        /// ��һ��
        /// </summary>
        First = 0x01,
        ///// <summary>
        ///// �ڶ���
        ///// </summary>
        //Second = 0x02,
        ///// <summary>
        ///// ������
        ///// </summary>
        //Third = 0x03,
        ///// <summary>
        ///// ���İ�
        ///// </summary>
        //Fourth = 0x04,
    }
}
