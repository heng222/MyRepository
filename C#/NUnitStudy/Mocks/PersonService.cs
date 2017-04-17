using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace NUnitStudy.Mocks
{
    public class PersonService
    {
        private readonly IRepository<Person> _repository;

        public PersonService(IRepository<Person> repository)
        {
            this._repository = repository;
        }

        public IEnumerable<Person> Query(Func<Person, bool> predicate)
        {
            return this._repository.GetAll().Where(predicate).ToList();
        }
    }
}
