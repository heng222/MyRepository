using System;

namespace ProWrite.UFE.Entity
{
    [Serializable]
    public struct VariableTimeType
    {
        //public TimeFormat Format;
        public int DLTSource;
        public int DLTField;
        public bool DLTisLocal;
        public FontInfoType FontInfo;
    }
}
