/*----------------------------------------------------------------
// ��˾���ƣ������빫˾����
// 
// ��Ŀ���ƣ�������Ŀ����
//
// �� �� �ˣ�zhangheng
// �������ڣ�2015-2-2 10:43:04 
// ��    �䣺heng222_z@163.com
//
// Copyright (C) ��˾���� 2019����������Ȩ��
//
//----------------------------------------------------------------*/


using System.Net;

using Products.Infrastructure.Types;

namespace Products.Domain.Communication
{
    /// <summary>
    /// 1��Nͨ�ŵ�UdpClient�ࡣ
    /// </summary>
    public abstract class One2NUdpClient : M2nUdpClient
    {
        #region "Field"
        #endregion

        #region "Constructor"
        /// <summary>
        /// ����һ�� OneToNUdpClient ����
        /// </summary>
        protected One2NUdpClient()
        {
        }

        /// <summary>
        /// ����һ��OneToNUdpClient����
        /// </summary>
        /// <param name="localType">���ؽڵ����͡�</param>
        /// <param name="localCode">���ؽڵ��š�</param>
        /// <param name="localEndPoint">�����ս�㡣</param>
        protected One2NUdpClient(NodeType localType, uint localCode, IPEndPoint localEndPoint)
        {
            this.LocalCode = localCode;
            this.LocalEndPoint = localEndPoint;
        }
        #endregion

        #region "Properties"
        /// <summary>
        /// ��ȡ���ؽڵ�ı�š�
        /// </summary>
        public virtual uint LocalCode { get; protected set; }

        #endregion

        #region "Abstract/Virtual methods"
        #endregion

        #region "Override methods"
        ///<inheritdoc/>
        protected override uint GetLocalCode(uint remoteCode, IPEndPoint remoteEndPoint)
        {
            return this.LocalCode;
        }
        #endregion

        #region "Private methods"
        #endregion

        #region "Protected methods"
        #endregion

        #region "Public methods"

        /// <summary>
        /// һ��ģ�巽����������������дʱ���ڷ������ݡ�
        /// </summary>
        /// <param name="data">��Ҫ���͵����ݡ�</param>
        /// <param name="remoteEndPoint">Զ���ս�㡣</param>
        public void Send(byte[] data, IPEndPoint remoteEndPoint)
        {
            base.Send(data, this.LocalCode, remoteEndPoint);
        }

        /// <summary>
        /// ��ָ�������ݷ��͵�Զ�̽ڵ㡣
        /// </summary>
        /// <param name="data">��Ҫ���͵����ݡ�</param>
        /// <param name="remoteCode">Զ�̽ڵ��š�</param>
        public void Send(byte[] data, uint remoteCode)
        {
            var remoteEndPoints = this.GetRemoteEndPoints(remoteCode);

            remoteEndPoints.ForEach(p => this.Send(data, p));
        }
        #endregion

    }
}
