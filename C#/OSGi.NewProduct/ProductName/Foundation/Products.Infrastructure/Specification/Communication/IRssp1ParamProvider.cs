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

using System;
using System.Collections.Generic;
using System.Net;

using Acl.RsspI4net.Config;

namespace Products.Infrastructure.Specification
{
    /// <summary>
    /// һ���ӿڣ����ڱ�ʾ�����ṩ����UDP��RSSP-1ͨ�Ų�����
    /// </summary>
    public interface IRssp1ParamProvider
    {
        /// <summary>
        /// �Ƿ�A����
        /// </summary>
        bool IsMachineA { get; }

        /// <summary>
        /// ���ڵ�Ĺ������ڡ�
        /// </summary>
        int WorkPeriod { get; }

        /// <summary>
        /// ���ع���������
        /// </summary>
        WorkParameters LocalWorkParameter { get; }

        /// <summary>
        /// ���ذ�ȫ������
        /// </summary>
        SafetyParameters LocalSafetyParam { get; }

        /// <summary>
        /// �Ự������
        /// </summary>
        IEnumerable<Tuple<IEnumerable<UdpParameters>, SessionConfig>> SessionParam { get; }

        /// <summary>
        /// ���� ָ���ĵ�ַ ���� ��Ӧ��ID��
        /// </summary>
        /// <param name="address">���磺0x1E01</param>
        /// <returns>���磺0x9201, 0x9202</returns>
        List<uint> FindRemoteCode(ushort address);

        /// <summary>
        /// ���ݽڵ���Զ����Ų��Ҷ�Ӧ��RSSP-I��ַ��
        /// </summary>
        /// <param name="customCode">�Զ����ţ����磺0x9201, 0x9202��</param>
        /// <returns>�Զ����Ŷ�Ӧ�ĵ�ַ�����磺0x1E01��</returns>
        ushort FindAddress(uint customCode);
    }
}
