using System;
using System.Xml.Serialization;

namespace ProWrite.UFE.Entity
{
    /// <summary>
    /// Layer type
    /// </summary>
    public enum ContentType : byte
    {
        TEXT,
        //??
        PAINT,
        DLT,
        PNG,
        MPEG,
        LIVEVIDEO,
    }
}
