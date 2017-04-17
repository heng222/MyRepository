using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace ProWrite.Core
{
    public interface ICopyable
    {
        object Copy();
    }
    public interface ICloneable<T>
    {
        T Copy();
    }
    public interface ICopyable<T>:ICopyable
        where T:class 
    {
        new T Copy();
        T NewInstance();
        void FromTo(T item);
    }
}
