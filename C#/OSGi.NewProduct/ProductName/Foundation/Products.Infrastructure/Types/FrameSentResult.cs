/*----------------------------------------------------------------
// ��˾���ƣ���˾����
// 
// ��Ŀ���ƣ���SIL2��֤�ı�׼��ATS
//
// �� �� �ˣ�zhangheng
// �������ڣ�2018-5-15 10:50:33 
// ��    �䣺zhangheng@163.com
//
// Copyright (C) ��˾���� 2009����������Ȩ��
//
//----------------------------------------------------------------*/

using System;
using System.Collections.Generic;
using System.Text;

namespace Products.Infrastructure.Types
{
    /// <summary>
    /// Э��֡���ͽ������
    /// </summary>
    public enum FrameSentResult : byte
    {
        /// <summary>
        /// δ֪��
        /// </summary>
        Unknown,
        /// <summary>
        /// ���ͳɹ���
        /// </summary>
        Successful,
        /// <summary>
        /// ����ʧ�ܡ�
        /// </summary>
        Failed,
    }
}
