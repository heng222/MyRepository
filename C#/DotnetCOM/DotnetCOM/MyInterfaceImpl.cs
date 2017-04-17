using System;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;
using System.Runtime.InteropServices;

namespace DotnetCOM
{
    #region
    // �ӿ� ʵ��
    // {E3CF2CAA-A38F-4865-9003-CC16D300A337}
    // DEFINE_GUID(<<name>>, 
    // 0xe3cf2caa, 0xa38f, 0x4865, 0x90, 0x3, 0xcc, 0x16, 0xd3, 0x0, 0xa3, 0x37);
    #endregion

    [Guid("E3CF2CAA-A38F-4865-9003-CC16D300A337"),
     ClassInterface(ClassInterfaceType.None),
     ComSourceInterfaces(typeof(IComInterfaceEvent))]
    public class MyInterfaceImpl : IComInterface
    {
        #region IComInterface ��Ա

        public void Test(int num, string str)
        {
            string caption = "C#��д��COM���";

            string text = String.Format("������num= {0}, str1= {1}", 
                num, str);

            MessageBox.Show(text, caption, MessageBoxButtons.YesNoCancel);
        }

        #endregion
    }
}
