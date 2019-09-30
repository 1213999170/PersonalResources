using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
//using Features.Linq;

namespace Features
{
    class Program
    {
        static void Main(string[] args)
        {
            Func<int, int> square = x => x * x;
            Func<int, int, int> add = (x, y) =>
            {
                int temp = x + y;
                return temp;
            };

            Action<int> write = x => Console.WriteLine(x);

            write(square(add(3, 5)));

            var developers = new Employee[]
            {
                new Employee { Id = 1, Name = "Scott" },
                new Employee { Id = 2, Name = "Chris" }
            };

            var sales = new List<Employee>()
            {
                new Employee { Id = 3, Name = "Alex" }
            };

            var query = developers.Where(e => e.Name.Length == 5)
                                               .OrderBy(e => e.Name);
            var query2 = from developer in developers
                         where developer.Name.Length == 5
                         orderby developer.Name
                         select developer;

            foreach (var employee in query2)
            {
                Console.WriteLine(employee.Name);
            }

            var name = "Scott";
            Console.WriteLine(name is int);
            Console.WriteLine(name is string);

            //foreach (var employee in developers.Where(
            //    delegate (Employee employee)
            //    {
            //        return employee.Name.StartsWith("S");
            //    }))
            //foreach (var employee in developers.Where(e => e.Name.StartsWith("S")))
            //{
            //    Console.WriteLine(employee.Name);
            //}

            //Console.WriteLine(developers.Count());

            //IEnumerator<Employee> enumerator = sales.GetEnumerator();
            //while (enumerator.MoveNext())
            //{
            //    Console.WriteLine(enumerator.Current.Name);
            //}

            // Query Syntax
            //string[] cities =
            //{
            //    "Boston",
            //    "Los Angeles",
            //    "Seattle",
            //    "London",
            //    "Hyderabad"
            //};

            //IEnumerable<string> filteredCities =
            //    from city in cities
            //    where city.StartsWith("L") && city.Length < 15
            //    orderby city
            //    select city;

            // Lambda Expressions
            //IEnumerable<string> filteredList = cities.Where(StartsWithL);
            //IEnumerable<string> filteredList = cities.Where(delegate(string s) { return s.StartsWith("L"); });
            //IEnumerable<string> filteredList = cities.Where(s => s.StartsWith("L"));
        }
        
        private static bool NameStartsWithS(Employee employee)
        {
            return employee.Name.StartsWith("S");
        }

        //public bool StartsWithL(string name)
        //{
        //    return name.StartsWith("L");
        //}
    }
}
