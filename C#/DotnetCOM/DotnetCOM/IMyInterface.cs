using System;
using System.Collections.Generic;
using System.Text;
using System.Runtime.InteropServices;

namespace DotnetCOM
{
    [Guid("8F6BD6AA-E2F3-4504-8DDC-191C5B5A546A")]
    public interface IComInterface
    {
        [DispId(1)]
        void Test(int num, string str1);
    }

//     public interface IComInterface
//     {
//         [DispId(1)]
//         string ComInterfaceDemoMessage(string str);
//         [DispId(2)]
//         int ComInterfaceDemoAdd();
//         [DispId(3)]
//         int ComInterfaceDemoRemove();
//         [DispId(4)]
//         float ComInterfaceDemoAddF();
//         [DispId(5)]
//         float ComInterfaceDemoRemoveF();
//         [DispId(6)]
//         object ComInterfaceDemoGetList();
//         [DispId(7)]
//         MyTestDemo ComInterfaceDemoTestDemo();
//         [DispId(8)]
//         string[] ComInterfaceGetStringList();
// 
//     }

    #region
    // com 事件 接口
    // {C3D879BE-8631-4bf5-8292-B96CDCB4D965}
    // DEFINE_GUID(<<name>>, 
    // 0xc3d879be, 0x8631, 0x4bf5, 0x82, 0x92, 0xb9, 0x6c, 0xdc, 0xb4, 0xd9, 0x65);
    #endregion
    [Guid("C3D879BE-8631-4bf5-8292-B96CDCB4D965"),
     InterfaceType(ComInterfaceType.InterfaceIsIDispatch)]
    public interface IComInterfaceEvent
    {

    }
}
