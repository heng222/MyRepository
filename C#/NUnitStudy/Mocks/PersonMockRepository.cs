using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace NUnitStudy.Mocks
{
    public class PersonMockRepository : IRepository<Person>
    {
        private static IEnumerable<Person> _people;

        private static IEnumerable<Person> GetPeople()
        {
            if (_people != null) return _people;

            _people = new List<Person>
            {
                new Person {FirstName = "John", LastName = "Doe"},
                new Person {FirstName = "Jane", LastName = "Doe"},
                new Person {FirstName = "John", LastName = "Smith"},
                new Person {FirstName = "Matthew", LastName = "MacDonald"},
                new Person {FirstName = "Andrew", LastName = "MacDonald"}
            };

            return _people;
        }

        public IEnumerable<Person> GetAll()
        {
            return GetPeople();
        }
    }
}
