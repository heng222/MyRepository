using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ProWrite.Entity.Library;
using ProWrite.Core;
using System.Drawing;
using ProWrite.Entity.DES;

namespace ProWrite.DES
{
    public class NailImageMessageInspector : ConverterBase<MessageInfo, MessageInfo>
    {
        private NailImageMessageInspector() { }

        public static readonly NailImageMessageInspector Instance = new NailImageMessageInspector();

        public override MessageInfo Convert(MessageInfo source)
        {
            var msg = source.Copy() as MessageInfo;

            var layers = msg.Items;
            for (int i = 1; i < layers.Length; i++)
            {
                msg.Delete(layers[i]);
            }

            layers[0].EntryEffect = LayerEffect.Empty;

            return msg;
        }
    }
}
