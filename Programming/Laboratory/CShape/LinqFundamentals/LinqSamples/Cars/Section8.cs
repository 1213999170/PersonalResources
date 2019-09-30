using System;
using System.Collections.Generic;
using System.Data.Entity;
using System.IO;
using System.Linq;
using System.Linq.Expressions;
using System.Text;
using System.Threading.Tasks;

namespace Cars
{
    class Section8
    {
        static void Main(string[] args)
        {
            Func<int, int> square = x => x * x;
            Expression<Func<int, int, int>> add = (x1, y1) => x1 + y1;

            var result = add.Compile()(3, 5);
            Console.WriteLine(result);
            Console.WriteLine(add);
            //Database.SetInitializer(new DropCreateDatabaseIfModelChanges<CarDb>());

            //InsertData();
            //QueryData();
        }

        private static void QueryData()
        {
            var db = new CarDb();
            db.Database.Log = Console.WriteLine;

            //var query = from car in db.Cars
            //            orderby car.Combined descending, car.Name ascending
            //            select car;
            var query =
                db.Cars.OrderByDescending(c => c.Combined)
                       .ThenBy(c => c.Name);

            foreach (var car in query.Take(10))
            {
                Console.WriteLine($"{car.Name}: {car.Combined}");
            }
        }

        private static void InsertData()
        {
            var cars = ProcessCars("fuel.csv");
            var db = new CarDb();

            db.Database.Log = Console.WriteLine;

            if (!db.Cars.Any())
            {
                foreach (var car in cars)
                {
                    db.Cars.Add(car);
                }
                db.SaveChanges();
            }
        }

        private static List<Car> ProcessCars(string path)
        {
            return File.ReadAllLines(path)
                .Skip(1)
                .Where(line => line.Length > 1)
                .ToCar()
                .ToList();

            //var query = 
            //    from line in File.ReadAllLines(path).Skip(1)
            //    where line.Length > 1
            //    select Car.ParseFromCsv(line);

            //return query.ToList();
        }
    }
}
