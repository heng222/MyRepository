/*----------------------------------------------------------------
// ��˾���ƣ������빫˾����
// 
// ��Ŀ���ƣ�������Ŀ����
//
// �� �� �ˣ�zhangheng
// �������ڣ�2015-2-2 10:43:04 
// ��    �䣺heng222_z@163.com
//
// Copyright (C) ��˾���� 2009����������Ȩ��
//
//----------------------------------------------------------------*/

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Net;

namespace Products.Infrastructure.Specification
{
    /// <summary>
    /// һ���ӿڣ����ڱ�ʾ�����ṩ������UDPͨ�Ų�����
    /// </summary>
    public interface IRawUdpParamProvider
    {
        /// <summary>
        /// ���ؼ����㡣
        /// </summary>
        IPEndPoint LocalEndPoint { get; }

        /// <summary>
        /// Key = Remote ID
        /// </summary>
        Dictionary<uint, IPEndPoint> RemoteEndPoints { get; }

        /// <summary>
        /// ���� IPEndPoint ��ȡ ��Ӧ��Զ�̽ڵ��š�
        /// </summary>
        /// <param name="endPoint">IP�ս�㡣</param>
        /// <returns>Զ�̽ڵ��š�</returns>
        uint GetRemoteCode(IPEndPoint endPoint);
    }
}
