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
using System.Collections.Generic;
using System.Text;
using Products.Infrastructure.Types;

namespace Products.Infrastructure.Events
{
    /// <summary>
    /// ���ڵ�䣩ͨ��״̬�仯�¼�������
    /// </summary>
    public sealed class CommStateChangedEventArgs : EventArgs
    {
        #region "Filed"
        #endregion

        #region "Constructor"
        /// <summary>
        /// ����һ�����ӱ仯�¼�������
        /// </summary>
        /// <param name="connected"></param>
        /// <param name="localId"></param>
        /// <param name="remoteId"></param>
        /// <param name="remoteType"></param>
        public CommStateChangedEventArgs(bool connected, uint localId, 
            uint remoteId, NodeType remoteType)
        {
            this.Connected = connected;
            this.LocalDeviceID = localId;
            this.RemoteDeviceID = remoteId;
            this.RemoteDeviceType = remoteType;
        }
        #endregion

        #region "Properties"
        /// <summary>
        /// ����һ��ֵ�����ڱ�ʾ�Ƿ�Ϊ�豸�������¼���
        /// </summary>
        public bool Connected { get; set; }

        /// <summary>
        /// ���¼���Ӧ�ı����豸ID(��IDΪ�豸�� ��ϵͳ �еı�ţ�������ӿ�ͨ��ʱʹ�õı��)
        /// </summary>
        public UInt32 LocalDeviceID { get; set; }

        /// <summary>
        /// ���¼���Ӧ�ĶԷ��豸����
        /// </summary>
        public NodeType RemoteDeviceType { get; set; }

        /// <summary>
        /// ���¼���Ӧ�ĶԷ��豸ID(��IDΪ�豸�� ��ϵͳ �еı�ţ�������ӿ�ͨ��ʱʹ�õı��)
        /// </summary>
        public UInt32 RemoteDeviceID { get; set; }
        #endregion

        #region "Override methods"
        #endregion

        #region "Private methods"
        #endregion

        #region "Public methods"
        #endregion

    }
}
