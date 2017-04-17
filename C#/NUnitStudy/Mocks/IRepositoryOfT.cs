using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace NUnitStudy.Mocks
{
    public interface IRepository<out T> where T : IEntity
    {
        IEnumerable<T> GetAll();
    }
}
