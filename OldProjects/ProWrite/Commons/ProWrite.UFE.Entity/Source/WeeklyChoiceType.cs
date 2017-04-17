using System;

namespace ProWrite.UFE.Entity
{

    [Flags]
    public enum WeeklyChoiceType : byte
    {
        M = 1,//1
        T = M * 2,//2
        W = T * 2,//3
        TH = W * 2,//4
        F = TH * 2,//5
        S = F * 2,//6
        SU = S * 2,//7
        MTWTHFSSU = M | T | W | TH | F | S | SU,
    }
      
}
