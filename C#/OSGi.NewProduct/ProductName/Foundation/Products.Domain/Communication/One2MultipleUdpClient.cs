/*----------------------------------------------------------------
// ��˾���ƣ���˾����
// 
// ��Ʒ���ƣ��й�糵����
//
// �� �� �ˣ�heng222_z
// �������ڣ�2019/11/14 10:50:55 
// ��    �䣺heng222_z@163.com
//
// Copyright (C) 2019 ̩��˹����������Ȩ����
//
//----------------------------------------------------------------*/

using System;
using System.Collections.Concurrent;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Timers;
using Acl.Log;
using Products.Infrastructure.Events;
using Products.Infrastructure.Messages;
using Products.Infrastructure.Types;

namespace Products.Domain.Communication
{
    /// <summary>
    /// һ�Զ�UdpClient��װ����
    /// </summary>
    public abstract class One2MultipleUdpClient : OneToNUdpClient
    {
        #region "Field"
        #endregion

        #region "Constructor"
        /// <summary>
        /// ����һ��One2MultiplyUdpClient����
        /// </summary>
        protected One2MultipleUdpClient()
        {
        }

        /// <summary>
        /// ����һ��One2MultiplyUdpClient����
        /// </summary>
        /// <param name="localCode">���ؽڵ��š�</param>
        /// <param name="localEndPoint">�����ս�㡣</param>
        protected One2MultipleUdpClient(uint localCode, IPEndPoint localEndPoint)
            : base(localCode, localEndPoint)
        {

        }
        #endregion

        #region "Properties"
        #endregion

        #region "Abstract methods"
        /// <summary>
        /// ������������дʱ�����ڻ�ȡԶ�̽ڵ��IP�ս�㡣
        /// </summary>
        /// <param name="remtoeCode">Զ�̽ڵ��š�</param>
        /// <returns>Զ�̽ڵ��IP�ս�㡣</returns>
        protected abstract List<IPEndPoint> GetRemoteEndPoints(uint remtoeCode);

        /// <summary>
        /// һ��ģ�巽�������ڷ������ݡ�
        /// </summary>
        /// <param name="data">��Ҫ���͵����ݡ�</param>
        /// <param name="remoteEndPoint">Զ���ս�㡣</param>
        public virtual void Send(byte[] data, IPEndPoint remoteEndPoint)
        {
            if (this.LocalClient == null) return;

            this.LocalClient.Send(data, data.Length, remoteEndPoint);
        }
        #endregion

        #region "Override methods"
        #endregion

        #region "Private methods"

        #endregion

        #region "Public methods"

        /// <summary>
        /// ��ָ�������ݷ��͵�Զ�̽ڵ㡣
        /// </summary>
        /// <param name="data">��Ҫ���͵����ݡ�</param>
        /// <param name="remoteCode">Զ�̽ڵ��š�</param>
        public void Send(byte[] data, uint remoteCode)
        {
            if (this.LocalClient == null) return;

            var remoteEndPoints = this.GetRemoteEndPoints(remoteCode);

            remoteEndPoints.ForEach(p => this.Send(data, p));
        }
        #endregion
    }
}