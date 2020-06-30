/*----------------------------------------------------------------
// ��˾���ƣ������빫˾����
// 
// ��Ŀ���ƣ���������Ŀ����
//
// �� �� �ˣ�zhangheng
// �������ڣ�2016-5-11 13:13:43 
// ��    �䣺zhangheng@163.com
//
// Copyright (C) ��˾���� 2019����������Ȩ��
//
//----------------------------------------------------------------*/

using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.Text;

namespace Products.Infrastructure.Exceptions
{
    /// <summary>
    /// ����������ȡ���쳣��
    /// </summary>
    public sealed class LanuchCanceledException : Exception
    {
        #region "Field"
        #endregion

        #region "Constructor"
        /// <summary>
        /// ��ʼ��һ�� <seealso cref="LanuchCanceledException"/> �����ʵ����
        /// </summary>
        public LanuchCanceledException()
            : base()
        {

        }
        /// <summary>
        /// ʹ��ָ���Ĵ�����Ϣ��ʼ��<seealso cref="LanuchCanceledException"/>�����ʵ����
        /// </summary>
        /// <param name="message">�����������Ϣ��</param>
        public LanuchCanceledException(string message)
            : base(message)
        {

        }

        /// <summary>
        /// ʹ��ָ��������Ϣ�Ͷ���Ϊ���쳣ԭ����ڲ��쳣����������ʼ�� <seealso cref="LanuchCanceledException"/> �����ʵ����
        /// </summary>
        /// <param name="message">�����쳣ԭ��Ĵ�����Ϣ��</param>
        /// <param name="ex">���µ�ǰ�쳣���쳣�����δָ���ڲ��쳣������һ�� null ���ã��� Visual Basic ��Ϊ Nothing����</param>
        public LanuchCanceledException(string message, Exception ex)
            : base(message, ex)
        {

        }

        /// <summary>
        /// �����л����ݳ�ʼ��<seealso cref="LanuchCanceledException"/>�����ʵ����
        /// </summary>
        /// <param name="info">System.Runtime.Serialization.SerializationInfo���������й��������쳣�����л��Ķ������ݡ�</param>
        /// <param name="context">System.Runtime.Serialization.StreamingContext���������й�Դ��Ŀ�����������Ϣ��</param>
        private LanuchCanceledException(SerializationInfo info, StreamingContext context)
            : base(info, context)
        {

        }
        #endregion

        #region "Properties"
        #endregion

        #region "Override methods"
        #endregion

        #region "Private methods"
        #endregion

        #region "Public methods"
        #endregion

    }
}
