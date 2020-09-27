/*----------------------------------------------------------------
// ��˾���ƣ������빫˾����
// 
// ��Ŀ���ƣ���������Ŀ����
//
// �� �� �ˣ�zhangheng
// �������ڣ�2013-7-23 15:14:23 
// ��    �䣺heng222_z@163.com
//
// Copyright (C) ��˾���ƣ���������Ȩ����
//
//----------------------------------------------------------------*/

using System;

using Products.Infrastructure.Types;

namespace Products.Infrastructure.Events
{
    /// <summary>
    /// ���ڵ�䣩ͨ��״̬�仯�¼�������
    /// </summary>
    public sealed class CommStateChangedEventArgs : EventArgs
    {
        #region "Field"
        #endregion

        #region "Constructor"
        /// <summary>
        /// ����һ�����ӱ仯�¼�������
        /// </summary>
        /// <param name="commState">ͨ��״̬��</param>
        /// <param name="localType">���ؽڵ����͡�</param>
        /// <param name="localId">���ؽڵ��š�</param>
        /// <param name="remoteType">Զ�̽ڵ����͡�</param>
        /// <param name="remoteId">Զ�̽ڵ��š�</param>
        public CommStateChangedEventArgs(bool? commState,
            NodeType localType, uint localId,
            NodeType remoteType, uint remoteId)
        {
            this.CommState = commState;

            this.LocalNodeType = localType;
            this.LocalNodeCode = localId;
            this.RemoteNodeType = remoteType;
            this.RemoteNodeCode = remoteId;
        }
        #endregion

        #region "Properties"
        /// <summary>
        /// ��ȡ�ڵ���ͨ��״̬��
        /// <para>true��ʾͨ��������false��ʾͨ���쳣��null��ʾδ֪��</para>
        /// </summary>
        public bool? CommState { get; set; }

        /// <summary>
        /// ��ȡ���ؽڵ����͡�
        /// </summary>
        public NodeType LocalNodeType { get; set; }
        /// <summary>
        /// ���¼���Ӧ�ı����豸ID(��IDΪ�豸�� ��ϵͳ �еı�ţ�������ӿ�ͨ��ʱʹ�õı��)
        /// </summary>
        public UInt32 LocalNodeCode { get; set; }

        /// <summary>
        /// ���¼���Ӧ�ĶԷ��豸����
        /// </summary>
        public NodeType RemoteNodeType { get; set; }
        /// <summary>
        /// ���¼���Ӧ�ĶԷ��豸ID(��IDΪ�豸�� ��ϵͳ �еı�ţ�������ӿ�ͨ��ʱʹ�õı��)
        /// </summary>
        public UInt32 RemoteNodeCode { get; set; }
        #endregion

        #region "Private methods"
        #endregion

        #region "Public methods"
        #endregion

    }
}
