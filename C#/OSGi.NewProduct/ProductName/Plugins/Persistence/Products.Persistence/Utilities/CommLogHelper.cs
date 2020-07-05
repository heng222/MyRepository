using System;
using System.Collections.Generic;
using System.Linq;
using System.Windows.Forms;

using Acl.CommStreamLog.Data;
using Acl.CommStreamLog.Parser;

using Products.Infrastructure.Log;
using Products.Infrastructure.Types;

using MappingItem = System.Tuple<Products.Infrastructure.Types.NodeType, Products.Infrastructure.Types.NodeType, uint, uint>;

namespace Products.Persistence
{
    /// <summary>
    /// 通信流日志帮助类
    /// </summary>
    static class CommLogHelper
    {
        #region "Feild"
        /// <summary>
        /// Item1：本方节点类型。
        /// Item2：对方节点类型。
        /// Item3：输入流编号。
        /// Item4：输出流编号。
        /// </summary>
        private static List<MappingItem> ParserCodeMapping;
        #endregion

        #region "Constructor"
        /// <summary>
        /// 静态构造函数。
        /// </summary>
        static CommLogHelper()
        {
            InitParserCodeMapping();
        }
        #endregion

        #region "Private methods"
        private static void InitParserCodeMapping()
        {
            ParserCodeMapping = new List<MappingItem>()
            {
                new MappingItem(NodeType.Node1, NodeType.Node1, CommLogParserCode.System1Input, CommLogParserCode.System1Input), // TODO:
            };
        }
        #endregion


        #region "public methods"        
        /// <summary>
        /// 根据本地类型与远程类型获取解析器编号。
        /// </summary>
        public static uint GetParserCode(NodeType localType, NodeType remoteType, bool isInputStream)
        {
            var ipc = CommLogParserCode.None;
            var opc = CommLogParserCode.None;

            var theItem = ParserCodeMapping.Where(p => p.Item1 == remoteType && p.Item2 == remoteType).FirstOrDefault();

            if (theItem != null)
            {
                ipc = theItem.Item3;
                opc = theItem.Item4;
            }

            return isInputStream ? ipc : opc;
        }
        #endregion
    }
}
