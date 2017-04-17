using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace ProWrite.Core
{
    public interface IConverter
    {
        object Convert(object source);
    }
    public interface IConverter<TSource, TTarget> : IConverter
    {
        TTarget Convert(TSource source);
    }

    public abstract class ConverterBase<TSource, TTarget>:IConverter<TSource,TTarget>
    {
        public abstract TTarget Convert(TSource source);
        object IConverter.Convert(object source)
        {
            return Convert((TSource)source);
        }
    }

   
}
