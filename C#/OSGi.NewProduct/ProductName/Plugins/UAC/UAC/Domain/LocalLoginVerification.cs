/*----------------------------------------------------------------
// ��˾���ƣ���˾����
// 
// ��Ʒ���ƣ�ATS
//
// �� �� �ˣ�heng222_z
// �������ڣ�2018/5/22 14:20:17 
// ��    �䣺heng222_z@163.com
//
// Copyright (C) 2018 ATS����������Ȩ����
//
//----------------------------------------------------------------*/

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Products.UAC.Domain
{
    /// <summary>
    /// ���ص�¼��֤
    /// </summary>
    class LocalLoginVerification : ILoginVerification
    {
        #region "Filed"
        #endregion

        #region "Constructor"
        #endregion

        #region "Properties"
        #endregion

        #region "Override methods"
        #endregion

        #region "Private methods"
        #endregion

        #region "Public methods"
        #endregion

        #region "ILoginVerification ����"
        public void LogOn(string userName, byte[] pwdMd5)
        {
            throw new NotImplementedException();
        }

        public void Logoff(string userName)
        {
            throw new NotImplementedException();
        }
        #endregion
    }
}
