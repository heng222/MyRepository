using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using NUnit.Framework;
using Moq;

namespace NUnitStudy.Mocks
{
    public class Person : IEntity
    {
        public string FirstName { get; set; }
        public string LastName { get; set; }
    }

    [TestFixture]
    public class PersonServiceTest
    {
        [Test]
        public void Should_Return_Two_Persons_With_FirstName_John_By_Manual()
        {
            // Given
            var repository = new PersonMockRepository();
            var service = new PersonService(repository);

            // When
            var persons = service.Query(p => p.FirstName == "John");

            // Then
            Assert.AreEqual(2,persons.Count(), "Should return 2 persons with first name John.");
        }

        [Test]
        public void Should_Return_Two_Persons_With_FirstName_John_By_Moq()
        {
            // Given
            var repository = new Mock<IRepository<Person>>();

            var data = new List<Person>
            {
                new Person {FirstName = "John", LastName = "Doe"},
                new Person {FirstName = "Jane", LastName = "Doe"},
                new Person {FirstName = "John", LastName = "Smith"},
                new Person {FirstName = "Matthew", LastName = "MacDonald"},
                new Person {FirstName = "Andrew", LastName = "MacDonald"}
            };

            repository.Setup(r => r.GetAll()).Returns(data);

            var people = new PersonService(repository.Object);

            // When
            var persons = people.Query(p => p.FirstName == "John");

            // Then
            Assert.AreEqual(persons.Count(), 2, "Should return 2 persons with first name John.");
        }
    }

   

    
}
