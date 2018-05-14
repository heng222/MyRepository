/*----------------------------------------------------------------
// ��˾���ƣ������빫˾����
// 
// ��Ŀ���ƣ���������Ŀ����
//
// �� �� �ˣ�zhangheng
// �������ڣ�03/02/2012 15:13:23 
// ��    �䣺heng222_z@163.com
//
// Copyright (C) ��˾���� 2009-2015 ��������Ȩ��
//
//----------------------------------------------------------------*/

using System;
using System.Collections.Generic;
using System.Text;
using Products.Infrastructure.Log;

namespace Products.Infrastructure.Protocol.Framework
{
    /// <summary>
    /// ͨѶЭ��֡���ඨ��
    /// </summary>
    public abstract class ProtocolFrame
    {
        #region "Filed"
        #endregion

        #region "Constructor"
        /// <summary>
        /// ʹ��ָ���Ĳ�����ʼ��һ��Э�鱨��
        /// </summary>
        /// <param name="parserCode">���������</param>
        protected ProtocolFrame(CommLogParserCode parserCode)
        {
            this.ParserCode = parserCode;
        }
        #endregion

        #region "Properties"
        /// <summary>
        /// ��ȡ��Э��֡�Ľ�������š�
        /// </summary>
        public CommLogParserCode ParserCode { get; private set; }
        #endregion

        #region "Virtual methods"

        #endregion

        #region "Private methods"
        #endregion

        #region "Public methods"
        #endregion
    }
}