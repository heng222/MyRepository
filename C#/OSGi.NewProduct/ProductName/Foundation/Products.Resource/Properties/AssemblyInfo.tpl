using System.Reflection;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;

// 有关程序集的常规信息通过以下
// 特性集控制。更改这些特性值可修改
// 与程序集关联的信息。
[assembly: AssemblyTitle("Products.Resource，代码修改：$WCDATE$, 构建：$WCNOW$")]

// 将 ComVisible 设置为 false 使此程序集中的类型
// 对 COM 组件不可见。如果需要从 COM 访问此程序集中的类型，
// 则将该类型上的 ComVisible 特性设置为 true。
[assembly: ComVisible(false)]

// 如果此项目向 COM 公开，则下列 GUID 用于类型库的 ID
[assembly: Guid("44d1d4a5-ee9e-4afd-add1-53b26ff76e8d")]

// 程序集的版本信息由下面四个值组成:
//
//      主版本
//      次版本 
//      内部版本号
//      修订号
//
// 可以指定所有这些值，也可以使用“内部版本号”和“修订号”的默认值，
// 方法是按如下所示使用“*”:
// [assembly: AssemblyVersion("1.0.*")]
[assembly: AssemblyVersion("1.0.0.$WCREV$")]
[assembly: AssemblyFileVersion("1.0.0.$WCREV$")]


// 检查是否存在 混合版本 以及 未提交的修改。
#if !DEBUG 
    #if $WCMIXED?true:false$ 
        #warning Mixed version found, please recompile after svn update!
    #endif 
    
    #if $WCMODS?true:false$ 
        #warning Modification found, please recompile after svn commit!
    #endif 
#endif